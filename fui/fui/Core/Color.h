#pragma once

#include "Predef.h"
#include "Vec2.h"

struct Vec3;

struct Rgbaf {
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 0;

	std::string toString() const;
	Vec3 toVec3() const;
	struct Rgba toRgba() const;
	int toInt() const;
};

struct Rgba {
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 0;

	int toInt() const {
		return (a << 24) | (r << 16) | (g << 8) | (b << 0);
	}
	std::string toString() const {
		char tmp[200];
		snprintf(tmp, sizeof(tmp), "rgba(%d,%d,%d,%d)", r, g, b, a);
		return std::string(tmp);
	}
};

struct Hsla {
	float h = 0;
	float s = 0;
	float l = 0;
	unsigned char a = 0;

	struct Rgba toRgba() const;
	int toRgbaInt() const;
	std::string toString() const {
		char tmp[200];
		snprintf(tmp, sizeof(tmp), "hsla(%.4f,%.4f,%.4f,%d)", h, s, l, a);
		return std::string(tmp);
	}
};

struct Hsva {
	float h = 0;
	float s = 0;
	float v = 0;
	unsigned char a = 0;

	struct Rgba toRgba() const;
	int toRgbaInt() const;
	std::string toString() const {
		char tmp[200];
		snprintf(tmp, sizeof(tmp), "hsva(%.4f,%.4f,%.4f,%d)", h, s, v, a);
		return std::string(tmp);
	}
};

inline Rgbaf mkRgbaf0() {
	Rgbaf ret;
	return ret;
}

inline Rgbaf mkRgbaf(float r, float g, float b, float a) {
	Rgbaf ret;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	ret.a = a;
	return ret;
}

inline Rgbaf mkRgbafByInt(int color) {
	Rgbaf v;
	v.a = (float)(((color) >> 24) & 0xFF) / 255.0f;
	v.r = (float)(((color) >> 16) & 0xFF) / 255.0f;
	v.g = (float)(((color) >> 8) & 0xFF) / 255.0f;
	v.b = (float)(((color) >> 0) & 0xFF) / 255.0f;
	return v;
}

inline Rgba mkRgba0() {
	Rgba ret;
	return ret;
}

inline Rgba mkRgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	Rgba ret;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	ret.a = a;
	return ret;
}

inline Rgba mkRgbaByFloat(float r, float g, float b, float a) {
	Rgba ret;
	ret.r = (unsigned char)(r * 255.0f);
	ret.g = (unsigned char)(g * 255.0f);
	ret.b = (unsigned char)(b * 255.0f);
	ret.a = (unsigned char)(a * 255.0f);
	return ret;
}

inline Rgba mkRgbaByInt(int color) {
	Rgba rgba;
	rgba.a = (((color) >> 24) & 0xFF);
	rgba.r = (((color) >> 16) & 0xFF);
	rgba.g = (((color) >> 8) & 0xFF);
	rgba.b = (((color) >> 0) & 0xFF);
	return rgba;
}

inline int mkIntByRgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	return (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

inline unsigned char colorGetA(int color) { return (((color) >> 24) & 0xFF); }
inline unsigned char colorGetR(int color) { return (((color) >> 16) & 0xFF); }
inline unsigned char colorGetG(int color) { return (((color) >> 8) & 0xFF); }
inline unsigned char colorGetB(int color) { return (((color) >> 0) & 0xFF); }

inline NVGcolor mkNVGColorByInt(int color) {
	unsigned char a = (((color) >> 24) & 0xFF);
	unsigned char r = (((color) >> 16) & 0xFF);
	unsigned char g = (((color) >> 8) & 0xFF);
	unsigned char b = (((color) >> 0) & 0xFF);
	return nvgRGBA(r, g, b, a);
}

Hsla rgbaToHsla(Rgba rgba);
Hsva rgbaToHsva(Rgba rgb);
Rgba hsvaToRgba(Hsva hsv);

inline Hsva mkHsvaByInt(int color) {
	Rgba r = mkRgbaByInt(color);
	return rgbaToHsva(r);
}
inline Hsva mkHsva_byInt(int color) { return mkHsvaByInt(color); }
inline Hsva mkHsva(float h, float s, float v, unsigned char a) {
	Hsva ret; ret.h = h; ret.s = s; ret.v = v; ret.a = a; return ret;
}
inline Hsla mkHsla(float h, float s, float l, unsigned char a) {
	Hsla ret; ret.h = h; ret.s = s; ret.l = l; ret.a = a; return ret;
}

inline Rgba Hsva::toRgba() const {
	return hsvaToRgba(*this);
}

inline int Hsva::toRgbaInt() const {
	return toRgba().toInt();
}

inline Rgba Hsla::toRgba() const {
	NVGcolor c = nvgHSLA(h, s, l, a);
	return mkRgbaByFloat(c.r, c.g, c.b, c.a);
}

inline int Hsla::toRgbaInt() const {
	return toRgba().toInt();
}
