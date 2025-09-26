
#include <stdio.h>
#include "./Orc/Orc.h"

#include "../UrgcDll/urgc_api.h"

import * from "./Sui/View/Button.orc"
import * from "./Sui/Core/Image.orc"
import * from "./Sui/View/ImageView.orc"
import * from "./Sui/View/TextView.orc"
import * from "./Sui/View/ScrollArea.orc"
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
import * from "./Sui/Dialog/FileDialog.orc"
import * from "./Sui/Layout/LayoutLinear.orc"
import * from "./Sui/Layout/LayoutAlign.orc"
import * from "./Sui/View/Checkbox.orc"
import * from "./Sui/View/Switch.orc"
import * from "./Sui/View/Slider.orc"
import * from "./Sui/View/ProgressView.orc"
import * from "./Sui/View/EditText.orc"
import * from "./Sui/View/TableView.orc"
import * from "./Sui/View/HoverViewEffect.orc"
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
import * from "./SuiDesigner/BezierEditView.orc"
import * from "./Json/Json.orc"
import * from "./SuiDesigner/ProjectMgr.orc"
import * from "./SuiDesignerMain.orc"

static ProjectMgr@ mgr
static Window@ win
static ProjectInfo@ curProject

static void openProject(ProjectInfo@ project){
    // MessageDialog_alert(
    //     str("打开：").addString(project.path).str,
    //     "tip")
    if !win {
        return;
    }
    Window@ tmp = win
    win = null

    startSuiDesigner()
    // mkTimerTimeout(^void(){
        tmp.close()
        tmp = null
    // }, 100)
}

static void showProjectMenu(ProjectInfo@ project){
    ^void cb(MenuNativeItem *item){
        if item.label.equals("Delete") {
            mgr.projects.remove(project)
            renderWindow()
        }
        if item.label.equals("打开") {
            openProject(project)
        }

    }
    mkMenuNativeItem(null, str(""), cb).{
        mkMenuNativeItem(o, str("Delete"), cb)
        mkMenuNativeItem(o, str("打开"), cb)

        MenuNative@ menu = new MenuNative()
        menu.create(o)
        menu.showAtMouse()
    }
}
static void renderProjectItemView(Node* o, ProjectInfo@ project, int i){
    if 0 {
        mkTextView(o, 0).{
            o.height = 100
            o.backgroundColor = i % 2 ? 0x110088ff : 0x11000000
            o.setText(project.path)
        }
        return
    }
    layoutLinear(o, i).{
        o.margin.top = 6
        o.margin.bottom = 6
        o.margin.left = 6
        o.margin.right = 6
        // o.border.b.set(1.0, 0xff000000)

        o.cursor.set("pointer")
        o.cbOnEvent = ^ void (Event *e){
            if e instanceof MouseEvent{
                MouseEvent* me = (MouseEvent*)e;
                if me.isClickInBubble(){
                    if me.button == 1 {
                        curProject = project
                        // MessageDialog_alert(
                            // str("点击").addString(project.path).str,
                            // "提示")
                        renderWindow()
                    }
                    else if me.button == 3{
                        // mgr.projects.remove(project)
                        // renderWindow()
                        showProjectMenu(project)
                    }
                }
                if me.isDblClickInBubble() && me.button == 1 {
                    openProject(project)
                }
            }

        }

        mkHoverViewEffect(o, 0).{
            o.border.setAll(0.0, 0x11000000)
            o.border.b.set(1.0, 0x11000000)

            o.hoverBorder.setAll(0.0, 0x11000000)
            o.hoverBorder.b.set(1.0, 0x11000000)

            o.activeBorder.setAll(0.0, 0x11000000)
            o.activeBorder.b.set(1.0, 0x11000000)

            o.backgroundColor = i % 2 == 0 
            ? 0x00000000 
            : 0x08000000

            o.activeBackgroundColor = 0x10000000

            o.isActive = project == curProject
        }


        mkImageView(o, 0).{
            o.setSrc(project.icon)
            o.width = 64
            o.height = 64
            // o.border.setAll(1, 0x35999999)
            o.margin.right = 12
        }
        layoutLinear(o, i).{
            o.direction.set("column")
            o.alignItems.set("start")

            mkTextView(o, 0).{
                String@ name = project.getName()
                o.setText(name)
                o.setFont_size(20)
            }
            mkTextView(o, 0).{
                o.setText(project.path)
                o.setFont_size(14)
                o.setColor(0xff666666)
            }
        }
    }
}

static const char *path = "./projects.json"
static void load(){
    if !Path_isFile(path){
        return
    }
    String@ text = Path_readText(path)
    // MessageDialog_alert("加载成功", "tip")
    Json@ jo = Json_parse(text.str)
    mgr.loadByJson(jo)
    // renderWindow()
}
static void save(){
    if !mgr {
        return
    }
    Json@ jo = mgr.toJson()
    printf("save:%s\n", jo.dump().str)
    Path_writeText(path, jo.dump().str)
    MessageDialog_alert("保存成功", "tip")
}

static void renderWindow(){
    if !win{
        return
    }
    Theme* t = themeIns()
    win.rootView.{

        o.name = str("rootDiv")


        //菜单
        if 1 {
        layoutLinear(o, 0).{
            // o.height = 30
            o.backgroundColor = t.menubar_bg
            // o.backgroundColor = 0xcc000000
            o.padding.setAxis(0, 6)
            String@ btnsStr = str("+ Add,- Delete,Import,Clear,Save,Load")
            List@ btns = btnsStr.splitByRe(",")
            // MenuBarCtrl@ group = new MenuBarCtrl()
            // group.window = win;
            for (int i = 0; i < btns.size(); i++){
                String@ btn = (String@)btns.get(i)
                mkMenuButton(o, i)~{
                    MenuButton@ mbutton = o

                    o.text = btn
                    o.onMouseMove = ^void(MouseEvent *me){
                        // printf("onmove:%p\n", mbutton)
                        // group.onmove(mbutton, me)
                    }
                    o.onClick =^void(MouseEvent *me){
                        // group.onclick(mbutton, me)
                        if btn.endsWith("+ Add"){
                            mgr.addTestProject("./")
                            // MessageDialog_alert(btn.str, "提示")
                            renderWindow()
                        }
                        else if btn.endsWith("Clear"){
                            mgr.projects.clear()
                            renderWindow()
                        }
                        else if btn.endsWith("Save"){
                            save()
                        }
                        else if btn.endsWith("Load"){
                            load()
                            renderWindow()
                            MessageDialog_alert("加载成功", "tip")
                        }
                        else if btn.endsWith("Delete"){
                            mgr.projects.remove(curProject)
                            renderWindow()
                        }
                        else if btn.endsWith("Import"){
                            String@ dirpath = fileDialog_getExistingDirectory("./", "选择项目目录")
                            if !dirpath {
                                MessageDialog_alert("未选择", "提示")
                            } else {
                                ProjectInfo@ p = new ProjectInfo()
                                p.path = dirpath
                                p.version = str("2.303.0")
                                mgr.projects.add(p)
                                MessageDialog_alert(str("选择").addString(dirpath).str, "提示")
                            }
                            renderWindow()
                        }
                        else {
                            MessageDialog_alert(btn.str, "提示")
                        }
                    }
                }
            }
        }
        }

        mkScrollArea(o, 0).{
            // o.height = 200
            o.alignItems.set("stretch")
            // o.backgroundColor = 0xffff0000
            // o.useMaxWidthConstraint = true
            o.useMinWidthConstraint = true

            layoutLinearCell(o, 0).{
                o.grow = 1.0
                o.alignSelf.set("stretch")
            }


            layoutLinear(o, 0).{
                o.direction.set("column")
                o.alignItems.set("stretch")
                o.padding.setAll(6)

                for int i = 0 ; i < mgr.projects.size(); i++{
                    ProjectInfo@ project = (ProjectInfo@)mgr.projects.get(i)
                    renderProjectItemView(o, project, i)
                }
            }

            // mkScrollBar(o, 0).{
            //     o.width = 30
            //     o.height = 100
            // }
        }

        if 0 {
        layoutLinear(o, 0).{
            o.justifyContent.set("center")
            // mkTextView(o, 0)~{
            //     o.margin.setAll(10)
            //     o.backgroundColor = 0xffeecccc;
            //     o.setText(str("hello world2"))
            // } 
            mkDrawButton(o, 0).{
                // o.setLabel(str("保存"))
                o.text = str("保存")
                o.onClick = ^void(MouseEvent*me){
                    MessageDialog_alert("保存", "提示")
                }
            }
            // mkColorView(o, 0).{
            // }
            // mkBezierEditView(o, 0).{
            //     o.margin.left = 10
            //     o.backgroundColor = 0xff333333
            //     o.width = 300
            //     o.height = 200
            // }
            // mkTextView(o, 0)~{
            //     o.margin.setAll(10)
            //     o.backgroundColor = 0xffeecccc;
            //     o.setText(str("hello world2"))
            // } 
            // mkColorPalete(o, 0).{
            //     o.mainColor = 0xff00ffff
            //     o.kind = str("sv")
            //     o.indicatorKind = str("circle")
            //     o.width = 200
            //     o.height = 200
            //     o.margin.right = 6  
            //     o.onChanged = ^void (Vec2 ratio){
            //         printf("ratio:%f,%f\n", ratio.x, ratio.y)
            //     }
            // }
            // mkColorPalete(o, 0).{
            //     o.kind = str("hue")
            //     o.width = 20
            //     o.height = 200
            //     o.margin.right = 6  
            //     o.onChanged = ^void (Vec2 ratio){
            //         printf("hue ratio:%f,%f\n", ratio.x, ratio.y)
            //     }
            // }
            // mkColorPalete(o, 0).{
            //     o.kind = str("alpha")
            //     o.width = 20
            //     o.height = 200
            //     o.onChanged = ^void (Vec2 ratio){
            //         printf("alpha ratio:%f,%f\n", ratio.x, ratio.y)
            //     }
            // }
        }
        }
    }

}
Window@ MainProject_showWindow(){
    mgr = new ProjectMgr()

    load()

    win = new Window()
    win.setSize(300, 300)
    win.{
        new LayoutLinear().{
            o.direction.set("column")
            o.alignItems.set("maxOrStretch")
            win.setRootView(o)
        }
        renderWindow()

        o.setTitle("项目")
        printf("setTitle\n");
        o.setRect(100, 100, 800, 400)
        o.moveToCenter()

        o.show()
    }
    return win;
}