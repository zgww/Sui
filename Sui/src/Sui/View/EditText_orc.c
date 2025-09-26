
#include "EditText_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
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


// static struct 
typedef struct tagSuiView$__Block_164_12 SuiView$__Block_164_12;

typedef struct tagSuiView$__Block_336_22 SuiView$__Block_336_22;

typedef struct tagSuiView$__Block_346_12 SuiView$__Block_346_12;

typedef struct tagSuiView$__Closure_165_45 SuiView$__Closure_165_45;

typedef struct tagSuiView$__Closure_338_45 SuiView$__Closure_338_45;

typedef struct tagSuiView$__Closure_347_29 SuiView$__Closure_347_29;

typedef struct tagSuiView$__Closure_350_29 SuiView$__Closure_350_29;



struct tagSuiView$__Block_164_12 {
	SuiView$Caret*  self ;
};





struct tagSuiView$__Block_336_22 {
	SuiView$EditText*  self ;
};





struct tagSuiView$__Block_346_12 {
	SuiView$EditText*  self ;
};





struct tagSuiView$__Closure_165_45 {
	void  (*invoke)(SuiView$__Closure_165_45 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_164_12*  __var___Block_164_12 ;
};





struct tagSuiView$__Closure_338_45 {
	void  (*invoke)(SuiView$__Closure_338_45 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_336_22*  __var___Block_336_22 ;
};





struct tagSuiView$__Closure_347_29 {
	Orc$String*  (*invoke)(SuiView$__Closure_347_29 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_346_12*  __var___Block_346_12 ;
};





struct tagSuiView$__Closure_350_29 {
	void  (*invoke)(SuiView$__Closure_350_29 *  self, const char *  text);
	Vtable_Object *  vtable ;
	SuiView$__Block_346_12*  __var___Block_346_12 ;
};





// static function declaration
static void  __finiBlock___Block_164_12(SuiView$__Block_164_12 *  self);
static void  __finiBlock___Block_336_22(SuiView$__Block_336_22 *  self);
static void  __finiBlock___Block_346_12(SuiView$__Block_346_12 *  self);
static void  __fn___Closure_165_45(SuiView$__Closure_165_45 *  self);
static void  __fini___Closure_165_45(SuiView$__Closure_165_45 *  self);
static SuiView$__Closure_165_45*  __make___Closure_165_45(SuiView$__Closure_165_45 **  __outRef__, SuiView$__Block_164_12 *  __var___Block_164_12);
static void  __fn___Closure_338_45(SuiView$__Closure_338_45 *  self);
static void  __fini___Closure_338_45(SuiView$__Closure_338_45 *  self);
static SuiView$__Closure_338_45*  __make___Closure_338_45(SuiView$__Closure_338_45 **  __outRef__, SuiView$__Block_336_22 *  __var___Block_336_22);
static Orc$String*  __fn___Closure_347_29(Orc$String **  __outRef__, SuiView$__Closure_347_29 *  self);
static void  __fini___Closure_347_29(SuiView$__Closure_347_29 *  self);
static SuiView$__Closure_347_29*  __make___Closure_347_29(SuiView$__Closure_347_29 **  __outRef__, SuiView$__Block_346_12 *  __var___Block_346_12);
static void  __fn___Closure_350_29(SuiView$__Closure_350_29 *  self, const char *  text);
static void  __fini___Closure_350_29(SuiView$__Closure_350_29 *  self);
static SuiView$__Closure_350_29*  __make___Closure_350_29(SuiView$__Closure_350_29 **  __outRef__, SuiView$__Block_346_12 *  __var___Block_346_12);



// get or init meta 
MetaStruct* SuiView$Range_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiView$Range", sizeof( SuiView$Range ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "start", OrcMetaType_int, offsetof(SuiView$Range, start), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "end", OrcMetaType_int, offsetof(SuiView$Range, end), 0, 0, 0, 0);//int
    }
	return meta;
}
SuiView$Range SuiView$mkRange(int  start, int  end){
	SuiView$Range r;
	r.start = start;
	r.end = end;
	return r; 
}


//vtable instance
Vtable_SuiView$Selection _vtable_SuiView$Selection;

// init meta

void SuiView$Selection_initMeta(Vtable_SuiView$Selection *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "start", OrcMetaType_int, offsetof(SuiView$Selection, start), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "end", OrcMetaType_int, offsetof(SuiView$Selection, end), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "get_range_value", offsetof(SuiView$Selection, get_range_value));
	orc_metaField_method(&pNext, "is_collapse", offsetof(SuiView$Selection, is_collapse));
	orc_metaField_method(&pNext, "is_range", offsetof(SuiView$Selection, is_range));
	orc_metaField_method(&pNext, "get_asc_range", offsetof(SuiView$Selection, get_asc_range));
	orc_metaField_method(&pNext, "clamp_pos", offsetof(SuiView$Selection, clamp_pos));
	orc_metaField_method(&pNext, "set_collapse_pos", offsetof(SuiView$Selection, set_collapse_pos));
	orc_metaField_method(&pNext, "set_start", offsetof(SuiView$Selection, set_start));
	orc_metaField_method(&pNext, "set_end", offsetof(SuiView$Selection, set_end));
	orc_metaField_method(&pNext, "move_delta", offsetof(SuiView$Selection, move_delta));
	orc_metaField_method(&pNext, "backspace", offsetof(SuiView$Selection, backspace));
	orc_metaField_method(&pNext, "del_range", offsetof(SuiView$Selection, del_range));
	orc_metaField_method(&pNext, "delete_act", offsetof(SuiView$Selection, delete_act));
	orc_metaField_method(&pNext, "insert", offsetof(SuiView$Selection, insert));
}


// vtable init


Vtable_SuiView$Selection* Vtable_SuiView$Selection_init(Vtable_SuiView$Selection* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Selection;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Selection_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Selection";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Selection_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Selection_fini(SuiView$Selection *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiView$Selection_init_fields(SuiView$Selection *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$Selection_fini;
	//fields
    {
	((SuiView$Selection*)self)->start = 0;
	((SuiView$Selection*)self)->end = 0;
	urgc_set_field(self, (void**)&((SuiView$Selection*)self)->get_value, NULL);
	urgc_set_field(self, (void**)&((SuiView$Selection*)self)->set_value, NULL);
    }
	((SuiView$Selection*)self)->get_range_value = (void*)SuiView$Selection$get_range_value;
	((SuiView$Selection*)self)->is_collapse = (void*)SuiView$Selection$is_collapse;
	((SuiView$Selection*)self)->is_range = (void*)SuiView$Selection$is_range;
	((SuiView$Selection*)self)->get_asc_range = (void*)SuiView$Selection$get_asc_range;
	((SuiView$Selection*)self)->clamp_pos = (void*)SuiView$Selection$clamp_pos;
	((SuiView$Selection*)self)->set_collapse_pos = (void*)SuiView$Selection$set_collapse_pos;
	((SuiView$Selection*)self)->set_start = (void*)SuiView$Selection$set_start;
	((SuiView$Selection*)self)->set_end = (void*)SuiView$Selection$set_end;
	((SuiView$Selection*)self)->move_delta = (void*)SuiView$Selection$move_delta;
	((SuiView$Selection*)self)->backspace = (void*)SuiView$Selection$backspace;
	((SuiView$Selection*)self)->del_range = (void*)SuiView$Selection$del_range;
	((SuiView$Selection*)self)->delete_act = (void*)SuiView$Selection$delete_act;
	((SuiView$Selection*)self)->insert = (void*)SuiView$Selection$insert;
}

// init function

void SuiView$Selection_init(SuiView$Selection *self, void *pOwner){
    Vtable_SuiView$Selection_init(&_vtable_SuiView$Selection);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Selection;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Selection_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Selection * SuiView$Selection_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Selection *self = calloc(1, sizeof(SuiView$Selection));
	
    SuiView$Selection_init(self, pOwner);
    return self;
}


// class members
Orc$String*  SuiView$Selection$get_range_value(Orc$String **  __outRef__, SuiView$Selection *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = (*(self->get_value))((tmp = NULL,&tmp), (void * )(self->get_value)) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$substring(&tmpReturn_1, tmp, self->start, self->end) ) ; 
}


bool  SuiView$Selection$is_collapse(SuiView$Selection *  self){
	return self->end == self->start; 
}


bool  SuiView$Selection$is_range(SuiView$Selection *  self){
	return self->end != self->start; 
}


SuiView$Range SuiView$Selection$get_asc_range(SuiView$Selection *  self){
	if (self->end < self->start) {
		return SuiView$mkRange(self->end, self->start) ; 
	}
	else {
		return SuiView$mkRange(self->start, self->end) ; 
	}
}


int  SuiView$Selection$clamp_pos(SuiView$Selection *  self, int  pos){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	int  l = Orc$String$length((*(self->get_value))(&tmpReturn_1, (void * )(self->get_value)) ) ;
	pos = Orc$clampInt(pos, 0, l) ;
	return pos; 
}


void  SuiView$Selection$set_collapse_pos(SuiView$Selection *  self, int  pos){
	pos = self->clamp_pos(self, pos) ;
	self->start = pos;
	self->end = pos;
}


void  SuiView$Selection$set_start(SuiView$Selection *  self, int  pos){
	pos = self->clamp_pos(self, pos) ;
	self->start = pos;
}


void  SuiView$Selection$set_end(SuiView$Selection *  self, int  pos){
	pos = self->clamp_pos(self, pos) ;
	self->end = pos;
}


void  SuiView$Selection$move_delta(SuiView$Selection *  self, int  delta, bool  shift){
	if (shift) {
		self->set_end(self, self->end + delta) ;
		return ; 
	}
	if (self->is_collapse(self) ) {
		self->set_collapse_pos(self, self->end + delta) ;
	}
	else {
		SuiView$Range r = self->get_asc_range(self) ;
		self->set_collapse_pos(self, delta < 0 ? r.start : r.end) ;
	}
}


Orc$String*  SuiView$Selection$backspace(Orc$String **  __outRef__, SuiView$Selection *  self){
	if (self->is_range(self) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, self->del_range(&tmpReturn_1, self) ) ; 
	}
	else {
		URGC_VAR_CLEANUP_CLASS Orc$String*  val = (*(self->get_value))((val = NULL,&val), (void * )(self->get_value)) ;
		if (self->start == 0) {
			return urgc_set_var_for_return_class((void ** )__outRef__, val) ; 
		}
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  nval = (nval=NULL,urgc_init_var_class((void**)&nval, Orc$String$addString(Orc$String$substring(&tmpReturn_2, val, 0, self->start - 1) , Orc$String$substring(&tmpReturn_3, val, self->start, Orc$String$length(val) ) ) ));
		self->set_collapse_pos(self, self->start - 1) ;
		return urgc_set_var_for_return_class((void ** )__outRef__, nval) ; 
	}
}


Orc$String*  SuiView$Selection$del_range(Orc$String **  __outRef__, SuiView$Selection *  self){
	SuiView$Range r = self->get_asc_range(self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  val = (*(self->get_value))((val = NULL,&val), (void * )(self->get_value)) ;
	self->set_collapse_pos(self, r.start) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$String$addString(Orc$String$substring(&tmpReturn_1, val, 0, r.start) , Orc$String$substringToEnd(&tmpReturn_2, val, r.end) ) ));
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


Orc$String*  SuiView$Selection$delete_act(Orc$String **  __outRef__, SuiView$Selection *  self){
	if (self->is_range(self) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, self->del_range(&tmpReturn_1, self) ) ; 
	}
	else {
		URGC_VAR_CLEANUP_CLASS Orc$String*  val = (*(self->get_value))((val = NULL,&val), (void * )(self->get_value)) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$String$addString(Orc$String$substring(&tmpReturn_2, val, 0, self->start) , Orc$String$substringToEnd(&tmpReturn_3, val, self->start + 1) ) ));
		return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


Orc$String*  SuiView$Selection$insert(Orc$String **  __outRef__, SuiView$Selection *  self, const char *  text){
	URGC_VAR_CLEANUP_CLASS Orc$String*  val = (*(self->get_value))((val = NULL,&val), (void * )(self->get_value)) ;
	SuiView$Range r = self->get_asc_range(self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  start = Orc$String$substring((start = NULL,&start), val, 0, r.start) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  end = Orc$String$substringToEnd((end = NULL,&end), val, r.end) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  nval = (nval=NULL,urgc_init_var_class((void**)&nval, Orc$String$addString(Orc$String$add(start, text) , end) ));
	(*(self->set_value))((void * )(self->set_value), nval->str) ;
	self->set_collapse_pos(self, self->start + Orc$utf8RuneLength(text) ) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, nval) ; 
}




//vtable instance
Vtable_SuiView$Caret _vtable_SuiView$Caret;

// init meta

void SuiView$Caret_initMeta(Vtable_SuiView$Caret *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "show", OrcMetaType_bool, offsetof(SuiView$Caret, show), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "blink_timer", ((Vtable_Object*)Vtable_SuiCore$Timer_init(0)), offsetof(SuiView$Caret, blink_timer), true, false, 1);
	orc_metaField_class(&pNext, "view", ((Vtable_Object*)Vtable_SuiCore$ViewBase_init(0)), offsetof(SuiView$Caret, view), true, false, 1);

	orc_metaField_method(&pNext, "isBlinking", offsetof(SuiView$Caret, isBlinking));
	orc_metaField_method(&pNext, "setShow", offsetof(SuiView$Caret, setShow));
	orc_metaField_method(&pNext, "blink", offsetof(SuiView$Caret, blink));
	orc_metaField_method(&pNext, "start", offsetof(SuiView$Caret, start));
	orc_metaField_method(&pNext, "stop", offsetof(SuiView$Caret, stop));
	orc_metaField_method(&pNext, "restart", offsetof(SuiView$Caret, restart));
}


// vtable init


Vtable_SuiView$Caret* Vtable_SuiView$Caret_init(Vtable_SuiView$Caret* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Caret;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Caret_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Caret";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Caret_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Caret_fini(SuiView$Caret *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiView$Caret_init_fields(SuiView$Caret *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$Caret_fini;
	//fields
    {
	((SuiView$Caret*)self)->show = true;
	urgc_set_field_class(self, (void**)&((SuiView$Caret*)self)->blink_timer, NULL);
	urgc_set_field_class(self, (void**)&((SuiView$Caret*)self)->view, NULL);
	urgc_set_field(self, (void**)&((SuiView$Caret*)self)->cb_notify, NULL);
    }
	((Object*)self)->ctor = (void*)SuiView$Caret$ctor;
	((SuiView$Caret*)self)->isBlinking = (void*)SuiView$Caret$isBlinking;
	((SuiView$Caret*)self)->setShow = (void*)SuiView$Caret$setShow;
	((SuiView$Caret*)self)->blink = (void*)SuiView$Caret$blink;
	((SuiView$Caret*)self)->start = (void*)SuiView$Caret$start;
	((SuiView$Caret*)self)->stop = (void*)SuiView$Caret$stop;
	((SuiView$Caret*)self)->restart = (void*)SuiView$Caret$restart;
}

// init function

void SuiView$Caret_init(SuiView$Caret *self, void *pOwner){
    Vtable_SuiView$Caret_init(&_vtable_SuiView$Caret);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Caret;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Caret_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Caret * SuiView$Caret_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Caret *self = calloc(1, sizeof(SuiView$Caret));
	
    SuiView$Caret_init(self, pOwner);
    return self;
}


// class members
void  SuiView$Caret$ctor(SuiView$Caret *  self){
	URGC_VAR_CLEANUP SuiView$__Block_164_12*  __var___Block_164_12 = (__var___Block_164_12=NULL,urgc_init_var((void**)&__var___Block_164_12, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_164_12) , __finiBlock___Block_164_12) ));
	urgc_set_field_class(__var___Block_164_12, (void * )offsetof(SuiView$__Block_164_12, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP SuiView$__Closure_165_45*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiView$Caret, blink_timer) , SuiCore$mkTimerInterval_noStart(&tmpReturn_1, __make___Closure_165_45(&tmpReturn_2, __var___Block_164_12) , 600) ) ;
}


bool  SuiView$Caret$isBlinking(SuiView$Caret *  self){
	return self->blink_timer->alive; 
}


void  SuiView$Caret$setShow(SuiView$Caret *  self, bool  _show){
	if (_show == self->show) {
		return ; 
	}
	self->show = _show;
	if (self->view) {
		self->view->invalidDraw(self->view) ;
	}
	if (self->cb_notify != NULL) {
		(*(self->cb_notify))((void * )(self->cb_notify), self) ;
	}
}


void  SuiView$Caret$blink(SuiView$Caret *  self){
	self->setShow(self, !self->show) ;
}


void  SuiView$Caret$start(SuiView$Caret *  self){
	printf("光标blink:start\n") ;
	self->blink_timer->start(self->blink_timer) ;
}


void  SuiView$Caret$stop(SuiView$Caret *  self){
	printf("光标blink:stop\n") ;
	self->setShow(self, false) ;
	self->blink_timer->cancel(self->blink_timer) ;
}


void  SuiView$Caret$restart(SuiView$Caret *  self){
	self->stop(self) ;
	self->start(self) ;
	self->show = true;
	if (self->cb_notify != NULL) {
		(*(self->cb_notify))((void * )(self->cb_notify), self) ;
	}
}




//vtable instance
Vtable_SuiView$EditText _vtable_SuiView$EditText;

// init meta

void SuiView$EditText_initMeta(Vtable_SuiView$EditText *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "value", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$EditText, value), true, false, 1);
	orc_metaField_primitive(&pNext, "font_size", OrcMetaType_int, offsetof(SuiView$EditText, font_size), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "font_face", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$EditText, font_face), true, false, 1);
	orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(SuiView$EditText, color), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "caret_color", OrcMetaType_int, offsetof(SuiView$EditText, caret_color), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "font_weight", OrcMetaType_int, offsetof(SuiView$EditText, font_weight), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "placeholder", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$EditText, placeholder), true, false, 1);
	orc_metaField_primitive(&pNext, "placeholder_color", OrcMetaType_int, offsetof(SuiView$EditText, placeholder_color), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "draw_offset", OrcMetaType_int, offsetof(SuiView$EditText, draw_offset), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "_caret_x", OrcMetaType_int, offsetof(SuiView$EditText, _caret_x), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "selection", ((Vtable_Object*)Vtable_SuiView$Selection_init(0)), offsetof(SuiView$EditText, selection), true, false, 1);
	orc_metaField_class(&pNext, "drag_timer", ((Vtable_Object*)Vtable_SuiCore$Timer_init(0)), offsetof(SuiView$EditText, drag_timer), true, false, 1);
	orc_metaField_class(&pNext, "caret", ((Vtable_Object*)Vtable_SuiView$Caret_init(0)), offsetof(SuiView$EditText, caret), true, false, 1);
	orc_metaField_class(&pNext, "text_editing", ((Vtable_Object*)Vtable_SuiCore$TextEditingEvent_init(0)), offsetof(SuiView$EditText, text_editing), true, false, 1);
	orc_metaField_class(&pNext, "_canvas", ((Vtable_Object*)Vtable_SuiCore$Canvas_init(0)), offsetof(SuiView$EditText, _canvas), false, true, 1);

	orc_metaField_method(&pNext, "setValue_notInFocus", offsetof(SuiView$EditText, setValue_notInFocus));
	orc_metaField_method(&pNext, "setValue", offsetof(SuiView$EditText, setValue));
	orc_metaField_method(&pNext, "getValue", offsetof(SuiView$EditText, getValue));
	orc_metaField_method(&pNext, "setFont_size", offsetof(SuiView$EditText, setFont_size));
	orc_metaField_method(&pNext, "getFont_size", offsetof(SuiView$EditText, getFont_size));
	orc_metaField_method(&pNext, "setFont_face", offsetof(SuiView$EditText, setFont_face));
	orc_metaField_method(&pNext, "getFont_face", offsetof(SuiView$EditText, getFont_face));
	orc_metaField_method(&pNext, "setColor", offsetof(SuiView$EditText, setColor));
	orc_metaField_method(&pNext, "getColor", offsetof(SuiView$EditText, getColor));
	orc_metaField_method(&pNext, "setCaret_color", offsetof(SuiView$EditText, setCaret_color));
	orc_metaField_method(&pNext, "getCaret_color", offsetof(SuiView$EditText, getCaret_color));
	orc_metaField_method(&pNext, "setFont_weight", offsetof(SuiView$EditText, setFont_weight));
	orc_metaField_method(&pNext, "getFont_weight", offsetof(SuiView$EditText, getFont_weight));
	orc_metaField_method(&pNext, "setPlaceholder", offsetof(SuiView$EditText, setPlaceholder));
	orc_metaField_method(&pNext, "getPlaceholder", offsetof(SuiView$EditText, getPlaceholder));
	orc_metaField_method(&pNext, "setPlaceholder_color", offsetof(SuiView$EditText, setPlaceholder_color));
	orc_metaField_method(&pNext, "getPlaceholder_color", offsetof(SuiView$EditText, getPlaceholder_color));
	orc_metaField_method(&pNext, "notify_changed", offsetof(SuiView$EditText, notify_changed));
	orc_metaField_method(&pNext, "set_value", offsetof(SuiView$EditText, set_value));
	orc_metaField_method(&pNext, "gocDragTimer", offsetof(SuiView$EditText, gocDragTimer));
	orc_metaField_method(&pNext, "on_window_focus_event", offsetof(SuiView$EditText, on_window_focus_event));
	orc_metaField_method(&pNext, "on_key_event", offsetof(SuiView$EditText, on_key_event));
	orc_metaField_method(&pNext, "on_focus_event", offsetof(SuiView$EditText, on_focus_event));
	orc_metaField_method(&pNext, "on_editing_event", offsetof(SuiView$EditText, on_editing_event));
	orc_metaField_method(&pNext, "on_input_event", offsetof(SuiView$EditText, on_input_event));
	orc_metaField_method(&pNext, "blur", offsetof(SuiView$EditText, blur));
	orc_metaField_method(&pNext, "get_x_of_position", offsetof(SuiView$EditText, get_x_of_position));
	orc_metaField_method(&pNext, "_update_text_input_rect", offsetof(SuiView$EditText, _update_text_input_rect));
	orc_metaField_method(&pNext, "update_draw_offset_by_keydown_move_with_default", offsetof(SuiView$EditText, update_draw_offset_by_keydown_move_with_default));
	orc_metaField_method(&pNext, "update_draw_offset_by_keydown_move", offsetof(SuiView$EditText, update_draw_offset_by_keydown_move));
	orc_metaField_method(&pNext, "clamp_draw_offset", offsetof(SuiView$EditText, clamp_draw_offset));
	orc_metaField_method(&pNext, "get_char_position_by_client_x", offsetof(SuiView$EditText, get_char_position_by_client_x));
	orc_metaField_method(&pNext, "on_mouse_event", offsetof(SuiView$EditText, on_mouse_event));
	orc_metaField_method(&pNext, "on_mouse_down", offsetof(SuiView$EditText, on_mouse_down));
	orc_metaField_method(&pNext, "on_rootView_mouse_up", offsetof(SuiView$EditText, on_rootView_mouse_up));
	orc_metaField_method(&pNext, "on_rootView_mouse_move", offsetof(SuiView$EditText, on_rootView_mouse_move));
	orc_metaField_method(&pNext, "_update_drag", offsetof(SuiView$EditText, _update_drag));
	orc_metaField_method(&pNext, "reset_text_editing", offsetof(SuiView$EditText, reset_text_editing));
	orc_metaField_method(&pNext, "draw_editing", offsetof(SuiView$EditText, draw_editing));
	orc_metaField_method(&pNext, "set_text_editing", offsetof(SuiView$EditText, set_text_editing));
	orc_metaField_method(&pNext, "selectAll", offsetof(SuiView$EditText, selectAll));
}


// vtable init


Vtable_SuiView$EditText* Vtable_SuiView$EditText_init(Vtable_SuiView$EditText* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$EditText;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$EditText_new;
    ((Vtable_Object*)pvt)->className = "SuiView$EditText";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$EditText_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$EditText_fini(SuiView$EditText *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiView$EditText_init_fields(SuiView$EditText *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$EditText_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$EditText*)self)->value, Orc$str(&tmpReturn_1, "") );
	((SuiView$EditText*)self)->font_size = 17;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$EditText*)self)->font_face, Orc$str(&tmpReturn_2, "") );
	((SuiView$EditText*)self)->color = 0xff000000;
	((SuiView$EditText*)self)->caret_color = 0xff000000;
	((SuiView$EditText*)self)->font_weight = 400;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$EditText*)self)->placeholder, Orc$str(&tmpReturn_3, "please input") );
	((SuiView$EditText*)self)->placeholder_color = 0xff999999;
	urgc_set_field(self, (void**)&((SuiView$EditText*)self)->onchanged, NULL);
	((SuiView$EditText*)self)->draw_offset = 0;
	((SuiView$EditText*)self)->_caret_x = 0;
	URGC_VAR_CLEANUP_CLASS SuiView$Selection*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$EditText*)self)->selection, SuiView$Selection_new(&tmpNewOwner_4) );
	urgc_set_field_class(self, (void**)&((SuiView$EditText*)self)->drag_timer, NULL);
	URGC_VAR_CLEANUP_CLASS SuiView$Caret*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$EditText*)self)->caret, SuiView$Caret_new(&tmpNewOwner_5) );
	urgc_set_field_class(self, (void**)&((SuiView$EditText*)self)->text_editing, NULL);
	urgc_set_field(self, (void**)&((SuiView$EditText*)self)->onValueChanged, NULL);
	((SuiView$EditText*)self)->_canvas = NULL;
    }
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiView$EditText$layoutContent;
	((SuiView$EditText*)self)->setValue_notInFocus = (void*)SuiView$EditText$setValue_notInFocus;
	((SuiView$EditText*)self)->setValue = (void*)SuiView$EditText$setValue;
	((SuiView$EditText*)self)->getValue = (void*)SuiView$EditText$getValue;
	((SuiView$EditText*)self)->setFont_size = (void*)SuiView$EditText$setFont_size;
	((SuiView$EditText*)self)->getFont_size = (void*)SuiView$EditText$getFont_size;
	((SuiView$EditText*)self)->setFont_face = (void*)SuiView$EditText$setFont_face;
	((SuiView$EditText*)self)->getFont_face = (void*)SuiView$EditText$getFont_face;
	((SuiView$EditText*)self)->setColor = (void*)SuiView$EditText$setColor;
	((SuiView$EditText*)self)->getColor = (void*)SuiView$EditText$getColor;
	((SuiView$EditText*)self)->setCaret_color = (void*)SuiView$EditText$setCaret_color;
	((SuiView$EditText*)self)->getCaret_color = (void*)SuiView$EditText$getCaret_color;
	((SuiView$EditText*)self)->setFont_weight = (void*)SuiView$EditText$setFont_weight;
	((SuiView$EditText*)self)->getFont_weight = (void*)SuiView$EditText$getFont_weight;
	((SuiView$EditText*)self)->setPlaceholder = (void*)SuiView$EditText$setPlaceholder;
	((SuiView$EditText*)self)->getPlaceholder = (void*)SuiView$EditText$getPlaceholder;
	((SuiView$EditText*)self)->setPlaceholder_color = (void*)SuiView$EditText$setPlaceholder_color;
	((SuiView$EditText*)self)->getPlaceholder_color = (void*)SuiView$EditText$getPlaceholder_color;
	((SuiView$EditText*)self)->notify_changed = (void*)SuiView$EditText$notify_changed;
	((SuiView$EditText*)self)->set_value = (void*)SuiView$EditText$set_value;
	((SuiView$EditText*)self)->gocDragTimer = (void*)SuiView$EditText$gocDragTimer;
	((Object*)self)->ctor = (void*)SuiView$EditText$ctor;
	((SuiCore$Node*)self)->react = (void*)SuiView$EditText$react;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$EditText$draw_self;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$EditText$onEvent;
	((SuiView$EditText*)self)->on_window_focus_event = (void*)SuiView$EditText$on_window_focus_event;
	((SuiView$EditText*)self)->on_key_event = (void*)SuiView$EditText$on_key_event;
	((SuiView$EditText*)self)->on_focus_event = (void*)SuiView$EditText$on_focus_event;
	((SuiView$EditText*)self)->on_editing_event = (void*)SuiView$EditText$on_editing_event;
	((SuiView$EditText*)self)->on_input_event = (void*)SuiView$EditText$on_input_event;
	((SuiCore$Node*)self)->onUnmounting = (void*)SuiView$EditText$onUnmounting;
	((SuiView$EditText*)self)->blur = (void*)SuiView$EditText$blur;
	((SuiView$EditText*)self)->get_x_of_position = (void*)SuiView$EditText$get_x_of_position;
	((SuiView$EditText*)self)->_update_text_input_rect = (void*)SuiView$EditText$_update_text_input_rect;
	((SuiView$EditText*)self)->update_draw_offset_by_keydown_move_with_default = (void*)SuiView$EditText$update_draw_offset_by_keydown_move_with_default;
	((SuiView$EditText*)self)->update_draw_offset_by_keydown_move = (void*)SuiView$EditText$update_draw_offset_by_keydown_move;
	((SuiView$EditText*)self)->clamp_draw_offset = (void*)SuiView$EditText$clamp_draw_offset;
	((SuiView$EditText*)self)->get_char_position_by_client_x = (void*)SuiView$EditText$get_char_position_by_client_x;
	((SuiView$EditText*)self)->on_mouse_event = (void*)SuiView$EditText$on_mouse_event;
	((SuiView$EditText*)self)->on_mouse_down = (void*)SuiView$EditText$on_mouse_down;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiView$EditText$onListenerEvent;
	((SuiView$EditText*)self)->on_rootView_mouse_up = (void*)SuiView$EditText$on_rootView_mouse_up;
	((SuiView$EditText*)self)->on_rootView_mouse_move = (void*)SuiView$EditText$on_rootView_mouse_move;
	((SuiView$EditText*)self)->_update_drag = (void*)SuiView$EditText$_update_drag;
	((SuiView$EditText*)self)->reset_text_editing = (void*)SuiView$EditText$reset_text_editing;
	((SuiView$EditText*)self)->draw_editing = (void*)SuiView$EditText$draw_editing;
	((SuiView$EditText*)self)->set_text_editing = (void*)SuiView$EditText$set_text_editing;
	((SuiView$EditText*)self)->selectAll = (void*)SuiView$EditText$selectAll;
}

// init function

void SuiView$EditText_init(SuiView$EditText *self, void *pOwner){
    Vtable_SuiView$EditText_init(&_vtable_SuiView$EditText);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$EditText;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$EditText_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$EditText * SuiView$EditText_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$EditText *self = calloc(1, sizeof(SuiView$EditText));
	
    SuiView$EditText_init(self, pOwner);
    return self;
}


// class members
void  SuiView$EditText$layoutContent(SuiView$EditText *  self, SuiCore$Frame *  ctx){
	
}


void  SuiView$EditText$setValue_notInFocus(SuiView$EditText *  self, Orc$String *  v){
	SuiCore$Focus *  tmpThis_1 = NULL;
	if (!(tmpThis_1 = SuiCore$insFocus() )->isFocus(tmpThis_1, self) ) {
		self->setValue(self, v) ;
	}
}


void  SuiView$EditText$setValue(SuiView$EditText *  self, Orc$String *  v){
	if (Orc$String$notEquals(self->value, v->str) ) {
		urgc_set_field_class(self, (void * )offsetof(SuiView$EditText, value) , v) ;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


Orc$String *  SuiView$EditText$getValue(SuiView$EditText *  self){
	return self->value; 
}


void  SuiView$EditText$setFont_size(SuiView$EditText *  self, int  v){
	if (v != self->font_size) {
		self->font_size = v;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


int  SuiView$EditText$getFont_size(SuiView$EditText *  self){
	return self->font_size; 
}


void  SuiView$EditText$setFont_face(SuiView$EditText *  self, Orc$String *  v){
	if (Orc$String$notEquals(self->font_face, v->str) ) {
		urgc_set_field_class(self, (void * )offsetof(SuiView$EditText, font_face) , v) ;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


Orc$String *  SuiView$EditText$getFont_face(SuiView$EditText *  self){
	return self->font_face; 
}


void  SuiView$EditText$setColor(SuiView$EditText *  self, int  v){
	if (v != self->color) {
		self->color = v;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


int  SuiView$EditText$getColor(SuiView$EditText *  self){
	return self->color; 
}


void  SuiView$EditText$setCaret_color(SuiView$EditText *  self, int  v){
	if (v != self->caret_color) {
		self->caret_color = v;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


int  SuiView$EditText$getCaret_color(SuiView$EditText *  self){
	return self->caret_color; 
}


void  SuiView$EditText$setFont_weight(SuiView$EditText *  self, int  v){
	if (v != self->font_weight) {
		self->font_weight = v;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


int  SuiView$EditText$getFont_weight(SuiView$EditText *  self){
	return self->font_weight; 
}


void  SuiView$EditText$setPlaceholder(SuiView$EditText *  self, Orc$String *  v){
	if (v != self->placeholder) {
		urgc_set_field_class(self, (void * )offsetof(SuiView$EditText, placeholder) , v) ;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


Orc$String *  SuiView$EditText$getPlaceholder(SuiView$EditText *  self){
	return self->placeholder; 
}


void  SuiView$EditText$setPlaceholder_color(SuiView$EditText *  self, int  v){
	if (v != self->placeholder_color) {
		self->placeholder_color = v;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


int  SuiView$EditText$getPlaceholder_color(SuiView$EditText *  self){
	return self->placeholder_color; 
}


void  SuiView$EditText$notify_changed(SuiView$EditText *  self, bool  by_user_event){
	if (self->onValueChanged) {
		(*(self->onValueChanged))((void * )(self->onValueChanged), self) ;
	}
}


void  SuiView$EditText$set_value(SuiView$EditText *  self, Orc$String*  nvalue, bool  by_user_event){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(nvalue);

	if (nvalue == NULL) {
		if (Orc$String$equals(self->value, "") ) {
			return ; 
		}
		else {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			urgc_set_var_class(&nvalue, Orc$str(&tmpReturn_1, "") ) ;
		}
	}
	printf("EditText.set_value:%s=>%s\n", self->value->str, nvalue->str) ;
	urgc_set_field_class(self, (void * )offsetof(SuiView$EditText, value) , nvalue) ;
	self->notify_changed(self, by_user_event) ;
}


SuiCore$Timer *  SuiView$EditText$gocDragTimer(SuiView$EditText *  self){
	URGC_VAR_CLEANUP SuiView$__Block_336_22*  __var___Block_336_22 = (__var___Block_336_22=NULL,urgc_init_var((void**)&__var___Block_336_22, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_336_22) , __finiBlock___Block_336_22) ));
	urgc_set_field_class(__var___Block_336_22, (void * )offsetof(SuiView$__Block_336_22, self) , self) ;
	if (self->drag_timer == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP SuiView$__Closure_338_45*  tmpReturn_2 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiView$EditText, drag_timer) , SuiCore$mkTimerInterval_noStart(&tmpReturn_1, __make___Closure_338_45(&tmpReturn_2, __var___Block_336_22) , 10) ) ;
	}
	return self->drag_timer; 
}


void  SuiView$EditText$ctor(SuiView$EditText *  self){
	URGC_VAR_CLEANUP SuiView$__Block_346_12*  __var___Block_346_12 = (__var___Block_346_12=NULL,urgc_init_var((void**)&__var___Block_346_12, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_346_12) , __finiBlock___Block_346_12) ));
	urgc_set_field_class(__var___Block_346_12, (void * )offsetof(SuiView$__Block_346_12, self) , self) ;
	URGC_VAR_CLEANUP SuiView$__Closure_347_29*  tmpReturn_1 = NULL;
	urgc_set_field(self->selection, (void * )offsetof(SuiView$Selection, get_value) , __make___Closure_347_29(&tmpReturn_1, __var___Block_346_12) ) ;
	URGC_VAR_CLEANUP SuiView$__Closure_350_29*  tmpReturn_2 = NULL;
	urgc_set_field(self->selection, (void * )offsetof(SuiView$Selection, set_value) , __make___Closure_350_29(&tmpReturn_2, __var___Block_346_12) ) ;
	urgc_set_field_class(self->caret, (void * )offsetof(SuiView$Caret, view) , self) ;
	((SuiCore$View * )self)->width = 50;
	((SuiCore$View * )self)->height = 26;
	((SuiCore$View * )self)->needClip = true;
}


void  SuiView$EditText$react(SuiView$EditText *  self){
	
}


void  SuiView$EditText$draw_self(SuiView$EditText *  self, SuiCore$Canvas *  canvas){
	self->_canvas = canvas;
	int  x = 0;
	int  y = 0;
	int  w = ((SuiCore$ViewBase * )self)->frame.width;
	int  h = ((SuiCore$ViewBase * )self)->frame.height;
	int  cornerRadius = 5;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$roundRect(canvas, x + 1, y + 1, w - 2, h - 2, 4 - 1) ;
	SuiCore$Canvas$boxGradient(canvas, true, x + 1, y + 1 + 1.5f, w - 2, h - 2, 3, 4, SuiCore$mkIntByRgba(53, 64, 64, 32) , SuiCore$mkIntByRgba(0, 0, 0, 32) ) ;
	SuiCore$Canvas$fill(canvas) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$roundRect(canvas, x + 0.5f, y + 0.5f, w - 1, h - 1, 4 - 0.5f) ;
	SuiCore$Canvas$strokeColorByInt32(canvas, SuiCore$mkIntByRgba(0, 0, 0, 48) ) ;
	SuiCore$Canvas$stroke(canvas) ;
	SuiCore$Canvas$fontSize(canvas, self->font_size) ;
	float  hor = SuiCore$Inset$hor(&((SuiCore$View * )self)->margin) ;
	float  ver = SuiCore$Inset$ver(&((SuiCore$View * )self)->margin) ;
	float  startOffset = 0.0;
	float  scissorW = w - startOffset * 2;
	SuiView$Range range = self->selection->get_asc_range(self->selection) ;
	float  caretY = 4;
	if (self->caret->isBlinking(self->caret)  && self->caret->show) {
		float  caretX = startOffset - 2 + self->draw_offset + self->get_x_of_position(self, range.start) ;
		SuiCore$Canvas$fillColorByInt32(canvas, (self->caret_color)) ;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$rect(canvas, caretX + 1, caretY, 2, h - caretY * 2) ;
		SuiCore$Canvas$fill(canvas) ;
	}
	SuiCore$Canvas$intersectScissor(canvas, startOffset, 0.0f, scissorW, h) ;
	if (self->selection->is_range(self->selection) ) {
		float  x = self->get_x_of_position(self, range.start)  + self->draw_offset;
		float  end_x = self->get_x_of_position(self, range.end)  + self->draw_offset;
		SuiCore$Canvas$fillColorByInt32(canvas, 0xc97ed3ff) ;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$rect(canvas, x, caretY, end_x - x, h - caretY * 2) ;
		SuiCore$Canvas$fill(canvas) ;
	}
	self->draw_editing(self, canvas, h) ;
	if (Orc$String$empty(self->value)  && !Orc$String$empty(self->placeholder) ) {
		SuiCore$Canvas$fillColorByInt32(canvas, (self->color)) ;
		SuiCore$Canvas$textAlign(canvas, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE) ;
		SuiCore$Canvas$text(canvas, x + h * 0.3f, y + h * 0.5f, self->placeholder->str) ;
	}
	if (!Orc$String$empty(self->value) ) {
		SuiCore$Canvas$fillColorByInt32(canvas, self->color) ;
		SuiCore$Canvas$textAlign(canvas, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE) ;
		float  textX = x + startOffset + self->draw_offset;
		SuiCore$Canvas$text(canvas, textX, y + h * 0.5f, self->value->str) ;
	}
}


void  SuiView$EditText$onEvent(SuiView$EditText *  self, SuiCore$Event *  evt){
	if (Orc_instanceof((Object*)evt, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )evt;
		self->on_mouse_event(self, me) ;
	}
	else if (Orc_instanceof((Object*)evt, (Vtable_Object*)Vtable_SuiCore$KeyEvent_init(NULL))) {
		SuiCore$KeyEvent *  ke = (SuiCore$KeyEvent * )evt;
		self->on_key_event(self, ke) ;
	}
	else if (Orc_instanceof((Object*)evt, (Vtable_Object*)Vtable_SuiCore$FocusEvent_init(NULL))) {
		SuiCore$FocusEvent *  fe = (SuiCore$FocusEvent * )evt;
		self->on_focus_event(self, fe) ;
	}
	else if (Orc_instanceof((Object*)evt, (Vtable_Object*)Vtable_SuiCore$TextEditingEvent_init(NULL))) {
		SuiCore$TextEditingEvent *  e2 = (SuiCore$TextEditingEvent * )evt;
		self->on_editing_event(self, e2) ;
	}
	else if (Orc_instanceof((Object*)evt, (Vtable_Object*)Vtable_SuiCore$TextInputEvent_init(NULL))) {
		SuiCore$TextInputEvent *  e2 = (SuiCore$TextInputEvent * )evt;
		self->on_input_event(self, e2) ;
	}
	else if (Orc_instanceof((Object*)evt, (Vtable_Object*)Vtable_SuiCore$WindowFocusEvent_init(NULL))) {
		SuiCore$WindowFocusEvent *  e2 = (SuiCore$WindowFocusEvent * )evt;
		self->on_window_focus_event(self, e2) ;
	}
}


void  SuiView$EditText$on_window_focus_event(SuiView$EditText *  self, SuiCore$WindowFocusEvent *  e){
	if (e->isFocus) {
		
	}
	else if (e->isBlur) {
		self->blur(self) ;
	}
}


void  SuiView$EditText$on_key_event(SuiView$EditText *  self, SuiCore$KeyEvent *  e){
	if (e->isKeyDown) {
		if (Orc$String$equals(e->key, "left") ) {
			self->selection->move_delta(self->selection, -1, e->shift) ;
			self->caret->restart(self->caret) ;
			self->update_draw_offset_by_keydown_move_with_default(self) ;
			((SuiCore$ViewBase * )self)->invalidDraw(self) ;
			((SuiCore$Event * )e)->stopPropagation(e) ;
		}
		else if (Orc$String$equals(e->key, "right") ) {
			self->selection->move_delta(self->selection, 1, e->shift) ;
			self->caret->restart(self->caret) ;
			self->update_draw_offset_by_keydown_move_with_default(self) ;
			((SuiCore$ViewBase * )self)->invalidDraw(self) ;
		}
		else if (Orc$String$equals(e->key, "backspace") ) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			self->set_value(self, self->selection->backspace(&tmpReturn_1, self->selection) , true) ;
			self->caret->restart(self->caret) ;
			self->update_draw_offset_by_keydown_move(self, 0.5, true) ;
			((SuiCore$ViewBase * )self)->invalidDraw(self) ;
		}
		else if (Orc$String$equals(e->key, "delete") ) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
			self->set_value(self, self->selection->delete_act(&tmpReturn_2, self->selection) , true) ;
			self->caret->restart(self->caret) ;
			self->update_draw_offset_by_keydown_move(self, 0.5, true) ;
			((SuiCore$ViewBase * )self)->invalidDraw(self) ;
		}
		else if (Orc$String$equals(e->key, "return") ) {
			self->blur(self) ;
		}
		else if (e->ctrl && Orc$String$equalsIgnoreCase(e->key, "c") ) {
			if (self->selection->is_range(self->selection) ) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  v = self->selection->get_range_value((v = NULL,&v), self->selection) ;
				SuiCore$clipboard_setText(v->str) ;
				printf("\n已复制:%s\n\n", v->str) ;
			}
		}
		else if (e->ctrl && Orc$String$equalsIgnoreCase(e->key, "v") ) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  v = SuiCore$clipboard_getText((v = NULL,&v)) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  nv = self->selection->insert((nv = NULL,&nv), self->selection, v->str) ;
			printf("paste nv:%s\n", nv->str) ;
			self->set_value(self, nv, true) ;
			self->caret->restart(self->caret) ;
			self->update_draw_offset_by_keydown_move_with_default(self) ;
			((SuiCore$ViewBase * )self)->invalidDraw(self) ;
		}
		else if (e->ctrl && Orc$String$equalsIgnoreCase(e->key, "x") ) {
			if (self->selection->is_range(self->selection) ) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  nv = self->selection->delete_act((nv = NULL,&nv), self->selection) ;
				printf("cut 选区。 nv:%s\n", nv->str) ;
				self->set_value(self, nv, true) ;
				self->caret->restart(self->caret) ;
				((SuiCore$ViewBase * )self)->invalidDraw(self) ;
			}
		}
		else if (e->ctrl && Orc$String$equalsIgnoreCase(e->key, "a") ) {
			self->selection->set_start(self->selection, 0) ;
			self->selection->set_end(self->selection, Orc$String$size(self->value) ) ;
			self->caret->restart(self->caret) ;
			((SuiCore$ViewBase * )self)->invalidDraw(self) ;
			((SuiCore$Event * )e)->stopPropagation(e) ;
		}
	}
}


void  SuiView$EditText$on_focus_event(SuiView$EditText *  self, SuiCore$FocusEvent *  evt){
	printf("EditText 焦点事件 isFocus:%d, isBlur:%d\n", evt->isFocus, evt->isBlur) ;
	if (evt->isFocus) {
		self->caret->restart(self->caret) ;
		self->_update_text_input_rect(self) ;
	}
	else if (evt->isBlur) {
		self->selection->set_collapse_pos(self->selection, self->selection->start) ;
		self->caret->stop(self->caret) ;
	}
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


void  SuiView$EditText$on_editing_event(SuiView$EditText *  self, SuiCore$TextEditingEvent *  evt){
	printf("EditText 收到IME合成事件:%s, start:%d\n", evt->text->str, evt->start) ;
	self->set_text_editing(self, evt) ;
}


void  SuiView$EditText$on_input_event(SuiView$EditText *  self, SuiCore$TextInputEvent *  e){
	printf("EditText 收到字符事件:%s\n", e->text->str) ;
	if (Orc$String$size(e->text)  == 1) {
		char  c = e->text->str[0];
		if (c == 0x08 || c == 0x0a || c == 0x1b || c == 0x0d) {
			return ; 
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  new_value = self->selection->insert((new_value = NULL,&new_value), self->selection, e->text->str) ;
	self->set_value(self, new_value, true) ;
	self->update_draw_offset_by_keydown_move_with_default(self) ;
	self->caret->restart(self->caret) ;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


void  SuiView$EditText$onUnmounting(SuiView$EditText *  self){
	self->blur(self) ;
}


void  SuiView$EditText$blur(SuiView$EditText *  self){
	SuiCore$Focus *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$insFocus() )->blurNode(tmpThis_1, self) ;
	self->caret->stop(self->caret) ;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


float  SuiView$EditText$get_x_of_position(SuiView$EditText *  self, int  pos){
	if (self->_canvas == NULL) {
		return 0; 
	}
	if (pos == 0) {
		return 0; 
	}
	float  bounds[4];
	bounds[0] = 0.0;
	bounds[1] = 0.0;
	bounds[2] = 0.0;
	bounds[3] = 0.0;
	int  charLen = Orc$utf8NumberCharLen(self->value->str, pos) ;
	SuiCore$Canvas$fontSize(self->_canvas, self->font_size) ;
	float  w = SuiCore$Canvas$textBounds(self->_canvas, 0, 0, self->value->str, self->value->str + charLen, bounds) ;
	return w; 
}


void  SuiView$EditText$_update_text_input_rect(SuiView$EditText *  self){
	
}


void  SuiView$EditText$update_draw_offset_by_keydown_move_with_default(SuiView$EditText *  self){
	self->update_draw_offset_by_keydown_move(self, 0.5, false) ;
}


void  SuiView$EditText$update_draw_offset_by_keydown_move(SuiView$EditText *  self, float  target_caret_ratio, bool  force){
	SuiCore$Rect rect = ((SuiCore$View * )self)->getContentLocalRect(self) ;
	float  x_from_start = self->get_x_of_position(self, self->selection->end) ;
	float  x = x_from_start + self->draw_offset;
	if (force || x < self->font_size / 2.0 || x >= rect.w - self->font_size / 2.0) {
		int  new_draw_offset = self->clamp_draw_offset(self, -x_from_start + rect.w * target_caret_ratio) ;
		printf("更新滚动偏移:%d -> %d\n", self->draw_offset, new_draw_offset) ;
		self->draw_offset = new_draw_offset;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


int  SuiView$EditText$clamp_draw_offset(SuiView$EditText *  self, int  offset){
	float  full_w = self->get_x_of_position(self, Orc$String$size(self->value) ) ;
	SuiCore$Rect rect = ((SuiCore$View * )self)->getContentLocalRect(self) ;
	return Orc$clampFloat(offset, Orc$minFloat(0.0, -full_w + rect.w) , 0.0) ; 
}


int  SuiView$EditText$get_char_position_by_client_x(SuiView$EditText *  self, int  client_x){
	SuiCore$Rect absRect = ((SuiCore$ViewBase * )self)->get_abs_rect(self) ;
	SuiCore$Rect lr = ((SuiCore$View * )self)->getContentLocalRect(self) ;
	float  dx = client_x - absRect.x;
	float  x_from_start = dx - self->draw_offset;
	int  guess_pos = (int )(x_from_start / Orc$maxInt(1, self->font_size + 2) );
	int  l = Orc$String$size(self->value)  + 1;
	for (int  i = Orc$maxInt(guess_pos, 1) ; i < l; i++) {
		float  width = self->get_x_of_position(self, i) ;
		if (width >= x_from_start) {
			float  prevWidth = self->get_x_of_position(self, i - 1) ;
			float  charWidth = width - prevWidth;
			float  dx_to_end = width - x_from_start;
			if (dx_to_end > charWidth / 2.0) {
				return Orc$maxInt(0, i - 1) ; 
			}
			else {
				return i; 
			}
		}
	}
	return Orc$String$size(self->value) ; 
}


void  SuiView$EditText$on_mouse_event(SuiView$EditText *  self, SuiCore$MouseEvent *  e){
	if (e->isMouseDown) {
		self->on_mouse_down(self, e) ;
	}
}


void  SuiView$EditText$on_mouse_down(SuiView$EditText *  self, SuiCore$MouseEvent *  e){
	int  position = self->get_char_position_by_client_x(self, e->clientX) ;
	printf("EditText.mousedown position:%d. shift:%d\n", position, e->shift) ;
	if (e->shift) {
		self->selection->set_end(self->selection, position) ;
	}
	else {
		self->selection->set_collapse_pos(self->selection, position) ;
	}
	SuiCore$Focus *  f = SuiCore$insFocus() ;
	f->focus(f, self) ;
	self->caret->restart(self->caret) ;
	((SuiCore$Event * )e)->stopPropagation(e) ;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	SuiCore$Timer *  tmpThis_1 = NULL;
	(tmpThis_1 = self->gocDragTimer(self) )->start(tmpThis_1) ;
	if (e->window != NULL && e->window->rootView != NULL) {
		((SuiCore$Emitter * )e->window->rootView)->addListenerOnce(e->window->rootView, self) ;
	}
}


void  SuiView$EditText$onListenerEvent(SuiView$EditText *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (((SuiCore$ViewEvent * )me)->isCapture && me->isMouseMove && ((SuiCore$ViewEvent * )me)->currentTarget == me->window->rootView) {
			self->on_rootView_mouse_move(self, me) ;
		}
		if (((SuiCore$ViewEvent * )me)->isCapture && me->isMouseUp && ((SuiCore$ViewEvent * )me)->currentTarget == me->window->rootView) {
			self->on_rootView_mouse_up(self, me) ;
		}
	}
}


void  SuiView$EditText$on_rootView_mouse_up(SuiView$EditText *  self, SuiCore$MouseEvent *  e){
	((SuiCore$Event * )e)->stopPropagation(e) ;
	if (e->window != NULL && e->window->rootView != NULL) {
		((SuiCore$Emitter * )e->window->rootView)->removeListener(e->window->rootView, self) ;
	}
	printf("\n\n\nEditText 处理rootView mouse_up事件\n\n\n") ;
	SuiCore$Timer *  tmpThis_1 = NULL;
	(tmpThis_1 = self->gocDragTimer(self) )->cancel(tmpThis_1) ;
}


void  SuiView$EditText$on_rootView_mouse_move(SuiView$EditText *  self, SuiCore$MouseEvent *  e){
	((SuiCore$Event * )e)->stopPropagation(e) ;
	printf("EditText 处理rootView mouse_move事件\n") ;
	int  position = self->get_char_position_by_client_x(self, e->clientX) ;
	if (self->selection->end != position) {
		self->selection->set_end(self->selection, position) ;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


void  SuiView$EditText$_update_drag(SuiView$EditText *  self){
	if (((SuiCore$Node * )self)->ownerWindow == NULL) {
		return ; 
	}
	SuiCore$Rect abs = ((SuiCore$ViewBase * )self)->get_abs_rect(self) ;
	SuiCore$Rect lr = ((SuiCore$View * )self)->getContentLocalRect(self) ;
	SuiCore$Vec2 pos = SuiCore$Mouse_getPosOfWindow(((SuiCore$Node * )self)->ownerWindow) ;
	int  client_x = pos.x;
	int  client_y = pos.y;
	int  dx = client_x - abs.x + lr.x;
	int  noffset = self->draw_offset;
	if (dx < self->font_size / 2.0f) {
		noffset = self->clamp_draw_offset(self, self->draw_offset + self->font_size / 2.0f) ;
	}
	else if (dx > lr.w - self->font_size / 2.0f) {
		noffset = self->clamp_draw_offset(self, self->draw_offset - self->font_size / 2.0f) ;
	}
	printf("_update_drag ============= old:%d, new:%d, dx:%d clientX:%d abs.x:%f, lr.x:%f\n", self->draw_offset, noffset, dx, client_x, abs.x, lr.x) ;
	if (noffset != self->draw_offset) {
		self->draw_offset = noffset;
	}
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


void  SuiView$EditText$reset_text_editing(SuiView$EditText *  self){
	self->set_text_editing(self, NULL) ;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


void  SuiView$EditText$draw_editing(SuiView$EditText *  self, SuiCore$Canvas *  canvas, int  h){
	if (self->text_editing == NULL) {
		return ; 
	}
	int  start = self->selection->start - self->text_editing->start;
	int  runelen = self->text_editing->start + self->text_editing->length;
	URGC_VAR_CLEANUP_CLASS Orc$String*  pre = Orc$String$substring((pre = NULL,&pre), self->value, 0, start) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  subfix = Orc$String$substringToEnd((subfix = NULL,&subfix), self->value, start + runelen) ;
	int  x0 = self->get_x_of_position(self, start)  + self->draw_offset;
	int  x1 = self->get_x_of_position(self, start + runelen)  + self->draw_offset;
	float  caretY = 8;
	SuiCore$Canvas$fillColorByInt32(canvas, (0xc97ed3ff)) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, x0, caretY, x1 - x0, h - caretY * 2) ;
	SuiCore$Canvas$fill(canvas) ;
}


void  SuiView$EditText$set_text_editing(SuiView$EditText *  self, SuiCore$TextEditingEvent *  evt){
	SuiCore$TextEditingEvent *  prev = self->text_editing;
	int  start = self->selection->start;
	int  runelen = 0;
	if (prev != NULL) {
		start = self->selection->start - prev->start;
		runelen = prev->start + prev->length;
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  pre = Orc$String$substring((pre = NULL,&pre), self->value, 0, start) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  subfix = Orc$String$substringToEnd((subfix = NULL,&subfix), self->value, start + runelen) ;
	urgc_set_field_class(self, (void * )offsetof(SuiView$EditText, value) , Orc$String$addString(Orc$String$addString(pre, evt->text) , subfix) ) ;
	self->notify_changed(self, evt != NULL) ;
	self->selection->set_collapse_pos(self->selection, start + evt->start) ;
	urgc_set_field_class(self, (void * )offsetof(SuiView$EditText, text_editing) , evt) ;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	self->_update_text_input_rect(self) ;
}


void  SuiView$EditText$selectAll(SuiView$EditText *  self){
	self->selection->set_start(self->selection, 0) ;
	self->selection->set_end(self->selection, Orc$String$size(self->value) ) ;
	self->caret->restart(self->caret) ;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}



static void  __finiBlock___Block_164_12(SuiView$__Block_164_12 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_164_12, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_336_22(SuiView$__Block_336_22 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_336_22, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_346_12(SuiView$__Block_346_12 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_346_12, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_165_45(SuiView$__Closure_165_45 *  self){
	self->__var___Block_164_12->self->blink(self->__var___Block_164_12->self) ;
}

static void  __fini___Closure_165_45(SuiView$__Closure_165_45 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_165_45, __var___Block_164_12) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_165_45*  __make___Closure_165_45(SuiView$__Closure_165_45 **  __outRef__, SuiView$__Block_164_12 *  __var___Block_164_12){
	URGC_VAR_CLEANUP SuiView$__Closure_165_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_165_45) , __fini___Closure_165_45) ));
	self->invoke = __fn___Closure_165_45;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_165_45, __var___Block_164_12) , __var___Block_164_12) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_338_45(SuiView$__Closure_338_45 *  self){
	printf("drag_timer.....定时器\n") ;
	self->__var___Block_336_22->self->_update_drag(self->__var___Block_336_22->self) ;
}

static void  __fini___Closure_338_45(SuiView$__Closure_338_45 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_338_45, __var___Block_336_22) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_338_45*  __make___Closure_338_45(SuiView$__Closure_338_45 **  __outRef__, SuiView$__Block_336_22 *  __var___Block_336_22){
	URGC_VAR_CLEANUP SuiView$__Closure_338_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_338_45) , __fini___Closure_338_45) ));
	self->invoke = __fn___Closure_338_45;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_338_45, __var___Block_336_22) , __var___Block_336_22) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static Orc$String*  __fn___Closure_347_29(Orc$String **  __outRef__, SuiView$__Closure_347_29 *  self){
	return urgc_set_var_for_return_class((void ** )__outRef__, self->__var___Block_346_12->self->value) ; 
}

static void  __fini___Closure_347_29(SuiView$__Closure_347_29 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_347_29, __var___Block_346_12) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_347_29*  __make___Closure_347_29(SuiView$__Closure_347_29 **  __outRef__, SuiView$__Block_346_12 *  __var___Block_346_12){
	URGC_VAR_CLEANUP SuiView$__Closure_347_29*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_347_29) , __fini___Closure_347_29) ));
	self->invoke = __fn___Closure_347_29;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_347_29, __var___Block_346_12) , __var___Block_346_12) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_350_29(SuiView$__Closure_350_29 *  self, const char *  text){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self->__var___Block_346_12->self, (void * )offsetof(SuiView$EditText, value) , Orc$str(&tmpReturn_1, text) ) ;
}

static void  __fini___Closure_350_29(SuiView$__Closure_350_29 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_350_29, __var___Block_346_12) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_350_29*  __make___Closure_350_29(SuiView$__Closure_350_29 **  __outRef__, SuiView$__Block_346_12 *  __var___Block_346_12){
	URGC_VAR_CLEANUP SuiView$__Closure_350_29*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_350_29) , __fini___Closure_350_29) ));
	self->invoke = __fn___Closure_350_29;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_350_29, __var___Block_346_12) , __var___Block_346_12) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$EditText*  SuiView$mkEditText(SuiView$EditText **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$EditText* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$EditText_init(NULL)) ) ; 
}



