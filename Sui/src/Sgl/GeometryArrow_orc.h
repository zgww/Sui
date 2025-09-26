
typedef struct tagSgl$GeometryArrow Sgl$GeometryArrow;
typedef struct tagVtable_Sgl$GeometryArrow Vtable_Sgl$GeometryArrow;


#ifndef define_struct___Sgl__GeometryArrow_orc_h__
#define define_struct___Sgl__GeometryArrow_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryArrow_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryArrow_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryArrow_orc_h__
#define __Sgl__GeometryArrow_orc_h__

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
struct tagVtable_Sgl$GeometryArrow {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryArrow _vtable_Sgl$GeometryArrow;

// class refc:0
struct tagSgl$GeometryArrow {
	Sgl$Geometry super; 
	float  cylinderRadius ;
	float  coneRadius ;
	float  cylinderHeight ;
	float  coneHeight ;
	int  radialSegments ;
	float  thetaStart ;
	float  thetaLength ;
	Sgl$Buffer*  vtxBuf ;
	Sgl$Buffer*  nmlBuf ;
	Sgl$Buffer*  face ;
	void  (*build) (Sgl$GeometryArrow *  self);
	void  (*buildTorso) (Sgl$GeometryArrow *  self);
	void  (*buildCone) (Sgl$GeometryArrow *  self);
};
Vtable_Sgl$GeometryArrow* Vtable_Sgl$GeometryArrow_init(Vtable_Sgl$GeometryArrow* pvt);
void Sgl$GeometryArrow_init_fields(Sgl$GeometryArrow *self);
void Sgl$GeometryArrow_init(Sgl$GeometryArrow *self, void *pOwner);
Sgl$GeometryArrow * Sgl$GeometryArrow_new(void *pOwner);
void Sgl$GeometryArrow_fini(Sgl$GeometryArrow *self);

void  Sgl$GeometryArrow$build(Sgl$GeometryArrow *  self);
void  Sgl$GeometryArrow$buildTorso(Sgl$GeometryArrow *  self);
void  Sgl$GeometryArrow$buildCone(Sgl$GeometryArrow *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
