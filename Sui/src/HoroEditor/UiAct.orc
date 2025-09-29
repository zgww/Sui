package HoroEditor

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Path.orc"
import * from "./HoroEditCtx.orc"
import * from "./HoroEditor.orc"
import * from "../SuiDesigner/ANode.orc"
import * from "../SuiDesigner/EventANodeChanged.orc"
import * from "../Sui/Core/NodeLib.orc"
import * from "../Sui/Dialog/Toast.orc"


void UiAct_savePrefab(HoroEditor* editor){
    HoroEditCtx@  ctx = editor.editCtx
    if ctx.prefab {
        ctx.prefab.save()
    }
}
void UiAct_addView(HoroEditor* editor, ANode@ anode, String@ viewName){
    if !anode.node {
        Toast_make("node is null")
        return 
    }
    NodeRegisterInfo@ info = NodeLib_use().findByClassName(viewName.str);
    if !info {
        Toast_make("未找到节点类")
        return
    }

    new ANode().{
        o.tag = viewName
        anode.appendChild(o)
        
        o.updateSubTreeNodes()

        new EventANodeChanged().{
            o.anode = anode
            o.emitToEbus()
        }
    }

    
    // Toast_make(viewName.str)
    // NodeRegisterInfo@ info = NodeLib_use().findByClassName(viewName.str);
    // if !info {
    //     Toast_make("未找到节点类")
    //     return
    // }
    // Object@ obj = info.mk()
    // if obj instanceof Node{

    // }
    // else {
    //     Toast_make("不是节点类")
    // }
}
