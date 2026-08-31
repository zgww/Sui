module;
#include "Core/Vec3.h"
#include "Core/Euler.h"
#include "Core/Mat.h"
#include "Core/Quaternion.h"

export module Sgl:Sphere;

import Sgl_Box3;

/// 布局上下文
export struct Sphere {
	Vec3 center;
	float radius;

	Sphere* set(Vec3 center, float radius) {
		this->center.copy(center);
		this->radius = radius;
		return this;
	}

	//Sphere* setFromPoints(Vec3Array* points, Vec3* optionalCenter) {

	//	Vec3* center = &this->center;

	//	if (optionalCenter != null) {

	//		center.copy(*optionalCenter);

	//	}
	//	else {
	//		Box3 _box
	//			_box.setFromPoints(points)
	//			this->center = _box.getCenter();
	//	}

	//	float maxRadiusSq = 0;

	//	int il = points.size
	//		for (int i = 0; i < il; i++) {
	//			maxRadiusSq = maxFloat(maxRadiusSq, center.distanceToSquared(points.data[i]));
	//		}

	//	this->radius = sqrt(maxRadiusSq);
	//	return this;
	//}

	Sphere* copy(Sphere sphere) {
		*this = sphere;
		return this;
	}

	bool isEmpty() {
		return (this->radius < 0);
	}

	void makeEmpty() {
		this->center.set(0, 0, 0);
		this->radius = -1;
	}

	bool containsPoint(Vec3 point) {
		return (point.distanceToSquared(this->center) <= (this->radius * this->radius));
	}

	float distanceToPoint(Vec3 point) {
		return (point.distanceTo(this->center) - this->radius);
	}

	float intersectsSphere(Sphere sphere) {
		float radiusSum = this->radius + sphere.radius;
		return sphere.center.distanceToSquared(this->center) <= (radiusSum * radiusSum);

	}

	//bool intersectsBox(Box3 box) {
	//	return box.intersectsSphere(*this);
	//}

	// intersectsPlane( plane ) {

	// 	return Math.abs( plane.distanceToPoint( this->center ) ) <= this->radius;

	// }

	Vec3 clampPoint(Vec3 point) {
		Vec3 target;

		float deltaLengthSq = this->center.distanceToSquared(point);

		target.copy(point);

		if (deltaLengthSq > (this->radius * this->radius)) {
			target = target.sub(this->center);
			target = target.normalize();
			target = target.scale(this->radius);
			target = target.add(this->center);
		}

		return target;

	}

	Box3 getBoundingBox() {
		Box3 target;

		if (this->isEmpty()) {
			// Empty sphere produces empty bounding box
			target.makeEmpty();
			return target;
		}

		target.set(this->center, this->center);
		target.expandByScalar(this->radius);

		return target;
	}

	void applyMatrix4Local(Mat& matrix) {
		//this->center.applyMatrix4Local(matrix);
		this->center = matrix.applyToVec3(this->center);
		this->radius = this->radius * matrix.getMaxScaleOnAxis();
	}

	void translate(Vec3 offset) {
		this->center = this->center.add(offset);
	}

	void expandByPoint(Vec3 point) {

		if (this->isEmpty()) {
			this->center.copy(point);
			this->radius = 0;
			return;

		}
		Vec3 _v1 = point.sub(this->center);

		float lengthSq = _v1.lengthSq();

		if (lengthSq > (this->radius * this->radius)) {

			// calculate the minimal sphere

			float length = sqrt(lengthSq);
			float delta = (length - this->radius) * 0.5;

			this->center.addScaledVectorLocal(_v1, delta / length);
			this->radius += delta;
		}

	}

	Sphere* unionSphere(Sphere sphere) {

		if (sphere.isEmpty()) {
			return this;
		}

		if (this->isEmpty()) {
			this->copy(sphere);
			return this;
		}

		if (this->center.equals(sphere.center) == true) {

			this->radius = maxFloat(this->radius, sphere.radius);

		}
		else {
			Vec3 _v2 = sphere.center.sub(this->center);
			_v2.setLength(sphere.radius);

			this->expandByPoint(sphere.center.add(_v2));
			this->expandByPoint(sphere.center.sub(_v2));
		}

		return this;
	}

	bool equals(Sphere sphere) {
		return sphere.center.equals(this->center) && (sphere.radius == this->radius);
	}

	Sphere clone() {
		return *this;
	}
};