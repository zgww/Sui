
typedef struct tagSgl$ImgInfo Sgl$ImgInfo;
typedef struct tagSgl$GeometryHeightMap Sgl$GeometryHeightMap;
typedef struct tagVtable_Sgl$GeometryHeightMap Vtable_Sgl$GeometryHeightMap;


#ifndef define_struct___Sgl__GeometryHeightMap_orc_h__
#define define_struct___Sgl__GeometryHeightMap_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryHeightMap_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../nanovg/stb_image.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryHeightMap_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$ImgInfo {
	int  width ;
	int  height ;
	int  channel ;
	unsigned char *  data ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryHeightMap_orc_h__
#define __Sgl__GeometryHeightMap_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Json/Json_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Sgl$ImgInfo_getOrInitMetaStruct();


// 虚表
struct tagVtable_Sgl$GeometryHeightMap {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryHeightMap _vtable_Sgl$GeometryHeightMap;

// class refc:0
struct tagSgl$GeometryHeightMap {
	Sgl$Geometry super; 
	float  incx ;
	float  incz ;
	float  texInc ;
	float  heightScale ;
	float  startX ;
	float  startY ;
	float  startZ ;
	Orc$String*  path ;
	void  (*toJson) (Sgl$GeometryHeightMap *  self, Json$Json *  jo);
	void  (*fromJson) (Sgl$GeometryHeightMap *  self, Json$Json *  jo);
	float  (*getHeight) (Sgl$GeometryHeightMap *  self, Sgl$ImgInfo *  info, int  row, int  col);
	void  (*buildByPath) (Sgl$GeometryHeightMap *  self, const char *  path);
	Sgl$Buffer*  (*calcNormals) (Sgl$Buffer **  __outRef__, Sgl$GeometryHeightMap *  self, Sgl$Buffer *  vtxs, int  width, int  height);
};
Vtable_Sgl$GeometryHeightMap* Vtable_Sgl$GeometryHeightMap_init(Vtable_Sgl$GeometryHeightMap* pvt);
void Sgl$GeometryHeightMap_init_fields(Sgl$GeometryHeightMap *self);
void Sgl$GeometryHeightMap_init(Sgl$GeometryHeightMap *self, void *pOwner);
Sgl$GeometryHeightMap * Sgl$GeometryHeightMap_new(void *pOwner);
void Sgl$GeometryHeightMap_fini(Sgl$GeometryHeightMap *self);

void  Sgl$GeometryHeightMap$dtor(Sgl$GeometryHeightMap *  self);
void  Sgl$GeometryHeightMap$toJson(Sgl$GeometryHeightMap *  self, Json$Json *  jo);
void  Sgl$GeometryHeightMap$fromJson(Sgl$GeometryHeightMap *  self, Json$Json *  jo);
float  Sgl$GeometryHeightMap$getHeight(Sgl$GeometryHeightMap *  self, Sgl$ImgInfo *  info, int  row, int  col);
void  Sgl$GeometryHeightMap$build(Sgl$GeometryHeightMap *  self);
void  Sgl$GeometryHeightMap$buildByPath(Sgl$GeometryHeightMap *  self, const char *  path);
Sgl$Buffer*  Sgl$GeometryHeightMap$calcNormals(Sgl$Buffer **  __outRef__, Sgl$GeometryHeightMap *  self, Sgl$Buffer *  vtxs, int  width, int  height);

void  Sgl$testHeightMap();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
