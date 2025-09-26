


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef ___orc_h__
#define ___orc_h__

//include  importHeadCode
#include "OrcLang/Orc.h"
#include <stdlib.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
int  OrcLang$absInt(int  a);
float  OrcLang$absFloat(float  a);
int  OrcLang$minInt(int  a, int  b);
int  OrcLang$maxInt(int  a, int  b);
float  OrcLang$lerpFloat(float  f, float  t, float  r);
float  OrcLang$minFloat(float  a, float  b);
float  OrcLang$maxFloat(float  a, float  b);
float  OrcLang$clampInt(int  x, int  min, int  max);
float  OrcLang$clampFloat(float  x, float  min, float  max);
void  OrcLang$Math_test();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
