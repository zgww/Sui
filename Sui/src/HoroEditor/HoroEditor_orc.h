
typedef struct tagSuiDesigner3d$HoroEditorSceneViewCallback SuiDesigner3d$HoroEditorSceneViewCallback;
typedef struct tagVtable_SuiDesigner3d$HoroEditorSceneViewCallback Vtable_SuiDesigner3d$HoroEditorSceneViewCallback;
typedef struct tagSuiDesigner3d$HoroEditor SuiDesigner3d$HoroEditor;
typedef struct tagVtable_SuiDesigner3d$HoroEditor Vtable_SuiDesigner3d$HoroEditor;


#ifndef define_struct___SuiDesigner3d__HoroEditor_orc_h__
#define define_struct___SuiDesigner3d__HoroEditor_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner3d__HoroEditor_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner3d__HoroEditor_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner3d__HoroEditor_orc_h__
#define __SuiDesigner3d__HoroEditor_orc_h__

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
#include "../SuiDesigner/ChessBgViewCallback_orc.h"
#include "../SuiDesigner/Theme_orc.h"
#include "../SuiDesigner/W3e_orc.h"
#include "../SuiDesigner/InvalidReact_orc.h"
#include "../SuiDesigner/MenuBarCtrl_orc.h"
#include "../SuiDesigner/ToolBase_orc.h"
#include "../SuiDesigner/SglGizmo_orc.h"
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
#include "../Sgl/Billboard_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Skybox_orc.h"
#include "../Sgl/OutlineFx_orc.h"
#include "../SuiDesigner/MdxReader_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/Project_orc.h"
#include "../SuiDesigner/SglInspectorView_orc.h"
#include "../SuiDesigner/SglInspView_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "./HoroSceneHierView_orc.h"
#include "./HoroEditCtx_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner3d$HoroEditorSceneViewCallback {
	Vtable_SuiCore$ViewCallback super;
};
//虚表实例
extern Vtable_SuiDesigner3d$HoroEditorSceneViewCallback _vtable_SuiDesigner3d$HoroEditorSceneViewCallback;

// class refc:0
struct tagSuiDesigner3d$HoroEditorSceneViewCallback {
	SuiCore$ViewCallback super; 
	SuiDesigner3d$HoroEditor*  horoEditor ;
};
Vtable_SuiDesigner3d$HoroEditorSceneViewCallback* Vtable_SuiDesigner3d$HoroEditorSceneViewCallback_init(Vtable_SuiDesigner3d$HoroEditorSceneViewCallback* pvt);
void SuiDesigner3d$HoroEditorSceneViewCallback_init_fields(SuiDesigner3d$HoroEditorSceneViewCallback *self);
void SuiDesigner3d$HoroEditorSceneViewCallback_init(SuiDesigner3d$HoroEditorSceneViewCallback *self, void *pOwner);
SuiDesigner3d$HoroEditorSceneViewCallback * SuiDesigner3d$HoroEditorSceneViewCallback_new(void *pOwner);
void SuiDesigner3d$HoroEditorSceneViewCallback_fini(SuiDesigner3d$HoroEditorSceneViewCallback *self);

void  SuiDesigner3d$HoroEditorSceneViewCallback$afterDrawSelf(SuiDesigner3d$HoroEditorSceneViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);


// 虚表
struct tagVtable_SuiDesigner3d$HoroEditor {
	Vtable_SuiCore$Listener super;
};
//虚表实例
extern Vtable_SuiDesigner3d$HoroEditor _vtable_SuiDesigner3d$HoroEditor;

// class refc:0
struct tagSuiDesigner3d$HoroEditor {
	SuiCore$Listener super; 
	SuiDesigner$HoroEditCtx*  editCtx ;
	Sui$Window*  win ;
	SuiLayout$LayoutAlignPositionCell*  imgCell ;
	SuiLayout$LayoutAlignPositionCell*  previewCell ;
	SuiDesigner$InvalidReact*  invalidReact ;
	Orc$String*  path ;
	SuiView$Drag*  drag ;
	SuiDesigner3d$HoroEditorSceneViewCallback*  viewCb ;
	void  (*printSceneTree) (SuiDesigner3d$HoroEditor *  self);
	SuiDesigner$ToolMgr*  toolMgr ;
	SuiDesigner$SglGizmo*  sglGizmo ;
	void  (*onSceneEvent) (SuiDesigner3d$HoroEditor *  self, SuiCore$Event *  e);
	void  (*_afterDrawScene) (SuiDesigner3d$HoroEditor *  self);
	SuiDesigner$ChessBgViewCallback*  chessBg ;
	SuiCore$ViewBase *  (*reactPreview) (SuiDesigner3d$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	void  (*showDialog_renameLayer) (SuiDesigner3d$HoroEditor *  self);
	Sgl$MaterialPreviewView*  glPreviewView ;
	Sgl$Material*  matl ;
	SuiCore$ViewBase *  (*reactScene) (SuiDesigner3d$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	SuiCore$View*  gizmosView ;
	void  (*reactGizmosView) (SuiDesigner3d$HoroEditor *  self);
	Sgl$Mesh*  mesh ;
	Sgl$Mesh*  meshSphere ;
	Sgl$SglSceneView*  sceneView ;
	void  (*react) (SuiDesigner3d$HoroEditor *  self);
	void  (*showWindow_mapSetting) (SuiDesigner3d$HoroEditor *  self);
	SuiDesigner3d_w3e$W3e*  w3e ;
	Sgl$Geometry*  geom ;
	void  (*onWindowEvent) (SuiDesigner3d$HoroEditor *  self, SuiCore$Event *  e);
	Sgl$Mesh*  heightmap ;
	Sgl$OutlineFx*  outlineFx ;
	void  (*showOutline) (SuiDesigner3d$HoroEditor *  self);
	void  (*testShowMatl) (SuiDesigner3d$HoroEditor *  self);
	void  (*showWindow) (SuiDesigner3d$HoroEditor *  self);
	void  (*openProject) (SuiDesigner3d$HoroEditor *  self, const char *  path);
};
Vtable_SuiDesigner3d$HoroEditor* Vtable_SuiDesigner3d$HoroEditor_init(Vtable_SuiDesigner3d$HoroEditor* pvt);
void SuiDesigner3d$HoroEditor_init_fields(SuiDesigner3d$HoroEditor *self);
void SuiDesigner3d$HoroEditor_init(SuiDesigner3d$HoroEditor *self, void *pOwner);
SuiDesigner3d$HoroEditor * SuiDesigner3d$HoroEditor_new(void *pOwner);
void SuiDesigner3d$HoroEditor_fini(SuiDesigner3d$HoroEditor *self);

void  SuiDesigner3d$HoroEditor$printSceneTree(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$onSceneEvent(SuiDesigner3d$HoroEditor *  self, SuiCore$Event *  e);
void  SuiDesigner3d$HoroEditor$_afterDrawScene(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$ctor(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$dtor(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$onListenerEvent(SuiDesigner3d$HoroEditor *  self, SuiCore$Event *  e);
SuiCore$ViewBase *  SuiDesigner3d$HoroEditor$reactPreview(SuiDesigner3d$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner3d$HoroEditor$showDialog_renameLayer(SuiDesigner3d$HoroEditor *  self);
SuiCore$ViewBase *  SuiDesigner3d$HoroEditor$reactScene(SuiDesigner3d$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner3d$HoroEditor$reactGizmosView(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$react(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$showWindow_mapSetting(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$onWindowEvent(SuiDesigner3d$HoroEditor *  self, SuiCore$Event *  e);
void  SuiDesigner3d$HoroEditor$showOutline(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$testShowMatl(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$showWindow(SuiDesigner3d$HoroEditor *  self);
void  SuiDesigner3d$HoroEditor$openProject(SuiDesigner3d$HoroEditor *  self, const char *  path);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
