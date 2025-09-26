
typedef struct tagSuiDesigner3d$W3eEditor SuiDesigner3d$W3eEditor;
typedef struct tagVtable_SuiDesigner3d$W3eEditor Vtable_SuiDesigner3d$W3eEditor;


#ifndef define_struct___SuiDesigner3d__W3eEditor_orc_h__
#define define_struct___SuiDesigner3d__W3eEditor_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner3d__W3eEditor_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner3d__W3eEditor_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner3d__W3eEditor_orc_h__
#define __SuiDesigner3d__W3eEditor_orc_h__

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
#include "../Sgl/GeometryRing_orc.h"
#include "../Sgl/GeometryCylinder_orc.h"
#include "../Sgl/GeometryCone_orc.h"
#include "../Sgl/GeometryArrow_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Skybox_orc.h"
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
struct tagVtable_SuiDesigner3d$W3eEditor {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner3d$W3eEditor _vtable_SuiDesigner3d$W3eEditor;

// class refc:0
struct tagSuiDesigner3d$W3eEditor {
	Object super; 
	SuiDesigner$SglEditCtx*  editCtx ;
	Sui$Window*  win ;
	SuiLayout$LayoutAlignPositionCell*  imgCell ;
	SuiLayout$LayoutAlignPositionCell*  previewCell ;
	SuiDesigner$InvalidReact*  invalidReact ;
	Orc$String*  path ;
	SuiView$Drag*  drag ;
	void  (*printSceneTree) (SuiDesigner3d$W3eEditor *  self);
	SuiDesigner$ChessBgViewCallback*  chessBg ;
	SuiCore$ViewBase *  (*reactPreview) (SuiDesigner3d$W3eEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	void  (*showDialog_renameLayer) (SuiDesigner3d$W3eEditor *  self);
	Sgl$MaterialPreviewView*  glPreviewView ;
	Sgl$Material*  matl ;
	SuiCore$ViewBase *  (*reactScene) (SuiDesigner3d$W3eEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	Sgl$Mesh*  mesh ;
	Sgl$Mesh*  meshSphere ;
	Sgl$SglSceneView*  sceneView ;
	void  (*drawDepthView) (SuiDesigner3d$W3eEditor *  self);
	void  (*react) (SuiDesigner3d$W3eEditor *  self);
	void  (*showWindow_mapSetting) (SuiDesigner3d$W3eEditor *  self);
	SuiDesigner3d_w3e$W3e*  w3e ;
	Sgl$Geometry*  geom ;
	void  (*onWindowEvent) (SuiDesigner3d$W3eEditor *  self, SuiCore$Event *  e);
	void  (*showWindow) (SuiDesigner3d$W3eEditor *  self);
};
Vtable_SuiDesigner3d$W3eEditor* Vtable_SuiDesigner3d$W3eEditor_init(Vtable_SuiDesigner3d$W3eEditor* pvt);
void SuiDesigner3d$W3eEditor_init_fields(SuiDesigner3d$W3eEditor *self);
void SuiDesigner3d$W3eEditor_init(SuiDesigner3d$W3eEditor *self, void *pOwner);
SuiDesigner3d$W3eEditor * SuiDesigner3d$W3eEditor_new(void *pOwner);
void SuiDesigner3d$W3eEditor_fini(SuiDesigner3d$W3eEditor *self);

void  SuiDesigner3d$W3eEditor$printSceneTree(SuiDesigner3d$W3eEditor *  self);
void  SuiDesigner3d$W3eEditor$ctor(SuiDesigner3d$W3eEditor *  self);
SuiCore$ViewBase *  SuiDesigner3d$W3eEditor$reactPreview(SuiDesigner3d$W3eEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner3d$W3eEditor$showDialog_renameLayer(SuiDesigner3d$W3eEditor *  self);
SuiCore$ViewBase *  SuiDesigner3d$W3eEditor$reactScene(SuiDesigner3d$W3eEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner3d$W3eEditor$drawDepthView(SuiDesigner3d$W3eEditor *  self);
void  SuiDesigner3d$W3eEditor$react(SuiDesigner3d$W3eEditor *  self);
void  SuiDesigner3d$W3eEditor$showWindow_mapSetting(SuiDesigner3d$W3eEditor *  self);
void  SuiDesigner3d$W3eEditor$onWindowEvent(SuiDesigner3d$W3eEditor *  self, SuiCore$Event *  e);
void  SuiDesigner3d$W3eEditor$showWindow(SuiDesigner3d$W3eEditor *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
