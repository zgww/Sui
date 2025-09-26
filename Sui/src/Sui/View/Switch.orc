package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"

import * from "../Core/Node.orc"
import * from "../Core/View.orc"
import * from "../Core/Event.orc"
import * from "../Core/Timer.orc"
import * from "./ViewBuilder.orc"
import * from "../Core/MouseEvent.orc"


/// 布局上下文
class Switch extends View {
	View@ circle = new View()
	bool checked = false
	AnimStep@ anim = new AnimStep();

	int circleSize = 14

	void ctor(){
		self.width = 34
		self.height = 20
		self.appendChild(self.circle)

		self.circle.width = self.circleSize
		self.circle.height = self.circleSize
		self.circle.frame.x = self.calcToX()
	}
	void react(){
		self.radius.setAll(10)
		
		self.backgroundColor = self.checked ? 0xff1677ff : 0x40000000;

		int d = (self.height - self.circle.height) / 2
		self.circle.frame.y = d
		self.circle.backgroundColor = 0xffffffff
		self.circle.radius.setAll(7)

		if self.isNewForReact {
			self.circle.frame.x = self.calcToX()
			self.isNewForReact = false
		}
		else {
			// printf("Switch react new frame:%f %f\n", self.frame.x, self.calcToX());
			self.anim.start(^void(){
				float toX = self.calcToX()
				self.circle.frame.x = self.anim.nextByMs(
					self.circle.frame.x, toX, 140)
				// printf("new frame:%f toX:%f\n", self.circle.frame.x, toX);
				self.invalidDraw()
			})
		}
	}

	float calcToX(){
		int d = (self.height - self.circle.height) / 2
		float toX = !self.checked ? d : self.width - d - self.circle.width
		return toX
	}


	void setChecked(bool v){
		if (v == self.checked){
			return;
		}
		self.checked = v

		if (self.onCheckedChanged){
			self.onCheckedChanged(self)
		}


		self.react()
		self.invalidLayout()
	}

	^void (Switch *ins) onCheckedChanged
	

	void onEvent(Event *ev){
		if (ev instanceof MouseEvent){
			MouseEvent *me = (MouseEvent*)ev
			if (me.isClickInBubble()){
				// printf("la\n")
				self.setChecked(!self.checked)
				ev.stopPropagation()
			}
		}
	}
}
Switch@ mkSwitch(void* parent, long long key){
    return (Switch@)gocNode(key ? (void*)key:__builtin_return_address(0) , 
		(Node*)parent, Switch)
}