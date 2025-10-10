package HoroEditor

#include "../Orc/Orc.h"
#include <stdio.h>
#include "../Json/cJSON.h"

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Number.orc"

import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Event.orc"

import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/View/ViewBuilder.orc"

import * from "../Sui/Layout/LayoutLinear.orc"

import * from "../SuiDesigner/Insp.orc"
import * from "../SuiDesigner/ANode.orc"

import * from "../Sgl/Obj3d.orc"

import * from "../Json/Json.orc"



import * from "./HoroEditCtx.orc"
import * from "./HoroEditor.orc"

import * from "../SuiDesigner/EventANodeChanged.orc"


class HoroInspView extends LayoutLinear{

    Insp@ insp = new Insp()
    HoroEditCtx@ editCtx
    HoroEditor@ editor
    void ctor(){
        self.insp.cbSetAttr = ^void(Object *obj, OrcMetaField*mf, Object*inspValue){
            printf("设置属性:%s value:%s\n",
                mf.name,
                inspValue.toString().str
            )
            Node* sel = self.editCtx.state.getFirstSelected()
            if sel instanceof ANode {
                ANode* anode = (ANode*)sel
                printf("给anode设置属性:%s\n", 
                    anode.toJson().dump().str
                )
                anode.setAttrValueObject(mf.name, inspValue)
            }
        }
    }

    void onListenerEvent(Event* e){
        if e instanceof EventHoroSceneChanged{
            self.invalidReact()
        }
        if e instanceof EventHoroSelectedChanged {
            self.invalidReact()
        }


        //选中的节点有变更
        // if (e instanceof EditEventSelectedChanged){
        //     self.invalidReact()
        // }
        if e instanceof EventANodeAttrChanged{
            // EventANodeAttrChanged* e = (EventANodeAttrChanged*)e;
            // self.trigger_react()
            self.invalidReact()
        }
    }

    void onMounted(){
        // EditCtx_ins().addListenerOnce(self)
        useEbus().addListener(self)
    }
    void onUnmounting(){
        // EditCtx_ins().removeListener(self)
        useEbus().removeListener(self)
    }


    void react(){
        self.direction = str("column")
        self.alignItems = str("stretch")
        // self.backgroundColor = 0x0

        self.startInnerReact()
        Node *o = self

        layoutLinearCell(o, 0).{ 
            // o.grow = 1 
        }

        HoroEditCtx@ ctx = self.editCtx;
        if ctx && ctx.state {
            ANode@ anode = (ANode@)ctx.state.getFirstSelected()
            if anode {
                Node* node = anode.node
                // Obj3d@ obj = ctx.getScene()
                if !(node instanceof Node) {
                    mkTextView(o, 0).{
                        o.setText(str("no node??"))
                    }
                }
                else {
                    Obj3d@ obj = (Obj3d@)node
                    // ANode@ anode = (ANode@)ctx.state.getFirstSelected()

                    mkScrollArea(o, 0).{
                        // o.backgroundColor = 0xff00ff0f
                        // o.width = 300
                        // o.height = 200
                        o.alignItems = str("stretch")
                        // o.useWidthContraint = true
                        o.useMinWidthConstraint = true
                        // o.padding.setHor(8)

                        layoutLinearCell(o, 0).{
                            // o.grow = 1
                        }

                        if obj {
                            self.insp.insp(o, obj)
                        }
                        else {
                            mkTextView(o, 0).{
                                o.setText(str("no data"))//anode ? anode.className: str("attr"))
                            }
                        }
                    }
                }
            }
        }


        // mkPanel(o, 0).{
        //     o.cbRenderTitle = ^void(Node *o){
        //         mkTextView(o, 0).{
        //             o.setText(str("title"))
        //         }
        //     }
        //     o.cbRenderContent = ^void(Node *o){
        //         mkTextView(o, 0).{
        //             o.setText(str("content"))
        //         }
        //     }
        // }


        self.endInnerReact()
    }
}
HoroInspView@ mkHoroInspView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (HoroInspView@)gocNode(sp, (Node*)parent, HoroInspView)
}
