
typedef struct tagSgl$GeoAttr Sgl$GeoAttr;
typedef struct tagVtable_Sgl$GeoAttr Vtable_Sgl$GeoAttr;
typedef struct tagSgl$Geometry Sgl$Geometry;
typedef struct tagVtable_Sgl$Geometry Vtable_Sgl$Geometry;


#ifndef define_struct___Sgl__Geometry_orc_h__
#define define_struct___Sgl__Geometry_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Geometry_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdlib.h>
#include <stdio.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__Geometry_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Geometry_orc_h__
#define __Sgl__Geometry_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Orc/String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$GeoAttr {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$GeoAttr _vtable_Sgl$GeoAttr;

// class refc:0
struct tagSgl$GeoAttr {
	Object super; 
	Orc$String*  key ;
	Sgl$Vbo*  vbo ;
	bool  (*bindVertexAttrib) (Sgl$GeoAttr *  self, Sgl$Material *  matl);
};
Vtable_Sgl$GeoAttr* Vtable_Sgl$GeoAttr_init(Vtable_Sgl$GeoAttr* pvt);
void Sgl$GeoAttr_init_fields(Sgl$GeoAttr *self);
void Sgl$GeoAttr_init(Sgl$GeoAttr *self, void *pOwner);
Sgl$GeoAttr * Sgl$GeoAttr_new(void *pOwner);
void Sgl$GeoAttr_fini(Sgl$GeoAttr *self);

extern bool  Sgl$GeoAttr$bindVertexAttrib(Sgl$GeoAttr *  self, Sgl$Material *  matl);


// 虚表
struct tagVtable_Sgl$Geometry {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Geometry _vtable_Sgl$Geometry;

// class refc:0
struct tagSgl$Geometry {
	Object super; 
	Orc$Map*  attrs ;
	Sgl$Vbo*  ibo ;
	Sgl$Vbo*  instanceVbo ;
	int  version ;
	void  (*setIboByBuffer) (Sgl$Geometry *  self, Sgl$Buffer *  buffer);
	void  (*setAttrByBuffer) (Sgl$Geometry *  self, const char *  name, Sgl$Buffer *  buffer, int  elementCountPerVertex);
	void  (*setIboByInts) (Sgl$Geometry *  self, int *  data, int  cnt);
	void  (*setIboByShorts) (Sgl$Geometry *  self, short *  data, int  cnt);
	void  (*applyAttrByBuffer) (Sgl$Geometry *  self, const char *  name, Sgl$Buffer *  buffer, int  elementCountPerVertex);
	void  (*setAttrByFloats) (Sgl$Geometry *  self, const char *  name, float *  data, int  floatCount, int  elementCountPerVertex);
	void  (*setInstanceAttrByBuffer) (Sgl$Geometry *  self, const char *  name, Sgl$Buffer *  buffer, int  elementCount);
	Sgl$GeoAttr *  (*getAttr) (Sgl$Geometry *  self, const char *  key);
	Sgl$GeoAttr *  (*setAttr) (Sgl$Geometry *  self, const char *  key, Sgl$Vbo*  vbo);
	Sgl$GeoAttr *  (*gocInstanceAttr) (Sgl$Geometry *  self, const char *  key);
	Sgl$GeoAttr *  (*gocAttr) (Sgl$Geometry *  self, const char *  key);
	bool  (*bindVertexAttribs) (Sgl$Geometry *  self, Sgl$Material *  matl);
};
Vtable_Sgl$Geometry* Vtable_Sgl$Geometry_init(Vtable_Sgl$Geometry* pvt);
void Sgl$Geometry_init_fields(Sgl$Geometry *self);
void Sgl$Geometry_init(Sgl$Geometry *self, void *pOwner);
Sgl$Geometry * Sgl$Geometry_new(void *pOwner);
void Sgl$Geometry_fini(Sgl$Geometry *self);

void  Sgl$Geometry$setIboByBuffer(Sgl$Geometry *  self, Sgl$Buffer *  buffer);
void  Sgl$Geometry$setAttrByBuffer(Sgl$Geometry *  self, const char *  name, Sgl$Buffer *  buffer, int  elementCountPerVertex);
void  Sgl$Geometry$setIboByInts(Sgl$Geometry *  self, int *  data, int  cnt);
void  Sgl$Geometry$setIboByShorts(Sgl$Geometry *  self, short *  data, int  cnt);
void  Sgl$Geometry$applyAttrByBuffer(Sgl$Geometry *  self, const char *  name, Sgl$Buffer *  buffer, int  elementCountPerVertex);
void  Sgl$Geometry$setAttrByFloats(Sgl$Geometry *  self, const char *  name, float *  data, int  floatCount, int  elementCountPerVertex);
void  Sgl$Geometry$setInstanceAttrByBuffer(Sgl$Geometry *  self, const char *  name, Sgl$Buffer *  buffer, int  elementCount);
Sgl$GeoAttr *  Sgl$Geometry$getAttr(Sgl$Geometry *  self, const char *  key);
Sgl$GeoAttr *  Sgl$Geometry$setAttr(Sgl$Geometry *  self, const char *  key, Sgl$Vbo*  vbo);
Sgl$GeoAttr *  Sgl$Geometry$gocInstanceAttr(Sgl$Geometry *  self, const char *  key);
Sgl$GeoAttr *  Sgl$Geometry$gocAttr(Sgl$Geometry *  self, const char *  key);
bool  Sgl$Geometry$bindVertexAttribs(Sgl$Geometry *  self, Sgl$Material *  matl);

Sgl$Buffer*  Sgl$Geometry_computeVertexNormals(Sgl$Buffer **  __outRef__, Sgl$Buffer *  face, Sgl$Buffer *  position);
void  Sgl$Geometry_normalNormals(Sgl$Buffer *  buffer);
void  Sgl$testGeometry();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
