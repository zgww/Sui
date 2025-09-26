
typedef struct tagSgl$Light Sgl$Light;
typedef struct tagVtable_Sgl$Light Vtable_Sgl$Light;


#ifndef define_struct___Sgl__Light_orc_h__
#define define_struct___Sgl__Light_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Light_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Light_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Light_orc_h__
#define __Sgl__Light_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Material_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Light {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$Light _vtable_Sgl$Light;

// class refc:0
struct tagSgl$Light {
	Sgl$Obj3d super; 
	
};
Vtable_Sgl$Light* Vtable_Sgl$Light_init(Vtable_Sgl$Light* pvt);
void Sgl$Light_init_fields(Sgl$Light *self);
void Sgl$Light_init(Sgl$Light *self, void *pOwner);
Sgl$Light * Sgl$Light_new(void *pOwner);
void Sgl$Light_fini(Sgl$Light *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
