
typedef struct tagSuiDesigner$ImageChessBg SuiDesigner$ImageChessBg;
typedef struct tagVtable_SuiDesigner$ImageChessBg Vtable_SuiDesigner$ImageChessBg;
typedef struct tagSuiDesigner$SceneTransform SuiDesigner$SceneTransform;
typedef struct tagVtable_SuiDesigner$SceneTransform Vtable_SuiDesigner$SceneTransform;
typedef struct tagSuiDesigner$SceneView SuiDesigner$SceneView;
typedef struct tagVtable_SuiDesigner$SceneView Vtable_SuiDesigner$SceneView;


#ifndef define_struct___SuiDesigner__SceneView_orc_h__
#define define_struct___SuiDesigner__SceneView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__SceneView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__SceneView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__SceneView_orc_h__
#define __SuiDesigner__SceneView_orc_h__

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
#include "./Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Json/Json_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./RegisterNodes_orc.h"
#include "./DrawDegree_orc.h"
#include "./UiAction_orc.h"
#include "./ANode_orc.h"
#include "./Gizmo_orc.h"
#include "./EditCtx_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./EventFileItemChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$ImageChessBg {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ImageChessBg _vtable_SuiDesigner$ImageChessBg;

// class refc:0
struct tagSuiDesigner$ImageChessBg {
	Object super; 
	int  width ;
	int  height ;
	int  color0 ;
	int  color1 ;
	SuiCore$Image*  img ;
	char *  (*new_createChessBg_inMemory) (SuiDesigner$ImageChessBg *  self, int  w, int  h);
	SuiCore$Image *  (*gocChessBgImage) (SuiDesigner$ImageChessBg *  self, SuiCore$Canvas *  canvas);
};
Vtable_SuiDesigner$ImageChessBg* Vtable_SuiDesigner$ImageChessBg_init(Vtable_SuiDesigner$ImageChessBg* pvt);
void SuiDesigner$ImageChessBg_init_fields(SuiDesigner$ImageChessBg *self);
void SuiDesigner$ImageChessBg_init(SuiDesigner$ImageChessBg *self, void *pOwner);
SuiDesigner$ImageChessBg * SuiDesigner$ImageChessBg_new(void *pOwner);
void SuiDesigner$ImageChessBg_fini(SuiDesigner$ImageChessBg *self);

char *  SuiDesigner$ImageChessBg$new_createChessBg_inMemory(SuiDesigner$ImageChessBg *  self, int  w, int  h);
SuiCore$Image *  SuiDesigner$ImageChessBg$gocChessBgImage(SuiDesigner$ImageChessBg *  self, SuiCore$Canvas *  canvas);


// 虚表
struct tagVtable_SuiDesigner$SceneTransform {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$SceneTransform _vtable_SuiDesigner$SceneTransform;

// class refc:1
struct tagSuiDesigner$SceneTransform {
	Object super; 
	SuiCore$Vec3 _translate ;
	float  _scale ;
	SuiCore$Mat2d mat ;
	void  (*setScale) (SuiDesigner$SceneTransform *  self, float  s);
	void  (*updateMat) (SuiDesigner$SceneTransform *  self);
	void  (*translate) (SuiDesigner$SceneTransform *  self, float  x, float  y, float  z);
	void  (*setTranslate) (SuiDesigner$SceneTransform *  self, float  x, float  y, float  z);
	void  (*identity) (SuiDesigner$SceneTransform *  self);
	void  (*performScaleByWheelEventAndSceneView) (SuiDesigner$SceneTransform *  self, SuiCore$WheelEvent *  we, SuiDesigner$SceneView *  v);
};
Vtable_SuiDesigner$SceneTransform* Vtable_SuiDesigner$SceneTransform_init(Vtable_SuiDesigner$SceneTransform* pvt);
void SuiDesigner$SceneTransform_init_fields(SuiDesigner$SceneTransform *self);
void SuiDesigner$SceneTransform_init(SuiDesigner$SceneTransform *self, void *pOwner);
SuiDesigner$SceneTransform * SuiDesigner$SceneTransform_new(void *pOwner);
void SuiDesigner$SceneTransform_fini(SuiDesigner$SceneTransform *self);

void  SuiDesigner$SceneTransform$setScale(SuiDesigner$SceneTransform *  self, float  s);
void  SuiDesigner$SceneTransform$updateMat(SuiDesigner$SceneTransform *  self);
void  SuiDesigner$SceneTransform$translate(SuiDesigner$SceneTransform *  self, float  x, float  y, float  z);
void  SuiDesigner$SceneTransform$setTranslate(SuiDesigner$SceneTransform *  self, float  x, float  y, float  z);
void  SuiDesigner$SceneTransform$identity(SuiDesigner$SceneTransform *  self);
void  SuiDesigner$SceneTransform$performScaleByWheelEventAndSceneView(SuiDesigner$SceneTransform *  self, SuiCore$WheelEvent *  we, SuiDesigner$SceneView *  v);


// 虚表
struct tagVtable_SuiDesigner$SceneView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiDesigner$SceneView _vtable_SuiDesigner$SceneView;

// class refc:0
struct tagSuiDesigner$SceneView {
	SuiCore$View super; 
	SuiDesigner$ImageChessBg*  chessBg ;
	SuiView$Drag*  drag ;
	SuiDesigner$SceneTransform*  sceneTransform ;
	SuiDesigner$DrawDegree*  degree ;
	SuiCore$Node*  rootNode ;
	SuiCore$Node*  gizmoRoot ;
	void  (*onUnmouting) (SuiDesigner$SceneView *  self);
	void  (*onLeftClickInCapture) (SuiDesigner$SceneView *  self, SuiCore$MouseEvent *  me);
	void  (*_routeRightMenu) (SuiDesigner$SceneView *  self, SuiView$MenuNativeItem *  item);
	void  (*onRightClick) (SuiDesigner$SceneView *  self, SuiCore$MouseEvent *  me);
	void  (*removeRootNode) (SuiDesigner$SceneView *  self);
	SuiView$Drag*  gizmoDrag ;
	bool  _reactGizmosDirty ;
	void  (*triggerReactGizmos) (SuiDesigner$SceneView *  self);
	void  (*reactGizmos) (SuiDesigner$SceneView *  self);
	SuiCore$Mat2d _sceneWorldMat ;
	void  (*drawRect_forANode) (SuiDesigner$SceneView *  self, SuiCore$Canvas *  canvas, SuiDesigner$ANode *  sel);
};
Vtable_SuiDesigner$SceneView* Vtable_SuiDesigner$SceneView_init(Vtable_SuiDesigner$SceneView* pvt);
void SuiDesigner$SceneView_init_fields(SuiDesigner$SceneView *self);
void SuiDesigner$SceneView_init(SuiDesigner$SceneView *self, void *pOwner);
SuiDesigner$SceneView * SuiDesigner$SceneView_new(void *pOwner);
void SuiDesigner$SceneView_fini(SuiDesigner$SceneView *self);

void  SuiDesigner$SceneView$ctor(SuiDesigner$SceneView *  self);
void  SuiDesigner$SceneView$onListenerEvent(SuiDesigner$SceneView *  self, SuiCore$Event *  event);
void  SuiDesigner$SceneView$onMounted(SuiDesigner$SceneView *  self);
void  SuiDesigner$SceneView$onUnmouting(SuiDesigner$SceneView *  self);
void  SuiDesigner$SceneView$onEvent(SuiDesigner$SceneView *  self, SuiCore$Event *  e);
void  SuiDesigner$SceneView$onLeftClickInCapture(SuiDesigner$SceneView *  self, SuiCore$MouseEvent *  me);
void  SuiDesigner$SceneView$_routeRightMenu(SuiDesigner$SceneView *  self, SuiView$MenuNativeItem *  item);
void  SuiDesigner$SceneView$onRightClick(SuiDesigner$SceneView *  self, SuiCore$MouseEvent *  me);
void  SuiDesigner$SceneView$removeRootNode(SuiDesigner$SceneView *  self);
void  SuiDesigner$SceneView$react(SuiDesigner$SceneView *  self);
void  SuiDesigner$SceneView$triggerReactGizmos(SuiDesigner$SceneView *  self);
void  SuiDesigner$SceneView$reactGizmos(SuiDesigner$SceneView *  self);
void  SuiDesigner$SceneView$draw_children(SuiDesigner$SceneView *  self, SuiCore$Canvas *  canvas);
void  SuiDesigner$SceneView$draw_self(SuiDesigner$SceneView *  self, SuiCore$Canvas *  canvas);
void  SuiDesigner$SceneView$drawSelfBorder(SuiDesigner$SceneView *  self, SuiCore$Canvas *  canvas);
void  SuiDesigner$SceneView$drawRect_forANode(SuiDesigner$SceneView *  self, SuiCore$Canvas *  canvas, SuiDesigner$ANode *  sel);

SuiDesigner$SceneView*  SuiDesigner$mkSceneView(SuiDesigner$SceneView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
