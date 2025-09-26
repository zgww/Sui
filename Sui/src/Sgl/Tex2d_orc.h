
typedef struct tagSgl$Tex2d Sgl$Tex2d;
typedef struct tagVtable_Sgl$Tex2d Vtable_Sgl$Tex2d;


#ifndef define_struct___Sgl__Tex2d_orc_h__
#define define_struct___Sgl__Tex2d_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Tex2d_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../nanovg/stb_image.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__Tex2d_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Tex2d_orc_h__
#define __Sgl__Tex2d_orc_h__

//include  importHeadCode
#include "../Sui/Core/Global_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./Vao_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Color_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Tex2d {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Tex2d _vtable_Sgl$Tex2d;

// class refc:0
struct tagSgl$Tex2d {
	Object super; 
	GLuint id ;
	GLuint wrapS ;
	GLuint wrapT ;
	GLuint minFilter ;
	GLuint magFilter ;
	int  width ;
	int  height ;
	int  format ;
	int  channelCount ;
	Orc$String*  path ;
	void  (*setWrapClampToEdge) (Sgl$Tex2d *  self);
	void  (*setWrapClampToBorder) (Sgl$Tex2d *  self, int  color);
	SuiCore$Vec2 (*Size) (Sgl$Tex2d *  self);
	void  (*updateParameters) (Sgl$Tex2d *  self);
	void  (*gen) (Sgl$Tex2d *  self);
	void  (*bind) (Sgl$Tex2d *  self);
	void  (*unbind) (Sgl$Tex2d *  self);
	void  (*active) (Sgl$Tex2d *  self, int  offset);
	void  (*generateMipmap) (Sgl$Tex2d *  self);
	void  (*image2dRgba) (Sgl$Tex2d *  self, unsigned char *  buf, int  w, int  h);
	void  (*image2dRgb) (Sgl$Tex2d *  self, unsigned char *  buf, int  w, int  h);
	void  (*image2dRed8) (Sgl$Tex2d *  self, unsigned char *  buf, int  w, int  h);
	void  (*initZerosRgb) (Sgl$Tex2d *  self, int  w, int  h);
	void  (*initZerosRed8) (Sgl$Tex2d *  self, int  w, int  h);
	void  (*initZerosRgba) (Sgl$Tex2d *  self, int  w, int  h);
	void  (*initForDepthAttachment) (Sgl$Tex2d *  self, int  w, int  h);
	void  (*initForStencilAttachment) (Sgl$Tex2d *  self, int  w, int  h);
	void  (*initForDepth32fStencil8Attachment) (Sgl$Tex2d *  self, int  w, int  h);
	void  (*initForDepth24Stencil8Attachment) (Sgl$Tex2d *  self, int  w, int  h);
	bool  (*loadImageByPathCstr) (Sgl$Tex2d *  self, const char *  path);
};
Vtable_Sgl$Tex2d* Vtable_Sgl$Tex2d_init(Vtable_Sgl$Tex2d* pvt);
void Sgl$Tex2d_init_fields(Sgl$Tex2d *self);
void Sgl$Tex2d_init(Sgl$Tex2d *self, void *pOwner);
Sgl$Tex2d * Sgl$Tex2d_new(void *pOwner);
void Sgl$Tex2d_fini(Sgl$Tex2d *self);

void  Sgl$Tex2d$setWrapClampToEdge(Sgl$Tex2d *  self);
void  Sgl$Tex2d$setWrapClampToBorder(Sgl$Tex2d *  self, int  color);
void  Sgl$Tex2d$ctor(Sgl$Tex2d *  self);
void  Sgl$Tex2d$dtor(Sgl$Tex2d *  self);
SuiCore$Vec2 Sgl$Tex2d$Size(Sgl$Tex2d *  self);
extern void  Sgl$Tex2d$updateParameters(Sgl$Tex2d *  self);
extern void  Sgl$Tex2d$gen(Sgl$Tex2d *  self);
extern void  Sgl$Tex2d$bind(Sgl$Tex2d *  self);
extern void  Sgl$Tex2d$unbind(Sgl$Tex2d *  self);
extern void  Sgl$Tex2d$active(Sgl$Tex2d *  self, int  offset);
extern void  Sgl$Tex2d$generateMipmap(Sgl$Tex2d *  self);
extern void  Sgl$Tex2d$image2dRgba(Sgl$Tex2d *  self, unsigned char *  buf, int  w, int  h);
extern void  Sgl$Tex2d$image2dRgb(Sgl$Tex2d *  self, unsigned char *  buf, int  w, int  h);
extern void  Sgl$Tex2d$image2dRed8(Sgl$Tex2d *  self, unsigned char *  buf, int  w, int  h);
void  Sgl$Tex2d$initZerosRgb(Sgl$Tex2d *  self, int  w, int  h);
void  Sgl$Tex2d$initZerosRed8(Sgl$Tex2d *  self, int  w, int  h);
void  Sgl$Tex2d$initZerosRgba(Sgl$Tex2d *  self, int  w, int  h);
extern void  Sgl$Tex2d$initForDepthAttachment(Sgl$Tex2d *  self, int  w, int  h);
extern void  Sgl$Tex2d$initForStencilAttachment(Sgl$Tex2d *  self, int  w, int  h);
extern void  Sgl$Tex2d$initForDepth32fStencil8Attachment(Sgl$Tex2d *  self, int  w, int  h);
extern void  Sgl$Tex2d$initForDepth24Stencil8Attachment(Sgl$Tex2d *  self, int  w, int  h);
bool  Sgl$Tex2d$loadImageByPathCstr(Sgl$Tex2d *  self, const char *  path);

Sgl$Tex2d*  Sgl$mkTex2dByPathCstr(Sgl$Tex2d **  __outRef__, const char *  path);
SuiCore$Image*  Sgl$loadImageByTex2d(SuiCore$Image **  __outRef__, Sgl$Tex2d *  tex);
extern int  Sgl$__nvglCreateImageFromTexId(int  texId, int  w, int  h, bool  flipY);
extern void  Sgl$deleteTexture(GLuint id);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
