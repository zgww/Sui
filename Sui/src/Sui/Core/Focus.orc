package SuiCore

#include <stdio.h>

import * from "./Node.orc"
import * from "./Event.orc"

class FocusEvent extends Event{
    // false: blur, true: focus
    bool isFocus = false
    bool isBlur = false
    Node@ source = null

    void init(Node* source, bool b){
        self.source = source
        self.isFocus = b
        self.isBlur = !b
    }
}

/// 聚焦管理
class Focus{
    Node@ focusNode = null

    // ^void(Node* node) onNodeFocus = null
    // ^void(Node* node) onNodeBlur = null

    void focus(Node* node){
        if (node == self.focusNode){
            return
        }
        
        if (self.focusNode != null){
            FocusEvent@ ev = new FocusEvent()
            ev.init(self.focusNode, false)
            self.focusNode.emit(ev)
            // if (self.onNodeBlur != null){
            //     self.onNodeBlur(self.focusNode)
            // }
        }

        self.focusNode = node

        FocusEvent@ ev = new FocusEvent()
        ev.init(self.focusNode, true)
        self.focusNode.emit(ev)
        // if (self.onNodeFocus != null){
        //     self.onNodeFocus(node)
        // }
    }
    void blurNode(Node* n){
        if (self.focusNode == n){
            self.blur()
        }
    }
    void blur(){
        if (self.focusNode != null){
            FocusEvent@ ev = new FocusEvent()
            ev.init(self.focusNode, false)
            self.focusNode.emit(ev)
            // if (self.onNodeBlur != null){
            //     self.onNodeBlur(self.focusNode)
            // }
            self.focusNode = null
        }
    }
    Node* getFocusNode(){
        return self.focusNode
    }
    bool isFocus(Node* node){
        return self.focusNode == node
    }
    bool hasFocus(){
        return self.focusNode != null
    }
    // void clear(){
    //     self.focusNode = null
    // }
}

Focus* insFocus(){
    static Focus@ ins = null
    if (ins == null){
        ins = new Focus()
    }
    return ins
}