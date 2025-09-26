
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
import * from "../Orc/String.orc"

import * from "./Geometry.orc"


class GeometrySphere extends Geometry {

    float radius = 100
    int widthSegments = 32
    int heightSegments = 32

    float phiStart = 0.0
    float phiLength = PI * 2


    float thetaStart = 0.0
    float thetaLength = PI

    void build(){
        Buffer@ pos = new Buffer()
        Buffer@ nmls = new Buffer()
        Buffer@ face = new Buffer()
        Buffer@ uvs = new Buffer()


        float thetaEnd = minFloat(
            self.thetaStart + self.thetaLength,
            PI,
        )

        int index = 0
        Vec3 vertex;
        Vec3 normal;

        int heightSegments = self.heightSegments
        int widthSegments = self.widthSegments

        List@ grid = new List()

        for int iy = 0; iy <= heightSegments; iy++{
            IntArray@ verticesRow = new IntArray()
            float v = iy / (float)heightSegments

            float uOffset = 0
            if iy == 0 && self.thetaStart == 0{
                uOffset = 0.5 / widthSegments
            } else if iy == heightSegments && thetaEnd == PI{
                uOffset = -0.5 / widthSegments
            }
            for int ix = 0; ix <= widthSegments; ix++{
                float u = ix / (float)widthSegments
                float theta = self.thetaStart + v * self.thetaLength
                float phi = self.phiStart + u * self.phiLength

                vertex.x = -self.radius * cos(phi) * sin(theta)
                vertex.y = self.radius * cos(theta)
                vertex.z = self.radius * sin(phi) * sin(theta)

                normal.x = vertex.x / self.radius
                normal.y = vertex.y / self.radius
                normal.z = vertex.z / self.radius

                pos.appendFloat3(vertex.x, vertex.y, vertex.z)
                nmls.appendFloat3(normal.x, normal.y, normal.z)

                uvs.appendFloat2(u + uOffset, 1 - v)

                verticesRow.append(index)
                index++
            }
            grid.add(verticesRow)
        }

        for int iy = 0; iy < heightSegments; iy++{
            for int ix = 0; ix < widthSegments; ix++{
                IntArray *iyRow = grid.get(iy)
                IntArray *iyRow1 = grid.get(iy+1)
                int a = iyRow.at(ix + 1)
                int b = iyRow.at(ix + 0)
                int c = iyRow1.at(ix + 0)
                int d = iyRow1.at(ix + 1)
                if iy != 0 || self.thetaStart > 0 {
                    face.appendInt3(a, b, d)
                }
                if iy != heightSegments - 1 || thetaEnd < PI {
                    face.appendInt3(b, c, d)
                }
            }
        }

        self.setAttrByBuffer("position", pos, 3)
        self.setAttrByBuffer("normal", nmls, 3)
        self.setAttrByBuffer("uv", uvs, 2)
        self.setIboByBuffer(face)
    }
}
