
package Sgl

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Camera.orc"
import * from "./Mat.orc"
import * from "./Program.orc"
import * from "./SpotLight.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Orc/String.orc"

import * from "./Geometry.orc"


// 全屏quad.适合用来做post-process
class GeometryFullscreenQuad extends Geometry {
    //近平面: -1,远平面:1
    float z = 0 //-0.999999

    void build(){
        // _geometry.setAttribute( 'position', new Float32BufferAttribute( [ - 1, 3, 0, - 1, - 1, 0, 3, - 1, 0 ], 3 ) );
        // _geometry.setAttribute( 'uv', new Float32BufferAttribute( [ 0, 2, 0, 0, 2, 0 ], 2 ) );

        Buffer@ vtx = new Buffer()
        Buffer@ nml = new Buffer()
        Buffer@ uv = new Buffer()
        Buffer@ face = new Buffer()

        float d = 3;

        vtx.appendFloat3(-1, d, self.z); nml.appendFloat3(0, 0, 1); uv.appendFloat2(0, 2);
        vtx.appendFloat3(-1,-1, self.z); nml.appendFloat3(0, 0, 1); uv.appendFloat2(0, 0);
        vtx.appendFloat3( d,-1, self.z); nml.appendFloat3(0, 0, 1); uv.appendFloat2(2, 0);

        // vtx.appendFloat3(-1,-1, 0); nml.appendFloat3(0, 0, 1); uv.appendFloat2(0, 0);
        // vtx.appendFloat3( 1,-1, 0); nml.appendFloat3(0, 0, 1); uv.appendFloat2(0, 2);
        // vtx.appendFloat3( 1, 1, 0); nml.appendFloat3(0, 0, 1); uv.appendFloat2(2, 0);
        // vtx.appendFloat3(-1, 1, 0); nml.appendFloat3(0, 0, 1); uv.appendFloat2(2, 0);

        face.appendInt3(0, 1, 2)
        // face.appendInt3(0, 2, 3)

        self.setAttrByBuffer("position", vtx, 3)
        self.setAttrByBuffer("normal", nml, 3)
        self.setAttrByBuffer("uv", uv, 2)
        self.setIboByBuffer(face)
    }
}