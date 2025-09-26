
typedef struct tagSgl$GeometryCircle Sgl$GeometryCircle;
typedef struct tagVtable_Sgl$GeometryCircle Vtable_Sgl$GeometryCircle;


#ifndef define_struct___Sgl__GeometryCircle_orc_h__
#define define_struct___Sgl__GeometryCircle_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryCircle_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryCircle_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryCircle_orc_h__
#define __Sgl__GeometryCircle_orc_h__

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
struct tagVtable_Sgl$GeometryCircle {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryCircle _vtable_Sgl$GeometryCircle;

// class refc:0
struct tagSgl$GeometryCircle {
	Sgl$Geometry super; 
	float  radius ;
	int  segments ;
	float  thetaStart ;
	float  thetaLength ;
	void  (*build) (Sgl$GeometryCircle *  self);
};
Vtable_Sgl$GeometryCircle* Vtable_Sgl$GeometryCircle_init(Vtable_Sgl$GeometryCircle* pvt);
void Sgl$GeometryCircle_init_fields(Sgl$GeometryCircle *self);
void Sgl$GeometryCircle_init(Sgl$GeometryCircle *self, void *pOwner);
Sgl$GeometryCircle * Sgl$GeometryCircle_new(void *pOwner);
void Sgl$GeometryCircle_fini(Sgl$GeometryCircle *self);

void  Sgl$GeometryCircle$build(Sgl$GeometryCircle *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
