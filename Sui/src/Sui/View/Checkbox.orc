package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"

import * from "../../Orc/String.orc"
import * from "../Core/ViewBase.orc"
import * from "../View/ImageView.orc"
import * from "../Core/Node.orc"
import * from "../Core/Event.orc"
import * from "./ViewBuilder.orc"
import * from "../Core/MouseEvent.orc"


/// 布局上下文
class Checkbox extends ImageView {

	String@ onSrc = str("./checkbox-checked.png")
	String@ offSrc = str("./checkbox-unchecked.png");

	bool checked = false

	void ctor(){
		self.setChecked(false)
	}

	void setChecked(bool v){
		self.checked = v
		if (self.checked){
			if (self.onSrc != null){
				self.setSrc(self.onSrc)
			}
		} else {
			if (self.offSrc != null){
				self.setSrc(self.offSrc)
			}
		}
		printf("setChecked:%d\n", self.checked);
		self.invalidLayout()
	}

	void onEvent(Event *ev){
		if (ev instanceof ViewEvent){
			ViewEvent *ve = (ViewEvent*)ev

			printf("Button.onEvent: %s isCapture:%d\n", Object_getClassName(ev), ve.isCapture)
			if (ev instanceof MouseEvent){
				MouseEvent *me = (MouseEvent*)ev
				if (me.isClick() && !me.isCapture){
					self.setChecked(!self.checked)
					me.stopPropagation()
				}
			}
		}
	}
}

Checkbox@ checkbox(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (Checkbox@)gocNode(sp, (Node*)parent, Checkbox)
}