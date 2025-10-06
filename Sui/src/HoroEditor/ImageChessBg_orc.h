
typedef struct tagHoroEditor$ImageChessBg HoroEditor$ImageChessBg;
typedef struct tagVtable_HoroEditor$ImageChessBg Vtable_HoroEditor$ImageChessBg;


#ifndef define_struct___HoroEditor__ImageChessBg_orc_h__
#define define_struct___HoroEditor__ImageChessBg_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__ImageChessBg_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__ImageChessBg_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__ImageChessBg_orc_h__
#define __HoroEditor__ImageChessBg_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Color_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$ImageChessBg {
	Vtable_Object super;
};
//虚表实例
extern Vtable_HoroEditor$ImageChessBg _vtable_HoroEditor$ImageChessBg;

// class refc:0
struct tagHoroEditor$ImageChessBg {
	Object super; 
	int  width ;
	int  height ;
	int  color0 ;
	int  color1 ;
	SuiCore$Image*  img ;
	char *  (*new_createChessBg_inMemory) (HoroEditor$ImageChessBg *  self, int  w, int  h);
	SuiCore$Image *  (*gocChessBgImage) (HoroEditor$ImageChessBg *  self, SuiCore$Canvas *  canvas);
};
Vtable_HoroEditor$ImageChessBg* Vtable_HoroEditor$ImageChessBg_init(Vtable_HoroEditor$ImageChessBg* pvt);
void HoroEditor$ImageChessBg_init_fields(HoroEditor$ImageChessBg *self);
void HoroEditor$ImageChessBg_init(HoroEditor$ImageChessBg *self, void *pOwner);
HoroEditor$ImageChessBg * HoroEditor$ImageChessBg_new(void *pOwner);
void HoroEditor$ImageChessBg_fini(HoroEditor$ImageChessBg *self);

char *  HoroEditor$ImageChessBg$new_createChessBg_inMemory(HoroEditor$ImageChessBg *  self, int  w, int  h);
SuiCore$Image *  HoroEditor$ImageChessBg$gocChessBgImage(HoroEditor$ImageChessBg *  self, SuiCore$Canvas *  canvas);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
