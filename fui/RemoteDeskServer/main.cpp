// ============================================================================
// RemoteDeskServer — 远程桌面中转服务器（TCP，每连接一线程）
// ----------------------------------------------------------------------------
// 职责：
//   1. 客户端注册（生成设备码，保存密码）
//   2. 控制请求校验（目标代码 + 密码）
//   3. 会话桥接：被控端 VIDEO 帧 -> 控制端；控制端 INPUT 事件 -> 被控端
// 视频流与通讯全部经服务器中转（不 P2P）。
// 用法: RemoteDeskServer.exe [port]   （默认 20000）
// ============================================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "../RemoteDeskProtocol.h"

#pragma comment(lib, "ws2_32.lib")

using namespace rdproto;

// ============================ 全局 ===========================================
static std::recursive_mutex g_mtx;
static std::map<std::string, SOCKET> g_byCode;   // 设备码 -> socket
static std::map<SOCKET, std::string> g_codeOf;   // socket -> 设备码
static std::map<SOCKET, std::string> g_passOf;   // socket -> 密码
static std::map<SOCKET, std::string> g_nameOf;   // socket -> 名称
static std::map<SOCKET, SOCKET>      g_peerOf;   // socket -> 对端（控制会话）

static void logline(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    printf("[%u] ", (unsigned)GetTickCount64() % 1000000);
    vprintf(fmt, ap);
    printf("\n");
    va_end(ap);
}

// ============================ 网络工具 =======================================
static bool sendAll(SOCKET s, const void* data, int len) {
    const char* p = (const char*)data;
    while (len > 0) {
        int n = send(s, p, len, 0);
        if (n <= 0) return false;
        p += n;
        len -= n;
    }
    return true;
}

static bool sendMsg(SOCKET s, uint8_t type, const void* payload, uint32_t len) {
    uint8_t hdr[sizeof(Header)];
    encodeHeader(hdr, type, len);
    if (!sendAll(s, hdr, sizeof(hdr))) return false;
    if (len && !sendAll(s, payload, (int)len)) return false;
    return true;
}

// 读完整一条消息：返回 type（0=连接关闭/错误）
static bool recvAll(SOCKET s, void* data, int len) {
    char* p = (char*)data;
    while (len > 0) {
        int n = recv(s, p, len, 0);
        if (n <= 0) return false;
        p += n;
        len -= n;
    }
    return true;
}

// 读完整一条消息：返回 type（-1=连接关闭/错误）
static int recvMsg(SOCKET s, std::vector<uint8_t>& out) {
    uint8_t hdr[sizeof(Header)];
    if (!recvAll(s, hdr, sizeof(hdr))) return -1;
    uint8_t type;
    uint32_t len;
    if (!parseHeader(hdr, type, len)) return -1;
    out.resize(len);
    if (len && !recvAll(s, out.data(), (int)len)) return -1;
    return type;
}

static std::string makeCode() {
    // 6 位数字设备码，避免与在线冲突
    for (int tries = 0; tries < 100; tries++) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%06u", (unsigned)(rand() % 1000000));
        if (g_byCode.find(buf) == g_byCode.end()) return buf;
    }
    return "000001";   // 理论不可达
}

static void closePeerSession(SOCKET s, const char* reason) {
    // 调用者已持有 g_mtx
    SOCKET peer = 0;
    auto it = g_peerOf.find(s);
    if (it != g_peerOf.end()) {
        peer = it->second;
        g_peerOf.erase(it);
    }
    if (peer && peer != INVALID_SOCKET) {
        g_peerOf.erase(peer);
        sendMsg(peer, S2C_PEER_CLOSED, reason, (uint32_t)strlen(reason) + 1);
    }
}

static void dropClient(SOCKET s, const char* why) {
    {
        std::lock_guard<std::recursive_mutex> lk(g_mtx);
        std::string code = g_codeOf[s];
        std::string name = g_nameOf[s];
        closePeerSession(s, why);
        if (!code.empty()) g_byCode.erase(code);
        g_codeOf.erase(s);
        g_passOf.erase(s);
        g_nameOf.erase(s);
        if (!code.empty())
            logline("client [%s] %s left (%s), online=%zu", code.c_str(), name.c_str(), why,
                    g_byCode.size());
    }
    closesocket(s);
}

// ============================ 每连接处理 =====================================
static void handleClient(SOCKET s) {
    char ip[64] = { 0 };
    {   // 打印对端地址
        sockaddr_in addr{};
        int alen = sizeof(addr);
        getpeername(s, (sockaddr*)&addr, &alen);
        inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));
    }
    logline("connection from %s", ip);

    for (;;) {
        std::vector<uint8_t> payload;
        int type = recvMsg(s, payload);
        if (type < 0) {
            dropClient(s, "conn closed");
            return;
        }

        switch (type) {
        case C2S_REGISTER: {
            // payload: name\0password\0
            std::string name, pass;
            size_t p0 = 0, p1 = payload.size();
            for (size_t i = 0; i < payload.size(); i++) {
                if (payload[i] == 0) { p1 = i; break; }
            }
            name.assign((char*)payload.data(), p1);
            if (p1 + 1 < payload.size())
                pass.assign((char*)payload.data() + p1 + 1, payload.size() - p1 - 1);

            std::string code;
            {
                std::lock_guard<std::recursive_mutex> lk(g_mtx);
                code = makeCode();
                g_byCode[code] = s;
                g_codeOf[s] = code;
                g_passOf[s] = pass;
                g_nameOf[s] = name.empty() ? "unnamed" : name;
            }
            sendMsg(s, S2C_REGISTERED, code.data(), (uint32_t)code.size() + 1);
            logline("client registered: code=%s name=%s online=%zu",
                    code.c_str(), name.c_str(), g_byCode.size());
            break;
        }
        case C2S_CONNECT: {
            // payload: targetCode\0password\0
            std::string tcode, tpass;
            size_t p1 = 0;
            for (size_t i = 0; i < payload.size(); i++) {
                if (payload[i] == 0) { p1 = i; break; }
            }
            tcode.assign((char*)payload.data(), p1);
            if (p1 + 1 < payload.size())
                tpass.assign((char*)payload.data() + p1 + 1, payload.size() - p1 - 1);

            std::lock_guard<std::recursive_mutex> lk(g_mtx);
            auto it = g_byCode.find(tcode);
            bool self = (it != g_byCode.end() && it->second == s);
            if (it == g_byCode.end() || self) {
                const char* reason = self ? "cannot control self" : "target not found";
                sendMsg(s, S2C_CONNECT_FAIL, reason, (uint32_t)strlen(reason) + 1);
                break;
            }
            SOCKET target = it->second;
            if (g_peerOf.count(target) || g_peerOf.count(s)) {
                const char* reason = "target busy or already in session";
                sendMsg(s, S2C_CONNECT_FAIL, reason, (uint32_t)strlen(reason) + 1);
                break;
            }
            std::string& realPass = g_passOf[target];
            if (realPass != tpass) {
                const char* reason = "wrong password";
                sendMsg(s, S2C_CONNECT_FAIL, reason, (uint32_t)strlen(reason) + 1);
                break;
            }
            // 建立桥接会话
            g_peerOf[s] = target;
            g_peerOf[target] = s;
            sendMsg(s, S2C_CONNECT_OK, nullptr, 0);
            sendMsg(target, S2C_CONNECT_OK, nullptr, 0);
            logline("session bridged: %s <-> %s", g_codeOf[s].c_str(), tcode.c_str());
            break;
        }
        case C2S_INPUT:     // 控制端 -> 被控端
        case S2C_VIDEO: {   // 被控端 -> 控制端（转发语义一致：直接投递对端）
            std::lock_guard<std::recursive_mutex> lk(g_mtx);
            auto it = g_peerOf.find(s);
            if (it == g_peerOf.end()) break;          // 无会话，丢弃
            SOCKET peer = it->second;
            if (peer == INVALID_SOCKET) break;
            if (!sendMsg(peer, (uint8_t)type, payload.data(), (uint32_t)payload.size())) {
                // 转发失败视为对端断开
                closePeerSession(s, "forward failed");
            }
            break;
        }
        case C2S_DISCONNECT: {
            std::lock_guard<std::recursive_mutex> lk(g_mtx);
            closePeerSession(s, "peer disconnected");
            break;
        }
        default:
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    int port = argc > 1 ? atoi(argv[1]) : 20000;
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
    srand((unsigned)GetTickCount64());

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSock == INVALID_SOCKET) { printf("socket failed\n"); return 1; }
    BOOL reuse = TRUE;
    setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((u_short)port);
    if (bind(listenSock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        printf("bind :%d failed %d\n", port, WSAGetLastError());
        return 1;
    }
    if (listen(listenSock, SOMAXCONN) != 0) { printf("listen failed\n"); return 1; }
    logline("RemoteDeskServer listening on :%d", port);

    for (;;) {
        SOCKET s = accept(listenSock, nullptr, nullptr);
        if (s == INVALID_SOCKET) continue;
        std::thread(handleClient, s).detach();
    }
    return 0;
}
