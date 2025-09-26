package Sgl

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

import * from "../Orc/String.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Vec3.orc"
import type * from "./Sphere.orc"
import type * from "./Box3.orc"
import * from "./Mat.orc"



/// 布局上下文
struct Ray {
    Vec3 origin
    Vec3 direction
}
struct IntersectResult {
	Vec3 point
	bool succ
}
IntersectResult mkIntersectResult(Vec3 point){
	IntersectResult r
	r.point = point
	r.succ = true
	return r
}
IntersectResult mkIntersectResultFail(){
	IntersectResult r
	r.point = mkVec3(0, 0, 0)
	r.succ = false
	return r
}
Ray mkRay(Vec3 origin, Vec3 direction){
    Ray r
    r.origin = origin
	//归一化的
    r.direction = direction
    return r
}
extension Ray {

	void set(Vec3 origin, Vec3 direction ) {

		self.origin.copy( origin );
		self.direction.copy( direction );
	}

	void copy(Ray ray ) {
        *self = ray
	}

	// at length
	Vec3 at(float t) {
        Vec3 target = self.origin
        target.addScaledVectorLocal(self.direction, t)
        return target
	}

	void lookAt( Vec3 v ) {
		Vec3 tmp = v.sub(self.origin)
        self.direction = tmp.normal()
	}

	// origin move forward t length
	void recast( float t ) {
		self.origin.copy( self.at( t) );
	}

	Vec3 closestPointToPoint(Vec3 point) {
        Vec3 target = point.sub(self.origin)

		float directionDistance = target.dot( self.direction );

		if ( directionDistance < 0 ) {
            return self.origin
		}

        target = self.origin
        target.addScaledVectorLocal(self.direction, directionDistance)
		// return target.copy( self.origin ).addScaledVector( self.direction, directionDistance );
        return target

	}

	float distanceToPoint( Vec3 point ) {

		return sqrt( self.distanceSqToPoint( point ) );

	}

	float distanceSqToPoint(Vec3 point ) {
		Vec3 _v = point.sub(self.origin)
        float directionDistance = _v.dot(self.direction)
		// const directionDistance = _vector.subVectors( point, self.origin ).dot( self.direction );

		// point behind the ray

		if ( directionDistance < 0 ) {

			return self.origin.distanceToSquared( point );

		}
        Vec3 tmp = self.origin
        tmp.addScaledVectorLocal(self.direction, directionDistance)
		// _vector.copy( self.origin ).addScaledVector( self.direction, directionDistance );

		// return _vector.distanceToSquared( point );
        return tmp.distanceToSquared(point)
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
	// 	_diff.copy( self.origin ).sub( _segCenter );

	// 	const segExtent = v0.distanceTo( v1 ) * 0.5;
	// 	const a01 = - self.direction.dot( _segDir );
	// 	const b0 = _diff.dot( self.direction );
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

	// 		optionalPointOnRay.copy( self.origin ).addScaledVector( self.direction, s0 );

	// 	}

	// 	if ( optionalPointOnSegment ) {

	// 		optionalPointOnSegment.copy( _segCenter ).addScaledVector( _segDir, s1 );

	// 	}

	// 	return sqrDist;

	// }

	IntersectResult intersectSphere(Sphere sphere, Vec3 result) {
		Vec3 target
		Vec3 _vector = sphere.center.sub(self.origin)

		float tca = _vector.dot( self.direction );
		float d2 = _vector.dot( _vector ) - tca * tca;
		float radius2 = sphere.radius * sphere.radius;

		if ( d2 > radius2 ) {return mkIntersectResultFail();}

		float thc = sqrt( radius2 - d2 );

		// t0 = first intersect point - entrance on front of sphere
		float t0 = tca - thc;

		// t1 = second intersect point - exit point on back of sphere
		float t1 = tca + thc;

		// test to see if t1 is behind the ray - if so, return null
		if ( t1 < 0 ) {return mkIntersectResultFail();}

		// test to see if t0 is behind the ray:
		// if it is, the ray is inside the sphere, so return the second exit point scaled by t1,
		// in order to always return an intersect point that is in front of the ray.
		if ( t0 < 0 ) {return mkIntersectResult(self.at( t1));}

		// else t0 is in front of the ray, so return the first collision point scaled by t0
		return mkIntersectResult(self.at( t0));
	}

	bool intersectsSphere(Sphere sphere ) {
		return self.distanceSqToPoint( sphere.center ) <= ( sphere.radius * sphere.radius );
	}

	// distanceToPlane( plane ) {

	// 	const denominator = plane.normal.dot( self.direction );

	// 	if ( denominator === 0 ) {

	// 		// line is coplanar, return origin
	// 		if ( plane.distanceToPoint( self.origin ) === 0 ) {

	// 			return 0;

	// 		}

	// 		// Null is preferable to undefined since undefined means.... it is undefined

	// 		return null;

	// 	}

	// 	const t = - ( self.origin.dot( plane.normal ) + plane.constant ) / denominator;

	// 	// Return if the ray never intersects the plane

	// 	return t >= 0 ? t : null;

	// }

	// intersectPlane( plane, target ) {

	// 	const t = self.distanceToPlane( plane );

	// 	if ( t === null ) {

	// 		return null;

	// 	}

	// 	return self.at( t, target );

	// }

	// intersectsPlane( plane ) {

	// 	// check if the ray lies on the plane first

	// 	const distToPoint = plane.distanceToPoint( self.origin );

	// 	if ( distToPoint === 0 ) {

	// 		return true;

	// 	}

	// 	const denominator = plane.normal.dot( self.direction );

	// 	if ( denominator * distToPoint < 0 ) {

	// 		return true;

	// 	}

	// 	// ray origin is behind the plane (and is pointing behind it)

	// 	return false;

	// }

	IntersectResult intersectBox(Box3 box) {
		float tmin = 0
		float tmax = 0
		float tymin = 0
		float tymax = 0
		float tzmin = 0
		float tzmax = 0

		float invdirx = 1 / self.direction.x;
		float invdiry = 1 / self.direction.y;
		float invdirz = 1 / self.direction.z;

		Vec3 origin = self.origin;

		if ( invdirx >= 0 ) {

			tmin = ( box.min.x - origin.x ) * invdirx;
			tmax = ( box.max.x - origin.x ) * invdirx;

		} else {

			tmin = ( box.max.x - origin.x ) * invdirx;
			tmax = ( box.min.x - origin.x ) * invdirx;

		}

		if ( invdiry >= 0 ) {

			tymin = ( box.min.y - origin.y ) * invdiry;
			tymax = ( box.max.y - origin.y ) * invdiry;

		} else {

			tymin = ( box.max.y - origin.y ) * invdiry;
			tymax = ( box.min.y - origin.y ) * invdiry;

		}

		if ( ( tmin > tymax ) || ( tymin > tmax ) ) {return mkIntersectResultFail() }

		if ( tymin > tmin || isNaN( tmin ) ) {tmin = tymin;}

		if ( tymax < tmax || isNaN( tmax ) ) {tmax = tymax;}

		if ( invdirz >= 0 ) {

			tzmin = ( box.min.z - origin.z ) * invdirz;
			tzmax = ( box.max.z - origin.z ) * invdirz;

		} else {

			tzmin = ( box.max.z - origin.z ) * invdirz;
			tzmax = ( box.min.z - origin.z ) * invdirz;

		}

		if ( ( tmin > tzmax ) || ( tzmin > tmax ) ) { return mkIntersectResultFail()}

		if ( tzmin > tmin || tmin != tmin ) {tmin = tzmin;}

		if ( tzmax < tmax || tmax != tmax ) { tmax = tzmax;}

		//return point closest to the ray (positive side)

		if ( tmax < 0 ) {return mkIntersectResultFail()}

		return mkIntersectResult(self.at( tmin >= 0 ? tmin : tmax))
	}

	bool intersectsBox(Box3 box ) {
		return self.intersectBox( box).succ;
	}

	IntersectResult intersectTriangle(Vec3 a, Vec3 b, Vec3 c, bool backfaceCulling) {

		// Compute the offset origin, edges, and normal.

		// from https://github.com/pmjoniak/GeometricTools/blob/master/GTEngine/Include/Mathematics/GteIntrRay3Triangle3.h

		Vec3 _edge1 =  b.sub( a );
		Vec3 _edge2 = c.sub( a );
		Vec3 _normal = _edge1.cross( _edge2 );

		// Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = ray direction,
		// E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
		//   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
		//   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
		//   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
		float DdN = self.direction.dot( _normal );
		float sign;

		if ( DdN > 0 ) {

			if ( backfaceCulling ) {return mkIntersectResultFail();}
			sign = 1;

		} else if ( DdN < 0 ) {

			sign = - 1;
			DdN = - DdN;

		} else {

			return mkIntersectResultFail();

		}

		Vec3 _diff =  self.origin.sub( a );
		_edge2 = _diff.cross( _edge2 );
		float DdQxE2 = sign * self.direction.dot( _edge2 );

		// b1 < 0, no intersection
		if ( DdQxE2 < 0 ) {

			return mkIntersectResultFail();

		}

		float DdE1xQ = sign * self.direction.dot( _edge1.cross( _diff ) );

		// b2 < 0, no intersection
		if ( DdE1xQ < 0 ) {

			return mkIntersectResultFail();

		}

		// b1+b2 > 1, no intersection
		if ( DdQxE2 + DdE1xQ > DdN ) {

			return mkIntersectResultFail();

		}

		// Line intersects triangle, check if ray does.
		float QdN = - sign * _diff.dot( _normal );

		// t < 0, no intersection
		if ( QdN < 0 ) {

			return mkIntersectResultFail();

		}

		// Ray intersects triangle.
		return mkIntersectResult( self.at( QdN / DdN) );
	}

	void applyMatrix4Local(Mat matrix4 ) {
		self.origin.applyMatrix4Local( matrix4 );
		self.direction.transformDirectionLocal( matrix4 );
	}

	bool equals(Ray ray ) {
		return ray.origin.equals( self.origin ) && ray.direction.equals( self.direction );
	}

	Ray clone() {
        return *self
	}

}