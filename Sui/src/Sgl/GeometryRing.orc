
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


class GeometryRing extends Geometry {

    float innerRadius = 50
    float outerRadius = 100
    int thetaSegments = 120
    int phiSegments = 1
    float thetaStart = 0.0
    float thetaLength = 3.141592653589793 * 2

    void build(){
        Buffer@ pos = new Buffer()
        Buffer@ nml = new Buffer()
        Buffer@ face = new Buffer()
        Buffer@ uvs = new Buffer()


        float radius = self.innerRadius
        float radiusStep = (self.outerRadius - self.innerRadius) / self.phiSegments
        Vec3 vertex;
        Vec2 uv;

        for int j = 0; j <= self.phiSegments; j++{
            for int i = 0; i <= self.thetaSegments; i++{
                float segment = self.thetaStart + i / (float)self.thetaSegments * self.thetaLength;
                vertex.x = radius * cos(segment);
                vertex.y = radius * sin(segment);
 
                pos.appendFloat3(vertex.x, vertex.y, vertex.z);
                nml.appendFloat3(0, 0, 1)
                uv.x = (vertex.x / self.outerRadius + 1) / 2.0
                uv.y = (vertex.y / self.outerRadius + 1) / 2.0
                uvs.appendFloat2(uv.x, uv.y);
            }
            radius += radiusStep
        }
        for int j = 0; j < self.phiSegments; j++{
            int thetaSegmentLevel = j * (self.thetaSegments + 1)
            for int i = 0; i < self.thetaSegments; i++{
                int segment = i + thetaSegmentLevel
                int a = segment
                int b = segment + self.thetaSegments + 1
                int c = segment + self.thetaSegments + 2
                int d = segment + 1

                face.appendInt3(a, b, d)
                face.appendInt3(b, c, d)
            }
        }

        self.setAttrByBuffer("position", pos, 3)
        self.setAttrByBuffer("normal", nml, 3)
        self.setAttrByBuffer("uv", uvs, 2)
        self.setIboByBuffer(face)
    }
}
