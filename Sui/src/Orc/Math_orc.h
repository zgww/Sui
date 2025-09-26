


#ifndef define_struct___Orc__Math_orc_h__
#define define_struct___Orc__Math_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__Math_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___Orc__Math_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__Math_orc_h__
#define __Orc__Math_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
int  Orc$absInt(int  a);
float  Orc$absFloat(float  a);
int  Orc$minInt(int  a, int  b);
int  Orc$maxInt(int  a, int  b);
float  Orc$calcRatio(float  value, float  left, float  right);
float  Orc$lerpFloat(float  f, float  t, float  r);
float  Orc$minFloat(float  a, float  b);
float  Orc$maxFloat3(float  a, float  b, float  c);
float  Orc$maxFloat(float  a, float  b);
double  Orc$minDouble(double  a, double  b);
double  Orc$maxDouble(double  a, double  b);
float  Orc$clampInt(int  x, int  min, int  max);
float  Orc$clampFloat(float  x, float  min, float  max);
extern bool  Orc$isNaN(float  v);
float  Orc$floorFloat(float  v);
void  Orc$Math_test();
extern double  Orc$EPSILON;
bool  Orc$eqFloat(float  a, float  b);
extern const double  Orc$LN2;
extern const double  Orc$PI;
double  Orc$toRad(double  degree);
double  Orc$toDeg(double  rad);
extern int  Orc$doubleSize();
extern int  Orc$floatSize();
extern int  Orc$shortSize();
extern int  Orc$intSize();
extern int  Orc$longSize();
extern int  Orc$longLongSize();
extern int  Orc$pointerSize();
int  Orc$randRange(int  fromV, int  toV);
extern float  Orc$rand01f();
float  Orc$random();
float  Orc$randRangef(float  fromV, float  toV);
float  Orc$randRadiusf(float  radius);
float  Orc$euclideanModulo(float  n, float  m);
float  Orc$mapLinear(float  x, float  a1, float  a2, float  b1, float  b2);
float  Orc$inverseLerp(float  x, float  y, float  value);
float  Orc$damp(float  x, float  y, float  lambda, float  dt);
float  Orc$pingpong(float  x, float  length);
float  Orc$smoothstep(float  x, float  min, float  max);
float  Orc$smootherstep(float  x, float  min, float  max);
bool  Orc$isPowerOfTwo(int  value);
float  Orc$ceilPowerOfTwo(float  value);
float  Orc$floorPowerOfTwo(float  value);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
