
typedef struct tagHoroEditor$HoroGeometryPreviewView HoroEditor$HoroGeometryPreviewView;
typedef struct tagVtable_HoroEditor$HoroGeometryPreviewView Vtable_HoroEditor$HoroGeometryPreviewView;


#ifndef define_struct___HoroEditor__HoroGeometryPreviewView_orc_h__
#define define_struct___HoroEditor__HoroGeometryPreviewView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__HoroGeometryPreviewView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__HoroGeometryPreviewView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__HoroGeometryPreviewView_orc_h__
#define __HoroEditor__HoroGeometryPreviewView_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Number_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Draw_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/GeometryPlane_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryCapsule_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DirLight_orc.h"
#include "../Sgl/PixelsReader_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/SplitterView_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Image_orc.h"
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
#include "../Sui/Core/KeyEvent_orc.h"
#include "./HoroEditor_orc.h"
#include "./UiAct_orc.h"
#include "../SuiDesigner/Theme_orc.h"
#include "../SuiDesigner/Insp_orc.h"
#include "../SuiDesigner/InvalidReact_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$HoroGeometryPreviewView {
	Vtable_SuiView$ImageView super;
};
//虚表实例
extern Vtable_HoroEditor$HoroGeometryPreviewView _vtable_HoroEditor$HoroGeometryPreviewView;

// class refc:0
struct tagHoroEditor$HoroGeometryPreviewView {
	SuiView$ImageView super; 
	Sui$Window*  win ;
	Sgl$Fbo*  fbo ;
	Sgl$Material*  matl ;
	Sgl$DrawCtx*  drawCtx ;
	Sgl$Scene*  scene ;
	Sgl$PerspectiveCamera*  camera ;
	SuiView$Drag*  drag ;
	float  rotateY ;
	float  scale ;
	SuiDesigner$InvalidReact*  _invalid ;
	Sgl$Mesh*  groundGrid ;
	SuiDesigner$Insp*  inspObj ;
	Sgl$Mesh*  mesh ;
	void  (*reactWindow) (HoroEditor$HoroGeometryPreviewView *  self);
	Orc$String*  path ;
	void  (*showWindow) (HoroEditor$HoroGeometryPreviewView *  self, const char *  path);
	void  (*onWindowEvent) (HoroEditor$HoroGeometryPreviewView *  self, SuiCore$Event *  e);
	void  (*mkBaseScene) (HoroEditor$HoroGeometryPreviewView *  self);
};
Vtable_HoroEditor$HoroGeometryPreviewView* Vtable_HoroEditor$HoroGeometryPreviewView_init(Vtable_HoroEditor$HoroGeometryPreviewView* pvt);
void HoroEditor$HoroGeometryPreviewView_init_fields(HoroEditor$HoroGeometryPreviewView *self);
void HoroEditor$HoroGeometryPreviewView_init(HoroEditor$HoroGeometryPreviewView *self, void *pOwner);
HoroEditor$HoroGeometryPreviewView * HoroEditor$HoroGeometryPreviewView_new(void *pOwner);
void HoroEditor$HoroGeometryPreviewView_fini(HoroEditor$HoroGeometryPreviewView *self);

void  HoroEditor$HoroGeometryPreviewView$ctor(HoroEditor$HoroGeometryPreviewView *  self);
void  HoroEditor$HoroGeometryPreviewView$dtor(HoroEditor$HoroGeometryPreviewView *  self);
void  HoroEditor$HoroGeometryPreviewView$reactWindow(HoroEditor$HoroGeometryPreviewView *  self);
void  HoroEditor$HoroGeometryPreviewView$showWindow(HoroEditor$HoroGeometryPreviewView *  self, const char *  path);
void  HoroEditor$HoroGeometryPreviewView$onWindowEvent(HoroEditor$HoroGeometryPreviewView *  self, SuiCore$Event *  e);
void  HoroEditor$HoroGeometryPreviewView$draw_self(HoroEditor$HoroGeometryPreviewView *  self, SuiCore$Canvas *  canvas);
void  HoroEditor$HoroGeometryPreviewView$onEvent(HoroEditor$HoroGeometryPreviewView *  self, SuiCore$Event *  e);
void  HoroEditor$HoroGeometryPreviewView$mkBaseScene(HoroEditor$HoroGeometryPreviewView *  self);

HoroEditor$HoroGeometryPreviewView*  HoroEditor$mkHoroGeometryPreviewView(HoroEditor$HoroGeometryPreviewView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
