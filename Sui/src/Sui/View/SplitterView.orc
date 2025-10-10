package SuiView

#include <stdio.h>

import * from "../../Orc/String.orc"
import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Inset.orc"
import * from "../Core/Node.orc"
import * from "../Core/Event.orc"
import * from "../Core/MouseEvent.orc"
import * from "../View/Drag.orc"
import * from "../View/ViewBuilder.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "../../SuiDesigner/Theme.orc"


/// 适用于LayoutLinear的splitter
class SplitterView extends View {

    Drag@ drag = new Drag()

    int hoverBg = themeIns().dock_splitterBgHover//0xff007aff//0xff00ff00
    int normalBg = themeIns().dock_splitterBg //0xffcdcdcf
    // bool isHor = true; //方向默认为水平

    float prevGrow = 0
    float nextGrow = 0

    void ctor(){
        self.hitTestPadding = mkInset(3, 3, 3, 3)
        self.drag.onDrag = ^void(Drag*d){
            LayoutLinear* ll = (LayoutLinear*)self.parent
            if ll instanceof LayoutLinear {
                bool isHor = ll.calcIsHor()

                int idx = self.parent.indexOf(self)
                if idx == 0 || idx == self.parent.getChildrenCount() - 1{
                    return
                }
                ViewBase* prev = (ViewBase*)self.parent.getChild(idx - 1)
                ViewBase* next = (ViewBase*)self.parent.getChild(idx + 1)
                if prev instanceof ViewBase && next instanceof ViewBase{
                    LayoutLinearCell* prevCell = (LayoutLinearCell*)prev.getChildByType(LayoutLinearCell)
                    LayoutLinearCell* nextCell = (LayoutLinearCell*)next.getChildByType(LayoutLinearCell)
                    if prevCell && nextCell {
                        if d.isDragStart{
                            if isHor {
                                self.prevGrow = prev.frame.width
                                self.nextGrow = next.frame.width
                            }
                            else {
                                self.prevGrow = prev.frame.height
                                self.nextGrow = next.frame.height
                            }
                        }
                        if d.isDragging {

                            if isHor {
                                self.prevGrow += d.deltaPos.x
                                self.nextGrow -= d.deltaPos.x

                            }
                            else {
                                self.prevGrow += d.deltaPos.y
                                self.nextGrow -= d.deltaPos.y
                            }
                            printf("更新Spliiter左右的cell.grow. :%f,%f\n", self.prevGrow, self.nextGrow);
                            prevCell.grow = self.prevGrow
                            nextCell.grow = self.nextGrow
                        }
                    }
                }
            }
        }
    }
    void react(){
        self.cursor = str("sizewe")
        self.backgroundColor = self.hover ? self.hoverBg : self.normalBg
        self.invalidDraw()
    }
    void onEvent(Event *e){
        if (e instanceof MouseEvent){
            if (self.drag){
                self.drag.onMouseDown((MouseEvent*)e)
            }
        }
    }
    // void draw_self(Canvas *canvas){
    //     if self.hover {
    //         canvas.save()
    //         self.frame.width += 4
    //         canvas.translate(-2, 0)
    //     }
    //     super.draw_self(canvas)
    //     if self.hover {
    //         canvas.restore()
    //     }
    // }
    
    void onHoverChanged(){
        self.invalidReact()
    }
}
SplitterView@ mkSplitterView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (SplitterView@)gocNode(sp, (Node*)parent, SplitterView)
}