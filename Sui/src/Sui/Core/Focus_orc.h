
typedef struct tagSuiCore$FocusEvent SuiCore$FocusEvent;
typedef struct tagVtable_SuiCore$FocusEvent Vtable_SuiCore$FocusEvent;
typedef struct tagSuiCore$Focus SuiCore$Focus;
typedef struct tagVtable_SuiCore$Focus Vtable_SuiCore$Focus;


#ifndef define_struct___SuiCore__Focus_orc_h__
#define define_struct___SuiCore__Focus_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Focus_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Focus_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Focus_orc_h__
#define __SuiCore__Focus_orc_h__

//include  importHeadCode
#include "./Node_orc.h"
#include "./Event_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiCore$FocusEvent {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_SuiCore$FocusEvent _vtable_SuiCore$FocusEvent;

// class refc:0
struct tagSuiCore$FocusEvent {
	SuiCore$Event super; 
	bool  isFocus ;
	bool  isBlur ;
	SuiCore$Node*  source ;
	void  (*init) (SuiCore$FocusEvent *  self, SuiCore$Node *  source, bool  b);
};
Vtable_SuiCore$FocusEvent* Vtable_SuiCore$FocusEvent_init(Vtable_SuiCore$FocusEvent* pvt);
void SuiCore$FocusEvent_init_fields(SuiCore$FocusEvent *self);
void SuiCore$FocusEvent_init(SuiCore$FocusEvent *self, void *pOwner);
SuiCore$FocusEvent * SuiCore$FocusEvent_new(void *pOwner);
void SuiCore$FocusEvent_fini(SuiCore$FocusEvent *self);

void  SuiCore$FocusEvent$init(SuiCore$FocusEvent *  self, SuiCore$Node *  source, bool  b);


// 虚表
struct tagVtable_SuiCore$Focus {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$Focus _vtable_SuiCore$Focus;

// class refc:0
struct tagSuiCore$Focus {
	Object super; 
	SuiCore$Node*  focusNode ;
	void  (*focus) (SuiCore$Focus *  self, SuiCore$Node *  node);
	void  (*blurNode) (SuiCore$Focus *  self, SuiCore$Node *  n);
	void  (*blur) (SuiCore$Focus *  self);
	SuiCore$Node *  (*getFocusNode) (SuiCore$Focus *  self);
	bool  (*isFocus) (SuiCore$Focus *  self, SuiCore$Node *  node);
	bool  (*hasFocus) (SuiCore$Focus *  self);
};
Vtable_SuiCore$Focus* Vtable_SuiCore$Focus_init(Vtable_SuiCore$Focus* pvt);
void SuiCore$Focus_init_fields(SuiCore$Focus *self);
void SuiCore$Focus_init(SuiCore$Focus *self, void *pOwner);
SuiCore$Focus * SuiCore$Focus_new(void *pOwner);
void SuiCore$Focus_fini(SuiCore$Focus *self);

void  SuiCore$Focus$focus(SuiCore$Focus *  self, SuiCore$Node *  node);
void  SuiCore$Focus$blurNode(SuiCore$Focus *  self, SuiCore$Node *  n);
void  SuiCore$Focus$blur(SuiCore$Focus *  self);
SuiCore$Node *  SuiCore$Focus$getFocusNode(SuiCore$Focus *  self);
bool  SuiCore$Focus$isFocus(SuiCore$Focus *  self, SuiCore$Node *  node);
bool  SuiCore$Focus$hasFocus(SuiCore$Focus *  self);

SuiCore$Focus *  SuiCore$insFocus();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
