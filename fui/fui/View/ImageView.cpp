#include "ImageView.h"
#include "../Core/Window.h"


void ImageView::setSrc(std::string src) {
	if (this->src == src) {
		return;
	}
	this->src = src;
	if (!src.empty()) {

		auto canvas = Canvas::getInstance();
		if (canvas) {
			_img = canvas->createImage(src.c_str());
		}
	}
	else {
		_img = nullptr;
	}
}

void ImageView::setImageMode(ImageMode mode) {
	if (this->imageMode != mode) {
		this->imageMode = mode;
		this->invalidLayout();
	}
}

//此函数用来在nvg支持类似于skia的  绘制源图像 某区域 到目标区域的功能。
void drawImage_atRect(Canvas* canvas, Image* imgId, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh) {
	int imgW = imgId->width();
		int  imgH = imgId->height();
	// nvgImageSize(vg, imgId, &imgW, &imgH);
	float wscale = dw / sw;
	float hscale = dh / sh;
	float imgScaleW = imgW * wscale;
	float imgScaleH = imgH * hscale;

	float ox = -sx * wscale + dx;
	float oy = -sy * hscale + dy;

	//创建图片笔刷。  ex,ey表示图片缩放到目标宽高
	canvas->imagePattern(true, ox, oy, imgScaleW, imgScaleH, 0.f, imgId, 1.f);
	// nvgFillPaint(vg, paint);

	canvas->beginPath();
	canvas->rect(dx, dy, dw, dh);
}

void ImageModeCalc::calc(int sw, int sh, int dw, int dh, ImageMode mode) {
	this->sw = (float)sw;
	this->sh = (float)sh;
	this->dw = (float)dw;
	this->dh = (float)dh;

	if (sw == 0.f || sh == 0.f || dw == 0.f || dh == 0.f) {
		return;
	}
	this->sr = sw / (float)sh;
	this->dr = dw / (float)dh;

	if (mode == ImageMode_Cover) {
		calc_cover();
	}
	else if (mode == ImageMode_Contain) {
		calc_contain();
	}
}

void ImageModeCalc::calc_contain() {
	float w_scale = dw / (float)sw;
	float h_scale = dh / (float)sh;
	float scale = minFloat(w_scale, h_scale);
	float tw = scale * this->sw;
	float th = scale * this->sh;
	this->dx = ((this->dw - tw) / 2.f);
	this->dy = ((this->dh - th) / 2.f);
	this->dw = tw;
	this->dh = th;
	this->scale = scale;
}

void ImageModeCalc::calc_cover() {
	float w_scale = sw / (float)dw;
	float h_scale = sh / (float)dh;
	float scale = minFloat(w_scale, h_scale);
	float tw = scale * dw;
	float th = scale * dh;
	this->sx = (int)((this->sw - tw) / 2.f);
	this->sy = (int)((this->sh - th) / 2.f);
	this->sw = (int)tw;
	this->sh = (int)th;
	this->scale = scale;
}

void ImageView::layout(Frame* ctx) {
	ctx->incTimesInOneLayout();

	this->updateFrame_forSelfWidthHeight(ctx);

	//默认情况
	this->initLayoutSize(ctx);


	if (this->cb && cb->cbLayout(this, ctx)) {
		return;
	}

	if (this->_isImageValid()) {
		if (this->imageMode == ImageMode_WrapContent) {
			ctx->setSize(
				this->_img->width() + this->margin.hor(),
				this->_img->height() + this->margin.ver());
		}
		else if (this->imageMode == ImageMode_WidthFix) {
			// //根据自身的宽高声明，进一步约束
			// self.updateFrame_forSelfWidthHeight(ctx);

			// //默认情况
			// self.initLayoutSize(ctx);
			ctx->setHeight(
				this->_img->height() / this->_img->width() * ctx->width
			);
		}
		else if (this->imageMode == ImageMode_HeightFix) {
			ctx->setWidth(
				this->_img->width() / this->_img->height() * ctx->height
			);
		}
	}

	//imageview的大小不受子视图影响
	Frame tmp = *ctx;
	this->layoutContent_fromOutBox(&tmp);

	//叠加margin
	ctx->setSize(
		ctx->width + this->margin.hor(),
		ctx->height + this->margin.ver()
	);
}

void ImageView::draw_self(Canvas* canvas) {
	View::draw_self(canvas);
	if (_isImageValid()) {
		//ImageModeCalc@ calc = new ImageModeCalc();

		Rect r = getViewRect();
		float w = r.w;// taitank::get_taitank_node_layout_width(yg);
		float h = r.h;// taitank::get_taitank_node_layout_height(yg);
		calc.calc(
			_img->width(), _img->height(),
			w, h, imageMode
		);
		// NVGpaint paint = nvgImagePattern(vg, calc.sx, calc.sy, calc.sw, calc.sh, 0.f, self._img._img, 1.f)
		// nvgFillPaint(vg, paint);
		// nvgBeginPath(vg)
		// nvgRect(vg, calc.dx, calc.dy, calc.dw, calc.dh);

		drawImage_atRect(canvas, _img,
			calc.sx, calc.sy, calc.sw, calc.sh,
			calc.dx, calc.dy, calc.dw, calc.dh);
		canvas->fill();
		// SkRect src; 
		// src.setXYWH(calc.sx, calc.sy, calc.sw, calc.sh);
		// SkRect dst;
		// dst.setXYWH(calc.dx, calc.dy, calc.dw, calc.dh);
		// SkSamplingOptions opt{SkFilterMode::kLinear};
		// canvas->drawImageRect(_img, src, dst, opt, nullptr, SkCanvas::kFast_SrcRectConstraint);
	}

}