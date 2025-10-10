
typedef struct tagSgl$Mesh Sgl$Mesh;
typedef struct tagVtable_Sgl$Mesh Vtable_Sgl$Mesh;


#ifndef define_struct___Sgl__Mesh_orc_h__
#define define_struct___Sgl__Mesh_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Mesh_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Mesh_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Mesh_orc_h__
#define __Sgl__Mesh_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./GeometryLine_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Vao_orc.h"
#include "./Raycaster_orc.h"
#include "./DrawCtx_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Map_orc.h"
#include "../Json/Json_orc.h"
#include "./GeometryBox_orc.h"
#include "./GeometryPlane_orc.h"
#include "./GeometrySphere_orc.h"
#include "../HoroEditor/HoroGeometryPreviewView_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Mesh {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$Mesh _vtable_Sgl$Mesh;

// class refc:0
struct tagSgl$Mesh {
	Sgl$Obj3d super; 
	Sgl$Material*  material ;
	Sgl$Geometry*  geometry ;
	Sgl$Vao*  vao ;
	Sgl$Vao*  depthVao ;
	Orc$String*  geometryPath ;
	Orc$String*  materialPath ;
	void  (*setMaterialPath) (Sgl$Mesh *  self, Orc$String*  p);
	void  (*setGeometryPath) (Sgl$Mesh *  self, Orc$String*  p);
};
Vtable_Sgl$Mesh* Vtable_Sgl$Mesh_init(Vtable_Sgl$Mesh* pvt);
void Sgl$Mesh_init_fields(Sgl$Mesh *self);
void Sgl$Mesh_init(Sgl$Mesh *self, void *pOwner);
Sgl$Mesh * Sgl$Mesh_new(void *pOwner);
void Sgl$Mesh_fini(Sgl$Mesh *self);

void  Sgl$Mesh$setMaterialPath(Sgl$Mesh *  self, Orc$String*  p);
void  Sgl$Mesh$setGeometryPath(Sgl$Mesh *  self, Orc$String*  p);
void  Sgl$Mesh$tick(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Mesh$draw(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Mesh$drawSelfRaw(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx, Sgl$Vao *  vao, Sgl$Material *  material);
void  Sgl$Mesh$drawSelf(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Mesh$drawDepth(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx);
bool  Sgl$Mesh$hitTestSelfByRaycaster(Sgl$Mesh *  self, Sgl$Raycaster *  raycaster);

Sgl$Mesh*  Sgl$mkMesh(Sgl$Mesh **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
