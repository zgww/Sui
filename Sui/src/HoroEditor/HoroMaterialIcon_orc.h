
typedef struct tagHoroEditor$HoroMaterialIconCreator HoroEditor$HoroMaterialIconCreator;
typedef struct tagVtable_HoroEditor$HoroMaterialIconCreator Vtable_HoroEditor$HoroMaterialIconCreator;
typedef struct tagHoroEditor$HoroMaterialIconMgr HoroEditor$HoroMaterialIconMgr;
typedef struct tagVtable_HoroEditor$HoroMaterialIconMgr Vtable_HoroEditor$HoroMaterialIconMgr;


#ifndef define_struct___HoroEditor__HoroMaterialIcon_orc_h__
#define define_struct___HoroEditor__HoroMaterialIcon_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__HoroMaterialIcon_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__HoroMaterialIcon_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__HoroMaterialIcon_orc_h__
#define __HoroEditor__HoroMaterialIcon_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/PixelsReader_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$HoroMaterialIconCreator {
	Vtable_Object super;
};
//虚表实例
extern Vtable_HoroEditor$HoroMaterialIconCreator _vtable_HoroEditor$HoroMaterialIconCreator;

// class refc:0
struct tagHoroEditor$HoroMaterialIconCreator {
	Object super; 
	Sgl$Fbo*  fbo ;
	SuiCore$Vec2 size ;
	Sgl$DrawCtx*  drawCtx ;
	Sgl$Scene*  scene ;
	Sgl$PerspectiveCamera*  camera ;
	Orc$String*  materialPath ;
	void  (*create) (HoroEditor$HoroMaterialIconCreator *  self, const char *  materialPath);
	void  (*saveAsPng) (HoroEditor$HoroMaterialIconCreator *  self, const char *  path);
	void  (*draw) (HoroEditor$HoroMaterialIconCreator *  self);
	void  (*mkScene) (HoroEditor$HoroMaterialIconCreator *  self);
};
Vtable_HoroEditor$HoroMaterialIconCreator* Vtable_HoroEditor$HoroMaterialIconCreator_init(Vtable_HoroEditor$HoroMaterialIconCreator* pvt);
void HoroEditor$HoroMaterialIconCreator_init_fields(HoroEditor$HoroMaterialIconCreator *self);
void HoroEditor$HoroMaterialIconCreator_init(HoroEditor$HoroMaterialIconCreator *self, void *pOwner);
HoroEditor$HoroMaterialIconCreator * HoroEditor$HoroMaterialIconCreator_new(void *pOwner);
void HoroEditor$HoroMaterialIconCreator_fini(HoroEditor$HoroMaterialIconCreator *self);

void  HoroEditor$HoroMaterialIconCreator$create(HoroEditor$HoroMaterialIconCreator *  self, const char *  materialPath);
void  HoroEditor$HoroMaterialIconCreator$saveAsPng(HoroEditor$HoroMaterialIconCreator *  self, const char *  path);
void  HoroEditor$HoroMaterialIconCreator$draw(HoroEditor$HoroMaterialIconCreator *  self);
void  HoroEditor$HoroMaterialIconCreator$mkScene(HoroEditor$HoroMaterialIconCreator *  self);


// 虚表
struct tagVtable_HoroEditor$HoroMaterialIconMgr {
	Vtable_Object super;
};
//虚表实例
extern Vtable_HoroEditor$HoroMaterialIconMgr _vtable_HoroEditor$HoroMaterialIconMgr;

// class refc:1
struct tagHoroEditor$HoroMaterialIconMgr {
	Object super; 
	
};
Vtable_HoroEditor$HoroMaterialIconMgr* Vtable_HoroEditor$HoroMaterialIconMgr_init(Vtable_HoroEditor$HoroMaterialIconMgr* pvt);
void HoroEditor$HoroMaterialIconMgr_init_fields(HoroEditor$HoroMaterialIconMgr *self);
void HoroEditor$HoroMaterialIconMgr_init(HoroEditor$HoroMaterialIconMgr *self, void *pOwner);
HoroEditor$HoroMaterialIconMgr * HoroEditor$HoroMaterialIconMgr_new(void *pOwner);
void HoroEditor$HoroMaterialIconMgr_fini(HoroEditor$HoroMaterialIconMgr *self);


void  HoroEditor$testHoroMaterialIconCreator();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
