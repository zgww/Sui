
typedef struct tagSgl$GeometryCone Sgl$GeometryCone;
typedef struct tagVtable_Sgl$GeometryCone Vtable_Sgl$GeometryCone;


#ifndef define_struct___Sgl__GeometryCone_orc_h__
#define define_struct___Sgl__GeometryCone_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryCone_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryCone_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryCone_orc_h__
#define __Sgl__GeometryCone_orc_h__

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
#include "./GeometryCylinder_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$GeometryCone {
	Vtable_Sgl$GeometryCylinder super;
};
//虚表实例
extern Vtable_Sgl$GeometryCone _vtable_Sgl$GeometryCone;

// class refc:0
struct tagSgl$GeometryCone {
	Sgl$GeometryCylinder super; 
	
};
Vtable_Sgl$GeometryCone* Vtable_Sgl$GeometryCone_init(Vtable_Sgl$GeometryCone* pvt);
void Sgl$GeometryCone_init_fields(Sgl$GeometryCone *self);
void Sgl$GeometryCone_init(Sgl$GeometryCone *self, void *pOwner);
Sgl$GeometryCone * Sgl$GeometryCone_new(void *pOwner);
void Sgl$GeometryCone_fini(Sgl$GeometryCone *self);

void  Sgl$GeometryCone$ctor(Sgl$GeometryCone *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
