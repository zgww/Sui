
typedef struct tagSuiView$TextLineInfo SuiView$TextLineInfo;
typedef struct tagVtable_SuiView$TextLineInfo Vtable_SuiView$TextLineInfo;
typedef struct tagSuiView$TextLayout SuiView$TextLayout;
typedef struct tagVtable_SuiView$TextLayout Vtable_SuiView$TextLayout;
typedef struct tagSuiView$RuneInfo SuiView$RuneInfo;
typedef struct tagSuiView$TextView SuiView$TextView;
typedef struct tagVtable_SuiView$TextView Vtable_SuiView$TextView;


#ifndef define_struct___SuiView__TextView_orc_h__
#define define_struct___SuiView__TextView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiView__TextView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include "../../nanovg/nanovg.h"




#ifdef INCLUDE_ONLY_TYPE___SuiView__TextView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiView$RuneInfo {
	int  rune_index ;
	int  x ;
	int  y ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiView__TextView_orc_h__
#define __SuiView__TextView_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Frame_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../View/ViewBuilder_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../SuiDesigner/Theme_orc.h"
#include "../Core/Global_orc.h"
#include "../Core/Canvas_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiView$TextLineInfo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$TextLineInfo _vtable_SuiView$TextLineInfo;

// class refc:0
struct tagSuiView$TextLineInfo {
	Object super; 
	int  x ;
	int  y ;
	int  w ;
	int  h ;
	Orc$String*  text ;
	void  (*update_text_align) (SuiView$TextLineInfo *  self, int  out_w, const char *  text_align);
};
Vtable_SuiView$TextLineInfo* Vtable_SuiView$TextLineInfo_init(Vtable_SuiView$TextLineInfo* pvt);
void SuiView$TextLineInfo_init_fields(SuiView$TextLineInfo *self);
void SuiView$TextLineInfo_init(SuiView$TextLineInfo *self, void *pOwner);
SuiView$TextLineInfo * SuiView$TextLineInfo_new(void *pOwner);
void SuiView$TextLineInfo_fini(SuiView$TextLineInfo *self);

void  SuiView$TextLineInfo$ctor(SuiView$TextLineInfo *  self);
void  SuiView$TextLineInfo$dtor(SuiView$TextLineInfo *  self);
void  SuiView$TextLineInfo$update_text_align(SuiView$TextLineInfo *  self, int  out_w, const char *  text_align);


// 虚表
struct tagVtable_SuiView$TextLayout {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiView$TextLayout _vtable_SuiView$TextLayout;

// class refc:0
struct tagSuiView$TextLayout {
	Object super; 
	Orc$String*  (*ellipsis_line) (Orc$String **  __outRef__, SuiView$TextLayout *  self, const char *  text);
	Orc$String*  text ;
	Orc$String*  text_align ;
	int  max_line ;
	int  font_size ;
	float  line_height ;
	Orc$List*  line_infos ;
	int  w ;
	int  h ;
	int  use_max_w ;
	int  use_max_h ;
	bool  ellipsis ;
	int  area_x ;
	char  _key[256] ;
	int  (*get_actual_line_height) (SuiView$TextLayout *  self);
	bool  dirty ;
	void  (*setText) (SuiView$TextLayout *  self, const char *  v);
	void  (*setTextAlign) (SuiView$TextLayout *  self, const char *  v);
	void  (*setMaxLine) (SuiView$TextLayout *  self, int  v);
	void  (*setW) (SuiView$TextLayout *  self, int  w);
	void  (*setH) (SuiView$TextLayout *  self, int  v);
	void  (*setFontSize) (SuiView$TextLayout *  self, int  v);
	void  (*layout) (SuiView$TextLayout *  self, int  w, int  h);
	bool  (*layout_line) (SuiView$TextLayout *  self, const char *  line);
	float  (*measureText) (SuiView$TextLayout *  self, const char *  str, float *  bounds);
	Orc$List*  (*break_text) (Orc$List **  __outRef__, SuiView$TextLayout *  self, const char *  line);
};
Vtable_SuiView$TextLayout* Vtable_SuiView$TextLayout_init(Vtable_SuiView$TextLayout* pvt);
void SuiView$TextLayout_init_fields(SuiView$TextLayout *self);
void SuiView$TextLayout_init(SuiView$TextLayout *self, void *pOwner);
SuiView$TextLayout * SuiView$TextLayout_new(void *pOwner);
void SuiView$TextLayout_fini(SuiView$TextLayout *self);

void  SuiView$TextLayout$ctor(SuiView$TextLayout *  self);
void  SuiView$TextLayout$dtor(SuiView$TextLayout *  self);
Orc$String*  SuiView$TextLayout$ellipsis_line(Orc$String **  __outRef__, SuiView$TextLayout *  self, const char *  text);
int  SuiView$TextLayout$get_actual_line_height(SuiView$TextLayout *  self);
void  SuiView$TextLayout$setText(SuiView$TextLayout *  self, const char *  v);
void  SuiView$TextLayout$setTextAlign(SuiView$TextLayout *  self, const char *  v);
void  SuiView$TextLayout$setMaxLine(SuiView$TextLayout *  self, int  v);
void  SuiView$TextLayout$setW(SuiView$TextLayout *  self, int  w);
void  SuiView$TextLayout$setH(SuiView$TextLayout *  self, int  v);
void  SuiView$TextLayout$setFontSize(SuiView$TextLayout *  self, int  v);
void  SuiView$TextLayout$layout(SuiView$TextLayout *  self, int  w, int  h);
bool  SuiView$TextLayout$layout_line(SuiView$TextLayout *  self, const char *  line);
float  SuiView$TextLayout$measureText(SuiView$TextLayout *  self, const char *  str, float *  bounds);
Orc$List*  SuiView$TextLayout$break_text(Orc$List **  __outRef__, SuiView$TextLayout *  self, const char *  line);



//结构体元数据获取即初始化
MetaStruct* SuiView$RuneInfo_getOrInitMetaStruct();


// 虚表
struct tagVtable_SuiView$TextView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiView$TextView _vtable_SuiView$TextView;

// class refc:0
struct tagSuiView$TextView {
	SuiCore$View super; 
	SuiCore$Vec2 (*get_pos_by_rune_cnt) (SuiView$TextView *  self, int  rune_cnt);
	SuiCore$Frame cacheFrame ;
	bool  layoutDirty ;
	Orc$String*  text ;
	void  (*setText) (SuiView$TextView *  self, Orc$String*  text);
	int  font_size ;
	void  (*setFont_size) (SuiView$TextView *  self, int  v);
	Orc$String*  font_face ;
	void  (*setFont_face) (SuiView$TextView *  self, Orc$String *  v);
	int  color ;
	void  (*setColor) (SuiView$TextView *  self, int  v);
	int  font_weight ;
	void  (*setFont_weight) (SuiView$TextView *  self, int  v);
	bool  underline ;
	void  (*setUnderline) (SuiView$TextView *  self, bool  v);
	bool  line_through ;
	void  (*setLine_through) (SuiView$TextView *  self, bool  v);
	bool  italic ;
	void  (*setItalic) (SuiView$TextView *  self, bool  v);
	float  line_height ;
	void  (*setLine_height) (SuiView$TextView *  self, float  v);
	Orc$String*  text_align ;
	void  (*setText_align) (SuiView$TextView *  self, Orc$String*  v);
	bool  wrap ;
	void  (*setWrap) (SuiView$TextView *  self, bool  v);
	int  max_line ;
	void  (*setMax_line) (SuiView$TextView *  self, int  v);
	bool  overflow_ellipsis ;
	void  (*setOverflow_ellipsis) (SuiView$TextView *  self, bool  v);
	SuiView$TextLayout*  _text_layout ;
	bool  _measure_dirty ;
	SuiView$RuneInfo (*get_rune_index_at_local_pos) (SuiView$TextView *  self, SuiCore$Vec2 *  pos);
	void  (*_set_tl) (SuiView$TextView *  self);
};
Vtable_SuiView$TextView* Vtable_SuiView$TextView_init(Vtable_SuiView$TextView* pvt);
void SuiView$TextView_init_fields(SuiView$TextView *self);
void SuiView$TextView_init(SuiView$TextView *self, void *pOwner);
SuiView$TextView * SuiView$TextView_new(void *pOwner);
void SuiView$TextView_fini(SuiView$TextView *self);

SuiCore$Vec2 SuiView$TextView$get_pos_by_rune_cnt(SuiView$TextView *  self, int  rune_cnt);
void  SuiView$TextView$layout(SuiView$TextView *  self, SuiCore$Frame *  ctx);
void  SuiView$TextView$ctor(SuiView$TextView *  self);
void  SuiView$TextView$invalidLayout(SuiView$TextView *  self);
void  SuiView$TextView$setText(SuiView$TextView *  self, Orc$String*  text);
void  SuiView$TextView$setFont_size(SuiView$TextView *  self, int  v);
void  SuiView$TextView$setFont_face(SuiView$TextView *  self, Orc$String *  v);
void  SuiView$TextView$setColor(SuiView$TextView *  self, int  v);
void  SuiView$TextView$setFont_weight(SuiView$TextView *  self, int  v);
void  SuiView$TextView$setUnderline(SuiView$TextView *  self, bool  v);
void  SuiView$TextView$setLine_through(SuiView$TextView *  self, bool  v);
void  SuiView$TextView$setItalic(SuiView$TextView *  self, bool  v);
void  SuiView$TextView$setLine_height(SuiView$TextView *  self, float  v);
void  SuiView$TextView$setText_align(SuiView$TextView *  self, Orc$String*  v);
void  SuiView$TextView$setWrap(SuiView$TextView *  self, bool  v);
void  SuiView$TextView$setMax_line(SuiView$TextView *  self, int  v);
void  SuiView$TextView$setOverflow_ellipsis(SuiView$TextView *  self, bool  v);
SuiView$RuneInfo SuiView$TextView$get_rune_index_at_local_pos(SuiView$TextView *  self, SuiCore$Vec2 *  pos);
void  SuiView$TextView$_set_tl(SuiView$TextView *  self);
void  SuiView$TextView$draw_self(SuiView$TextView *  self, SuiCore$Canvas *  canvas);

SuiView$TextView*  SuiView$mkTextView(SuiView$TextView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
