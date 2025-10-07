package HoroEditor

#include "../Orc/Orc.h"

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Path.orc"

import * from "../Json/Json.orc"

import * from "./HoroEditCtx.orc"
import * from "./HoroEditor.orc"

import * from "../SuiDesigner/ANode.orc"
import * from "../SuiDesigner/EventANodeChanged.orc"
import * from "../SuiDesigner/FileItem.orc"
import * from "../SuiDesigner/Prefab.orc"
import * from "../SuiDesigner/EventFileItemChanged.orc"

import * from "../Sui/Core/NodeLib.orc"

import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sgl/Obj3d.orc"



//创建prefab
void UiAct_createPrefab3d(FileItem@ parent){
    //确保parent是目录
    if parent && !parent.isDirectory{
        parent = parent.parent
    }

    if !parent {
        MessageDialog_alert("未指定父目录", "tip")
        return
    }



    MessageDialog_prompt("新建预制3d.prefab.json", "新建预制3d", ^void (String@ newName){
        String@ path = parent.path.clone().add("/").addString(newName)
        Prefab@ prefab = new Prefab()
        prefab.root = mkANodeByTag(Vtable_getClassName(Obj3d))
        String@ text = prefab.toJson().dump()

        MessageDialog_alert(str("新建预制. 路径").add(path.str).str, "tip")

        if Path_writeText(path.str, text.str) {
            MessageDialog_alert(str("新建预制成功. 路径").add(path.str), "tip")

            parent.loadSubtree()

            new EventFileItemChanged().{
                o.fileItem = parent
                o.emitToEbus()
            }
        }
    })
}
void UiAct_savePrefab(HoroEditor* editor){
    HoroEditCtx@  ctx = editor.editCtx
    if ctx.prefab {
        ctx.prefab.save()

        Toast_make("保存成功")
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
