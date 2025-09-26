
typedef struct tagSgl$GeometryCapsule Sgl$GeometryCapsule;
typedef struct tagVtable_Sgl$GeometryCapsule Vtable_Sgl$GeometryCapsule;


#ifndef define_struct___Sgl__GeometryCapsule_orc_h__
#define define_struct___Sgl__GeometryCapsule_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryCapsule_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryCapsule_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryCapsule_orc_h__
#define __Sgl__GeometryCapsule_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "./Geometry_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$GeometryCapsule {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryCapsule _vtable_Sgl$GeometryCapsule;

// class refc:0
struct tagSgl$GeometryCapsule {
	Sgl$Geometry super; 
	float  radius ;
	int  segments ;
	float  thetaStart ;
	float  thetaLength ;
	void  (*build) (Sgl$GeometryCapsule *  self);
};
Vtable_Sgl$GeometryCapsule* Vtable_Sgl$GeometryCapsule_init(Vtable_Sgl$GeometryCapsule* pvt);
void Sgl$GeometryCapsule_init_fields(Sgl$GeometryCapsule *self);
void Sgl$GeometryCapsule_init(Sgl$GeometryCapsule *self, void *pOwner);
Sgl$GeometryCapsule * Sgl$GeometryCapsule_new(void *pOwner);
void Sgl$GeometryCapsule_fini(Sgl$GeometryCapsule *self);

void  Sgl$GeometryCapsule$build(Sgl$GeometryCapsule *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
