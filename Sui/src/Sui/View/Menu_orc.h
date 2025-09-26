
typedef struct tagSuiView$Menu SuiView$Menu;
typedef struct tagVtable_SuiView$Menu Vtable_SuiView$Menu;


#ifndef define_struct___SuiView__Menu_orc_h__
#define define_struct___SuiView__Menu_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__Menu_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___SuiView__Menu_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__Menu_orc_h__
#define __SuiView__Menu_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$Menu {
	Vtable_SuiCore$ViewBase super;
};
//虚表实例
extern Vtable_SuiView$Menu _vtable_SuiView$Menu;

// class refc:0
struct tagSuiView$Menu {
	SuiCore$ViewBase super; 
	
};
Vtable_SuiView$Menu* Vtable_SuiView$Menu_init(Vtable_SuiView$Menu* pvt);
void SuiView$Menu_init_fields(SuiView$Menu *self);
void SuiView$Menu_init(SuiView$Menu *self, void *pOwner);
SuiView$Menu * SuiView$Menu_new(void *pOwner);
void SuiView$Menu_fini(SuiView$Menu *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
