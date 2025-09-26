
typedef struct tagSgl$Mat Sgl$Mat;


#ifndef define_struct___Sgl__Mat_orc_h__
#define define_struct___Sgl__Mat_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Mat_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Sui/Core/linmath.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__Mat_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$Mat {
	float  data[16] ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Mat_orc_h__
#define __Sgl__Mat_orc_h__

//include  importHeadCode
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Mat3_orc.h"
#include "../Sui/Core/Euler_orc.h"
#include "../Sui/Core/Quaternion_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Sgl$Mat_getOrInitMetaStruct();

Sgl$Mat Sgl$mkMatIdentity();
Sgl$Mat *  Sgl$Mat$set(Sgl$Mat *  self, float  n11, float  n12, float  n13, float  n14, float  n21, float  n22, float  n23, float  n24, float  n31, float  n32, float  n33, float  n34, float  n41, float  n42, float  n43, float  n44);
Sgl$Mat Sgl$Mat$clone(Sgl$Mat *  self);
Sgl$Mat *  Sgl$Mat$copy(Sgl$Mat *  self, Sgl$Mat m);
Sgl$Mat *  Sgl$Mat$copyPosition(Sgl$Mat *  self, Sgl$Mat m);
Sgl$Mat *  Sgl$Mat$setFromMatrix3(Sgl$Mat *  self, SuiCore$Mat3 m);
Sgl$Mat *  Sgl$Mat$extractBasis(Sgl$Mat *  self, SuiCore$Vec3 *  xAxis, SuiCore$Vec3 *  yAxis, SuiCore$Vec3 *  zAxis);
Sgl$Mat *  Sgl$Mat$makeBasis(Sgl$Mat *  self, SuiCore$Vec3 xAxis, SuiCore$Vec3 yAxis, SuiCore$Vec3 zAxis);
Sgl$Mat *  Sgl$Mat$extractRotationLocal(Sgl$Mat *  self, Sgl$Mat m);
Sgl$Mat *  Sgl$Mat$makeRotationFromEuler(Sgl$Mat *  self, SuiCore$Euler euler);
Sgl$Mat *  Sgl$Mat$makeRotationFromQuaternion(Sgl$Mat *  self, SuiCore$Quaternion q);
Sgl$Mat *  Sgl$Mat$lookAtLocal(Sgl$Mat *  self, SuiCore$Vec3 eye, SuiCore$Vec3 target, SuiCore$Vec3 up);
Sgl$Mat *  Sgl$Mat$multiplyLocal(Sgl$Mat *  self, Sgl$Mat m);
Sgl$Mat *  Sgl$Mat$premultiplyLocal(Sgl$Mat *  self, Sgl$Mat m);
Sgl$Mat *  Sgl$Mat$multiplyMatricesLocal(Sgl$Mat *  self, Sgl$Mat a, Sgl$Mat b);
Sgl$Mat *  Sgl$Mat$multiplyScalarLocal(Sgl$Mat *  self, float  s);
float  Sgl$Mat$determinant(Sgl$Mat *  self);
Sgl$Mat *  Sgl$Mat$transposeLocal(Sgl$Mat *  self);
Sgl$Mat *  Sgl$Mat$setPosition(Sgl$Mat *  self, float  x, float  y, float  z);
Sgl$Mat *  Sgl$Mat$invertLocal(Sgl$Mat *  self);
Sgl$Mat *  Sgl$Mat$scaleVec3(Sgl$Mat *  self, SuiCore$Vec3 v);
float  Sgl$Mat$getMaxScaleOnAxis(Sgl$Mat *  self);
Sgl$Mat *  Sgl$Mat$makeTranslation(Sgl$Mat *  self, float  x, float  y, float  z);
Sgl$Mat *  Sgl$Mat$makeRotationX(Sgl$Mat *  self, float  theta);
Sgl$Mat *  Sgl$Mat$makeRotationY(Sgl$Mat *  self, float  theta);
Sgl$Mat *  Sgl$Mat$makeRotationZ(Sgl$Mat *  self, float  theta);
Sgl$Mat *  Sgl$Mat$makeRotationAxis(Sgl$Mat *  self, SuiCore$Vec3 axis, float  angle);
Sgl$Mat *  Sgl$Mat$makeScale(Sgl$Mat *  self, float  x, float  y, float  z);
Sgl$Mat *  Sgl$Mat$makeShear(Sgl$Mat *  self, float  xy, float  xz, float  yx, float  yz, float  zx, float  zy);
Sgl$Mat *  Sgl$Mat$compose(Sgl$Mat *  self, SuiCore$Vec3 position, SuiCore$Quaternion quaternion, SuiCore$Vec3 scale);
Sgl$Mat *  Sgl$Mat$decompose(Sgl$Mat *  self, SuiCore$Vec3 *  position, SuiCore$Quaternion *  quaternion, SuiCore$Vec3 *  scale);
Sgl$Mat *  Sgl$Mat$makePerspective(Sgl$Mat *  self, float  left, float  right, float  top, float  bottom, float  near, float  far);
Sgl$Mat *  Sgl$Mat$makeOrthographic(Sgl$Mat *  self, float  left, float  right, float  top, float  bottom, float  near, float  far);
bool  Sgl$Mat$equals(Sgl$Mat *  self, Sgl$Mat matrix);
Sgl$Mat *  Sgl$Mat$fromArray(Sgl$Mat *  self, float *  array, int  offset);
float *  Sgl$Mat$toArray(Sgl$Mat *  self, float *  array, int  offset);
SuiCore$Vec3 Sgl$Mat$rotationMatrixToEulerXYZ(Sgl$Mat *  self);
void  Sgl$Mat$identity(Sgl$Mat *  self);
void  Sgl$Mat$rotateX(Sgl$Mat *  self, float  angle);
void  Sgl$Mat$rotateY(Sgl$Mat *  self, float  angle);
void  Sgl$Mat$rotateZ(Sgl$Mat *  self, float  angle);
void  Sgl$Mat$rotate(Sgl$Mat *  self, float  x, float  y, float  z, float  angle);
void  Sgl$Mat$scale(Sgl$Mat *  self, float  x, float  y, float  z);
void  Sgl$Mat$setTranslate(Sgl$Mat *  self, float  x, float  y, float  z);
void  Sgl$Mat$translate(Sgl$Mat *  self, float  x, float  y, float  z);
Sgl$Mat Sgl$Mat$invert(Sgl$Mat *  self);
void  Sgl$Mat$invertSelf(Sgl$Mat *  self);
void  Sgl$Mat$frustum(Sgl$Mat *  self, float  left, float  right, float  bottom, float  top, float  near, float  far);
void  Sgl$Mat$ortho(Sgl$Mat *  self, float  left, float  right, float  bottom, float  top, float  near, float  far);
void  Sgl$Mat$perspective(Sgl$Mat *  self, float  y_fov, float  aspect, float  near, float  far);
void  Sgl$Mat$mul(Sgl$Mat *  self, Sgl$Mat *  a, Sgl$Mat *  b);
void  Sgl$Mat$lookAtFake(Sgl$Mat *  self, SuiCore$Vec3 eye, SuiCore$Vec3 center, SuiCore$Vec3 up);
SuiCore$Vec3 Sgl$Mat$mulVec3(Sgl$Mat *  self, SuiCore$Vec3 v);
SuiCore$Vec4 Sgl$Mat$mulVec4(Sgl$Mat *  self, SuiCore$Vec4 v);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
