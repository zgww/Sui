
#include "TextView_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../../nanovg/nanovg.h"
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


// static struct 


// static function declaration



//vtable instance
Vtable_SuiView$TextLineInfo _vtable_SuiView$TextLineInfo;

// init meta

void SuiView$TextLineInfo_initMeta(Vtable_SuiView$TextLineInfo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "x", OrcMetaType_int, offsetof(SuiView$TextLineInfo, x), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "y", OrcMetaType_int, offsetof(SuiView$TextLineInfo, y), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "w", OrcMetaType_int, offsetof(SuiView$TextLineInfo, w), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "h", OrcMetaType_int, offsetof(SuiView$TextLineInfo, h), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "text", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$TextLineInfo, text), true, false, 1);

	orc_metaField_method(&pNext, "update_text_align", offsetof(SuiView$TextLineInfo, update_text_align));
}


// vtable init


Vtable_SuiView$TextLineInfo* Vtable_SuiView$TextLineInfo_init(Vtable_SuiView$TextLineInfo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$TextLineInfo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$TextLineInfo_new;
    ((Vtable_Object*)pvt)->className = "SuiView$TextLineInfo";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$TextLineInfo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$TextLineInfo_fini(SuiView$TextLineInfo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiView$TextLineInfo_init_fields(SuiView$TextLineInfo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$TextLineInfo_fini;
	//fields
    {
	((SuiView$TextLineInfo*)self)->x = 0;
	((SuiView$TextLineInfo*)self)->y = 0;
	((SuiView$TextLineInfo*)self)->w = 0;
	((SuiView$TextLineInfo*)self)->h = 0;
	urgc_set_field_class(self, (void**)&((SuiView$TextLineInfo*)self)->text, NULL);
    }
	((Object*)self)->ctor = (void*)SuiView$TextLineInfo$ctor;
	((Object*)self)->dtor = (void*)SuiView$TextLineInfo$dtor;
	((SuiView$TextLineInfo*)self)->update_text_align = (void*)SuiView$TextLineInfo$update_text_align;
}

// init function

void SuiView$TextLineInfo_init(SuiView$TextLineInfo *self, void *pOwner){
    Vtable_SuiView$TextLineInfo_init(&_vtable_SuiView$TextLineInfo);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$TextLineInfo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$TextLineInfo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$TextLineInfo * SuiView$TextLineInfo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$TextLineInfo *self = calloc(1, sizeof(SuiView$TextLineInfo));
	
    SuiView$TextLineInfo_init(self, pOwner);
    return self;
}


// class members
void  SuiView$TextLineInfo$ctor(SuiView$TextLineInfo *  self){
	
}


void  SuiView$TextLineInfo$dtor(SuiView$TextLineInfo *  self){
	
}


void  SuiView$TextLineInfo$update_text_align(SuiView$TextLineInfo *  self, int  out_w, const char *  text_align){
	if (strcmp(text_align, "left")  == 0) {
		self->x = 0;
	}
	else if (strcmp(text_align, "center")  == 0) {
		self->x = (out_w - self->w) / 2;
	}
	else if (strcmp(text_align, "right")  == 0) {
		self->x = (out_w - self->w);
	}
}




//vtable instance
Vtable_SuiView$TextLayout _vtable_SuiView$TextLayout;

// init meta

void SuiView$TextLayout_initMeta(Vtable_SuiView$TextLayout *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "text", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$TextLayout, text), true, false, 1);
	orc_metaField_class(&pNext, "text_align", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$TextLayout, text_align), true, false, 1);
	orc_metaField_primitive(&pNext, "max_line", OrcMetaType_int, offsetof(SuiView$TextLayout, max_line), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "font_size", OrcMetaType_int, offsetof(SuiView$TextLayout, font_size), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "line_height", OrcMetaType_float, offsetof(SuiView$TextLayout, line_height), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "line_infos", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiView$TextLayout, line_infos), true, false, 1);
	orc_metaField_primitive(&pNext, "w", OrcMetaType_int, offsetof(SuiView$TextLayout, w), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "h", OrcMetaType_int, offsetof(SuiView$TextLayout, h), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "use_max_w", OrcMetaType_int, offsetof(SuiView$TextLayout, use_max_w), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "use_max_h", OrcMetaType_int, offsetof(SuiView$TextLayout, use_max_h), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "ellipsis", OrcMetaType_bool, offsetof(SuiView$TextLayout, ellipsis), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "area_x", OrcMetaType_int, offsetof(SuiView$TextLayout, area_x), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "_key", OrcMetaType_char, offsetof(SuiView$TextLayout, _key), 0, 0, 1, 1);//char
	orc_metaField_primitive(&pNext, "dirty", OrcMetaType_bool, offsetof(SuiView$TextLayout, dirty), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "ellipsis_line", offsetof(SuiView$TextLayout, ellipsis_line));
	orc_metaField_method(&pNext, "get_actual_line_height", offsetof(SuiView$TextLayout, get_actual_line_height));
	orc_metaField_method(&pNext, "setText", offsetof(SuiView$TextLayout, setText));
	orc_metaField_method(&pNext, "setTextAlign", offsetof(SuiView$TextLayout, setTextAlign));
	orc_metaField_method(&pNext, "setMaxLine", offsetof(SuiView$TextLayout, setMaxLine));
	orc_metaField_method(&pNext, "setW", offsetof(SuiView$TextLayout, setW));
	orc_metaField_method(&pNext, "setH", offsetof(SuiView$TextLayout, setH));
	orc_metaField_method(&pNext, "setFontSize", offsetof(SuiView$TextLayout, setFontSize));
	orc_metaField_method(&pNext, "layout", offsetof(SuiView$TextLayout, layout));
	orc_metaField_method(&pNext, "layout_line", offsetof(SuiView$TextLayout, layout_line));
	orc_metaField_method(&pNext, "measureText", offsetof(SuiView$TextLayout, measureText));
	orc_metaField_method(&pNext, "break_text", offsetof(SuiView$TextLayout, break_text));
}


// vtable init


Vtable_SuiView$TextLayout* Vtable_SuiView$TextLayout_init(Vtable_SuiView$TextLayout* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$TextLayout;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$TextLayout_new;
    ((Vtable_Object*)pvt)->className = "SuiView$TextLayout";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$TextLayout_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$TextLayout_fini(SuiView$TextLayout *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiView$TextLayout_init_fields(SuiView$TextLayout *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$TextLayout_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TextLayout*)self)->text, Orc$str(&tmpReturn_1, "") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TextLayout*)self)->text_align, Orc$str(&tmpReturn_2, "left") );
	((SuiView$TextLayout*)self)->max_line = 0;
	((SuiView$TextLayout*)self)->font_size = 14;
	((SuiView$TextLayout*)self)->line_height = 1.4f;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TextLayout*)self)->line_infos, Orc$List_new(&tmpNewOwner_3) );
	((SuiView$TextLayout*)self)->use_max_w = 0;
	((SuiView$TextLayout*)self)->use_max_h = 0;
	((SuiView$TextLayout*)self)->ellipsis = false;
	((SuiView$TextLayout*)self)->area_x = 0;
	((SuiView$TextLayout*)self)->dirty = true;
    }
	((Object*)self)->ctor = (void*)SuiView$TextLayout$ctor;
	((Object*)self)->dtor = (void*)SuiView$TextLayout$dtor;
	((SuiView$TextLayout*)self)->ellipsis_line = (void*)SuiView$TextLayout$ellipsis_line;
	((SuiView$TextLayout*)self)->get_actual_line_height = (void*)SuiView$TextLayout$get_actual_line_height;
	((SuiView$TextLayout*)self)->setText = (void*)SuiView$TextLayout$setText;
	((SuiView$TextLayout*)self)->setTextAlign = (void*)SuiView$TextLayout$setTextAlign;
	((SuiView$TextLayout*)self)->setMaxLine = (void*)SuiView$TextLayout$setMaxLine;
	((SuiView$TextLayout*)self)->setW = (void*)SuiView$TextLayout$setW;
	((SuiView$TextLayout*)self)->setH = (void*)SuiView$TextLayout$setH;
	((SuiView$TextLayout*)self)->setFontSize = (void*)SuiView$TextLayout$setFontSize;
	((SuiView$TextLayout*)self)->layout = (void*)SuiView$TextLayout$layout;
	((SuiView$TextLayout*)self)->layout_line = (void*)SuiView$TextLayout$layout_line;
	((SuiView$TextLayout*)self)->measureText = (void*)SuiView$TextLayout$measureText;
	((SuiView$TextLayout*)self)->break_text = (void*)SuiView$TextLayout$break_text;
}

// init function

void SuiView$TextLayout_init(SuiView$TextLayout *self, void *pOwner){
    Vtable_SuiView$TextLayout_init(&_vtable_SuiView$TextLayout);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$TextLayout;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$TextLayout_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$TextLayout * SuiView$TextLayout_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$TextLayout *self = calloc(1, sizeof(SuiView$TextLayout));
	
    SuiView$TextLayout_init(self, pOwner);
    return self;
}


// class members
void  SuiView$TextLayout$ctor(SuiView$TextLayout *  self){
	
}


void  SuiView$TextLayout$dtor(SuiView$TextLayout *  self){
	
}


Orc$String*  SuiView$TextLayout$ellipsis_line(Orc$String **  __outRef__, SuiView$TextLayout *  self, const char *  text){
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = Orc$str((s = NULL,&s), text) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  s2 = (s2=NULL,urgc_init_var_class((void**)&s2, Orc$String$add(Orc$String$substringByCount(&tmpReturn_1, s, 0, Orc$String$size(s)  - 1) , "..") ));
	return urgc_set_var_for_return_class((void ** )__outRef__, s2) ; 
}


int  SuiView$TextLayout$get_actual_line_height(SuiView$TextLayout *  self){
	float  lh = self->line_height * self->font_size;
	return Orc$maxInt((int )lh, self->font_size) ; 
}


void  SuiView$TextLayout$setText(SuiView$TextLayout *  self, const char *  v){
	if (!Orc$String$equals(self->text, v) ) {
		Orc$String$set(self->text, v) ;
		self->dirty = true;
	}
}


void  SuiView$TextLayout$setTextAlign(SuiView$TextLayout *  self, const char *  v){
	if (!Orc$String$equals(self->text_align, v) ) {
		Orc$String$set(self->text_align, v) ;
		self->dirty = true;
	}
}


void  SuiView$TextLayout$setMaxLine(SuiView$TextLayout *  self, int  v){
	if (self->max_line != v) {
		self->max_line = v;
		self->dirty = true;
	}
}


void  SuiView$TextLayout$setW(SuiView$TextLayout *  self, int  w){
	if (self->w != w) {
		self->w = w;
		self->dirty = true;
	}
}


void  SuiView$TextLayout$setH(SuiView$TextLayout *  self, int  v){
	if (self->h != v) {
		self->h = v;
		self->dirty = true;
	}
}


void  SuiView$TextLayout$setFontSize(SuiView$TextLayout *  self, int  v){
	if (self->font_size != v) {
		self->font_size = v;
		self->dirty = true;
	}
}


void  SuiView$TextLayout$layout(SuiView$TextLayout *  self, int  w, int  h){
	self->setW(self, w) ;
	self->setH(self, h) ;
	if (!self->dirty) {
		return ; 
	}
	self->dirty = false;
	URGC_VAR_CLEANUP_CLASS Orc$List*  lines = Orc$String$splitByRe((lines = NULL,&lines), self->text, "\n") ;
	self->use_max_w = 0;
	self->use_max_h = 0;
	self->line_infos->clear(self->line_infos) ;
	int  l = lines->size(lines) ;
	for (int  i = 0; i < l; i++) {
		Orc$String *  line = (Orc$String * )lines->get(lines, i) ;
		if (self->layout_line(self, line->str) ) {
			break;
		}
	}
	float  lh = self->get_actual_line_height(self) ;
	float  half_lh_space = (lh - self->font_size) / 2;
	float  y = half_lh_space + self->font_size;
	l = self->line_infos->size(self->line_infos) ;
	for (int  i = 0; i < l; i++) {
		SuiView$TextLineInfo *  li = (SuiView$TextLineInfo * )self->line_infos->get(self->line_infos, i) ;
		li->y = y;
		if (self->use_max_w < li->w) {
			self->use_max_w = li->w;
		}
		y = y + lh;
		if (h > 0) {
			
		}
	}
	l = self->line_infos->size(self->line_infos) ;
	for (int  i = 0; i < l; i++) {
		SuiView$TextLineInfo *  li = (SuiView$TextLineInfo * )self->line_infos->get(self->line_infos, i) ;
		li->update_text_align(li, self->use_max_w, self->text_align->str) ;
	}
	float  descent = self->font_size / 3.f;
	self->use_max_h = y - half_lh_space - self->font_size + descent;
	self->area_x = 0;
	if (Orc$String$equals(self->text_align, "center") ) {
		self->area_x = (w - self->use_max_w) / 2.f;
	}
	if (Orc$String$equals(self->text_align, "right") ) {
		self->area_x = (w - self->use_max_w);
	}
	if (self->use_max_w > w) {
		
	}
	else if (self->use_max_h > h) {
		
	}
}


bool  SuiView$TextLayout$layout_line(SuiView$TextLayout *  self, const char *  line){
	URGC_VAR_CLEANUP_CLASS Orc$List*  lines = self->break_text((lines = NULL,&lines), self, line) ;
	if (self->max_line <= 0) {
		int  l = lines->size(lines) ;
		for (int  i = 0; i < l; i++) {
			self->line_infos->add(self->line_infos, lines->get(lines, i) ) ;
		}
		return false; 
	}
	else {
		int  l = lines->size(lines) ;
		for (int  i = 0; i < l; i++) {
			SuiView$TextLineInfo *  line = (SuiView$TextLineInfo * )lines->get(lines, i) ;
			if (self->line_infos->size(self->line_infos)  < self->max_line) {
				self->line_infos->add(self->line_infos, line) ;
			}
			else {
				if (self->ellipsis) {
					if (i > 0) {
						SuiView$TextLineInfo *  li = (SuiView$TextLineInfo * )self->line_infos->get(self->line_infos, self->line_infos->size(self->line_infos)  - 1) ;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
						urgc_set_field_class(li, (void * )offsetof(SuiView$TextLineInfo, text) , self->ellipsis_line(&tmpReturn_1, self, li->text->str) ) ;
					}
				}
				break;
			}
		}
		return self->line_infos->size(self->line_infos)  >= self->max_line; 
	}
}


float  SuiView$TextLayout$measureText(SuiView$TextLayout *  self, const char *  str, float *  bounds){
	SuiCore$Canvas *  canvas = SuiCore$Global_getCanvas() ;
	int  line_w = (int )SuiCore$Canvas$textBounds(canvas, 0, 0, str, NULL, bounds) ;
	return line_w; 
}


Orc$List*  SuiView$TextLayout$break_text(Orc$List **  __outRef__, SuiView$TextLayout *  self, const char *  line){
	SuiCore$Canvas *  canvas = SuiCore$Global_getCanvas() ;
	int  min_cap_char_cnt = Orc$maxInt(1, (int )(self->w / self->font_size) - 1) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  remain = Orc$str((remain = NULL,&remain), line) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  lines = (lines=NULL,urgc_init_var_class((void**)&lines, Orc$List_new(&lines) ));
	float  bounds[4];
	memset(bounds, 0, sizeof(bounds) ) ;
	int  prev_w = 0;
	SuiCore$Canvas$fontSize(canvas, self->font_size) ;
	while (Orc$String$notEquals(remain, "") ) {
		int  l = min_cap_char_cnt + 1;
		int  ml = Orc$String$size(remain) ;
		while (true) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  subtext = Orc$String$substringByCount((subtext = NULL,&subtext), remain, 0, l) ;
			int  line_w = (int )SuiCore$Canvas$textBounds(canvas, 0, 0, subtext->str, NULL, bounds) ;
			float  boundHeight = bounds[3] - bounds[1];
			if (line_w > self->w) {
				URGC_VAR_CLEANUP_CLASS SuiView$TextLineInfo*  line_info = (line_info=NULL,urgc_init_var_class((void**)&line_info, SuiView$TextLineInfo_new(&line_info) ));
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
				urgc_set_field_class(line_info, (void * )offsetof(SuiView$TextLineInfo, text) , Orc$String$substringByCount(&tmpReturn_1, remain, 0, l - 1) ) ;
				line_info->w = prev_w;
				line_info->h = (int )(boundHeight);
				lines->add(lines, line_info) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
				urgc_set_var_class(&remain, Orc$String$substringByCount(&tmpReturn_2, remain, l - 1, Orc$String$size(remain) ) ) ;
				break;
			}
			if (l >= ml) {
				URGC_VAR_CLEANUP_CLASS SuiView$TextLineInfo*  line_info = (line_info=NULL,urgc_init_var_class((void**)&line_info, SuiView$TextLineInfo_new(&line_info) ));
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				urgc_set_field_class(line_info, (void * )offsetof(SuiView$TextLineInfo, text) , Orc$String$substringByCount(&tmpReturn_3, remain, 0, l) ) ;
				line_info->w = line_w;
				line_info->h = (int )boundHeight;
				lines->add(lines, line_info) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
				urgc_set_var_class(&remain, Orc$str(&tmpReturn_4, "") ) ;
				break;
			}
			prev_w = line_w;
			l = l + 1;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, lines) ; 
}




// get or init meta 
MetaStruct* SuiView$RuneInfo_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiView$RuneInfo", sizeof( SuiView$RuneInfo ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "rune_index", OrcMetaType_int, offsetof(SuiView$RuneInfo, rune_index), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "x", OrcMetaType_int, offsetof(SuiView$RuneInfo, x), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "y", OrcMetaType_int, offsetof(SuiView$RuneInfo, y), 0, 0, 0, 0);//int
    }
	return meta;
}

//vtable instance
Vtable_SuiView$TextView _vtable_SuiView$TextView;

// init meta

void SuiView$TextView_initMeta(Vtable_SuiView$TextView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "cacheFrame", SuiCore$Frame_getOrInitMetaStruct(), offsetof(SuiView$TextView, cacheFrame), false, false, 0);
	orc_metaField_primitive(&pNext, "layoutDirty", OrcMetaType_bool, offsetof(SuiView$TextView, layoutDirty), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "text", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$TextView, text), true, false, 1);
	orc_metaField_primitive(&pNext, "font_size", OrcMetaType_int, offsetof(SuiView$TextView, font_size), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "font_face", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$TextView, font_face), true, false, 1);
	orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(SuiView$TextView, color), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "font_weight", OrcMetaType_int, offsetof(SuiView$TextView, font_weight), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "underline", OrcMetaType_bool, offsetof(SuiView$TextView, underline), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "line_through", OrcMetaType_bool, offsetof(SuiView$TextView, line_through), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "italic", OrcMetaType_bool, offsetof(SuiView$TextView, italic), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "line_height", OrcMetaType_float, offsetof(SuiView$TextView, line_height), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "text_align", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$TextView, text_align), true, false, 1);
	orc_metaField_primitive(&pNext, "wrap", OrcMetaType_bool, offsetof(SuiView$TextView, wrap), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "max_line", OrcMetaType_int, offsetof(SuiView$TextView, max_line), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "overflow_ellipsis", OrcMetaType_bool, offsetof(SuiView$TextView, overflow_ellipsis), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "_text_layout", ((Vtable_Object*)Vtable_SuiView$TextLayout_init(0)), offsetof(SuiView$TextView, _text_layout), true, false, 1);
	orc_metaField_primitive(&pNext, "_measure_dirty", OrcMetaType_bool, offsetof(SuiView$TextView, _measure_dirty), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "get_pos_by_rune_cnt", offsetof(SuiView$TextView, get_pos_by_rune_cnt));
	orc_metaField_method(&pNext, "setText", offsetof(SuiView$TextView, setText));
	orc_metaField_method(&pNext, "setFont_size", offsetof(SuiView$TextView, setFont_size));
	orc_metaField_method(&pNext, "setFont_face", offsetof(SuiView$TextView, setFont_face));
	orc_metaField_method(&pNext, "setColor", offsetof(SuiView$TextView, setColor));
	orc_metaField_method(&pNext, "setFont_weight", offsetof(SuiView$TextView, setFont_weight));
	orc_metaField_method(&pNext, "setUnderline", offsetof(SuiView$TextView, setUnderline));
	orc_metaField_method(&pNext, "setLine_through", offsetof(SuiView$TextView, setLine_through));
	orc_metaField_method(&pNext, "setItalic", offsetof(SuiView$TextView, setItalic));
	orc_metaField_method(&pNext, "setLine_height", offsetof(SuiView$TextView, setLine_height));
	orc_metaField_method(&pNext, "setText_align", offsetof(SuiView$TextView, setText_align));
	orc_metaField_method(&pNext, "setWrap", offsetof(SuiView$TextView, setWrap));
	orc_metaField_method(&pNext, "setMax_line", offsetof(SuiView$TextView, setMax_line));
	orc_metaField_method(&pNext, "setOverflow_ellipsis", offsetof(SuiView$TextView, setOverflow_ellipsis));
	orc_metaField_method(&pNext, "get_rune_index_at_local_pos", offsetof(SuiView$TextView, get_rune_index_at_local_pos));
	orc_metaField_method(&pNext, "_set_tl", offsetof(SuiView$TextView, _set_tl));
}


// vtable init


Vtable_SuiView$TextView* Vtable_SuiView$TextView_init(Vtable_SuiView$TextView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$TextView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$TextView_new;
    ((Vtable_Object*)pvt)->className = "SuiView$TextView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$TextView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$TextView_fini(SuiView$TextView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiView$TextView_init_fields(SuiView$TextView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$TextView_fini;
	//fields
    {
	((SuiView$TextView*)self)->cacheFrame = SuiCore$mkFrame() ;
	((SuiView$TextView*)self)->layoutDirty = true;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TextView*)self)->text, Orc$str(&tmpReturn_1, "") );
	((SuiView$TextView*)self)->font_size = SuiDesigner$themeIns() ->textview_fontSize;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TextView*)self)->font_face, Orc$str(&tmpReturn_2, "") );
	((SuiView$TextView*)self)->color = SuiDesigner$themeIns() ->textview_color;
	((SuiView$TextView*)self)->font_weight = 0;
	((SuiView$TextView*)self)->underline = false;
	((SuiView$TextView*)self)->line_through = false;
	((SuiView$TextView*)self)->italic = false;
	((SuiView$TextView*)self)->line_height = 1.4f;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TextView*)self)->text_align, Orc$str(&tmpReturn_3, "left") );
	((SuiView$TextView*)self)->wrap = false;
	((SuiView$TextView*)self)->max_line = 0;
	((SuiView$TextView*)self)->overflow_ellipsis = false;
	URGC_VAR_CLEANUP_CLASS SuiView$TextLayout*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TextView*)self)->_text_layout, SuiView$TextLayout_new(&tmpNewOwner_4) );
	((SuiView$TextView*)self)->_measure_dirty = true;
    }
	((SuiView$TextView*)self)->get_pos_by_rune_cnt = (void*)SuiView$TextView$get_pos_by_rune_cnt;
	((SuiCore$ViewBase*)self)->layout = (void*)SuiView$TextView$layout;
	((Object*)self)->ctor = (void*)SuiView$TextView$ctor;
	((SuiCore$ViewBase*)self)->invalidLayout = (void*)SuiView$TextView$invalidLayout;
	((SuiView$TextView*)self)->setText = (void*)SuiView$TextView$setText;
	((SuiView$TextView*)self)->setFont_size = (void*)SuiView$TextView$setFont_size;
	((SuiView$TextView*)self)->setFont_face = (void*)SuiView$TextView$setFont_face;
	((SuiView$TextView*)self)->setColor = (void*)SuiView$TextView$setColor;
	((SuiView$TextView*)self)->setFont_weight = (void*)SuiView$TextView$setFont_weight;
	((SuiView$TextView*)self)->setUnderline = (void*)SuiView$TextView$setUnderline;
	((SuiView$TextView*)self)->setLine_through = (void*)SuiView$TextView$setLine_through;
	((SuiView$TextView*)self)->setItalic = (void*)SuiView$TextView$setItalic;
	((SuiView$TextView*)self)->setLine_height = (void*)SuiView$TextView$setLine_height;
	((SuiView$TextView*)self)->setText_align = (void*)SuiView$TextView$setText_align;
	((SuiView$TextView*)self)->setWrap = (void*)SuiView$TextView$setWrap;
	((SuiView$TextView*)self)->setMax_line = (void*)SuiView$TextView$setMax_line;
	((SuiView$TextView*)self)->setOverflow_ellipsis = (void*)SuiView$TextView$setOverflow_ellipsis;
	((SuiView$TextView*)self)->get_rune_index_at_local_pos = (void*)SuiView$TextView$get_rune_index_at_local_pos;
	((SuiView$TextView*)self)->_set_tl = (void*)SuiView$TextView$_set_tl;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$TextView$draw_self;
}

// init function

void SuiView$TextView_init(SuiView$TextView *self, void *pOwner){
    Vtable_SuiView$TextView_init(&_vtable_SuiView$TextView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$TextView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$TextView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$TextView * SuiView$TextView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$TextView *self = calloc(1, sizeof(SuiView$TextView));
	
    SuiView$TextView_init(self, pOwner);
    return self;
}


// class members
SuiCore$Vec2 SuiView$TextView$get_pos_by_rune_cnt(SuiView$TextView *  self, int  rune_cnt){
	SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0) ;
	for (int  r = 0; r < self->_text_layout->line_infos->size(self->_text_layout->line_infos) ; r++) {
		SuiView$TextLineInfo *  li = (SuiView$TextLineInfo * )self->_text_layout->line_infos->get(self->_text_layout->line_infos, r) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  utf8 = (utf8=NULL,urgc_init_var_class((void**)&utf8, li->text));
		int  rune_len = Orc$String$length(utf8) ;
		if (rune_cnt > rune_len) {
			rune_cnt = rune_cnt - rune_len;
			continue;
		}
		else {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpText = Orc$String$substringByCount((tmpText = NULL,&tmpText), utf8, 0, rune_cnt) ;
			ret.x = li->x + (int )self->_text_layout->measureText(self->_text_layout, tmpText->str, NULL) ;
			ret.y = li->y;
		}
	}
	return ret; 
}


void  SuiView$TextView$layout(SuiView$TextView *  self, SuiCore$Frame *  ctx){
	if (!self->layoutDirty) {
		if (SuiCore$Frame$isSizeSatisfy_otherFrameConstraints(&self->cacheFrame, ctx) ) {
			return ; 
		}
	}
	self->layoutDirty = false;
	SuiCore$Frame$incTimesInOneLayout(ctx) ;
	((SuiCore$View * )self)->updateFrame_forSelfWidthHeight(self, ctx) ;
	if (SuiCore$Frame$setSize_ifTight(ctx) ) {
		SuiCore$Frame _ctx = ((SuiCore$View * )self)->makeContentLayoutCtx(self, ctx) ;
		self->_set_tl(self) ;
		self->_text_layout->layout(self->_text_layout, _ctx.maxWidth, _ctx.maxHeight) ;
		self->cacheFrame = SuiCore$Frame$copy(ctx) ;
		return ; 
	}
	if (Orc$String$equals(self->text, "") ) {
		SuiCore$Frame$setSize(ctx, SuiCore$Inset$hor(&((SuiCore$View * )self)->margin) , SuiCore$Inset$ver(&((SuiCore$View * )self)->margin) ) ;
		SuiCore$Frame _ctx = ((SuiCore$View * )self)->makeContentLayoutCtx(self, ctx) ;
		self->_set_tl(self) ;
		self->_text_layout->layout(self->_text_layout, _ctx.maxWidth, _ctx.maxHeight) ;
		self->cacheFrame = SuiCore$Frame$copy(ctx) ;
		return ; 
	}
	SuiCore$Frame contentCtx = ((SuiCore$View * )self)->makeContentLayoutCtx(self, ctx) ;
	self->_set_tl(self) ;
	self->_text_layout->layout(self->_text_layout, ctx->maxWidth == INFINITY ? 99999999 : ctx->maxWidth, ctx->maxHeight == INFINITY ? 99999999 : ctx->maxHeight) ;
	SuiCore$Frame$setSize(&contentCtx, self->_text_layout->use_max_w, self->_text_layout->use_max_h) ;
	((SuiCore$View * )self)->updateFrame_byContentCtx(self, ctx, &contentCtx) ;
	self->cacheFrame = SuiCore$Frame$copy(ctx) ;
}


void  SuiView$TextView$ctor(SuiView$TextView *  self){
	((SuiCore$View * )self)->backgroundColor = SuiDesigner$themeIns() ->textview_bg;
}


void  SuiView$TextView$invalidLayout(SuiView$TextView *  self){
	SuiCore$ViewBase$invalidLayout(self) ;
	self->layoutDirty = true;
}


void  SuiView$TextView$setText(SuiView$TextView *  self, Orc$String*  text){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(text);

	if (Orc$String$equalsString(self->text, text) ) {
		return ; 
	}
	if (text == NULL) {
		Orc$String$set(self->text, "") ;
	}
	else {
		urgc_set_field_class(self, (void * )offsetof(SuiView$TextView, text) , text) ;
	}
	((SuiCore$ViewBase * )self)->invalidLayout(self) ;
}


void  SuiView$TextView$setFont_size(SuiView$TextView *  self, int  v){
	if (v != self->font_size) {
		self->font_size = v;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


void  SuiView$TextView$setFont_face(SuiView$TextView *  self, Orc$String *  v){
	if (!Orc$String$equals(self->font_face, v->str) ) {
		urgc_set_field_class(self, (void * )offsetof(SuiView$TextView, font_face) , v) ;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


void  SuiView$TextView$setColor(SuiView$TextView *  self, int  v){
	if (v != self->color) {
		self->color = v;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


void  SuiView$TextView$setFont_weight(SuiView$TextView *  self, int  v){
	if (v != self->font_weight) {
		self->font_weight = v;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


void  SuiView$TextView$setUnderline(SuiView$TextView *  self, bool  v){
	if (v != self->underline) {
		self->underline = v;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


void  SuiView$TextView$setLine_through(SuiView$TextView *  self, bool  v){
	if (v != self->line_through) {
		self->line_through = v;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


void  SuiView$TextView$setItalic(SuiView$TextView *  self, bool  v){
	if (v != self->italic) {
		self->italic = v;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


void  SuiView$TextView$setLine_height(SuiView$TextView *  self, float  v){
	if (v != self->line_height) {
		self->line_height = v;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


void  SuiView$TextView$setText_align(SuiView$TextView *  self, Orc$String*  v){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(v);

	if (v != self->text_align) {
		urgc_set_field_class(self, (void * )offsetof(SuiView$TextView, text_align) , v) ;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


void  SuiView$TextView$setWrap(SuiView$TextView *  self, bool  v){
	if (v != self->wrap) {
		self->wrap = v;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


void  SuiView$TextView$setMax_line(SuiView$TextView *  self, int  v){
	if (v != self->max_line) {
		self->max_line = v;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


void  SuiView$TextView$setOverflow_ellipsis(SuiView$TextView *  self, bool  v){
	if (v != self->overflow_ellipsis) {
		self->overflow_ellipsis = v;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


SuiView$RuneInfo SuiView$TextView$get_rune_index_at_local_pos(SuiView$TextView *  self, SuiCore$Vec2 *  pos){
	SuiView$RuneInfo ret;
	memset(&ret, 0, sizeof(ret) ) ;
	ret.rune_index = 0;
	float  lh = self->_text_layout->get_actual_line_height(self->_text_layout) ;
	int  l = self->_text_layout->line_infos->size(self->_text_layout->line_infos) ;
	for (int  i = 0; i < l; i++) {
		SuiView$TextLineInfo *  li = (SuiView$TextLineInfo * )self->_text_layout->line_infos->get(self->_text_layout->line_infos, i) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  utf8 = (utf8=NULL,urgc_init_var_class((void**)&utf8, li->text));
		float  y0 = i * lh;
		if (y0 <= pos->y && pos->y <= y0 + lh) {
			int  left = 0;
			ret.y = li->y;
			int  jl = Orc$String$size(utf8) ;
			for (int  j = 1; j < jl; j++) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  subtext = Orc$String$substringByCount((subtext = NULL,&subtext), utf8, 0, j) ;
				float  right = self->_text_layout->measureText(self->_text_layout, subtext->str, NULL) ;
				if (left <= pos->x && pos->x <= right) {
					if (pos->x <= (left + right) / 2.0f) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  prevtext = Orc$String$substringByCount((prevtext = NULL,&prevtext), subtext, 0, j - 1) ;
						ret.rune_index = ret.rune_index + Orc$String$size(prevtext) ;
						ret.x = left;
					}
					else {
						ret.rune_index = ret.rune_index + Orc$String$size(subtext) ;
						ret.x = right;
					}
					return ret; 
				}
				left = right;
			}
			ret.rune_index = ret.rune_index + Orc$String$size(utf8) ;
			ret.x = self->_text_layout->measureText(self->_text_layout, li->text->str, NULL) ;
			return ret; 
		}
		else {
			ret.rune_index = ret.rune_index + Orc$String$size(utf8) ;
		}
	}
	return ret; 
}


void  SuiView$TextView$_set_tl(SuiView$TextView *  self){
	SuiView$TextLayout *  tl = self->_text_layout;
	tl->setText(tl, self->text->str) ;
	tl->setTextAlign(tl, self->text_align->str) ;
	tl->setFontSize(tl, self->font_size) ;
	tl->setMaxLine(tl, self->max_line) ;
	tl->ellipsis = self->overflow_ellipsis;
	tl->line_height = self->line_height;
}


void  SuiView$TextView$draw_self(SuiView$TextView *  self, SuiCore$Canvas *  canvas){
	SuiCore$View$draw_self(self, canvas) ;
	float  w = 0.f;
	float  h = 0.f;
	float  pl = ((SuiCore$View * )self)->padding.left;
	float  pt = ((SuiCore$View * )self)->padding.top;
	SuiCore$Canvas$fillColorByInt32(canvas, self->color) ;
	SuiCore$Canvas$fontSize(canvas, self->font_size) ;
	int  l = self->_text_layout->line_infos->size(self->_text_layout->line_infos) ;
	for (int  i = 0; i < l; i++) {
		SuiView$TextLineInfo *  li = (SuiView$TextLineInfo * )self->_text_layout->line_infos->get(self->_text_layout->line_infos, i) ;
		const char *  s = li->text->str;
		SuiCore$Canvas$text(canvas, li->x + pl + self->_text_layout->area_x, li->y + pt, li->text->str) ;
		const char *  s2 = li->text->str;
	}
}



SuiView$TextView*  SuiView$mkTextView(SuiView$TextView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$TextView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$TextView_init(NULL)) ) ; 
}



