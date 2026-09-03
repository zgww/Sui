// Canvas 的 Skia 后端实现 (GPU: GrDirectContext, 由窗口层提供)
// 坐标语义与 nanovg 后端一致: 绘制坐标即像素坐标, devicePixelRatio 不参与 CTM。

#define NOMINMAX

#include "../Core/Canvas.h"
#include "SkiaBridge.h"

#include "include/codec/SkCodec.h"
#include "include/codec/SkBmpDecoder.h"
#include "include/codec/SkGifDecoder.h"
#include "include/codec/SkIcoDecoder.h"
#include "include/codec/SkJpegDecoder.h"
#include "include/codec/SkPngDecoder.h"
#include "include/codec/SkWebpDecoder.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkBlurTypes.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
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
#include "include/core/SkPixmap.h"
#include "include/core/SkRRect.h"
#include "include/core/SkSamplingOptions.h"
#include "include/core/SkSurface.h"
#include "include/core/SkTypeface.h"
#include "include/effects/SkGradient.h"
#include "include/gpu/ganesh/GrDirectContext.h"
#include "include/ports/SkTypeface_win.h"

#include <map>
#include <string>
#include <vector>
#include <string.h>
#include <math.h>

// ---------------------------------------------------------------------------
// 后端内部状态
// ---------------------------------------------------------------------------

struct SkiaState {
	SkColor4f fillColor = { 0, 0, 0, 1 };
	SkColor4f strokeColor = { 0, 0, 0, 1 };
	sk_sp<SkShader> fillShader;      // null = 纯色
	sk_sp<SkShader> strokeShader;
	float fillShaderAlpha = 1.0f;    // imagePattern 的附加透明度
	float strokeShaderAlpha = 1.0f;

	float strokeWidth = 1.0f;
	int lineCap = CANVAS_CAP_BUTT;
	int lineJoin = CANVAS_JOIN_MITER;
	float globalAlpha = 1.0f;
	bool shapeAntiAlias = true;

	std::string fontFace = "sans";
	float fontSize = 16.0f;
	float letterSpacing = 0.0f;
	float lineHeight = 1.0f;
	int textAlign = CANVAS_ALIGN_LEFT | CANVAS_ALIGN_BASELINE;
	float fontBlur = 0.0f;

	SkColor4f shadowColor = { 0, 0, 0, 0 };   // a=0 无阴影
	float shadowOffsetX = 0.0f;
	float shadowOffsetY = 0.0f;
	float shadowBlur = 0.0f;
};

struct SkiaCtx {
	// 当前帧渲染目标（由窗口层通过 skiaCanvasBindFrame 设置, 不拥有）
	SkCanvas* skCanvas = nullptr;
	GrDirectContext* grContext = nullptr;
	float viewW = 0;
	float viewH = 0;
	float dpr = 1.0f;

	SkiaState st;
	std::vector<SkiaState> stack;

	SkPathBuilder path;

	sk_sp<SkFontMgr> fontMgr;
	std::map<std::string, sk_sp<SkTypeface>> typefaces;

	// 拥有所有通过 Canvas 创建的图像 (Image::bitmap 指向其中的 SkImage*)
	std::vector<sk_sp<SkImage>> images;
};

static SkiaCtx* g_skiaCtx = nullptr;
static Canvas* gCanvas = nullptr;

// ---------------------------------------------------------------------------
// 辅助
// ---------------------------------------------------------------------------

static SkColor4f color4fByInt(int color, float alphaMul = 1.0f) {
	SkColor4f c;
	c.fR = (float)(((color >> 16) & 0xFF)) / 255.0f;
	c.fG = (float)(((color >> 8) & 0xFF)) / 255.0f;
	c.fB = (float)(((color) & 0xFF)) / 255.0f;
	c.fA = (float)(((color >> 24) & 0xFF)) / 255.0f * alphaMul;
	return c;
}

static sk_sp<SkTypeface> findTypeface(SkiaCtx* ctx, const std::string& face) {
	auto it = ctx->typefaces.find(face);
	if (it != ctx->typefaces.end()) {
		return it->second;
	}
	sk_sp<SkTypeface> tf;
	if (ctx->fontMgr) {
		const char* name = face.c_str();
		if (face.empty() || face == "sans" || face == "sans-serif") {
			name = "Microsoft YaHei";
		}
		tf = ctx->fontMgr->legacyMakeTypeface(name, SkFontStyle::Normal());
		if (!tf) tf = ctx->fontMgr->legacyMakeTypeface("Microsoft YaHei", SkFontStyle::Normal());
		if (!tf) tf = ctx->fontMgr->legacyMakeTypeface("SimSun", SkFontStyle::Normal());
		if (!tf) tf = ctx->fontMgr->legacyMakeTypeface(nullptr, SkFontStyle::Normal());
	}
	ctx->typefaces[face] = tf;
	return tf;
}

static SkFont makeFont(SkiaCtx* ctx) {
	SkFont font(findTypeface(ctx, ctx->st.fontFace), ctx->st.fontSize);
	font.setEdging(SkFont::Edging::kAntiAlias);
	font.setSubpixel(true);
	return font;
}

static SkPaint makePaint(SkiaCtx* ctx, bool strokeStyle) {
	SkPaint p;
	p.setAntiAlias(ctx->st.shapeAntiAlias);
	if (strokeStyle) {
		p.setStyle(SkPaint::kStroke_Style);
		p.setStrokeWidth(ctx->st.strokeWidth);
		switch (ctx->st.lineCap) {
		case CANVAS_CAP_ROUND: p.setStrokeCap(SkPaint::kRound_Cap); break;
		case CANVAS_CAP_SQUARE: p.setStrokeCap(SkPaint::kSquare_Cap); break;
		default: p.setStrokeCap(SkPaint::kButt_Cap); break;
		}
		switch (ctx->st.lineJoin) {
		case CANVAS_JOIN_ROUND: p.setStrokeJoin(SkPaint::kRound_Join); break;
		case CANVAS_JOIN_BEVEL: p.setStrokeJoin(SkPaint::kBevel_Join); break;
		default: p.setStrokeJoin(SkPaint::kMiter_Join); break;
		}
		if (ctx->st.strokeShader) {
			p.setShader(ctx->st.strokeShader);
			p.setAlphaf(ctx->st.strokeShaderAlpha * ctx->st.globalAlpha);
		} else {
			p.setColor4f(ctx->st.strokeColor);
			p.setAlphaf(ctx->st.strokeColor.fA * ctx->st.globalAlpha);
		}
	} else {
		if (ctx->st.fillShader) {
			p.setShader(ctx->st.fillShader);
			p.setAlphaf(ctx->st.fillShaderAlpha * ctx->st.globalAlpha);
		} else {
			p.setColor4f(ctx->st.fillColor);
			p.setAlphaf(ctx->st.fillColor.fA * ctx->st.globalAlpha);
		}
	}
	return p;
}

static bool hasShadow(SkiaCtx* ctx) {
	return ctx->st.shadowColor.fA > 0.0f &&
		(ctx->st.shadowBlur > 0.0f || ctx->st.shadowOffsetX != 0.0f || ctx->st.shadowOffsetY != 0.0f);
}

// ---------------------------------------------------------------------------
// 桥接: 窗口层每帧设置渲染目标
// ---------------------------------------------------------------------------

void skiaCanvasBindFrame(SkSurface* surface, GrDirectContext* grContext) {
	if (!g_skiaCtx) return;
	g_skiaCtx->skCanvas = surface ? surface->getCanvas() : nullptr;
	g_skiaCtx->grContext = grContext;
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
	if (g_skiaCtx) {
		data = g_skiaCtx;
		return;
	}
	g_skiaCtx = new SkiaCtx();
	g_skiaCtx->fontMgr = SkFontMgr_New_DirectWrite();
	data = g_skiaCtx;
}

void Canvas::bindWindow(void* hwnd) {
}

void Canvas::unbindWindow() {
}

void Canvas::beginFrame(float w, float h, float devicePixelRatio) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->viewW = w;
	ctx->viewH = h;
	ctx->dpr = devicePixelRatio;

	// 复位上一帧遗留的矩阵/裁剪/状态
	ctx->skCanvas->restoreToCount(1);
	ctx->skCanvas->clear(SK_ColorTRANSPARENT);
	ctx->stack.clear();
	ctx->st = SkiaState();
	ctx->path = SkPathBuilder();
}

void Canvas::endFrame() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->grContext) return;
	ctx->grContext->flushAndSubmit();
}

void Canvas::cancelFrame() {
	// Skia 的绘制在 flush 前不会提交到 GPU, 下一帧 beginFrame 的 clear 会覆盖
}

void Canvas::globalAlpha(float alpha) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.globalAlpha = alpha;
}

void Canvas::fill() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	SkPath p = ctx->path.snapshot();
	if (hasShadow(ctx)) {
		SkPaint sp = makePaint(ctx, false);
		sp.setShader(nullptr);
		sp.setColor4f(ctx->st.shadowColor);
		sp.setAlphaf(ctx->st.shadowColor.fA * ctx->st.globalAlpha);
		if (ctx->st.shadowBlur > 0) {
			sp.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, ctx->st.shadowBlur * 0.5f, true));
		}
		ctx->skCanvas->save();
		ctx->skCanvas->translate(ctx->st.shadowOffsetX, ctx->st.shadowOffsetY);
		ctx->skCanvas->drawPath(p, sp);
		ctx->skCanvas->restore();
	}
	ctx->skCanvas->drawPath(p, makePaint(ctx, false));
}

void Canvas::stroke() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	SkPath p = ctx->path.snapshot();
	if (hasShadow(ctx)) {
		SkPaint sp = makePaint(ctx, true);
		sp.setShader(nullptr);
		sp.setColor4f(ctx->st.shadowColor);
		sp.setAlphaf(ctx->st.shadowColor.fA * ctx->st.globalAlpha);
		if (ctx->st.shadowBlur > 0) {
			sp.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, ctx->st.shadowBlur * 0.5f, true));
		}
		ctx->skCanvas->save();
		ctx->skCanvas->translate(ctx->st.shadowOffsetX, ctx->st.shadowOffsetY);
		ctx->skCanvas->drawPath(p, sp);
		ctx->skCanvas->restore();
	}
	ctx->skCanvas->drawPath(p, makePaint(ctx, true));
}

void Canvas::strokeColorByInt32(int c) {
	strokeColor(colorGetR(c), colorGetG(c), colorGetB(c), colorGetA(c));
}

void Canvas::fillColorByInt32(int c) {
	fillColor(colorGetR(c), colorGetG(c), colorGetB(c), colorGetA(c));
}

void Canvas::fillColor(int r, int g, int b, int a) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.fillColor = { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
	ctx->st.fillShader = nullptr;
}

void Canvas::strokeColor(int r, int g, int b, int a) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.strokeColor = { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
	ctx->st.strokeShader = nullptr;
}

void Canvas::strokeWidth(float width) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.strokeWidth = width;
}

// 阴影 (类似 HTML5 canvas shadow)
void Canvas::shadowColor(int r, int g, int b, int a) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.shadowColor = { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
}

void Canvas::shadowOffset(float x, float y) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.shadowOffsetX = x;
	ctx->st.shadowOffsetY = y;
}

void Canvas::shadowBlur(float blur) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.shadowBlur = blur;
}

void Canvas::shapeAntiAlias(int enabled) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.shapeAntiAlias = enabled != 0;
}

void Canvas::lineJoin(int join) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.lineJoin = join;
}

void Canvas::lineCap(int cap) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.lineCap = cap;
}

void Canvas::translate(float x, float y) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->skCanvas->translate(x, y);
}

void Canvas::scale(float x, float y) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->skCanvas->scale(x, y);
}

void Canvas::rotate(float rad) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->skCanvas->rotate(rad * 180.0f / 3.14159265358979323846f);
}

void Canvas::skewX(float rad) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->skCanvas->skew(tanf(rad), 0.0f);
}

void Canvas::skewY(float rad) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->skCanvas->skew(0.0f, tanf(rad));
}

void Canvas::transform(const Mat2d& mat) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	SkMatrix m;
	m.setAll(
		mat.data[0], mat.data[2], mat.data[4],
		mat.data[1], mat.data[3], mat.data[5],
		0, 0, 1
	);
	ctx->skCanvas->concat(m);
}

void Canvas::setTransform(const Mat2d& mat) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	SkMatrix m;
	m.setAll(
		mat.data[0], mat.data[2], mat.data[4],
		mat.data[1], mat.data[3], mat.data[5],
		0, 0, 1
	);
	ctx->skCanvas->setMatrix(m);
}

void Canvas::resetTransform() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->skCanvas->setMatrix(SkMatrix::I());
}

void Canvas::currentTransform(Mat2d* mat) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!mat) return;
	if (!ctx || !ctx->skCanvas) {
		mat2dIdentity(mat->data);
		return;
	}
	SkMatrix m = ctx->skCanvas->getTotalMatrix();
	mat->data[0] = m.getScaleX();
	mat->data[1] = m.getSkewY();
	mat->data[2] = m.getSkewX();
	mat->data[3] = m.getScaleY();
	mat->data[4] = m.getTranslateX();
	mat->data[5] = m.getTranslateY();
}

void Canvas::save() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->stack.push_back(ctx->st);
	ctx->skCanvas->save();
}

void Canvas::restore() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	if (ctx->stack.empty()) return;
	ctx->st = ctx->stack.back();
	ctx->stack.pop_back();
	ctx->skCanvas->restore();
}

void Canvas::reset() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st = SkiaState();
	if (ctx->skCanvas) {
		ctx->skCanvas->setMatrix(SkMatrix::I());
	}
}

void Canvas::scissor(float x, float y, float w, float h) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->skCanvas->clipRect(SkRect::MakeXYWH(x, y, w, h), SkClipOp::kIntersect, false);
}

void Canvas::intersectScissor(float x, float y, float w, float h) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	ctx->skCanvas->clipRect(SkRect::MakeXYWH(x, y, w, h), SkClipOp::kIntersect, false);
}

void Canvas::resetScissor() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas) return;
	// Skia 裁剪栈无法单独弹出裁剪, 近似恢复为整帧区域
	ctx->skCanvas->clipRect(SkRect::MakeWH(ctx->viewW, ctx->viewH), SkClipOp::kIntersect, false);
}

void Canvas::beginPath() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path = SkPathBuilder();
}

void Canvas::closePath() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.close();
}

void Canvas::moveTo(float x, float y) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.moveTo(x, y);
}

void Canvas::lineTo(float x, float y) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.lineTo(x, y);
}

void Canvas::bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.cubicTo(c1x, c1y, c2x, c2y, x, y);
}

void Canvas::quadTo(float cx, float cy, float x, float y) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.quadTo(cx, cy, x, y);
}

void Canvas::arcTo(float x1, float y1, float x2, float y2, float radius) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.arcTo(SkPoint::Make(x1, y1), SkPoint::Make(x2, y2), radius);
}

void Canvas::pathWinding(int dir) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	// nanovg: CCW=实心, CW=挖洞; 用偶奇填充近似挖洞语义
	if (dir == CANVAS_CW) {
		ctx->path.setFillType(SkPathFillType::kEvenOdd);
	} else {
		ctx->path.setFillType(SkPathFillType::kWinding);
	}
}

void Canvas::arc(float cx, float cy, float r, float a0, float a1, int dir) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	float sweep;
	if (dir == CANVAS_CW) {
		while (a1 < a0) a1 += 6.28318530717958647692f;
		sweep = a1 - a0;
	} else {
		while (a1 > a0) a1 -= 6.28318530717958647692f;
		sweep = a1 - a0;
	}
	SkRect oval = SkRect::MakeLTRB(cx - r, cy - r, cx + r, cy + r);
	ctx->path.arcTo(oval, a0 * 180.0f / 3.14159265358979323846f,
		sweep * 180.0f / 3.14159265358979323846f, false);
}

void Canvas::rect(float x, float y, float w, float h) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.addRect(SkRect::MakeXYWH(x, y, w, h));
}

void Canvas::roundRect(float x, float y, float w, float h, float r) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.addRRect(SkRRect::MakeRectXY(SkRect::MakeXYWH(x, y, w, h), r, r));
}

void Canvas::roundRectVarying(float x, float y, float w, float h, float rtl, float rtr, float rbr, float rbl) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	SkRect rc = SkRect::MakeXYWH(x, y, w, h);
	SkVector radii[4] = {
		{ rtl, rtl },   // kUpperLeft_Corner
		{ rtr, rtr },   // kUpperRight_Corner
		{ rbr, rbr },   // kLowerRight_Corner
		{ rbl, rbl },   // kLowerLeft_Corner
	};
	SkRRect rrect;
	rrect.setRectRadii(rc, radii);
	ctx->path.addRRect(rrect);
}

void Canvas::ellipse(float cx, float cy, float rx, float ry) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.addOval(SkRect::MakeLTRB(cx - rx, cy - ry, cx + rx, cy + ry));
}

void Canvas::circle(float cx, float cy, float r) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->path.addCircle(cx, cy, r);
}

// ---------------------------------------------------------------------------
// 文本
// ---------------------------------------------------------------------------

void Canvas::fontBlur(float blur) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.fontBlur = blur;
}

void Canvas::fontFace(const char* name) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.fontFace = name ? name : "sans";
}

void Canvas::fontSize(float size) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.fontSize = size;
}

void Canvas::textLetterSpacing(float spacing) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.letterSpacing = spacing;
}

void Canvas::texLineHeight(float lineHeight) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.lineHeight = lineHeight;
}

void Canvas::textAlign(int align) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	ctx->st.textAlign = align;
}

// 垂直对齐: 返回有效基线Y (nanovg语义: descender为负)
static float alignBaselineY(SkiaCtx* ctx, float ascender, float descender, float y) {
	int align = ctx->st.textAlign;
	if (align & CANVAS_ALIGN_TOP) return y + ascender;
	if (align & CANVAS_ALIGN_MIDDLE) return y + (ascender - descender) * 0.5f;
	if (align & CANVAS_ALIGN_BOTTOM) return y + descender;
	return y;
}

void Canvas::text(float x, float y, const char* string) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !ctx->skCanvas || !string || !*string) return;

	SkFont font = makeFont(ctx);
	SkFontMetrics fm;
	font.getMetrics(&fm);
	float ascender = -fm.fAscent;
	float descender = -fm.fDescent;
	float lineh = fm.fDescent - fm.fAscent + fm.fLeading;

	float lineY = alignBaselineY(ctx, ascender, descender, y);// -descender;

	SkPaint paint = makePaint(ctx, false);
	if (ctx->st.fontBlur > 0) {
		paint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, ctx->st.fontBlur * 0.5f, true));
	}

	// 分行绘制 (nanovg: \n换行, 行推进 = lineh * lineHeight)
	const char* p = string;
	while (*p) {
		const char* nl = strchr(p, '\n');
		size_t len = nl ? (size_t)(nl - p) : strlen(p);
		if (len > 0) {
			float w = font.measureText(p, len, SkTextEncoding::kUTF8);
			float lx = x;
			if (ctx->st.textAlign & CANVAS_ALIGN_CENTER) lx = x - w * 0.5f;
			else if (ctx->st.textAlign & CANVAS_ALIGN_RIGHT) lx = x - w;
			if (ctx->st.letterSpacing != 0.0f) {
				// 逐字符绘制以支持字距
				const char* q = p;
				const char* end = p + len;
				float cx = lx;
				while (q < end) {
					const char* next = q + 1;
					while (next < end && (*next & 0xC0) == 0x80) next++;
					size_t clen = (size_t)(next - q);
					ctx->skCanvas->drawSimpleText(q, clen, SkTextEncoding::kUTF8, cx, lineY, font, paint);
					cx += font.measureText(q, clen, SkTextEncoding::kUTF8) + ctx->st.letterSpacing;
					q = next;
				}
			} else {
				ctx->skCanvas->drawSimpleText(p, len, SkTextEncoding::kUTF8, lx, lineY, font, paint);
			}
		}
		if (!nl) break;
		p = nl + 1;
		lineY += lineh * ctx->st.lineHeight;
	}
}

float Canvas::textBounds(float x, float y, const char* string, const char* end, float* bounds) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx || !string) {
		if (bounds) { bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0; }
		return 0;
	}
	size_t len = end ? (size_t)(end - string) : strlen(string);
	if (len == 0) {
		if (bounds) { bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0; }
		return 0;
	}

	SkFont font = makeFont(ctx);
	SkFontMetrics fm;
	font.getMetrics(&fm);
	float ascender = -fm.fAscent;
	float descender = -fm.fDescent;
	float lineh = fm.fDescent - fm.fAscent + fm.fLeading;

	// 最大行宽
	float maxW = 0;
	int lineCount = 1;
	{
		const char* p = string;
		const char* stop = string + len;
		while (p < stop) {
			const char* nl = (const char*)memchr(p, '\n', (size_t)(stop - p));
			const char* lineEnd = nl ? nl : stop;
			size_t llen = (size_t)(lineEnd - p);
			if (llen > 0) {
				float w = font.measureText(p, llen, SkTextEncoding::kUTF8);
				if (w > maxW) maxW = w;
			}
			if (!nl) break;
			p = nl + 1;
			lineCount++;
		}
	}

	float baseY = alignBaselineY(ctx, ascender, descender, y);
	float x0 = x;
	if (ctx->st.textAlign & CANVAS_ALIGN_CENTER) x0 = x - maxW * 0.5f;
	else if (ctx->st.textAlign & CANVAS_ALIGN_RIGHT) x0 = x - maxW;

	float top = baseY - ascender;
	float bottom = baseY - descender + (lineCount - 1) * lineh * ctx->st.lineHeight;

	if (bounds) {
		// nanovg语义: 用当前变换矩阵映射包围盒
		SkPoint pts[4] = {
			{ x0, top }, { x0 + maxW, top }, { x0 + maxW, bottom }, { x0, bottom }
		};
		if (ctx->skCanvas) {
			SkMatrix m = ctx->skCanvas->getTotalMatrix();
			m.mapPoints(SkSpan<SkPoint>(pts, 4));
		}
		float minx = pts[0].x(), miny = pts[0].y(), maxx = pts[0].x(), maxy = pts[0].y();
		for (int i = 1; i < 4; i++) {
			if (pts[i].x() < minx) minx = pts[i].x();
			if (pts[i].y() < miny) miny = pts[i].y();
			if (pts[i].x() > maxx) maxx = pts[i].x();
			if (pts[i].y() > maxy) maxy = pts[i].y();
		}
		bounds[0] = minx;
		bounds[1] = miny;
		bounds[2] = maxx;
		bounds[3] = maxy;
	}
	return maxW;
}

TextMetrics Canvas::textMetrics() {
	SkiaCtx* ctx = (SkiaCtx*)data;
	TextMetrics tm;
	tm.ascender = 0;
	tm.descender = 0;
	tm.lineh = 0;
	if (!ctx) return tm;
	SkFont font = makeFont(ctx);
	SkFontMetrics fm;
	font.getMetrics(&fm);
	tm.ascender = -fm.fAscent;
	tm.descender = -fm.fDescent;      // 负值, 与nanovg一致
	tm.lineh = fm.fDescent - fm.fAscent + fm.fLeading;
	return tm;
}

// ---------------------------------------------------------------------------
// 图像
// ---------------------------------------------------------------------------

static SkImage* getSkImage(Image* img) {
	if (!img) return nullptr;
	return (SkImage*)img->bitmap;
}

void Canvas::drawImage(Image* img, float x, float y, float alpha) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	SkImage* im = getSkImage(img);
	if (!ctx || !ctx->skCanvas || !im) return;
	SkPaint p;
	p.setAntiAlias(true);
	p.setAlphaf(alpha * ctx->st.globalAlpha);
	ctx->skCanvas->drawImage(im, x, y, SkSamplingOptions(SkFilterMode::kLinear), &p);
}

void Canvas::drawImageAtRect(Image* img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, float alpha) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	SkImage* im = getSkImage(img);
	if (!ctx || !ctx->skCanvas || !im) return;
	if (sw <= 0 || sh <= 0 || dw <= 0 || dh <= 0) return;
	SkRect src = SkRect::MakeXYWH(sx, sy, sw, sh);
	SkRect dst = SkRect::MakeXYWH(dx, dy, dw, dh);
	SkPaint p;
	p.setAntiAlias(true);
	p.setAlphaf(alpha * ctx->st.globalAlpha);
	ctx->skCanvas->drawImageRect(im, src, dst, SkSamplingOptions(SkFilterMode::kLinear), &p,
		SkCanvas::kStrict_SrcRectConstraint);
}

// ---------------------------------------------------------------------------
// 渐变 / 图案
// ---------------------------------------------------------------------------

static void setShader(SkiaCtx* ctx, bool fill, sk_sp<SkShader> shader, float alpha) {
	if (fill) {
		ctx->st.fillShader = shader;
		ctx->st.fillShaderAlpha = alpha;
	} else {
		ctx->st.strokeShader = shader;
		ctx->st.strokeShaderAlpha = alpha;
	}
}

void Canvas::linearGradient(bool fill, float sx, float sy, float ex, float ey, int icolor, int ocol) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	SkColor4f colors[] = { color4fByInt(icolor), color4fByInt(ocol) };
	SkPoint pts[] = { SkPoint::Make(sx, sy), SkPoint::Make(ex, ey) };
	SkGradient::Colors gc(SkSpan(colors, 2), SkTileMode::kClamp);
	sk_sp<SkShader> shader = SkShaders::LinearGradient(pts, SkGradient(gc, SkGradient::Interpolation()));
	if (shader) setShader(ctx, fill, shader, 1.0f);
}

void Canvas::boxGradient(bool fill, float x, float y, float w, float h, float r, float f, int icol, int ocol) {
	// 与 D2D 后端一致: 近似为径向渐变
	float cx = x + w * 0.5f;
	float cy = y + h * 0.5f;
	float outr = sqrtf(w * w + h * h) * 0.5f;
	radialGradient(fill, cx, cy, f, outr, icol, ocol);
}

void Canvas::radialGradient(bool fill, float cx, float cy, float inr, float outr, int icol, int ocol) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	if (!ctx) return;
	if (outr < 0.001f) outr = 0.001f;
	float ratio = inr / outr;
	if (ratio < 0) ratio = 0;
	if (ratio > 1) ratio = 1;

	sk_sp<SkShader> shader;
	if (ratio > 0.001f) {
		SkColor4f colors[] = { color4fByInt(icol), color4fByInt(icol), color4fByInt(ocol) };
		float pos[] = { 0.0f, ratio, 1.0f };
		SkGradient::Colors gc(SkSpan(colors, 3), SkSpan(pos, 3), SkTileMode::kClamp);
		shader = SkShaders::RadialGradient(SkPoint::Make(cx, cy), outr, SkGradient(gc, SkGradient::Interpolation()));
	} else {
		SkColor4f colors[] = { color4fByInt(icol), color4fByInt(ocol) };
		SkGradient::Colors gc(SkSpan(colors, 2), SkTileMode::kClamp);
		shader = SkShaders::RadialGradient(SkPoint::Make(cx, cy), outr, SkGradient(gc, SkGradient::Interpolation()));
	}
	if (shader) setShader(ctx, fill, shader, 1.0f);
}

void Canvas::imagePattern(bool fill, float ox, float oy, float ex, float ey, float angle, Image* image, float alpha) {
	SkiaCtx* ctx = (SkiaCtx*)data;
	SkImage* im = getSkImage(image);
	if (!ctx || !im) return;
	float iw = (float)im->width();
	float ih = (float)im->height();
	if (iw <= 0 || ih <= 0) return;

	// nanovg语义: 图像被缩放到 ex x ey, 原点在(ox,oy), 绕原点旋转angle
	SkMatrix lm = SkMatrix::Translate(ox, oy);
	if (angle != 0.0f) {
		lm.postRotate(angle * 180.0f / 3.14159265358979323846f);
	}
	lm.postScale(ex / iw, ey / ih);

	sk_sp<SkShader> shader = im->makeShader(SkTileMode::kRepeat, SkTileMode::kRepeat,
		SkSamplingOptions(SkFilterMode::kLinear), lm);
	if (shader) setShader(ctx, fill, shader, alpha);
}

// ---------------------------------------------------------------------------
// 图像创建
// ---------------------------------------------------------------------------

Ref<Image> Canvas::createImageRGBA(int w, int h, const unsigned char* imgData) {
	Ref<Image> img{ new Image() };
	if (!g_skiaCtx || !imgData || w <= 0 || h <= 0) return nullptr;

	SkImageInfo info = SkImageInfo::Make(w, h, kRGBA_8888_SkColorType, kUnpremul_SkAlphaType);
	SkPixmap pm(info, imgData, (size_t)w * 4);
	sk_sp<SkImage> im = SkImages::RasterFromPixmapCopy(pm);
	if (!im) return nullptr;

	g_skiaCtx->images.push_back(im);
	img->bitmap = im.get();
	img->_img = 1;
	return img;
}

Ref<Image> Canvas::createImage(const char* path) {
	Ref<Image> img{ new Image() };
	if (!g_skiaCtx || !path) return nullptr;

	sk_sp<SkData> data = SkData::MakeFromFileName(path);
	if (!data) return nullptr;

	SkCodecs::Decoder decoders[] = {
		SkPngDecoder::Decoder(),
		SkJpegDecoder::Decoder(),
		SkWebpDecoder::Decoder(),
		SkGifDecoder::Decoder(),
		SkBmpDecoder::Decoder(),
		SkIcoDecoder::Decoder(),
	};
	std::unique_ptr<SkCodec> codec = SkCodec::MakeFromData(data, SkSpan<const SkCodecs::Decoder>(decoders, 6));
	if (!codec) return nullptr;

	SkBitmap bmp;
	if (!bmp.tryAllocPixels(codec->getInfo())) return nullptr;
	if (codec->getPixels(bmp.pixmap(), nullptr) != SkCodec::kSuccess) return nullptr;

	sk_sp<SkImage> im = SkImages::RasterFromBitmap(bmp);
	if (!im) return nullptr;

	g_skiaCtx->images.push_back(im);
	img->bitmap = im.get();
	img->_img = 1;
	return img;
}

Canvas* Canvas::getInstance() {
	return gCanvas;
}

// ---------------------------------------------------------------------------
// Image (Skia后端)
// ---------------------------------------------------------------------------

Vec2 Image::size() {
	return mkVec2(width(), height());
}

float Image::width() {
	if (_img == 0) return 0;
	SkImage* im = (SkImage*)bitmap;
	return im ? (float)im->width() : 0.0f;
}

float Image::height() {
	if (_img == 0) return 0;
	SkImage* im = (SkImage*)bitmap;
	return im ? (float)im->height() : 0.0f;
}
