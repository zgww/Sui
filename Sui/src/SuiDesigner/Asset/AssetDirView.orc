package SuiDesigner

#include <stdio.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Path.orc"
import * from "../../Sui/Core/View.orc"
import * from "../../Sui/Core/ViewBase.orc"
import * from "../../Sui/Core/Node.orc"
import * from "../../Sui/Core/Event.orc"
import * from "../../Sui/Core/Emitter.orc"
import * from "../../Sui/Dialog/MessageDialog.orc"
import * from "../../Sui/Dialog/Toast.orc"
import * from "../../Sui/Core/MouseEvent.orc"
import * from "../../Sui/View/TextView.orc"
import * from "../../Sui/View/TreeView.orc"
import * from "../../Sui/View/ImageView.orc"
import * from "../../Sui/View/ViewBuilder.orc"
import * from "../../Sui/View/ScrollArea.orc"
import * from "../../Sui/View/MenuNative.orc"
import * from "../../Sui/View/HoverViewEffect.orc"
import * from "../../Sui/Layout/LayoutLinear.orc"
import * from "../../Sui/Layout/RowWrap.orc"
import * from "../../Sui/Layout/LayoutAlign.orc"

import * from "../FileItem.orc"
import * from "../UiAction.orc"
import * from "../../HoroEditor/UiAct.orc"
import * from "../Theme.orc"
import * from "../Project.orc"
import * from "../EventANodeChanged.orc"
import * from "../EventFileItemChanged.orc"



class SelectFileItems {
    List@ list = new List()
    ^List@ () getAll = null
    ^void () onChanged


    void select(FileItem@ fi){
        self.list.clear()
        self.list.add(fi)
        self.fire_onChanged()
    }

    void fire_onChanged(){
        if self.onChanged {
            self.onChanged()
        }
    }

    void selectMulti(FileItem@ fi, bool ctrl, bool shift){
        if !ctrl && !shift {
            self.select(fi)
            return
        }
        if ctrl {
            self.list.addOnce(fi)
            self.fire_onChanged()
            return
        }
        if shift {
            //空的情况
            if !self.list.first() {
                self.select(fi)
                return
            }
            if self.getAll {
                List@ all = self.getAll()
                if all {
                    FileItem* last = self.list.last()
                    if last {
                        int idx = all.indexOf(last)
                        int idx2 = all.indexOf(fi)
                        self.list = all.span(idx, idx2)
                        self.list.add(last) //确保锚点还是在最后一个
                        self.fire_onChanged()
                    }
                }
            }
        }
    }
}

AssetDirView@ curAssetDirView = null
class AssetDirView extends LayoutLinear {
    //选中的FileITem
    // FileItem@ activeFileItem = null
    List@ activeFileItems = new List()
    //所在的目录
    FileItem@ parentFileItem = null
    SelectFileItems@ selectFileItems = new SelectFileItems()

    void ctor(){
        super.ctor()
        self.selectFileItems.getAll = ^List@ (){
            return self.getCurrentDirFileItem().children
        }
    }


    //取得当前所在的目录FileItem. 不是parentFileItem.因为有可能是根
    FileItem* getCurrentDirFileItem(){
        Project* project = Project_ins()
        FileItem *curDirFileItem = self.parentFileItem  ? self.parentFileItem : project.dirFileItem
        return curDirFileItem
    }


    void onListenerEvent(Event *event){
        if event instanceof EventANodeChanged{
            EventANodeChanged* e = (EventANodeChanged*)e;
        }
        else if event instanceof EventFileItemChanged{
            EventFileItemChanged* e = (EventFileItemChanged*)e;
            self.trigger_react()
        }
        
    }
    void onMounted(){
        super.onMounted()
        curAssetDirView = self
        useEbus().addListener(self)
    }
    void onUnmounting(){
        super.onUnmounting()
        if curAssetDirView == self{
            curAssetDirView = null
        }
        useEbus().removeListener(self)
    }
    void react(){
        Theme* t = themeIns()

        self.direction = str("column")
        self.alignItems = str("stretch")

        self.startInnerReact()

        // mkTextView(self, 0).{
        //     o.setText(str("good"))
        // }

        Project@ project = Project_ins()
        FileItem *curDirFileItem = self.parentFileItem  ? self.parentFileItem : project.dirFileItem
        
        AssetDirView* o = (AssetDirView*)self

        o.backgroundColor = t.dir_bg //0x33ffffff
        layoutLinearCell(o, 0).{
            o.grow = 1
        }

        // layoutAlign(o, 0).{
        //     layoutLinearCell(o, 0).{
        //         o.grow = 1
        //     }
        // }

        mkScrollArea(o, 0).{
            // o.backgroundColor = 0xff00ffff
            // o.width = 300
            // o.height = 200
            o.alignItems = str("stretch")
            o.useMaxWidthConstraint = true
            // o.useMinWidthConstraint = true

            o.margin.setAll(6)

            layoutLinearCell(o, 0).{
                o.grow = 1
            }

            mkRowWrap(o, 0).{
                // o.alignItems = str("stretch")
                o.alignItems.set("start")

                int l = curDirFileItem.children.size()
                for (int i = 0; i<l;i++){
                    FileItem@ fi = (FileItem@)curDirFileItem.children.get(i)
                    self.reactFileItem(o, fi)
                }

            }

        }

        self.endInnerReact()
    }
    void _openDirectory(FileItem @fi){
        if (fi.isDirectory){
            self.parentFileItem = fi
            self.invalidReact()
        }
    }
    void _routeMenuNativeItem(MenuNativeItem *item, FileItem @fi){
        if (item.cmd){
            if item.cmd.equals("OpenFile"){
                UiAction_openFile(fi)
                return;
            }
            if item.cmd.equals("CreatePrefab2d"){
                UiAction_createPrefab(fi)
                return;
            }
            if item.cmd.equals("CreatePrefab3d"){
                UiAct_createPrefab3d(fi)
                return;
            }
            if item.cmd.equals("DeleteFileItem"){//打开
                UiAction_delete(fi)
                return;
            }
            if item.cmd.equals("RenameFileItem"){//重命名
                UiAction_renameFileItem(fi)
                return;
            }
            if (item.cmd.equals("CreateDirectory")){//创建目录
                UiAction_createDirectory(fi)
                return;
            }
            if (item.cmd.equals("OpenDirectory")){//打开目录
                self._openDirectory(fi)
                return;
            }
            if (item.cmd.equals("ShowImageInNewWindow")){//打开目录
                // Toast_make("hi new image")
                UiAction_showImageInNewWindow(fi)
                return;
            }
            if (item.cmd.equals("ShowFileInfoInNewWindow")){//显示文件属性
                // Toast_make("hi new image")
                UiAction_showFileInfoInNewWindow(fi)
                return;
            }
            if (item.cmd.equals("ShowFileTextInNewWindow")){//显示文件属性
                // Toast_make("hi new image")
                UiAction_showFileTextInNewWindow(fi)
                return;
            }
            if (item.cmd.equals("CreateMaterial")){//创建材质
                // Toast_make("hi new image")
                UiAction_createMaterial(fi)
                return;
            }

            if (item.cmd.equals("ShowMaterialInspectorWindow")){//检视材质
                UiAction_showMaterialInspectorWindow(fi)
                return
            }
            if (item.cmd.equals("GotoParentDirectory")){//
                if (self.parentFileItem && self.parentFileItem.parent){
                    self.parentFileItem = self.parentFileItem.parent
                    self.invalidReact()
                }
                return;
            }
            if (item.cmd.startsWith("CreateGeometry/")){//检视材质
                UiAct_createGeometry(fi, item.cmd)
                return
            }
        }
        MessageDialog_alert(item.label.str, "tip")
    }
    void _self_onRightClick(MouseEvent *me){
        if (me.isClickInBubble() && me.button == 3){
            mkMenuNativeItem(null, null, null).{
                ^void onActive(MenuNativeItem*item){
                    printf("\n\n========================================onActive menu on AssetDirView cmd:%s item:%s\n",
                        item.cmd.str,
                        item.label.str, 
                    )
                    self._routeMenuNativeItem(item, self.getCurrentDirFileItem())
                }

                mkMenuNativeItem(o, str("返回上级目录"), onActive). {o.cmd = str("GotoParentDirectory")}
                mkMenuNativeItem(o, str("创建Prefab2d"), onActive). {o.cmd = str("CreatePrefab2d")}
                mkMenuNativeItem(o, str("创建Prefab3d"), onActive). {o.cmd = str("CreatePrefab3d")}
                mkMenuNativeItem(o, str("创建目录"), onActive). {o.cmd = str("CreateDirectory")}
                mkMenuNativeItem(o, str("创建几何体"), null). {
                    mkMenuNativeItem(o, str("Box"), onActive). {o.cmd = str("CreateGeometry/Box")}
                    mkMenuNativeItem(o, str("Sphere"), onActive). {o.cmd = str("CreateGeometry/Sphere")}
                    mkMenuNativeItem(o, str("Plane"), onActive). {o.cmd = str("CreateGeometry/Plane")}
                    mkMenuNativeItem(o, str("Capsule"), onActive). {o.cmd = str("CreateGeometry/Capsule")}
                }
                // mkMenuNativeItem(o, str("返回上级目录"), null). {o.cmd = str("GotoParentDirectory")}

                MenuNative@ n = new MenuNative()
                n.create(o)
                n.showAtMouse()
            }
        }
    }

    void onEvent(Event *e){
        if (e instanceof MouseEvent){
            self._self_onRightClick((MouseEvent*)e)
        }
    }
    void _fileItem_onEvent(Event *e, FileItem@ fi){
        FileItem@ tmpFi = fi
        if (e instanceof MouseEvent){
            MouseEvent *me = (MouseEvent*)e
            if (me.isClickInBubble()){
                // MessageDialog_alert(str("mouse button").addi(me.button).str, "title")
                if (me.isDblClick){//双击打开目录
                    self._openDirectory(fi);
                } else if (me.button == 1){
                    self.selectFileItems.selectMulti(fi, me.ctrl, me.shift)
                    // self.activeFileItem = fi
                    self.invalidReact()
                }
                else if (me.button == 3){
                    e.stopPropagation()

                    mkMenuNativeItem(null, null, null).{
                        ^void onActive(MenuNativeItem*item){
                            printf("\n\n========================================onActive menu cmd:%s item:%s, fi:%s\n",
                                item.cmd.str,
                                item.label.str, 
                                tmpFi.path.str,
                            )
                            self._routeMenuNativeItem(item, tmpFi)
                        }

                        mkMenuNativeItem(o, str("创建目录"), onActive). {o.cmd = str("CreateDirectory")}
                        if (fi.isDirectory){
                            mkMenuNativeItem(o, str("打开目录"), onActive). {o.cmd = str("OpenDirectory")}
                        }
                        else {
                            mkMenuNativeItem(o, str("打开"), onActive). {o.cmd = str("OpenFile")}
                        }

                        //常见的图片
                        if Path_isUsualImage(fi.path.str){
                            mkMenuNativeItem(o, str("新窗口显示图片"), onActive). {o.cmd = str("ShowImageInNewWindow")}
                        }
                        if !fi.isDirectory {
                            mkMenuNativeItem(o, str("属性"), onActive). {o.cmd = str("ShowFileInfoInNewWindow")}
                        }
                        if fi.filename.endsWith(".txt")
                        || fi.filename.endsWith(".json") 
                        || fi.filename.endsWith(".yml") 
                        || fi.filename.endsWith(".ini") 
                        || fi.filename.endsWith(".js") 
                        || fi.filename.endsWith(".lua") 
                        {
                            mkMenuNativeItem(o, str("新窗口显示文本内容"), onActive). {o.cmd = str("ShowFileTextInNewWindow")}
                        }
                        if fi.filename.endsWith(".vs")
                        || fi.filename.endsWith(".fs")
                        {
                            mkMenuNativeItem(o, str("创建材质"), onActive). {o.cmd = str("CreateMaterial")}
                        }
                        if fi.filename.endsWith(".matl.json")
                        {
                            mkMenuNativeItem(o, str("检视材质"), onActive). {o.cmd = str("ShowMaterialInspectorWindow")}
                        }

                        mkMenuNativeItem(o, str("创建Prefab"), onActive). {o.cmd = str("CreatePrefab")}
                        mkMenuNativeItem(o, str("重命名"), onActive). {o.cmd = str("RenameFileItem")}

                        mkMenuNativeItem(o, str("删除"), onActive). {o.cmd = str("DeleteFileItem")}

                        mkMenuNativeItem(o, str("返回上级目录"), onActive). {o.cmd = str("GotoParentDirectory")}

                        MenuNative@ n = new MenuNative()
                        n.create(o)
                        n.showAtMouse()
                    }
                }
            }
        }
    }
    void reactFileItem(Node*o, FileItem@ fi){
        Theme* t = themeIns()

        FileItem@ tmpFi = fi
        layoutLinear(o, (long long)fi).{
            o.width = 80
            o.direction = str("column")
            o.margin.setHor(6)
            o.cursor = str("pointer")

            o.cbOnEvent = ^void (Event *e){
                self._fileItem_onEvent(e, tmpFi)
            }

            mkHoverViewEffect(o, 0).{
                // o.isActive = self.activeFileItem == fi
                o.isActive = self.selectFileItems.list.has(fi)
                // o.hoverBackgroundColor = 0xff
            }

            mkImageView(o, 0).{
                if fi.path.endsWith(".png"){
                    o.setSrc(fi.path)
                }
                else if fi.path.endsWith(".prefab.json"){
                    o.setSrc(Path_resolveFromExecutionDir("../asset/icon/prefab.png"))
                }
                else {
                    o.setSrc(
                        fi.isDirectory
                        ? Path_resolveFromExecutionDir("../asset/icon/dir.png")
                        : Path_resolveFromExecutionDir("../asset/icon/file.png")
                    )
                }
                o.width = 60
                o.height = 60
            }
            mkTextView(o, 0).{
                o.margin.setVer(6)
                o.setText(fi.filename)
                o.setFont_size(t.dir_fontSize)
                o.color = t.dir_color
            }
        }
    }
}



AssetDirView@ mkAssetDirView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (AssetDirView@)gocNode(sp, (Node*)parent, AssetDirView)
}
