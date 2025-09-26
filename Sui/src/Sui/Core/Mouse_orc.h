
typedef struct tagSuiCore$MouseData SuiCore$MouseData;


#ifndef define_struct___SuiCore__Mouse_orc_h__
#define define_struct___SuiCore__Mouse_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Mouse_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Mouse_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$MouseData {
	int  clientX ;
	int  clientY ;
	int  button ;
	long long  windowId ;
	bool  isMouseDown ;
	bool  isMouseMove ;
	bool  isMouseUp ;
	bool  isDoubleClick ;
	int  uid ;
	bool  shift ;
	bool  alt ;
	bool  ctrl ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Mouse_orc_h__
#define __SuiCore__Mouse_orc_h__

//include  importHeadCode
#include "./Vec2_orc.h"
#include "./Window_orc.h"
#include "./MouseEvent_orc.h"
#include "./Event_orc.h"
#include "./App_orc.h"
#include "./ViewBase_orc.h"
#include "./Node_orc.h"
#include "../../Orc/String_orc.h"
#include "./Emitter_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
extern SuiCore$Vec2 SuiCore$Mouse_getPos();
SuiCore$Vec2 SuiCore$Mouse_getPosOfWindow(Sui$Window *  window);
void  SuiCore$testMouse();


//结构体元数据获取即初始化
MetaStruct* SuiCore$MouseData_getOrInitMetaStruct();

void  SuiCore$setMouseEventFromMouseData(SuiCore$MouseEvent *  ev, SuiCore$MouseData *  md);
SuiCore$MouseEvent*  SuiCore$newMouseEventFromMouseData(SuiCore$MouseEvent **  __outRef__, SuiCore$MouseData *  md);
void  SuiCore$dispatchMouseEvent(SuiCore$MouseEvent*  ev);
void  SuiCore$dispatchMouseMoveEvent(SuiCore$MouseEvent*  ev);
void  SuiCore$Mouse_onMouseDown(SuiCore$MouseData md);
void  SuiCore$Mouse_onMouseMove(SuiCore$MouseData md);
void  SuiCore$Mouse_onMouseUp(SuiCore$MouseData md);
void  SuiCore$Mouse_onWheel(SuiCore$MouseData *  md, int  deltaX, int  deltaY);
void  SuiCore$printMouseData(SuiCore$MouseData *  md, const char *  prefix);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
