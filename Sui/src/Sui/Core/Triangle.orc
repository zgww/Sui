
package SuiCore

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Sgl/Mat.orc"
import type * from "../../Sgl/Sphere.orc"
import type * from "./Mat3.orc"
import type * from "./Plane.orc"
import * from "./Vec3.orc"
import type * from "./Spherical.orc"



/// 三角形
struct Triangle {
    Vec3 a;
    Vec3 b;
    Vec3 c;
}
extension Triangle {

	Triangle* set( Vec3 a,Vec3  b, Vec3  c ) {

		self.a.copy( a );
		self.b.copy( b );
		self.c.copy( c );

		return self;

	}

	Triangle* setFromPointsAndIndices(Vec3* points, int i0, int i1, int i2 ) {

		self.a.copy( points[ i0 ] );
		self.b.copy( points[ i1 ] );
		self.c.copy( points[ i2 ] );

		return self;

	}

	// // setFromAttributeAndIndices( attribute, i0, i1, i2 ) {

	// // 	self.a.fromBufferAttribute( attribute, i0 );
	// // 	self.b.fromBufferAttribute( attribute, i1 );
	// // 	self.c.fromBufferAttribute( attribute, i2 );

	// // 	return self;

	// // }

	Triangle clone() {
        return *self;
	}

	Triangle* copy(Triangle triangle ) {

		self.a.copy( triangle.a );
		self.b.copy( triangle.b );
		self.c.copy( triangle.c );

		return self;

	}

	float getArea() {
        Vec3 _v0;
        Vec3 _v1;

		_v0.subVectorsLocal( self.c, self.b );
		_v1.subVectorsLocal( self.a, self.b );

		return _v0.cross( _v1 ).length() * 0.5;

	}

	Vec3 getMidpoint( ) {
        Vec3 target
		target.addVectorsLocal( self.a, self.b ).addLocal( self.c ).multiplyScalarLocal( 1 / 3.0 );
        return target
	}

	Vec3 getNormal( ) {
        Vec3 target

		target = Triangle_getNormal( self.a, self.b, self.c);
        return target

	}

	Plane getPlane( ) {
        Plane target;

		target.setFromCoplanarPoints( self.a, self.b, self.c );
        return target
	}

	Vec3 getBarycoord(Vec3 point) {

		return Triangle_getBarycoord( point, self.a, self.b, self.c);

	}

	// getUV( point, uv1, uv2, uv3, target ) { // @deprecated, r151

	// 	if ( warnedGetUV === false ) {

	// 		console.warn( 'THREE.Triangle.getUV() has been renamed to THREE.Triangle.getInterpolation().' );

	// 		warnedGetUV = true;

	// 	}

	// 	return Triangle_getInterpolation( point, self.a, self.b, self.c, uv1, uv2, uv3 );

	// }

	Vec3 getInterpolation(Vec3 point, Vec3 v1, Vec3 v2, Vec3 v3) {

		return Triangle_getInterpolation( point, self.a, self.b, self.c, v1, v2, v3 );

	}

	bool containsPoint(Vec3 point ) {

		return Triangle_containsPoint( point, self.a, self.b, self.c );

	}

	bool isFrontFacing( Vec3 direction ) {

		return Triangle_isFrontFacing( self.a, self.b, self.c, direction );

	}

	// intersectsBox( box ) {

	// 	return box.intersectsTriangle( self );

	// }

	Vec3 closestPointToPoint( Vec3 p) {
        Vec3 target
        Vec3 _vab
        Vec3 _vac
        Vec3 _vap
        Vec3 _vbp
        Vec3 _vcp
        Vec3 _vbc

		Vec3 a = self.a
        Vec3 b = self.b
        Vec3 c = self.c;
		float v
        float w;

		// algorithm thanks to Real-Time Collision Detection by Christer Ericson,
		// published by Morgan Kaufmann Publishers, (c) 2005 Elsevier Inc.,
		// under the accompanying license; see chapter 5.1.5 for detailed explanation.
		// basically, we're distinguishing which of the voronoi regions of the triangle
		// the point lies in with the minimum amount of redundant computation.

		_vab.subVectorsLocal( b, a );
		_vac.subVectorsLocal( c, a );
		_vap.subVectorsLocal( p, a );
		float d1 = _vab.dot( _vap );
		float d2 = _vac.dot( _vap );
		if ( d1 <= 0 && d2 <= 0 ) {

			// vertex region of A; barycentric coords (1, 0, 0)
			target.copy( a );
			return target

		}

		_vbp.subVectorsLocal( p, b );
		float d3 = _vab.dot( _vbp );
		float d4 = _vac.dot( _vbp );
		if ( d3 >= 0 && d4 <= d3 ) {

			// vertex region of B; barycentric coords (0, 1, 0)
			target.copy( b );
            return target;
		}

		float vc = d1 * d4 - d3 * d2;
		if ( vc <= 0 && d1 >= 0 && d3 <= 0 ) {

			v = d1 / ( d1 - d3 );
			// edge region of AB; barycentric coords (1-v, v, 0)
			target.copy( a ).addScaledVectorLocal( _vab, v );
            return target
		}

		_vcp.subVectorsLocal( p, c );
		float d5 = _vab.dot( _vcp );
		float d6 = _vac.dot( _vcp );
		if ( d6 >= 0 && d5 <= d6 ) {

			// vertex region of C; barycentric coords (0, 0, 1)
			target.copy( c );
            return target

		}

		float vb = d5 * d2 - d1 * d6;
		if ( vb <= 0 && d2 >= 0 && d6 <= 0 ) {

			w = d2 / ( d2 - d6 );
			// edge region of AC; barycentric coords (1-w, 0, w)
			target.copy( a ).addScaledVectorLocal( _vac, w );
            return target

		}

		float va = d3 * d6 - d5 * d4;
		if ( va <= 0 && ( d4 - d3 ) >= 0 && ( d5 - d6 ) >= 0 ) {

			_vbc.subVectorsLocal( c, b );
			w = ( d4 - d3 ) / ( ( d4 - d3 ) + ( d5 - d6 ) );
			// edge region of BC; barycentric coords (0, 1-w, w)
			target.copy( b ).addScaledVectorLocal( _vbc, w ); // edge region of BC
            return target

		}

		// face region
		float denom = 1 / ( va + vb + vc );
		// u = va * denom
		v = vb * denom;
		w = vc * denom;

		target.copy( a ).addScaledVectorLocal( _vab, v ).addScaledVectorLocal( _vac, w );
        return target

	}

	bool equals(Triangle triangle ) {

		return triangle.a.equals( self.a ) && triangle.b.equals( self.b ) && triangle.c.equals( self.c );

	}
}

Vec3 Triangle_getNormal(Vec3 a, Vec3 b, Vec3 c) {
    Vec3 target
    Vec3 _v0

    target.subVectorsLocal( c, b );
    _v0.subVectorsLocal( a, b );
    target.crossLocal( _v0 );

    float targetLengthSq = target.lengthSq();
    if ( targetLengthSq > 0 ) {

        target.multiplyScalarLocal( 1 / sqrt( targetLengthSq ) );
        return target

    }

    target.set( 0, 0, 0 );
    return target

}

// static/instance method to calculate barycentric coordinates
	// based on: http://www.blackpawn.com/texts/pointinpoly/default.html
Vec3 Triangle_getBarycoord( Vec3 point, Vec3 a, Vec3 b, Vec3 c) {
    Vec3 target
    Vec3 _v0
    Vec3 _v1
    Vec3 _v2

    _v0.subVectorsLocal( c, a );
    _v1.subVectorsLocal( b, a );
    _v2.subVectorsLocal( point, a );

    float dot00 = _v0.dot( _v0 );
    float dot01 = _v0.dot( _v1 );
    float dot02 = _v0.dot( _v2 );
    float dot11 = _v1.dot( _v1 );
    float dot12 = _v1.dot( _v2 );

    float denom = ( dot00 * dot11 - dot01 * dot01 );

    // collinear or singular triangle
    if ( denom == 0 ) {

        // arbitrary location outside of triangle?
        // not sure if this is the best idea, maybe should be returning undefined
        target.set( - 2, - 1, - 1 );
        return target

    }

    float invDenom = 1 / denom;
    float u = ( dot11 * dot02 - dot01 * dot12 ) * invDenom;
    float v = ( dot00 * dot12 - dot01 * dot02 ) * invDenom;

    // barycentric coordinates must always sum to 1
    target.set( 1 - u - v, v, u );
    return target

}


bool Triangle_containsPoint( Vec3 point, Vec3 a, Vec3 b, Vec3 c ) {

    Vec3 _v3 = Triangle_getBarycoord( point, a, b, c);

    return ( _v3.x >= 0 ) && ( _v3.y >= 0 ) && ( ( _v3.x + _v3.y ) <= 1 );

}

bool Triangle_isFrontFacing( Vec3 a, Vec3 b, Vec3 c, Vec3 direction ) {
    Vec3 _v0
    Vec3 _v1

    _v0.subVectorsLocal( c, b );
    _v1.subVectorsLocal( a, b );

    // strictly front facing
    return ( _v0.cross( _v1 ).dot( direction ) < 0 ) ? true : false;

}

Vec3 Triangle_getInterpolation( Vec3 point, Vec3 p1, Vec3 p2, Vec3 p3, Vec3 v1, Vec3 v2, Vec3 v3 ) {
    Vec3 target

    Vec3 _v3 = Triangle_getBarycoord( point, p1, p2, p3 );

    target.setScalar( 0 );

    target.addScaledVectorLocal( v1, _v3.x );
    target.addScaledVectorLocal( v2, _v3.y );
    target.addScaledVectorLocal( v3, _v3.z );

    return target;
}