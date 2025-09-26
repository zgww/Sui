// WglPixelFormat.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <GL/gl.h>
//#include "GL/wglext.h"
#include <dwmapi.h>

#pragma comment (lib, "dwmapi.lib")

#define WGL_NUMBER_PIXEL_FORMATS_ARB 0x2000
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_TYPE_RGBA_ARB 0x202b
#define WGL_ACCELERATION_ARB 0x2003
#define WGL_NO_ACCELERATION_ARB 0x2025
#define WGL_RED_BITS_ARB 0x2015
#define WGL_RED_SHIFT_ARB 0x2016
#define WGL_GREEN_BITS_ARB 0x2017
#define WGL_GREEN_SHIFT_ARB 0x2018
#define WGL_BLUE_BITS_ARB 0x2019
#define WGL_BLUE_SHIFT_ARB 0x201a
#define WGL_ALPHA_BITS_ARB 0x201b
#define WGL_ALPHA_SHIFT_ARB 0x201c
#define WGL_ACCUM_BITS_ARB 0x201d
#define WGL_ACCUM_RED_BITS_ARB 0x201e
#define WGL_ACCUM_GREEN_BITS_ARB 0x201f
#define WGL_ACCUM_BLUE_BITS_ARB 0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB 0x2021
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_AUX_BUFFERS_ARB 0x2024
#define WGL_STEREO_ARB 0x2012

#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_COLOR_BITS_ARB 0x2014

#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_SAMPLE_BUFFERS_ARB 0x2041
#define WGL_SAMPLES_ARB 0x2042


#define WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20a9
#define WGL_CONTEXT_DEBUG_BIT_ARB 0x00000001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000004
#define WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB 0x00000004
#define WGL_LOSE_CONTEXT_ON_RESET_ARB 0x8252
#define WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define WGL_NO_RESET_NOTIFICATION_ARB 0x8261
#define WGL_CONTEXT_RELEASE_BEHAVIOR_ARB 0x2097
#define WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB 0
#define WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
#define WGL_CONTEXT_OPENGL_NO_ERROR_ARB 0x31b3
#define WGL_COLORSPACE_EXT 0x309d
#define WGL_COLORSPACE_SRGB_EXT 0x3089

#define ERROR_INVALID_VERSION_ARB 0x2095
#define ERROR_INVALID_PROFILE_ARB 0x2096
#define ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB 0x2054


#define GL_MULTISAMPLE 0x809D


// 函数指针声明
typedef BOOL(WINAPI* PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int* attribList);


// 函数指针
typedef BOOL(WINAPI* PFNWGLGETPIXELFORMATATTRIBIVARBPROC)(
    HDC hDC,              // 设备上下文
    int iPixelFormat,     // 要查询的像素格式编号
    int iLayerPlane,      // 通常为 0（主平面）
    int nAttributes,      // 属性数量
    const int* piAttributes,  // 属性列表（如 WGL_SAMPLE_BUFFERS_ARB）
    int* piValues         // 输出：对应的属性值
    );
PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB = nullptr;

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;


LRESULT proc(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam) {

    switch (Msg){
        //case WM_NCHITTEST:
        //{
        //    return HTCLOSE;
        //    return HTTRANSPARENT;
        //    return HTCAPTION;
        //    return HTNOWHERE;
        //}
    }

    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
// 简化版窗口创建
HWND CreateOpenGLWindow(HINSTANCE hInstance) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = proc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"OpenGLMSAA";
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    RegisterClass(&wc);

    return CreateWindowEx(

        //0| WS_EX_TRANSPARENT, 
        0,
        L"OpenGLMSAA", L"OpenGL MSAA Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr
    );
}
int main()
{
    std::cout << "Hello World!\n";

    auto hInstance = GetModuleHandle(NULL);

    HWND hWnd = CreateOpenGLWindow(hInstance);
    // 设置窗口扩展样式，允许鼠标穿透
    //SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_TRANSPARENT);

    // 可选：设置可点击区域（通过 Region）
    HRGN region = CreateRectRgn(0, 0, 200, 200);
    //HRGN region = CreatePolygonRgn(points, num_points, WINDING);
    //SetWindowRgn(hWnd, region, TRUE);

    HDC hDC = GetDC(hWnd);

    // 1. 创建临时像素格式（不支持 MSAA）
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,                                // Version Number
        PFD_DRAW_TO_WINDOW |         // Format Must Support Window
        PFD_SUPPORT_OPENGL |         // Format Must Support OpenGL
        PFD_SUPPORT_COMPOSITION |         // Format Must Support Composition
        PFD_DOUBLEBUFFER,                 // Must Support Double Buffering
        PFD_TYPE_RGBA,                    // Request An RGBA Format
        32,                               // Select Our Color Depth
        0, 0, 0, 0, 0, 0,                 // Color Bits Ignored
        8,                                // An Alpha Buffer  重要。  如果要开启透明，则必须 要有alpha buffer
        0,                                // Shift Bit Ignored
        0,                                // No Accumulation Buffer
        0, 0, 0, 0,                       // Accumulation Bits Ignored
        24,                               // 16Bit Z-Buffer (Depth Buffer)
        8,                                // Some Stencil Buffer
        0,                                // No Auxiliary Buffer
        PFD_MAIN_PLANE,                   // Main Drawing Layer
        0,                                // Reserved
        0, 0, 0                           // Layer Masks Ignored
    };

    int pixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, 12, &pfd);

    ReleaseDC(hWnd, hDC);
    hDC = GetDC(hWnd);
    //auto fmt = ChoosePixelFormat(hDC, &pfd);
    if (!SetPixelFormat(hDC, 12, &pfd))
    {
        printf("SetPixelFormat fail\n");
    }

    // 获取支持的像素格式总数
    int maxFormats;
    maxFormats = DescribePixelFormat(hDC, 1, sizeof(PIXELFORMATDESCRIPTOR), nullptr);

        PIXELFORMATDESCRIPTOR pfd11;
        maxFormats = DescribePixelFormat(hDC, 111, sizeof(PIXELFORMATDESCRIPTOR), &pfd11);

        PIXELFORMATDESCRIPTOR pfd12;
        maxFormats = DescribePixelFormat(hDC, 12, sizeof(PIXELFORMATDESCRIPTOR), &pfd12);

        PIXELFORMATDESCRIPTOR pfd43;
        maxFormats = DescribePixelFormat(hDC, 43, sizeof(PIXELFORMATDESCRIPTOR), &pfd43);

        PIXELFORMATDESCRIPTOR pfd44;
        maxFormats = DescribePixelFormat(hDC, 44, sizeof(PIXELFORMATDESCRIPTOR), &pfd44);


    HGLRC tempContext = wglCreateContext(hDC);
    wglMakeCurrent(hDC, tempContext);



    if (1) {


        // 2. 加载 WGL 扩展函数
        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

        // 加载扩展函数
        wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)
            wglGetProcAddress("wglGetPixelFormatAttribivARB");

        if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB) {
            MessageBox(hWnd, L"WGL ARB extensions not supported", L"Error", MB_OK);
            return -1;
        }
        // 3. 使用 wglChoosePixelFormatARB 选择支持 MSAA 的格式
        int attribList[] = {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB, 32,
            WGL_DEPTH_BITS_ARB, 24,
            //WGL_ALPHA_BITS_ARB, 8,
            WGL_STENCIL_BITS_ARB, 8,
            WGL_SAMPLE_BUFFERS_ARB, 1,           // 启用多重采样
            WGL_SAMPLES_ARB, 4,                  // 4x MSAA（可改为 2, 8 等）
            0, 0
        };
        int pixelFormatBest;
        UINT numFormats;
        BOOL result = wglChoosePixelFormatARB(hDC, attribList, nullptr, 1, &pixelFormatBest, &numFormats);


            int attrib = WGL_SAMPLES_ARB;
            int vals = 0;
            wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &vals);

            attrib = WGL_SAMPLE_BUFFERS_ARB;
            int valsSampleBuffers = 0;
            wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &valsSampleBuffers);

            attrib = WGL_STENCIL_BITS_ARB;
            int valsWGL_STENCIL_BITS_ARB = 0;
            wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &valsWGL_STENCIL_BITS_ARB);

            attrib = WGL_DEPTH_BITS_ARB;
            int valsWGL_DEPTH_BITS_ARB = 0;
            wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &valsWGL_DEPTH_BITS_ARB);

            attrib = WGL_COLOR_BITS_ARB;
            int valsWGL_COLOR_BITS_ARB = 0;
            wglGetPixelFormatAttribivARB(hDC, 44, 0, 1, &attrib, &valsWGL_COLOR_BITS_ARB);

        if (!result || numFormats == 0) {
            MessageBox(hWnd, L"Failed to choose MSAA pixel format", L"Error", MB_OK);
            return -1;
        }

        // 4. 清除并设置新的像素格式
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(tempContext);
        ReleaseDC(hWnd, hDC);
        hDC = GetDC(hWnd);
        SetPixelFormat(hDC, pixelFormatBest, &pfd);  // 注意：这里 pfd 不重要，但 API 要求

        // 5. 创建真正的 OpenGL 上下文（可选：使用现代 OpenGL）
        HGLRC hGLRC = wglCreateContextAttribsARB(hDC, nullptr, nullptr); // nullptr 表示兼容或核心上下文（取决于系统默认）
        if (!hGLRC) {
            MessageBox(hWnd, L"Failed to create OpenGL context", L"Error", MB_OK);
            return -1;
        }

        wglMakeCurrent(hDC, hGLRC);

        // 6. 启用 MSAA（在 OpenGL 中）
        glEnable(GL_MULTISAMPLE);
    }

    if (1) {
        BOOL composition, opaque;

        DWORD color;
        DwmIsCompositionEnabled(&composition);;
        auto v = DwmGetColorizationColor(&color, &opaque);
        HRGN region = CreateRectRgn(0, 0, -1, -1);
        DWM_BLURBEHIND bb = { 0 };
        bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        bb.hRgnBlur = region;
        bb.fEnable = TRUE;

        DwmEnableBlurBehindWindow(hWnd, &bb);
        DeleteObject(region);
    }

    ShowWindow(hWnd, SW_SHOW);


    // 你的 OpenGL 渲染代码...
    glClearColor(1.0f, 0.0f, 0.0f, 0.003f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SwapBuffers(hDC);


    // 消息循环...
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);


        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SwapBuffers(hDC);
    }

    return 0;
}
