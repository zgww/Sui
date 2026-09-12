// ============================================================================
// RemoteVideoView.cpp — 远程画面视图（网络 H.264 -> 硬解 -> EGLImage -> Skia）
// ============================================================================
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <dxgi.h>
#include <dxgi1_2.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/hwcontext.h>
#include <libavutil/hwcontext_d3d11va.h>
#include <libavutil/pixdesc.h>
#include <libavutil/error.h>
#include <libavutil/frame.h>
}

#ifndef EGL_EGLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES 1
#endif
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>

#include <include/core/SkImage.h>
#include <include/core/SkYUVAInfo.h>
#include <include/gpu/GpuTypes.h>
#include <include/gpu/ganesh/GrBackendSurface.h>
#include <include/gpu/ganesh/GrDirectContext.h>
#include <include/gpu/ganesh/GrYUVABackendTextures.h>
#include <include/gpu/ganesh/SkImageGanesh.h>
#include <include/gpu/ganesh/gl/GrGLBackendSurface.h>
#include <include/gpu/ganesh/gl/GrGLTypes.h>

#include "Core/Timer.h"
#include "CanvasSkia/SkiaBridge.h"

#include "RemoteVideoView.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstring>
#include <deque>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>

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

using namespace Microsoft::WRL;

static void _logGlError(const char* tag) {
    GLenum e = glGetError();
    if (e != GL_NO_ERROR) printf("[rview] GL error %s: 0x%x\n", tag, (unsigned)e);
}

// ============================ Impl ===========================================

struct RemoteVideoView::Impl {
    // 共享渲染设备（进程级，注入 fui ANGLE）
    static ComPtr<ID3D11Device>        s_dev;
    static ComPtr<ID3D11DeviceContext> s_ctx;

    // 每视图独立解码设备 + 解码线程（与渲染主线程 D3D11 context 隔离）
    ComPtr<ID3D11Device>        decDev;
    ComPtr<ID3D11DeviceContext> decD3DCtx;
    std::thread decThread;
    std::mutex qMutex;
    std::condition_variable qCv;
    std::deque<AVFrame*>           q;        // 已解码未渲染帧
    std::deque<std::vector<uint8_t>> pktQ;   // 网络 H.264 包（待解码）
    bool eos = false, stopReq = false;

    // FFmpeg 解码器（d3d11va 硬解）
    AVCodecContext* decCtx = nullptr;
    AVBufferRef*    hwDevRef = nullptr;
    AVPixelFormat   hwPixFmt = AV_PIX_FMT_NONE;
    std::atomic<int> videoW{0}, videoH{0};

    // 渲染（主线程）
    struct CachedSlot {
        EGLImageKHR yImg = EGL_NO_IMAGE_KHR;
        EGLImageKHR uvImg = EGL_NO_IMAGE_KHR;
        GLuint yTex = 0, uvTex = 0;
        sk_sp<SkImage> image;
    };
    struct Slot {
        AVFrame* hwFrame = nullptr;
        std::shared_ptr<CachedSlot> cs;
    };
    Slot slots[3];
    int slotCur = 0;
    sk_sp<SkImage> curImage;
    int64_t lastFrameUs = 0;
    std::map<std::pair<ID3D11Texture2D*, int>, std::shared_ptr<CachedSlot>> texCache;
    std::unordered_map<HANDLE, ComPtr<ID3D11Texture2D>> sharedTexCache;
    std::atomic<long long> framesShown{0};

    bool initDecoder();
    void decodeLoop();
    bool makeImageFromHwFrame(ID3D11Texture2D* tex, int slice, AVFrame* frame, Slot& slot);
    void releaseSlot(Slot& s);
    void clearCaches();
};

ComPtr<ID3D11Device>        RemoteVideoView::Impl::s_dev;
ComPtr<ID3D11DeviceContext> RemoteVideoView::Impl::s_ctx;

static AVPixelFormat g_hwPixFmtAsk = AV_PIX_FMT_D3D11;
static AVPixelFormat _getHwFormat(AVCodecContext*, const AVPixelFormat* fmts) {
    for (int i = 0; fmts[i] != AV_PIX_FMT_NONE; i++) {
        if (fmts[i] == g_hwPixFmtAsk) return fmts[i];
    }
    return fmts[0];
}

static char _errbuf[256];
static const char* _errstr(int err) {
    av_strerror(err, _errbuf, sizeof(_errbuf));
    return _errbuf;
}

// ============================ 共享 GPU 设备 ==================================

bool RemoteVideoView::ensureSharedGpuDevice() {
    if (Impl::s_dev) return true;
    D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
    };
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                   D3D11_CREATE_DEVICE_VIDEO_SUPPORT | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                                   levels, _countof(levels), D3D11_SDK_VERSION,
                                   Impl::s_dev.ReleaseAndGetAddressOf(), nullptr,
                                   Impl::s_ctx.ReleaseAndGetAddressOf());
    if (FAILED(hr)) { printf("[rview] D3D11CreateDevice failed 0x%08x\n", (unsigned)hr); return false; }
    skiaSetExternalD3D11Device((void*)Impl::s_dev.Get());
    printf("[rview] shared D3D11 device 0x%p injected into fui\n", (void*)Impl::s_dev.Get());
    return true;
}

void* RemoteVideoView::sharedD3D11Device() {
    return Impl::s_dev ? (void*)Impl::s_dev.Get() : nullptr;
}

long long RemoteVideoView::framesShown() const { return d ? d->framesShown.load() : 0; }

// ============================ 解码器初始化（解码线程） =========================

bool RemoteVideoView::Impl::initDecoder() {
    // 独立解码设备（与共享渲染设备隔离，避免 D3D11 immediate context 跨线程）
    D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
    };
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                   D3D11_CREATE_DEVICE_VIDEO_SUPPORT | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                                   levels, _countof(levels), D3D11_SDK_VERSION,
                                   decDev.GetAddressOf(), nullptr, decD3DCtx.GetAddressOf());
    if (FAILED(hr)) { printf("[rview] dec device failed 0x%08x\n", (unsigned)hr); return false; }

    const AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec) { printf("[rview] no h264 decoder\n"); return false; }

    for (int i = 0; ; i++) {
        const AVCodecHWConfig* cfg = avcodec_get_hw_config(codec, i);
        if (!cfg) break;
        if (cfg->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX &&
            cfg->device_type == AV_HWDEVICE_TYPE_D3D11VA) {
            hwPixFmt = cfg->pix_fmt;
            break;
        }
    }
    if (hwPixFmt == AV_PIX_FMT_NONE) { printf("[rview] no d3d11va hw config\n"); return false; }

    // 用独立解码设备建 FFmpeg hw device ctx
    AVBufferRef* hwdev = av_hwdevice_ctx_alloc(AV_HWDEVICE_TYPE_D3D11VA);
    if (!hwdev) return false;
    AVHWDeviceContext* hwctx = (AVHWDeviceContext*)hwdev->data;
    AVD3D11VADeviceContext* d3d11va = (AVD3D11VADeviceContext*)hwctx->hwctx;
    decDev.Get()->AddRef();
    decD3DCtx.Get()->AddRef();
    d3d11va->device = decDev.Get();
    d3d11va->device_context = decD3DCtx.Get();
    d3d11va->BindFlags = D3D11_BIND_DECODER | D3D11_BIND_SHADER_RESOURCE;
    d3d11va->MiscFlags = D3D11_RESOURCE_MISC_SHARED;   // 供渲染线程 OpenSharedResource 零拷贝导入
    if (av_hwdevice_ctx_init(hwdev) < 0) {
        printf("[rview] av_hwdevice_ctx_init failed\n");
        av_buffer_unref(&hwdev);
        return false;
    }

    decCtx = avcodec_alloc_context3(codec);
    if (!decCtx) { av_buffer_unref(&hwdev); return false; }
    decCtx->hw_device_ctx = hwdev;   // 所有权转移给 decCtx
    hwDevRef = hwdev;
    decCtx->thread_count = 1;
    decCtx->get_format = _getHwFormat;
    g_hwPixFmtAsk = hwPixFmt;

    int ret = avcodec_open2(decCtx, codec, nullptr);
    if (ret < 0) { printf("[rview] avcodec_open2 failed: %s\n", _errstr(ret)); return false; }
    printf("[rview] h264 decoder ready (d3d11va)\n");
    return true;
}

// ============================ 解码线程 =======================================

void RemoteVideoView::Impl::decodeLoop() {
    if (!initDecoder()) {
        printf("[rview] decode init failed\n");
        eos = true;
        qCv.notify_all();
        return;
    }
    AVPacket* pkt = av_packet_alloc();
    if (!pkt) return;

    while (!stopReq) {
        std::vector<uint8_t> data;
        {
            std::unique_lock<std::mutex> lk(qMutex);
            qCv.wait(lk, [&] { return stopReq || !pktQ.empty(); });
            if (stopReq) break;
            data = std::move(pktQ.front());
            pktQ.pop_front();
        }

        av_packet_unref(pkt);
        pkt->data = data.data();
        pkt->size = (int)data.size();

        int ret = avcodec_send_packet(decCtx, pkt);
        if (ret < 0) {
            static int sendErrLogged = 0;
            if (sendErrLogged++ < 5) printf("[rview] send_packet ret=%d (%s)\n", ret, _errstr(ret));
            continue;
        }
        for (;;) {
            AVFrame* f = av_frame_alloc();
            if (!f) break;
            ret = avcodec_receive_frame(decCtx, f);
            if (ret < 0) { av_frame_free(&f); break; }
            if (f->format == hwPixFmt) {
                videoW = f->width;
                videoH = f->height;
                {
                    std::lock_guard<std::mutex> lk(qMutex);
                    if (q.size() >= 6) {          // 有界队列：丢最旧（显示最新）
                        AVFrame* old = q.front();
                        q.pop_front();
                        av_frame_unref(old);
                        av_frame_free(&old);
                    }
                    q.push_back(f);
                }
                qCv.notify_all();
            } else {
                av_frame_free(&f);
            }
        }
    }
    av_packet_free(&pkt);
    printf("[rview] decode thread exit\n");
}

// ============================ 渲染（主线程） =================================

void RemoteVideoView::Impl::releaseSlot(Slot& s) {
    if (s.hwFrame) { av_frame_unref(s.hwFrame); av_frame_free(&s.hwFrame); }
    s.cs.reset();
}

void RemoteVideoView::Impl::clearCaches() {
    EGLDisplay ed = (EGLDisplay)skiaGetEGLDisplay();
    if (ed != EGL_NO_DISPLAY) {
        for (auto& kv : texCache) {
            CachedSlot& cs = *kv.second;
            if (cs.yImg != EGL_NO_IMAGE_KHR) eglDestroyImageKHR(ed, cs.yImg);
            if (cs.uvImg != EGL_NO_IMAGE_KHR) eglDestroyImageKHR(ed, cs.uvImg);
            cs.yImg = cs.uvImg = EGL_NO_IMAGE_KHR;
            if (cs.yTex) { glDeleteTextures(1, &cs.yTex); cs.yTex = 0; }
            if (cs.uvTex) { glDeleteTextures(1, &cs.uvTex); cs.uvTex = 0; }
        }
    }
    texCache.clear();
    sharedTexCache.clear();
}

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

bool RemoteVideoView::Impl::makeImageFromHwFrame(ID3D11Texture2D* tex, int slice, AVFrame* hwFrame, Slot& slot) {
    EGLDisplay display = (EGLDisplay)skiaGetEGLDisplay();
    GrDirectContext* gr = (GrDirectContext*)skiaCanvasGetGrContext();
    if (display == EGL_NO_DISPLAY || !gr || !tex) return false;

    slot.hwFrame = av_frame_alloc();
    if (!slot.hwFrame) return false;
    av_frame_ref(slot.hwFrame, hwFrame);

    auto key = std::make_pair(tex, slice);
    auto it = texCache.find(key);
    if (it != texCache.end()) {
        slot.cs = it->second;
        if (slot.cs->image) return true;
        slot.cs.reset();
    }

    auto cs = std::make_shared<CachedSlot>();
    EGLint yAttrs[]  = { EGL_D3D11_TEXTURE_PLANE_ANGLE, 0,
                         EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE, slice, EGL_NONE };
    EGLint uvAttrs[] = { EGL_D3D11_TEXTURE_PLANE_ANGLE, 1,
                         EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE, slice, EGL_NONE };
    cs->yImg = eglCreateImageKHR(display, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE,
                                 reinterpret_cast<EGLClientBuffer>(tex), yAttrs);
    if (cs->yImg == EGL_NO_IMAGE_KHR) return false;
    cs->uvImg = eglCreateImageKHR(display, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE,
                                  reinterpret_cast<EGLClientBuffer>(tex), uvAttrs);
    if (cs->uvImg == EGL_NO_IMAGE_KHR) {
        eglDestroyImageKHR(display, cs->yImg);
        cs->yImg = EGL_NO_IMAGE_KHR;
        return false;
    }

    glGenTextures(1, &cs->yTex);
    glBindTexture(GL_TEXTURE_2D, cs->yTex);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, cs->yImg);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenTextures(1, &cs->uvTex);
    glBindTexture(GL_TEXTURE_2D, cs->uvTex);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, cs->uvImg);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    _logGlError("texture setup");

    int vw = videoW.load(), vh = videoH.load();
    if (vw <= 0 || vh <= 0) return false;

    GrGLTextureInfo yInfo{};
    yInfo.fTarget = GL_TEXTURE_2D; yInfo.fID = cs->yTex;  yInfo.fFormat = GL_R8;
    GrGLTextureInfo uvInfo{};
    uvInfo.fTarget = GL_TEXTURE_2D; uvInfo.fID = cs->uvTex; uvInfo.fFormat = GL_RG8;

    GrBackendTexture yBT  = GrBackendTextures::MakeGL(vw, vh, skgpu::Mipmapped::kNo, yInfo, "rd_y");
    GrBackendTexture uvBT = GrBackendTextures::MakeGL(vw / 2, vh / 2, skgpu::Mipmapped::kNo, uvInfo, "rd_uv");

    GrBackendTexture planes[SkYUVAInfo::kMaxPlanes] = { yBT, uvBT, GrBackendTexture(), GrBackendTexture() };
    SkYUVAInfo yuvaInfo(SkISize::Make(vw, vh), SkYUVAInfo::PlaneConfig::kY_UV,
                        SkYUVAInfo::Subsampling::k420, _pickYuvCs(hwFrame));
    GrYUVABackendTextures yuvaTextures(yuvaInfo, planes, kTopLeft_GrSurfaceOrigin);

    cs->image = SkImages::TextureFromYUVATextures(gr, yuvaTextures);
    if (!cs->image) { printf("[rview] TextureFromYUVATextures failed\n"); return false; }

    texCache[key] = cs;
    slot.cs = cs;
    return true;
}

// ============================ 视图生命周期 ===================================

RemoteVideoView::RemoteVideoView() {
    d = new Impl();
}

RemoteVideoView::~RemoteVideoView() {
    stopStream();
    Impl* p = d;
    if (!p) return;
    p->curImage.reset();
    p->releaseSlot(p->slots[0]);
    p->releaseSlot(p->slots[1]);
    p->releaseSlot(p->slots[2]);
    p->texCache.clear();
    p->sharedTexCache.clear();
    if (p->decCtx) { avcodec_free_context(&p->decCtx); p->decCtx = nullptr; }
    if (p->hwDevRef) { av_buffer_unref(&p->hwDevRef); p->hwDevRef = nullptr; }
    delete d;
    d = nullptr;
}

void RemoteVideoView::startStream() {
    if (!d) return;
    stopStream();
    Impl* p = d;
    p->stopReq = false;
    p->eos = false;
    p->lastFrameUs = 0;
    p->decThread = std::thread([p] { p->decodeLoop(); });

    auto self = Ref(this);
    _tickTimer = mkTimerInterval(CLOSURE([=]() {
        if (self.get()) self->tickFrame();
    }), 8);
}

void RemoteVideoView::stopStream() {
    if (!d) return;
    Impl* p = d;
    if (_tickTimer) {
        _tickTimer->cancel();
        _tickTimer->runFunc = nullptr;
        _tickTimer = nullptr;
    }
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
    {
        std::lock_guard<std::mutex> lk(p->qMutex);
        p->pktQ.clear();
    }
    p->releaseSlot(p->slots[0]);
    p->releaseSlot(p->slots[1]);
    p->releaseSlot(p->slots[2]);
    p->curImage.reset();
    p->slotCur = 0;
    if (p->decCtx) { avcodec_free_context(&p->decCtx); p->decCtx = nullptr; }
    if (p->hwDevRef) { av_buffer_unref(&p->hwDevRef); p->hwDevRef = nullptr; }
    p->videoW = 0; p->videoH = 0;
    p->clearCaches();
}

void RemoteVideoView::feedPacket(const uint8_t* data, size_t len) {
    if (!d || !data || len == 0) return;
    std::vector<uint8_t> v(data, data + len);
    {
        std::lock_guard<std::mutex> lk(d->qMutex);
        d->pktQ.push_back(std::move(v));
    }
    d->qCv.notify_all();
}

// ============================ 帧驱动 =========================================

void RemoteVideoView::tickFrame() {
    Impl* p = d;
    if (!p || !p->decThread.joinable()) return;

    // 每 33ms 显示一帧（30fps 远程流）；每次取最新帧（解码队列已丢旧保新）
    int64_t intervalUs = 33333;
    int64_t nowUs = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
    if (p->lastFrameUs == 0) p->lastFrameUs = nowUs - intervalUs;
    if (nowUs - p->lastFrameUs < intervalUs) return;
    p->lastFrameUs = nowUs;

    AVFrame* frame = nullptr;
    {
        std::lock_guard<std::mutex> lk(p->qMutex);
        if (!p->q.empty()) {
            frame = p->q.front();
            p->q.pop_front();
        }
    }
    if (!frame) return;
    p->qCv.notify_all();

    // 零拷贝导入共享渲染设备
    ComPtr<ID3D11Texture2D> sharedTex;
    bool sharedOk = false;
    ID3D11Texture2D* decTex = reinterpret_cast<ID3D11Texture2D*>(frame->data[0]);
    if (decTex && Impl::s_dev) {
        ComPtr<IDXGIResource> res;
        HANDLE shareH = nullptr;
        if (SUCCEEDED(decTex->QueryInterface(__uuidof(IDXGIResource), (void**)&res)) &&
            SUCCEEDED(res->GetSharedHandle(&shareH)) && shareH) {
            auto sit = p->sharedTexCache.find(shareH);
            if (sit != p->sharedTexCache.end()) {
                sharedTex = sit->second;
                sharedOk = true;
            } else if (SUCCEEDED(Impl::s_dev->OpenSharedResource(
                       shareH, __uuidof(ID3D11Texture2D), (void**)&sharedTex))) {
                p->sharedTexCache[shareH] = sharedTex;
                sharedOk = true;
            }
        }
    }
    if (!sharedOk) {
        static int sharedFailLogged = 0;
        if (sharedFailLogged++ < 5) printf("[rview] OpenSharedResource/GetSharedHandle fail\n");
        av_frame_unref(frame);
        av_frame_free(&frame);
        return;
    }

    p->releaseSlot(p->slots[(p->slotCur + 1) % 3]);
    int slice = static_cast<int>(reinterpret_cast<intptr_t>(frame->data[1]));
    bool ok = p->makeImageFromHwFrame(sharedTex.Get(), slice, frame, p->slots[p->slotCur]);
    if (ok && p->slots[p->slotCur].cs) {
        p->curImage = p->slots[p->slotCur].cs->image;
        p->framesShown++;
        invalidDraw();
    } else {
        static int mkFailLogged = 0;
        if (mkFailLogged++ < 5) printf("[rview] makeImageFromHwFrame fail (ok=%d cs=%d)\n", (int)ok, (int)(p->slots[p->slotCur].cs != nullptr));
    }
    p->slotCur = (p->slotCur + 1) % 3;
    av_frame_unref(frame);
    av_frame_free(&frame);
}

// ============================ 绘制 ===========================================

void RemoteVideoView::draw_self(Canvas* canvas) {
    View::draw_self(canvas);
    if (!d || !d->curImage) return;

    Rect r = getViewRect();
    if (r.w <= 0.5f || r.h <= 0.5f) return;

    int vw = d->videoW.load(), vh = d->videoH.load();
    if (vw <= 0 || vh <= 0) return;

    // fill 拉伸铺满（远程桌面鼠标坐标按窗口客户区归一化，与显示一致）
    skiaCanvasDrawImageAtRect(d->curImage.get(), 0, 0, (float)vw, (float)vh,
                              r.x, r.y, r.w, r.h, 1.0f);
}
