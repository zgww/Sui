
typedef struct tagSuiCore$Frame SuiCore$Frame;


#ifndef define_struct___SuiCore__Frame_orc_h__
#define define_struct___SuiCore__Frame_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Frame_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Frame_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Frame {
	int  timesInOneLayout ;
	int  applyCacheTimes ;
	float  minWidth ;
	float  minHeight ;
	float  maxWidth ;
	float  maxHeight ;
	float  prevMinWidth ;
	float  prevMinHeight ;
	float  prevMaxWidth ;
	float  prevMaxHeight ;
	float  x ;
	float  y ;
	float  width ;
	float  height ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Frame_orc_h__
#define __SuiCore__Frame_orc_h__

//include  importHeadCode
#include "./Node_orc.h"
#include "./Inset_orc.h"
#include "./Vec2_orc.h"
#include "./Rect_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./LayoutCell_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "../../Orc/Math_orc.h"
#include "../../Orc/List_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Frame_getOrInitMetaStruct();

SuiCore$Frame SuiCore$mkFrame();
SuiCore$Frame SuiCore$Frame$copy(SuiCore$Frame *  self);
bool  SuiCore$Frame$isConstraintsNotChanged(SuiCore$Frame *  self);
bool  SuiCore$Frame$checkAndUseCacheResult(SuiCore$Frame *  self);
void  SuiCore$Frame$saveConstraints(SuiCore$Frame *  self);
void  SuiCore$Frame$incTimesInOneLayout(SuiCore$Frame *  self);
SuiCore$Frame SuiCore$Frame$inset(SuiCore$Frame *  self, SuiCore$Inset inset);
SuiCore$Frame SuiCore$Frame$outset(SuiCore$Frame *  self, SuiCore$Inset inset);
SuiCore$Rect SuiCore$Frame$toRect(SuiCore$Frame *  self);
void  SuiCore$Frame$copyConstraints(SuiCore$Frame *  self, SuiCore$Frame *  ctx);
void  SuiCore$Frame$copyMaxConstraints(SuiCore$Frame *  self, SuiCore$Frame *  ctx);
void  SuiCore$Frame$copyMinConstraints(SuiCore$Frame *  self, SuiCore$Frame *  ctx);
void  SuiCore$Frame$setMinConstraints(SuiCore$Frame *  self, float  w, float  h);
void  SuiCore$Frame$setMaxConstraints(SuiCore$Frame *  self, float  w, float  h);
void  SuiCore$Frame$setMinWidth(SuiCore$Frame *  self, float  minV);
void  SuiCore$Frame$setMinHeight(SuiCore$Frame *  self, float  minV);
void  SuiCore$Frame$setWidthConstraint(SuiCore$Frame *  self, float  minv, float  maxv);
void  SuiCore$Frame$setHeightConstraint(SuiCore$Frame *  self, float  minv, float  maxv);
void  SuiCore$Frame$clampTightWidthConstraint(SuiCore$Frame *  self, float  v);
void  SuiCore$Frame$clampTightHeightConstraint(SuiCore$Frame *  self, float  v);
void  SuiCore$Frame$plusWidthConstraint(SuiCore$Frame *  self, float  minW, float  maxW);
void  SuiCore$Frame$plusHeightConstraint(SuiCore$Frame *  self, float  minW, float  maxW);
void  SuiCore$Frame$plusConstraints(SuiCore$Frame *  self, float  minW, float  maxW, float  minH, float  maxH);
void  SuiCore$Frame$clampWidth(SuiCore$Frame *  self, float  v, float  minW, float  maxW);
void  SuiCore$Frame$clampHeight(SuiCore$Frame *  self, float  v, float  minW, float  maxW);
void  SuiCore$Frame$setSize(SuiCore$Frame *  self, float  w, float  h);
SuiCore$Vec2 SuiCore$Frame$getSize(SuiCore$Frame *  self);
void  SuiCore$Frame$setWidth(SuiCore$Frame *  self, float  w);
void  SuiCore$Frame$setHeight(SuiCore$Frame *  self, float  h);
void  SuiCore$Frame$setRect(SuiCore$Frame *  self, float  x, float  y, float  w, float  h);
void  SuiCore$Frame$setPosition(SuiCore$Frame *  self, float  x, float  y);
float  SuiCore$Frame$getBottom(SuiCore$Frame *  self);
float  SuiCore$Frame$getRight(SuiCore$Frame *  self);
bool  SuiCore$Frame$setSize_ifAnyTight(SuiCore$Frame *  self);
bool  SuiCore$Frame$setSize_ifTight(SuiCore$Frame *  self);
void  SuiCore$Frame$copyWidthConstraint(SuiCore$Frame *  self, SuiCore$Frame *  ctx);
void  SuiCore$Frame$copyHeightConstraint(SuiCore$Frame *  self, SuiCore$Frame *  ctx);
void  SuiCore$Frame$setTightWidth(SuiCore$Frame *  self, float  w);
void  SuiCore$Frame$setTightHeight(SuiCore$Frame *  self, float  h);
void  SuiCore$Frame$setTight(SuiCore$Frame *  self, float  w, float  h);
bool  SuiCore$Frame$isTightWidth(SuiCore$Frame *  self);
bool  SuiCore$Frame$isTightHeight(SuiCore$Frame *  self);
bool  SuiCore$Frame$isTight(SuiCore$Frame *  self);
bool  SuiCore$Frame$isLoose(SuiCore$Frame *  self);
void  SuiCore$Frame$reset(SuiCore$Frame *  self);
bool  SuiCore$Frame$isSizeSatisfy_otherFrameConstraints(SuiCore$Frame *  self, SuiCore$Frame *  ctx);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
