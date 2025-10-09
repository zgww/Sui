
typedef struct tagSuiDesigner$ToolBase SuiDesigner$ToolBase;
typedef struct tagVtable_SuiDesigner$ToolBase Vtable_SuiDesigner$ToolBase;
typedef struct tagSuiDesigner$ToolSelect SuiDesigner$ToolSelect;
typedef struct tagVtable_SuiDesigner$ToolSelect Vtable_SuiDesigner$ToolSelect;
typedef struct tagSuiDesigner$ToolMgr SuiDesigner$ToolMgr;
typedef struct tagVtable_SuiDesigner$ToolMgr Vtable_SuiDesigner$ToolMgr;


#ifndef define_struct___SuiDesigner__ToolBase_orc_h__
#define define_struct___SuiDesigner__ToolBase_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__ToolBase_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__ToolBase_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__ToolBase_orc_h__
#define __SuiDesigner__ToolBase_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Camera_orc.h"
#include "../Sgl/Raycaster_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Light_orc.h"
#include "../Sgl/SpotLight_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/Billboard_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryLine_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "./SglEditCtx_orc.h"
#include "./SglGizmo_orc.h"
#include "./ANode_orc.h"
#include "../HoroEditor/HoroEditor_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$ToolBase {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ToolBase _vtable_SuiDesigner$ToolBase;

// class refc:0
struct tagSuiDesigner$ToolBase {
	Object super; 
	Orc$String*  name ;
	Orc$String*  iconPath ;
	SuiDesigner$ToolMgr*  mgr ;
	void  (*onEnable) (SuiDesigner$ToolBase *  self);
	void  (*onDisable) (SuiDesigner$ToolBase *  self);
	void  (*reactGizmo) (SuiDesigner$ToolBase *  self, Sgl$Obj3d *  gizmoScene);
	void  (*onEvent) (SuiDesigner$ToolBase *  self, SuiCore$Event *  e);
	void  (*draw2d) (SuiDesigner$ToolBase *  self, SuiCore$Canvas *  canvas);
	void  (*reactGizmosView) (SuiDesigner$ToolBase *  self, SuiCore$Node *  o);
};
Vtable_SuiDesigner$ToolBase* Vtable_SuiDesigner$ToolBase_init(Vtable_SuiDesigner$ToolBase* pvt);
void SuiDesigner$ToolBase_init_fields(SuiDesigner$ToolBase *self);
void SuiDesigner$ToolBase_init(SuiDesigner$ToolBase *self, void *pOwner);
SuiDesigner$ToolBase * SuiDesigner$ToolBase_new(void *pOwner);
void SuiDesigner$ToolBase_fini(SuiDesigner$ToolBase *self);

void  SuiDesigner$ToolBase$onEnable(SuiDesigner$ToolBase *  self);
void  SuiDesigner$ToolBase$onDisable(SuiDesigner$ToolBase *  self);
void  SuiDesigner$ToolBase$reactGizmo(SuiDesigner$ToolBase *  self, Sgl$Obj3d *  gizmoScene);
void  SuiDesigner$ToolBase$onEvent(SuiDesigner$ToolBase *  self, SuiCore$Event *  e);
void  SuiDesigner$ToolBase$draw2d(SuiDesigner$ToolBase *  self, SuiCore$Canvas *  canvas);
void  SuiDesigner$ToolBase$reactGizmosView(SuiDesigner$ToolBase *  self, SuiCore$Node *  o);


// 虚表
struct tagVtable_SuiDesigner$ToolSelect {
	Vtable_SuiDesigner$ToolBase super;
};
//虚表实例
extern Vtable_SuiDesigner$ToolSelect _vtable_SuiDesigner$ToolSelect;

// class refc:0
struct tagSuiDesigner$ToolSelect {
	SuiDesigner$ToolBase super; 
	SuiCore$Vec3 leftPos ;
	SuiView$Drag*  drag ;
};
Vtable_SuiDesigner$ToolSelect* Vtable_SuiDesigner$ToolSelect_init(Vtable_SuiDesigner$ToolSelect* pvt);
void SuiDesigner$ToolSelect_init_fields(SuiDesigner$ToolSelect *self);
void SuiDesigner$ToolSelect_init(SuiDesigner$ToolSelect *self, void *pOwner);
SuiDesigner$ToolSelect * SuiDesigner$ToolSelect_new(void *pOwner);
void SuiDesigner$ToolSelect_fini(SuiDesigner$ToolSelect *self);

void  SuiDesigner$ToolSelect$onEnable(SuiDesigner$ToolSelect *  self);
void  SuiDesigner$ToolSelect$onDisable(SuiDesigner$ToolSelect *  self);
void  SuiDesigner$ToolSelect$draw2d(SuiDesigner$ToolSelect *  self, SuiCore$Canvas *  canvas);
void  SuiDesigner$ToolSelect$reactGizmosView(SuiDesigner$ToolSelect *  self, SuiCore$Node *  o);
void  SuiDesigner$ToolSelect$onEvent(SuiDesigner$ToolSelect *  self, SuiCore$Event *  e);
void  SuiDesigner$ToolSelect$reactGizmo(SuiDesigner$ToolSelect *  self, Sgl$Obj3d *  o);


// 虚表
struct tagVtable_SuiDesigner$ToolMgr {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ToolMgr _vtable_SuiDesigner$ToolMgr;

// class refc:0
struct tagSuiDesigner$ToolMgr {
	Object super; 
	SuiDesigner$ToolBase*  tool ;
	SuiCore$Node*  selectNode ;
	Sgl$Scene*  scene ;
	Sgl$Camera*  camera ;
	SuiDesigner$SglEditCtx*  editCtx ;
	HoroEditor$HoroEditor*  editor ;
	void  (*setTool) (SuiDesigner$ToolMgr *  self, SuiDesigner$ToolBase *  tool);
	void  (*onEvent) (SuiDesigner$ToolMgr *  self, SuiCore$Event *  e);
	void  (*reactGizmo) (SuiDesigner$ToolMgr *  self, SuiDesigner$SglGizmo *  gizmoScene);
	void  (*_reactGizmosForNode) (SuiDesigner$ToolMgr *  self, SuiCore$Node *  n);
	SuiCore$Node *  gizmosView ;
	void  (*reactGizmosView) (SuiDesigner$ToolMgr *  self, SuiCore$Node *  o);
	void  (*draw2d) (SuiDesigner$ToolMgr *  self, SuiCore$Canvas *  canvas);
};
Vtable_SuiDesigner$ToolMgr* Vtable_SuiDesigner$ToolMgr_init(Vtable_SuiDesigner$ToolMgr* pvt);
void SuiDesigner$ToolMgr_init_fields(SuiDesigner$ToolMgr *self);
void SuiDesigner$ToolMgr_init(SuiDesigner$ToolMgr *self, void *pOwner);
SuiDesigner$ToolMgr * SuiDesigner$ToolMgr_new(void *pOwner);
void SuiDesigner$ToolMgr_fini(SuiDesigner$ToolMgr *self);

void  SuiDesigner$ToolMgr$setTool(SuiDesigner$ToolMgr *  self, SuiDesigner$ToolBase *  tool);
void  SuiDesigner$ToolMgr$onEvent(SuiDesigner$ToolMgr *  self, SuiCore$Event *  e);
void  SuiDesigner$ToolMgr$reactGizmo(SuiDesigner$ToolMgr *  self, SuiDesigner$SglGizmo *  gizmoScene);
void  SuiDesigner$ToolMgr$_reactGizmosForNode(SuiDesigner$ToolMgr *  self, SuiCore$Node *  n);
void  SuiDesigner$ToolMgr$reactGizmosView(SuiDesigner$ToolMgr *  self, SuiCore$Node *  o);
void  SuiDesigner$ToolMgr$draw2d(SuiDesigner$ToolMgr *  self, SuiCore$Canvas *  canvas);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
