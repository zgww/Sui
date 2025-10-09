package SuiDesigner

#include <stdio.h>
#include <string.h>


import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Path.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/View/Drag.orc"

import * from "../Sui/Core/View.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/Core/Canvas.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sgl/Scene.orc"
import * from "../Sgl/Camera.orc"
import * from "../Sgl/Raycaster.orc"
import * from "../Sgl/Obj3d.orc"
import * from "../Sgl/Light.orc"
import * from "../Sgl/SpotLight.orc"
import * from "../Sgl/PointLight.orc"
import * from "../Sgl/Mesh.orc"
import * from "../Sgl/Billboard.orc"
import * from "../Sgl/GeometryBox.orc"
import * from "../Sgl/GeometryLine.orc"
import * from "../Sgl/GeometrySphere.orc"
import * from "../Sgl/Material.orc"
import * from "../Sgl/PerspectiveCamera.orc"
import * from "./SglEditCtx.orc"
import * from "./SglGizmo.orc"
import * from "./ANode.orc"

import * from "../HoroEditor/HoroEditor.orc"



// gizmo树更新. 由editor发起。 主要是tool和select node等结点需要
// 绘制
// 事件响应
class ToolBase {
    // 工具名称
    String@ name = str("")
    // 图标
    String@ iconPath

    ToolMgr@ mgr

    // 工具启用
    void onEnable(){
    }
    void onDisable(){
    }
    void reactGizmo(Obj3d* gizmoScene){
    }
    void onEvent(Event* e) {
    }
    void draw2d(Canvas *canvas){
    }
    void reactGizmosView(Node* o){
    }
}

class ToolSelect extends ToolBase{

    Vec3 leftPos = mkVec3(-200, 0, -200)
    Drag@ drag= new Drag()

    void onEnable(){
        printf("onEnable ToolSelect\n.");
        self.drag .onDrag = ^void (Drag *d){
            printf("on drag gizmo left\n")
            self.leftPos.add3fLocal(
                d.deltaPos.x,
                -d.deltaPos.y,
                0
            )
        }
    }
    void onDisable(){
        printf("onDisable ToolSelect\n.");
    }
    void draw2d(Canvas *canvas){
        // canvas.beginPath()
        // canvas.rect(10, 10, 100, 100)
        // canvas.fillColorByInt32(0xff0000ff)
        // canvas.fill()
    }
    void reactGizmosView(Node* o){
        // mkImageView(o, 0).{
        //     // printf("gizmos:%p\n", o)
        //     o.setSrc(str("../asset/gizmo/camera.png"))
        //     // o.height = 32
        //     o.width = 32
        //     o.setImageMode(WidthFix)

        //     Vec3 clientPos = self.mgr.camera.project(mkVec3(0, 0, 0))
        //     Vec2 clientSize = self.mgr.editCtx.sceneView.frame.getSize()

        //     o.frame.x = clientSize.width() * (clientPos.x + 1.0 ) / 2.0 - o.frame.width / 2.0
        //     o.frame.y = clientSize.height() * (1.0 - (clientPos.y + 1.0) / 2.0) - o.frame.height / 2.0

        //     // o.backgroundColor = 0xffffffff
        //     // o.border.setAll(2, 0xff000000)

        //     o.cbOnEvent = ^void(Event *e){
        //         if e instanceof MouseEvent {
        //             MouseEvent* me = (MouseEvent*)e
        //             if me.button == 1 && me.isClickInBubble(){
        //                 printf("\n\n点击了 gizmos 2d view\n\n");
        //                 me.stopPropagation()
        //                 Toast_make("点击了camera")
        //             }
        //         }
        //     }
        // }
    }

    void onEvent(Event* e) {
        if e instanceof MouseEvent {
            MouseEvent *me = (MouseEvent*)e
            if me.button == 1 && me.isClickInBubble(){
                Raycaster@ raycaster = new Raycaster()
                raycaster.ray = self.mgr.camera.mkRay(me.ndcPos)
                RayCheckResult r = raycaster.raycastTree(self.mgr.scene)

                printf("\n\nToolSelect. ndcPos:%s onClick succ:%d dist:%f, point:%s, name:%s\n", 
                    me.ndcPos.toString().str,
                    r.succ,
                    r.distance,
                    r.point.toString().str,
                    r.obj ? r.obj.name.str:"null"
                );
                if r.succ {
                    //选中r.obj
                    // self.mgr.editCtx.state.setSelected(r.obj)
                    self.mgr.editor.selectByNode(r.obj)
                    printf("选中对象....")
                }
            }
        }
    }
    void reactGizmo(Obj3d* o){
        // printf("reactGizmo. toolselect\n")

        // mkMesh(o, 0).{
        //     if o.isNewForReact{
        //         o.material = new Material()
        //         o.material.load("../asset/hi.matl.json")
        //         GeometryBox@ box = new GeometryBox()
        //         box.width = 100
        //         box.height = 100
        //         box.depth = 100

        //         box.build()
        //         o.geometry = box
        //     }
        //     o.position.set(0, 500, -500)
        // }
        bool dragging = false;
        ^void cbOnEvent(Event *e){
            if e instanceof ViewEvent{
                ViewEvent *ve = (ViewEvent*)e
                // printf("box gizmo.cbOnEvent:%s. %s\n", e.name.str, ve.target.name.str);
            }
            if e instanceof MouseEvent {
                MouseEvent *me = (MouseEvent*)e
                self.drag.onMouseDown(me)
                if me.isCapture {



                    // if me.isMouseDown {
                    //     dragging = true
                    // }
                    // else if me.isMouseUp {
                    //     dragging = false
                    // }
                    // else if me.isMouseMove {
                    //     printf("dragging. isMouseMove name:%d %s\n", dragging, me.currentTarget.name.str);
                    //     // if dragging {
                    //         if me.currentTarget.name.equals("left") {
                    //             self.leftPos.add3fLocal(me.clientX, me.clientY, 0)
                    //             printf("drag leftPos:%s\n", self.leftPos.toString().str)
                    //         }
                    //     // }
                    // }
                    // // printf("\ngizmo dragging");
                    printf("box gizmo.cbOnEvent:%s. %s. dragging:%d isCapture:%d\n", e.name.str, me.target.name.str, dragging, me.isCapture);
                }
            }
        }

        Obj3d *obj3d = self.mgr.selectNode 
        if obj3d instanceof Obj3d {
            // SglGizmo_scale(o, 0, obj3d);
            SglGizmo_rotate(o, 0, obj3d);
            // SglGizmo_translate(o, 0, obj3d);
        }


        // Mesh* mesh = null
        // mesh = SglGizmo_box(o, 0, 60, self.leftPos, 0xffffffff)
        // mesh.name = str("left")
        // mesh.cbOnEvent = cbOnEvent

        // mesh = SglGizmo_box(o, 0, 60, mkVec3(100, 0, -100), 0xffff0000)
        // mesh.name = str("right")
        // mesh.cbOnEvent = cbOnEvent

        // mesh = SglGizmo_box(o, 0, 60, mkVec3(100, 100, -100), 0xff00ff00)
        // mesh.name = str("right-top")
        // mesh.cbOnEvent = cbOnEvent

        // mesh = SglGizmo_box(o, 0, 60, mkVec3(0, -100, -100), 0xff0000ff)
        // mesh.name = str("bottom")
        // mesh.cbOnEvent = cbOnEvent

        // mesh = SglGizmo_box(o, 0, 60, mkVec3(0, 0, 0), 0xffffff00)
        // mesh.name = str("center")
        // mesh.cbOnEvent = cbOnEvent

        if self.mgr.selectNode instanceof PerspectiveCamera{
            PerspectiveCamera* cam = (PerspectiveCamera*)self.mgr.selectNode
            mkMesh(o, 0). {
                if o.isNewForReact {
                    GeometryLine@ geom = new GeometryLine()
                    cam.updateProjectionMat()
                    cam.updateViewMat()

                    geom.buildCameraHelper(cam)
                    o.geometry = geom
                    o.material = new Material()
                    o.material.load("../asset/line.matl.json")
                }
                o.position = cam.localToWorld(mkVec3(0, 0, 0))
                //TODO 旋转。。。
                cam._world_transform.decompose(
                    &o.position,
                    &o.quaternion,
                    &o.scale,
                )
                o.rotation = o.quaternion.toVec3AsEuler(null)

                // scene.appendChild(o)
            }
        }
        else if self.mgr.selectNode instanceof SpotLight{
            SpotLight* l = (SpotLight*)self.mgr.selectNode
            mkMesh(o, 0). {
                if o.isNewForReact {
                    GeometryLine@ geom = new GeometryLine()

                    geom.buildSpotLightHelper(l)
                    o.geometry = geom
                    o.material = new Material()
                    o.material.load("../asset/line.matl.json")
                }
                o.position = l.localToWorld(mkVec3(0, 0, 0))
                // scene.appendChild(o)
            }
        }
        else if self.mgr.selectNode instanceof PointLight{
            PointLight* l = (PointLight*)self.mgr.selectNode
            mkMesh(o, 0). {
                if o.isNewForReact {
                    GeometrySphere@ geom = new GeometrySphere()
                    geom.radius = l.distance
                    geom.widthSegments = 8
                    geom.heightSegments = 8
                    geom.build()

                    o.geometry = geom
                    o.material = new Material()
                    o.material.load("../asset/box.matl.json")
                    o.material.wireframe = true
                }
                o.position = l.localToWorld(mkVec3(0, 0, 0))
                // scene.appendChild(o)
            }
        }

    }
}

class ToolMgr {
    //当前选中的工具
    ToolBase@ tool 
    Node@ selectNode 

    Scene@ scene
    Camera@ camera
    SglEditCtx@ editCtx 

    HoroEditor@ editor



    void setTool(ToolBase* tool){
        if self.tool == tool{
            return
        }
        if self.tool {
            self.tool.onDisable()
        }
        self.tool = tool
        if self.tool{
            self.tool.mgr = self
            self.tool.onEnable()
        }
    }

    void onEvent(Event *e){
        // printf("on SceneEvent e:%p. %s\n", e, e.name.str)
        if self.tool {
            self.tool.onEvent(e)
        }
    }
    void reactGizmo(SglGizmo* gizmoScene){
        if self.tool {
            gizmoScene.scene.{
                self.tool.reactGizmo(gizmoScene.scene)
            }
        }
    }

    void _reactGizmosForNode(Node* n){
        Node* o = self.gizmosView
        if n instanceof Obj3d {
            Obj3d* obj3d = (Obj3d*)n
            if n instanceof Light {
                mkImageView(o, (long long)n).{
                    // printf("gizmos:%p\n", o)
                    o.setSrc(Path_resolveFromExecutionDir("../asset/gizmo/light.png"))
                    // o.height = 32
                    o.width = 32
                    o.setImageMode(WidthFix)

                    Vec3 worldPos = obj3d.localToWorld(mkVec3(0, 0, 0))
                    Vec3 clientPos = self.camera.project(worldPos)
                    Vec2 clientSize = self.editCtx.sceneView.frame.getSize()

                    o.frame.x = clientSize.width() * (clientPos.x + 1.0 ) / 2.0 - o.frame.width / 2.0
                    o.frame.y = clientSize.height() * (1.0 - (clientPos.y + 1.0) / 2.0) - o.frame.height / 2.0

                    o.cbOnEvent = ^void(Event*e){
                        if e instanceof MouseEvent {
                            MouseEvent* me = (MouseEvent*)e
                            if me.button == 1 && me.isClick() {
                                printf("click light\n")

                                self.editor.selectByNode(n)
                            }
                        }
                    }
                }
            }
            else if n instanceof Camera {
                mkImageView(o, (long long)n).{
                    // printf("gizmos:%p\n", o)
                    o.setSrc(Path_resolveFromExecutionDir("../asset/gizmo/camera.png"))
                    // o.height = 32
                    o.width = 32
                    o.setImageMode(WidthFix)

                    Vec3 worldPos = obj3d.localToWorld(mkVec3(0, 0, 0))
                    Vec3 clientPos = self.camera.project(worldPos)
                    Vec2 clientSize = self.editCtx.sceneView.frame.getSize()

                    o.frame.x = clientSize.width() * (clientPos.x + 1.0 ) / 2.0 - o.frame.width / 2.0
                    o.frame.y = clientSize.height() * (1.0 - (clientPos.y + 1.0) / 2.0) - o.frame.height / 2.0
                    o.cbOnEvent = ^void(Event*e){
                        if e instanceof MouseEvent {
                            MouseEvent* me = (MouseEvent*)e
                            if me.button == 1 && me.isClick() {
                                printf("click camera\n")
                                self.editor.selectByNode(n)
                            }
                        }
                    }
                }

            }
        }
    }
    Node* gizmosView
    void reactGizmosView(Node* o){
        self.gizmosView = o
        self.scene.walk(self._reactGizmosForNode, self)

        if self.tool {
            self.tool.reactGizmosView(o)
        }
    }
    void draw2d(Canvas *canvas){

        if self.tool {
            self.tool.draw2d(canvas)
        }

    }
}