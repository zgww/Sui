#include "Image.h"
#include "nanovg/nanovg.h"
#include "Canvas.h"

Vec2 Image::size() {
	return mkVec2(width(), height());
}

float Image::width() {
	if (_img == 0) {
		return 0;
	}
	int w = 0;
	int h = 0;
	auto canvas = Canvas::getInstance();
	if (canvas) {
		nvgImageSize((NVGcontext*)canvas->data, _img, &w, &h);
		return (float)w;
	}
	return -1.0f;
}

float Image::height() {
	if (_img == 0) {
		return 0;
	}
	int w = 0;
	int h = 0;

	auto canvas = Canvas::getInstance();
	if (canvas) {
		nvgImageSize((NVGcontext*)canvas->data, _img, &w, &h);
		return (float)h;
	}
	return -1.0f;
}
