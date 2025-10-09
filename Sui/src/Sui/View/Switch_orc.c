
#include "Switch_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include "../Core/Node_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Timer_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/MouseEvent_orc.h"


// static struct 
typedef struct tagSuiView$__Block_32_13 SuiView$__Block_32_13;

typedef struct tagSuiView$__Closure_52_19 SuiView$__Closure_52_19;



struct tagSuiView$__Block_32_13 {
	SuiView$Switch*  self ;
};





struct tagSuiView$__Closure_52_19 {
	void  (*invoke)(SuiView$__Closure_52_19 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_32_13*  __var___Block_32_13 ;
};





// static function declaration
static void  __finiBlock___Block_32_13(SuiView$__Block_32_13 *  self);
static void  __fn___Closure_52_19(SuiView$__Closure_52_19 *  self);
static void  __fini___Closure_52_19(SuiView$__Closure_52_19 *  self);
static SuiView$__Closure_52_19*  __make___Closure_52_19(SuiView$__Closure_52_19 **  __outRef__, SuiView$__Block_32_13 *  __var___Block_32_13);



//vtable instance
Vtable_SuiView$Switch _vtable_SuiView$Switch;

// init meta

void SuiView$Switch_initMeta(Vtable_SuiView$Switch *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "circle", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiView$Switch, circle), true, false, 1);
	orc_metaField_primitive(&pNext, "checked", OrcMetaType_bool, offsetof(SuiView$Switch, checked), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "anim", ((Vtable_Object*)Vtable_SuiCore$AnimStep_init(0)), offsetof(SuiView$Switch, anim), true, false, 1);
	orc_metaField_primitive(&pNext, "circleSize", OrcMetaType_int, offsetof(SuiView$Switch, circleSize), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "calcToX", offsetof(SuiView$Switch, calcToX));
	orc_metaField_method(&pNext, "setChecked", offsetof(SuiView$Switch, setChecked));
}


// vtable init


Vtable_SuiView$Switch* Vtable_SuiView$Switch_init(Vtable_SuiView$Switch* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Switch;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Switch_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Switch";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Switch_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Switch_fini(SuiView$Switch *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$Switch*)self)->circle);
	urgc_fini_field_class(self, (void**)&((SuiView$Switch*)self)->anim);

}

// init fields function


void SuiView$Switch_init_fields(SuiView$Switch *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$Switch_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$Switch*)self)->circle, SuiCore$View_new(&tmpNewOwner_1) );
	((SuiView$Switch*)self)->checked = false;
	URGC_VAR_CLEANUP_CLASS SuiCore$AnimStep*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$Switch*)self)->anim, SuiCore$AnimStep_new(&tmpNewOwner_2) );
	((SuiView$Switch*)self)->circleSize = 14;
	urgc_set_field(self, (void**)&((SuiView$Switch*)self)->onCheckedChanged, NULL);
    }
	((Object*)self)->ctor = (void*)SuiView$Switch$ctor;
	((SuiCore$Node*)self)->react = (void*)SuiView$Switch$react;
	((SuiView$Switch*)self)->calcToX = (void*)SuiView$Switch$calcToX;
	((SuiView$Switch*)self)->setChecked = (void*)SuiView$Switch$setChecked;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$Switch$onEvent;
}

// init function

void SuiView$Switch_init(SuiView$Switch *self, void *pOwner){
    Vtable_SuiView$Switch_init(&_vtable_SuiView$Switch);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Switch;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Switch_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Switch * SuiView$Switch_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Switch *self = calloc(1, sizeof(SuiView$Switch));
	
    SuiView$Switch_init(self, pOwner);
    return self;
}


// class members
void  SuiView$Switch$ctor(SuiView$Switch *  self){
	((SuiCore$View * )self)->width = 34;
	((SuiCore$View * )self)->height = 20;
	((SuiCore$Node * )self)->appendChild(self, self->circle) ;
	self->circle->width = self->circleSize;
	self->circle->height = self->circleSize;
	((SuiCore$ViewBase * )self->circle)->frame.x = self->calcToX(self) ;
}


void  SuiView$Switch$react(SuiView$Switch *  self){
	URGC_VAR_CLEANUP SuiView$__Block_32_13*  __var___Block_32_13 = (__var___Block_32_13=NULL,urgc_init_var((void**)&__var___Block_32_13, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_32_13) , __finiBlock___Block_32_13) ));
	urgc_set_field_class(__var___Block_32_13, (void * )offsetof(SuiView$__Block_32_13, self) , self) ;
	((SuiCore$View * )self)->radius->setAll(((SuiCore$View * )self)->radius, 10) ;
	((SuiCore$View * )self)->backgroundColor = self->checked ? 0xff1677ff : 0x40ffffff;
	int  d = (((SuiCore$View * )self)->height - self->circle->height) / 2;
	((SuiCore$ViewBase * )self->circle)->frame.y = d;
	self->circle->backgroundColor = 0xffffffff;
	self->circle->radius->setAll(self->circle->radius, 7) ;
	if (((SuiCore$Node * )self)->isNewForReact) {
		((SuiCore$ViewBase * )self->circle)->frame.x = self->calcToX(self) ;
		((SuiCore$Node * )self)->isNewForReact = false;
	}
	else {
		URGC_VAR_CLEANUP SuiView$__Closure_52_19*  tmpReturn_1 = NULL;
		self->anim->start(self->anim, __make___Closure_52_19(&tmpReturn_1, __var___Block_32_13) ) ;
	}
}


float  SuiView$Switch$calcToX(SuiView$Switch *  self){
	int  d = (((SuiCore$View * )self)->height - self->circle->height) / 2;
	float  toX = !self->checked ? d : ((SuiCore$View * )self)->width - d - self->circle->width;
	return toX; 
}


void  SuiView$Switch$setChecked(SuiView$Switch *  self, bool  v){
	if (v == self->checked) {
		return ; 
	}
	self->checked = v;
	if (self->onCheckedChanged) {
		(*(self->onCheckedChanged))((void * )(self->onCheckedChanged), self) ;
	}
	((SuiCore$Node * )self)->react(self) ;
	((SuiCore$ViewBase * )self)->invalidLayout(self) ;
}


void  SuiView$Switch$onEvent(SuiView$Switch *  self, SuiCore$Event *  ev){
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
		if (me->isClickInBubble(me) ) {
			self->setChecked(self, !self->checked) ;
			ev->stopPropagation(ev) ;
		}
	}
}



static void  __finiBlock___Block_32_13(SuiView$__Block_32_13 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_32_13, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_52_19(SuiView$__Closure_52_19 *  self){
	float  toX = self->__var___Block_32_13->self->calcToX(self->__var___Block_32_13->self) ;
	((SuiCore$ViewBase * )self->__var___Block_32_13->self->circle)->frame.x = self->__var___Block_32_13->self->anim->nextByMs(self->__var___Block_32_13->self->anim, ((SuiCore$ViewBase * )self->__var___Block_32_13->self->circle)->frame.x, toX, 140) ;
	((SuiCore$ViewBase * )self->__var___Block_32_13->self)->invalidDraw(self->__var___Block_32_13->self) ;
}

static void  __fini___Closure_52_19(SuiView$__Closure_52_19 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_52_19, __var___Block_32_13) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_52_19*  __make___Closure_52_19(SuiView$__Closure_52_19 **  __outRef__, SuiView$__Block_32_13 *  __var___Block_32_13){
	URGC_VAR_CLEANUP SuiView$__Closure_52_19*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_52_19) , __fini___Closure_52_19) ));
	self->invoke = __fn___Closure_52_19;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_52_19, __var___Block_32_13) , __var___Block_32_13) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$Switch*  SuiView$mkSwitch(SuiView$Switch **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$Switch* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$Switch_init(NULL)) ) ; 
}



