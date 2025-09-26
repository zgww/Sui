
typedef struct tagSuiCore$Rgbaf SuiCore$Rgbaf;
typedef struct tagSuiCore$Rgba SuiCore$Rgba;
typedef struct tagSuiCore$Hsla SuiCore$Hsla;
typedef struct tagSuiCore$Hsva SuiCore$Hsva;


#ifndef define_struct___SuiCore__Color_orc_h__
#define define_struct___SuiCore__Color_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Color_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Color_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Rgbaf {
	float  r ;
	float  g ;
	float  b ;
	float  a ;
};


struct tagSuiCore$Rgba {
	unsigned char  r ;
	unsigned char  g ;
	unsigned char  b ;
	unsigned char  a ;
};


struct tagSuiCore$Hsla {
	float  h ;
	float  s ;
	float  l ;
	unsigned char  a ;
};


struct tagSuiCore$Hsva {
	float  h ;
	float  s ;
	float  v ;
	unsigned char  a ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Color_orc_h__
#define __SuiCore__Color_orc_h__

//include  importHeadCode
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Vec3_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Rgbaf_getOrInitMetaStruct();

Orc$String*  SuiCore$Rgbaf$toString(Orc$String **  __outRef__, SuiCore$Rgbaf *  self);
SuiCore$Vec3 SuiCore$Rgbaf$toVec3(SuiCore$Rgbaf *  self);
SuiCore$Rgba SuiCore$Rgbaf$toRgba(SuiCore$Rgbaf *  self);
int  SuiCore$Rgbaf$toInt(SuiCore$Rgbaf *  self);


//结构体元数据获取即初始化
MetaStruct* SuiCore$Rgba_getOrInitMetaStruct();



//结构体元数据获取即初始化
MetaStruct* SuiCore$Hsla_getOrInitMetaStruct();



//结构体元数据获取即初始化
MetaStruct* SuiCore$Hsva_getOrInitMetaStruct();

SuiCore$Rgbaf SuiCore$mkRgbafByFloat4(float *  f4);
SuiCore$Rgbaf SuiCore$mkRgbaf(float  r, float  g, float  b, float  a);
SuiCore$Rgbaf SuiCore$mkRgbafByInt(int  color);
SuiCore$Rgba SuiCore$mkRgbaByFloat(float  r, float  g, float  b, float  a);
SuiCore$Rgba SuiCore$mkRgba(unsigned char  r, unsigned char  g, unsigned char  b, unsigned char  a);
SuiCore$Hsla SuiCore$mkHsla(float  h, float  s, float  l, unsigned char  a);
SuiCore$Hsva SuiCore$mkHsva(float  h, float  s, float  v, unsigned char  a);
SuiCore$Rgba SuiCore$mkRgbaByInt(int  color);
int  SuiCore$mkIntByRgba(unsigned char  r, unsigned char  g, unsigned char  b, unsigned char  a);
SuiCore$Hsva SuiCore$mkHsva_byInt(int  color);
SuiCore$Rgba SuiCore$Hsva$toRgba(SuiCore$Hsva *  self);
int  SuiCore$Hsva$toRgbaInt(SuiCore$Hsva *  self);
Orc$String*  SuiCore$Hsva$toString(Orc$String **  __outRef__, SuiCore$Hsva *  self);
SuiCore$Rgba SuiCore$Hsla$toRgba(SuiCore$Hsla *  self);
int  SuiCore$Hsla$toRgbaInt(SuiCore$Hsla *  self);
Orc$String*  SuiCore$Hsla$toString(Orc$String **  __outRef__, SuiCore$Hsla *  self);
int  SuiCore$Rgba$toInt(SuiCore$Rgba *  self);
Orc$String*  SuiCore$Rgba$toString(Orc$String **  __outRef__, SuiCore$Rgba *  self);
unsigned char  SuiCore$colorGetA(int  color);
unsigned char  SuiCore$colorGetR(int  color);
unsigned char  SuiCore$colorGetG(int  color);
unsigned char  SuiCore$colorGetB(int  color);
NVGcolor SuiCore$mkNVGColorByInt(int  color);
SuiCore$Hsla SuiCore$rgbaToHsla(SuiCore$Rgba rgba);
SuiCore$Hsva SuiCore$rgbaToHsva(SuiCore$Rgba rgb);
SuiCore$Rgba SuiCore$hsvaToRgba(SuiCore$Hsva hsv);
void  SuiCore$testColor();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
