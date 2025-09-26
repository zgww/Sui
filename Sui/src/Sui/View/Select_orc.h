
typedef struct tagSuiView$Select SuiView$Select;
typedef struct tagVtable_SuiView$Select Vtable_SuiView$Select;


#ifndef define_struct___SuiView__Select_orc_h__
#define define_struct___SuiView__Select_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__Select_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__Select_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__Select_orc_h__
#define __SuiView__Select_orc_h__

//include  importHeadCode
#include "../Core/Node_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Timer_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Mouse_orc.h"
#include "../Core/Cursor_orc.h"
#include "./ViewBuilder_orc.h"
#include "./TextView_orc.h"
#include "./MenuNative_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Dialog/MessageDialog_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$Select {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$Select _vtable_SuiView$Select;

// class refc:0
struct tagSuiView$Select {
	SuiLayout$LayoutLinear super; 
	bool  isActive ;
	Orc$List*  options ;
	int  value ;
	void  (**onChanged)(void *  self, int  i, Orc$String*  label);
	void  (*fire_onChanged) (SuiView$Select *  self);
	void  (*appendOptionCStr) (SuiView$Select *  self, const char *  text);
	void  (*appendOption) (SuiView$Select *  self, Orc$String *  text);
	void  (*setIsActive) (SuiView$Select *  self, bool  v);
	void  (*setValue) (SuiView$Select *  self, int  i);
	void  (*showPopupMenu) (SuiView$Select *  self);
};
Vtable_SuiView$Select* Vtable_SuiView$Select_init(Vtable_SuiView$Select* pvt);
void SuiView$Select_init_fields(SuiView$Select *self);
void SuiView$Select_init(SuiView$Select *self, void *pOwner);
SuiView$Select * SuiView$Select_new(void *pOwner);
void SuiView$Select_fini(SuiView$Select *self);

void  SuiView$Select$fire_onChanged(SuiView$Select *  self);
void  SuiView$Select$ctor(SuiView$Select *  self);
void  SuiView$Select$appendOptionCStr(SuiView$Select *  self, const char *  text);
void  SuiView$Select$appendOption(SuiView$Select *  self, Orc$String *  text);
void  SuiView$Select$react(SuiView$Select *  self);
void  SuiView$Select$setIsActive(SuiView$Select *  self, bool  v);
void  SuiView$Select$setValue(SuiView$Select *  self, int  i);
void  SuiView$Select$showPopupMenu(SuiView$Select *  self);
void  SuiView$Select$onEvent(SuiView$Select *  self, SuiCore$Event *  ev);

SuiView$Select*  SuiView$mkSelect(SuiView$Select **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
