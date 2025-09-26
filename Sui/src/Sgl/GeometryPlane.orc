
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

import * from "./Geometry.orc"


class GeometryPlane extends Geometry {

    float width = 1000
    float height = 1000
    int widthSegments = 10
    int heightSegments = 10

    int planeType = 0 //0: xy, 1: xz, 2: yz

    void build(){
        Buffer@ vtxs = new Buffer()
        Buffer@ nmls = new Buffer()
        Buffer@ face = new Buffer()
        Buffer@ uvs = new Buffer()

        float widthHalf = self.width / 2.0
        float heightHalf = self.height / 2.0

        int gridX = self.widthSegments
        int gridY = self.heightSegments
        int gridX1 = self.widthSegments + 1
        int gridY1 = self.heightSegments + 1
        float segWidth = self.width / gridX
        float segHeight = self.width / gridY

        for int j = 0; j < gridY1; j++{
            float y = j * segHeight - heightHalf;
            for int i = 0; i < gridX1; i++{
                float x = i * segWidth - widthHalf;
                // printf("add pos:%f,%f\n", x, y)

                if self.planeType == 0 {
                    vtxs.appendFloat3(x, y, 0)
                    nmls.appendFloat3(0, 0, 1)
                }
                else if self.planeType == 1 {
                    vtxs.appendFloat3(x, 0, y)
                    nmls.appendFloat3(0, 1, 0)
                }
                else {
                    vtxs.appendFloat3(0, x, y)
                    nmls.appendFloat3(1, 0, 0)
                }

                uvs.appendFloat2(
                    i / (float)gridX, 
                    1 - (j / (float)gridY)
                )
            }
        }
        for int j = 0; j < gridY1 - 1; j++{
            for int i = 0; i < gridX1 - 1; i++{
                int a = i + j * gridX1
                int b = i + 1 + j * gridX1
                int c = i + 1 + (j + 1) * gridX1
                int d = i + (j + 1) * gridX1
                face.appendInt3(a, b, c)
                face.appendInt3(a, c, d)
            }
        }

        self.setAttrByBuffer("position", vtxs, 3)
        self.setAttrByBuffer("normal", nmls, 3)
        self.setAttrByBuffer("uv", uvs, 2)
        self.setIboByBuffer(face)
    }
}
