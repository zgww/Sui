
typedef struct tagSuiCore$BoxShadow SuiCore$BoxShadow;
typedef struct tagVtable_SuiCore$BoxShadow Vtable_SuiCore$BoxShadow;


#ifndef define_struct___SuiCore__BoxShadow_orc_h__
#define define_struct___SuiCore__BoxShadow_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__BoxShadow_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___SuiCore__BoxShadow_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__BoxShadow_orc_h__
#define __SuiCore__BoxShadow_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$BoxShadow {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$BoxShadow _vtable_SuiCore$BoxShadow;

// class refc:1
struct tagSuiCore$BoxShadow {
	Object super; 
	float  dx ;
	float  dy ;
	float  sigmaX ;
	float  sigmaY ;
	int  color ;
};
Vtable_SuiCore$BoxShadow* Vtable_SuiCore$BoxShadow_init(Vtable_SuiCore$BoxShadow* pvt);
void SuiCore$BoxShadow_init_fields(SuiCore$BoxShadow *self);
void SuiCore$BoxShadow_init(SuiCore$BoxShadow *self, void *pOwner);
SuiCore$BoxShadow * SuiCore$BoxShadow_new(void *pOwner);
void SuiCore$BoxShadow_fini(SuiCore$BoxShadow *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
