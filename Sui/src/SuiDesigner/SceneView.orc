package SuiDesigner

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
import * from "../Sui/Core/Color.orc"
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
import * from "./Serial/BiJson.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Json/Json.orc"
import * from "./Asset/AssetDirView.orc"
import * from "./Asset/AssetDirTreeView.orc"
import * from "./RegisterNodes.orc"
import * from "./DrawDegree.orc"
import * from "./UiAction.orc"
import * from "./ANode.orc"
import * from "./Gizmo.orc"
import * from "./EditCtx.orc"
import * from "./EventANodeChanged.orc"
import * from "./EventFileItemChanged.orc"

// static int x = 80
// static int y = 80
class ImageChessBg {
    // int chessBgImageId = 0
    int width = 32
    int height = 32
    int color0 = 0xff333333
    int color1 = 0xff000000
    Image@ img = null

    char *new_createChessBg_inMemory(int w, int h){
        char *data = malloc(w * h * 4)
        int hw = w / 2
        int hh = h / 2


        int a0 = colorGetA(self.color0)
        int r0 = colorGetR(self.color0)
        int g0 = colorGetG(self.color0)
        int b0 = colorGetB(self.color0)

        int a1 = colorGetA(self.color1)
        int r1 = colorGetR(self.color1)
        int g1 = colorGetG(self.color1)
        int b1 = colorGetB(self.color1)


        for (int y = 0; y < h; y++){
            for (int x = 0; x < w; x++){
                int i = (y * w + x) * 4
                bool mode = (x < hw && y < hh) || (x >= hw && y >= hh)
                if (mode){
                    data[i] = r0
                    data[i + 1] = g0
                    data[i + 2] = b0
                    data[i + 3] = a0
                } else {
                    data[i] = r1
                    data[i + 1] = g1
                    data[i + 2] = b1
                    data[i + 3] = a1
                }
            }
        }

        return data
    }
    Image* gocChessBgImage(Canvas *canvas){
        if (self.img == null){
            int w = self.width
            int h = self.height

            char *imgData = self.new_createChessBg_inMemory(w, h) 
            self.img = canvas.createImageRGBA(w, h, (const unsigned char *)imgData)
            free(imgData)
        }
        return self.img
    }
}
class SceneTransform {
    Vec3 _translate;
    float _scale = 1;
    Mat2d mat = mkMat2d()//最终生成的矩阵
    void setScale(float s){
        self._scale = s
        self.updateMat()
    }
    void updateMat(){
        self.mat.identity()
        self.mat.translate(
            self._translate.x,
            self._translate.y,
            self._translate.z,
        )
        self.mat.scale(
            self._scale,
            self._scale,
            self._scale,
        )
    }
    void translate(float x, float y, float z){
        self._translate = self._translate.add3f(x, y, z)
        self.updateMat()
    }
    void setTranslate(float x, float y, float z){
        self._translate.set(x, y, z)
        self.updateMat()
    }
    void identity(){
        self._translate.set(0, 0, 0)
        self._scale = 1
        self.updateMat()
    }
    void performScaleByWheelEventAndSceneView(
        WheelEvent* we,
        SceneView* v
    ){
        Vec2 viewPos = v.worldToLocal(we.clientX, we.clientY)
        Mat2d invMat = self.mat.inverseNew()
        Vec3 scenePos = invMat.transformPoint(viewPos.x, viewPos.y, 0)

        // float s = self._scale
        // float nextScale = maxFloat(0.01, self._scale + (we.deltaY > 0 ? 1 : -1) * 0.1)
        // int idx = v.degree.levelOptions.indexOf(v.degree.curOption)
        // int nextIdx = minInt(maxInt(0, idx + (we.deltaY > 0 ? 1 : -1)), v.degree.levelOpotions.size() - 1)
        // // DrawDegreeItem@ opt = v.degree.findAndUpdateCurOption(nextScale)
        // self.setScale(opt.value)
        DrawDegreeItem@ opt = v.degree.findAndReturnOffset(self._scale, we.deltaY > 0 ? 1 : -1)
        v.degree.curOption = opt
        v.degree.curScale = opt.value
        self.setScale(opt.value)


        Vec3 newViewPos = self.mat.transformPoint(scenePos.x, scenePos.y, 0)
        printf("scale. client:%d,%d, viewPos:%f,%f, scenePos:%f,%f,newViewPos:%f,%f, delta:%f,%f\n",
            we.clientX, 
            we.clientY, 
            viewPos.x,
            viewPos.y,
            scenePos.x,
            scenePos.y,
            newViewPos.x,
            newViewPos.y,
            viewPos.x - 
            newViewPos.x,
            viewPos.y - 
            newViewPos.y,
        )
        self.translate(
            viewPos.x - 
            newViewPos.x,
            viewPos.y - 
            newViewPos.y,
            0,
        )


        printf("wheel. result:%f opt:%f,degree:%f\n", 
            self._scale, opt.value, opt.degree);
    }
}

class SceneView extends View {
    ImageChessBg@ chessBg = new ImageChessBg();

    Drag@ drag = new Drag()

    SceneTransform@ sceneTransform = new SceneTransform()

    DrawDegree@ degree = new DrawDegree()


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

        EditCtx_ins().sceneView = self

        useEbus().addListener(self)
    }
    void onUnmouting(){
        super.onUnmounting()
        EditCtx_ins().sceneView = null
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

            if me.isBubble() && me.button == 3 {
                if me.isMouseDown{
                    printf("mouse down scene\n");
                    // self.drag.onMouseDown(me);
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
        if self.rootNode && self.rootNode instanceof ViewBase {
            ViewBase* rootView = (ViewBase*)self.rootNode
            ViewBase* found = rootView.hitTestChildren(me.clientX, me.clientY);
            if found {
                ANode@ vnode = EditCtx_ins().findANodeByNode(found)
                printf("findANode:%p, %p\n", vnode, found)
                if vnode {
                    me.stopPropagation()
                    EditCtx_ins().state.setSelected(vnode)
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

        ANode@ root = EditCtx_ins().root
        if !root {
            self.removeRootNode()
        }
        else {
            if (root.node && (root.node.parent != self || root.node != self.rootNode)){
                self.removeRootNode()
                self.insertChild(root.node, 0)
                self.rootNode = root.node
            }
            root.updateSubTreeNodes()
        }

        // gizmo root
        if !self.gizmoRoot {
            View@ o = new View()
            self.gizmoRoot = o
            self.appendChild(o)

            o.hitTestType.set("onlychildren")
            // o.width = 100
            // o.height = 200
            // o.width = infinity
            // o.height = infinity
            o.backgroundColor = 0x0000ff00
            o.cbOnEvent = ^void(Event *e){
                if e instanceof MouseEvent {
                    MouseEvent* me = (MouseEvent*)e
                    if me.isClickInBubble(){
                        // Toast_make("hi click gizmo root")
                    }
                }
            }
        }
        self.reactGizmos()

        // self.startInnerReact()

        self.backgroundColor = 0xcc000000

        // self.endInnerReact()
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
        self.gizmoDrag.onDrag = ^void (Drag *d){
            // printf("========================================move:%f,%f\n", d.deltaPos.x, d.deltaPos.y)
            // x += d.deltaPos.x
            // y += d.deltaPos.y
            // self.triggerReactGizmos()
        }
        self.gizmoRoot.{

            EditCtx@ ctx = EditCtx_ins()
            if (ctx.state){
                ANode* sel = (ANode*)ctx.state.getFirstSelected()
                if sel && sel.node && sel.node instanceof View{
                    View* selView = (View*) sel.node
                    Frame* f = &selView.frame

                    //将视图的坐标转到scene下
                    Mat2d invMat = self._sceneWorldMat.inverseNew()
                    
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


                    // {
                    //     Vec3 scenePos = selView._world_transform.localToLocal(&invMat, 0, 0, 0)
                    //     Gizmo_reactRect(o, scenePos)
                    // }
                    // {
                    //     Vec3 scenePos = selView._world_transform.localToLocal(&invMat, f.width, 0, 0)
                    //     Gizmo_reactRect(o, scenePos)
                    // }
                    // {
                    //     Vec3 scenePos = selView._world_transform.localToLocal(&invMat, f.width, f.height, 0)
                    //     Gizmo_reactRect(o, scenePos)
                    // }
                    // {
                    //     Vec3 scenePos = selView._world_transform.localToLocal(&invMat, 0, f.height, 0)
                    //     Gizmo_reactRect(o, scenePos)
                    // }

                }
            }
        }
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
        self.triggerReactGizmos()


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
		// nvgFillPaint(vg, bp)	
		canvas.fill()

        //绘制刻度尺
        self.degree.draw(canvas, self.sceneTransform.mat, r.w, r.h, 0, 0)

        // canvas.save()
        // canvas.transform(self.sceneTransform.mat)
        // canvas.restore()
    }
    void drawSelfBorder(Canvas *canvas){
        super.drawSelfBorder(canvas)
        //绘制gizmo

        EditCtx@ ctx = EditCtx_ins()

        //绘制hover
        self.drawRect_forANode(canvas, ctx.hoverNode)

        if (ctx.state){
            ANode* sel = (ANode*)ctx.state.getFirstSelected()
            // self.drawRect_forANode(vg, sel)
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

            canvas.fillColorByInt32(mkIntByRgba (0, 255, 0, 64))
            canvas.fill()
            canvas.strokeWidth( 1)
            canvas.strokeColorByInt32( mkIntByRgba(0, 255, 0, 192))
            canvas.stroke()
        }
    }
}

SceneView@ mkSceneView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (SceneView@)gocNode(sp, (Node*)parent, SceneView)
}