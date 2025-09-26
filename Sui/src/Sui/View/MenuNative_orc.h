
typedef struct tagSuiView$MenuNativeItem SuiView$MenuNativeItem;
typedef struct tagVtable_SuiView$MenuNativeItem Vtable_SuiView$MenuNativeItem;
typedef struct tagSuiView$MenuNative SuiView$MenuNative;
typedef struct tagVtable_SuiView$MenuNative Vtable_SuiView$MenuNative;


#ifndef define_struct___SuiView__MenuNative_orc_h__
#define define_struct___SuiView__MenuNative_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__MenuNative_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../../UrgcDll/urgc_api.h"
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__MenuNative_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__MenuNative_orc_h__
#define __SuiView__MenuNative_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/Mouse_orc.h"
#include "../Core/Vec2_orc.h"
#include "../../Orc/Time_orc.h"
#include "../Core/Timer_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../Core/App_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../Core/Window_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$MenuNativeItem {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$MenuNativeItem _vtable_SuiView$MenuNativeItem;

// class refc:0
struct tagSuiView$MenuNativeItem {
	Object super; 
	int  commandId ;
	int  id ;
	Orc$String*  cmd ;
	Orc$String*  label ;
	void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item);
	Orc$List*  children ;
	void  (*append) (SuiView$MenuNativeItem *  self, SuiView$MenuNativeItem *  item);
};
Vtable_SuiView$MenuNativeItem* Vtable_SuiView$MenuNativeItem_init(Vtable_SuiView$MenuNativeItem* pvt);
void SuiView$MenuNativeItem_init_fields(SuiView$MenuNativeItem *self);
void SuiView$MenuNativeItem_init(SuiView$MenuNativeItem *self, void *pOwner);
SuiView$MenuNativeItem * SuiView$MenuNativeItem_new(void *pOwner);
void SuiView$MenuNativeItem_fini(SuiView$MenuNativeItem *self);

void  SuiView$MenuNativeItem$ctor(SuiView$MenuNativeItem *  self);
void  SuiView$MenuNativeItem$dtor(SuiView$MenuNativeItem *  self);
void  SuiView$MenuNativeItem$append(SuiView$MenuNativeItem *  self, SuiView$MenuNativeItem *  item);

SuiView$MenuNativeItem*  SuiView$mkMenuNativeItem(SuiView$MenuNativeItem **  __outRef__, SuiView$MenuNativeItem *  parent, Orc$String*  label, void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item));

// 虚表
struct tagVtable_SuiView$MenuNative {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$MenuNative _vtable_SuiView$MenuNative;

// class refc:0
struct tagSuiView$MenuNative {
	Object super; 
	long long  id ;
	SuiView$MenuNativeItem*  root ;
	long long  windowId ;
	void  (**cbOnDismiss)(void *  self);
	void  (*create) (SuiView$MenuNative *  self, SuiView$MenuNativeItem *  root);
	long long  (*buildNativeMenu) (SuiView$MenuNative *  self, SuiView$MenuNativeItem *  root);
	void  (*show) (SuiView$MenuNative *  self);
	void  (*showAt) (SuiView$MenuNative *  self, int  clientX, int  clientY);
	void  (*showAtScreenPosition) (SuiView$MenuNative *  self, int  screenX, int  screenY);
	void  (*showAtMouse) (SuiView$MenuNative *  self);
	void  (*onDismiss) (SuiView$MenuNative *  self);
	void  (*destroy) (SuiView$MenuNative *  self);
	bool  (*dispatchCommand) (SuiView$MenuNative *  self, SuiView$MenuNativeItem *  item, Sui$Window *  win, int  commandId);
};
Vtable_SuiView$MenuNative* Vtable_SuiView$MenuNative_init(Vtable_SuiView$MenuNative* pvt);
void SuiView$MenuNative_init_fields(SuiView$MenuNative *self);
void SuiView$MenuNative_init(SuiView$MenuNative *self, void *pOwner);
SuiView$MenuNative * SuiView$MenuNative_new(void *pOwner);
void SuiView$MenuNative_fini(SuiView$MenuNative *self);

void  SuiView$MenuNative$ctor(SuiView$MenuNative *  self);
void  SuiView$MenuNative$dtor(SuiView$MenuNative *  self);
void  SuiView$MenuNative$create(SuiView$MenuNative *  self, SuiView$MenuNativeItem *  root);
extern long long  SuiView$MenuNative$buildNativeMenu(SuiView$MenuNative *  self, SuiView$MenuNativeItem *  root);
void  SuiView$MenuNative$show(SuiView$MenuNative *  self);
extern void  SuiView$MenuNative$showAt(SuiView$MenuNative *  self, int  clientX, int  clientY);
extern void  SuiView$MenuNative$showAtScreenPosition(SuiView$MenuNative *  self, int  screenX, int  screenY);
void  SuiView$MenuNative$showAtMouse(SuiView$MenuNative *  self);
void  SuiView$MenuNative$onDismiss(SuiView$MenuNative *  self);
extern void  SuiView$MenuNative$destroy(SuiView$MenuNative *  self);
bool  SuiView$MenuNative$dispatchCommand(SuiView$MenuNative *  self, SuiView$MenuNativeItem *  item, Sui$Window *  win, int  commandId);

void  SuiView$MenuNative_doCommand(long long  windowId, int  commandId);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
