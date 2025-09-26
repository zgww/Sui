
typedef struct tagSuiCore$Timer SuiCore$Timer;
typedef struct tagVtable_SuiCore$Timer Vtable_SuiCore$Timer;
typedef struct tagSuiCore$TimerMgr SuiCore$TimerMgr;
typedef struct tagVtable_SuiCore$TimerMgr Vtable_SuiCore$TimerMgr;
typedef struct tagSuiCore$AnimStep SuiCore$AnimStep;
typedef struct tagVtable_SuiCore$AnimStep Vtable_SuiCore$AnimStep;
typedef struct tagSuiCore$TimerTestEnt SuiCore$TimerTestEnt;
typedef struct tagVtable_SuiCore$TimerTestEnt Vtable_SuiCore$TimerTestEnt;


#ifndef define_struct___SuiCore__Timer_orc_h__
#define define_struct___SuiCore__Timer_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Timer_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdint.h>
#include <stdio.h>
#include "../../../UrgcDll/urgc_api.h"




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Timer_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Timer_orc_h__
#define __SuiCore__Timer_orc_h__

//include  importHeadCode
#include "../../Orc/List_orc.h"
#include "../../Orc/Time_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Thread_orc.h"
#include "../../Orc/Mutex_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$Timer {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Timer _vtable_SuiCore$Timer;

// class refc:0
struct tagSuiCore$Timer {
	Object super; 
	void  (**runFunc)(void *  self);
	bool  alive ;
	bool  isInterval ;
	int  intervalMs ;
	int  remainMs ;
	Orc$String*  name ;
	void  (*restart) (SuiCore$Timer *  self);
	void  (*start) (SuiCore$Timer *  self);
	void  (*cancel) (SuiCore$Timer *  self);
	void  (*fire) (SuiCore$Timer *  self);
	bool  (*onTick) (SuiCore$Timer *  self, int  dtMs);
};
Vtable_SuiCore$Timer* Vtable_SuiCore$Timer_init(Vtable_SuiCore$Timer* pvt);
void SuiCore$Timer_init_fields(SuiCore$Timer *self);
void SuiCore$Timer_init(SuiCore$Timer *self, void *pOwner);
SuiCore$Timer * SuiCore$Timer_new(void *pOwner);
void SuiCore$Timer_fini(SuiCore$Timer *self);

void  SuiCore$Timer$dtor(SuiCore$Timer *  self);
void  SuiCore$Timer$restart(SuiCore$Timer *  self);
void  SuiCore$Timer$start(SuiCore$Timer *  self);
void  SuiCore$Timer$cancel(SuiCore$Timer *  self);
void  SuiCore$Timer$fire(SuiCore$Timer *  self);
bool  SuiCore$Timer$onTick(SuiCore$Timer *  self, int  dtMs);


// 虚表
struct tagVtable_SuiCore$TimerMgr {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$TimerMgr _vtable_SuiCore$TimerMgr;

// class refc:0
struct tagSuiCore$TimerMgr {
	Object super; 
	Orc$List*  items ;
	Orc$Mutex*  itemsMutex ;
	Orc$List*  fireings ;
	Orc$Mutex*  fireingsMutex ;
	void  (*addItemOnce) (SuiCore$TimerMgr *  self, SuiCore$Timer *  timer);
	void  (*addItem) (SuiCore$TimerMgr *  self, SuiCore$Timer *  timer);
	void  (*fire) (SuiCore$TimerMgr *  self);
	void  (*tick) (SuiCore$TimerMgr *  self, int  dtMs);
	void  (*clearDeadTimers) (SuiCore$TimerMgr *  self);
	void  (*startThreadTick) (SuiCore$TimerMgr *  self);
	void  (*startThreadTickAndFire) (SuiCore$TimerMgr *  self);
};
Vtable_SuiCore$TimerMgr* Vtable_SuiCore$TimerMgr_init(Vtable_SuiCore$TimerMgr* pvt);
void SuiCore$TimerMgr_init_fields(SuiCore$TimerMgr *self);
void SuiCore$TimerMgr_init(SuiCore$TimerMgr *self, void *pOwner);
SuiCore$TimerMgr * SuiCore$TimerMgr_new(void *pOwner);
void SuiCore$TimerMgr_fini(SuiCore$TimerMgr *self);

void  SuiCore$TimerMgr$dtor(SuiCore$TimerMgr *  self);
void  SuiCore$TimerMgr$addItemOnce(SuiCore$TimerMgr *  self, SuiCore$Timer *  timer);
void  SuiCore$TimerMgr$addItem(SuiCore$TimerMgr *  self, SuiCore$Timer *  timer);
void  SuiCore$TimerMgr$fire(SuiCore$TimerMgr *  self);
void  SuiCore$TimerMgr$tick(SuiCore$TimerMgr *  self, int  dtMs);
void  SuiCore$TimerMgr$clearDeadTimers(SuiCore$TimerMgr *  self);
void  SuiCore$TimerMgr$startThreadTick(SuiCore$TimerMgr *  self);
void  SuiCore$TimerMgr$startThreadTickAndFire(SuiCore$TimerMgr *  self);

SuiCore$TimerMgr*  SuiCore$insTimerMgr(SuiCore$TimerMgr **  __outRef__);
SuiCore$Timer*  SuiCore$mkTimerTimeout(SuiCore$Timer **  __outRef__, void  (**fn)(void *  self), int  milliSecond);
SuiCore$Timer*  SuiCore$mkTimerInterval(SuiCore$Timer **  __outRef__, void  (**fn)(void *  self), int  milliSecond);
SuiCore$Timer*  SuiCore$mkTimerInterval_noStart(SuiCore$Timer **  __outRef__, void  (**fn)(void *  self), int  milliSecond);
Orc$List *  SuiCore$gocAnimationFrameList();
void  SuiCore$requestAnimationFrame(bool  (**fn)(void *  self));
void  SuiCore$tickAnimationFrames();

// 虚表
struct tagVtable_SuiCore$AnimStep {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$AnimStep _vtable_SuiCore$AnimStep;

// class refc:0
struct tagSuiCore$AnimStep {
	Object super; 
	void  (**update)(void *  self);
	bool  running ;
	int  runningCnt ;
	long long  elapsedMs ;
	long long  prevElapsedMs ;
	long long  prevMs ;
	void  (*start) (SuiCore$AnimStep *  self, void  (**fn)(void *  self));
	float  (*nextByMs) (SuiCore$AnimStep *  self, float  x, float  to, float  ms);
	float  (*next) (SuiCore$AnimStep *  self, float  x, float  to, float  absStep);
	void  (*tick) (SuiCore$AnimStep *  self);
	void  (*_start) (SuiCore$AnimStep *  self);
	void  (*cancel) (SuiCore$AnimStep *  self);
};
Vtable_SuiCore$AnimStep* Vtable_SuiCore$AnimStep_init(Vtable_SuiCore$AnimStep* pvt);
void SuiCore$AnimStep_init_fields(SuiCore$AnimStep *self);
void SuiCore$AnimStep_init(SuiCore$AnimStep *self, void *pOwner);
SuiCore$AnimStep * SuiCore$AnimStep_new(void *pOwner);
void SuiCore$AnimStep_fini(SuiCore$AnimStep *self);

void  SuiCore$AnimStep$start(SuiCore$AnimStep *  self, void  (**fn)(void *  self));
float  SuiCore$AnimStep$nextByMs(SuiCore$AnimStep *  self, float  x, float  to, float  ms);
float  SuiCore$AnimStep$next(SuiCore$AnimStep *  self, float  x, float  to, float  absStep);
void  SuiCore$AnimStep$tick(SuiCore$AnimStep *  self);
void  SuiCore$AnimStep$_start(SuiCore$AnimStep *  self);
void  SuiCore$AnimStep$cancel(SuiCore$AnimStep *  self);


// 虚表
struct tagVtable_SuiCore$TimerTestEnt {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$TimerTestEnt _vtable_SuiCore$TimerTestEnt;

// class refc:1
struct tagSuiCore$TimerTestEnt {
	Object super; 
	int  i ;
};
Vtable_SuiCore$TimerTestEnt* Vtable_SuiCore$TimerTestEnt_init(Vtable_SuiCore$TimerTestEnt* pvt);
void SuiCore$TimerTestEnt_init_fields(SuiCore$TimerTestEnt *self);
void SuiCore$TimerTestEnt_init(SuiCore$TimerTestEnt *self, void *pOwner);
SuiCore$TimerTestEnt * SuiCore$TimerTestEnt_new(void *pOwner);
void SuiCore$TimerTestEnt_fini(SuiCore$TimerTestEnt *self);

void  SuiCore$TimerTestEnt$dtor(SuiCore$TimerTestEnt *  self);

void  SuiCore$testTimer();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
