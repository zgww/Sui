// ============================================================================
// InputHook.cpp — 控制端输入采集（WH_MOUSE_LL / WH_KEYBOARD_LL）
//                + 被控端输入注入（SetCursorPos / mouse_event / keybd_event）
// ============================================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <cstdio>

#include "InputHook.h"

using namespace rdproto;

static InputHook* g_hook = nullptr;

bool InputHook::start(HWND hwnd) {
    stop();
    if (!hwnd) return false;
    target = hwnd;
    g_hook = this;
    hMouse = SetWindowsHookExW(WH_MOUSE_LL, mouseProc, GetModuleHandleW(nullptr), 0);
    hKey = SetWindowsHookExW(WH_KEYBOARD_LL, keyProc, GetModuleHandleW(nullptr), 0);
    if (!hMouse && !hKey) return false;
    printf("[hook] started (mouse=%d key=%d)\n", hMouse != nullptr, hKey != nullptr);
    return true;
}

void InputHook::stop() {
    if (hMouse) { UnhookWindowsHookEx(hMouse); hMouse = nullptr; }
    if (hKey) { UnhookWindowsHookEx(hKey); hKey = nullptr; }
    if (g_hook == this) g_hook = nullptr;
}

void InputHook::push(const InputEvent& e) {
    std::lock_guard<std::mutex> lk(mtx);
    queue.push_back(e);
}

std::deque<InputEvent> InputHook::takeEvents() {
    std::lock_guard<std::mutex> lk(mtx);
    std::deque<InputEvent> out;
    out.swap(queue);
    return out;
}

// 屏幕坐标 -> 目标窗口客户区 -> 归一化 0-65535
static bool screenToNorm(HWND wnd, int sx, int sy, uint16_t& nx, uint16_t& ny) {
    RECT rc;
    if (!GetClientRect(wnd, &rc) || rc.right <= 0 || rc.bottom <= 0) return false;
    POINT p{ sx, sy };
    if (!ScreenToClient(wnd, &p)) return false;
    if (p.x < 0 || p.y < 0 || p.x >= rc.right || p.y >= rc.bottom) return false;
    nx = (uint16_t)((uint64_t)p.x * 65535 / rc.right);
    ny = (uint16_t)((uint64_t)p.y * 65535 / rc.bottom);
    return true;
}

LRESULT CALLBACK InputHook::mouseProc(int code, WPARAM wp, LPARAM lp) {
    if (code >= 0 && g_hook) {
        MSLLHOOKSTRUCT* ms = (MSLLHOOKSTRUCT*)lp;
        InputEvent e{};
        switch (wp) {
        case WM_MOUSEMOVE: e.type = IN_MOUSE_MOVE; break;
        case WM_LBUTTONDOWN: e.type = IN_MOUSE_DOWN; e.button = 0; break;
        case WM_LBUTTONUP:   e.type = IN_MOUSE_UP;   e.button = 0; break;
        case WM_RBUTTONDOWN: e.type = IN_MOUSE_DOWN; e.button = 1; break;
        case WM_RBUTTONUP:   e.type = IN_MOUSE_UP;   e.button = 1; break;
        case WM_MBUTTONDOWN: e.type = IN_MOUSE_DOWN; e.button = 2; break;
        case WM_MBUTTONUP:   e.type = IN_MOUSE_UP;   e.button = 2; break;
        case WM_MOUSEWHEEL:  e.type = IN_MOUSE_WHEEL; e.wheel = (int16_t)HIWORD(ms->mouseData); break;
        default: break;
        }
        if (e.type != 0) {
            uint16_t nx = 0, ny = 0;
            HWND hwnd = g_hook->target;
            if (e.type == IN_MOUSE_WHEEL || screenToNorm(hwnd, ms->pt.x, ms->pt.y, nx, ny)) {
                e.x = nx; e.y = ny;
                g_hook->push(e);
            }
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

LRESULT CALLBACK InputHook::keyProc(int code, WPARAM wp, LPARAM lp) {
    if (code >= 0 && g_hook) {
        // 仅当目标窗口在前台时转发键盘
        HWND fg = GetForegroundWindow();
        HWND target = g_hook->target;
        if (fg == target || (target && IsChild(target, fg))) {
            KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lp;
            if (wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN || wp == WM_KEYUP || wp == WM_SYSKEYUP) {
                InputEvent e{};
                e.type = (wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN) ? IN_KEY_DOWN : IN_KEY_UP;
                e.vk = (uint16_t)kb->vkCode;
                g_hook->push(e);
            }
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

// ============================ 输入注入 =======================================

void InputInject::handle(const InputEvent& e, int screenW, int screenH) {
    switch (e.type) {
    case IN_MOUSE_MOVE: {
        if (screenW <= 0 || screenH <= 0) return;
        int x = (int)((uint64_t)e.x * screenW / 65535);
        int y = (int)((uint64_t)e.y * screenH / 65535);
        SetCursorPos(x, y);
        break;
    }
    case IN_MOUSE_DOWN:
    case IN_MOUSE_UP: {
        DWORD flags = 0;
        if (e.button == 0) flags = e.type == IN_MOUSE_DOWN ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;
        else if (e.button == 1) flags = e.type == IN_MOUSE_DOWN ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP;
        else flags = e.type == IN_MOUSE_DOWN ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP;
        mouse_event(flags, 0, 0, 0, 0);
        break;
    }
    case IN_MOUSE_WHEEL: {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, (DWORD)e.wheel, 0);
        break;
    }
    case IN_KEY_DOWN:
    case IN_KEY_UP: {
        keybd_event((BYTE)e.vk, 0, e.type == IN_KEY_UP ? KEYEVENTF_KEYUP : 0, 0);
        break;
    }
    default:
        break;
    }
}
