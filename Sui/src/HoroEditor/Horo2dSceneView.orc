package HoroEditor

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"


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
import * from "../Sui/Core/Mat2d.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/Timer.orc"
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
import * from "../Json/Json.orc"
import * from "../SuiDesigner/Asset/AssetDirView.orc"
import * from "../SuiDesigner/Asset/AssetDirTreeView.orc"
import * from "../SuiDesigner/RegisterNodes.orc"
import * from "../SuiDesigner/DrawDegree.orc"
import * from "../SuiDesigner/UiAction.orc"
import * from "../SuiDesigner/ANode.orc"
import * from "../SuiDesigner/Gizmo.orc"
import * from "../SuiDesigner/EditCtx.orc"
import * from "../SuiDesigner/EventANodeChanged.orc"
import * from "../SuiDesigner/EventFileItemChanged.orc"
import * from "./ImageChessBg.orc"
import * from "./SceneTransform.orc"
import * from "./HoroEditor.orc"


class Horo2dSceneView extends View {
    ImageChessBg@ chessBg = new ImageChessBg();

    Drag@ drag = new Drag()

    SceneTransform@ sceneTransform = new SceneTransform()

    DrawDegree@ degree = new DrawDegree()
    HoroEditor@ editor


    ANode@ root
    //根结点 
    Node@ rootNode

    // gizmoNode
    Node@ gizmoRoot


    void ctor(){
        self.needClip = true
        self.sceneTransform.translate(0, 0, 0)
        self.drag.onDrag = ^void(Drag *d){
            printf("on drag. dx:%f,%f\n", d.deltaPos.x, d.deltaPos.y)
            self.sceneTransform.translate(d.deltaPos.x, d.deltaPos.y, 0)
        }
    }
    void onListenerEvent(Event *event){
        if event instanceof EventANodeAttrChanged{
            self.trigger_react()
        }
        else if event instanceof EventANodeChanged{
            EventANodeChanged* e = (EventANodeChanged*)e;
            self.trigger_react()
        }
        else if event instanceof EventFileItemChanged{
            EventFileItemChanged* e = (EventFileItemChanged*)e;
            self.trigger_react()
        }
    }
    void onMounted(){
        super.onMounted()

        // EditCtx_ins().sceneView = self

        useEbus().addListener(self)
    }
    void onUnmouting(){
        super.onUnmounting()
        // EditCtx_ins().sceneView = null

        useEbus().removeListener(self)
    }

    void onEvent(Event *e){
        if e instanceof WheelEvent {
            WheelEvent *we = (WheelEvent *)e;
            // printf("\nwheel delta:%d\n", we.deltaY)

            if we.isCapture {
                self.sceneTransform.performScaleByWheelEventAndSceneView(
                    we, self
                )
            }
            // float nextScale = maxFloat(0.01, self.sceneTransform._scale + (we.deltaY > 0 ? 1 : -1) * 0.1)
            // DrawDegreeItem@ opt = self.degree.findAndUpdateCurOption(nextScale)
            // self.sceneTransform.setScale(opt.value)
            // Toast_make("wheel ")
            return
        }
        if e instanceof MouseEvent {
            MouseEvent *me = (MouseEvent *)e;

            self.drag.onMouseDown_byPrefer(me, 3, false, true);

            if me.isBubble() && me.button == 3 {
                if me.isMouseDown{
                    printf("mouse down scene\n");
                }
                if me.isMouseUp {
                    printf("mouse up scene\n")
                }
            }
            if me.isClickInBubble() && me.button == 3 {
                self.onRightClick(me)
            }
            if me.button == 1 && me.isCapture && me.isClick() {
                self.onLeftClickInCapture(me)
            }
        }
    }
    void onLeftClickInCapture(MouseEvent *me){
        //点选元素
        // MessageDialog_alert("left click ", "tip")
        if self.root && self.root.node instanceof ViewBase {
            ViewBase* rootView = (ViewBase*)self.root.node
            ViewBase* found = rootView.hitTestChildren(me.clientX, me.clientY);
            if found {
                
                ANode@ vnode = self.editor.editCtx.findANodeByNode(found)
                // printf("findANode:%p, %p\n", vnode, found)
                if vnode {
                    me.stopPropagation()
                    self.editor.editCtx.state.setAncestorsOpen(vnode)
                    self.editor.editCtx.state.setSelected(vnode)
                }

                // MessageDialog_alert("hit", "tip")
            }
            else {
                Vec2 viewPos = self.worldToLocal(me.clientX, me.clientY)
                Mat2d invMat = self.sceneTransform.mat.inverseNew()
                Vec3 scenePos = invMat.transformPoint(viewPos.x, viewPos.y, 0)
                // MessageDialog_alert("left click ", "tip")
                printf("\n\n========================================left click. viewPos:%f,%f, scenePos:%f,%f\n\n",
                    viewPos.x,
                    viewPos.y, 
                    scenePos.x, 
                    scenePos.y, 
                );
            }
        }
    }
    void _routeRightMenu(MenuNativeItem *item){
        if item.cmd{
            if item.cmd.equals("ResetSceneTransform"){
                self.sceneTransform.identity()
                return;
            }

        }
        String@ s = str("选中菜单").addString(item.cmd) 
        MessageDialog_alert(s.str, "tip")
    }

    void onRightClick(MouseEvent *me){
        printf("on right click scene\n")
        mkMenuNativeItem(null, null, null).{
            ^void onActive(MenuNativeItem*item){
                printf("\n\n========================================onActive menu on AssetDirView cmd:%s item:%s\n",
                    item.cmd.str,
                    item.label.str, 
                )
                self._routeRightMenu(item)
                // MessageDialog_alert("hi", "tip")
            }

            mkMenuNativeItem(o, str("重置场景坐标"), onActive). {o.cmd = str("ResetSceneTransform")}
            mkMenuNativeItem(o, str("hi"), onActive). {o.cmd = str("Hi")}
            // mkMenuNativeItem(o, str("返回上级目录"), null). {o.cmd = str("GotoParentDirectory")}

            MenuNative@ n = new MenuNative()
            n.create(o)
            n.showAtMouse()
        }
    }

    void removeRootNode(){
        if self.rootNode {
            self.rootNode.removeSelf()
            self.rootNode = null
        }
    }


    void react(){
        // if (self.editCtx == null){
            // registerNodes()
            // VNode@ vn = loadPrefab("button.json")
            // vn.printTree(0)
            // vn.updateSubTreeNodes()
            // self.root = vn
            // self.appendChild(vn.node)
        // }

        Node* o = self
        self.startInnerReact()
        ANode@ root = self.root
        if root && root.node {
            self.placeKid(root.node)
        }
        // if !root {
        //     self.removeRootNode()
        // }
        // else {
        //     if (root.node && (root.node.parent != self || root.node != self.rootNode)){
        //         self.removeRootNode()
        //         self.insertChild(root.node, 0)
        //         self.rootNode = root.node
        //     }
        //     root.updateSubTreeNodes()
        // }

        // gizmo root
        {

        
            View@ v = mkView(o, 0)
            self.gizmoRoot = v
            v.hitTestType.set("onlychildren")

            get_unusedMapForReact(v)
            get_mapForReact(v)

            v.backgroundColor = 0x0000ff00
            v.endReact()
            // o.cbOnEvent = ^void(Event *e){
            //     if e instanceof MouseEvent {
            //         MouseEvent* me = (MouseEvent*)e
            //         if me.isClickInBubble(){
            //             // Toast_make("hi click gizmo root")
            //         }
            //     }
            // }
        }


        self.backgroundColor = 0xcc000000

        self.endInnerReact()

        self.reactGizmos()
    }


    Drag@ gizmoDrag = new Drag()

    bool _reactGizmosDirty = false
    void triggerReactGizmos(){
        if (self._reactGizmosDirty){
            return
        }
        self._reactGizmosDirty = true
        // printf("\n\n----------------------------------------trigger react\n\n")

        requestAnimationFrame(^bool(){
            // printf("\n\n----------------------------------------trigger react done\n\n");
            self._reactGizmosDirty = false
            self.reactGizmos()
            return true
        })
    }

    void reactGizmos(){
        // if 1 {return;}
        if !self.editor {
            return
        }
        // i, act, cur, prev
        // 0-0, , [], []
        // 0-1, , [], [b5c0]
        // 1-0, del b5c0 , [], []
        // 1-0, , [], [d5f0]
        ANode* sel = self.editor.editCtx.state.getFirstSelected()

        self.gizmoDrag.onDrag = ^void (Drag *d){
            // printf("========================================move:%f,%f\n", d.deltaPos.x, d.deltaPos.y)
            // x += d.deltaPos.x
            // y += d.deltaPos.y
            // self.triggerReactGizmos()
        }
        View* inner = null
        Object* prevfirst = null
        int prevSize = self.gizmoRoot._unusedMapForReact.size()
        if self.gizmoRoot._unusedMapForReact.size() > 0 {
            List@ keys = self.gizmoRoot._unusedMapForReact.keys()
            String@ key = keys.get(0)
            prevfirst = self.gizmoRoot._unusedMapForReact.get(key.str)
        } 
        self.gizmoRoot.{
            ANode* sel = self.editor.editCtx.state.getFirstSelected()

            // EditCtx@ ctx = EditCtx_ins()
            // if (ctx.state){
            //     ANode* sel = (ANode*)ctx.state.getFirstSelected()
            if sel && sel.node && sel.node instanceof ViewBase{
                ViewBase* selView = (ViewBase*) sel.node
                Frame* f = &selView.frame

                //将视图的坐标转到scene下
                Mat2d invMat = self._sceneWorldMat.inverseNew()

                // mkView(o, 0).{
                //     o.name.set("inner")
                //     inner = o
                //     o.width = 100
                //     o.height = 100
                //     o.backgroundColor = 0xffff0000
                // }
                
                mkGizmoRectView(o, 0).{
                    Vec3 lt = selView._world_transform.localToLocal(&invMat, 0, 0, 0)
                    Vec3 rb = selView._world_transform.localToLocal(&invMat, f.width, f.height, 0)
                    o.targetRect.set_ltrb(lt.x, lt.y, rb.x, rb.y)
                    o.onRectChanged = ^ void(Rect newr){
                        sel.setAttr("width", Json_mkNumber(newr.w))
                        sel.setAttr("height", Json_mkNumber(newr.h))
                        selView.width = newr.w
                        selView.height = newr.h

                        selView.frame.x = newr.x
                        selView.frame.y = newr.y
                        selView.invalidLayout()

                        new EventANodeAttrChanged().{
                            o.anode = sel
                            o.emitToEbus()
                        }
                    }
                }
            }
            // }
        }
        Object* first = null
        if self.gizmoRoot._unusedMapForReact.size() > 0 {
            List@ keys = self.gizmoRoot._unusedMapForReact.keys()
            String@ key = keys.get(0)
            first = self.gizmoRoot._unusedMapForReact.get(key.str)
        } 
        // urgc_report_sources_of(inner);

        // printf("react map size:%d/%d. first:%d, %p=>%p, map:%p, %p, view:%p. %p\n",
        //     self.gizmoRoot._mapForReact.size(),
        //     self.gizmoRoot._unusedMapForReact.size(),
        //     prevSize,
        //     prevfirst,
        //     first,

        //     self.gizmoRoot._mapForReact,
        //     self.gizmoRoot._unusedMapForReact,
        //     self.gizmoRoot, inner
        // );
    }


    void draw_children(Canvas *canvas){
        canvas.save()
        canvas.transform(self.sceneTransform.mat)

        canvas->currentTransform(&self._sceneWorldMat)

        super.draw_children(canvas);
        canvas.restore()
    }
    Mat2d _sceneWorldMat = mkMat2d()

    void draw_self(Canvas *canvas){
        // self.triggerReactGizmos()

        // super.draw_self(canvas)

		Image* bg = self.chessBg.gocChessBgImage(canvas)
		//绘制背景

        Rect r = self.getViewRect();

        canvas.beginPath();
		canvas.rect( 0, 0, r.w, r.h)

		canvas.imagePattern(
            true, 
            0, 0, self.chessBg.width, self.chessBg.height, 0, bg, 1
		)
		canvas.fill()

        //绘制刻度尺
        self.degree.draw(canvas, self.sceneTransform.mat, r.w, r.h, 0, 0)
    }
    void drawSelfBorder(Canvas *canvas){
        if !self.editor {
            return;
        }
        super.drawSelfBorder(canvas)
        //绘制gizmo

        //绘制hover
        self.drawRect_forANode(canvas, null)//ctx.hoverNode)
        ANode* sel = self.editor.editCtx.state.getFirstSelected()
        if sel{
            self.drawRect_forANode(canvas, sel)
        }
    }
    void drawRect_forANode(Canvas*canvas, ANode* sel){
        if (!sel){
            return;
        }
        Node* n = sel.node
        // Node* n = ctx.hoverNode.node
        if (n && n instanceof ViewBase){
            ViewBase *vb = (ViewBase*)n

            Rect myrect =self.get_abs_rect();
            Rect rect = vb.get_abs_rect();
            int x = rect.x - myrect.x
            int y = rect.y - myrect.y
            

            canvas.beginPath()
            canvas.rect( x, y, rect.w, rect.h)

            canvas.fillColorByInt32( mkIntByRgba(0, 128, 255, 64))
            canvas.fill()
            canvas.strokeWidth( 1)
            canvas.strokeColorByInt32(mkIntByRgba(0, 128, 255, 192))
            canvas.stroke()
        }
    }
}

Horo2dSceneView@ mkHoro2dSceneView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (Horo2dSceneView@)gocNode(sp, (Node*)parent, Horo2dSceneView)
}