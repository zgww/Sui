
typedef struct tagSgl$ModelLoader Sgl$ModelLoader;
typedef struct tagVtable_Sgl$ModelLoader Vtable_Sgl$ModelLoader;


#ifndef define_struct___Sgl__ModelLoader_orc_h__
#define define_struct___Sgl__ModelLoader_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__ModelLoader_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__ModelLoader_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__ModelLoader_orc_h__
#define __Sgl__ModelLoader_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "./Obj3d_orc.h"
#include "./Mesh_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Geometry_orc.h"
#include "./Material_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$ModelLoader {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$ModelLoader _vtable_Sgl$ModelLoader;

// class refc:0
struct tagSgl$ModelLoader {
	Sgl$Obj3d super; 
	Sgl$Buffer*  vertices ;
	Sgl$Buffer*  normals ;
	Sgl$Buffer*  texCoords ;
	Sgl$Buffer*  faces ;
	Orc$String*  path ;
	Sgl$Mesh*  mesh ;
	void  (*setPath) (Sgl$ModelLoader *  self, Orc$String*  path);
	void  (*_load) (Sgl$ModelLoader *  self);
	Sgl$Geometry*  (*buildGeometry) (Sgl$Geometry **  __outRef__, Sgl$ModelLoader *  self);
};
Vtable_Sgl$ModelLoader* Vtable_Sgl$ModelLoader_init(Vtable_Sgl$ModelLoader* pvt);
void Sgl$ModelLoader_init_fields(Sgl$ModelLoader *self);
void Sgl$ModelLoader_init(Sgl$ModelLoader *self, void *pOwner);
Sgl$ModelLoader * Sgl$ModelLoader_new(void *pOwner);
void Sgl$ModelLoader_fini(Sgl$ModelLoader *self);

void  Sgl$ModelLoader$setPath(Sgl$ModelLoader *  self, Orc$String*  path);
extern void  Sgl$ModelLoader$_load(Sgl$ModelLoader *  self);
Sgl$Geometry*  Sgl$ModelLoader$buildGeometry(Sgl$Geometry **  __outRef__, Sgl$ModelLoader *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
