package Sgl

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

import * from "../Orc/String.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sgl/Buffer.orc"
import type * from "../Sgl/Box3.orc"
import type * from "../Sgl/Mat.orc"



/// 布局上下文
struct Sphere {
    Vec3 center
    float radius
}
extension Sphere {

	Sphere* set(Vec3 center, float radius ) {
		self.center.copy( center );
		self.radius = radius;
		return self
	}

	Sphere* setFromPoints( Vec3Array* points, Vec3 *optionalCenter ) {

		Vec3* center = &self.center;

		if ( optionalCenter != null ) {

			center.copy( *optionalCenter );

		} else {
            Box3 _box
            _box.setFromPoints( points )
			self.center = _box.getCenter( );
		}

		float maxRadiusSq = 0;

        int il = points.size
		for ( int i = 0 ; i < il; i ++ ) {
			maxRadiusSq = maxFloat( maxRadiusSq, center.distanceToSquared( points.data[ i ] ) );
		}

		self.radius = sqrt( maxRadiusSq );
		return self;
	}

	Sphere* copy(Sphere sphere ) {
        *self = sphere
		return self;
	}

	bool isEmpty() {
		return ( self.radius < 0 );
	}

	void makeEmpty() {
		self.center.set( 0, 0, 0 );
		self.radius = - 1;
	}

	bool containsPoint(Vec3 point ) {
		return ( point.distanceToSquared( self.center ) <= ( self.radius * self.radius ) );
	}

	float distanceToPoint(Vec3 point ) {
		return ( point.distanceTo( self.center ) - self.radius );
	}

	float intersectsSphere(Sphere sphere ) {
		float radiusSum = self.radius + sphere.radius;
		return sphere.center.distanceToSquared( self.center ) <= ( radiusSum * radiusSum );

	}

	bool intersectsBox(Box3 box ) {
		return box.intersectsSphere( *self );
	}

	// intersectsPlane( plane ) {

	// 	return Math.abs( plane.distanceToPoint( self.center ) ) <= self.radius;

	// }

	Vec3 clampPoint( Vec3 point) {
        Vec3 target

		float deltaLengthSq = self.center.distanceToSquared( point );

		target.copy( point );

		if ( deltaLengthSq > ( self.radius * self.radius ) ) {
			target = target.sub( self.center )
            target = target.normal();
			target = target.scale( self.radius )
            target = target.add( self.center );
		}

		return target;

	}

	Box3 getBoundingBox( ) {
        Box3 target

		if ( self.isEmpty() ) {
			// Empty sphere produces empty bounding box
			target.makeEmpty();
			return target;
		}

		target.set( self.center, self.center );
		target.expandByScalar( self.radius );

		return target;
	}

	void applyMatrix4Local( Mat matrix ) {
		self.center.applyMatrix4Local( matrix );
		self.radius = self.radius * matrix.getMaxScaleOnAxis();
	}

	void translate(Vec3 offset ) {
		self.center = self.center.add( offset );
	}

	void expandByPoint(Vec3 point ) {

		if ( self.isEmpty() ) {
			self.center.copy( point );
			self.radius = 0;
			return ;

		}
        Vec3 _v1 = point.sub(self.center)

		float lengthSq = _v1.lengthSq();

		if ( lengthSq > ( self.radius * self.radius ) ) {

			// calculate the minimal sphere

			float length = sqrt( lengthSq );
			float delta = ( length - self.radius ) * 0.5;

			self.center.addScaledVectorLocal( _v1, delta / length );
			self.radius += delta;
		}

	}

	Sphere* union(Sphere sphere ) {

		if ( sphere.isEmpty() ) {
            return self
		}

		if ( self.isEmpty() ) {
			self.copy( sphere );
			return self;
		}

		if ( self.center.equals( sphere.center ) == true ) {

			 self.radius = maxFloat( self.radius, sphere.radius );

		} else {
            Vec3 _v2 = sphere.center.sub(self.center)
            _v2.setLength(sphere.radius)

			self.expandByPoint( sphere.center .add( _v2 ) );
			self.expandByPoint( sphere.center .sub( _v2 ) );
		}

		return self;
	}

	bool equals(Sphere sphere ) {
		return sphere.center.equals( self.center ) && ( sphere.radius == self.radius );
	}

	Sphere clone() {
        return *self
	}
}