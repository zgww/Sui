
typedef struct tagUser User;
typedef struct tagVtable_User Vtable_User;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef __Main_orc_h__
#define __Main_orc_h__

//include  importHeadCode
#include "Orc/Orc.h"
#include <stdlib.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_User {
	Vtable_Object super;
};
//虚表实例
extern Vtable_User _vtable_User;

// class
struct tagUser {
	Object super; 
	int  id ;
	void  (*say) (User *  self);
};
Vtable_User* Vtable_User_init(Vtable_User* pvt);
void User_init_fields(User *self);
void User_init(User *self);
User * User_new();
void User_fini(User *self);

void  User$say(User *  self);

int  main();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
