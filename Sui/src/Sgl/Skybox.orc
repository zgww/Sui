
package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "./Mat.orc"
import * from "./Material.orc"
import * from "./Geometry.orc"
import * from "./Obj3d.orc"
import * from "./Tex2d.orc"
import * from "./DrawCtx.orc"
import * from "./Buffer.orc"
import * from "./Vao.orc"


class Skybox extends Obj3d {
    //材质，，含program和opengl开关状态
    Material@ material = new Material();
    //顶点数据
    Geometry@ geometry;

    Tex2d@ front;
    Tex2d@ back;
    Tex2d@ left;
    Tex2d@ right;
    Tex2d@ upTex;
    Tex2d@ down;

    Vao@ vao = new Vao()


    void ctor(){
        self.material.load("../asset/skybox.matl.json")
        self.buildGeometry()

        self.front = mkTex2dByPathCstr("../asset/skybox/front.png")
        self.back = mkTex2dByPathCstr("../asset/skybox/back.png")
        self.left = mkTex2dByPathCstr("../asset/skybox/left.png")
        self.right = mkTex2dByPathCstr("../asset/skybox/right.png")
        self.upTex = mkTex2dByPathCstr("../asset/skybox/up.png")
        self.down = mkTex2dByPathCstr("../asset/skybox/down.png")
    }


    void buildGeometry(){
        Buffer@ vtxBuf = new Buffer()
        Buffer@ faceBuf = new Buffer()
        Buffer@ uvBuf = new Buffer()
        Buffer@ texIdxBuf = new Buffer()

        ^void mkPlane(
            float texIdx,
            Vec3 lb,
            Vec3 rb,
            Vec3 rt,
            Vec3 lt
        ){
            int idx = vtxBuf.floatSize()  / 3
            //前
            vtxBuf.appendVec3(lb)
            vtxBuf.appendVec3(rb)
            vtxBuf.appendVec3(rt)
            vtxBuf.appendVec3(lt)

            uvBuf.appendFloat3(texIdx, 0, 0)
            uvBuf.appendFloat3(texIdx, 1, 0)
            uvBuf.appendFloat3(texIdx, 1, 1)
            uvBuf.appendFloat3(texIdx, 0, 1)

            int a = idx
            int b = idx+1
            int c = idx+2
            int d = idx+3
            faceBuf.appendInt3(a, b, c)
            faceBuf.appendInt3(a, c, d)
        }

        float h = 500;
        Vec3 f0 = mkVec3(-h, -h,  h)
        Vec3 f1 = mkVec3( h, -h,  h)
        Vec3 f2 = mkVec3( h,  h,  h)
        Vec3 f3 = mkVec3(-h,  h,  h)

        Vec3 b0 = mkVec3(-h, -h, -h)
        Vec3 b1 = mkVec3( h, -h, -h)
        Vec3 b2 = mkVec3( h,  h, -h)
        Vec3 b3 = mkVec3(-h,  h, -h)

        if 0 {
            //前
            mkPlane(0, f0, f1, f2, f3)
            //后
            mkPlane(1, b1, b0, b3, b2)
            //左
            mkPlane(2, b0, f0, f3, b3)
            //右
            mkPlane(3, f1, b1, b2, f2)
            //上
            mkPlane(4, f3, f2, b2, b3)
            //下
            mkPlane(5, b0, b1, f1, f0)
        }
        if 1 {
            //前
            mkPlane(0, f0, f1, f2, f3)
            //后
            mkPlane(1, b0, b1, b2, b3)
            //左
            mkPlane(2, b0, f0, f3, b3)
            //右
            mkPlane(3, f1, b1, b2, f2)
            //上
            mkPlane(4, f3, f2, b2, b3)
            //下
            mkPlane(5, b0, b1, f1, f0)
        }


        self.geometry = new Geometry()
        self.geometry.{
            o.setAttrByBuffer("position", vtxBuf, 3)
            o.setAttrByBuffer("idxUv", uvBuf, 3) //texIdx,x,y
            o.setIboByBuffer(faceBuf)
        }
    }

    void draw(DrawCtx* ctx){
        if self.material == null ||
            self.geometry == null {
            return;
        }

        self.material.setUniformTex2d("tex[0]", self.front)
        self.material.setUniformTex2d("tex[1]", self.back)
        self.material.setUniformTex2d("tex[2]", self.left)
        self.material.setUniformTex2d("tex[3]", self.right)
        self.material.setUniformTex2d("tex[4]", self.upTex)
        self.material.setUniformTex2d("tex[5]", self.down)

        ctx.setMvpToMaterial(self, self.material)

        //去掉平移,模型等于固定在相机空间零点
        self.material.view.data[12] = 0
        self.material.view.data[13] = 0
        self.material.view.data[14] = 0
        self.material.updateMvp()

        self.vao.draw(self.geometry, self.material)
    }
}