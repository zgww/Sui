
typedef struct tagSgl$GeometryRing Sgl$GeometryRing;
typedef struct tagVtable_Sgl$GeometryRing Vtable_Sgl$GeometryRing;


#ifndef define_struct___Sgl__GeometryRing_orc_h__
#define define_struct___Sgl__GeometryRing_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryRing_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryRing_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryRing_orc_h__
#define __Sgl__GeometryRing_orc_h__

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
struct tagVtable_Sgl$GeometryRing {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryRing _vtable_Sgl$GeometryRing;

// class refc:0
struct tagSgl$GeometryRing {
	Sgl$Geometry super; 
	float  innerRadius ;
	float  outerRadius ;
	int  thetaSegments ;
	int  phiSegments ;
	float  thetaStart ;
	float  thetaLength ;
	void  (*build) (Sgl$GeometryRing *  self);
};
Vtable_Sgl$GeometryRing* Vtable_Sgl$GeometryRing_init(Vtable_Sgl$GeometryRing* pvt);
void Sgl$GeometryRing_init_fields(Sgl$GeometryRing *self);
void Sgl$GeometryRing_init(Sgl$GeometryRing *self, void *pOwner);
Sgl$GeometryRing * Sgl$GeometryRing_new(void *pOwner);
void Sgl$GeometryRing_fini(Sgl$GeometryRing *self);

void  Sgl$GeometryRing$build(Sgl$GeometryRing *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
