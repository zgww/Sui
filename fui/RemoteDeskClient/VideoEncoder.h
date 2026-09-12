// ============================================================================
// VideoEncoder.h — FFmpeg H.264 编码（h264_nvenc 硬件优先，回退 h264_mf/libopenh264）
// 输入 BGRA（ScreenCapture 输出）-> swscale -> NV12 -> 编码 -> H.264 包
// ============================================================================
#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct AVCodecContext;
struct AVFrame;
struct SwsContext;

class VideoEncoder {
public:
    VideoEncoder() = default;
    ~VideoEncoder() { close(); }

    // 初始化编码器（w/h 为输入 BGRA 尺寸）
    bool init(int w, int h, int fps = 30, int bitrateKbps = 6000);
    // 输入一帧 BGRA，产出 0..N 个 H.264 包（追加到 out）
    bool encodeBGRA(const uint8_t* bgra, int64_t ptsMs, std::vector<std::vector<uint8_t>>& out);
    // 收到空帧可调用 flush（收尾）
    void flush(std::vector<std::vector<uint8_t>>& out);
    void close();

    std::string encoderName() const { return name; }
    int width() const { return w; }
    int height() const { return h; }

private:
    AVCodecContext* enc = nullptr;
    AVFrame* frame = nullptr;
    SwsContext* sws = nullptr;
    std::string name;
    int w = 0, h = 0;
    int64_t frameIdx = 0;

    bool drainPackets(std::vector<std::vector<uint8_t>>& out);
};
