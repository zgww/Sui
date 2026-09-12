// ============================================================================
// main.cpp — RemoteDeskClient 远程桌面客户端（fui UI）
// ----------------------------------------------------------------------------
// 功能：
//   - 连接中转服务器，注册本机（获取设备码，密码可改）
//   - 输入目标设备码+密码 -> 控制对方（远程画面 GPU 硬解渲染 + 本机输入转发）
//   - 被他人控制（屏幕 DXGI 采集 -> NVENC 编码 -> 服务器中转 + 输入注入）
// 用法: RemoteDeskClient.exe [serverHost] [serverPort]
// ============================================================================
#include <Windows.h>
#include <cstdio>
#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

#include "Core/App.h"
#include "Core/Window.h"
#include "Core/Timer.h"
#include "Urgc/Urgc.h"
#include "Layout/LayoutLinear.h"
#include "View/Button.h"
#include "View/EditText.h"
#include "View/TextView.h"

#include "Network.h"
#include "ScreenCapture.h"
#include "VideoEncoder.h"
#include "InputHook.h"
#include "RemoteVideoView.h"

using namespace rdproto;

// ============================ 全局状态 ========================================
static NetClient         g_net;
static InputHook         g_hook;
static InputInject       g_inject;
static std::atomic<bool> g_controlledActive{false};   // 被控采集线程运行标志
static std::thread       g_ctrlThread;                // 被控采集+编码+发送线程
static std::atomic<bool> g_amController{false};       // 我是控制方（会话中）
static std::atomic<bool> g_amControlled{false};       // 我是被控方（会话中）
static std::atomic<bool> g_pendingConnect{false};     // 已发 CONNECT 等待结果

static std::mutex           g_stateMtx;
static std::string          g_myCode, g_myPass = "1234";
static std::string          g_serverStatus = "未连接";
static std::string          g_sessionStatus = "空闲";
static std::string          g_targetCode, g_targetPass = "1234";
static std::atomic<bool>    g_autoConnect{false};   // 命令行自动连接（联调用）

static Ref<EditText> g_etServer, g_etMyPass, g_etTargetCode, g_etTargetPass;
static Ref<TextView> g_tvServer, g_tvMy, g_tvSession;
static Ref<RemoteVideoView> g_video;

// ============================ 会话控制 ========================================

static void stopSession() {
    if (g_amController) {
        g_hook.stop();
        g_video->stopStream();
        g_amController = false;
    }
    if (g_amControlled) {
        g_controlledActive = false;
        if (g_ctrlThread.joinable()) g_ctrlThread.join();
        g_amControlled = false;
    }
    g_pendingConnect = false;
    {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_sessionStatus = "已断开";
    }
}

static void startControllerSide() {
    g_amController = true;
    g_pendingConnect = false;
    // 钩子目标：本客户端窗口（FindWindow 按标题）
    HWND hwnd = FindWindowW(nullptr, L"远程桌面客户端");
    if (hwnd) g_hook.start(hwnd);
    g_video->startStream();
    {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_sessionStatus = "正在控制 " + g_targetCode;
    }
}

static void startControlledSide() {
    g_amControlled = true;
    g_pendingConnect = false;
    g_controlledActive = true;
    g_ctrlThread = std::thread([] {
        ScreenCapture cap;
        VideoEncoder enc;
        if (!cap.init()) {
            printf("[client] capture init failed\n");
            g_controlledActive = false;
            return;
        }
        int lastW = 0, lastH = 0;
        std::vector<uint8_t> bgra;
        std::vector<std::vector<uint8_t>> pkts;
        auto lastSend = std::chrono::steady_clock::now();
        int64_t frameNo = 0;
        while (g_controlledActive && g_net.connected()) {
            int w = 0, h = 0;
            if (cap.captureBGRA(bgra, w, h)) {
                if (w != lastW || h != lastH) {
                    if (!enc.init(w, h, 30, 6000)) {
                        g_controlledActive = false;
                        return;
                    }
                    lastW = w; lastH = h;
                    printf("[client] screen %dx%d\n", w, h);
                }
                // 30fps 节流
                auto now = std::chrono::steady_clock::now();
                auto need = std::chrono::milliseconds(33);
                if (now - lastSend < need) {
                    std::this_thread::sleep_for(need - (now - lastSend));
                }
                lastSend = std::chrono::steady_clock::now();

                pkts.clear();
                if (enc.encodeBGRA(bgra.data(), frameNo++, pkts)) {
                    for (auto& p : pkts) {
                        std::vector<uint8_t> payload(p.size() + 8);
                        memcpy(payload.data(), &frameNo, 8);   // pts 占位（渲染端按节流显示）
                        memcpy(payload.data() + 8, p.data(), p.size());
                        if (!g_net.send(S2C_VIDEO, payload)) break;
                    }
                }
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
        printf("[client] controlled session thread exit\n");
    });
    {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_sessionStatus = "正被他人控制";
    }
}

// ============================ 网络消息处理（recv 线程） ========================

static void onNetMessage(uint8_t type, const uint8_t* payload, uint32_t len) {
    switch (type) {
    case 0: {   // 连接断开（自定义）
        if (g_amController || g_amControlled || g_pendingConnect) stopSession();
        {
            std::lock_guard<std::mutex> lk(g_stateMtx);
            g_serverStatus = "服务器连接断开";
        }
        break;
    }
    case S2C_REGISTERED: {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_myCode.assign((const char*)payload, strnlen((const char*)payload, len));
        g_serverStatus = "已注册，设备码 " + g_myCode;
        printf("[client] registered code=%s\n", g_myCode.c_str());
        if (g_autoConnect) {
            g_pendingConnect = true;
            std::string p = g_targetCode;
            p.push_back(0);
            p += g_targetPass;
            p.push_back(0);
            g_net.send(C2S_CONNECT, p.data(), (uint32_t)p.size());
        }
        break;
    }
    case S2C_CONNECT_OK: {
        if (g_pendingConnect) {
            startControllerSide();          // 我发起的连接 -> 我是控制方
        } else {
            startControlledSide();          // 服务器通知 -> 我是被控方
        }
        break;
    }
    case S2C_CONNECT_FAIL: {
        std::string reason((const char*)payload, strnlen((const char*)payload, len));
        g_pendingConnect = false;
        {
            std::lock_guard<std::mutex> lk(g_stateMtx);
            g_sessionStatus = "连接失败: " + reason;
        }
        printf("[client] connect fail: %s\n", reason.c_str());
        break;
    }
    case S2C_PEER_CLOSED: {
        printf("[client] peer closed\n");
        stopSession();
        break;
    }
    case S2C_VIDEO: {
        // 视频帧（被控端 -> 控制端，经服务器）：pts(8B) + H.264 数据
        if (len > 8) g_video->feedPacket(payload + 8, len - 8);
        break;
    }
    case C2S_INPUT: {
        // 输入事件（控制端 -> 被控端）：InputEvent 数组
        size_t n = len / sizeof(InputEvent);
        int sw = GetSystemMetrics(SM_CXSCREEN);
        int sh = GetSystemMetrics(SM_CYSCREEN);
        for (size_t i = 0; i < n; i++) {
            InputEvent e;
            memcpy(&e, payload + i * sizeof(InputEvent), sizeof(e));
            g_inject.handle(e, sw, sh);
        }
        break;
    }
    default:
        break;
    }
}

// ============================ UI 操作 =========================================

static void connectServer() {
    if (g_net.connected()) { g_net.disconnect(); }

    std::string addr = g_etServer ? g_etServer->value : "127.0.0.1:20000";
    std::string host = addr;
    int port = 20000;
    size_t colon = addr.rfind(':');
    if (colon != std::string::npos) {
        host = addr.substr(0, colon);
        port = atoi(addr.substr(colon + 1).c_str());
    }

    if (!g_net.connectTo(host, port)) {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_serverStatus = "连接服务器失败";
        return;
    }
    g_net.setHandler(onNetMessage);
    {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_serverStatus = "已连接，注册中...";
        g_myPass = g_etMyPass ? g_etMyPass->value : g_myPass;
    }
    // 注册：name\0password\0
    std::string payload = "RemoteDeskClient";
    payload.push_back(0);
    payload += g_myPass;
    payload.push_back(0);
    g_net.send(C2S_REGISTER, payload.data(), (uint32_t)payload.size());
}

static void requestConnect() {
    if (!g_net.connected()) {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_sessionStatus = "请先连接服务器";
        return;
    }
    if (g_amController || g_amControlled) {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_sessionStatus = "已在会话中，请先断开";
        return;
    }
    std::string code = g_etTargetCode ? g_etTargetCode->value : "";
    std::string pass = g_etTargetPass ? g_etTargetPass->value : "";
    if (code.empty()) {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_sessionStatus = "请输入目标设备码";
        return;
    }
    g_targetCode = code;
    g_targetPass = pass;
    g_pendingConnect = true;
    std::string payload = code;
    payload.push_back(0);
    payload += pass;
    payload.push_back(0);
    g_net.send(C2S_CONNECT, payload.data(), (uint32_t)payload.size());
    {
        std::lock_guard<std::mutex> lk(g_stateMtx);
        g_sessionStatus = "连接中 " + code + "...";
    }
}

// ============================ main ===========================================

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(65001);
    setvbuf(stdout, nullptr, _IONBF, 0);

    urgc.start_process_thread();
    App* app = App_use();

    // 关键顺序：共享 D3D11 设备注入 fui（ANGLE 基于该设备）-> 再建窗口
    if (!RemoteVideoView::ensureSharedGpuDevice()) {
        printf("FATAL: ensureSharedGpuDevice failed\n");
        return 1;
    }

    Ref<Window> win{ new Window() };

    // ---- UI 布局 ----
    Ref<LayoutLinear> root{ new LayoutLinear() };
    root->column();
    root->width = 1100;
    root->height = 760;
    root->backgroundColor = 0xff1a1a2e;
    root->padding = Inset(8, 8, 8, 8);

    auto makeRow = [&]() {
        Ref<LayoutLinear> row{ new LayoutLinear() };
        row->row();
        row->width = 1084;
        row->height = 36;
        row->alignItems = "center";
        root->appendChild(row.get());
        return row;
    };
    auto makeLabel = [&](LayoutLinear* row, const std::string& t, float w) {
        Ref<TextView> tv{ new TextView() };
        tv->setText(t);
        tv->setColor(0xffcccccc);
        tv->setFontSize(13.0f);
        tv->width = w;
        row->appendChild(tv.get());
        return tv;
    };
    auto makeEdit = [&](LayoutLinear* row, const std::string& def, float w) {
        Ref<EditText> et{ new EditText() };
        et->setValue(def);
        et->width = w;
        et->height = 26;
        row->appendChild(et.get());
        return et;
    };
    auto makeBtn = [&](LayoutLinear* row, const std::string& label, float w) {
        Ref<Button> btn{ new Button() };
        btn->setLabel(label);
        btn->width = w;
        btn->height = 28;
        row->appendChild(btn.get());
        return btn;
    };

    // 行1：服务器
    {
        Ref<LayoutLinear> row = makeRow();
        makeLabel(row.get(), "服务器:", 60);
        g_etServer = makeEdit(row.get(), "127.0.0.1:20000", 180);
        Ref<Button> b = makeBtn(row.get(), "连接服务器", 110);
        g_tvServer = makeLabel(row.get(), "未连接", 420);
        b->onClick = CLOSURE([](MouseEvent*) { connectServer(); });
    }
    // 行2：本机信息
    {
        Ref<LayoutLinear> row = makeRow();
        makeLabel(row.get(), "我的设备码:", 90);
        g_tvMy = makeLabel(row.get(), "-", 120);
        makeLabel(row.get(), "我的密码:", 70);
        g_etMyPass = makeEdit(row.get(), "1234", 90);
        Ref<Button> b = makeBtn(row.get(), "更新注册", 90);
        b->onClick = CLOSURE([](MouseEvent*) {
            if (g_net.connected()) {
                std::lock_guard<std::mutex> lk(g_stateMtx);
                g_myPass = g_etMyPass->value;
            }
            connectServer();
        });
        Ref<TextView> tip = makeLabel(row.get(), "(本机可被此密码控制)", 220);
        tip->setColor(0xff888888);
    }
    // 行3：远程控制
    {
        Ref<LayoutLinear> row = makeRow();
        makeLabel(row.get(), "目标设备码:", 90);
        g_etTargetCode = makeEdit(row.get(), "", 120);
        makeLabel(row.get(), "目标密码:", 70);
        g_etTargetPass = makeEdit(row.get(), "1234", 90);
        Ref<Button> bc = makeBtn(row.get(), "连接并控制", 110);
        bc->onClick = CLOSURE([](MouseEvent*) { requestConnect(); });
        Ref<Button> bd = makeBtn(row.get(), "断开", 70);
        bd->onClick = CLOSURE([](MouseEvent*) {
            if (g_amController || g_amControlled) {
                g_net.send(C2S_DISCONNECT, nullptr, 0);
                stopSession();
            }
        });
        g_tvSession = makeLabel(row.get(), "空闲", 300);
    }
    // 主区：远程画面
    {
        g_video = new RemoteVideoView();
        g_video->width = 1084;
        g_video->height = 640;
        g_video->backgroundColor = 0xff000000;
        root->appendChild(g_video.get());
    }

    win->setRootView(root.get());
    win->setTitle("远程桌面客户端");
    win->setSize(1100, 760);
    win->moveToCenter();
    win->show();

    // UI 刷新 Timer（200ms）：状态文本
    static Ref<Timer> uiTimer;
    static long long g_lastFs = 0;
    uiTimer = mkTimerInterval(CLOSURE([]() {
        std::string srv, my, ses;
        {
            std::lock_guard<std::mutex> lk(g_stateMtx);
            srv = g_serverStatus;
            my = g_myCode;
            ses = g_sessionStatus;
        }
        if (g_tvServer) g_tvServer->setText(srv);
        if (g_tvMy) {
            char buf[96];
            snprintf(buf, sizeof(buf), "%s (%s)", my.c_str(), g_net.connected() ? "在线" : "离线");
            g_tvMy->setText(buf);
        }
        if (g_tvSession) g_tvSession->setText(ses);
        // 渲染帧数日志（控制端验证画面流动）
        if (g_video && g_amController) {
            long long fs = g_video->framesShown();
            if (fs > 0 && fs != g_lastFs) {
                g_lastFs = fs;
                if (fs <= 5 || fs % 300 == 0)
                    printf("[client] remote frames shown: %lld\n", fs);
            }
        }
    }), 200);

    // 输入发送 Timer（10ms）：控制端采集事件批量发送
    static Ref<Timer> inputTimer;
    inputTimer = mkTimerInterval(CLOSURE([]() {
        if (!g_amController || !g_net.connected()) return;
        auto evs = g_hook.takeEvents();
        if (evs.empty()) return;
        std::vector<uint8_t> payload(evs.size() * sizeof(InputEvent));
        for (size_t i = 0; i < evs.size(); i++) {
            memcpy(payload.data() + i * sizeof(InputEvent), &evs[i], sizeof(InputEvent));
        }
        g_net.send(C2S_INPUT, payload);
    }), 10);

    // 命令行可传服务器地址
    {
        std::string host = argc > 1 ? argv[1] : "127.0.0.1";
        int port = argc > 2 ? atoi(argv[2]) : 20000;
        if (g_etServer) g_etServer->setValue(host + ":" + std::to_string(port));
    }

    // 启动 1 秒后自动连接服务器（命令行可覆盖 host/port）
    static Ref<Timer> bootTimer;
    static std::atomic<bool> g_booted{false};
    bootTimer = mkTimerInterval(CLOSURE([]() {
        if (!g_booted) {
            g_booted = true;
            if (bootTimer) { bootTimer->cancel(); bootTimer = nullptr; }
            connectServer();
        }
    }), 1000);

    // 自动连接目标（第 3 个参数起：目标设备码 目标密码 -> 注册后自动连接）
    if (argc > 3) {
        g_etTargetCode->setValue(argv[3]);
        g_targetCode = argv[3];
        g_etTargetPass->setValue(argc > 4 ? argv[4] : "1234");
        g_targetPass = argc > 4 ? argv[4] : "1234";
        g_autoConnect = true;
    }

    win->onClosed = CLOSURE([](Window*) {
        g_controlledActive = false;
        if (g_ctrlThread.joinable()) g_ctrlThread.join();
        g_net.disconnect();
    });

    app->runEventLoop();
    return 0;
}
