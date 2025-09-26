package SuiDesigner

#include <stdio.h>
#include "../Orc/Orc.h"

import * from "../Sui/View/Button.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/Core/App.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Orc/Time.orc"
import * from "../Orc/String.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/Mouse.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Inset.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Sui/Layout/LayoutAlign.orc"
import * from "../Sui/View/Checkbox.orc"
import * from "../Sui/View/Switch.orc"
import * from "../Sui/View/Slider.orc"
import * from "../Sui/View/ProgressView.orc"
import * from "../Sui/View/TableView.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/View/ColorPalete.orc"
import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/MenuNative.orc"
import * from "../Sui/View/Select.orc"
import * from "../Sui/View/DockLayout.orc"
import * from "../Sui/View/SystemTrayIcon.orc"
import * from "../SuiDesigner/Asset/FileWatcher.orc"
import * from "../SuiDesigner/Asset/AssetDirView.orc"
import * from "../SuiDesigner/Asset/AssetDirTreeView.orc"
import * from "../SuiDesigner/Serial/BiJson.orc"
import * from "../SuiDesigner/SceneView.orc"
import * from "../SuiDesigner/SceneHierView.orc"
import * from "../SuiDesigner/Inspector.orc"
import * from "../SuiDesigner/InspectorView.orc"
import * from "../SuiDesigner/Theme.orc"
import * from "../SuiDesigner/Project.orc"
import * from "../SuiDesigner/UiAction.orc"


//菜单栏控制器
class MenuBarCtrl {
    //需要手动设置
    // Window@ window;


    // idle->popup->movePopup
    String@ status = str("idle");
    MenuButton@ curMenu;
    MenuButton@ nextMenu;
    MenuNative@ popup;


    void dtor(){
        printf("~MenuBarCtrl\n")
    }
    
    ^MenuNativeItem@ (MenuButton *mbutton) cbCreateMenuNativeItem = null


    void showPopup(MenuButton@ mbutton){
        printf("set Trigging:%p\n", mbutton)
        self.curMenu = mbutton
        self.nextMenu = null
        // String@ btn2 = btn;

        if !self.cbCreateMenuNativeItem{
            return
        }

        MenuNativeItem@ item = self.cbCreateMenuNativeItem(mbutton)

        MenuNative@ n = new MenuNative()
        self.popup = n
        n.cbOnDismiss = ^void(){
            printf("\ncbOnDismiss:%p\n\n", self);
            self.onPopupDismiss()
        }
        n.create(item)
        Rect r = mbutton.get_abs_rect()
        n.showAt(r.x, r.bottom())
    }
    void onclick(MenuButton@ mbutton, MouseEvent *me){
        self.showPopup(mbutton)
    }
    void onmove(MenuButton@ menu, MouseEvent *me){
        if !self.popup {
            return
        }
        if (!self.curMenu){
            // printf("onmove not curMenu\n")
            return;
        }
        if (menu == self.curMenu){
            // printf("onmove curMenu:%p menu:%p\n", self.curMenu, menu)
            return
        }
        if (self.popup){
            printf("destroy popup:%p, %p\n", self.popup, self.curMenu)
            if self.curMenu {
                self.curMenu.hover = false
                self.curMenu.react()
            }
            self.popup.destroy()
            self.popup = null
            self.curMenu = null
        }
        if (menu && self.curMenu == null){
            menu.hover = true
            menu.react()
            // self.showPopup(menu)
            // printf("onmove trigger menu.onClick. menu:%p\n", menu)
            // self.curMenu = menu
            self.nextMenu = menu
            // mkTimerTimeout(^void(){
            printf("menu.onClick\n");
            // self.showPopup(menu)
            // }, 100)
        }
    }
    void setPopup(MenuNative@ popup, MenuButton@ curMenu){
        printf("setPopup:%p, %p\n", popup, curMenu)
        self.curMenu = curMenu
        self.popup = popup
    }
    void onPopupDismiss(){
        printf("onPopupDismiss:%p next:%p\n", self.popup, self.nextMenu)
        if self.nextMenu {
            MenuButton@ m = self.nextMenu
            self.nextMenu = null
            self.showPopup(m)
        }
        // self.popup = null
        // self.curMenu = null
    }
}