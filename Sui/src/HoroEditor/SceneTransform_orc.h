
typedef struct tagHoroEditor$SceneTransform HoroEditor$SceneTransform;
typedef struct tagVtable_HoroEditor$SceneTransform Vtable_HoroEditor$SceneTransform;


#ifndef define_struct___HoroEditor__SceneTransform_orc_h__
#define define_struct___HoroEditor__SceneTransform_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__SceneTransform_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__SceneTransform_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__SceneTransform_orc_h__
#define __HoroEditor__SceneTransform_orc_h__

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
#include "./Horo2dSceneView_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$SceneTransform {
	Vtable_Object super;
};
//虚表实例
extern Vtable_HoroEditor$SceneTransform _vtable_HoroEditor$SceneTransform;

// class refc:1
struct tagHoroEditor$SceneTransform {
	Object super; 
	SuiCore$Vec3 _translate ;
	float  _scale ;
	SuiCore$Mat2d mat ;
	void  (*setScale) (HoroEditor$SceneTransform *  self, float  s);
	void  (*updateMat) (HoroEditor$SceneTransform *  self);
	void  (*translate) (HoroEditor$SceneTransform *  self, float  x, float  y, float  z);
	void  (*setTranslate) (HoroEditor$SceneTransform *  self, float  x, float  y, float  z);
	void  (*identity) (HoroEditor$SceneTransform *  self);
	void  (*performScaleByWheelEventAndSceneView) (HoroEditor$SceneTransform *  self, SuiCore$WheelEvent *  we, HoroEditor$Horo2dSceneView *  v);
};
Vtable_HoroEditor$SceneTransform* Vtable_HoroEditor$SceneTransform_init(Vtable_HoroEditor$SceneTransform* pvt);
void HoroEditor$SceneTransform_init_fields(HoroEditor$SceneTransform *self);
void HoroEditor$SceneTransform_init(HoroEditor$SceneTransform *self, void *pOwner);
HoroEditor$SceneTransform * HoroEditor$SceneTransform_new(void *pOwner);
void HoroEditor$SceneTransform_fini(HoroEditor$SceneTransform *self);

void  HoroEditor$SceneTransform$setScale(HoroEditor$SceneTransform *  self, float  s);
void  HoroEditor$SceneTransform$updateMat(HoroEditor$SceneTransform *  self);
void  HoroEditor$SceneTransform$translate(HoroEditor$SceneTransform *  self, float  x, float  y, float  z);
void  HoroEditor$SceneTransform$setTranslate(HoroEditor$SceneTransform *  self, float  x, float  y, float  z);
void  HoroEditor$SceneTransform$identity(HoroEditor$SceneTransform *  self);
void  HoroEditor$SceneTransform$performScaleByWheelEventAndSceneView(HoroEditor$SceneTransform *  self, SuiCore$WheelEvent *  we, HoroEditor$Horo2dSceneView *  v);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
