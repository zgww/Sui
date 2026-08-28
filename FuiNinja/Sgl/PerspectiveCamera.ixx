module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Naga/TimeUtil.h"
#include "Core/Vec2.h"
#include "Core/Vec3.h"
#include "Naga/Path.h"

export module Sgl:PerspectiveCamera;

import :Camera;




export class PerspectiveCamera :public Camera {
public:

	//相机投影矩阵的相关参数
	float fov = 45 / 180.0 * PI; // y_fov
	float aspect = 1.0;
	float nearPlane = 300.1;
	float farPlane = 500;

	// 视角的相关参数
	Vec3 target = mkVec3(0, 0, 0);
	// Vec3 up = mkVec3(0, 1, 0)

	// Mat view;//视图矩阵
	// Mat projection;//投影矩阵


	//构建投影矩阵
	void updateProjectionMat() {
		this->projection.perspective(
			this->fov,
			this->aspect,
			this->nearPlane,
			this->farPlane
		);
		// 45 / 180.0 * 3.1415926, 1.0, 0.1, 10000)
	}

	//更新视图矩阵
	void updateViewMat() {
		// Vec3 eye = this->localToWorld(mkVec3(0, 0, 0))
		// //旋转矩阵
		// Mat t
		// t.lookAtLocal(eye, this->target, this->up)
		// t.setPosition(
		//     this->position.x,
		//     this->position.y,
		//     this->position.z,
		// )

		// Quaternion q
		// q.setFromRotationMatrix(t)

		// this->view = t;
		// this->view.invertLocal()

		//view矩阵就是相机模型矩阵的逆矩阵
		this->updateWorldMatrixUptoRoot();
		this->view.copy(this->_world_transform)->invertLocal();

		// this->view = this->_world_transform
		// //view矩阵即camera模型矩阵的逆矩阵
		// this->view.invertLocal()

		// Mat rot
		// rot.lookAtLocal(
		//     worldPos,
		//     this->target,
		//     this->up);

		// Euler euler
		// euler.setFromRotationMatrix(rot, null)

		// this->rotation.setFromEuler(euler)

		// Mat t
		// t.makeTranslation(
		//     this->position.x,
		//     this->position.y,
		//     this->position.z,
		//     )
		// Mat s
		// s.makeScale(
		//     this->scale.x,
		//     this->scale.y,
		//     this->scale.z,
		// )
		// Mat sr
		// // view = t * s * r
		// sr.multiplyMatricesLocal(s, rot)
		// // this->view.multiplyMatricesLocal(t, sr)
		// this->updateTransform()
		// this->view = this->transform


		// this->view
		//     .lookAtFake(
		//     worldPos,
		//     this->target,
		//     this->up);

			// mkVec3(0, -1000, 2000), mkVec3(0, 0, 0), mkVec3(0, 0, 1))
	}
	void moveForward() {
		float step = 10;
		Vec3 worldPos = this->localToWorld(mkVec3(0, 0, 0));
		Vec3 viewDir = this->target.sub(worldPos);
		viewDir = viewDir.normalize();
		viewDir = viewDir.scale(step);

		Vec3 newWorldPos = worldPos.add(viewDir);
		this->position = newWorldPos;
		this->target = this->target.add(viewDir);
	}
	void moveBackward() {
		float step = 10;
		Vec3 worldPos = this->localToWorld(mkVec3(0, 0, 0));
		Vec3 viewDir = this->target.sub(worldPos);
		viewDir = viewDir.normalize();
		viewDir = viewDir.scale(-1 * step);

		Vec3 newWorldPos = worldPos.add(viewDir);
		this->position = newWorldPos;
		this->target = this->target.add(viewDir);
	}

	void rotateLeft() {
		this->_world_transform = this->view.invert();
		Vec3 localTarget = this->worldToLocal(this->target);
		Mat rot;
		rot.identity();
		rot.rotateY(1.1 / 180.0 * PI);

		Vec3 newLocalTarget = rot.mulVec3(localTarget);
		Vec3 newTarget = this->localToWorld(newLocalTarget);
		this->target = newTarget;

	}
	void rotateRight() {
		this->_world_transform = this->view.invert();
		Vec3 localTarget = this->worldToLocal(this->target);
		Mat rot;;
		rot.identity();
		rot.rotateY(-1.1 / 180.0 * PI);

		Vec3 newLocalTarget = rot.mulVec3(localTarget);
		Vec3 newTarget = this->localToWorld(newLocalTarget);
		this->target = newTarget;
	}
	void rise() {
		this->position.y += 10;
	}
	void fall() {
		this->position.y -= 10;
	}
	Ray mkRay(Vec2 ndcPos) {
		Ray r;
		r.origin.setFromMatrixPosition(this->_world_transform);

		Vec3 wp = this->unproject(
			mkVec3(ndcPos.x, ndcPos.y, 0.5)
		);
		Vec3 dir = wp.sub(r.origin);
		r.direction = dir.normalize();

		// r.direction.set( ndcPos.x, ndcPos.y, 0.5 ) 
			// .unproject( camera ).sub( this.ray.origin ).normalize();
		return r;
	}

};