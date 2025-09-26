package Sgl

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

import * from "../Sui/Core/Vec3.orc"
import * from "../Orc/String.orc"
import * from "../Orc/Math.orc"
import * from "../Sgl/Buffer.orc"
import type * from "./Sphere.orc"



/// 布局上下文
struct Box3 {
    Vec3 min
    Vec3 max
}
extension Box3 {

	void set(Vec3  min, Vec3 max ) {
		self.min.copy( min );
		self.max.copy( max );
	}

	void setFromArray(FloatArray* array ) {
		self.makeEmpty();
        int il = array.size
		for ( int i = 0; i < il; i += 3 ) {

			self.expandByPoint( 
                mkVec3(
                    array.data[i],
                    array.data[i+1],
                    array.data[i+2],
                )
            );
		}
	}

	// setFromBufferAttribute( attribute ) {

	// 	self.makeEmpty();

	// 	for ( let i = 0, il = attribute.count; i < il; i ++ ) {

	// 		self.expandByPoint( _vector.fromBufferAttribute( attribute, i ) );

	// 	}

	// 	return self;

	// }

	void setFromPoints(Vec3Array* points ) {
		self.makeEmpty();
        int il = points.size
		for ( int i = 0; i < il; i ++ ) {
			self.expandByPoint( points.data[ i ] );

		}
	}

	void setFromCenterAndSize(Vec3 center, Vec3 size ) {

		Vec3 halfSize = size.scale( 0.5 );

		self.min = center .sub( halfSize );
		self.max = center .add( halfSize );
	}

	// setFromObject( object, precise = false ) {

	// 	self.makeEmpty();

	// 	return self.expandByObject( object, precise );

	// }

	Box3 clone() {
        return *self
	}

	void copy(Box3 box ) {
		self.min.copy( box.min );
		self.max.copy( box.max );
	}

	void makeEmpty() {
		self.min.x = self.min.y = self.min.z = + infinity;
		self.max.x = self.max.y = self.max.z = - infinity;
	}

	bool isEmpty() {

		// self is a more robust check for empty than ( volume <= 0 ) because volume can get positive with two negative axes

		return ( self.max.x < self.min.x ) || ( self.max.y < self.min.y ) || ( self.max.z < self.min.z );

	}

	Vec3 getCenter( ) {
		return self.isEmpty() 
        ?  mkVec3( 0, 0, 0 ) 
        : self.min.add(self.max).scale( 0.5 );
	}

	Vec3 getSize() {

		return self.isEmpty() 
        ? mkVec3( 0, 0, 0 ) 
        : self.max.sub(self.min );
	}

	void expandByPoint(Vec3 point ) {
		self.min.minLocal( point );
		self.max.maxLocal( point );
	}

	void expandByVector(Vec3 vector ) {
		self.min = self.min.sub( vector );
		self.max = self.max.add( vector );
	}

	void expandByScalar(float  scalar ) {
		self.min.addScalarLocal( - scalar );
		self.max.addScalarLocal( scalar );
	}

	// expandByObject( object, precise = false ) {

	// 	// Computes the world-axis-aligned bounding box of an object (including its children),
	// 	// accounting for both the object's, and children's, world transforms

	// 	object.updateWorldMatrix( false, false );

	// 	if ( object.boundingBox !== undefined ) {

	// 		if ( object.boundingBox === null ) {

	// 			object.computeBoundingBox();

	// 		}

	// 		_box.copy( object.boundingBox );
	// 		_box.applyMatrix4( object.matrixWorld );

	// 		self.union( _box );

	// 	} else {

	// 		const geometry = object.geometry;

	// 		if ( geometry !== undefined ) {

	// 			if ( precise && geometry.attributes !== undefined && geometry.attributes.position !== undefined ) {

	// 				const position = geometry.attributes.position;
	// 				for ( let i = 0, l = position.count; i < l; i ++ ) {

	// 					_vector.fromBufferAttribute( position, i ).applyMatrix4( object.matrixWorld );
	// 					self.expandByPoint( _vector );

	// 				}

	// 			} else {

	// 				if ( geometry.boundingBox === null ) {

	// 					geometry.computeBoundingBox();

	// 				}

	// 				_box.copy( geometry.boundingBox );
	// 				_box.applyMatrix4( object.matrixWorld );

	// 				self.union( _box );

	// 			}

	// 		}

	// 	}

	// 	const children = object.children;

	// 	for ( let i = 0, l = children.length; i < l; i ++ ) {

	// 		self.expandByObject( children[ i ], precise );

	// 	}

	// 	return self;

	// }

	bool containsPoint(Vec3 point ) {

		return point.x < self.min.x || point.x > self.max.x ||
			point.y < self.min.y || point.y > self.max.y ||
			point.z < self.min.z || point.z > self.max.z ? false : true;

	}

	bool containsBox(Box3 box ) {
		return self.min.x <= box.min.x && box.max.x <= self.max.x &&
			self.min.y <= box.min.y && box.max.y <= self.max.y &&
			self.min.z <= box.min.z && box.max.z <= self.max.z;
	}

	Vec3 getParameter(Vec3 point) {
		// self can potentially have a divide by zero if the box
		// has a size dimension of 0.

		return mkVec3(
			( point.x - self.min.x ) / ( self.max.x - self.min.x ),
			( point.y - self.min.y ) / ( self.max.y - self.min.y ),
			( point.z - self.min.z ) / ( self.max.z - self.min.z )
		);

	}

	bool intersectsBox(Box3 box ) {
		// using 6 splitting planes to rule out intersections.
		return box.max.x < self.min.x || box.min.x > self.max.x ||
			box.max.y < self.min.y || box.min.y > self.max.y ||
			box.max.z < self.min.z || box.min.z > self.max.z ? false : true;
	}

	bool intersectsSphere(Sphere sphere ) {

		// Find the point on the AABB closest to the sphere center.
		Vec3 _vector = self.clampPoint( sphere.center);

		// If that point is inside the sphere, the AABB and sphere intersect.
		return _vector.distanceToSquared( sphere.center ) 
        <= ( sphere.radius * sphere.radius );

	}

	// intersectsPlane( plane ) {

	// 	// We compute the minimum and maximum dot product values. If those values
	// 	// are on the same side (back or front) of the plane, then there is no intersection.

	// 	let min, max;

	// 	if ( plane.normal.x > 0 ) {

	// 		min = plane.normal.x * self.min.x;
	// 		max = plane.normal.x * self.max.x;

	// 	} else {

	// 		min = plane.normal.x * self.max.x;
	// 		max = plane.normal.x * self.min.x;

	// 	}

	// 	if ( plane.normal.y > 0 ) {

	// 		min += plane.normal.y * self.min.y;
	// 		max += plane.normal.y * self.max.y;

	// 	} else {

	// 		min += plane.normal.y * self.max.y;
	// 		max += plane.normal.y * self.min.y;

	// 	}

	// 	if ( plane.normal.z > 0 ) {

	// 		min += plane.normal.z * self.min.z;
	// 		max += plane.normal.z * self.max.z;

	// 	} else {

	// 		min += plane.normal.z * self.max.z;
	// 		max += plane.normal.z * self.min.z;

	// 	}

	// 	return ( min <= - plane.constant && max >= - plane.constant );

	// }

	// intersectsTriangle( triangle ) {

	// 	if ( self.isEmpty() ) {

	// 		return false;

	// 	}

	// 	// compute box center and extents
	// 	self.getCenter( _center );
	// 	_extents.subVectors( self.max, _center );

	// 	// translate triangle to aabb origin
	// 	_v0.subVectors( triangle.a, _center );
	// 	_v1.subVectors( triangle.b, _center );
	// 	_v2.subVectors( triangle.c, _center );

	// 	// compute edge vectors for triangle
	// 	_f0.subVectors( _v1, _v0 );
	// 	_f1.subVectors( _v2, _v1 );
	// 	_f2.subVectors( _v0, _v2 );

	// 	// test against axes that are given by cross product combinations of the edges of the triangle and the edges of the aabb
	// 	// make an axis testing of each of the 3 sides of the aabb against each of the 3 sides of the triangle = 9 axis of separation
	// 	// axis_ij = u_i x f_j (u0, u1, u2 = face normals of aabb = x,y,z axes vectors since aabb is axis aligned)
	// 	let axes = [
	// 		0, - _f0.z, _f0.y, 0, - _f1.z, _f1.y, 0, - _f2.z, _f2.y,
	// 		_f0.z, 0, - _f0.x, _f1.z, 0, - _f1.x, _f2.z, 0, - _f2.x,
	// 		- _f0.y, _f0.x, 0, - _f1.y, _f1.x, 0, - _f2.y, _f2.x, 0
	// 	];
	// 	if ( ! satForAxes( axes, _v0, _v1, _v2, _extents ) ) {

	// 		return false;

	// 	}

	// 	// test 3 face normals from the aabb
	// 	axes = [ 1, 0, 0, 0, 1, 0, 0, 0, 1 ];
	// 	if ( ! satForAxes( axes, _v0, _v1, _v2, _extents ) ) {

	// 		return false;

	// 	}

	// 	// finally testing the face normal of the triangle
	// 	// use already existing triangle edge vectors here
	// 	_triangleNormal.crossVectors( _f0, _f1 );
	// 	axes = [ _triangleNormal.x, _triangleNormal.y, _triangleNormal.z ];

	// 	return satForAxes( axes, _v0, _v1, _v2, _extents );

	// }

	Vec3 clampPoint(Vec3 point) {
		return point.clamp( self.min, self.max );
	}

	float distanceToPoint(Vec3 point ) {

		Vec3 _vector = self.clampPoint( point)
        float r = _vector.distanceTo( point );
        return r

	}

	Sphere getBoundingSphere( ) {

		if ( self.isEmpty() ) {
            Sphere s
            s.makeEmpty()

            return s
		} else {
            Sphere target

			target.center = self.getCenter();
			target.radius = self.getSize().length() * 0.5;
            return target
		}

	}

	Box3 intersect(Box3 box ) {
        Box3 r = *self

		r.min.maxLocal( box.min );
		r.max.minLocal( box.max );

		// ensure that if there is no overlap, the result is fully empty, not slightly empty with non-inf/+inf values that will cause subsequence intersects to erroneously return valid values.
		if ( r.isEmpty() ) {
            r.makeEmpty();
        } 

		return r;
	}

	Box3 union(Box3 box ) {
        Box3 r = *self

		r.min.minLocal( box.min );
		r.max.maxLocal( box.max );

		return r;
	}

	// applyMatrix4( matrix ) {

	// 	// transform of empty box is an empty box.
	// 	if ( self.isEmpty() ) return self;

	// 	// NOTE: I am using a binary pattern to specify all 2^3 combinations below
	// 	_points[ 0 ].set( self.min.x, self.min.y, self.min.z ).applyMatrix4( matrix ); // 000
	// 	_points[ 1 ].set( self.min.x, self.min.y, self.max.z ).applyMatrix4( matrix ); // 001
	// 	_points[ 2 ].set( self.min.x, self.max.y, self.min.z ).applyMatrix4( matrix ); // 010
	// 	_points[ 3 ].set( self.min.x, self.max.y, self.max.z ).applyMatrix4( matrix ); // 011
	// 	_points[ 4 ].set( self.max.x, self.min.y, self.min.z ).applyMatrix4( matrix ); // 100
	// 	_points[ 5 ].set( self.max.x, self.min.y, self.max.z ).applyMatrix4( matrix ); // 101
	// 	_points[ 6 ].set( self.max.x, self.max.y, self.min.z ).applyMatrix4( matrix ); // 110
	// 	_points[ 7 ].set( self.max.x, self.max.y, self.max.z ).applyMatrix4( matrix ); // 111

	// 	self.setFromPoints( _points );

	// 	return self;

	// }

	void translate(Vec3 offset ) {
		self.min = self.min.add( offset );
		self.max = self.max.add( offset );
	}

	bool equals(Box3 box ) {
		return box.min.equals( self.min ) && box.max.equals( self.max );
	}
}

// void satForAxes( axes, v0, v1, v2, extents ) {

// 	for ( let i = 0, j = axes.length - 3; i <= j; i += 3 ) {

// 		_testAxis.fromArray( axes, i );
// 		// project the aabb onto the separating axis
// 		const r = extents.x * Math.abs( _testAxis.x ) + extents.y * Math.abs( _testAxis.y ) + extents.z * Math.abs( _testAxis.z );
// 		// project all 3 vertices of the triangle onto the separating axis
// 		const p0 = v0.dot( _testAxis );
// 		const p1 = v1.dot( _testAxis );
// 		const p2 = v2.dot( _testAxis );
// 		// actual test, basically see if either of the most extreme of the triangle points intersects r
// 		if ( Math.max( - Math.max( p0, p1, p2 ), Math.min( p0, p1, p2 ) ) > r ) {

// 			// points of the projected triangle are outside the projected half-length of the aabb
// 			// the axis is separating and we can exit
// 			return false;

// 		}

// 	}

// 	return true;

// }