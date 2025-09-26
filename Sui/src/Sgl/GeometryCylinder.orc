
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


class GeometryCylinder extends Geometry {

    float radiusTop = 10
    float radiusBottom = 10
    float height = 20
    int radialSegments = 32
    int heightSegments = 1

    bool openEnded = false
    float thetaStart = 0
    float thetaLength = PI * 2

    Buffer@ positions = new Buffer()
    Buffer@ normals = new Buffer()
    Buffer@ face = new Buffer()
    Buffer@ uvs = new Buffer()


    void build(){

        float halfHeight = self.height / 2.0
        int groupStart = 0

        int index = 0
        self.generateTorso(&index)

        if self.openEnded == false {
            if self.radiusTop > 0 {
                self.generateCap(true, &index)
            }
            if self.radiusBottom > 0 {
                self.generateCap(false, &index)
            }
        }

        self.setAttrByBuffer("position", self.positions, 3)
        self.setAttrByBuffer("normal", self.normals, 3)
        self.setAttrByBuffer("uv", self.uvs, 2)
        self.setIboByBuffer(self.face)
    }

    void generateTorso(int *index){
        float halfHeight = self.height / 2.0
        Vec3 normal;
        Vec3 vertex;
        float slope = (self.radiusBottom - self.radiusTop) / self.height
        List@ indexArray = new List()

        for int y = 0; y <= self.heightSegments;  y++{
            IntArray@ indexRow = new IntArray()

            float v = y / (float)self.heightSegments;

            float radius = v * (self.radiusBottom - self.radiusTop) + self.radiusTop;

            for int x = 0; x <= self.radialSegments; x++{
                float u = x / (float)self.radialSegments;

                float theta = u * self.thetaLength + self.thetaStart;
                float sinTheta = sin(theta)
                float cosTheta = cos(theta)

                self.positions.appendFloat3(
                    radius * sinTheta,
                    -v * self.height + halfHeight,
                    radius * cosTheta,
                )

                normal = normal.set(sinTheta, slope, cosTheta).normal()
                self.normals.appendFloat3(normal.x, normal.y, normal.z)
                self.uvs.appendFloat2(u, 1 - v)

                indexRow.append(*index)
                ;(*index)++;
            }
            indexArray.add(indexRow)
        }

        for int x = 0; x < self.radialSegments; x++{
            for int y = 0; y < self.heightSegments;  y++{
                IntArray *row0 = (IntArray*)indexArray.get(y)
                IntArray *row1 = (IntArray*)indexArray.get(y+1)

                int a = row0.at(x)
                int b = row1.at(x)
                int c = row1.at(x + 1)
                int d = row0.at(x + 1)

                self.face.appendInt3(a, b, d)
                self.face.appendInt3(b, c, d)
            }
        }


    }
    void generateCap(bool top, int *index){
        float halfHeight = self.height / 2.0
        int centerIndexStart = *index
        Vec2 uv;
        Vec3 vertex;
        int groupCount = 0
        float radius = top == true ? self.radiusTop : self.radiusBottom
        float sign = top == true ? 1 : -1

        //中间
        for int x = 0; x <= self.radialSegments; x++{
            self.positions.appendFloat3(0, halfHeight * sign, 0)
            self.normals.appendFloat3(0, sign, 0);
            self.uvs.appendFloat2(0.5, 0.5)

            ;(*index)++
        }
        int centerIndexEnd = *index;

        for int x = 0; x <= self.radialSegments; x++{
            float u = x / (float)self.radialSegments;
            float theta = u * self.thetaLength + self.thetaStart

            float cosTheta = cos(theta)
            float sinTheta = sin(theta)


            // vertex
            self.positions.appendFloat3(
                radius * sinTheta,
                halfHeight * sign,
                radius * cosTheta,
            )

            self.normals.appendFloat3(0, sign, 0)

            self.uvs.appendFloat2(
                cosTheta * 0.5 + 0.5,
                sinTheta * 0.5 * sign + 0.5,
            );

            ;(*index)++;
        }
        //face
        for int x = 0; x < self.radialSegments; x++{
            int c = centerIndexStart + x;
            int i = centerIndexEnd + x;

            if top == true {
                self.face.appendInt3(i, i + 1 , c)
            }
            else {
                self.face.appendInt3(i + 1, i, c)
            }



        }
    }
}
