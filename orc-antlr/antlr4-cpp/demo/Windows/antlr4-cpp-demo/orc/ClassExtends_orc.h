
typedef struct tagProject_Mod$Parent Project_Mod$Parent;
typedef struct tagVtable_Project_Mod$Parent Vtable_Project_Mod$Parent;
typedef struct tagProject_Mod$User Project_Mod$User;
typedef struct tagVtable_Project_Mod$User Vtable_Project_Mod$User;


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
struct tagVtable_Project_Mod$Parent {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Project_Mod$Parent _vtable_Project_Mod$Parent;

// class
struct tagProject_Mod$Parent {
	Object super; 
	int  age ;
	void  (*say) (Project_Mod$Parent *  self);
	void  (*say2) (Project_Mod$Parent *  self);
};
Vtable_Project_Mod$Parent* Vtable_Project_Mod$Parent_init(Vtable_Project_Mod$Parent* pvt);
void Project_Mod$Parent_init_fields(Project_Mod$Parent *self);
void Project_Mod$Parent_init(Project_Mod$Parent *self);
Project_Mod$Parent * Project_Mod$Parent_new();
void Project_Mod$Parent_fini(Project_Mod$Parent *self);

// 虚表
struct tagVtable_Project_Mod$User {
	Vtable_Project_Mod$Parent super;
};
//虚表实例
extern Vtable_Project_Mod$User _vtable_Project_Mod$User;

// class
struct tagProject_Mod$User {
	Project_Mod$Parent super; 
	int  level ;
	char *  name ;
	char *  hint ;
	int  (*say3) (Project_Mod$User *  self);
};
Vtable_Project_Mod$User* Vtable_Project_Mod$User_init(Vtable_Project_Mod$User* pvt);
void Project_Mod$User_init_fields(Project_Mod$User *self);
void Project_Mod$User_init(Project_Mod$User *self);
Project_Mod$User * Project_Mod$User_new();
void Project_Mod$User_fini(Project_Mod$User *self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
