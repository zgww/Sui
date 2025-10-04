package HoroEditor

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Time.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Json/Json.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Emitter.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/Mouse.orc"
import * from "../Sui/Core/KeyEvent.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Dialog/FileDialog.orc"
import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Sui/Layout/LayoutAlign.orc"
import * from "../Sui/View/DockLayout.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sui/View/MenuNative.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Canvas.orc"
import * from "../Sgl/Buffer.orc"
import * from "../SuiDesigner/DrawDegree.orc"
import * from "../SuiDesigner/ChessBgViewCallback.orc"
import * from "../SuiDesigner/Theme.orc"
import * from "../SuiDesigner/ANode.orc"
import * from "../SuiDesigner/EventANodeChanged.orc"
import * from "../SuiDesigner/InvalidReact.orc"
import * from "../SuiDesigner/MenuBarCtrl.orc"
import * from "../SuiDesigner/ToolBase.orc"
import * from "../SuiDesigner/SglGizmo.orc"
import type * from "../SuiDesigner/RegisterNodes.orc"
import * from "../Sgl/Material.orc"
import * from "../Sgl/Draw.orc"
import * from "../Sgl/Tex2d.orc"
import * from "../Sgl/Obj3d.orc"
import * from "../Sgl/Geometry.orc"
import * from "../Sgl/Mesh.orc"
import * from "../Sgl/SkinMesh.orc"
import * from "../Sgl/Particle.orc"
import * from "../Sgl/GeometryHeightMap.orc"
import * from "../Sgl/GeometryBox.orc"
import * from "../Sgl/GeometryPlane.orc"
import * from "../Sgl/GeometryRect.orc"
import * from "../Sgl/GeometrySphere.orc"
import * from "../Sgl/GeometryCircle.orc"
import * from "../Sgl/GeometryLine.orc"
import * from "../Sgl/GeometryRing.orc"
import * from "../Sgl/GeometryCylinder.orc"
import * from "../Sgl/GeometryCone.orc"
import * from "../Sgl/GeometryArrow.orc"
import * from "../Sgl/Billboard.orc"
import * from "../Sgl/Scene.orc"
import * from "../Sgl/PointLight.orc"
import * from "../Sgl/DrawCtx.orc"
import * from "../Sgl/Fbo.orc"
import * from "../Sgl/Tex2d.orc"
import * from "../Sgl/PerspectiveCamera.orc"
import * from "../Sgl/Skybox.orc"
import * from "../Sgl/OutlineFx.orc"
import * from "../SuiDesigner/MdxReader.orc"
import * from "../SuiDesigner/Asset/AssetDirView.orc"
import * from "../SuiDesigner/Asset/AssetDirTreeView.orc"
import * from "../SuiDesigner/Project.orc"
import * from "../SuiDesigner/SglInspectorView.orc"

import * from "../Sgl/SglSceneView.orc"

import * from "./HoroSceneHierView.orc"
import * from "./Horo3dSceneView.orc"
import * from "./HoroEditCtx.orc"
import * from "./HoroInspView.orc"
import * from "./UiAct.orc"

static DockLayout@ dockLayoutIns = null


class HoroEditorSceneViewCallback extends ViewCallback {
    HoroEditor@ horoEditor
    void afterDrawSelf(View *div, Canvas *canvas){
        // printf("haha\n")

        // canvas.beginPath()
        // canvas.rect(10, 10, 100, 100)
        // canvas.fillColorByInt32(0xffff0000)
        // canvas.fill()

        self.horoEditor.toolMgr.draw2d(canvas)
    }
}

// 赫萝 horoscope 星象.  horo 有时间的意思
class HoroEditor extends Listener{
    HoroEditCtx@ editCtx = new HoroEditCtx()
    Window@ win

    InvalidReact@ invalidReact  = mkInvalidReact(self)

    Drag@ drag = new Drag()
    HoroEditorSceneViewCallback@ viewCb = new HoroEditorSceneViewCallback()


    ToolMgr@ toolMgr = new ToolMgr()
    SglGizmo@ sglGizmo = new SglGizmo()

    Horo3dSceneView@ sceneView

    View@ gizmosView

    void onSceneEvent(Event* e){
        if e instanceof MouseEvent {
            MouseEvent *me = (MouseEvent*)e
            Rect absRect = self.sceneView.get_abs_rect()
            Vec2 fboSize = self.sceneView.fbo.getSize()
            //计算ndcPos
            me.ndcPos = mkVec2(
                (me.clientX - absRect.x) / fboSize.x * 2.0 - 1.0,
                -(me.clientY - absRect.bottom()) / fboSize.y * 2.0 - 1.0,
            )
            // printf("ndcPos:%f,%f\n", me.ndcPos.x, me.ndcPos.y);
        }


        if e.isStopPropagation { return }
        self.sglGizmo.onEvent(e)

        {
            if e.isStopPropagation { return }
            self.toolMgr.onEvent(e)
        }
    }
    void _afterDrawScene(){
        Node* sel = self.editCtx.state.getFirstSelected()
        if sel && sel instanceof Obj3d{
            //绘制outline
            // self.outlineFx.draw(self.sceneView.drawCtx, sel, self.sceneView.fbo)
        }

        self.toolMgr.scene  = self.sceneView.scene
        self.toolMgr.camera  = self.sceneView.camera

        self.toolMgr.selectNode = sel
        self.toolMgr.editCtx = self.editCtx
        // self.toolMgr.selectNodes.clear()
        // self.toolMgr.selectNodes.add()

        // printf("after scene draw2. select:%p\n", self.toolMgr.selectNode)


        // 更新gizmo
        self.toolMgr.reactGizmo(self.sglGizmo)
        // 绘制gizmo
        self.sglGizmo.draw(self.sceneView.drawCtx)

        self.reactGizmosView()
    }


    void ctor(){
        self.viewCb.horoEditor = self

        // self.curTilePosArr = mkVec2(-1, -1)
        self.drag.onDrag = ^ void (Drag *d){
            if d.isDragging {
                printf("isDragging tileset\n")
            }
        }

        String@ projectDirPath = Path_dirname(Path_getExecutionPath().str).add("/../asset/matl")
        printf("projectDirPath:%s\n", projectDirPath.str)
        Project_ins().init(projectDirPath.str)

        self.toolMgr.setTool(new ToolSelect())
        useEbus().addListener(self)
    }
    void dtor(){
        useEbus().removeListener(self)
    }
    void onListenerEvent(Event *e){
        if e instanceof EventHoroSelectedChanged{
            self.invalidReact.invalid()
        }
        else if e instanceof EventANodeChanged{
            EventANodeChanged* e = (EventANodeChanged*)e;
            self.invalidReact.invalid()
        }

    }
    
    void reactScene_forViewBase(Node* o, ANode* anode){
        ViewBase* root = (ViewBase*)anode.node
        // mkTextView(o, 0).{
        //     o.setText(str("这是ViewBase"))
        // }
        if root {
            o.placeKid(root)
        }
    }
    void reactScene_forObj3d(Node* o, ANode* anode){
        Obj3d* root = (Obj3d*)anode.node
        mkHoro3dSceneView(o, 0).{
            o.cb = self.viewCb
            o.cbOnEvent = ^void(Event *e){
                self.onSceneEvent(e)
            }
            self.sceneView = o

            o.drawCtx.cbAfterDraw = ^void(){
                self._afterDrawScene()
            }

            o.backgroundColor = 0x00ffffff
            o.setImageMode(Cover)
            if o.isNewForReact {
                o.mkBaseScene()
                self.editCtx.setSceneView( o)

                useEbus().emit(new EventHoroSceneChanged())
            }

            //将3d根结点加入到渲染场景中
            o.scene.{
                // root.position.set(100, 100, 0)
                o.placeKid(root)
            }

            o.width = 500
            o.height = 500

            layoutAlignPositionCell(o, 0).{
                o.left = 0
                o.top = 0
                o.right = 0
                o.bottom  = 0
            }
            mkView(o, 0).{ //用来承载gizmos2dview
                // o.backgroundColor = 0xff00ff00
                // o.width = 00
                // o.height = 100
                self.gizmosView = o
            }
        }
    }
    ViewBase* reactScene(Node* o, DockItem *item){
        layoutAlign(o, (long long)item).{
            o.backgroundColor = 0xffefefef
            o.useMaxConstraint = false
            // o.direction.set("column")
            // o.alignItems.set("start")
            o.needClip = true
            o.cbOnEvent = ^void(Event*e){
                if e instanceof MouseEvent {
                    MouseEvent *me = (MouseEvent*)e;
                }
            }

            layoutLinearCell(o, 0)

            {//根据目标的根结点不同，切换不同的sceneView
                ANode@ root = self.editCtx.getRoot()
                if root {
                    if root.node instanceof ViewBase {
                        self.reactScene_forViewBase(o, root)
                    }
                    else if root.node instanceof Obj3d {
                        self.reactScene_forObj3d(o, root)
                    }
                }
            }

            return o
        }
    }
    void reactGizmosView(){
        self.gizmosView.{
            self.toolMgr.reactGizmosView(self.gizmosView)
        }
    }

    void reactMenubar(Node* o){
        Theme* t = themeIns()
        //菜单
        layoutLinear(o, 0).{
            // o.height = 30
            o.backgroundColor = t.menubar_bg
            // o.backgroundColor = 0xcc000000
            o.padding.setAxis(0, 6)
            String@ btnsStr = str("文件,项目,视图,调试,窗口,帮助")
            List@ btns = btnsStr.splitByRe(",")
            MenuBarCtrl@ group = new MenuBarCtrl()
            group.cbCreateMenuNativeItem = ^MenuNativeItem@ (MenuButton* mbutton){
                ^void onActive(MenuNativeItem*item){
                    printf("\n\n========================================onActive menu:%s\n", item.label.str)
                    if item.label.equals("退出"){
                        exit(0);
                    }
                    if item.label.equals("保存场景"){
                        UiAct_savePrefab(self)
                        return
                    }
                    Toast_make(item.label.str)
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
                    else if mbutton.text.equals("调试"){
                        mkMenuNativeItem(o, str("Outline"), onActive)
                        // mkMenuNativeItem(o, str("绘制深度图"), onActive)
                    }
                    else {
                        mkMenuNativeItem(o, str("退出"), onActive)
                    }
                    return o;
                }
            }
            // group.window = win;
            for (int i = 0; i < btns.size(); i++){
                Object* obj = btns.get(i)
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
    }

    void reactDocklayout(Node* o){
        Theme* t = themeIns()
        dockLayout(o, 0).{
            dockLayoutIns = o
            o.width = 100
            o.height = 20

            // o.backgroundColor = 0x30000033
            if(o.isNewForReact){
                o.cbRenderItemHeadView = ^void (
                    DockItem *item, ViewBase *o, int kidIndex
                ){
                    DockItem@ tmpItem = item
                    DockLayout@ tmpDock = dockLayoutIns
                    layoutLinear(o, (long long)item).{
                        o.border.setAll(0.0f, 0xffaeaeb2)
                        bool active =  item.parent.tabActiveIndex == kidIndex 
                        if active {
                            o.border.t.w = 1.f;
                            o.border.t.color = t.c_main
                        }
                        // o.padding.top = 4
                        o.padding.setHor(6)
                        o.padding.setVer(2)

                        o.backgroundColor = 
                            active ? t.dock_head_bg_active
                            : t.dock_head_bg

                        mkImageView(o, ((long long)item)+1).{
                            o.width = 14
                            o.height = 14
                            o.setImageMode(Fill)
                            o.margin.right = 4
                            if (item.id.equals("hier")){
                                o.setSrc(Path_resolveFromExecutionDir("../asset/icon-light/hierarchy.png"))
                            }
                            else if (item.id.equals("scene")){
                                o.setSrc(Path_resolveFromExecutionDir("../asset/icon-light/scene.png"))
                            }
                            else if (item.id.equals("inspector")){
                                o.setSrc(Path_resolveFromExecutionDir("../asset/icon-light/inspector.png"))
                            }
                            else {
                                o.setSrc(Path_resolveFromExecutionDir("../asset/icon-light/directory.png"))
                            }
                        }
                        mkTextView(o, (long long)item).{
                            o.cursor = str("pointer")
                            o.setText(item.id)
                            // o.color = 0xff00ff00
                            o.color = t.dock_head_c
                            o.setFont_size(11)
                            // o.margin.right = 4
                            // o.margin.top = 8



                            if kidIndex < item.parent.children.size() - 1{
                                // o.border.r.w = 1.f;
                            }
                        }
                    }
                }
                o.cbRenderItemContentView = ^ViewBase* (DockItem *item, ViewBase *o){
                    if (item.id.equals("project")){
                        mkAssetDirTreeView(o, (long long)item).{
                            o.backgroundColor = t.dock_content_bg
                            return o
                        }
                    }
                    if (item.id.equals("dir")){
                        mkAssetDirView(o, (long long)item).{
                            o.backgroundColor = t.dock_content_bg
                            return o
                        }
                    }
                    if (item.id.equals("hier")){
                        mkHoroSceneHierView(o, (long long)item).{
                            o.editCtx = self.editCtx
                            o.editor = self
                            // o.backgroundColor = t.dock_content_bg
                            // o.backgroundColor = 0xffffffff
                            return o
                        }
                    }
                    if (item.id.equals("inspector")){
                        mkHoroInspView(o, (long long)item)~{
                            o.editCtx = self.editCtx
                            o.editor = self
                            o.backgroundColor = t.dock_content_bg
                            return o
                        }
                    }
                    if (item.id.equals("scene")){
                        return self.reactScene(o, item)
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

                o.root.{
                    o.isHorizontal = false

                    mkDockItemSplitter(o, null, true).{
                        mkDockItem(o, str("hier")).{
                            o.intId = 0;
                            o.width = 150
                        }
                        mkDockItem(o, str("scene")).{
                            o.intId = 0;
                        }
                        mkDockItem(o, str("inspector")).{
                            o.intId = 0;
                            o.width = 150
                        }
                    }
                    mkDockItemSplitter(o, null, true).{
                        o.width = 150
                        mkDockItem(o, str("project")).{
                            o.intId = 0;
                            o.width = 160
                        }
                        mkDockItem(o, str("dir")).{
                            o.intId = 0;
                        }
                    }
                }
            }
            layoutLinearCell(o, 0)
        }
    }

    void reactToolbar(Node*o){
        layoutLinear(o, 0).{
            mkDrawButton(o, 0).{
                o.typePrimary()
                o.text = str("Download")
                o.onClick = ^void(MouseEvent *me){
                    // self.addTileLayer()
                }
            }
            mkDrawButton(o, 0).{
                o.text = str("添加tilelayer")
                o.onClick = ^void(MouseEvent *me){
                    // self.addTileLayer()
                }
            }
            mkDrawButton(o, 0).{ o.isActive = true; o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/setting.png"); }

            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/project.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/open-door.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/collapse.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/expand.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/add.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/delete.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/bezier.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/user.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/shortcut.png"); }

            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/file-open.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/save.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/print.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/play.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/pause.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/apps.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/align-left.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/align-center.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/align-right.png"); }

            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/align-top.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/align-middle.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/align-bottom.png"); }

            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/download.png"); }

            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/sort-a-to-z.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/sort-z-to-a.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/filter.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/search.png"); }

            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/node.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/cube.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/text-view.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/edit-text.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/image-view.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/button.png"); }

            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/directory.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/camera.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/light.png"); }
            mkDrawButton(o, 0).{ o.normalBg = 0; o.src = Path_resolveFromExecutionDir("../asset/icon-light/path.png"); }


        }
    }

    void react(){
        // printf("react SpriteSheetEditor\n")
        Theme* t = themeIns()
        self.win.rootView.{
            self.reactMenubar(o)
            self.reactToolbar(o)
            self.reactDocklayout(o)
        }
    }


    void onWindowEvent(Event *e){
        if e instanceof KeyEvent {
            KeyEvent *ke = (KeyEvent*)e
            printf("2窗口收到键盘消息:%s\n", ke.key.str);
            //前进
            if ke.key.equals("W"){
                self.sceneView.camera.moveForward()
            }
            if ke.key.equals("S"){
                self.sceneView.camera.moveBackward()
            }
            //左转
            if ke.key.equals("A"){
                self.sceneView.camera.rotateLeft()
            }
            if ke.key.equals("D"){
                self.sceneView.camera.rotateRight()
            }
            //升降
            if ke.key.equals("E"){
                self.sceneView.camera.rise()
            }
            if ke.key.equals("Q"){
                self.sceneView.camera.fall()
            }
        }
    }

    void showWindow(){
        self.win = new Window() //先创建窗口，初始化opengl环境



        self.win.{
            o.cbOnEvent = ^void (Event*e){
                self.onWindowEvent(e)
            }

            new LayoutLinear().{
                o.backgroundColor = themeIns().bg1 //0xffffffff
                o.direction.set("column")
                o.alignItems.set("stretch")

                // ChessBgViewCallback@ tmp= new ChessBgViewCallback()
                // o.cb  = tmp

                self.win.setRootView(o)
            }

            self.react()


            o.setTitle("Horo编辑器")
            o.setSize(800, 600)
            o.moveToCenter()
            o.show()
        }
    }
    void openProject(const char *path){
        registerNodes()

        // String@ projectDirPath = Path_dirname(Path_getExecutionPath().str).add("/../asset/matl")
        // printf("projectDirPath:%s\n", projectDirPath.str)
        Path_setcwd(path)


        String@ abspath = Path_toAbsolute(path)
        String@ cwd = Path_getcwd();
        printf("打开项目。 项目路径为:%s. cwd:%s", abspath.str, cwd.str)
        Project_ins().init(abspath.str)

        //确保opengl环境有初始化了
        Window@ win = new Window();

        // self.editCtx.openPrefab("prefab/button.prefab.json")
        self.editCtx.openPrefab("prefab/3d.prefab.json")


        self.showWindow()
        win.close()
    }
}