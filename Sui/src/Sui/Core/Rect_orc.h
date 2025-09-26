
typedef struct tagSuiCore$Rect SuiCore$Rect;


#ifndef define_struct___SuiCore__Rect_orc_h__
#define define_struct___SuiCore__Rect_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Rect_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Rect_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$Rect {
	float  x ;
	float  y ;
	float  w ;
	float  h ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Rect_orc_h__
#define __SuiCore__Rect_orc_h__

//include  importHeadCode
#include "./Vec2_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiCore$Rect_getOrInitMetaStruct();

void  SuiCore$Rect$setAll(SuiCore$Rect *  self, float  x, float  y, float  w, float  h);
bool  SuiCore$Rect$isEmpty(SuiCore$Rect *  self);
void  SuiCore$Rect$set_ltrb(SuiCore$Rect *  self, float  left, float  top, float  right, float  bottom);
bool  SuiCore$Rect$containsPosition(SuiCore$Rect *  self, float  px, float  py);
SuiCore$Rect SuiCore$Rect$containsPositionIn5Patch(SuiCore$Rect *  self, float  px, float  py, SuiCore$Rect centerRect);
SuiCore$Rect SuiCore$Rect$containsPositionIn5Patch_withOutType(SuiCore$Rect *  self, float  px, float  py, SuiCore$Rect centerRect, int *  outType);
SuiCore$Vec2 SuiCore$Rect$containsPositionIn9Patch(SuiCore$Rect *  self, float  px, float  py);
float  SuiCore$Rect$right(SuiCore$Rect *  self);
float  SuiCore$Rect$bottom(SuiCore$Rect *  self);
float  SuiCore$Rect$centerX(SuiCore$Rect *  self);
float  SuiCore$Rect$centerY(SuiCore$Rect *  self);
SuiCore$Vec2 SuiCore$Rect$centerPos(SuiCore$Rect *  self);
SuiCore$Vec2 SuiCore$Rect$leftTop(SuiCore$Rect *  self);
SuiCore$Vec2 SuiCore$Rect$leftBottom(SuiCore$Rect *  self);
SuiCore$Vec2 SuiCore$Rect$rightTop(SuiCore$Rect *  self);
SuiCore$Vec2 SuiCore$Rect$rightBottom(SuiCore$Rect *  self);
void  SuiCore$Rect$offset(SuiCore$Rect *  self, float  x, float  y);
SuiCore$Rect SuiCore$Rect$inset(SuiCore$Rect *  self, float  dx, float  dy);
void  SuiCore$Rect$normal(SuiCore$Rect *  self);
bool  SuiCore$Rect$isIntersect(SuiCore$Rect *  self, SuiCore$Rect *  b);
bool  SuiCore$Rect$equals(SuiCore$Rect *  self, SuiCore$Rect *  b);
float  SuiCore$cross(float  x1, float  y1, float  x2, float  y2, float  x, float  y);
bool  SuiCore$isInRect(float  x1, float  y1, float  x2, float  y2, float  x3, float  y3, float  x4, float  y4, float  x, float  y);
SuiCore$Rect SuiCore$mkRect0();
SuiCore$Rect SuiCore$mkRect(float  x, float  y, float  w, float  h);
SuiCore$Rect SuiCore$mkRectByCenterWH(float  cx, float  cy, float  w, float  h);
SuiCore$Rect SuiCore$mkRectByCenterRadius(float  cx, float  cy, float  rad);
void  SuiCore$testRect();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
