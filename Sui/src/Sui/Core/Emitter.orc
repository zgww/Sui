package SuiCore

#include <stdio.h>
import * from "../../Orc/List.orc"
import * from "../../Orc/String.orc"
import * from "./Event.orc"


class Listener {
    void ctor(){
    }
    void onListenerEvent(Event *event){
    }
}


class Emitter extends Listener {
    List@ listeners = new List()
    //方便设置
    Listener@ listener = null
    ^void (Event *e) cbOnEvent

    
    void addListenerOnce(Listener *listener){
        self.listeners.addOnce(listener)
    }
    void addListener(Listener *listener){
        self.listeners.add(listener)
    }
    void removeListener(Listener *listener){
        self.listeners.remove(listener)
    }
    void emit(Event *event){
        if (self.cbOnEvent != null){
            self.cbOnEvent(event)
        }

        if event.isStopPropagation == 2{
            return;
        }

        self.onEvent(event)

        if event.isStopPropagation == 2{
            return;
        }

        if (self.listener){
            self.listener.onListenerEvent(event)
        }

        if event.isStopPropagation == 2{
            return;
        }
        
        //弄个临时列表出来。 防止在循环过程中修改了列表
        List@ tmps = self.listeners.copy()

        for (int i = 0; i < tmps.size(); i++){
            Listener@ listener = (Listener@)tmps.get(i);
            if (listener){
                listener.onListenerEvent(event);

                if event.isStopPropagation == 2{
                    return;
                }
            }
        }
    }
    void onEvent(Event *event){

    }
}

//事件总线
Emitter* useEbus(){
    static Emitter@ ins = null
    if !ins {
        ins = new Emitter()
    }
    return ins
}



void testEmitter(){
    Emitter@ e = new Emitter()
    e.cbOnEvent = ^void(Event *e){
        printf("cbOnEvent: event Name:%s\n", e.name.str)
    }
    Event@ ev = new Event()
    ev.name = str("点击事件")
    e.emit(ev)
    printf("test emitter\n")
}