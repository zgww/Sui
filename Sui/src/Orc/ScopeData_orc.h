
typedef struct tagOrc$ScopeData Orc$ScopeData;


#ifndef define_struct___Orc__ScopeData_orc_h__
#define define_struct___Orc__ScopeData_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__ScopeData_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___Orc__ScopeData_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagOrc$ScopeData {
	void *  data ;
	void *  onExitScope ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__ScopeData_orc_h__
#define __Orc__ScopeData_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Orc$ScopeData_getOrInitMetaStruct();

Orc$ScopeData Orc$mkScopeData(void *  data, void *  onExitScope);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
