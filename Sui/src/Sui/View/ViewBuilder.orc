package SuiView

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../Orc/Orc.h"

import * from "../../Orc/ScopeData.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Map.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/String.orc"

import * from "../Core/View.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Inset.orc"
import * from "../Core/ViewBase.orc"
import * from "../Core/Node.orc"
import * from "../Core/Emitter.orc"
import * from "../Core/Frame.orc"
import * from "../Core/Window.orc"
import type * from "../Layout/LayoutLinear.orc"
// import * from "./ImageView.orc"
// import * from "./TextView.orc"

 
 
 
 
//用来存放需要clear的节点。react过程新建的节点都要放进来被管理

// static List@ getList(){
//     static List@ list = null
//     if (list == null){
//         list = new List()
//     }
//     return list
// }

Node@ gocNode(void *sp, Node* parent, Vtable_Object*vt){
    char key[32];
    snprintf(key, 32, "%p", sp);


    Map* unusedMap = get_unusedMapForReact(parent)
    View* n = (View*)unusedMap.get(key)
    
    if (!n){
        // Object@ tmp = vt.make(&tmp)
        n = vt.make(&n);
    } else {
        n.isNewForReact = false //标记为非新建
    }

    strcpy(n.key, key)

    unusedMap.del(key)


    Map* map = get_mapForReact(parent)
    map.put(key, n)

    //有内部react
    if parent.hasInnerReact && !parent.isInInnerReact() {
        if parent.outKids == null {
            parent.outKids = new List()
        }
        parent.outKids.insert(n, parent._appendIndexForReact)
    }
    else {
        //插入到指定位置
        parent.insertChild(n, parent._appendIndexForReact)
    }
    parent._appendIndexForReact = parent._appendIndexForReact + 1

    // List@ lst = getList()
    // lst.add(n)
    return n
}
// long long getStackKey(int offset){
//     void *addr =  __builtin_return_address(offset + 1)
//     return (long long)addr;
// }
View@ mkView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    View@ n = (View@)gocNode(sp, (Node*)parent, View)
    return n
}

// TextView@ mkTextView(void* parent, long long key){
//     void *addr =  __builtin_return_address(0)
//     void *sp = key ? (void*)key: addr
//     return (TextView@)gocNode(sp, (Node*)parent, TextView)
// }
// T@ r<T>(Vtable_Object<T> *vt){
//     void *sp = __builtin_return_address(1)
//     return (T@)gocNode(sp, View)
// }

// void clearUnusedNodes(Node *cur){
//     //逆序直到cur
//     List@ lst = getList()
//     for (int i = lst.size() - 1; i >= 0; i--){
//         Node@ n = (Node@)lst.get(i);

//         clearUnusedKids(n)

//         lst.removeAt(i)
//         if (n == cur){
//             break;
//         }
//     }
// }
// Map@ get_mapForReact(Node* n){
//     if (!n._mapForReact){
//         n._mapForReact = new Map()
//     }
//     return n._mapForReact
// }
// Map@ get_unusedMapForReact(Node* n){
//     if (!n._unusedMapForReact){
//         n._unusedMapForReact = new Map()
//     }
//     return n._unusedMapForReact
// }
// static void clearUnusedKids(Node *n){
//     //遍历 _unusedMapForReact， 删除节点， 清空map
//     Map@ unused = get_unusedMapForReact(n)
//     Map@ map = get_mapForReact(n)

//     List@ keys = unused.keys()
//     //删除未使用的节点
//     for (int i = 0, l = keys.size(); i < l; i++){
//         String@ key = keys.get(i);
//         Node @unusedNode = (Node*)unused.get(key.str)
//         unusedNode.removeSelf()
//     }

//     unused.clear()

//     n._mapForReact = unused
//     n._unusedMapForReact = map
// }

class TestPlaceView extends View {
    void ctor(){
        self.hasInnerReact = true
    }
    void react(){
        self.startInnerReact()


        Node* o = self
        layoutLinear(o, 0).{
            o.asColumn().aic()

            o.placeKid(self.outKids.get(2))
            mkView(o, 0).{
                o.width = 200
                o.height = 100
                o.padding.setAll(10)

                o.backgroundColor = 0x7f0000ff

                o.placeKid(self.outKids.get(0))
            }
            o.placeKid(self.outKids.get(1))
        }

        self.endInnerReact()
    }
}
TestPlaceView@ mkTestPlaceView(void* parent, long long key){
    return (TestPlaceView@)gocNode(key?(void*)key:__builtin_return_address(0) , (Node*)parent, TestPlaceView)
}
void testPlaceKidsTo(){

    new Window().{ 
        Window* win = o

        new LayoutLinear().{
            o.jcc().aic()
            win.setRootView(o)

        }
        
        ^void react = ^void(){
            win.rootView.{
                mkTestPlaceView(o,0).{
                    o.backgroundColor = 0x6f00ff00
                    o.padding.setAll(20)
                    mkView(o, 0).{
                        o.width = 100
                        o.height = 100
                        o.backgroundColor = 0x3fff0000
                    }
                    mkView(o, 0).{
                        o.width = 100
                        o.height = 100
                        o.backgroundColor = 0x4fffff00
                    }
                    mkView(o, 0).{
                        o.width = 100
                        o.height = 100
                        o.backgroundColor = 0x5fff00ff
                    }
                }
            }
        }
        react()
        react()
        react()
        react()
        react()

        o.setTransparent()
        o.setTitle("测试outKids")
        o.setSize(640, 480)
        o.show()
    }

}