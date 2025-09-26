
typedef struct tagSuiDesigner$SceneHierView SuiDesigner$SceneHierView;
typedef struct tagVtable_SuiDesigner$SceneHierView Vtable_SuiDesigner$SceneHierView;


#ifndef define_struct___SuiDesigner__SceneHierView_orc_h__
#define define_struct___SuiDesigner__SceneHierView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__SceneHierView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__SceneHierView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__SceneHierView_orc_h__
#define __SuiDesigner__SceneHierView_orc_h__

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
#include "./ANode_orc.h"
#include "./EditCtx_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./EventFileItemChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$SceneHierView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiDesigner$SceneHierView _vtable_SuiDesigner$SceneHierView;

// class refc:0
struct tagSuiDesigner$SceneHierView {
	SuiLayout$LayoutLinear super; 
	void  (*onUnmouting) (SuiDesigner$SceneHierView *  self);
	void  (*_routeRightMenu) (SuiDesigner$SceneHierView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$ANode*  anode);
	void  (*_onItemRightClick) (SuiDesigner$SceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item);
	void  (*_onEvent_forItemView) (SuiDesigner$SceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item);
};
Vtable_SuiDesigner$SceneHierView* Vtable_SuiDesigner$SceneHierView_init(Vtable_SuiDesigner$SceneHierView* pvt);
void SuiDesigner$SceneHierView_init_fields(SuiDesigner$SceneHierView *self);
void SuiDesigner$SceneHierView_init(SuiDesigner$SceneHierView *self, void *pOwner);
SuiDesigner$SceneHierView * SuiDesigner$SceneHierView_new(void *pOwner);
void SuiDesigner$SceneHierView_fini(SuiDesigner$SceneHierView *self);

void  SuiDesigner$SceneHierView$ctor(SuiDesigner$SceneHierView *  self);
void  SuiDesigner$SceneHierView$onListenerEvent(SuiDesigner$SceneHierView *  self, SuiCore$Event *  event);
void  SuiDesigner$SceneHierView$onMounted(SuiDesigner$SceneHierView *  self);
void  SuiDesigner$SceneHierView$onUnmouting(SuiDesigner$SceneHierView *  self);
void  SuiDesigner$SceneHierView$_routeRightMenu(SuiDesigner$SceneHierView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$ANode*  anode);
void  SuiDesigner$SceneHierView$_onItemRightClick(SuiDesigner$SceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item);
void  SuiDesigner$SceneHierView$_onEvent_forItemView(SuiDesigner$SceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item);
void  SuiDesigner$SceneHierView$react(SuiDesigner$SceneHierView *  self, int  xxx);

SuiDesigner$SceneHierView*  SuiDesigner$mkSceneHierView(SuiDesigner$SceneHierView **  __outRef__, void *  parent, long long  key);
void  SuiDesigner$testScene();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
