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
import * from "../Project.orc"
import * from "../EventANodeChanged.orc"
import * from "../EventFileItemChanged.orc"
import * from "../Theme.orc"
import * from "./AssetDirView.orc"


class AssetDirTreeView extends LayoutLinear {
    void ctor(){
        super.ctor()
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
        useEbus().addListener(self)
    }
    void onUnmounting(){
        super.onUnmounting()
        useEbus().removeListener(self)
    }
    void _routeMenuNativeItem(MenuNativeItem *item, FileItem @fi){
        if !item.cmd{
            return
        }
        {

            if item.cmd.equals("DeleteDirectory"){//
                UiAction_deleteDirectory(fi)
                return;
            }
            if item.cmd.equals("CreateDirectory"){//
                UiAction_createDirectory(fi)
                return;
            }
            if item.cmd.equals("RenameDirectory"){//
                UiAction_renameFileItem(fi)
                return;
            }
            if item.cmd.equals("CreatePrefab2d"){//
                UiAction_createPrefab(fi)
                return;
            }
            if item.cmd.equals("CreatePrefab3d"){//
                UiAct_createPrefab3d(fi)
                return;
            }
        }

        MessageDialog_alert(item.label.clone().addString(fi.path).str, "tip")
    }
    void _self_onRightClick(MouseEvent* me){
        me.stopPropagation()

        mkMenuNativeItem(null, null, null).{
            ^void onActive(MenuNativeItem*item){
                printf("\n\n========================================onActive menu cmd:%s item:%s\n",
                    item.cmd.str,
                    item.label.str, 
                )
                Project@ project = Project_ins()
                self._routeMenuNativeItem(item, project.dirFileItem)
                // MessageDialog_alert(item.label.str, "tip")
            }

            // mkMenuNativeItem(o, str("删除目录"), onActive). {o.cmd = str("DeleteDirectory")}
            mkMenuNativeItem(o, str("创建目录"), onActive). {o.cmd = str("CreateDirectory")}
            // mkMenuNativeItem(o, str("重命名目录"), onActive). {o.cmd = str("RenameDirectory")}

            MenuNative@ n = new MenuNative()
            n.create(o)
            n.showAtMouse()
        }
    }
    void onEvent(Event *e){
        super.onEvent(e)
        if e instanceof MouseEvent{
            MouseEvent* me = (MouseEvent*)e;
            if me.button == 3 && me.isClickInBubble() {
                self._self_onRightClick(me)
            }
        }
    }
    void _dirItem_onEvent(Event *e, FileItem@ fi){
        if e instanceof MouseEvent{
            MouseEvent* me = (MouseEvent*)e;
            if me.button == 3 && me.isClickInBubble() {
                e.stopPropagation()
                // MessageDialog_alert("lala", "tip")
                mkMenuNativeItem(null, null, null).{
                    ^void onActive(MenuNativeItem*item){
                        printf("\n\n========================================onActive menu cmd:%s item:%s, fi:%s\n",
                            item.cmd.str,
                            item.label.str, 
                            fi.path.str,
                        )
                        // self._routeMenuNativeItem(item, tmpFi)
                        self._routeMenuNativeItem(item, fi)
                        // MessageDialog_alert(item.label.str, "tip")
                    }

                    mkMenuNativeItem(o, str("删除目录"), onActive). {o.cmd = str("DeleteDirectory")}
                    mkMenuNativeItem(o, str("创建目录"), onActive). {o.cmd = str("CreateDirectory")}
                    mkMenuNativeItem(o, str("重命名目录"), onActive). {o.cmd = str("RenameDirectory")}
                    mkMenuNativeItem(o, str("创建Prefab2d"), onActive). {o.cmd = str("CreatePrefab2d")}
                    mkMenuNativeItem(o, str("创建Prefab3d"), onActive). {o.cmd = str("CreatePrefab3d")}

                    MenuNative@ n = new MenuNative()
                    n.create(o)
                    n.showAtMouse()
                }
            }
        }
    }
    void react(){
        Theme* t = themeIns()
        self.direction = str("column")
        self.alignItems = str("stretch")

        self.startInnerReact()

        // mkTextView(self, 0)~{
        //     o.setText(str("good"))
        // }

        Project@ project = Project_ins()
        
        AssetDirTreeView* o = (AssetDirTreeView*)self

        o.backgroundColor = t.dirTree_bg //0x33ffffff
        layoutLinearCell(o, 0)~{
            o.grow = 1
        }

        // layoutAlign(o, 0)~{
        //     layoutLinearCell(o, 0)~{
        //         o.grow = 1
        //     }
        // }

        mkScrollArea(o, 0)~{
            // o.backgroundColor = 0xff00ffff
            // o.width = 300
            // o.height = 200
            o.alignItems = str("stretch")
            // o.useWidthContraint = true
            o.useMinWidthConstraint = true
            

            layoutLinearCell(o, 0)~{
                o.grow = 1
            }

            mkTreeView(o, 0)~{
                TreeView@ treeView = o
                // o.border.setAll(2, 0xff000000)
                // o.margin.setAll(20)
                // o.backgroundColor = 0xffff3300

                o.state.roots = project.dirFileItem.getSubDirectoryChildren()
                o.state.getId = ^String@ (Object *item){
                    FileItem@ s = (FileItem@)item
                    return s.path
                }
                o.state.getItemChildren = ^List@ (Object *item){
                    // printf("o:%p\n", o)
                    FileItem@ s = (FileItem@)item
                    // if (s.hasSubDirectory()){
                    //     return s.children
                    // }
                    // return null
                    return s.getSubDirectoryChildren()
                }
                o.state.cbSelectedIdChanged = ^void(TreeState *state){
                    Object *sel = state.getFirstSelected()
                    if (sel){ //通知变化
                        if (curAssetDirView){
                            FileItem@ fi = (FileItem*)sel;
                            curAssetDirView._openDirectory(fi)
                        }
                    }
                }
                o.alignItems.set("maxOrStretch")
                        // AssetDirTreeView@ tmpSelf = self;
                o.cbOnEvent_forItemView = ^void(Event *e, ViewBase* v, Object* item){
                    if item instanceof FileItem{
                        self._dirItem_onEvent(e, (FileItem*)item)
                    }
                }
                o.reactItem = ^void (Node *parentNode, Object *item, int deep){
                    Node* o = parentNode
                    int idx = -1
                    if (parentNode instanceof ViewBase){
                        ViewBase *vb = (ViewBase*)parentNode
                        idx = vb.viewIndexInParent()
                    }

                    FileItem@ s = (FileItem@)item

                    bool isSelected = treeView.state.isSelected(item)
                    mkHoverViewEffect(o, 0).{
                        o.border.l.w = 0.f
                        o.border.r.w = 0.f
                        o.hoverBorder.l.w = 0.f
                        o.hoverBorder.r.w = 0.f
                        o.activeBorder.l.w = 0.f
                        o.activeBorder.r.w = 0.f

                        o.backgroundColor = idx % 2 == 1 ? 0x09000000: 0
                        o.isActive = isSelected
                        o.cbOnHoverChanged = ^void(ViewBase*v){
                            printf("DirTree.cbOnHoverChanged:%d\n", v.hover);
                        }
                    }

                    bool hasKids = s.hasSubDirectory()
                    bool isOpend = treeView.state.isOpend(item)
                    mkImageView(o, 0).{
                        o.width = 12
                        o.height = 12
                        o.setSrc(
                            hasKids 
                            ?
                                isOpend 
                                ? str("../asset/icon/light-arrow-down.png")
                                : str("../asset/icon/light-arrow-right.png")
                            : null
                        )
                    }


                    // mkTextView(o, 0)~{
                    //     o.setText_align(str("center"))
                    //     o.width = 20
                    //     // o.backgroundColor = 0x120033ff
                    //     if (s.hasSubDirectory()){
                    //         o.setText(str(isOpend ? "v " :"> "))
                    //     } else {
                    //         o.setText(str(" "))
                    //     }
                    // }

                    mkTextView(o, 0)~{
                        // o.backgroundColor = 0x120033ff
                        o.color = t.dirTree_color
                        o.setFont_size(t.dirTree_fontSize)
                        o.setText(s.filename)
                    }
                }
            }
        }

        self.endInnerReact()
    }
}


void testAsset(){
    {
        FileItem@ root = FileItem_loadDirectoryTree("D:/ws/oms_ts/omsdeploy")
        root.printTree(0)
    }
}

AssetDirTreeView@ mkAssetDirTreeView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (AssetDirTreeView@)gocNode(sp, (Node*)parent, AssetDirTreeView)
}