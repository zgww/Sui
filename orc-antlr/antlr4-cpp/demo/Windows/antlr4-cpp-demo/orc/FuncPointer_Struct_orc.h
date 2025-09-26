
typedef struct tagProject_Mod$Father Project_Mod$Father;
typedef struct tagProject_Mod$User Project_Mod$User;


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

struct tagProject_Mod$Father {
void  (*hi)();

};

//结构体元数据获取即初始化
MetaStruct* Project_Mod$Father_getOrInitMetaStruct();


struct tagProject_Mod$User {
Project_Mod$Father *  p ;
Project_Mod$Father p2 ;

};

//结构体元数据获取即初始化
MetaStruct* Project_Mod$User_getOrInitMetaStruct();

void  Project_Mod$main();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
