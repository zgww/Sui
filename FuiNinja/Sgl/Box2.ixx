module;
#include "Core/Vec2.h";
#include "Core/Vec3.h";
#include "Core/Euler.h"
#include "Core/Quaternion.h"

export module Sgl:Box2;



/// 布局上下文
export struct Box2 {
	Vec2 min;
	Vec2 max;

	void set(Vec2 min, Vec2 max) {
		this->min.copy(min);
		this->max.copy(max);
	}

	//Box2 * setFromPoints(Vec2Array * points) {

	//	this->makeEmpty();
	//	int il = points.size;

	//	for (int i = 0; i < il; i++) {
	//		this->expandByPoint(points.data[i]);
	//	}

	//	return this;
	//}

	void setFromCenterAndSize(Vec2 center, Vec2 size) {
		Vec2 halfSize = size.scale(0.5);
		this->min = center.sub(halfSize);
		this->max = center.add(halfSize);
	}

	void makeEmpty() {
		this->min.x = this->min.y = +infinity;
		this->max.x = this->max.y = -infinity;
	}

	bool isEmpty() {
		// this is a more robust check for empty than ( volume <= 0 ) because volume can get positive with two negative axes
		return (this->max.x < this->min.x) || (this->max.y < this->min.y);
	}

	Vec2 getCenter() {
		if (this->isEmpty()) {
			return mkVec2(0, 0);
		}
		Vec2 tmp = this->min.add(this->max);
		return tmp.scale(0.5);
		// return this->isEmpty() ? target.set( 0, 0 ) : target.addVectors( this->min, this->max ).multiplyScalar( 0.5 );
	}

	Vec2 getSize() {
		if (this->isEmpty()) {
			return mkVec2(0, 0);
		}
		Vec2 tmp = this->max.sub(this->min);
		return tmp;
	}

	void expandByPoint(Vec2 point) {
		this->min.minLocal(point);
		this->max.maxLocal(point);
	}

	void expandByVector(Vec2 vector) {
		this->min = this->min.sub(vector);
		this->max = this->max.add(vector);
	}

	void expandByScalar(float scalar) {
		this->min.addScalarLocal(-scalar);
		this->max.addScalarLocal(scalar);
	}

	bool containsPoint(Vec2 point) {
		return point.x < this->min.x || point.x > this->max.x ||
			point.y < this->min.y || point.y > this->max.y ? false : true;
	}

	bool containsBox(Box2 box) {
		return this->min.x <= box.min.x && box.max.x <= this->max.x &&
			this->min.y <= box.min.y && box.max.y <= this->max.y;
	}

	Vec2 getParameter(Vec2 point) {
		Vec2 target;

		// this can potentially have a divide by zero if the box
		// has a size dimension of 0.

		target.set(
			(point.x - this->min.x) / (this->max.x - this->min.x),
			(point.y - this->min.y) / (this->max.y - this->min.y)
		);
		return target;
	}

	bool intersectsBox(Box2 box) {
		// using 4 splitting planes to rule out intersections

		return box.max.x < this->min.x || box.min.x > this->max.x ||
			box.max.y < this->min.y || box.min.y > this->max.y ? false : true;
	}

	Vec2 clampPoint(Vec2 point) {
		return point.clamp(this->min, this->max);
	}

	float distanceToPoint(Vec2 point) {
		return this->clampPoint(point).distanceTo(point);
	}

	void intersect(Box2 box) {

		this->min.maxLocal(box.min);
		this->max.minLocal(box.max);

		if (this->isEmpty()) {
			this->makeEmpty();
		}
	}

	void unionBox2(Box2 box) {
		this->min.minLocal(box.min);
		this->max.maxLocal(box.max);
	}

	void translate(Vec2 offset) {
		this->min = this->min.add(offset);
		this->max = this->max.add(offset);
	}

	bool equals(Box2 box) {
		return box.min.equals(this->min) && box.max.equals(this->max);
	}

};

Box2 mkBox2Zero() {
	Box2 r;
	memset(&r, 0, sizeof(Box2));
	return r;
}