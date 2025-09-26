
typedef struct tagSgl$GeometryRect Sgl$GeometryRect;
typedef struct tagVtable_Sgl$GeometryRect Vtable_Sgl$GeometryRect;


#ifndef define_struct___Sgl__GeometryRect_orc_h__
#define define_struct___Sgl__GeometryRect_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryRect_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryRect_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryRect_orc_h__
#define __Sgl__GeometryRect_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$GeometryRect {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryRect _vtable_Sgl$GeometryRect;

// class refc:0
struct tagSgl$GeometryRect {
	Sgl$Geometry super; 
	float  width ;
	float  height ;
	void  (*build) (Sgl$GeometryRect *  self);
};
Vtable_Sgl$GeometryRect* Vtable_Sgl$GeometryRect_init(Vtable_Sgl$GeometryRect* pvt);
void Sgl$GeometryRect_init_fields(Sgl$GeometryRect *self);
void Sgl$GeometryRect_init(Sgl$GeometryRect *self, void *pOwner);
Sgl$GeometryRect * Sgl$GeometryRect_new(void *pOwner);
void Sgl$GeometryRect_fini(Sgl$GeometryRect *self);

void  Sgl$GeometryRect$build(Sgl$GeometryRect *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
