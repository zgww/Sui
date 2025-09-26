
typedef struct tagSuiLayout$RowWrap SuiLayout$RowWrap;
typedef struct tagVtable_SuiLayout$RowWrap Vtable_SuiLayout$RowWrap;


#ifndef define_struct___SuiLayout__RowWrap_orc_h__
#define define_struct___SuiLayout__RowWrap_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiLayout__RowWrap_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiLayout__RowWrap_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiLayout__RowWrap_orc_h__
#define __SuiLayout__RowWrap_orc_h__

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
struct tagVtable_SuiLayout$RowWrap {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiLayout$RowWrap _vtable_SuiLayout$RowWrap;

// class refc:0
struct tagSuiLayout$RowWrap {
	SuiCore$View super; 
	void  (*alignItems_ofRow) (SuiLayout$RowWrap *  self, int  rowStartIdx, int  rowEndIdx, float  rowHeight);
	void  (*positionChildren) (SuiLayout$RowWrap *  self, SuiCore$Frame *  ctx);
	Orc$String*  alignItems ;
	float  rowGap ;
	float  colGap ;
};
Vtable_SuiLayout$RowWrap* Vtable_SuiLayout$RowWrap_init(Vtable_SuiLayout$RowWrap* pvt);
void SuiLayout$RowWrap_init_fields(SuiLayout$RowWrap *self);
void SuiLayout$RowWrap_init(SuiLayout$RowWrap *self, void *pOwner);
SuiLayout$RowWrap * SuiLayout$RowWrap_new(void *pOwner);
void SuiLayout$RowWrap_fini(SuiLayout$RowWrap *self);

void  SuiLayout$RowWrap$alignItems_ofRow(SuiLayout$RowWrap *  self, int  rowStartIdx, int  rowEndIdx, float  rowHeight);
void  SuiLayout$RowWrap$positionChildren(SuiLayout$RowWrap *  self, SuiCore$Frame *  ctx);
void  SuiLayout$RowWrap$layoutContent(SuiLayout$RowWrap *  self, SuiCore$Frame *  contentCtx);

SuiLayout$RowWrap*  SuiLayout$mkRowWrap(SuiLayout$RowWrap **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
