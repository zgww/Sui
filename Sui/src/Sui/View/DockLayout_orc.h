
typedef struct tagSuiView$DockItem SuiView$DockItem;
typedef struct tagVtable_SuiView$DockItem Vtable_SuiView$DockItem;
typedef struct tagSuiView$DockLayout SuiView$DockLayout;
typedef struct tagVtable_SuiView$DockLayout Vtable_SuiView$DockLayout;
typedef struct tagSuiView$DockSplitterView SuiView$DockSplitterView;
typedef struct tagVtable_SuiView$DockSplitterView Vtable_SuiView$DockSplitterView;


#ifndef define_struct___SuiView__DockLayout_orc_h__
#define define_struct___SuiView__DockLayout_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__DockLayout_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__DockLayout_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__DockLayout_orc_h__
#define __SuiView__DockLayout_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Mouse_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "./ViewBuilder_orc.h"
#include "./Drag_orc.h"
#include "../../Json/Json_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$DockItem {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$DockItem _vtable_SuiView$DockItem;

// class refc:0
struct tagSuiView$DockItem {
	Object super; 
	int  intId ;
	Orc$String*  id ;
	SuiCore$ViewBase*  view ;
	bool  isHorizontal ;
	Orc$String*  type ;
	float  width ;
	float  weight ;
	float  _sumContentSize ;
	float  _sumFlexSize ;
	float  _sumWeight ;
	Orc$List*  children ;
	SuiView$DockItem*  parent ;
	SuiCore$ViewBase*  nextSplitterView ;
	SuiCore$ViewBase*  prevSplitterView ;
	void  (*fromJson) (SuiView$DockItem *  self, Json$Json*  jo);
	Json$Json*  (*toJson) (Json$Json **  __outRef__, SuiView$DockItem *  self);
	int  tabActiveIndex ;
	void  (*setTabActiveIndex) (SuiView$DockItem *  self, int  index);
	void  (*setSelfActive_inTab) (SuiView$DockItem *  self);
	float  (*calcWeight_ofKid_forDragSplitter) (SuiView$DockItem *  self, SuiView$DockItem *  kid, float  delta, float  minSize);
	void  (*appendChild) (SuiView$DockItem *  self, SuiView$DockItem *  item);
	void  (*removeSelf) (SuiView$DockItem *  self);
	bool  (*insertBefore) (SuiView$DockItem *  self, SuiView$DockItem *  newItem, SuiView$DockItem *  relChild);
	bool  (*insertAfter) (SuiView$DockItem *  self, SuiView$DockItem *  newItem, SuiView$DockItem *  relChild);
	bool  (*insertOffset) (SuiView$DockItem *  self, SuiView$DockItem *  newItem, SuiView$DockItem *  relChild, int  offset);
	void  (*removeChild) (SuiView$DockItem *  self, SuiView$DockItem *  kid);
	SuiView$DockItem *  (*tryGetParentTab) (SuiView$DockItem *  self);
	void  (*printTree) (SuiView$DockItem *  self, int  tab);
	bool  (*isEmptySplitter) (SuiView$DockItem *  self);
	bool  (*isEmptyTab) (SuiView$DockItem *  self);
};
Vtable_SuiView$DockItem* Vtable_SuiView$DockItem_init(Vtable_SuiView$DockItem* pvt);
void SuiView$DockItem_init_fields(SuiView$DockItem *self);
void SuiView$DockItem_init(SuiView$DockItem *self, void *pOwner);
SuiView$DockItem * SuiView$DockItem_new(void *pOwner);
void SuiView$DockItem_fini(SuiView$DockItem *self);

void  SuiView$DockItem$fromJson(SuiView$DockItem *  self, Json$Json*  jo);
Json$Json*  SuiView$DockItem$toJson(Json$Json **  __outRef__, SuiView$DockItem *  self);
void  SuiView$DockItem$setTabActiveIndex(SuiView$DockItem *  self, int  index);
void  SuiView$DockItem$dtor(SuiView$DockItem *  self);
void  SuiView$DockItem$setSelfActive_inTab(SuiView$DockItem *  self);
float  SuiView$DockItem$calcWeight_ofKid_forDragSplitter(SuiView$DockItem *  self, SuiView$DockItem *  kid, float  delta, float  minSize);
void  SuiView$DockItem$appendChild(SuiView$DockItem *  self, SuiView$DockItem *  item);
void  SuiView$DockItem$removeSelf(SuiView$DockItem *  self);
bool  SuiView$DockItem$insertBefore(SuiView$DockItem *  self, SuiView$DockItem *  newItem, SuiView$DockItem *  relChild);
bool  SuiView$DockItem$insertAfter(SuiView$DockItem *  self, SuiView$DockItem *  newItem, SuiView$DockItem *  relChild);
bool  SuiView$DockItem$insertOffset(SuiView$DockItem *  self, SuiView$DockItem *  newItem, SuiView$DockItem *  relChild, int  offset);
void  SuiView$DockItem$removeChild(SuiView$DockItem *  self, SuiView$DockItem *  kid);
SuiView$DockItem *  SuiView$DockItem$tryGetParentTab(SuiView$DockItem *  self);
void  SuiView$DockItem$printTree(SuiView$DockItem *  self, int  tab);
bool  SuiView$DockItem$isEmptySplitter(SuiView$DockItem *  self);
bool  SuiView$DockItem$isEmptyTab(SuiView$DockItem *  self);

SuiView$DockItem*  SuiView$DockItem_fromJson(SuiView$DockItem **  __outRef__, Json$Json*  jo);
SuiView$DockItem*  SuiView$mkDockItem(SuiView$DockItem **  __outRef__, SuiView$DockItem *  parent, Orc$String*  id);
SuiView$DockItem*  SuiView$mkDockItemSplitter(SuiView$DockItem **  __outRef__, SuiView$DockItem *  parent, Orc$String*  id, bool  isHorizontal);
SuiView$DockItem*  SuiView$mkDockItemTab(SuiView$DockItem **  __outRef__, SuiView$DockItem *  parent, Orc$String*  id);

// 虚表
struct tagVtable_SuiView$DockLayout {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$DockLayout _vtable_SuiView$DockLayout;

// class refc:0
struct tagSuiView$DockLayout {
	SuiCore$View super; 
	int  splitterSize ;
	float  minItemSize ;
	int  tabHeadBg ;
	SuiView$DockItem*  root ;
	SuiCore$ViewBase *  (**cbRenderItemContentView)(void *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  parent);
	void  (**cbRenderItemHeadView)(void *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  parent, int  kidIndex);
	SuiView$Drag*  dragTab ;
	void  (*doDrop) (SuiView$DockLayout *  self);
	void  (*onDragSplitter) (SuiView$DockLayout *  self, SuiView$Drag *  drag, SuiView$DockItem *  parentDockItem, SuiView$DockItem *  prevDockItem, SuiView$DockItem *  nextDockItem);
	void  (*_reactDockItem) (SuiView$DockLayout *  self, SuiView$DockItem *  item);
	void  (*_onClickTabItemHead) (SuiView$DockLayout *  self, SuiView$DockItem *  kid);
	void  (*_onEvent_tabItemHead) (SuiView$DockLayout *  self, SuiCore$Event *  e, SuiView$DockItem *  kid);
	void  (*_reactTabHeads) (SuiView$DockLayout *  self, SuiView$DockItem *  tab, SuiCore$ViewBase *  parent);
	void  (*_reactTabContent) (SuiView$DockLayout *  self, SuiView$DockItem *  tab, SuiCore$ViewBase *  parent);
	void  (*layoutContentDockItem) (SuiView$DockLayout *  self, SuiCore$Frame *  frame, SuiView$DockItem *  item, int  px, int  py);
	void  (*drawDndIndicator) (SuiView$DockLayout *  self, SuiCore$Canvas *  canvas);
	SuiView$DockItem *  (*findDockItem_containsVec2) (SuiView$DockLayout *  self, SuiView$DockItem *  item, int  clientX, int  clientY);
	SuiView$DockItem*  (*upto_findMostAncestorInDockItemSplitter) (SuiView$DockItem **  __outRef__, SuiView$DockLayout *  self, SuiView$DockItem*  item);
	bool  (*dropInSplitter) (SuiView$DockLayout *  self, SuiView$DockItem*  source, SuiView$DockItem*  target, bool  isHorizontal, bool  isBefore);
	SuiView$DockItem*  (*upto_getOrWrap_DockItemTab) (SuiView$DockItem **  __outRef__, SuiView$DockLayout *  self, SuiView$DockItem*  item);
	void  (*clearAllEmptyTab) (SuiView$DockLayout *  self, SuiView$DockItem *  item);
	void  (*eachThenWrapTab_forNakeDockItemInSplitter) (SuiView$DockLayout *  self, SuiView$DockItem*  item);
};
Vtable_SuiView$DockLayout* Vtable_SuiView$DockLayout_init(Vtable_SuiView$DockLayout* pvt);
void SuiView$DockLayout_init_fields(SuiView$DockLayout *self);
void SuiView$DockLayout_init(SuiView$DockLayout *self, void *pOwner);
SuiView$DockLayout * SuiView$DockLayout_new(void *pOwner);
void SuiView$DockLayout_fini(SuiView$DockLayout *self);

void  SuiView$DockLayout$ctor(SuiView$DockLayout *  self);
void  SuiView$DockLayout$doDrop(SuiView$DockLayout *  self);
void  SuiView$DockLayout$react(SuiView$DockLayout *  self);
void  SuiView$DockLayout$onDragSplitter(SuiView$DockLayout *  self, SuiView$Drag *  drag, SuiView$DockItem *  parentDockItem, SuiView$DockItem *  prevDockItem, SuiView$DockItem *  nextDockItem);
void  SuiView$DockLayout$_reactDockItem(SuiView$DockLayout *  self, SuiView$DockItem *  item);
void  SuiView$DockLayout$_onClickTabItemHead(SuiView$DockLayout *  self, SuiView$DockItem *  kid);
void  SuiView$DockLayout$_onEvent_tabItemHead(SuiView$DockLayout *  self, SuiCore$Event *  e, SuiView$DockItem *  kid);
void  SuiView$DockLayout$_reactTabHeads(SuiView$DockLayout *  self, SuiView$DockItem *  tab, SuiCore$ViewBase *  parent);
void  SuiView$DockLayout$_reactTabContent(SuiView$DockLayout *  self, SuiView$DockItem *  tab, SuiCore$ViewBase *  parent);
void  SuiView$DockLayout$layoutContent(SuiView$DockLayout *  self, SuiCore$Frame *  frame);
void  SuiView$DockLayout$layoutContentDockItem(SuiView$DockLayout *  self, SuiCore$Frame *  frame, SuiView$DockItem *  item, int  px, int  py);
void  SuiView$DockLayout$draw_self(SuiView$DockLayout *  self, SuiCore$Canvas *  canvas);
void  SuiView$DockLayout$drawDndIndicator(SuiView$DockLayout *  self, SuiCore$Canvas *  canvas);
SuiView$DockItem *  SuiView$DockLayout$findDockItem_containsVec2(SuiView$DockLayout *  self, SuiView$DockItem *  item, int  clientX, int  clientY);
SuiView$DockItem*  SuiView$DockLayout$upto_findMostAncestorInDockItemSplitter(SuiView$DockItem **  __outRef__, SuiView$DockLayout *  self, SuiView$DockItem*  item);
bool  SuiView$DockLayout$dropInSplitter(SuiView$DockLayout *  self, SuiView$DockItem*  source, SuiView$DockItem*  target, bool  isHorizontal, bool  isBefore);
SuiView$DockItem*  SuiView$DockLayout$upto_getOrWrap_DockItemTab(SuiView$DockItem **  __outRef__, SuiView$DockLayout *  self, SuiView$DockItem*  item);
void  SuiView$DockLayout$clearAllEmptyTab(SuiView$DockLayout *  self, SuiView$DockItem *  item);
void  SuiView$DockLayout$eachThenWrapTab_forNakeDockItemInSplitter(SuiView$DockLayout *  self, SuiView$DockItem*  item);
SuiCore$ViewBase *  SuiView$DockLayout$hitTestChildren(SuiView$DockLayout *  self, float  x, float  y);


// 虚表
struct tagVtable_SuiView$DockSplitterView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$DockSplitterView _vtable_SuiView$DockSplitterView;

// class refc:0
struct tagSuiView$DockSplitterView {
	SuiCore$View super; 
	SuiView$Drag*  drag ;
	int  hoverBg ;
	int  normalBg ;
};
Vtable_SuiView$DockSplitterView* Vtable_SuiView$DockSplitterView_init(Vtable_SuiView$DockSplitterView* pvt);
void SuiView$DockSplitterView_init_fields(SuiView$DockSplitterView *self);
void SuiView$DockSplitterView_init(SuiView$DockSplitterView *self, void *pOwner);
SuiView$DockSplitterView * SuiView$DockSplitterView_new(void *pOwner);
void SuiView$DockSplitterView_fini(SuiView$DockSplitterView *self);

void  SuiView$DockSplitterView$ctor(SuiView$DockSplitterView *  self);
void  SuiView$DockSplitterView$react(SuiView$DockSplitterView *  self);
void  SuiView$DockSplitterView$onEvent(SuiView$DockSplitterView *  self, SuiCore$Event *  e);
void  SuiView$DockSplitterView$onHoverChanged(SuiView$DockSplitterView *  self);

SuiView$DockLayout*  SuiView$dockLayout(SuiView$DockLayout **  __outRef__, void *  parent, long long  key);
SuiView$DockSplitterView*  SuiView$dockSplitterView(SuiView$DockSplitterView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
