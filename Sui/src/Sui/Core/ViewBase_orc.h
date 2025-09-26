
typedef struct tagSuiCore$ViewBase SuiCore$ViewBase;
typedef struct tagVtable_SuiCore$ViewBase Vtable_SuiCore$ViewBase;


#ifndef define_struct___SuiCore__ViewBase_orc_h__
#define define_struct___SuiCore__ViewBase_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__ViewBase_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiCore__ViewBase_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__ViewBase_orc_h__
#define __SuiCore__ViewBase_orc_h__

//include  importHeadCode
#include "./Node_orc.h"
#include "./Rect_orc.h"
#include "./Frame_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./LayoutCell_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Math_orc.h"
#include "./Vec2_orc.h"
#include "./Vec3_orc.h"
#include "./Mat2d_orc.h"
#include "./Inset_orc.h"
#include "./Window_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./App_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./Color_orc.h"
#include "./Canvas_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$ViewBase {
	Vtable_SuiCore$Node super;
};
//虚表实例
extern Vtable_SuiCore$ViewBase _vtable_SuiCore$ViewBase;

// class refc:0
struct tagSuiCore$ViewBase {
	SuiCore$Node super; 
	Orc$String*  hitTestType ;
	SuiCore$Inset hitTestPadding ;
	SuiCore$Frame frame ;
	Orc$List*  layoutCells ;
	SuiCore$Mat2d transform ;
	SuiCore$Mat2d _world_transform ;
	bool  visible ;
	Orc$String*  cursor ;
	bool  hover ;
	int  z ;
	Orc$List *  (*gocLayoutCells) (SuiCore$ViewBase *  self);
	SuiCore$LayoutCell *  (*getLayoutCellByType) (SuiCore$ViewBase *  self, Vtable_Object *  vt);
	SuiCore$ViewBase *  (*getChildViewAt) (SuiCore$ViewBase *  self, int  at);
	SuiCore$ViewBase *  (*getChildAsView) (SuiCore$ViewBase *  self, int  at);
	int  (*getChildrenViewCount) (SuiCore$ViewBase *  self);
	SuiCore$Rect (*getScreenRect) (SuiCore$ViewBase *  self);
	SuiCore$Rect (*get_abs_rect) (SuiCore$ViewBase *  self);
	bool  (*_hitTestClientRect) (SuiCore$ViewBase *  self, SuiCore$Rect *  r, float  x, float  y);
	bool  (*_hitTestSelf) (SuiCore$ViewBase *  self, float  x, float  y);
	void  (*_on_invalidLayout) (SuiCore$ViewBase *  self);
	void  (*_on_invalidDraw) (SuiCore$ViewBase *  self);
	void  (*resetViewTreeDirty) (SuiCore$ViewBase *  self);
	SuiCore$Vec2 (*localToWorld) (SuiCore$ViewBase *  self, float  x, float  y);
	SuiCore$Vec2 (*worldToLocal) (SuiCore$ViewBase *  self, float  x, float  y);
	SuiCore$ViewBase *  (*hitTest) (SuiCore$ViewBase *  self, float  x, float  y);
	SuiCore$ViewBase *  (*hitTestChildren) (SuiCore$ViewBase *  self, float  x, float  y);
	int  (*viewIndexOf) (SuiCore$ViewBase *  self, SuiCore$Node *  child);
	int  (*viewIndexInParent) (SuiCore$ViewBase *  self);
	void  (*markLayoutStart) (SuiCore$ViewBase *  self);
	void  (*printLayoutTimes) (SuiCore$ViewBase *  self, int  tab);
	void  (*layoutContent) (SuiCore$ViewBase *  self, SuiCore$Frame *  contentCtx);
	void  (*layout) (SuiCore$ViewBase *  self, SuiCore$Frame *  ctx);
	void  (*invalidLayout) (SuiCore$ViewBase *  self);
	void  (*draw) (SuiCore$ViewBase *  self, SuiCore$Canvas *  canvas);
	void  (*draw_children) (SuiCore$ViewBase *  self, SuiCore$Canvas *  canvas);
	void  (*draw_self) (SuiCore$ViewBase *  self, SuiCore$Canvas *  canvas);
	void  (*invalidDraw) (SuiCore$ViewBase *  self);
	bool  (*canLayoutByParent) (SuiCore$ViewBase *  self);
	void  (*setVisible) (SuiCore$ViewBase *  self, bool  v);
	void  (*setHover) (SuiCore$ViewBase *  self, bool  v);
	void  (**cbOnHoverChanged)(void *  self);
	void  (*onHoverChanged) (SuiCore$ViewBase *  self);
};
Vtable_SuiCore$ViewBase* Vtable_SuiCore$ViewBase_init(Vtable_SuiCore$ViewBase* pvt);
void SuiCore$ViewBase_init_fields(SuiCore$ViewBase *self);
void SuiCore$ViewBase_init(SuiCore$ViewBase *self, void *pOwner);
SuiCore$ViewBase * SuiCore$ViewBase_new(void *pOwner);
void SuiCore$ViewBase_fini(SuiCore$ViewBase *self);

Orc$List *  SuiCore$ViewBase$gocLayoutCells(SuiCore$ViewBase *  self);
SuiCore$LayoutCell *  SuiCore$ViewBase$getLayoutCellByType(SuiCore$ViewBase *  self, Vtable_Object *  vt);
SuiCore$ViewBase *  SuiCore$ViewBase$getChildViewAt(SuiCore$ViewBase *  self, int  at);
SuiCore$ViewBase *  SuiCore$ViewBase$getChildAsView(SuiCore$ViewBase *  self, int  at);
int  SuiCore$ViewBase$getChildrenViewCount(SuiCore$ViewBase *  self);
SuiCore$Rect SuiCore$ViewBase$getScreenRect(SuiCore$ViewBase *  self);
SuiCore$Rect SuiCore$ViewBase$get_abs_rect(SuiCore$ViewBase *  self);
bool  SuiCore$ViewBase$_hitTestClientRect(SuiCore$ViewBase *  self, SuiCore$Rect *  r, float  x, float  y);
bool  SuiCore$ViewBase$_hitTestSelf(SuiCore$ViewBase *  self, float  x, float  y);
void  SuiCore$ViewBase$_on_invalidLayout(SuiCore$ViewBase *  self);
void  SuiCore$ViewBase$_on_invalidDraw(SuiCore$ViewBase *  self);
void  SuiCore$ViewBase$resetViewTreeDirty(SuiCore$ViewBase *  self);
void  SuiCore$ViewBase$invalidReact(SuiCore$ViewBase *  self);
SuiCore$Vec2 SuiCore$ViewBase$localToWorld(SuiCore$ViewBase *  self, float  x, float  y);
SuiCore$Vec2 SuiCore$ViewBase$worldToLocal(SuiCore$ViewBase *  self, float  x, float  y);
SuiCore$ViewBase *  SuiCore$ViewBase$hitTest(SuiCore$ViewBase *  self, float  x, float  y);
SuiCore$ViewBase *  SuiCore$ViewBase$hitTestChildren(SuiCore$ViewBase *  self, float  x, float  y);
int  SuiCore$ViewBase$viewIndexOf(SuiCore$ViewBase *  self, SuiCore$Node *  child);
int  SuiCore$ViewBase$viewIndexInParent(SuiCore$ViewBase *  self);
void  SuiCore$ViewBase$markLayoutStart(SuiCore$ViewBase *  self);
void  SuiCore$ViewBase$printLayoutTimes(SuiCore$ViewBase *  self, int  tab);
void  SuiCore$ViewBase$layoutContent(SuiCore$ViewBase *  self, SuiCore$Frame *  contentCtx);
void  SuiCore$ViewBase$layout(SuiCore$ViewBase *  self, SuiCore$Frame *  ctx);
void  SuiCore$ViewBase$invalidLayout(SuiCore$ViewBase *  self);
void  SuiCore$ViewBase$draw(SuiCore$ViewBase *  self, SuiCore$Canvas *  canvas);
void  SuiCore$ViewBase$draw_children(SuiCore$ViewBase *  self, SuiCore$Canvas *  canvas);
void  SuiCore$ViewBase$draw_self(SuiCore$ViewBase *  self, SuiCore$Canvas *  canvas);
void  SuiCore$ViewBase$invalidDraw(SuiCore$ViewBase *  self);
bool  SuiCore$ViewBase$canLayoutByParent(SuiCore$ViewBase *  self);
void  SuiCore$ViewBase$setVisible(SuiCore$ViewBase *  self, bool  v);
void  SuiCore$ViewBase$setHover(SuiCore$ViewBase *  self, bool  v);
void  SuiCore$ViewBase$onHoverChanged(SuiCore$ViewBase *  self);
Orc$String*  SuiCore$ViewBase$toString(Orc$String **  __outRef__, SuiCore$ViewBase *  self);

SuiCore$ViewBase *  SuiCore$hitTestChildren_withZ(SuiCore$ViewBase *  ins, float  x, float  y);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
