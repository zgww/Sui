


#ifndef define_struct___SuiDialog__MessageDialog_orc_h__
#define define_struct___SuiDialog__MessageDialog_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDialog__MessageDialog_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDialog__MessageDialog_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDialog__MessageDialog_orc_h__
#define __SuiDialog__MessageDialog_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../Core/Window_orc.h"
#include "../Core/App_orc.h"
#include "../View/EditText_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../View/Button_orc.h"
#include "../../SuiDesigner/Theme_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
extern void  SuiDialog$MessageDialog_alert(const char *  content, const char *  title);
extern void  SuiDialog$MessageDialog_alert_error(const char *  content, const char *  title);
extern void  SuiDialog$MessageDialog_alert_warn(const char *  content, const char *  title);
extern bool  SuiDialog$MessageDialog_confirm(const char *  content, const char *  title);
void  SuiDialog$MessageDialog_prompt(const char *  value, const char *  title, void  (**onNewValue)(void *  self, Orc$String*  newValue));
void  SuiDialog$testMessageDialog();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
