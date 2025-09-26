
typedef struct tagSuiLayout$LayoutAlignPositionCell SuiLayout$LayoutAlignPositionCell;
typedef struct tagVtable_SuiLayout$LayoutAlignPositionCell Vtable_SuiLayout$LayoutAlignPositionCell;
typedef struct tagSuiLayout$LayoutAlignCell SuiLayout$LayoutAlignCell;
typedef struct tagVtable_SuiLayout$LayoutAlignCell Vtable_SuiLayout$LayoutAlignCell;
typedef struct tagSuiLayout$LayoutAlign SuiLayout$LayoutAlign;
typedef struct tagVtable_SuiLayout$LayoutAlign Vtable_SuiLayout$LayoutAlign;


#ifndef define_struct___SuiLayout__LayoutAlign_orc_h__
#define define_struct___SuiLayout__LayoutAlign_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiLayout__LayoutAlign_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiLayout__LayoutAlign_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiLayout__LayoutAlign_orc_h__
#define __SuiLayout__LayoutAlign_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/LayoutCell_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/List_orc.h"
#include "../View/ViewBuilder_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiLayout$LayoutAlignPositionCell {
	Vtable_SuiCore$LayoutCell super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutAlignPositionCell _vtable_SuiLayout$LayoutAlignPositionCell;

// class refc:0
struct tagSuiLayout$LayoutAlignPositionCell {
	SuiCore$LayoutCell super; 
	float  left ;
	float  top ;
	float  right ;
	float  bottom ;
};
Vtable_SuiLayout$LayoutAlignPositionCell* Vtable_SuiLayout$LayoutAlignPositionCell_init(Vtable_SuiLayout$LayoutAlignPositionCell* pvt);
void SuiLayout$LayoutAlignPositionCell_init_fields(SuiLayout$LayoutAlignPositionCell *self);
void SuiLayout$LayoutAlignPositionCell_init(SuiLayout$LayoutAlignPositionCell *self, void *pOwner);
SuiLayout$LayoutAlignPositionCell * SuiLayout$LayoutAlignPositionCell_new(void *pOwner);
void SuiLayout$LayoutAlignPositionCell_fini(SuiLayout$LayoutAlignPositionCell *self);



// 虚表
struct tagVtable_SuiLayout$LayoutAlignCell {
	Vtable_SuiCore$LayoutCell super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutAlignCell _vtable_SuiLayout$LayoutAlignCell;

// class refc:0
struct tagSuiLayout$LayoutAlignCell {
	SuiCore$LayoutCell super; 
	SuiCore$Vec2 anchor ;
	SuiCore$Vec2 align ;
	SuiCore$Vec2 sizeRatio ;
	void  (*setSameRatio) (SuiLayout$LayoutAlignCell *  self, float  x, float  y);
	void  (*setTopLeft) (SuiLayout$LayoutAlignCell *  self);
	void  (*setTopCenter) (SuiLayout$LayoutAlignCell *  self);
	void  (*setTopRight) (SuiLayout$LayoutAlignCell *  self);
	void  (*setBottomLeft) (SuiLayout$LayoutAlignCell *  self);
	void  (*setBottomCenter) (SuiLayout$LayoutAlignCell *  self);
	void  (*setBottomRight) (SuiLayout$LayoutAlignCell *  self);
	void  (*setMiddleLeft) (SuiLayout$LayoutAlignCell *  self);
	void  (*setCenter) (SuiLayout$LayoutAlignCell *  self);
	void  (*setMiddleRight) (SuiLayout$LayoutAlignCell *  self);
};
Vtable_SuiLayout$LayoutAlignCell* Vtable_SuiLayout$LayoutAlignCell_init(Vtable_SuiLayout$LayoutAlignCell* pvt);
void SuiLayout$LayoutAlignCell_init_fields(SuiLayout$LayoutAlignCell *self);
void SuiLayout$LayoutAlignCell_init(SuiLayout$LayoutAlignCell *self, void *pOwner);
SuiLayout$LayoutAlignCell * SuiLayout$LayoutAlignCell_new(void *pOwner);
void SuiLayout$LayoutAlignCell_fini(SuiLayout$LayoutAlignCell *self);

void  SuiLayout$LayoutAlignCell$setSameRatio(SuiLayout$LayoutAlignCell *  self, float  x, float  y);
void  SuiLayout$LayoutAlignCell$setTopLeft(SuiLayout$LayoutAlignCell *  self);
void  SuiLayout$LayoutAlignCell$setTopCenter(SuiLayout$LayoutAlignCell *  self);
void  SuiLayout$LayoutAlignCell$setTopRight(SuiLayout$LayoutAlignCell *  self);
void  SuiLayout$LayoutAlignCell$setBottomLeft(SuiLayout$LayoutAlignCell *  self);
void  SuiLayout$LayoutAlignCell$setBottomCenter(SuiLayout$LayoutAlignCell *  self);
void  SuiLayout$LayoutAlignCell$setBottomRight(SuiLayout$LayoutAlignCell *  self);
void  SuiLayout$LayoutAlignCell$setMiddleLeft(SuiLayout$LayoutAlignCell *  self);
void  SuiLayout$LayoutAlignCell$setCenter(SuiLayout$LayoutAlignCell *  self);
void  SuiLayout$LayoutAlignCell$setMiddleRight(SuiLayout$LayoutAlignCell *  self);


// 虚表
struct tagVtable_SuiLayout$LayoutAlign {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutAlign _vtable_SuiLayout$LayoutAlign;

// class refc:0
struct tagSuiLayout$LayoutAlign {
	SuiCore$View super; 
	SuiCore$Vec2 anchor ;
	SuiCore$Vec2 align ;
	bool  useMaxConstraint ;
	void  (*setSameRatio) (SuiLayout$LayoutAlign *  self, float  x, float  y);
	void  (*setTopLeft) (SuiLayout$LayoutAlign *  self);
	void  (*setTopCenter) (SuiLayout$LayoutAlign *  self);
	void  (*setTopRight) (SuiLayout$LayoutAlign *  self);
	void  (*setBottomLeft) (SuiLayout$LayoutAlign *  self);
	void  (*setBottomCenter) (SuiLayout$LayoutAlign *  self);
	void  (*setBottomRight) (SuiLayout$LayoutAlign *  self);
	void  (*setMiddleLeft) (SuiLayout$LayoutAlign *  self);
	void  (*setCenter) (SuiLayout$LayoutAlign *  self);
	void  (*setMiddleRight) (SuiLayout$LayoutAlign *  self);
	void  (*getAnchorAndAlign_byView) (SuiLayout$LayoutAlign *  self, SuiCore$ViewBase *  view, SuiCore$Vec2 *  anchor, SuiCore$Vec2 *  align);
};
Vtable_SuiLayout$LayoutAlign* Vtable_SuiLayout$LayoutAlign_init(Vtable_SuiLayout$LayoutAlign* pvt);
void SuiLayout$LayoutAlign_init_fields(SuiLayout$LayoutAlign *self);
void SuiLayout$LayoutAlign_init(SuiLayout$LayoutAlign *self, void *pOwner);
SuiLayout$LayoutAlign * SuiLayout$LayoutAlign_new(void *pOwner);
void SuiLayout$LayoutAlign_fini(SuiLayout$LayoutAlign *self);

void  SuiLayout$LayoutAlign$setSameRatio(SuiLayout$LayoutAlign *  self, float  x, float  y);
void  SuiLayout$LayoutAlign$setTopLeft(SuiLayout$LayoutAlign *  self);
void  SuiLayout$LayoutAlign$setTopCenter(SuiLayout$LayoutAlign *  self);
void  SuiLayout$LayoutAlign$setTopRight(SuiLayout$LayoutAlign *  self);
void  SuiLayout$LayoutAlign$setBottomLeft(SuiLayout$LayoutAlign *  self);
void  SuiLayout$LayoutAlign$setBottomCenter(SuiLayout$LayoutAlign *  self);
void  SuiLayout$LayoutAlign$setBottomRight(SuiLayout$LayoutAlign *  self);
void  SuiLayout$LayoutAlign$setMiddleLeft(SuiLayout$LayoutAlign *  self);
void  SuiLayout$LayoutAlign$setCenter(SuiLayout$LayoutAlign *  self);
void  SuiLayout$LayoutAlign$setMiddleRight(SuiLayout$LayoutAlign *  self);
void  SuiLayout$LayoutAlign$layoutContent(SuiLayout$LayoutAlign *  self, SuiCore$Frame *  ctx);
void  SuiLayout$LayoutAlign$getAnchorAndAlign_byView(SuiLayout$LayoutAlign *  self, SuiCore$ViewBase *  view, SuiCore$Vec2 *  anchor, SuiCore$Vec2 *  align);

SuiLayout$LayoutAlign*  SuiLayout$layoutAlign(SuiLayout$LayoutAlign **  __outRef__, void *  parent, long long  key);
SuiLayout$LayoutAlignCell*  SuiLayout$layoutAlignCell(SuiLayout$LayoutAlignCell **  __outRef__, void *  parent, long long  key);
SuiLayout$LayoutAlignPositionCell*  SuiLayout$layoutAlignPositionCell(SuiLayout$LayoutAlignPositionCell **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
