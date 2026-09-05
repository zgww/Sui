// SkiaDemo: 原生 Win32 窗口 + ANGLE(EGL/GLES3) + Skia GPU 渲染
// 窗口中心绘制 200x100 长方形，中间偏上位置绘制文本 "skia, 你好"
// 窗口下方两排图片: 第一排 icons/*.png, 第二排 icons/*.svg

#define NOMINMAX
#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include "include/codec/SkCodec.h"
#include "include/codec/SkPngDecoder.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkBlurTypes.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkData.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontMetrics.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkFontStyle.h"
#include "include/core/SkImage.h"
#include "include/core/SkMaskFilter.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"
#include "include/core/SkRRect.h"
#include "include/core/SkSamplingOptions.h"
#include "include/core/SkSurface.h"
#include "include/core/SkTypeface.h"
#include "include/gpu/ganesh/GrBackendSurface.h"
#include "include/gpu/ganesh/GrDirectContext.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/ganesh/gl/GrGLAssembleInterface.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLInterface.h"
#include "include/ports/SkTypeface_win.h"
#include <opencv2/opencv.hpp>

static const wchar_t* kWindowTitle = L"SkiaDemo - Skia + ANGLE(GLES3)";

static EGLDisplay g_display = EGL_NO_DISPLAY;
static EGLConfig  g_config  = nullptr;
static EGLContext g_context = EGL_NO_CONTEXT;
static EGLSurface g_surface = EGL_NO_SURFACE;
static HWND g_hwnd = nullptr;

static sk_sp<GrDirectContext> g_grContext;
static sk_sp<SkSurface>       g_skSurface;
static sk_sp<SkTypeface>      g_typeface;

static int g_width  = 0;
static int g_height = 0;
static int g_stencilBits = 0;
static int g_sampleCnt   = 0;

// ---------------------------------------------------------------------------
// 图片资源: 第一排 PNG, 第二排 SVG
// ---------------------------------------------------------------------------
static const char* kIconNames[] = { "open", "zoom-in", "zoom-out", "fit", "rotate", "register" };
static const int kIconCount = 6;

static sk_sp<SkImage> g_pngIcons[kIconCount];

struct SvgIcon {
	SkPath   path;
	SkColor  strokeColor = SK_ColorWHITE;
	SkScalar strokeWidth = 2.0f;
	SkRect   viewBox = SkRect::MakeWH(24, 24);
	bool     valid = false;
};
static SvgIcon g_svgIcons[kIconCount];

static std::string exe_dir() {
	char buf[MAX_PATH] = {};
	GetModuleFileNameA(nullptr, buf, MAX_PATH);
	std::string s = buf;
	size_t p = s.find_last_of("\\/");
	return p == std::string::npos ? std::string() : s.substr(0, p + 1);
}

static std::string find_icons_dir() {
	std::string fromExe = exe_dir() + "..\\..\\icons\\";
	if (GetFileAttributesA((fromExe + "open.png").c_str()) != INVALID_FILE_ATTRIBUTES) {
		return fromExe;
	}
	return "icons\\";
}

static sk_sp<SkImage> load_png(const std::string& file) {
	sk_sp<SkData> data = SkData::MakeFromFileName(file.c_str());
	if (!data) {
		printf("png: cannot open %s\n", file.c_str());
		return nullptr;
	}
	SkCodec::Result result = SkCodec::kInvalidInput;
	std::unique_ptr<SkCodec> codec = SkPngDecoder::Decode(data, &result);
	if (!codec) {
		printf("png: decode failed %s (result=%d)\n", file.c_str(), (int)result);
		return nullptr;
	}
	SkBitmap bmp;
	if (!bmp.tryAllocPixels(codec->getInfo())) {
		printf("png: alloc failed %s\n", file.c_str());
		return nullptr;
	}
	if (codec->getPixels(bmp.pixmap(), nullptr) != SkCodec::kSuccess) {
		printf("png: getPixels failed %s\n", file.c_str());
		return nullptr;
	}
	return SkImages::RasterFromBitmap(bmp);
}

// ---------------------------------------------------------------------------
// Mini SVG 解析器: 仅支持本组图标用到的元素(path/circle/line/polyline)与
// path 命令(M m L l H h V v A a Z z), stroke 线条风格
// ---------------------------------------------------------------------------
static std::string find_attr(const std::string& tag, const char* name) {
	std::string pat = std::string(name) + "=";
	size_t p = tag.find(pat);
	if (p == std::string::npos) return {};
	p += pat.size();
	if (p >= tag.size() || (tag[p] != '"' && tag[p] != '\'')) return {};
	char quote = tag[p];
	size_t e = tag.find(quote, p + 1);
	if (e == std::string::npos) return {};
	return tag.substr(p + 1, e - p - 1);
}

static float attr_float(const std::string& tag, const char* name, float def) {
	std::string v = find_attr(tag, name);
	if (v.empty()) return def;
	return (float)strtod(v.c_str(), nullptr);
}

static bool parse_numbers(const std::string& s, float* out, int count) {
	const char* p = s.c_str();
	for (int i = 0; i < count; i++) {
		while (*p == ' ' || *p == ',' || *p == '\t' || *p == '\r' || *p == '\n') p++;
		char* end = nullptr;
		double v = strtod(p, &end);
		if (end == p) return false;
		p = end;
		out[i] = (float)v;
	}
	return true;
}

static void parse_path_d(const std::string& d, SkPathBuilder& b) {
	const char* p = d.c_str();
	char cmd = 0;
	float cx = 0, cy = 0;
	auto skip_ws = [&]() {
		while (*p == ' ' || *p == ',' || *p == '\t' || *p == '\r' || *p == '\n') p++;
	};
	auto num = [&](float* out) -> bool {
		skip_ws();
		char* end = nullptr;
		double v = strtod(p, &end);
		if (end == p) return false;
		p = end;
		*out = (float)v;
		return true;
	};
	for (;;) {
		skip_ws();
		if (!*p) break;
		if (isalpha((unsigned char)*p)) {
			cmd = *p++;
		} else {
			// 隐式重复参数: M->L, m->l
			if (cmd == 'M') cmd = 'L';
			else if (cmd == 'm') cmd = 'l';
		}
		float x = 0, y = 0, v = 0;
		switch (cmd) {
		case 'M':
			if (!num(&x) || !num(&y)) return;
			b.moveTo(x, y); cx = x; cy = y;
			break;
		case 'm':
			if (!num(&x) || !num(&y)) return;
			cx += x; cy += y;
			b.moveTo(cx, cy);
			break;
		case 'L':
			if (!num(&x) || !num(&y)) return;
			b.lineTo(x, y); cx = x; cy = y;
			break;
		case 'l':
			if (!num(&x) || !num(&y)) return;
			cx += x; cy += y;
			b.lineTo(cx, cy);
			break;
		case 'H':
			if (!num(&v)) return;
			b.lineTo(v, cy); cx = v;
			break;
		case 'h':
			if (!num(&v)) return;
			cx += v; b.lineTo(cx, cy);
			break;
		case 'V':
			if (!num(&v)) return;
			b.lineTo(cx, v); cy = v;
			break;
		case 'v':
			if (!num(&v)) return;
			cy += v; b.lineTo(cx, cy);
			break;
		case 'A': case 'a': {
			float rx, ry, rot, laf, sf, dx, dy;
			if (!num(&rx) || !num(&ry) || !num(&rot) ||
				!num(&laf) || !num(&sf) || !num(&dx) || !num(&dy)) return;
			if (cmd == 'a') { dx += cx; dy += cy; }
			b.arcTo({rx, ry}, rot,
				laf ? SkPathBuilder::kLarge_ArcSize : SkPathBuilder::kSmall_ArcSize,
				sf ? SkPathDirection::kCW : SkPathDirection::kCCW,
				{dx, dy});
			cx = dx; cy = dy;
			break;
		}
		case 'Z': case 'z':
			b.close();
			break;
		default:
			printf("svg: unsupported path command '%c'\n", cmd);
			return;
		}
	}
}

static bool load_svg(const std::string& file, SvgIcon* out) {
	FILE* fp = fopen(file.c_str(), "rb");
	if (!fp) {
		printf("svg: cannot open %s\n", file.c_str());
		return false;
	}
	std::string text;
	char buf[4096];
	size_t n;
	while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) text.append(buf, n);
	fclose(fp);

	SkPathBuilder builder;

	// 根元素属性
	size_t root = text.find("<svg");
	if (root == std::string::npos) {
		printf("svg: no <svg> root in %s\n", file.c_str());
		return false;
	}
	size_t rootEnd = text.find('>', root);
	std::string rootTag = text.substr(root, rootEnd - root);
	std::string vb = find_attr(rootTag, "viewBox");
	float v[4] = {0, 0, 24, 24};
	if (!vb.empty()) parse_numbers(vb, v, 4);
	out->viewBox = SkRect::MakeXYWH(v[0], v[1], v[2], v[3]);
	out->strokeWidth = attr_float(rootTag, "stroke-width", 2.0f);

	// 子元素
	static const char* kElems[] = {"<path", "<circle", "<line", "<polyline"};
	for (size_t pos = rootEnd; pos < text.size();) {
		size_t next = std::string::npos;
		const char* which = nullptr;
		for (const char* e : kElems) {
			size_t p = text.find(e, pos);
			if (p != std::string::npos && (next == std::string::npos || p < next)) {
				next = p;
				which = e;
			}
		}
		if (next == std::string::npos) break;
		size_t tagEnd = text.find('>', next);
		if (tagEnd == std::string::npos) break;
		std::string tag = text.substr(next, tagEnd - next);
		if (strcmp(which, "<path") == 0) {
			parse_path_d(find_attr(tag, "d"), builder);
		} else if (strcmp(which, "<circle") == 0) {
			float c[3];
			if (parse_numbers(find_attr(tag, "cx"), &c[0], 1) &&
				parse_numbers(find_attr(tag, "cy"), &c[1], 1) &&
				parse_numbers(find_attr(tag, "r"), &c[2], 1)) {
				builder.addCircle(c[0], c[1], c[2]);
			}
		} else if (strcmp(which, "<line") == 0) {
			float c[4];
			if (parse_numbers(find_attr(tag, "x1"), &c[0], 1) &&
				parse_numbers(find_attr(tag, "y1"), &c[1], 1) &&
				parse_numbers(find_attr(tag, "x2"), &c[2], 1) &&
				parse_numbers(find_attr(tag, "y2"), &c[3], 1)) {
				builder.moveTo(c[0], c[1]);
				builder.lineTo(c[2], c[3]);
			}
		} else if (strcmp(which, "<polyline") == 0) {
			std::string pts = find_attr(tag, "points");
			std::vector<float> nums;
			const char* q = pts.c_str();
			while (*q) {
				while (*q == ' ' || *q == ',') q++;
				if (!*q) break;
				char* end = nullptr;
				double val = strtod(q, &end);
				if (end == q) break;
				nums.push_back((float)val);
				q = end;
			}
			for (size_t i = 0; i + 1 < nums.size(); i += 2) {
				if (i == 0) builder.moveTo(nums[0], nums[1]);
				else builder.lineTo(nums[i], nums[i + 1]);
			}
		}
		pos = tagEnd + 1;
	}

	out->path = builder.snapshot();
	out->valid = !out->path.isEmpty();
	if (!out->valid) {
		printf("svg: empty path %s\n", file.c_str());
		return false;
	}
	return true;
}

static void load_assets() {
	std::string dir = find_icons_dir();
	printf("icons dir: %s\n", dir.c_str());
	for (int i = 0; i < kIconCount; i++) {
		g_pngIcons[i] = load_png(dir + kIconNames[i] + ".png");
		load_svg(dir + kIconNames[i] + ".svg", &g_svgIcons[i]);
	}
}

static GrGLFuncPtr egl_get_proc(void*, const char name[]) {
	return (GrGLFuncPtr)eglGetProcAddress(name);
}

static bool init_egl(HWND hwnd) {
	g_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (g_display == EGL_NO_DISPLAY) {
		printf("error: eglGetDisplay failed\n");
		return false;
	}
	EGLint major = 0, minor = 0;
	if (!eglInitialize(g_display, &major, &minor)) {
		printf("error: eglInitialize failed (0x%x)\n", eglGetError());
		return false;
	}
	printf("EGL %d.%d | %s\n", major, minor, eglQueryString(g_display, EGL_VENDOR));

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
	return true;
}

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

	sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_DirectWrite();
	if (fontMgr) {
		g_typeface = fontMgr->legacyMakeTypeface("Microsoft YaHei", SkFontStyle::Normal());
		if (!g_typeface) {
			g_typeface = fontMgr->legacyMakeTypeface("SimSun", SkFontStyle::Normal());
		}
	}
	if (!g_typeface) {
		printf("warning: no CJK typeface found, text may render as boxes\n");
	}
	return true;
}

static bool create_backbuffer(int w, int h) {
	g_skSurface.reset();
	if (w <= 0 || h <= 0) return false;

	GrGLFramebufferInfo fbInfo;
	fbInfo.fFBOID = 0;
	fbInfo.fFormat = GL_RGBA8;
	GrBackendRenderTarget rt = GrBackendRenderTargets::MakeGL(w, h, g_sampleCnt, g_stencilBits, fbInfo);

	g_skSurface = SkSurfaces::WrapBackendRenderTarget(
		g_grContext.get(), rt, kBottomLeft_GrSurfaceOrigin,
		kRGBA_8888_SkColorType, nullptr, nullptr);
	if (!g_skSurface) {
		printf("error: WrapBackendRenderTarget failed (%dx%d)\n", w, h);
		return false;
	}
	printf("backbuffer: %dx%d (stencil=%d samples=%d)\n", w, h, g_stencilBits, g_sampleCnt);
	return true;
}

static void draw_frame(cv::Mat& mat) {
	if (!g_skSurface) return;
	SkCanvas* canvas = g_skSurface->getCanvas();

	canvas->clear(SK_ColorWHITE);

	// 窗口中心: 200x100 长方形 (阴影 blur=10, offset=5,5)
	SkRect rect = SkRect::MakeXYWH(
		(g_width - 200.0f) * 0.5f + 0.f, (g_height - 100.0f) * 0.5f + 150.f, 200.0f, 100.0f);

	// 阴影: 阴影体 = 矩形平移(5,5), 高斯模糊; HTML5 shadowBlur=10 按 Chrome 惯例换算 sigma=blur/2
	const SkScalar shadowBlur   = 10.0f;
	const SkScalar shadowOffset = 5.0f;
	SkPaint shadowPaint;
	shadowPaint.setAntiAlias(true);
	shadowPaint.setColor(SkColorSetARGB(89, 0, 0, 0));
	shadowPaint.setMaskFilter(SkMaskFilter::MakeBlur(
		kNormal_SkBlurStyle, shadowBlur * 0.5f, true));
	canvas->drawRect(rect.makeOffset(shadowOffset, shadowOffset), shadowPaint);

	SkPaint paint;
	paint.setAntiAlias(true);
	paint.setColor(SkColorSetRGB(0x2F, 0x6F, 0xDB));
	canvas->drawRect(rect, paint);

	// 窗口中间偏上: 文本 "skia, 你好"
	static const char kText[] = "skia, 你好。是♀";
	SkFont font(g_typeface, 48.0f);
	SkFontMetrics metrics;
	font.getMetrics(&metrics);
	SkScalar textWidth = font.measureText(kText, strlen(kText), SkTextEncoding::kUTF8);
	SkScalar x = (g_width - textWidth) * 0.5f + 0.f;
	SkScalar textCenterY = g_height * 0.35f + 150.f;
	SkScalar y = textCenterY - (metrics.fAscent + metrics.fDescent) * 0.5f;

	SkPaint textPaint;
	textPaint.setAntiAlias(true);
	textPaint.setColor(SK_ColorBLACK);
	canvas->drawString(kText, x, y, font, textPaint);

	// 窗口下方两排图片: 第一排 PNG, 第二排 SVG (白色线条图标需要深色底板)
	const SkScalar cell = 64.0f;   // 底板边长
	const SkScalar pad  = 8.0f;    // 底板内边距
	const SkScalar gap  = 12.0f;   // 底板间距
	const SkScalar bottomMargin = 36.0f;
	SkScalar rowW = kIconCount * cell + (kIconCount - 1) * gap;
	SkScalar x0 = (g_width - rowW) * 0.5f;
	SkScalar row1Y = g_height - 2 * cell - gap - bottomMargin;
	SkScalar row2Y = row1Y + cell + gap;

	SkPaint platePaint;
	platePaint.setAntiAlias(true);
	platePaint.setColor(SkColorSetARGB(255, 43, 43, 48));

	SkSamplingOptions sampling(SkCubicResampler{1.0f / 3.0f, 1.0f / 3.0f});

	for (int i = 0; i < kIconCount; i++) {
		SkScalar ix = x0 + i * (cell + gap);
		SkRect plate = SkRect::MakeXYWH(ix, row1Y, cell, cell);
		canvas->drawRRect(SkRRect::MakeRectXY(plate, 10, 10), platePaint);
		if (g_pngIcons[i]) {
			SkRect dst = SkRect::MakeXYWH(ix + pad, row1Y + pad, cell - 2 * pad, cell - 2 * pad);
			canvas->drawImageRect(g_pngIcons[i].get(), dst, sampling, nullptr);
		}
	}

	for (int i = 0; i < kIconCount; i++) {
		SkScalar ix = x0 + i * (cell + gap);
		SkRect plate = SkRect::MakeXYWH(ix, row2Y, cell, cell);
		canvas->drawRRect(SkRRect::MakeRectXY(plate, 10, 10), platePaint);
		const SvgIcon& icon = g_svgIcons[i];
		if (!icon.valid) continue;
		SkRect dst = SkRect::MakeXYWH(ix + pad, row2Y + pad, cell - 2 * pad, cell - 2 * pad);
		const SkRect& vb = icon.viewBox;
		SkScalar s = dst.width() / vb.width();
		canvas->save();
		canvas->translate(dst.fLeft - vb.fLeft * s, dst.fTop - vb.fTop * s);
		canvas->scale(s, s);
		SkPaint strokePaint;
		strokePaint.setAntiAlias(true);
		strokePaint.setStyle(SkPaint::kStroke_Style);
		strokePaint.setColor(icon.strokeColor);
		strokePaint.setStrokeWidth(icon.strokeWidth);
		strokePaint.setStrokeCap(SkPaint::kRound_Cap);
		strokePaint.setStrokeJoin(SkPaint::kRound_Join);
		canvas->drawPath(icon.path, strokePaint);
		canvas->restore();
	}

	//绘制opencv视频帧
	SkImageInfo info = SkImageInfo::Make(
		mat.cols, mat.rows,
		kBGRA_8888_SkColorType,
		kPremul_SkAlphaType
	);

	//SkBi pixmap(info, mat.data, mat.step);
	// 直接将 mat 的像素写入 skiaCanvas 的 (x, y) 位置
	// 零拷贝，不经过 SkImage 转换
	int rowSize = mat.elemSize() * mat.cols;
	size_t step = mat.step;
	canvas->writePixels(info, mat.data, rowSize,  10, 10);


	skgpu::ganesh::FlushAndSubmit(g_skSurface.get());
	eglSwapBuffers(g_display, g_surface);
}

static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_ERASEBKGND:
		return 1;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int main() {
	setvbuf(stdout, nullptr, _IONBF, 0);
	SetProcessDPIAware();

	cv::VideoCapture vc;
	//auto vc = cv::VideoCapture("http://vjs.zencdn.net/v/oceans.mp4");
	cv::Mat img;
	cv::Mat frame_bgra;
	vc.open("http://vjs.zencdn.net/v/oceans.mp4", cv::CAP_ANY);
	//while (vc.isOpened()) {
	//	auto ok = vc.read(img);
	//	if (ok) {
	//		// 2. 核心步骤：BGR (3通道) -> BGRA (4通道)
	//		// 这一步是必须的，OpenCV 底层使用了 SIMD 优化，速度很快
	//		cv::cvtColor(img, frame_bgra, cv::COLOR_BGR2BGRA);
	//		// 3. 创建一个名为 "Display" 的窗口，并显示图片
	//		cv::imshow("Display", img);
	//	}
	//	int key = cv::waitKey(30) & 0xff;
	//	if (key == 'q' || key == 27) {
	//		break;
	//	}
	//}
	//MessageBoxW(NULL, L"异常?", L"标题",
	//	MB_YESNO | MB_ICONQUESTION);



	HINSTANCE hInstance = GetModuleHandleW(nullptr);
	WNDCLASSEXW wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wnd_proc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
	wc.lpszClassName = L"SkiaDemoWnd";
	if (!RegisterClassExW(&wc)) {
		printf("error: RegisterClassExW failed\n");
		return 1;
	}

	const int clientW = 1000, clientH = 1000;
	RECT rc = {0, 0, clientW, clientH};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	int winX = (sw - (rc.right - rc.left)) / 2;
	int winY = (sh - (rc.bottom - rc.top)) / 2;

	g_hwnd = CreateWindowExW(0, L"SkiaDemoWnd", kWindowTitle, WS_OVERLAPPEDWINDOW,
		winX, winY, rc.right - rc.left, rc.bottom - rc.top,
		nullptr, nullptr, hInstance, nullptr);
	if (!g_hwnd) {
		printf("error: CreateWindowExW failed\n");
		return 1;
	}

	if (!init_egl(g_hwnd)) return 1;
	if (!init_skia()) return 1;
	load_assets();

	ShowWindow(g_hwnd, SW_SHOW);
	UpdateWindow(g_hwnd);

	bool running = true;
	while (running) {
		MSG msg;
		while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				running = false;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		if (!running) break;

		RECT client;
		GetClientRect(g_hwnd, &client);
		int w = client.right - client.left;
		int h = client.bottom - client.top;
		if (w != g_width || h != g_height) {
			g_width = w;
			g_height = h;
			create_backbuffer(w, h);
		}

		auto ok = vc.read(img);
		if (ok) {
			// 2. 核心步骤：BGR (3通道) -> BGRA (4通道)
			// 这一步是必须的，OpenCV 底层使用了 SIMD 优化，速度很快
			cv::cvtColor(img, frame_bgra, cv::COLOR_BGR2BGRA);
			// 3. 创建一个名为 "Display" 的窗口，并显示图片
			//cv::imshow("Display", img);
		}

		draw_frame(frame_bgra);
	}

	g_skSurface.reset();
	g_typeface.reset();
	if (g_grContext) {
		g_grContext->flushAndSubmit();
		g_grContext.reset();
	}
	if (g_display != EGL_NO_DISPLAY) {
		eglMakeCurrent(g_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (g_surface != EGL_NO_SURFACE) eglDestroySurface(g_display, g_surface);
		if (g_context != EGL_NO_CONTEXT) eglDestroyContext(g_display, g_context);
		eglTerminate(g_display);
	}
	return 0;
}
