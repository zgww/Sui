package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "./Mat.orc"
import * from "./Obj3d.orc"
import * from "./Material.orc"
import * from "./Geometry.orc"
import * from "./GeometryLine.orc"
import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Vao.orc"
import * from "./Raycaster.orc"
import * from "./DrawCtx.orc"
import * from "../Orc/List.orc"
import * from "../Orc/String.orc"
import * from "../Orc/Map.orc"
import * from "../Json/Json.orc"

import * from "./GeometryBox.orc"
import * from "./GeometryPlane.orc"
import * from "./GeometrySphere.orc"
import * from "../HoroEditor/HoroGeometryPreviewView.orc"


class Mesh extends Obj3d {
    //材质，，含program和opengl开关状态
    Material@ material;
    //顶点数据
    Geometry@ geometry;

    //顶点数据与材质的绑定关系
    Vao@ vao = new Vao();
    Vao@ depthVao = new Vao();

    String@ geometryPath;
    String@ materialPath;

    void setMaterialPath(String@ p){
        if p && !p.endsWith(".matl.json") {
            printf("not a matl.json file\n");
            return 
        }
        self.materialPath = p
        if p && p.notEmpty() {
            new Material()~{
                o.load(p.str)
                self.material = o
            }
        }
        else {
            self.material = null
        }
    }
    void setGeometryPath(String@ p){
        self.geometryPath = p

        //内置的几何体
        // if p.equals("Geometry/Box.geometry.json"){
        //     GeometryBox@ geom = new GeometryBox()
        //     geom.build()
        //     self.geometry = geom
        //     self.material = new Material()
        //     self.material.load("../asset/basic.matl.json")
        // }
        // else if p.equals("Geometry/Sphere.geometry.json"){
        //     GeometrySphere@ geom = new GeometrySphere()
        //     geom.build()
        //     self.geometry = geom
        //     self.material = new Material()
        //     self.material.load("../asset/basic.matl.json")
        // }
        // else if p.equals("Geometry/Plane.geometry.json"){
        //     GeometryPlane@ geom = new GeometryPlane()
        //     geom.build()
        //     self.geometry = geom
        //     self.material = new Material()
        //     self.material.load("../asset/basic.matl.json")
        // }
        // else 
        {
            Geometry@ geom = HoroGeometry_parseGeometryJson(p.str)
            self.geometry = geom
            self.material = new Material()
            self.material.load("../asset/basic.matl.json")
        }
        printf("设置几何路径:%s\n", p ? p.str: "null")
    }


    void tick(DrawCtx *ctx){
        // printf("mesh tick:%lld\n", ctx.dtMs);
    }
    void draw(DrawCtx *ctx){
        if self.material == null ||
            self.geometry == null {
            return;
        }
        //如果是透明的，就放在最后，按深度排序并绘制
        if ctx.addTransparentObj3dIfIsTransparent(self, self.material){
        }
        else {
            self.drawSelf(ctx)
        }

        self.drawChildren(ctx)
    }
    void drawSelfRaw(DrawCtx* ctx, Vao* vao, Material* material){
        //更新矩阵
        // self.material.model = self._world_transform
        // self.material.view = ctx.camera.view
        // self.material.projection = ctx.camera.projection
        ctx.setMvpToMaterial(self, material)
        ctx.setGlobalInfosToMaterial(material)

        if self.geometry instanceof GeometryLine {
            GeometryLine* gl = (GeometryLine*)self.geometry
            gl.draw(self.material)
            return
        }

        vao.draw(
            self.geometry,
            material
        )
    }
    void drawSelf(DrawCtx *ctx){
        self.drawSelfRaw(ctx, self.vao, self.material)
    }
    void drawDepth(DrawCtx *ctx){
        Material *matl = ctx.depthMatl

        //更新矩阵
        matl.model = self._world_transform
        matl.view = ctx.camera.view
        matl.projection = ctx.camera.projection
        matl.updateMvp()

        ctx.setGlobalInfosToMaterial(matl)

        self.depthVao.draw(
            self.geometry,
            matl
        )
    }

    bool hitTestSelfByRaycaster(Raycaster* raycaster){
		RayCheckResult r = raycaster.raycastGeometry(self, self.geometry)
        raycaster.result = r;
		return r.succ
	}
}
Mesh@ mkMesh(void* parent, long long key){
    return (Mesh@)gocNode(
        key?(void*)key:__builtin_return_address(0),
        (Node*)parent, Mesh)
}
