// ============================================================================
// InputHook.h — 控制端输入采集（低级钩子）+ 被控端输入注入（SendInput）
// ============================================================================
#pragma once
#include <cstdint>
#include <deque>
#include <mutex>
#include <windows.h>

#include "../RemoteDeskProtocol.h"

// ---- 控制端：低级鼠标/键盘钩子采集 ----
class InputHook {
public:
    InputHook() = default;
    ~InputHook() { stop(); }

    // hwnd: 远程画面所在窗口（钩子只转发该窗口内的鼠标 / 该窗口前台时的键盘）
    bool start(HWND hwnd);
    void stop();
    bool running() const { return hMouse != nullptr || hKey != nullptr; }

    // 取出全部待发事件（由发送线程消费）
    std::deque<rdproto::InputEvent> takeEvents();

private:
    HHOOK hMouse = nullptr;
    HHOOK hKey = nullptr;
    HWND target = nullptr;
    std::mutex mtx;
    std::deque<rdproto::InputEvent> queue;

    void push(const rdproto::InputEvent& e);
    static LRESULT CALLBACK mouseProc(int code, WPARAM wp, LPARAM lp);
    static LRESULT CALLBACK keyProc(int code, WPARAM wp, LPARAM lp);
};

// ---- 被控端：把接收到的输入事件注入本机 ----
class InputInject {
public:
    // screenW/H: 被控端屏幕尺寸（归一化坐标换算）
    void handle(const rdproto::InputEvent& e, int screenW, int screenH);
};
