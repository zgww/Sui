// ============================================================================
// Network.h — 远程桌面客户端 TCP 网络（连接服务器、注册、收发消息）
// ============================================================================
#pragma once
#include <atomic>
#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "../RemoteDeskProtocol.h"

class NetClient {
public:
    using MsgHandler = std::function<void(uint8_t type, const uint8_t* payload, uint32_t len)>;

    NetClient() = default;
    ~NetClient() { disconnect(); }

    // 连接服务器并进入收包循环（内部启动 recv 线程）
    bool connectTo(const std::string& host, int port);
    void disconnect();

    bool send(uint8_t type, const void* payload, uint32_t len);
    bool send(uint8_t type, const std::vector<uint8_t>& payload) {
        return send(type, payload.empty() ? nullptr : payload.data(), (uint32_t)payload.size());
    }
    bool connected() const { return running.load(); }
    void setHandler(MsgHandler h) { handler = std::move(h); }

private:
    std::atomic<bool> running{false};
    SOCKET s = INVALID_SOCKET;
    std::thread recvTh;
    std::mutex sendMtx;
    MsgHandler handler;

    void recvLoop();
};
