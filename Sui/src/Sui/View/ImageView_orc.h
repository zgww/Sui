
typedef enum enumSuiView$ImageMode SuiView$ImageMode;
typedef struct tagSuiView$ImageModeCalc SuiView$ImageModeCalc;
typedef struct tagVtable_SuiView$ImageModeCalc Vtable_SuiView$ImageModeCalc;
typedef struct tagSuiView$ImageView SuiView$ImageView;
typedef struct tagVtable_SuiView$ImageView Vtable_SuiView$ImageView;


#ifndef define_struct___SuiView__ImageView_orc_h__
#define define_struct___SuiView__ImageView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__ImageView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__ImageView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__ImageView_orc_h__
#define __SuiView__ImageView_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Bezier_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Global_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/Node_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Map_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/Image_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../../SuiDesigner/Inspector_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "../../SuiDesigner/Insp_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
enum enumSuiView$ImageMode {
	SuiView$WrapContent, 
	SuiView$WidthFix, 
	SuiView$HeightFix, 
	SuiView$Contain, 
	SuiView$Cover, 
	SuiView$Fill, 

};

// 虚表
struct tagVtable_SuiView$ImageModeCalc {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$ImageModeCalc _vtable_SuiView$ImageModeCalc;

// class refc:1
struct tagSuiView$ImageModeCalc {
	Object super; 
	SuiCore$Rect (*getSrcRect) (SuiView$ImageModeCalc *  self);
	SuiCore$Rect (*getDstRect) (SuiView$ImageModeCalc *  self);
	int  sw ;
	int  sh ;
	int  dw ;
	int  dh ;
	int  sx ;
	int  sy ;
	int  dx ;
	int  dy ;
	float  sr ;
	float  dr ;
	float  scale ;
	void  (*calc) (SuiView$ImageModeCalc *  self, int  sw, int  sh, int  dw, int  dh, SuiView$ImageMode mode);
	void  (*calc_contain) (SuiView$ImageModeCalc *  self);
	void  (*calc_cover) (SuiView$ImageModeCalc *  self);
};
Vtable_SuiView$ImageModeCalc* Vtable_SuiView$ImageModeCalc_init(Vtable_SuiView$ImageModeCalc* pvt);
void SuiView$ImageModeCalc_init_fields(SuiView$ImageModeCalc *self);
void SuiView$ImageModeCalc_init(SuiView$ImageModeCalc *self, void *pOwner);
SuiView$ImageModeCalc * SuiView$ImageModeCalc_new(void *pOwner);
void SuiView$ImageModeCalc_fini(SuiView$ImageModeCalc *self);

SuiCore$Rect SuiView$ImageModeCalc$getSrcRect(SuiView$ImageModeCalc *  self);
SuiCore$Rect SuiView$ImageModeCalc$getDstRect(SuiView$ImageModeCalc *  self);
void  SuiView$ImageModeCalc$calc(SuiView$ImageModeCalc *  self, int  sw, int  sh, int  dw, int  dh, SuiView$ImageMode mode);
void  SuiView$ImageModeCalc$calc_contain(SuiView$ImageModeCalc *  self);
void  SuiView$ImageModeCalc$calc_cover(SuiView$ImageModeCalc *  self);


// 虚表
struct tagVtable_SuiView$ImageView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$ImageView _vtable_SuiView$ImageView;

// class refc:0
struct tagSuiView$ImageView {
	SuiCore$View super; 
	SuiCore$Bezier bezier ;
	SuiCore$Vec2 pos ;
	float  ratio ;
	void  (*setRatio) (SuiView$ImageView *  self, float  v);
	void  (*insp) (SuiView$ImageView *  self, SuiDesigner$Insp *  insp);
	void  (*onInspect) (SuiView$ImageView *  self, SuiDesigner$Inspector *  insp);
	Orc$String*  src ;
	SuiView$ImageMode imageMode ;
	SuiView$ImageModeCalc*  calc ;
	SuiCore$Image*  _img ;
	void  (*setSrc) (SuiView$ImageView *  self, Orc$String*  src);
	void  (*setImageMode) (SuiView$ImageView *  self, SuiView$ImageMode mode);
	bool  (*_isImageValid) (SuiView$ImageView *  self);
};
Vtable_SuiView$ImageView* Vtable_SuiView$ImageView_init(Vtable_SuiView$ImageView* pvt);
void SuiView$ImageView_init_fields(SuiView$ImageView *self);
void SuiView$ImageView_init(SuiView$ImageView *self, void *pOwner);
SuiView$ImageView * SuiView$ImageView_new(void *pOwner);
void SuiView$ImageView_fini(SuiView$ImageView *self);

void  SuiView$ImageView$setRatio(SuiView$ImageView *  self, float  v);
void  SuiView$ImageView$insp(SuiView$ImageView *  self, SuiDesigner$Insp *  insp);
void  SuiView$ImageView$onInspect(SuiView$ImageView *  self, SuiDesigner$Inspector *  insp);
void  SuiView$ImageView$layout(SuiView$ImageView *  self, SuiCore$Frame *  ctx);
void  SuiView$ImageView$setSrc(SuiView$ImageView *  self, Orc$String*  src);
void  SuiView$ImageView$setImageMode(SuiView$ImageView *  self, SuiView$ImageMode mode);
bool  SuiView$ImageView$_isImageValid(SuiView$ImageView *  self);
void  SuiView$ImageView$draw_self(SuiView$ImageView *  self, SuiCore$Canvas *  canvas);

void  SuiView$drawImage_atRect(SuiCore$Canvas *  canvas, SuiCore$Image *  imgId, float  sx, float  sy, float  sw, float  sh, float  dx, float  dy, float  dw, float  dh);
SuiView$ImageView*  SuiView$mkImageView(SuiView$ImageView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
