
typedef struct tagHoroEditor$Horo2dSceneView HoroEditor$Horo2dSceneView;
typedef struct tagVtable_HoroEditor$Horo2dSceneView Vtable_HoroEditor$Horo2dSceneView;


#ifndef define_struct___HoroEditor__Horo2dSceneView_orc_h__
#define define_struct___HoroEditor__Horo2dSceneView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__Horo2dSceneView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__Horo2dSceneView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__Horo2dSceneView_orc_h__
#define __HoroEditor__Horo2dSceneView_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Mat2d_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
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
#include "../Json/Json_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/RegisterNodes_orc.h"
#include "../SuiDesigner/DrawDegree_orc.h"
#include "../SuiDesigner/UiAction_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../SuiDesigner/Gizmo_orc.h"
#include "../SuiDesigner/EditCtx_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"
#include "../SuiDesigner/EventFileItemChanged_orc.h"
#include "./ImageChessBg_orc.h"
#include "./SceneTransform_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$Horo2dSceneView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_HoroEditor$Horo2dSceneView _vtable_HoroEditor$Horo2dSceneView;

// class refc:0
struct tagHoroEditor$Horo2dSceneView {
	SuiCore$View super; 
	HoroEditor$ImageChessBg*  chessBg ;
	SuiView$Drag*  drag ;
	HoroEditor$SceneTransform*  sceneTransform ;
	SuiDesigner$DrawDegree*  degree ;
	SuiDesigner$ANode*  root ;
	SuiCore$Node*  rootNode ;
	SuiCore$Node*  gizmoRoot ;
	void  (*onUnmouting) (HoroEditor$Horo2dSceneView *  self);
	void  (*onLeftClickInCapture) (HoroEditor$Horo2dSceneView *  self, SuiCore$MouseEvent *  me);
	void  (*_routeRightMenu) (HoroEditor$Horo2dSceneView *  self, SuiView$MenuNativeItem *  item);
	void  (*onRightClick) (HoroEditor$Horo2dSceneView *  self, SuiCore$MouseEvent *  me);
	void  (*removeRootNode) (HoroEditor$Horo2dSceneView *  self);
	SuiView$Drag*  gizmoDrag ;
	bool  _reactGizmosDirty ;
	void  (*triggerReactGizmos) (HoroEditor$Horo2dSceneView *  self);
	void  (*reactGizmos) (HoroEditor$Horo2dSceneView *  self);
	SuiCore$Mat2d _sceneWorldMat ;
	void  (*drawRect_forANode) (HoroEditor$Horo2dSceneView *  self, SuiCore$Canvas *  canvas, SuiDesigner$ANode *  sel);
};
Vtable_HoroEditor$Horo2dSceneView* Vtable_HoroEditor$Horo2dSceneView_init(Vtable_HoroEditor$Horo2dSceneView* pvt);
void HoroEditor$Horo2dSceneView_init_fields(HoroEditor$Horo2dSceneView *self);
void HoroEditor$Horo2dSceneView_init(HoroEditor$Horo2dSceneView *self, void *pOwner);
HoroEditor$Horo2dSceneView * HoroEditor$Horo2dSceneView_new(void *pOwner);
void HoroEditor$Horo2dSceneView_fini(HoroEditor$Horo2dSceneView *self);

void  HoroEditor$Horo2dSceneView$ctor(HoroEditor$Horo2dSceneView *  self);
void  HoroEditor$Horo2dSceneView$onListenerEvent(HoroEditor$Horo2dSceneView *  self, SuiCore$Event *  event);
void  HoroEditor$Horo2dSceneView$onMounted(HoroEditor$Horo2dSceneView *  self);
void  HoroEditor$Horo2dSceneView$onUnmouting(HoroEditor$Horo2dSceneView *  self);
void  HoroEditor$Horo2dSceneView$onEvent(HoroEditor$Horo2dSceneView *  self, SuiCore$Event *  e);
void  HoroEditor$Horo2dSceneView$onLeftClickInCapture(HoroEditor$Horo2dSceneView *  self, SuiCore$MouseEvent *  me);
void  HoroEditor$Horo2dSceneView$_routeRightMenu(HoroEditor$Horo2dSceneView *  self, SuiView$MenuNativeItem *  item);
void  HoroEditor$Horo2dSceneView$onRightClick(HoroEditor$Horo2dSceneView *  self, SuiCore$MouseEvent *  me);
void  HoroEditor$Horo2dSceneView$removeRootNode(HoroEditor$Horo2dSceneView *  self);
void  HoroEditor$Horo2dSceneView$react(HoroEditor$Horo2dSceneView *  self);
void  HoroEditor$Horo2dSceneView$triggerReactGizmos(HoroEditor$Horo2dSceneView *  self);
void  HoroEditor$Horo2dSceneView$reactGizmos(HoroEditor$Horo2dSceneView *  self);
void  HoroEditor$Horo2dSceneView$draw_children(HoroEditor$Horo2dSceneView *  self, SuiCore$Canvas *  canvas);
void  HoroEditor$Horo2dSceneView$draw_self(HoroEditor$Horo2dSceneView *  self, SuiCore$Canvas *  canvas);
void  HoroEditor$Horo2dSceneView$drawSelfBorder(HoroEditor$Horo2dSceneView *  self, SuiCore$Canvas *  canvas);
void  HoroEditor$Horo2dSceneView$drawRect_forANode(HoroEditor$Horo2dSceneView *  self, SuiCore$Canvas *  canvas, SuiDesigner$ANode *  sel);

HoroEditor$Horo2dSceneView*  HoroEditor$mkHoro2dSceneView(HoroEditor$Horo2dSceneView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
