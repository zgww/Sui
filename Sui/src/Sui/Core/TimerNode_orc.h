
typedef struct tagSuiCore$TimerNode SuiCore$TimerNode;
typedef struct tagVtable_SuiCore$TimerNode Vtable_SuiCore$TimerNode;


#ifndef define_struct___SuiCore__TimerNode_orc_h__
#define define_struct___SuiCore__TimerNode_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__TimerNode_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__TimerNode_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__TimerNode_orc_h__
#define __SuiCore__TimerNode_orc_h__

//include  importHeadCode
#include "./Node_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$TimerNode {
	Vtable_SuiCore$Node super;
};
//虚表实例
extern Vtable_SuiCore$TimerNode _vtable_SuiCore$TimerNode;

// class refc:0
struct tagSuiCore$TimerNode {
	SuiCore$Node super; 
	
};
Vtable_SuiCore$TimerNode* Vtable_SuiCore$TimerNode_init(Vtable_SuiCore$TimerNode* pvt);
void SuiCore$TimerNode_init_fields(SuiCore$TimerNode *self);
void SuiCore$TimerNode_init(SuiCore$TimerNode *self, void *pOwner);
SuiCore$TimerNode * SuiCore$TimerNode_new(void *pOwner);
void SuiCore$TimerNode_fini(SuiCore$TimerNode *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
