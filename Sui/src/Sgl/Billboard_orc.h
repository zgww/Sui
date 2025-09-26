
typedef struct tagSgl$Billboard Sgl$Billboard;
typedef struct tagVtable_Sgl$Billboard Vtable_Sgl$Billboard;


#ifndef define_struct___Sgl__Billboard_orc_h__
#define define_struct___Sgl__Billboard_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Billboard_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Billboard_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Billboard_orc_h__
#define __Sgl__Billboard_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Vao_orc.h"
#include "./Raycaster_orc.h"
#include "./DrawCtx_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Map_orc.h"
#include "../Json/Json_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Billboard {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$Billboard _vtable_Sgl$Billboard;

// class refc:0
struct tagSgl$Billboard {
	Sgl$Obj3d super; 
	Sgl$Material*  material ;
	Sgl$Geometry*  geometry ;
	Sgl$Vao*  vao ;
	Sgl$Vao*  depthVao ;
};
Vtable_Sgl$Billboard* Vtable_Sgl$Billboard_init(Vtable_Sgl$Billboard* pvt);
void Sgl$Billboard_init_fields(Sgl$Billboard *self);
void Sgl$Billboard_init(Sgl$Billboard *self, void *pOwner);
Sgl$Billboard * Sgl$Billboard_new(void *pOwner);
void Sgl$Billboard_fini(Sgl$Billboard *self);

void  Sgl$Billboard$tick(Sgl$Billboard *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Billboard$draw(Sgl$Billboard *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Billboard$drawSelf(Sgl$Billboard *  self, Sgl$DrawCtx *  ctx);
void  Sgl$Billboard$drawDepth(Sgl$Billboard *  self, Sgl$DrawCtx *  ctx);
bool  Sgl$Billboard$hitTestSelfByRaycaster(Sgl$Billboard *  self, Sgl$Raycaster *  raycaster);

Sgl$Billboard*  Sgl$mkBillboard(Sgl$Billboard **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
