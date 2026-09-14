// ============================================================================
// main.cpp —— fui + HwVideoPlayerView 全 GPU 视频播放演示（支持多路并发）
// ----------------------------------------------------------------------------
// 用法：
//   fui_hw_video_player.exe [mediaUrl] [count]
//     mediaUrl : 本地文件路径或 http(s):// 网络流地址（默认播放测试视频）
//     count    : 并发播放实例数（默认 1；count>1 时网格平铺同时播放）
//   示例：
//     fui_hw_video_player.exe E:\...\oceans.mp4           单路
//     fui_hw_video_player.exe E:\...\oceans.mp4 40        40 路同时播放
//     fui_hw_video_player.exe https://.../v.mp4 40        40 路 URL 播放
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
#include <vector>

#include "Core/App.h"
#include "Core/Window.h"
#include "Urgc/Urgc.h"
#include "Layout/RowWrap.h"

#include "HwVideoPlayerView.h"

static void runPlayer(const std::string& mediaUrl, int count) {
    SetConsoleOutputCP(65001);
    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);
    printf("[main] step 1: start (count=%d)\n", count);

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

    // ---- 多路并发：RowWrap 网格平铺 ----
    std::vector<Ref<HwVideoPlayerView>> players;
    Ref<RowWrap> root{ new RowWrap() };

    const float cw = 256.0f, ch = 144.0f;   // 每格 256x144（16:9）
    const float gap = 4.0f;
    const int   cols = (count <= 1) ? 1 : 8;
    const int   rows = (count <= 1) ? 1 : (count + cols - 1) / cols;
    const int   winW = (int)(cols * cw + (cols - 1) * gap) + 16;
    const int   winH = (int)(rows * ch + (rows - 1) * gap) + 48;

    root->width = (float)winW;
    root->height = (float)winH;
    root->rowGap = gap;
    root->colGap = gap;
    root->backgroundColor = 0xff101010;

    int okCount = 0;
    for (int i = 0; i < count; i++) {
        Ref<HwVideoPlayerView> player{ new HwVideoPlayerView() };
        player->width = cw;
        player->height = ch;
        player->setFitMode(1);
        root->appendChild(player.get());
        players.push_back(player);
        if (player->open(mediaUrl)) {
            okCount++;
        } else {
            printf("[main] player[%d] open failed: %s\n", i, player->getStatusText().c_str());
        }
    }
    printf("[main] step 6: opened %d/%d players\n", okCount, count);

    win->setRootView(root.get());
    win->setTitle(std::format("fui HwVideoPlayerView x{} - FFmpeg D3D11VA -> Skia GPU (zero-copy)", count).c_str());
    win->setSize(winW, winH);
    win->moveToCenter();
    win->show();
    printf("[main] step 7: window shown %dx%d\n", winW, winH);

    printf("input media: %s\n", mediaUrl.c_str());
    printf("pipeline: D3D11VA hw-decode -> EGLImage zero-copy -> Skia GPU render (no CPU pixel path)\n");
    printf("[main] step 8: enter event loop\n");

    // 统计 Timer：每 5 秒打印全实例累计渲染帧数与帧率（static 保活，避免 TimerMgr 悬垂）
    static Ref<Timer> g_statTimer;
    g_statTimer = mkTimerInterval(CLOSURE([=]() {
        static long long lastTotal = 0;
        static double lastSec = 0.0;
        static int capAt = 0;
        long long total = HwVideoPlayerView::totalShownAll();
        double now = (double)GetTickCount64() / 1000.0;
        double dt = now - lastSec;
        if (dt >= 5.0) {
            double fpsAll = (total - lastTotal) / dt;
            printf("[stat] instances=%d totalShown=%lld allFps=%.1f perInstance=%.1f fps\n",
                   HwVideoPlayerView::instanceCount(), total, fpsAll,
                   fpsAll / (HwVideoPlayerView::instanceCount() > 0 ? HwVideoPlayerView::instanceCount() : 1));
            lastTotal = total;
            lastSec = now;
            // 验证：不同播放时刻各截一次（对比 EGLImage 缓存内容是否跟随更新）
            if (++capAt == 2 && !players.empty() && players[0].get() != nullptr) {
                players[0]->saveCurrentFrame("E:\\ws\\Sui\\fui\\fui_hw_video_player\\capA.bmp");
            }
            if (capAt == 3 && !players.empty() && players[0].get() != nullptr) {
                players[0]->saveCurrentFrame("E:\\ws\\Sui\\fui\\fui_hw_video_player\\capB.bmp");
            }
        }
    }), 1000);

    win->onClosed = CLOSURE([=](Window* w) {
        printf("window closed. totalShown=%lld\n", HwVideoPlayerView::totalShownAll());
    });

    app->runEventLoop();
}

int main(int argc, char* argv[]) {
    const char* url = "E:\\ws\\Sui\\fui\\SkiaDrawOpencvFrame\\oceans.mp4";
    url = "F:\\ws\\Sui\\fui\\fui\\x64\\Release\\oceans.mp4";
    int count = 50;
    if (argc > 1) url = argv[1];
    if (argc > 2) count = atoi(argv[2]);
    if (count < 1) count = 1;
    if (count > 100) count = 100;
    runPlayer(url, count);
    return 0;
}
