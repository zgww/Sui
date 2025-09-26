package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"


import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Node.orc"
import * from "../Core/Event.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Color.orc"
import * from "../Core/MouseEvent.orc"
import * from "../View/ImageView.orc"
import * from "../Core/Canvas.orc"
import * from "../View/TextView.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "./ViewBuilder.orc"
//import * from "../Core/Radius.orc"
import * from "../Core/Inset.orc"   

import * from "../../SuiDesigner/Inspector.orc"

/// 布局上下文
class Button extends LayoutLinear {

	void ctor(){
		self.cursor = str("pointer")
	}

	void react() {  
		self.cursor.set("pointer")
		self.direction.set("row")
		self.justifyContent.set("center")
		self.alignItems.set("center")
		self.radius.setAll(6)
		self.padding.setAxis(5, 16)

		Node * o = (Node*)self;


		self.startInnerReact();
		if (self.src != null){
			mkImageView(o, 0).{ 
				o.setSrc(self.src) 
			}
		}


		if (self.label != null){
			mkTextView(o, 0).{
				o.color = self.labelColor
				o.setText(self.label)
			}
		}

		self.endInnerReact();
		// clearUnusedKids((Node*)self);
	}
	int labelColor = 0xffffffff;
	void onEvent(Event *ev){
		if (ev instanceof MouseEnterEvent){
			self.backgroundColor = 0xffff8888
			self.labelColor = 0xff0000ff
			self.react()
			self.invalidDraw()
		}
		if (ev instanceof MouseLeaveEvent){
			self.backgroundColor = 0xffff0000
			self.labelColor = 0xffffffff
			self.react()
			self.invalidDraw()
		}
		if (ev instanceof MouseEvent){
			MouseEvent *me = (MouseEvent*)ev
			if (me.isClickInBubble()){
				//if (self.clickListener){
					//self.clickListener.onEvent(me);
				//}
				if (self.onClick){
					self.onClick(me)
				}

			}
		}
		if (ev instanceof ViewEvent){

			ViewEvent *ve = (ViewEvent*)ev

			// printf("Button.onEvent: %s isCapture:%d\n", Object_getClassName(ev), ve.isCapture)

		}
	}

	// bool inspect(LineKeep* lk) 

	//bool checked = false; 
	// Ref<Closure<void()>> ontap{ nullptr, this };

	// Ref<TextView> tv{ 0, this };

	String@ label= str("submit");
    void setLabel(String@ v){ 
		if (v != self.label) {
			self->label = v; 
			//invalidLayout();
			self.trigger_react();
		}
	}

	String@ src = null;
    void setSrc(String@ v){ 
		if (v != self.src) {
			self->src = v;
			//invalidLayout();
			self.trigger_react();
		}
	}

	bool in_group = false;
    void setIn_group(bool v){ 
		if (v != self.in_group) {
			self->in_group = v;

			self.trigger_react();
			//invalidLayout();
		}
	}

	bool checked = false;
    void setChecked(bool v){ 
		if (v != self.checked) {
			self->checked = v;
			self.trigger_react();
			//invalidLayout();
		}
	}

	//MouseEventListener@ clickListener = null;
	^void (MouseEvent *me) onClick = null
}


class DrawButton extends LayoutLinear{
	String@ text = null;
	String@ src = null;

	int hoverBg = 0x8f9c9c9c//nvgRGBA(156,156,156,100)
	int normalBg = 0xef9c9c9c //nvgRGBA(156,156,156,200)


	// void onInspect(Inspector *insp){
	// 	// super.onInspect();

	// 	insp.color("hoverBg")
	// 	insp.path("hoverBg")
	// 	insp.image("hoverBg")
	// 	insp.box("").{
	// 		insp.render("hover")
	// 	}
	// 	insp.attrColo("hoverBg").box()
	// 	insp.attrColo("src").endBox()


	// 	insp.markAttrAsColor("hoverBg")
	// 	insp.markAttrAsColor("normalBg")


	// 	Node *o = insp.parentNode
	// 	// mkTextView(parent, 0).{
	// 	// 	o.setText(str("from onInspect"))
	// 	// }


	// 	layoutLinear(o, 0).{
	// 		// o.height = 30
	// 		o.backgroundColor = 0x114493f3
	// 		o.padding.setAll(6)
	// 		String@ btnsStr = str("购物车,arrow-down")
	// 		List@ btns = btnsStr.splitByRe(",")

	// 		for (int i = 0; i < btns.size(); i++){
	// 			String@ btn = (String@)btns.get(i)   
	// 			mkDrawButton(o, i).{
	// 				String@ path = str("asset/icon/")
	// 				path.addString(btn).add(".png")

	// 				o.src = path
	// 				o.onClick =^void(MouseEvent *me){
	// 					me.stopPropagation()
	// 				}
	// 			}
	// 		}
	// 	}

	// }
	void ctor(){
		// self.minWidth = 40
		self.padding.setHor(8)
		self.height = 30
		self.justifyContent.set("center")
		self.alignItems.set("center")
		self.cursor.set("pointer")
	}
	void onHoverChanged(){
		self.invalidReact()
		self.invalidDraw()
	}
	void react(){
		self.startInnerReact()
		if (self.src){
			mkImageView(self, 0).{
				o.width = 20
				o.height = 20
				o.setSrc(self.src)
			}
		}
		if (self.text){
			mkTextView(self, 0).{
				o.setText(self.text)
				o.color = self.hover ? 0xffffffff: 0x99ffffff
			}
		}
		self.endInnerReact()
	}

    void draw_self(Canvas *canvas){
        Rect vr = self.getViewRect()
		int x = 0
		int y = 0
		int w = vr.w
		int h = vr.h
		int cornerRadius = 5

		int r = 156
		int g = 156
		int b = 156
		// NVGpaint bg = nvgLinearGradient(vg, x,y,x,y+h, 
		// 	self.hover ? nvgRGBA(r,g,b,100) : nvgRGBA(r,g,b,128), 
		// 	self.hover ? nvgRGBA(r,g,b,160) : nvgRGBA(r,g,b,200),
		// );
		canvas.fillColorByInt32(
			(self.hover? self.hoverBg : self.normalBg));
		canvas.beginPath();
		canvas.roundRect(x+1,y+1, w-2,h-2, cornerRadius-1);
		//if (!isBlack(col)) {
			//nvgFillColor(vg, col);
			//nvgFill(vg);
		//}
		// nvgFillPaint(vg, bg);
		canvas.fill();
    }
	void onEvent(Event *ev){
		if (ev instanceof MouseEvent){
			MouseEvent *me = (MouseEvent*)ev
			if (me.isClickInBubble()){
				if (self.onClick){
					self.onClick(me)
				}
			}
		}
		if (ev instanceof ViewEvent){

			ViewEvent *ve = (ViewEvent*)ev

			// printf("Button.onEvent: %s isCapture:%d\n", Object_getClassName(ev), ve.isCapture)

		}
	}
	^void(MouseEvent *me) onClick = null
}

class MenuButton extends LayoutLinear{
	String@ text = null;

	int normalBackgroundcolor = 0x00999999;
	int hoverBackgroundcolor = 0x33999999;


	void ctor(){
		// self.minWidth = 40
		self.padding.setHor(8)
		self.justifyContent.set("center")
		self.alignItems.set("center")
		self.cursor.set("pointer")
	}

	void dtor(){
		printf("~MenuButton:%s. %p\n", self.text ? self.text.str:"(null text)", self);
	}

	void onHoverChanged(){
		self.invalidReact()
		self.invalidDraw()
	}
	void draw(void *canvas){
		self.backgroundColor = self.hover ? self.hoverBackgroundcolor: self.normalBackgroundcolor
		super.draw(canvas)
	}
	void react(){
		// self.backgroundColor = self.hover ? 0x33999999: 0x00999999
		// self.backgroundColor = self.hover ? self.hoverBackgroundcolor: self.normalBackgroundcolor
		// self.border.setAll(1, self.hover ? 0x66999999: 0)

		self.startInnerReact()

		if (self.text){
			mkTextView(self, 0).{
				o.setFont_size(12)
				o.setText(self.text)
				o.color = self.hover ? 0xffffffff: 0x99ffffff
			}
		}
		self.endInnerReact()
	}

	void onEvent(Event *ev){
		if (ev instanceof MouseEvent){
			MouseEvent *me = (MouseEvent*)ev
			//已触发的状态下，可以使用move 就能激活
			// printf("MenuButton. mouseMove:%d. group:%p. triggering:%p self:%p\n",
			// me.isMouseMove,
			//  self.group, self.group.triggeringMenuButton, self);
			if (me.isMouseMove){

				if (self.onMouseMove){
					self.onMouseMove(me)
				}
			}
			if (me.isClickInBubble()){
				if (self.onClick){
					self.onClick(me)
				}
			}
		}
		if (ev instanceof ViewEvent){

			ViewEvent *ve = (ViewEvent*)ev

			// printf("Button.onEvent: %s isCapture:%d\n", Object_getClassName(ev), ve.isCapture)

		}
	}
	^void(MouseEvent *me) onClick = null
	^void(MouseEvent *me) onMouseMove = null
}

Button@ mkButton(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (Button@)gocNode(sp, (Node*)parent, Button)
}


DrawButton@ mkDrawButton(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (DrawButton@)gocNode(sp, (Node*)parent, DrawButton)
}
MenuButton@ mkMenuButton(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (MenuButton@)gocNode(sp, (Node*)parent, MenuButton)
}