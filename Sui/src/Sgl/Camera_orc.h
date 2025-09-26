
typedef struct tagSgl$Camera Sgl$Camera;
typedef struct tagVtable_Sgl$Camera Vtable_Sgl$Camera;


#ifndef define_struct___Sgl__Camera_orc_h__
#define define_struct___Sgl__Camera_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Camera_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Camera_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Camera_orc_h__
#define __Sgl__Camera_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "./Mat_orc.h"
#include "./Ray_orc.h"
#include "./Obj3d_orc.h"
#include "./Scene_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Camera {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$Camera _vtable_Sgl$Camera;

// class refc:0
struct tagSgl$Camera {
	Sgl$Obj3d super; 
	SuiCore$Rect viewport ;
	Sgl$Mat view ;
	Sgl$Mat projection ;
	Sgl$Mat (*calcVp) (Sgl$Camera *  self);
	void  (*updateProjectionMat) (Sgl$Camera *  self);
	void  (*updateViewMat) (Sgl$Camera *  self);
	void  (*updateMat) (Sgl$Camera *  self);
	Sgl$Ray (*mkRay) (Sgl$Camera *  self, SuiCore$Vec2 ndcPos);
	SuiCore$Vec3 (*project) (Sgl$Camera *  self, SuiCore$Vec3 worldPos);
	SuiCore$Vec3 (*unproject) (Sgl$Camera *  self, SuiCore$Vec3 ndcPos);
	SuiCore$Vec3 (*unprojectToView) (Sgl$Camera *  self, SuiCore$Vec3 ndcPos);
};
Vtable_Sgl$Camera* Vtable_Sgl$Camera_init(Vtable_Sgl$Camera* pvt);
void Sgl$Camera_init_fields(Sgl$Camera *self);
void Sgl$Camera_init(Sgl$Camera *self, void *pOwner);
Sgl$Camera * Sgl$Camera_new(void *pOwner);
void Sgl$Camera_fini(Sgl$Camera *self);

void  Sgl$Camera$onMounted(Sgl$Camera *  self);
Sgl$Mat Sgl$Camera$calcVp(Sgl$Camera *  self);
void  Sgl$Camera$updateProjectionMat(Sgl$Camera *  self);
void  Sgl$Camera$updateViewMat(Sgl$Camera *  self);
void  Sgl$Camera$updateMat(Sgl$Camera *  self);
Sgl$Ray Sgl$Camera$mkRay(Sgl$Camera *  self, SuiCore$Vec2 ndcPos);
SuiCore$Vec3 Sgl$Camera$project(Sgl$Camera *  self, SuiCore$Vec3 worldPos);
SuiCore$Vec3 Sgl$Camera$unproject(Sgl$Camera *  self, SuiCore$Vec3 ndcPos);
SuiCore$Vec3 Sgl$Camera$unprojectToView(Sgl$Camera *  self, SuiCore$Vec3 ndcPos);
void  Sgl$Camera$lookAt(Sgl$Camera *  self, float  x, float  y, float  z);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
