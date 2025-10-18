
typedef struct tagHoroEditor$HoroMaterialIconCreator HoroEditor$HoroMaterialIconCreator;
typedef struct tagVtable_HoroEditor$HoroMaterialIconCreator Vtable_HoroEditor$HoroMaterialIconCreator;
typedef struct tagHoroEditor$HoroModelIconCreator HoroEditor$HoroModelIconCreator;
typedef struct tagVtable_HoroEditor$HoroModelIconCreator Vtable_HoroEditor$HoroModelIconCreator;
typedef struct tagHoroEditor$HoroIconMgr HoroEditor$HoroIconMgr;
typedef struct tagVtable_HoroEditor$HoroIconMgr Vtable_HoroEditor$HoroIconMgr;


#ifndef define_struct___HoroEditor__HoroIconMgr_orc_h__
#define define_struct___HoroEditor__HoroIconMgr_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__HoroIconMgr_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__HoroIconMgr_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__HoroIconMgr_orc_h__
#define __HoroEditor__HoroIconMgr_orc_h__

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
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/PixelsReader_orc.h"
#include "../Sgl/ModelLoader_orc.h"


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
	void  (*showTextureWindow) (HoroEditor$HoroMaterialIconCreator *  self);
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
void  HoroEditor$HoroMaterialIconCreator$showTextureWindow(HoroEditor$HoroMaterialIconCreator *  self);
void  HoroEditor$HoroMaterialIconCreator$saveAsPng(HoroEditor$HoroMaterialIconCreator *  self, const char *  path);
void  HoroEditor$HoroMaterialIconCreator$draw(HoroEditor$HoroMaterialIconCreator *  self);
void  HoroEditor$HoroMaterialIconCreator$mkScene(HoroEditor$HoroMaterialIconCreator *  self);


// 虚表
struct tagVtable_HoroEditor$HoroModelIconCreator {
	Vtable_Object super;
};
//虚表实例
extern Vtable_HoroEditor$HoroModelIconCreator _vtable_HoroEditor$HoroModelIconCreator;

// class refc:0
struct tagHoroEditor$HoroModelIconCreator {
	Object super; 
	Sgl$Fbo*  fbo ;
	SuiCore$Vec2 size ;
	Sgl$DrawCtx*  drawCtx ;
	Sgl$Scene*  scene ;
	Sgl$PerspectiveCamera*  camera ;
	Orc$String*  modelPath ;
	void  (*create) (HoroEditor$HoroModelIconCreator *  self, const char *  modelPath);
	void  (*showTextureWindow) (HoroEditor$HoroModelIconCreator *  self);
	void  (*saveAsPng) (HoroEditor$HoroModelIconCreator *  self, const char *  path);
	void  (*draw) (HoroEditor$HoroModelIconCreator *  self);
	void  (*mkScene) (HoroEditor$HoroModelIconCreator *  self);
};
Vtable_HoroEditor$HoroModelIconCreator* Vtable_HoroEditor$HoroModelIconCreator_init(Vtable_HoroEditor$HoroModelIconCreator* pvt);
void HoroEditor$HoroModelIconCreator_init_fields(HoroEditor$HoroModelIconCreator *self);
void HoroEditor$HoroModelIconCreator_init(HoroEditor$HoroModelIconCreator *self, void *pOwner);
HoroEditor$HoroModelIconCreator * HoroEditor$HoroModelIconCreator_new(void *pOwner);
void HoroEditor$HoroModelIconCreator_fini(HoroEditor$HoroModelIconCreator *self);

void  HoroEditor$HoroModelIconCreator$create(HoroEditor$HoroModelIconCreator *  self, const char *  modelPath);
void  HoroEditor$HoroModelIconCreator$showTextureWindow(HoroEditor$HoroModelIconCreator *  self);
void  HoroEditor$HoroModelIconCreator$saveAsPng(HoroEditor$HoroModelIconCreator *  self, const char *  path);
void  HoroEditor$HoroModelIconCreator$draw(HoroEditor$HoroModelIconCreator *  self);
void  HoroEditor$HoroModelIconCreator$mkScene(HoroEditor$HoroModelIconCreator *  self);


// 虚表
struct tagVtable_HoroEditor$HoroIconMgr {
	Vtable_Object super;
};
//虚表实例
extern Vtable_HoroEditor$HoroIconMgr _vtable_HoroEditor$HoroIconMgr;

// class refc:1
struct tagHoroEditor$HoroIconMgr {
	Object super; 
	SuiCore$Image *  (*request) (HoroEditor$HoroIconMgr *  self, const char *  path);
};
Vtable_HoroEditor$HoroIconMgr* Vtable_HoroEditor$HoroIconMgr_init(Vtable_HoroEditor$HoroIconMgr* pvt);
void HoroEditor$HoroIconMgr_init_fields(HoroEditor$HoroIconMgr *self);
void HoroEditor$HoroIconMgr_init(HoroEditor$HoroIconMgr *self, void *pOwner);
HoroEditor$HoroIconMgr * HoroEditor$HoroIconMgr_new(void *pOwner);
void HoroEditor$HoroIconMgr_fini(HoroEditor$HoroIconMgr *self);

SuiCore$Image *  HoroEditor$HoroIconMgr$request(HoroEditor$HoroIconMgr *  self, const char *  path);

void  HoroEditor$testHoroMaterialIconCreator();
void  HoroEditor$testHoroModelIconCreator();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
