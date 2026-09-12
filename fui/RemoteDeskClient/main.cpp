// ============================================================================
// main.cpp — RemoteDeskClient 远程桌面客户端（ToDesk 风格 UI）
// ----------------------------------------------------------------------------
// UI 全部采用 fui 推荐的声明式写法：RINS / RN / REND（React 式 get-or-create
// diff 渲染）。状态变化 -> 改成员 -> render() 重描，框架自动复用/增删节点。
//
// 业务链路：
//   控制端：本机输入钩子 -> 服务器中转 -> 被控端注入
//   被控端：DXGI 屏幕采集 -> 硬件编码 -> 服务器中转 -> 控制端 D3D11VA 硬解
//           -> EGLImage 零拷贝 -> Skia GPU 渲染（全程不回 CPU）
// 用法: RemoteDeskClient.exe [serverHost] [serverPort] [targetCode] [targetPass]
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
#include "Core/Node.h"
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

// ============================ 配色/尺寸 =======================================
static constexpr int NAV_W       = 232;
static constexpr int COLOR_MAIN  = 0xff2d8cf0;
static constexpr int COLOR_MAIN_D= 0xff1f7ad8;
static constexpr int COLOR_BG    = 0xfff7f8fa;
static constexpr int COLOR_TEXT  = 0xff1a1a1a;
static constexpr int COLOR_SUB   = 0xff8a8f99;
static constexpr int COLOR_BORDER= 0xffe5e6eb;
static constexpr int WIN_W       = 1280;
static constexpr int WIN_H       = 800;
static constexpr int TOPBAR_H    = 56;
static constexpr int BOTTOM_H    = 110;
static constexpr int CONTENT_H   = WIN_H - TOPBAR_H - BOTTOM_H;       // 634
static constexpr int MAIN_W      = WIN_W - NAV_W;                      // 1048
static constexpr int CARD_W      = 470;

static std::string formatCode(const std::string& s) {
    std::string out;
    for (size_t i = 0; i < s.size(); i++) { if (i > 0 && i % 3 == 0) out += ' '; out += s[i]; }
    return out;
}
static std::string digitsOnly(const std::string& s) {
    std::string out; for (char c : s) if (c >= '0' && c <= '9') out += c; return out;
}
static std::string maskPass(const std::string& p) {
    return std::string(std::max<size_t>(p.size(), 1), '*');
}

// ============================ 客户端应用 ======================================
class ClientApp {
public:
    // ---------- 窗口/视图树 ----------
    Ref<Window>       win;
    Ref<LayoutLinear> root;
    RemoteVideoView*  video = nullptr;     // RN diff 复用时回填
    EditText*         etCode = nullptr;
    EditText*         etPass = nullptr;

    // ---------- UI 状态（驱动 render） ----------
    int  curNav = 1;                       // 默认选中"远程控制"
    int  mode   = 0;                       // 0=远程控制 1=文件传输
    std::atomic<bool> uiDirty{true};

    // ---------- 业务状态（recv 线程写，UI 线程读） ----------
    std::mutex mtx;
    std::string myCode;
    std::string myPass       = "1234";
    std::string srvStatus    = "未连接服务器";
    std::string sesStatus    = "空闲";
    bool amController        = false;
    bool amControlled        = false;
    bool pending             = false;
    std::string targetCode, targetPass;
    std::string autoTargetCode, autoTargetPass;
    bool autoConnect         = false;

    std::string serverHost = "127.0.0.1";
    int         serverPort = 20000;

    // ---------- 业务组件 ----------
    NetClient              net;
    InputHook              hook;
    InputInject            inject;
    std::atomic<bool>      controlledActive{false};
    std::thread            ctrlThread;

    bool inSession() const { return amController || amControlled; }
    void markDirty() { uiDirty = true; }

    // ============================ 会话动作 ====================================
    void connectServer() {
        if (net.connected()) net.disconnect();
        if (!net.connectTo(serverHost, serverPort)) {
            std::lock_guard<std::mutex> lk(mtx);
            srvStatus = "连接服务器失败"; markDirty(); return;
        }
        net.setHandler([this](uint8_t t, const uint8_t* p, uint32_t n){ onNetMessage(t,p,n); });
        { std::lock_guard<std::mutex> lk(mtx); srvStatus = "已连接，注册中..."; markDirty(); }
        std::string payload = "RemoteDeskClient"; payload.push_back(0);
        payload += myPass; payload.push_back(0);
        net.send(C2S_REGISTER, payload.data(), (uint32_t)payload.size());
    }

    void requestConnect() {
        if (!net.connected()) { std::lock_guard<std::mutex> lk(mtx); sesStatus="请先连接服务器"; markDirty(); return; }
        if (inSession())      { std::lock_guard<std::mutex> lk(mtx); sesStatus="已在会话中，请先断开"; markDirty(); return; }
        std::string clean = digitsOnly(etCode ? etCode->value : "");
        std::string pass  = etPass ? etPass->value : "";
        if (clean.size() < 4) { std::lock_guard<std::mutex> lk(mtx); sesStatus="请输入目标设备码"; markDirty(); return; }
        if (pass.empty())     { std::lock_guard<std::mutex> lk(mtx); sesStatus="请输入目标临时密码"; markDirty(); return; }
        targetCode = clean; targetPass = pass; pending = true;
        std::string payload = clean; payload.push_back(0);
        payload += pass; payload.push_back(0);
        net.send(C2S_CONNECT, payload.data(), (uint32_t)payload.size());
        std::lock_guard<std::mutex> lk(mtx);
        sesStatus = "连接中 " + clean + "..."; markDirty();
    }

    void stopSession() {
        if (amController) { hook.stop(); if (video) video->stopStream(); amController = false; }
        if (amControlled) { controlledActive = false; if (ctrlThread.joinable()) ctrlThread.join(); amControlled = false; }
        pending = false; markDirty();
        std::lock_guard<std::mutex> lk(mtx);
        sesStatus = "已断开";
    }

    void startControllerSide() {
        amController = true; pending = false;
        HWND hwnd = FindWindowW(nullptr, L"RemoteDeskClient");
        if (hwnd) hook.start(hwnd);
        if (video) video->startStream();   // 节点已存在则直接启动；否则 render 创建时补启动
        markDirty();
        std::lock_guard<std::mutex> lk(mtx);
        sesStatus = "正在控制 " + targetCode;
    }

    void startControlledSide() {
        amControlled = true; pending = false; controlledActive = true;
        if (ctrlThread.joinable()) ctrlThread.join();
        ctrlThread = std::thread([this] { controlledThread(); });
        markDirty();
        std::lock_guard<std::mutex> lk(mtx);
        sesStatus = "正被他人控制";
    }

    // 被控端：屏幕采集 -> 硬件编码 -> 发送
    void controlledThread() {
        ScreenCapture cap; VideoEncoder enc;
        if (!cap.init()) { printf("[client] capture init failed\n"); controlledActive=false; return; }
        int lastW=0, lastH=0; int64_t frameNo=0;
        std::vector<uint8_t> bgra; std::vector<std::vector<uint8_t>> pkts;
        auto lastSend = std::chrono::steady_clock::now();
        while (controlledActive && net.connected()) {
            int w=0,h=0;
            if (cap.captureBGRA(bgra,w,h)) {
                if (w!=lastW || h!=lastH) {
                    if (!enc.init(w,h,30,6000)) { controlledActive=false; return; }
                    lastW=w; lastH=h; printf("[client] screen %dx%d\n",w,h);
                }
                auto now=std::chrono::steady_clock::now();
                auto need=std::chrono::milliseconds(33);
                if (now-lastSend<need) std::this_thread::sleep_for(need-(now-lastSend));
                lastSend=std::chrono::steady_clock::now();
                pkts.clear();
                if (enc.encodeBGRA(bgra.data(),frameNo++,pkts)) {
                    for (auto& p:pkts) {
                        std::vector<uint8_t> payload(p.size()+8);
                        memcpy(payload.data(),&frameNo,8);
                        memcpy(payload.data()+8,p.data(),p.size());
                        if (!net.send(S2C_VIDEO,payload)) break;
                    }
                }
            } else std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        printf("[client] controlled thread exit\n");
    }

    // ============================ 网络回调（recv 线程） =======================
    void onNetMessage(uint8_t type, const uint8_t* payload, uint32_t len) {
        switch (type) {
        case 0:
            if (inSession() || pending) stopSession();
            { std::lock_guard<std::mutex> lk(mtx); srvStatus="服务器连接断开"; markDirty(); }
            break;
        case S2C_REGISTERED: {
            std::lock_guard<std::mutex> lk(mtx);
            myCode.assign((const char*)payload, strnlen((const char*)payload,len));
            srvStatus = "已注册，设备码 " + myCode; markDirty();
            printf("[client] registered code=%s\n", myCode.c_str());
            if (autoConnect) {
                pending = true;
                std::string p = targetCode; p.push_back(0);
                p += targetPass; p.push_back(0);
                net.send(C2S_CONNECT,p.data(),(uint32_t)p.size());
            }
            break;
        }
        case S2C_CONNECT_OK:
            if (pending) startControllerSide(); else startControlledSide();
            break;
        case S2C_CONNECT_FAIL: {
            std::string reason((const char*)payload, strnlen((const char*)payload,len));
            pending=false;
            std::lock_guard<std::mutex> lk(mtx);
            sesStatus="连接失败: "+reason; markDirty();
            printf("[client] connect fail: %s\n",reason.c_str());
            break;
        }
        case S2C_PEER_CLOSED:
            printf("[client] peer closed\n"); stopSession(); break;
        case S2C_VIDEO:
            if (len>8 && video) video->feedPacket(payload+8,len-8);
            break;
        case C2S_INPUT: {
            size_t n = len/sizeof(InputEvent);
            int sw=GetSystemMetrics(SM_CXSCREEN), sh=GetSystemMetrics(SM_CYSCREEN);
            for (size_t i=0;i<n;i++) {
                InputEvent e; memcpy(&e,payload+i*sizeof(InputEvent),sizeof(e));
                inject.handle(e,sw,sh);
            }
            break;
        }
        default: break;
        }
    }

    // ============================ 声明式 UI ===================================
    void render() {
        // 取一份状态快照（避免在 RN 树里持锁）
        std::string srv, my, ses, pass;
        bool sess;
        { std::lock_guard<std::mutex> lk(mtx);
          srv=srvStatus; my=myCode; ses=sesStatus; pass=myPass; }
        sess = inSession();

        try {
        RINS(root.get()) {
            o.direction = "row";
            o.backgroundColor = COLOR_BG;
            o.width = WIN_W; o.height = WIN_H;

            // ---------------- 左侧导航 ----------------
            RN(LayoutLinear, "nav") {
                RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
                o.direction = "column";
                o.width = NAV_W; o.height = WIN_H;
                o.backgroundColor = COLOR_BG;

                // logo
                RN(LayoutLinear, "logo") {
                    RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
                    o.direction = "row"; o.height = 64; o.alignItems = "center";
                    RN(TextView, "t") { o.text="RemoteDesk"; o.fontSize=18; o.color=COLOR_MAIN;
                                        o.margin.left = 20; } REND;
                } REND;
                // 账号
                RN(LayoutLinear, "user") {
                    RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
                    o.direction = "row"; o.height = 52; o.alignItems = "center";
                    RN(TextView, "u") { o.text="136****1920"; o.fontSize=13; o.color=COLOR_TEXT;
                                        o.margin.left=20; } REND;
                    RN(TextView, "v") { o.text="  个人版 升级"; o.fontSize=12; o.color=COLOR_MAIN; } REND;
                } REND;
                // 菜单
                static const char* items[8] = {
                    "个人中心","远程控制","设备列表","文件中心",
                    "游戏与应用中心","镜像屏/扩展屏","屏幕墙","高级设置" };
                for (int i=0;i<8;i++) {
                    RN(Button, std::string("nav")+std::to_string(i)) {
                        o.label = items[i];
                        o.width = NAV_W-40; o.height = 40;
                        o.fontSize = 14;
                        o.margin.left = 20; o.margin.top = 2;
                        o.radius.setAll(6);
                        bool sel = (i == curNav);
                        // fui Button 标准三态：isActive(选中) > hover > normal
                        o.labelColor = sel ? COLOR_MAIN : COLOR_TEXT;
                        o.normalBg = COLOR_BG;        // 常规：导航灰
                        o.hoverBg  = 0xffeceef1;      // 悬停：浅灰
                        o.activeBg = 0xffe8f3ff;      // 选中：浅蓝
                        o.isActive = sel;
                        int idx = i;
                        o.onClick = CLOSURE([this,idx](MouseEvent*){ curNav=idx; render(); });
                    } REND;
                }
                // 弹性占位
                RN(LayoutLinear, "navSpacer") {
                    RN(LayoutLinearCell) { o.grow = 1.0f; o.alignSelf = "stretch"; } REND;
                    o.direction="column"; o.width = NAV_W;
                } REND;
                // 底部广告
                RN(LayoutLinear, "ad") {
                    RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
                    o.direction="column"; o.width=NAV_W-40;
                    o.backgroundColor=0xffffffff; o.radius.setAll(8);
                    o.padding=Inset(14,10,14,10); o.margin.left=20; o.margin.bottom=14;
                    RN(TextView,"a"){ o.text="VIP+多控一"; o.fontSize=13; o.color=COLOR_TEXT; }REND;
                    RN(TextView,"b"){ o.text="最高直降158"; o.fontSize=12; o.color=COLOR_SUB;
                                      o.margin.top=4; }REND;
                } REND;
            } REND;

            // ---------------- 右侧主区 ----------------
            RN(LayoutLinear, "main") {
                RN(LayoutLinearCell) { o.grow = 1.0f; o.alignSelf = "stretch"; } REND;
                o.direction = "column"; o.width = MAIN_W; o.height = WIN_H;
                o.backgroundColor = 0xffffffff;

                // ---- 顶栏 ----
                RN(LayoutLinear, "topbar") {
                    RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
                    o.direction="row"; o.height=TOPBAR_H; o.alignItems="center";
                    RN(TextView,"title"){ o.text="远程控制"; o.fontSize=17; o.color=COLOR_TEXT;
                                          o.margin.left=24; }REND;
                    RN(TextView,"sub"){ o.text="  ·  远程控制设备"; o.fontSize=13; o.color=COLOR_SUB; }REND;
                    RN(LayoutLinear,"tbSpring"){
                        RN(LayoutLinearCell){ o.grow=1.0f; o.alignSelf="stretch"; }REND;
                        o.direction="row"; o.height=TOPBAR_H;
                    }REND;
                    RN(TextView,"srv"){ o.setText(srv); o.fontSize=12; o.color=COLOR_SUB;
                                        o.width=240; }REND;
                    RN(Button,"min"){ o.label="—"; o.width=44; o.height=TOPBAR_H;
                        o.normalBg=0xffffffff; o.hoverBg=0xfff0f1f3; o.activeBg=0xfff0f1f3;
                        o.labelColor=COLOR_SUB; o.radius.setAll(0);
                        o.onClick=CLOSURE([this](MouseEvent*){ if(win) win->minimize(); }); }REND;
                    RN(Button,"max"){ o.label="□"; o.width=44; o.height=TOPBAR_H;
                        o.normalBg=0xffffffff; o.hoverBg=0xfff0f1f3; o.activeBg=0xfff0f1f3;
                        o.labelColor=COLOR_SUB; o.radius.setAll(0);
                        o.onClick=CLOSURE([this](MouseEvent*){ if(win) win->maximize(); }); }REND;
                    RN(Button,"close"){ o.label="×"; o.width=44; o.height=TOPBAR_H;
                        o.normalBg=0xffffffff; o.hoverBg=0xfff5222d; o.activeBg=0xffd93026;
                        o.labelColor=COLOR_SUB; o.radius.setAll(0);
                        o.onClick=CLOSURE([this](MouseEvent*){ if(win) win->close(); }); }REND;
                } REND;

                // ---- 内容区（连接前卡片 / 连接后视频，二选一） ----
                RN(LayoutLinear, "content") {
                    RN(LayoutLinearCell) { o.grow = 1.0f; o.alignSelf = "stretch"; } REND;
                    o.direction="row"; o.height=CONTENT_H;
                    o.padding=Inset(24,16,24,16);

                    // ============ 连接前：两张卡片（常驻，靠 visible 切换） ============
                    RN(LayoutLinear, "cards") {
                        RN(LayoutLinearCell){ o.grow=1.0f; o.alignSelf="stretch"; }REND;
                        o.direction="row"; o.visible = !sess;

                            // 左卡：允许控制本设备
                            RN(LayoutLinear, "cardMine") {
                                o.direction="column"; o.width=CARD_W; o.height=CONTENT_H-32;
                                o.backgroundColor=0xffffffff; o.radius.setAll(12);
                                o.border.setAll(1,COLOR_BORDER); o.padding=Inset(28,20,28,20);
                                RN(TextView,"t1"){ o.text="允许控制本设备"; o.fontSize=19; o.color=COLOR_TEXT; }REND;
                                RN(TextView,"t2"){ o.text="待开启二次验证保护"; o.fontSize=12; o.color=COLOR_SUB;
                                                   o.margin.top=4; }REND;
                                RN(LayoutLinear,"g1"){ o.direction="column"; o.height=30; }REND;
                                RN(TextView,"l1"){ o.text="设备代码"; o.fontSize=13; o.color=COLOR_SUB; }REND;
                                RN(TextView,"code"){ o.setText(my.empty()?"- - -":formatCode(my));
                                    o.fontSize=36; o.color=COLOR_TEXT; o.margin.top=6; }REND;
                                RN(LayoutLinear,"g2"){ o.direction="column"; o.height=26; }REND;
                                RN(TextView,"l2"){ o.text="连接模式-临时密码"; o.fontSize=13; o.color=COLOR_SUB; }REND;
                                RN(TextView,"pwd"){ o.setText(maskPass(pass)); o.fontSize=36; o.color=COLOR_TEXT;
                                                    o.margin.top=6; }REND;
                                RN(LayoutLinear,"g3"){ o.direction="column"; o.height=22; }REND;
                                RN(TextView,"tip"){ o.text="控制本设备需校验本机锁屏密码"; o.fontSize=12;
                                                     o.color=COLOR_SUB; }REND;
                            } REND;
                            // 卡间距
                            RN(LayoutLinear,"cardGap"){ o.direction="row"; o.width=20; }REND;
                            // 右卡：远程控制设备
                            RN(LayoutLinear, "cardPeer") {
                                o.direction="column"; o.width=CARD_W; o.height=CONTENT_H-32;
                                o.backgroundColor=0xffffffff; o.radius.setAll(12);
                                o.border.setAll(1,COLOR_BORDER); o.padding=Inset(28,20,28,20);
                                RN(TextView,"t1"){ o.text="远程控制设备"; o.fontSize=19; o.color=COLOR_TEXT; }REND;
                                RN(TextView,"t2"){ o.text="已准备好连接(端到端加密已启用)"; o.fontSize=12;
                                                    o.color=COLOR_SUB; o.margin.top=4; }REND;
                                RN(LayoutLinear,"g1"){ o.direction="column"; o.height=24; }REND;
                                RN(TextView,"l1"){ o.text="连接代码"; o.fontSize=13; o.color=COLOR_SUB; }REND;
                                RN(EditText,"codeInput"){
                                    if (o.created) o.value = autoTargetCode.empty()?"":formatCode(autoTargetCode);
                                    o.placeholder="000 000"; o.font_size=22; o.color=COLOR_TEXT;
                                    o.placeholder_color=COLOR_SUB;
                                    o.width=414; o.height=42; o.margin.top=6;
                                    o.backgroundColor=0xfff2f3f5; o.radius.setAll(8);
                                    etCode = &o;
                                    o.onchanged = CLOSURE([this](std::string v){
                                        std::string d = digitsOnly(v);
                                        if (d.size()>6) d=d.substr(0,6);
                                        std::string out = formatCode(d);
                                        if (out != v && etCode) etCode->setValue(out);
                                    });
                                } REND;
                                RN(LayoutLinear,"g2"){ o.direction="column"; o.height=14; }REND;
                                RN(TextView,"l2"){ o.text="临时密码"; o.fontSize=13; o.color=COLOR_SUB; }REND;
                                RN(EditText,"passInput"){
                                    if (o.created) o.value = autoTargetPass;
                                    o.placeholder="请输入对方临时密码"; o.font_size=15; o.color=COLOR_TEXT;
                                    o.placeholder_color=COLOR_SUB;
                                    o.width=414; o.height=38; o.margin.top=6;
                                    o.backgroundColor=0xfff2f3f5; o.radius.setAll(8);
                                    etPass = &o;
                                } REND;
                                RN(LayoutLinear,"g3"){ o.direction="column"; o.height=14; }REND;
                                // 模式行
                                RN(LayoutLinear,"modeRow"){
                                    o.direction="row"; o.height=34;
                                    RN(Button,"mCtrl"){
                                        o.label="远程控制"; o.width=110; o.height=34; o.radius.setAll(6);
                                        bool on=(mode==0);
                                        o.labelColor = on?COLOR_MAIN:COLOR_SUB;
                                        o.normalBg=0xffffffff; o.hoverBg=0xfff2f3f5; o.activeBg=0xffe8f3ff;
                                        o.isActive = on;
                                        o.onClick=CLOSURE([this](MouseEvent*){ mode=0; render(); });
                                    }REND;
                                    RN(LayoutLinear,"mg"){ o.direction="row"; o.width=10; }REND;
                                    RN(Button,"mFile"){
                                        o.label="文件传输"; o.width=110; o.height=34; o.radius.setAll(6);
                                        bool on=(mode==1);
                                        o.labelColor = on?COLOR_MAIN:COLOR_SUB;
                                        o.normalBg=0xffffffff; o.hoverBg=0xfff2f3f5; o.activeBg=0xffe8f3ff;
                                        o.isActive = on;
                                        o.onClick=CLOSURE([this](MouseEvent*){ mode=1; render(); });
                                    }REND;
                                }REND;
                                RN(LayoutLinear,"g4"){ o.direction="column"; o.height=18; }REND;
                                RN(Button,"connect"){
                                    o.label="连 接"; o.width=414; o.height=44; o.radius.setAll(8);
                                    o.labelColor=0xffffffff;
                                    o.normalBg=COLOR_MAIN; o.hoverBg=COLOR_MAIN_D; o.activeBg=COLOR_MAIN_D;
                                    o.onClick=CLOSURE([this](MouseEvent*){ requestConnect(); });
                                }REND;
                                RN(LayoutLinear,"g5"){ o.direction="column"; o.height=12; }REND;
                                RN(TextView,"status"){ o.setText(ses); o.fontSize=12; o.color=COLOR_SUB; }REND;
                            } REND;
                        } REND;
                        // ============ 连接后：远程视频（常驻，靠 visible 切换） ============
                        RN(LayoutLinear, "session") {
                            RN(LayoutLinearCell){ o.grow=1.0f; o.alignSelf="stretch"; }REND;
                            o.direction="column"; o.visible = sess;
                            RN(LayoutLinear,"vbar"){
                                o.direction="row"; o.height=44; o.alignItems="center";
                                o.padding=Inset(12,0,0,0);
                                RN(TextView,"vs"){ o.setText(ses); o.fontSize=13; o.color=COLOR_TEXT;
                                                    o.margin.left=4; }REND;
                                RN(LayoutLinear,"vsp"){
                                    RN(LayoutLinearCell){o.grow=1.0f;o.alignSelf="stretch";}REND;
                                    o.direction="row"; o.height=44;
                                }REND;
                                RN(Button,"disconnect"){
                                    o.label="断开连接"; o.width=96; o.height=32; o.radius.setAll(6);
                                    o.labelColor=0xffffffff;
                                    o.normalBg=0xfff5222d; o.hoverBg=0xffd93026; o.activeBg=0xffd93026;
                                    o.margin.right=8;
                                    o.onClick=CLOSURE([this](MouseEvent*){
                                        if(inSession()){ net.send(C2S_DISCONNECT,nullptr,0); stopSession(); }
                                    });
                                }REND;
                            }REND;
                            RN(RemoteVideoView,"remoteVideo"){
                                o.width = MAIN_W-32; o.height = CONTENT_H-44;
                                o.backgroundColor = 0xff000000;
                                video = &o;   // 节点常驻，指针稳定
                            }REND;
                        } REND;
                } REND;

                // ---- 底部功能模块 ----
                RN(LayoutLinear, "bottom") {
                    RN(LayoutLinearCell){ o.grow=-1.0f; o.alignSelf="stretch"; }REND;
                    o.direction="row"; o.height=BOTTOM_H; o.padding=Inset(24,10,24,14);
                    static const char* mods[4]={"文件中心","游戏与应用中心","观看模式","镜像屏/扩展屏"};
                    static const char* subs[4]={"设备与资料管理","云游戏与应用","仅观看被控端","多屏协同"};
                    for (int i=0;i<4;i++) {
                        if (i>0) { RN(LayoutLinear,std::string("mg")+std::to_string(i)){
                            o.direction="row"; o.width=14; }REND; }
                        RN(LayoutLinear,std::string("mod")+std::to_string(i)){
                            o.direction="column"; o.width=236; o.height=80;
                            o.backgroundColor=0xfff7f8fa; o.radius.setAll(10);
                            o.padding=Inset(16,12,16,12);
                            RN(TextView,"m"){ o.text=mods[i]; o.fontSize=14; o.color=COLOR_TEXT; }REND;
                            RN(TextView,"s"){ o.text=subs[i]; o.fontSize=12; o.color=COLOR_SUB;
                                               o.margin.top=6; }REND;
                        }REND;
                    }
                } REND;
            } REND;
        } REND;
        } catch (const std::exception& e) {
            printf("[render] exception: %s\n", e.what());
            return;
        } catch (...) {
            printf("[render] unknown exception\n");
            return;
        }

        App_use()->invalidDraw();
    }
};

// ============================ main ===========================================
int main(int argc, char* argv[]) {
    SetConsoleOutputCP(65001);
    setvbuf(stdout,nullptr,_IONBF,0);

    urgc.start_process_thread();
    App* app = App_use();

    // GPU 共享设备必须早于 Window 创建
    if (!RemoteVideoView::ensureSharedGpuDevice()) {
        printf("FATAL: ensureSharedGpuDevice failed\n"); return 1;
    }

    ClientApp* g = new ClientApp();

    if (argc>1) g->serverHost = argv[1];
    if (argc>2) g->serverPort = atoi(argv[2]);
    if (argc>3) {
        g->autoTargetCode = argv[3];
        g->autoTargetPass = argc>4 ? argv[4] : g->myPass;
        g->targetCode = g->autoTargetCode;
        g->targetPass = g->autoTargetPass;
        g->autoConnect = true;
    }

    g->win  = new Window();
    g->root = new LayoutLinear();
    g->render();
    g->win->setRootView(g->root);
    g->win->setTitle("RemoteDeskClient");
    g->win->setSize(WIN_W,WIN_H);
    g->win->moveToCenter();
    g->win->show();
    g->win->onClosed = CLOSURE([g](Window*){
        g->controlledActive=false;
        if (g->ctrlThread.joinable()) g->ctrlThread.join();
        g->net.disconnect();
    });

    // 1 秒后自动连服务器
    static Ref<Timer> bootTimer;
    static std::atomic<bool> booted{false};
    bootTimer = mkTimerInterval(CLOSURE([g]() {
        if (!booted) { booted=true; if(bootTimer){bootTimer->cancel();bootTimer=nullptr;} g->connectServer(); }
    }),1000);

    // UI 状态驱动重渲染（100ms）；视频帧不走 fui 树
    static Ref<Timer> uiTimer;
    static long long lastFs=0;
    uiTimer = mkTimerInterval(CLOSURE([g]() {
        if (g->uiDirty.exchange(false)) g->render();
        if (g->amController && g->video) {
            long long fs=g->video->framesShown();
            if (fs>0 && fs!=lastFs) { lastFs=fs; if(fs<=5||fs%300==0)
                printf("[client] remote frames shown: %lld\n",(long long)fs); }
        }
    }),100);

    // 输入转发（10ms）
    static Ref<Timer> inputTimer;
    inputTimer = mkTimerInterval(CLOSURE([g]() {
        if (!g->amController || !g->net.connected()) return;
        auto evs = g->hook.takeEvents();
        if (evs.empty()) return;
        std::vector<uint8_t> payload(evs.size()*sizeof(InputEvent));
        for (size_t i=0;i<evs.size();i++)
            memcpy(payload.data()+i*sizeof(InputEvent),&evs[i],sizeof(InputEvent));
        g->net.send(C2S_INPUT,payload);
    }),10);

    app->runEventLoop();
    return 0;
}
