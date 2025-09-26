
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
struct tagVtable_Project_Mod$User {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Project_Mod$User _vtable_Project_Mod$User;

// class
struct tagProject_Mod$User {
	Object super; 
	int  age ;
	int  name ;
	char *  data ;
	void  (*say) (Project_Mod$User *  self);
	void  (*nice_guy) (Project_Mod$User *  self, int  age);
	void  (*nice_guy_three) (Project_Mod$User *  self, int  age, bool  ok, char *  data);
};
Vtable_Project_Mod$User* Vtable_Project_Mod$User_init(Vtable_Project_Mod$User* pvt);
void Project_Mod$User_init_fields(Project_Mod$User *self);
void Project_Mod$User_init(Project_Mod$User *self);
Project_Mod$User * Project_Mod$User_new();
void Project_Mod$User_fini(Project_Mod$User *self);

void  Project_Mod$User$say(Project_Mod$User *  self);
void  Project_Mod$User$nice_guy(Project_Mod$User *  self, int  age);
void  Project_Mod$User$nice_guy_three(Project_Mod$User *  self, int  age, bool  ok, char *  data);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
