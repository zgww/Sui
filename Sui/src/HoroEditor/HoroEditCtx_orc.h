
typedef struct tagSuiDesigner$EventHoroSceneChanged SuiDesigner$EventHoroSceneChanged;
typedef struct tagVtable_SuiDesigner$EventHoroSceneChanged Vtable_SuiDesigner$EventHoroSceneChanged;
typedef struct tagSuiDesigner$EventHoroSelectedChanged SuiDesigner$EventHoroSelectedChanged;
typedef struct tagVtable_SuiDesigner$EventHoroSelectedChanged Vtable_SuiDesigner$EventHoroSelectedChanged;
typedef struct tagSuiDesigner$HoroEditCtx SuiDesigner$HoroEditCtx;
typedef struct tagVtable_SuiDesigner$HoroEditCtx Vtable_SuiDesigner$HoroEditCtx;


#ifndef define_struct___SuiDesigner__HoroEditCtx_orc_h__
#define define_struct___SuiDesigner__HoroEditCtx_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__HoroEditCtx_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__HoroEditCtx_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__HoroEditCtx_orc_h__
#define __SuiDesigner__HoroEditCtx_orc_h__

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
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Obj3d_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$EventHoroSceneChanged {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_SuiDesigner$EventHoroSceneChanged _vtable_SuiDesigner$EventHoroSceneChanged;

// class refc:0
struct tagSuiDesigner$EventHoroSceneChanged {
	SuiCore$Event super; 
	
};
Vtable_SuiDesigner$EventHoroSceneChanged* Vtable_SuiDesigner$EventHoroSceneChanged_init(Vtable_SuiDesigner$EventHoroSceneChanged* pvt);
void SuiDesigner$EventHoroSceneChanged_init_fields(SuiDesigner$EventHoroSceneChanged *self);
void SuiDesigner$EventHoroSceneChanged_init(SuiDesigner$EventHoroSceneChanged *self, void *pOwner);
SuiDesigner$EventHoroSceneChanged * SuiDesigner$EventHoroSceneChanged_new(void *pOwner);
void SuiDesigner$EventHoroSceneChanged_fini(SuiDesigner$EventHoroSceneChanged *self);



// 虚表
struct tagVtable_SuiDesigner$EventHoroSelectedChanged {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_SuiDesigner$EventHoroSelectedChanged _vtable_SuiDesigner$EventHoroSelectedChanged;

// class refc:0
struct tagSuiDesigner$EventHoroSelectedChanged {
	SuiCore$Event super; 
	
};
Vtable_SuiDesigner$EventHoroSelectedChanged* Vtable_SuiDesigner$EventHoroSelectedChanged_init(Vtable_SuiDesigner$EventHoroSelectedChanged* pvt);
void SuiDesigner$EventHoroSelectedChanged_init_fields(SuiDesigner$EventHoroSelectedChanged *self);
void SuiDesigner$EventHoroSelectedChanged_init(SuiDesigner$EventHoroSelectedChanged *self, void *pOwner);
SuiDesigner$EventHoroSelectedChanged * SuiDesigner$EventHoroSelectedChanged_new(void *pOwner);
void SuiDesigner$EventHoroSelectedChanged_fini(SuiDesigner$EventHoroSelectedChanged *self);



// 虚表
struct tagVtable_SuiDesigner$HoroEditCtx {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$HoroEditCtx _vtable_SuiDesigner$HoroEditCtx;

// class refc:0
struct tagSuiDesigner$HoroEditCtx {
	Object super; 
	SuiView$TreeState*  state ;
	Sgl$SglSceneView*  sceneView ;
	Orc$List*  roots ;
	SuiCore$Node*  hoverNode ;
	void  (*setState) (SuiDesigner$HoroEditCtx *  self, SuiView$TreeState*  state);
	void  (*onSelectedChanged) (SuiDesigner$HoroEditCtx *  self);
	void  (*setSceneView) (SuiDesigner$HoroEditCtx *  self, Sgl$SglSceneView *  sceneView);
	Sgl$Scene *  (*getScene) (SuiDesigner$HoroEditCtx *  self);
};
Vtable_SuiDesigner$HoroEditCtx* Vtable_SuiDesigner$HoroEditCtx_init(Vtable_SuiDesigner$HoroEditCtx* pvt);
void SuiDesigner$HoroEditCtx_init_fields(SuiDesigner$HoroEditCtx *self);
void SuiDesigner$HoroEditCtx_init(SuiDesigner$HoroEditCtx *self, void *pOwner);
SuiDesigner$HoroEditCtx * SuiDesigner$HoroEditCtx_new(void *pOwner);
void SuiDesigner$HoroEditCtx_fini(SuiDesigner$HoroEditCtx *self);

void  SuiDesigner$HoroEditCtx$setState(SuiDesigner$HoroEditCtx *  self, SuiView$TreeState*  state);
void  SuiDesigner$HoroEditCtx$onSelectedChanged(SuiDesigner$HoroEditCtx *  self);
void  SuiDesigner$HoroEditCtx$setSceneView(SuiDesigner$HoroEditCtx *  self, Sgl$SglSceneView *  sceneView);
Sgl$Scene *  SuiDesigner$HoroEditCtx$getScene(SuiDesigner$HoroEditCtx *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
