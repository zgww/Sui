
typedef struct tagSuiDesigner$HoroSceneHierView SuiDesigner$HoroSceneHierView;
typedef struct tagVtable_SuiDesigner$HoroSceneHierView Vtable_SuiDesigner$HoroSceneHierView;


#ifndef define_struct___SuiDesigner__HoroSceneHierView_orc_h__
#define define_struct___SuiDesigner__HoroSceneHierView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__HoroSceneHierView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__HoroSceneHierView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__HoroSceneHierView_orc_h__
#define __SuiDesigner__HoroSceneHierView_orc_h__

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
struct tagVtable_SuiDesigner$HoroSceneHierView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiDesigner$HoroSceneHierView _vtable_SuiDesigner$HoroSceneHierView;

// class refc:0
struct tagSuiDesigner$HoroSceneHierView {
	SuiLayout$LayoutLinear super; 
	SuiDesigner$HoroEditCtx*  editCtx ;
	void  (*onUnmouting) (SuiDesigner$HoroSceneHierView *  self);
	void  (*_routeRightMenu) (SuiDesigner$HoroSceneHierView *  self, SuiView$MenuNativeItem *  item, SuiCore$Node*  node);
	void  (*_onItemRightClick) (SuiDesigner$HoroSceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item);
	void  (*_onEvent_forItemView) (SuiDesigner$HoroSceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item);
};
Vtable_SuiDesigner$HoroSceneHierView* Vtable_SuiDesigner$HoroSceneHierView_init(Vtable_SuiDesigner$HoroSceneHierView* pvt);
void SuiDesigner$HoroSceneHierView_init_fields(SuiDesigner$HoroSceneHierView *self);
void SuiDesigner$HoroSceneHierView_init(SuiDesigner$HoroSceneHierView *self, void *pOwner);
SuiDesigner$HoroSceneHierView * SuiDesigner$HoroSceneHierView_new(void *pOwner);
void SuiDesigner$HoroSceneHierView_fini(SuiDesigner$HoroSceneHierView *self);

void  SuiDesigner$HoroSceneHierView$ctor(SuiDesigner$HoroSceneHierView *  self);
void  SuiDesigner$HoroSceneHierView$onListenerEvent(SuiDesigner$HoroSceneHierView *  self, SuiCore$Event *  event);
void  SuiDesigner$HoroSceneHierView$onMounted(SuiDesigner$HoroSceneHierView *  self);
void  SuiDesigner$HoroSceneHierView$onUnmouting(SuiDesigner$HoroSceneHierView *  self);
void  SuiDesigner$HoroSceneHierView$_routeRightMenu(SuiDesigner$HoroSceneHierView *  self, SuiView$MenuNativeItem *  item, SuiCore$Node*  node);
void  SuiDesigner$HoroSceneHierView$_onItemRightClick(SuiDesigner$HoroSceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item);
void  SuiDesigner$HoroSceneHierView$_onEvent_forItemView(SuiDesigner$HoroSceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item);
void  SuiDesigner$HoroSceneHierView$react(SuiDesigner$HoroSceneHierView *  self, int  xxx);

SuiDesigner$HoroSceneHierView*  SuiDesigner$mkHoroSceneHierView(SuiDesigner$HoroSceneHierView **  __outRef__, void *  parent, long long  key);
void  SuiDesigner$testHoroSceneHier();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
