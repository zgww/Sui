#include "../Core/Canvas.h"

#include <windows.h>
#include <objbase.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include <string>
#include <stdio.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "ole32.lib")


// ---------------------------------------------------------------------------
// 后端内部状态
// ---------------------------------------------------------------------------

struct CanvasState {
	D2D1::Matrix3x2F xform = D2D1::Matrix3x2F::Identity();
	float globalAlpha;
	float strokeW;
	D2D1_CAP_STYLE cap;
	D2D1_LINE_JOIN join;
	int fillColor;
	int strokeColor;
	bool hasScissor;
	D2D1_RECT_F scissorRect;
	D2D1::Matrix3x2F scissorXform = D2D1::Matrix3x2F::Identity();
	std::string fontFace;
	float fontSize;
	int textAlignFlags;
	float letterSpacing;
	float lineHeight;
	float fontBlur;
	int shadowColor;
	float shadowOffsetX;
	float shadowOffsetY;
	float shadowBlur;
};

struct CanvasCtx {
	// 工厂
	ID2D1Factory1* factory1 = nullptr;   // 用于 CreateDevice
	ID2D1Factory* factory = nullptr;     // 用于 CreatePathGeometry/CreateStrokeStyle
	IDWriteFactory* dwriteFactory = nullptr;

	// 每个窗口的设备上下文 + 交换链
	ID2D1DeviceContext* rt = nullptr;
	IDXGISwapChain1* swapChain = nullptr;
	ID2D1Bitmap1* targetBitmap = nullptr;
	HWND hwnd = nullptr;

	// 帧尺寸 / dpi
	float frameW = 0;
	float frameH = 0;
	float dpr = 1.0f;
	D2D1::Matrix3x2F baseScale = D2D1::Matrix3x2F::Identity();

	// 用户坐标系变换（不含dpr缩放）
	D2D1::Matrix3x2F xform = D2D1::Matrix3x2F::Identity();

	// 路径（几何可复用，方便同一路径多次 fill/stroke）
	ID2D1PathGeometry* pathGeo = nullptr;
	ID2D1GeometrySink* sink = nullptr;
	bool figureOpen = false;
	bool figureClosed = false;
	float lastX = 0;
	float lastY = 0;

	// 画刷
	ID2D1SolidColorBrush* fillSolid = nullptr;
	ID2D1SolidColorBrush* strokeSolid = nullptr;
	ID2D1Brush* fillBrush = nullptr;
	ID2D1Brush* strokeBrush = nullptr;
	int fillColor = 0xFF000000;
	int strokeColor = 0xFF000000;

	float strokeW = 1.0f;
	D2D1_CAP_STYLE cap = D2D1_CAP_STYLE_FLAT;
	D2D1_LINE_JOIN join = D2D1_LINE_JOIN_MITER;
	ID2D1StrokeStyle* strokeStyle = nullptr;
	float globalAlpha = 1.0f;

	// 裁剪
	bool hasScissor = false;
	D2D1_RECT_F scissorRect{};
	D2D1::Matrix3x2F scissorXform = D2D1::Matrix3x2F::Identity();

	// 字体 / 文本
	std::string fontFace = "sans";
	float fontSize = 16.0f;
	int textAlignFlags = CANVAS_ALIGN_LEFT | CANVAS_ALIGN_BASELINE;
	float letterSpacing = 0.0f;
	float lineHeight = 1.0f;
	float fontBlur = 0.0f;

	// 阴影
	int shadowColor = 0; // 0 = 透明 = 无阴影
	float shadowOffsetX = 0;
	float shadowOffsetY = 0;
	float shadowBlur = 0;

	// 阴影离屏资源（用 D2D 1.1 Shadow effect）
	ID2D1DeviceContext* shadowDC = nullptr;
	ID2D1Bitmap1* shadowBmp = nullptr;
	ID2D1SolidColorBrush* shadowWhiteBrush = nullptr;
	ID2D1Effect* shadowEffect = nullptr;
	float shadowBmpW = 0;
	float shadowBmpH = 0;

	IDWriteTextFormat* textFormat = nullptr;
	std::string textFormatFace;
	float textFormatSize = -1.0f;

	// 字体度量缓存（避免每次 text()/textBounds() 都查询系统字体集合）
	struct {
		std::string face;
		UINT16 designUnitsPerEm = 0;
		UINT16 ascent = 0;
		UINT16 descent = 0;
		UINT16 lineGap = 0;
		bool valid = false;
	} metricsCache;

	// 状态栈
	std::vector<CanvasState> stack;
};

// 全局共享工厂（所有窗口共享，保证位图可跨渲染目标使用）
static ID2D1Factory1* g_d2dFactory = nullptr;
static ID2D1Device* g_d2dDevice = nullptr;
static ID3D11Device* g_d3dDevice = nullptr;
static IDWriteFactory* g_dwriteFactory = nullptr;
static IWICImagingFactory* g_wicFactory = nullptr;

static void ensureFactories() {
	if (!g_dwriteFactory) {
		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&g_dwriteFactory);
	}
	if (!g_wicFactory) {
		CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_wicFactory));
	}
	if (!g_d2dFactory) {
		D2D1_FACTORY_OPTIONS opt = {};
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &opt, (void**)&g_d2dFactory);
	}
	if (!g_d3dDevice && g_d2dFactory) {
		D3D_FEATURE_LEVEL levels[] = {
			D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		D3D_FEATURE_LEVEL got = D3D_FEATURE_LEVEL_10_0;
		HRESULT hr = D3D11CreateDevice(
			nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
			levels, (UINT)(sizeof(levels) / sizeof(levels[0])), D3D11_SDK_VERSION,
			&g_d3dDevice, &got, nullptr);
		if (SUCCEEDED(hr) && g_d3dDevice) {
			IDXGIDevice* dxgiDevice = nullptr;
			if (SUCCEEDED(g_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice)) && dxgiDevice) {
				g_d2dFactory->CreateDevice(dxgiDevice, &g_d2dDevice);
				dxgiDevice->Release();
			}
		}
	}
}

static Canvas* gCanvas;

// ---------------------------------------------------------------------------
// 辅助函数
// ---------------------------------------------------------------------------

static D2D1::Matrix3x2F mat2d_to_d2d(const float* t) {
	return D2D1::Matrix3x2F(t[0], t[1], t[2], t[3], t[4], t[5]);
}

static void d2d_to_mat2d(const D2D1::Matrix3x2F& m, Mat2d* out) {
	out->data[0] = m._11; out->data[1] = m._12;
	out->data[2] = m._21; out->data[3] = m._22;
	out->data[4] = m._31; out->data[5] = m._32;
}

static D2D1::Matrix3x2F mat_inverse(const D2D1::Matrix3x2F& m) {
	float a = m._11, b = m._12, c = m._21, d = m._22, e = m._31, f = m._32;
	float det = a * d - b * c;
	if (det > -1e-9f && det < 1e-9f) {
		return D2D1::Matrix3x2F::Identity();
	}
	float ia = d / det, ib = -b / det, ic = -c / det, id = a / det;
	float ie = (c * f - d * e) / det;
	float ief = (b * e - a * f) / det;
	return D2D1::Matrix3x2F(ia, ib, ic, id, ie, ief);
}

static D2D1::ColorF color_from_int(int color, float alphaMult) {
	float a = (float)((color >> 24) & 0xFF) / 255.0f;
	float r = (float)((color >> 16) & 0xFF) / 255.0f;
	float g = (float)((color >> 8) & 0xFF) / 255.0f;
	float b = (float)((color >> 0) & 0xFF) / 255.0f;
	return D2D1::ColorF(r, g, b, a * alphaMult);
}

static std::wstring utf8_to_wide(const char* str, const char* end = nullptr) {
	if (!str) return std::wstring();
	int len = end ? (int)(end - str) : -1;
	int wlen = MultiByteToWideChar(CP_UTF8, 0, str, len, nullptr, 0);
	if (wlen <= 0) return std::wstring();
	std::wstring out(wlen, 0);
	MultiByteToWideChar(CP_UTF8, 0, str, len, &out[0], wlen);
	return out;
}

static const wchar_t* map_face(const std::string& face) {
	if (face == "sans" || face == "sans-serif" || face.empty()) {
		return L"Microsoft YaHei";
	}
	// 其余名字直接按UTF8转宽字符后使用，缓存到静态
	static thread_local std::wstring buf;
	buf = utf8_to_wide(face.c_str());
	return buf.c_str();
}

// ---------------------------------------------------------------------------
// Canvas 实现
// ---------------------------------------------------------------------------

Canvas::Canvas() {
	gCanvas = this;
}

Canvas::~Canvas() {
	if (gCanvas == this) {
		gCanvas = nullptr;
	}
}

void Canvas::init() {
	ensureFactories();
}

// 从交换链当前后缓冲重建 target bitmap 并设为渲染目标
static void set_target_from_swapchain(CanvasCtx* ctx) {
	if (!ctx->swapChain || !ctx->rt) return;
	if (ctx->targetBitmap) {
		ctx->rt->SetTarget(nullptr);
		ctx->targetBitmap->Release();
		ctx->targetBitmap = nullptr;
	}
	IDXGISurface* surface = nullptr;
	if (SUCCEEDED(ctx->swapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&surface)) && surface) {
		D2D1_BITMAP_PROPERTIES1 bp = D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));
		ctx->rt->CreateBitmapFromDxgiSurface(surface, &bp, &ctx->targetBitmap);
		surface->Release();
		ctx->rt->SetTarget(ctx->targetBitmap);
	}
}

static void resize_swapchain(CanvasCtx* ctx, UINT32 w, UINT32 h) {
	if (!ctx->swapChain || !ctx->rt) return;
	if (w < 1) w = 1;
	if (h < 1) h = 1;
	ctx->rt->SetTarget(nullptr);
	if (ctx->targetBitmap) { ctx->targetBitmap->Release(); ctx->targetBitmap = nullptr; }
	ctx->swapChain->ResizeBuffers(0, w, h, DXGI_FORMAT_UNKNOWN, 0);
	set_target_from_swapchain(ctx);
}

void Canvas::bindWindow(void* hwnd) {
	ensureFactories();
	if (!g_d2dFactory || !g_d2dDevice || !g_d3dDevice) return;

	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) {
		ctx = new CanvasCtx();
		data = ctx;
	}
	ctx->factory1 = g_d2dFactory;
	ctx->factory = g_d2dFactory;
	ctx->dwriteFactory = g_dwriteFactory;
	ctx->hwnd = (HWND)hwnd;

	if (!ctx->rt && ctx->hwnd) {
		RECT rc{};
		GetClientRect(ctx->hwnd, &rc);
		UINT w = rc.right > rc.left ? (rc.right - rc.left) : 1;
		UINT h = rc.bottom > rc.top ? (rc.bottom - rc.top) : 1;

		// 创建交换链
		IDXGIDevice* dxgiDevice = nullptr;
		IDXGIAdapter* adapter = nullptr;
		IDXGIFactory2* dxgiFactory2 = nullptr;
		if (SUCCEEDED(g_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice)) && dxgiDevice) {
			dxgiDevice->GetAdapter(&adapter);
		}
		if (adapter) {
			adapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory2);
		}
		if (dxgiFactory2) {
			DXGI_SWAP_CHAIN_DESC1 scd = {};
			scd.Width = w;
			scd.Height = h;
			scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			scd.SampleDesc.Count = 1;
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.BufferCount = 2;
			scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			scd.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
			dxgiFactory2->CreateSwapChainForHwnd(g_d3dDevice, ctx->hwnd, &scd, nullptr, nullptr, &ctx->swapChain);
			dxgiFactory2->Release();
		}
		if (adapter) adapter->Release();
		if (dxgiDevice) dxgiDevice->Release();

		// 创建设备上下文
		g_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &ctx->rt);

		if (ctx->swapChain && ctx->rt) {
				set_target_from_swapchain(ctx);
				ctx->rt->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 1), &ctx->fillSolid);
				ctx->rt->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 1), &ctx->strokeSolid);
				ctx->fillBrush = ctx->fillSolid;
				ctx->strokeBrush = ctx->strokeSolid;

				// 阴影离屏资源（D2D 1.1 shadow effect）
				g_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &ctx->shadowDC);
				if (ctx->shadowDC) {
					ctx->shadowDC->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1, 1), &ctx->shadowWhiteBrush);
				}
				ctx->rt->CreateEffect(CLSID_D2D1Shadow, &ctx->shadowEffect);
			}
	}
}

void Canvas::unbindWindow() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	// 释放渲染目标及其子资源（绘制全部在主线程，这里直接释放）
	if (ctx->sink) { ctx->sink->Release(); ctx->sink = nullptr; }
	if (ctx->pathGeo) { ctx->pathGeo->Release(); ctx->pathGeo = nullptr; }
	if (ctx->strokeStyle) { ctx->strokeStyle->Release(); ctx->strokeStyle = nullptr; }
	if (ctx->textFormat) { ctx->textFormat->Release(); ctx->textFormat = nullptr; }
	if (ctx->fillSolid) { ctx->fillSolid->Release(); ctx->fillSolid = nullptr; }
	if (ctx->strokeSolid) { ctx->strokeSolid->Release(); ctx->strokeSolid = nullptr; }
	if (ctx->shadowWhiteBrush) { ctx->shadowWhiteBrush->Release(); ctx->shadowWhiteBrush = nullptr; }
	if (ctx->shadowEffect) { ctx->shadowEffect->Release(); ctx->shadowEffect = nullptr; }
	if (ctx->shadowBmp) { ctx->shadowBmp->Release(); ctx->shadowBmp = nullptr; }
	if (ctx->shadowDC) { ctx->shadowDC->Release(); ctx->shadowDC = nullptr; }
	if (ctx->rt) { ctx->rt->SetTarget(nullptr); ctx->rt->Release(); ctx->rt = nullptr; }
	if (ctx->targetBitmap) { ctx->targetBitmap->Release(); ctx->targetBitmap = nullptr; }
	if (ctx->swapChain) { ctx->swapChain->Release(); ctx->swapChain = nullptr; }
	ctx->fillBrush = nullptr;
	ctx->strokeBrush = nullptr;
	ctx->hwnd = nullptr;
}

// 应用用户变换到渲染目标：设备变换 = baseScale * xform
static void apply_xform(CanvasCtx* ctx) {
	if (!ctx || !ctx->rt) return;
	ctx->rt->SetTransform(ctx->baseScale * ctx->xform);
}

// 设置填充/描边画刷（管理临时画刷的释放）
static void set_fill_brush(CanvasCtx* ctx, ID2D1Brush* b) {
	if (ctx->fillBrush && ctx->fillBrush != ctx->fillSolid) {
		ctx->fillBrush->Release();
	}
	ctx->fillBrush = b;
}

static void set_stroke_brush(CanvasCtx* ctx, ID2D1Brush* b) {
	if (ctx->strokeBrush && ctx->strokeBrush != ctx->strokeSolid) {
		ctx->strokeBrush->Release();
	}
	ctx->strokeBrush = b;
}

static void apply_fill_color(CanvasCtx* ctx) {
	if (!ctx->fillSolid) return;
	ctx->fillSolid->SetColor(color_from_int(ctx->fillColor, ctx->globalAlpha));
	set_fill_brush(ctx, ctx->fillSolid);
}

static void apply_stroke_color(CanvasCtx* ctx) {
	if (!ctx->strokeSolid) return;
	ctx->strokeSolid->SetColor(color_from_int(ctx->strokeColor, ctx->globalAlpha));
	set_stroke_brush(ctx, ctx->strokeSolid);
}

static void ensure_stroke_style(CanvasCtx* ctx) {
	if (!ctx->rt || ctx->strokeStyle) return;
	D2D1_STROKE_STYLE_PROPERTIES sp = D2D1::StrokeStyleProperties(
		ctx->cap, ctx->cap, ctx->cap, ctx->join, 10.0f, D2D1_DASH_STYLE_SOLID, 0.0f);
	ctx->factory->CreateStrokeStyle(sp, nullptr, 0, &ctx->strokeStyle);
}

// 阴影是否激活
static bool shadow_active(CanvasCtx* ctx) {
	return ctx->shadowColor != 0 && ((ctx->shadowColor >> 24) & 0xFF) != 0;
}

// 确保阴影离屏资源存在（在 bindWindow 中已创建，这里兜底）
static void ensure_shadow_resources(CanvasCtx* ctx) {
	if (!ctx->rt) return;
	if (!ctx->shadowDC && g_d2dDevice) {
		g_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &ctx->shadowDC);
	}
	if (!ctx->shadowWhiteBrush && ctx->shadowDC) {
		ctx->shadowDC->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &ctx->shadowWhiteBrush);
	}
	if (!ctx->shadowEffect) {
		ctx->rt->CreateEffect(CLSID_D2D1Shadow, &ctx->shadowEffect);
	}
}

// 为阴影准备离屏位图（含模糊外扩边距），返回设备空间源矩形
static bool prepare_shadow_bitmap(CanvasCtx* ctx, const D2D1_RECT_F& bounds, D2D1_RECT_F* outSrc) {
	if (!(bounds.right > bounds.left && bounds.bottom > bounds.top)) return false;
	float blur = ctx->shadowBlur;
	float margin = (blur < 0.1f) ? 2.0f : (blur * 2.0f + 4.0f);
	D2D1_RECT_F src = D2D1::RectF(bounds.left - margin, bounds.top - margin, bounds.right + margin, bounds.bottom + margin);
	float bw = src.right - src.left;
	float bh = src.bottom - src.top;
	if (bw < 1.0f || bh < 1.0f || bw > 1e7f || bh > 1e7f) return false;
	UINT32 iw = (UINT32)(bw + 0.5f);
	UINT32 ih = (UINT32)(bh + 0.5f);

	bool need = !ctx->shadowBmp;
	if (!need) {
		D2D1_SIZE_U sz = ctx->shadowBmp->GetPixelSize();
		if (sz.width != iw || sz.height != ih) need = true;
	}
	if (need) {
		if (ctx->shadowBmp) { ctx->shadowBmp->Release(); ctx->shadowBmp = nullptr; }
		D2D1_BITMAP_PROPERTIES1 bp = D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
		HRESULT hr = ctx->shadowDC->CreateBitmap(D2D1::SizeU(iw, ih), nullptr, 0, &bp, &ctx->shadowBmp);
		printf("[shadow] CreateBitmap %ux%u hr=0x%08X\n", iw, ih, (unsigned)hr);
		if (SUCCEEDED(hr)) {
			ctx->shadowBmpW = bw; ctx->shadowBmpH = bh;
		}
	}
	if (!ctx->shadowBmp) return false;
	*outSrc = src;
	return true;
}

// 用 shadow effect 把离屏白色剪影上色并投影到主目标
static void flush_shadow(CanvasCtx* ctx, const D2D1_RECT_F& src) {
	ctx->shadowEffect->SetInput(0, ctx->shadowBmp);
	float sa = ((ctx->shadowColor >> 24) & 0xFF) / 255.0f * ctx->globalAlpha;
	D2D1_VECTOR_4F c;
	c.x = ((ctx->shadowColor >> 16) & 0xFF) / 255.0f;
	c.y = ((ctx->shadowColor >> 8) & 0xFF) / 255.0f;
	c.z = ((ctx->shadowColor >> 0) & 0xFF) / 255.0f;
	c.w = sa < 0.0f ? 0.0f : (sa > 1.0f ? 1.0f : sa);
	ctx->shadowEffect->SetValue(D2D1_SHADOW_PROP_COLOR, c);
	ctx->shadowEffect->SetValue(D2D1_SHADOW_PROP_BLUR_STANDARD_DEVIATION, ctx->shadowBlur * 0.5f);

	// 阴影内容已是设备/像素坐标，须用恒等变换绘制，避免和 rt 当前变换叠加
	D2D1::Matrix3x2F saved;
	ctx->rt->GetTransform(&saved);
	ctx->rt->SetTransform(D2D1::Matrix3x2F::Identity());
	ctx->rt->DrawImage(ctx->shadowEffect,
		D2D1::Point2F(src.left + ctx->shadowOffsetX, src.top + ctx->shadowOffsetY),
		D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE_SOURCE_OVER);
	ctx->rt->SetTransform(saved);
}

// 绘制阴影 fill：用 shadow effect 生成模糊阴影
static void draw_shadow_fill(CanvasCtx* ctx) {
	if (!shadow_active(ctx) || !ctx->pathGeo || !ctx->rt) return;
	ensure_shadow_resources(ctx);
	if (!ctx->shadowDC || !ctx->shadowEffect || !ctx->shadowWhiteBrush) {
		printf("[shadow-fill] missing res dc=%p eff=%p brush=%p\n", (void*)ctx->shadowDC, (void*)ctx->shadowEffect, (void*)ctx->shadowWhiteBrush);
		return;
	}

	D2D1::Matrix3x2F cur;
	ctx->rt->GetTransform(&cur);
	D2D1_RECT_F bounds;
	if (FAILED(ctx->pathGeo->GetBounds(&cur, &bounds))) return;

	D2D1_RECT_F src;
	if (!prepare_shadow_bitmap(ctx, bounds, &src)) return;

	{
		static int dbg = 0;
		if (dbg++ < 5) printf("[shadow-fill] bounds(%.1f,%.1f,%.1f,%.1f) src(%.1f,%.1f) off(%.1f,%.1f) blur=%.1f color=0x%08X\n",
			bounds.left, bounds.top, bounds.right, bounds.bottom,
			src.left, src.top, ctx->shadowOffsetX, ctx->shadowOffsetY, (double)ctx->shadowBlur, ctx->shadowColor);
	}

	ctx->shadowDC->SetTarget(ctx->shadowBmp);
	ctx->shadowDC->BeginDraw();
	ctx->shadowDC->Clear(D2D1::ColorF(0, 0, 0, 0));
	ctx->shadowDC->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	ctx->shadowDC->SetTransform(D2D1::Matrix3x2F::Translation(-src.left, -src.top) * cur);
	ctx->shadowDC->FillGeometry(ctx->pathGeo, ctx->shadowWhiteBrush);
	ctx->shadowDC->EndDraw();
	ctx->shadowDC->Flush();

	flush_shadow(ctx, src);
}

// 绘制阴影 stroke
static void draw_shadow_stroke(CanvasCtx* ctx) {
	if (!shadow_active(ctx) || !ctx->pathGeo || !ctx->rt) return;
	ensure_shadow_resources(ctx);
	if (!ctx->shadowDC || !ctx->shadowEffect || !ctx->shadowWhiteBrush) return;
	ensure_stroke_style(ctx);

	D2D1::Matrix3x2F cur;
	ctx->rt->GetTransform(&cur);
	D2D1_RECT_F bounds;
	if (FAILED(ctx->pathGeo->GetBounds(&cur, &bounds))) return;

	D2D1_RECT_F src;
	if (!prepare_shadow_bitmap(ctx, bounds, &src)) return;

	ctx->shadowDC->SetTarget(ctx->shadowBmp);
	ctx->shadowDC->BeginDraw();
	ctx->shadowDC->Clear(D2D1::ColorF(0, 0, 0, 0));
	ctx->shadowDC->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	ctx->shadowDC->SetTransform(D2D1::Matrix3x2F::Translation(-src.left, -src.top) * cur);
	ctx->shadowDC->DrawGeometry(ctx->pathGeo, ctx->shadowWhiteBrush, ctx->strokeW, ctx->strokeStyle);
	ctx->shadowDC->EndDraw();
	ctx->shadowDC->Flush();

	flush_shadow(ctx, src);
}

// 绘制文本阴影
static void draw_shadow_text(CanvasCtx* ctx, IDWriteTextLayout* layout, float originX, float originY) {
	if (!shadow_active(ctx) || !layout) return;
	ensure_shadow_resources(ctx);
	if (!ctx->shadowDC || !ctx->shadowEffect || !ctx->shadowWhiteBrush) return;

	DWRITE_TEXT_METRICS m;
	layout->GetMetrics(&m);
	if (!(m.width > 0 || m.height > 0)) return;

	D2D1::Matrix3x2F cur;
	ctx->rt->GetTransform(&cur);
	D2D1_RECT_F bounds = D2D1::RectF(originX, originY, originX + m.width, originY + m.height);

	D2D1_RECT_F src;
	if (!prepare_shadow_bitmap(ctx, bounds, &src)) return;

	ctx->shadowDC->SetTarget(ctx->shadowBmp);
	ctx->shadowDC->BeginDraw();
	ctx->shadowDC->Clear(D2D1::ColorF(0, 0, 0, 0));
	ctx->shadowDC->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	ctx->shadowDC->SetTransform(D2D1::Matrix3x2F::Translation(-src.left, -src.top) * cur);
	ctx->shadowDC->DrawTextLayout(D2D1::Point2F(originX, originY), layout, ctx->shadowWhiteBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	ctx->shadowDC->EndDraw();
	ctx->shadowDC->Flush();

	flush_shadow(ctx, src);
}

static void finalize_path(CanvasCtx* ctx) {
	if (!ctx->sink) return;
	if (ctx->figureOpen) {
		ctx->sink->EndFigure(ctx->figureClosed ? D2D1_FIGURE_END_CLOSED : D2D1_FIGURE_END_OPEN);
		ctx->figureOpen = false;
	}
	ctx->sink->Close();
	ctx->sink->Release();
	ctx->sink = nullptr;
}

// 计算裁剪在设备空间的AABB，并以恒等变换压入裁剪
static void push_clip(CanvasCtx* ctx) {
	if (!ctx || !ctx->rt || !ctx->hasScissor) return;
	D2D1::Matrix3x2F m = ctx->baseScale * ctx->scissorXform;
	D2D1_POINT_2F corners[4] = {
		m.TransformPoint(D2D1::Point2F(ctx->scissorRect.left, ctx->scissorRect.top)),
		m.TransformPoint(D2D1::Point2F(ctx->scissorRect.right, ctx->scissorRect.top)),
		m.TransformPoint(D2D1::Point2F(ctx->scissorRect.right, ctx->scissorRect.bottom)),
		m.TransformPoint(D2D1::Point2F(ctx->scissorRect.left, ctx->scissorRect.bottom)),
	};
	float minX = corners[0].x, minY = corners[0].y, maxX = corners[0].x, maxY = corners[0].y;
	for (int i = 1; i < 4; i++) {
		if (corners[i].x < minX) minX = corners[i].x;
		if (corners[i].x > maxX) maxX = corners[i].x;
		if (corners[i].y < minY) minY = corners[i].y;
		if (corners[i].y > maxY) maxY = corners[i].y;
	}
	D2D1_MATRIX_3X2_F cur = ctx->baseScale * ctx->xform;
	ctx->rt->SetTransform(D2D1::Matrix3x2F::Identity());
	ctx->rt->PushAxisAlignedClip(D2D1::RectF(minX, minY, maxX, maxY), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	ctx->rt->SetTransform(cur);
}

static void pop_clip(CanvasCtx* ctx) {
	if (!ctx || !ctx->rt || !ctx->hasScissor) return;
	ctx->rt->PopAxisAlignedClip();
}

void Canvas::beginFrame(float w, float h, float devicePixelRatio) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;

	if (devicePixelRatio <= 0) devicePixelRatio = 1.0f;
	UINT32 pw = (UINT32)(w * devicePixelRatio + 0.5f);
	UINT32 ph = (UINT32)(h * devicePixelRatio + 0.5f);
	if (ctx->frameW != w || ctx->frameH != h) {
		resize_swapchain(ctx, pw, ph);
	}

	ctx->frameW = w;
	ctx->frameH = h;
	ctx->dpr = devicePixelRatio;
	ctx->baseScale = D2D1::Matrix3x2F::Scale(devicePixelRatio, devicePixelRatio);

	ctx->rt->BeginDraw();
	ctx->rt->Clear(D2D1::ColorF(0, 0, 0, 0));
	ctx->rt->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	// 释放上一帧残留的路径
	if (ctx->sink) { ctx->sink->Release(); ctx->sink = nullptr; }
	if (ctx->pathGeo) { ctx->pathGeo->Release(); ctx->pathGeo = nullptr; }
	ctx->figureOpen = false;
	ctx->figureClosed = false;

	// 重置每帧状态
	ctx->stack.clear();
	ctx->xform = D2D1::Matrix3x2F::Identity();
	ctx->globalAlpha = 1.0f;
	ctx->strokeW = 1.0f;
	ctx->cap = D2D1_CAP_STYLE_FLAT;
	ctx->join = D2D1_LINE_JOIN_MITER;
	ctx->hasScissor = false;
	ctx->shadowColor = 0;
	ctx->shadowOffsetX = 0;
	ctx->shadowOffsetY = 0;
	ctx->shadowBlur = 0;
	apply_xform(ctx);
}

void Canvas::endFrame() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;
	finalize_path(ctx);
	ctx->rt->EndDraw();
	if (ctx->swapChain) ctx->swapChain->Present(1, 0);
}

void Canvas::cancelFrame() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;
	finalize_path(ctx);
	ctx->rt->EndDraw();
}

void Canvas::globalAlpha(float alpha) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->globalAlpha = alpha;
	apply_fill_color(ctx);
	apply_stroke_color(ctx);
}

void Canvas::stroke() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt || !ctx->pathGeo || !ctx->strokeBrush) return;
	finalize_path(ctx);
	ensure_stroke_style(ctx);
	push_clip(ctx);
	draw_shadow_stroke(ctx);
	ctx->rt->DrawGeometry(ctx->pathGeo, ctx->strokeBrush, ctx->strokeW, ctx->strokeStyle);
	pop_clip(ctx);
}

void Canvas::fill() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt || !ctx->pathGeo || !ctx->fillBrush) return;
	finalize_path(ctx);
	push_clip(ctx);
	draw_shadow_fill(ctx);
	ctx->rt->FillGeometry(ctx->pathGeo, ctx->fillBrush);
	pop_clip(ctx);
}

void Canvas::strokeColorByInt32(int c) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->strokeColor = c;
	apply_stroke_color(ctx);
}

void Canvas::fillColorByInt32(int c) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->fillColor = c;
	apply_fill_color(ctx);
}

void Canvas::fillColor(int r, int g, int b, int a) {
	fillColorByInt32((a << 24) | (r << 16) | (g << 8) | (b << 0));
}

void Canvas::strokeColor(int r, int g, int b, int a) {
	strokeColorByInt32((a << 24) | (r << 16) | (g << 8) | (b << 0));
}

void Canvas::strokeWidth(float width) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->strokeW = width;
}

void Canvas::shadowColor(int r, int g, int b, int a) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->shadowColor = (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

void Canvas::shadowOffset(float x, float y) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->shadowOffsetX = x;
	ctx->shadowOffsetY = y;
}

void Canvas::shadowBlur(float blur) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->shadowBlur = blur;
}

void Canvas::shapeAntiAlias(int enabled) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;
	ctx->rt->SetAntialiasMode(enabled ? D2D1_ANTIALIAS_MODE_PER_PRIMITIVE : D2D1_ANTIALIAS_MODE_ALIASED);
}

void Canvas::lineJoin(int join) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->join = (join == CANVAS_JOIN_ROUND) ? D2D1_LINE_JOIN_ROUND : (join == CANVAS_JOIN_BEVEL ? D2D1_LINE_JOIN_BEVEL : D2D1_LINE_JOIN_MITER);
	if (ctx->strokeStyle) { ctx->strokeStyle->Release(); ctx->strokeStyle = nullptr; }
}

void Canvas::lineCap(int cap) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	D2D1_CAP_STYLE c = (cap == CANVAS_CAP_ROUND) ? D2D1_CAP_STYLE_ROUND : (cap == CANVAS_CAP_SQUARE ? D2D1_CAP_STYLE_SQUARE : D2D1_CAP_STYLE_FLAT);
	ctx->cap = c;
	if (ctx->strokeStyle) { ctx->strokeStyle->Release(); ctx->strokeStyle = nullptr; }
}

void Canvas::translate(float x, float y) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->xform = D2D1::Matrix3x2F::Translation(x, y) * ctx->xform;
	apply_xform(ctx);
}

void Canvas::scale(float x, float y) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->xform = D2D1::Matrix3x2F::Scale(x, y) * ctx->xform;
	apply_xform(ctx);
}

void Canvas::rotate(float rad) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->xform = D2D1::Matrix3x2F::Rotation(rad) * ctx->xform;
	apply_xform(ctx);
}

void Canvas::skewX(float rad) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->xform = D2D1::Matrix3x2F::Skew(rad, 0) * ctx->xform;
	apply_xform(ctx);
}

void Canvas::skewY(float rad) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->xform = D2D1::Matrix3x2F::Skew(0, rad) * ctx->xform;
	apply_xform(ctx);
}

void Canvas::transform(const Mat2d& mat) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->xform = mat2d_to_d2d(mat.data) * ctx->xform;
	apply_xform(ctx);
}

void Canvas::setTransform(const Mat2d& mat) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->xform = mat2d_to_d2d(mat.data);
	apply_xform(ctx);
}

void Canvas::resetTransform() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->xform = D2D1::Matrix3x2F::Identity();
	apply_xform(ctx);
}

void Canvas::currentTransform(Mat2d* mat) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!mat) return;
	if (!ctx) { mat->identity(); return; }
	d2d_to_mat2d(ctx->xform, mat);
}

void Canvas::save() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	CanvasState s;
	s.xform = ctx->xform;
	s.globalAlpha = ctx->globalAlpha;
	s.strokeW = ctx->strokeW;
	s.cap = ctx->cap;
	s.join = ctx->join;
	s.fillColor = ctx->fillColor;
	s.strokeColor = ctx->strokeColor;
	s.hasScissor = ctx->hasScissor;
	s.scissorRect = ctx->scissorRect;
	s.scissorXform = ctx->scissorXform;
	s.fontFace = ctx->fontFace;
	s.fontSize = ctx->fontSize;
	s.textAlignFlags = ctx->textAlignFlags;
	s.letterSpacing = ctx->letterSpacing;
	s.lineHeight = ctx->lineHeight;
	s.fontBlur = ctx->fontBlur;
	s.shadowColor = ctx->shadowColor;
	s.shadowOffsetX = ctx->shadowOffsetX;
	s.shadowOffsetY = ctx->shadowOffsetY;
	s.shadowBlur = ctx->shadowBlur;
	ctx->stack.push_back(s);
}

void Canvas::restore() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	if (ctx->stack.empty()) return;
	CanvasState s = ctx->stack.back();
	ctx->stack.pop_back();

	ctx->xform = s.xform;
	ctx->globalAlpha = s.globalAlpha;
	ctx->strokeW = s.strokeW;
	ctx->cap = s.cap;
	ctx->join = s.join;
	if (ctx->strokeStyle) { ctx->strokeStyle->Release(); ctx->strokeStyle = nullptr; }
	ctx->fillColor = s.fillColor;
	ctx->strokeColor = s.strokeColor;
	ctx->hasScissor = s.hasScissor;
	ctx->scissorRect = s.scissorRect;
	ctx->scissorXform = s.scissorXform;
	ctx->fontFace = s.fontFace;
	ctx->fontSize = s.fontSize;
	ctx->textAlignFlags = s.textAlignFlags;
	ctx->letterSpacing = s.letterSpacing;
	ctx->lineHeight = s.lineHeight;
	ctx->fontBlur = s.fontBlur;
	ctx->shadowColor = s.shadowColor;
	ctx->shadowOffsetX = s.shadowOffsetX;
	ctx->shadowOffsetY = s.shadowOffsetY;
	ctx->shadowBlur = s.shadowBlur;

	apply_xform(ctx);
	apply_fill_color(ctx);
	apply_stroke_color(ctx);
}

void Canvas::reset() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->xform = D2D1::Matrix3x2F::Identity();
	ctx->globalAlpha = 1.0f;
	ctx->strokeW = 1.0f;
	ctx->cap = D2D1_CAP_STYLE_FLAT;
	ctx->join = D2D1_LINE_JOIN_MITER;
	ctx->fillColor = 0xFF000000;
	ctx->strokeColor = 0xFF000000;
	ctx->hasScissor = false;
	ctx->fontFace = "sans";
	ctx->fontSize = 16.0f;
	ctx->textAlignFlags = CANVAS_ALIGN_LEFT | CANVAS_ALIGN_BASELINE;
	ctx->letterSpacing = 0.0f;
	ctx->lineHeight = 1.0f;
	ctx->fontBlur = 0.0f;
	ctx->shadowColor = 0;
	ctx->shadowOffsetX = 0;
	ctx->shadowOffsetY = 0;
	ctx->shadowBlur = 0;
	ctx->stack.clear();
	if (ctx->strokeStyle) { ctx->strokeStyle->Release(); ctx->strokeStyle = nullptr; }
	apply_xform(ctx);
	apply_fill_color(ctx);
	apply_stroke_color(ctx);
}

void Canvas::scissor(float x, float y, float w, float h) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->hasScissor = true;
	ctx->scissorRect = D2D1::RectF(x, y, x + w, y + h);
	ctx->scissorXform = ctx->xform;
}

void Canvas::intersectScissor(float x, float y, float w, float h) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	if (!ctx->hasScissor) {
		scissor(x, y, w, h);
		return;
	}
	// 把已有裁剪从 scissorXform 空间变换到当前用户空间，再求交集
	D2D1::Matrix3x2F m = mat_inverse(ctx->xform) * ctx->scissorXform;
	D2D1_POINT_2F corners[4] = {
		m.TransformPoint(D2D1::Point2F(ctx->scissorRect.left, ctx->scissorRect.top)),
		m.TransformPoint(D2D1::Point2F(ctx->scissorRect.right, ctx->scissorRect.top)),
		m.TransformPoint(D2D1::Point2F(ctx->scissorRect.right, ctx->scissorRect.bottom)),
		m.TransformPoint(D2D1::Point2F(ctx->scissorRect.left, ctx->scissorRect.bottom)),
	};
	float minX = corners[0].x, minY = corners[0].y, maxX = corners[0].x, maxY = corners[0].y;
	for (int i = 1; i < 4; i++) {
		if (corners[i].x < minX) minX = corners[i].x;
		if (corners[i].x > maxX) maxX = corners[i].x;
		if (corners[i].y < minY) minY = corners[i].y;
		if (corners[i].y > maxY) maxY = corners[i].y;
	}
	float nx = x, ny = y, nw = w, nh = h;
	float ix1 = (minX > nx) ? minX : nx;
	float iy1 = (minY > ny) ? minY : ny;
	float ix2 = (maxX < nx + nw) ? maxX : nx + nw;
	float iy2 = (maxY < ny + nh) ? maxY : ny + nh;
	ctx->scissorRect = D2D1::RectF(ix1, iy1, ix2, iy2);
	ctx->scissorXform = ctx->xform;
}

void Canvas::resetScissor() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->hasScissor = false;
}

void Canvas::beginPath() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;
	if (ctx->sink) { ctx->sink->Release(); ctx->sink = nullptr; }
	if (ctx->pathGeo) { ctx->pathGeo->Release(); ctx->pathGeo = nullptr; }
	ctx->figureOpen = false;
	ctx->figureClosed = false;
	if (SUCCEEDED(ctx->factory->CreatePathGeometry(&ctx->pathGeo)) && ctx->pathGeo) {
		ctx->pathGeo->Open(&ctx->sink);
	}
}

void Canvas::closePath() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->figureClosed = true;
}

void Canvas::moveTo(float x, float y) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->sink) return;
	if (ctx->figureOpen) {
		ctx->sink->EndFigure(ctx->figureClosed ? D2D1_FIGURE_END_CLOSED : D2D1_FIGURE_END_OPEN);
		ctx->figureClosed = false;
	}
	ctx->sink->BeginFigure(D2D1::Point2F(x, y), D2D1_FIGURE_BEGIN_FILLED);
	ctx->figureOpen = true;
	ctx->lastX = x; ctx->lastY = y;
}

void Canvas::lineTo(float x, float y) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->sink || !ctx->figureOpen) return;
	ctx->sink->AddLine(D2D1::Point2F(x, y));
	ctx->lastX = x; ctx->lastY = y;
}

void Canvas::bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->sink || !ctx->figureOpen) return;
	D2D1_BEZIER_SEGMENT seg;
	seg.point1 = D2D1::Point2F(c1x, c1y);
	seg.point2 = D2D1::Point2F(c2x, c2y);
	seg.point3 = D2D1::Point2F(x, y);
	ctx->sink->AddBezier(seg);
	ctx->lastX = x; ctx->lastY = y;
}

void Canvas::quadTo(float cx, float cy, float x, float y) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->sink || !ctx->figureOpen) return;
	D2D1_QUADRATIC_BEZIER_SEGMENT seg;
	seg.point1 = D2D1::Point2F(cx, cy);
	seg.point2 = D2D1::Point2F(x, y);
	ctx->sink->AddQuadraticBezier(seg);
	ctx->lastX = x; ctx->lastY = y;
}

void Canvas::arcTo(float x1, float y1, float x2, float y2, float radius) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->sink || !ctx->figureOpen) return;
	float x0 = ctx->lastX, y0 = ctx->lastY;
	float dx0 = x0 - x1, dy0 = y0 - y1;
	float dx1 = x2 - x1, dy1 = y2 - y1;
	float d0 = sqrtf(dx0 * dx0 + dy0 * dy0);
	float d1 = sqrtf(dx1 * dx1 + dy1 * dy1);
	if (d0 < 1e-6f || d1 < 1e-6f) {
		ctx->sink->AddLine(D2D1::Point2F(x1, y1));
		ctx->lastX = x1; ctx->lastY = y1;
		return;
	}
	float u0x = dx0 / d0, u0y = dy0 / d0;
	float u1x = dx1 / d1, u1y = dy1 / d1;
	float a = u0x * u1x + u0y * u1y;
	float tang = sqrtf((1 - a) / (1 + a));
	float ang = acosf(a);
	float r = radius < 0 ? -radius : radius;
	float dist = tang * r;
	D2D1_POINT_2F p0 = D2D1::Point2F(x1 + u0x * dist, y1 + u0y * dist);
	D2D1_POINT_2F p1 = D2D1::Point2F(x1 + u1x * dist, y1 + u1y * dist);
	ctx->sink->AddLine(p0);

	D2D1_ARC_SEGMENT arc;
	arc.point = p1;
	arc.size = D2D1::SizeF(r, r);
	arc.rotationAngle = 0;
	arc.sweepDirection = (u0x * u1y - u0y * u1x) < 0 ? D2D1_SWEEP_DIRECTION_CLOCKWISE : D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;
	arc.arcSize = D2D1_ARC_SIZE_SMALL;
	ctx->sink->AddArc(arc);

	ctx->lastX = x2; ctx->lastY = y2;
}

void Canvas::pathWinding(int dir) {
	// nanvg用CCW/CW区分实心/挖洞，Direct2D用填充模式近似，这里默认非零填充即可
	(void)dir;
}

void Canvas::arc(float cx, float cy, float r, float a0, float a1, int dir) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->sink) return;
	float sx = cx + r * cosf(a0);
	float sy = cy + r * sinf(a0);
	float ex = cx + r * cosf(a1);
	float ey = cy + r * sinf(a1);
	if (!ctx->figureOpen) {
		ctx->sink->BeginFigure(D2D1::Point2F(sx, sy), D2D1_FIGURE_BEGIN_FILLED);
		ctx->figureOpen = true;
	} else {
		ctx->sink->AddLine(D2D1::Point2F(sx, sy));
	}
	D2D1_ARC_SEGMENT arc;
	arc.point = D2D1::Point2F(ex, ey);
	arc.size = D2D1::SizeF(r, r);
	arc.rotationAngle = 0;
	arc.sweepDirection = (dir == CANVAS_CW) ? D2D1_SWEEP_DIRECTION_CLOCKWISE : D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;
	arc.arcSize = D2D1_ARC_SIZE_SMALL;
	ctx->sink->AddArc(arc);
	ctx->lastX = ex; ctx->lastY = ey;
}

void Canvas::rect(float x, float y, float w, float h) {
	moveTo(x, y);
	lineTo(x + w, y);
	lineTo(x + w, y + h);
	lineTo(x, y + h);
	closePath();
}

void Canvas::roundRect(float x, float y, float w, float h, float r) {
	roundRectVarying(x, y, w, h, r, r, r, r);
}

void Canvas::roundRectVarying(float x, float y, float w, float h, float rtl, float rtr, float rbr, float rbl) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->sink) return;
	float halfw = w * 0.5f;
	if (rtl > halfw) rtl = halfw;
	if (rtr > halfw) rtr = halfw;
	if (rbr > halfw) rbr = halfw;
	if (rbl > halfw) rbl = halfw;
	float halfh = h * 0.5f;
	if (rtl > halfh) rtl = halfh;
	if (rtr > halfh) rtr = halfh;
	if (rbr > halfh) rbr = halfh;
	if (rbl > halfh) rbl = halfh;
	if (rtl < 0) rtl = 0;
	if (rtr < 0) rtr = 0;
	if (rbr < 0) rbr = 0;
	if (rbl < 0) rbl = 0;

	ctx->sink->BeginFigure(D2D1::Point2F(x + rtl, y), D2D1_FIGURE_BEGIN_FILLED);
	ctx->figureOpen = true;

	if (rtr > 0) {
		ctx->sink->AddLine(D2D1::Point2F(x + w - rtr, y));
		D2D1_ARC_SEGMENT a;
		a.point = D2D1::Point2F(x + w, y + rtr);
		a.size = D2D1::SizeF(rtr, rtr);
		a.rotationAngle = 0;
		a.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
		a.arcSize = D2D1_ARC_SIZE_SMALL;
		ctx->sink->AddArc(a);
	} else {
		ctx->sink->AddLine(D2D1::Point2F(x + w, y));
	}

	if (rbr > 0) {
		ctx->sink->AddLine(D2D1::Point2F(x + w, y + h - rbr));
		D2D1_ARC_SEGMENT a;
		a.point = D2D1::Point2F(x + w - rbr, y + h);
		a.size = D2D1::SizeF(rbr, rbr);
		a.rotationAngle = 0;
		a.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
		a.arcSize = D2D1_ARC_SIZE_SMALL;
		ctx->sink->AddArc(a);
	} else {
		ctx->sink->AddLine(D2D1::Point2F(x + w, y + h));
	}

	if (rbl > 0) {
		ctx->sink->AddLine(D2D1::Point2F(x + rbl, y + h));
		D2D1_ARC_SEGMENT a;
		a.point = D2D1::Point2F(x, y + h - rbl);
		a.size = D2D1::SizeF(rbl, rbl);
		a.rotationAngle = 0;
		a.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
		a.arcSize = D2D1_ARC_SIZE_SMALL;
		ctx->sink->AddArc(a);
	} else {
		ctx->sink->AddLine(D2D1::Point2F(x, y + h));
	}

	if (rtl > 0) {
		ctx->sink->AddLine(D2D1::Point2F(x, y + rtl));
		D2D1_ARC_SEGMENT a;
		a.point = D2D1::Point2F(x + rtl, y);
		a.size = D2D1::SizeF(rtl, rtl);
		a.rotationAngle = 0;
		a.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
		a.arcSize = D2D1_ARC_SIZE_SMALL;
		ctx->sink->AddArc(a);
	} else {
		ctx->sink->AddLine(D2D1::Point2F(x, y));
	}

	ctx->figureClosed = true;
	ctx->sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	ctx->figureOpen = false;
	ctx->lastX = x; ctx->lastY = y;
}

void Canvas::ellipse(float cx, float cy, float rx, float ry) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->sink) return;
	ctx->sink->BeginFigure(D2D1::Point2F(cx - rx, cy), D2D1_FIGURE_BEGIN_FILLED);
	ctx->figureOpen = false;
	D2D1_ARC_SEGMENT a1;
	a1.point = D2D1::Point2F(cx + rx, cy);
	a1.size = D2D1::SizeF(rx, ry);
	a1.rotationAngle = 0;
	a1.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
	a1.arcSize = D2D1_ARC_SIZE_SMALL;
	ctx->sink->AddArc(a1);
	D2D1_ARC_SEGMENT a2;
	a2.point = D2D1::Point2F(cx - rx, cy);
	a2.size = D2D1::SizeF(rx, ry);
	a2.rotationAngle = 0;
	a2.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
	a2.arcSize = D2D1_ARC_SIZE_SMALL;
	ctx->sink->AddArc(a2);
	ctx->sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	ctx->figureOpen = false;
	ctx->lastX = cx - rx; ctx->lastY = cy;
}

void Canvas::circle(float cx, float cy, float r) {
	ellipse(cx, cy, r, r);
}

void Canvas::fontBlur(float blur) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->fontBlur = blur;
}

void Canvas::fontFace(const char* name) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->fontFace = name ? name : "sans";
}

void Canvas::fontSize(float size) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->fontSize = size;
}

void Canvas::textLetterSpacing(float spacing) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->letterSpacing = spacing;
}

void Canvas::texLineHeight(float lineHeight) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->lineHeight = lineHeight;
}

void Canvas::textAlign(int align) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx) return;
	ctx->textAlignFlags = align;
}

// 确保当前字体/字号对应的文本格式
static void ensure_text_format(CanvasCtx* ctx) {
	if (!ctx || !ctx->rt || !ctx->dwriteFactory) return;
	if (ctx->textFormat && ctx->textFormatFace == ctx->fontFace && ctx->textFormatSize == ctx->fontSize) {
		return;
	}
	if (ctx->textFormat) { ctx->textFormat->Release(); ctx->textFormat = nullptr; }
	ctx->dwriteFactory->CreateTextFormat(
		map_face(ctx->fontFace),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		ctx->fontSize,
		L"",
		&ctx->textFormat);
	if (ctx->textFormat) {
		ctx->textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		ctx->textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		ctx->textFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
		ctx->textFormatFace = ctx->fontFace;
		ctx->textFormatSize = ctx->fontSize;
	}
}

// 获取当前字体的 ascent / descent / lineGap（单位：DIP，descent为正数）
static void font_metrics(CanvasCtx* ctx, float* ascent, float* descent, float* lineGap) {
	*ascent = ctx->fontSize * 0.8f;
	*descent = ctx->fontSize * 0.2f;
	*lineGap = 0;
	if (!ctx || !ctx->dwriteFactory) return;

	// 字体名没变时直接用缓存的设计单位重新计算
	if (ctx->metricsCache.valid && ctx->metricsCache.face == ctx->fontFace) {
		float scale = ctx->fontSize / (float)ctx->metricsCache.designUnitsPerEm;
		*ascent = ctx->metricsCache.ascent * scale;
		*descent = ctx->metricsCache.descent * scale;
		*lineGap = ctx->metricsCache.lineGap * scale;
		return;
	}

	IDWriteFontCollection* coll = nullptr;
	ctx->dwriteFactory->GetSystemFontCollection(&coll, FALSE);
	if (!coll) return;

	UINT32 idx = 0;
	BOOL exists = FALSE;
	std::wstring fam = map_face(ctx->fontFace);
	coll->FindFamilyName(fam.c_str(), &idx, &exists);
	if (!exists) idx = 0;

	IDWriteFontFamily* family = nullptr;
	if (SUCCEEDED(coll->GetFontFamily(idx, &family)) && family) {
		IDWriteFont* font = nullptr;
		if (SUCCEEDED(family->GetFont(0, &font)) && font) {
			DWRITE_FONT_METRICS fm;
			font->GetMetrics(&fm);
			ctx->metricsCache.face = ctx->fontFace;
			ctx->metricsCache.designUnitsPerEm = fm.designUnitsPerEm;
			ctx->metricsCache.ascent = fm.ascent;
			ctx->metricsCache.descent = fm.descent;
			ctx->metricsCache.lineGap = fm.lineGap;
			ctx->metricsCache.valid = true;

			float scale = ctx->fontSize / (float)fm.designUnitsPerEm;
			*ascent = fm.ascent * scale;
			*descent = fm.descent * scale;
			*lineGap = fm.lineGap * scale;
			font->Release();
		}
		family->Release();
	}
	coll->Release();
}

// 创建单行文本布局（调用方负责Release）
static IDWriteTextLayout* make_text_layout(CanvasCtx* ctx, const std::wstring& text) {
	ensure_text_format(ctx);
	if (!ctx->textFormat) return nullptr;
	IDWriteTextLayout* layout = nullptr;
	ctx->dwriteFactory->CreateTextLayout(text.c_str(), (UINT32)text.size(), ctx->textFormat, 100000.0f, 100000.0f, &layout);
	return layout;
}

void Canvas::text(float x, float y, const char* string) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt || !ctx->fillBrush || !string) return;
	std::wstring wstr = utf8_to_wide(string);
	if (wstr.empty()) return;
	IDWriteTextLayout* layout = make_text_layout(ctx, wstr);
	if (!layout) return;

	DWRITE_TEXT_METRICS m;
	layout->GetMetrics(&m);
	float width = m.width;

	float ascent = 0, descent = 0, lineGap = 0;
	font_metrics(ctx, &ascent, &descent, &lineGap);

	float originX = x;
	if (ctx->textAlignFlags & CANVAS_ALIGN_CENTER) originX = x - width * 0.5f;
	else if (ctx->textAlignFlags & CANVAS_ALIGN_RIGHT) originX = x - width;

	float baselineY = y;
	if (ctx->textAlignFlags & CANVAS_ALIGN_TOP) baselineY = y + ascent;
	else if (ctx->textAlignFlags & CANVAS_ALIGN_MIDDLE) baselineY = y + (ascent - descent) * 0.5f;
	else if (ctx->textAlignFlags & CANVAS_ALIGN_BOTTOM) baselineY = y - descent;
	// 否则按BASELINE处理

	float originY = baselineY - ascent;

	// 阴影（用 D2D 1.1 shadow effect，GPU 高斯模糊）
	draw_shadow_text(ctx, layout, originX, originY);

	ctx->rt->DrawTextLayout(D2D1::Point2F(originX, originY), layout, ctx->fillBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
	layout->Release();
}

float Canvas::textBounds(float x, float y, const char* string, const char* end, float* bounds) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !string) {
		if (bounds) { bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0; }
		return 0;
	}
	std::wstring wstr = utf8_to_wide(string, end);
	if (wstr.empty()) {
		if (bounds) { bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0; }
		return 0;
	}
	IDWriteTextLayout* layout = make_text_layout(ctx, wstr);
	if (!layout) {
		if (bounds) { bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0; }
		return 0;
	}
	DWRITE_TEXT_METRICS m;
	layout->GetMetrics(&m);
	float width = m.width;

	float ascent = 0, descent = 0, lineGap = 0;
	font_metrics(ctx, &ascent, &descent, &lineGap);

	float x0 = x;
	if (ctx->textAlignFlags & CANVAS_ALIGN_CENTER) x0 = x - width * 0.5f;
	else if (ctx->textAlignFlags & CANVAS_ALIGN_RIGHT) x0 = x - width;

	float top, bottom;
	if (ctx->textAlignFlags & CANVAS_ALIGN_TOP) { top = y; bottom = y + ascent + descent; }
	else if (ctx->textAlignFlags & CANVAS_ALIGN_MIDDLE) { top = y - (ascent + descent) * 0.5f; bottom = y + (ascent + descent) * 0.5f; }
	else if (ctx->textAlignFlags & CANVAS_ALIGN_BOTTOM) { top = y - (ascent + descent); bottom = y; }
	else { top = y - ascent; bottom = y + descent; }

	if (bounds) {
		bounds[0] = x0;
		bounds[1] = top;
		bounds[2] = x0 + width;
		bounds[3] = bottom;
	}
	layout->Release();
	return width;
}

TextMetrics Canvas::textMetrics() {
	CanvasCtx* ctx = (CanvasCtx*)data;
	TextMetrics tm;
	tm.ascender = 0;
	tm.descender = 0;
	tm.lineh = 0;
	if (!ctx) return tm;
	float ascent = 0, descent = 0, lineGap = 0;
	font_metrics(ctx, &ascent, &descent, &lineGap);
	tm.ascender = ascent;
	tm.descender = descent;
	tm.lineh = ascent + descent;
	return tm;
}

void Canvas::drawImage(Image* img, float x, float y, float alpha) {
	if (!img || !img->bitmap) return;
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;
	ID2D1Bitmap* bmp = (ID2D1Bitmap*)img->bitmap;
	D2D1_SIZE_F s = bmp->GetSize();
	imagePattern(true, x, y, s.width, s.height, 0, img, alpha);
	beginPath();
	rect(x, y, s.width, s.height);
	fill();
}

void Canvas::drawImageAtRect(Image* img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, float alpha) {
	if (!img || !img->bitmap) return;
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;
	// 与ImageView的drawImage_atRect保持一致的语义：裁剪源区域并缩放到目标区域
	ID2D1Bitmap* bmp = (ID2D1Bitmap*)img->bitmap;
	D2D1_SIZE_F isize = bmp->GetSize();
	float iw = isize.width, ih = isize.height;
	float wscale = dw / sw;
	float hscale = dh / sh;
	float ox = -sx * wscale + dx;
	float oy = -sy * hscale + dy;
	float ew = iw * wscale;
	float eh = ih * hscale;
	imagePattern(true, ox, oy, ew, eh, 0, img, alpha);
	beginPath();
	rect(dx, dy, dw, dh);
	fill();
}

// 创建一个位图画刷（把位图映射到用户空间矩形 [ox,oy,ex,ey]，带around(ox,oy)旋转）
static void make_image_brush(CanvasCtx* ctx, Image* image, float ox, float oy, float ex, float ey, float angle, float alpha, bool fill) {
	ID2D1Bitmap* bmp = (ID2D1Bitmap*)image->bitmap;
	if (!bmp || !ctx->rt) return;
	D2D1_SIZE_F s = bmp->GetSize();
	float bw = s.width, bh = s.height;
	// nanovg语义: ex,ey 是图片被缩放到的目标宽高
	float tx = (bw > 0) ? ex / bw : 1.0f;
	float ty = (bh > 0) ? ey / bh : 1.0f;

	D2D1_BITMAP_BRUSH_PROPERTIES bp = D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	ID2D1BitmapBrush* brush = nullptr;
	ctx->rt->CreateBitmapBrush(bmp, bp, &brush);
	if (!brush) return;

	D2D1::Matrix3x2F local =
		D2D1::Matrix3x2F::Translation(ox, oy) *
		D2D1::Matrix3x2F::Rotation(angle) *
		D2D1::Matrix3x2F::Scale(tx, ty);
	brush->SetTransform(local);
	brush->SetOpacity(alpha * ctx->globalAlpha);

	if (fill) set_fill_brush(ctx, brush);
	else set_stroke_brush(ctx, brush);
}

void Canvas::linearGradient(bool fill, float sx, float sy, float ex, float ey, int icolor, int ocol) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;
	D2D1_GRADIENT_STOP stops[2];
	stops[0].position = 0.0f; stops[0].color = color_from_int(icolor, ctx->globalAlpha);
	stops[1].position = 1.0f; stops[1].color = color_from_int(ocol, ctx->globalAlpha);
	ID2D1GradientStopCollection* gsc = nullptr;
	ctx->rt->CreateGradientStopCollection(stops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &gsc);
	if (!gsc) return;
	D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES props(D2D1::Point2F(sx, sy), D2D1::Point2F(ex, ey));
	ID2D1LinearGradientBrush* brush = nullptr;
	ctx->rt->CreateLinearGradientBrush(props, gsc, &brush);
	gsc->Release();
	if (!brush) return;
	if (fill) set_fill_brush(ctx, brush);
	else set_stroke_brush(ctx, brush);
}

void Canvas::boxGradient(bool fill, float x, float y, float w, float h, float r, float f, int icol, int ocol) {
	// 近似实现为径向渐变
	float cx = x + w * 0.5f;
	float cy = y + h * 0.5f;
	float outr = sqrtf(w * w + h * h) * 0.5f;
	radialGradient(fill, cx, cy, f, outr, icol, ocol);
}

void Canvas::radialGradient(bool fill, float cx, float cy, float inr, float outr, int icol, int ocol) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;
	if (outr < 0.001f) outr = 0.001f;
	float ratio = inr / outr;
	if (ratio < 0) ratio = 0;
	if (ratio > 1) ratio = 1;

	D2D1_GRADIENT_STOP stops[3];
	int n = 0;
	if (ratio > 0.001f) {
		stops[0].position = 0.0f; stops[0].color = color_from_int(icol, ctx->globalAlpha);
		stops[1].position = ratio; stops[1].color = color_from_int(icol, ctx->globalAlpha);
		stops[2].position = 1.0f; stops[2].color = color_from_int(ocol, ctx->globalAlpha);
		n = 3;
	} else {
		stops[0].position = 0.0f; stops[0].color = color_from_int(icol, ctx->globalAlpha);
		stops[1].position = 1.0f; stops[1].color = color_from_int(ocol, ctx->globalAlpha);
		n = 2;
	}
	ID2D1GradientStopCollection* gsc = nullptr;
	ctx->rt->CreateGradientStopCollection(stops, (UINT32)n, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &gsc);
	if (!gsc) return;
	D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES props(D2D1::Point2F(cx, cy), D2D1::Point2F(cx, cy), outr, outr);
	ID2D1RadialGradientBrush* brush = nullptr;
	ctx->rt->CreateRadialGradientBrush(props, gsc, &brush);
	gsc->Release();
	if (!brush) return;
	if (fill) set_fill_brush(ctx, brush);
	else set_stroke_brush(ctx, brush);
}

void Canvas::imagePattern(bool fill, float ox, float oy, float ex, float ey, float angle, Image* image, float alpha) {
	if (!image || !image->bitmap) return;
	CanvasCtx* ctx = (CanvasCtx*)data;
	if (!ctx || !ctx->rt) return;
	make_image_brush(ctx, image, ox, oy, ex, ey, angle, alpha, fill);
}

Ref<Image> Canvas::createImageRGBA(int w, int h, const unsigned char* imgData) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	Ref<Image> img{new Image()};
	if (!ctx || !ctx->rt || !imgData || w <= 0 || h <= 0) return nullptr;

	// 源数据为直通RGBA，转换为预乘BGRA
	std::vector<unsigned char> buf((size_t)w * h * 4);
	for (int i = 0; i < w * h; i++) {
		unsigned char r = imgData[i * 4 + 0];
		unsigned char g = imgData[i * 4 + 1];
		unsigned char b = imgData[i * 4 + 2];
		unsigned char a = imgData[i * 4 + 3];
		buf[i * 4 + 0] = (unsigned char)(b * a / 255);
		buf[i * 4 + 1] = (unsigned char)(g * a / 255);
		buf[i * 4 + 2] = (unsigned char)(r * a / 255);
		buf[i * 4 + 3] = a;
	}

	D2D1_BITMAP_PROPERTIES bp = D2D1::BitmapProperties(
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
	ID2D1Bitmap* bmp = nullptr;
	ctx->rt->CreateBitmap(D2D1::SizeU(w, h), buf.data(), w * 4, bp, &bmp);
	if (bmp) {
		img->bitmap = bmp;
		return img;
	}
	return nullptr;
}

Ref<Image> Canvas::createImage(const char* path) {
	CanvasCtx* ctx = (CanvasCtx*)data;
	Ref<Image> img{new Image()};
	if (!ctx || !ctx->rt || !path) return nullptr;
	ensureFactories();
	if (!g_wicFactory) return nullptr;

	IWICBitmapDecoder* decoder = nullptr;
	std::wstring wpath = utf8_to_wide(path);
	if (FAILED(g_wicFactory->CreateDecoderFromFilename(wpath.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder)) || !decoder) {
		return nullptr;
	}
	IWICBitmapFrameDecode* frame = nullptr;
	if (FAILED(decoder->GetFrame(0, &frame)) || !frame) {
		decoder->Release();
		return nullptr;
	}
	IWICFormatConverter* converter = nullptr;
	g_wicFactory->CreateFormatConverter(&converter);
	converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);

	ID2D1Bitmap* bmp = nullptr;
	ctx->rt->CreateBitmapFromWicBitmap(converter, nullptr, &bmp);

	converter->Release();
	frame->Release();
	decoder->Release();

	if (bmp) {
		img->bitmap = bmp;
		return img;
	}
	return nullptr;
}

Canvas* Canvas::getInstance() {
	return gCanvas;
}