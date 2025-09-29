
typedef struct tagHoroEditor$HoroSceneHierView HoroEditor$HoroSceneHierView;
typedef struct tagVtable_HoroEditor$HoroSceneHierView Vtable_HoroEditor$HoroSceneHierView;


#ifndef define_struct___HoroEditor__HoroSceneHierView_orc_h__
#define define_struct___HoroEditor__HoroSceneHierView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__HoroSceneHierView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__HoroSceneHierView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__HoroSceneHierView_orc_h__
#define __HoroEditor__HoroSceneHierView_orc_h__

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
#include "../SuiDesigner/Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/RegisterNodes_orc.h"
#include "../SuiDesigner/DrawDegree_orc.h"
#include "../SuiDesigner/UiAction_orc.h"
#include "../SuiDesigner/EditCtx_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"
#include "../SuiDesigner/EventFileItemChanged_orc.h"
#include "./HoroEditCtx_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Camera_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$HoroSceneHierView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_HoroEditor$HoroSceneHierView _vtable_HoroEditor$HoroSceneHierView;

// class refc:0
struct tagHoroEditor$HoroSceneHierView {
	SuiLayout$LayoutLinear super; 
	HoroEditor$HoroEditCtx*  editCtx ;
	void  (*onUnmouting) (HoroEditor$HoroSceneHierView *  self);
	void  (*_routeRightMenu) (HoroEditor$HoroSceneHierView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$ANode*  node);
	void  (*_onItemRightClick) (HoroEditor$HoroSceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item);
	void  (*_onEvent_forItemView) (HoroEditor$HoroSceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item);
};
Vtable_HoroEditor$HoroSceneHierView* Vtable_HoroEditor$HoroSceneHierView_init(Vtable_HoroEditor$HoroSceneHierView* pvt);
void HoroEditor$HoroSceneHierView_init_fields(HoroEditor$HoroSceneHierView *self);
void HoroEditor$HoroSceneHierView_init(HoroEditor$HoroSceneHierView *self, void *pOwner);
HoroEditor$HoroSceneHierView * HoroEditor$HoroSceneHierView_new(void *pOwner);
void HoroEditor$HoroSceneHierView_fini(HoroEditor$HoroSceneHierView *self);

void  HoroEditor$HoroSceneHierView$ctor(HoroEditor$HoroSceneHierView *  self);
void  HoroEditor$HoroSceneHierView$onListenerEvent(HoroEditor$HoroSceneHierView *  self, SuiCore$Event *  event);
void  HoroEditor$HoroSceneHierView$onMounted(HoroEditor$HoroSceneHierView *  self);
void  HoroEditor$HoroSceneHierView$onUnmouting(HoroEditor$HoroSceneHierView *  self);
void  HoroEditor$HoroSceneHierView$_routeRightMenu(HoroEditor$HoroSceneHierView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$ANode*  node);
void  HoroEditor$HoroSceneHierView$_onItemRightClick(HoroEditor$HoroSceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item);
void  HoroEditor$HoroSceneHierView$_onEvent_forItemView(HoroEditor$HoroSceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item);
void  HoroEditor$HoroSceneHierView$react(HoroEditor$HoroSceneHierView *  self, int  xxx);

HoroEditor$HoroSceneHierView*  HoroEditor$mkHoroSceneHierView(HoroEditor$HoroSceneHierView **  __outRef__, void *  parent, long long  key);
void  HoroEditor$testHoroSceneHier();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
