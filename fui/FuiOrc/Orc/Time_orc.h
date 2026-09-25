


#ifndef define_struct___Orc__Time_orc_h__
#define define_struct___Orc__Time_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__Time_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Orc__Time_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__Time_orc_h__
#define __Orc__Time_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
extern void  Orc$Time_sleepMs(int  milliSecond);
extern long long  Orc$Time_unixMs();
void  Orc$Time_sleepSec(float  sec);
long long  Orc$Time_unixSec();
void  Orc$Time_test();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
