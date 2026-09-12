// ============================================================================
// ScreenCapture.cpp — DXGI Desktop Duplication 屏幕采集
// ============================================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <cstdio>

#include "ScreenCapture.h"

using namespace Microsoft::WRL;

bool ScreenCapture::init() {
    close();

    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
                                   D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                   D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                                   levels, _countof(levels), D3D11_SDK_VERSION,
                                   &dev, nullptr, &ctx);
    if (FAILED(hr)) { printf("[capture] D3D11CreateDevice failed 0x%08x\n", (unsigned)hr); return false; }

    ComPtr<IDXGIDevice> dxgiDev;
    ComPtr<IDXGIAdapter> adapter;
    ComPtr<IDXGIOutput> output;
    if (FAILED(dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDev)) ||
        FAILED(dxgiDev->GetAdapter(&adapter)) ||
        FAILED(adapter->EnumOutputs(0, &output))) {
        printf("[capture] no primary output\n");
        return false;
    }
    ComPtr<IDXGIOutput1> out1;
    if (FAILED(output->QueryInterface(__uuidof(IDXGIOutput1), (void**)&out1)) ||
        FAILED(out1->DuplicateOutput(dev.Get(), &dup))) {
        printf("[capture] DuplicateOutput failed\n");
        return false;
    }

    DXGI_OUTPUT_DESC od{};
    output->GetDesc(&od);
    w = (int)od.DesktopCoordinates.right - (int)od.DesktopCoordinates.left;
    h = (int)od.DesktopCoordinates.bottom - (int)od.DesktopCoordinates.top;
    if (w <= 0 || h <= 0) { printf("[capture] bad desktop size %dx%d\n", w, h); return false; }

    D3D11_TEXTURE2D_DESC sd{};
    sd.Width = w; sd.Height = h;
    sd.MipLevels = 1; sd.ArraySize = 1;
    sd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.SampleDesc.Count = 1;
    sd.Usage = D3D11_USAGE_STAGING;
    sd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    hr = dev->CreateTexture2D(&sd, nullptr, &staging);
    if (FAILED(hr)) { printf("[capture] staging tex failed\n"); return false; }

    printf("[capture] desktop %dx%d ready\n", w, h);
    return true;
}

bool ScreenCapture::captureBGRA(std::vector<uint8_t>& out, int& ow, int& oh) {
    if (!dup) return false;
    DXGI_OUTDUPL_FRAME_INFO info{};
    ComPtr<IDXGIResource> res;
    HRESULT hr = dup->AcquireNextFrame(200, &info, &res);
    if (hr == DXGI_ERROR_WAIT_TIMEOUT) return false;      // 无新帧
    if (hr == DXGI_ERROR_ACCESS_LOST) {
        // 桌面会话切换：重建 duplication
        close();
        if (!init()) return false;
        return false;
    }
    if (FAILED(hr) || !res) return false;

    ComPtr<ID3D11Texture2D> tex;
    res->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&tex);
    if (tex) {
        ctx->CopyResource(staging.Get(), tex.Get());
        D3D11_MAPPED_SUBRESOURCE map{};
        if (SUCCEEDED(ctx->Map(staging.Get(), 0, D3D11_MAP_READ, 0, &map))) {
            out.resize((size_t)w * h * 4);
            const uint8_t* src = (const uint8_t*)map.pData;
            uint8_t* dst = out.data();
            for (int y = 0; y < h; y++) {
                memcpy(dst + (size_t)y * w * 4, src + (size_t)y * map.RowPitch, (size_t)w * 4);
            }
            ctx->Unmap(staging.Get(), 0);
            ow = w; oh = h;
            dup->ReleaseFrame();
            return true;
        }
    }
    dup->ReleaseFrame();
    return false;
}

void ScreenCapture::close() {
    if (dup) { dup->ReleaseFrame(); dup.Reset(); }
    staging.Reset();
    ctx.Reset();
    dev.Reset();
    w = h = 0;
}
