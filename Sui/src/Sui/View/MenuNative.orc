
package SuiView

#include <stdio.h>
#include "../../../UrgcDll/urgc_api.h"
#include "../../Orc/Orc.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/Mouse.orc"
import * from "../Core/Vec2.orc"
import * from "../../Orc/Time.orc"
import * from "../Core/Timer.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "../Core/App.orc"
import type * from "../Core/Window.orc"

static int gMenuId = 10000;
static MenuNative@ currentMenuNative


class MenuNativeItem{
	int commandId = 0
	int id = 0 //用于使用者识别的
    String@ cmd = str("") //用于使用者识别的
    String@ label
    ^void (MenuNativeItem *item) onActive

    List@ children = new List()

    void ctor(){
        self.commandId = gMenuId
        self.id = gMenuId
        gMenuId = gMenuId + 1
    }
    void dtor(){
        // printf(".MenuNativeItem\n");
    }

    void append(MenuNativeItem *item){
        self.children.add(item)
    }
}
MenuNativeItem@ mkMenuNativeItem(MenuNativeItem* parent, String@ label, ^void (MenuNativeItem*item) onActive){
    MenuNativeItem@ ins = new MenuNativeItem()
    ins.label = label
    if label{
        ins.cmd.set(label.str)
    }
    ins.onActive = onActive

    if (parent){
        parent.append(ins)
    }

    return ins
}

// 原生弹出式菜单
// 用法：
// ^void onActive(MenuNativeItem *item){
// }
// mkMenuNativeItem(null, str(""), onActive).{
//     mkMenuNativeItem(o, str("menu1"), onActive).{ }
//     mkMenuNativeItem(o, str("menu2"), onActive).{ }
//     mkMenuNativeItem(o, str("menu3"), onActive).{ }
//     mkMenuNativeItem(o, str("menu4"), onActive).{ }
//     mkMenuNativeItem(o, str("menu5"), onActive).{ }

//     MenuNative@ n = new MenuNative()
//     n.create(o)
//     n.showAtMouse()
////   Vec2 p = Mouse_getPos()
////   n.showAt(0, 0)
// }
class MenuNative {
    long long id // menu handle
    MenuNativeItem@ root
    long long windowId

    ^void () cbOnDismiss

    void ctor(){
        currentMenuNative = self
    }
    void dtor(){
        printf(".MenuNative\n");
    }

    void create(MenuNativeItem *root){
        self.root = root
        self.id = self.buildNativeMenu(root)

        // self.id = self.createNativeMenu()
        // self.buildNativeMenuItems(root, self.id)
    }
    extern long long buildNativeMenu(MenuNativeItem* root)

    void show(){
        Vec2 s = Mouse_getPos()
        self.showAtScreenPosition(s.x, s.y)
    }
    extern void showAt(int clientX, int clientY)
    extern void showAtScreenPosition(int screenX, int screenY)

    void showAtMouse(){
        Vec2 p = Mouse_getPos()
        self.showAtScreenPosition(p.x, p.y)
    }

    void onDismiss(){
        printf("\n\nMenuNative菜单已经消失.\n");
        if (self.cbOnDismiss){
            self.cbOnDismiss()
        }

        Timer* t =mkTimerTimeout(^void(){
            printf("\nMenuNative.onDismiss Timeout\n");
            currentMenuNative = null
        }, 200)
        // Time_sleepMs(10000);
        // printf("report sou...\n");
        // urgc_report_sources_of(t);
    }
    extern void destroy()

    bool dispatchCommand(MenuNativeItem* item, Window* win, int commandId){
        if (item.commandId == commandId){
            if (item.onActive){
                item.onActive(item)
            }
            return true
        }
        int l = item.children.size()
        for (int i = 0; i < l; i++){
            MenuNativeItem *kid = (MenuNativeItem*)item.children.get(i)
            bool succ = self.dispatchCommand(kid, win, commandId)
            if (succ){
                return true;
            }
        }
        return false
    }
}
//取得当前弹出的菜单
// MenuNative *getCurrentMenuNative(){

// }


void MenuNative_doCommand(long long windowId, int commandId){
    App@ app = App_use()
    Window@ win = app.findWindowById(windowId)

    printf("windowId:%lld win:%s, command:%d\n", windowId,
    win == null
    ? "Null"
    : win.getTitle().str
    , commandId
    );
    if (currentMenuNative){
        currentMenuNative.dispatchCommand(
            currentMenuNative.root,
            win, commandId)

    }
}