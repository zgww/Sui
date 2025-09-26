
typedef struct tagProject$Parent Project$Parent;
typedef struct tagVtable_Project$Parent Vtable_Project$Parent;
typedef struct tagProject$User Project$User;
typedef struct tagVtable_Project$User Vtable_Project$User;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef ___orc_h__
#define ___orc_h__

//include  importHeadCode
#include "Orc.h"
#include <stdlib.h>
#include "stdio.h";


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
void  Project$printf();
void  Project$main();

// 虚表
struct tagVtable_Project$Parent {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Project$Parent _vtable_Project$Parent;

// class
struct tagProject$Parent {
	Object super; 
	int  superField ;
	Project$User*  superTmp ;
	void  (*lala) (Project$Parent *  self);
};
Vtable_Project$Parent* Vtable_Project$Parent_init(Vtable_Project$Parent* pvt);
void Project$Parent_init_fields(Project$Parent *self);
void Project$Parent_init(Project$Parent *self);
Project$Parent * Project$Parent_new();
void Project$Parent_fini(Project$Parent *self);

void  Project$Parent$lala(Project$Parent *  self);


// 虚表
struct tagVtable_Project$User {
	Vtable_Project$Parent super;
};
//虚表实例
extern Vtable_Project$User _vtable_Project$User;

// class
struct tagProject$User {
	Project$Parent super; 
	int  age ;
	Project$User*  tmp ;
	void  (*say) (Project$User *  self);
};
Vtable_Project$User* Vtable_Project$User_init(Vtable_Project$User* pvt);
void Project$User_init_fields(Project$User *self);
void Project$User_init(Project$User *self);
Project$User * Project$User_new();
void Project$User_fini(Project$User *self);

void  Project$User$say(Project$User *  self);

void  Project$User$globalFn(Project$User *  self, Project$User*  xx);
Project$User*  Project$User$returnRef(Project$User **  __outRef__, Project$User *  self, Project$User*  other);
int  Project$getMyAge(int  b);
Project$User*  Project$createUser(Project$User **  __outRef__);
void  Project$hi();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
