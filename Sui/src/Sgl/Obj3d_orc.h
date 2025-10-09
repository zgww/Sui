
typedef struct tagSgl$Obj3d Sgl$Obj3d;
typedef struct tagVtable_Sgl$Obj3d Vtable_Sgl$Obj3d;


#ifndef define_struct___Sgl__Obj3d_orc_h__
#define define_struct___Sgl__Obj3d_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Obj3d_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Obj3d_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Obj3d_orc_h__
#define __Sgl__Obj3d_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Orc/String_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Euler_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/Quaternion_orc.h"
#include "./Mat_orc.h"
#include "./Ray_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./DrawCtx_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./Raycaster_orc.h"
#include "./Material_orc.h"
#include "./Vao_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Obj3d {
	Vtable_SuiCore$Node super;
};
//虚表实例
extern Vtable_Sgl$Obj3d _vtable_Sgl$Obj3d;

// class refc:0
struct tagSgl$Obj3d {
	SuiCore$Node super; 
	Orc$String*  objid ;
	SuiCore$Vec3 position ;
	SuiCore$Vec3 rotation ;
	SuiCore$Vec3 scale ;
	SuiCore$Rgba rgba ;
	int  textColor ;
	SuiCore$Quaternion quaternion ;
	SuiCore$Vec3 _viewPosition ;
	SuiCore$Vec3 up ;
	Sgl$Mat transform ;
	Sgl$Mat _world_transform ;
	bool  visible ;
	Orc$String*  (*gocId) (Orc$String **  __outRef__, Sgl$Obj3d *  self);
	SuiCore$Vec3 (*worldToLocal) (Sgl$Obj3d *  self, SuiCore$Vec3 v3);
	SuiCore$Vec3 (*localToWorld) (Sgl$Obj3d *  self, SuiCore$Vec3 v3);
	void  (*updateTransform) (Sgl$Obj3d *  self);
	void  (*updateWorldTransformAndSubtree) (Sgl$Obj3d *  self);
	void  (*updateChildrenWorldTransform) (Sgl$Obj3d *  self);
	void  (*drawDepth) (Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
	void  (*draw) (Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
	void  (*drawTransparent) (Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
	void  (*drawSelfRaw) (Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx, Sgl$Vao *  vao, Sgl$Material *  matl);
	void  (*drawSelf) (Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
	void  (*drawChildren) (Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
	void  (*tick) (Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
	bool  (*hitTestSelfByRaycaster) (Sgl$Obj3d *  self, Sgl$Raycaster *  raycaster);
	void  (*lookAt) (Sgl$Obj3d *  self, float  x, float  y, float  z);
};
Vtable_Sgl$Obj3d* Vtable_Sgl$Obj3d_init(Vtable_Sgl$Obj3d* pvt);
void Sgl$Obj3d_init_fields(Sgl$Obj3d *self);
void Sgl$Obj3d_init(Sgl$Obj3d *self, void *pOwner);
Sgl$Obj3d * Sgl$Obj3d_new(void *pOwner);
void Sgl$Obj3d_fini(Sgl$Obj3d *self);

Orc$String*  Sgl$Obj3d$gocId(Orc$String **  __outRef__, Sgl$Obj3d *  self);
SuiCore$Vec3 Sgl$Obj3d$worldToLocal(Sgl$Obj3d *  self, SuiCore$Vec3 v3);
SuiCore$Vec3 Sgl$Obj3d$localToWorld(Sgl$Obj3d *  self, SuiCore$Vec3 v3);
void  Sgl$Obj3d$updateTransform(Sgl$Obj3d *  self);
void  Sgl$Obj3d$updateWorldTransformAndSubtree(Sgl$Obj3d *  self);
void  Sgl$Obj3d$updateChildrenWorldTransform(Sgl$Obj3d *  self);
void  Sgl$Obj3d$drawDepth(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Obj3d$draw(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Obj3d$drawTransparent(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Obj3d$drawSelfRaw(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx, Sgl$Vao *  vao, Sgl$Material *  matl);
void  Sgl$Obj3d$drawSelf(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Obj3d$drawChildren(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Obj3d$tick(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx);
bool  Sgl$Obj3d$hitTestSelfByRaycaster(Sgl$Obj3d *  self, Sgl$Raycaster *  raycaster);
void  Sgl$Obj3d$lookAt(Sgl$Obj3d *  self, float  x, float  y, float  z);

SuiCore$Vec3 Sgl$Obj3d$applyRotationToVec3(Sgl$Obj3d *  self, SuiCore$Vec3 v3);
void  Sgl$Obj3d$updateWorldMatrixUptoRoot(Sgl$Obj3d *  self);
void  Sgl$Obj3d$lookAtByDir(Sgl$Obj3d *  self, bool  negativeZ, float  x, float  y, float  z);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
