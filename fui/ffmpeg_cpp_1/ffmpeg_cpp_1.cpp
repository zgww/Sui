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

// 辅助函数：将 RGB24 数据保存为 PPM 图片
void save_ppm(const uint8_t* data, int linesize, int width, int height, const char* filename) {
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

    // 4. 准备像素格式转换 (从视频原生格式 -> RGB24)
    struct SwsContext* sws_ctx = sws_getContext(
        codec_ctx->width, codec_ctx->height, codec_ctx->pix_fmt,
        codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB24,
        SWS_BILINEAR, NULL, NULL, NULL);


    // 【核心修复】：使用标准的指针数组和步长数组
    uint8_t* dst_data[4] = { 0 };
    int dst_linesize[4] = { 0 };
    // 分配 RGB24 内存
    auto ret = av_image_alloc(dst_data, dst_linesize, codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB24, 1);
    if (ret < 0) {
        fprintf(stderr, "无法分配目标图像内存\n");
        return -1;
    }

    //uint8_t* rgb_data = NULL;
    //int rgb_linesize = 0;
    //av_image_alloc(&rgb_data, &rgb_linesize, codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB24, 1);

    // 5. 分配 Packet 和 Frame
    pkt = av_packet_alloc();
    frame = av_frame_alloc();

    int cnt = 0;
    // 6. 读取并解码，直到拿到第一帧
    while (av_read_frame(fmt_ctx, pkt) >= 0) {
        if (pkt->stream_index == video_stream_idx) {
            avcodec_send_packet(codec_ctx, pkt);
            while (avcodec_receive_frame(codec_ctx, frame) == 0) {
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