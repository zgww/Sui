
typedef struct tagOrcLang$ScopeData OrcLang$ScopeData;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef __ScopeData_orc_h__
#define __ScopeData_orc_h__

//include  importHeadCode
#include "Orc/Orc.h"
#include <stdlib.h>


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

struct tagOrcLang$ScopeData {
	void *  data ;
	void *  onExitScope ;
};

//结构体元数据获取即初始化
MetaStruct* OrcLang$ScopeData_getOrInitMetaStruct();

OrcLang$ScopeData OrcLang$mkScopeData(void *  data, void *  onExitScope);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
