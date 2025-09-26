
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


class GeometryTorus extends Geometry {

    float radius = 100
    float tube = 5.4//管道半径?
    float radialSegments = 12
    float tubularSegments = 48
    float arc = PI * 2


    void build(){
        Buffer@ pos = new Buffer()
        Buffer@ nmls = new Buffer()
        Buffer@ face = new Buffer()
        Buffer@ uvs = new Buffer()


		// helper variables

		Vec3 center ;
		Vec3 vertex ;
		Vec3 normal ;

		// generate vertices, normals and uvs

		for ( int j = 0; j <= self.radialSegments; j ++ ) {

			for ( int i = 0; i <= self.tubularSegments; i ++ ) {

				float u = i / self.tubularSegments * self.arc;
				float v = j / self.radialSegments * PI * 2.0;

				// vertex

				vertex.x = ( self.radius + self.tube * cos( v ) ) * cos( u );
				vertex.y = ( self.radius + self.tube * cos( v ) ) * sin( u );
				vertex.z = self.tube * sin( v );

				pos.appendFloat3( vertex.x, vertex.y, vertex.z );

				// normal

				center.x = self.radius * cos( u );
				center.y = self.radius * sin( u );
				normal.subVectorsLocal( vertex, center ).normalizeLocal();

				nmls.appendFloat3( normal.x, normal.y, normal.z );

				// uv

				uvs.appendFloat2( 
                    i / self.tubularSegments ,
                    j / self.radialSegments 
                );
			}

		}

		// generate indices

		for ( int j = 1; j <= self.radialSegments; j ++ ) {

			for ( int i = 1; i <= self.tubularSegments; i ++ ) {

				// indices

				int a = ( self.tubularSegments + 1 ) * j + i - 1;
				int b = ( self.tubularSegments + 1 ) * ( j - 1 ) + i - 1;
				int c = ( self.tubularSegments + 1 ) * ( j - 1 ) + i;
				int d = ( self.tubularSegments + 1 ) * j + i;

				// faces

				face.appendInt3( a, b, d );
				face.appendInt3( b, c, d );
			}

		}


        self.setAttrByBuffer("position", pos, 3)
        self.setAttrByBuffer("normal", nmls, 3)
        self.setAttrByBuffer("uv", uvs, 2)
        self.setIboByBuffer(face)
    }
}
