// ============================================================================
// ffmpeg_hw_skia_gpu_render.cpp
// ----------------------------------------------------------------------------
// FFmpeg D3D11VA 硬解码 + ANGLE EGLImage 零拷贝导入 + Skia GPU 渲染
//
// 整条像素管线全程在 GPU 上完成，解码帧像素数据从不回传 CPU：
//
//   FFmpeg D3D11VA 硬解码（NV12，解码帧直接落在 GPU 的 D3D11 纹理）
//     |  帧数据留在显存，无 av_hwframe_transfer_data / sws_scale
//     v
//   ANGLE EGLImage 导入（EGL_D3D11_TEXTURE_ANGLE + 平面/数组切片）
//     |  FFmpeg 解码器与 ANGLE 共用同一个 ID3D11Device，零拷贝
//     v
//   GL 纹理（Y 平面 GL_R8、UV 平面 GL_RG8，由 EGLImage 直接绑定）
//     v
//   Skia Ganesh GL 后端：GrYUVABackendTextures -> SkImage
//     |  Skia 在 GPU 上完成 YUV->RGB 转换与绘制
//     v
//   eglSwapBuffers 呈现到窗口
//
// 唯一经过 CPU 的是压缩码流（av_read_frame 读文件/网络），不属于
// "解码->渲染"的像素路径。
// ============================================================================

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

// Windows SDK 头必须先于 extern "C" 块包含：
// libavutil/hwcontext_d3d11va.h 会在 extern "C" 内包含 <d3d11.h>，
// 而 SDK 头含有 C++ 代码（如 operator==），若在 extern "C" 内解析会产生 C 链接冲突。
#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <dxgi.h>
#include <dxgi1_2.h>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/hwcontext.h>
#include <libavutil/hwcontext_d3d11va.h>
#include <libavutil/pixdesc.h>
#include <libavutil/error.h>
}

// 使 EGL 扩展函数原型（eglCreateImageKHR 等）可见
#ifndef EGL_EGLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES 1
#endif
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
// 使 GLES 扩展函数原型（glEGLImageTargetTexture2DOES 等）可见
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>

#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkImage.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPaint.h"
#include "include/core/SkSurface.h"
#include "include/core/SkYUVAInfo.h"
#include "include/gpu/GpuTypes.h"
#include "include/gpu/ganesh/GrBackendSurface.h"
#include "include/gpu/ganesh/GrDirectContext.h"
#include "include/gpu/ganesh/GrTypes.h"
#include "include/gpu/ganesh/GrYUVABackendTextures.h"
#include "include/gpu/ganesh/SkImageGanesh.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/ganesh/gl/GrGLAssembleInterface.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLInterface.h"
#include "include/gpu/ganesh/gl/GrGLTypes.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>

// ---- 用户头文件缺失的 ANGLE 常量（数值来自 ANGLE 官方 eglext_angle.h）----
#ifndef EGL_D3D11_DEVICE_ANGLE
#define EGL_D3D11_DEVICE_ANGLE 0x33A1
#endif
#ifndef EGL_D3D11_TEXTURE_ANGLE
#define EGL_D3D11_TEXTURE_ANGLE 0x3484
#endif
#ifndef EGL_D3D11_TEXTURE_PLANE_ANGLE
#define EGL_D3D11_TEXTURE_PLANE_ANGLE 0x3492
#endif
#ifndef EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE
#define EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE 0x3493
#endif
#ifndef EGL_PLATFORM_DEVICE_EXT
#define EGL_PLATFORM_DEVICE_EXT 0x313F
#endif

// ============================ 全局状态 =====================================

static HWND            g_hwnd = nullptr;
static int             g_winW = 1280;
static int             g_winH = 720;

// D3D11 设备：FFmpeg 解码器与 ANGLE 共用（零拷贝的前提）
static Microsoft::WRL::ComPtr<ID3D11Device>         g_d3d11Device;
static Microsoft::WRL::ComPtr<ID3D11DeviceContext>  g_d3d11Ctx;

// EGL / ANGLE
static EGLDeviceEXT    g_eglDevice = EGL_NO_DEVICE_EXT;
static EGLDisplay      g_display   = EGL_NO_DISPLAY;
static EGLSurface      g_surface   = EGL_NO_SURFACE;
static EGLContext      g_context   = EGL_NO_CONTEXT;
static EGLConfig       g_config    = nullptr;
static EGLint          g_stencilBits = 0;
static EGLint          g_sampleCnt   = 0;

// Skia
static sk_sp<GrDirectContext> g_grContext;
static sk_sp<SkSurface>       g_skSurface;

// FFmpeg
static AVFormatContext* g_fmtCtx    = nullptr;
static AVCodecContext*  g_decCtx    = nullptr;
static AVBufferRef*     g_hwDevRef  = nullptr;   // d3d11va hw device ctx（持有外部设备引用）
static int              g_videoStream = -1;
static AVPixelFormat    g_hwPixFmt   = AV_PIX_FMT_NONE;
static int              g_videoW = 0, g_videoH = 0;
static bool             g_eof = false;

// 解码帧槽位（双缓冲）：持有解码帧引用，保证解码器纹理在渲染完成前不被复用
struct FrameSlot {
    AVFrame*      hwFrame = nullptr;   // 引用解码帧（保住 D3D11 纹理缓冲）
    EGLImageKHR   yImage  = EGL_NO_IMAGE_KHR;   // Y 平面 EGLImage
    EGLImageKHR   uvImage = EGL_NO_IMAGE_KHR;   // UV 平面 EGLImage
    GLuint        yTex = 0;             // 由 EGLImage 绑定的 GL 纹理
    GLuint        uvTex = 0;
    sk_sp<SkImage> image;               // Skia GPU 图像
};
static FrameSlot g_slots[2];
static int       g_slotCur = 0;

// ============================ 工具函数 =====================================

static void log_gl_error(const char* tag) {
    GLenum e = glGetError();
    if (e != GL_NO_ERROR) printf("[%s] GL error 0x%x\n", tag, (unsigned)e);
}

// C++ 下的 av_err2str 替代（av_err2str 是 C99 复合字面量宏）
static const char* errstr(int ret) {
    static char buf[AV_ERROR_MAX_STRING_SIZE];
    av_strerror(ret, buf, sizeof(buf));
    return buf;
}

static void release_slot(FrameSlot& s) {
    // SkImage 先释放（其 GPU 绘制在上一帧已 flush + swap 完成）
    s.image.reset();
    if (s.yTex)  { glDeleteTextures(1, &s.yTex);  s.yTex = 0; }
    if (s.uvTex) { glDeleteTextures(1, &s.uvTex); s.uvTex = 0; }
    if (s.yImage != EGL_NO_IMAGE_KHR)  { eglDestroyImageKHR(g_display, s.yImage);  s.yImage = EGL_NO_IMAGE_KHR; }
    if (s.uvImage != EGL_NO_IMAGE_KHR) { eglDestroyImageKHR(g_display, s.uvImage); s.uvImage = EGL_NO_IMAGE_KHR; }
    if (s.hwFrame) { av_frame_unref(s.hwFrame); av_frame_free(&s.hwFrame); }
}

// ============================ 窗口 =========================================

static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_SIZE: {
            RECT r; GetClientRect(hwnd, &r);
            g_winW = r.right - r.left; g_winH = r.bottom - r.top;
            if (g_grContext && g_winW > 0 && g_winH > 0) {
                g_skSurface.reset();  // 下一帧会按新尺寸重建
            }
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            if (wp == VK_ESCAPE) PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
}

static bool create_window() {
    WNDCLASS wc{};
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = wnd_proc;
    wc.hInstance     = GetModuleHandle(nullptr);
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"FfmpegHwSkiaGpuRenderWnd";
    RegisterClass(&wc);

    RECT rc{ 0, 0, g_winW, g_winH };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    g_hwnd = CreateWindow(wc.lpszClassName, L"FFmpeg D3D11VA HW-Decode -> Skia GPU Render (zero-copy)",
                          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          rc.right - rc.left, rc.bottom - rc.top,
                          nullptr, nullptr, wc.hInstance, nullptr);
    return g_hwnd != nullptr;
}

// ============================ D3D11 ========================================

static bool init_d3d11() {
    D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
    };
    UINT flags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT |  // 硬解必须
                 D3D11_CREATE_DEVICE_BGRA_SUPPORT;    // ANGLE 需要
    D3D_FEATURE_LEVEL got = D3D_FEATURE_LEVEL_11_0;
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
                                   levels, ARRAYSIZE(levels), D3D11_SDK_VERSION,
                                   g_d3d11Device.ReleaseAndGetAddressOf(), &got,
                                   g_d3d11Ctx.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        printf("error: D3D11CreateDevice failed 0x%08x\n", (unsigned)hr);
        return false;
    }
    printf("D3D11 device created, feature level 0x%x\n", (unsigned)got);
    return true;
}

// ============================ ANGLE ========================================

static GrGLFuncPtr egl_get_proc(void*, const char name[]) {
    return (GrGLFuncPtr)eglGetProcAddress(name);
}

static bool init_egl(HWND hwnd) {
    // 关键：把 FFmpeg 解码器用的同一个 D3D11 设备注入 ANGLE，
    // 之后 EGLImage 才能直接包装解码器的 D3D11 纹理（同设备零拷贝）。
    g_eglDevice = eglCreateDeviceANGLE(EGL_D3D11_DEVICE_ANGLE,
                                       reinterpret_cast<void*>(g_d3d11Device.Get()),
                                       nullptr);
    if (g_eglDevice == EGL_NO_DEVICE_EXT) {
        printf("error: eglCreateDeviceANGLE failed (0x%x)\n", eglGetError());
        return false;
    }

    g_display = eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, g_eglDevice, nullptr);
    if (g_display == EGL_NO_DISPLAY) {
        printf("error: eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT) failed (0x%x)\n", eglGetError());
        return false;
    }

    EGLint major = 0, minor = 0;
    if (!eglInitialize(g_display, &major, &minor)) {
        printf("error: eglInitialize failed (0x%x)\n", eglGetError());
        return false;
    }
    printf("EGL %d.%d | %s\n", major, minor, eglQueryString(g_display, EGL_VENDOR));

    // 校验 ANGLE 确实用的是我们注入的设备（同设备校验，失败即报错）
    EGLAttrib angleDev = 0;
    if (eglQueryDeviceAttribEXT(g_eglDevice, EGL_D3D11_DEVICE_ANGLE, &angleDev) == EGL_TRUE) {
        printf("ANGLE shares D3D11 device with FFmpeg decoder: %s\n",
               (void*)angleDev == (void*)g_d3d11Device.Get() ? "YES (zero-copy ok)" : "NO (mismatch!)");
    }

    if (!eglBindAPI(EGL_OPENGL_ES_API)) {
        printf("error: eglBindAPI failed (0x%x)\n", eglGetError());
        return false;
    }

    const EGLint configAttribs[] = {
        EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_RED_SIZE,        8,
        EGL_GREEN_SIZE,      8,
        EGL_BLUE_SIZE,       8,
        EGL_ALPHA_SIZE,      8,
        EGL_DEPTH_SIZE,      0,
        EGL_STENCIL_SIZE,    8,
        EGL_NONE
    };
    EGLint numConfigs = 0;
    if (!eglChooseConfig(g_display, configAttribs, &g_config, 1, &numConfigs) || numConfigs < 1) {
        printf("error: eglChooseConfig failed (0x%x)\n", eglGetError());
        return false;
    }

    g_surface = eglCreateWindowSurface(g_display, g_config, (EGLNativeWindowType)hwnd, nullptr);
    if (g_surface == EGL_NO_SURFACE) {
        printf("error: eglCreateWindowSurface failed (0x%x)\n", eglGetError());
        return false;
    }

    const EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 3,
        EGL_NONE
    };
    g_context = eglCreateContext(g_display, g_config, EGL_NO_CONTEXT, contextAttribs);
    if (g_context == EGL_NO_CONTEXT) {
        printf("error: eglCreateContext failed (0x%x)\n", eglGetError());
        return false;
    }

    if (!eglMakeCurrent(g_display, g_surface, g_surface, g_context)) {
        printf("error: eglMakeCurrent failed (0x%x)\n", eglGetError());
        return false;
    }
    eglSwapInterval(g_display, 1);

    eglGetConfigAttrib(g_display, g_config, EGL_STENCIL_SIZE, &g_stencilBits);
    eglGetConfigAttrib(g_display, g_config, EGL_SAMPLES, &g_sampleCnt);
    printf("GLES: %s | stencil=%d samples=%d\n",
           (const char*)glGetString(GL_VERSION), g_stencilBits, g_sampleCnt);

    const char* exts = (const char*)glGetString(GL_EXTENSIONS);
    printf("GL_OES_EGL_image: %s\n", exts && strstr(exts, "GL_OES_EGL_image") ? "supported" : "MISSING");
    return true;
}

// ============================ Skia =========================================

static bool init_skia() {
    sk_sp<const GrGLInterface> glInterface = GrGLMakeAssembledInterface(nullptr, egl_get_proc);
    if (!glInterface) {
        printf("error: GrGLMakeAssembledInterface failed\n");
        return false;
    }
    g_grContext = GrDirectContexts::MakeGL(glInterface);
    if (!g_grContext) {
        printf("error: GrDirectContexts::MakeGL failed\n");
        return false;
    }
    printf("Skia Ganesh GL context created\n");
    return true;
}

static bool rebuild_backbuffer() {
    if (!g_grContext || g_winW <= 0 || g_winH <= 0) return false;
    g_skSurface.reset();

    GrGLFramebufferInfo fbInfo{};
    fbInfo.fFBOID = 0;  // 默认帧缓冲（EGL 窗口表面）
    fbInfo.fFormat = GL_RGBA8;
    GrBackendRenderTarget rt = GrBackendRenderTargets::MakeGL(g_winW, g_winH,
                                                              g_sampleCnt, g_stencilBits, fbInfo);
    g_skSurface = SkSurfaces::WrapBackendRenderTarget(
        g_grContext.get(), rt, kBottomLeft_GrSurfaceOrigin,
        kRGBA_8888_SkColorType, SkColorSpace::MakeSRGB(), nullptr, nullptr);
    if (!g_skSurface) {
        printf("error: WrapBackendRenderTarget failed (%dx%d)\n", g_winW, g_winH);
        return false;
    }
    return true;
}

// ============================ FFmpeg 硬解 ==================================

static AVPixelFormat get_hw_format(AVCodecContext*, const AVPixelFormat* fmts) {
    for (int i = 0; fmts[i] != AV_PIX_FMT_NONE; i++) {
        if (fmts[i] == g_hwPixFmt) return fmts[i];
    }
    return fmts[0];
}

static bool init_hw_decoder(const char* path) {
    int ret = avformat_open_input(&g_fmtCtx, path, nullptr, nullptr);
    if (ret < 0) { printf("error: avformat_open_input(%s) failed: %s\n", path, errstr(ret)); return false; }
    ret = avformat_find_stream_info(g_fmtCtx, nullptr);
    if (ret < 0) { printf("error: avformat_find_stream_info failed\n"); return false; }

    g_videoStream = av_find_best_stream(g_fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (g_videoStream < 0) { printf("error: no video stream\n"); return false; }
    AVStream* st = g_fmtCtx->streams[g_videoStream];
    printf("container: %s | %dx%d | %s\n",
           g_fmtCtx->iformat->name, st->codecpar->width, st->codecpar->height,
           av_get_pix_fmt_name((AVPixelFormat)st->codecpar->format));

    const AVCodec* codec = avcodec_find_decoder(st->codecpar->codec_id);
    if (!codec) { printf("error: decoder not found\n"); return false; }

    // 查找 D3D11VA 硬件配置
    const AVCodecHWConfig* hwcfg = nullptr;
    for (int i = 0; (hwcfg = avcodec_get_hw_config(codec, i)); i++) {
        if (hwcfg->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX &&
            hwcfg->device_type == AV_HWDEVICE_TYPE_D3D11VA) {
            g_hwPixFmt = hwcfg->pix_fmt;
            break;
        }
    }
    if (!hwcfg) {
        printf("error: no D3D11VA hw config for %s\n", codec->name);
        return false;
    }
    printf("hw decode: %s via D3D11VA (pix_fmt=%s)\n",
           codec->name, av_get_pix_fmt_name(g_hwPixFmt));

    // 用外部 D3D11 设备创建 FFmpeg d3d11va 设备上下文 —— 与 ANGLE 同一设备
    g_hwDevRef = av_hwdevice_ctx_alloc(AV_HWDEVICE_TYPE_D3D11VA);
    if (!g_hwDevRef) { printf("error: av_hwdevice_ctx_alloc failed\n"); return false; }
    AVHWDeviceContext* hwdev = (AVHWDeviceContext*)g_hwDevRef->data;
    AVD3D11VADeviceContext* d3d11va = (AVD3D11VADeviceContext*)hwdev->hwctx;

    // FFmpeg 释放时会对这两个接口 Release，此处先 AddRef
    g_d3d11Device.Get()->AddRef();
    g_d3d11Ctx.Get()->AddRef();
    d3d11va->device         = g_d3d11Device.Get();
    d3d11va->device_context = g_d3d11Ctx.Get();
    d3d11va->BindFlags = D3D11_BIND_DECODER | D3D11_BIND_SHADER_RESOURCE;
    d3d11va->MiscFlags = D3D11_RESOURCE_MISC_SHARED;  // 纹理可跨 API 共享（同设备下兜底）

    ret = av_hwdevice_ctx_init(g_hwDevRef);
    if (ret < 0) { printf("error: av_hwdevice_ctx_init failed: %s\n", errstr(ret)); return false; }

    g_decCtx = avcodec_alloc_context3(codec);
    if (!g_decCtx) { printf("error: avcodec_alloc_context3 failed\n"); return false; }
    avcodec_parameters_to_context(g_decCtx, st->codecpar);
    g_decCtx->hw_device_ctx = av_buffer_ref(g_hwDevRef);
    g_decCtx->get_format    = get_hw_format;
    g_decCtx->thread_count  = 1;  // 单线程，解码帧与渲染同步，避免线程竞争

    ret = avcodec_open2(g_decCtx, codec, nullptr);
    if (ret < 0) { printf("error: avcodec_open2 failed: %s\n", errstr(ret)); return false; }

    if (g_decCtx->hw_frames_ctx) {
        AVHWFramesContext* fctx = (AVHWFramesContext*)g_decCtx->hw_frames_ctx->data;
        printf("hw frames: format=%s sw_format=%s pool=%d texture=%dx%d\n",
               av_get_pix_fmt_name(fctx->format), av_get_pix_fmt_name(fctx->sw_format),
               fctx->initial_pool_size, fctx->width, fctx->height);
        if (fctx->sw_format != AV_PIX_FMT_NV12) {
            printf("warning: sw_format %s, only NV12 is supported by this demo\n",
                   av_get_pix_fmt_name(fctx->sw_format));
        }
    }

    g_videoW = g_decCtx->width;
    g_videoH = g_decCtx->height;
    return true;
}

// 解码下一帧。返回 1=有新帧(写入 out)，-1=EOF/错误
static int decode_next_frame(AVFrame* out) {
    for (;;) {
        int r = avcodec_receive_frame(g_decCtx, out);
        if (r == 0) return 1;
        if (r == AVERROR_EOF) return -1;
        if (r != AVERROR(EAGAIN)) {
            printf("decode error: %s\n", errstr(r));
            return -1;
        }
        AVPacket pkt{};
        if (av_read_frame(g_fmtCtx, &pkt) < 0) {
            avcodec_send_packet(g_decCtx, nullptr);  // 冲刷解码器尾帧
            continue;
        }
        if (pkt.stream_index == g_videoStream) {
            int s = avcodec_send_packet(g_decCtx, &pkt);
            if (s < 0 && s != AVERROR(EAGAIN)) {
                printf("send_packet error: %s\n", errstr(s));
            }
        }
        av_packet_unref(&pkt);
    }
}

// ============ 解码帧 -> EGLImage -> GL 纹理 -> Skia 图像（全 GPU，零拷贝）====

static SkYUVColorSpace pick_yuv_cs(const AVFrame* f) {
    bool limited = f->color_range != AVCOL_RANGE_JPEG;
    switch (f->colorspace) {
        case AVCOL_SPC_BT709:
            return limited ? kRec709_Limited_SkYUVColorSpace : kRec709_Full_SkYUVColorSpace;
        case AVCOL_SPC_BT2020_NCL:
            return limited ? kBT2020_8bit_Limited_SkYUVColorSpace : kBT2020_8bit_Full_SkYUVColorSpace;
        default:
            return limited ? kRec601_Limited_SkYUVColorSpace : kJPEG_Full_SkYUVColorSpace;
    }
}

static bool make_image_from_hwframe(AVFrame* hwFrame, FrameSlot& slot) {
    // D3D11VA 帧布局：data[0]=ID3D11Texture2D*（数组纹理），data[1]=数组切片索引
    ID3D11Texture2D* tex = reinterpret_cast<ID3D11Texture2D*>(hwFrame->data[0]);
    int slice = static_cast<int>(reinterpret_cast<intptr_t>(hwFrame->data[1]));
    if (!tex) {
        printf("error: hw frame has no D3D11 texture\n");
        return false;
    }

    // 持有解码帧引用：渲染完成前解码器不得复用该纹理缓冲
    slot.hwFrame = av_frame_alloc();
    if (!slot.hwFrame) return false;
    av_frame_ref(slot.hwFrame, hwFrame);

    // ---- GPU 零拷贝：D3D11 纹理 -> ANGLE EGLImage（Y/UV 两个平面）----
    EGLint yAttrs[]  = { EGL_D3D11_TEXTURE_PLANE_ANGLE, 0,
                         EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE, slice, EGL_NONE };
    EGLint uvAttrs[] = { EGL_D3D11_TEXTURE_PLANE_ANGLE, 1,
                         EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE, slice, EGL_NONE };
    slot.yImage = eglCreateImageKHR(g_display, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE,
                                    reinterpret_cast<EGLClientBuffer>(tex), yAttrs);
    if (slot.yImage == EGL_NO_IMAGE_KHR) {
        printf("error: eglCreateImageKHR(Y plane) failed (0x%x)\n", eglGetError());
        release_slot(slot);
        return false;
    }
    slot.uvImage = eglCreateImageKHR(g_display, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE,
                                     reinterpret_cast<EGLClientBuffer>(tex), uvAttrs);
    if (slot.uvImage == EGL_NO_IMAGE_KHR) {
        printf("error: eglCreateImageKHR(UV plane) failed (0x%x)\n", eglGetError());
        release_slot(slot);
        return false;
    }

    // ---- EGLImage -> GL 纹理（Y: R8，UV: RG8，NV12 平面 1 尺寸减半）----
    glGenTextures(1, &slot.yTex);
    glBindTexture(GL_TEXTURE_2D, slot.yTex);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, slot.yImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenTextures(1, &slot.uvTex);
    glBindTexture(GL_TEXTURE_2D, slot.uvTex);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, slot.uvImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    log_gl_error("texture setup");

    // ---- GL 纹理 -> Skia GPU 图像（YUVA / NV12）----
    // 注意：GrBackendTextures::MakeGL 的 fFormat 已带 GL_R8/GL_RG8，
    // 不要再给 GrBackendFormats::MakeGL 传 GL_RED/GL_RG 作为外部格式，
    // 否则 Skia 会把纹理当作外部纹理走不支持路径并 abort（0xC0000409）。
    int vw = g_videoW, vh = g_videoH;
    GrGLTextureInfo yInfo{};
    yInfo.fTarget = GL_TEXTURE_2D; yInfo.fID = slot.yTex;  yInfo.fFormat = GL_R8;
    GrGLTextureInfo uvInfo{};
    uvInfo.fTarget = GL_TEXTURE_2D; uvInfo.fID = slot.uvTex; uvInfo.fFormat = GL_RG8;

    GrBackendTexture yBT  = GrBackendTextures::MakeGL(vw, vh, skgpu::Mipmapped::kNo, yInfo, "decoded_y");
    GrBackendTexture uvBT = GrBackendTextures::MakeGL(vw / 2, vh / 2, skgpu::Mipmapped::kNo, uvInfo, "decoded_uv");

    GrBackendTexture planes[SkYUVAInfo::kMaxPlanes] = { yBT, uvBT, GrBackendTexture(), GrBackendTexture() };
    SkYUVAInfo yuvaInfo(SkISize::Make(vw, vh),
                        SkYUVAInfo::PlaneConfig::kY_UV,
                        SkYUVAInfo::Subsampling::k420,
                        pick_yuv_cs(hwFrame));
    GrYUVABackendTextures yuvaTextures(yuvaInfo, planes, kTopLeft_GrSurfaceOrigin);

    slot.image = SkImages::TextureFromYUVATextures(g_grContext.get(), yuvaTextures);
    if (!slot.image) {
        printf("error: SkImages::TextureFromYUVATextures failed\n");
        release_slot(slot);
        return false;
    }
    return true;
}

// ============================ 渲染 =========================================

static void draw_frame(const sk_sp<SkImage>& img) {
    if (!g_skSurface || !img) return;
    SkCanvas* canvas = g_skSurface->getCanvas();
    canvas->clear(SK_ColorBLACK);

    float scale = std::min((float)g_winW / (float)g_videoW, (float)g_winH / (float)g_videoH);
    float dw = g_videoW * scale, dh = g_videoH * scale;
    SkRect dst = SkRect::MakeXYWH((g_winW - dw) * 0.5f, (g_winH - dh) * 0.5f, dw, dh);

    SkSamplingOptions sampling(SkFilterMode::kLinear, SkMipmapMode::kNone);
    canvas->drawImageRect(img.get(), dst, sampling, nullptr);

    canvas->save();
    for (int dx = 0; dx < 1000; dx += 10) {
        for (int dy = 0; dy < 1000; dy += 10) {
            canvas->translate(10, 1);
            canvas->drawImageRect(img.get(), dst, sampling, nullptr);
        }
        canvas->translate(-1000, 1);
    }
    canvas->restore();

    // 提交 GPU 绘制（flush + 等待 GPU 完成，确保解码器纹理安全回收）
    skgpu::ganesh::FlushAndSubmit(g_skSurface.get());
    eglSwapBuffers(g_display, g_surface);
}

// ============================ 主流程 =======================================

int main(int argc, char** argv) {
    // 崩溃/异常时也能看到已打印的日志
    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);

    const char* path = (argc > 1) ? argv[1]
                                  : "E:\\ws\\Sui\\fui\\SkiaDrawOpencvFrame\\oceans.mp4";
    printf("input: %s\n", path);
    printf("usage: %s [video_file]\n", argv[0]);

    if (!create_window())    { printf("error: create window failed\n"); return 1; }
    if (!init_d3d11())       return 1;
    if (!init_egl(g_hwnd))   return 1;
    if (!init_skia())        return 1;
    if (!rebuild_backbuffer()) return 1;
    if (!init_hw_decoder(path)) return 1;

    // 帧率节奏
    AVStream* st = g_fmtCtx->streams[g_videoStream];
    double fps = av_q2d(st->avg_frame_rate);
    if (!(fps > 0.0)) fps = av_q2d(st->r_frame_rate);
    if (!(fps > 0.0)) fps = 30.0;
    long long intervalUs = (long long)(1e6 / fps);
    printf("target fps: %.2f\n", fps);

    LARGE_INTEGER freq{}, tPrev{};
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&tPrev);

    AVFrame* hwFrame = av_frame_alloc();
    if (!hwFrame) return 1;

    long long frameCount = 0;
    LARGE_INTEGER statT0{};
    QueryPerformanceCounter(&statT0);
    bool running = true;

    printf("\n--- decoding & rendering on GPU (zero-copy, no CPU pixel path) ---\n");
    while (running) {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) { running = false; break; }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (!running) break;

        if (g_skSurface == nullptr && g_winW > 0 && g_winH > 0) {
            rebuild_backbuffer();  // 窗口尺寸变化后重建
            continue;
        }

        int r = decode_next_frame(hwFrame);
        if (r == 1) {
            // 上一槽的绘制已在上一帧 swap 时完成，可以安全回收
            release_slot(g_slots[g_slotCur]);

            FrameSlot& slot = g_slots[g_slotCur];
            if (make_image_from_hwframe(hwFrame, slot)) {
                draw_frame(slot.image);
                frameCount++;
            }
            g_slotCur ^= 1;
            av_frame_unref(hwFrame);

            // 节奏控制（解码/渲染慢于帧率时自然降速）
            LARGE_INTEGER now{};
            QueryPerformanceCounter(&now);
            long long elapsedUs = (now.QuadPart - tPrev.QuadPart) * 1000000LL / freq.QuadPart;
            long long sleepUs = intervalUs - elapsedUs;
            if (sleepUs > 0) Sleep((DWORD)(sleepUs / 1000));
            QueryPerformanceCounter(&tPrev);

            // 每 30 帧打印一次实际渲染帧率
            if (frameCount % 30 == 0) {
                LARGE_INTEGER tNow{};
                QueryPerformanceCounter(&tNow);
                double secs = (double)(tNow.QuadPart - statT0.QuadPart) / (double)freq.QuadPart;
                printf("rendered %lld frames | %.1f fps\n", frameCount, secs > 0 ? frameCount / secs : 0.0);
            }
        } else if (r == -1) {
            printf("\nend of stream. total frames rendered: %lld\n", frameCount);
            running = false;
        }
        // r == 0：内部已继续读包，不会发生
    }

    // ---- 清理 ----
    release_slot(g_slots[0]);
    release_slot(g_slots[1]);
    av_frame_free(&hwFrame);

    g_skSurface.reset();
    if (g_grContext) { g_grContext->flushAndSubmit(); g_grContext.reset(); }

    if (g_display != EGL_NO_DISPLAY) {
        eglMakeCurrent(g_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (g_surface != EGL_NO_SURFACE) { eglDestroySurface(g_display, g_surface); g_surface = EGL_NO_SURFACE; }
        if (g_context != EGL_NO_CONTEXT) { eglDestroyContext(g_display, g_context); g_context = EGL_NO_CONTEXT; }
        eglTerminate(g_display);
        g_display = EGL_NO_DISPLAY;
    }
    if (g_eglDevice != EGL_NO_DEVICE_EXT) {
        eglReleaseDeviceANGLE(g_eglDevice);
        g_eglDevice = EGL_NO_DEVICE_EXT;
    }

    avcodec_free_context(&g_decCtx);
    avformat_close_input(&g_fmtCtx);
    av_buffer_unref(&g_hwDevRef);   // 释放 FFmpeg 对 D3D11 设备的引用

    g_d3d11Ctx.Reset();
    g_d3d11Device.Reset();
    printf("cleanup done\n");
    return 0;
}
