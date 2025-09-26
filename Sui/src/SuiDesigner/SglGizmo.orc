package SuiDesigner

#include <stdio.h>
#include <string.h>


import * from "../Orc/Math.orc"
import * from "../Sgl/Obj3d.orc"
import * from "../Sgl/Scene.orc"
import * from "../Sgl/Mesh.orc"
import * from "../Sgl/Material.orc"
import * from "../Sgl/GeometryBox.orc"
import * from "../Sgl/GeometryRect.orc"
import * from "../Sgl/GeometryLine.orc"
import * from "../Sgl/GeometryCone.orc"
import * from "../Sgl/GeometryTorus.orc"
import * from "../Sgl/DrawCtx.orc"
import * from "../Sgl/Tex2d.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sgl/PerspectiveCamera.orc"
import * from "../Sgl/Ray.orc"
import * from "../Sgl/Raycaster.orc"
import * from "../Sgl/Billboard.orc"



// static struct HitTest{
//     SglGizmo* sglGizmo
//     Ray ray
//     Obj3d* target
//     Raycaster* 
// }
// extension HitTest {
//     bool hitTestNode(Node *n){
//         if n instanceof Obj3d {
//             Obj3d* obj3d = (Obj3d*)n

//         }
//     }
// }
// static bool _hitTestNode(HitTest* _self, Node*n){
//     if n instanceof Obj3d {
//         Obj3d* obj3d = (Obj3d*)n
//         if obj3d.hitTestSelfByRay(ray){
//             _self.target = obj3d

//             return false // found. stop walk
//         }

//         return true // walk children
//     }
//     return false
// }

// gizmo树更新. 由editor发起。 主要是tool和select node等结点需要
// 绘制
// 事件响应
class SglGizmo {
    Scene@ scene = new Scene()
    PerspectiveCamera@ camera = null

    Raycaster@ raycaster = new Raycaster()

    ^Vec2 (Vec2 clientPos) getNdcPos;

    //分发鼠标事件
    void dispatchMouseEvent(MouseEvent *e){
        // printf("分发鼠标事件\n")
        self.hitTest(e)
    }
    void hitTest(MouseEvent *e){
        // Vec2 ndcPos = mkVec2(0, 0)
        // if self.getNdcPos != null{
        //     ndcPos = self.getNdcPos(mkVec2(0, 0))
        // }
        // e.ndcPos.x = -0.15
        // e.ndcPos.y = 0

        self.raycaster.ray = self.camera.mkRay(e.ndcPos)
        RayCheckResult r = self.raycaster.raycastTree(self.scene)


        // HitTest info
        // memset(&info, 0, sizeof(HitTest))

        // info.sglGizmo = self
        
        // self.scene.walkIf(_hitTestNode, &info)

        // 有目标
        // if info.target {
        // printf("raycast succ:%d\n", r.succ);
        if r.succ {
            Node* cur = r.obj
            e.target = cur
            while cur {
                //gizmo只做事件冒泡,无捕获
                // info.target.onEvent(e)
                e.currentTarget = cur
                cur.emit(e)
                if e.isStopPropagation {
                    break
                }
                cur = cur.parent
            }
        }
        // }
    }
    void onEvent(Event *e){
        if e instanceof MouseEvent {
            self.dispatchMouseEvent((MouseEvent*)e)
        }
    }

    void draw(DrawCtx* ctx){
        self.camera = ctx.camera

        ctx.tick(self.scene)

        self.scene.updateWorldTransformAndSubtree()
        self.scene.draw(ctx)

        ctx.lineGeometry.{
            o.color = 0xffff00ff
            o.moveTo(0, 0, 0)
            o.lineTo(100, 10000, 0)
        }
    }
}

Obj3d@ SglGizmo_translate(Obj3d* o, long long key, Obj3d@ target){
    mkMesh(o, key ? key: (long long)__builtin_return_address(0)).{
        float w = 100;
        if o.isNewForReact {
            GeometryLine@ geom = new GeometryLine()
            geom.color = 0xffff0000; geom.moveTo(0, 0, 0); geom.lineTo(w, 0, 0);
            geom.color = 0xff00ff00; geom.moveTo(0, 0, 0); geom.lineTo(0, w, 0);
            geom.color = 0xff0000ff; geom.moveTo(0, 0, 0); geom.lineTo(0, 0, w);
            o.geometry = geom
            o.material = new Material()
            o.material.load("../asset/line.matl.json")
        }
        target._world_transform.decompose(
            &o.position,
            &o.quaternion,
            &o.scale,
        )


        ^void cbOnEvent(Event *e){
            if e instanceof MouseEvent {
                MouseEvent *me = (MouseEvent*)e
                printf("mouse event:%s\n", me.toString().str)


                if me.button == 1 && me.isMouseDown && me.isBubble() {
                    Mesh@ mesh = (Mesh@)me.currentTarget
                    if mesh instanceof Mesh {
                        Drag@ drag = new Drag()
                        drag.onDrag = ^void(Drag *d){
                            if d.isDragging {
                                printf("dragging...%s %f\n", mesh.name.str, d.deltaPos.x)

                                if mesh.name.equals("xArrow"){
                                    //改为与面求交点
                                    target.position.x += d.deltaPos.x
                                }
                                else if mesh.name.equals("yArrow"){
                                    target.position.y += d.deltaPos.x
                                }
                                else if mesh.name.equals("zArrow"){
                                    target.position.z += d.deltaPos.x
                                }
                            }
                        }
                        drag.onMouseDown(me)
                    }
                }
            }
        }

        //三个块
        Mesh* mesh;
        mesh = SglGizmo_cone(o, 0, 60, mkVec3(w, 0, 0), 0xffff0000)
        mesh.name.set("xArrow")
        mesh.cbOnEvent = cbOnEvent
        mesh.rotation.z = -PI / 2

        mesh = SglGizmo_cone(o, 0, 60, mkVec3(0, w, 0), 0xff00ff00)
        mesh.name.set("yArrow")
        mesh.cbOnEvent = cbOnEvent

        mesh = SglGizmo_cone(o, 0, 60, mkVec3(0, 0, w), 0xff0000ff)
        mesh.name.set("zArrow")
        mesh.cbOnEvent = cbOnEvent
        mesh.rotation.x = PI / 2

        return o;
    }
}
Obj3d@ SglGizmo_rotate(Obj3d* o, long long key, Obj3d@ target){
    mkMesh(o, key ? key: (long long)__builtin_return_address(0)).{
        float w = 100;
        if o.isNewForReact {
            GeometryLine@ geom = new GeometryLine()
            geom.color = 0xffff0000; geom.moveTo(0, 0, 0); geom.lineTo(w, 0, 0);
            geom.color = 0xff00ff00; geom.moveTo(0, 0, 0); geom.lineTo(0, w, 0);
            geom.color = 0xff0000ff; geom.moveTo(0, 0, 0); geom.lineTo(0, 0, w);
            o.geometry = geom
            o.material = new Material()
            o.material.load("../asset/line.matl.json")
        }
        target._world_transform.decompose(
            &o.position,
            &o.quaternion,
            &o.scale,
        )
        o.rotation = o.quaternion.toVec3AsEuler(null)


        ^void cbOnEvent(Event *e){
            if e instanceof MouseEvent {
                MouseEvent *me = (MouseEvent*)e
                printf("mouse event:%s\n", me.toString().str)


                if me.button == 1 && me.isMouseDown && me.isBubble() {
                    Mesh@ mesh = (Mesh@)me.currentTarget
                    if mesh instanceof Mesh {
                        Drag@ drag = new Drag()
                        drag.onDrag = ^void(Drag *d){
                            if d.isDragging {
                                printf("dragging...%s %f\n", mesh.name.str, d.deltaPos.x)

                                if mesh.name.equals("xTorus"){
                                    //改为与面求交点
                                    target.rotation.x += d.deltaPos.x / 180.0 * PI
                                }
                                else if mesh.name.equals("yTorus"){
                                    target.rotation.y += d.deltaPos.x / 180.0 * PI
                                }
                                else if mesh.name.equals("zTorus"){
                                    target.rotation.z += d.deltaPos.x / 180.0 * PI
                                }
                            }
                        }
                        drag.onMouseDown(me)
                    }
                }
            }
        }

        //三个块
        Mesh* mesh;
        mesh = SglGizmo_torus(o, 0, 60, mkVec3(0, 0, 0), 0xffff0000)
        mesh.name.set("xTorus")
        mesh.cbOnEvent = cbOnEvent
        mesh.rotation.y = PI / 2

        mesh = SglGizmo_torus(o, 0, 60, mkVec3(0, 0, 0), 0xff00ff00)
        mesh.name.set("yTorus")
        mesh.cbOnEvent = cbOnEvent
        mesh.rotation.x = PI / 2

        mesh = SglGizmo_torus(o, 0, 60, mkVec3(0, 0, 0), 0xff0000ff)
        mesh.name.set("zTorus")
        mesh.cbOnEvent = cbOnEvent

        return o;
    }
}
Obj3d@ SglGizmo_scale(Obj3d* o, long long key, Obj3d@ target){
    mkMesh(o, key ? key: (long long)__builtin_return_address(0)).{
        float w = 100;
        if o.isNewForReact {
            GeometryLine@ geom = new GeometryLine()
            geom.color = 0xffff0000; geom.moveTo(0, 0, 0); geom.lineTo(w, 0, 0);
            geom.color = 0xff00ff00; geom.moveTo(0, 0, 0); geom.lineTo(0, w, 0);
            geom.color = 0xff0000ff; geom.moveTo(0, 0, 0); geom.lineTo(0, 0, w);
            o.geometry = geom
            o.material = new Material()
            o.material.load("../asset/line.matl.json")
        }
        target._world_transform.decompose(
            &o.position,
            &o.quaternion,
            &o.scale,
        )


        ^void cbOnEvent(Event *e){
            if e instanceof MouseEvent {
                MouseEvent *me = (MouseEvent*)e
                printf("mouse event:%s\n", me.toString().str)


                if me.button == 1 && me.isMouseDown && me.isBubble() {
                    Mesh@ mesh = (Mesh@)me.currentTarget
                    if mesh instanceof Mesh {
                        Drag@ drag = new Drag()
                        drag.onDrag = ^void(Drag *d){
                            if d.isDragging {
                                printf("dragging...%s\n", mesh.name.str)

                                if mesh.name.equals("xCube"){
                                }
                                else if mesh.name.equals("yCube"){
                                }
                                else if mesh.name.equals("zCube"){
                                }
                            }
                        }
                        drag.onMouseDown(me)
                    }
                }
            }
        }

        //三个块
        Mesh* mesh;
        mesh = SglGizmo_box(o, 0, 40, mkVec3(w, 0, 0), 0xffff0000)
        mesh.name.set("xCube")
        mesh.cbOnEvent = cbOnEvent

        mesh = SglGizmo_box(o, 0, 40, mkVec3(0, w, 0), 0xff00ff00)
        mesh.name.set("yCube")
        mesh.cbOnEvent = cbOnEvent

        mesh = SglGizmo_box(o, 0, 40, mkVec3(0, 0, w), 0xff0000ff)
        mesh.name.set("zCube")
        mesh.cbOnEvent = cbOnEvent

        return o;
    }
}
Obj3d@ SglGizmo_image(Obj3d* o, long long key, const char *imgPath){
    mkBillboard(o, key ? key: (long long)__builtin_return_address(0)).{
        if o.isNewForReact{
            o.material = new Material()
            o.material.load("../asset/hi.matl.json")

            Tex2d@ tex = mkTex2dByPathCstr(imgPath)
            o.material.setUniformTex2d("tex", tex)

            GeometryRect@ box = new GeometryRect()
            box.build()

            o.geometry = box
        }
        // o.position = pos

        return o
    }
    return null
}
Obj3d@ SglGizmo_button(Node* o, long long key, const char *label, ^void() onClick){
    return null
}
// Obj3d@ SglGizmo_radio(Node* o, long long key, const char *label, ^void(bool checked) onChange){
//     return null
// }
Obj3d@ SglGizmo_text(Obj3d* o, long long key, const char *label){
    return null
}
Mesh@ SglGizmo_box(Obj3d* o, long long key,  float size, Vec3 pos, int color){
    mkMesh(o, key ? key: (long long)__builtin_return_address(0)).{
        if o.isNewForReact{
            o.material = new Material()
            o.material.load("../asset/basic.matl.json")
            GeometryBox@ box = new GeometryBox()
            box.width = size
            box.height = size
            box.depth = size
            box.color = color
            

            box.build()

            o.geometry = box
        }
        o.material.setUniformColor4fByInt32Color("color", color)
        o.position = pos

        return o
    }
}
Mesh@ SglGizmo_cone(Obj3d* o, long long key,  float size, Vec3 pos, int color){
    mkMesh(o, key ? key: (long long)__builtin_return_address(0)).{
        if o.isNewForReact{
            o.material = new Material()
            o.material.load("../asset/basic.matl.json")
            GeometryCone@ cone = new GeometryCone()
            cone.height = size
            cone.radiusBottom = size / 4.0

            cone.build()

            o.geometry = cone
        }
        o.material.setUniformColor4fByInt32Color("color", color)
        o.position = pos

        return o
    }
}
Mesh@ SglGizmo_torus(Obj3d* o, long long key,  float size, Vec3 pos, int color){
    mkMesh(o, key ? key: (long long)__builtin_return_address(0)).{
        if o.isNewForReact{
            o.material = new Material()
            o.material.load("../asset/basic.matl.json")
            GeometryTorus@ cone = new GeometryTorus()

            // cone.height = size
            // cone.radiusBottom = size / 4.0

            cone.build()

            o.geometry = cone
        }
        o.material.setUniformColor4fByInt32Color("color", color)
        o.position = pos

        return o
    }
}