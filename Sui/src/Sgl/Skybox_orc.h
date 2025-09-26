
typedef struct tagSgl$Skybox Sgl$Skybox;
typedef struct tagVtable_Sgl$Skybox Vtable_Sgl$Skybox;


#ifndef define_struct___Sgl__Skybox_orc_h__
#define define_struct___Sgl__Skybox_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Skybox_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Skybox_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Skybox_orc_h__
#define __Sgl__Skybox_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./Obj3d_orc.h"
#include "./Tex2d_orc.h"
#include "./DrawCtx_orc.h"
#include "./Buffer_orc.h"
#include "./Vao_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Skybox {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$Skybox _vtable_Sgl$Skybox;

// class refc:0
struct tagSgl$Skybox {
	Sgl$Obj3d super; 
	Sgl$Material*  material ;
	Sgl$Geometry*  geometry ;
	Sgl$Tex2d*  front ;
	Sgl$Tex2d*  back ;
	Sgl$Tex2d*  left ;
	Sgl$Tex2d*  right ;
	Sgl$Tex2d*  up ;
	Sgl$Tex2d*  down ;
	Sgl$Vao*  vao ;
	void  (*buildGeometry) (Sgl$Skybox *  self);
};
Vtable_Sgl$Skybox* Vtable_Sgl$Skybox_init(Vtable_Sgl$Skybox* pvt);
void Sgl$Skybox_init_fields(Sgl$Skybox *self);
void Sgl$Skybox_init(Sgl$Skybox *self, void *pOwner);
Sgl$Skybox * Sgl$Skybox_new(void *pOwner);
void Sgl$Skybox_fini(Sgl$Skybox *self);

void  Sgl$Skybox$ctor(Sgl$Skybox *  self);
void  Sgl$Skybox$buildGeometry(Sgl$Skybox *  self);
void  Sgl$Skybox$draw(Sgl$Skybox *  self, Sgl$DrawCtx *  ctx);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
