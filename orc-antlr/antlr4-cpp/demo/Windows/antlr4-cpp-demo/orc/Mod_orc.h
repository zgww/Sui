
typedef struct tagProject_Mod$User Project_Mod$User;
typedef struct tagVtable_Project_Mod$User Vtable_Project_Mod$User;
typedef struct tagProject_Mod$AVFrame Project_Mod$AVFrame;


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
	char *  name ;
	void  (*printInfo) (Project_Mod$User *  self);
};
Vtable_Project_Mod$User* Vtable_Project_Mod$User_init(Vtable_Project_Mod$User* pvt);
void Project_Mod$User_init_fields(Project_Mod$User *self);
void Project_Mod$User_init(Project_Mod$User *self);
Project_Mod$User * Project_Mod$User_new();
void Project_Mod$User_fini(Project_Mod$User *self);

void  Project_Mod$User$printInfo(Project_Mod$User *  self);


struct tagProject_Mod$AVFrame {
int  nbytes ;
char *  data ;

};

//结构体元数据获取即初始化
MetaStruct* Project_Mod$AVFrame_getOrInitMetaStruct();

extern int  Project_Mod$user;
void  Project_Mod$sayok();
void  Project_Mod$gogogo();
Project_Mod$AVFrame Project_Mod$mkFrame();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
