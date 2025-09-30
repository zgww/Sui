package SuiCore

#include <stdio.h>

import * from "./Event.orc"
import * from "./Emitter.orc"
import * from "./Window.orc"
import * from "./Node.orc"
import * from "./Cursor.orc"
import * from "./Vec2.orc"
import * from "./ViewBase.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Time.orc"
import * from "../../Orc/String.orc"


//可以冒泡的事件
class ViewEvent extends Event{

    Node@ target
    Node@ currentTarget
    //是不是捕获阶段
    bool isCapture = false

    bool isBubble(){
        return !self.isCapture
    }
}

struct ClickRecord {
    int clientX
    int clientY
    long long clickUnixMs
    int button
}
//用来记录每次点击，用来跟踪双击
static ClickRecord clickRecord

/// 布局上下文
class MouseEvent extends ViewEvent {
    int clientX = 0;
    int clientY = 0;
    Window@ window = null;

    // ndc坐标.只在sgl里才有效
    Vec2 ndcPos

    // button 1:left, 2:middle, 3:right
    int button = 0
    int mouseDownClientX = 0
    int mouseDownClientY = 0
    
    bool isMouseDown = false
    bool isMouseUp = false
    bool isMouseMove = false
    bool isWheel = false

    bool ctrl = false
    bool shift = false
    bool alt = false

    bool isDblClick = false
    

    bool isClick(){
        if (self.isMouseUp){
            int dx = self.clientX - self.mouseDownClientX
            int dy = self.clientY - self.mouseDownClientY

            return dx * dx + dy * dy < MouseEvent_clickOffsetThreshold * MouseEvent_clickOffsetThreshold
        }
        return false
    }
    bool isClickInBubble(){
        return !self.isCapture && self.isClick()
    }
    bool isDblClickInBubble(){
        return !self.isCapture && self.isDblClick
    }

    String@ toString(){
        char buffer[1024];
        snprintf(buffer, 1023, "MouseEvent(%s,window:%p, pos:%d,%d, downPos:%d,%d, type:%s)",
            self.name.str,
            self.window,
            self.clientX, self.clientY,
            self.mouseDownClientX,
            self.mouseDownClientY,
            self.isMouseDown? "mousedown":
            self.isMouseUp ? "mouseup":
            self.isMouseMove? "mousemove":
            self.isWheel ? "wheel":"none"
        )
        String@ ret = str(buffer)

        return ret
    }
}

class MouseEnterEvent extends MouseEvent {
    
}

class MouseLeaveEvent extends MouseEvent {
    
}
class WheelEvent extends MouseEvent{
    //-1/1 只为了表示正负
    int deltaY = 0;
    int deltaX = 0;
}

class MouseEventListener {
    void onEvent(MouseEvent *ev){

    }
}

int MouseEvent_clickOffsetThreshold = 10

//感知hover
class HoverSentive {
    List@ hoverings = new List()

    void clear(){
        self.hoverings.clear()
    }

    void setHover(Node *node, bool hover){
        if (node instanceof ViewBase){
            ViewBase *vb = (ViewBase*)node
            vb.setHover(hover)
        }
    }


    void onmousemove(MouseEvent* e, ViewBase* hitTestView){
        //mouseenter, mouseleave
        List@ addlist = new List();
        List@ dellist = new List();

        List* hoverings = self.hoverings

        //当前所有hover的节点
        List@ parents = hitTestView ? hitTestView->getAncients(true) : new List();
        String@ cursor = str("unset"); //指针

        //找出移除(leave)
        for (int i = hoverings->size() - 1; i >= 0; i--) {
            ViewBase* v = (ViewBase*)hoverings->get(i);
            //不存在，说明要取消hover
            if (!parents.has(v) ) {
                // printf("离开:%p\n", v)
                dellist->add(v);
                hoverings->removeAt(i);
                self.setHover(v, false);
            }
        }
        //找出新增(enter)
        for (int i = 0; i < parents.size(); i++) {
            ViewBase* v = (ViewBase*)parents->get(i);
            //鼠标样式：从叶子向上找到第一个非unset的样式
            if (v instanceof ViewBase) {
                //if (v->style.cursor != "" && v->style.cursor != "unset") {
                //	cursor = v->style.cursor;
                //}
                if (v->cursor.notEquals("") && !v->cursor.equals("unset")) {
                    cursor = v->cursor;
                }

                if (v && !hoverings->has(v)) {
                    // printf("新增:%p\n", v)
                    addlist->add(v);
                    hoverings->add(v);

                    self.setHover(v, true);
                }
            }

        }

        //激发leave事件
        MouseLeaveEvent@ leave = new MouseLeaveEvent();
        leave.name = str("mouseleave");
        leave.clientX = e->clientX
        leave.clientY = e->clientY
        leave.button = 0;
        leave.window = e->window;

        int l = dellist->size()
        for (int i = 0; i < l; i++) {
            ViewBase* v = (ViewBase*)dellist->get(i);
            v->emit(leave);
        }

        //激发enter事件
        MouseEnterEvent@ enter = new MouseEnterEvent();
        enter.name = str("mouseenter");
        enter.clientX = e->clientX
        enter.clientY = e->clientY
        enter.button = 0;
        enter.window = e->window;

        // printf("hover hitTestView:%p, 结束数量:%d, 新增数量:%d\n", hitTestView, dellist.size(), addlist.size())

        l = addlist->size()
        for (int i = 0; i < l; i++) {
            ViewBase* v = (ViewBase*)addlist->get(i);
            v->emit(enter);
        }

        //更新Cursor
        // printf("\t更新cursor:%s\n", cursor.str);
        Cursor_ins()->setCursor(cursor.str);

    }
    void onmouseleave(Window *win){
        MouseEvent@ leave = new MouseEvent();
        leave.name = str("mouseleave");
        leave.clientX = 0;
        leave.clientY = 0;
        leave.button = 0;
        leave.window = win;

        int  l = self.hoverings.size()
        for (int i = 0; i < l; i++){
            ViewBase* v = (ViewBase*)self.hoverings.get(i);
            if (v instanceof ViewBase){
                self.setHover(v, false);
                v.emit(leave);   
            }
        }
        self.hoverings.clear();
    }
}

HoverSentive* sinsHoverSentive(){
    static HoverSentive @ins = null
    if (ins == null){
        ins = new HoverSentive()
    }
    return ins
}

void preprocessMouseEvent(MouseEvent *ev){
    if (ev.isClick()){
        long long nowMs = Time_unixMs()
        int dx = ev.clientX - clickRecord.clientX
        int dy = ev.clientY - clickRecord.clientY
        int threshold = 10 * 10
        long long msThreshold = 400 // ms
        long long msGap = nowMs - clickRecord.clickUnixMs 
        printf("\n\n预处理鼠标事件. dx:%d, dy:%d, msGap:%lld\n",
            dx, dy, msGap
        );
        if (
            clickRecord.button == ev.button
            && msGap < msThreshold
            && dx * dx < threshold 
            && dy * dy < threshold){
            ev.isDblClick = true
        } else {
            ev.isDblClick = false
        }
        if ev.isDblClick {
            printf("触了了双击事件\n\n",);
        }

        //记录上次的点击时间
        clickRecord.clientX = ev.clientX
        clickRecord.clientY = ev.clientY
        clickRecord.clickUnixMs = nowMs
        clickRecord.button = ev.button
    }
}


void propagateViewEvent(ViewBase* view, ViewEvent* ev){



    bool isBreak = false
    //捕获
    List@ nodes = view.getAncients(true)
    ev.isCapture = true
    for (int i = nodes.size() - 1; i >= 0; i --){
        ViewBase* n = (ViewBase*)nodes.get(i);
		ev.currentTarget = n;
		n.emit(ev);

		if (ev.isStopPropagation) {
			break
		}
    }
    if (!ev.isStopPropagation){
        //冒泡
        ev.isCapture = false
        int  l = nodes.size()
        for (int i = 0; i < l; i ++){
            ViewBase* n = (ViewBase*)nodes.get(i);
            ev.currentTarget = n;
            n.emit(ev);
            if (ev.isStopPropagation) {
                break
            }
        }
    }

    ev.currentTarget = null
}