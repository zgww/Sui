#pragma once

#include "Predef.h"
#include "Mat2d.h"
#include "Image.h"
#include "Color.h"

// 文本对齐标志（水平/垂直可组合）
enum CanvasAlign {
	CANVAS_ALIGN_LEFT = 1 << 0,
	CANVAS_ALIGN_CENTER = 1 << 1,
	CANVAS_ALIGN_RIGHT = 1 << 2,

	CANVAS_ALIGN_TOP = 1 << 3,
	CANVAS_ALIGN_MIDDLE = 1 << 4,
	CANVAS_ALIGN_BOTTOM = 1 << 5,
	CANVAS_ALIGN_BASELINE = 1 << 6,
};

// 路径绕向
enum CanvasWinding {
	CANVAS_CCW = 1,		// 实心形状
	CANVAS_CW = 2,		// 挖洞
};

// 线帽
enum CanvasLineCap {
	CANVAS_CAP_BUTT = 0,
	CANVAS_CAP_ROUND = 1,
	CANVAS_CAP_SQUARE = 2,
};

// 线连接
enum CanvasLineJoin {
	CANVAS_JOIN_MITER = 0,
	CANVAS_JOIN_ROUND = 1,
	CANVAS_JOIN_BEVEL = 2,
};

class TextMetrics {
public:
	float ascender;
	float descender;
	float lineh;
};

class Canvas : public GcObj {
public:
	void* data = nullptr;

	Canvas();
	virtual ~Canvas();
	void init();

	// Direct2D后端: 将画布绑定到原生窗口（创建渲染目标）
	void bindWindow(void* hwnd);
	// Direct2D后端: 解除窗口绑定并释放渲染目标
	void unbindWindow();

	void beginFrame(float w, float h, float devicePixelRatio);
	void endFrame();
	void cancelFrame();

	void globalAlpha(float alpha);
	void stroke();
	void fill();

	void strokeColorByInt32(int c);
	void fillColorByInt32(int c);
	void fillColor(int r, int g, int b, int a);
	void strokeColor(int r, int g, int b, int a);
	void strokeWidth(float width);

	// 阴影 (类似 HTML5 canvas shadow)
	void shadowColor(int r, int g, int b, int a);
	void shadowOffset(float x, float y);
	void shadowBlur(float blur);

	void shapeAntiAlias(int enabled);
	void lineJoin(int join);
	void lineCap(int cap);

	void translate(float x, float y);
	void scale(float x, float y);
	void rotate(float rad);
	void skewX(float rad);
	void skewY(float rad);

	void transform(const Mat2d& mat);
	void setTransform(const Mat2d& mat);
	void resetTransform();
	void currentTransform(Mat2d* mat);

	void save();
	void restore();
	void reset();

	void scissor(float x, float y, float w, float h);
	void intersectScissor(float x, float y, float w, float h);
	void resetScissor();

	void beginPath();
	void closePath();
	void moveTo(float x, float y);
	void lineTo(float x, float y);
	void bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y);
	void quadTo(float cx, float cy, float x, float y);
	void arcTo(float x1, float y1, float x2, float y2, float radius);

	void pathWinding(int dir);

	void arc(float cx, float cy, float r, float a0, float a1, int dir);
	void rect(float x, float y, float w, float h);
	void roundRect(float x, float y, float w, float h, float r);
	void roundRectVarying(float x, float y, float w, float h, float rtl, float rtr, float rbr, float rbl);
	void ellipse(float cx, float cy, float rx, float ry);
	void circle(float cx, float cy, float r);

	void fontBlur(float blur);
	void fontFace(const char* name);
	void fontSize(float size);
	void textLetterSpacing(float spacing);
	void texLineHeight(float lineHeight);
	void textAlign(int align);
	void text(float x, float y, const char* string);
	float textBounds(float x, float y, const char* string, const char* end, float* bounds);
	TextMetrics textMetrics();

	void drawImage(Image* img, float x, float y, float alpha);
	void drawImageAtRect(Image* img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, float alpha);

	void linearGradient(bool fill, float sx, float sy, float ex, float ey, int icolor, int ocol);
	void boxGradient(bool fill, float x, float y, float w, float h, float r, float f, int icol, int ocol);
	void radialGradient(bool fill, float cx, float cy, float inr, float outr, int icol, int ocol);
	void imagePattern(bool fill, float ox, float oy, float ex, float ey, float angle, Image* image, float alpha);

	Ref<Image> createImageRGBA(int w, int h, const unsigned char* imgData);
	Ref<Image> createImage(const char* path);

	static Canvas* getInstance();
};

