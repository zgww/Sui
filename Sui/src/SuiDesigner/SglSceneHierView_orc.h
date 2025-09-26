
typedef struct tagSuiDesigner$SglSceneHierView SuiDesigner$SglSceneHierView;
typedef struct tagVtable_SuiDesigner$SglSceneHierView Vtable_SuiDesigner$SglSceneHierView;


#ifndef define_struct___SuiDesigner__SglSceneHierView_orc_h__
#define define_struct___SuiDesigner__SglSceneHierView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__SglSceneHierView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__SglSceneHierView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__SglSceneHierView_orc_h__
#define __SuiDesigner__SglSceneHierView_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./RegisterNodes_orc.h"
#include "./DrawDegree_orc.h"
#include "./UiAction_orc.h"
#include "./EditCtx_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./EventFileItemChanged_orc.h"
#include "./SglEditCtx_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Camera_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$SglSceneHierView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiDesigner$SglSceneHierView _vtable_SuiDesigner$SglSceneHierView;

// class refc:0
struct tagSuiDesigner$SglSceneHierView {
	SuiLayout$LayoutLinear super; 
	SuiDesigner$SglEditCtx*  editCtx ;
	void  (*onUnmouting) (SuiDesigner$SglSceneHierView *  self);
	void  (*_routeRightMenu) (SuiDesigner$SglSceneHierView *  self, SuiView$MenuNativeItem *  item, SuiCore$Node*  node);
	void  (*_onItemRightClick) (SuiDesigner$SglSceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item);
	void  (*_onEvent_forItemView) (SuiDesigner$SglSceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item);
};
Vtable_SuiDesigner$SglSceneHierView* Vtable_SuiDesigner$SglSceneHierView_init(Vtable_SuiDesigner$SglSceneHierView* pvt);
void SuiDesigner$SglSceneHierView_init_fields(SuiDesigner$SglSceneHierView *self);
void SuiDesigner$SglSceneHierView_init(SuiDesigner$SglSceneHierView *self, void *pOwner);
SuiDesigner$SglSceneHierView * SuiDesigner$SglSceneHierView_new(void *pOwner);
void SuiDesigner$SglSceneHierView_fini(SuiDesigner$SglSceneHierView *self);

void  SuiDesigner$SglSceneHierView$ctor(SuiDesigner$SglSceneHierView *  self);
void  SuiDesigner$SglSceneHierView$onListenerEvent(SuiDesigner$SglSceneHierView *  self, SuiCore$Event *  event);
void  SuiDesigner$SglSceneHierView$onMounted(SuiDesigner$SglSceneHierView *  self);
void  SuiDesigner$SglSceneHierView$onUnmouting(SuiDesigner$SglSceneHierView *  self);
void  SuiDesigner$SglSceneHierView$_routeRightMenu(SuiDesigner$SglSceneHierView *  self, SuiView$MenuNativeItem *  item, SuiCore$Node*  node);
void  SuiDesigner$SglSceneHierView$_onItemRightClick(SuiDesigner$SglSceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item);
void  SuiDesigner$SglSceneHierView$_onEvent_forItemView(SuiDesigner$SglSceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item);
void  SuiDesigner$SglSceneHierView$react(SuiDesigner$SglSceneHierView *  self, int  xxx);

SuiDesigner$SglSceneHierView*  SuiDesigner$mkSglSceneHierView(SuiDesigner$SglSceneHierView **  __outRef__, void *  parent, long long  key);
void  SuiDesigner$testSglSceneHier();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
