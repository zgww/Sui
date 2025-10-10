
typedef struct tagSuiCore$Image SuiCore$Image;
typedef struct tagVtable_SuiCore$Image Vtable_SuiCore$Image;


#ifndef define_struct___SuiCore__Image_orc_h__
#define define_struct___SuiCore__Image_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Image_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../nanovg/nanovg.h"
#include "../../nanovg/stb_image_write.h"




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Image_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Image_orc_h__
#define __SuiCore__Image_orc_h__

//include  importHeadCode
#include "./Global_orc.h"
#include "./Vec2_orc.h"
#include "./Canvas_orc.h"
#include "../../Orc/Map_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Buffer_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Image {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Image _vtable_SuiCore$Image;

// class refc:1
struct tagSuiCore$Image {
	Object super; 
	int  _img ;
	SuiCore$Vec2 (*size) (SuiCore$Image *  self);
	float  (*width) (SuiCore$Image *  self);
	float  (*height) (SuiCore$Image *  self);
};
Vtable_SuiCore$Image* Vtable_SuiCore$Image_init(Vtable_SuiCore$Image* pvt);
void SuiCore$Image_init_fields(SuiCore$Image *self);
void SuiCore$Image_init(SuiCore$Image *self, void *pOwner);
SuiCore$Image * SuiCore$Image_new(void *pOwner);
void SuiCore$Image_fini(SuiCore$Image *self);

SuiCore$Vec2 SuiCore$Image$size(SuiCore$Image *  self);
float  SuiCore$Image$width(SuiCore$Image *  self);
float  SuiCore$Image$height(SuiCore$Image *  self);

void  SuiCore$Image_writeFloatsAsGrey_toPng(const char *  topath, int  w, int  h, float *  vs);
void  SuiCore$Image_writeRgbas_toPng(const char *  topath, int  w, int  h, unsigned char *  rgbas);
void  SuiCore$Image_writeFloatsAsRgba_toPng(const char *  topath, int  w, int  h, float *  vs);
void  SuiCore$Image_convertFloatsToGreyBuffer(Sgl$Buffer *  b, int  w, int  h, float *  vs);
void  SuiCore$Image_convertFloatsToRgbaBuffer(Sgl$Buffer *  b, int  w, int  h, float *  vs);
Orc$Map*  SuiCore$getImageMap(Orc$Map **  __outRef__);
SuiCore$Image*  SuiCore$loadImage(SuiCore$Image **  __outRef__, const char *  path);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
