
typedef struct tagSgl$SpotLight Sgl$SpotLight;
typedef struct tagVtable_Sgl$SpotLight Vtable_Sgl$SpotLight;


#ifndef define_struct___Sgl__SpotLight_orc_h__
#define define_struct___Sgl__SpotLight_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__SpotLight_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__SpotLight_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__SpotLight_orc_h__
#define __Sgl__SpotLight_orc_h__

//include  importHeadCode
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Light_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$SpotLight {
	Vtable_Sgl$Light super;
};
//虚表实例
extern Vtable_Sgl$SpotLight _vtable_Sgl$SpotLight;

// class refc:0
struct tagSgl$SpotLight {
	Sgl$Light super; 
	float  distance ;
	float  angle ;
};
Vtable_Sgl$SpotLight* Vtable_Sgl$SpotLight_init(Vtable_Sgl$SpotLight* pvt);
void Sgl$SpotLight_init_fields(Sgl$SpotLight *self);
void Sgl$SpotLight_init(Sgl$SpotLight *self, void *pOwner);
Sgl$SpotLight * Sgl$SpotLight_new(void *pOwner);
void Sgl$SpotLight_fini(Sgl$SpotLight *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
