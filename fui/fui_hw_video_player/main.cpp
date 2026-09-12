// ============================================================================
// main.cpp —— fui + HwVideoPlayerView 全 GPU 视频播放演示
// ----------------------------------------------------------------------------
// 用法：
//   fui_hw_video_player.exe [mediaUrl]
//   mediaUrl 可以是本地文件路径或 http(s):// 网络流地址。
//   不传参数时播放默认测试视频。
//
// 全链路 GPU 加速（解码 -> 渲染不经过 CPU）：
//   输入媒体 URL
//     -> HwVideoPlayerView::open(url)
//     -> FFmpeg D3D11VA 硬解码（NV12 帧直接落在 GPU 纹理）
//     -> ANGLE EGLImage 零拷贝导入（与 fui 窗口共用同一 D3D11 设备）
//     -> Skia GrYUVABackendTextures GPU 渲染到 fui 窗口
// ============================================================================

#include <Windows.h>
#include <cstdio>
#include <string>

#include "Core/App.h"
#include "Core/Window.h"
#include "Urgc/Urgc.h"

#include "HwVideoPlayerView.h"

static void runPlayer(const std::string& mediaUrl) {
    SetConsoleOutputCP(65001);
    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);
    printf("[main] step 1: start\n");

    urgc.start_process_thread();
    printf("[main] step 2: urgc started\n");

    App* app = App_use();
    printf("[main] step 3: App_use ok\n");

    // 关键顺序：先创建共享 D3D11 设备并注入 fui（ANGLE 将基于该设备创建 Display），
    // 然后才能创建 fui Window —— 这是 FFmpeg 硬解帧零拷贝导入 ANGLE/Skia 的前提。
    if (!HwVideoPlayerView::ensureSharedGpuDevice()) {
        printf("FATAL: HwVideoPlayerView::ensureSharedGpuDevice failed\n");
        return;
    }
    printf("[main] step 4: shared gpu device injected\n");

    Ref<Window> win{ new Window() };
    printf("[main] step 5: window created\n");
    Ref<HwVideoPlayerView> player{ new HwVideoPlayerView() };
    printf("[main] step 6: player created\n");

    win->setRootView(player.get());
    win->setTitle("fui HwVideoPlayerView - FFmpeg D3D11VA -> Skia GPU (zero-copy)");
    win->setSize(1280, 720);
    win->moveToCenter();
    win->show();
    printf("[main] step 7: window shown\n");

    printf("input media: %s\n", mediaUrl.c_str());
    if (!player->open(mediaUrl)) {
        printf("FATAL: open failed. status=%s\n", player->getStatusText().c_str());
    } else {
        printf("playing. video=%dx%d\n", player->getVideoWidth(), player->getVideoHeight());
        printf("pipeline: D3D11VA hw-decode -> EGLImage zero-copy -> Skia GPU render (no CPU pixel path)\n");

        // 验证用：播放 3 秒后从窗口 GL 表面读回一帧存 BMP（确认 GPU 画面真实渲染）。
        // 注意：Timer 由 TimerMgr 全局列表持有，局部变量块结束即析构会留下
        // 悬垂指针（后台 tick 线程访问已回收 Timer → UB 并停掉其他 Timer），
        // 因此必须用 static 保活到进程结束。
        // fui TimerMgr 复合遍历已加整体锁（g_timerMutex），多 Timer 并发安全。
        static Ref<Timer> g_capTimer;
        g_capTimer = mkTimerInterval(CLOSURE([=]() {
            static int capDone = 0;
            if (!capDone && player->getVideoWidth() > 0) {
                capDone = 1;
                player->saveCurrentFrame("frame_capture.bmp");
            }
        }), 3000);
    }
    printf("[main] step 8: enter event loop\n");

    win->onClosed = CLOSURE([=](Window* w) {
        printf("window closed. status=%s\n", player->getStatusText().c_str());
    });

    app->runEventLoop();
}

int main(int argc, char* argv[]) {
    const char* url = "E:\\ws\\Sui\\fui\\SkiaDrawOpencvFrame\\oceans.mp4";
    if (argc > 1) {
        url = argv[1];
    }
    runPlayer(url);
    return 0;
}
