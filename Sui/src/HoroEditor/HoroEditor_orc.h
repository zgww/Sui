
typedef struct tagHoroEditor$HoroEditorSceneViewCallback HoroEditor$HoroEditorSceneViewCallback;
typedef struct tagVtable_HoroEditor$HoroEditorSceneViewCallback Vtable_HoroEditor$HoroEditorSceneViewCallback;
typedef struct tagHoroEditor$HoroEditor HoroEditor$HoroEditor;
typedef struct tagVtable_HoroEditor$HoroEditor Vtable_HoroEditor$HoroEditor;


#ifndef define_struct___HoroEditor__HoroEditor_orc_h__
#define define_struct___HoroEditor__HoroEditor_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__HoroEditor_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__HoroEditor_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__HoroEditor_orc_h__
#define __HoroEditor__HoroEditor_orc_h__

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
#include "../SuiDesigner/EventANodeChanged_orc.h"
#include "../SuiDesigner/InvalidReact_orc.h"
#include "../SuiDesigner/MenuBarCtrl_orc.h"
#include "../SuiDesigner/ToolBase_orc.h"
#include "../SuiDesigner/SglGizmo_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../SuiDesigner/RegisterNodes_orc.h"
#undef INCLUDE_ONLY_TYPE
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
#include "./UiAct_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$HoroEditorSceneViewCallback {
	Vtable_SuiCore$ViewCallback super;
};
//虚表实例
extern Vtable_HoroEditor$HoroEditorSceneViewCallback _vtable_HoroEditor$HoroEditorSceneViewCallback;

// class refc:0
struct tagHoroEditor$HoroEditorSceneViewCallback {
	SuiCore$ViewCallback super; 
	HoroEditor$HoroEditor*  horoEditor ;
};
Vtable_HoroEditor$HoroEditorSceneViewCallback* Vtable_HoroEditor$HoroEditorSceneViewCallback_init(Vtable_HoroEditor$HoroEditorSceneViewCallback* pvt);
void HoroEditor$HoroEditorSceneViewCallback_init_fields(HoroEditor$HoroEditorSceneViewCallback *self);
void HoroEditor$HoroEditorSceneViewCallback_init(HoroEditor$HoroEditorSceneViewCallback *self, void *pOwner);
HoroEditor$HoroEditorSceneViewCallback * HoroEditor$HoroEditorSceneViewCallback_new(void *pOwner);
void HoroEditor$HoroEditorSceneViewCallback_fini(HoroEditor$HoroEditorSceneViewCallback *self);

void  HoroEditor$HoroEditorSceneViewCallback$afterDrawSelf(HoroEditor$HoroEditorSceneViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);


// 虚表
struct tagVtable_HoroEditor$HoroEditor {
	Vtable_SuiCore$Listener super;
};
//虚表实例
extern Vtable_HoroEditor$HoroEditor _vtable_HoroEditor$HoroEditor;

// class refc:0
struct tagHoroEditor$HoroEditor {
	SuiCore$Listener super; 
	HoroEditor$HoroEditCtx*  editCtx ;
	Sui$Window*  win ;
	SuiLayout$LayoutAlignPositionCell*  imgCell ;
	SuiLayout$LayoutAlignPositionCell*  previewCell ;
	SuiDesigner$InvalidReact*  invalidReact ;
	Orc$String*  path ;
	SuiView$Drag*  drag ;
	HoroEditor$HoroEditorSceneViewCallback*  viewCb ;
	void  (*printSceneTree) (HoroEditor$HoroEditor *  self);
	SuiDesigner$ToolMgr*  toolMgr ;
	SuiDesigner$SglGizmo*  sglGizmo ;
	void  (*onSceneEvent) (HoroEditor$HoroEditor *  self, SuiCore$Event *  e);
	void  (*_afterDrawScene) (HoroEditor$HoroEditor *  self);
	SuiDesigner$ChessBgViewCallback*  chessBg ;
	SuiCore$ViewBase *  (*reactPreview) (HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	void  (*showDialog_renameLayer) (HoroEditor$HoroEditor *  self);
	Sgl$MaterialPreviewView*  glPreviewView ;
	Sgl$Material*  matl ;
	SuiCore$ViewBase *  (*reactScene) (HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	SuiCore$View*  gizmosView ;
	void  (*reactGizmosView) (HoroEditor$HoroEditor *  self);
	Sgl$Mesh*  mesh ;
	Sgl$Mesh*  meshSphere ;
	Sgl$SglSceneView*  sceneView ;
	void  (*react) (HoroEditor$HoroEditor *  self);
	void  (*showWindow_mapSetting) (HoroEditor$HoroEditor *  self);
	SuiDesigner3d_w3e$W3e*  w3e ;
	Sgl$Geometry*  geom ;
	void  (*onWindowEvent) (HoroEditor$HoroEditor *  self, SuiCore$Event *  e);
	Sgl$Mesh*  heightmap ;
	Sgl$OutlineFx*  outlineFx ;
	void  (*showOutline) (HoroEditor$HoroEditor *  self);
	void  (*testShowMatl) (HoroEditor$HoroEditor *  self);
	void  (*showWindow) (HoroEditor$HoroEditor *  self);
	void  (*openProject) (HoroEditor$HoroEditor *  self, const char *  path);
};
Vtable_HoroEditor$HoroEditor* Vtable_HoroEditor$HoroEditor_init(Vtable_HoroEditor$HoroEditor* pvt);
void HoroEditor$HoroEditor_init_fields(HoroEditor$HoroEditor *self);
void HoroEditor$HoroEditor_init(HoroEditor$HoroEditor *self, void *pOwner);
HoroEditor$HoroEditor * HoroEditor$HoroEditor_new(void *pOwner);
void HoroEditor$HoroEditor_fini(HoroEditor$HoroEditor *self);

void  HoroEditor$HoroEditor$printSceneTree(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$onSceneEvent(HoroEditor$HoroEditor *  self, SuiCore$Event *  e);
void  HoroEditor$HoroEditor$_afterDrawScene(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$ctor(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$dtor(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$onListenerEvent(HoroEditor$HoroEditor *  self, SuiCore$Event *  e);
SuiCore$ViewBase *  HoroEditor$HoroEditor$reactPreview(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  HoroEditor$HoroEditor$showDialog_renameLayer(HoroEditor$HoroEditor *  self);
SuiCore$ViewBase *  HoroEditor$HoroEditor$reactScene(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  HoroEditor$HoroEditor$reactGizmosView(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$react(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$showWindow_mapSetting(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$onWindowEvent(HoroEditor$HoroEditor *  self, SuiCore$Event *  e);
void  HoroEditor$HoroEditor$showOutline(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$testShowMatl(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$showWindow(HoroEditor$HoroEditor *  self);
void  HoroEditor$HoroEditor$openProject(HoroEditor$HoroEditor *  self, const char *  path);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
