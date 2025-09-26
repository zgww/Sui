
typedef struct tagTest$User Test$User;
typedef struct tagVtable_Test$User Vtable_Test$User;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef ___orc_h__
#define ___orc_h__

//include  importHeadCode
#include "Orc.h"
#include <stdlib.h>


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Test$User {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Test$User _vtable_Test$User;

// class
struct tagTest$User {
	Object super; 
	void  (*cleanData) (Test$User *  self);
};
Vtable_Test$User* Vtable_Test$User_init(Vtable_Test$User* pvt);
void Test$User_init_fields(Test$User *self);
void Test$User_init(Test$User *self);
Test$User * Test$User_new();
void Test$User_fini(Test$User *self);

void  Test$User$cleanData(Test$User *  self);

void  Test$User$say(Test$User *  self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
