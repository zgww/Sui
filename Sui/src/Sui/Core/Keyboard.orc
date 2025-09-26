package SuiCore

#include <stdio.h>

import * from "./KeyEvent.orc"
import * from "./Window.orc"
import * from "./App.orc"
import * from "../../Orc/String.orc"



struct KeyboardData {
    //mousedown|mousemove|mouseup
    // const char* eventType
    //1:left, 2:middle, 3:right button

    int char_code
    //临时指针,不需要释放
    const char *key;

    long long windowId
    bool isKeyDown
    bool isKeyUp
    bool shift
    bool ctrl
    bool alt
}
KeyEvent@ newKeyEvent_fromKeyboardData(KeyboardData* kd){
    App@ app = App_use()
    Window@ win = app.findWindowById(kd.windowId)

    KeyEvent@ ke = new KeyEvent()
    ke.char_code = kd.char_code
    ke.key = str(kd.key)
    ke.window = win
    ke.isKeyDown = kd.isKeyDown
    ke.isKeyUp = kd.isKeyUp
    ke.shift = kd.shift
    ke.ctrl = kd.ctrl
    ke.alt = kd.alt
    return ke
}
void Keyboard_onKeyDown(KeyboardData* kd){
    printKeyboardData(kd);
    KeyEvent@ ke = newKeyEvent_fromKeyboardData(kd)
    ke.dispatch()
}
void Keyboard_onKeyUp(KeyboardData* kd){
    printKeyboardData(kd);
    KeyEvent@ ke = newKeyEvent_fromKeyboardData(kd)
    ke.dispatch()
}
void printKeyboardData(KeyboardData* kd){
    printf("KeyboardData. char_code:%d, key:%s, windowId:%lld, isKeyDown:%d, isKeyUp:%d, shift:%d, ctrl:%d, alt:%d\n",
        kd.char_code, kd.key, kd.windowId, kd.isKeyDown, kd.isKeyUp, kd.shift, kd.ctrl, kd.alt);
}
