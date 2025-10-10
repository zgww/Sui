package SuiView

#include <stdio.h>

import * from "../Core/ViewBase.orc"
import * from "../Core/MouseEvent.orc"
import * from "../Core/Emitter.orc"
import * from "../Core/Event.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Cursor.orc"
import * from "../../Orc/String.orc"

/// 拖拽
/// 用法:
/// 
// Drag@ dragTab = new Drag()
// void ctor(){
//     // self.dragSplitter.onDrag =^ void(Drag *d){
//     //     printf("drag....\n");
//     // }
//     self.dragTab.onDrag = ^void(Drag *d){
//         if (d.isDragging || d.isDragEnd){
//             printf("\n\n\t drag tab\n")
//             self.invalidDraw()
//         }
//         if (d.isDragEnd){
//             self.doDrop()
//         }
//     }
// }
// //处理事件：tab项
// void _onEvent_tabItemHead(Event *e, DockItem *kid){
//     if (e instanceof MouseEvent){
//         MouseEvent *me = (MouseEvent*)e

//         if (me.isMouseDown){
//             // MessageDialog_alert("click tab head", "title标题")
//             self._onClickTabItemHead(kid)
//         }

//         self.dragTab.data = kid
//         self.dragTab.onMouseDown(me)
//     }
// }
class Drag extends Listener{
    ^void(Drag *d) onDrag = null

    Vec2 currentClientPos;
    Vec2 downClientPos;
    Vec2 deltaPos //相对kkk的位移

    String@ cursor = null

    //mousedown时进入checking状态
    bool isDragChecking = false
    bool isDragEnd = false
    bool isDragStart = false
    bool isDragging = false

    // 移动阈值后，才开始计算dragging
    float moveThreshold = 5

    //用户数据
    Object@ data = null

    // no own the event
    MouseEvent *mouseEvent = null
    int mouseDownButton = 1

    //期望在什么状态下触发
    // int preferButton = 1
    // bool preferBubble = true
    // bool preferCapture = false

    void dtor(){
        printf(".Drag\n")
    }

    void setStatus(const char *status){
        self.isDragEnd = strEq(status, "end")
        self.isDragStart = strEq(status, "start")
        self.isDragging = strEq(status, "dragging")
        self.isDragChecking = strEq(status, "checking")
        if (self.cursor){
            if (self.isDragStart){
                Cursor_ins().setCursor(self.cursor.str)
                Cursor_ins().setIsLocked(true)
            }
            else if (self.isDragEnd){
                Cursor_ins().setCursor("normal")
                Cursor_ins().setIsLocked(false)
            }
        }
    }

    void onMouseDown_byPrefer(Event *e, int button, bool cap, bool bubble){
        MouseEvent* me = (MouseEvent*)e;
        if me == null || !(me instanceof MouseEvent) {
            return
        }
        if (!me.isMouseDown){//非MouseDown event
            return;
        }

        if me.button != button {
            return;
        }

        if me.isCapture && !cap{ // 只在冒泡阶段处理
            return
        }
        if me.isBubble() && !bubble { // 只在冒泡阶段处理
            return
        }

        self.onMouseDown(e)
    }

    void onMouseDownIf(Event *e){
    }
    void onMouseDown(Event *e){
        MouseEvent* me = (MouseEvent*)e;
        if me == null || !(me instanceof MouseEvent) {
            return
        }
        if (!me.isMouseDown){//非MouseDown event
            return;
        }
        self.mouseDownButton = me.button
        self.mouseEvent = me;

        printf("\n\nDrag onMouseDown\n");
        ViewBase *rv = me.window.rootView
        if (rv != null){
            rv.removeListener(self)
            rv.addListener(self)
        }
        self.deltaPos.x = 0
        self.deltaPos.y = 0
        self.downClientPos.x = me.clientX
        self.downClientPos.y = me.clientY
        self.currentClientPos = self.downClientPos

        self.setStatus("checking")
        if (self.onDrag != null){
            self.onDrag(self)
        }

        // self.setStatus("start")
    }

    void onListenerEvent(Event *ev){
        if (ev instanceof MouseEvent){
			MouseEvent *me = (MouseEvent*)ev
            self.mouseEvent = me;


            if me.isCapture {
                if (me.isMouseUp){
                        printf("\n\nDrag onMouseUp\n")
                        ViewBase *rv = me.window.rootView
                        rv.removeListener(self)

                        if (self.isDragging){
                            me.stopPropagation()
                            self.setStatus("end")
                            if (self.onDrag != null){
                                self.onDrag(self)
                            }
                        }

                        self.setStatus("idle")
                        return
                }
                else if (me.isMouseMove){
                        if self.isDragging {//已经在拖拽中了，严格阻止传播
                            me.stopImmediatePropagation()
                        } else {
                            me.stopPropagation()
                        }

                        // printf("\n\nDrag onMouseMove\n")
                        self.deltaPos.x = me.clientX - self.currentClientPos.x
                        self.deltaPos.y = me.clientY - self.currentClientPos.y
                        self.currentClientPos.x = me.clientX
                        self.currentClientPos.y = me.clientY

                        //检查是不是在开始拖拽了中
                        if self.isDragChecking{
                            float moveX = me.clientX - self.downClientPos.x
                            float moveY = me.clientY - self.downClientPos.y

                            float moveDistance = moveX * moveX + moveY * moveY
                            if (moveDistance >= self.moveThreshold * self.moveThreshold){
                                me.stopImmediatePropagation()

                                self.setStatus("start")
                                if (self.onDrag != null){
                                    self.onDrag(self)
                                }

                                self.setStatus("dragging")
                                return;
                            }
                        }
                        if 0{
                            printf("drag status:%d,%d,%d,%d\n", 
                                self.isDragStart,
                                self.isDragChecking,
                                self.isDragging,
                                self.isDragEnd,
                            );
                        }

                        if (self.onDrag != null){
                            self.onDrag(self)
                        }
                }
            }
        }
    }
    
}
