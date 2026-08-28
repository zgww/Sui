module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Core/Mat.h"
#include "View/ImageView.h"
#include "View/Drag.h"
#include "Naga/Path.h"
#include "Naga/StrUtil.h"

export module Sgl:Bone;

import :Obj3d;
import :Buffer;

class Skeleton;

struct CalcData {
	Skeleton* skeleton;
	int index;
};
static bool _walkBoneIf_toCalcBoneMatrix(CalcData* calcData, Node* n);

//用于骨骼动画
export class Bone :public Obj3d {
public:
	Vec3 originPosition; // mdx动画记录的是相对位移

	// 动画矩阵，是每帧计算的. 不能直接用_world_transform. 因为动画矩阵是相对于模型空间的,不是相对于世界的
	Mat animMatrix = mkMatIdentity(); //当前帧的变换矩阵
	//绑定矩阵，是在创建时计算好的
	Mat bindPose = mkMatIdentity();//绑定矩阵的逆矩阵
	//绑定矩阵的逆，是在创建时计算好的
	Mat bindMatrixInverse = mkMatIdentity();//绑定矩阵的逆矩阵
	// 两个矩阵的乘就是offsetMatrix,要传到shader中的

	//最终每个骨骼的offsetMatrix是要放入uniform mat boneMatrix[20]中的， index就是对应的这个数组的下标
	int index = -1;//-1 表示未分配index

	// //mdx要用的属性
	int parentId;
	int id;

	void drawSelf(DrawCtx* ctx) {
		Obj3d* p = (Obj3d*)this->parent.get();
		if (dynamic_cast<Obj3d*>(p)) {
			Vec3 f = p->localToWorld(mkVec3(0, 0, 0));
			Vec3 t = p->localToWorld(this->position);
			//绘制骨骼
			//auto& o = *ctx->lineGeometry;
			//    o.color = 0xff00ff00;

			//    o.moveTo(f.x, f.y, f.z);
			//    // o.color = 0xff0000ff
			//    o.lineTo_color(t.x, t.y, t.z, 0xff0000ff);
		}
	}
};

export class Skeleton : public Obj3d {
public:
	Ref<MatArray> offsetMatrixArray{ new MatArray() };


	void calcBoneMatrixArray() {
		this->offsetMatrixArray->clear();
		CalcData calcData;
		calcData.index = 0;
		calcData.skeleton = this;

		this->walkIf([=](void* calcData, Node* n) {
			return _walkBoneIf_toCalcBoneMatrix((CalcData*)calcData, n);
			}, &calcData);
	}
	void tick(DrawCtx* ctx) {
		this->calcBoneMatrixArray();
	}
};
//遍历skeleton子树,计算offsetMatrix,并附加到Skeleton.offsetMatrixArray
static bool _walkBoneIf_toCalcBoneMatrix(CalcData* calcData, Node* n) {
	if (dynamic_cast<Bone*>(n)) {
		Bone* bone = (Bone*)n;
		bone->index = calcData->index;
		calcData->index++;


		//计算骨骼矩阵
		Mat modelMatrix;

		bone->updateTransform();
		if (dynamic_cast<Bone*>(n->parent.get())) {//上级不是骨骼
			Bone* parentBone = bone->parent.dy_cast<Bone*>();
			modelMatrix.mul(&parentBone->animMatrix, &bone->transform);
		}
		else { //乘父骨骼的矩阵
			modelMatrix = bone->transform;
		}
		bone->animMatrix = modelMatrix;

		Mat offsetMatrix;
		offsetMatrix.mul(&modelMatrix, &bone->bindMatrixInverse);

		// calcData.skeleton.offsetMatrixArray.add(offsetMatrix)
		calcData->skeleton->offsetMatrixArray->set(bone->id, offsetMatrix);
		// printf("bone %s:%d, index:%d\n", bone.name.str, bone.id, bone.index);

		return true;
	}
	if (dynamic_cast<Skeleton*>(n)) {
		return true;
	}
	return false;
};