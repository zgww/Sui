package Sgl

#include <stdlib.h>
#include <stdio.h>
#include "./UnitOpengl.h"

import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Time.orc"
import * from "../Orc/Math.orc"
import * from "./Scene.orc"
import * from "./Camera.orc"
import * from "./Obj3d.orc"
import * from "./Material.orc"
import * from "./Geometry.orc"
import * from "./GeometryLine.orc"
import * from "./Light.orc"
import * from "./Mat.orc"
import * from "./PointLight.orc"
import * from "./DirLight.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Color.orc"

//渲染上下文
class DrawCtx {
    List@ lights = new List()
    // List@ cameras = new List()

    Scene *scene 
    Camera *camera

    Vec2 frameSize = mkVec2(500, 500);

    long long prevTickMs = 0;
    long long dtMs = 0 //两次tick的间隔毫秒
    float dtSec = 0.0
    float passSec = 0.0

    Material@ depthMatl = new Material()
    Material@ lineMatl = new Material()
    GeometryLine@ lineGeometry = new GeometryLine()

    PointerArray@ transparentObj3ds = new PointerArray()

    ^void() cbAfterDraw

    void ctor(){
        self.depthMatl.load("../asset/depth.matl.json")
        self.lineMatl.load("../asset/line.matl.json")
    }

    bool addTransparentObj3dIfIsTransparent(Obj3d* obj3d, Material *matl){
        if matl && matl.transparent {
            self.transparentObj3ds.add(obj3d)
            return true
        }
        return false
    }

    void drawLineGeometry(){
        self.lineGeometry.draw(self.lineMatl)
    }
    void drawAxis(){
        {
            //绘制坐标轴
            self.lineGeometry.{
                // x轴
                o.color = 0xffff0000
                o.moveTo(-100000, 0, 0)
                o.lineTo( 100000, 0, 0)

                // y轴
                o.color = 0xff00ff00
                o.moveTo(0, -100000, 0)
                o.lineTo(0,  100000, 0)

                // z轴
                o.color = 0xff00a0ff
                o.moveTo(0, 0, -100000)
                o.lineTo(0, 0,  100000)
            }
        }
    }

    // void collectCameras(){
    //     if !self.scene {
    //         return;
    //     }
    // }

    void collectLights(){
        if !self.scene {
            return;
        }
        // self._collectLight;
        // Node *n = (Node*)self.scene;
        // n.walk(null, self)
        // Obj3d *o3d = (Obj3d*)self.scene;
        // o3d.walk(null, self)
        self.lights.clear()
        self.scene.walk(self._collectLight, self)
    }

    void _collectLight(Node *n){
        if n instanceof Light {
            self.lights.add((Light*)n)
        }
    }

    void tick(Scene *scene){
        long long nowMs = Time_unixMs()
        self.dtMs = 0 
        self.dtSec = 0 
        if self.prevTickMs > 0 {
            self.dtMs = nowMs - self.prevTickMs
            self.dtSec = self.dtMs / 1000.0
            // printf("nowMs:%lld, prev:%lld\n", nowMs, self.prevTickMs)
        }
        self.passSec += self.dtSec
        self.prevTickMs = nowMs
        scene.walkIf(self.tickObj3d, self)
    }
    bool tickObj3d(Node *n){
        if n instanceof Obj3d {
            Obj3d *obj3d = (Obj3d*)n
            if !obj3d.visible {
                return false
            }
            obj3d.tick(self)

            return true
        }
        return false
    }

    //绘制深度图，实现阴影要用
    //绘制深度图共用同一个场景， 使用指定的相机。 根据灯光不同，如方向光用正交相机，点光源用
    //透视相机
    //绘制深度图时，通常是共用同一个材质的
    void drawDepth(Scene* scene, Camera *camera){
        if scene {
            self.scene = scene
            self.camera = camera

            self.tick(scene)

            self.collectLights()

            //透明度排序
            glViewport(
                (int)(self.camera.viewport.x * self.frameSize.x),
                (int)(self.camera.viewport.y * self.frameSize.y),
                (int)(self.camera.viewport.w * self.frameSize.x),
                (int)(self.camera.viewport.h * self.frameSize.y),
            )

            //更新模型矩阵
            scene.updateWorldTransformAndSubtree()

            //更新相机的矩阵
            self.camera.updateProjectionMat()
            self.camera.updateViewMat()


            self.depthMatl.view = camera.view
            self.depthMatl.projection = camera.projection

            scene.walk(self._drawNodeDepth, self)
        }
    }
    void _drawNodeDepth(Node *n){
        if n instanceof Obj3d {
            Obj3d *o3d = (Obj3d*)n

            self.depthMatl.model = o3d._world_transform

            o3d.drawDepth(self)
        }
    }

    void updateViewport(){
        glViewport(
            (int)(self.camera.viewport.x * self.frameSize.x),
            (int)(self.camera.viewport.y * self.frameSize.y),
            (int)(self.camera.viewport.w * self.frameSize.x),
            (int)(self.camera.viewport.h * self.frameSize.y),
        )
    }

    // [camera]?
    void draw(Scene *scene, Camera *camera){
        if !scene {
            printf("DrawCtx fail. no scene\n")
            return;
        }

        self.scene = scene
        if camera {
            self.camera = camera
        }
        if !self.camera {
            self.camera = scene.findNodeByClass(Camera)
            if !self.camera {
                printf("DrawCtx fail. no camera\n")
                return
            }
        }

        self.transparentObj3ds.clear()

        self.tick(scene)

        self.collectLights()
        // self.collectCameras()

        self.updateViewport()
        //透明度排序

        //更新模型矩阵
        scene.updateWorldTransformAndSubtree()

        //更新相机的矩阵
        self.camera.updateProjectionMat()
        self.camera.updateViewMat()

        self.lineGeometry.clear()

        //绘制
        scene.draw(self)
        self.drawTransparentObj3ds()

        if self.cbAfterDraw{
            self.cbAfterDraw()
        }

        // scene.walk(self._drawNodeDepth, self)

        self.setMvpToMaterial(null, self.lineMatl)

        // self.lineGeometry.appendVertexAndColor(mkVec3(0,0,0), 0xff0000ff)
        // self.lineGeometry.appendVertexAndColor(mkVec3(400,400,0.5), 0xffff0000)
        // self.lineGeometry.appendVertexAndColor(mkVec3(400,400,0.5), 0xffff0000)
        // self.lineGeometry.appendVertexAndColor(mkVec3(800,-400,0.5), 0xff00ffff)


    }
    void drawTransparentObj3ds(){
        int size = self.transparentObj3ds.size();
        if size <= 0 {
            return;
        }

        //计算在相机中的位置
        Mat view = self.camera.view

        for int i = 0; i < size; i++{
            Obj3d *obj3d = self.transparentObj3ds.get(i)
            if obj3d{
                Vec3 worldPos = obj3d.localToWorld(mkVec3(0, 0, 0))
                obj3d._viewPosition = view.mulVec3(worldPos)
            }
        }
        //按深度排序
        qsort(self.transparentObj3ds.data, size, pointerSize(), cmpObj3dDepth)


        //绘制
        for int i = 0; i < size; i++{
            Obj3d *obj3d = self.transparentObj3ds.get(i)
            if obj3d{
                obj3d.drawTransparent(self)
            }
        }
    }
    //设置矩阵
    void setMvpToMaterial(Obj3d *obj3d, Material *material){
        // if obj3d {
        //     material.model = obj3d._world_transform
        // }
        // else {
        //     material.model = mkMatIdentity() //在世界坐标系下
        // }
        // material.view = self.camera.view
        // material.projection = self.camera.projection

        material.setMvp(
            obj3d ? obj3d._world_transform : mkMatIdentity(),
            self.camera.view,
            self.camera.projection,
        )
    }

    void setGlobalInfosToMaterial(Material *matl){
        //累计秒数
        //帧间隔
        matl.setUniform4f("time", 
            self.passSec, 
            self.dtSec, 
            0, 0
        )
        self.setLightsToMaterial(matl)
    }

    //设置灯光信息到材质上
    void setLightsToMaterial(Material *matl){
        for int i = 0; i < self.lights.size(); i++{
            Light *light = (Light*)self.lights.get(i)
            // light.setToMaterial(matl)
            if light instanceof PointLight {
                PointLight *pl = (PointLight*)light;
                Rgbaf c = mkRgbafByInt(pl.color)

                //要求使用结构体
                // struct PointLight {
                //     vec3 position
                //     vec3 color
                //     float intensity
                //     float distance
                //     float decay
                // }
                // printf("set light\n")

                Vec3 pos = light.localToWorld(mkVec3(0, 0, 0))
                matl.setUniform3f("pointLight.position", pos.x, pos.y, pos.z)
                matl.setUniform3f("pointLight.color", c.r, c.g, c.b);
                matl.setUniform1f("pointLight.intensity", pl.intensity)
                matl.setUniform1f("pointLight.distance", pl.distance)
                matl.setUniform1f("pointLight.decay", pl.decay)
            }
            else if light instanceof DirLight {
                DirLight *pl = (DirLight*)light;
                Rgbaf ambient = mkRgbafByInt(pl.ambient)
                Rgbaf diffuse = mkRgbafByInt(pl.diffuse)
                Rgbaf specular = mkRgbafByInt(pl.specular)

                Vec3 pos = light.localToWorld(mkVec3(0, 0, 0))
                pos = pos.scale(-1)
                pos = pos.normal()
                matl.setUniformVec3("dirLight.direction", pos);//光源->物体
                matl.setUniform3f("dirLight.ambient", ambient.r, ambient.g, ambient.b);
                matl.setUniform3f("dirLight.diffuse", diffuse.r, diffuse.g, diffuse.b);
                matl.setUniform3f("dirLight.specular", specular.r, specular.g, specular.b);
            }

        }
    }
}
static int cmpObj3dDepth(const void *a, const void *b){
    Obj3d* aobj = a;
    Obj3d* bobj = b;
    float dz =  aobj._viewPosition.z - bobj._viewPosition.z;
    return dz <= 0 ? -1 : 0;
}