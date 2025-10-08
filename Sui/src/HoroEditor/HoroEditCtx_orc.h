
typedef struct tagHoroEditor$EventHoroSceneChanged HoroEditor$EventHoroSceneChanged;
typedef struct tagVtable_HoroEditor$EventHoroSceneChanged Vtable_HoroEditor$EventHoroSceneChanged;
typedef struct tagHoroEditor$EventHoroSelectedChanged HoroEditor$EventHoroSelectedChanged;
typedef struct tagVtable_HoroEditor$EventHoroSelectedChanged Vtable_HoroEditor$EventHoroSelectedChanged;
typedef struct tagHoroEditor$HoroEditCtx HoroEditor$HoroEditCtx;
typedef struct tagVtable_HoroEditor$HoroEditCtx Vtable_HoroEditor$HoroEditCtx;


#ifndef define_struct___HoroEditor__HoroEditCtx_orc_h__
#define define_struct___HoroEditor__HoroEditCtx_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__HoroEditCtx_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__HoroEditCtx_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__HoroEditCtx_orc_h__
#define __HoroEditor__HoroEditCtx_orc_h__

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
#include "../SuiDesigner/EventFileItemChanged_orc.h"
#include "../SuiDesigner/Prefab_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Obj3d_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$EventHoroSceneChanged {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_HoroEditor$EventHoroSceneChanged _vtable_HoroEditor$EventHoroSceneChanged;

// class refc:0
struct tagHoroEditor$EventHoroSceneChanged {
	SuiCore$Event super; 
	
};
Vtable_HoroEditor$EventHoroSceneChanged* Vtable_HoroEditor$EventHoroSceneChanged_init(Vtable_HoroEditor$EventHoroSceneChanged* pvt);
void HoroEditor$EventHoroSceneChanged_init_fields(HoroEditor$EventHoroSceneChanged *self);
void HoroEditor$EventHoroSceneChanged_init(HoroEditor$EventHoroSceneChanged *self, void *pOwner);
HoroEditor$EventHoroSceneChanged * HoroEditor$EventHoroSceneChanged_new(void *pOwner);
void HoroEditor$EventHoroSceneChanged_fini(HoroEditor$EventHoroSceneChanged *self);



// 虚表
struct tagVtable_HoroEditor$EventHoroSelectedChanged {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_HoroEditor$EventHoroSelectedChanged _vtable_HoroEditor$EventHoroSelectedChanged;

// class refc:0
struct tagHoroEditor$EventHoroSelectedChanged {
	SuiCore$Event super; 
	
};
Vtable_HoroEditor$EventHoroSelectedChanged* Vtable_HoroEditor$EventHoroSelectedChanged_init(Vtable_HoroEditor$EventHoroSelectedChanged* pvt);
void HoroEditor$EventHoroSelectedChanged_init_fields(HoroEditor$EventHoroSelectedChanged *self);
void HoroEditor$EventHoroSelectedChanged_init(HoroEditor$EventHoroSelectedChanged *self, void *pOwner);
HoroEditor$EventHoroSelectedChanged * HoroEditor$EventHoroSelectedChanged_new(void *pOwner);
void HoroEditor$EventHoroSelectedChanged_fini(HoroEditor$EventHoroSelectedChanged *self);



// 虚表
struct tagVtable_HoroEditor$HoroEditCtx {
	Vtable_Object super;
};
//虚表实例
extern Vtable_HoroEditor$HoroEditCtx _vtable_HoroEditor$HoroEditCtx;

// class refc:0
struct tagHoroEditor$HoroEditCtx {
	Object super; 
	SuiView$TreeState*  state ;
	Sgl$SglSceneView*  sceneView ;
	Orc$List*  roots ;
	SuiCore$Node*  hoverNode ;
	SuiDesigner$Prefab*  prefab ;
	void  (*setState) (HoroEditor$HoroEditCtx *  self, SuiView$TreeState*  state);
	SuiDesigner$ANode*  (*findANodeByNode) (SuiDesigner$ANode **  __outRef__, HoroEditor$HoroEditCtx *  self, SuiCore$Node *  node);
	void  (*onSelectedChanged) (HoroEditor$HoroEditCtx *  self);
	void  (*setSceneView) (HoroEditor$HoroEditCtx *  self, Sgl$SglSceneView *  sceneView);
	Sgl$Scene *  (*getScene) (HoroEditor$HoroEditCtx *  self);
	void  (*closeCurrentPrefab) (HoroEditor$HoroEditCtx *  self);
	void  (*openPrefab) (HoroEditor$HoroEditCtx *  self, const char *  path);
	SuiDesigner$ANode*  (*getRoot) (SuiDesigner$ANode **  __outRef__, HoroEditor$HoroEditCtx *  self);
};
Vtable_HoroEditor$HoroEditCtx* Vtable_HoroEditor$HoroEditCtx_init(Vtable_HoroEditor$HoroEditCtx* pvt);
void HoroEditor$HoroEditCtx_init_fields(HoroEditor$HoroEditCtx *self);
void HoroEditor$HoroEditCtx_init(HoroEditor$HoroEditCtx *self, void *pOwner);
HoroEditor$HoroEditCtx * HoroEditor$HoroEditCtx_new(void *pOwner);
void HoroEditor$HoroEditCtx_fini(HoroEditor$HoroEditCtx *self);

void  HoroEditor$HoroEditCtx$ctor(HoroEditor$HoroEditCtx *  self);
void  HoroEditor$HoroEditCtx$setState(HoroEditor$HoroEditCtx *  self, SuiView$TreeState*  state);
SuiDesigner$ANode*  HoroEditor$HoroEditCtx$findANodeByNode(SuiDesigner$ANode **  __outRef__, HoroEditor$HoroEditCtx *  self, SuiCore$Node *  node);
void  HoroEditor$HoroEditCtx$onSelectedChanged(HoroEditor$HoroEditCtx *  self);
void  HoroEditor$HoroEditCtx$setSceneView(HoroEditor$HoroEditCtx *  self, Sgl$SglSceneView *  sceneView);
Sgl$Scene *  HoroEditor$HoroEditCtx$getScene(HoroEditor$HoroEditCtx *  self);
void  HoroEditor$HoroEditCtx$closeCurrentPrefab(HoroEditor$HoroEditCtx *  self);
void  HoroEditor$HoroEditCtx$openPrefab(HoroEditor$HoroEditCtx *  self, const char *  path);
SuiDesigner$ANode*  HoroEditor$HoroEditCtx$getRoot(SuiDesigner$ANode **  __outRef__, HoroEditor$HoroEditCtx *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
