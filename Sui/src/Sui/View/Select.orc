
package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"

import * from "../Core/Node.orc"
import * from "../Core/View.orc"
import * from "../Core/Event.orc"
import * from "../Core/Timer.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Mouse.orc"
import * from "../Core/Cursor.orc"
import * from "./ViewBuilder.orc"
import * from "./TextView.orc"
import * from "./MenuNative.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "../Core/MouseEvent.orc"
import * from "../Dialog/MessageDialog.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"


/// 下拉框
class Select extends LayoutLinear {
    // String@ text = str("please select")
    bool isActive = false
    //List<String>
    List@ options = new List()
    int value = -1;

    ^void (int i, String@ label) onChanged;

    void fire_onChanged(){
        if self.onChanged {
            String@ label = self.options.get(self.value)
            self.onChanged(self.value, label)
        }
    }

    void ctor(){
		self.cursor = str("pointer")

        self.border.setAll(1, 0xff999999)
        self.radius.setAll(6)
        self.padding.setAxis(4, 8)
    }
    void appendOptionCStr(const char* text){
        if (text){
            self.options.add(str(text))
        }
    }
    void appendOption(String* text){
        if (text){
            self.options.add(text)
        }
    }
    void react(){
        self.startInnerReact()

        mkTextView(self, 0).{
            String@ text = (String@)self.options.get(self.value)
            o.setText(text == null ? str("please select") : text)
        }
        mkTextView(self, 0).{
            o.setText(
                self.isActive 
                ?  str(" ^ ")
                : str(" v ")
                )
        }

        self.endInnerReact()
    }

	// View@ circle = new View()
	// bool checked = false
	// AnimStep@ anim = new AnimStep();

	// int circleSize = 20

	// void ctor(){
	// 	self.width = 48
	// 	self.height = 26
	// 	self.appendChild(self.circle)

	// 	self.circle.width = self.circleSize
	// 	self.circle.height = self.circleSize
	// 	self.circle.frame.x = self.calcToX()
	// }
	// void react(){
	// 	self.radius.setAll(15)
		
	// 	self.backgroundColor = self.checked ? 0xff1677ff : 0x40000000;

	// 	int d = (self.height - self.circle.height) / 2
	// 	self.circle.frame.y = d
	// 	self.circle.backgroundColor = 0xffffffff
	// 	self.circle.radius.setAll(11)

	// 	printf("Switch react new frame:%f %f\n", self.frame.x, self.calcToX());
	// 	self.anim.start(^void(){
	// 		float toX = self.calcToX()
	// 		self.circle.frame.x = self.anim.nextByMs(
	// 			self.circle.frame.x, toX, 140)
	// 		printf("new frame:%f toX:%f\n", self.circle.frame.x, toX);
	// 		self.invalidDraw()
	// 	})
	// }

	// float calcToX(){
	// 	int d = (self.height - self.circle.height) / 2
	// 	float toX = !self.checked ? d : self.width - d - self.circle.width
	// 	return toX
	// }

	void setIsActive(bool v){
		self.isActive = v
		self.react()
		self.invalidLayout()
	}
    // void setText(String@ text){
    //     self.text = text == null ? str(""): text
    //     self.invalidReact()
    // }
    void setValue(int i){
        self.value = i
        // self.text = text == null ? str(""): text
        self.invalidReact()
    }

    void showPopupMenu(){
        self.setIsActive(true)

        ^void onActive(MenuNativeItem *item){
            printf("\n\nactive menu:%d, %s\n\n", item.id, 
            item.label == null ? "null": item.label.str);
            // self.setText(item.label)
            self.setValue(item.id)
            self.fire_onChanged()
        }

        mkMenuNativeItem(null, str(""), onActive).{
            for (int i = 0; i < self.options.size(); i++){
                String@ text = self.options.get(i)
                mkMenuNativeItem(o, text, onActive).{ o.id = i; }

            }
            // mkMenuNativeItem(o, str("menu1"), onActive).{ o.id = 0; }
            // mkMenuNativeItem(o, str("menu2"), onActive).{ o.id = 1; }
            // mkMenuNativeItem(o, str("menu3"), onActive).{ o.id = 2; }
            // mkMenuNativeItem(o, str("menu4"), onActive).{ o.id = 3; }
            // mkMenuNativeItem(o, str("menu5"), onActive).{ o.id = 4; }

            MenuNative@ n = new MenuNative()
            n.create(o)
            n.cbOnDismiss = ^void (){
                printf("cbOnDismiss\n");
                self.setIsActive(false)
            }
            Vec2 p = Mouse_getPos()

            //菜单会阻塞渲染,所以延时处理
            // mkTimerTimeout(^void (){
            //     Rect r = self.get_abs_rect()
            //     n.showAt(r.x, r.bottom())
            //     // n.showAt(0, 0)
            // }, 20)
            requestAnimationFrame(^ bool (){
                Rect r = self.get_abs_rect()
                n.showAt(r.x, r.bottom())
                return true
            })
        }
    }

    // void onHoverChanged(){
    //     Cursor_ins().setCursor(
    //         self.hover 
    //         ? "pointer"
    //         : "arrow"
    //     )
    // }

	void onEvent(Event *ev){
		if (ev instanceof MouseEvent){
			MouseEvent *me = (MouseEvent*)ev
			if (me.isClickInBubble()){
				printf("Click Select\n")
                self.showPopupMenu()
				// self.setChecked(!self.checked)
                // MessageDialog_alert("content", "title")

				ev.stopPropagation()
			}
		}
	}
}

Select@ mkSelect(void* parent, long long key){
    return (Select@)gocNode(
        key ? (void*)key:__builtin_return_address(0) , 
		(Node*)parent, Select)
}
