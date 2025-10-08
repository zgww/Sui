package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"

import * from "../../Orc/Path.orc"

import * from "../../Orc/String.orc"
import * from "../Core/ViewBase.orc"
import * from "../Core/Node.orc"
import * from "../Core/Event.orc"
import * from "../Core/MouseEvent.orc"
import * from "../View/ImageView.orc"
import * from "../View/TextView.orc"
import * from "../Core/View.orc"
import * from "../View/ViewBuilder.orc"
import * from "../Layout/LayoutLinear.orc"

import * from "../../SuiDesigner/Theme.orc"

/// 布局上下文
class Panel extends LayoutLinear{

    ^void (Node* o) cbRenderTitle
    ^void (Node* o) cbRenderContent

    String@ title
    bool open = true

    View@ body

    int titleColor = themeIns().panel_titleColor
    int titleFontSize = themeIns().panel_titleFontSize

    void onEvent_forHead(Event *e){
        if (e instanceof MouseEvent){
            self.onClick_inHead((MouseEvent*)e)
        }
    }
    void onClick_inHead(MouseEvent*e){
        if (e.isClickInBubble()){
            self.setOpen(!self.open)
        }
    }
    void setOpen(bool v){
        if (v == self.open){
            return;
        }
        self.open = v
        self.invalidReact()
    }

    void react(){
        self.direction.set("column")
        self.alignItems.set("stretch")


        self.startInnerReact()

        Node *o = self

        //标题
        layoutLinear(o, 0).{
            o.cbOnEvent = ^void (Event *e){
                self.onEvent_forHead(e)
            }

            o.backgroundColor = 0x0d000000
            o.border.setAll(1, 0x33000000)

            mkImageView(o, 0).{
                // o.imageMode = HeightFix
                o.width = 16
                o.height = 16
                o.setSrc(
                    self.open 
                    ? Path_resolveFromExecutionDir("../asset/icon/light-arrow-down.png")
                    : Path_resolveFromExecutionDir("../asset/icon/light-arrow-right.png")
                )
                o.margin.right = 4
            }

            if self.title{
                mkTextView(o, 0).{
                    o.setText(self.title)
                    o.color = self.titleColor
                    o.setFont_size(self.titleFontSize)
                }
            } else if (self.cbRenderTitle){
                self.cbRenderTitle(o)
            }
        }

        //回调模式
        if self.cbRenderContent{
            if (self.open){
                if (self.cbRenderContent){
                    self.cbRenderContent(o)
                }
            }
        }
        else {
            //非回调的模式
            LayoutLinear* tmp = layoutLinear(o, 0)
            tmp.direction.set("column")
            tmp.visible = self.open
            // tmp.height = self.open ? 200 : 100
            self.body = tmp
        }

        self.endInnerReact()
    }
}
/// 布局上下文
class Panel2 extends LayoutLinear{

    ^void (Node* o) cbRenderTitle

    String@ title
    bool open = true


    void ctor(){
        self.hasInnerReact = true
    }


    void onEvent_forHead(Event *e){
        if (e instanceof MouseEvent){
            self.onClick_inHead((MouseEvent*)e)
        }
    }
    void onClick_inHead(MouseEvent*e){
        if (e.isClickInBubble()){
            self.setOpen(!self.open)
        }
    }
    void setOpen(bool v){
        if (v == self.open){
            return;
        }
        self.open = v
        self.invalidReact()
    }

    void react(){
        self.direction.set("column")
        self.alignItems.set("stretch")


        self.startInnerReact()

        Node *o = self

        //标题
        layoutLinear(o, 0).{
            o.cbOnEvent = ^void (Event *e){
                self.onEvent_forHead(e)
            }

            o.backgroundColor = 0x0d000000
            o.border.setAll(1, 0x33000000)

            mkImageView(o, 0).{
                // o.imageMode = HeightFix
                o.width = 16
                o.height = 16
                o.setSrc(
                    self.open 
                    ? Path_resolveFromExecutionDir("../asset/icon/light-arrow-down.png")
                    : Path_resolveFromExecutionDir("../asset/icon/light-arrow-right.png")
                )
                o.margin.right = 4
            }

            if self.title{
                mkTextView(o, 0).{
                    o.setText(self.title)
                }
            } else if (self.cbRenderTitle){
                self.cbRenderTitle(o)
            }
        }

        if self.open {
            self.placeKids(self.outKids)
        }

        self.endInnerReact()
    }
}

Panel@ mkPanel(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (Panel@)gocNode(sp, (Node*)parent, Panel)
}
Panel2@ mkPanel2(void* parent, long long key){
    void *sp = key ? (void*)key: __builtin_return_address(0)
    return (Panel2@)gocNode(sp, (Node*)parent, Panel2)
}