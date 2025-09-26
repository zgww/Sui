
package Sgl

#include <stdio.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Program.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Orc/String.orc"

import * from "./Geometry.orc"


class GeometryBox extends Geometry {

    Vec3 center

    float width = 100
    float height = 100
    float depth = 100

    int widthSegments = 1
    int heightSegments = 1
    int depthSegments = 1

    int color = 0xffff0000

    void mkPlane(
        int segcols,
        int segrows,
        float dx,
        float dy,

        Vec3 xfactor,//将列映射成vec3
        Vec3 yfactor,//将行映射成vec3

        Vec3 p0,
        Vec3 normalVec3,

        Buffer *position,
        Buffer *normal,
        Buffer *uv,
        Buffer *face,
        Buffer *color,
    ){
        int cols = segcols + 1
        int rows = segrows + 1
        float stepX = dx / segcols
        float stepY = dy / segrows

        int startVertIndex = position.floatSize() / 3
        Rgbaf cf = mkRgbafByInt(self.color)

        for int r = 0; r < rows; r++{
            for int c = 0; c < cols; c++{
                Vec3 x = xfactor.scale(c * stepX )
                Vec3 y = yfactor.scale(r * stepY )
                Vec3 pos = p0.add(x.add(y))

                position.appendFloat3(pos.x, pos.y, pos.z)
                normal.appendFloat3(normalVec3.x, normalVec3.y, normalVec3.z) //法线向上
                color.appendFloat4(
                    cf.r,
                    cf.g,
                    cf.b,
                    cf.a,
                )

                float u = c / (float)(segcols)
                float v = r / (float)segrows //uv坐标
                uv.appendFloat2(u, v)

                // 索引 
                int lb = startVertIndex + r * cols + c
                int rb = lb + 1
                int rt = lb + cols + 1
                int lt = lb + cols
                
                // printf("add pos %d,%d:%f,%f,%f %f,%f,%f; uv:%f,%f\n", c, r, pos.x, pos.y, pos.z, p0.x, p0.y, p0.z, u, v)
                if r < rows - 1 && c < cols  - 1{
                    // printf("\tface %d,%d,%d,%d cnt:%d \n", lb, rb, rt, lt, face.intSize())
                    face.appendInt3(lb, rb, rt) //右下
                    face.appendInt3(lb, rt, lt) //左上
                }
            }
        }
    }

    void build(){
        Buffer@ position = new Buffer()
        Buffer@ uv = new Buffer()
        Buffer@ normal = new Buffer()
        Buffer@ face = new Buffer()
        Buffer@ color = new Buffer()

        float startX = self.center.x - self.width / 2.0
        float startY = self.center.y - self.height / 2.0
        float startZ = self.center.z - self.depth / 2.0
        float endX = self.center.x + self.width / 2.0
        float endY = self.center.y + self.height / 2.0
        float endZ = self.center.z + self.depth / 2.0

        //前xy
        if 1 {
            self.mkPlane(
                self.widthSegments,
                self.heightSegments,

                endX - startX,
                endY - startY,

                mkVec3(1, 0, 0), //列向量
                mkVec3(0, 1, 0), //行向量

                mkVec3(startX, startY, endZ),

                mkVec3(0, 0, 1), //法线向上

                position, normal, uv, face, color
            )
        }
        if 1{

            //右zy
            self.mkPlane(
                self.depthSegments,
                self.heightSegments,

                -endZ + startZ,
                endY - startY,

                mkVec3(0, 0, 1), //列向量
                mkVec3(0, 1, 0), //行向量

                mkVec3(endX, startY, endZ),
                mkVec3(1, 0, 0), //法线向右

                position, normal, uv, face, color
            )
        }
        if 1{

            //后xy
            self.mkPlane(
                self.widthSegments,
                self.heightSegments,

                -endX + startX,
                endY - startY,

                mkVec3(1, 0, 0), //列向量
                mkVec3(0, 1, 0), //行向量

                mkVec3(endX, startY, startZ),
                mkVec3(0, 0, -1), //法线向后

                position, normal, uv, face, color
            )
        }
        if 1 {

            //左zy
            self.mkPlane(
                self.depthSegments,
                self.heightSegments,

                endZ - startZ,
                endY - startY,

                mkVec3(0, 0, 1), //列向量
                mkVec3(0, 1, 0), //行向量

                mkVec3(startX, startY, startZ),
                mkVec3(-1, 0, 0), //法线向左

                position, normal, uv, face, color
            )
        }
        if 1{

        //下xz
            self.mkPlane(
                self.widthSegments,
                self.depthSegments,

                endX - startX,
                endZ - startZ,

                mkVec3(1, 0, 0), //列向量
                mkVec3(0, 0, 1), //行向量

                mkVec3(startX, startY, startZ),
                mkVec3(0, -1, 0), //法线向下

                position, normal, uv, face, color
            )
        }
        if 1 {

        //上xz
            self.mkPlane(
                self.widthSegments,
                self.depthSegments,

                endX - startX,
                -endZ + startZ,

                mkVec3(1, 0, 0), //列向量
                mkVec3(0, 0, 1), //行向量

                mkVec3(startX, endY, endZ),
                mkVec3(0, 1, 0), //法线向上

                position, normal, uv, face, color
            )
        }

        self.setAttrByBuffer("position", position, 3)
        self.setAttrByBuffer("normal", normal, 3)
        self.setAttrByBuffer("color", color, 4)
        self.setAttrByBuffer("uv", uv, 2)
        self.setIboByBuffer(face)
    }
}
