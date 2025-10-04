
typedef struct tagSuiView$Button SuiView$Button;
typedef struct tagVtable_SuiView$Button Vtable_SuiView$Button;
typedef struct tagSuiView$DrawButton SuiView$DrawButton;
typedef struct tagVtable_SuiView$DrawButton Vtable_SuiView$DrawButton;
typedef struct tagSuiView$MenuButton SuiView$MenuButton;
typedef struct tagVtable_SuiView$MenuButton Vtable_SuiView$MenuButton;


#ifndef define_struct___SuiView__Button_orc_h__
#define define_struct___SuiView__Button_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__Button_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__Button_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__Button_orc_h__
#define __SuiView__Button_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/ImageView_orc.h"
#include "../Core/Canvas_orc.h"
#include "../View/TextView_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/Inset_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../../SuiDesigner/Inspector_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "../../SuiDesigner/Theme_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$Button {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$Button _vtable_SuiView$Button;

// class refc:0
struct tagSuiView$Button {
	SuiLayout$LayoutLinear super; 
	int  labelColor ;
	Orc$String*  label ;
	void  (*setLabel) (SuiView$Button *  self, Orc$String*  v);
	Orc$String*  src ;
	void  (*setSrc) (SuiView$Button *  self, Orc$String*  v);
	bool  in_group ;
	void  (*setIn_group) (SuiView$Button *  self, bool  v);
	bool  checked ;
	void  (*setChecked) (SuiView$Button *  self, bool  v);
	void  (**onClick)(void *  self, SuiCore$MouseEvent *  me);
};
Vtable_SuiView$Button* Vtable_SuiView$Button_init(Vtable_SuiView$Button* pvt);
void SuiView$Button_init_fields(SuiView$Button *self);
void SuiView$Button_init(SuiView$Button *self, void *pOwner);
SuiView$Button * SuiView$Button_new(void *pOwner);
void SuiView$Button_fini(SuiView$Button *self);

void  SuiView$Button$ctor(SuiView$Button *  self);
void  SuiView$Button$react(SuiView$Button *  self);
void  SuiView$Button$onEvent(SuiView$Button *  self, SuiCore$Event *  ev);
void  SuiView$Button$setLabel(SuiView$Button *  self, Orc$String*  v);
void  SuiView$Button$setSrc(SuiView$Button *  self, Orc$String*  v);
void  SuiView$Button$setIn_group(SuiView$Button *  self, bool  v);
void  SuiView$Button$setChecked(SuiView$Button *  self, bool  v);


// 虚表
struct tagVtable_SuiView$DrawButton {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$DrawButton _vtable_SuiView$DrawButton;

// class refc:0
struct tagSuiView$DrawButton {
	SuiLayout$LayoutLinear super; 
	Orc$String*  text ;
	Orc$String*  src ;
	int  normalBg ;
	int  hoverBg ;
	int  activeBg ;
	int  color ;
	int  activeColor ;
	int  hoverColor ;
	bool  isActive ;
	void  (*typePrimary) (SuiView$DrawButton *  self);
	void  (**onClick)(void *  self, SuiCore$MouseEvent *  me);
};
Vtable_SuiView$DrawButton* Vtable_SuiView$DrawButton_init(Vtable_SuiView$DrawButton* pvt);
void SuiView$DrawButton_init_fields(SuiView$DrawButton *self);
void SuiView$DrawButton_init(SuiView$DrawButton *self, void *pOwner);
SuiView$DrawButton * SuiView$DrawButton_new(void *pOwner);
void SuiView$DrawButton_fini(SuiView$DrawButton *self);

void  SuiView$DrawButton$typePrimary(SuiView$DrawButton *  self);
void  SuiView$DrawButton$ctor(SuiView$DrawButton *  self);
void  SuiView$DrawButton$onHoverChanged(SuiView$DrawButton *  self);
void  SuiView$DrawButton$react(SuiView$DrawButton *  self);
void  SuiView$DrawButton$draw_self(SuiView$DrawButton *  self, SuiCore$Canvas *  canvas);
void  SuiView$DrawButton$onEvent(SuiView$DrawButton *  self, SuiCore$Event *  ev);


// 虚表
struct tagVtable_SuiView$MenuButton {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$MenuButton _vtable_SuiView$MenuButton;

// class refc:0
struct tagSuiView$MenuButton {
	SuiLayout$LayoutLinear super; 
	Orc$String*  text ;
	int  normalBackgroundcolor ;
	int  hoverBackgroundcolor ;
	void  (**onClick)(void *  self, SuiCore$MouseEvent *  me);
	void  (**onMouseMove)(void *  self, SuiCore$MouseEvent *  me);
};
Vtable_SuiView$MenuButton* Vtable_SuiView$MenuButton_init(Vtable_SuiView$MenuButton* pvt);
void SuiView$MenuButton_init_fields(SuiView$MenuButton *self);
void SuiView$MenuButton_init(SuiView$MenuButton *self, void *pOwner);
SuiView$MenuButton * SuiView$MenuButton_new(void *pOwner);
void SuiView$MenuButton_fini(SuiView$MenuButton *self);

void  SuiView$MenuButton$ctor(SuiView$MenuButton *  self);
void  SuiView$MenuButton$dtor(SuiView$MenuButton *  self);
void  SuiView$MenuButton$onHoverChanged(SuiView$MenuButton *  self);
void  SuiView$MenuButton$draw(SuiView$MenuButton *  self, void *  canvas);
void  SuiView$MenuButton$react(SuiView$MenuButton *  self);
void  SuiView$MenuButton$onEvent(SuiView$MenuButton *  self, SuiCore$Event *  ev);

SuiView$Button*  SuiView$mkButton(SuiView$Button **  __outRef__, void *  parent, long long  key);
SuiView$DrawButton*  SuiView$mkDrawButton(SuiView$DrawButton **  __outRef__, void *  parent, long long  key);
SuiView$MenuButton*  SuiView$mkMenuButton(SuiView$MenuButton **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
