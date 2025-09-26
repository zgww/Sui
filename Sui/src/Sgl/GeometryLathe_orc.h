
typedef struct tagSgl$GeometryLathe Sgl$GeometryLathe;
typedef struct tagVtable_Sgl$GeometryLathe Vtable_Sgl$GeometryLathe;


#ifndef define_struct___Sgl__GeometryLathe_orc_h__
#define define_struct___Sgl__GeometryLathe_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryLathe_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryLathe_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryLathe_orc_h__
#define __Sgl__GeometryLathe_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$GeometryLathe {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryLathe _vtable_Sgl$GeometryLathe;

// class refc:0
struct tagSgl$GeometryLathe {
	Sgl$Geometry super; 
	int  segments ;
	float  phiStart ;
	float  phiLength ;
	Sgl$Vec3Array*  points ;
	void  (*build) (Sgl$GeometryLathe *  self);
};
Vtable_Sgl$GeometryLathe* Vtable_Sgl$GeometryLathe_init(Vtable_Sgl$GeometryLathe* pvt);
void Sgl$GeometryLathe_init_fields(Sgl$GeometryLathe *self);
void Sgl$GeometryLathe_init(Sgl$GeometryLathe *self, void *pOwner);
Sgl$GeometryLathe * Sgl$GeometryLathe_new(void *pOwner);
void Sgl$GeometryLathe_fini(Sgl$GeometryLathe *self);

void  Sgl$GeometryLathe$build(Sgl$GeometryLathe *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
