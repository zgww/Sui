package SuiView
#include <stdio.h>
#include "../../Orc/Orc.h"

#include "../../nanovg/nanovg.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Node.orc"
import * from "../Core/Event.orc"
import * from "../Core/Color.orc"
import * from "../View/Drag.orc"
import * from "../Core/Canvas.orc"
import * from "./ViewBuilder.orc"
import * from "../Core/MouseEvent.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Timer.orc"
import * from "../../Orc/Math.orc"


/// 布局上下文
class ProgressView extends View {

	float value = 0.0
	float valueForAnim = 0.0
	AnimStep@ anim = null

	void ctor(){
		self.backgroundColor = 0xffefefef
		self.width = 200
		self.height = 6
		// self.react()

		self.setValue(0.6)
	}
	void startValueAnim(){
		if (self.anim == null){
			self.anim = new AnimStep()
		}
		self.anim.start(^void(){
			self.valueForAnim = self.anim.next(self.valueForAnim, self.value, 0.05)
			self.invalidDraw()
		})
	}

	void setValue(float v){
		if (self.value == v){
			return
		}
		self.value = v
		self.invalidDraw()
		self.startValueAnim()
	}

	void draw_self(Canvas *canvas){
		super.draw_self(canvas)

		float w = self.frame.width

		//绘制进度
		canvas.fillColorByInt32( (0xff1677ff));
		canvas.beginPath()
		canvas.rect( 0, 0, w * self.valueForAnim, self.frame.height)
		canvas.fill()
	}


}

ProgressView@ mkProgressView(void* parent, long long key){
    return (ProgressView@)gocNode(
		key ? (void*)key : __builtin_return_address(0) , 
		(Node*)parent, ProgressView)
}