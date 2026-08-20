#pragma once

#include "Predef.h"
#include "Mat2d.h"
#include "Image.h"
#include "Color.h"

class Canvas : public GcObj {
public:
	void* data = nullptr;

	Canvas();
	virtual ~Canvas();
	void init();

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

	void drawImage(Image* img, float x, float y, float alpha);
	void drawImageAtRect(Image* img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh, float alpha);

	void linearGradient(bool fill, float sx, float sy, float ex, float ey, int icolor, int ocol);
	void boxGradient(bool fill, float x, float y, float w, float h, float r, float f, int icol, int ocol);
	void radialGradient(bool fill, float cx, float cy, float inr, float outr, int icol, int ocol);
	void imagePattern(bool fill, float ox, float oy, float ex, float ey, float angle, Image* image, float alpha);

	int _createImageRGBA(int w, int h, int imgFlags, const unsigned char* imgData);
	Ref<Image> createImageRGBA(int w, int h, const unsigned char* imgData);
	int _createImage(const char* path);
	Ref<Image> createImage(const char* path);

	static Canvas* getInstance();
};

