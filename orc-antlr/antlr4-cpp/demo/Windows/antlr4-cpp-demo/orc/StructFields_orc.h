
typedef struct tagProject_Mod$User Project_Mod$User;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef ___orc_h__
#define ___orc_h__

//include  importHeadCode
#include "Orc.h"
#include <stdlib.h>
#include "stdio.h";
#include "missing StringLit_orc.h";


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
enum Project_Mod$UserType {
	Project_Mod$UserType_DoIt, 
	Project_Mod$UserType_DoIt2, 

};

struct tagProject_Mod$User {
int  age ;
bool  isMale ;
int *  p_age ;

};

//结构体元数据获取即初始化
MetaStruct* Project_Mod$User_getOrInitMetaStruct();

void  Project_Mod$User$say(Project_Mod$User *  self);
void  Project_Mod$User$print(Project_Mod$User *  self);
extern int  Project_Mod$age;
void  Project_Mod$say();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
