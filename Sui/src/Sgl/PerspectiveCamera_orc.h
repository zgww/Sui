
typedef struct tagSgl$PerspectiveCamera Sgl$PerspectiveCamera;
typedef struct tagVtable_Sgl$PerspectiveCamera Vtable_Sgl$PerspectiveCamera;


#ifndef define_struct___Sgl__PerspectiveCamera_orc_h__
#define define_struct___Sgl__PerspectiveCamera_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__PerspectiveCamera_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__PerspectiveCamera_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__PerspectiveCamera_orc_h__
#define __Sgl__PerspectiveCamera_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Euler_orc.h"
#include "../Sui/Core/Quaternion_orc.h"
#include "../Orc/Math_orc.h"
#include "./Camera_orc.h"
#include "./Mat_orc.h"
#include "./Ray_orc.h"
#include "./Obj3d_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$PerspectiveCamera {
	Vtable_Sgl$Camera super;
};
//虚表实例
extern Vtable_Sgl$PerspectiveCamera _vtable_Sgl$PerspectiveCamera;

// class refc:0
struct tagSgl$PerspectiveCamera {
	Sgl$Camera super; 
	float  fov ;
	float  aspect ;
	float  nearPlane ;
	float  farPlane ;
	SuiCore$Vec3 target ;
	void  (*moveForward) (Sgl$PerspectiveCamera *  self);
	void  (*moveBackward) (Sgl$PerspectiveCamera *  self);
	void  (*rotateLeft) (Sgl$PerspectiveCamera *  self);
	void  (*rotateRight) (Sgl$PerspectiveCamera *  self);
	void  (*rise) (Sgl$PerspectiveCamera *  self);
	void  (*fall) (Sgl$PerspectiveCamera *  self);
};
Vtable_Sgl$PerspectiveCamera* Vtable_Sgl$PerspectiveCamera_init(Vtable_Sgl$PerspectiveCamera* pvt);
void Sgl$PerspectiveCamera_init_fields(Sgl$PerspectiveCamera *self);
void Sgl$PerspectiveCamera_init(Sgl$PerspectiveCamera *self, void *pOwner);
Sgl$PerspectiveCamera * Sgl$PerspectiveCamera_new(void *pOwner);
void Sgl$PerspectiveCamera_fini(Sgl$PerspectiveCamera *self);

void  Sgl$PerspectiveCamera$updateProjectionMat(Sgl$PerspectiveCamera *  self);
void  Sgl$PerspectiveCamera$updateViewMat(Sgl$PerspectiveCamera *  self);
void  Sgl$PerspectiveCamera$moveForward(Sgl$PerspectiveCamera *  self);
void  Sgl$PerspectiveCamera$moveBackward(Sgl$PerspectiveCamera *  self);
void  Sgl$PerspectiveCamera$rotateLeft(Sgl$PerspectiveCamera *  self);
void  Sgl$PerspectiveCamera$rotateRight(Sgl$PerspectiveCamera *  self);
void  Sgl$PerspectiveCamera$rise(Sgl$PerspectiveCamera *  self);
void  Sgl$PerspectiveCamera$fall(Sgl$PerspectiveCamera *  self);
Sgl$Ray Sgl$PerspectiveCamera$mkRay(Sgl$PerspectiveCamera *  self, SuiCore$Vec2 ndcPos);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
