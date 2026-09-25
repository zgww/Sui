
typedef struct tagUser User;
typedef struct tagVtable_User Vtable_User;


#ifndef define_struct_____User_orc_h__
#define define_struct_____User_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE_____User_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE_____User_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef ____User_orc_h__
#define ____User_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
void  say();

// 虚表
struct tagVtable_User {
	Vtable_Object super;
};
//虚表实例
extern Vtable_User _vtable_User;

// class refc:1
struct tagUser {
	Object super; 
	int  age ;
	void  (*say) (User *  self, const char *  msg);
};
Vtable_User* Vtable_User_init(Vtable_User* pvt);
void User_init_fields(User *self);
void User_init(User *self, void *pOwner);
User * User_new(void *pOwner);
void User_fini(User *self);

void  User$ctor(User *  self);
void  User$dtor(User *  self);
void  User$say(User *  self, const char *  msg);

User*  orcMain(User **  __outRef__);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
