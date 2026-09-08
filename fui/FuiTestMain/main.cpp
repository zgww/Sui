#include <Windows.h>
#include <stdio.h>
#include <d2d1.h>
#include "Urgc/Urgc.h"
#include <rttr/type.h>
#include <rttr/variant.h>
#include <rttr/property.h>
#include <rttr/method.h>
#include "Core/Emitter.h"
#include "Core/Node.h"
#include "Core/View.h"
#include "Core/Rect.h"

#pragma comment(lib, "d2d1.lib")

static bool rttr_check_type(const char* name) {
	rttr::type t = rttr::type::get_by_name(name);
	if (!t.is_valid()) { printf("[FAIL] type '%s' not registered\n", name); return false; }
	printf("[OK]   %-9s props=%-3zu methods=%-3zu bases=%zu\n",
		name, t.get_properties().size(), t.get_methods().size(), t.get_base_classes().size());
	return true;
}

static int rttr_verify() {
	printf("==== RTTR runtime verification ====\n");
	bool ok = true;
	const char* names[] = { "Emitter","Node","ViewBase","View","Rect","Inset","Vec2","Edge","Border","Frame" };
	for (const char* n : names) ok &= rttr_check_type(n);

	struct Pair { const char* d; const char* b; };
	Pair pairs[] = { {"View","ViewBase"}, {"ViewBase","Node"}, {"Node","Emitter"} };
	for (auto& p : pairs) {
		rttr::type d = rttr::type::get_by_name(p.d);
		rttr::type b = rttr::type::get_by_name(p.b);
		bool derived = d.is_valid() && b.is_valid() && d.is_derived_from(b);
		printf("%-11s is_derived_from %-9s : %s\n", p.d, p.b, derived ? "true" : "false");
		ok &= derived;
	}

	rttr::type tRect = rttr::type::get_by_name("Rect");
	rttr::variant inst = tRect.create();
	if (!inst.is_valid()) { printf("[FAIL] Rect create failed\n"); ok = false; }
	else {
		rttr::property px = tRect.get_property("x");
		bool set_ok = px.set_value(inst, 5.0f);
		float got = px.get_value(inst).to_float();
		float r = tRect.get_method("right").invoke(inst).to_float();
		printf("Rect: set x=5 -> %s, get x=%.1f, right()=%.1f\n", set_ok ? "ok" : "FAIL", got, r);
		ok &= set_ok && got == 5.0f && r == 5.0f;
	}

	printf("==== RTTR verification %s ====\n", ok ? "PASSED" : "FAILED");
	return ok ? 0 : 1;
}

static ID2D1Factory* g_factory = nullptr;
static ID2D1HwndRenderTarget* g_target = nullptr;
static ID2D1LinearGradientBrush* g_gradient = nullptr;
static ID2D1SolidColorBrush* g_solid = nullptr;

static void recreateGradientBrush() {
	if (!g_target) return;

	D2D1_SIZE_F size = g_target->GetSize();
	D2D1_GRADIENT_STOP stops[] = {
		{ 0.0f, D2D1::ColorF(0x89b4fa) },
		{ 1.0f, D2D1::ColorF(0xf5c2e7) },
	};
	ID2D1GradientStopCollection* collection = nullptr;
	g_target->CreateGradientStopCollection(stops, 2, &collection);

	ID2D1LinearGradientBrush* brush = nullptr;
	g_target->CreateLinearGradientBrush(
		D2D1::LinearGradientBrushProperties(
			D2D1::Point2F(0.0f, 0.0f),
			D2D1::Point2F(size.width, size.height)),
		collection, &brush);
	collection->Release();

	if (g_gradient) g_gradient->Release();
	g_gradient = brush;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE: {
		RECT rc;
		GetClientRect(hwnd, &rc);
		if (FAILED(g_factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right, rc.bottom)),
				&g_target))) {
			return -1;
		}
		g_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0.5f), &g_solid);
		recreateGradientBrush();
		return 0;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);

		g_target->BeginDraw();
		g_target->Clear(D2D1::ColorF(0x181825));

		D2D1_SIZE_F size = g_target->GetSize();
		D2D1_RECT_F rect = D2D1::RectF(
			size.width * 0.1f, size.height * 0.1f,
			size.width * 0.9f, size.height * 0.9f);
		g_target->FillRoundedRectangle(
			D2D1::RoundedRect(rect, 24.0f, 24.0f), g_gradient);

		g_target->FillEllipse(
			D2D1::Ellipse(D2D1::Point2F(size.width * 0.5f, size.height * 0.5f), 60.0f, 60.0f),
			g_solid);

		g_target->EndDraw();
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_SIZE:
		if (g_target && wParam  != SIZE_MINIMIZED) {
			g_target->Resize(D2D1::SizeU(LOWORD(lParam), HIWORD(lParam)));
			recreateGradientBrush();
			//InvalidateRect(hwnd, nullptr, FALSE);
		}
		return 0;
	case WM_ERASEBKGND:
		return 1;
	case WM_DESTROY:
		if (g_solid) { g_solid->Release(); g_solid = nullptr; }
		if (g_gradient) { g_gradient->Release(); g_gradient = nullptr; }
		if (g_target) { g_target->Release(); g_target = nullptr; }
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
class User {
public:
	float data[1024];
};
//int WinMain(
//	HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR     lpCmdLine,
//	int       nShowCmd
//) {
int main(int argc, char** argv) {
	urgc.start_process_thread();

	SetConsoleOutputCP(65001);

	if (argc > 1 && strcmp(argv[1], "--rttr") == 0) {
		return rttr_verify();
	}

	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_factory))) {
		printf("D2D1CreateFactory failed\n");
		return 1;
	}
	Ref<User> user = new User();
	WNDCLASSW wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandleW(nullptr);
	wc.lpszClassName = L"FuiTestD2D";
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(
		0, wc.lpszClassName, L"FuiTestMain - Direct2D",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 900, 600,
		nullptr, nullptr, wc.hInstance, nullptr);
	if (!hwnd) {
		g_factory->Release();
		return 1;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessageW(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	g_factory->Release();
	return (int)msg.wParam;
}
