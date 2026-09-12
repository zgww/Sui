// ============================================================================
// HwVideoPlayerView.cpp
// ----------------------------------------------------------------------------
// fui + Skia 全 GPU 视频播放视图实现。
//
// 像素管线（全程 GPU，零 CPU 回读）：
//   FFmpeg D3D11VA 硬解码(NV12) -> ANGLE EGLImage(平面/数组切片) -> GL 纹理
//   -> Skia GrYUVABackendTextures -> SkImage -> fui 窗口 SkCanvas 绘制
//
// 线程模型：
//   - 解码线程：av_read_frame / avcodec_send_packet / receive_frame，
//     产出 AVFrame（持有 D3D11 纹理引用）放入有界队列（满则丢最旧帧追帧）。
//   - 主线程（fui Timer 回调）：取最新帧 -> EGLImage 导入 -> GL 绑定
//     -> TextureFromYUVATextures -> 保存为显示帧 -> invalidDraw。
//   - draw_self（主线程）：把显示帧 drawImageRect 到当前 SkCanvas。
//     双缓冲渲染槽：绘制前释放对侧槽（其 GL 绘制已在上一次 flushAndSubmit 完成）。
// ============================================================================

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

// Windows SDK 头必须先于 extern "C" 的 ffmpeg 头：
// libavutil/hwcontext_d3d11va.h 会在 extern "C" 内包含 <d3d11.h>，
// SDK 头含 C++ 代码，在 extern "C" 内解析会导致 C2733/C2678。
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
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
}

// EGL 扩展函数原型（eglCreateImageKHR 等）
#ifndef EGL_EGLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES 1
#endif
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
// GLES 扩展函数原型（glEGLImageTargetTexture2DOES 等）
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>

// Skia 头必须先于 fui 头（fui 的 Node.h 定义 R/STATIC/CLASS 宏会污染 Skia 模板）
#include <include/core/SkImage.h>
#include <include/core/SkYUVAInfo.h>
#include <include/gpu/GpuTypes.h>
#include <include/gpu/ganesh/GrBackendSurface.h>
#include <include/gpu/ganesh/GrDirectContext.h>
#include <include/gpu/ganesh/GrYUVABackendTextures.h>
#include <include/gpu/ganesh/SkImageGanesh.h>
#include <include/gpu/ganesh/gl/GrGLBackendSurface.h>
#include <include/gpu/ganesh/gl/GrGLTypes.h>

// fui 头（include 根目录为 ..\fui）
#include "Core/View.h"
#include "Core/App.h"
#include "Core/Timer.h"
#include "CanvasSkia/SkiaBridge.h"

#include "HwVideoPlayerView.h"

#include <rttr/registration>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstring>
#include <deque>
#include <mutex>
#include <thread>

// ============================ 常量与工具 =====================================

// 用户头文件缺失的 ANGLE 常量（数值来自 ANGLE 官方 eglext_angle.h）
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

// C++ 下 av_err2str 的替代（av_err2str 是 C99 复合字面量宏）
static const char* _errstr(int ret) {
    static char buf[AV_ERROR_MAX_STRING_SIZE];
    av_strerror(ret, buf, sizeof(buf));
    return buf;
}

static void _logGlError(const char* tag) {
    GLenum e = glGetError();
    if (e != GL_NO_ERROR) printf("[%s] GL error 0x%x\n", tag, (unsigned)e);
}

// get_format 回调（C 函数指针，无用户数据）：
// avcodec_open2 期间 FFmpeg 询问硬件像素格式，用静态记录当前目标格式。
static AVPixelFormat g_hwPixFmtAsk = AV_PIX_FMT_NONE;
static AVPixelFormat _getHwFormat(AVCodecContext*, const AVPixelFormat* fmts) {
    for (int i = 0; fmts[i] != AV_PIX_FMT_NONE; i++) {
        if (fmts[i] == g_hwPixFmtAsk) return fmts[i];
    }
    return fmts[0];
}

// ============================ Impl ==========================================

struct HwVideoPlayerView::Impl {
    // ---- 共享 GPU 设备（进程级，与 fui/ANGLE 共用）----
    static Microsoft::WRL::ComPtr<ID3D11Device>        s_dev;
    static Microsoft::WRL::ComPtr<ID3D11DeviceContext> s_ctx;

    // ---- 渲染槽（仅主线程访问）----
    // 三槽轮换：显示帧所在槽 = (slotCur+2)%3，释放槽 = (slotCur+1)%3。
    // 被释放的槽必定"已在上一次 endFrame flushAndSubmit 完成绘制"且
    // "curImage 已切走（无 SkImage 引用）"，避免提前删除 GPU 仍在使用的纹理
    // （NVIDIA 驱动 nvwgf2umx 对此类 use-after-delete 直接崩溃 0xC0000005）。
    struct Slot {
        AVFrame*     hwFrame = nullptr;      // 引用解码帧（保纹理缓冲不被复用）
        EGLImageKHR  yImg  = EGL_NO_IMAGE_KHR;
        EGLImageKHR  uvImg = EGL_NO_IMAGE_KHR;
        GLuint       yTex = 0;
        GLuint       uvTex = 0;
        sk_sp<SkImage> image;
    };
    Slot slots[3];
    int  slotCur = 0;
    sk_sp<SkImage> curImage;                 // 当前显示帧（引用 slots 中某一帧的图像）
    int64_t lastFrameUs = 0;

    // ---- FFmpeg（open 时在主线程创建，close 时主线程清理）----
    AVFormatContext* fmtCtx = nullptr;
    AVCodecContext*  decCtx = nullptr;
    AVBufferRef*     hwDevRef = nullptr;     // d3d11va hw device ctx（持有外部设备引用）
    int              videoStream = -1;
    AVPixelFormat    hwPixFmt = AV_PIX_FMT_NONE;
    std::atomic<int> videoW{0};
    std::atomic<int> videoH{0};
    std::atomic<double> fps{25.0};

    // ---- 主线程同步解码用帧（v1 单线程解码+渲染，与任务1同架构，规避
    //      D3D11 immediate context 跨线程并发导致的解码器崩溃）----
    AVFrame* renderFrame = nullptr;

    // ---- 解码线程与帧队列（保留用于后续网络流异步化扩展）----
    std::thread             decThread;
    std::mutex              qMutex;
    std::condition_variable qCv;
    std::deque<AVFrame*>    q;               // 已解码未渲染帧（持有纹理引用）
    bool                    eos = false;
    bool                    stopReq = false;
    bool                    paused = false;
    bool                    opened = false;
    std::atomic<long long>  framesDecoded{0};
    std::atomic<long long>  framesShown{0};
    std::string             url;
    std::string             status = "idle";

    // ---- 解码线程 ----
    void decodeLoop();
    bool initDecoder();
    int  decodeNext(AVFrame* out);

    // ---- 渲染（主线程）----
    bool makeImageFromHwFrame(AVFrame* hwFrame, Slot& slot);
    void releaseSlot(Slot& s);
};

Microsoft::WRL::ComPtr<ID3D11Device>        HwVideoPlayerView::Impl::s_dev;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> HwVideoPlayerView::Impl::s_ctx;

// ====================== FFmpeg 硬解（解码线程）===============================

bool HwVideoPlayerView::Impl::initDecoder() {
    int ret = avformat_open_input(&fmtCtx, url.c_str(), nullptr, nullptr);
    if (ret < 0) {
        printf("HwVideoPlayerView: avformat_open_input(%s) failed: %s\n", url.c_str(), _errstr(ret));
        return false;
    }
    ret = avformat_find_stream_info(fmtCtx, nullptr);
    if (ret < 0) {
        printf("HwVideoPlayerView: avformat_find_stream_info failed\n");
        return false;
    }

    videoStream = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (videoStream < 0) {
        printf("HwVideoPlayerView: no video stream in %s\n", url.c_str());
        return false;
    }
    AVStream* st = fmtCtx->streams[videoStream];
    printf("HwVideoPlayerView: container=%s | %dx%d | %s\n",
           fmtCtx->iformat->name, st->codecpar->width, st->codecpar->height,
           av_get_pix_fmt_name((AVPixelFormat)st->codecpar->format));

    const AVCodec* codec = avcodec_find_decoder(st->codecpar->codec_id);
    if (!codec) {
        printf("HwVideoPlayerView: decoder not found for codec_id %d\n", st->codecpar->codec_id);
        return false;
    }

    // 查找 D3D11VA 硬件配置
    const AVCodecHWConfig* hwcfg = nullptr;
    for (int i = 0; (hwcfg = avcodec_get_hw_config(codec, i)); i++) {
        if (hwcfg->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX &&
            hwcfg->device_type == AV_HWDEVICE_TYPE_D3D11VA) {
            hwPixFmt = hwcfg->pix_fmt;
            break;
        }
    }
    if (!hwcfg) {
        printf("HwVideoPlayerView: no D3D11VA hw config for %s\n", codec->name);
        return false;
    }
    printf("HwVideoPlayerView: hw decode %s via D3D11VA (pix_fmt=%s)\n",
           codec->name, av_get_pix_fmt_name(hwPixFmt));

    // 用共享 D3D11 设备创建 FFmpeg d3d11va 设备上下文 —— 与 ANGLE 同一设备（零拷贝前提）
    hwDevRef = av_hwdevice_ctx_alloc(AV_HWDEVICE_TYPE_D3D11VA);
    if (!hwDevRef) {
        printf("HwVideoPlayerView: av_hwdevice_ctx_alloc failed\n");
        return false;
    }
    AVHWDeviceContext* hwdev = (AVHWDeviceContext*)hwDevRef->data;
    AVD3D11VADeviceContext* d3d11va = (AVD3D11VADeviceContext*)hwdev->hwctx;

    // FFmpeg 释放时会对这两个接口 Release，此处先 AddRef
    s_dev.Get()->AddRef();
    s_ctx.Get()->AddRef();
    d3d11va->device         = s_dev.Get();
    d3d11va->device_context = s_ctx.Get();
    d3d11va->BindFlags = D3D11_BIND_DECODER | D3D11_BIND_SHADER_RESOURCE;
    d3d11va->MiscFlags = D3D11_RESOURCE_MISC_SHARED;

    ret = av_hwdevice_ctx_init(hwDevRef);
    if (ret < 0) {
        printf("HwVideoPlayerView: av_hwdevice_ctx_init failed: %s\n", _errstr(ret));
        return false;
    }

    decCtx = avcodec_alloc_context3(codec);
    if (!decCtx) {
        printf("HwVideoPlayerView: avcodec_alloc_context3 failed\n");
        return false;
    }
    avcodec_parameters_to_context(decCtx, st->codecpar);
    decCtx->hw_device_ctx = av_buffer_ref(hwDevRef);
    decCtx->get_format    = _getHwFormat;
    decCtx->thread_count  = 1;   // 单线程解码，帧纹理生命周期可控

    g_hwPixFmtAsk = hwPixFmt;
    ret = avcodec_open2(decCtx, codec, nullptr);
    if (ret < 0) {
        printf("HwVideoPlayerView: avcodec_open2 failed: %s\n", _errstr(ret));
        return false;
    }

    if (decCtx->hw_frames_ctx) {
        AVHWFramesContext* fctx = (AVHWFramesContext*)decCtx->hw_frames_ctx->data;
        printf("HwVideoPlayerView: hw frames format=%s sw_format=%s pool=%d texture=%dx%d\n",
               av_get_pix_fmt_name(fctx->format), av_get_pix_fmt_name(fctx->sw_format),
               fctx->initial_pool_size, fctx->width, fctx->height);
        if (fctx->sw_format != AV_PIX_FMT_NV12) {
            printf("HwVideoPlayerView: warning: sw_format %s, only NV12 is rendered correctly\n",
                   av_get_pix_fmt_name(fctx->sw_format));
        }
    }

    videoW = decCtx->width;
    videoH = decCtx->height;

    // 帧率
    double f = av_q2d(st->avg_frame_rate);
    if (!(f > 0.0)) f = av_q2d(st->r_frame_rate);
    if (!(f > 0.0)) f = 30.0;
    fps = f;
    printf("HwVideoPlayerView: video %dx%d, target %.2f fps\n", videoW.load(), videoH.load(), f);
    return true;
}

// 解码下一帧：1=有帧(out)  0=继续(内部已读包)  -1=EOF/错误
int HwVideoPlayerView::Impl::decodeNext(AVFrame* out) {
    for (;;) {
        int r = avcodec_receive_frame(decCtx, out);
        if (r == 0) return 1;
        if (r == AVERROR_EOF) return -1;
        if (r != AVERROR(EAGAIN)) {
            printf("HwVideoPlayerView: decode error: %s\n", _errstr(r));
            return -1;
        }
        AVPacket pkt{};
        if (av_read_frame(fmtCtx, &pkt) < 0) {
            avcodec_send_packet(decCtx, nullptr);   // 冲刷解码器尾帧
            continue;
        }
        if (pkt.stream_index == videoStream) {
            int s = avcodec_send_packet(decCtx, &pkt);
            if (s < 0 && s != AVERROR(EAGAIN)) {
                printf("HwVideoPlayerView: send_packet error: %s\n", _errstr(s));
            }
        }
        av_packet_unref(&pkt);
    }
}

void HwVideoPlayerView::Impl::decodeLoop() {
    // v1 已改为主线程同步解码（tickFrame 内 decodeNext）。
    // 曾验证：解码线程 + 渲染主线程共用 D3D11 immediate context 会随机崩溃
    // （avcodec-63.dll 0xC0000005），故本函数不再使用，保留仅为说明历史架构。
}

// ============ 解码帧 -> EGLImage -> GL 纹理 -> Skia 图像（全 GPU，零拷贝）====

static SkYUVColorSpace _pickYuvCs(const AVFrame* f) {
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

bool HwVideoPlayerView::Impl::makeImageFromHwFrame(AVFrame* hwFrame, Slot& slot) {
    EGLDisplay display = (EGLDisplay)skiaGetEGLDisplay();
    GrDirectContext* gr = (GrDirectContext*)skiaCanvasGetGrContext();
    if (display == EGL_NO_DISPLAY || !gr) {
        printf("HwVideoPlayerView: fui skia context not ready (display=%p gr=%p)\n", display, (void*)gr);
        return false;
    }

    // D3D11VA 帧布局：data[0]=ID3D11Texture2D*（数组纹理），data[1]=数组切片索引
    ID3D11Texture2D* tex = reinterpret_cast<ID3D11Texture2D*>(hwFrame->data[0]);
    int slice = static_cast<int>(reinterpret_cast<intptr_t>(hwFrame->data[1]));
    if (!tex) {
        printf("HwVideoPlayerView: hw frame has no D3D11 texture\n");
        return false;
    }

    // 持有解码帧引用：渲染完成前解码器不得复用该纹理缓冲
    slot.hwFrame = av_frame_alloc();
    if (!slot.hwFrame) return false;
    av_frame_ref(slot.hwFrame, hwFrame);

    // GPU 零拷贝：D3D11 纹理 -> ANGLE EGLImage（Y/UV 两个平面，数组切片）
    EGLint yAttrs[]  = { EGL_D3D11_TEXTURE_PLANE_ANGLE, 0,
                         EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE, slice, EGL_NONE };
    EGLint uvAttrs[] = { EGL_D3D11_TEXTURE_PLANE_ANGLE, 1,
                         EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE, slice, EGL_NONE };
    slot.yImg = eglCreateImageKHR(display, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE,
                                  reinterpret_cast<EGLClientBuffer>(tex), yAttrs);
    if (slot.yImg == EGL_NO_IMAGE_KHR) {
        printf("HwVideoPlayerView: eglCreateImageKHR(Y) failed 0x%x\n", eglGetError());
        releaseSlot(slot);
        return false;
    }
    slot.uvImg = eglCreateImageKHR(display, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE,
                                   reinterpret_cast<EGLClientBuffer>(tex), uvAttrs);
    if (slot.uvImg == EGL_NO_IMAGE_KHR) {
        printf("HwVideoPlayerView: eglCreateImageKHR(UV) failed 0x%x\n", eglGetError());
        releaseSlot(slot);
        return false;
    }

    // EGLImage -> GL 纹理（Y: R8，UV: RG8，NV12 平面 1 尺寸减半）
    glGenTextures(1, &slot.yTex);
    glBindTexture(GL_TEXTURE_2D, slot.yTex);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, slot.yImg);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenTextures(1, &slot.uvTex);
    glBindTexture(GL_TEXTURE_2D, slot.uvTex);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, slot.uvImg);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    _logGlError("texture setup");

    // GL 纹理 -> Skia GPU 图像（YUVA / NV12）
    // 注意：GrBackendTextures::MakeGL 的 fFormat 已带 GL_R8/GL_RG8，
    // 不要再给 GrBackendFormats::MakeGL 传 GL_RED/GL_RG 外部格式（会 abort）。
    int vw = videoW.load(), vh = videoH.load();
    if (vw <= 0 || vh <= 0) {
        releaseSlot(slot);
        return false;
    }
    GrGLTextureInfo yInfo{};
    yInfo.fTarget = GL_TEXTURE_2D; yInfo.fID = slot.yTex;  yInfo.fFormat = GL_R8;
    GrGLTextureInfo uvInfo{};
    uvInfo.fTarget = GL_TEXTURE_2D; uvInfo.fID = slot.uvTex; uvInfo.fFormat = GL_RG8;

    GrBackendTexture yBT  = GrBackendTextures::MakeGL(vw, vh, skgpu::Mipmapped::kNo, yInfo, "hwdec_y");
    GrBackendTexture uvBT = GrBackendTextures::MakeGL(vw / 2, vh / 2, skgpu::Mipmapped::kNo, uvInfo, "hwdec_uv");

    GrBackendTexture planes[SkYUVAInfo::kMaxPlanes] = { yBT, uvBT, GrBackendTexture(), GrBackendTexture() };
    SkYUVAInfo yuvaInfo(SkISize::Make(vw, vh),
                        SkYUVAInfo::PlaneConfig::kY_UV,
                        SkYUVAInfo::Subsampling::k420,
                        _pickYuvCs(hwFrame));
    GrYUVABackendTextures yuvaTextures(yuvaInfo, planes, kTopLeft_GrSurfaceOrigin);

    slot.image = SkImages::TextureFromYUVATextures(gr, yuvaTextures);
    if (!slot.image) {
        printf("HwVideoPlayerView: SkImages::TextureFromYUVATextures failed\n");
        releaseSlot(slot);
        return false;
    }
    return true;
}

bool HwVideoPlayerView::saveCurrentFrame(const char* bmpPath) {
    if (!d || !d->opened || !bmpPath) return false;
    EGLDisplay display = (EGLDisplay)skiaGetEGLDisplay();
    if (!display) return false;
    EGLSurface surf = eglGetCurrentSurface(EGL_DRAW);
    if (surf == EGL_NO_SURFACE) return false;

    EGLint w = 0, h = 0;
    eglQuerySurface(display, surf, EGL_WIDTH, &w);
    eglQuerySurface(display, surf, EGL_HEIGHT, &h);
    if (w <= 0 || h <= 0) return false;

    glFinish();
    std::vector<unsigned char> px((size_t)w * h * 4);
    glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, px.data());

    // 写 32bit BMP（GL 原点左下 → BMP 自下而上，像素行序可直接使用）
    const uint32_t dataSize = (uint32_t)px.size();
    const uint32_t fileSize = 54 + dataSize;
    std::vector<unsigned char> bmp(fileSize);
    bmp[0] = 'B'; bmp[1] = 'M';
    memcpy(&bmp[2], &fileSize, 4);
    bmp[10] = 54;
    bmp[14] = 40; bmp[26] = 1; bmp[28] = 32;
    memcpy(&bmp[18], &w, 4);
    memcpy(&bmp[22], &h, 4);
    memcpy(&bmp[34], &dataSize, 4);
    // BGRA 数据（GL_RGBA → BGRA 交换）
    const unsigned char* src = px.data();
    unsigned char* dst = bmp.data() + 54;
    for (size_t i = 0; i < (size_t)w * h; i++) {
        dst[i * 4 + 0] = src[i * 4 + 2];
        dst[i * 4 + 1] = src[i * 4 + 1];
        dst[i * 4 + 2] = src[i * 4 + 0];
        dst[i * 4 + 3] = 0xFF;
    }
    FILE* fp = nullptr;
    fopen_s(&fp, bmpPath, "wb");
    if (!fp) return false;
    fwrite(bmp.data(), 1, bmp.size(), fp);
    fclose(fp);
    printf("HwVideoPlayerView: saved frame capture to %s (%dx%d)\n", bmpPath, w, h);
    return true;
}

void HwVideoPlayerView::Impl::releaseSlot(Slot& s) {
    s.image.reset();
    if (s.yTex)  { glDeleteTextures(1, &s.yTex);  s.yTex = 0; }
    if (s.uvTex) { glDeleteTextures(1, &s.uvTex); s.uvTex = 0; }
    if (s.yImg != EGL_NO_IMAGE_KHR) {
        EGLDisplay display = (EGLDisplay)skiaGetEGLDisplay();
        if (display != EGL_NO_DISPLAY) eglDestroyImageKHR(display, s.yImg);
        s.yImg = EGL_NO_IMAGE_KHR;
    }
    if (s.uvImg != EGL_NO_IMAGE_KHR) {
        EGLDisplay display = (EGLDisplay)skiaGetEGLDisplay();
        if (display != EGL_NO_DISPLAY) eglDestroyImageKHR(display, s.uvImg);
        s.uvImg = EGL_NO_IMAGE_KHR;
    }
    if (s.hwFrame) { av_frame_unref(s.hwFrame); av_frame_free(&s.hwFrame); }
}

// ============================ 生命周期 =======================================

HwVideoPlayerView::HwVideoPlayerView() {
    d = new Impl();
    _fitMode = 0;
}

HwVideoPlayerView::~HwVideoPlayerView() {
    // 窗口关闭/进程退出路径：只做安全清理。
    // 注意 fui 窗口销毁时 ANGLE EGL display 可能已被终止，
    // 因此不在这里释放 GL/EGL/Skia 资源（GPU 资源随进程退出自动回收）。
    stopTickTimer();
    Impl* p = d;
    if (!p) return;
    {
        std::lock_guard<std::mutex> lk(p->qMutex);
        p->stopReq = true;
    }
    p->qCv.notify_all();
    if (p->decThread.joinable()) p->decThread.join();
    while (!p->q.empty()) {
        AVFrame* f = p->q.front();
        p->q.pop_front();
        av_frame_unref(f);
        av_frame_free(&f);
    }
    p->curImage.reset();
    p->slots[0].image.reset();
    p->slots[1].image.reset();
    p->slots[2].image.reset();
    if (p->renderFrame) { av_frame_free(&p->renderFrame); p->renderFrame = nullptr; }
    // ffmpeg 清理
    if (p->decCtx) { avcodec_free_context(&p->decCtx); p->decCtx = nullptr; }
    if (p->fmtCtx) { avformat_close_input(&p->fmtCtx); p->fmtCtx = nullptr; }
    if (p->hwDevRef) { av_buffer_unref(&p->hwDevRef); p->hwDevRef = nullptr; }
    delete d;
    d = nullptr;
}

bool HwVideoPlayerView::ensureSharedGpuDevice() {
    if (Impl::s_dev) return true;   // 幂等

    D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
    };
    UINT flags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT |   // 硬解必须
                 D3D11_CREATE_DEVICE_BGRA_SUPPORT;     // ANGLE 需要
    D3D_FEATURE_LEVEL got = D3D_FEATURE_LEVEL_11_0;
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
                                   levels, ARRAYSIZE(levels), D3D11_SDK_VERSION,
                                   Impl::s_dev.ReleaseAndGetAddressOf(), &got,
                                   Impl::s_ctx.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        printf("HwVideoPlayerView: D3D11CreateDevice failed 0x%08x\n", (unsigned)hr);
        return false;
    }
    skiaSetExternalD3D11Device((void*)Impl::s_dev.Get());
    printf("HwVideoPlayerView: shared D3D11 device created (0x%p, feature 0x%x) and injected into fui\n",
           (void*)Impl::s_dev.Get(), (unsigned)got);
    return true;
}

void* HwVideoPlayerView::sharedD3D11Device() {
    return Impl::s_dev ? (void*)Impl::s_dev.Get() : nullptr;
}

bool HwVideoPlayerView::open(const std::string& mediaUrl) {
    if (!d) return false;
    close();

    url = mediaUrl;
    d->url = mediaUrl;

    if (!Impl::s_dev) {
        if (!ensureSharedGpuDevice()) {
            d->status = "no gpu device";
            return false;
        }
    }
    // 校验：fui 的 ANGLE display 必须已基于注入设备（若窗口先于 ensureSharedGpuDevice 创建则失败）
    void* injected = skiaGetExternalD3D11Device();
    if (injected != (void*)Impl::s_dev.Get()) {
        printf("HwVideoPlayerView: ERROR shared device not injected into fui "
               "(call HwVideoPlayerView::ensureSharedGpuDevice() BEFORE creating the fui Window)\n");
        d->status = "device injection too late";
        return false;
    }

    d->status = "opening";
    d->eos = false;
    d->stopReq = false;
    d->paused = false;
    d->lastFrameUs = 0;

    // v1：主线程同步初始化解码器（与渲染同线程，D3D11 immediate context 无并发）
    Impl* p = d;
    if (!p->initDecoder()) {
        p->status = "open failed";
        return false;
    }
    p->renderFrame = av_frame_alloc();
    if (!p->renderFrame) {
        p->status = "open failed";
        return false;
    }
    p->opened = true;
    p->status = "playing";
    printf("HwVideoPlayerView: opened, video=%dx%d (decode+render on UI thread, zero-copy GPU)\n",
           p->videoW.load(), p->videoH.load());

    // 帧驱动定时器：主线程每 8ms 轮询一次，tickFrame 内按视频帧率节流
    auto self = Ref(this);
    _tickTimer = mkTimerInterval(CLOSURE([=]() {
        if (self.get()) self->tickFrame();
    }), 8);

    return true;
}

void HwVideoPlayerView::stopTickTimer() {
    if (_tickTimer) {
        _tickTimer->cancel();
        _tickTimer->runFunc = nullptr;   // 打破 timer -> closure -> this 循环引用
        _tickTimer = nullptr;
    }
}

void HwVideoPlayerView::play() {
    if (!d) return;
    d->paused = false;
    d->status = d->opened ? "playing" : d->status;
}

void HwVideoPlayerView::pause() {
    if (!d) return;
    d->paused = true;
    d->status = "paused";
}

void HwVideoPlayerView::close() {
    if (!d) return;
    Impl* p = d;

    stopTickTimer();

    // 停解码线程
    {
        std::lock_guard<std::mutex> lk(p->qMutex);
        p->stopReq = true;
    }
    p->qCv.notify_all();
    if (p->decThread.joinable()) p->decThread.join();

    // 清队列
    while (!p->q.empty()) {
        AVFrame* f = p->q.front();
        p->q.pop_front();
        av_frame_unref(f);
        av_frame_free(&f);
    }

    // 释放渲染槽（窗口存活时 EGL display 仍有效）
    p->releaseSlot(p->slots[0]);
    p->releaseSlot(p->slots[1]);
    p->releaseSlot(p->slots[2]);
    p->curImage.reset();
    p->slotCur = 0;
    p->lastFrameUs = 0;

    // 释放主线程同步解码帧
    if (p->renderFrame) { av_frame_free(&p->renderFrame); p->renderFrame = nullptr; }

    // ffmpeg 清理
    if (p->decCtx) { avcodec_free_context(&p->decCtx); p->decCtx = nullptr; }
    if (p->fmtCtx) { avformat_close_input(&p->fmtCtx); p->fmtCtx = nullptr; }
    if (p->hwDevRef) { av_buffer_unref(&p->hwDevRef); p->hwDevRef = nullptr; }

    p->videoStream = -1;
    p->hwPixFmt = AV_PIX_FMT_NONE;
    p->videoW = 0;
    p->videoH = 0;
    p->eos = false;
    p->opened = false;
    p->framesDecoded = 0;
    p->framesShown = 0;
    p->status = "closed";
}

bool HwVideoPlayerView::isPlaying() const {
    return d && d->opened && !d->paused && !d->eos;
}

bool HwVideoPlayerView::isEnded() const {
    return d && d->eos && d->q.empty();
}

int HwVideoPlayerView::getVideoWidth() const { return d ? d->videoW.load() : 0; }
int HwVideoPlayerView::getVideoHeight() const { return d ? d->videoH.load() : 0; }

std::string HwVideoPlayerView::getStatusText() const {
    if (!d) return "idle";
    char buf[160];
    snprintf(buf, sizeof(buf), "%s | %lld/%lld frames | %dx%d",
             d->status.c_str(), d->framesShown.load(), d->framesDecoded.load(),
             d->videoW.load(), d->videoH.load());
    return buf;
}

void HwVideoPlayerView::setFitMode(int mode) {
    if (_fitMode != mode) {
        _fitMode = mode;
        invalidDraw();
    }
}

// ============================ 绘制 ===========================================

void HwVideoPlayerView::draw_self(Canvas* canvas) {
    View::draw_self(canvas);
    if (!d || !d->curImage) return;

    Rect r = getViewRect();
    if (r.w <= 0.5f || r.h <= 0.5f) return;

    int vw = d->videoW.load(), vh = d->videoH.load();
    if (vw <= 0 || vh <= 0) return;

    float dx, dy, dw, dh;
    if (_fitMode == 1) {
        dx = r.x; dy = r.y; dw = r.w; dh = r.h;   // fill 拉伸铺满
    } else {
        float scale = std::min(r.w / (float)vw, r.h / (float)vh);
        dw = vw * scale;
        dh = vh * scale;
        dx = r.x + (r.w - dw) * 0.5f;
        dy = r.y + (r.h - dh) * 0.5f;
    }
    skiaCanvasDrawImageAtRect(d->curImage.get(), 0, 0, (float)vw, (float)vh,
                              dx, dy, dw, dh, 1.0f);
}

// ============================ 帧驱动 =========================================

// 由 HwVideoPlayerView 的内部 Timer（主线程）周期性调用：
// 按视频帧率节流 -> 取最新解码帧 -> 生成 GPU 显示帧 -> invalidDraw
void HwVideoPlayerView::tickFrame() {
    Impl* p = d;
    if (!p || !p->opened || p->paused) return;

    // 帧率节流（微秒精度，fui Timer 后台 tick 粒度 ~60ms）：
    // 单次 tick 内连续"解码+渲染"追帧，直到追平当前时间，实际速率贴近视频帧率。
    double f = p->fps.load();
    int64_t intervalUs = (f > 0.0) ? (int64_t)(1e6 / f) : 40000;
    int64_t nowUs = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
    if (p->lastFrameUs == 0) {
        p->lastFrameUs = nowUs - intervalUs;   // 首帧立即显示
    }

    bool needDraw = false;
    for (int burst = 0; burst < 6; burst++) {   // 单 tick 最多追 6 帧，避免长循环饿死消息
        nowUs = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        if (nowUs - p->lastFrameUs < intervalUs) break;   // 已追平当前时间
        p->lastFrameUs += intervalUs;

        // v1：主线程同步解码一帧（解码器与渲染共用同一线程，无 D3D11 并发）
        int r = p->decodeNext(p->renderFrame);
        if (r == 1) {
            // 三槽轮换：先释放最旧槽（已 flush 且 curImage 已切走，无引用），
            // 再渲染新帧到当前槽并更新显示帧。
            p->releaseSlot(p->slots[(p->slotCur + 1) % 3]);
            bool ok = p->makeImageFromHwFrame(p->renderFrame, p->slots[p->slotCur]);
            if (ok) {
                p->curImage = p->slots[p->slotCur].image;
                p->framesShown++;
            }
            p->slotCur = (p->slotCur + 1) % 3;
            av_frame_unref(p->renderFrame);
            p->framesDecoded++;
            needDraw = true;

            long long shown = p->framesShown.load();
            if (shown <= 5 || shown % 300 == 0) {
                printf("HwVideoPlayerView: rendered %lld frames on GPU (zero-copy) | decoded %lld | %s\n",
                       shown, p->framesDecoded.load(), p->status.c_str());
            }
        } else if (r == -1) {
            p->eos = true;
            if (p->status != "ended") {
                p->status = "ended";
                printf("HwVideoPlayerView: playback ended, total frames rendered: %lld\n", p->framesShown.load());
                stopTickTimer();
            }
            break;
        }
    }

    if (needDraw) {
        App* app = App_use();
        if (app) app->invalidDraw();
    }
}

// ============================ RTTR 注册 ======================================

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<HwVideoPlayerView>("HwVideoPlayerView")
        .constructor<>()(policy::ctor::as_raw_ptr)
        .property("url", &HwVideoPlayerView::url)
        .property("autoPlay", &HwVideoPlayerView::autoPlay)
        .property("fitMode", &HwVideoPlayerView::getFitMode, &HwVideoPlayerView::setFitMode)
        .method("open", &HwVideoPlayerView::open)
        .method("play", &HwVideoPlayerView::play)
        .method("pause", &HwVideoPlayerView::pause)
        .method("close", &HwVideoPlayerView::close)
        .method("isPlaying", &HwVideoPlayerView::isPlaying)
        .method("isEnded", &HwVideoPlayerView::isEnded)
        .method("getVideoWidth", &HwVideoPlayerView::getVideoWidth)
        .method("getVideoHeight", &HwVideoPlayerView::getVideoHeight)
        .method("getStatusText", &HwVideoPlayerView::getStatusText)
        .method("ensureSharedGpuDevice", &HwVideoPlayerView::ensureSharedGpuDevice)
        .method("sharedD3D11Device", &HwVideoPlayerView::sharedD3D11Device);
}
