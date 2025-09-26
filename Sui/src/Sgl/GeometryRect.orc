
package Sgl

#include <stdio.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Program.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Orc/String.orc"

import * from "./Geometry.orc"


class GeometryRect extends Geometry {

    // float startX = 0
    // float startY = 0
    // float startZ = 0

    float width = 100
    float height = 100

    void build(){
        Buffer@ buf = new Buffer()
        Buffer@ normal = new Buffer()
        Buffer@ uv = new Buffer()
        Buffer@ face = new Buffer()


        float startX = -self.width / 2.0
        float startY = -self.width / 2.0
        float startZ = 0

        buf.appendFloat3(startX, startY, startZ);
        normal.appendFloat3(0, 1, 0)
        uv.appendFloat2(0, 0)

        buf.appendFloat3(startX + self.width, startY, startZ);
        normal.appendFloat3(0, 1, 0)
        uv.appendFloat2(1, 0)

        buf.appendFloat3(startX + self.width, startY + self.height, startZ);
        normal.appendFloat3(0, 1, 0)
        uv.appendFloat2(1, 1)

        buf.appendFloat3(startX, startY + self.height, startZ);
        normal.appendFloat3(0, 1, 0)
        uv.appendFloat2(0, 1)

        face.appendInt3(0, 1, 2)
        face.appendInt3(0, 2, 3)

        self.setAttrByBuffer("position", buf, 3)
        self.setAttrByBuffer("normal", normal, 3)
        self.setAttrByBuffer("uv", uv, 2)
        self.setIboByBuffer(face)
    }
}
