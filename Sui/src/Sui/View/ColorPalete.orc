package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Node.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Image.orc"
import * from "../Core/Color.orc"
import * from "../Core/Canvas.orc"
import * from "../Core/Event.orc"
import * from "../Core/MouseEvent.orc"
import * from "../View/TextView.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/String.orc"
import * from "./Drag.orc"
import * from "./ViewBuilder.orc"



static char *new_createChessBg_inMemory(int w, int h, int r, int g, int b, int a){
	char *data = malloc(w * h * 4)
	int hw = w / 2
	int hh = h / 2

	for (int y = 0; y < h; y++){
		for (int x = 0; x < w; x++){
			int i = (y * w + x) * 4
			data[i] = r
			data[i + 1] = g
			data[i + 2] = b
			data[i + 3] = (x < hw && y < hh) || (x >= hw && y >= hh)? a : 0
		}
	}

	return data
}
static Image* gocChessBgImage(Canvas *canvas){
	static Image@ img = null
	if (img == null){
		int w = 16
		int h = 16

		char *imgData = new_createChessBg_inMemory(w, h, 
			128, 128, 128, 255) 

		img = canvas.createImageRGBA(w, h, (const unsigned char *)imgData)

		free(imgData)
	}
	return img
}
/// 颜色盘
class ColorPalete extends View {
	// 都是归一化的0-1值. 原点在左下角
	Vec2 indicatorPos = mkVec2(0, 0)
	Drag@ drag = new Drag()

	//sv的主色
	int color = 0xffff0000

	bool xDraggale = true
	bool yDraggale = true
	//sv|alpha|hue
	String@ kind = str("sv")
	// circle|rect
	String@ indicatorKind = str("rect");
	// bool rect = false;
	^void (Vec2 ratio) onChanged = null

	Vec2 calcIndicatorPosInPixel(){
		Rect r = self.getContentLocalRect()
		return mkVec2(
			r.w * self.indicatorPos.x,
			r.h * (1.0 - self.indicatorPos.y),
		)
	}

	void onEvent(Event *e){
		if (e instanceof MouseEvent){
			self.onMouseEvent((MouseEvent*)e)
		}
	}
	void onMouseEvent(MouseEvent *me){
		if (me.isMouseDown){
			self.drag.onDrag = ^void (Drag *d){
				self.onDrag(d)
			}
			self.drag.onMouseDown(me)
		}
	}
	void onDrag(Drag *d){
		if (d.isDragging || d.isDragStart || d.isDragChecking){
			Rect r = self.getContentLocalRect()
			Vec2 pos = self.calcIndicatorPosInPixel()

			int tox = pos.x + d.deltaPos.x
			int toy = pos.y + d.deltaPos.y

			{
				Rect r = self.getContentClientRect()
				tox = d.currentClientPos.x - r.x
				toy = d.currentClientPos.y - r.y
				printf("tox:%d, toy:%d cur:%f, %f, r:%f,%f\n", 
				tox, toy, 
				d.currentClientPos.x,
				d.currentClientPos.y,
				r.x, r.y)
			}

			printf("tox:%d, toy:%d\n", tox, toy)
			tox = clampInt(tox, 0, r.w)
			toy = clampInt(toy, 0, r.h)

			float xRatio = 0
			if r.w > 0 {
				xRatio = tox / r.w
			}
			float yRatio = 0
			if r.h > 0 {
				yRatio = toy / r.h
			}

			if (self.xDraggale){
				self.indicatorPos.x = xRatio
			}
			if (self.yDraggale){
				self.indicatorPos.y = 1.0 - yRatio
			}

			if self.onChanged{
				self.onChanged(self.indicatorPos)
			}

			self.invalidDraw()
		}
	}

	//色盘
	void drawCircle(Canvas *canvas, int x, int y){
		// Marker on
		canvas.strokeWidth( 2.0f);
		canvas.beginPath();
		// nvgRect(vg, -2, y - h / 2, w + 4, h)
		canvas.circle( x, y, 4);
		canvas.strokeColor( 255,255,255,192)
		canvas.stroke();
	}
	//色盘
	void drawMark(Canvas *canvas, int w, int y){
		int h = 8
		// Marker on
		canvas.strokeWidth( 2.0f);
		canvas.beginPath();
		canvas.rect( -2.f, y - h / 2, w+4.f, h)
		canvas.strokeColor( 255,255,255,192);
		canvas.stroke();
	}
	void drawHue(Canvas *canvas, int w, int h){
		// w = 20
		float seg = h / 6.0
		for (int i = 0; i < 6; i++){
			float y = i * seg
			canvas.beginPath()
			canvas.rect(0, y, w, seg+(i == 5 ? 0 : 1))

			canvas.linearGradient(true,
				0, y, 
				0, y + seg,
				mkHsla(1.0 - (i / 6.0), 1.0f, 0.55, 255).toRgbaInt(), 
				mkHsla(1.0 - ((i + 1) / 6.0), 1.0f, 0.55, 255).toRgbaInt()
			)
			canvas.fill()
		}
	}
	//透明度
	void drawAlpha(Canvas *canvas, int w, int h){
		canvas.beginPath()
		// nvgFillColor(vg, nvgRGBA(255, 0, 0, 255))
		// nvgRoundedRect(vg, 0, 0, w, h, 15)
		canvas.rect( 0, 0, w, h)

		Image* bg = gocChessBgImage(canvas)
		//绘制背景
		canvas.imagePattern(
			true,
			0, 0, 16, 16, 0, bg, 1
		)
		// nvgFillPaint(vg, bp)	
		canvas.fill()


		// NVGpaint lg = nvgLinearGradient(vg, 
		// 	0.0, 0.0, 0.0, h, 
		// 	nvgRGBA(255, 255, 255, 255),
		// 	// nvgRGBA(255, 255, 255, 0),
		// 	nvgRGBA(0, 0, 0, 200),
		// )
		// nvgFillPaint(vg, lg)

		canvas.linearGradient(true,
			0.0, 0.0, 0.0, h, 
			mkIntByRgba(255, 255, 255, 255),
			// nvgRGBA(255, 255, 255, 0),
			mkIntByRgba(0, 0, 0, 200),
		)
		canvas.fill()
	}
	//饱和度和亮度
	void drawSv(Canvas *canvas, int w, int h){
		canvas.beginPath()
		// nvgFillColor(vg, nvgRGBA(255, 0, 0, 255))
		// nvgRoundedRect(vg, 0, 0, w, h, 15)
		canvas.rect(0, 0, w, h)

		// nvgFillColor(vg, nvgRGBA(255, 0, 0, 255))
		canvas.fillColorByInt32(self.color)
		canvas.fill()

		// NVGpaint lg = nvgLinearGradient(vg, 
		// 	0.0, 0.0, w, 0.0,
		// 	nvgRGBA(255, 255, 255, 255),
		// 	nvgRGBA(255, 255, 255, 0),
		// )
		// nvgFillPaint(vg, lg)
		canvas.linearGradient(true,
			0.0, 0.0, w, 0.0,
			mkIntByRgba(255, 255, 255, 255),
			mkIntByRgba(255, 255, 255, 0),
		)
		canvas.fill()

		{
			// NVGpaint lg = nvgLinearGradient(vg, 
			// 	0.0, 0.0, 0.0, h,
			// 	nvgRGBA(0, 0, 0, 0),
			// 	nvgRGBA(0, 0, 0, 255),
			// )
			// nvgFillPaint(vg, lg)
			canvas.linearGradient(true,
				0.0, 0.0, 0.0, h,
				mkIntByRgba(0, 0, 0, 0),
				mkIntByRgba(0, 0, 0, 255),
			)
			canvas.fill()
		}
	}
	void draw_self(Canvas *canvas){
		Rect r = self.getContentLocalRect()
		int w = r.w
		int h = r.h

		self.backgroundColor = 0xff000000

		super.draw_self(canvas)

		if self.kind.equals("sv") {
			self.drawSv(canvas, w, h)
		}
		if self.kind.equals("alpha") {
			self.drawAlpha(canvas, w, h)
		}
		if self.kind.equals("hue") {
			self.drawHue(canvas, w, h)
		}

		Vec2 indiPos = self.calcIndicatorPosInPixel()
		if self.indicatorKind.equals("rect") {
			self.drawMark(canvas, w, indiPos.y)
		}
		if self.indicatorKind.equals("circle") {
			self.drawCircle(canvas, indiPos.x, indiPos.y)
		}

	}
}

class ColorView extends LayoutLinear {

	// int color = 0;
	Hsva hsva = mkHsva(0.0, 1.0, 1.0, 255);
	bool showRgba = true
	bool showHsva = false
	bool showHsla = false

	^void (int newcolor) onChanged;

	void fire_onChanged(){
		if self.onChanged {
			int color = self.hsva.toRgbaInt()
			self.onChanged(color)
		}
	}

	// void ctor(){
	// 	super.ctor()

	// 	// Hsla sv = mkHsla(0.5, 0.5, 0.5, 255)

	// 	// self.color = c
	// }
	void setColor(int c){
		// self.color = c
		Rgba rgba = mkRgbaByInt(c)
		self.hsva = rgbaToHsva(rgba)
	}
	void draw_self(Canvas *canvas){
		super.draw_self(canvas)
	}
	void react(){
		self.startInnerReact()
		ColorView* o = self;


		Hsva sv = mkHsva(self.hsva.h, 1.0, 1.0, 255)
		int svColor = sv.toRgbaInt()

		self.direction.set("column")
		self.alignItems.set("stretch")

		layoutLinear(o, 0).{
			mkColorPalete(o, 0).{
				o.indicatorPos.set(self.hsva.s, self.hsva.v)

				o.color = svColor
				o.kind = str("sv")
				o.indicatorKind = str("circle")
				o.width = 200
				o.height = 200
				// o.margin.left = 100
				o.margin.right = 6  
				o.onChanged = ^void (Vec2 ratio){
					printf("ratio:%f,%f\n", ratio.x, ratio.y)
					self.hsva.s = ratio.x
					self.hsva.v = ratio.y

					self.fire_onChanged()

					// self.color = hsva.toRgbaInt()
					self.trigger_react()
				}
			}
			mkColorPalete(o, 0).{
				o.indicatorPos.y = self.hsva.h / 360.0
				printf("hue:%f\n", self.hsva.h)

				o.kind = str("hue")
				o.width = 20
				o.height = 200
				o.margin.right = 6  
				o.onChanged = ^void (Vec2 ratio){
					self.hsva.h = ratio.y * 360.0
					printf("hue ratio:%f,%f. hue:%f\n", ratio.x, ratio.y, self.hsva.h)


					self.fire_onChanged()
					// self.color = self.hsva.toRgbaInt()
					self.trigger_react()
				}
			}
			mkColorPalete(o, 0).{
				o.indicatorPos.y = self.hsva.a / 255.0

				o.kind = str("alpha")
				o.width = 20
				o.height = 200
				o.onChanged = ^void (Vec2 ratio){

					// hsla.a = ratio.y * 255.0
					// rgba.a = ratio.y * 255.0
					self.hsva.a = ratio.y * 255.0


					self.fire_onChanged()
					printf("alpha ratio:%f,%f. alpha:%d\n", ratio.x, ratio.y, self.hsva.a)
					// self.color = rgba.toInt()
					self.trigger_react()
				}
			}
		}
		layoutLinear(o, 0).{
			mkView(o, 0).{
				o.backgroundColor = self.hsva.toRgbaInt()
				o.width = 16
				o.height = 16
				o.border.setAll(1, 0xff000000)
				o.padding.setAll(1)
				o.margin.setVer(6)
				o.margin.right = 6
			}
			layoutLinear(o, 0).{
				o.direction.set("column")
				o.alignItems.set("start")
				if self.showHsva {
					mkTextView(o, 0).{
						String@ s = self.hsva.toString()
						o.setText(s)
					}
				}
				if self.showRgba {
					mkTextView(o, 0).{
						Rgba r = self.hsva.toRgba()
						String@ s = r.toString()
						o.setText(s)
					}
				}
				if self.showHsla {
					mkTextView(o, 0).{
						Rgba r = self.hsva.toRgba()
						Hsla hsl = rgbaToHsla(r)

						String@ s = hsl.toString()
						o.setText(s)
					}
				}
			}
		}
		
		self.endInnerReact()
	}
}

ColorPalete@ mkColorPalete(void* parent, long long key){
    return (ColorPalete@)gocNode(
		key ? (void*)key: __builtin_return_address(0)
		, (Node*)parent, ColorPalete)
}
ColorView@ mkColorView(void* parent, long long key){
    return (ColorView@)gocNode(
		key ? (void*)key: __builtin_return_address(0)
		, (Node*)parent, ColorView)
}