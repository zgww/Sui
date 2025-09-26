package SuiDesigner


#include <stdio.h>
#include <string.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Number.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/NodeLib.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/Canvas.orc"

import * from "../Sui/Dialog/MessageDialog.orc"

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
import * from "./EventFileItemChanged.orc"
import * from "../Sgl/SglSceneView.orc"
import * from "../Sgl/Scene.orc"
import * from "../Sgl/Obj3d.orc"


class EventSglSceneChanged extends Event{
}
class EventSglSelectedChanged extends Event{
}

class SglEditCtx {
    TreeState@ state = null

    SglSceneView@ sceneView
    List@ roots = new List()
    Node@ hoverNode 

    void setState(TreeState@ state){
        self.state = state
        state.cbSelectedIdChanged = ^void (TreeState* state){
            self.onSelectedChanged()
        }
    }

    void onSelectedChanged(){
        //广播事件
        EventSglSelectedChanged@ e = new EventSglSelectedChanged()
        // MessageDialog_alert("sel changed", "tip")
        useEbus().emit(e)
    }
    void setSceneView(SglSceneView *sceneView){
        self.sceneView = sceneView
        self.roots.clear()
        if sceneView{
            self.roots.add(self.sceneView.scene)
        }
    }


    Scene* getScene(){
        if self.sceneView{
            return self.sceneView.scene
        }
        return null
    }


}