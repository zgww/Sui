
typedef struct tagSuiView$Splitter SuiView$Splitter;
typedef struct tagVtable_SuiView$Splitter Vtable_SuiView$Splitter;


#ifndef define_struct___SuiView__Splitter_orc_h__
#define define_struct___SuiView__Splitter_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__Splitter_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___SuiView__Splitter_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__Splitter_orc_h__
#define __SuiView__Splitter_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$Splitter {
	Vtable_SuiCore$ViewBase super;
};
//虚表实例
extern Vtable_SuiView$Splitter _vtable_SuiView$Splitter;

// class refc:0
struct tagSuiView$Splitter {
	SuiCore$ViewBase super; 
	
};
Vtable_SuiView$Splitter* Vtable_SuiView$Splitter_init(Vtable_SuiView$Splitter* pvt);
void SuiView$Splitter_init_fields(SuiView$Splitter *self);
void SuiView$Splitter_init(SuiView$Splitter *self, void *pOwner);
SuiView$Splitter * SuiView$Splitter_new(void *pOwner);
void SuiView$Splitter_fini(SuiView$Splitter *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
