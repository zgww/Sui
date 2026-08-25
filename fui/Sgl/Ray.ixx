module;
#include "Core/Vec3.h";
#include "Core/Euler.h"
#include "Core/Quaternion.h"
#include "Core/Plane.h"

export module Sgl:Ray;

import :Mat;
import :Sphere;


/// 布局上下文
export struct DistanceResult {
	float distance;
	bool succ;
};
export struct IntersectResult {
	Vec3 point;
	bool succ;
};


IntersectResult mkIntersectResult(Vec3 point) {
	IntersectResult r;
	r.point = point;
	r.succ = true;
	return r;
}
IntersectResult mkIntersectResultFail() {
	IntersectResult r;
	r.point = mkVec3(0, 0, 0);
	r.succ = false;
	return r;
}
export struct Ray {
	Vec3 origin;
	Vec3 direction;

	void set(Vec3 origin, Vec3 direction) {

		this->origin.copy(origin);
		this->direction.copy(direction);
	}

	void copy(Ray ray) {
		*this = ray;
	}

	// at length
	Vec3 at(float t) {
		Vec3 target = this->origin;
		target.addScaledVectorLocal(this->direction, t);
			return target;
	}

	void lookAt(Vec3 v) {
		Vec3 tmp = v.sub(this->origin);
		this->direction = tmp.normalize();
	}

	// origin move forward t length
	void recast(float t) {
		this->origin.copy(this->at(t));
	}

	Vec3 closestPointToPoint(Vec3 point) {
		Vec3 target = point.sub(this->origin);

			float directionDistance = target.dot(this->direction);

		if (directionDistance < 0) {
			return this->origin;
		}

		target = this->origin;
		target.addScaledVectorLocal(this->direction, directionDistance);
			// return target.copy( this->origin ).addScaledVector( this->direction, directionDistance );
			return target;

	}

	float distanceToPoint(Vec3 point) {

		return sqrt(this->distanceSqToPoint(point));

	}

	float distanceSqToPoint(Vec3 point) {
		Vec3 _v = point.sub(this->origin);
		float directionDistance = _v.dot(this->direction);
			// const directionDistance = _vector.subVectors( point, this->origin ).dot( this->direction );

			// point behind the ray

			if (directionDistance < 0) {

				return this->origin.distanceToSquared(point);

			}
			Vec3 tmp = this->origin;
			tmp.addScaledVectorLocal(this->direction, directionDistance);
			// _vector.copy( this->origin ).addScaledVector( this->direction, directionDistance );

			// return _vector.distanceToSquared( point );
			return tmp.distanceToSquared(point);
	}

	// float distanceSqToSegment(Vec3 v0, Vec3 v1, Vec3 optionalPointOnRay, Vec3 optionalPointOnSegment ) {

	// 	// from https://github.com/pmjoniak/GeometricTools/blob/master/GTEngine/Include/Mathematics/GteDistRaySegment.h
	// 	// It returns the min distance between the ray and the segment
	// 	// defined by v0 and v1
	// 	// It can also set two optional targets :
	// 	// - The closest point on the ray
	// 	// - The closest point on the segment
	//     Vec3 _segCenter
	//     Vec3 _segDir
	//     Vec3 _diff

	// 	_segCenter.copy( v0 ).add( v1 ).multiplyScalar( 0.5 );
	// 	_segDir.copy( v1 ).sub( v0 ).normalize();
	// 	_diff.copy( this->origin ).sub( _segCenter );

	// 	const segExtent = v0.distanceTo( v1 ) * 0.5;
	// 	const a01 = - this->direction.dot( _segDir );
	// 	const b0 = _diff.dot( this->direction );
	// 	const b1 = - _diff.dot( _segDir );
	// 	const c = _diff.lengthSq();
	// 	const det = Math.abs( 1 - a01 * a01 );
	// 	let s0, s1, sqrDist, extDet;

	// 	if ( det > 0 ) {

	// 		// The ray and segment are not parallel.

	// 		s0 = a01 * b1 - b0;
	// 		s1 = a01 * b0 - b1;
	// 		extDet = segExtent * det;

	// 		if ( s0 >= 0 ) {

	// 			if ( s1 >= - extDet ) {

	// 				if ( s1 <= extDet ) {

	// 					// region 0
	// 					// Minimum at interior points of ray and segment.

	// 					const invDet = 1 / det;
	// 					s0 *= invDet;
	// 					s1 *= invDet;
	// 					sqrDist = s0 * ( s0 + a01 * s1 + 2 * b0 ) + s1 * ( a01 * s0 + s1 + 2 * b1 ) + c;

	// 				} else {

	// 					// region 1

	// 					s1 = segExtent;
	// 					s0 = Math.max( 0, - ( a01 * s1 + b0 ) );
	// 					sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

	// 				}

	// 			} else {

	// 				// region 5

	// 				s1 = - segExtent;
	// 				s0 = Math.max( 0, - ( a01 * s1 + b0 ) );
	// 				sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

	// 			}

	// 		} else {

	// 			if ( s1 <= - extDet ) {

	// 				// region 4

	// 				s0 = Math.max( 0, - ( - a01 * segExtent + b0 ) );
	// 				s1 = ( s0 > 0 ) ? - segExtent : Math.min( Math.max( - segExtent, - b1 ), segExtent );
	// 				sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

	// 			} else if ( s1 <= extDet ) {

	// 				// region 3

	// 				s0 = 0;
	// 				s1 = Math.min( Math.max( - segExtent, - b1 ), segExtent );
	// 				sqrDist = s1 * ( s1 + 2 * b1 ) + c;

	// 			} else {

	// 				// region 2

	// 				s0 = Math.max( 0, - ( a01 * segExtent + b0 ) );
	// 				s1 = ( s0 > 0 ) ? segExtent : Math.min( Math.max( - segExtent, - b1 ), segExtent );
	// 				sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

	// 			}

	// 		}

	// 	} else {

	// 		// Ray and segment are parallel.

	// 		s1 = ( a01 > 0 ) ? - segExtent : segExtent;
	// 		s0 = Math.max( 0, - ( a01 * s1 + b0 ) );
	// 		sqrDist = - s0 * s0 + s1 * ( s1 + 2 * b1 ) + c;

	// 	}

	// 	if ( optionalPointOnRay ) {

	// 		optionalPointOnRay.copy( this->origin ).addScaledVector( this->direction, s0 );

	// 	}

	// 	if ( optionalPointOnSegment ) {

	// 		optionalPointOnSegment.copy( _segCenter ).addScaledVector( _segDir, s1 );

	// 	}

	// 	return sqrDist;

	// }

	IntersectResult intersectSphere(Sphere sphere, Vec3 result) {
		Vec3 target;
		Vec3 _vector = sphere.center.sub(this->origin);

			float tca = _vector.dot(this->direction);
		float d2 = _vector.dot(_vector) - tca * tca;
		float radius2 = sphere.radius * sphere.radius;

		if (d2 > radius2) { return mkIntersectResultFail(); }

		float thc = sqrt(radius2 - d2);

		// t0 = first intersect point - entrance on front of sphere
		float t0 = tca - thc;

		// t1 = second intersect point - exit point on back of sphere
		float t1 = tca + thc;

		// test to see if t1 is behind the ray - if so, return null
		if (t1 < 0) { return mkIntersectResultFail(); }

		// test to see if t0 is behind the ray:
		// if it is, the ray is inside the sphere, so return the second exit point scaled by t1,
		// in order to always return an intersect point that is in front of the ray.
		if (t0 < 0) { return mkIntersectResult(this->at(t1)); }

		// else t0 is in front of the ray, so return the first collision point scaled by t0
		return mkIntersectResult(this->at(t0));
	}

	bool intersectsSphere(Sphere sphere) {
		return this->distanceSqToPoint(sphere.center) <= (sphere.radius * sphere.radius);
	}

	DistanceResult distanceToPlane(Plane plane) {
		DistanceResult r;

			float denominator = plane.normal.dot(this->direction);

		if (eqFloat(denominator, 0)) {

			// line is coplanar, return origin
			if (eqFloat(plane.distanceToPoint(this->origin), 0)) {
				r.distance = 0;
				r.succ = true;
					return r;
			}

			// Null is preferable to undefined since undefined means.... it is undefined

			r.succ = false;
				return r;

		}

		float t = -(this->origin.dot(plane.normal) + plane.constant) / denominator;

		// Return if the ray never intersects the plane

		if ( t >= 0 ) { //射线有方向性
			r.distance = t;//t >= 0 ? t : null;
				r.succ = true;
		}
		else {
			r.succ = false;
		}

		return r;
	}

	IntersectResult intersectPlane(Plane plane) {
		DistanceResult t = this->distanceToPlane(plane);

		if (!t.succ){ //说明平行
			return  mkIntersectResultFail();
		}

		Vec3 p = this->at(t.distance);
		return mkIntersectResult(p);
	}

	// intersectsPlane( plane ) {

	// 	// check if the ray lies on the plane first

	// 	const distToPoint = plane.distanceToPoint( this->origin );

	// 	if ( distToPoint === 0 ) {

	// 		return true;

	// 	}

	// 	const denominator = plane.normal.dot( this->direction );

	// 	if ( denominator * distToPoint < 0 ) {

	// 		return true;

	// 	}

	// 	// ray origin is behind the plane (and is pointing behind it)

	// 	return false;

	// }

	IntersectResult intersectBox(Box3 box) {
		float tmin = 0;
		float tmax = 0;
		float tymin = 0;
		float tymax = 0;
		float tzmin = 0;
		float tzmax = 0;

			float invdirx = 1 / this->direction.x;
		float invdiry = 1 / this->direction.y;
		float invdirz = 1 / this->direction.z;

		Vec3 origin = this->origin;

		if (invdirx >= 0) {

			tmin = (box.min.x - origin.x) * invdirx;
			tmax = (box.max.x - origin.x) * invdirx;

		}
		else {

			tmin = (box.max.x - origin.x) * invdirx;
			tmax = (box.min.x - origin.x) * invdirx;

		}

		if (invdiry >= 0) {

			tymin = (box.min.y - origin.y) * invdiry;
			tymax = (box.max.y - origin.y) * invdiry;

		}
		else {

			tymin = (box.max.y - origin.y) * invdiry;
			tymax = (box.min.y - origin.y) * invdiry;

		}

		if ((tmin > tymax) || (tymin > tmax)) { return mkIntersectResultFail(); }

		if (tymin > tmin || isNaN(tmin)) { tmin = tymin; }

		if (tymax < tmax || isNaN(tmax)) { tmax = tymax; }

		if (invdirz >= 0) {

			tzmin = (box.min.z - origin.z) * invdirz;
			tzmax = (box.max.z - origin.z) * invdirz;

		}
		else {

			tzmin = (box.max.z - origin.z) * invdirz;
			tzmax = (box.min.z - origin.z) * invdirz;

		}

		if ((tmin > tzmax) || (tzmin > tmax)) { return mkIntersectResultFail(); }

		if (tzmin > tmin || tmin != tmin) { tmin = tzmin; }

		if (tzmax < tmax || tmax != tmax) { tmax = tzmax; }

		//return point closest to the ray (positive side)

		if (tmax < 0) { return mkIntersectResultFail(); }

		return mkIntersectResult(this->at(tmin >= 0 ? tmin : tmax));
	}

	bool intersectsBox(Box3 box) {
		return this->intersectBox(box).succ;
	}

	IntersectResult intersectTriangle(Vec3 a, Vec3 b, Vec3 c, bool backfaceCulling) {

		// Compute the offset origin, edges, and normal.

		// from https://github.com/pmjoniak/GeometricTools/blob/master/GTEngine/Include/Mathematics/GteIntrRay3Triangle3.h

		Vec3 _edge1 = b.sub(a);
		Vec3 _edge2 = c.sub(a);
		Vec3 _normal = _edge1.cross(_edge2);

		// Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = ray direction,
		// E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
		//   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
		//   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
		//   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
		float DdN = this->direction.dot(_normal);
		float sign;

		if (DdN > 0) {

			if (backfaceCulling) { return mkIntersectResultFail(); }
			sign = 1;

		}
		else if (DdN < 0) {

			sign = -1;
			DdN = -DdN;

		}
		else {

			return mkIntersectResultFail();

		}

		Vec3 _diff = this->origin.sub(a);
		_edge2 = _diff.cross(_edge2);
		float DdQxE2 = sign * this->direction.dot(_edge2);

		// b1 < 0, no intersection
		if (DdQxE2 < 0) {

			return mkIntersectResultFail();

		}

		float DdE1xQ = sign * this->direction.dot(_edge1.cross(_diff));

		// b2 < 0, no intersection
		if (DdE1xQ < 0) {

			return mkIntersectResultFail();

		}

		// b1+b2 > 1, no intersection
		if (DdQxE2 + DdE1xQ > DdN) {

			return mkIntersectResultFail();

		}

		// Line intersects triangle, check if ray does.
		float QdN = -sign * _diff.dot(_normal);

		// t < 0, no intersection
		if (QdN < 0) {

			return mkIntersectResultFail();

		}

		// Ray intersects triangle.
		return mkIntersectResult(this->at(QdN / DdN));
	}

	void applyMatrix4Local(Mat matrix4) {
		//this->origin.applyMatrix4Local(matrix4);
		this->origin = matrix4.applyToVec3(this->origin);
		//this->direction.transformDirectionLocal(matrix4);
		this->direction = matrix4.transformDirection(this->direction);
	}

	bool equals(Ray ray) {
		return ray.origin.equals(this->origin) && ray.direction.equals(this->direction);
	}

	Ray clone() {
		return *this;
	}
};




Ray mkRay(Vec3 origin, Vec3 direction) {
	Ray r;
	r.origin = origin;
	//归一化的
	r.direction = direction;
	return r;

}