
package Sgl

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Camera.orc"
import * from "./Mat.orc"
import * from "./Program.orc"
import * from "./SpotLight.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Orc/String.orc"

import * from "./Geometry.orc"


//线段
//适合用来调试用
class GeometryLine extends Geometry {
    float lineWidth = 1.0


    //顶点坐标
    Buffer@ vtxBuf = new Buffer()
    //顶点颜色
    Buffer@ colorBuf = new Buffer()

    int color = 0xffff0000 //最后的颜色

    Vec3 lastVtx
    bool hasLastVtx = false


    void clear(){
        self.vtxBuf.clear()
        self.colorBuf.clear()
    }

    void moveToVec3_color(Vec3 v, int color){
        self.moveToVec3(v)
        self.color = color
    }
    void moveToVec3(Vec3 v){
        self.moveTo(v.x, v.y, v.z)
    }
    void lineToVec3(Vec3 v){
        self.lineTo(v.x, v.y, v.z)
    }
    void lineToVec3_color(Vec3 v, int color){
        self.lineTo_color(v.x, v.y, v.z, color)
    }
    void moveTo_color(float x, float y, float z, int color){
        self.moveTo(x, y, z)
        self.color = color
    }
    void moveTo(float x, float y, float z){
        self.hasLastVtx = true
        ;&self.lastVtx.{
            o.x = x
            o.y = y
            o.z = z
        }
    }
    void lineTo(float x, float y, float z){
        self.appendVertexAndColor(self.lastVtx, self.color)

        self.lastVtx = mkVec3(x, y, z)
        self.appendVertexAndColor(self.lastVtx, self.color)
    }
    void lineTo_color(float x, float y, float z, int color){
        self.appendVertexAndColor(self.lastVtx, self.color)

        self.lastVtx = mkVec3(x, y, z)
        self.color = color
        self.appendVertexAndColor(self.lastVtx, self.color)
    }


    void appendVertex(Vec3 pos){
        self.appendVertexAndColor(pos, self.color)
    }
    void appendVertexAndColor(Vec3 pos, int color){
        Rgbaf c = mkRgbafByInt(color)
        self.color = color

        self.vtxBuf.appendFloat3(pos.x, pos.y, pos.z)
        self.colorBuf.appendFloat4(c.r, c.g, c.b, c.a)
    }
    void updateBuffer(){
        self.applyAttrByBuffer("position", self.vtxBuf, 3)
        self.applyAttrByBuffer("color", self.colorBuf, 4)
    }
    void draw(Material* matl){
        self.updateBuffer()


        matl.program.use()
        matl.prepareDraw()
        matl.updateUniforms()

        self.bindVertexAttribs(matl)

        glLineWidth(self.lineWidth)
        glDrawArrays(
            GL_LINES, //绘制线段
            0, //从第0个顶点开始
            self.vtxBuf.floatSize() / 3 //顶点数量
        );

        matl.endDraw()
    }


    void build(){
        Buffer@ buf = new Buffer()
        Buffer@ normal = new Buffer()
        Buffer@ uv = new Buffer()
        Buffer@ face = new Buffer()

        self.setAttrByBuffer("position", buf, 3)
        self.setAttrByBuffer("normal", normal, 3)
        self.setAttrByBuffer("uv", uv, 2)
        self.setIboByBuffer(face)
    }

    void buildSpotLightHelper(SpotLight* sl){
        self.clear()
        float l = sl.distance
        float w = l * tan(sl.angle)
        
        // Vec3 v0 = 
        // 圆锥朝下
        //中心线
        self.moveTo(0, 0, 0); self.lineTo_color( 0, -l,  0, 0xffff0000);
        self.moveTo(0, 0, 0); self.lineTo_color( w, -l,  0, 0xffff0000);
        self.moveTo(0, 0, 0); self.lineTo_color(-w, -l,  0, 0xffff0000);
        self.moveTo(0, 0, 0); self.lineTo_color( 0, -l,  w, 0xffff0000);
        self.moveTo(0, 0, 0); self.lineTo_color( 0, -l, -w, 0xffff0000);
    }

    void buildCameraHelper(Camera *camera){
        self.clear()
        // 通过反向投影计算各个点位
        float w = 1
        float h = 1

        // center to target
        Vec3 c = camera.unprojectToView(mkVec3(  0,  0, -1))
        Vec3 t = camera.unprojectToView(mkVec3(  0,  0, 1))

        // near
        Vec3 n1 = camera.unprojectToView(mkVec3(-w, -h, -1))
        Vec3 n2 = camera.unprojectToView(mkVec3( w, -h, -1))
        Vec3 n3 = camera.unprojectToView(mkVec3(-w,  h, -1))
        Vec3 n4 = camera.unprojectToView(mkVec3( w,  h, -1))

        // far
        Vec3 f1 = camera.unprojectToView(mkVec3(-w, -h,  1))
        Vec3 f2 = camera.unprojectToView(mkVec3( w, -h,  1))
        Vec3 f3 = camera.unprojectToView(mkVec3(-w,  h,  1))
        Vec3 f4 = camera.unprojectToView(mkVec3( w,  h,  1))

        // up
        Vec3 u1 = camera.unprojectToView(mkVec3( w * 0.7,  h * 1.1,  -1))
        Vec3 u2 = camera.unprojectToView(mkVec3(-w * 0.7,  h * 1.1,  -1))
        Vec3 u3 = camera.unprojectToView(mkVec3( 0,  h * 2,  -1))


        // cross 交叉线
        Vec3 cf1 = camera.unprojectToView(mkVec3( -w,  0,  1))
        Vec3 cf2 = camera.unprojectToView(mkVec3(  w,  0,  1))
        Vec3 cf3 = camera.unprojectToView(mkVec3(  0, -h,  1))
        Vec3 cf4 = camera.unprojectToView(mkVec3(  0,  h,  1))

        Vec3 cn1 = camera.unprojectToView(mkVec3( -w,  0, -1))
        Vec3 cn2 = camera.unprojectToView(mkVec3(  w,  0, -1))
        Vec3 cn3 = camera.unprojectToView(mkVec3(  0, -h, -1))
        Vec3 cn4 = camera.unprojectToView(mkVec3(  0,  h, -1))

        self.color = 0xffffffff
        // 相机点位，外四面
        // self.color = 0xffff0000
        self.moveTo(0, 0, 0); self.lineToVec3(n1);
        self.moveTo(0, 0, 0); self.lineToVec3(n2);
        self.moveTo(0, 0, 0); self.lineToVec3(n3);
        self.moveTo(0, 0, 0); self.lineToVec3(n4);

        self.moveToVec3(n1); self.lineToVec3(n2);
        self.moveToVec3(n2); self.lineToVec3(n4);
        self.moveToVec3(n3); self.lineToVec3(n4);
        self.moveToVec3(n1); self.lineToVec3(n3);


        // self.color = 0xffffffff
        self.moveToVec3(n1); self.lineToVec3(f1);
        self.moveToVec3(n2); self.lineToVec3(f2);
        self.moveToVec3(n3); self.lineToVec3(f3);
        self.moveToVec3(n4); self.lineToVec3(f4);


        self.moveToVec3(f1); self.lineToVec3(f2);
        self.moveToVec3(f2); self.lineToVec3(f4);
        self.moveToVec3(f3); self.lineToVec3(f4);
        self.moveToVec3(f1); self.lineToVec3(f3);

        //中心线
        // self.color = 0xffffffff
        self.moveTo(0, 0, 0); self.lineToVec3(t);

        //交叉线
        // self.color = 0xffff00ff
        self.moveToVec3(cf1); self.lineToVec3(cf2);
        self.moveToVec3(cf3); self.lineToVec3(cf4);

        self.moveToVec3(cn1); self.lineToVec3(cn2);
        self.moveToVec3(cn3); self.lineToVec3(cn4);
    }
}
