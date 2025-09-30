
typedef struct tagSuiCore$ViewEvent SuiCore$ViewEvent;
typedef struct tagVtable_SuiCore$ViewEvent Vtable_SuiCore$ViewEvent;
typedef struct tagSuiCore$ClickRecord SuiCore$ClickRecord;
typedef struct tagSuiCore$MouseEvent SuiCore$MouseEvent;
typedef struct tagVtable_SuiCore$MouseEvent Vtable_SuiCore$MouseEvent;
typedef struct tagSuiCore$MouseEnterEvent SuiCore$MouseEnterEvent;
typedef struct tagVtable_SuiCore$MouseEnterEvent Vtable_SuiCore$MouseEnterEvent;
typedef struct tagSuiCore$MouseLeaveEvent SuiCore$MouseLeaveEvent;
typedef struct tagVtable_SuiCore$MouseLeaveEvent Vtable_SuiCore$MouseLeaveEvent;
typedef struct tagSuiCore$WheelEvent SuiCore$WheelEvent;
typedef struct tagVtable_SuiCore$WheelEvent Vtable_SuiCore$WheelEvent;
typedef struct tagSuiCore$MouseEventListener SuiCore$MouseEventListener;
typedef struct tagVtable_SuiCore$MouseEventListener Vtable_SuiCore$MouseEventListener;
typedef struct tagSuiCore$HoverSentive SuiCore$HoverSentive;
typedef struct tagVtable_SuiCore$HoverSentive Vtable_SuiCore$HoverSentive;


#ifndef define_struct___SuiCore__MouseEvent_orc_h__
#define define_struct___SuiCore__MouseEvent_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__MouseEvent_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__MouseEvent_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiCore$ClickRecord {
	int  clientX ;
	int  clientY ;
	long long  clickUnixMs ;
	int  button ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__MouseEvent_orc_h__
#define __SuiCore__MouseEvent_orc_h__

//include  importHeadCode
#include "./Event_orc.h"
#include "./Emitter_orc.h"
#include "./Window_orc.h"
#include "./Node_orc.h"
#include "./Cursor_orc.h"
#include "./Vec2_orc.h"
#include "./ViewBase_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Time_orc.h"
#include "../../Orc/String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$ViewEvent {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_SuiCore$ViewEvent _vtable_SuiCore$ViewEvent;

// class refc:0
struct tagSuiCore$ViewEvent {
	SuiCore$Event super; 
	SuiCore$Node*  target ;
	SuiCore$Node*  currentTarget ;
	bool  isCapture ;
	bool  (*isBubble) (SuiCore$ViewEvent *  self);
};
Vtable_SuiCore$ViewEvent* Vtable_SuiCore$ViewEvent_init(Vtable_SuiCore$ViewEvent* pvt);
void SuiCore$ViewEvent_init_fields(SuiCore$ViewEvent *self);
void SuiCore$ViewEvent_init(SuiCore$ViewEvent *self, void *pOwner);
SuiCore$ViewEvent * SuiCore$ViewEvent_new(void *pOwner);
void SuiCore$ViewEvent_fini(SuiCore$ViewEvent *self);

bool  SuiCore$ViewEvent$isBubble(SuiCore$ViewEvent *  self);



//结构体元数据获取即初始化
MetaStruct* SuiCore$ClickRecord_getOrInitMetaStruct();


// 虚表
struct tagVtable_SuiCore$MouseEvent {
	Vtable_SuiCore$ViewEvent super;
};
//虚表实例
extern Vtable_SuiCore$MouseEvent _vtable_SuiCore$MouseEvent;

// class refc:0
struct tagSuiCore$MouseEvent {
	SuiCore$ViewEvent super; 
	int  clientX ;
	int  clientY ;
	Sui$Window*  window ;
	SuiCore$Vec2 ndcPos ;
	int  button ;
	int  mouseDownClientX ;
	int  mouseDownClientY ;
	bool  isMouseDown ;
	bool  isMouseUp ;
	bool  isMouseMove ;
	bool  isWheel ;
	bool  ctrl ;
	bool  shift ;
	bool  alt ;
	bool  isDblClick ;
	bool  (*isClick) (SuiCore$MouseEvent *  self);
	bool  (*isClickInBubble) (SuiCore$MouseEvent *  self);
	bool  (*isDblClickInBubble) (SuiCore$MouseEvent *  self);
	Orc$String*  (*toString) (Orc$String **  __outRef__, SuiCore$MouseEvent *  self);
};
Vtable_SuiCore$MouseEvent* Vtable_SuiCore$MouseEvent_init(Vtable_SuiCore$MouseEvent* pvt);
void SuiCore$MouseEvent_init_fields(SuiCore$MouseEvent *self);
void SuiCore$MouseEvent_init(SuiCore$MouseEvent *self, void *pOwner);
SuiCore$MouseEvent * SuiCore$MouseEvent_new(void *pOwner);
void SuiCore$MouseEvent_fini(SuiCore$MouseEvent *self);

bool  SuiCore$MouseEvent$isClick(SuiCore$MouseEvent *  self);
bool  SuiCore$MouseEvent$isClickInBubble(SuiCore$MouseEvent *  self);
bool  SuiCore$MouseEvent$isDblClickInBubble(SuiCore$MouseEvent *  self);
Orc$String*  SuiCore$MouseEvent$toString(Orc$String **  __outRef__, SuiCore$MouseEvent *  self);


// 虚表
struct tagVtable_SuiCore$MouseEnterEvent {
	Vtable_SuiCore$MouseEvent super;
};
//虚表实例
extern Vtable_SuiCore$MouseEnterEvent _vtable_SuiCore$MouseEnterEvent;

// class refc:0
struct tagSuiCore$MouseEnterEvent {
	SuiCore$MouseEvent super; 
	
};
Vtable_SuiCore$MouseEnterEvent* Vtable_SuiCore$MouseEnterEvent_init(Vtable_SuiCore$MouseEnterEvent* pvt);
void SuiCore$MouseEnterEvent_init_fields(SuiCore$MouseEnterEvent *self);
void SuiCore$MouseEnterEvent_init(SuiCore$MouseEnterEvent *self, void *pOwner);
SuiCore$MouseEnterEvent * SuiCore$MouseEnterEvent_new(void *pOwner);
void SuiCore$MouseEnterEvent_fini(SuiCore$MouseEnterEvent *self);



// 虚表
struct tagVtable_SuiCore$MouseLeaveEvent {
	Vtable_SuiCore$MouseEvent super;
};
//虚表实例
extern Vtable_SuiCore$MouseLeaveEvent _vtable_SuiCore$MouseLeaveEvent;

// class refc:0
struct tagSuiCore$MouseLeaveEvent {
	SuiCore$MouseEvent super; 
	
};
Vtable_SuiCore$MouseLeaveEvent* Vtable_SuiCore$MouseLeaveEvent_init(Vtable_SuiCore$MouseLeaveEvent* pvt);
void SuiCore$MouseLeaveEvent_init_fields(SuiCore$MouseLeaveEvent *self);
void SuiCore$MouseLeaveEvent_init(SuiCore$MouseLeaveEvent *self, void *pOwner);
SuiCore$MouseLeaveEvent * SuiCore$MouseLeaveEvent_new(void *pOwner);
void SuiCore$MouseLeaveEvent_fini(SuiCore$MouseLeaveEvent *self);



// 虚表
struct tagVtable_SuiCore$WheelEvent {
	Vtable_SuiCore$MouseEvent super;
};
//虚表实例
extern Vtable_SuiCore$WheelEvent _vtable_SuiCore$WheelEvent;

// class refc:0
struct tagSuiCore$WheelEvent {
	SuiCore$MouseEvent super; 
	int  deltaY ;
	int  deltaX ;
};
Vtable_SuiCore$WheelEvent* Vtable_SuiCore$WheelEvent_init(Vtable_SuiCore$WheelEvent* pvt);
void SuiCore$WheelEvent_init_fields(SuiCore$WheelEvent *self);
void SuiCore$WheelEvent_init(SuiCore$WheelEvent *self, void *pOwner);
SuiCore$WheelEvent * SuiCore$WheelEvent_new(void *pOwner);
void SuiCore$WheelEvent_fini(SuiCore$WheelEvent *self);



// 虚表
struct tagVtable_SuiCore$MouseEventListener {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$MouseEventListener _vtable_SuiCore$MouseEventListener;

// class refc:1
struct tagSuiCore$MouseEventListener {
	Object super; 
	void  (*onEvent) (SuiCore$MouseEventListener *  self, SuiCore$MouseEvent *  ev);
};
Vtable_SuiCore$MouseEventListener* Vtable_SuiCore$MouseEventListener_init(Vtable_SuiCore$MouseEventListener* pvt);
void SuiCore$MouseEventListener_init_fields(SuiCore$MouseEventListener *self);
void SuiCore$MouseEventListener_init(SuiCore$MouseEventListener *self, void *pOwner);
SuiCore$MouseEventListener * SuiCore$MouseEventListener_new(void *pOwner);
void SuiCore$MouseEventListener_fini(SuiCore$MouseEventListener *self);

void  SuiCore$MouseEventListener$onEvent(SuiCore$MouseEventListener *  self, SuiCore$MouseEvent *  ev);

extern int  SuiCore$MouseEvent_clickOffsetThreshold;

// 虚表
struct tagVtable_SuiCore$HoverSentive {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$HoverSentive _vtable_SuiCore$HoverSentive;

// class refc:0
struct tagSuiCore$HoverSentive {
	Object super; 
	Orc$List*  hoverings ;
	void  (*clear) (SuiCore$HoverSentive *  self);
	void  (*setHover) (SuiCore$HoverSentive *  self, SuiCore$Node *  node, bool  hover);
	void  (*onmousemove) (SuiCore$HoverSentive *  self, SuiCore$MouseEvent *  e, SuiCore$ViewBase *  hitTestView);
	void  (*onmouseleave) (SuiCore$HoverSentive *  self, Sui$Window *  win);
};
Vtable_SuiCore$HoverSentive* Vtable_SuiCore$HoverSentive_init(Vtable_SuiCore$HoverSentive* pvt);
void SuiCore$HoverSentive_init_fields(SuiCore$HoverSentive *self);
void SuiCore$HoverSentive_init(SuiCore$HoverSentive *self, void *pOwner);
SuiCore$HoverSentive * SuiCore$HoverSentive_new(void *pOwner);
void SuiCore$HoverSentive_fini(SuiCore$HoverSentive *self);

void  SuiCore$HoverSentive$clear(SuiCore$HoverSentive *  self);
void  SuiCore$HoverSentive$setHover(SuiCore$HoverSentive *  self, SuiCore$Node *  node, bool  hover);
void  SuiCore$HoverSentive$onmousemove(SuiCore$HoverSentive *  self, SuiCore$MouseEvent *  e, SuiCore$ViewBase *  hitTestView);
void  SuiCore$HoverSentive$onmouseleave(SuiCore$HoverSentive *  self, Sui$Window *  win);

SuiCore$HoverSentive *  SuiCore$sinsHoverSentive();
void  SuiCore$preprocessMouseEvent(SuiCore$MouseEvent *  ev);
void  SuiCore$propagateViewEvent(SuiCore$ViewBase *  view, SuiCore$ViewEvent *  ev);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
