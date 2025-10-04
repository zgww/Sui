
typedef struct tagSuiView$Range SuiView$Range;
typedef struct tagSuiView$Selection SuiView$Selection;
typedef struct tagVtable_SuiView$Selection Vtable_SuiView$Selection;
typedef struct tagSuiView$Caret SuiView$Caret;
typedef struct tagVtable_SuiView$Caret Vtable_SuiView$Caret;
typedef struct tagSuiView$EditText SuiView$EditText;
typedef struct tagVtable_SuiView$EditText Vtable_SuiView$EditText;


#ifndef define_struct___SuiView__EditText_orc_h__
#define define_struct___SuiView__EditText_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__EditText_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__EditText_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiView$Range {
	int  start ;
	int  end ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__EditText_orc_h__
#define __SuiView__EditText_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Timer_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/KeyEvent_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Focus_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/Mouse_orc.h"
#include "../Core/Clipboard_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "./ViewBuilder_orc.h"
#include "../../SuiDesigner/Theme_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* SuiView$Range_getOrInitMetaStruct();

SuiView$Range SuiView$mkRange(int  start, int  end);

// 虚表
struct tagVtable_SuiView$Selection {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$Selection _vtable_SuiView$Selection;

// class refc:0
struct tagSuiView$Selection {
	Object super; 
	int  start ;
	int  end ;
	Orc$String*  (**get_value)(Orc$String **  __outRef__, void *  self);
	void  (**set_value)(void *  self, const char *  string);
	Orc$String*  (*get_range_value) (Orc$String **  __outRef__, SuiView$Selection *  self);
	bool  (*is_collapse) (SuiView$Selection *  self);
	bool  (*is_range) (SuiView$Selection *  self);
	SuiView$Range (*get_asc_range) (SuiView$Selection *  self);
	int  (*clamp_pos) (SuiView$Selection *  self, int  pos);
	void  (*set_collapse_pos) (SuiView$Selection *  self, int  pos);
	void  (*set_start) (SuiView$Selection *  self, int  pos);
	void  (*set_end) (SuiView$Selection *  self, int  pos);
	void  (*move_delta) (SuiView$Selection *  self, int  delta, bool  shift);
	Orc$String*  (*backspace) (Orc$String **  __outRef__, SuiView$Selection *  self);
	Orc$String*  (*del_range) (Orc$String **  __outRef__, SuiView$Selection *  self);
	Orc$String*  (*delete_act) (Orc$String **  __outRef__, SuiView$Selection *  self);
	Orc$String*  (*insert) (Orc$String **  __outRef__, SuiView$Selection *  self, const char *  text);
};
Vtable_SuiView$Selection* Vtable_SuiView$Selection_init(Vtable_SuiView$Selection* pvt);
void SuiView$Selection_init_fields(SuiView$Selection *self);
void SuiView$Selection_init(SuiView$Selection *self, void *pOwner);
SuiView$Selection * SuiView$Selection_new(void *pOwner);
void SuiView$Selection_fini(SuiView$Selection *self);

Orc$String*  SuiView$Selection$get_range_value(Orc$String **  __outRef__, SuiView$Selection *  self);
bool  SuiView$Selection$is_collapse(SuiView$Selection *  self);
bool  SuiView$Selection$is_range(SuiView$Selection *  self);
SuiView$Range SuiView$Selection$get_asc_range(SuiView$Selection *  self);
int  SuiView$Selection$clamp_pos(SuiView$Selection *  self, int  pos);
void  SuiView$Selection$set_collapse_pos(SuiView$Selection *  self, int  pos);
void  SuiView$Selection$set_start(SuiView$Selection *  self, int  pos);
void  SuiView$Selection$set_end(SuiView$Selection *  self, int  pos);
void  SuiView$Selection$move_delta(SuiView$Selection *  self, int  delta, bool  shift);
Orc$String*  SuiView$Selection$backspace(Orc$String **  __outRef__, SuiView$Selection *  self);
Orc$String*  SuiView$Selection$del_range(Orc$String **  __outRef__, SuiView$Selection *  self);
Orc$String*  SuiView$Selection$delete_act(Orc$String **  __outRef__, SuiView$Selection *  self);
Orc$String*  SuiView$Selection$insert(Orc$String **  __outRef__, SuiView$Selection *  self, const char *  text);


// 虚表
struct tagVtable_SuiView$Caret {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$Caret _vtable_SuiView$Caret;

// class refc:0
struct tagSuiView$Caret {
	Object super; 
	bool  show ;
	SuiCore$Timer*  blink_timer ;
	SuiCore$ViewBase*  view ;
	void  (**cb_notify)(void *  self, SuiView$Caret *  ins);
	bool  (*isBlinking) (SuiView$Caret *  self);
	void  (*setShow) (SuiView$Caret *  self, bool  _show);
	void  (*blink) (SuiView$Caret *  self);
	void  (*start) (SuiView$Caret *  self);
	void  (*stop) (SuiView$Caret *  self);
	void  (*restart) (SuiView$Caret *  self);
};
Vtable_SuiView$Caret* Vtable_SuiView$Caret_init(Vtable_SuiView$Caret* pvt);
void SuiView$Caret_init_fields(SuiView$Caret *self);
void SuiView$Caret_init(SuiView$Caret *self, void *pOwner);
SuiView$Caret * SuiView$Caret_new(void *pOwner);
void SuiView$Caret_fini(SuiView$Caret *self);

void  SuiView$Caret$ctor(SuiView$Caret *  self);
bool  SuiView$Caret$isBlinking(SuiView$Caret *  self);
void  SuiView$Caret$setShow(SuiView$Caret *  self, bool  _show);
void  SuiView$Caret$blink(SuiView$Caret *  self);
void  SuiView$Caret$start(SuiView$Caret *  self);
void  SuiView$Caret$stop(SuiView$Caret *  self);
void  SuiView$Caret$restart(SuiView$Caret *  self);


// 虚表
struct tagVtable_SuiView$EditText {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$EditText _vtable_SuiView$EditText;

// class refc:0
struct tagSuiView$EditText {
	SuiCore$View super; 
	Orc$String*  value ;
	int  font_size ;
	Orc$String*  font_face ;
	int  color ;
	int  caret_color ;
	int  font_weight ;
	Orc$String*  placeholder ;
	int  placeholder_color ;
	void  (**onchanged)(void *  self, Orc$String *  value);
	int  draw_offset ;
	int  _caret_x ;
	SuiView$Selection*  selection ;
	SuiCore$Timer*  drag_timer ;
	SuiView$Caret*  caret ;
	SuiCore$TextEditingEvent*  text_editing ;
	void  (*setValue_notInFocus) (SuiView$EditText *  self, Orc$String *  v);
	void  (*setValue) (SuiView$EditText *  self, Orc$String *  v);
	Orc$String *  (*getValue) (SuiView$EditText *  self);
	void  (*setFont_size) (SuiView$EditText *  self, int  v);
	int  (*getFont_size) (SuiView$EditText *  self);
	void  (*setFont_face) (SuiView$EditText *  self, Orc$String *  v);
	Orc$String *  (*getFont_face) (SuiView$EditText *  self);
	void  (*setColor) (SuiView$EditText *  self, int  v);
	int  (*getColor) (SuiView$EditText *  self);
	void  (*setCaret_color) (SuiView$EditText *  self, int  v);
	int  (*getCaret_color) (SuiView$EditText *  self);
	void  (*setFont_weight) (SuiView$EditText *  self, int  v);
	int  (*getFont_weight) (SuiView$EditText *  self);
	void  (*setPlaceholder) (SuiView$EditText *  self, Orc$String *  v);
	Orc$String *  (*getPlaceholder) (SuiView$EditText *  self);
	void  (*setPlaceholder_color) (SuiView$EditText *  self, int  v);
	int  (*getPlaceholder_color) (SuiView$EditText *  self);
	void  (**onValueChanged)(void *  self, SuiView$EditText *  et);
	void  (*notify_changed) (SuiView$EditText *  self, bool  by_user_event);
	void  (*set_value) (SuiView$EditText *  self, Orc$String*  nvalue, bool  by_user_event);
	SuiCore$Timer *  (*gocDragTimer) (SuiView$EditText *  self);
	void  (*on_window_focus_event) (SuiView$EditText *  self, SuiCore$WindowFocusEvent *  e);
	void  (*on_key_event) (SuiView$EditText *  self, SuiCore$KeyEvent *  e);
	void  (*on_focus_event) (SuiView$EditText *  self, SuiCore$FocusEvent *  evt);
	void  (*on_editing_event) (SuiView$EditText *  self, SuiCore$TextEditingEvent *  evt);
	void  (*on_input_event) (SuiView$EditText *  self, SuiCore$TextInputEvent *  e);
	void  (*blur) (SuiView$EditText *  self);
	SuiCore$Canvas *  _canvas ;
	float  (*get_x_of_position) (SuiView$EditText *  self, int  pos);
	void  (*_update_text_input_rect) (SuiView$EditText *  self);
	void  (*update_draw_offset_by_keydown_move_with_default) (SuiView$EditText *  self);
	void  (*update_draw_offset_by_keydown_move) (SuiView$EditText *  self, float  target_caret_ratio, bool  force);
	int  (*clamp_draw_offset) (SuiView$EditText *  self, int  offset);
	int  (*get_char_position_by_client_x) (SuiView$EditText *  self, int  client_x);
	void  (*on_mouse_event) (SuiView$EditText *  self, SuiCore$MouseEvent *  e);
	void  (*on_mouse_down) (SuiView$EditText *  self, SuiCore$MouseEvent *  e);
	void  (*on_rootView_mouse_up) (SuiView$EditText *  self, SuiCore$MouseEvent *  e);
	void  (*on_rootView_mouse_move) (SuiView$EditText *  self, SuiCore$MouseEvent *  e);
	void  (*_update_drag) (SuiView$EditText *  self);
	void  (*reset_text_editing) (SuiView$EditText *  self);
	void  (*draw_editing) (SuiView$EditText *  self, SuiCore$Canvas *  canvas, int  h);
	void  (*set_text_editing) (SuiView$EditText *  self, SuiCore$TextEditingEvent *  evt);
	void  (*selectAll) (SuiView$EditText *  self);
};
Vtable_SuiView$EditText* Vtable_SuiView$EditText_init(Vtable_SuiView$EditText* pvt);
void SuiView$EditText_init_fields(SuiView$EditText *self);
void SuiView$EditText_init(SuiView$EditText *self, void *pOwner);
SuiView$EditText * SuiView$EditText_new(void *pOwner);
void SuiView$EditText_fini(SuiView$EditText *self);

void  SuiView$EditText$layoutContent(SuiView$EditText *  self, SuiCore$Frame *  ctx);
void  SuiView$EditText$setValue_notInFocus(SuiView$EditText *  self, Orc$String *  v);
void  SuiView$EditText$setValue(SuiView$EditText *  self, Orc$String *  v);
Orc$String *  SuiView$EditText$getValue(SuiView$EditText *  self);
void  SuiView$EditText$setFont_size(SuiView$EditText *  self, int  v);
int  SuiView$EditText$getFont_size(SuiView$EditText *  self);
void  SuiView$EditText$setFont_face(SuiView$EditText *  self, Orc$String *  v);
Orc$String *  SuiView$EditText$getFont_face(SuiView$EditText *  self);
void  SuiView$EditText$setColor(SuiView$EditText *  self, int  v);
int  SuiView$EditText$getColor(SuiView$EditText *  self);
void  SuiView$EditText$setCaret_color(SuiView$EditText *  self, int  v);
int  SuiView$EditText$getCaret_color(SuiView$EditText *  self);
void  SuiView$EditText$setFont_weight(SuiView$EditText *  self, int  v);
int  SuiView$EditText$getFont_weight(SuiView$EditText *  self);
void  SuiView$EditText$setPlaceholder(SuiView$EditText *  self, Orc$String *  v);
Orc$String *  SuiView$EditText$getPlaceholder(SuiView$EditText *  self);
void  SuiView$EditText$setPlaceholder_color(SuiView$EditText *  self, int  v);
int  SuiView$EditText$getPlaceholder_color(SuiView$EditText *  self);
void  SuiView$EditText$notify_changed(SuiView$EditText *  self, bool  by_user_event);
void  SuiView$EditText$set_value(SuiView$EditText *  self, Orc$String*  nvalue, bool  by_user_event);
SuiCore$Timer *  SuiView$EditText$gocDragTimer(SuiView$EditText *  self);
void  SuiView$EditText$ctor(SuiView$EditText *  self);
void  SuiView$EditText$react(SuiView$EditText *  self);
void  SuiView$EditText$draw_self(SuiView$EditText *  self, SuiCore$Canvas *  canvas);
void  SuiView$EditText$onEvent(SuiView$EditText *  self, SuiCore$Event *  evt);
void  SuiView$EditText$on_window_focus_event(SuiView$EditText *  self, SuiCore$WindowFocusEvent *  e);
void  SuiView$EditText$on_key_event(SuiView$EditText *  self, SuiCore$KeyEvent *  e);
void  SuiView$EditText$on_focus_event(SuiView$EditText *  self, SuiCore$FocusEvent *  evt);
void  SuiView$EditText$on_editing_event(SuiView$EditText *  self, SuiCore$TextEditingEvent *  evt);
void  SuiView$EditText$on_input_event(SuiView$EditText *  self, SuiCore$TextInputEvent *  e);
void  SuiView$EditText$onUnmounting(SuiView$EditText *  self);
void  SuiView$EditText$blur(SuiView$EditText *  self);
float  SuiView$EditText$get_x_of_position(SuiView$EditText *  self, int  pos);
void  SuiView$EditText$_update_text_input_rect(SuiView$EditText *  self);
void  SuiView$EditText$update_draw_offset_by_keydown_move_with_default(SuiView$EditText *  self);
void  SuiView$EditText$update_draw_offset_by_keydown_move(SuiView$EditText *  self, float  target_caret_ratio, bool  force);
int  SuiView$EditText$clamp_draw_offset(SuiView$EditText *  self, int  offset);
int  SuiView$EditText$get_char_position_by_client_x(SuiView$EditText *  self, int  client_x);
void  SuiView$EditText$on_mouse_event(SuiView$EditText *  self, SuiCore$MouseEvent *  e);
void  SuiView$EditText$on_mouse_down(SuiView$EditText *  self, SuiCore$MouseEvent *  e);
void  SuiView$EditText$onListenerEvent(SuiView$EditText *  self, SuiCore$Event *  e);
void  SuiView$EditText$on_rootView_mouse_up(SuiView$EditText *  self, SuiCore$MouseEvent *  e);
void  SuiView$EditText$on_rootView_mouse_move(SuiView$EditText *  self, SuiCore$MouseEvent *  e);
void  SuiView$EditText$_update_drag(SuiView$EditText *  self);
void  SuiView$EditText$reset_text_editing(SuiView$EditText *  self);
void  SuiView$EditText$draw_editing(SuiView$EditText *  self, SuiCore$Canvas *  canvas, int  h);
void  SuiView$EditText$set_text_editing(SuiView$EditText *  self, SuiCore$TextEditingEvent *  evt);
void  SuiView$EditText$selectAll(SuiView$EditText *  self);

SuiView$EditText*  SuiView$mkEditText(SuiView$EditText **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
