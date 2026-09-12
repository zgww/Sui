#define _CRT_SECURE_NO_WARNINGS

// 如果是 C++ 编译，需要告诉编译器 FFmpeg 是 C 库
#ifdef __cplusplus
extern "C" {
#endif
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <iostream>

static AVBufferRef* g_hw_device_ctx = nullptr;
static AVPixelFormat g_hw_pix_fmt = AV_PIX_FMT_NONE;
// 辅助函数：将 RGB24 数据保存为 PPM 图片
static void save_ppm(const uint8_t* data, int linesize, int width, int height, const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) return;
    // PPM 文件头：P6 表示二进制 RGB，接着是宽高和最大颜色值 255
    fprintf(f, "P6\n%d %d\n255\n", width, height);
    for (int y = 0; y < height; y++) {
        // 注意：linesize 可能包含内存对齐的 padding，必须按 linesize 步进
        fwrite(data + y * linesize, 1, width * 3, f);
    }
    fclose(f);
}
// ========== 回调函数：让解码器选择硬件像素格式 ==========
// 解码器在初始化时会调用此函数，传入它支持的所有像素格式列表。
// 我们需要从中选出硬件格式，否则解码器会回退到软件解码。
static enum AVPixelFormat get_hw_format(AVCodecContext* ctx,
    const enum AVPixelFormat* pix_fmts)
{
    for (int i = 0; pix_fmts[i] != AV_PIX_FMT_NONE; i++) {
        if (pix_fmts[i] == g_hw_pix_fmt) {
            return g_hw_pix_fmt;  // 选择硬件格式
        }
    }
    // 如果硬件格式不在列表中，回退到第一个软件格式
    std::cerr << "[WARN] 硬件像素格式不可用，回退到软件解码" << std::endl;
    return pix_fmts[0];
}
// ========== 初始化硬件解码器 ==========
// 返回值：视频流的索引，失败返回 -1
static int init_hw_decoder(AVFormatContext* fmt_ctx,
    AVCodecContext** out_dec_ctx,
    AVHWDeviceType target_type)
{
    // --- Step 1: 查找视频流 ---
    int video_stream_idx = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO,
        -1, -1, nullptr, 0);
    if (video_stream_idx < 0) {
        std::cerr << "[ERROR] 未找到视频流" << std::endl;
        return -1;
    }

    AVStream* video_stream = fmt_ctx->streams[video_stream_idx];
    const AVCodec* codec = avcodec_find_decoder(video_stream->codecpar->codec_id);
    if (!codec) {
        std::cerr << "[ERROR] 找不到解码器" << std::endl;
        return -1;
    }

    // --- Step 2: 确认解码器支持目标硬件加速 ---
    // 遍历解码器的硬件配置，找到匹配的硬件类型和像素格式
    bool hw_supported = false;
    for (int i = 0;; i++) {
        const AVCodecHWConfig* config = avcodec_get_hw_config(codec, i);
        if (!config) break;

        if ((config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX) &&
            config->device_type == target_type)
        {
            g_hw_pix_fmt = config->pix_fmt;
            hw_supported = true;
            std::cout << "[INFO] 找到硬件配置: "
                << av_hwdevice_get_type_name(target_type)
                << ", 像素格式: "
                << av_get_pix_fmt_name(g_hw_pix_fmt) << std::endl;
            break;
        }
    }

    if (!hw_supported) {
        std::cerr << "[ERROR] 解码器 " << codec->name
            << " 不支持 " << av_hwdevice_get_type_name(target_type)
            << " 硬件加速" << std::endl;
        return -1;
    }

    // --- Step 3: 创建硬件设备上下文 ---
    // 第二个参数是设备名称，nullptr 表示使用默认设备
    // 对于多 GPU 系统，可以指定如 "0", "1" 或 "/dev/dri/renderD128"
    int ret = av_hwdevice_ctx_create(&g_hw_device_ctx, target_type,
        nullptr, nullptr, 0);
    if (ret < 0) {
        std::cerr << "[ERROR] 创建硬件设备上下文失败 (错误码: " << ret << ")" << std::endl;
        return -1;
    }

    // --- Step 4: 配置解码器上下文 ---
    AVCodecContext* dec_ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(dec_ctx, video_stream->codecpar);

    // 关键：绑定硬件设备上下文
    dec_ctx->hw_device_ctx = av_buffer_ref(g_hw_device_ctx);
    // 关键：设置像素格式选择回调
    dec_ctx->get_format = get_hw_format;

    ret = avcodec_open2(dec_ctx, codec, nullptr);
    if (ret < 0) {
        std::cerr << "[ERROR] 打开解码器失败" << std::endl;
        avcodec_free_context(&dec_ctx);
        return -1;
    }

    *out_dec_ctx = dec_ctx;
    return video_stream_idx;
}

int main(int argc, char* argv[]) {
    //if (argc < 2) {
    //    printf("用法: %s <输入视频路径>\n", argv[0]);
    //    return 1;
    //}
    SetConsoleOutputCP(65001);

    const char* in_filename = "http://vjs.zencdn.net/v/oceans.mp4";// argv[1];
    const char* out_filename = "output_frame.ppm";

    char exeFileName[1024];
    GetModuleFileNameA(NULL, exeFileName, sizeof(exeFileName));
    char* lastO = strrchr(exeFileName, '\\');
    *lastO = 0;
    printf("exeFileName:%s\n", exeFileName);
    //const char* dllPath = ".\\depends";
    //SetDllDirectoryA(exeFileName);

    AVFormatContext* fmt_ctx = NULL;
    AVCodecContext* codec_ctx = NULL;
    AVFrame* frame = NULL;
    AVPacket* pkt = NULL;
    int video_stream_idx = -1;

    // 1. 打开视频文件 (解封装)
    if (avformat_open_input(&fmt_ctx, in_filename, NULL, NULL) < 0) {
        fprintf(stderr, "无法打开视频文件\n"); return -1;
    }
    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        fprintf(stderr, "无法获取流信息\n"); return -1;
    }


    AVHWDeviceType hw_type = AV_HWDEVICE_TYPE_CUDA;
    //hw_type = AV_HWDEVICE_TYPE_D3D11VA;
    video_stream_idx = init_hw_decoder(fmt_ctx, &codec_ctx, hw_type);
    if (video_stream_idx < 0) return 1;

    //默认的解码器
    if (0) {
        // 2. 找到最佳视频流
        video_stream_idx = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
        if (video_stream_idx < 0) {
            fprintf(stderr, "未找到视频流\n"); return -1;
        }

        // 3. 初始化解码器
        const AVCodec* codec = avcodec_find_decoder(fmt_ctx->streams[video_stream_idx]->codecpar->codec_id);


        codec_ctx = avcodec_alloc_context3(codec);
        avcodec_parameters_to_context(codec_ctx, fmt_ctx->streams[video_stream_idx]->codecpar);
        if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
            fprintf(stderr, "无法打开解码器\n"); return -1;
        }
    }

    // 4. 准备像素格式转换 (从视频原生格式 -> RGB24)
    struct SwsContext* sws_ctx = sws_getContext(
        codec_ctx->width, codec_ctx->height, 
        AV_PIX_FMT_NV12,
        //codec_ctx->pix_fmt,
        codec_ctx->width, codec_ctx->height, 
        AV_PIX_FMT_RGB24,
        //AV_PIX_FMT_RGBA,
        SWS_BILINEAR, NULL, NULL, NULL);


    // 【核心修复】：使用标准的指针数组和步长数组
    uint8_t* dst_data[4] = { 0 };
    int dst_linesize[4] = { 0 };
    // 分配 RGB24 内存
    auto ret = av_image_alloc(dst_data, dst_linesize, codec_ctx->width, codec_ctx->height, 
        //AV_PIX_FMT_RGBA,
        AV_PIX_FMT_RGB24,
        1);
    if (ret < 0) {
        fprintf(stderr, "无法分配目标图像内存\n");
        return -1;
    }

    //uint8_t* rgb_data = NULL;
    //int rgb_linesize = 0;
    //av_image_alloc(&rgb_data, &rgb_linesize, codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB24, 1);

    // 5. 分配 Packet 和 Frame
    pkt = av_packet_alloc();
    frame = av_frame_alloc();// CPU 帧
    AVFrame* hw_frame = av_frame_alloc();   // GPU 帧

    int cnt = 0;
    // 6. 读取并解码，直到拿到第一帧
    while (av_read_frame(fmt_ctx, pkt) >= 0) {
        if (pkt->stream_index == video_stream_idx) {
            avcodec_send_packet(codec_ctx, pkt);
            while (avcodec_receive_frame(codec_ctx, hw_frame) == 0) {
                if (hw_frame->format == g_hw_pix_fmt) {
                    // ====== 关键：将帧从 GPU 显存传输到 CPU 内存 ======
                    ret = av_hwframe_transfer_data(frame, hw_frame, 0);
                    if (ret < 0) {
                        std::cerr << "[ERROR] GPU->CPU 帧传输失败" << std::endl;
                        continue;
                    }
                    // 现在 sw_frame 中包含 CPU 可访问的像素数据
                    // sw_frame->data[0], sw_frame->linesize[0] 等可正常使用
                    std::cout << "[HW] 解码帧 #"
                        << " (" << frame->width << "x" << frame->height << ")"
                        << " format" << frame->format
                        << std::endl;


                    // 成功解码出一帧，进行像素转换
                    auto height_of_slice = sws_scale(sws_ctx, (const uint8_t* const*)frame->data, frame->linesize, 0,
                        codec_ctx->height, dst_data, dst_linesize);

                    if (height_of_slice > 0) {
                        // 保存为图片
                        save_ppm(dst_data[0], dst_linesize[0], codec_ctx->width, codec_ctx->height, out_filename);
                        printf("成功提取第%d帧并保存为 %s\n", cnt, out_filename);
                        cnt++;
                        if (cnt > 30) {
                            goto cleanup; // 只要第一帧，直接跳到清理阶段
                        }
                    }
                    else {
                        printf("sws_scale 异常:%d\n", height_of_slice);
                    }
                }

            }
        }
        av_packet_unref(pkt);
    }

cleanup:
    // 7. 释放所有资源
    av_packet_free(&pkt);
    av_frame_free(&frame);
    avcodec_free_context(&codec_ctx);
    avformat_close_input(&fmt_ctx);
    sws_freeContext(sws_ctx);
    //av_freep(&rgb_data); // 释放 av_image_alloc 分配的内存

    return 0;
}