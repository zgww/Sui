
typedef struct tagSuiCore$Mat3 SuiCore$Mat3;


#ifndef define_struct___SuiCore__Mat3_orc_h__
#define define_struct___SuiCore__Mat3_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Mat3_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Mat3_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Mat3 {
	float  data[9] ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Mat3_orc_h__
#define __SuiCore__Mat3_orc_h__

//include  importHeadCode
#include "../../Orc/Math_orc.h"
#include "./Vec3_orc.h"
#include "../../Sgl/Mat_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Mat3_getOrInitMetaStruct();

SuiCore$Mat3 *  SuiCore$Mat3$set(SuiCore$Mat3 *  self, float  n11, float  n12, float  n13, float  n21, float  n22, float  n23, float  n31, float  n32, float  n33);
SuiCore$Mat3 *  SuiCore$Mat3$identity(SuiCore$Mat3 *  self);
SuiCore$Mat3 *  SuiCore$Mat3$copy(SuiCore$Mat3 *  self, SuiCore$Mat3 m);
SuiCore$Mat3 *  SuiCore$Mat3$extractBasis(SuiCore$Mat3 *  self, SuiCore$Vec3 xAxis, SuiCore$Vec3 yAxis, SuiCore$Vec3 zAxis);
SuiCore$Mat3 *  SuiCore$Mat3$setFromMatrix4(SuiCore$Mat3 *  self, Sgl$Mat m);
SuiCore$Mat3 *  SuiCore$Mat3$multiplyLocal(SuiCore$Mat3 *  self, SuiCore$Mat3 m);
SuiCore$Mat3 *  SuiCore$Mat3$premultiplyLocal(SuiCore$Mat3 *  self, SuiCore$Mat3 m);
SuiCore$Mat3 *  SuiCore$Mat3$multiplyMatricesLocal(SuiCore$Mat3 *  self, SuiCore$Mat3 a, SuiCore$Mat3 b);
SuiCore$Mat3 *  SuiCore$Mat3$multiplyScalarLocal(SuiCore$Mat3 *  self, float  s);
float  SuiCore$Mat3$determinant(SuiCore$Mat3 *  self);
SuiCore$Mat3 *  SuiCore$Mat3$invertLocal(SuiCore$Mat3 *  self);
SuiCore$Mat3 *  SuiCore$Mat3$transposeLocal(SuiCore$Mat3 *  self);
SuiCore$Mat3 *  SuiCore$Mat3$getNormalMatrix(SuiCore$Mat3 *  self, Sgl$Mat matrix4);
SuiCore$Mat3 *  SuiCore$Mat3$transposeIntoArray(SuiCore$Mat3 *  self, float *  r);
SuiCore$Mat3 *  SuiCore$Mat3$setUvTransform(SuiCore$Mat3 *  self, float  tx, float  ty, float  sx, float  sy, float  rotation, float  cx, float  cy);
SuiCore$Mat3 *  SuiCore$Mat3$scaleLocal(SuiCore$Mat3 *  self, float  sx, float  sy);
SuiCore$Mat3 *  SuiCore$Mat3$rotateLocal(SuiCore$Mat3 *  self, float  theta);
SuiCore$Mat3 *  SuiCore$Mat3$translateLocal(SuiCore$Mat3 *  self, float  tx, float  ty);
SuiCore$Mat3 *  SuiCore$Mat3$makeTranslation(SuiCore$Mat3 *  self, float  x, float  y);
SuiCore$Mat3 *  SuiCore$Mat3$makeRotation(SuiCore$Mat3 *  self, float  theta);
SuiCore$Mat3 *  SuiCore$Mat3$makeScale(SuiCore$Mat3 *  self, float  x, float  y);
bool  SuiCore$Mat3$equals(SuiCore$Mat3 *  self, SuiCore$Mat3 matrix);
SuiCore$Mat3 *  SuiCore$Mat3$fromArray(SuiCore$Mat3 *  self, float *  array, int  offset);
SuiCore$Mat3 *  SuiCore$Mat3$toArray(SuiCore$Mat3 *  self, float *  array, int  offset);
SuiCore$Mat3 SuiCore$Mat3$clone(SuiCore$Mat3 *  self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
