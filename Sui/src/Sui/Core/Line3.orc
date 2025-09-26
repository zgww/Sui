
package SuiCore

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Sgl/Mat.orc"
import * from "./Mat3.orc"
import * from "./Vec3.orc"
import * from "./Plane.orc"
import * from "./Spherical.orc"



struct Line3 {
    Vec3 start
    Vec3 end
}
extension Line3 {

	Line3* set( Vec3 start, Vec3 end ) {

		self.start.copy( start );
		self.end.copy( end );

		return self;

	}

	Line3* copy(Line3 line ) {

		self.start.copy( line.start );
		self.end.copy( line.end );

		return self;

	}

	Vec3 getCenter( ) {
        Vec3 target

		target.addVectorsLocal( self.start, self.end ).multiplyScalarLocal( 0.5 );
        return target

	}

	Vec3 delta( ) {

        Vec3 target
		target.subVectorsLocal( self.end, self.start );
        return target
	}

	float distanceSq() {

		return self.start.distanceToSquared( self.end );

	}

	float distance() {

		return self.start.distanceTo( self.end );

	}

	Vec3 at( float t) {

		Vec3 target = self.delta( ).multiplyScalarLocal( t ).add( self.start );
        return target
	}

	float closestPointToPointParameter( Vec3 point, bool clampToLine ) {
        Vec3 _startP
        Vec3 _startEnd

		_startP.subVectorsLocal( point, self.start );
		_startEnd.subVectorsLocal( self.end, self.start );

		float startEnd2 = _startEnd.dot( _startEnd );
		float startEnd_startP = _startEnd.dot( _startP );

		float t = startEnd_startP / startEnd2;

		if ( clampToLine ) {
			t = clampFloat( t, 0, 1 );
		}

		return t;

	}

	Vec3 closestPointToPoint( Vec3 point, bool clampToLine) {

		float t = self.closestPointToPointParameter( point, clampToLine );

		Vec3 result =  self.delta( ).multiplyScalarLocal( t ).add( self.start );
        return result
	}

	Line3* applyMatrix4Local(Mat matrix ) {

		self.start.applyMatrix4Local( matrix );
		self.end.applyMatrix4Local( matrix );

		return self;

	}

	bool equals(Line3 line ) {

		return line.start.equals( self.start ) && line.end.equals( self.end );

	}

	Line3 clone() {
        return *self

		// return new self.constructor().copy( self );
	}

}