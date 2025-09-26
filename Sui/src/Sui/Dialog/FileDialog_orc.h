
typedef struct tagSuiDialog$FileDialog SuiDialog$FileDialog;
typedef struct tagVtable_SuiDialog$FileDialog Vtable_SuiDialog$FileDialog;


#ifndef define_struct___SuiDialog__FileDialog_orc_h__
#define define_struct___SuiDialog__FileDialog_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDialog__FileDialog_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDialog__FileDialog_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDialog__FileDialog_orc_h__
#define __SuiDialog__FileDialog_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Path_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDialog$FileDialog {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDialog$FileDialog _vtable_SuiDialog$FileDialog;

// class refc:1
struct tagSuiDialog$FileDialog {
	Object super; 
	
};
Vtable_SuiDialog$FileDialog* Vtable_SuiDialog$FileDialog_init(Vtable_SuiDialog$FileDialog* pvt);
void SuiDialog$FileDialog_init_fields(SuiDialog$FileDialog *self);
void SuiDialog$FileDialog_init(SuiDialog$FileDialog *self, void *pOwner);
SuiDialog$FileDialog * SuiDialog$FileDialog_new(void *pOwner);
void SuiDialog$FileDialog_fini(SuiDialog$FileDialog *self);


extern Orc$List*  SuiDialog$fileDialog_getOpenFileName(Orc$List **  __outRef__, const char *  dir, const char *  title);
extern Orc$String*  SuiDialog$fileDialog_getSaveFileName(Orc$String **  __outRef__, const char *  dir, const char *  title);
extern Orc$String*  SuiDialog$fileDialog_getExistingDirectory(Orc$String **  __outRef__, const char *  dir, const char *  title);
Orc$List*  SuiDialog$FileDialog_getOpenFileName(Orc$List **  __outRef__, const char *  dir, const char *  title);
void  SuiDialog$test();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
