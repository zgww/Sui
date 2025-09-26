
typedef struct tagSgl$PointLight Sgl$PointLight;
typedef struct tagVtable_Sgl$PointLight Vtable_Sgl$PointLight;


#ifndef define_struct___Sgl__PointLight_orc_h__
#define define_struct___Sgl__PointLight_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__PointLight_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__PointLight_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__PointLight_orc_h__
#define __Sgl__PointLight_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Light_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$PointLight {
	Vtable_Sgl$Light super;
};
//虚表实例
extern Vtable_Sgl$PointLight _vtable_Sgl$PointLight;

// class refc:0
struct tagSgl$PointLight {
	Sgl$Light super; 
	int  color ;
	float  intensity ;
	float  distance ;
	float  decay ;
};
Vtable_Sgl$PointLight* Vtable_Sgl$PointLight_init(Vtable_Sgl$PointLight* pvt);
void Sgl$PointLight_init_fields(Sgl$PointLight *self);
void Sgl$PointLight_init(Sgl$PointLight *self, void *pOwner);
Sgl$PointLight * Sgl$PointLight_new(void *pOwner);
void Sgl$PointLight_fini(Sgl$PointLight *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
