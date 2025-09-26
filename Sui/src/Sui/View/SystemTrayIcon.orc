
package SuiView

#include <stdio.h>
#include <stdlib.h>

import * from "../Core/ViewBase.orc"
import * from "../Core/Mouse.orc"
import * from "../Core/Vec2.orc"
import * from "../../Orc/Time.orc"
import * from "../Core/Timer.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "../Core/App.orc"
import * from "../View/MenuNative.orc"
import type * from "../Core/Window.orc"

// 系统托盘图标
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
//     n.create(root)
//     Vec2 p = Mouse_getPos()
//     n.showAt(0, 0)
// }

class SystemTrayIcon {
    int uid; //唯一标识 

    void *data
    String@ iconPath

    void setIconPath(const char *iconPath){
        self.iconPath = str(iconPath)
    }
    void ctor(){
        static int id = 100
        id++
        self.uid = id
    }
    extern void dtor(){

    extern bool initData()

    bool init(){
        bool ok = self.initData()
        if ok {
            //加入列表
            List@ trays = SystemTrayIcons_use();
            trays.add(self)
        }
        return ok
    }

    extern bool doDestroy()

    void destroy(){
        bool ok = self.doDestroy()
        if ok {
            List@ trays = SystemTrayIcons_use();
            trays.remove(self)
        }
    }

}
//统一释放托盘。 不然windows下的托盘不会随着程序退出而退出
static void onappexit(){
    printf("on app exit\n")
    List@ list = SystemTrayIcons_use();

    //必须倒序,因为destroy会remove from trays
    for (int i = list.size() - 1; i >= 0 ; i--){
        SystemTrayIcon@ tray = (SystemTrayIcon@)list.get(i)
        if tray{
            tray.destroy()
        }
    }
}
List@ SystemTrayIcons_use(){
    static List@ list = null
    if !list {
        list = new List()
        atexit(onappexit)
    }
    return list
}
SystemTrayIcon@ SystemTrayIcons_findByUid(int uid){
    List@ list = SystemTrayIcons_use();

    for (int i = 0; i < list.size(); i++){
        SystemTrayIcon@ tray = (SystemTrayIcon@)list.get(i)
        if tray && tray.uid == uid {
            return tray;
        }
    }
    return null
}
void SystemTrayIcon_onMouseData(MouseData md){
    printf("on SystemTrayIcon mouseData. uid:%d\n", md.uid)
    SystemTrayIcon@ tray = SystemTrayIcons_findByUid(md.uid)
    if tray {
        printf("finded. tray. uid:%d\n", tray.uid)

        if md.isDoubleClick{
            ^void onActive(MenuNativeItem *item){
                if item.label.equals("delete icon"){
                    tray.destroy()
                }
                if item.label.equals("exit"){
                    exit(0)
                }
            }

            mkMenuNativeItem(null, str(""), onActive).{
                mkMenuNativeItem(o, str("exit"), onActive).{ }
                mkMenuNativeItem(o, str("delete icon"), onActive).{ }
                mkMenuNativeItem(o, str("menu3"), onActive).{ }
                mkMenuNativeItem(o, str("menu4"), onActive).{ }
                mkMenuNativeItem(o, str("menu5"), onActive).{ }

                MenuNative@ n = new MenuNative()
                n.windowId = md.windowId
                n.create(o)
                Vec2 p = Mouse_getPos()
                printf("show At:%f, %f\n", p.x, p.y)
                n.showAtMouse()
            }
        }
    }
}

//取得当前弹出的菜单
// MenuNative *getCurrentMenuNative(){

// }