
typedef struct tagSgl$Draw Sgl$Draw;
typedef struct tagVtable_Sgl$Draw Vtable_Sgl$Draw;
typedef struct tagSgl$ObjLoader Sgl$ObjLoader;
typedef struct tagVtable_Sgl$ObjLoader Vtable_Sgl$ObjLoader;


#ifndef define_struct___Sgl__Draw_orc_h__
#define define_struct___Sgl__Draw_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Draw_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__Draw_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Draw_orc_h__
#define __Sgl__Draw_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./Vao_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Map_orc.h"
#include "../Json/Json_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Draw {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Draw _vtable_Sgl$Draw;

// class refc:0
struct tagSgl$Draw {
	Object super; 
	Sgl$Material*  material ;
	Sgl$Geometry*  geometry ;
	Sgl$Vao*  vao ;
	bool  (*needBuildVao) (Sgl$Draw *  self);
	bool  (*buildVaoIfNeed) (Sgl$Draw *  self);
	bool  (*buildVao) (Sgl$Draw *  self);
	void  (*use) (Sgl$Draw *  self);
	void  (*draw) (Sgl$Draw *  self);
	void  (*buildGeometryByJsonPathCstr) (Sgl$Draw *  self, const char *  path);
};
Vtable_Sgl$Draw* Vtable_Sgl$Draw_init(Vtable_Sgl$Draw* pvt);
void Sgl$Draw_init_fields(Sgl$Draw *self);
void Sgl$Draw_init(Sgl$Draw *self, void *pOwner);
Sgl$Draw * Sgl$Draw_new(void *pOwner);
void Sgl$Draw_fini(Sgl$Draw *self);

bool  Sgl$Draw$needBuildVao(Sgl$Draw *  self);
bool  Sgl$Draw$buildVaoIfNeed(Sgl$Draw *  self);
bool  Sgl$Draw$buildVao(Sgl$Draw *  self);
void  Sgl$Draw$use(Sgl$Draw *  self);
extern void  Sgl$Draw$draw(Sgl$Draw *  self);
void  Sgl$Draw$buildGeometryByJsonPathCstr(Sgl$Draw *  self, const char *  path);


// 虚表
struct tagVtable_Sgl$ObjLoader {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$ObjLoader _vtable_Sgl$ObjLoader;

// class refc:0
struct tagSgl$ObjLoader {
	Object super; 
	Sgl$Buffer*  vertices ;
	Sgl$Buffer*  normals ;
	Sgl$Buffer*  texCoords ;
	Sgl$Buffer*  faces ;
	Orc$String*  path ;
	void  (*load) (Sgl$ObjLoader *  self, const char *  path);
	void  (*_load) (Sgl$ObjLoader *  self);
	Sgl$Geometry*  (*buildGeometry) (Sgl$Geometry **  __outRef__, Sgl$ObjLoader *  self);
};
Vtable_Sgl$ObjLoader* Vtable_Sgl$ObjLoader_init(Vtable_Sgl$ObjLoader* pvt);
void Sgl$ObjLoader_init_fields(Sgl$ObjLoader *self);
void Sgl$ObjLoader_init(Sgl$ObjLoader *self, void *pOwner);
Sgl$ObjLoader * Sgl$ObjLoader_new(void *pOwner);
void Sgl$ObjLoader_fini(Sgl$ObjLoader *self);

void  Sgl$ObjLoader$load(Sgl$ObjLoader *  self, const char *  path);
extern void  Sgl$ObjLoader$_load(Sgl$ObjLoader *  self);
Sgl$Geometry*  Sgl$ObjLoader$buildGeometry(Sgl$Geometry **  __outRef__, Sgl$ObjLoader *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
