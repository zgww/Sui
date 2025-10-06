
typedef struct tagSuiView$Drag SuiView$Drag;
typedef struct tagVtable_SuiView$Drag Vtable_SuiView$Drag;


#ifndef define_struct___SuiView__Drag_orc_h__
#define define_struct___SuiView__Drag_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__Drag_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiView__Drag_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__Drag_orc_h__
#define __SuiView__Drag_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/Emitter_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Cursor_orc.h"
#include "../../Orc/String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$Drag {
	Vtable_SuiCore$Listener super;
};
//虚表实例
extern Vtable_SuiView$Drag _vtable_SuiView$Drag;

// class refc:0
struct tagSuiView$Drag {
	SuiCore$Listener super; 
	void  (**onDrag)(void *  self, SuiView$Drag *  d);
	SuiCore$Vec2 currentClientPos ;
	SuiCore$Vec2 downClientPos ;
	SuiCore$Vec2 deltaPos ;
	Orc$String*  cursor ;
	bool  isDragChecking ;
	bool  isDragEnd ;
	bool  isDragStart ;
	bool  isDragging ;
	float  moveThreshold ;
	Object*  data ;
	SuiCore$MouseEvent *  mouseEvent ;
	int  mouseDownButton ;
	void  (*setStatus) (SuiView$Drag *  self, const char *  status);
	void  (*onMouseDown_byPrefer) (SuiView$Drag *  self, SuiCore$Event *  e, int  button, bool  cap, bool  bubble);
	void  (*onMouseDownIf) (SuiView$Drag *  self, SuiCore$Event *  e);
	void  (*onMouseDown) (SuiView$Drag *  self, SuiCore$Event *  e);
};
Vtable_SuiView$Drag* Vtable_SuiView$Drag_init(Vtable_SuiView$Drag* pvt);
void SuiView$Drag_init_fields(SuiView$Drag *self);
void SuiView$Drag_init(SuiView$Drag *self, void *pOwner);
SuiView$Drag * SuiView$Drag_new(void *pOwner);
void SuiView$Drag_fini(SuiView$Drag *self);

void  SuiView$Drag$dtor(SuiView$Drag *  self);
void  SuiView$Drag$setStatus(SuiView$Drag *  self, const char *  status);
void  SuiView$Drag$onMouseDown_byPrefer(SuiView$Drag *  self, SuiCore$Event *  e, int  button, bool  cap, bool  bubble);
void  SuiView$Drag$onMouseDownIf(SuiView$Drag *  self, SuiCore$Event *  e);
void  SuiView$Drag$onMouseDown(SuiView$Drag *  self, SuiCore$Event *  e);
void  SuiView$Drag$onListenerEvent(SuiView$Drag *  self, SuiCore$Event *  ev);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
