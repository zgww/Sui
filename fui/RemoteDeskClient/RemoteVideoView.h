// ============================================================================
// RemoteVideoView.h — 远程桌面画面视图（fui View）
// ----------------------------------------------------------------------------
// 全 GPU 管线（复用 HwVideoPlayerView 已验证架构）：
//   网络线程 feedPacket(H.264) -> 解码线程(独立D3D11设备 d3d11va 硬解)
//     -> 帧队列 -> 主线程 OpenSharedResource 导入共享渲染设备
//     -> ANGLE EGLImage(Y/UV 平面+数组切片) -> GrYUVABackendTextures -> Skia 绘制
// 全程零 CPU 像素回读；EGLImage/GL/SkImage 按帧池纹理缓存常驻。
// ============================================================================
#pragma once
#include <cstdint>
#include <string>
#include <memory>

#include "Core/View.h"

class RemoteVideoView : public View {
public:
    RemoteVideoView();
    ~RemoteVideoView() override;

    // 网络线程调用：喂一帧 H.264 裸流数据（编码端 AVPacket）
    void feedPacket(const uint8_t* data, size_t len);
    // 会话开始/结束
    void startStream();
    void stopStream();
    // fui 绘制
    void draw_self(Canvas* canvas) override;
    // 共享渲染设备（进程级，必须在 fui Window 创建前 ensure）
    static bool ensureSharedGpuDevice();
    static void* sharedD3D11Device();

    long long framesShown() const;

private:
    struct Impl;
    Impl* d;
    void tickFrame();
    Ref<Timer> _tickTimer;

    RTTR_ENABLE(View)
};
