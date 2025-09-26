
typedef struct tagTest$Vec3 Test$Vec3;


#ifndef define_struct___Test__callReturnStructExtension_orc_h__
#define define_struct___Test__callReturnStructExtension_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Test__callReturnStructExtension_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#define INCLUDE_ONLY_TYPE
#include "./Struct_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___Test__callReturnStructExtension_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagTest$Vec3 {
	Project_Mod$Main main ;
	float  x ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Test__callReturnStructExtension_orc_h__
#define __Test__callReturnStructExtension_orc_h__

//include  importHeadCode
#include "./Struct_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Test$Vec3_getOrInitMetaStruct();

Test$Vec3 Test$mkVec3();
Test$Vec3 Test$Vec3$print(Test$Vec3 *  self);
Test$Vec3 Test$Vec3$gogo(Test$Vec3 *  self);
void  Test$printMyName();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
