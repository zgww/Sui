
typedef struct tagSuiView$Panel SuiView$Panel;
typedef struct tagVtable_SuiView$Panel Vtable_SuiView$Panel;
typedef struct tagSuiView$Panel2 SuiView$Panel2;
typedef struct tagVtable_SuiView$Panel2 Vtable_SuiView$Panel2;


#ifndef define_struct___SuiView__Panel_orc_h__
#define define_struct___SuiView__Panel_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__Panel_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__Panel_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__Panel_orc_h__
#define __SuiView__Panel_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/ImageView_orc.h"
#include "../View/TextView_orc.h"
#include "../View/ViewBuilder_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../SuiDesigner/Theme_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$Panel {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$Panel _vtable_SuiView$Panel;

// class refc:0
struct tagSuiView$Panel {
	SuiLayout$LayoutLinear super; 
	void  (**cbRenderTitle)(void *  self, SuiCore$Node *  o);
	void  (**cbRenderContent)(void *  self, SuiCore$Node *  o);
	Orc$String*  title ;
	bool  open ;
	SuiCore$View*  body ;
	int  titleColor ;
	int  titleFontSize ;
	void  (*onEvent_forHead) (SuiView$Panel *  self, SuiCore$Event *  e);
	void  (*onClick_inHead) (SuiView$Panel *  self, SuiCore$MouseEvent *  e);
	void  (*setOpen) (SuiView$Panel *  self, bool  v);
};
Vtable_SuiView$Panel* Vtable_SuiView$Panel_init(Vtable_SuiView$Panel* pvt);
void SuiView$Panel_init_fields(SuiView$Panel *self);
void SuiView$Panel_init(SuiView$Panel *self, void *pOwner);
SuiView$Panel * SuiView$Panel_new(void *pOwner);
void SuiView$Panel_fini(SuiView$Panel *self);

void  SuiView$Panel$onEvent_forHead(SuiView$Panel *  self, SuiCore$Event *  e);
void  SuiView$Panel$onClick_inHead(SuiView$Panel *  self, SuiCore$MouseEvent *  e);
void  SuiView$Panel$setOpen(SuiView$Panel *  self, bool  v);
void  SuiView$Panel$react(SuiView$Panel *  self);


// 虚表
struct tagVtable_SuiView$Panel2 {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$Panel2 _vtable_SuiView$Panel2;

// class refc:0
struct tagSuiView$Panel2 {
	SuiLayout$LayoutLinear super; 
	void  (**cbRenderTitle)(void *  self, SuiCore$Node *  o);
	Orc$String*  title ;
	bool  open ;
	void  (*onEvent_forHead) (SuiView$Panel2 *  self, SuiCore$Event *  e);
	void  (*onClick_inHead) (SuiView$Panel2 *  self, SuiCore$MouseEvent *  e);
	void  (*setOpen) (SuiView$Panel2 *  self, bool  v);
};
Vtable_SuiView$Panel2* Vtable_SuiView$Panel2_init(Vtable_SuiView$Panel2* pvt);
void SuiView$Panel2_init_fields(SuiView$Panel2 *self);
void SuiView$Panel2_init(SuiView$Panel2 *self, void *pOwner);
SuiView$Panel2 * SuiView$Panel2_new(void *pOwner);
void SuiView$Panel2_fini(SuiView$Panel2 *self);

void  SuiView$Panel2$ctor(SuiView$Panel2 *  self);
void  SuiView$Panel2$onEvent_forHead(SuiView$Panel2 *  self, SuiCore$Event *  e);
void  SuiView$Panel2$onClick_inHead(SuiView$Panel2 *  self, SuiCore$MouseEvent *  e);
void  SuiView$Panel2$setOpen(SuiView$Panel2 *  self, bool  v);
void  SuiView$Panel2$react(SuiView$Panel2 *  self);

SuiView$Panel*  SuiView$mkPanel(SuiView$Panel **  __outRef__, void *  parent, long long  key);
SuiView$Panel2*  SuiView$mkPanel2(SuiView$Panel2 **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
