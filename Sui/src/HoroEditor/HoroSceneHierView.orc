package HoroEditor

#include <stdio.h>
#include <string.h>


#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Number.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/NodeLib.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/Canvas.orc"

import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Dialog/Toast.orc"

import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/View/MenuNative.orc"

import * from "../Sui/Layout/LayoutLinear.orc"

import * from "../Sui/View/ViewBuilder.orc"
import * from "../SuiDesigner/Serial/BiJson.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/View/Drag.orc"
import * from "../SuiDesigner/Asset/AssetDirView.orc"
import * from "../SuiDesigner/Asset/AssetDirTreeView.orc"
import * from "../SuiDesigner/RegisterNodes.orc"
import * from "../SuiDesigner/DrawDegree.orc"
import * from "../SuiDesigner/UiAction.orc"
import * from "../SuiDesigner/EditCtx.orc"
import * from "../SuiDesigner/ANode.orc"
import * from "../SuiDesigner/EventANodeChanged.orc"
import * from "../SuiDesigner/EventFileItemChanged.orc"
import * from "./HoroEditCtx.orc"
import * from "./HoroEditor.orc"
import * from "./UiAct.orc"
import * from "../Sgl/Obj3d.orc"
import * from "../Sgl/Camera.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/Core/Vec2.orc"


class HoroSceneHierView extends LayoutLinear {

    HoroEditCtx@ editCtx
    HoroEditor@ editor

    Drag@ drag = new Drag()
    DragCrossWindowIndicator@ indi = new DragCrossWindowIndicator()


    void ctor(){
        super.ctor()
        self.drag.onDrag = ^void(Drag*d){
            printf("onDrag HoroSceneHierView\n")
            if d.isDragStart{
                self.indi.start()
            }
            else if d.isDragging {
                self.indi.onDragMove(mkVec2(0, 0))
            }
            else if d.isDragEnd {
                self.indi.end()
            }
        }
    }
    void onEvent(Event *event){
        super.onEvent(event)
        if event instanceof MouseEvent {
            MouseEvent *me = (MouseEvent*)event
            if me.button == 1 && me.isMouseDown {
                printf("感知到按下\n")
                self.drag.onMouseDown(me)

            }
        }
    }
    void onListenerEvent(Event *event){
        if event instanceof EventHoroSceneChanged{
            self.trigger_react()
        }
        else if event instanceof EventANodeAttrChanged {
            self.trigger_react()
        }
        else if event instanceof EventANodeChanged {
            self.trigger_react()
        }
    }
    void onMounted(){
        super.onMounted()
        useEbus().addListener(self)
    }
    void onUnmouting(){
        super.onUnmounting()
        useEbus().removeListener(self)
    }
    void _routeRightMenu(MenuNativeItem* item, ANode@ anode){
        if !item.cmd {
            return 
        }

        if item.cmd.startsWith("PreviewCamera"){
            // UiAction_previewCamera(self.editCtx.sceneView.drawCtx,  (Camera*)node)
        }
        if item.cmd.startsWith("RefreshHier"){
            self.trigger_react()
        }
        if item.cmd.startsWith("AddView/"){
            String@ viewName = Path_basename(item.cmd.str)
            // MessageDialog_alert(item.cmd.str, "tip")
            Toast_make(viewName.str)
            // UiAction_addView(anode, viewName)
            UiAct_addView(self.editor, anode, viewName)
            return
        }
        if item.cmd.equals("RenameView"){
            UiAction_renameANode(anode)
            // MessageDialog_alert("重命名", "tip")
            return
        }
        if item.cmd.equals("DeleteView"){
            // MessageDialog_alert("删除", "tip")
            // UiAction_deleteANode(anode)
            anode.removeSelf()
            useEbus().emit(new EventHoroSceneChanged())
            return
        }
        else if item.cmd.equals("LocateView"){
            // UiAction_locateView(anode)
            // MessageDialog_alert(item.cmd.str, "tip")
        }
        else if item.cmd.equals("CopyView"){
            // MessageDialog_alert(item.cmd.str, "tip")
            List@ list = new List()
            list.add(anode)
            UiAction_copyANodes(list)
        }
        else if item.cmd.equals("PasteView"){
            // MessageDialog_alert(item.cmd.str, "tip")
            UiAction_pasteANodes(anode)
        }
        else if item.cmd.equals("CutView"){
            // MessageDialog_alert(item.cmd.str, "tip")
            List@ list = new List()
            list.add(anode)
            UiAction_cutANodes(list)
        }
        
    }
    void _onItemRightClick(MouseEvent *me, Node *view, Object *item){
        me.stopPropagation()
        if item instanceof ANode {
            ANode@ node = (ANode@)item

            mkMenuNativeItem(null, null, null).{
                ^void onActive(MenuNativeItem*item){
                    printf("\n\n========================================onActive menu on AssetDirView cmd:%s item:%s\n",
                        item.cmd.str,
                        item.label.str, 
                    )
                    self._routeRightMenu(item, node)
                    // self._routeRightMenu(item)
                    // MessageDialog_alert("hi", "tip")
                }

                mkMenuNativeItem(o, str("刷新层级"), onActive). {o.cmd = str("RefreshHier")}
                mkMenuNativeItem(o, str("重命名"), onActive). {o.cmd = str("RenameView")}
                mkMenuNativeItem(o, str("添加"), onActive). {
                    o.cmd = str("RenameView")

                    NodeLib@ lib = NodeLib_use()
                    for int i = 0; i < lib.list.size(); i++{
                        NodeRegisterInfo* info = (NodeRegisterInfo*)lib.list.get(i)
                        mkMenuNativeItem(o, str(info.className), onActive). {
                            o.cmd = str("AddView/").add(info.className)
                        }
                    }
                    // mkMenuNativeItem(o, str("Node"), onActive). {o.cmd = str("AddView/Node")}
                    // mkMenuNativeItem(o, str("ViewBase"), onActive). {o.cmd = str("AddView/ViewBase")}
                    // mkMenuNativeItem(o, str("View"), onActive). {o.cmd = str("AddView/View")}
                    // mkMenuNativeItem(o, str("Button"), onActive). {o.cmd = str("AddView/Button")}
                    // mkMenuNativeItem(o, str("MenuButton"), onActive). {o.cmd = str("AddView/MenuButton")}
                    // mkMenuNativeItem(o, str("DrawButton"), onActive). {o.cmd = str("AddView/DrawButton")}
                    // mkMenuNativeItem(o, str("Slider"), onActive). {o.cmd = str("AddView/Slider")}
                    // mkMenuNativeItem(o, str("Switch"), onActive). {o.cmd = str("AddView/Switch")}
                    // mkMenuNativeItem(o, str("ImageView"), onActive). {o.cmd = str("AddView/ImageView")}
                    // mkMenuNativeItem(o, str("TextView"), onActive). {o.cmd = str("AddView/TextView")}
                    // mkMenuNativeItem(o, str("EditText"), onActive). {o.cmd = str("AddView/EditText")}
                    // mkMenuNativeItem(o, str("数据容器"), onActive).{
                    //     mkMenuNativeItem(o, str("TreeView"), onActive). {o.cmd = str("AddView/TreeView")}
                    //     mkMenuNativeItem(o, str("TableView"), onActive). {o.cmd = str("AddView/TableView")}
                    // }
                    // mkMenuNativeItem(o, str("ProgressView"), onActive). {o.cmd = str("AddView/ProgressView")}
                }
                mkMenuNativeItem(o, str("删除"), onActive). {o.cmd = str("DeleteView")}

                if node instanceof Camera {
                    mkMenuNativeItem(o, str("预览相机"), onActive). {o.cmd = str("PreviewCamera")}
                }


                mkMenuNativeItem(o, str("定位"), onActive). {o.cmd = str("LocateView")}
                mkMenuNativeItem(o, str("复制"), onActive). {o.cmd = str("CopyView")}
                mkMenuNativeItem(o, str("粘贴"), onActive). {o.cmd = str("PasteView")}
                mkMenuNativeItem(o, str("剪切"), onActive). {o.cmd = str("CutView")}
                // mkMenuNativeItem(o, str("返回上级目录"), null). {o.cmd = str("GotoParentDirectory")}

                MenuNative@ n = new MenuNative()
                n.create(o)
                n.showAtMouse()
            }
        }
    }

    void _onEvent_forItemView(Event *e, Node *view, Object *item){
        if e instanceof MouseEvent{
            MouseEvent* me =(MouseEvent*)e;
            if me.button == 3 && me.isClickInBubble(){
                self._onItemRightClick(me, view, item)
                return
            }
        }
    }
    void react(int xxx){
        self.direction = str("column")
        self.alignItems = str("stretch")

        self.startInnerReact()

        // mkTextView(self, 0)~{
        //     o.setText(str("good"))
        // }

        // Project@ project = Project_ins()
        // EditCtx@ ctx = EditCtx_ins();
        
        HoroSceneHierView* o = (HoroSceneHierView*)self

        // o.backgroundColor = 0x33ffffff
        // o.backgroundColor = 0x33ffffff
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

            // mkTextView(o, 0)~{
            //     // o.backgroundColor = 0x120033ff
            //     o.setText(str("你好啊 HoroSceneHierView"))
            //     o.color = 0xffffffff
            // }


            mkTreeView(o, 0).{
                if o.isNewForReact {
                    printf("new scene hier tree view\n")
                }
                TreeView@ treeView = o
                // o.border.setAll(2, 0xff000000)
                // o.margin.setAll(20)
                // o.backgroundColor = 0xffff3300

                self.editCtx.setState(o.state)
                o.state.roots = self.editCtx.roots
                o.state.getId = ^String@ (Object *item){
                    ANode@ s = (ANode@)item
                    String@ id = s.getId();
                    // printf("tag:%s, id:%s\n", s.tag.str, id.str)
                    return id;
                }
                o.state.getItemChildren = ^List@ (Object *item){
                    ANode@ s = (ANode@)item
                    return s.children
                }
                o.alignItems.set("maxOrStretch")

                o.cbOnEvent_forItemView = ^void(Event *e, Node* n, Object *item){
                    self._onEvent_forItemView(e, n, item)
                }
                o.reactItem = ^void (Node *parentNode, Object *item, int deep){
                    Node* o = parentNode
                    ANode@ s = (ANode@)item

                    int idx = -1
                    if (parentNode instanceof ViewBase){
                        ViewBase *vb = (ViewBase*)parentNode
                        idx = vb.viewIndexInParent()
                    }

                    bool isSelected = treeView.state.isSelected(item)
                    
                    mkHoverViewEffect(o, 0).{
                        // o.backgroundColor = idx % 2 == 1 ? 0xffffffff: 0
                        // o.backgroundColor =  0xffff0000
                        o.isActive = isSelected
                        o.cbOnHoverChanged = ^void(ViewBase*v){
                            ^void hi(){
                                printf("xxx:%d\n", xxx)
                                // self.ctor()
                            }
                            if (v.hover){
                                self.editCtx.hoverNode = s
                            } else {
                                self.editCtx.hoverNode = null
                            }
                            // self.invalidDraw()
                            printf("Scene.cbOnHoverChanged:%d\n", v.hover);
                        }
                    }

                    //箭头

                    bool hasKids = s.children.size() > 0
                    bool isOpend = treeView.state.isOpend(item)
                    mkImageView(o, 0).{
                        o.width = 12
                        o.height = 12
                        o.setSrc(
                            hasKids 
                            ?
                                isOpend 
                                ? Path_resolveFromExecutionDir("asset/icon/arrow-down.png")
                                : Path_resolveFromExecutionDir("asset/icon/arrow-right.png")
                            : null
                        )
                    }

                        // mkTextView(o, 0)~{
                        //     o.setText_align(str("center"))
                        //     o.width = 20
                        //     // o.backgroundColor = 0x120033ff
                        //     if (s.children.size() > 0){
                        //         o.setText(str(isOpend ? "v " :"> "))
                        //     } else {
                        //         o.setText(str(" "))
                        //     }
                        // }

                    mkTextView(o, 0).{
                        Vtable_Object *vt = orc_getVtableByObject(s);
                        String@ name = s.getName()
                        if name && name.notEmpty() {
                            // String@ basename = Path_basename(name.str)
                            // o.setText(basename)
                            o.setText(name)
                        }
                        else {
                            // o.setText(str(vt.className))
                            o.setText(s.tag)
                        }
                        // o.backgroundColor = 0x120033ff
                        // if s.node && s.node.name && s.node.name.notEmpty() {
                        //     o.setText(s.node.name)
                        // }
                        // else {
                        //     o.setText(s.tag)
                        // }
                    }
                }
            }
        }

        self.endInnerReact()
    }
}

HoroSceneHierView@ mkHoroSceneHierView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (HoroSceneHierView@)gocNode(sp, (Node*)parent, HoroSceneHierView)
}


void testHoroSceneHier(){
    // registerNodes()

    printf("testScene\n");
    // VNode@ vn = loadPrefab("asset/button.json")
    // vn.printTree(0)
    // vn.updateSubTreeNodes()
}