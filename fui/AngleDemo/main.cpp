// AngleDemo: Win32 window + ANGLE(EGL) + NanoVG GLES3
// 在窗口中间绘制一个 100x200 的长方形

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <d3d11.h>     // ID3D11Device 接口声明 (仅 QI 用，不链接 d3d11.lib)
#include <d3d11on12.h> // ID3D11On12Device 接口声明

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include "nanovg/nanovg.h"

// NanoVG GLES3 后端实现（编译进本翻译单元）
#define NANOVG_GLES3_IMPLEMENTATION
#include "nanovg/nanovg_gl.h"

// GLES2 后端实现编译在 nanovg_gles2_impl.cpp 中（nanovg_gl.h 有 include guard，
// 无法在同一文件里同时展开两套实现），此处仅声明接口
extern "C" NVGcontext* nvgCreateGLES2(int flags);
extern "C" void nvgDeleteGLES2(NVGcontext* ctx);

static NVGcontext* g_vg = nullptr;

static void FatalError(const char* title, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    printf("FATAL [%s]: %s\n", title, buf);
    fflush(stdout);
    MessageBoxA(nullptr, buf, title, MB_OK | MB_ICONERROR);
    ExitProcess(1);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            DestroyWindow(hwnd);
            return 0;
        }
        break;
    case WM_ERASEBKGND:
        return 1; // 背景由 EGL 交换链负责，避免闪烁
    case WM_SIZE:
        return 0;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static void DrawFrame(int winWidth, int winHeight, float pixelRatio) {
    glViewport(0, 0, winWidth, winHeight);
    glClearColor(0.10f, 0.12f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    nvgBeginFrame(g_vg, (float)winWidth, (float)winHeight, pixelRatio);

    // 100x200 长方形，居中
    float w = 100.0f;
    float h = 200.0f;
    float x = (winWidth - w) * 0.5f;
    float y = (winHeight - h) * 0.5f;

    nvgBeginPath(g_vg);
    nvgRect(g_vg, x, y, w, h);
    nvgFillColor(g_vg, nvgRGBAf(0.20f, 0.60f, 1.00f, 1.0f));
    nvgFill(g_vg);

    // 描边便于观察边缘
    nvgStrokeColor(g_vg, nvgRGBAf(1.0f, 1.0f, 1.0f, 0.8f));
    nvgStrokeWidth(g_vg, 2.0f);
    nvgStroke(g_vg);

    nvgEndFrame(g_vg);
}

int Run(HINSTANCE hInstance, int nCmdShow) {
    SetProcessDPIAware();

    // ---- 1. 创建 Win32 窗口 ----
    WNDCLASSEXW wc = { sizeof(WNDCLASSEXW) };
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = L"AngleDemoWnd";
    if (!RegisterClassExW(&wc)) {
        FatalError("Error", "RegisterClassExW failed (%u)", (unsigned)GetLastError());
    }

    const int winW = 800, winH = 600;
    RECT rc = { 0, 0, winW, winH };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindowExW(
        0, wc.lpszClassName, L"AngleDemo - NanoVG GLES3 via ANGLE",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) {
        FatalError("Error", "CreateWindowExW failed (%u)", (unsigned)GetLastError());
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // ---- 2. 初始化 EGL (ANGLE)，通过 eglGetPlatformDisplay 指定后端 ----
    // 渲染后端由环境变量 ANGLE_DEMO_BACKEND 选择: default | d3d11 | d3d11on12 | gl | gles | vulkan | null
    // 注: ANGLE 没有"原生 D3D12 后端"。"D3D12" 路径是 d3d11on12 ——
    //     在 D3D12 设备之上创建 D3D11 设备 (D3D11/D3D12 互操作层, D3D11On12CreateDevice)
    const char* backendEnv = getenv("ANGLE_DEMO_BACKEND");
    if (!backendEnv || !*backendEnv) backendEnv = "default";
    //backendEnv = "d3d11on12";
    //backendEnv = "gl";

    // GLES 上下文版本由环境变量 ANGLE_DEMO_ES 选择: 2 | 3 (默认 3)
    // 这是与后端独立的另一个维度: 后端决定"GLES 调用翻译成什么"，
    // ES 版本决定"应用程序面向哪个版本的 GLES API"
    const char* esEnv = getenv("ANGLE_DEMO_ES");
    int esVersion = (esEnv && strcmp(esEnv, "2") == 0) ? 2 : 3;
    printf("Requested backend: %s, requested ES version: %d\n", backendEnv, esVersion);

    // 标题栏实时显示当前请求的后端/ES 版本，便于确认生效组合
    {
        char title[128];
        snprintf(title, sizeof(title), "AngleDemo - %s / ES%d (NanoVG)", backendEnv, esVersion);
        SetWindowTextA(hwnd, title);
    }

    EGLAttrib platformAttribs[8];
    int attrCount = 0;
    if (strcmp(backendEnv, "d3d11") == 0) {
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_ANGLE;
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE;
    } else if (strcmp(backendEnv, "d3d11on12") == 0) {
        // D3D11On12 要求: platform type 必须为 D3D11，且必须显式指定
        // device type 为 HARDWARE 或 WARP，否则属性校验直接失败
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_ANGLE;
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE;
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_DEVICE_TYPE_ANGLE;
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_DEVICE_TYPE_HARDWARE_ANGLE;
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_D3D11ON12_ANGLE;
        platformAttribs[attrCount++] = EGL_TRUE;
    } else if (strcmp(backendEnv, "gl") == 0) {
        // 原生桌面 OpenGL 后端 (Windows 上走 WGL)
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_ANGLE;
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_OPENGL_ANGLE;
    } else if (strcmp(backendEnv, "gles") == 0) {
        // 原生 OpenGL ES 后端: 需要平台本身有原生 EGL 实现并传入
        // EGL_PLATFORM_ANGLE_EGL_HANDLE_ANGLE，Windows 上通常不可用
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_ANGLE;
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_OPENGLES_ANGLE;
    } else if (strcmp(backendEnv, "vulkan") == 0) {
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_ANGLE;
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_VULKAN_ANGLE;
    } else if (strcmp(backendEnv, "null") == 0) {
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_ANGLE;
        platformAttribs[attrCount++] = EGL_PLATFORM_ANGLE_TYPE_NULL_ANGLE;
    }
    platformAttribs[attrCount++] = EGL_NONE;

    EGLDisplay display;
    if (attrCount == 1) {
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY); // 不指定，让 ANGLE 自选默认后端
    } else {
        display = eglGetPlatformDisplay(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, platformAttribs);
    }
    if (display == EGL_NO_DISPLAY) {
        EGLint eglErr = eglGetError();
        if (strcmp(backendEnv, "d3d11on12") == 0) {
            // 常见原因: 当前 ANGLE 构建未启用 EGL_ANGLE_platform_angle_d3d11on12
            // (客户端扩展里查不到该扩展名时，该属性会被 EGL_BAD_ATTRIBUTE 拒绝)
            printf("d3d11on12 requested but failed (eglErr=0x%x).\n"
                   "Check EGL client extensions for 'EGL_ANGLE_platform_angle_d3d11on12':\n  %s\n",
                   (unsigned)eglErr, eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS));
        }
        FatalError("EGL", "eglGetPlatformDisplay failed (0x%x)", (unsigned)eglErr);
    }

    EGLint major = 0, minor = 0;
    if (!eglInitialize(display, &major, &minor)) {
        FatalError("EGL", "eglInitialize failed (0x%x)", (unsigned)eglGetError());
    }
    printf("EGL %d.%d, vendor: %s\n", major, minor, eglQueryString(display, EGL_VENDOR));

    // config 按目标 ES 版本选择 renderable 位 (ES3 位配置对 ES2 上下文也兼容)
    const EGLint configAttribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, (esVersion == 2) ? EGL_OPENGL_ES2_BIT : EGL_OPENGL_ES3_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_STENCIL_SIZE, 8,   // nanovg 需要 stencil
        EGL_NONE
    };
    EGLConfig config = nullptr;
    EGLint numConfigs = 0;
    if (!eglChooseConfig(display, configAttribs, &config, 1, &numConfigs) || numConfigs < 1) {
        FatalError("EGL", "eglChooseConfig failed (0x%x)", (unsigned)eglGetError());
    }

    EGLSurface surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hwnd, nullptr);
    if (surface == EGL_NO_SURFACE) {
        FatalError("EGL", "eglCreateWindowSurface failed (0x%x)", (unsigned)eglGetError());
    }

    // ES 上下文版本在这里指定: EGL_CONTEXT_CLIENT_VERSION = 2 或 3
    // 注意: ANGLE 默认开启"向后兼容"(EGL_ANGLE_create_context_backwards_compatible)，
    // 会把 ES2 请求静默提升到显示支持的最高一致版本(此处为 ES 3.0)。
    // 要拿到真正的 ES2 上下文，必须同时传 BACKWARDS_COMPATIBLE=EGL_FALSE
    const EGLint ctxAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, esVersion,
        (esVersion == 2) ? EGL_CONTEXT_OPENGL_BACKWARDS_COMPATIBLE_ANGLE : EGL_NONE,
        (esVersion == 2) ? EGL_FALSE : EGL_NONE,
        EGL_NONE
    };
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttribs);
    if (context == EGL_NO_CONTEXT) {
        FatalError("EGL", "eglCreateContext failed (0x%x)", (unsigned)eglGetError());
    }

    if (!eglMakeCurrent(display, surface, surface, context)) {
        FatalError("EGL", "eglMakeCurrent failed (0x%x)", (unsigned)eglGetError());
    }
    eglSwapInterval(display, 1); // vsync
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION : %s\n", glGetString(GL_VERSION));
    printf("GLSL_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // ---- 查询 ANGLE 实际使用的后端 ----
    {
        printf("EGL client exts    : %s\n", eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS));
        printf("EGL_VENDOR (display) : %s\n", eglQueryString(display, EGL_VENDOR));
        printf("EGL display exts     : %s\n", eglQueryString(display, EGL_EXTENSIONS));

        typedef EGLBoolean (EGLAPIENTRYP PFN_QueryDisplayAttribEXT)(EGLDisplay, EGLint, EGLAttrib*);
        PFN_QueryDisplayAttribEXT queryDisplayAttrib =
            (PFN_QueryDisplayAttribEXT)eglGetProcAddress("eglQueryDisplayAttribEXT");

        // 方法A: EGL_ANGLE_platform_angle 标准查询接口（较新的 ANGLE 才支持）
        if (queryDisplayAttrib) {
            EGLAttrib backend = 0;
            if (queryDisplayAttrib(display, EGL_PLATFORM_ANGLE_TYPE_ANGLE, &backend)) {
                printf("ANGLE backend (EGL query) : 0x%x\n", (unsigned)backend);
            } else {
                printf("ANGLE backend (EGL query) : unsupported (eglErr=0x%x)\n", (unsigned)eglGetError());
            }

            // 方法B: EGL_ANGLE_device_query 查询设备扩展（能反映后端）
            EGLAttrib device = 0;
            if (queryDisplayAttrib(display, EGL_DEVICE_EXT, &device) && device != 0) {
                typedef const char* (EGLAPIENTRYP PFN_QueryDeviceStringEXT)(EGLDeviceEXT, EGLint);
                PFN_QueryDeviceStringEXT queryDeviceString =
                    (PFN_QueryDeviceStringEXT)eglGetProcAddress("eglQueryDeviceStringEXT");
                if (queryDeviceString) {
                    printf("EGL device exts     : %s\n", queryDeviceString((EGLDeviceEXT)device, EGL_EXTENSIONS));
                }
            }
        }

        // 方法C: 解析 GL_RENDERER 字符串（通用可靠，各版本 ANGLE 都可用）
        const char* renderer = (const char*)glGetString(GL_RENDERER);
        const char* backendName = "UNKNOWN";
        if (renderer) {
            if (strstr(renderer, "Direct3D11"))           backendName = "D3D11";
            else if (strstr(renderer, "Direct3D"))          backendName = "D3D9";
            else if (strstr(renderer, "Vulkan"))            backendName = "Vulkan";
            else if (strstr(renderer, "NULL"))              backendName = "NULL";
            else if (strstr(renderer, "OpenGL"))           backendName = "OpenGL";
            else if (strstr(renderer, "Metal"))            backendName = "Metal";
        }
        printf("ANGLE backend (renderer string) : %s\n", backendName);

        // 方法D: 取出 ID3D11Device，QueryInterface ID3D11On12Device 严格验证
        //       (只有通过 D3D11On12CreateDevice 创建的设备才实现该接口)
        if (queryDisplayAttrib) {
            EGLAttrib device = 0;
            if (queryDisplayAttrib(display, EGL_DEVICE_EXT, &device) && device != 0) {
                typedef EGLBoolean (EGLAPIENTRYP PFN_QueryDeviceAttribEXT)(EGLDeviceEXT, EGLint, EGLAttrib*);
                PFN_QueryDeviceAttribEXT queryDeviceAttrib =
                    (PFN_QueryDeviceAttribEXT)eglGetProcAddress("eglQueryDeviceAttribEXT");
                if (queryDeviceAttrib) {
                    EGLAttrib devPtr = 0;
                    if (queryDeviceAttrib((EGLDeviceEXT)device, EGL_D3D11_DEVICE_ANGLE, &devPtr) && devPtr != 0) {
                        ID3D11Device* d3d11 = (ID3D11Device*)(intptr_t)devPtr;
                        ID3D11On12Device* on12 = nullptr;
                        if (SUCCEEDED(d3d11->QueryInterface(__uuidof(ID3D11On12Device), (void**)&on12)) && on12) {
                            printf("D3D11On12 device    : YES —— D3D11 设备叠在 D3D12 之上\n");
                            on12->Release();
                        } else {
                            printf("D3D11On12 device    : no —— 普通 D3D11 设备\n");
                        }
                    } else {
                        printf("D3D11On12 device    : 无法获取 ID3D11Device 指针 (eglErr=0x%x)\n", (unsigned)eglGetError());
                    }
                }
            }
        }
    }
    fflush(stdout);

    // ---- 3. 创建 NanoVG 上下文（按 ES 版本选对应后端实现）----
    if (esVersion == 2) {
        g_vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    } else {
        g_vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    }
    if (g_vg == nullptr) {
        FatalError("NanoVG", "nvgCreateGLES%d failed", esVersion);
    }

    // ---- 4. 渲染循环 ----
    {
        HDC hdc = GetDC(hwnd);
        float pixelRatio = GetDeviceCaps(hdc, LOGPIXELSX) / 96.0f;
        ReleaseDC(hwnd, hdc);

        bool running = true;
        while (running) {
            MSG msg;
            while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    running = false;
                    break;
                }
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
            if (!running) break;

            EGLint winWidth = 0, winHeight = 0;
            eglQuerySurface(display, surface, EGL_WIDTH, &winWidth);
            eglQuerySurface(display, surface, EGL_HEIGHT, &winHeight);
            if (winWidth > 0 && winHeight > 0) {
                DrawFrame(winWidth, winHeight, pixelRatio);
                eglSwapBuffers(display, surface);
            }
        }
    }

    // ---- 5. 清理 ----
    if (esVersion == 2) {
        nvgDeleteGLES2(g_vg);
    } else {
        nvgDeleteGLES3(g_vg);
    }
    g_vg = nullptr;
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    (void)hPrevInstance; (void)lpCmdLine;
    return Run(hInstance, nShowCmd);
}

int main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    return Run(GetModuleHandleW(nullptr), SW_SHOWDEFAULT);
}
