
typedef struct tagSuiCore$LayoutCell SuiCore$LayoutCell;
typedef struct tagVtable_SuiCore$LayoutCell Vtable_SuiCore$LayoutCell;


#ifndef define_struct___SuiCore__LayoutCell_orc_h__
#define define_struct___SuiCore__LayoutCell_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__LayoutCell_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__LayoutCell_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__LayoutCell_orc_h__
#define __SuiCore__LayoutCell_orc_h__

//include  importHeadCode
#include "../../Orc/List_orc.h"
#include "./Node_orc.h"
#include "./ViewBase_orc.h"
#include "./Frame_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$LayoutCell {
	Vtable_SuiCore$Node super;
};
//虚表实例
extern Vtable_SuiCore$LayoutCell _vtable_SuiCore$LayoutCell;

// class refc:0
struct tagSuiCore$LayoutCell {
	SuiCore$Node super; 
	void  (*invalidLayout) (SuiCore$LayoutCell *  self);
};
Vtable_SuiCore$LayoutCell* Vtable_SuiCore$LayoutCell_init(Vtable_SuiCore$LayoutCell* pvt);
void SuiCore$LayoutCell_init_fields(SuiCore$LayoutCell *self);
void SuiCore$LayoutCell_init(SuiCore$LayoutCell *self, void *pOwner);
SuiCore$LayoutCell * SuiCore$LayoutCell_new(void *pOwner);
void SuiCore$LayoutCell_fini(SuiCore$LayoutCell *self);

void  SuiCore$LayoutCell$invalidLayout(SuiCore$LayoutCell *  self);
void  SuiCore$LayoutCell$onMounted(SuiCore$LayoutCell *  self);
void  SuiCore$LayoutCell$onUnmounting(SuiCore$LayoutCell *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
