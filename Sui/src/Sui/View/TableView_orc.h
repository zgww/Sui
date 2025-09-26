
typedef struct tagSuiView$TableViewColumn SuiView$TableViewColumn;
typedef struct tagVtable_SuiView$TableViewColumn Vtable_SuiView$TableViewColumn;
typedef struct tagSuiView$TableView SuiView$TableView;
typedef struct tagVtable_SuiView$TableView Vtable_SuiView$TableView;


#ifndef define_struct___SuiView__TableView_orc_h__
#define define_struct___SuiView__TableView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__TableView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___SuiView__TableView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__TableView_orc_h__
#define __SuiView__TableView_orc_h__

//include  importHeadCode
#include "../../Orc/List_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "./ViewBuilder_orc.h"
#include "./TextView_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$TableViewColumn {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$TableViewColumn _vtable_SuiView$TableViewColumn;

// class refc:0
struct tagSuiView$TableViewColumn {
	Object super; 
	int  width ;
	Orc$String*  label ;
};
Vtable_SuiView$TableViewColumn* Vtable_SuiView$TableViewColumn_init(Vtable_SuiView$TableViewColumn* pvt);
void SuiView$TableViewColumn_init_fields(SuiView$TableViewColumn *self);
void SuiView$TableViewColumn_init(SuiView$TableViewColumn *self, void *pOwner);
SuiView$TableViewColumn * SuiView$TableViewColumn_new(void *pOwner);
void SuiView$TableViewColumn_fini(SuiView$TableViewColumn *self);


SuiView$TableViewColumn*  SuiView$mkTableViewColumn(SuiView$TableViewColumn **  __outRef__, int  width, Orc$String*  label);

// 虚表
struct tagVtable_SuiView$TableView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiView$TableView _vtable_SuiView$TableView;

// class refc:0
struct tagSuiView$TableView {
	SuiLayout$LayoutLinear super; 
	void  (**renderTh)(void *  self);
	void  (**renderTd)(void *  self, SuiCore$Node *  o, int  row, int  column);
	int  rowHeight ;
	int  rowCount ;
	Orc$List*  columns ;
	void  (*renderHead) (SuiView$TableView *  self);
	void  (*renderBody) (SuiView$TableView *  self);
	void  (*onMouseEvent) (SuiView$TableView *  self, SuiCore$MouseEvent *  e);
	int  hoverRow ;
	int  hoverCol ;
	int  hoverStartX ;
	int  hoverEndX ;
};
Vtable_SuiView$TableView* Vtable_SuiView$TableView_init(Vtable_SuiView$TableView* pvt);
void SuiView$TableView_init_fields(SuiView$TableView *self);
void SuiView$TableView_init(SuiView$TableView *self, void *pOwner);
SuiView$TableView * SuiView$TableView_new(void *pOwner);
void SuiView$TableView_fini(SuiView$TableView *self);

void  SuiView$TableView$react(SuiView$TableView *  self);
void  SuiView$TableView$renderHead(SuiView$TableView *  self);
void  SuiView$TableView$renderBody(SuiView$TableView *  self);
void  SuiView$TableView$draw_self(SuiView$TableView *  self, SuiCore$Canvas *  canvas);
void  SuiView$TableView$onEvent(SuiView$TableView *  self, SuiCore$Event *  e);
void  SuiView$TableView$onMouseEvent(SuiView$TableView *  self, SuiCore$MouseEvent *  e);

SuiView$TableView*  SuiView$mkTableView(SuiView$TableView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
