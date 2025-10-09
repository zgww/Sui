
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
import * from "../Sui/Core/Vec3.orc"
import * from "../Orc/String.orc"
import * from "../Orc/Math.orc"

import * from "./Geometry.orc"


class GeometryCapsule extends Geometry {

    float radius = 100
    int segments = 20
    float thetaStart = 0.0
    float thetaLength = 3.141592653589793 * 2

    void build(){
        Buffer@ pos = new Buffer()
        Buffer@ nmls = new Buffer()
        Buffer@ face = new Buffer()
        Buffer@ uvs = new Buffer()

        int segments = maxInt(3, self.segments)
        float radius = self.radius


        //center point

        pos.appendFloat3(0, 0, 0)
        nmls.appendFloat3(0, 0, 1)
        uvs.appendFloat2(0.5, 0.5)
        {
            int s = 0
            for int i = 3; s <= self.segments; i+=3 {
                float segment = self.thetaStart + s / self.segments * self.thetaLength
                float x = radius * cos(segment)
                float y = radius * sin(segment)
                pos.appendFloat3(x, y, 0)
                nmls.appendFloat3(0, 0, 1)

                uvs.appendFloat2(
                    (x / radius + 1) / 2.0,
                    (y / radius + 1) / 2.0,
                )

                s++
            }
        }
        for int i = 1; i < segments; i++{
            face.appendInt3(i, i + 1, 0)
        }

        self.setAttrByBuffer("position", pos, 3)
        self.setAttrByBuffer("normal", nmls, 3)
        self.setAttrByBuffer("uv", uvs, 2)
        self.setIboByBuffer(face)
    }
}
