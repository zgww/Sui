
typedef struct tagSgl$DirLight Sgl$DirLight;
typedef struct tagVtable_Sgl$DirLight Vtable_Sgl$DirLight;


#ifndef define_struct___Sgl__DirLight_orc_h__
#define define_struct___Sgl__DirLight_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__DirLight_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__DirLight_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__DirLight_orc_h__
#define __Sgl__DirLight_orc_h__

//include  importHeadCode
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
struct tagVtable_Sgl$DirLight {
	Vtable_Sgl$Light super;
};
//虚表实例
extern Vtable_Sgl$DirLight _vtable_Sgl$DirLight;

// class refc:0
struct tagSgl$DirLight {
	Sgl$Light super; 
	int  ambient ;
	int  diffuse ;
	int  specular ;
};
Vtable_Sgl$DirLight* Vtable_Sgl$DirLight_init(Vtable_Sgl$DirLight* pvt);
void Sgl$DirLight_init_fields(Sgl$DirLight *self);
void Sgl$DirLight_init(Sgl$DirLight *self, void *pOwner);
Sgl$DirLight * Sgl$DirLight_new(void *pOwner);
void Sgl$DirLight_fini(Sgl$DirLight *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
