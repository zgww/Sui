
package Sgl

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Program.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Orc/String.orc"

import * from "./Geometry.orc"

//跟陶艺类似,旋转成体
class GeometryLathe extends Geometry {

    int segments = 12
    float phiStart = 0
    float phiLength = PI * 2
    Vec3Array@ points = new Vec3Array()

    void build(){
        Buffer@ pos = new Buffer()
        Buffer@ nmls = new Buffer()
        Buffer@ uvs = new Buffer()
        Buffer@ face = new Buffer()


        float inverseSegments = 1.0 / (float)self.segments
        Vec3 vertex;
        Vec2 uv;
        Vec3 normal;
        Vec3 curNormal;
        Vec3 prevNormal;
        Vec3Array *points = self.points
        FloatArray@ initNormals = new FloatArray()
        float dx = 0
        float dy = 0

        for int j = 0; j <= (self.points.size - 1); j++{
            if j == 0{
                dx = points.get(j + 1).x - points.get(j).x
                dy = points.get(j + 1).y - points.get(j).y
                normal.x = dy * 1.0;
                normal.y = -dx
                normal.z = dy * 0.0

                prevNormal.copy(normal)
                normal = normal.normal()
                initNormals.appendFloat3(normal.x, normal.y, normal.z)
            }
            else if j == self.points.size - 1{
                initNormals.appendFloat3(prevNormal.x, prevNormal.y, prevNormal.z)
            }
            else {
                dx = points.get(j + 1).x - points.get(j).x
                dy = points.get(j + 1).y - points.get(j).y
                normal.x = dy * 1.0;
                normal.y = -dx
                normal.z = dy * 0.0
                curNormal.copy(normal)

                normal.x += prevNormal.x
                normal.y += prevNormal.y
                normal.z += prevNormal.z

                normal = normal.normal()
                 
                initNormals.appendFloat3(normal.x, normal.y, normal.z)
                prevNormal.copy(curNormal)
            }
        }
        for int i = 0; i < segments; i++{
            float phi = self.phiStart + i * inverseSegments * self.phiLength
            float cosPhi = cos(phi)
            float sinPhi = sin(phi)

            for int j = 0; j < points.size; j++{
                vertex.x = points.get(j).x * sinPhi
                vertex.y = points.get(j).y
                vertex.z = points.get(j).x * cosPhi

                pos.appendFloat3(vertex.x, vertex.y, vertex.z)

                {
                    float x = initNormals.get(3 * j + 0) * sinPhi
                    float y = initNormals.get(3 * j + 1) 
                    float z = initNormals.get(3 * j + 0) * cosPhi
                    nmls.appendFloat3(x, y, z)
                }


                uv.x = (float)i / (float)self.segments
                uv.y = (float)j / (float)(points.size - 1)
                uvs.appendFloat2(uv.x, uv.y)
            }
        }

        for int i = 0; i < self.segments; i++{
            for int j = 0; j < points.size - 1; j++{
                int base = j + i * points.size

                int a = base
                int b = base + points.size
                int c = base + points.size + 1
                int d = base + 1

                face.appendInt3(a, b, d)
                face.appendInt3(c, d, b)
            }
        }

        self.setAttrByBuffer("position", pos, 3)
        self.setAttrByBuffer("normal", nmls, 3)
        self.setAttrByBuffer("uv", uvs, 3)
        self.setIboByBuffer(face)
    }
}
