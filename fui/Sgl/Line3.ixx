module;
#include "Core/Vec3.h";
#include "Core/Euler.h"
#include "Core/Mat.h"
#include "Core/Quaternion.h"
#include "Core/Plane.h"

export module Sgl:Line3;


export struct Line3 {
	Vec3 start;
	Vec3 end;

	Line3 * set(Vec3 start, Vec3 end) {

		this->start.copy(start);
		this->end.copy(end);

		return this;

	}

	Line3 * copy(Line3 line) {

		this->start.copy(line.start);
		this->end.copy(line.end);

		return this;

	}

	Vec3 getCenter() {
		Vec3 target;
		target.addVectorsLocal(this->start, this->end)->multiplyScalarLocal(0.5);
		return target;

	}

	Vec3 delta() {

		Vec3 target;
		target.subVectorsLocal(this->end, this->start);
		return target;
	}

	float distanceSq() {

		return this->start.distanceToSquared(this->end);

	}

	float distance() {

		return this->start.distanceTo(this->end);

	}

	Vec3 at(float t) {
		Vec3 target = this->delta().multiplyScalarLocal(t)->add(this->start);
		return target;
	}

	float closestPointToPointParameter(Vec3 point, bool clampToLine) {
		Vec3 _startP;
		Vec3 _startEnd;

		_startP.subVectorsLocal(point, this->start);
		_startEnd.subVectorsLocal(this->end, this->start);

		float startEnd2 = _startEnd.dot(_startEnd);
		float startEnd_startP = _startEnd.dot(_startP);

		float t = startEnd_startP / startEnd2;

		if (clampToLine) {
			t = clampFloat(t, 0, 1);
		}

		return t;

	}

	Vec3 closestPointToPoint(Vec3 point, bool clampToLine) {

		float t = this->closestPointToPointParameter(point, clampToLine);

		Vec3 result = this->delta().multiplyScalarLocal(t)->add(this->start);
		return result;
	}

	Line3 * applyMatrix4Local(Mat matrix) {

		this->start.applyMatrix4Local(matrix);
		this->end.applyMatrix4Local(matrix);

		return this;

	}

	bool equals(Line3 line) {

		return line.start.equals(this->start) && line.end.equals(this->end);

	}

	Line3 clone() {
		return *this;

			// return new this->constructor().copy( this );
		}

};