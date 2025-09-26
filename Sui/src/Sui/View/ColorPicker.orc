package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Node.orc"
import * from "../Core/Window.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Color.orc"
import * from "../Core/Canvas.orc"
import * from "../Core/Event.orc"
import * from "../Dialog/Toast.orc"
import * from "../Core/MouseEvent.orc"
import * from "../View/TextView.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/String.orc"
import * from "./Drag.orc"
import * from "./ColorPalete.orc"
import * from "./ViewBuilder.orc"


/// 颜色盘
class ColorPicker extends View {
	// int value = 0xff000000;

	^void (int newcolor) onChanged;

	void fire_onChanged(int newcolor){
		if self.onChanged {
			self.onChanged(newcolor)
		}

	}

	void ctor(){
		super.ctor()
		self.width = 14
		self.height = 14
		self.border.setAll(2, 0xffffffff)
		self.backgroundColor = 0xff00ff00
	}

	void showWindow_colorPalete(){
		Window@ win = new Window()
		win.{
			new LayoutLinear().{
				win.setRootView(o)

				o.direction.set("column")
				o.alignItems.set("center")
				// o.justifyContent.set("center")
				o.padding.setAll(8)

				// mkTextView(o, 0).{
				// 	o.setText(str("你好"))
				// }
				mkColorView(o, 0).{
					if o.isNewForReact {
						o.hsva = mkHsva_byInt(self.backgroundColor)
					}
					o.onChanged = ^ void (int c){
						self.backgroundColor = c
						self.fire_onChanged(c)
						self.invalidDraw()
					}
				}
			}

			o.setOwner(self.getWindow())
			o.setTitle("ColorPicker")
			o.setSize(300, 300)
			o.moveToCenter()
			o.show()
		}
	}

	void onEvent(Event *e){
		if (e instanceof MouseEvent){
			self.onMouseEvent((MouseEvent*)e)
		}
	}
	void onMouseEvent(MouseEvent *me){
		if me.isClickInBubble(){
			self.showWindow_colorPalete()
			// Toast_make("HI")
			// self.drag.onDrag = ^void (Drag *d){
			// 	self.onDrag(d)
			// }
			// self.drag.onMouseDown(me)
		}
	}

	// void onDrag(Drag *d){
	// 	if (d.isDragging || d.isDragStart || d.isDragChecking){
	// 		Rect r = self.getContentLocalRect()
	// 		Vec2 pos = self.calcIndicatorPosInPixel()

	// 		int tox = pos.x + d.deltaPos.x
	// 		int toy = pos.y + d.deltaPos.y

	// 		{
	// 			Rect r = self.getContentClientRect()
	// 			tox = d.currentClientPos.x - r.x
	// 			toy = d.currentClientPos.y - r.y
	// 			printf("tox:%d, toy:%d cur:%f, %f, r:%f,%f\n", 
	// 			tox, toy, 
	// 			d.currentClientPos.x,
	// 			d.currentClientPos.y,
	// 			r.x, r.y)
	// 		}

	// 		printf("tox:%d, toy:%d\n", tox, toy)
	// 		tox = clampInt(tox, 0, r.w)
	// 		toy = clampInt(toy, 0, r.h)

	// 		float xRatio = 0
	// 		if r.w > 0 {
	// 			xRatio = tox / r.w
	// 		}
	// 		float yRatio = 0
	// 		if r.h > 0 {
	// 			yRatio = toy / r.h
	// 		}

	// 		if (self.xDraggale){
	// 			self.indicatorPos.x = xRatio
	// 		}
	// 		if (self.yDraggale){
	// 			self.indicatorPos.y = 1.0 - yRatio
	// 		}

	// 		if self.onChanged{
	// 			self.onChanged(self.indicatorPos)
	// 		}

	// 		self.invalidDraw()
	// 	}
	// }

}

ColorPicker@ mkColorPicker(void* parent, long long key){
    return (ColorPicker@)gocNode(
		key ? (void*)key: __builtin_return_address(0)
		, (Node*)parent, ColorPicker)
}