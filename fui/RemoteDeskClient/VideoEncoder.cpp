// ============================================================================
// VideoEncoder.cpp — FFmpeg H.264 编码
// ============================================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <cstdio>
#include <cstring>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

#include "VideoEncoder.h"

bool VideoEncoder::init(int iw, int ih, int fps, int bitrateKbps) {
    close();
    w = iw; h = ih;

    const char* names[] = { "h264_nvenc", "h264_mf", "libopenh264" };
    const AVCodec* codec = nullptr;
    for (const char* n : names) {
        codec = avcodec_find_encoder_by_name(n);
        if (codec) { name = n; break; }
    }
    if (!codec) { printf("[enc] no usable h264 encoder\n"); return false; }

    enc = avcodec_alloc_context3(codec);
    if (!enc) return false;
    enc->width = w;
    enc->height = h;
    enc->time_base = AVRational{ 1, fps };
    enc->framerate = AVRational{ fps, 1 };
    enc->pix_fmt = AV_PIX_FMT_NV12;
    enc->bit_rate = bitrateKbps * 1000;
    enc->gop_size = fps * 2;               // 2 秒一个关键帧（低延迟远程桌面可更长）
    enc->max_b_frames = 0;                 // 无 B 帧，低延迟
    enc->thread_count = 1;
    enc->flags |= AV_CODEC_FLAG_LOW_DELAY;

    if (name == "h264_nvenc") {
        av_opt_set(enc->priv_data, "preset", "p1", 0);       // 最低延迟档
        av_opt_set(enc->priv_data, "tune", "ll", 0);
        av_opt_set(enc->priv_data, "zerolatency", "1", 0);
        av_opt_set(enc->priv_data, "rc", "cbr", 0);
        av_opt_set(enc->priv_data, "repeat-headers", "1", 0); // 每个关键帧带 SPS/PPS（无缝加入）
        av_opt_set(enc->priv_data, "bf", "0", 0);
    } else if (name == "libopenh264") {
        av_opt_set(enc->priv_data, "slice_mode", "auto", 0);
        av_opt_set(enc->priv_data, "rc_mode", "bitrate", 0);
    }

    int ret = avcodec_open2(enc, codec, nullptr);
    if (ret < 0) {
        char err[128] = { 0 };
        av_strerror(ret, err, sizeof(err));
        printf("[enc] avcodec_open2(%s) failed: %s\n", name.c_str(), err);
        avcodec_free_context(&enc);
        enc = nullptr;
        name.clear();
        // 回退尝试下一个可用编码器
        for (const char* n : names) {
            if (codec == avcodec_find_encoder_by_name(n)) continue;   // 跳过刚失败的
            const AVCodec* alt = avcodec_find_encoder_by_name(n);
            if (!alt) continue;
            enc = avcodec_alloc_context3(alt);
            if (!enc) continue;
            enc->width = w; enc->height = h;
            enc->time_base = AVRational{ 1, fps };
            enc->framerate = AVRational{ fps, 1 };
            enc->pix_fmt = AV_PIX_FMT_NV12;
            enc->bit_rate = bitrateKbps * 1000;
            enc->gop_size = fps * 2;
            enc->max_b_frames = 0;
            enc->thread_count = 1;
            enc->flags |= AV_CODEC_FLAG_LOW_DELAY;
            if (std::string(n) == "libopenh264") {
                av_opt_set(enc->priv_data, "slice_mode", "auto", 0);
                av_opt_set(enc->priv_data, "rc_mode", "bitrate", 0);
            }
            if (avcodec_open2(enc, alt, nullptr) == 0) { name = n; break; }
            avcodec_free_context(&enc);
            enc = nullptr;
        }
        if (!enc) { printf("[enc] all fallback encoders failed\n"); return false; }
        printf("[enc] fell back to %s\n", name.c_str());
    }

    frame = av_frame_alloc();
    if (!frame) { close(); return false; }
    frame->format = AV_PIX_FMT_NV12;
    frame->width = w;
    frame->height = h;
    if (av_frame_get_buffer(frame, 32) < 0) { close(); return false; }

    sws = sws_getContext(w, h, AV_PIX_FMT_BGRA, w, h, AV_PIX_FMT_NV12,
                         SWS_BILINEAR | SWS_ACCURATE_RND, nullptr, nullptr, nullptr);
    if (!sws) { printf("[enc] sws_getContext failed\n"); close(); return false; }

    printf("[enc] encoder %s %dx%d @%dfps ready\n", name.c_str(), w, h, fps);
    return true;
}

bool VideoEncoder::drainPackets(std::vector<std::vector<uint8_t>>& out) {
    AVPacket* pkt = av_packet_alloc();
    if (!pkt) return false;
    bool ok = true;
    for (;;) {
        int ret = avcodec_receive_packet(enc, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) break;
        if (ret < 0) { ok = false; break; }
        out.emplace_back(pkt->data, pkt->data + pkt->size);
        av_packet_unref(pkt);
    }
    av_packet_free(&pkt);
    return ok;
}

bool VideoEncoder::encodeBGRA(const uint8_t* bgra, int64_t ptsMs,
                              std::vector<std::vector<uint8_t>>& out) {
    if (!enc || !frame || !sws) return false;
    const uint8_t* src[1] = { bgra };
    int srcStride[1] = { w * 4 };
    uint8_t* dst[2] = { frame->data[0], frame->data[1] };
    int dstStride[2] = { frame->linesize[0], frame->linesize[1] };
    sws_scale(sws, src, srcStride, 0, h, dst, dstStride);

    frame->pts = (frameIdx++) * av_rescale_q(1, AVRational{ 1, 30 }, enc->time_base);
    // 简单起见以固定 30fps 时间基；ptsMs 用于节流
    (void)ptsMs;

    int ret = avcodec_send_frame(enc, frame);
    if (ret < 0) return false;
    return drainPackets(out);
}

void VideoEncoder::flush(std::vector<std::vector<uint8_t>>& out) {
    if (!enc) return;
    avcodec_send_frame(enc, nullptr);
    drainPackets(out);
}

void VideoEncoder::close() {
    if (sws) { sws_freeContext(sws); sws = nullptr; }
    if (frame) { av_frame_free(&frame); }
    if (enc) { avcodec_free_context(&enc); }
    name.clear();
    frameIdx = 0;
}
