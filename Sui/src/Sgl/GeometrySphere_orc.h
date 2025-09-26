
typedef struct tagSgl$GeometrySphere Sgl$GeometrySphere;
typedef struct tagVtable_Sgl$GeometrySphere Vtable_Sgl$GeometrySphere;


#ifndef define_struct___Sgl__GeometrySphere_orc_h__
#define define_struct___Sgl__GeometrySphere_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometrySphere_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometrySphere_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometrySphere_orc_h__
#define __Sgl__GeometrySphere_orc_h__

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
struct tagVtable_Sgl$GeometrySphere {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometrySphere _vtable_Sgl$GeometrySphere;

// class refc:0
struct tagSgl$GeometrySphere {
	Sgl$Geometry super; 
	float  radius ;
	int  widthSegments ;
	int  heightSegments ;
	float  phiStart ;
	float  phiLength ;
	float  thetaStart ;
	float  thetaLength ;
	void  (*build) (Sgl$GeometrySphere *  self);
};
Vtable_Sgl$GeometrySphere* Vtable_Sgl$GeometrySphere_init(Vtable_Sgl$GeometrySphere* pvt);
void Sgl$GeometrySphere_init_fields(Sgl$GeometrySphere *self);
void Sgl$GeometrySphere_init(Sgl$GeometrySphere *self, void *pOwner);
Sgl$GeometrySphere * Sgl$GeometrySphere_new(void *pOwner);
void Sgl$GeometrySphere_fini(Sgl$GeometrySphere *self);

void  Sgl$GeometrySphere$build(Sgl$GeometrySphere *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
