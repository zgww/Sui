package SuiDesigner

#include <stdio.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Path.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/View/MenuNative.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Sui/Layout/RowWrap.orc"
import * from "../Sui/Layout/LayoutAlign.orc"

import * from "./FileItem.orc"
import * from "./UiAction.orc"
import * from "./EditCtx.orc"
import * from "./EventANodeChanged.orc"
import * from "./EventFileItemChanged.orc"


// class Asset {
//     FileItem@ rootFileItem = null
// }

class Project {
    String@ projectDir = str("")
    FileItem@ dirFileItem = null

    void init(const char *projectDir){
        self.projectDir = str(projectDir)
        self.dirFileItem = FileItem_loadDirectoryTree(projectDir)
        printf("\n\n打印项目根文件目录树: %s\n", projectDir);
        self.dirFileItem.printTree(0)
    }
}

Project@ Project_ins(){
    static Project@ ins = null
    if (ins == null){
        ins = new Project()
    }
    return ins
}
