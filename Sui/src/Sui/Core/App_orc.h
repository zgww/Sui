
typedef struct tagSuiCore$AppEventLoopMessage SuiCore$AppEventLoopMessage;
typedef struct tagVtable_SuiCore$AppEventLoopMessage Vtable_SuiCore$AppEventLoopMessage;
typedef struct tagSuiCore$App SuiCore$App;
typedef struct tagVtable_SuiCore$App Vtable_SuiCore$App;


#ifndef define_struct___SuiCore__App_orc_h__
#define define_struct___SuiCore__App_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__App_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdlib.h>
#include <stdio.h>
#include "../../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiCore__App_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__App_orc_h__
#define __SuiCore__App_orc_h__

//include  importHeadCode
#include "../../Orc/List_orc.h"
#include "../../Orc/Time_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Mutex_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./Window_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./Vec2_orc.h"
#include "./ViewBase_orc.h"
#include "./Node_orc.h"
#include "./Emitter_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./MouseEvent_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./Timer_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$AppEventLoopMessage {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$AppEventLoopMessage _vtable_SuiCore$AppEventLoopMessage;

// class refc:1
struct tagSuiCore$AppEventLoopMessage {
	Object super; 
	
};
Vtable_SuiCore$AppEventLoopMessage* Vtable_SuiCore$AppEventLoopMessage_init(Vtable_SuiCore$AppEventLoopMessage* pvt);
void SuiCore$AppEventLoopMessage_init_fields(SuiCore$AppEventLoopMessage *self);
void SuiCore$AppEventLoopMessage_init(SuiCore$AppEventLoopMessage *self, void *pOwner);
SuiCore$AppEventLoopMessage * SuiCore$AppEventLoopMessage_new(void *pOwner);
void SuiCore$AppEventLoopMessage_fini(SuiCore$AppEventLoopMessage *self);



// 虚表
struct tagVtable_SuiCore$App {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$App _vtable_SuiCore$App;

// class refc:0
struct tagSuiCore$App {
	Object super; 
	Orc$List*  windows ;
	Sui$Window *  (*findWindowById) (SuiCore$App *  self, long long  id);
	void  (*addWindow) (SuiCore$App *  self, Sui$Window *  win);
	void  (*eachWindow) (SuiCore$App *  self, void  (**onWin)(void *  self, Sui$Window *  win));
	void  (*removeWindow) (SuiCore$App *  self, Sui$Window *  win);
	void  (*layoutAndDrawAllWindows) (SuiCore$App *  self);
	void  (*quit) (SuiCore$App *  self);
	bool  _invalidDraw ;
	void  (*invalidDraw) (SuiCore$App *  self);
	void  (*invalidLayout) (SuiCore$App *  self);
	void  (*processDirtyReacts) (SuiCore$App *  self);
	void  (*processRecuDirtyReacts) (SuiCore$App *  self, SuiCore$Node *  n);
	Orc$Mutex*  postMessageMutex ;
	Orc$List*  messageList ;
	void  (*postMessage_toEventLoop_threadSafe) (SuiCore$App *  self, SuiCore$AppEventLoopMessage*  msg);
	SuiCore$AppEventLoopMessage*  (*peekFromMessageList) (SuiCore$AppEventLoopMessage **  __outRef__, SuiCore$App *  self);
	void  (*processMessageList) (SuiCore$App *  self);
	void  (*init) (SuiCore$App *  self);
	void  (*runEventLoop) (SuiCore$App *  self);
};
Vtable_SuiCore$App* Vtable_SuiCore$App_init(Vtable_SuiCore$App* pvt);
void SuiCore$App_init_fields(SuiCore$App *self);
void SuiCore$App_init(SuiCore$App *self, void *pOwner);
SuiCore$App * SuiCore$App_new(void *pOwner);
void SuiCore$App_fini(SuiCore$App *self);

Sui$Window *  SuiCore$App$findWindowById(SuiCore$App *  self, long long  id);
void  SuiCore$App$addWindow(SuiCore$App *  self, Sui$Window *  win);
void  SuiCore$App$eachWindow(SuiCore$App *  self, void  (**onWin)(void *  self, Sui$Window *  win));
void  SuiCore$App$removeWindow(SuiCore$App *  self, Sui$Window *  win);
void  SuiCore$App$layoutAndDrawAllWindows(SuiCore$App *  self);
void  SuiCore$App$quit(SuiCore$App *  self);
void  SuiCore$App$invalidDraw(SuiCore$App *  self);
void  SuiCore$App$invalidLayout(SuiCore$App *  self);
void  SuiCore$App$processDirtyReacts(SuiCore$App *  self);
void  SuiCore$App$processRecuDirtyReacts(SuiCore$App *  self, SuiCore$Node *  n);
void  SuiCore$App$postMessage_toEventLoop_threadSafe(SuiCore$App *  self, SuiCore$AppEventLoopMessage*  msg);
SuiCore$AppEventLoopMessage*  SuiCore$App$peekFromMessageList(SuiCore$AppEventLoopMessage **  __outRef__, SuiCore$App *  self);
void  SuiCore$App$processMessageList(SuiCore$App *  self);
void  SuiCore$App$init(SuiCore$App *  self);
extern void  SuiCore$App$runEventLoop(SuiCore$App *  self);

SuiCore$App*  SuiCore$App_use(SuiCore$App **  __outRef__);
void  SuiCore$App_onDestroyWindow(long long  id);
bool  SuiCore$App_repaintWindowById(long long  id);
void  SuiCore$testApp();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
