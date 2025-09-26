
#include "ProgressView_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Color_orc.h"
#include "../View/Drag_orc.h"
#include "../Core/Canvas_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Timer_orc.h"
#include "../../Orc/Math_orc.h"


// static struct 
typedef struct tagSuiView$__Block_36_22 SuiView$__Block_36_22;

typedef struct tagSuiView$__Closure_40_18 SuiView$__Closure_40_18;



struct tagSuiView$__Block_36_22 {
	SuiView$ProgressView*  self ;
};





struct tagSuiView$__Closure_40_18 {
	void  (*invoke)(SuiView$__Closure_40_18 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_36_22*  __var___Block_36_22 ;
};





// static function declaration
static void  __finiBlock___Block_36_22(SuiView$__Block_36_22 *  self);
static void  __fn___Closure_40_18(SuiView$__Closure_40_18 *  self);
static void  __fini___Closure_40_18(SuiView$__Closure_40_18 *  self);
static SuiView$__Closure_40_18*  __make___Closure_40_18(SuiView$__Closure_40_18 **  __outRef__, SuiView$__Block_36_22 *  __var___Block_36_22);



//vtable instance
Vtable_SuiView$ProgressView _vtable_SuiView$ProgressView;

// init meta

void SuiView$ProgressView_initMeta(Vtable_SuiView$ProgressView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_float, offsetof(SuiView$ProgressView, value), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "valueForAnim", OrcMetaType_float, offsetof(SuiView$ProgressView, valueForAnim), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "anim", ((Vtable_Object*)Vtable_SuiCore$AnimStep_init(0)), offsetof(SuiView$ProgressView, anim), true, false, 1);

	orc_metaField_method(&pNext, "startValueAnim", offsetof(SuiView$ProgressView, startValueAnim));
	orc_metaField_method(&pNext, "setValue", offsetof(SuiView$ProgressView, setValue));
}


// vtable init


Vtable_SuiView$ProgressView* Vtable_SuiView$ProgressView_init(Vtable_SuiView$ProgressView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$ProgressView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$ProgressView_new;
    ((Vtable_Object*)pvt)->className = "SuiView$ProgressView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$ProgressView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$ProgressView_fini(SuiView$ProgressView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiView$ProgressView_init_fields(SuiView$ProgressView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$ProgressView_fini;
	//fields
    {
	((SuiView$ProgressView*)self)->value = 0.0;
	((SuiView$ProgressView*)self)->valueForAnim = 0.0;
	urgc_set_field_class(self, (void**)&((SuiView$ProgressView*)self)->anim, NULL);
    }
	((Object*)self)->ctor = (void*)SuiView$ProgressView$ctor;
	((SuiView$ProgressView*)self)->startValueAnim = (void*)SuiView$ProgressView$startValueAnim;
	((SuiView$ProgressView*)self)->setValue = (void*)SuiView$ProgressView$setValue;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$ProgressView$draw_self;
}

// init function

void SuiView$ProgressView_init(SuiView$ProgressView *self, void *pOwner){
    Vtable_SuiView$ProgressView_init(&_vtable_SuiView$ProgressView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$ProgressView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$ProgressView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$ProgressView * SuiView$ProgressView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$ProgressView *self = calloc(1, sizeof(SuiView$ProgressView));
	
    SuiView$ProgressView_init(self, pOwner);
    return self;
}


// class members
void  SuiView$ProgressView$ctor(SuiView$ProgressView *  self){
	((SuiCore$View * )self)->backgroundColor = 0xffefefef;
	((SuiCore$View * )self)->width = 200;
	((SuiCore$View * )self)->height = 6;
	self->setValue(self, 0.6) ;
}


void  SuiView$ProgressView$startValueAnim(SuiView$ProgressView *  self){
	URGC_VAR_CLEANUP SuiView$__Block_36_22*  __var___Block_36_22 = (__var___Block_36_22=NULL,urgc_init_var((void**)&__var___Block_36_22, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_36_22) , __finiBlock___Block_36_22) ));
	urgc_set_field_class(__var___Block_36_22, (void * )offsetof(SuiView$__Block_36_22, self) , self) ;
	if (self->anim == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$AnimStep*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiView$ProgressView, anim) , SuiCore$AnimStep_new(&tmpNewOwner_1) ) ;
	}
	URGC_VAR_CLEANUP SuiView$__Closure_40_18*  tmpReturn_2 = NULL;
	self->anim->start(self->anim, __make___Closure_40_18(&tmpReturn_2, __var___Block_36_22) ) ;
}


void  SuiView$ProgressView$setValue(SuiView$ProgressView *  self, float  v){
	if (self->value == v) {
		return ; 
	}
	self->value = v;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	self->startValueAnim(self) ;
}


void  SuiView$ProgressView$draw_self(SuiView$ProgressView *  self, SuiCore$Canvas *  canvas){
	SuiCore$View$draw_self(self, canvas) ;
	float  w = ((SuiCore$ViewBase * )self)->frame.width;
	SuiCore$Canvas$fillColorByInt32(canvas, (0xff1677ff)) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 0, 0, w * self->valueForAnim, ((SuiCore$ViewBase * )self)->frame.height) ;
	SuiCore$Canvas$fill(canvas) ;
}



static void  __finiBlock___Block_36_22(SuiView$__Block_36_22 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_36_22, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_40_18(SuiView$__Closure_40_18 *  self){
	self->__var___Block_36_22->self->valueForAnim = self->__var___Block_36_22->self->anim->next(self->__var___Block_36_22->self->anim, self->__var___Block_36_22->self->valueForAnim, self->__var___Block_36_22->self->value, 0.05) ;
	((SuiCore$ViewBase * )self->__var___Block_36_22->self)->invalidDraw(self->__var___Block_36_22->self) ;
}

static void  __fini___Closure_40_18(SuiView$__Closure_40_18 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_40_18, __var___Block_36_22) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_40_18*  __make___Closure_40_18(SuiView$__Closure_40_18 **  __outRef__, SuiView$__Block_36_22 *  __var___Block_36_22){
	URGC_VAR_CLEANUP SuiView$__Closure_40_18*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_40_18) , __fini___Closure_40_18) ));
	self->invoke = __fn___Closure_40_18;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_40_18, __var___Block_36_22) , __var___Block_36_22) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$ProgressView*  SuiView$mkProgressView(SuiView$ProgressView **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$ProgressView* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$ProgressView_init(NULL)) ) ; 
}



