#include "Canvas.h"

#include <glew.h>
#define NANOVG_GL3_IMPLEMENTATION
#include "../nanovg/nanovg.h"
#include "../nanovg/nanovg_gl.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STB_IMAGE_STATIC
#include "../nanovg/stb_image.h"
#endif

static Canvas* gCanvas;

Canvas::Canvas() {
	gCanvas = this;
}
Canvas::~Canvas() {
	if (gCanvas == this) {
		gCanvas = nullptr;
	}
}

void Canvas::init() {
	if (data) return;
	data = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
}

void Canvas::beginFrame(float w, float h, float devicePixelRatio) {
	NVGcontext* vg = (NVGcontext*)data;
	nvgBeginFrame(vg, w, h, devicePixelRatio);
}

void Canvas::endFrame() {
	NVGcontext* vg = (NVGcontext*)data;
	nvgEndFrame(vg);
}

void Canvas::cancelFrame() {
	NVGcontext* vg = (NVGcontext*)data;
	nvgCancelFrame(vg);
}

void Canvas::globalAlpha(float alpha) {
	nvgGlobalAlpha((NVGcontext*)data, alpha);
}

void Canvas::stroke() {
	nvgStroke((NVGcontext*)data);
}

void Canvas::fill() {
	nvgFill((NVGcontext*)data);
}

void Canvas::strokeColorByInt32(int c) {
	strokeColor(colorGetR(c), colorGetG(c), colorGetB(c), colorGetA(c));
}

void Canvas::fillColorByInt32(int c) {
	fillColor(colorGetR(c), colorGetG(c), colorGetB(c), colorGetA(c));
}

void Canvas::fillColor(int r, int g, int b, int a) {
	nvgFillColor((NVGcontext*)data, nvgRGBA((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a));
}

void Canvas::strokeColor(int r, int g, int b, int a) {
	nvgStrokeColor((NVGcontext*)data, nvgRGBA((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a));
}

void Canvas::strokeWidth(float width) {
	nvgStrokeWidth((NVGcontext*)data, width);
}

void Canvas::shapeAntiAlias(int enabled) {
	nvgShapeAntiAlias((NVGcontext*)data, enabled);
}

void Canvas::lineJoin(int join) {
	nvgLineJoin((NVGcontext*)data, join);
}

void Canvas::lineCap(int cap) {
	nvgLineCap((NVGcontext*)data, cap);
}

void Canvas::translate(float x, float y) {
	nvgTranslate((NVGcontext*)data, x, y);
}

void Canvas::scale(float x, float y) {
	nvgScale((NVGcontext*)data, x, y);
}

void Canvas::rotate(float rad) {
	nvgRotate((NVGcontext*)data, rad);
}

void Canvas::skewX(float rad) {
	nvgSkewX((NVGcontext*)data, rad);
}

void Canvas::skewY(float rad) {
	nvgSkewY((NVGcontext*)data, rad);
}

void Canvas::transform(const Mat2d& mat) {
	nvgTransform((NVGcontext*)data, mat.data[0], mat.data[1], mat.data[2], mat.data[3], mat.data[4], mat.data[5]);
}

void Canvas::setTransform(const Mat2d& mat) {
	nvgResetTransform((NVGcontext*)data);
	nvgTransform((NVGcontext*)data, mat.data[0], mat.data[1], mat.data[2], mat.data[3], mat.data[4], mat.data[5]);
}

void Canvas::resetTransform() {
	nvgResetTransform((NVGcontext*)data);
}

void Canvas::currentTransform(Mat2d* mat) {
	float xform[6];
	nvgCurrentTransform((NVGcontext*)data, xform);
	memcpy(mat->data, xform, sizeof(float) * 6);
}

void Canvas::save() {
	nvgSave((NVGcontext*)data);
}

void Canvas::restore() {
	nvgRestore((NVGcontext*)data);
}

void Canvas::reset() {
	nvgReset((NVGcontext*)data);
}

void Canvas::scissor(float x, float y, float w, float h) {
	nvgScissor((NVGcontext*)data, x, y, w, h);
}

void Canvas::intersectScissor(float x, float y, float w, float h) {
	nvgIntersectScissor((NVGcontext*)data, x, y, w, h);
}

void Canvas::resetScissor() {
	nvgResetScissor((NVGcontext*)data);
}

void Canvas::beginPath() {
	nvgBeginPath((NVGcontext*)data);
}

void Canvas::closePath() {
	nvgClosePath((NVGcontext*)data);
}

void Canvas::moveTo(float x, float y) {
	nvgMoveTo((NVGcontext*)data, x, y);
}

void Canvas::lineTo(float x, float y) {
	nvgLineTo((NVGcontext*)data, x, y);
}

void Canvas::bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y) {
	nvgBezierTo((NVGcontext*)data, c1x, c1y, c2x, c2y, x, y);
}

void Canvas::quadTo(float cx, float cy, float x, float y) {
	nvgQuadTo((NVGcontext*)data, cx, cy, x, y);
}

void Canvas::arcTo(float x1, float y1, float x2, float y2, float radius) {
	nvgArcTo((NVGcontext*)data, x1, y1, x2, y2, radius);
}

void Canvas::pathWinding(int dir) {
	nvgPathWinding((NVGcontext*)data, dir);
}

void Canvas::arc(float cx, float cy, float r, float a0, float a1, int dir) {
	nvgArc((NVGcontext*)data, cx, cy, r, a0, a1, dir);
}

void Canvas::rect(float x, float y, float w, float h) {
	nvgRect((NVGcontext*)data, x, y, w, h);
}

void Canvas::roundRect(float x, float y, float w, float h, float r) {
	nvgRoundedRect((NVGcontext*)data, x, y, w, h, r);
}

void Canvas::roundRectVarying(float x, float y, float w, float h, float rtl, float rtr, float rbr, float rbl) {
	nvgRoundedRectVarying((NVGcontext*)data, x, y, w, h, rtl, rtr, rbr, rbl);
}

void Canvas::ellipse(float cx, float cy, float rx, float ry) {
	nvgEllipse((NVGcontext*)data, cx, cy, rx, ry);
}

void Canvas::circle(float cx, float cy, float r) {
	nvgCircle((NVGcontext*)data, cx, cy, r);
}

void Canvas::fontBlur(float blur) {
	nvgFontBlur((NVGcontext*)data, blur);
}

void Canvas::fontFace(const char* name) {
	nvgFontFace((NVGcontext*)data, name);
}

void Canvas::fontSize(float size) {
	nvgFontSize((NVGcontext*)data, size);
}

void Canvas::textLetterSpacing(float spacing) {
	nvgTextLetterSpacing((NVGcontext*)data, spacing);
}

void Canvas::texLineHeight(float lineHeight) {
	nvgTextLineHeight((NVGcontext*)data, lineHeight);
}

void Canvas::textAlign(int align) {
	nvgTextAlign((NVGcontext*)data, align);
}

void Canvas::text(float x, float y, const char* string) {
	nvgText((NVGcontext*)data, x, y, string, nullptr);
}

float Canvas::textBounds(float x, float y, const char* string, const char* end, float* bounds) {
	return nvgTextBounds((NVGcontext*)data, x, y, string, end, bounds);
}

TextMetrics Canvas::textMetrics()
{
	TextMetrics tm;
	nvgTextMetrics((NVGcontext*)data, &tm.ascender, &tm.descender, &tm.lineh);
	return tm;
}

void Canvas::drawImage(Image* img, float x, float y, float alpha) {
	if (!img || img->_img == 0) return;
	NVGcontext* vg = (NVGcontext*)data;
	int w = 0, h = 0;
	nvgImageSize(vg, img->_img, &w, &h);
	NVGpaint paint = nvgImagePattern(vg, x, y, (float)w, (float)h, 0, img->_img, alpha);
	nvgBeginPath(vg);
	nvgRect(vg, x, y, (float)w, (float)h);
	nvgFillPaint(vg, paint);
	nvgFill(vg);
}

void Canvas::drawImageAtRect(Image* img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, float alpha) {
	if (!img || img->_img == 0) return;
	NVGpaint paint = nvgImagePattern((NVGcontext*)data, dx, dy, dw, dh, 0, img->_img, alpha);
	nvgBeginPath((NVGcontext*)data);
	nvgRect((NVGcontext*)data, dx, dy, dw, dh);
	nvgFillPaint((NVGcontext*)data, paint);
	nvgFill((NVGcontext*)data);
}

void Canvas::linearGradient(bool fill, float sx, float sy, float ex, float ey, int icolor, int ocol) {
	NVGpaint p = nvgLinearGradient((NVGcontext*)data, sx, sy, ex, ey, mkNVGColorByInt(icolor), mkNVGColorByInt(ocol));
	if (fill) nvgFillPaint((NVGcontext*)data, p); else nvgStrokePaint((NVGcontext*)data, p);
}

void Canvas::boxGradient(bool fill, float x, float y, float w, float h, float r, float f, int icol, int ocol) {
	NVGpaint p = nvgBoxGradient((NVGcontext*)data, x, y, w, h, r, f, mkNVGColorByInt(icol), mkNVGColorByInt(ocol));
	if (fill) nvgFillPaint((NVGcontext*)data, p); else nvgStrokePaint((NVGcontext*)data, p);
}

void Canvas::radialGradient(bool fill, float cx, float cy, float inr, float outr, int icol, int ocol) {
	NVGpaint p = nvgRadialGradient((NVGcontext*)data, cx, cy, inr, outr, mkNVGColorByInt(icol), mkNVGColorByInt(ocol));
	if (fill) nvgFillPaint((NVGcontext*)data, p); else nvgStrokePaint((NVGcontext*)data, p);
}

void Canvas::imagePattern(bool fill, float ox, float oy, float ex, float ey, float angle, Image* image, float alpha) {
	if (!image || image->_img == 0) return;
	NVGpaint p = nvgImagePattern((NVGcontext*)data, ox, oy, ex, ey, angle, image->_img, alpha);
	if (fill) nvgFillPaint((NVGcontext*)data, p); else nvgStrokePaint((NVGcontext*)data, p);
}

int Canvas::_createImageRGBA(int w, int h, int imgFlags, const unsigned char* imgData) {
	return nvgCreateImageRGBA((NVGcontext*)data, w, h, imgFlags, imgData);
}

Ref<Image> Canvas::createImageRGBA(int w, int h, const unsigned char* imgData) {
	Ref<Image> img{new Image()};
	img->_img = _createImageRGBA(w, h, 0, imgData);
	return img;
}

int Canvas::_createImage(const char* path) {
	return nvgCreateImage((NVGcontext*)data, path, 0);
}

Ref<Image> Canvas::createImage(const char* path) {
	Ref<Image> img{new Image()};
	img->_img = _createImage(path);
	if (img->_img) return img;
	return nullptr;
}

Canvas* Canvas::getInstance()
{
	return gCanvas;
}

