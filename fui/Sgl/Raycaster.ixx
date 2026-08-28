module;
#include "Core/Vec3.h";
#include "Core/Euler.h"
#include "Core/Mat.h"
#include "Core/Quaternion.h"
#include "Core/Plane.h"

export module Sgl:Raycaster;


import :Obj3d;
import :Geometry;
import :Ray;

export struct RayCheckResult {
	bool succ;
	float distance;
	Vec3 point;
	Obj3d* obj;
	const char* desc;
};
export RayCheckResult mkRayCheckResultFail() {
	RayCheckResult r;
	memset(&r, 0, sizeof(RayCheckResult));
	return r;
}

//光线投射,用来做hitTest
export class Raycaster : public GcObj {
public:
	float nearDistance = 1;
	float farDistance = 10000;
	Ray ray;

	//存放结果
	RayCheckResult result;

	RayCheckResult raycastTree(Obj3d* root) {
		//重置
		this->result = mkRayCheckResultFail();

		this->raycastNode(root);
		// root.walkIf(this->_raycastNode, self)
		return this->result;
	}
	bool raycastNode(Node* n) {
		if  (dynamic_cast<Obj3d*>(n))  {
			Obj3d* obj3d = (Obj3d*)n;
			if (obj3d->hitTestSelfByRaycaster(this)) { //成功
				return true;
			}
			for (int i = 0, l = n->getChildrenCount(); i < l; i++) {
				Node* kid = (Node*)n->getChild(i);
				if (this->raycastNode(kid)) {//有成功的，就直接退出raycast
					return true;
				}
			}
		}
		return false;
	}


	// 取交点
	RayCheckResult checkIntersection(Obj3d* obj, Ray localRay, Vec3 pA, Vec3 pB, Vec3 pC) {

		IntersectResult intersect;

		// if ( material.side === BackSide ) {

		//     intersect = ray.intersectTriangle( pC, pB, pA, true, point );

		// } else {

		intersect = localRay.intersectTriangle(pA, pB, pC, false);//( material.side === FrontSide ));

			// }

			if (!intersect.succ) {
				return mkRayCheckResultFail();
			}

		Vec3 _intersectionPointWorld;

		_intersectionPointWorld.copy(intersect.point);
		_intersectionPointWorld.applyMatrix4Local(obj->_world_transform);

		float distance = this->ray.origin.distanceTo(_intersectionPointWorld);

		if (distance < this->nearDistance || distance > this->farDistance) {
			return mkRayCheckResultFail();
		}


		RayCheckResult r;
		memset(&r, 0, sizeof(RayCheckResult));

		r.succ = true;
		r.distance = distance;
		r.point = _intersectionPointWorld;
		r.obj = obj;
		return r;
	}


	RayCheckResult raycastGeometry(Obj3d* obj, Geometry* geom) {
		if (geom == nullptr || geom->ibo == nullptr){
			return mkRayCheckResultFail();
		}
		GeoAttr* positionAttr = geom->getAttr("position");
		if (positionAttr == nullptr){
			auto o = mkRayCheckResultFail();
			o.desc = "no positionAttr";
			return o;
		}
		auto & buf = positionAttr->vbo->buf;
		if (buf->size == 0){
			auto o = mkRayCheckResultFail();
				o.desc = "no positionAttr.vbo.buf";
				return o;
		}
		auto idxBuf = geom->ibo->buf;
		if (idxBuf->size == 0){
			auto o = mkRayCheckResultFail();
			o.desc = "no ibo.buf";
			return o;
		}

		int indexCount = geom->ibo->calcIndexCount();
		// 只支持triangles. 三点成面
		if (indexCount % 3 != 0) {
			RayCheckResult r = mkRayCheckResultFail();
			r.desc = "invalid indexCount";
			return r;
		}

		int* indexInts = (int* )idxBuf->data;
		float* vtxFloats = (float*)buf->data;
		Vec3 a;
		Vec3 b;
		Vec3 c;
		Ray localRay = this->ray;
		localRay.applyMatrix4Local(obj->_world_transform.invert());

		for (int i = 0; i < indexCount; i += 3) {
			int indexA = indexInts[i];
			int indexB = indexInts[i + 1];
			int indexC = indexInts[i + 2];

			a.fromArray(vtxFloats, indexA * 3);
			b.fromArray(vtxFloats, indexB * 3);
			c.fromArray(vtxFloats, indexC * 3);

			RayCheckResult r = this->checkIntersection(obj, localRay, a, b, c);
			if (r.succ) {
				return r;
			}
		}

		auto ret = mkRayCheckResultFail();
		// o.desc = "no ibo.buf";
		return ret;
	}

};
