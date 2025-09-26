
typedef struct tagSgl$SkinMesh Sgl$SkinMesh;
typedef struct tagVtable_Sgl$SkinMesh Vtable_Sgl$SkinMesh;


#ifndef define_struct___Sgl__SkinMesh_orc_h__
#define define_struct___Sgl__SkinMesh_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__SkinMesh_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__SkinMesh_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__SkinMesh_orc_h__
#define __Sgl__SkinMesh_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Bone_orc.h"
#include "./Geometry_orc.h"
#include "./Material_orc.h"
#include "./Vao_orc.h"
#include "./DrawCtx_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$SkinMesh {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$SkinMesh _vtable_Sgl$SkinMesh;

// class refc:0
struct tagSgl$SkinMesh {
	Sgl$Obj3d super; 
	Sgl$Material*  material ;
	Sgl$Geometry*  geometry ;
	Sgl$Skeleton*  skeleton ;
	Sgl$Vao*  vao ;
	void  (*initRootBoneIfNeed) (Sgl$SkinMesh *  self);
};
Vtable_Sgl$SkinMesh* Vtable_Sgl$SkinMesh_init(Vtable_Sgl$SkinMesh* pvt);
void Sgl$SkinMesh_init_fields(Sgl$SkinMesh *self);
void Sgl$SkinMesh_init(Sgl$SkinMesh *self, void *pOwner);
Sgl$SkinMesh * Sgl$SkinMesh_new(void *pOwner);
void Sgl$SkinMesh_fini(Sgl$SkinMesh *self);

void  Sgl$SkinMesh$initRootBoneIfNeed(Sgl$SkinMesh *  self);
void  Sgl$SkinMesh$onMounted(Sgl$SkinMesh *  self);
void  Sgl$SkinMesh$tick(Sgl$SkinMesh *  self, Sgl$DrawCtx *  ctx);
void  Sgl$SkinMesh$draw(Sgl$SkinMesh *  self, Sgl$DrawCtx *  ctx);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
