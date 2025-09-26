
typedef struct tagSgl$SglSceneView Sgl$SglSceneView;
typedef struct tagVtable_Sgl$SglSceneView Vtable_Sgl$SglSceneView;
typedef struct tagSgl$DepthTexturePreview Sgl$DepthTexturePreview;
typedef struct tagVtable_Sgl$DepthTexturePreview Vtable_Sgl$DepthTexturePreview;


#ifndef define_struct___Sgl__SglSceneView_orc_h__
#define define_struct___Sgl__SglSceneView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__SglSceneView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__SglSceneView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__SglSceneView_orc_h__
#define __Sgl__SglSceneView_orc_h__

//include  importHeadCode
#include "./Mat_orc.h"
#include "./Program_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Math_orc.h"
#include "../Json/Json_orc.h"
#include "../Sui/Core/Focus_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/View/Switch_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/Panel_orc.h"
#include "../Sui/View/ColorPicker_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "./Tex2d_orc.h"
#include "./Fbo_orc.h"
#include "./Draw_orc.h"
#include "./Geometry_orc.h"
#include "./Material_orc.h"
#include "./DrawCtx_orc.h"
#include "./Scene_orc.h"
#include "./Buffer_orc.h"
#include "./PointLight_orc.h"
#include "./DirLight_orc.h"
#include "./PixelsReader_orc.h"
#include "./PerspectiveCamera_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$SglSceneView {
	Vtable_SuiView$ImageView super;
};
//虚表实例
extern Vtable_Sgl$SglSceneView _vtable_Sgl$SglSceneView;

// class refc:0
struct tagSgl$SglSceneView {
	SuiView$ImageView super; 
	Sgl$Fbo*  fbo ;
	Sgl$Material*  matl ;
	Sgl$Draw*  drawObj ;
	Sgl$DrawCtx*  drawCtx ;
	Sgl$Scene*  scene ;
	Sgl$PerspectiveCamera*  camera ;
	void  (*buildDrawObj) (Sgl$SglSceneView *  self);
	Sgl$DepthTexturePreview*  depthPreview ;
	float  rotateY ;
	float  scale ;
	void  (*applyModel) (Sgl$SglSceneView *  self);
	void  (*mkBaseScene) (Sgl$SglSceneView *  self);
	SuiView$Drag*  drag ;
};
Vtable_Sgl$SglSceneView* Vtable_Sgl$SglSceneView_init(Vtable_Sgl$SglSceneView* pvt);
void Sgl$SglSceneView_init_fields(Sgl$SglSceneView *self);
void Sgl$SglSceneView_init(Sgl$SglSceneView *self, void *pOwner);
Sgl$SglSceneView * Sgl$SglSceneView_new(void *pOwner);
void Sgl$SglSceneView_fini(Sgl$SglSceneView *self);

void  Sgl$SglSceneView$buildDrawObj(Sgl$SglSceneView *  self);
void  Sgl$SglSceneView$draw_self(Sgl$SglSceneView *  self, SuiCore$Canvas *  canvas);
void  Sgl$SglSceneView$onEvent(Sgl$SglSceneView *  self, SuiCore$Event *  e);
void  Sgl$SglSceneView$applyModel(Sgl$SglSceneView *  self);
void  Sgl$SglSceneView$mkBaseScene(Sgl$SglSceneView *  self);

Sgl$SglSceneView*  Sgl$mkSglSceneView(Sgl$SglSceneView **  __outRef__, void *  parent, long long  key);
void  Sgl$SglSceneView_showTextureWindow(Sgl$Tex2d *  tex, int  w, int  h);

// 虚表
struct tagVtable_Sgl$DepthTexturePreview {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$DepthTexturePreview _vtable_Sgl$DepthTexturePreview;

// class refc:0
struct tagSgl$DepthTexturePreview {
	Object super; 
	Sgl$Tex2d*  depthTex ;
	Sgl$Buffer*  depthRedBuffer ;
	Sgl$DepthFloatPixlesReader*  depthPixelsReader ;
	void  (*init_readPixels) (Sgl$DepthTexturePreview *  self, int  w, int  h);
	void  (*init) (Sgl$DepthTexturePreview *  self, int  width, int  height);
	void  (*showTextureWindow) (Sgl$DepthTexturePreview *  self);
	void  (*readPixels) (Sgl$DepthTexturePreview *  self);
};
Vtable_Sgl$DepthTexturePreview* Vtable_Sgl$DepthTexturePreview_init(Vtable_Sgl$DepthTexturePreview* pvt);
void Sgl$DepthTexturePreview_init_fields(Sgl$DepthTexturePreview *self);
void Sgl$DepthTexturePreview_init(Sgl$DepthTexturePreview *self, void *pOwner);
Sgl$DepthTexturePreview * Sgl$DepthTexturePreview_new(void *pOwner);
void Sgl$DepthTexturePreview_fini(Sgl$DepthTexturePreview *self);

void  Sgl$DepthTexturePreview$init_readPixels(Sgl$DepthTexturePreview *  self, int  w, int  h);
void  Sgl$DepthTexturePreview$init(Sgl$DepthTexturePreview *  self, int  width, int  height);
void  Sgl$DepthTexturePreview$showTextureWindow(Sgl$DepthTexturePreview *  self);
void  Sgl$DepthTexturePreview$readPixels(Sgl$DepthTexturePreview *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
