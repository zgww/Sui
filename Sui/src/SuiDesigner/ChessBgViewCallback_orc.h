
typedef struct tagSuiDesigner$ChessBgViewCallback SuiDesigner$ChessBgViewCallback;
typedef struct tagVtable_SuiDesigner$ChessBgViewCallback Vtable_SuiDesigner$ChessBgViewCallback;


#ifndef define_struct___SuiDesigner__ChessBgViewCallback_orc_h__
#define define_struct___SuiDesigner__ChessBgViewCallback_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__ChessBgViewCallback_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__ChessBgViewCallback_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__ChessBgViewCallback_orc_h__
#define __SuiDesigner__ChessBgViewCallback_orc_h__

//include  importHeadCode
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Canvas_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$ChessBgViewCallback {
	Vtable_SuiCore$ViewCallback super;
};
//虚表实例
extern Vtable_SuiDesigner$ChessBgViewCallback _vtable_SuiDesigner$ChessBgViewCallback;

// class refc:0
struct tagSuiDesigner$ChessBgViewCallback {
	SuiCore$ViewCallback super; 
	int  width ;
	int  height ;
	int  color0 ;
	int  color1 ;
	SuiCore$Image*  img ;
	Object*  obj ;
	char *  (*new_createChessBg_inMemory) (SuiDesigner$ChessBgViewCallback *  self, int  w, int  h);
	int  (*gocChessBgImage) (SuiDesigner$ChessBgViewCallback *  self, SuiCore$Canvas *  canvas);
};
Vtable_SuiDesigner$ChessBgViewCallback* Vtable_SuiDesigner$ChessBgViewCallback_init(Vtable_SuiDesigner$ChessBgViewCallback* pvt);
void SuiDesigner$ChessBgViewCallback_init_fields(SuiDesigner$ChessBgViewCallback *self);
void SuiDesigner$ChessBgViewCallback_init(SuiDesigner$ChessBgViewCallback *self, void *pOwner);
SuiDesigner$ChessBgViewCallback * SuiDesigner$ChessBgViewCallback_new(void *pOwner);
void SuiDesigner$ChessBgViewCallback_fini(SuiDesigner$ChessBgViewCallback *self);

void  SuiDesigner$ChessBgViewCallback$dtor(SuiDesigner$ChessBgViewCallback *  self);
bool  SuiDesigner$ChessBgViewCallback$cbLayout(SuiDesigner$ChessBgViewCallback *  self, SuiCore$View *  div, SuiCore$Frame *  ctx);
bool  SuiDesigner$ChessBgViewCallback$cbDraw(SuiDesigner$ChessBgViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);
char *  SuiDesigner$ChessBgViewCallback$new_createChessBg_inMemory(SuiDesigner$ChessBgViewCallback *  self, int  w, int  h);
int  SuiDesigner$ChessBgViewCallback$gocChessBgImage(SuiDesigner$ChessBgViewCallback *  self, SuiCore$Canvas *  canvas);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
