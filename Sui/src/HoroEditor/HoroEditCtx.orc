package HoroEditor


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
import * from "../SuiDesigner/Serial/BiJson.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/View/Drag.orc"
import * from "../SuiDesigner/Asset/AssetDirView.orc"
import * from "../SuiDesigner/Asset/AssetDirTreeView.orc"
import * from "../SuiDesigner/RegisterNodes.orc"
import * from "../SuiDesigner/DrawDegree.orc"
import * from "../SuiDesigner/UiAction.orc"
import * from "../SuiDesigner/EventFileItemChanged.orc"
import * from "../SuiDesigner/Prefab.orc"
import * from "../SuiDesigner/ANode.orc"

import * from "../Sgl/SglSceneView.orc"
import * from "../Sgl/Scene.orc"
import * from "../Sgl/Obj3d.orc"


class EventHoroSceneChanged extends Event{
}
class EventHoroSelectedChanged extends Event{
}

class HoroEditCtx {
    TreeState@ state = null

    SglSceneView@ sceneView
    List@ roots = new List()
    Node@ hoverNode 
    Prefab@ prefab = null //当前编辑的预制体

    void setState(TreeState@ state){
        self.state = state
        state.cbSelectedIdChanged = ^void (TreeState* state){
            self.onSelectedChanged()
        }
    }
    ANode@ findANodeByNode(Node* node){
        ANode* root = self.getRoot()
        if root && root.node {
            // 场景视图所在节点
            Node* scene = root.node.parent
            //因为vnode可能不含子节点,所以向上找找
            Node *n = node
            while n && n != scene {
                ANode@ found = root.findANodeByNode(n)
                if found {
                    return found
                }
                // if !found {
                n = n.parent
                // }
            }
        }
        return null
    }

    void onSelectedChanged(){
        //广播事件
        EventHoroSelectedChanged@ e = new EventHoroSelectedChanged()
        // MessageDialog_alert("sel changed", "tip")
        useEbus().emit(e)
    }
    void setSceneView(SglSceneView *sceneView){
        self.sceneView = sceneView
        if sceneView{
            // self.roots.clear()
            // self.roots.add(self.sceneView.scene)
        }
    }


    Scene* getScene(){
        if self.sceneView{
            return self.sceneView.scene
        }
        return null
    }


    void closeCurrentPrefab(){
        if !self.prefab {
            return
        }
        for int i = 0; i < self.roots.size(); i++{
            ANode* root = (ANode*)self.roots.get(i)
            root.removeSelf()
        }
        self.roots.clear()

        self.prefab = null
    }

    void openPrefab(const char *path){
        self.closeCurrentPrefab()
        new Prefab().{
            self.prefab = o
            o.loadByPathCstr(path)

            self.getRoot().printTree(0)
            self.getRoot().updateSubTreeNodes()

            self.roots.clear()
            self.roots.add(self.prefab.root)
            int size = self.roots.size()
            printf("HoroEdit roots. size:%d\n", size )
        }

    }
    ANode@ getRoot(){
        if self.prefab {
            return self.prefab.root
        }
        return null
    }
}
