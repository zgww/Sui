
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


//由圆柱体+椎体构成. y轴朝向
class GeometryArrow extends Geometry {

    float cylinderRadius = 10
    float coneRadius = 30

    //柱体高
    float cylinderHeight = 50
    float coneHeight = 50


    int radialSegments = 32

    float thetaStart = 0
    float thetaLength = PI * 2

    Buffer@ vtxBuf = new Buffer()
    Buffer@ nmlBuf = new Buffer()
    Buffer@ face = new Buffer()
    // Buffer@ uvs = new Buffer()


    void build(){
        // int index = 0
        self.buildTorso()
        self.buildCone()

        self.nmlBuf = Geometry_computeVertexNormals(self.face, self.vtxBuf)

        self.setAttrByBuffer("position", self.vtxBuf, 3)
        self.setAttrByBuffer("normal", self.nmlBuf, 3)
        // self.setAttrByBuffer("uv", self.uvs, 2)
        self.setIboByBuffer(self.face)
    }
    void buildTorso(){
        float radius = self.cylinderRadius
        //底面
        //中心点
        self.vtxBuf.appendFloat3(0, 0, 0)
        //柱底面
        for int x = 0; x <= self.radialSegments; x++{
            float u = x / (float)self.radialSegments;
            float theta = -u * self.thetaLength + self.thetaStart;
            float sinTheta = sin(theta)
            float cosTheta = cos(theta)

            self.vtxBuf.appendFloat3(
                radius * cosTheta,
                0, 
                radius * sinTheta,
            )
            if x == self.radialSegments{//终点与圆心与起始点是相连
                // self.face.appendInt3(0, 1, x + 1, 1)
                self.face.appendInt3(0, 1, x + 1)
            }
            else {
                // self.face.appendInt3(0, x + 1, (x + 2))
                self.face.appendInt3(0, x + 2, (x + 1))
            }
        }

        int start = self.vtxBuf.floatSize() / 3

        for int x = 0; x <= self.radialSegments; x++{
            float u = x / (float)self.radialSegments;
            float theta = -u * self.thetaLength + self.thetaStart;
            float sinTheta = sin(theta)
            float cosTheta = cos(theta)

            self.vtxBuf.appendFloat3(
                radius * cosTheta,
                self.cylinderHeight, 
                radius * sinTheta,
            )

            int bottomIdx = x + 1 
            int a = bottomIdx
            int b = bottomIdx + 1
            int d = start + x
            int c = d + 1

            if x == self.radialSegments {
                b = 1
                c = start
            }

            self.face.appendInt3(a, b, c)
            self.face.appendInt3(a, c, d)
        }
    }
    void buildCone(){
        float radius = self.coneRadius
        int start = self.vtxBuf.floatSize() / 3
        self.vtxBuf.appendFloat3(0, self.cylinderHeight, 0)

        //锥底面
        for int x = 0; x <= self.radialSegments; x++{
            float u = x / (float)self.radialSegments;
            float theta = -u * self.thetaLength + self.thetaStart;
            float sinTheta = sin(theta)
            float cosTheta = cos(theta)

            self.vtxBuf.appendFloat3(
                radius * cosTheta,
                self.cylinderHeight, 
                radius * sinTheta,
            )
            if x == self.radialSegments{//终点与圆心与起始点是相连
                self.face.appendInt3(start, start + x + 1, start + 1)
            }
            else {
                self.face.appendInt3(start, start + x + 1, start + (x + 2))
            }
        }

        int topStart = self.vtxBuf.floatSize() / 3
        self.vtxBuf.appendFloat3(0, self.cylinderHeight + self.coneHeight, 0)
        //锥侧面
        for int x = 0; x <= self.radialSegments; x++{
            float u = x / (float)self.radialSegments;
            float theta = -u * self.thetaLength + self.thetaStart;
            float sinTheta = sin(theta)
            float cosTheta = cos(theta)

            self.vtxBuf.appendFloat3(
                radius * cosTheta,
                self.cylinderHeight, 
                radius * sinTheta,
            )
            if x == self.radialSegments{//终点与圆心与起始点是相连
                self.face.appendInt3(topStart, topStart + x + 1, topStart + 1)
            }
            else {
                self.face.appendInt3(topStart, topStart + x + 1, topStart + (x + 2))
            }
        }
    }
}
