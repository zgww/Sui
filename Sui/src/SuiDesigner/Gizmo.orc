package SuiDesigner

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"


#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Number.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/NodeLib.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/Canvas.orc"

import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Dialog/Toast.orc"

import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/View/MenuNative.orc"

import * from "../Sui/Layout/LayoutLinear.orc"

import * from "../Sui/View/ViewBuilder.orc"
import * from "./Serial/BiJson.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/View/Drag.orc"
import * from "./Asset/AssetDirView.orc"
import * from "./Asset/AssetDirTreeView.orc"
import * from "./RegisterNodes.orc"
import * from "./DrawDegree.orc"
import * from "./UiAction.orc"
import * from "./ANode.orc"
import * from "./EditCtx.orc"
import * from "./EventANodeChanged.orc"
import * from "./EventFileItemChanged.orc"



class GizmoRectView extends View{
    Rect targetRect

    View* lt
    View* rt
    View* rb
    View* lb

    Drag@ drag = new Drag()

    ^void (Rect newTargetRect) onRectChanged

    Rect _tmpRect

	void layout(Frame* ctx) {
        // do nothing
        // self.layoutContent(ctx)
    }

    void ctor(){
        super.ctor()
        self.drag.onDrag = ^void(Drag *d){
            if d.isDragStart {
                self._tmpRect = self.targetRect
            }
            if d.isDragging {
                Rect *r = &self._tmpRect
                if d.data == self.lt { 
                    r.x += d.deltaPos.x
                    r.y += d.deltaPos.y

                    r.w -= d.deltaPos.x
                    r.h -= d.deltaPos.y
                }
                if d.data == self.rt { 
                    // self.targetRect.x -= d.deltaPos.x
                    r.y += d.deltaPos.y

                    r.w += d.deltaPos.x
                    r.h -= d.deltaPos.y
                }
                if d.data == self.rb { 
                    r.w += d.deltaPos.x
                    r.h += d.deltaPos.y
                }
                if d.data == self.lb { 
                    r.x += d.deltaPos.x

                    r.w -= d.deltaPos.x
                    r.h += d.deltaPos.y
                }
                printf("on drag========================================rect:%f,%f,%f,%f\n",
                    r.x,
                    r.y,
                    r.w,
                    r.h,

                )
                if self.onRectChanged {
                    self.onRectChanged(*r)
                }
            }
        }
    }


    void react(){
        Rect r = self.targetRect

        View* o = (View*)self
        o.border.setAll(1, 0xffffff)
        o.backgroundColor = 0x320088ff
        o.frame.width = self.targetRect.w
        o.frame.height = self.targetRect.h
        o.frame.x = r.x
        o.frame.y = r.y

        o.startInnerReact()

        self. lt = Gizmo_reactRect(o, 0, 0, 0)
        self. rt = Gizmo_reactRect(o, r.w, 0, 1)
        self. rb = Gizmo_reactRect(o, r.w, r.h, 2)
        self. lb = Gizmo_reactRect(o, 0, r.h, 3)
        self.bindEvent(self.lt)
        self.bindEvent(self.rt)
        self.bindEvent(self.rb)
        self.bindEvent(self.lb)

        o.endInnerReact()
    }
    void bindEvent(View@ v){
        v.cbOnEvent = ^ void (Event *e){
            if e instanceof MouseEvent {
                MouseEvent *me = (MouseEvent*) e;

                if me.button == 1 && me.isCapture && me.isMouseDown {
                    self.drag.data = v
                    self.drag.onMouseDown(me)
                }
            }
        }

    }
}


View * Gizmo_reactRect(
    Node *o,
    float x, float y, 
    long long key,

    ){

    mkView(o, key).{
        o.width = 8
        o.height = 8
        o.frame.width = 8
        o.frame.height  = 8
        o.frame.x = x - o.width / 2 - 1
        o.frame.y = y - o.height / 2 - 1
        o.backgroundColor = 0xaaeeeeff
        o.cursor.set("pointer")
        o.border.setAll(1, 0xffffffff)

        return o
    }
}

GizmoRectView@ mkGizmoRectView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (GizmoRectView@)gocNode(sp, (Node*)parent, GizmoRectView)
}