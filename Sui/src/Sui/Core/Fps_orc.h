
typedef struct tagSuiCore$Fps SuiCore$Fps;


#ifndef define_struct___SuiCore__Fps_orc_h__
#define define_struct___SuiCore__Fps_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Fps_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Fps_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Fps {
	float  fps ;
	float  layoutFps ;
	float  drawFps ;
	long long  costMs ;
	long long  layoutCostMs ;
	long long  drawCostMs ;
	long long  startMs ;
	long long  endMs ;
	long long  layoutStartMs ;
	long long  layoutEndMs ;
	long long  drawStartMs ;
	long long  drawEndMs ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Fps_orc_h__
#define __SuiCore__Fps_orc_h__

//include  importHeadCode
#include "../../Orc/Time_orc.h"
#include "../Core/Canvas_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Fps_getOrInitMetaStruct();

void  SuiCore$Fps$startFrame(SuiCore$Fps *  self);
void  SuiCore$Fps$endFrame(SuiCore$Fps *  self);
void  SuiCore$Fps$startLayout(SuiCore$Fps *  self);
void  SuiCore$Fps$endLayout(SuiCore$Fps *  self);
void  SuiCore$Fps$startDraw(SuiCore$Fps *  self);
void  SuiCore$Fps$endDraw(SuiCore$Fps *  self);
void  SuiCore$Fps$draw(SuiCore$Fps *  self, SuiCore$Canvas *  canvas, int  h);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
