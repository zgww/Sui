// ============================================================================
// Network.cpp
// ============================================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <cstdio>
#include <cstring>

#include "Network.h"

#pragma comment(lib, "ws2_32.lib")

using namespace rdproto;

namespace {
class WsaGuard {
public:
    WsaGuard() {
        WSADATA wsa;
        ok = (WSAStartup(MAKEWORD(2, 2), &wsa) == 0);
    }
    ~WsaGuard() { if (ok) WSACleanup(); }
    bool ok = false;
};
WsaGuard g_wsa;

bool sendAll(SOCKET s, const void* data, int len) {
    const char* p = (const char*)data;
    while (len > 0) {
        int n = send(s, p, len, 0);
        if (n <= 0) return false;
        p += n;
        len -= n;
    }
    return true;
}
bool recvAll(SOCKET s, void* data, int len) {
    char* p = (char*)data;
    while (len > 0) {
        int n = recv(s, p, len, 0);
        if (n <= 0) return false;
        p += n;
        len -= n;
    }
    return true;
}
} // namespace

bool NetClient::connectTo(const std::string& host, int port) {
    disconnect();
    if (!g_wsa.ok) return false;

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)port);
    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) != 1) {
        // 域名解析
        addrinfo hints{}, *res = nullptr;
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        if (getaddrinfo(host.c_str(), nullptr, &hints, &res) != 0 || !res) {
            closesocket(sock);
            return false;
        }
        addr.sin_addr = ((sockaddr_in*)res->ai_addr)->sin_addr;
        freeaddrinfo(res);
    }

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        closesocket(sock);
        return false;
    }

    // 启用 TCP_NODELAY（低延迟远程桌面）
    int nodelay = 1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&nodelay, sizeof(nodelay));

    s = sock;
    running = true;
    recvTh = std::thread([this] { recvLoop(); });
    return true;
}

void NetClient::disconnect() {
    running = false;
    if (s != INVALID_SOCKET) {
        shutdown(s, SD_BOTH);
        closesocket(s);
        s = INVALID_SOCKET;
    }
    if (recvTh.joinable()) recvTh.join();
}

bool NetClient::send(uint8_t type, const void* payload, uint32_t len) {
    if (!running.load() || s == INVALID_SOCKET) return false;
    std::lock_guard<std::mutex> lk(sendMtx);
    uint8_t hdr[sizeof(Header)];
    encodeHeader(hdr, type, len);
    if (!sendAll(s, hdr, sizeof(hdr))) return false;
    if (len && !sendAll(s, payload, (int)len)) return false;
    return true;
}

void NetClient::recvLoop() {
    while (running.load()) {
        uint8_t hdr[sizeof(Header)];
        if (!recvAll(s, hdr, sizeof(hdr))) break;
        uint8_t type;
        uint32_t len;
        if (!parseHeader(hdr, type, len)) break;
        std::vector<uint8_t> payload(len);
        if (len && !recvAll(s, payload.data(), (int)len)) break;
        if (handler) handler(type, payload.data(), len);
    }
    running = false;
    // 通知上层连接断开（通过 handler 传一个 0 类型）
    if (handler) handler(0, nullptr, 0);
}
