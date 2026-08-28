module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Vec2.h"
#include "Core/Vec3.h"
#include "Core/Mat.h"
#include "Core/Euler.h"
#include "Core/Quaternion.h"
#include "Core/Node.h"
#include "Core/Canvas.h"
#include "Core/Image.h"
#include "Naga/Path.h"

#define NANOVG_GL3
#include "nanovg/nanovg_gl.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "nanovg/stb_image_write.h"

#include <vector>

export module Sgl:Obj3d;


export class DrawCtx;
export class Raycaster;

export class Obj3d : public Node {
public:
	std::string objid;
	Vec3 position;
	Vec3 rotation; // euler
	Vec3 scale = mkVec3(1.0, 1.0, 1);

	Rgba rgba = mkRgbaByInt(0xffff0000);
	int textColor = 0xff00ff00;

	Quaternion quaternion;

	Vec3 _viewPosition;

	Vec3 up = mkVec3(0, 1, 0);


	Mat transform = mkMatIdentity();
	Mat _world_transform = mkMatIdentity();

	bool visible = true;

	std::string gocId() {
		if (this->objid == "") {
			this->objid = ("");
			this->objid += ((long long)this);
		}
		return this->objid;
	}

	Vec3 worldToLocal(Vec3 v3) {
		Vec4 v4 = mkVec4(v3.x, v3.y, v3.z, 1.0);
		Mat inv = this->_world_transform.invert();
		Vec4 ret = inv.mulVec4(v4);
		return mkVec3(ret.x, ret.y, ret.z);
	}

	Vec3 localToWorld(Vec3 v3) {
		Vec4 v4 = mkVec4(v3.x, v3.y, v3.z, 1.0);
		Vec4 ret = this->_world_transform.mulVec4(v4);
		return mkVec3(ret.x, ret.y, ret.z);
	}

	void updateTransform() {
		// this->transform.identity()
		// this->transform.makeTranslation(this->position.x, this->position.y, this->position.z)
		// // this->transform.setTranslate(this->position.x, this->position.y, this->position.z)
		// this->transform.scale(this->scale.x, this->scale.y, this->scale.z)
		// this->transform.rotateX(this->rotation.x)
		// this->transform.rotateY(this->rotation.y)
		// this->transform.rotateZ(this->rotation.z)


		Quaternion q;
		Euler e;
		e.set(this->rotation.x, this->rotation.y, this->rotation.z,
			"XYZ"
			// "YXZ"
		);
		q.setFromEuler(e);

		this->transform.compose(this->position, q, this->scale);
	}

	//更新子树矩阵
	void updateWorldTransformAndSubtree() {
		//更新transform
		this->updateTransform();
		// this->transform.identity()
		// this->transform.setTranslate(this->position.x, this->position.y, this->position.z)
		// this->transform.scale(this->scale.x, this->scale.y, this->scale.z)
		// this->transform.rotateX(this->rotation.x)
		// this->transform.rotateY(this->rotation.y)
		// this->transform.rotateZ(this->rotation.z)



		if (this->parent && dynamic_cast<Obj3d*>(this->parent.get())) {
			Obj3d* p = (Obj3d*)this->parent.get();
			this->_world_transform.mul(
				&p->_world_transform,
				&this->transform
			);
		}
		else {
			this->_world_transform = this->transform;
		}
		// Vec3 wpos = this->localToWorld(mkVec3(0, 0, 0))

		this->updateChildrenWorldTransform();
	}
	void updateChildrenWorldTransform() {
		int l = this->getChildrenCount();
		for (int i = 0; i < l; i++) {
			Node* view = this->getChild(i);
			if (dynamic_cast<Obj3d*>(view)) {
				Obj3d* obj = (Obj3d*)view;
				if (obj->visible) { //&& view->style.display != DISPLAY_TYPE_NONE) {
					obj->updateWorldTransformAndSubtree();
				}
			}
		}
	}

	 //收集
	 void collectTransparent(DrawCtx *ctx){
	 }

	//void drawDepth(DrawCtx* ctx) {
	//}
	void draw(DrawCtx* ctx) {
		this->drawSelf(ctx);
		this->drawChildren(ctx);
	}
	//在draw中，如果发现material需要在transparent中绘制，就可以调用ctx的方法加入到transparentList中
	void drawTransparent(DrawCtx* ctx) {
		this->drawSelf(ctx);
	}

	//void drawSelfRaw(DrawCtx* ctx, Vao* vao, Material* matl) {
	//}
	void drawSelf(DrawCtx* ctx) {
	}
	void drawChildren(DrawCtx* ctx) {
		int l = this->getChildrenCount();
		for (int i = 0; i < l; i++) {
			Node* view = this->getChild(i);
			if (dynamic_cast<Obj3d*>(view)) {
				Obj3d* obj = (Obj3d*)view;
				if (obj->visible) { //&& view->style.display != DISPLAY_TYPE_NONE) {
					obj->draw(ctx);
				}
			}
		}
	}
	void tick(DrawCtx* ctx) {
	}
	//结果放到raycaster.result中
	bool hitTestSelfByRaycaster(Raycaster* raycaster) {
		return false;
	}

	// 令正z轴朝向目标位置
	void lookAt(float x, float y, float z) {
		this->lookAtByDir(false, x, y, z);
	}

	void translateWorldPosition(Vec3 delta) {
		Vec3 wp = this->localToWorld(mkVec3(0, 0, 0));
		wp.addLocal(delta);
		this->setWorldPosition(wp);
	}
	void setWorldPosition(Vec3 v3) {
		Obj3d* p = this->getParentObj3d();
		if (p) {
			this->position = p->worldToLocal(v3);
		}
		else {
			this->position = v3;
		}
	}
	Obj3d* getParentObj3d() {
		if (dynamic_cast<Obj3d*>(this->parent.get())) {
			return (Obj3d*)this->parent.get();
		}
		return nullptr;
	}
	//本地方向矢量转世界坐标下的方向矢量
	//只应用旋转
	Vec3 applyRotationToVec3(Vec3 v3) {
		Mat rot;
		rot.extractRotationLocal(this->_world_transform);
		Vec3 ret = v3.applyMatrix4(rot);
		return ret;
	}

	//更新世界矩阵，从自己到根结点
	void updateWorldMatrixUptoRoot() {
		this->updateTransform();

		Obj3d* parent = (Obj3d*)this->parent.get();
		if (parent != nullptr && dynamic_cast<Obj3d*>(parent)) {
			parent->updateWorldMatrixUptoRoot();
			this->_world_transform.multiplyMatricesLocal(parent->_world_transform, this->transform);
		}
		else {//说明自己就是根
			this->_world_transform.copy(this->transform);
		}
	}

	// 相机以负轴为前方，需要negativeZ=true
	// 普通的obj以正轴为前方
	void lookAtByDir(bool negativeZ, float x, float y, float z) {
		Obj3d* parent = (Obj3d*)this->parent.get();
		if (parent != nullptr && !(dynamic_cast<Obj3d*>(parent))) {
			return;
		}

		// this->updateWorldMatrix( true, false );

		Vec3 _target = mkVec3(x, y, z);
		Vec3 _position;
		_position.setFromMatrixPosition(this->_world_transform);
		Mat _m1;

		if (negativeZ) { // ( this.isCamera || this.isLight ) {

			_m1.lookAtLocal(_position, _target, this->up);

		}
		else {

			//注意eye和目标点的位置。
			_m1.lookAtLocal(_target, _position, this->up);

		}

		this->quaternion.setFromRotationMatrix(_m1);

		if (parent) {
			Quaternion _q1;

			_m1.extractRotationLocal(parent->_world_transform);
			_q1.setFromRotationMatrix(_m1);
			this->quaternion.premultiplyLocal(*_q1.invertLocal());

		}
		Euler euler;
		euler.setFromQuaternion(this->quaternion, Euler_Default);
		this->rotation.setFromEuler(euler);
	}
};