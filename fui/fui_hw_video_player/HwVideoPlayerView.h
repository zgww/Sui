#pragma once

// ============================================================================
// HwVideoPlayerView.h
// ----------------------------------------------------------------------------
// 基于 fui + Skia 的全 GPU 视频播放视图：
//
//   媒体 URL / 文件路径
//     |
//     v
//   FFmpeg D3D11VA 硬解码（解码帧直接落在 GPU 的 D3D11 纹理，像素不回 CPU）
//     |
//     v
//   ANGLE EGLImage 零拷贝导入（解码器与 ANGLE 共用同一 ID3D11Device）
//     |
//     v
//   GL 纹理（Y:GL_R8 / UV:GL_RG8，EGLImage 直接绑定）
//     |
//     v
//   Skia Ganesh GL 后端 GrYUVABackendTextures -> SkImage（GPU 上完成 YUV->RGB）
//     |
//     v
//   fui 窗口 SkCanvas 绘制（drawImageRect）-> eglSwapBuffers 呈现
//
// 从解码到渲染全程不经过 CPU（唯一经过 CPU 的是压缩码流读取）。
// 使用方式（注意顺序）：
//   1. HwVideoPlayerView::ensureSharedGpuDevice();   // 必须早于任何 fui Window 创建
//   2. 创建 fui Window 并把本视图挂到视图树（rootView 或任意容器）
//   3. player->open("本地路径 或 http(s)://...");      // 输入媒体 URL 即播放
// ============================================================================

#include "Core/View.h"
#include "Core/Timer.h"

#include <string>

class HwVideoPlayerView : public View {
    RTTR_ENABLE(View)
public:
    // 媒体地址（本地路径或 http(s) URL），open 时写入
    std::string url;
    bool autoPlay = true;

    HwVideoPlayerView();
    virtual ~HwVideoPlayerView();

    // 打开媒体并开始播放（本地文件路径或 http(s) URL）
    bool open(const std::string& mediaUrl);
    void play();
    void pause();
    // 停止并释放当前媒体（可再次 open）
    void close();

    bool isPlaying() const;
    bool isEnded() const;
    int getVideoWidth() const;
    int getVideoHeight() const;
    // 状态文本：idle / opening / playing / paused / ended / open failed: ...
    std::string getStatusText() const;

    // 在创建任何 fui Window 之前调用一次（幂等）：
    // 创建共享 D3D11 设备并注入 fui，使 FFmpeg 硬解与 ANGLE/Skia 渲染共用同一 GPU 设备。
    static bool ensureSharedGpuDevice();
    static void* sharedD3D11Device();

    // 全部实例累计渲染帧数（多视图并发验证用，主线程安全）
    static long long totalShownAll();
    static int instanceCount();

    // 全屏/拉伸模式（默认 contain 等比缩放居中）
    void setFitMode(int mode);   // 0=contain  1=fill(拉伸铺满)
    int getFitMode() const { return _fitMode; }

    // 调试/验证：把当前窗口 GL 表面内容读回并保存为 BMP（仅验证用，不属于播放路径）
    bool saveCurrentFrame(const char* bmpPath);

    virtual void draw_self(Canvas* canvas) override;
    virtual const char* getClassName() const override { return "HwVideoPlayerView"; }

private:
    struct Impl;
    Impl* d = nullptr;               // 实现（FFmpeg 解码线程 / 帧队列 / GPU 渲染槽）
    int _fitMode = 0;

    // 帧驱动定时器（主线程 fire，驱动 tickFrame -> invalidDraw）
    Ref<Timer> _tickTimer{nullptr, this};

    // 帧驱动：取帧 -> 生成 GPU 显示帧 -> invalidDraw
    void tickFrame();
    // 停止帧驱动定时器（close/析构时调用，打破 timer->closure->this 循环引用）
    void stopTickTimer();
};
