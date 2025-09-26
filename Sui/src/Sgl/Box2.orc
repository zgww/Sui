package Sgl

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

import * from "../Orc/String.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sgl/Buffer.orc"



/// 布局上下文
struct Box2 {
    Vec2 min
    Vec2 max
}
Box2 mkBox2Zero(){
    Box2 r
    memset(&r, 0, sizeof(Box2))
    return r
}
extension Box2 {
	void set(Vec2 min, Vec2 max ) {
		self.min.copy( min );
		self.max.copy( max );
	}

	Box2* setFromPoints(Vec2Array* points ) {

		self.makeEmpty();
        int il = points.size;

		for int i = 0; i < il; i ++ {
			self.expandByPoint( points.data[ i ] );
		}

		return self;
	}

	void setFromCenterAndSize(Vec2 center, Vec2 size ) {
		Vec2 halfSize = size.scale(0.5)
        self.min = center.sub(halfSize)
        self.max = center.add(halfSize)
	}

	void makeEmpty() {
		self.min.x = self.min.y = + infinity;
		self.max.x = self.max.y = - infinity;
	}

	bool isEmpty() {
		// self is a more robust check for empty than ( volume <= 0 ) because volume can get positive with two negative axes
		return ( self.max.x < self.min.x ) || ( self.max.y < self.min.y );
	}

	Vec2 getCenter( ) {
        if self.isEmpty() {
            return mkVec2(0, 0)
        }
        Vec2 tmp = self.min.add(self.max)
        return tmp.scale(0.5)
		// return self.isEmpty() ? target.set( 0, 0 ) : target.addVectors( self.min, self.max ).multiplyScalar( 0.5 );
	}

	Vec2 getSize( ) {
        if self.isEmpty() {
            return mkVec2(0, 0)
        }
        Vec2 tmp = self.max.sub(self.min)
        return tmp
	}

	void expandByPoint(Vec2 point ) {
		self.min.minLocal( point );
		self.max.maxLocal( point );
	}

	void expandByVector(Vec2 vector ) {
		self.min = self.min.sub( vector );
		self.max = self.max.add( vector );
	}

	void expandByScalar(float scalar ) {
		self.min.addScalarLocal( - scalar );
		self.max.addScalarLocal( scalar );
	}

	bool containsPoint(Vec2 point ) {
		return point.x < self.min.x || point.x > self.max.x ||
			point.y < self.min.y || point.y > self.max.y ? false : true;
	}

	bool containsBox(Box2 box ) {
		return self.min.x <= box.min.x && box.max.x <= self.max.x &&
			self.min.y <= box.min.y && box.max.y <= self.max.y;
	}

	Vec2 getParameter(Vec2 point) {
        Vec2 target

		// self can potentially have a divide by zero if the box
		// has a size dimension of 0.

		target.set(
			( point.x - self.min.x ) / ( self.max.x - self.min.x ),
			( point.y - self.min.y ) / ( self.max.y - self.min.y )
		);
		return target
	}

	bool intersectsBox(Box2 box ) {
		// using 4 splitting planes to rule out intersections

		return box.max.x < self.min.x || box.min.x > self.max.x ||
			box.max.y < self.min.y || box.min.y > self.max.y ? false : true;
	}

	Vec2 clampPoint( Vec2 point ) {
		return point.clamp( self.min, self.max );
	}

	float distanceToPoint(Vec2 point ) {
		return self.clampPoint( point).distanceTo( point );
	}

	void intersect(Box2 box ) {

		self.min.maxLocal( box.min );
		self.max.minLocal( box.max );

		if ( self.isEmpty() ) {
            self.makeEmpty();
        }
	}

	void union(Box2 box ) {
		self.min.minLocal( box.min );
		self.max.maxLocal( box.max );
	}

	void translate(Vec2 offset ) {
		self.min = self.min.add( offset );
		self.max = self.max.add( offset );
	}

	bool equals(Box2 box ) {
		return box.min.equals( self.min ) && box.max.equals( self.max );
	}
}
