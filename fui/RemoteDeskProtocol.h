// ============================================================================
// RemoteDeskProtocol.h — 远程桌面共享协议（Server / Client 共用）
// ----------------------------------------------------------------------------
// 通讯模型（TCP，全经服务器中转）：
//   客户端 -> 服务器 : REGISTER / CONNECT / INPUT / DISCONNECT
//   服务器 -> 客户端 : REGISTERED / CONNECT_OK / CONNECT_FAIL / PEER_CLOSED
//   被控端 -> 服务器 -> 控制端 : VIDEO（屏幕视频帧）
//   控制端 -> 服务器 -> 被控端 : INPUT（鼠标/键盘输入事件）
//
// 帧格式： [Header(9B)][payload]
//   Header: magic(4B) + type(1B) + payloadLen(4B, 小端)
//   每条消息以 2 字节 '\r\n' 结束对齐（纯网络流无需，保留以便调试转储）。
// ============================================================================
#pragma once
#include <cstdint>
#include <cstring>
#include <string>

namespace rdproto {

constexpr uint32_t kMagic = 0x52444B31;          // "RDK1" 小端

enum MsgType : uint8_t {
    C2S_REGISTER     = 1,   // payload: name\0password\0
    S2C_REGISTERED   = 2,   // payload: deviceCode\0
    C2S_CONNECT      = 3,   // payload: targetCode\0password\0
    S2C_CONNECT_OK   = 4,   // payload: (空)
    S2C_CONNECT_FAIL = 5,   // payload: reason\0
    S2C_PEER_CLOSED  = 6,   // payload: reason\0 （对端断开）
    C2S_INPUT        = 7,   // payload: InputEvent 数组
    S2C_VIDEO        = 8,   // payload: uint64 pts + 视频数据
    C2S_DISCONNECT   = 9,   // payload: (空)
};

#pragma pack(push, 1)
struct Header {
    uint32_t magic;
    uint8_t  type;
    uint32_t payloadLen;
};
#pragma pack(pop)
static_assert(sizeof(Header) == 9, "Header must be 9 bytes");

// ---- 输入事件（控制端 -> 被控端）----
enum InputType : uint8_t {
    IN_MOUSE_MOVE   = 1,   // x,y 为归一化坐标(0-65535)，dx/dy 为相对增量（备用）
    IN_MOUSE_DOWN   = 2,   // button: 0=左 1=右 2=中
    IN_MOUSE_UP     = 3,
    IN_MOUSE_WHEEL  = 4,   // wheel: 滚轮增量（120 的倍数）
    IN_KEY_DOWN     = 5,   // vk: Windows 虚拟键码
    IN_KEY_UP       = 6,
};

#pragma pack(push, 1)
struct InputEvent {
    uint8_t  type;
    uint8_t  button;       // 鼠标按键
    uint16_t x;            // 归一化 0-65535（相对屏幕宽高）
    uint16_t y;
    int16_t  dx;           // 相对位移增量（备用）
    int16_t  dy;
    int16_t  wheel;        // 滚轮
    uint16_t vk;           // 虚拟键码
    uint16_t padding;
};
#pragma pack(pop)
static_assert(sizeof(InputEvent) == 16, "InputEvent must be 16 bytes");

// ---- 工具 ----
inline size_t encodeHeader(uint8_t* buf, uint8_t type, uint32_t len) {
    Header h;
    h.magic = kMagic;
    h.type = type;
    h.payloadLen = len;
    memcpy(buf, &h, sizeof(h));
    return sizeof(h);
}

inline bool parseHeader(const uint8_t* buf, uint8_t& type, uint32_t& len) {
    Header h;
    memcpy(&h, buf, sizeof(h));
    if (h.magic != kMagic) return false;
    type = h.type;
    len = h.payloadLen;
    return true;
}

} // namespace rdproto
