
typedef struct tagHoroEditor$Horo3dSceneView HoroEditor$Horo3dSceneView;
typedef struct tagVtable_HoroEditor$Horo3dSceneView Vtable_HoroEditor$Horo3dSceneView;


#ifndef define_struct___HoroEditor__Horo3dSceneView_orc_h__
#define define_struct___HoroEditor__Horo3dSceneView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__Horo3dSceneView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__Horo3dSceneView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__Horo3dSceneView_orc_h__
#define __HoroEditor__Horo3dSceneView_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Draw_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DirLight_orc.h"
#include "../Sgl/PixelsReader_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
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


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$Horo3dSceneView {
	Vtable_SuiView$ImageView super;
};
//虚表实例
extern Vtable_HoroEditor$Horo3dSceneView _vtable_HoroEditor$Horo3dSceneView;

// class refc:0
struct tagHoroEditor$Horo3dSceneView {
	SuiView$ImageView super; 
	Sgl$Fbo*  fbo ;
	Sgl$Material*  matl ;
	Sgl$DrawCtx*  drawCtx ;
	Sgl$Scene*  scene ;
	Sgl$PerspectiveCamera*  camera ;
	SuiView$Drag*  drag ;
	float  rotateY ;
	float  scale ;
	void  (*mkBaseScene) (HoroEditor$Horo3dSceneView *  self);
};
Vtable_HoroEditor$Horo3dSceneView* Vtable_HoroEditor$Horo3dSceneView_init(Vtable_HoroEditor$Horo3dSceneView* pvt);
void HoroEditor$Horo3dSceneView_init_fields(HoroEditor$Horo3dSceneView *self);
void HoroEditor$Horo3dSceneView_init(HoroEditor$Horo3dSceneView *self, void *pOwner);
HoroEditor$Horo3dSceneView * HoroEditor$Horo3dSceneView_new(void *pOwner);
void HoroEditor$Horo3dSceneView_fini(HoroEditor$Horo3dSceneView *self);

void  HoroEditor$Horo3dSceneView$draw_self(HoroEditor$Horo3dSceneView *  self, SuiCore$Canvas *  canvas);
void  HoroEditor$Horo3dSceneView$onEvent(HoroEditor$Horo3dSceneView *  self, SuiCore$Event *  e);
void  HoroEditor$Horo3dSceneView$mkBaseScene(HoroEditor$Horo3dSceneView *  self);

HoroEditor$Horo3dSceneView*  HoroEditor$mkHoro3dSceneView(HoroEditor$Horo3dSceneView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
