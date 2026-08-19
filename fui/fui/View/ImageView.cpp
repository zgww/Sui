#include "ImageView.h"
#include "../Core/Window.h"

void ImageView::setSrc(const std::string& s) {
	if (src == s) return;
	src = s;
	if (s.empty()) {
		_img = nullptr;
	} else {
		Window* win = getWindow();
		if (win && win->canvas && win->canvas->data) {
			_img = win->canvas->createImage(s.c_str());
		}
	}
	invalidLayout();
}

void ImageView::setImageMode(ImageMode mode) {
	if (imageMode != mode) {
		imageMode = mode;
		invalidLayout();
	}
}

bool ImageView::isImageValid() {
	return _img != nullptr && _img->_img != 0;
}

void ImageView::layout(Frame* ctx) {
	updateFrame_forSelfWidthHeight(ctx);
	initLayoutSize(ctx);

	if (isImageValid()) {
		Window* win = getWindow();
		if (win && win->canvas && win->canvas->data) {
			NVGcontext* vg = (NVGcontext*)win->canvas->data;
			int iw = 0, ih = 0;
			nvgImageSize(vg, _img->_img, &iw, &ih);
			float imgW = (float)iw;
			float imgH = (float)ih;

			if (imageMode == ImageMode_WrapContent) {
				ctx->setSize(imgW, imgH);
			} else if (imageMode == ImageMode_WidthFix) {
				float h = ctx->width > 0 ? ctx->width * imgH / imgW : imgH;
				ctx->setSize(ctx->width, h);
			} else if (imageMode == ImageMode_HeightFix) {
				float w = ctx->height > 0 ? ctx->height * imgW / imgH : imgW;
				ctx->setSize(w, ctx->height);
			} else if (imageMode == ImageMode_Contain || imageMode == ImageMode_Cover) {
				float availW = ctx->maxWidth == infinity ? imgW : ctx->maxWidth;
				float availH = ctx->maxHeight == infinity ? imgH : ctx->maxHeight;
				float scale = imageMode == ImageMode_Contain
					? minFloat(availW / imgW, availH / imgH)
					: maxFloat(availW / imgW, availH / imgH);
				ctx->setSize(imgW * scale, imgH * scale);
			} else if (imageMode == ImageMode_Fill) {
				// use constraints as-is
			}
		}
	}

	layoutContent_fromOutBox(ctx);
	ctx->saveConstraints();
}

void ImageView::draw_self(Canvas* canvas) {
	View::draw_self(canvas);

	if (!isImageValid() || !canvas || !canvas->data) return;

	Vec2 size = getSizeWithoutMargin();
	float w = size.x;
	float h = size.y;

	NVGcontext* vg = (NVGcontext*)canvas->data;
	int iw = 0, ih = 0;
	nvgImageSize(vg, _img->_img, &iw, &ih);
	float imgW = (float)iw;
	float imgH = (float)ih;

	if (imgW <= 0 || imgH <= 0) return;

	if (imageMode == ImageMode_Fill) {
		canvas->drawImageAtRect(_img, 0, 0, imgW, imgH, 0, 0, w, h, 1.0f);
	} else if (imageMode == ImageMode_Contain || imageMode == ImageMode_Cover) {
		float scale = imageMode == ImageMode_Contain
			? minFloat(w / imgW, h / imgH)
			: maxFloat(w / imgW, h / imgH);
		float dw = imgW * scale;
		float dh = imgH * scale;
		float dx = (w - dw) / 2.0f;
		float dy = (h - dh) / 2.0f;
		canvas->drawImageAtRect(_img, 0, 0, imgW, imgH, dx, dy, dw, dh, 1.0f);
	} else {
		canvas->drawImage(_img, 0, 0, 1.0f);
	}
}
