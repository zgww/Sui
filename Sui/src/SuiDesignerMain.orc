#include <stdio.h>
#include "./Orc/Orc.h"

#include "../UrgcDll/urgc_api.h"
#include "../include/miniaudio.h"

import * from "./Sui/View/Button.orc"
import * from "./Sui/Core/Image.orc"
import * from "./Sui/View/ImageView.orc"
import * from "./Sui/View/TextView.orc"
import * from "./Sui/View/ViewBuilder.orc"
import * from "./Sui/Core/App.orc"
import * from "./Sui/Core/Timer.orc"
import * from "./Sui/Core/Window.orc"
import * from "./Orc/Time.orc"
import * from "./Orc/String.orc"
import * from "./Orc/Path.orc"
import * from "./Orc/List.orc"
import * from "./Orc/Map.orc"
import * from "./Orc/Math.orc"
import * from "./Sui/Core/Node.orc"
import * from "./Sui/Core/Emitter.orc"
import * from "./Sui/Core/Event.orc"
import * from "./Sui/Core/ViewBase.orc"
import * from "./Sui/Core/Mouse.orc"
import * from "./Sui/Core/MouseEvent.orc"
import * from "./Sui/Core/View.orc"
import * from "./Sui/Core/Rect.orc"
import * from "./Sui/Core/Vec2.orc"
import * from "./Sui/Core/Inset.orc"
import * from "./Sui/Core/Frame.orc"
import * from "./Sui/Dialog/MessageDialog.orc"
import * from "./Sui/Layout/LayoutLinear.orc"
import * from "./Sui/Layout/LayoutAlign.orc"
import * from "./Sui/View/Checkbox.orc"
import * from "./Sui/View/Switch.orc"
import * from "./Sui/View/Slider.orc"
import * from "./Sui/View/ProgressView.orc"
import * from "./Sui/View/EditText.orc"
import * from "./Sui/View/TableView.orc"
import * from "./Sui/View/ScrollArea.orc"
import * from "./Sui/View/ColorPalete.orc"
import * from "./Sui/View/TreeView.orc"
import * from "./Sui/View/MenuNative.orc"
import * from "./Sui/View/Select.orc"
import * from "./Sui/View/DockLayout.orc"
import * from "./Sui/View/SystemTrayIcon.orc"
import * from "./SuiDesigner/Asset/FileWatcher.orc"
import * from "./SuiDesigner/Asset/AssetDirView.orc"
import * from "./SuiDesigner/Asset/AssetDirTreeView.orc"
import * from "./SuiDesigner/Serial/BiJson.orc"
import * from "./SuiDesigner/SceneView.orc"
import * from "./SuiDesigner/SceneHierView.orc"
import * from "./SuiDesigner/Inspector.orc"
import * from "./SuiDesigner/InspectorView.orc"
import * from "./SuiDesigner/Theme.orc"
import * from "./SuiDesigner/Project.orc"
import * from "./SuiDesigner/UiAction.orc"
import * from "./Json/Json.orc"
import * from "./MainProject.orc"
import * from "./SuiDesigner/EditCtx.orc"
import * from "./SuiDesigner/SpriteSheetEditor.orc"
import * from "./SuiDesigner/TileEditor.orc"
import * from "./SuiDesigner/W3eEditor.orc"
import * from "./SuiDesigner/SglEditor.orc"
import * from "./SuiDesigner/MdxReader.orc"
import * from "./SuiDesigner/Insp.orc"
import * from "./Sgl/Material.orc"
import * from "./Sgl/Buffer.orc"
import * from "./Sgl/Geometry.orc"
import * from "./Sgl/GeometryHeightMap.orc"
import * from "./Sui/Core/TestMath.orc"

DockLayout@ dockLayoutIns = null
//菜单栏控制器
class MenuBarCtrl {
    // idle->popup->movePopup
    String@ status = str("idle");
    MenuButton@ curMenu;
    MenuButton@ nextMenu;
    MenuNative@ popup;

    Window@ window;

    void dtor(){
        printf("~MenuBarCtrl\n")
    }


    void showPopup(MenuButton@ mbutton){
        printf("set Trigging:%p\n", mbutton)
        self.curMenu = mbutton
        self.nextMenu = null
        // String@ btn2 = btn;

        ^void onActive(MenuNativeItem*item){
            printf("\n\n========================================onActive menu:%s\n", item.label.str)
            if (item.label.equals("Close")){
                exit(0);
            }
            if (item.label.equals("保存场景")){
                // MessageDialog_alert("保存", "tip")
                UiAction_savePrefab()
            }
            if (item.label.equals("关闭场景")){
                // MessageDialog_alert("保存", "tip")
                UiAction_closeCurrentPrefab()
            }
            if (item.label.equals("退出")){
                exit(0);
            }
            if (item.label.equals("NewWindow")){
                show_newWindow(null)
            }
            else if (item.label.equals("MaxWindow")){
                self.window.maximize();
            }
            else if (item.label.equals("SaveDockLayout")){
                Json@ jo = dockLayoutIns.root.toJson()
                String@ s = jo.dump()
                printf("docklayout:\n%s\n", s.str);
                Path_writeText("mainlayout.json", s.str)
            }
            else if (item.label.equals("LoadDockLayout")){
                String@ text = Path_readText("mainlayout.json")
                printf("text:%s\n", text.str);
                Json@ jo = Json_parse(text.str)
                DockItem@ root = DockItem_fromJson(jo)

                dockLayoutIns.root = root;
                dockLayoutIns.trigger_react()


            }
            else {
                MessageDialog_alert(item.label.str, "tip")
            }
        }
        mkMenuNativeItem(null, null, null).{
            if mbutton.text.equals("文件"){
                mkMenuNativeItem(o, str("新建场景"), onActive)
                mkMenuNativeItem(o, str("打开场景"), onActive)
                mkMenuNativeItem(o, str("保存场景"), onActive)
                mkMenuNativeItem(o, str("最近打开"), onActive).{
                    mkMenuNativeItem(o, str("场景1"), onActive)
                    mkMenuNativeItem(o, str("场景2"), onActive)
                }
                mkMenuNativeItem(o, str("另存为场景"), onActive)
                mkMenuNativeItem(o, str("保存所有场景"), onActive)
                mkMenuNativeItem(o, str("关闭场景"), onActive)
                mkMenuNativeItem(o, str("重载已保存的场景"), onActive)
                mkMenuNativeItem(o, str("设置"), onActive)
                mkMenuNativeItem(o, str("退出"), onActive)
            }
            else if mbutton.text.equals("项目"){
                mkMenuNativeItem(o, str("退出到项目列表"), onActive)
                mkMenuNativeItem(o, str("重新加载当前项目"), onActive)
                mkMenuNativeItem(o, str("项目设置"), onActive)
                mkMenuNativeItem(o, str("导出"), onActive)
                mkMenuNativeItem(o, str("工具-孤立资源浏览器"), onActive)
                mkMenuNativeItem(o, str("打开用户数据目录"), onActive)
            }
            else if mbutton.text.equals("帮助"){
                mkMenuNativeItem(o, str("在线文档"), onActive)
                mkMenuNativeItem(o, str("社区"), onActive)
                mkMenuNativeItem(o, str("问与答"), onActive)
                mkMenuNativeItem(o, str("搜索帮助"), onActive)
                mkMenuNativeItem(o, str("报告问题"), onActive)
                mkMenuNativeItem(o, str("支持Sui开发"), onActive)
                mkMenuNativeItem(o, str("关于Sui"), onActive)
                mkMenuNativeItem(o, str("关于OrcLang"), onActive)
            }
            else if mbutton.text.equals("调试"){
                mkMenuNativeItem(o, str("运行预览"), onActive)
                mkMenuNativeItem(o, str("使用远程调试器"), onActive)
                mkMenuNativeItem(o, str("显示网格"), onActive)
                mkMenuNativeItem(o, str("显示路径"), onActive)
                mkMenuNativeItem(o, str("显示避障"), onActive)
                mkMenuNativeItem(o, str("显示碰撞区域"), onActive)
                mkMenuNativeItem(o, str("附加到进程"), onActive)
            }
            else if mbutton.text.equals("窗口"){
                mkMenuNativeItem(o, str("NewWindow"), onActive)
                mkMenuNativeItem(o, str("MaxWindow"), onActive)
                mkMenuNativeItem(o, str("重置布局"), onActive)
                mkMenuNativeItem(o, str("保存布局"), onActive)
                mkMenuNativeItem(o, str("加载布局"), onActive)
            }
            else if mbutton.text.equals("视图"){
                mkMenuNativeItem(o, str("Node"), onActive). {o.cmd = str("AddView_Node")}
                mkMenuNativeItem(o, str("ViewBase"), onActive). {}
                mkMenuNativeItem(o, str("View"), onActive). {}
                mkMenuNativeItem(o, str("Button"), onActive). {}
                mkMenuNativeItem(o, str("Slider"), onActive). {}
                mkMenuNativeItem(o, str("Switch"), onActive). {}
                mkMenuNativeItem(o, str("ImageView"), onActive). {}
                mkMenuNativeItem(o, str("TextView"), onActive). {}
                mkMenuNativeItem(o, str("EditText"), onActive). {}
                mkMenuNativeItem(o, str("ListView"), onActive). {
                    mkMenuNativeItem(o, str("TreeView"), onActive). {}
                    mkMenuNativeItem(o, str("TableView"), onActive). {}
                }
                mkMenuNativeItem(o, str("ProgressView"), onActive). {}
            }
            else {
                // mkMenuNativeItem(o, str("Open"), onActive)
                // mkMenuNativeItem(o, str("Close"), onActive)
                // mkMenuNativeItem(o, str("Save"), onActive)
                // mkMenuNativeItem(o, str("Open Recent"), onActive)
                // mkMenuNativeItem(o, str("Profile"), onActive)
                mkMenuNativeItem(o, str("About"), onActive)
                // mkMenuNativeItem(o, str("NewWindow"), onActive)
                // mkMenuNativeItem(o, str("MaxWindow"), onActive)
                // mkMenuNativeItem(o, str("SaveDockLayout"), onActive)
                // mkMenuNativeItem(o, str("LoadDockLayout"), onActive)
            }

            MenuNative@ n = new MenuNative()
            self.popup = n
            n.cbOnDismiss = ^void(){
                printf("\ncbOnDismiss:%p\n\n", self);
                self.onPopupDismiss()
                o = null
            }
            n.create(o)
            Rect r = mbutton.get_abs_rect()
            n.showAt(r.x, r.bottom())
        }
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


class Tmp {
    int i = 0;
    int j = 123
    double dv = 123.03
}
void testMeta(){
    Tmp@ tmp = new Tmp();
    OrcMetaField *f = orc_getMetaField(Tmp, "dv");
    double * pdouble =  ((char *)tmp) + OrcMetaField_getAddress(f);
    *pdouble = 23.2;
    printf("get mf :%p dv:%f %f\n", f, tmp.dv, *pdouble);
}

void testWindow2(){

    printf("TestWindow from orc\n");
    App@ app = App_use()

    long long ms = Time_unixMs()
    printf("now ms:%lld\n", ms)
    Time_sleepMs(1000*2)
    {
        long long ms = Time_unixMs()
        printf("now ms:%lld\n", ms)
    }
    printf("done\n")
}


class TmpListener extends Listener {
    void onListenerEvent(Event *ev){
        const char *className = Object_getClassName(ev)
        printf("监听到事件:%s\n", className )
        if (ev instanceof MouseEvent){
            MouseEvent *me = (MouseEvent*)ev
            printf("\t鼠标事件:%s\n", me.toString().str)

            if (me.isClickInBubble()){
                MessageDialog_alert("你1点击了我", "标题")

                me.stopPropagation()
            }
        }
    }
}
class TmpListener2 extends Listener {
    void onListenerEvent(Event *ev){
        printf("监听到事件2:%s\n", Object_getClassName(ev))
        if (ev instanceof MouseEvent){
            MouseEvent *me = (MouseEvent*)ev
            printf("\t鼠标事件2:%s\n", me.toString().str)
            if (me.isClickInBubble()){
                MessageDialog_alert("你2点击了我", "标题")
                
                me.stopPropagation()
            }
        }
    }
}
class ClickListener extends MouseEventListener{
    
    void onEvent(MouseEvent *ev){
        if (ev.isClickInBubble()){
            ev.stopPropagation()
            printf("按钮点击事件 capture:%d\n", ev.isCapture);
            MessageDialog_alert("点击了按钮。你2点击了我", "标题")
        }
    }
}
void show_newWindow(Window *parent){
    Window@ win = new Window()
    win.setSize(300, 300)
    win.{
        win.rootView.{
            o.name = str("rootDiv")
            layoutLinear(o, 0)~{
                mkTextView(o, 0)~{
                    o.margin.setAll(10)
                    o.backgroundColor = 0xffeecccc;
                    o.setText(str("hello world2"))
                } 
                mkTextView(o, 0)~{
                    o.margin.setAll(10)
                    o.backgroundColor = 0xffeecccc;
                    o.setText(str("hello world2"))
                } 
            }
        }

        o.setTitle("SuiDesigner")
        printf("setTitle\n");
        o.setRect(100, 100, 800, 400)
        o.setOwner(parent)

        o.show()
    }
}
void startSuiDesigner(){
    if (false){
        printf("testWindow  \n")
        return;
    }
    // printf("TestWindow from orc\n");
    App@ app = App_use()

    // Project_ins().init("D:/ws/far/karui-vs-plain/asset")
    String@ projectDirPath = Path_dirname(Path_getExecutionPath().str).add("/asset")
    printf("projectDirPath:%s\n", projectDirPath.str)
    Project_ins().init(projectDirPath.str)
    EditCtx_ins().init()


    Theme* t = themeIns()

    Window@ win = new Window()


    new LayoutLinear().{
        o.direction = str("column")
        // o.backgroundColor = 0x230090ff
        o.backgroundColor = t.bg1
        o.alignItems = str("stretch")

        win.setRootView(o)
    }


    win.{
        if 1 {


        win.rootView.{
            o.name = str("rootDiv")
            // layoutLinear(o, 0)~{
            //     imageView(o, 0)~{
            //         o.setSrc(
            //             str("asset/icon/arrow-down.png")
            //         )
            //         o.margin.right = 10
            //     }
            // }
            if (1){
                //菜单
                layoutLinear(o, 0).{
                    // o.height = 30
                    o.backgroundColor = t.menubar_bg
                    // o.backgroundColor = 0xcc000000
                    o.padding.setAxis(0, 6)
                    String@ btnsStr = str("文件,项目,视图,调试,窗口,帮助")
                    List@ btns = btnsStr.splitByRe(",")
                    MenuBarCtrl@ group = new MenuBarCtrl()
                    group.window = win;
                    for (int i = 0; i < btns.size(); i++){
                        String@ btn = (String@)btns.get(i)
                        mkMenuButton(o, i).{
                            MenuButton@ mbutton = o

                            o.text = btn
                            o.onMouseMove = ^void(MouseEvent *me){
                                // printf("onmove:%p\n", mbutton)
                                group.onmove(mbutton, me)
                            }
                            o.onClick =^void(MouseEvent *me){
                                group.onclick(mbutton, me)
                            }
                        }
                    }
                }
                
                // loadImage("asset/icon/arrow-down.png")
                //工具栏
                if 1 {

                layoutLinear(o, 0).{
                    // o.height = 30
                    // o.backgroundColor = 0x114493f3
                    o.backgroundColor = t.toolbar_bg
                    o.padding.setAll(6)
                    // String@ btnsStr = str("more,更多,购物车,profile_light,search,play,print,login,share,back,close,add,loading,refresh1,loading2,sub,upload,content_doc,arrow-right,arrow-down")
                    String@ btnsStr = str("more,更多,购物车,profile_light,search,play,print,login,share,back,close,add,loading,refresh1,loading2,sub,upload,content_doc")
                    List@ btns = btnsStr.splitByRe(",")

                    for (int i = 0; i < btns.size(); i++){
                        String@ btn = (String@)btns.get(i)
                        mkDrawButton(o, i).{
                            String@ path = str("asset/icon/")
                            path.addString(btn).add(".png")


                            o.normalBg = t.toolbar_menubutton_bg
                            o.hoverBg = t.toolbar_menubutton_bg_hover

                            o.src = path
                            o.onClick =^void(MouseEvent *me){
                                me.stopPropagation()
                            }
                        }
                    }
                }
                }

                // mkView(o, 0)~{
                //     o.backgroundColor = 0x99ff0000
                //     o.width = 100
                //     o.height = 20
                //     layoutLinearCell(o, 0)~{
                //         o.grow = 2
                //     }
                // }
                // mkView(o, 0)~{
                //     o.backgroundColor = 0x9900ff00
                //     o.width = 100
                //     o.height = 20
                //     layoutLinearCell(o, 0)~{
                //         o.grow = 3
                //     }
                // }
                if 1 {

                dockLayout(o, 0)~{
                    dockLayoutIns = o

                    o.tabHeadBg = t.dock_headbar_bg

                    // o.border.setAll(3, 0xff000000)
                    // o.padding.setAll(16)
                    // o.margin.setAll(16)
                    o.radius.setAll(6)
                    // o.backgroundColor = 0x990000ff
                    o.backgroundColor = 0x00000000
                    o.width = 100
                    o.height = 20
                    o.needClip = true

                    if(o.isNewForReact){
                        o.cbRenderItemHeadView = ^void (
                            DockItem *item, ViewBase *o, int kidIndex
                        ){
                            DockItem@ tmpItem = item
                            DockLayout@ tmpDock = dockLayoutIns
                            mkTextView(o, (long long)item)~{
                                o.cursor = str("pointer")
                                o.setText(item.id)
                                // o.color = 0xff00ff00
                                o.color = t.dock_head_c
                                o.padding.top = 4
                                o.padding.setHor(8)
                                // o.margin.right = 4
                                // o.margin.top = 8
                                o.border.setAll(0.0f, 0xffaeaeb2)

                                bool active =  item.parent.tabActiveIndex == kidIndex 
                                if active {
                                    o.border.t.w = 2.f;
                                    o.border.t.color = t.c_main
                                }

                                if kidIndex < item.parent.children.size() - 1{
                                    o.border.r.w = 1.f;
                                }
                                // o.backgroundColor = 
                                    // item.parent.tabActiveIndex == kidIndex ? 0x99000030l
                                    // : 0x66000030
                                o.backgroundColor = 
                                    active ? t.dock_head_bg_active
                                    : t.dock_head_bg
                            }
                        }
                        o.cbRenderItemContentView = ^ViewBase* (DockItem *item, ViewBase *o){
                            if (item.id.equals("project")){
                                mkAssetDirTreeView(o, (long long)item)~{
                                    o.backgroundColor = t.dock_content_bg
                                    return o
                                }
                            }
                            if (item.id.equals("hier")){
                                mkSceneHierView(o, (long long)item)~{
                                    o.backgroundColor = t.dock_content_bg
                                    return o
                                }
                            }
                            if (item.id.equals("inspector")){
                                mkInspectorView(o, (long long)item)~{
                                    o.backgroundColor = t.dock_content_bg
                                    return o
                                }
                            }
                            if (item.id.equals("dir")){
                                mkAssetDirView(o, (long long)item)~{
                                    o.backgroundColor = t.dock_content_bg
                                    return o
                                }
                            }
                            if (item.id.equals("scene")){
                                mkSceneView(o, (long long)item)~{
                                    o.backgroundColor = t.dock_content_bg
                                    layoutLinearCell(o, 0)~{
                                        o.grow = 1
                                    }
                                    return o
                                }
                            }


                            mkTextView(o, (long long)item)~{
                                o.needClip = true

                                printf("render dock content:%d, %s\n", item.intId, item.id.str);
                                o.setText(item.id)
                                o.font_size = 30
                                o.color = 0xff000000
                                o.radius.setAll(6)
                                o.padding.setAll(6)

                                o.backgroundColor = 
                                    item.intId == 0 ? 0x53ff0000
                                    : item.intId == 1 ? 0x53f0ff00
                                    : item.intId == 2 ? 0x5330ffff
                                    : 0x5300ffff

                                layoutLinearCell(o, 0)~{
                                    o.grow = 1
                                }

                                return o
                            }
                        }

                        DockItem *root = o.root
                        mkDockItemTab(root, str("tab-project")).{
                            o.width = 150
                            mkDockItem(o, str("hier")).{
                                o.intId = 0;
                            }
                        }
                        // mkDockItemSplitter(root, str("console"), false).{
                        //     o.intId = 11;
                        //     mkDockItem(o, str("lala")).{
                        //         o.intId = 1;
                        //         o.width = 100
                        //     }
                        //     mkDockItem(o, str("good")).{
                        //         o.intId = 3;
                        //         o.width = 100
                        //     }
                        //     mkDockItem(o, str("nice")).{o.intId = 3;}
                        // }

                        mkDockItemSplitter(root, str("center"), false).{
                            mkDockItemTab(o, str("center")).{
                                o.intId = 10

                                mkDockItem(o, str("scene")).{o.intId = 3 }
                                mkDockItem(o, str("tab1")).{o.intId = 3 }
                            }
                            mkDockItemSplitter(o, str("center"), true).{
                                mkDockItemTab(o, str("tab-project")).{
                                    o.width = 150
                                    mkDockItem(o, str("project")).{
                                        o.intId = 30;
                                    }
                                }
                                mkDockItem(o, str("dir")).{o.intId = 3 }
                                
                            }
                        }
                        mkDockItemTab(root, str("tab-inspector")).{
                            o.width = 250
                            mkDockItem(o, str("inspector")).{
                                o.intId = 2 
                            }
                        }
                    }


                    layoutLinearCell(o, 0)~{
                        o.grow = 1
                    }
                }
                }
            }

            // mkView(o, 0)~{
            //     o.name = str("div")
            //     o.backgroundColor = 0xffff0000
            //     // o.margin.setAll(10);

            //     o.width = 16.f
            //     o.height = 16.f

            //     o.backgroundColor = 0xffffffff
            //     o.radius.setAll(11)
            //     o.border.setAll(4, 0xff1677ff)
            // }


            if (0){

            // layoutLinear(o, 0)~{
            //     o.direction = str("column")

            //     // o.width = 16
            //     o.height = 300
            //     o.backgroundColor = 0x3f0000f0
            //     o.alignItems = str("stretch")
            //     o.padding.setAll(6);



            //     if (1){

            //     layoutLinear(o, 0)~{
            //         o.backgroundColor = 0x33000000
            //         o.radius.setAll(6)
            //         //o.width = 100
            //         //o.height = 100
            //         o.margin.setAll(6);
            //         o.name = str("layoutLinear")
            //         o.needClip = true
            //         if (o.isNewForReact){ //刚建的结点
            //             o.listener = new TmpListener()
            //         }
            //         // o.direction = str("column")
            //         mkImageView(o, 0)~{
            //             o.setSrc(str("./print.png"));
            //         }

            //         mkSelect(o, 0)~{
            //             o.appendOptionCStr("cstr0")
            //             o.appendOptionCStr("cstr1")
            //             o.appendOptionCStr("cstr2")
            //             o.appendOptionCStr("cstr3")
            //         }

            //         mkView(o, 0)~{
            //             o.width = 50.f
            //             o.height = 50.f
            //             o.name = str("内部div")
            //             o.backgroundColor = 0xffff0000
            //             // o.desiredWidth = 100

            //             o.margin.setAll(10);
            //         }

            //         if (1){
            //             mkButton(o, 0)~{
            //                 //o.clickListener = new ClickListener()
            //                 o.onClick = ^void(MouseEvent *me){

            //                     // MessageDialog_alert("hi closure", "closure标题")
            //                     me.stopPropagation()

            //                     ^void onActive(MenuNativeItem*item){
            //                         printf("\n\n========================================onActive menu\n")
            //                     }

            //                     MenuNativeItem *root = mkMenuNativeItem(null, null, null)
            //                     root.{
            //                         mkMenuNativeItem(o, str("hi"), onActive)
            //                         mkMenuNativeItem(o, str("hi2"), onActive)
            //                     }

            //                     MenuNative@ n = new MenuNative()
            //                     n.create(root)
            //                     Vec2 p = Mouse_getPos()
            //                     n.showAt(0, 0)
            //                     // n.showAtScreenPosition(0, 0)
            //                     // n.showAtScreenPosition(p.x, p.y)
            //                 }
            //                 o.backgroundColor = 0xffff0000
            //                 // o.margin.setAll(10);
            //             }
            //         }
            //         mkDrawButton(o, 0)~{
            //             o.onClick =^void(MouseEvent *me){
            //                 // MessageDialog_alert("hi drawButton", "closure标题")
            //                 win.enable(false)
            //                 show_newWindow(win)
            //                 me.stopPropagation()
            //             }
            //         }
            //         mkProgressView(o, 0)~{
            //             o.width = 100
            //             o.margin.setHor(10)
            //         }
            //         checkbox(o, 0)~{
            //         }
            //         mkSwitch(o, 0)~{
            //         }
            //         mkSlider(o, 0)~{
            //             o.width = 100
            //         }


            //         // div(o, 0)~{
            //         //     o.width = 50
            //         //     o.height = 50
            //         //     o.name = str("内部div")
            //         //     o.backgroundColor = 0xffff0ff0
                        
            //         //     o.margin.setAll(10);
            //         // }                
            //         // div(o, 0)~{
            //         //     o.width = 50
            //         //     o.height = 50
            //         //     o.name = str("内部div")
            //         //     o.backgroundColor = 0xffff0ff0
                        
            //         //     o.margin.setAll(10);
            //         // }              
            //         // div(o, 0)~{
            //         //     o.width = 50
            //         //     o.height = 50
            //         //     o.name = str("内部div")
            //         //     o.backgroundColor = 0xffff0ff0
                        
            //         //     o.margin.setAll(10);
            //         // }   
            //         // div(o, 0)~{
            //         //     o.width = 50
            //         //     o.height = 50
            //         //     o.name = str("内部div")
            //         //     o.backgroundColor = 0xffff0ff0
                        
            //         //     o.margin.setAll(10);
            //         //     o.listener = new TmpListener2()
            //         // }           
            //         mkTextView(o, 0)~{
            //             o.margin.setAll(10)
            //             o.backgroundColor = 0xffeecccc;
            //             o.setText(str("hello world2"))
            //         } 
            //         mkTextView(o, 0)~{
            //             o.margin.setAll(10)
            //             o.backgroundColor = 0xffeecccc;
            //             o.color = 0xffffff00;
            //             o.setText(str("hello world3"))
            //         } 
            //         //mkTextView(o, 0)~{
            //             //o.margin.setAll(10)
            //             //o.backgroundColor = 0xffeecccc;
            //             //o.color = 0xff0000ff
            //             //o.font_size = 30
            //             //o.setText(str("hello world4"))
            //         //} 
            //         //mkTextView(o, 0)~{
            //             //o.margin.setAll(10)
            //             //o.backgroundColor = 0xffeecccc;
            //             //o.color = 0xff00ffff;
            //             //o.padding.setAll(5)
            //             //o.setText(str("hello world5"))
            //         //}
            //         // div(o, 0)~{
            //         //     o.width = 50
            //         //     o.height = 50
            //         //     o.name = str("内部div")
            //         //     o.backgroundColor = 0xffff0ff0
                        
            //         //     o.margin.setAll(10);
            //         //     o.listener = new TmpListener2()
            //         // }
            //     }
            //     }
            //     if (1){
            //     layoutLinear(o, 0)~{
            //         o.width = 800;
            //         o.height = 266
            //         o.alignItems = str("stretch")
            //         o.radius.setAll(6)
            //         // o.backgroundColor = 0x3ff000f0
            //         // layoutLinearCell(o, 0)~{
            //         //     o.grow = 1
            //         // }

            //         mkView(o, 0)~{
            //             // o.height = 300
            //             o.width = 100
            //             o.backgroundColor = 0x33000000
            //             o.margin.setAll(6);
            //             o.radius.setAll(6)
            //         }
            //         mkView(o, 0)~{
            //             // o.height = 300
            //             o.width = 400
            //             o.backgroundColor = 0x330ff000
            //             o.margin.setAll(6);
            //             o.radius.setAll(6)

            //             layoutAlign(o, 0)~{
            //                 o.width = 200
            //                 o.height = 200
            //                 o.backgroundColor = 0x330ff0f0
            //                 o.setCenter()

            //                 mkView(o, 0)~{
            //                     o.height = 50
            //                     o.width = 50
            //                     o.backgroundColor = 0x53ff0000
            //                     o.margin.setAll(6);
            //                     o.radius.setAll(6)
            //                 }
            //                 mkView(o, 0)~{
            //                     o.height = 30
            //                     o.width = 30
            //                     o.backgroundColor = 0x53ffff00
            //                     o.margin.setAll(6);
            //                     o.radius.setAll(6)
            //                 }
            //                 mkView(o, 0)~{
            //                     o.height = 30
            //                     o.width = 30
            //                     o.backgroundColor = 0x53ffff00
            //                     o.margin.setAll(6);
            //                     o.radius.setAll(6)

            //                     layoutAlignCell(o, 0)~{
            //                         o.setTopRight()
            //                     }
            //                 }
            //                 mkView(o, 0)~{
            //                     o.height = 70
            //                     o.width = 30
            //                     o.backgroundColor = 0x5300ffff
            //                     o.margin.setAll(6);
            //                     o.radius.setAll(6)

            //                     layoutAlignCell(o, 0)~{
            //                         o.setMiddleLeft()
            //                     }
            //                 }
            //                 mkView(o, 0)~{
            //                     o.height = 30
            //                     o.width = 80
            //                     o.backgroundColor = 0x53ff00ff
            //                     o.margin.setAll(6);
            //                     o.radius.setAll(6)

            //                     layoutAlignCell(o, 0)~{
            //                         o.setBottomRight()
            //                     }
            //                 }
            //                 mkView(o, 0)~{
            //                     o.height = 120
            //                     o.width = 80
            //                     o.backgroundColor = 0x53ff00ff
            //                     o.margin.setAll(6);
            //                     o.radius.setAll(6)

            //                     layoutAlignCell(o, 0)~{
            //                         o.setBottomCenter()
            //                     }
            //                 }

            //                 mkView(o, 0)~{
            //                     o.backgroundColor = 0xd36030ff
            //                     o.margin.setAll(6);
            //                     o.radius.setAll(6)

            //                     layoutAlignPositionCell(o, 0)~{
            //                         o.left = 10
            //                         o.top = 20
            //                         o.right = 30
            //                         o.bottom = 5
            //                     }
            //                 }
            //             }
            //         }
            //         mkView(o, 0)~{
            //             // o.height = 300
            //             // o.width = 500
            //             o.backgroundColor = 0x33000000
            //             o.margin.setAll(6);
            //             o.radius.setAll(6)

            //             layoutLinearCell(o, 0)~{
            //                 o.grow = 1
            //             }

            //             // mkEditText(o, 0)~{
            //             //     o.margin.setAll(6)
            //             // }
            //             if (0){
            //                 mkTableView(o, 0)~{
            //                     if (o.isNewForReact){
            //                         {
            //                             TableViewColumn@ col = mkTableViewColumn(50, str("Id"))
            //                             o.columns.add(col)
            //                         }
            //                         {
            //                             TableViewColumn@ col = mkTableViewColumn(50, str("name"))
            //                             o.columns.add(col)
            //                         }
            //                         {
            //                             TableViewColumn@ col = mkTableViewColumn(50, str("age"))
            //                             o.columns.add(col)
            //                         }
            //                         {
            //                             TableViewColumn@ col = mkTableViewColumn(50, str("level"))
            //                             o.columns.add(col)
            //                         }
            //                     }
            //                     o.row = 10
            //                     o.margin.setAll(6)
            //                     o.width = 300
            //                     // Node *tmp = o
            //                     o.renderTd = ^void (Node *o, int row, int col){
            //                         mkTextView(o, 0)~{
            //                             o.setColor(0xffffffff)
            //                             o.setText(str("go").addi(col))
            //                             //.addi(row))
            //                         }
            //                     }
            //                     // o.height = 300
            //                     o.backgroundColor = 0x330030ff
            //                 }
            //             }
            //             if (0){
            //                 ScrollArea *sa = null
            //                 mkScrollArea(o, 0)~{
            //                     sa = o
            //                     o.width = 300
            //                     o.height = 300
            //                     o.backgroundColor = 0x09ff0000
            //                     for (int i = 0; i < 10; i++){
            //                         mkView(o, i)~{
            //                             o.margin.setAll(6)
            //                             o.width = 100
            //                             o.height = 100
            //                             o.backgroundColor = 
            //                             i % 2 == 0 ? 0x550000ff :
            //                             0x5500ff00

            //                             mkTextView(o, 0)~{
            //                                 o.color = 0xffffffff
            //                                 o.setText(str("block").addi(i))
            //                             }
            //                         }
            //                     }
            //                 }
            //                 mkScrollBar(o, 0)~{
            //                     o.bindScrollArea(sa)

            //                 }
            //             }


            //             if (0){
            //                 mkColorPalete(o, 0)~{
            //                     o.margin.setAll(20)
            //                     o.xDraggale = false
            //                     o.width = 200
            //                     o.height = 200
            //                 }
            //             }
            //             if (1){
            //                 mkTreeView(o, 0)~{
            //                     o.margin.setAll(20)
            //                     o.width = 200
            //                     List@ data = new List()
            //                     data.add(str("parent"))
            //                     data.add(str("world"))
            //                     data.add(str("ni"))
            //                     data.add(str("hao"))

            //                     List@ data2 = new List()
            //                     data2.add(str("hello"))
            //                     data2.add(str("world"))
            //                     data2.add(str("ni"))
            //                     data2.add(str("hao"))
            //                     o.state.roots = data
            //                     o.state.getId = ^String@ (Object *item){
            //                         String@ s = (String@)item
            //                         return s
            //                     }
            //                     o.state.getItemChildren = ^List@ (Object *item){
            //                         // printf("o:%p\n", o)
            //                         String@ s = (String@)item
            //                         if (s.equals("parent")){
            //                             return data2
            //                         }
            //                         return null
            //                     }
            //                     o.reactItem = ^void (Node *o, Object *item, int deep){
            //                         mkTextView(o, 0)~{
            //                             o.backgroundColor = 0x120033ff
            //                             o.setText((String@)item)
            //                         }
            //                     }
            //                 }
            //             }
            //         }
            //     }

            //     }
            // }

            }
        }
        }

        // Time_sleepMs(3000)
        // printf("report 2 rootView:%p\n", 
        //    win.rootView);
        // urgc_report_sources_of(win.rootView);


        // o.initData()
        printf("initData\n");
        o.setTitle("SuiDesigner")
        printf("setTitle\n");
        o.setRect(100, 300, 800, 400)

        // printf("setPos\n");
        // o.setSize(200, 400)
        printf("setRect\n");
        o.show()
        printf("show\n");

    }


    // printNodeTree((Node*)win.rootView, 0);

    // SystemTrayIcon@ tray = new SystemTrayIcon()
    // tray.setIconPath("icon2.ico")
    // tray.init()


    
    // app.runEventLoop()
}

extern void windowInit()

class Tmp3{
    int tmp = 30
}
class Tmp2{
    int a = 10
    Tmp3@ tmp3
    void print(){
        printf("tmp.a = %d\n", self.a)
    }

    void ctor(){
        printf("Tmp()\n")
    }
    void dtor(){
        printf("~Tmp()\n")
    }
}
void test_tmp2(){
    Tmp2@ a = new Tmp2()
    ^ void say(){
        printf("say a.a:%d \n", a.a);
        a.a = -1
    } 
 
    a.a = 323
    a.print()
    say();
    a.print()
}

extern void test_tgfx()

int testAudio(){
    {//音频
        ma_result result;
        ma_engine engine;
        result = ma_engine_init(NULL, &engine);

        printf("hi. result:%d MA_SUCCESS:%d\n", result, MA_SUCCESS);
        if (result != MA_SUCCESS) {
            return result;  // Failed to initialize the engine.
        }
        // ma_engine_play_sound(&engine, "a.wav", NULL);

        const char *path = "../asset/a.mp3";
        // if (argc >= 2){
        //     path = argv[1];
        // }

        printf("play sound:%s\n", path);
        ma_engine_play_sound(&engine, path, NULL);
        getchar();
    }
    return 0;
}
int main(){
    urgc_start_process_thread();
    windowInit()

    // Window@ win = new Window()

    // testBiJson()
    // test_tmp2()

    // getchar();
    // test_tgfx();

    // MainProject_showWindow()

    // testMaterialMeta()

    // startSuiDesigner()
    // new SpriteSheetEditor().{
    //     o.showWindow()
    // }

    // testIntArray()

    // new TileEditor().{
    //     o.showWindow()
    // }

    // new SglEditor().{
    //     o.showWindow()
    // }
    // testAudio();
    // testMath();

    // printf("hi\n")

    // testPlaceKidsTo()

    testInsp()

    // testTransparency()

    // testMdxReader()
    // new Window().{
    //     o.rootView.{
    //         mkTextView(o, 0).{
    //             o.setText(str("sfh"))
    //         }

    //     }
    //     o.show()

    // }
    // testHeightMap()
    // testGeometry()
    App_use().runEventLoop()

    // testMessageDialog()
    // testJson();

    // if MessageDialog_confirm("OK?", "tip"){
    //     printf("ok\n")
    // }
    // else {
    //     printf("no\n")
    // }
    return 0
}

void testTransparency(){
    Window@ win = new Window()
    new LayoutAlign().{
        o.backgroundColor = 0x33afafff
        o.anchor.set(0.5, 0.5)
        o.align.set(0.5, 0.5)


        win.rootView = o
        mkView(o, 0).{
            o.backgroundColor = 0xffefefff
            o.width = 100
            o.height = 100
        }
        mkTextView(o, 0).{
            o.setText(str("你好呀， Sui"))
        }
    }
    win.setTitle("hi transparency")
    win.setSize(800, 600)
    win.show()

}