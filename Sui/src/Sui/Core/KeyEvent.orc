package SuiCore

#include <stdio.h>

import * from "./Event.orc"
import * from "./MouseEvent.orc"
import * from "../../Orc/String.orc"
import type * from "./Window.orc"
import * from "./App.orc"
import * from "./Focus.orc"

//基本文本事件
class TextEventBase extends ViewEvent {
    Window@ window = null
    void dispatch(){
        Focus* f =  insFocus()
        //分发到焦点节点
        if (f.focusNode != null){
            f.focusNode.emit(self)
        }
        //分发到window
        if (!self.isStopPropagation && self.window != null){
            self.window.emit(self)
        }
        //分发到全局
        // if (!self.isStopPropagation){
        //     App_use().emit(self)
        // }
    }
}
//文本输入法事件(输入法合成事件)
class TextEditingEvent extends TextEventBase{
    //当前输入法的输入字符
    String@ text = null;
    int start = 0; //输入法光标位置   单位：字符
    int length = 0; //输入法光标后字符长 单位：字符
    void reset(){
        self.start = 0
        self.length = 0
    }
    bool is_editing(){
        return self.start + self.length > 0;
    }
    int total_rune_length(){//字符总长
        return self.start + self.length
        // if (self.text == null){
        //     return 0
        // }
        // int l = self.text.length()
        // return l
    }
}
//输入法合成事件
void dispatchImeEndComposition(long long windowId){
    printf("输入法合成结束事件\n");
}
//结束输入法合成
void dispatchImeComposition(
    const char *text,
    int start, 
    int length,
    long long windowId
){
    printf("输入法合成事件 text:%s, start:%d, length:%d, windowId:%lld\n",
    text, start,length, windowId);

    App@ app = App_use()
    Window@ win = app.findWindowById(windowId)

    TextEditingEvent@ e = new TextEditingEvent()
    e.text = str(text);
    e.start = start
    e.length = length
    e.window = win

    dispatchEventToFocusNode(e, win)
}



//输入事件
class TextInputEvent extends TextEventBase{
    String@ text = null
}

void dispatchTextInputEvent(const char *text, long long windowId){
    App@ app = App_use()
    Window@ win = app.findWindowById(windowId)

    TextInputEvent@ e = new TextInputEvent()
    e.text = str(text);
    e.window = win
    printf("dispatchTextInputEvent:%s\n", e.text.str);

    dispatchEventToFocusNode(e, win)
}

/// 布局上下文
class KeyEvent extends Event {
    //编码，请优先使用Key
    int char_code = 0;
    String@ key = null

    bool isKeyDown = false
    bool isKeyUp = false

    bool shift = false
    bool ctrl = false
    bool alt = false

    Window@ window = null

    void setIsKeyDown(bool isKeyDown){
        self.isKeyDown = isKeyDown
        self.isKeyUp = !isKeyDown
    }
    void dispatch(){
        dispatchEventToFocusNode(self, self.window)
    }
}
void dispatchEventToFocusNode(Event *evt, Window *window){
    Focus* f =  insFocus()
    //分发到焦点节点
    if (f.focusNode != null){
        f.focusNode.emit(evt)
    }
    //分发到window
    if (!evt.isStopPropagation && window != null){
        window.emit(evt)
    }
}


//窗体焦点事件
class WindowFocusEvent extends Event{
    bool isFocus = false
    bool isBlur = false
    Window@ window = null
}
//派发事件实例
void dispatchWindowFocusEvent(WindowFocusEvent *e){
    Focus* f =  insFocus()
    //分发到焦点节点
    if (f.focusNode != null){
        f.focusNode.emit(e)
    }
    //分发到window
    Window *window = e.window
    if (!e.isStopPropagation && window != null){
        window.emit(e)
    }
}