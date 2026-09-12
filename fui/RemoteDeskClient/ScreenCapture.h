// ============================================================================
// ScreenCapture.h — DXGI Desktop Duplication 屏幕采集（主显示器）
// ============================================================================
#pragma once
#include <cstdint>
#include <vector>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <wrl/client.h>

class ScreenCapture {
public:
    ScreenCapture() = default;
    ~ScreenCapture() { close(); }

    bool init();
    // 采集一帧全屏 BGRA（自上而下行序），返回 false 表示失败/无新帧
    bool captureBGRA(std::vector<uint8_t>& out, int& w, int& h);
    void close();

    int width() const { return w; }
    int height() const { return h; }

private:
    Microsoft::WRL::ComPtr<ID3D11Device>        dev;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> ctx;
    Microsoft::WRL::ComPtr<IDXGIOutputDuplication> dup;
    Microsoft::WRL::ComPtr<ID3D11Texture2D>     staging;
    int w = 0, h = 0;
};
