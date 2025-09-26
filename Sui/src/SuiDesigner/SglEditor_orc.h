
typedef struct tagSuiDesigner3d$SglEditorSceneViewCallback SuiDesigner3d$SglEditorSceneViewCallback;
typedef struct tagVtable_SuiDesigner3d$SglEditorSceneViewCallback Vtable_SuiDesigner3d$SglEditorSceneViewCallback;
typedef struct tagSuiDesigner3d$SglEditor SuiDesigner3d$SglEditor;
typedef struct tagVtable_SuiDesigner3d$SglEditor Vtable_SuiDesigner3d$SglEditor;


#ifndef define_struct___SuiDesigner3d__SglEditor_orc_h__
#define define_struct___SuiDesigner3d__SglEditor_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner3d__SglEditor_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner3d__SglEditor_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner3d__SglEditor_orc_h__
#define __SuiDesigner3d__SglEditor_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Mouse_orc.h"
#include "../Sui/Core/KeyEvent_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Dialog/FileDialog_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "../Sui/View/DockLayout_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "../SuiDesigner/DrawDegree_orc.h"
#include "./ChessBgViewCallback_orc.h"
#include "./Theme_orc.h"
#include "./W3e_orc.h"
#include "./InvalidReact_orc.h"
#include "./MenuBarCtrl_orc.h"
#include "./ToolBase_orc.h"
#include "./SglGizmo_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/Draw_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/SkinMesh_orc.h"
#include "../Sgl/Particle_orc.h"
#include "../Sgl/GeometryHeightMap_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryPlane_orc.h"
#include "../Sgl/GeometryRect_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/GeometryCircle_orc.h"
#include "../Sgl/GeometryLine_orc.h"
#include "../Sgl/GeometryRing_orc.h"
#include "../Sgl/GeometryCylinder_orc.h"
#include "../Sgl/GeometryCone_orc.h"
#include "../Sgl/GeometryArrow_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/Billboard_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Skybox_orc.h"
#include "../Sgl/OutlineFx_orc.h"
#include "./MdxReader_orc.h"
#include "./SglSceneHierView_orc.h"
#include "./SglEditCtx_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./Project_orc.h"
#include "./SglInspectorView_orc.h"
#include "./SglInspView_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner3d$SglEditorSceneViewCallback {
	Vtable_SuiCore$ViewCallback super;
};
//虚表实例
extern Vtable_SuiDesigner3d$SglEditorSceneViewCallback _vtable_SuiDesigner3d$SglEditorSceneViewCallback;

// class refc:0
struct tagSuiDesigner3d$SglEditorSceneViewCallback {
	SuiCore$ViewCallback super; 
	SuiDesigner3d$SglEditor*  sglEditor ;
};
Vtable_SuiDesigner3d$SglEditorSceneViewCallback* Vtable_SuiDesigner3d$SglEditorSceneViewCallback_init(Vtable_SuiDesigner3d$SglEditorSceneViewCallback* pvt);
void SuiDesigner3d$SglEditorSceneViewCallback_init_fields(SuiDesigner3d$SglEditorSceneViewCallback *self);
void SuiDesigner3d$SglEditorSceneViewCallback_init(SuiDesigner3d$SglEditorSceneViewCallback *self, void *pOwner);
SuiDesigner3d$SglEditorSceneViewCallback * SuiDesigner3d$SglEditorSceneViewCallback_new(void *pOwner);
void SuiDesigner3d$SglEditorSceneViewCallback_fini(SuiDesigner3d$SglEditorSceneViewCallback *self);

void  SuiDesigner3d$SglEditorSceneViewCallback$afterDrawSelf(SuiDesigner3d$SglEditorSceneViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);


// 虚表
struct tagVtable_SuiDesigner3d$SglEditor {
	Vtable_SuiCore$Listener super;
};
//虚表实例
extern Vtable_SuiDesigner3d$SglEditor _vtable_SuiDesigner3d$SglEditor;

// class refc:0
struct tagSuiDesigner3d$SglEditor {
	SuiCore$Listener super; 
	SuiDesigner$SglEditCtx*  editCtx ;
	Sui$Window*  win ;
	SuiLayout$LayoutAlignPositionCell*  imgCell ;
	SuiLayout$LayoutAlignPositionCell*  previewCell ;
	SuiDesigner$InvalidReact*  invalidReact ;
	Orc$String*  path ;
	SuiView$Drag*  drag ;
	SuiDesigner3d$SglEditorSceneViewCallback*  viewCb ;
	void  (*printSceneTree) (SuiDesigner3d$SglEditor *  self);
	SuiDesigner$ToolMgr*  toolMgr ;
	SuiDesigner$SglGizmo*  sglGizmo ;
	void  (*onSceneEvent) (SuiDesigner3d$SglEditor *  self, SuiCore$Event *  e);
	void  (*_afterDrawScene) (SuiDesigner3d$SglEditor *  self);
	SuiDesigner$ChessBgViewCallback*  chessBg ;
	SuiCore$ViewBase *  (*reactPreview) (SuiDesigner3d$SglEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	void  (*showDialog_renameLayer) (SuiDesigner3d$SglEditor *  self);
	Sgl$MaterialPreviewView*  glPreviewView ;
	Sgl$Material*  matl ;
	SuiCore$ViewBase *  (*reactScene) (SuiDesigner3d$SglEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	SuiCore$View*  gizmosView ;
	void  (*reactGizmosView) (SuiDesigner3d$SglEditor *  self);
	Sgl$Mesh*  mesh ;
	Sgl$Mesh*  meshSphere ;
	Sgl$SglSceneView*  sceneView ;
	void  (*react) (SuiDesigner3d$SglEditor *  self);
	void  (*showWindow_mapSetting) (SuiDesigner3d$SglEditor *  self);
	SuiDesigner3d_w3e$W3e*  w3e ;
	Sgl$Geometry*  geom ;
	void  (*onWindowEvent) (SuiDesigner3d$SglEditor *  self, SuiCore$Event *  e);
	Sgl$Mesh*  heightmap ;
	Sgl$OutlineFx*  outlineFx ;
	void  (*showOutline) (SuiDesigner3d$SglEditor *  self);
	void  (*testShowMatl) (SuiDesigner3d$SglEditor *  self);
	void  (*showWindow) (SuiDesigner3d$SglEditor *  self);
};
Vtable_SuiDesigner3d$SglEditor* Vtable_SuiDesigner3d$SglEditor_init(Vtable_SuiDesigner3d$SglEditor* pvt);
void SuiDesigner3d$SglEditor_init_fields(SuiDesigner3d$SglEditor *self);
void SuiDesigner3d$SglEditor_init(SuiDesigner3d$SglEditor *self, void *pOwner);
SuiDesigner3d$SglEditor * SuiDesigner3d$SglEditor_new(void *pOwner);
void SuiDesigner3d$SglEditor_fini(SuiDesigner3d$SglEditor *self);

void  SuiDesigner3d$SglEditor$printSceneTree(SuiDesigner3d$SglEditor *  self);
void  SuiDesigner3d$SglEditor$onSceneEvent(SuiDesigner3d$SglEditor *  self, SuiCore$Event *  e);
void  SuiDesigner3d$SglEditor$_afterDrawScene(SuiDesigner3d$SglEditor *  self);
void  SuiDesigner3d$SglEditor$ctor(SuiDesigner3d$SglEditor *  self);
void  SuiDesigner3d$SglEditor$dtor(SuiDesigner3d$SglEditor *  self);
void  SuiDesigner3d$SglEditor$onListenerEvent(SuiDesigner3d$SglEditor *  self, SuiCore$Event *  e);
SuiCore$ViewBase *  SuiDesigner3d$SglEditor$reactPreview(SuiDesigner3d$SglEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner3d$SglEditor$showDialog_renameLayer(SuiDesigner3d$SglEditor *  self);
SuiCore$ViewBase *  SuiDesigner3d$SglEditor$reactScene(SuiDesigner3d$SglEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner3d$SglEditor$reactGizmosView(SuiDesigner3d$SglEditor *  self);
void  SuiDesigner3d$SglEditor$react(SuiDesigner3d$SglEditor *  self);
void  SuiDesigner3d$SglEditor$showWindow_mapSetting(SuiDesigner3d$SglEditor *  self);
void  SuiDesigner3d$SglEditor$onWindowEvent(SuiDesigner3d$SglEditor *  self, SuiCore$Event *  e);
void  SuiDesigner3d$SglEditor$showOutline(SuiDesigner3d$SglEditor *  self);
void  SuiDesigner3d$SglEditor$testShowMatl(SuiDesigner3d$SglEditor *  self);
void  SuiDesigner3d$SglEditor$showWindow(SuiDesigner3d$SglEditor *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
