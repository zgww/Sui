
typedef struct tagSgl$OutlineFx Sgl$OutlineFx;
typedef struct tagVtable_Sgl$OutlineFx Vtable_Sgl$OutlineFx;


#ifndef define_struct___Sgl__OutlineFx_orc_h__
#define define_struct___Sgl__OutlineFx_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__OutlineFx_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___Sgl__OutlineFx_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__OutlineFx_orc_h__
#define __Sgl__OutlineFx_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "./Tex2d_orc.h"
#include "./Fbo_orc.h"
#include "./Buffer_orc.h"
#include "./Obj3d_orc.h"
#include "./DrawCtx_orc.h"
#include "./Material_orc.h"
#include "./Vao_orc.h"
#include "./GeometryFullscreenQuad_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$OutlineFx {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$OutlineFx _vtable_Sgl$OutlineFx;

// class refc:0
struct tagSgl$OutlineFx {
	Object super; 
	Sgl$Fbo*  fbo ;
	Sgl$Fbo*  fboEdge ;
	Sgl$Material*  maskMatl ;
	Sgl$Material*  drawMatl ;
	Sgl$Vao*  vao ;
	Sgl$Vao*  vaoQuad ;
	Sgl$GeometryFullscreenQuad*  fsQuad ;
	void  (*init) (Sgl$OutlineFx *  self);
	bool  (*needUpdateFbo) (Sgl$OutlineFx *  self, SuiCore$Vec2 targetSize);
	void  (*updateFbo) (Sgl$OutlineFx *  self, SuiCore$Vec2 size);
	void  (*drawMask) (Sgl$OutlineFx *  self, Sgl$DrawCtx *  ctx, Sgl$Obj3d *  obj3d);
	void  (*drawFxQuad) (Sgl$OutlineFx *  self);
	void  (*draw) (Sgl$OutlineFx *  self, Sgl$DrawCtx *  ctx, Sgl$Obj3d *  obj3d, Sgl$Fbo *  targetFbo);
};
Vtable_Sgl$OutlineFx* Vtable_Sgl$OutlineFx_init(Vtable_Sgl$OutlineFx* pvt);
void Sgl$OutlineFx_init_fields(Sgl$OutlineFx *self);
void Sgl$OutlineFx_init(Sgl$OutlineFx *self, void *pOwner);
Sgl$OutlineFx * Sgl$OutlineFx_new(void *pOwner);
void Sgl$OutlineFx_fini(Sgl$OutlineFx *self);

void  Sgl$OutlineFx$init(Sgl$OutlineFx *  self);
bool  Sgl$OutlineFx$needUpdateFbo(Sgl$OutlineFx *  self, SuiCore$Vec2 targetSize);
void  Sgl$OutlineFx$updateFbo(Sgl$OutlineFx *  self, SuiCore$Vec2 size);
void  Sgl$OutlineFx$drawMask(Sgl$OutlineFx *  self, Sgl$DrawCtx *  ctx, Sgl$Obj3d *  obj3d);
void  Sgl$OutlineFx$drawFxQuad(Sgl$OutlineFx *  self);
void  Sgl$OutlineFx$draw(Sgl$OutlineFx *  self, Sgl$DrawCtx *  ctx, Sgl$Obj3d *  obj3d, Sgl$Fbo *  targetFbo);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
