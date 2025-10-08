
typedef struct tagSuiCore$ViewCallback SuiCore$ViewCallback;
typedef struct tagVtable_SuiCore$ViewCallback Vtable_SuiCore$ViewCallback;
typedef struct tagSuiCore$View SuiCore$View;
typedef struct tagVtable_SuiCore$View Vtable_SuiCore$View;


#ifndef define_struct___SuiCore__View_orc_h__
#define define_struct___SuiCore__View_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__View_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__View_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__View_orc_h__
#define __SuiCore__View_orc_h__

//include  importHeadCode
#include "./Node_orc.h"
#include "./Rect_orc.h"
#include "./Frame_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Math_orc.h"
#include "./Vec2_orc.h"
#include "./Inset_orc.h"
#include "./ViewBase_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./Window_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./BoxShadow_orc.h"
#include "./Border_orc.h"
#include "./Edge_orc.h"
#include "./Radius_orc.h"
#include "./Color_orc.h"
#include "./Rect_orc.h"
#include "./Canvas_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$ViewCallback {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$ViewCallback _vtable_SuiCore$ViewCallback;

// class refc:1
struct tagSuiCore$ViewCallback {
	Object super; 
	bool  (*cbLayout) (SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Frame *  ctx);
	bool  (*cbDraw) (SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);
	bool  (*cbDrawSelf) (SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);
	void  (*afterDrawSelf) (SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);
};
Vtable_SuiCore$ViewCallback* Vtable_SuiCore$ViewCallback_init(Vtable_SuiCore$ViewCallback* pvt);
void SuiCore$ViewCallback_init_fields(SuiCore$ViewCallback *self);
void SuiCore$ViewCallback_init(SuiCore$ViewCallback *self, void *pOwner);
SuiCore$ViewCallback * SuiCore$ViewCallback_new(void *pOwner);
void SuiCore$ViewCallback_fini(SuiCore$ViewCallback *self);

bool  SuiCore$ViewCallback$cbLayout(SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Frame *  ctx);
bool  SuiCore$ViewCallback$cbDraw(SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);
bool  SuiCore$ViewCallback$cbDrawSelf(SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);
void  SuiCore$ViewCallback$afterDrawSelf(SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);


// 虚表
struct tagVtable_SuiCore$View {
	Vtable_SuiCore$ViewBase super;
};
//虚表实例
extern Vtable_SuiCore$View _vtable_SuiCore$View;

// class refc:0
struct tagSuiCore$View {
	SuiCore$ViewBase super; 
	SuiCore$Vec2 size ;
	bool  needClip ;
	float  width ;
	float  height ;
	void  (*setHeight) (SuiCore$View *  self, float  h);
	void  (*setWidth) (SuiCore$View *  self, float  v);
	float  desiredWidth ;
	float  desiredHeight ;
	float  minWidth ;
	float  maxWidth ;
	float  minHeight ;
	float  maxHeight ;
	SuiCore$Border*  border ;
	SuiCore$Radius*  radius ;
	SuiCore$Inset padding ;
	SuiCore$Inset margin ;
	SuiCore$BoxShadow*  boxShadow ;
	int  backgroundColor ;
	SuiCore$ViewCallback*  cb ;
	SuiCore$Rect (*getViewRect_baseClient) (SuiCore$View *  self);
	SuiCore$Rect (*getFrameRect) (SuiCore$View *  self);
	SuiCore$Rect (*getViewRect) (SuiCore$View *  self);
	SuiCore$Rect (*getContentRect) (SuiCore$View *  self);
	SuiCore$Vec2 (*getNonContentSize) (SuiCore$View *  self);
	SuiCore$Inset (*getInsetOfFrameToContent) (SuiCore$View *  self);
	SuiCore$Vec2 (*getSizeWithoutMargin) (SuiCore$View *  self);
	float  (*getOutWidth) (SuiCore$View *  self);
	float  (*getOutHeight) (SuiCore$View *  self);
	float  (*getOutMinWidth) (SuiCore$View *  self);
	float  (*getOutMinHeight) (SuiCore$View *  self);
	float  (*getOutMaxWidth) (SuiCore$View *  self);
	float  (*getOutMaxHeight) (SuiCore$View *  self);
	void  (*updateFrame_forSelfWidthHeight) (SuiCore$View *  self, SuiCore$Frame *  ctx);
	SuiCore$Rect (*getContentLocalRect) (SuiCore$View *  self);
	SuiCore$Rect (*getContentRect_baseViewRect) (SuiCore$View *  self);
	SuiCore$Vec2 (*getViewSize) (SuiCore$View *  self);
	void  (*layoutContent_fromOutBox) (SuiCore$View *  self, SuiCore$Frame *  ctx);
	void  (*initLayoutSize) (SuiCore$View *  self, SuiCore$Frame *  ctx);
	bool  (*callCbLayout) (SuiCore$View *  self, SuiCore$Frame *  ctx);
	void  (*updateFrame_byContentCtx) (SuiCore$View *  self, SuiCore$Frame *  targetCtx, SuiCore$Frame *  contentCtx);
	SuiCore$Frame (*makeContentLayoutCtx) (SuiCore$View *  self, SuiCore$Frame *  ctx);
	SuiCore$Rect (*getContentClientRect) (SuiCore$View *  self);
	void  (*clip) (SuiCore$View *  self, SuiCore$Canvas *  canvas);
	void  (*drawSelfBorder) (SuiCore$View *  self, SuiCore$Canvas *  canvas);
};
Vtable_SuiCore$View* Vtable_SuiCore$View_init(Vtable_SuiCore$View* pvt);
void SuiCore$View_init_fields(SuiCore$View *self);
void SuiCore$View_init(SuiCore$View *self, void *pOwner);
SuiCore$View * SuiCore$View_new(void *pOwner);
void SuiCore$View_fini(SuiCore$View *self);

void  SuiCore$View$setHeight(SuiCore$View *  self, float  h);
void  SuiCore$View$setWidth(SuiCore$View *  self, float  v);
SuiCore$Rect SuiCore$View$getViewRect_baseClient(SuiCore$View *  self);
bool  SuiCore$View$_hitTestSelf(SuiCore$View *  self, float  x, float  y);
SuiCore$Rect SuiCore$View$getFrameRect(SuiCore$View *  self);
SuiCore$Rect SuiCore$View$getViewRect(SuiCore$View *  self);
SuiCore$Rect SuiCore$View$getContentRect(SuiCore$View *  self);
SuiCore$Vec2 SuiCore$View$getNonContentSize(SuiCore$View *  self);
SuiCore$Inset SuiCore$View$getInsetOfFrameToContent(SuiCore$View *  self);
SuiCore$Vec2 SuiCore$View$getSizeWithoutMargin(SuiCore$View *  self);
float  SuiCore$View$getOutWidth(SuiCore$View *  self);
float  SuiCore$View$getOutHeight(SuiCore$View *  self);
float  SuiCore$View$getOutMinWidth(SuiCore$View *  self);
float  SuiCore$View$getOutMinHeight(SuiCore$View *  self);
float  SuiCore$View$getOutMaxWidth(SuiCore$View *  self);
float  SuiCore$View$getOutMaxHeight(SuiCore$View *  self);
void  SuiCore$View$updateFrame_forSelfWidthHeight(SuiCore$View *  self, SuiCore$Frame *  ctx);
SuiCore$Rect SuiCore$View$getContentLocalRect(SuiCore$View *  self);
SuiCore$Rect SuiCore$View$getContentRect_baseViewRect(SuiCore$View *  self);
SuiCore$Vec2 SuiCore$View$getViewSize(SuiCore$View *  self);
void  SuiCore$View$layoutContent_fromOutBox(SuiCore$View *  self, SuiCore$Frame *  ctx);
void  SuiCore$View$layoutContent(SuiCore$View *  self, SuiCore$Frame *  contentCtx);
void  SuiCore$View$initLayoutSize(SuiCore$View *  self, SuiCore$Frame *  ctx);
bool  SuiCore$View$callCbLayout(SuiCore$View *  self, SuiCore$Frame *  ctx);
void  SuiCore$View$layout(SuiCore$View *  self, SuiCore$Frame *  ctx);
void  SuiCore$View$updateFrame_byContentCtx(SuiCore$View *  self, SuiCore$Frame *  targetCtx, SuiCore$Frame *  contentCtx);
SuiCore$Frame SuiCore$View$makeContentLayoutCtx(SuiCore$View *  self, SuiCore$Frame *  ctx);
SuiCore$Rect SuiCore$View$get_abs_rect(SuiCore$View *  self);
SuiCore$Rect SuiCore$View$getContentClientRect(SuiCore$View *  self);
void  SuiCore$View$clip(SuiCore$View *  self, SuiCore$Canvas *  canvas);
void  SuiCore$View$draw(SuiCore$View *  self, SuiCore$Canvas *  canvas);
void  SuiCore$View$drawSelfBorder(SuiCore$View *  self, SuiCore$Canvas *  canvas);
void  SuiCore$View$draw_self(SuiCore$View *  self, SuiCore$Canvas *  canvas);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
