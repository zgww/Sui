package SuiView

#include <stdio.h>
#include "../../nanovg/nanovg.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Bezier.orc"
import * from "../Core/Inset.orc"
import * from "../Core/Global.orc"
import * from "../Core/Canvas.orc"
import * from "../Core/Frame.orc"
import * from "../Core/Node.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Map.orc"
import * from "./ViewBuilder.orc"
import * from "../Core/Image.orc"
import type * from "../../SuiDesigner/Inspector.orc"



enum ImageMode {
	WrapContent, //使用图处宽高
	WidthFix, //定宽
	HeightFix, //定高
	Contain, //定宽高，内容缩小至完全显示
	Cover, //定宽高，内容放大至完全占满
	Fill, //定宽高，拉伸
}


class  ImageModeCalc {

	Rect getSrcRect(){
		return mkRect(self.sx, self.sy, self.sw, self.sh);
	}
	Rect getDstRect(){
		return mkRect(self.dx, self.dy, self.dw, self.dh);
	}

	int sw = 0;
	int sh = 0;
	int dw = 0;
	int dh = 0;

	int sx = 0;
	int sy = 0;
	int dx = 0;
	int dy = 0;
	float sr = 0.f;
	float dr = 0.f;
	float scale = 1.f
	void calc(
		int sw, int sh, int dw, int dh, ImageMode mode
	){
		self->sw = sw;
		self->sh = sh;
		self->dw = dw;
		self->dh = dh;
 
		if (sw == 0 || sh == 0 || dw == 0 || dh == 0) {
			return;
		}
		self.sr = sw / (float)sh;
		self.dr = dw / (float)dh;

		if (mode == Cover) {
			self.calc_cover();
		}
		else if (mode == Contain) {
			self.calc_contain();
		}

	}
	void calc_contain(){
		float w_scale = self.dw / (float)self.sw;
		float h_scale = self.dh / (float)self.sh;
		float scale = minFloat(w_scale, h_scale);
		float tw = scale * self.sw;
		float th = scale * self.sh;
		self.dx = (self.dw - tw) / 2.f;
		self.dy = (self.dh - th) / 2.f;
		self.dw = tw;
		self.dh = th;
		self.scale = scale
	}
	void calc_cover(){
		float w_scale = self.sw / (float)self.dw;
		float h_scale = self.sh / (float)self.dh;
		float scale = minFloat(w_scale, h_scale);
		float tw = scale * self.dw;
		float th = scale * self.dh;
		self.sx = (self.sw - tw) / 2.f;
		self.sy = (self.sh - th) / 2.f;
		self.sw = tw;
		self.sh = th;
		self.scale = scale
	}
}

/// 布局上下文
class ImageView extends View {
	Bezier bezier = mkBezier();
	Vec2 pos;
	float ratio = 10.0
	void setRatio(float v){
		self.ratio = v
		printf("set ratio:%f\n", self.ratio)
	}
	void onInspect(Inspector *insp){
		insp.markAttrAsImageSrc("src")
		insp.markAttrAsSlider("ratio", 10, 20)
		// insp.markAttrAsFileSrc("src")
		// insp.markAttrAsSelect("imageMode").{
		// 	o.setOption(WrapContent, "WrapContent")
		// 	o.setOption(WidthFix, "WidthFix")
		// 	o.setOption(HeightFix, "HeightFix")
		// 	o.setOption(Contain, "Contain")
		// 	o.setOption(Cover, "Cover")
		// 	o.setOption(Fill, "Fill")
		// }
	}

	void layout(Frame* ctx) {
		ctx.incTimesInOneLayout()
		
		// if (self._isImageValid()) {
		// 	if (self.cb && self.cb.cbLayout(self, ctx)) {
		// 		return;
		// 	}
		// }

		//根据自身的宽高声明，进一步约束
		self.updateFrame_forSelfWidthHeight(ctx);

		//默认情况
		self.initLayoutSize(ctx);



		if (self.cb && self.cb.cbLayout(self, ctx)) {
			return;
		}

		if (self._isImageValid()) {
			if (self.imageMode == WrapContent) {
				ctx->setSize(
					self._img->width() + self.margin.hor(),
					self._img->height() + self.margin.ver());
			}
			else if (self.imageMode == WidthFix) {
				// //根据自身的宽高声明，进一步约束
				// self.updateFrame_forSelfWidthHeight(ctx);

				// //默认情况
				// self.initLayoutSize(ctx);
				ctx->setHeight(
					self._img->height() / self._img->width() * ctx->width
				);
			}
			else if (self.imageMode == HeightFix) {
				ctx->setWidth(
					self._img->width() / self._img->height() * ctx->height
				);
			}
		}

		//imageview的大小不受子视图影响
		Frame tmp = *ctx;
        self.layoutContent_fromOutBox(&tmp)

		//叠加margin
		ctx->setSize(
			ctx->width + self.margin.hor(),
			ctx->height + self.margin.ver()
		);
	}
	String@ src = str("");

	// String@ _loaded_src = str("");
	// bool _src_loaded = false;

	//SkImage img;
	ImageMode imageMode = WrapContent;

	ImageModeCalc@ calc = new ImageModeCalc();

	Image@ _img = NULL
	// sk_sp<SkImage> _img = NULL;

	// Trace trace;

	//static void registerMeta();

	// static sk_sp<SkImage> loadImageFromPath(string filepath);

	//static Ref<SkBitmap> loadBitmapFromPath(string filepath);

	//virtual void measure(int w, int w_mode, int h, int h_mode) {
	//}
	void setSrc(String@ src){
		if (self.src && src && self->src.equals(src.str)) {
			return
		}

		//printf("aload src:%s\n", src.c_str());
		self->src = src;
		if (src){
			self._img = loadImage(src.str)
		}
		else {
			self._img = null
		}
		// ImgHolder::aload(src)
		// 	->then(
		// 		CLOSURE([=](Ref<GcObj> obj) {

		// 			auto imgholder = dynamic_cast<ImgHolder*>(obj.get());
		// 			this->_img = imgholder->img;

		// 			printf("加载图片完成:%s 在线程%s  设置到imageview\n", src.c_str(), ThreadUtil::get_thread_id().c_str());
		// 			//Window::markDirtyByView(this);
		// 			invalidLayout();
				
		// 		}, this)
		// 	);
	}
	void setImageMode(ImageMode mode){
		if (self.imageMode != mode) {
			self->imageMode = mode;
			self.invalidLayout();
		}
	}
	bool _isImageValid(){
		return self._img != NULL;
	}

	// void _loadImageIfNeed(){
	// 	if 
	// 	self.src 
	// 	&& self.src.notEmpty() 
	// 	&& !self._src_loaded {

	// 		self._src_loaded = true
	// 		self._img = loadImage(self.src.str)
	// 		self._loaded_src = self.src
	// 	}
	// }


	void draw_self(Canvas* canvas) {


		super.draw_self(canvas);
		if (self._isImageValid()) {
			//ImageModeCalc@ calc = new ImageModeCalc();

			Rect r = self.getViewRect()
			float w = r.w;// taitank::get_taitank_node_layout_width(yg);
			float h = r.h;// taitank::get_taitank_node_layout_height(yg);
			self.calc.calc(
				self._img->width(), self._img->height(),
				w, h, self.imageMode
			);
			// NVGpaint paint = nvgImagePattern(vg, calc.sx, calc.sy, calc.sw, calc.sh, 0.f, self._img._img, 1.f)
			// nvgFillPaint(vg, paint);
			// nvgBeginPath(vg)
			// nvgRect(vg, calc.dx, calc.dy, calc.dw, calc.dh);

			drawImage_atRect(canvas, self._img, 
				self.calc.sx, self.calc.sy, self.calc.sw, self.calc.sh, 
				self.calc.dx, self.calc.dy, self.calc.dw, self.calc.dh);
			canvas.fill();
			// SkRect src; 
			// src.setXYWH(calc.sx, calc.sy, calc.sw, calc.sh);
			// SkRect dst;
			// dst.setXYWH(calc.dx, calc.dy, calc.dw, calc.dh);
			// SkSamplingOptions opt{SkFilterMode::kLinear};
			// canvas->drawImageRect(_img, src, dst, opt, nullptr, SkCanvas::kFast_SrcRectConstraint);
		}

	}
}

//此函数用来在nvg支持类似于skia的  绘制源图像 某区域 到目标区域的功能。
void drawImage_atRect(Canvas *canvas, Image* imgId, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh) {
    int imgW = imgId.width()
	int  imgH = imgId.height();
    // nvgImageSize(vg, imgId, &imgW, &imgH);
    float wscale = dw / sw;
    float hscale = dh / sh;
    float imgScaleW = imgW * wscale   ;
    float imgScaleH = imgH * hscale;

    float ox = -sx * wscale + dx;
    float oy = -sy * hscale + dy;

    //创建图片笔刷。  ex,ey表示图片缩放到目标宽高
    canvas.imagePattern(true, ox, oy, imgScaleW, imgScaleH, 0.f, imgId, 1.f);
    // nvgFillPaint(vg, paint);

    canvas.beginPath();
    canvas.rect( dx, dy, dw, dh);
}



ImageView@ mkImageView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (ImageView@)gocNode(sp, (Node*)parent, ImageView)
}