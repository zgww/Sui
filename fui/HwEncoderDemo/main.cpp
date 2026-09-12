// ============================================================================
// main.cpp — HwEncoderDemo 硬件编码 DEMO（独立验证 FFmpeg 硬件编码链路）
// ----------------------------------------------------------------------------
// 功能：
//   1. 内置生成 NV12 测试画面（标准彩条 + 移动方块 + 帧号）
//   2. 自动尝试硬件编码器：h264_nvenc(NVIDIA) -> h264_mf(MediaFoundation 硬件)
//      -> libopenh264(软件兜底)，逐个打印可用性
//   3. 编码 N 帧输出 out.h264 裸流，打印性能统计（fps/码率/帧大小）
//
// 用法: HwEncoderDemo.exe [帧数] [宽] [高] [码率kbps]
// 示例: HwEncoderDemo.exe 300 1280 720 4000
// ============================================================================
#include <cstdio>
#include <cstring>
#include <string>
#include <chrono>
#include <vector>
#include <Windows.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/pixfmt.h>
#include <libavutil/imgutils.h>
}

static const char* _errstr(int err) {
    static char buf[128];
    av_strerror(err, buf, sizeof(buf));
    return buf;
}

// ---------------- NV12 测试源生成 ----------------
// 标准 100% 彩条 YUV 值（Y, U, V）
static const int kBarY[8]  = { 180, 16, 118, 16, 146, 16, 82, 235 };
static const int kBarU[8]  = { 128, 128, 128, 128, 44, 44, 44, 128 };
static const int kBarV[8]  = { 128, 128, 128, 128, 148, 148, 148, 128 };

static void fillTestFrame(AVFrame* f, int64_t frameNo) {
    int w = f->width, h = f->height;
    uint8_t* y = f->data[0];
    uint8_t* uv = f->data[1];
    int yStride = f->linesize[0];
    int uvStride = f->linesize[1];

    // Y 平面：8 段彩条 + 移动白色方块
    for (int row = 0; row < h; row++) {
        uint8_t* line = y + (size_t)row * yStride;
        for (int col = 0; col < w; col++) {
            int bar = (col * 8) / w;
            line[col] = (uint8_t)kBarY[bar];
        }
    }
    // 移动方块（白）
    int sq = w / 8;
    int sx = (int)((frameNo * (w / 40)) % (w - sq));
    int sy = (int)((frameNo * (h / 48)) % (h - sq));
    for (int row = sy; row < sy + sq; row++)
        for (int col = sx; col < sx + sq; col++)
            y[(size_t)row * yStride + col] = 235;

    // UV 平面（色度，随列分段）
    for (int row = 0; row < h / 2; row++) {
        uint8_t* line = uv + (size_t)row * uvStride;
        for (int col = 0; col < w; col += 2) {
            int bar = (col * 8) / w;
            line[col] = (uint8_t)kBarU[bar];
            line[col + 1] = (uint8_t)kBarV[bar];
        }
    }
}

// ---------------- 编码器探测与配置 ----------------
struct EncoderResult {
    std::string name;
    bool        ok = false;
    int64_t     bytes = 0;
    double      encodeMs = 0;
    int         frames = 0;
    int         w = 0, h = 0;
};

// 尝试打开一个编码器；成功返回 0
static int tryOpenEncoder(const std::string& name, AVCodecContext** outCtx,
                          int w, int h, int fps, int kbps) {
    const AVCodec* codec = avcodec_find_encoder_by_name(name.c_str());
    if (!codec) { printf("  [%s] encoder not found in this ffmpeg build\n", name.c_str()); return -1; }

    AVCodecContext* c = avcodec_alloc_context3(codec);
    if (!c) return -1;
    c->width = w;
    c->height = h;
    c->time_base = AVRational{ 1, fps };
    c->framerate = AVRational{ fps, 1 };
    c->pix_fmt = AV_PIX_FMT_NV12;
    c->bit_rate = (int64_t)kbps * 1000;
    c->gop_size = fps * 2;
    c->max_b_frames = 0;               // 无 B 帧（低延迟）
    c->thread_count = 1;
    c->flags |= AV_CODEC_FLAG_LOW_DELAY;

    if (name == "h264_nvenc") {
        av_opt_set(c->priv_data, "preset", "p1", 0);
        av_opt_set(c->priv_data, "tune", "ll", 0);
        av_opt_set(c->priv_data, "zerolatency", "1", 0);
        av_opt_set(c->priv_data, "rc", "cbr", 0);
        av_opt_set(c->priv_data, "repeat-headers", "1", 0);
        av_opt_set(c->priv_data, "bf", "0", 0);
    } else if (name == "h264_mf") {
        av_opt_set(c->priv_data, "b", std::to_string(kbps * 1000).c_str(), 0);
        av_opt_set(c->priv_data, "bf", "0", 0);
    } else if (name == "libopenh264") {
        av_opt_set(c->priv_data, "slice_mode", "auto", 0);
        av_opt_set(c->priv_data, "rc_mode", "bitrate", 0);
    }

    int ret = avcodec_open2(c, codec, nullptr);
    if (ret < 0) {
        printf("  [%s] avcodec_open2 failed: %s\n", name.c_str(), _errstr(ret));
        avcodec_free_context(&c);
        return -1;
    }
    *outCtx = c;
    return 0;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(65001);
    setvbuf(stdout, nullptr, _IONBF, 0);

    int totalFrames = argc > 1 ? atoi(argv[1]) : 300;
    int width  = argc > 2 ? atoi(argv[2]) : 1280;
    int height = argc > 3 ? atoi(argv[3]) : 720;
    int kbps   = argc > 4 ? atoi(argv[4]) : 4000;
    int fps = 30;

    printf("=== HwEncoderDemo ===\n");
    printf("source: NV12 test pattern %dx%d, %d frames @%dfps, %dkbps\n\n", width, height, totalFrames, fps, kbps);

    // 编码器回退链
    const char* chain[] = { "h264_nvenc", "h264_mf", "libopenh264" };
    AVCodecContext* enc = nullptr;
    std::string usedName;

    for (const char* n : chain) {
        printf("trying encoder [%s] ...\n", n);
        if (tryOpenEncoder(n, &enc, width, height, fps, kbps) == 0) {
            usedName = n;
            printf("  -> OK, hardware encoder %s ready\n", n);
            break;
        }
    }
    if (!enc) {
        printf("\nFATAL: no usable encoder (NVENC needs nvEncodeAPI.dll next to exe)\n");
        return 1;
    }
    printf("encoder: %s (%s)\n\n", usedName.c_str(), usedName == "libopenh264" ? "software" : "hardware");

    // 输出文件
    std::string outPath = "out.h264";
    FILE* fp = nullptr;
    fopen_s(&fp, outPath.c_str(), "wb");
    if (!fp) { printf("FATAL: cannot open %s\n", outPath.c_str()); return 1; }

    // 输入帧
    AVFrame* frame = av_frame_alloc();
    frame->format = AV_PIX_FMT_NV12;
    frame->width = width;
    frame->height = height;
    av_frame_get_buffer(frame, 32);

    AVPacket* pkt = av_packet_alloc();

    int64_t totalBytes = 0;
    auto t0 = std::chrono::steady_clock::now();

    for (int i = 0; i < totalFrames; i++) {
        // 可写保证（avcodec 可能修改 data 指针）
        av_frame_make_writable(frame);
        fillTestFrame(frame, i);
        frame->pts = i;

        int ret = avcodec_send_frame(enc, frame);
        if (ret < 0) { printf("send_frame failed: %s\n", _errstr(ret)); break; }

        while (avcodec_receive_packet(enc, pkt) == 0) {
            fwrite(pkt->data, 1, pkt->size, fp);
            totalBytes += pkt->size;
            av_packet_unref(pkt);
        }
    }

    // flush 编码器尾部缓冲
    avcodec_send_frame(enc, nullptr);
    while (avcodec_receive_packet(enc, pkt) == 0) {
        fwrite(pkt->data, 1, pkt->size, fp);
        totalBytes += pkt->size;
        av_packet_unref(pkt);
    }

    auto t1 = std::chrono::steady_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    fclose(fp);
    printf("=== RESULT ===\n");
    printf("encoder      : %s\n", usedName.c_str());
    printf("frames       : %d\n", totalFrames);
    printf("output       : %s (%.1f KB)\n", outPath.c_str(), totalBytes / 1024.0);
    printf("encode time  : %.1f ms\n", ms);
    printf("throughput   : %.1f fps\n", totalFrames * 1000.0 / ms);
    printf("bitrate      : %.0f kbps\n", totalBytes * 8.0 * fps / 1000.0 / totalFrames);
    if (totalFrames > 0)
        printf("avg frame    : %.1f KB\n", totalBytes / 1024.0 / totalFrames);

    // 硬件编码器额外信息
    if (enc->hw_frames_ctx)
        printf("hw_frames_ctx: yes (GPU memory)\n");

    av_packet_free(&pkt);
    av_frame_free(&frame);
    avcodec_free_context(&enc);
    printf("\nDone. Verify with: ffmpeg -i out.h264 -f null -\n");
    return 0;
}
