package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"

import * from "../Core/Node.orc"
import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Border.orc"
import * from "../Core/Event.orc"
import * from "../Core/MouseEvent.orc"
import * from "./ViewBuilder.orc"

class HoverViewEffect extends Node{
    int backgroundColor = 0x00ffffff
    Border@ border = mkBorder(1, 0x00000000)//new Border()

    int hoverBackgroundColor = 0x22666666 // 0x33ff0000
    Border@ hoverBorder = mkBorder(1, 0x00007aff) //new Border()

    int activeBackgroundColor = 0x33007aff//0x22ff0000
    Border@ activeBorder = mkBorder(1, 0x66007aff )//0x44ff0000)

    bool isActive = false

    ^void (MouseEvent *e) onClick
    //回调的方式 允许 外部控制. return true表示已处理
    ^bool (Event *e) onHostEvent

    ^void(ViewBase*parent) cbOnHoverChanged


    void onMounted(){
        // self.parent.addListenerOnce(self)
        if (self.parent instanceof View){
            View @v = (View*)self.parent
            v.cbOnHoverChanged = ^void (){
                printf("HoverViewEffect. cbOnHoverChanged:%d\n", v.hover);
                self.applyEffect()

                if (self.cbOnHoverChanged){
                    self.cbOnHoverChanged(v)
                }
            }
            if self.onClick || self.onHostEvent {
                v.cbOnEvent = ^void (Event *e){
                    if self.onHostEvent {
                        if self.onHostEvent(e){
                            return;
                        }
                    }
                    if e instanceof MouseEvent {
                        MouseEvent *me = (MouseEvent*)e
                        if me.button == 1 && me.isClickInBubble() {
                            if self.onClick {
                                self.onClick(me)
                            }
                        }
                    }
                }
            }
        }
        // self.applyEffect()
    }
    void react(){
        self.applyEffect()
    }

    void applyEffect(){
        if (self.parent instanceof View){
            View *v = (View*)self.parent
            bool hover = v.hover
            int bgColor =  self.backgroundColor
            Border *border = self.border

            if (self.isActive){
                bgColor = self.activeBackgroundColor
                border = self.activeBorder
            }
            else if (hover){
                bgColor = self.hoverBackgroundColor
                border = self.hoverBorder
            }

            v.backgroundColor = bgColor;
            v.border.copyFrom(border)
            v.invalidDraw()
        }
    }
    void onUnmounting(){
        // self.parent.removeListener(self)
        if (self.parent instanceof View){
            View *v = (View*)self.parent
            v.cbOnHoverChanged = null
            self.applyEffect()
        }
    }

    // void onListenerEvent(Event *e){
    //     if (e instanceof)
    // }
}



HoverViewEffect@ mkHoverViewEffect(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (HoverViewEffect@)gocNode(sp, (Node*)parent, HoverViewEffect)
}