
typedef struct tagSuiCore$KeyboardData SuiCore$KeyboardData;


#ifndef define_struct___SuiCore__Keyboard_orc_h__
#define define_struct___SuiCore__Keyboard_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Keyboard_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Keyboard_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$KeyboardData {
	int  char_code ;
	const char *  key ;
	long long  windowId ;
	bool  isKeyDown ;
	bool  isKeyUp ;
	bool  shift ;
	bool  ctrl ;
	bool  alt ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Keyboard_orc_h__
#define __SuiCore__Keyboard_orc_h__

//include  importHeadCode
#include "./KeyEvent_orc.h"
#include "./Window_orc.h"
#include "./App_orc.h"
#include "../../Orc/String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$KeyboardData_getOrInitMetaStruct();

SuiCore$KeyEvent*  SuiCore$newKeyEvent_fromKeyboardData(SuiCore$KeyEvent **  __outRef__, SuiCore$KeyboardData *  kd);
void  SuiCore$Keyboard_onKeyDown(SuiCore$KeyboardData *  kd);
void  SuiCore$Keyboard_onKeyUp(SuiCore$KeyboardData *  kd);
void  SuiCore$printKeyboardData(SuiCore$KeyboardData *  kd);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
