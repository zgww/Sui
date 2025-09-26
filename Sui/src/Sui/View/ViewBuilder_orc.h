
typedef struct tagSuiView$TestPlaceView SuiView$TestPlaceView;
typedef struct tagVtable_SuiView$TestPlaceView Vtable_SuiView$TestPlaceView;


#ifndef define_struct___SuiView__ViewBuilder_orc_h__
#define define_struct___SuiView__ViewBuilder_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__ViewBuilder_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__ViewBuilder_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__ViewBuilder_orc_h__
#define __SuiView__ViewBuilder_orc_h__

//include  importHeadCode
#include "../../Orc/ScopeData_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Map_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Emitter_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/Window_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../Layout/LayoutLinear_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
SuiCore$Node*  SuiView$gocNode(SuiCore$Node **  __outRef__, void *  sp, SuiCore$Node *  parent, Vtable_Object *  vt);
SuiCore$View*  SuiView$mkView(SuiCore$View **  __outRef__, void *  parent, long long  key);

// 虚表
struct tagVtable_SuiView$TestPlaceView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$TestPlaceView _vtable_SuiView$TestPlaceView;

// class refc:0
struct tagSuiView$TestPlaceView {
	SuiCore$View super; 
	
};
Vtable_SuiView$TestPlaceView* Vtable_SuiView$TestPlaceView_init(Vtable_SuiView$TestPlaceView* pvt);
void SuiView$TestPlaceView_init_fields(SuiView$TestPlaceView *self);
void SuiView$TestPlaceView_init(SuiView$TestPlaceView *self, void *pOwner);
SuiView$TestPlaceView * SuiView$TestPlaceView_new(void *pOwner);
void SuiView$TestPlaceView_fini(SuiView$TestPlaceView *self);

void  SuiView$TestPlaceView$ctor(SuiView$TestPlaceView *  self);
void  SuiView$TestPlaceView$react(SuiView$TestPlaceView *  self);

SuiView$TestPlaceView*  SuiView$mkTestPlaceView(SuiView$TestPlaceView **  __outRef__, void *  parent, long long  key);
void  SuiView$testPlaceKidsTo();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
