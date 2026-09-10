#include "Color.h"
#include "Vec2.h"

#include <rttr/registration>

std::string Rgbaf::toString() const {
	char buf[256];
	snprintf(buf, sizeof(buf), "Rgbaf(%f,%f,%f,%f)", r, g, b, a);
	return std::string(buf);
}

Rgba Rgbaf::toRgba() const {
	Rgba ret;
	ret.r = (unsigned char)(r * 255.0f);
	ret.g = (unsigned char)(g * 255.0f);
	ret.b = (unsigned char)(b * 255.0f);
	ret.a = (unsigned char)(a * 255.0f);
	return ret;
}

int Rgbaf::toInt() const {
	return toRgba().toInt();
}

Hsla rgbaToHsla(Rgba rgba) {
	unsigned char red = rgba.r;
	unsigned char green = rgba.g;
	unsigned char blue = rgba.b;
	unsigned char alpha = rgba.a;

	double r = red / 255.0;
	double g = green / 255.0;
	double b = blue / 255.0;

	double maxVal = maxDouble(maxDouble(r, g), b);
	double minVal = minDouble(minDouble(r, g), b);

	double h = 0.0;
	double s = 0.0;
	double l = 0.0;
	l = (maxVal + minVal) / 2.0;

	if (maxVal == minVal) {
		h = 0.0;
		s = 0.0;
	} else {
		double d = maxVal - minVal;
		s = l > 0.5 ? d / (2.0 - maxVal - minVal) : d / (maxVal + minVal);

		if (maxVal == r) {
			h = (g - b) / d + (g < b ? 6.0 : 0.0);
		} else if (maxVal == g) {
			h = (b - r) / d + 2.0;
		} else {
			h = (r - g) / d + 4.0;
		}
		h *= 60.0;
	}

	Hsla ret;
	ret.h = (float)h;
	ret.s = (float)s;
	ret.l = (float)l;
	ret.a = alpha;
	return ret;
}

Hsva rgbaToHsva(Rgba rgb) {
	float maxv = 0.0f;
	float minv = 0.0f;
	float delta = 0.0f;
	float r = (float)((int)rgb.r) / 255.0f;
	float g = (float)((int)rgb.g) / 255.0f;
	float b = (float)((int)rgb.b) / 255.0f;
	float h = 0.0f;
	float s = 0.0f;
	float v = 0.0f;

	maxv = maxFloat(maxFloat(r, g), b);
	minv = minFloat(minFloat(r, g), b);
	delta = (maxv - minv);

	if (delta == 0) {
		h = 0;
	} else {
		if (r == maxv) {
			h = ((g - b) / delta) * 60.0f;
		} else if (g == maxv) {
			h = 120.0f + (((b - r) / delta) * 60.0f);
		} else if (b == maxv) {
			h = 240.0f + (((r - g) / delta) * 60.0f);
		}
		if (h < 0) {
			h += 360.0f;
		}
	}

	if (maxv == 0) {
		s = 0;
	} else {
		s = (float)(delta / maxv);
	}

	v = maxv;

	Hsva ret;
	ret.h = h;
	ret.s = s;
	ret.v = v;
	ret.a = rgb.a;
	return ret;
}

Rgba hsvaToRgba(Hsva hsv) {
	int i = 0;
	float f = 0.0f;
	float a = 0.0f;
	float b = 0.0f;
	float c = 0.0f;
	Rgba rgb;
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	rgb.a = hsv.a;

	float h = hsv.h;
	float s = hsv.s;
	float v = hsv.v;
	if (h >= 360.0f) {
		h = 0.0f;
	}

	if (s == 0) {
		rgb.r = (unsigned char)((int)(v * 255.0f));
		rgb.g = (unsigned char)((int)(v * 255.0f));
		rgb.b = (unsigned char)((int)(v * 255.0f));
	} else {
		h /= 60.0f;
		i = (int)floorf(h);
		f = h - i;
		a = v * (1.0f - s);
		b = v * (1.0f - s * f);
		c = v * (1.0f - s * (1.0f - f));
		if (i == 0) {
			rgb.r = (unsigned char)((int)(v * 255.0f));
			rgb.g = (unsigned char)((int)(c * 255.0f));
			rgb.b = (unsigned char)((int)(a * 255.0f));
		} else if (i == 1) {
			rgb.r = (unsigned char)((int)(b * 255.0f));
			rgb.g = (unsigned char)((int)(v * 255.0f));
			rgb.b = (unsigned char)((int)(a * 255.0f));
		} else if (i == 2) {
			rgb.r = (unsigned char)((int)(a * 255.0f));
			rgb.g = (unsigned char)((int)(v * 255.0f));
			rgb.b = (unsigned char)((int)(c * 255.0f));
		} else if (i == 3) {
			rgb.r = (unsigned char)((int)(a * 255.0f));
			rgb.g = (unsigned char)((int)(b * 255.0f));
			rgb.b = (unsigned char)((int)(v * 255.0f));
		} else if (i == 4) {
			rgb.r = (unsigned char)((int)(c * 255.0f));
			rgb.g = (unsigned char)((int)(a * 255.0f));
			rgb.b = (unsigned char)((int)(v * 255.0f));
		} else {
			rgb.r = (unsigned char)((int)(v * 255.0f));
			rgb.g = (unsigned char)((int)(a * 255.0f));
			rgb.b = (unsigned char)((int)(b * 255.0f));
		}
	}
	return rgb;
}

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Rgbaf>("Rgbaf")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Rgbaf(*)(float, float, float, float)>(&mkRgbaf))
		.constructor(static_cast<Rgbaf(*)(int)>(&mkRgbafByInt))
		.property("r", &Rgbaf::r)
		.property("g", &Rgbaf::g)
		.property("b", &Rgbaf::b)
		.property("a", &Rgbaf::a)
		.method("toString", &Rgbaf::toString)
		.method("toRgba", &Rgbaf::toRgba)
		.method("toInt", &Rgbaf::toInt);

	registration::class_<Rgba>("Rgba")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Rgba(*)(unsigned char, unsigned char, unsigned char, unsigned char)>(&mkRgba))
		.constructor(static_cast<Rgba(*)(int)>(&mkRgbaByInt))
		.property("r", &Rgba::r)
		.property("g", &Rgba::g)
		.property("b", &Rgba::b)
		.property("a", &Rgba::a)
		.method("toInt", &Rgba::toInt)
		.method("toString", &Rgba::toString);

	registration::class_<Hsla>("Hsla")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Hsla(*)(float, float, float, unsigned char)>(&mkHsla))
		.property("h", &Hsla::h)
		.property("s", &Hsla::s)
		.property("l", &Hsla::l)
		.property("a", &Hsla::a)
		.method("toRgba", &Hsla::toRgba)
		.method("toRgbaInt", &Hsla::toRgbaInt)
		.method("toString", &Hsla::toString);

	registration::class_<Hsva>("Hsva")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Hsva(*)(float, float, float, unsigned char)>(&mkHsva))
		.property("h", &Hsva::h)
		.property("s", &Hsva::s)
		.property("v", &Hsva::v)
		.property("a", &Hsva::a)
		.method("toRgba", &Hsva::toRgba)
		.method("toRgbaInt", &Hsva::toRgbaInt)
		.method("toString", &Hsva::toString);
}
