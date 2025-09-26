
typedef struct tagProject_Mod$Father Project_Mod$Father;
typedef struct tagVtable_Project_Mod$Father Vtable_Project_Mod$Father;
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
int  Project_Mod$say();

// 虚表
struct tagVtable_Project_Mod$Father {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Project_Mod$Father _vtable_Project_Mod$Father;

// class
struct tagProject_Mod$Father {
	Object super; 
	void  (*lala) (Project_Mod$Father *  self);
};
Vtable_Project_Mod$Father* Vtable_Project_Mod$Father_init(Vtable_Project_Mod$Father* pvt);
void Project_Mod$Father_init_fields(Project_Mod$Father *self);
void Project_Mod$Father_init(Project_Mod$Father *self);
Project_Mod$Father * Project_Mod$Father_new();
void Project_Mod$Father_fini(Project_Mod$Father *self);

// 虚表
struct tagVtable_Project_Mod$User {
	Vtable_Project_Mod$Father super;
};
//虚表实例
extern Vtable_Project_Mod$User _vtable_Project_Mod$User;

// class
struct tagProject_Mod$User {
	Project_Mod$Father super; 
	void  (*print) (Project_Mod$User *  self);
};
Vtable_Project_Mod$User* Vtable_Project_Mod$User_init(Vtable_Project_Mod$User* pvt);
void Project_Mod$User_init_fields(Project_Mod$User *self);
void Project_Mod$User_init(Project_Mod$User *self);
Project_Mod$User * Project_Mod$User_new();
void Project_Mod$User_fini(Project_Mod$User *self);
void  Project_Mod$User$calc(Project_Mod$User *  self);
Project_Mod$User*  Project_Mod$useRef(Project_Mod$User **  __outRef__, Project_Mod$User*  u);
void  Project_Mod$main();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
