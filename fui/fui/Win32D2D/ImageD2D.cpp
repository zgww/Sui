#include "Image.h"
#include <d2d1.h>

Vec2 Image::size() {
	return mkVec2(width(), height());
}

float Image::width() {
	if (!bitmap) {
		return 0;
	}
	D2D1_SIZE_F s = ((ID2D1Bitmap*)bitmap)->GetSize();
	return s.width;
}

float Image::height() {
	if (!bitmap) {
		return 0;
	}
	D2D1_SIZE_F s = ((ID2D1Bitmap*)bitmap)->GetSize();
	return s.height;
}