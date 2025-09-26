package SuiCore

#include <stdio.h>


import * from "../../Orc/List.orc"
import * from "./Node.orc"
import * from "./ViewBase.orc"
import * from "./Frame.orc"


/// 布局上下文
class LayoutCell extends Node {
    void invalidLayout(){
        if (self.parent instanceof ViewBase) {
            ViewBase *parentView = (ViewBase*)self.parent;
            parentView.invalidLayout()
        }
    }
    void onMounted(){
        // 如果父是ViewBase, 则注册到layoutCells
        if (self.parent instanceof ViewBase) {
            ViewBase *parentView = (ViewBase*)self.parent;
            List *layoutCells = parentView->gocLayoutCells();
            layoutCells.add(self);
            parentView->invalidLayout();
        }

    }
    void onUnmounting(){
        //如果父是ViewBase, 则取消注册到layoutCells
        if (self.parent instanceof ViewBase) {
            ViewBase *parentView = (ViewBase*)self.parent;
            List *cells = parentView->gocLayoutCells();
            // List* cells = parentView->layoutCtx.layoutCells;
            cells.remove(self)
            parentView->invalidLayout();
        }
    }
}