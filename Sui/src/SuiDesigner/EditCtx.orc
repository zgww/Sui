package SuiDesigner

#include <stdio.h>
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Json/Json.orc"
import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "./RegisterNodes.orc"
import * from "../Sui/Core/NodeLib.orc"
import * from "../Sui/View/TreeView.orc"
import * from "./ANode.orc"
import * from "./Prefab.orc"
import * from "./SceneView.orc"
import * from "./SceneHierView.orc"
import * from "./EventANodeChanged.orc"

//编辑事件基类
class EditEventBase extends Event {
}
//选中的节点有变化
class EditEventSelectedChanged extends EditEventBase {
}



//编辑器的上下文
//编辑器的核心信息团
class EditCtx extends Emitter {
    ANode@ root = null
    // List<VNode>
    List@ roots = new List()
    TreeState@ state = null
    ANode@ hoverNode = null

    Prefab@ prefab = null //当前编辑的预制体
    // SceneHierView@ sceneHierView  
    SceneView@ sceneView

    ANode@ findANodeByNode(Node* node){
        if self.root && self.root.node {
            // 场景视图所在节点
            Node* scene = self.root.node.parent
            //因为vnode可能不含子节点,所以向上找找
            Node *n = node
            while n && n != scene {
                ANode@ found = self.root.findANodeByNode(n)
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

    void setState(TreeState@ state){
        self.state = state
        state.cbSelectedIdChanged = ^void (TreeState* state){
            self.onSelectedChanged()
        }
    }

    void onSelectedChanged(){
        //广播事件
        EditEventSelectedChanged@ e = new EditEventSelectedChanged()
        // MessageDialog_alert("sel changed", "tip")
        self.emit(e)
    }

    void closeCurrentPrefab(){
        if !self.prefab {
            return
        }
        if self.root {
            self.root.removeSelf()
        }
        self.root = null
        self.roots.clear()
        self.prefab = null
    }

    void openPrefab(const char *path){
        self.closeCurrentPrefab()
        new Prefab().{
            self.prefab = o
            o.loadByPathCstr("../asset/button.prefab.json")
            self.root = o.root
            self.root.printTree(0)
            self.root.updateSubTreeNodes()

            self.roots.clear()
            self.roots.add(self.root)
        }

    }


    void init(){
        registerNodes()
        mkTimerTimeout(^void(){
            printf("========================================timer open prefab\n")
            self.openPrefab("../asset/button.prefab.json")

            new EventANodeChanged().{
                o.anode = EditCtx_ins().root
                o.emitToEbus()
            }
        }, 300)

        // new Prefab().{
        //     self.prefab = o
        //     o.loadByPathCstr("../asset/button.prefab.json")
        //     self.root = o.root
        //     self.root.printTree(0)
        //     self.root.updateSubTreeNodes()

        //     self.roots.clear()
        //     self.roots.add(self.root)
        // }

        // VNode@ vn = loadPrefab("button.json")
        // vn.printTree(0)
        // vn.updateSubTreeNodes()
        // self.root = vn
        // self.roots.add(vn)
    }
}

EditCtx@ EditCtx_ins(){
    static EditCtx@ ins = null
    if !ins {
        ins = new EditCtx()
    }
    return ins;
}