
typedef struct tagProject$User Project$User;
typedef struct tagVtable_Project$User Vtable_Project$User;


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
struct tagVtable_Project$User {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Project$User _vtable_Project$User;

// class
struct tagProject$User {
	Object super; 
	
};
Vtable_Project$User* Vtable_Project$User_init(Vtable_Project$User* pvt);
void Project$User_init_fields(Project$User *self);
void Project$User_init(Project$User *self);
Project$User * Project$User_new();
void Project$User_fini(Project$User *self);


void  Project$hi();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
