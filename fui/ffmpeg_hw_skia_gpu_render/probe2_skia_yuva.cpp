// probe2_skia_yuva.cpp — 复刻应用 Skia YUVA 路径，隔离崩溃点
// 用法: probe2_skia_yuva.exe <variant 1|2|3>
//   v1: MakeGL(GL_R8, GL_RED) / (GL_RG8, GL_RG)      —— 应用当前写法
//   v2: MakeGL(GL_R8, 0)      / (GL_RG8, 0)
//   v3: MakeGL(GL_R8, GL_TEXTURE_2D) / (GL_RG8, GL_TEXTURE_2D)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <d3d11.h>
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkImage.h"
#include "include/core/SkImageInfo.h"
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

#ifndef EGL_D3D11_DEVICE_ANGLE
#define EGL_D3D11_DEVICE_ANGLE 0x33A1
#endif
#ifndef EGL_PLATFORM_DEVICE_EXT
#define EGL_PLATFORM_DEVICE_EXT 0x313F
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

static GrGLFuncPtr egl_get_proc(void*, const char name[]) {
    return (GrGLFuncPtr)eglGetProcAddress(name);
}

int main(int argc, char** argv) {
    setvbuf(stdout, nullptr, _IONBF, 0);
    int variant = argc > 1 ? atoi(argv[1]) : 1;
    printf("variant = %d\n", variant);

    ID3D11Device* dev = nullptr;
    D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_9_1;
    D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        D3D11_CREATE_DEVICE_VIDEO_SUPPORT | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        nullptr, 0, D3D11_SDK_VERSION, &dev, &fl, nullptr);

    D3D11_TEXTURE2D_DESC td = {};
    td.Width = 960; td.Height = 400; td.MipLevels = 1; td.ArraySize = 8;
    td.Format = DXGI_FORMAT_NV12;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_DECODER | D3D11_BIND_SHADER_RESOURCE;
    td.MiscFlags = D3D11_RESOURCE_MISC_SHARED;
    ID3D11Texture2D* tex = nullptr;
    dev->CreateTexture2D(&td, nullptr, &tex);
    printf("d3d11 tex ok\n");

    EGLDeviceEXT edev = eglCreateDeviceANGLE(EGL_D3D11_DEVICE_ANGLE, dev, nullptr);
    EGLDisplay dpy = eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, edev, nullptr);
    EGLint maj, min;
    eglInitialize(dpy, &maj, &min);

    EGLConfig cfg; EGLint ncfg = 0;
    EGLint cfgAttrs[] = { EGL_SURFACE_TYPE, EGL_PBUFFER_BIT, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, EGL_NONE };
    eglChooseConfig(dpy, cfgAttrs, &cfg, 1, &ncfg);
    EGLint ctxAttrs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    EGLContext ctx = eglCreateContext(dpy, cfg, EGL_NO_CONTEXT, ctxAttrs);
    // 用 pbuffer 表面，让 Skia 有默认帧缓冲可画
    EGLint pbAttrs[] = { EGL_WIDTH, 960, EGL_HEIGHT, 400, EGL_NONE };
    EGLSurface surf = eglCreatePbufferSurface(dpy, cfg, pbAttrs);
    eglMakeCurrent(dpy, surf, surf, ctx);
    printf("egl ctx + pbuffer ok\n");

    sk_sp<const GrGLInterface> glInterface = GrGLMakeAssembledInterface(nullptr, egl_get_proc);
    if (!glInterface) { printf("FAIL: GrGLMakeAssembledInterface\n"); return 2; }
    sk_sp<GrDirectContext> grContext = GrDirectContexts::MakeGL(glInterface);
    if (!grContext) { printf("FAIL: GrDirectContexts::MakeGL\n"); return 2; }
    printf("skia ctx ok\n");

    // EGLImage 导入（slice 0）—— 用字面量避免宏歧义（0x3492=plane, 0x3493=slice）
    EGLint yAttrs[]  = { 0x3492, 0, 0x3493, 0, EGL_NONE };
    EGLint uvAttrs[] = { 0x3492, 1, 0x3493, 0, EGL_NONE };
    EGLImageKHR yImg = eglCreateImageKHR(dpy, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE, (EGLClientBuffer)tex, yAttrs);
    EGLImageKHR uvImg = eglCreateImageKHR(dpy, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE, (EGLClientBuffer)tex, uvAttrs);
    printf("images: y=%p uv=%p err=0x%x\n", (void*)yImg, (void*)uvImg, eglGetError());

    GLuint yTex = 0, uvTex = 0;
    glGenTextures(1, &yTex);
    glBindTexture(GL_TEXTURE_2D, yTex);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, yImg);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenTextures(1, &uvTex);
    glBindTexture(GL_TEXTURE_2D, uvTex);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, uvImg);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    printf("gl bind ok err=0x%x\n", (unsigned)glGetError());

    // 用当前上下文直接采样 Y 平面验证纹理内容可读
    // （先验证 EGLImage 纹理真能读，排除“纹理无效”这一层）
    {
        GLuint prog = glCreateProgram();
        // 简化：直接读像素需要 FBO；先跳过，信任 bind ok
        glDeleteProgram(prog);
    }

    int vw = 960, vh = 400;
    GrGLTextureInfo yInfo{};
    yInfo.fTarget = GL_TEXTURE_2D; yInfo.fID = yTex;  yInfo.fFormat = GL_R8;
    GrGLTextureInfo uvInfo{};
    uvInfo.fTarget = GL_TEXTURE_2D; uvInfo.fID = uvTex; uvInfo.fFormat = GL_RG8;

    GrBackendFormat yFmt, uvFmt;
    if (variant == 1) {
        yFmt  = GrBackendFormats::MakeGL(GL_R8,  GL_RED);
        uvFmt = GrBackendFormats::MakeGL(GL_RG8, GL_RG);
    } else if (variant == 2) {
        yFmt  = GrBackendFormats::MakeGL(GL_R8,  0);
        uvFmt = GrBackendFormats::MakeGL(GL_RG8, 0);
    } else {
        yFmt  = GrBackendFormats::MakeGL(GL_R8,  GL_TEXTURE_2D);
        uvFmt = GrBackendFormats::MakeGL(GL_RG8, GL_TEXTURE_2D);
    }

    GrBackendTexture yBT  = GrBackendTextures::MakeGL(vw, vh, skgpu::Mipmapped::kNo, yInfo, "decoded_y");
    GrBackendTexture uvBT = GrBackendTextures::MakeGL(vw / 2, vh / 2, skgpu::Mipmapped::kNo, uvInfo, "decoded_uv");

    GrBackendTexture planes[SkYUVAInfo::kMaxPlanes] = { yBT, uvBT, GrBackendTexture(), GrBackendTexture() };
    SkYUVAInfo yuvaInfo(SkISize::Make(vw, vh),
                        SkYUVAInfo::PlaneConfig::kY_UV,
                        SkYUVAInfo::Subsampling::k420,
                        kRec709_Limited_SkYUVColorSpace);
    GrYUVABackendTextures yuvaTextures(yuvaInfo, planes, kTopLeft_GrSurfaceOrigin);
    printf("backend textures ok, calling TextureFromYUVATextures...\n");

    sk_sp<SkImage> img = SkImages::TextureFromYUVATextures(grContext.get(), yuvaTextures);
    printf("TextureFromYUVATextures -> %p\n", (void*)img.get());
    if (!img) { printf("FAIL: image is null\n"); return 3; }

    // 画到 pbuffer 表面验证 GPU 管线
    GrGLFramebufferInfo fbInfo{};
    fbInfo.fFBOID = 0;
    fbInfo.fFormat = GL_RGBA8;
    GrBackendRenderTarget rt = GrBackendRenderTargets::MakeGL(960, 400, 0, 0, fbInfo);
    auto surf2 = SkSurfaces::WrapBackendRenderTarget(grContext.get(), rt, kBottomLeft_GrSurfaceOrigin,
                                                     kRGBA_8888_SkColorType, SkColorSpace::MakeSRGB(), nullptr, nullptr);
    if (!surf2) { printf("FAIL: WrapBackendRenderTarget\n"); return 4; }
    SkCanvas* canvas = surf2->getCanvas();
    canvas->clear(SK_ColorBLACK);
    SkSamplingOptions sampling(SkFilterMode::kLinear, SkMipmapMode::kNone);
    canvas->drawImageRect(img.get(), SkRect::MakeWH(960, 400), sampling, nullptr);
    skgpu::ganesh::FlushAndSubmit(surf2.get());
    printf("draw + flush ok\n");
    return 0;
}
