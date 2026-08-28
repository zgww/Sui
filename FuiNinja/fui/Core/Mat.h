#pragma once
#include "Core/Vec3.h"
#include "Core/Euler.h"
#include "Core/Quaternion.h"


class Mat {
public:
	float data[16];
	// void ctor(){
	//     this->identity()
	// }



	Mat* set(float n11, float n12, float n13, float n14, float n21, float n22, float n23, float n24, float n31, float n32, float n33, float n34, float n41, float n42, float n43, float n44);

	Mat* identity();

	Mat clone();

	Mat* copy(Mat m);

	Mat* copyPosition(Mat m);

	//Mat* setFromMatrix3(Mat3 m) {

	//	float* me = m.data;

	//	this->set(

	//		me[0], me[3], me[6], 0,
	//		me[1], me[4], me[7], 0,
	//		me[2], me[5], me[8], 0,
	//		0, 0, 0, 1

	//	);

	//	return this;

	//}

	// 提取y轴旋转矩阵.适用于相机xz漫游
	Mat extractYRotationMatrix();


	Mat* extractBasis(Vec3* xAxis, Vec3* yAxis, Vec3* zAxis);


	Vec3 mkVec3FromMatrixColumn(int index);

	Mat* makeBasis(Vec3 xAxis, Vec3 yAxis, Vec3 zAxis);

	Mat* extractRotationLocal(Mat m);

	Mat* makeRotationFromEuler(Euler& euler);

	Mat* makeRotationFromQuaternion(Quaternion q);

	Quaternion toQuaternionAsRotationMatrix();

	//只考虑旋转
	Mat* lookAtLocal(Vec3 eye, Vec3 target, Vec3 up);

	Mat* multiplyLocal(Mat m);

	Mat* premultiplyLocal(Mat m);

	Mat* multiplyMatricesLocal(Mat a, Mat b);

	Mat* multiplyScalarLocal(float s);

	float determinant();

	Mat* transposeLocal();

	Mat* setPosition(float x, float y, float z);

	Mat* invertLocal();

	Mat* scaleVec3(Vec3 v);

	float getMaxScaleOnAxis();

	Mat* makeTranslation(float x, float y, float z);

	Mat* makeRotationX(float theta);

	Mat* makeRotationY(float theta);

	Mat* makeRotationZ(float theta);

	Mat* makeRotationAxis(Vec3 axis, float angle);

	Mat* makeScale(float x, float y, float z);

	Mat* makeShear(float xy, float xz, float yx, float yz, float zx, float zy);

	Mat* compose(Vec3 position, Quaternion& quaternion, Vec3 scale);
	Mat* decompose(Vec3* position, Quaternion* quaternion, Vec3* scale);



	Mat* makePerspective(float left, float right, float top, float bottom, float near, float far);

	Mat* makeOrthographic(float left, float right, float top, float bottom, float near, float far);

	bool equals(Mat matrix);

	Mat* fromArray(float* array, int offset);

	float* toArray(float* array, int offset);




	Vec3 applyToVec3(Vec3 self);




	Vec3 transformDirection(Vec3 self);








	//转为euler
	Vec3 rotationMatrixToEulerXYZ();
	//void identity() {
	//	// mat4x4 m = (mat4x4)this->data;
	//	mat4x4_identity((void*)this->data);
	//}
	void rotateX(float angle);
	// void copyFrom(Mat *m){
	//     mat4x4_dup((void*)this->data, (void*)m.data)
	// }
	// Mat clone(){
	//     Mat m;
	//     m.copyFrom(this)
	//     return m
	// }
	void rotateY(float angle);
	void rotateZ(float angle);
	void rotate(float x, float y, float z, float angle);
	void scale(float x, float y, float z);
	// void transpose(){
	//     mat4x4 bk;
	//     mat4x4_dup((void*)bk, (void*)this->data)
	//     mat4x4_transpose((void*)this->data, (void*)bk);
	// }
	void setTranslate(float x, float y, float z);
	void translate(float x, float y, float z);
	Mat invert();
	void invertthis();
	void frustum(float left, float right, float bottom, float top, float near, float far);
	void ortho(float left, float right, float bottom, float top, float near, float far);
	void perspective(float y_fov, float aspect, float near, float far);
	void mul(Mat* a, Mat* b);
	void lookAtFake(Vec3 eye, Vec3 center, Vec3 up);
	Vec3 mulVec3(Vec3 v);
	Vec4 mulVec4(Vec4 v);

};
Mat mkMatIdentity();