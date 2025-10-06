
typedef struct tagSuiView$TreeState SuiView$TreeState;
typedef struct tagVtable_SuiView$TreeState Vtable_SuiView$TreeState;
typedef struct tagSuiView$TreeView SuiView$TreeView;
typedef struct tagVtable_SuiView$TreeView Vtable_SuiView$TreeView;


#ifndef define_struct___SuiView__TreeView_orc_h__
#define define_struct___SuiView__TreeView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__TreeView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__TreeView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__TreeView_orc_h__
#define __SuiView__TreeView_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../Core/Node_orc.h"
#include "./ViewBuilder_orc.h"
#include "./TextView_orc.h"
#include "./HoverViewEffect_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/String_orc.h"
#include "../Dialog/MessageDialog_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$TreeState {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$TreeState _vtable_SuiView$TreeState;

// class refc:0
struct tagSuiView$TreeState {
	Object super; 
	Orc$List*  roots ;
	Orc$String*  (**getId)(Orc$String **  __outRef__, void *  self, Object *  item);
	Orc$List*  (**getItemChildren)(Orc$List **  __outRef__, void *  self, Object *  item);
	void  (**cbSelectedIdChanged)(void *  self, SuiView$TreeState *  state);
	Object *  (**getParent)(void *  self, Object *  item);
	Orc$List*  selectedIds ;
	Orc$List*  opendIds ;
	Object *  (*getById) (SuiView$TreeState *  self, Orc$String*  id);
	void  (*_flatTree) (SuiView$TreeState *  self, Orc$List*  items, Orc$List *  out);
	Orc$List*  (*flatTree) (Orc$List **  __outRef__, SuiView$TreeState *  self);
	Object *  (*_getById) (SuiView$TreeState *  self, Orc$String*  id, Orc$List *  list);
	Object *  (*getFirstSelected) (SuiView$TreeState *  self);
	bool  (*isSelected) (SuiView$TreeState *  self, Object *  item);
	bool  (*isOpend) (SuiView$TreeState *  self, Object *  item);
	void  (*setSelectedWithShiftAndCtrl) (SuiView$TreeState *  self, Object *  item, bool  shift, bool  ctrl);
	void  (*fire_cbSelectedIdChanged) (SuiView$TreeState *  self);
	void  (*setAncestorsOpen) (SuiView$TreeState *  self, Object *  item);
	void  (*setSelected) (SuiView$TreeState *  self, Object *  item);
	void  (*setOpen) (SuiView$TreeState *  self, Object *  item, bool  open);
};
Vtable_SuiView$TreeState* Vtable_SuiView$TreeState_init(Vtable_SuiView$TreeState* pvt);
void SuiView$TreeState_init_fields(SuiView$TreeState *self);
void SuiView$TreeState_init(SuiView$TreeState *self, void *pOwner);
SuiView$TreeState * SuiView$TreeState_new(void *pOwner);
void SuiView$TreeState_fini(SuiView$TreeState *self);

Object *  SuiView$TreeState$getById(SuiView$TreeState *  self, Orc$String*  id);
void  SuiView$TreeState$_flatTree(SuiView$TreeState *  self, Orc$List*  items, Orc$List *  out);
Orc$List*  SuiView$TreeState$flatTree(Orc$List **  __outRef__, SuiView$TreeState *  self);
Object *  SuiView$TreeState$_getById(SuiView$TreeState *  self, Orc$String*  id, Orc$List *  list);
Object *  SuiView$TreeState$getFirstSelected(SuiView$TreeState *  self);
bool  SuiView$TreeState$isSelected(SuiView$TreeState *  self, Object *  item);
bool  SuiView$TreeState$isOpend(SuiView$TreeState *  self, Object *  item);
void  SuiView$TreeState$setSelectedWithShiftAndCtrl(SuiView$TreeState *  self, Object *  item, bool  shift, bool  ctrl);
void  SuiView$TreeState$fire_cbSelectedIdChanged(SuiView$TreeState *  self);
void  SuiView$TreeState$setAncestorsOpen(SuiView$TreeState *  self, Object *  item);
void  SuiView$TreeState$setSelected(SuiView$TreeState *  self, Object *  item);
void  SuiView$TreeState$setOpen(SuiView$TreeState *  self, Object *  item, bool  open);


// 虚表
struct tagVtable_SuiView$TreeView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$TreeView _vtable_SuiView$TreeView;

// class refc:0
struct tagSuiView$TreeView {
	SuiLayout$LayoutLinear super; 
	SuiView$TreeState*  state ;
	void  (**reactItem)(void *  self, SuiCore$Node *  o, Object *  item, int  deep);
	void  (**cbOnEvent_forItemView)(void *  self, SuiCore$Event *  e, SuiCore$ViewBase *  o, Object *  item);
	void  (*reactChildren) (SuiView$TreeView *  self, SuiCore$Node *  parent, Orc$List *  items, int  deep);
};
Vtable_SuiView$TreeView* Vtable_SuiView$TreeView_init(Vtable_SuiView$TreeView* pvt);
void SuiView$TreeView_init_fields(SuiView$TreeView *self);
void SuiView$TreeView_init(SuiView$TreeView *self, void *pOwner);
SuiView$TreeView * SuiView$TreeView_new(void *pOwner);
void SuiView$TreeView_fini(SuiView$TreeView *self);

void  SuiView$TreeView$ctor(SuiView$TreeView *  self);
void  SuiView$TreeView$react(SuiView$TreeView *  self);
void  SuiView$TreeView$reactChildren(SuiView$TreeView *  self, SuiCore$Node *  parent, Orc$List *  items, int  deep);

SuiView$TreeView*  SuiView$mkTreeView(SuiView$TreeView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
