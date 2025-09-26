
typedef struct tagSuiView$SystemTrayIcon SuiView$SystemTrayIcon;
typedef struct tagVtable_SuiView$SystemTrayIcon Vtable_SuiView$SystemTrayIcon;


#ifndef define_struct___SuiView__SystemTrayIcon_orc_h__
#define define_struct___SuiView__SystemTrayIcon_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__SystemTrayIcon_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>




#ifdef INCLUDE_ONLY_TYPE___SuiView__SystemTrayIcon_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__SystemTrayIcon_orc_h__
#define __SuiView__SystemTrayIcon_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/Mouse_orc.h"
#include "../Core/Vec2_orc.h"
#include "../../Orc/Time_orc.h"
#include "../Core/Timer_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../Core/App_orc.h"
#include "../View/MenuNative_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../Core/Window_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$SystemTrayIcon {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$SystemTrayIcon _vtable_SuiView$SystemTrayIcon;

// class refc:0
struct tagSuiView$SystemTrayIcon {
	Object super; 
	int  uid ;
	void *  data ;
	Orc$String*  iconPath ;
	void  (*setIconPath) (SuiView$SystemTrayIcon *  self, const char *  iconPath);
	bool  (*initData) (SuiView$SystemTrayIcon *  self);
	bool  (*init) (SuiView$SystemTrayIcon *  self);
	bool  (*doDestroy) (SuiView$SystemTrayIcon *  self);
	void  (*destroy) (SuiView$SystemTrayIcon *  self);
};
Vtable_SuiView$SystemTrayIcon* Vtable_SuiView$SystemTrayIcon_init(Vtable_SuiView$SystemTrayIcon* pvt);
void SuiView$SystemTrayIcon_init_fields(SuiView$SystemTrayIcon *self);
void SuiView$SystemTrayIcon_init(SuiView$SystemTrayIcon *self, void *pOwner);
SuiView$SystemTrayIcon * SuiView$SystemTrayIcon_new(void *pOwner);
void SuiView$SystemTrayIcon_fini(SuiView$SystemTrayIcon *self);

void  SuiView$SystemTrayIcon$setIconPath(SuiView$SystemTrayIcon *  self, const char *  iconPath);
void  SuiView$SystemTrayIcon$ctor(SuiView$SystemTrayIcon *  self);
extern void  SuiView$SystemTrayIcon$dtor(SuiView$SystemTrayIcon *  self);
extern bool  SuiView$SystemTrayIcon$initData(SuiView$SystemTrayIcon *  self);
bool  SuiView$SystemTrayIcon$init(SuiView$SystemTrayIcon *  self);
extern bool  SuiView$SystemTrayIcon$doDestroy(SuiView$SystemTrayIcon *  self);
void  SuiView$SystemTrayIcon$destroy(SuiView$SystemTrayIcon *  self);

Orc$List*  SuiView$SystemTrayIcons_use(Orc$List **  __outRef__);
SuiView$SystemTrayIcon*  SuiView$SystemTrayIcons_findByUid(SuiView$SystemTrayIcon **  __outRef__, int  uid);
void  SuiView$SystemTrayIcon_onMouseData(SuiCore$MouseData md);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
