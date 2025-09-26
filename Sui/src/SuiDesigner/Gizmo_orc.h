
typedef struct tagSuiDesigner$GizmoRectView SuiDesigner$GizmoRectView;
typedef struct tagVtable_SuiDesigner$GizmoRectView Vtable_SuiDesigner$GizmoRectView;


#ifndef define_struct___SuiDesigner__Gizmo_orc_h__
#define define_struct___SuiDesigner__Gizmo_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__Gizmo_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__Gizmo_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__Gizmo_orc_h__
#define __SuiDesigner__Gizmo_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Frame_orc.h"
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
struct tagVtable_SuiDesigner$GizmoRectView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiDesigner$GizmoRectView _vtable_SuiDesigner$GizmoRectView;

// class refc:0
struct tagSuiDesigner$GizmoRectView {
	SuiCore$View super; 
	SuiCore$Rect targetRect ;
	SuiCore$View *  lt ;
	SuiCore$View *  rt ;
	SuiCore$View *  rb ;
	SuiCore$View *  lb ;
	SuiView$Drag*  drag ;
	void  (**onRectChanged)(void *  self, SuiCore$Rect newTargetRect);
	SuiCore$Rect _tmpRect ;
	void  (*bindEvent) (SuiDesigner$GizmoRectView *  self, SuiCore$View*  v);
};
Vtable_SuiDesigner$GizmoRectView* Vtable_SuiDesigner$GizmoRectView_init(Vtable_SuiDesigner$GizmoRectView* pvt);
void SuiDesigner$GizmoRectView_init_fields(SuiDesigner$GizmoRectView *self);
void SuiDesigner$GizmoRectView_init(SuiDesigner$GizmoRectView *self, void *pOwner);
SuiDesigner$GizmoRectView * SuiDesigner$GizmoRectView_new(void *pOwner);
void SuiDesigner$GizmoRectView_fini(SuiDesigner$GizmoRectView *self);

void  SuiDesigner$GizmoRectView$layout(SuiDesigner$GizmoRectView *  self, SuiCore$Frame *  ctx);
void  SuiDesigner$GizmoRectView$ctor(SuiDesigner$GizmoRectView *  self);
void  SuiDesigner$GizmoRectView$react(SuiDesigner$GizmoRectView *  self);
void  SuiDesigner$GizmoRectView$bindEvent(SuiDesigner$GizmoRectView *  self, SuiCore$View*  v);

SuiCore$View *  SuiDesigner$Gizmo_reactRect(SuiCore$Node *  o, float  x, float  y, long long  key);
SuiDesigner$GizmoRectView*  SuiDesigner$mkGizmoRectView(SuiDesigner$GizmoRectView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
