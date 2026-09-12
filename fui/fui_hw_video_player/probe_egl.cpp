// probe_egl.cpp — 最小探针：验证 ANGLE(用户lib) 对 D3D11 NV12 纹理 -> EGLImage -> GL 的支持
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
#include <string.h>

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

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    ID3D11Device* dev = nullptr;
    D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_9_1;
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        D3D11_CREATE_DEVICE_VIDEO_SUPPORT | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        nullptr, 0, D3D11_SDK_VERSION, &dev, &fl, nullptr);
    printf("d3d11 hr=0x%08x fl=0x%x\n", (unsigned)hr, (unsigned)fl);
    if (FAILED(hr)) return 1;

    D3D11_TEXTURE2D_DESC td = {};
    td.Width = 960; td.Height = 400; td.MipLevels = 1; td.ArraySize = 8;
    td.Format = DXGI_FORMAT_NV12;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_DECODER | D3D11_BIND_SHADER_RESOURCE;
    td.MiscFlags = D3D11_RESOURCE_MISC_SHARED;
    ID3D11Texture2D* tex = nullptr;
    hr = dev->CreateTexture2D(&td, nullptr, &tex);
    printf("CreateTexture2D NV12 arr8 hr=0x%08x\n", (unsigned)hr);
    if (FAILED(hr)) return 1;

    EGLDeviceEXT edev = eglCreateDeviceANGLE(EGL_D3D11_DEVICE_ANGLE, dev, nullptr);
    printf("eglCreateDeviceANGLE = %p (err 0x%x)\n", (void*)edev, eglGetError());
    if (!edev) return 1;
    EGLDisplay dpy = eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, edev, nullptr);
    printf("eglGetPlatformDisplayEXT = %p (err 0x%x)\n", (void*)dpy, eglGetError());
    if (dpy == EGL_NO_DISPLAY) return 1;
    EGLint maj, min;
    if (!eglInitialize(dpy, &maj, &min)) { printf("eglInitialize failed 0x%x\n", eglGetError()); return 1; }
    printf("EGL %d.%d | %s\n", (int)maj, (int)min, eglQueryString(dpy, EGL_VENDOR));

    EGLConfig cfg; EGLint ncfg = 0;
    EGLint cfgAttrs[] = { EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE };
    eglChooseConfig(dpy, cfgAttrs, &cfg, 1, &ncfg);
    EGLint ctxAttrs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    EGLContext ctx = eglCreateContext(dpy, cfg, EGL_NO_CONTEXT, ctxAttrs);
    printf("ctx = %p (err 0x%x)\n", (void*)ctx, eglGetError());
    if (ctx == EGL_NO_CONTEXT) return 1;
    eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);

    const char* exts = eglQueryString(dpy, EGL_EXTENSIONS);
    printf("has EGL_ANGLE_image_d3d11_texture: %d\n", exts && strstr(exts, "EGL_ANGLE_image_d3d11_texture") ? 1 : 0);

    // T1: plane0, no slice
    EGLint a1[] = { EGL_D3D11_TEXTURE_PLANE_ANGLE, 0, EGL_NONE };
    EGLImageKHR im1 = eglCreateImageKHR(dpy, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE, (EGLClientBuffer)tex, a1);
    printf("T1 plane0 noslice  = %p err 0x%x\n", (void*)im1, eglGetError());
    // T2: plane0, slice0
    EGLint a2[] = { EGL_D3D11_TEXTURE_PLANE_ANGLE, 0, EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE, 0, EGL_NONE };
    EGLImageKHR im2 = eglCreateImageKHR(dpy, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE, (EGLClientBuffer)tex, a2);
    printf("T2 plane0 slice0   = %p err 0x%x\n", (void*)im2, eglGetError());
    // T3: plane1, slice0
    EGLint a3[] = { EGL_D3D11_TEXTURE_PLANE_ANGLE, 1, EGL_D3D11_TEXTURE_ARRAY_SLICE_ANGLE, 0, EGL_NONE };
    EGLImageKHR im3 = eglCreateImageKHR(dpy, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE, (EGLClientBuffer)tex, a3);
    printf("T3 plane1 slice0   = %p err 0x%x\n", (void*)im3, eglGetError());
    // T4: no attrs
    EGLImageKHR im4 = eglCreateImageKHR(dpy, EGL_NO_CONTEXT, EGL_D3D11_TEXTURE_ANGLE, (EGLClientBuffer)tex, nullptr);
    printf("T4 noattrs         = %p err 0x%x\n", (void*)im4, eglGetError());

    GLuint t = 0;
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);
    if (im1) { glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, im1); printf("bind im1 gle=0x%x\n", (unsigned)glGetError()); }
    if (im2) { glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, im2); printf("bind im2 gle=0x%x\n", (unsigned)glGetError()); }
    if (im3) { glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, im3); printf("bind im3 gle=0x%x\n", (unsigned)glGetError()); }
    if (im4) { glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, im4); printf("bind im4 gle=0x%x\n", (unsigned)glGetError()); }
    printf("done\n");
    return 0;
}
