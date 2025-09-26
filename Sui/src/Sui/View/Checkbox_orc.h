
typedef struct tagSuiView$Checkbox SuiView$Checkbox;
typedef struct tagVtable_SuiView$Checkbox Vtable_SuiView$Checkbox;


#ifndef define_struct___SuiView__Checkbox_orc_h__
#define define_struct___SuiView__Checkbox_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__Checkbox_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__Checkbox_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__Checkbox_orc_h__
#define __SuiView__Checkbox_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../View/ImageView_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/MouseEvent_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$Checkbox {
	Vtable_SuiView$ImageView super;
};
//虚表实例
extern Vtable_SuiView$Checkbox _vtable_SuiView$Checkbox;

// class refc:0
struct tagSuiView$Checkbox {
	SuiView$ImageView super; 
	Orc$String*  onSrc ;
	Orc$String*  offSrc ;
	bool  checked ;
	void  (*setChecked) (SuiView$Checkbox *  self, bool  v);
};
Vtable_SuiView$Checkbox* Vtable_SuiView$Checkbox_init(Vtable_SuiView$Checkbox* pvt);
void SuiView$Checkbox_init_fields(SuiView$Checkbox *self);
void SuiView$Checkbox_init(SuiView$Checkbox *self, void *pOwner);
SuiView$Checkbox * SuiView$Checkbox_new(void *pOwner);
void SuiView$Checkbox_fini(SuiView$Checkbox *self);

void  SuiView$Checkbox$ctor(SuiView$Checkbox *  self);
void  SuiView$Checkbox$setChecked(SuiView$Checkbox *  self, bool  v);
void  SuiView$Checkbox$onEvent(SuiView$Checkbox *  self, SuiCore$Event *  ev);

SuiView$Checkbox*  SuiView$checkbox(SuiView$Checkbox **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
