
typedef struct tagSuiDesigner3d_w3e$W3eCorner SuiDesigner3d_w3e$W3eCorner;
typedef struct tagVtable_SuiDesigner3d_w3e$W3eCorner Vtable_SuiDesigner3d_w3e$W3eCorner;
typedef struct tagSuiDesigner3d_w3e$W3e SuiDesigner3d_w3e$W3e;
typedef struct tagVtable_SuiDesigner3d_w3e$W3e Vtable_SuiDesigner3d_w3e$W3e;


#ifndef define_struct___SuiDesigner3d_w3e__W3e_orc_h__
#define define_struct___SuiDesigner3d_w3e__W3e_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner3d_w3e__W3e_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner3d_w3e__W3e_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner3d_w3e__W3e_orc_h__
#define __SuiDesigner3d_w3e__W3e_orc_h__

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
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Mouse_orc.h"
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
#include "./InvalidReact_orc.h"
#include "./MenuBarCtrl_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/Vbo_orc.h"
#include "../Sgl/Tex2d_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner3d_w3e$W3eCorner {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner3d_w3e$W3eCorner _vtable_SuiDesigner3d_w3e$W3eCorner;

// class refc:1
struct tagSuiDesigner3d_w3e$W3eCorner {
	Object super; 
	float  groundHeight ;
	float  waterHeight ;
	bool  mapEdge ;
	bool  ramp ;
	bool  blight ;
	bool  water ;
	bool  boundary ;
	int  groundTexture ;
	int  cliffVariation ;
	int  groundVariation ;
	int  cliffTexture ;
	int  layerHeight ;
	float  actualGroundHeight ;
	void  (*calcActualGroundHeight) (SuiDesigner3d_w3e$W3eCorner *  self);
	void  (*load) (SuiDesigner3d_w3e$W3eCorner *  self, Sgl$BufferReader *  stream);
};
Vtable_SuiDesigner3d_w3e$W3eCorner* Vtable_SuiDesigner3d_w3e$W3eCorner_init(Vtable_SuiDesigner3d_w3e$W3eCorner* pvt);
void SuiDesigner3d_w3e$W3eCorner_init_fields(SuiDesigner3d_w3e$W3eCorner *self);
void SuiDesigner3d_w3e$W3eCorner_init(SuiDesigner3d_w3e$W3eCorner *self, void *pOwner);
SuiDesigner3d_w3e$W3eCorner * SuiDesigner3d_w3e$W3eCorner_new(void *pOwner);
void SuiDesigner3d_w3e$W3eCorner_fini(SuiDesigner3d_w3e$W3eCorner *self);

void  SuiDesigner3d_w3e$W3eCorner$calcActualGroundHeight(SuiDesigner3d_w3e$W3eCorner *  self);
void  SuiDesigner3d_w3e$W3eCorner$load(SuiDesigner3d_w3e$W3eCorner *  self, Sgl$BufferReader *  stream);


// 虚表
struct tagVtable_SuiDesigner3d_w3e$W3e {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner3d_w3e$W3e _vtable_SuiDesigner3d_w3e$W3e;

// class refc:0
struct tagSuiDesigner3d_w3e$W3e {
	Object super; 
	Orc$String*  head ;
	int  version ;
	char  tileset ;
	int  haveCustomTileset ;
	int  groundTilesetCount ;
	Orc$List*  groundTilesetNames ;
	int  cliffTilesetCount ;
	Orc$List*  cliffTilesetNames ;
	SuiCore$IntVec2 mapSize ;
	SuiCore$Vec2 centerOffset ;
	Orc$List*  corners ;
	Orc$List*  groundTexs ;
	Sgl$Geometry*  (*mkGeometry) (Sgl$Geometry **  __outRef__, SuiDesigner3d_w3e$W3e *  self);
	void  (*mkGroundTexs) (SuiDesigner3d_w3e$W3e *  self);
	void  (*setUniformTexs) (SuiDesigner3d_w3e$W3e *  self, Sgl$Material *  matl);
	void  (*load) (SuiDesigner3d_w3e$W3e *  self, const char *  path);
};
Vtable_SuiDesigner3d_w3e$W3e* Vtable_SuiDesigner3d_w3e$W3e_init(Vtable_SuiDesigner3d_w3e$W3e* pvt);
void SuiDesigner3d_w3e$W3e_init_fields(SuiDesigner3d_w3e$W3e *self);
void SuiDesigner3d_w3e$W3e_init(SuiDesigner3d_w3e$W3e *self, void *pOwner);
SuiDesigner3d_w3e$W3e * SuiDesigner3d_w3e$W3e_new(void *pOwner);
void SuiDesigner3d_w3e$W3e_fini(SuiDesigner3d_w3e$W3e *self);

Sgl$Geometry*  SuiDesigner3d_w3e$W3e$mkGeometry(Sgl$Geometry **  __outRef__, SuiDesigner3d_w3e$W3e *  self);
void  SuiDesigner3d_w3e$W3e$mkGroundTexs(SuiDesigner3d_w3e$W3e *  self);
void  SuiDesigner3d_w3e$W3e$setUniformTexs(SuiDesigner3d_w3e$W3e *  self, Sgl$Material *  matl);
void  SuiDesigner3d_w3e$W3e$load(SuiDesigner3d_w3e$W3e *  self, const char *  path);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
