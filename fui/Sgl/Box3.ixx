module;
#include "Core/Vec3.h";
#include "Core/Euler.h"
#include "Core/Quaternion.h"

export module Sgl:Box3;



/// 布局上下文
export struct Box3 {
	Vec3 min;
	Vec3 max;

	void set(Vec3  min, Vec3 max) {
		this->min.copy(min);
		this->max.copy(max);
	}

	//void setFromArray(FloatArray * array) {
	//	this->makeEmpty();
	//	int il = array.size
	//	for (int i = 0; i < il; i += 3) {

	//		this->expandByPoint(
	//			mkVec3(
	//				array.data[i],
	//				array.data[i + 1],
	//				array.data[i + 2],
	//			)
	//		);
	//	}
	//}

	// setFromBufferAttribute( attribute ) {

	// 	this->makeEmpty();

	// 	for ( let i = 0, il = attribute.count; i < il; i ++ ) {

	// 		this->expandByPoint( _vector.fromBufferAttribute( attribute, i ) );

	// 	}

	// 	return self;

	// }

	//void setFromPoints(Vec3Array * points) {
	//	this->makeEmpty();
	//	int il = points.size
	//	for (int i = 0; i < il; i++) {
	//		this->expandByPoint(points.data[i]);

	//	}
	//}

	void setFromCenterAndSize(Vec3 center, Vec3 size) {

		Vec3 halfSize = size.scale(0.5);

		this->min = center.sub(halfSize);
		this->max = center.add(halfSize);
	}

	// setFromObject( object, precise = false ) {

	// 	this->makeEmpty();

	// 	return this->expandByObject( object, precise );

	// }

	Box3 clone() {
		return *this;
	}

	void copy(Box3 box) {
		this->min.copy(box.min);
		this->max.copy(box.max);
	}

	void makeEmpty() {
		this->min.x = this->min.y = this->min.z = +infinity;
		this->max.x = this->max.y = this->max.z = -infinity;
	}

	bool isEmpty() {

		// self is a more robust check for empty than ( volume <= 0 ) because volume can get positive with two negative axes

		return (this->max.x < this->min.x) || (this->max.y < this->min.y) || (this->max.z < this->min.z);

	}

	Vec3 getCenter() {
		return this->isEmpty()
			? mkVec3(0, 0, 0)
			: this->min.add(this->max).scale(0.5);
	}

	Vec3 getSize() {
		return this->isEmpty()
			? mkVec3(0, 0, 0)
			: this->max.sub(this->min);
	}

	void expandByPoint(Vec3 point) {
		this->min.minLocal(point);
		this->max.maxLocal(point);
	}

	void expandByVector(Vec3 vector) {
		this->min = this->min.sub(vector);
		this->max = this->max.add(vector);
	}

	void expandByScalar(float  scalar) {
		this->min.addScalarLocal(-scalar);
		this->max.addScalarLocal(scalar);
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

	// 		this->union( _box );

	// 	} else {

	// 		const geometry = object.geometry;

	// 		if ( geometry !== undefined ) {

	// 			if ( precise && geometry.attributes !== undefined && geometry.attributes.position !== undefined ) {

	// 				const position = geometry.attributes.position;
	// 				for ( let i = 0, l = position.count; i < l; i ++ ) {

	// 					_vector.fromBufferAttribute( position, i ).applyMatrix4( object.matrixWorld );
	// 					this->expandByPoint( _vector );

	// 				}

	// 			} else {

	// 				if ( geometry.boundingBox === null ) {

	// 					geometry.computeBoundingBox();

	// 				}

	// 				_box.copy( geometry.boundingBox );
	// 				_box.applyMatrix4( object.matrixWorld );

	// 				this->union( _box );

	// 			}

	// 		}

	// 	}

	// 	const children = object.children;

	// 	for ( let i = 0, l = children.length; i < l; i ++ ) {

	// 		this->expandByObject( children[ i ], precise );

	// 	}

	// 	return self;

	// }

	bool containsPoint(Vec3 point) {

		return point.x < this->min.x || point.x > this->max.x ||
			point.y < this->min.y || point.y > this->max.y ||
			point.z < this->min.z || point.z > this->max.z ? false : true;

	}

	bool containsBox(Box3 box) {
		return this->min.x <= box.min.x && box.max.x <= this->max.x &&
			this->min.y <= box.min.y && box.max.y <= this->max.y &&
			this->min.z <= box.min.z && box.max.z <= this->max.z;
	}

	Vec3 getParameter(Vec3 point) {
		// self can potentially have a divide by zero if the box
		// has a size dimension of 0.

		return mkVec3(
			(point.x - this->min.x) / (this->max.x - this->min.x),
			(point.y - this->min.y) / (this->max.y - this->min.y),
			(point.z - this->min.z) / (this->max.z - this->min.z)
		);

	}

	bool intersectsBox(Box3 box) {
		// using 6 splitting planes to rule out intersections.
		return box.max.x < this->min.x || box.min.x > this->max.x ||
			box.max.y < this->min.y || box.min.y > this->max.y ||
			box.max.z < this->min.z || box.min.z > this->max.z ? false : true;
	}

	//bool intersectsSphere(Sphere sphere) {

	//	// Find the point on the AABB closest to the sphere center.
	//	Vec3 _vector = this->clampPoint(sphere.center);

	//	// If that point is inside the sphere, the AABB and sphere intersect.
	//	return _vector.distanceToSquared(sphere.center)
	//	<= (sphere.radius * sphere.radius);

	//}

	// intersectsPlane( plane ) {

	// 	// We compute the minimum and maximum dot product values. If those values
	// 	// are on the same side (back or front) of the plane, then there is no intersection.

	// 	let min, max;

	// 	if ( plane.normal.x > 0 ) {

	// 		min = plane.normal.x * this->min.x;
	// 		max = plane.normal.x * this->max.x;

	// 	} else {

	// 		min = plane.normal.x * this->max.x;
	// 		max = plane.normal.x * this->min.x;

	// 	}

	// 	if ( plane.normal.y > 0 ) {

	// 		min += plane.normal.y * this->min.y;
	// 		max += plane.normal.y * this->max.y;

	// 	} else {

	// 		min += plane.normal.y * this->max.y;
	// 		max += plane.normal.y * this->min.y;

	// 	}

	// 	if ( plane.normal.z > 0 ) {

	// 		min += plane.normal.z * this->min.z;
	// 		max += plane.normal.z * this->max.z;

	// 	} else {

	// 		min += plane.normal.z * this->max.z;
	// 		max += plane.normal.z * this->min.z;

	// 	}

	// 	return ( min <= - plane.constant && max >= - plane.constant );

	// }

	// intersectsTriangle( triangle ) {

	// 	if ( this->isEmpty() ) {

	// 		return false;

	// 	}

	// 	// compute box center and extents
	// 	this->getCenter( _center );
	// 	_extents.subVectors( this->max, _center );

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
		return point.clamp(this->min, this->max);
	}

	float distanceToPoint(Vec3 point) {

		Vec3 _vector = this->clampPoint(point);
		float r = _vector.distanceTo(point);
		return r;

	}

	//Sphere getBoundingSphere() {

	//	if (this->isEmpty()) {
	//		Sphere s;
	//		s.makeEmpty();

	//		return s;
	//	}
	//	else {
	//		Sphere target;

	//		target.center = this->getCenter();
	//		target.radius = this->getSize().length() * 0.5;
	//		return target;
	//	}

	//}

	Box3 intersect(Box3 box) {
		Box3 r = *this;

		r.min.maxLocal(box.min);
		r.max.minLocal(box.max);

		// ensure that if there is no overlap, the result is fully empty, not slightly empty with non-inf/+inf values that will cause subsequence intersects to erroneously return valid values.
		if (r.isEmpty()) {
			r.makeEmpty();
		}

		return r;
	}

	Box3 unionBox3(Box3 box) {
		Box3 r = *this;

		r.min.minLocal(box.min);
		r.max.maxLocal(box.max);

		return r;
	}

	// applyMatrix4( matrix ) {

	// 	// transform of empty box is an empty box.
	// 	if ( this->isEmpty() ) return self;

	// 	// NOTE: I am using a binary pattern to specify all 2^3 combinations below
	// 	_points[ 0 ].set( this->min.x, this->min.y, this->min.z ).applyMatrix4( matrix ); // 000
	// 	_points[ 1 ].set( this->min.x, this->min.y, this->max.z ).applyMatrix4( matrix ); // 001
	// 	_points[ 2 ].set( this->min.x, this->max.y, this->min.z ).applyMatrix4( matrix ); // 010
	// 	_points[ 3 ].set( this->min.x, this->max.y, this->max.z ).applyMatrix4( matrix ); // 011
	// 	_points[ 4 ].set( this->max.x, this->min.y, this->min.z ).applyMatrix4( matrix ); // 100
	// 	_points[ 5 ].set( this->max.x, this->min.y, this->max.z ).applyMatrix4( matrix ); // 101
	// 	_points[ 6 ].set( this->max.x, this->max.y, this->min.z ).applyMatrix4( matrix ); // 110
	// 	_points[ 7 ].set( this->max.x, this->max.y, this->max.z ).applyMatrix4( matrix ); // 111

	// 	this->setFromPoints( _points );

	// 	return self;

	// }

	void translate(Vec3 offset) {
		this->min = this->min.add(offset);
		this->max = this->max.add(offset);
	}

	bool equals(Box3 box) {
		return box.min.equals(this->min) && box.max.equals(this->max);
	}
};