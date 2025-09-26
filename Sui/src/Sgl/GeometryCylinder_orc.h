
typedef struct tagSgl$GeometryCylinder Sgl$GeometryCylinder;
typedef struct tagVtable_Sgl$GeometryCylinder Vtable_Sgl$GeometryCylinder;


#ifndef define_struct___Sgl__GeometryCylinder_orc_h__
#define define_struct___Sgl__GeometryCylinder_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryCylinder_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryCylinder_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryCylinder_orc_h__
#define __Sgl__GeometryCylinder_orc_h__

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
struct tagVtable_Sgl$GeometryCylinder {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryCylinder _vtable_Sgl$GeometryCylinder;

// class refc:0
struct tagSgl$GeometryCylinder {
	Sgl$Geometry super; 
	float  radiusTop ;
	float  radiusBottom ;
	float  height ;
	int  radialSegments ;
	int  heightSegments ;
	bool  openEnded ;
	float  thetaStart ;
	float  thetaLength ;
	Sgl$Buffer*  positions ;
	Sgl$Buffer*  normals ;
	Sgl$Buffer*  face ;
	Sgl$Buffer*  uvs ;
	void  (*build) (Sgl$GeometryCylinder *  self);
	void  (*generateTorso) (Sgl$GeometryCylinder *  self, int *  index);
	void  (*generateCap) (Sgl$GeometryCylinder *  self, bool  top, int *  index);
};
Vtable_Sgl$GeometryCylinder* Vtable_Sgl$GeometryCylinder_init(Vtable_Sgl$GeometryCylinder* pvt);
void Sgl$GeometryCylinder_init_fields(Sgl$GeometryCylinder *self);
void Sgl$GeometryCylinder_init(Sgl$GeometryCylinder *self, void *pOwner);
Sgl$GeometryCylinder * Sgl$GeometryCylinder_new(void *pOwner);
void Sgl$GeometryCylinder_fini(Sgl$GeometryCylinder *self);

void  Sgl$GeometryCylinder$build(Sgl$GeometryCylinder *  self);
void  Sgl$GeometryCylinder$generateTorso(Sgl$GeometryCylinder *  self, int *  index);
void  Sgl$GeometryCylinder$generateCap(Sgl$GeometryCylinder *  self, bool  top, int *  index);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
