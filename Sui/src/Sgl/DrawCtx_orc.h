
typedef struct tagSgl$DrawCtx Sgl$DrawCtx;
typedef struct tagVtable_Sgl$DrawCtx Vtable_Sgl$DrawCtx;


#ifndef define_struct___Sgl__DrawCtx_orc_h__
#define define_struct___Sgl__DrawCtx_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__DrawCtx_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdlib.h>
#include <stdio.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__DrawCtx_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__DrawCtx_orc_h__
#define __Sgl__DrawCtx_orc_h__

//include  importHeadCode
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Math_orc.h"
#include "./Scene_orc.h"
#include "./Camera_orc.h"
#include "./Obj3d_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./GeometryLine_orc.h"
#include "./Light_orc.h"
#include "./Mat_orc.h"
#include "./PointLight_orc.h"
#include "./DirLight_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Color_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$DrawCtx {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$DrawCtx _vtable_Sgl$DrawCtx;

// class refc:0
struct tagSgl$DrawCtx {
	Object super; 
	Orc$List*  lights ;
	Sgl$Scene *  scene ;
	Sgl$Camera *  camera ;
	SuiCore$Vec2 frameSize ;
	long long  prevTickMs ;
	long long  dtMs ;
	float  dtSec ;
	float  passSec ;
	Sgl$Material*  depthMatl ;
	Sgl$Material*  lineMatl ;
	Sgl$GeometryLine*  lineGeometry ;
	Orc$PointerArray*  transparentObj3ds ;
	void  (**cbAfterDraw)(void *  self);
	bool  (*addTransparentObj3dIfIsTransparent) (Sgl$DrawCtx *  self, Sgl$Obj3d *  obj3d, Sgl$Material *  matl);
	void  (*drawLineGeometry) (Sgl$DrawCtx *  self);
	void  (*drawAxis) (Sgl$DrawCtx *  self);
	void  (*collectLights) (Sgl$DrawCtx *  self);
	void  (*_collectLight) (Sgl$DrawCtx *  self, SuiCore$Node *  n);
	void  (*tick) (Sgl$DrawCtx *  self, Sgl$Scene *  scene);
	bool  (*tickObj3d) (Sgl$DrawCtx *  self, SuiCore$Node *  n);
	void  (*drawDepth) (Sgl$DrawCtx *  self, Sgl$Scene *  scene, Sgl$Camera *  camera);
	void  (*_drawNodeDepth) (Sgl$DrawCtx *  self, SuiCore$Node *  n);
	void  (*updateViewport) (Sgl$DrawCtx *  self);
	void  (*draw) (Sgl$DrawCtx *  self, Sgl$Scene *  scene, Sgl$Camera *  camera);
	void  (*drawTransparentObj3ds) (Sgl$DrawCtx *  self);
	void  (*setMvpToMaterial) (Sgl$DrawCtx *  self, Sgl$Obj3d *  obj3d, Sgl$Material *  material);
	void  (*setGlobalInfosToMaterial) (Sgl$DrawCtx *  self, Sgl$Material *  matl);
	void  (*setLightsToMaterial) (Sgl$DrawCtx *  self, Sgl$Material *  matl);
};
Vtable_Sgl$DrawCtx* Vtable_Sgl$DrawCtx_init(Vtable_Sgl$DrawCtx* pvt);
void Sgl$DrawCtx_init_fields(Sgl$DrawCtx *self);
void Sgl$DrawCtx_init(Sgl$DrawCtx *self, void *pOwner);
Sgl$DrawCtx * Sgl$DrawCtx_new(void *pOwner);
void Sgl$DrawCtx_fini(Sgl$DrawCtx *self);

void  Sgl$DrawCtx$ctor(Sgl$DrawCtx *  self);
bool  Sgl$DrawCtx$addTransparentObj3dIfIsTransparent(Sgl$DrawCtx *  self, Sgl$Obj3d *  obj3d, Sgl$Material *  matl);
void  Sgl$DrawCtx$drawLineGeometry(Sgl$DrawCtx *  self);
void  Sgl$DrawCtx$drawAxis(Sgl$DrawCtx *  self);
void  Sgl$DrawCtx$collectLights(Sgl$DrawCtx *  self);
void  Sgl$DrawCtx$_collectLight(Sgl$DrawCtx *  self, SuiCore$Node *  n);
void  Sgl$DrawCtx$tick(Sgl$DrawCtx *  self, Sgl$Scene *  scene);
bool  Sgl$DrawCtx$tickObj3d(Sgl$DrawCtx *  self, SuiCore$Node *  n);
void  Sgl$DrawCtx$drawDepth(Sgl$DrawCtx *  self, Sgl$Scene *  scene, Sgl$Camera *  camera);
void  Sgl$DrawCtx$_drawNodeDepth(Sgl$DrawCtx *  self, SuiCore$Node *  n);
void  Sgl$DrawCtx$updateViewport(Sgl$DrawCtx *  self);
void  Sgl$DrawCtx$draw(Sgl$DrawCtx *  self, Sgl$Scene *  scene, Sgl$Camera *  camera);
void  Sgl$DrawCtx$drawTransparentObj3ds(Sgl$DrawCtx *  self);
void  Sgl$DrawCtx$setMvpToMaterial(Sgl$DrawCtx *  self, Sgl$Obj3d *  obj3d, Sgl$Material *  material);
void  Sgl$DrawCtx$setGlobalInfosToMaterial(Sgl$DrawCtx *  self, Sgl$Material *  matl);
void  Sgl$DrawCtx$setLightsToMaterial(Sgl$DrawCtx *  self, Sgl$Material *  matl);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
