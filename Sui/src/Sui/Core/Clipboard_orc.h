


#ifndef define_struct___SuiCore__Clipboard_orc_h__
#define define_struct___SuiCore__Clipboard_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Clipboard_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Clipboard_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Clipboard_orc_h__
#define __SuiCore__Clipboard_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
extern void  SuiCore$clipboard_setText(const char *  text);
extern Orc$String*  SuiCore$clipboard_getText(Orc$String **  __outRef__);
void  SuiCore$testClipboard();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
