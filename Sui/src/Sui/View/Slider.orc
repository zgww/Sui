package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Node.orc"
import * from "../Core/Event.orc"
import * from "../Core/Color.orc"
import * from "../Core/Frame.orc"
import * from "../View/Drag.orc"
import * from "./ViewBuilder.orc"
import * from "../Core/MouseEvent.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Canvas.orc"
import * from "../../Orc/Math.orc"


/// 布局上下文
class Slider extends View {
	View@ circle = new View()
	float ratio = 0.5
	float fromValue = 0
	float toValue = 1
	// float value = self.ratio

	Drag@ drag = new Drag()

	^void (float v) onChanged;
	void fire_onChanged(){
		if self.onChanged {
			float v = self.getValue()
			self.onChanged(v)
		}
	}

	void layoutContent(Frame *f){
		Frame tmp = *f
		super.layoutContent(f);
		//不受子节点的影响
		*f = tmp
	}

	void setRatioByValue(float value){
		self.ratio = (value - self.fromValue) / (self.toValue - self.fromValue)
	}

	float getValue(){
		return (self.toValue - self.fromValue) * self.ratio + self.fromValue
	}


	void ctor(){
		// self.backgroundColor = 0xffefefef
		// self.width = 200
		self.height = 16
		self.appendChild(self.circle)

		self.circle.width = 16
		self.circle.height= 16
		self.circle.frame.x = self.calcToX()
		self.react()
	}
	float calcToX(){
		Rect r = self.getViewRect()
		float x = r.w * self.ratio
		return x - self.circle.width / 2.0
	}
	float calcToY(){
		return self.frame.height / 2.0 -self.circle.frame.height / 2.0
	}
    void draw_self(Canvas *canvas){
		super.draw_self(canvas)

		//更新circle的位置
		self.circle.frame.x = self.calcToX()
		self.circle.frame.y = self.calcToY()

		float barH = 6
		Rect r = self.getViewRect()
		float w = r.w
		// float w = self.frame.width
		float y = (self.frame.height - barH) / 2.0

		
		//绘制进度条
        // nvgFillColor(vg, mkNVGColorByInt(0xffe1e1e1));
        canvas.fillColorByInt32( (0x33000000));
        canvas.beginPath()
        canvas.rect( 0, y, w, barH)
        canvas.fill()

		//绘制底条
        canvas.fillColorByInt32( (
			0xff1677ff
		));
		// 0xff1230ff
        canvas.beginPath()
        canvas.rect( 0, y, w * self.ratio, barH)
        canvas.fill()
    }
	void react(){
		// self.radius.setAll(15)

		// self.circle.layoutCtx.y = 0
		self.circle.backgroundColor = 0xffffffff
		self.circle.radius.setAll(11)
		self.circle.border.setAll(4, 0xff1677ff)
	}
	void setRatio(float v){
		self.ratio = v
		self.invalidDraw()
	}

	void onEvent(Event *ev){
		if (ev instanceof MouseEvent){
			MouseEvent *me = (MouseEvent*)ev
			if (me.isBubble() && me.isMouseDown){
				self.drag.onMouseDown(me)
				self.drag.onDrag = ^void (Drag *d){
					Rect r = self.getViewRect_baseClient()
					// Rect r = self.get_abs_rect()
					float v = (d.currentClientPos.x - r.x) / r.w
					printf("ondrag...v:%f, w:%f\n", v, r.w)
					v = clampFloat(v, 0.0, 1.0)
					self.setRatio(v)
				}
			}
		}
	}
}

Slider@ mkSlider(void* parent, long long key){
    return (Slider@)gocNode(key ? (void*)key:__builtin_return_address(0) , 
		(Node*)parent, Slider)
}