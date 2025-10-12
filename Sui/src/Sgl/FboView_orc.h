
typedef struct tagSgl$FboView Sgl$FboView;
typedef struct tagVtable_Sgl$FboView Vtable_Sgl$FboView;


#ifndef define_struct___Sgl__FboView_orc_h__
#define define_struct___Sgl__FboView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__FboView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__FboView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__FboView_orc_h__
#define __Sgl__FboView_orc_h__

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
#include "../Sgl/GeometryHeightMap_orc.h"
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
#include "../SuiDesigner/Theme_orc.h"
#include "../SuiDesigner/Insp_orc.h"
#include "../SuiDesigner/InvalidReact_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$FboView {
	Vtable_SuiView$ImageView super;
};
//虚表实例
extern Vtable_Sgl$FboView _vtable_Sgl$FboView;

// class refc:0
struct tagSgl$FboView {
	SuiView$ImageView super; 
	Sgl$Fbo*  fbo ;
	Sgl$DrawCtx*  drawCtx ;
	Sgl$Scene*  scene ;
	Sgl$PerspectiveCamera*  camera ;
	Sgl$Mesh*  groundGrid ;
	SuiView$Drag*  drag ;
	void  (**cbDraw)(void *  self, Sgl$FboView *  s);
	void  (*mkBaseScene) (Sgl$FboView *  self);
};
Vtable_Sgl$FboView* Vtable_Sgl$FboView_init(Vtable_Sgl$FboView* pvt);
void Sgl$FboView_init_fields(Sgl$FboView *self);
void Sgl$FboView_init(Sgl$FboView *self, void *pOwner);
Sgl$FboView * Sgl$FboView_new(void *pOwner);
void Sgl$FboView_fini(Sgl$FboView *self);

void  Sgl$FboView$ctor(Sgl$FboView *  self);
void  Sgl$FboView$draw_self(Sgl$FboView *  self, SuiCore$Canvas *  canvas);
void  Sgl$FboView$onEvent(Sgl$FboView *  self, SuiCore$Event *  e);
void  Sgl$FboView$mkBaseScene(Sgl$FboView *  self);

Sgl$FboView*  Sgl$mkFboView(Sgl$FboView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
