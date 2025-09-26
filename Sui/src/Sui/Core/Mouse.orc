package SuiCore

#include <stdio.h>

import * from "./Vec2.orc"
import * from "./Window.orc"
import * from "./MouseEvent.orc"
import * from "./Event.orc"
import * from "./App.orc"
import * from "./ViewBase.orc"
import * from "./Node.orc"
import * from "../../Orc/String.orc"
import * from "./Emitter.orc"


//相对于屏幕的位置
extern Vec2 Mouse_getPos()


//相对于窗口的位置
Vec2 Mouse_getPosOfWindow(Window* window) {
    if (window){
        Vec2 pos = Mouse_getPos()
        Vec2 winPos = window.getPos()
        return mkVec2(pos.x - winPos.x, pos.y - winPos.y)
    }
    return mkVec2(0.f, 0.f)
} 

void testMouse(){
    Vec2 pos = Mouse_getPos()
    Vec2 winPos = Mouse_getPosOfWindow(null)
    printf("pos:%f,%f. winPos:%f,%f\n", pos.x, pos.y, winPos.x, winPos.y)
    Mouse_getPos()
}

struct MouseData {
    int clientX
    int clientY
    //mousedown|mousemove|mouseup
    // const char* eventType
    //1:left, 2:middle, 3:right button
    int button 
    long long windowId
    bool isMouseDown
    bool isMouseMove
    bool isMouseUp
    bool isDoubleClick

    int uid; // 自定义的id

    bool shift
    bool alt
    bool ctrl
}



static int mouseDownClientX = 0
static int mouseDownClientY = 0
void setMouseEventFromMouseData(MouseEvent *ev, MouseData* md){
    if (md.isMouseDown){
        mouseDownClientX = md.clientX
        mouseDownClientY = md.clientY
    }

    App@ app = App_use()
    Window@ win = app.findWindowById(md.windowId)

    // MouseEvent@ ev = new MouseEvent()
    ev.clientX = md.clientX
    ev.clientY = md.clientY
    ev.window = win
    ev.mouseDownClientX = mouseDownClientX
    ev.mouseDownClientY = mouseDownClientY
    ev.isMouseDown = md.isMouseDown
    ev.isMouseMove = md.isMouseMove
    ev.isMouseUp = md.isMouseUp

    ev.button = md.button

    ev.ctrl = md.ctrl
    ev.shift = md.shift
    ev.alt = md.alt
}
MouseEvent@ newMouseEventFromMouseData(MouseData* md){
    MouseEvent@ ev = new MouseEvent()
    setMouseEventFromMouseData(ev, md)
    return ev
}

//分发鼠标事件:down/up
void dispatchMouseEvent(MouseEvent@ ev){
    if (!ev.window ){
        return
    }
    if (!ev.window.rootView ){
        return
    }

    ViewBase* view = ev.window.rootView.hitTest(ev.clientX, ev.clientY)
    if (!view) { //没有具体的view接收事件，如mouseup在窗体外
        view = ev.window.rootView
        //ev.window.emit(ev)
        //return
    }
    preprocessMouseEvent(ev)
    propagateViewEvent(view, ev);
}
//分发鼠标移动事件。 主要还要处理hover
void dispatchMouseMoveEvent(MouseEvent@ ev){
    // if (1){
    //     return;
    // }
    if (!ev.window){
        return
    }
    if (!ev.window.rootView ){
        return
    }

    HoverSentive* sen = sinsHoverSentive()

    ViewBase* view = ev.window.rootView.hitTest(ev.clientX, ev.clientY)
    if (!view) { //没有具体的view接收事件，如mouseup在窗体外
        view = ev.window.rootView
        //ev.window.emit(ev)
        sen.onmousemove(ev, null);
        //return
    }

    propagateViewEvent(view, ev);
    sen.onmousemove(ev, view);
}
void Mouse_onMouseDown(MouseData md){
    MouseEvent@ ev = newMouseEventFromMouseData(&md)
    ev.name.set("mousedown")
    dispatchMouseEvent(ev)
}
void Mouse_onMouseMove(MouseData md){
    MouseEvent@ ev = newMouseEventFromMouseData(&md)
    ev.name.set("mousemove")
    // printMouseData(&md, "pref22ix mouse_onMouseMove");
    dispatchMouseMoveEvent(ev)
}
void Mouse_onMouseUp(MouseData md){
    MouseEvent@ ev = newMouseEventFromMouseData(&md)
    ev.name.set("mouseup")
    dispatchMouseEvent(ev)
}

//滚一次，120, 快速滚，可能出现360, 600
void Mouse_onWheel(MouseData *md, int deltaX, int deltaY){
    WheelEvent@ ev = new WheelEvent()
    setMouseEventFromMouseData(ev, md)
    ev.deltaX = deltaX
    ev.deltaY = deltaY
    ev.isWheel = true


    printf("滚轮事件; clientX:%d, clientY:%d, deltaX:%d, deltaY:%d\n",
        ev.clientX, ev.clientY, ev.deltaX, ev.deltaY
    )

    dispatchMouseEvent(ev)  
}

void printMouseData(MouseData *md, const char *prefix) {

    printf("%s; windowId:%lld, button:%s, clientPos:%d,%d eventType:%s\n",
        prefix, 
        md->windowId,
        md->button == 1 ? "left" :
        md->button == 2 ? "middle" :
        md->button == 3 ? "right":"none",
        md->clientX,
        md->clientY,

        md->isMouseDown ?"mousedown"
        : md->isMouseMove ?"mousemove"
        : md->isDoubleClick ?"doubleclick"
        :"mouseup"
        );
}