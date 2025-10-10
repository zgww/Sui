
typedef struct tagSuiLayout$LayoutLinearCell SuiLayout$LayoutLinearCell;
typedef struct tagVtable_SuiLayout$LayoutLinearCell Vtable_SuiLayout$LayoutLinearCell;
typedef struct tagSuiLayout$LayoutLinear SuiLayout$LayoutLinear;
typedef struct tagVtable_SuiLayout$LayoutLinear Vtable_SuiLayout$LayoutLinear;


#ifndef define_struct___SuiLayout__LayoutLinear_orc_h__
#define define_struct___SuiLayout__LayoutLinear_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiLayout__LayoutLinear_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiLayout__LayoutLinear_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiLayout__LayoutLinear_orc_h__
#define __SuiLayout__LayoutLinear_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
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
struct tagVtable_SuiLayout$LayoutLinearCell {
	Vtable_SuiCore$LayoutCell super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutLinearCell _vtable_SuiLayout$LayoutLinearCell;

// class refc:0
struct tagSuiLayout$LayoutLinearCell {
	SuiCore$LayoutCell super; 
	float  grow ;
	Orc$String*  alignSelf ;
};
Vtable_SuiLayout$LayoutLinearCell* Vtable_SuiLayout$LayoutLinearCell_init(Vtable_SuiLayout$LayoutLinearCell* pvt);
void SuiLayout$LayoutLinearCell_init_fields(SuiLayout$LayoutLinearCell *self);
void SuiLayout$LayoutLinearCell_init(SuiLayout$LayoutLinearCell *self, void *pOwner);
SuiLayout$LayoutLinearCell * SuiLayout$LayoutLinearCell_new(void *pOwner);
void SuiLayout$LayoutLinearCell_fini(SuiLayout$LayoutLinearCell *self);

void  SuiLayout$LayoutLinearCell$dtor(SuiLayout$LayoutLinearCell *  self);


// 虚表
struct tagVtable_SuiLayout$LayoutLinear {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutLinear _vtable_SuiLayout$LayoutLinear;

// class refc:0
struct tagSuiLayout$LayoutLinear {
	SuiCore$View super; 
	bool  (*isMax_in_maxOrStretch) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx, bool  isHor);
	void  (*layoutCross) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);
	bool  (*calcIsHor) (SuiLayout$LayoutLinear *  self);
	Orc$String *  (*getCrossAlign_ofKid) (SuiLayout$LayoutLinear *  self, SuiCore$ViewBase *  view);
	void  (*positionChildren) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);
	void  (*setMainConstraints) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor, float  minV, float  maxV);
	void  (*setCrossConstraints) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor, float  minV, float  maxV);
	float  (*getMainMaxConstraint) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor);
	float  (*getCrossMaxConstraint) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor);
	void  (*update_maxCrossSize) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor);
	bool  (*layout_mainInf) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);
	bool  (*layout_mainLimit) (SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);
	Orc$String*  direction ;
	Orc$String*  justifyContent ;
	Orc$String*  alignItems ;
	SuiLayout$LayoutLinear *  (*jcc) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*jcs) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*jce) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*jcsb) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*jcsa) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*jcse) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*ais) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*aic) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*aie) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*aiStretch) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*aiMaxOrStretch) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*column) (SuiLayout$LayoutLinear *  self);
	SuiLayout$LayoutLinear *  (*row) (SuiLayout$LayoutLinear *  self);
	float  maxCrossSize ;
};
Vtable_SuiLayout$LayoutLinear* Vtable_SuiLayout$LayoutLinear_init(Vtable_SuiLayout$LayoutLinear* pvt);
void SuiLayout$LayoutLinear_init_fields(SuiLayout$LayoutLinear *self);
void SuiLayout$LayoutLinear_init(SuiLayout$LayoutLinear *self, void *pOwner);
SuiLayout$LayoutLinear * SuiLayout$LayoutLinear_new(void *pOwner);
void SuiLayout$LayoutLinear_fini(SuiLayout$LayoutLinear *self);

bool  SuiLayout$LayoutLinear$isMax_in_maxOrStretch(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx, bool  isHor);
void  SuiLayout$LayoutLinear$layoutCross(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);
bool  SuiLayout$LayoutLinear$calcIsHor(SuiLayout$LayoutLinear *  self);
Orc$String *  SuiLayout$LayoutLinear$getCrossAlign_ofKid(SuiLayout$LayoutLinear *  self, SuiCore$ViewBase *  view);
void  SuiLayout$LayoutLinear$positionChildren(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);
void  SuiLayout$LayoutLinear$setMainConstraints(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor, float  minV, float  maxV);
void  SuiLayout$LayoutLinear$setCrossConstraints(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor, float  minV, float  maxV);
float  SuiLayout$LayoutLinear$getMainMaxConstraint(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor);
float  SuiLayout$LayoutLinear$getCrossMaxConstraint(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor);
void  SuiLayout$LayoutLinear$update_maxCrossSize(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor);
bool  SuiLayout$LayoutLinear$layout_mainInf(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);
bool  SuiLayout$LayoutLinear$layout_mainLimit(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);
void  SuiLayout$LayoutLinear$layoutContent(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcc(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcs(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jce(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcsb(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcsa(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcse(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$ais(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$aic(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$aie(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$aiStretch(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$aiMaxOrStretch(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$column(SuiLayout$LayoutLinear *  self);
SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$row(SuiLayout$LayoutLinear *  self);
void  SuiLayout$LayoutLinear$layout(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx);

SuiLayout$LayoutLinear*  SuiLayout$layoutLinear(SuiLayout$LayoutLinear **  __outRef__, void *  parent, long long  key);
SuiLayout$LayoutLinearCell*  SuiLayout$layoutLinearCell(SuiLayout$LayoutLinearCell **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
