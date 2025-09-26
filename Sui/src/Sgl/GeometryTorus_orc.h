
typedef struct tagSgl$GeometryTorus Sgl$GeometryTorus;
typedef struct tagVtable_Sgl$GeometryTorus Vtable_Sgl$GeometryTorus;


#ifndef define_struct___Sgl__GeometryTorus_orc_h__
#define define_struct___Sgl__GeometryTorus_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryTorus_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryTorus_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryTorus_orc_h__
#define __Sgl__GeometryTorus_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$GeometryTorus {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryTorus _vtable_Sgl$GeometryTorus;

// class refc:0
struct tagSgl$GeometryTorus {
	Sgl$Geometry super; 
	float  radius ;
	float  tube ;
	float  radialSegments ;
	float  tubularSegments ;
	float  arc ;
	void  (*build) (Sgl$GeometryTorus *  self);
};
Vtable_Sgl$GeometryTorus* Vtable_Sgl$GeometryTorus_init(Vtable_Sgl$GeometryTorus* pvt);
void Sgl$GeometryTorus_init_fields(Sgl$GeometryTorus *self);
void Sgl$GeometryTorus_init(Sgl$GeometryTorus *self, void *pOwner);
Sgl$GeometryTorus * Sgl$GeometryTorus_new(void *pOwner);
void Sgl$GeometryTorus_fini(Sgl$GeometryTorus *self);

void  Sgl$GeometryTorus$build(Sgl$GeometryTorus *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
