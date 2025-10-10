package SuiDesigner

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
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/ViewBase.orc"

import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/Switch.orc"
import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/View/Panel.orc"

import * from "../Sui/Layout/LayoutLinear.orc"

import * from "../Sui/View/ViewBuilder.orc"
import * from "./Serial/BiJson.orc"
import * from "../Sui/Core/Color.orc"
import * from "./Asset/AssetDirView.orc"
import * from "./Asset/AssetDirTreeView.orc"
import * from "./SceneView.orc"
import * from "./SceneHierView.orc"
import * from "./ANode.orc"
import * from "./SglEditCtx.orc"
import * from "./Inspector.orc"
import * from "../Sgl/Obj3d.orc"
import * from "./EventANodeChanged.orc"


class SglInspectorView extends LayoutLinear{

    Inspector@ inspector = new Inspector()
    SglEditCtx@ editCtx

    void onListenerEvent(Event* e){
        if e instanceof EventSglSceneChanged {
            self.invalidReact()
        }
        if e instanceof EventSglSelectedChanged {
            self.invalidReact()
        }
        //选中的节点有变更
        // if (e instanceof EditEventSelectedChanged){
        //     self.invalidReact()
        // }
        // else if e instanceof EventANodeAttrChanged{
        //     EventANodeAttrChanged* e = (EventANodeAttrChanged*)e;
        //     self.trigger_react()
        // }
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

        SglEditCtx@ ctx = self.editCtx;
        if ctx && ctx.state {
            Node@ node = (Node@)ctx.state.getFirstSelected()
                // Obj3d@ obj = ctx.getScene()

            if !(node instanceof Obj3d) {
                mkTextView(o, 0).{
                    o.setText(str("no anode"))
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

                    layoutLinearCell(o, 0).{
                        // o.grow = 1
                    }

                    if obj {
                        self.inspector.obj = obj
                        self.inspector.reactObject(o)
                    }
                    else {
                        mkTextView(o, 0).{
                            o.setText(str("no data"))//anode ? anode.className: str("attr"))
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
SglInspectorView@ mkSglInspectorView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (SglInspectorView@)gocNode(sp, (Node*)parent, SglInspectorView)
}