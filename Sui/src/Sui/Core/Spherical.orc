
package SuiCore

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Sgl/Mat.orc"
import * from "./Mat3.orc"
import * from "./Vec3.orc"



/// 布局上下文
struct Spherical {
	float radius
	float phi  //  polar angle
	float theta  // azimuthal angle
}
extension Spherical {
	Spherical* set( float radius, float phi, float theta ) {

		self.radius = radius;
		self.phi = phi;
		self.theta = theta;

		return self;
	}

	Spherical* copy(Spherical other ) {

		self.radius = other.radius;
		self.phi = other.phi;
		self.theta = other.theta;

		return self;

	}

	// restrict phi to be between EPS and PI-EPS
	Spherical* makeSafe() {

		float EPS = 0.000001;
		self.phi = maxFloat( EPS, minFloat( PI - EPS, self.phi ) );

		return self;

	}

	Spherical* setFromVector3(Vec3 v ) {

		return self.setFromCartesianCoords( v.x, v.y, v.z );

	}

	Spherical* setFromCartesianCoords(float x, float y, float z ) {

		self.radius = sqrt( x * x + y * y + z * z );

		if eqFloat( self.radius, 0 ) {

			self.theta = 0;
			self.phi = 0;

		} else {

			self.theta = atan2( x, z );
			self.phi = acos( clampFloat( y / self.radius, - 1, 1 ) );

		}

		return self;

	}

	Spherical clone() {
		return *self;
		// return new self.constructor().copy( self );
	}
}