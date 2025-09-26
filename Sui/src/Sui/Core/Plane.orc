


package SuiCore

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Sgl/Mat.orc"
import type * from "../../Sgl/Sphere.orc"
import * from "./Mat3.orc"
import * from "./Vec3.orc"
import * from "./Spherical.orc"



/// 平面
struct Plane {
    Vec3 normal;//法线. 被 认为是归一化的
    
    float constant;
}
extension Plane {
    Plane* set( Vec3 normal, float constant ) {

		self.normal.copy( normal );
		self.constant = constant;

		return self;

	}

	Plane* setComponents( float x, float y, float z, float w ) {

		self.normal.set( x, y, z );
		self.constant = w;

		return self;

	}

	Plane * setFromNormalAndCoplanarPoint( Vec3 normal, Vec3 point ) {

		self.normal.copy( normal );
		self.constant = - point.dot( self.normal );

		return self;

	}

	Plane * setFromCoplanarPoints(Vec3 a, Vec3 b, Vec3 c ) {

        // Vec3 _vector1
        // Vec3 _vector2
		Vec3 normal = c.sub( b ).cross(  a.sub(b) ).normal();

		// Q: should an error be thrown if normal is zero (e.g. degenerate plane)?

		self.setFromNormalAndCoplanarPoint( normal, a );

		return self;

	}

	Plane* copy(Plane plane ) {

		self.normal.copy( plane.normal );
		self.constant = plane.constant;

		return self;

	}

	Plane* normalizeLocal() {

		// Note: will lead to a divide by zero if the plane is invalid.

		float inverseNormalLength = 1.0 / self.normal.length();
		self.normal.multiplyScalarLocal( inverseNormalLength );
		self.constant *= inverseNormalLength;

		return self;

	}

	Plane* negateLocal() {

		self.constant *= - 1.0;
		self.normal.negateLocal();

		return self;

	}

	float distanceToPoint(Vec3 point ) {

		return self.normal.dot( point ) + self.constant;

	}

	float distanceToSphere(Sphere sphere ) {

		return self.distanceToPoint( sphere.center ) - sphere.radius;

	}

	Vec3 projectPoint(Vec3 point) {
        Vec3 target = point;

		target.addScaledVectorLocal( self.normal, - self.distanceToPoint( point ) );
        return target;

	}

	// intersectLine( line, target ) {

	// 	const direction = line.delta( _vector1 );

	// 	const denominator = self.normal.dot( direction );

	// 	if ( denominator === 0 ) {

	// 		// line is coplanar, return origin
	// 		if ( self.distanceToPoint( line.start ) === 0 ) {

	// 			return target.copy( line.start );

	// 		}

	// 		// Unsure if self is the correct method to handle self case.
	// 		return null;

	// 	}

	// 	const t = - ( line.start.dot( self.normal ) + self.constant ) / denominator;

	// 	if ( t < 0 || t > 1 ) {

	// 		return null;

	// 	}

	// 	return target.copy( line.start ).addScaledVector( direction, t );

	// }

	// intersectsLine( line ) {

	// 	// Note: self tests if a line intersects the plane, not whether it (or its end-points) are coplanar with it.

	// 	const startSign = self.distanceToPoint( line.start );
	// 	const endSign = self.distanceToPoint( line.end );

	// 	return ( startSign < 0 && endSign > 0 ) || ( endSign < 0 && startSign > 0 );

	// }

	// intersectsBox( box ) {

	// 	return box.intersectsPlane( self );

	// }

	// intersectsSphere( sphere ) {

	// 	return sphere.intersectsPlane( self );

	// }

	Vec3 coplanarPoint( ) {
        Vec3 target = self.normal
		target.multiplyScalarLocal( - self.constant );
        return target
	}

	// applyMatrix4Local(Mat matrix, Mat* optionalNormalMatrix ) {

	// 	const normalMatrix = optionalNormalMatrix || _normalMatrix.getNormalMatrix( matrix );

	// 	const referencePoint = self.coplanarPoint( _vector1 ).applyMatrix4( matrix );

	// 	const normal = self.normal.applyMatrix3( normalMatrix ).normalize();

	// 	self.constant = - referencePoint.dot( normal );

	// 	return self;

	// }

	Plane* translate(Vec3 offset ) {

		self.constant -= offset.dot( self.normal );

		return self;

	}

	bool equals(Plane plane ) {

		return plane.normal.equals( self.normal ) && ( eqFloat(plane.constant , self.constant ));

	}

	Plane clone() {
        return *self;

		// return new self.constructor().copy( self );

	}

}