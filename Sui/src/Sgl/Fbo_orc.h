
typedef struct tagSgl$Fbo Sgl$Fbo;
typedef struct tagVtable_Sgl$Fbo Vtable_Sgl$Fbo;
typedef struct tagSgl$Rbo Sgl$Rbo;
typedef struct tagVtable_Sgl$Rbo Vtable_Sgl$Rbo;


#ifndef define_struct___Sgl__Fbo_orc_h__
#define define_struct___Sgl__Fbo_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Fbo_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "./UnitOpengl.h"
#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Fbo_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Fbo_orc_h__
#define __Sgl__Fbo_orc_h__

//include  importHeadCode
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "./Tex2d_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Fbo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Fbo _vtable_Sgl$Fbo;

// class refc:0
struct tagSgl$Fbo {
	Object super; 
	GLuint id ;
	Sgl$Tex2d*  tex2d ;
	Sgl$Tex2d*  depthTex2d ;
	Sgl$Tex2d*  stencilTex2d ;
	Sgl$Rbo*  depthStencilRbo ;
	SuiCore$Vec2 (*getSize) (Sgl$Fbo *  self);
	void  (*gen) (Sgl$Fbo *  self);
	void  (*bind) (Sgl$Fbo *  self);
	void  (*unbind) (Sgl$Fbo *  self);
	bool  (*isStatusComplete) (Sgl$Fbo *  self);
	int  (*checkStatus) (Sgl$Fbo *  self);
	const char *  (*statusDesc) (Sgl$Fbo *  self);
	void  (*startDraw) (Sgl$Fbo *  self, float  r, float  g, float  b, float  a, bool  clearColor, bool  clearDepth, bool  clearStencil);
	void  (*endDraw) (Sgl$Fbo *  self);
	void  (*setGlDrawBufferNone) (Sgl$Fbo *  self);
	void  (*setGlReadBufferNone) (Sgl$Fbo *  self);
	void  (*setGlDrawBufferDefault) (Sgl$Fbo *  self);
	void  (*setGlReadBufferDefault) (Sgl$Fbo *  self);
	void  (*attachColorTex2d) (Sgl$Fbo *  self, Sgl$Tex2d *  tex2d, int  colorAttachmentIndex);
	void  (*attachDepthTex2d) (Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
	void  (*attachStencilTex2d) (Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
	void  (*attachRenderBuffer_asDepthStencil) (Sgl$Fbo *  self, Sgl$Rbo *  rbo);
	void  (*_attachColorTex2d) (Sgl$Fbo *  self, Sgl$Tex2d *  tex2d, int  colorAttachmentIndex);
	void  (*_attachDepthTex2d) (Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
	void  (*_attachDepthStencilTex2d) (Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
	void  (*_attachStencilTex2d) (Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
	void  (*_attachRenderBuffer_asDepthStencil) (Sgl$Fbo *  self, Sgl$Rbo *  rbo);
	void  (*buildWithColorDepth32fStencil8Texture) (Sgl$Fbo *  self, int  w, int  h, bool  colorTex, bool  depthStencilTex);
	void  (*buildWithColorDepth24Stencil8Texture) (Sgl$Fbo *  self, int  w, int  h, bool  colorTex, bool  depthStencilTex);
	void  (*buildWithColorDepthStencilTexture) (Sgl$Fbo *  self, int  w, int  h, bool  colorTex, bool  depthTex, bool  stencilTex);
	void  (*buildWithColorDepthStencil) (Sgl$Fbo *  self, int  w, int  h);
};
Vtable_Sgl$Fbo* Vtable_Sgl$Fbo_init(Vtable_Sgl$Fbo* pvt);
void Sgl$Fbo_init_fields(Sgl$Fbo *self);
void Sgl$Fbo_init(Sgl$Fbo *self, void *pOwner);
Sgl$Fbo * Sgl$Fbo_new(void *pOwner);
void Sgl$Fbo_fini(Sgl$Fbo *self);

void  Sgl$Fbo$ctor(Sgl$Fbo *  self);
void  Sgl$Fbo$dtor(Sgl$Fbo *  self);
SuiCore$Vec2 Sgl$Fbo$getSize(Sgl$Fbo *  self);
extern void  Sgl$Fbo$gen(Sgl$Fbo *  self);
extern void  Sgl$Fbo$bind(Sgl$Fbo *  self);
extern void  Sgl$Fbo$unbind(Sgl$Fbo *  self);
extern bool  Sgl$Fbo$isStatusComplete(Sgl$Fbo *  self);
extern int  Sgl$Fbo$checkStatus(Sgl$Fbo *  self);
extern const char *  Sgl$Fbo$statusDesc(Sgl$Fbo *  self);
extern void  Sgl$Fbo$startDraw(Sgl$Fbo *  self, float  r, float  g, float  b, float  a, bool  clearColor, bool  clearDepth, bool  clearStencil);
extern void  Sgl$Fbo$endDraw(Sgl$Fbo *  self);
extern void  Sgl$Fbo$setGlDrawBufferNone(Sgl$Fbo *  self);
extern void  Sgl$Fbo$setGlReadBufferNone(Sgl$Fbo *  self);
extern void  Sgl$Fbo$setGlDrawBufferDefault(Sgl$Fbo *  self);
extern void  Sgl$Fbo$setGlReadBufferDefault(Sgl$Fbo *  self);
void  Sgl$Fbo$attachColorTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d, int  colorAttachmentIndex);
void  Sgl$Fbo$attachDepthTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
void  Sgl$Fbo$attachStencilTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
void  Sgl$Fbo$attachRenderBuffer_asDepthStencil(Sgl$Fbo *  self, Sgl$Rbo *  rbo);
extern void  Sgl$Fbo$_attachColorTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d, int  colorAttachmentIndex);
extern void  Sgl$Fbo$_attachDepthTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
extern void  Sgl$Fbo$_attachDepthStencilTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
extern void  Sgl$Fbo$_attachStencilTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d);
extern void  Sgl$Fbo$_attachRenderBuffer_asDepthStencil(Sgl$Fbo *  self, Sgl$Rbo *  rbo);
void  Sgl$Fbo$buildWithColorDepth32fStencil8Texture(Sgl$Fbo *  self, int  w, int  h, bool  colorTex, bool  depthStencilTex);
void  Sgl$Fbo$buildWithColorDepth24Stencil8Texture(Sgl$Fbo *  self, int  w, int  h, bool  colorTex, bool  depthStencilTex);
void  Sgl$Fbo$buildWithColorDepthStencilTexture(Sgl$Fbo *  self, int  w, int  h, bool  colorTex, bool  depthTex, bool  stencilTex);
void  Sgl$Fbo$buildWithColorDepthStencil(Sgl$Fbo *  self, int  w, int  h);

extern void  Sgl$deleteFrameBuffer(GLuint id);

// 虚表
struct tagVtable_Sgl$Rbo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Rbo _vtable_Sgl$Rbo;

// class refc:1
struct tagSgl$Rbo {
	Object super; 
	GLuint id ;
	void  (*gen) (Sgl$Rbo *  self);
	void  (*bind) (Sgl$Rbo *  self);
	void  (*unbind) (Sgl$Rbo *  self);
	void  (*storageAs_DEPTH24_STENCIL8) (Sgl$Rbo *  self, int  w, int  h);
};
Vtable_Sgl$Rbo* Vtable_Sgl$Rbo_init(Vtable_Sgl$Rbo* pvt);
void Sgl$Rbo_init_fields(Sgl$Rbo *self);
void Sgl$Rbo_init(Sgl$Rbo *self, void *pOwner);
Sgl$Rbo * Sgl$Rbo_new(void *pOwner);
void Sgl$Rbo_fini(Sgl$Rbo *self);

void  Sgl$Rbo$ctor(Sgl$Rbo *  self);
void  Sgl$Rbo$dtor(Sgl$Rbo *  self);
extern void  Sgl$Rbo$gen(Sgl$Rbo *  self);
extern void  Sgl$Rbo$bind(Sgl$Rbo *  self);
extern void  Sgl$Rbo$unbind(Sgl$Rbo *  self);
extern void  Sgl$Rbo$storageAs_DEPTH24_STENCIL8(Sgl$Rbo *  self, int  w, int  h);

extern void  Sgl$deleteRenderBuffer(GLuint id);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
