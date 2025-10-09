
#include "HoverViewEffect_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../Core/Node_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Border_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "./ViewBuilder_orc.h"


// static struct 
typedef struct tagSuiView$__Block_35_40 SuiView$__Block_35_40;

typedef struct tagSuiView$__Block_33_20 SuiView$__Block_33_20;

typedef struct tagSuiView$__Closure_37_33 SuiView$__Closure_37_33;

typedef struct tagSuiView$__Closure_46_30 SuiView$__Closure_46_30;



struct tagSuiView$__Block_35_40 {
	SuiCore$View*  v ;
};





struct tagSuiView$__Block_33_20 {
	SuiView$HoverViewEffect*  self ;
};





struct tagSuiView$__Closure_37_33 {
	void  (*invoke)(SuiView$__Closure_37_33 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_35_40*  __var___Block_35_40 ;
	SuiView$__Block_33_20*  __var___Block_33_20 ;
};





struct tagSuiView$__Closure_46_30 {
	void  (*invoke)(SuiView$__Closure_46_30 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiView$__Block_33_20*  __var___Block_33_20 ;
};





// static function declaration
static void  __finiBlock___Block_35_40(SuiView$__Block_35_40 *  self);
static void  __finiBlock___Block_33_20(SuiView$__Block_33_20 *  self);
static void  __fn___Closure_37_33(SuiView$__Closure_37_33 *  self);
static void  __fini___Closure_37_33(SuiView$__Closure_37_33 *  self);
static SuiView$__Closure_37_33*  __make___Closure_37_33(SuiView$__Closure_37_33 **  __outRef__, SuiView$__Block_35_40 *  __var___Block_35_40, SuiView$__Block_33_20 *  __var___Block_33_20);
static void  __fn___Closure_46_30(SuiView$__Closure_46_30 *  self, SuiCore$Event *  e);
static void  __fini___Closure_46_30(SuiView$__Closure_46_30 *  self);
static SuiView$__Closure_46_30*  __make___Closure_46_30(SuiView$__Closure_46_30 **  __outRef__, SuiView$__Block_33_20 *  __var___Block_33_20);



//vtable instance
Vtable_SuiView$HoverViewEffect _vtable_SuiView$HoverViewEffect;

// init meta

void SuiView$HoverViewEffect_initMeta(Vtable_SuiView$HoverViewEffect *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "backgroundColor", OrcMetaType_int, offsetof(SuiView$HoverViewEffect, backgroundColor), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "border", ((Vtable_Object*)Vtable_SuiCore$Border_init(0)), offsetof(SuiView$HoverViewEffect, border), true, false, 1);
	orc_metaField_primitive(&pNext, "hoverBackgroundColor", OrcMetaType_int, offsetof(SuiView$HoverViewEffect, hoverBackgroundColor), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "hoverBorder", ((Vtable_Object*)Vtable_SuiCore$Border_init(0)), offsetof(SuiView$HoverViewEffect, hoverBorder), true, false, 1);
	orc_metaField_primitive(&pNext, "activeBackgroundColor", OrcMetaType_int, offsetof(SuiView$HoverViewEffect, activeBackgroundColor), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "activeBorder", ((Vtable_Object*)Vtable_SuiCore$Border_init(0)), offsetof(SuiView$HoverViewEffect, activeBorder), true, false, 1);
	orc_metaField_primitive(&pNext, "isActive", OrcMetaType_bool, offsetof(SuiView$HoverViewEffect, isActive), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "applyEffect", offsetof(SuiView$HoverViewEffect, applyEffect));
}


// vtable init


Vtable_SuiView$HoverViewEffect* Vtable_SuiView$HoverViewEffect_init(Vtable_SuiView$HoverViewEffect* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$HoverViewEffect;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Node_init(&_vtable_SuiCore$Node);

	// init by super vtable init function
    Vtable_SuiCore$Node_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Node;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$HoverViewEffect_new;
    ((Vtable_Object*)pvt)->className = "SuiView$HoverViewEffect";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$HoverViewEffect_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$HoverViewEffect_fini(SuiView$HoverViewEffect *self){
	//super fini
    SuiCore$Node_fini((SuiCore$Node *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$HoverViewEffect*)self)->border);
	urgc_fini_field_class(self, (void**)&((SuiView$HoverViewEffect*)self)->hoverBorder);
	urgc_fini_field_class(self, (void**)&((SuiView$HoverViewEffect*)self)->activeBorder);

}

// init fields function


void SuiView$HoverViewEffect_init_fields(SuiView$HoverViewEffect *self){
	//super class
    SuiCore$Node_init_fields((SuiCore$Node*)self);

    ((Object*)self)->fini = (void*)SuiView$HoverViewEffect_fini;
	//fields
    {
	((SuiView$HoverViewEffect*)self)->backgroundColor = 0x00ffffff;
	URGC_VAR_CLEANUP_CLASS SuiCore$Border*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$HoverViewEffect*)self)->border, SuiCore$mkBorder(&tmpReturn_1, 1, 0x00000000) );
	((SuiView$HoverViewEffect*)self)->hoverBackgroundColor = 0x22666666;
	URGC_VAR_CLEANUP_CLASS SuiCore$Border*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$HoverViewEffect*)self)->hoverBorder, SuiCore$mkBorder(&tmpReturn_2, 1, 0x00007aff) );
	((SuiView$HoverViewEffect*)self)->activeBackgroundColor = 0x53007aff;
	URGC_VAR_CLEANUP_CLASS SuiCore$Border*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$HoverViewEffect*)self)->activeBorder, SuiCore$mkBorder(&tmpReturn_3, 1, 0x76007aff) );
	((SuiView$HoverViewEffect*)self)->isActive = false;
	urgc_set_field(self, (void**)&((SuiView$HoverViewEffect*)self)->onClick, NULL);
	urgc_set_field(self, (void**)&((SuiView$HoverViewEffect*)self)->onHostEvent, NULL);
	urgc_set_field(self, (void**)&((SuiView$HoverViewEffect*)self)->cbOnHoverChanged, NULL);
    }
	((SuiCore$Node*)self)->onMounted = (void*)SuiView$HoverViewEffect$onMounted;
	((SuiCore$Node*)self)->react = (void*)SuiView$HoverViewEffect$react;
	((SuiView$HoverViewEffect*)self)->applyEffect = (void*)SuiView$HoverViewEffect$applyEffect;
	((SuiCore$Node*)self)->onUnmounting = (void*)SuiView$HoverViewEffect$onUnmounting;
}

// init function

void SuiView$HoverViewEffect_init(SuiView$HoverViewEffect *self, void *pOwner){
    Vtable_SuiView$HoverViewEffect_init(&_vtable_SuiView$HoverViewEffect);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$HoverViewEffect;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$HoverViewEffect_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$HoverViewEffect * SuiView$HoverViewEffect_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$HoverViewEffect *self = calloc(1, sizeof(SuiView$HoverViewEffect));
	
    SuiView$HoverViewEffect_init(self, pOwner);
    return self;
}


// class members
void  SuiView$HoverViewEffect$onMounted(SuiView$HoverViewEffect *  self){
	URGC_VAR_CLEANUP SuiView$__Block_33_20*  __var___Block_33_20 = (__var___Block_33_20=NULL,urgc_init_var((void**)&__var___Block_33_20, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_33_20) , __finiBlock___Block_33_20) ));
	urgc_set_field_class(__var___Block_33_20, (void * )offsetof(SuiView$__Block_33_20, self) , self) ;
	if (Orc_instanceof((Object*)((SuiCore$Node * )self)->parent, (Vtable_Object*)Vtable_SuiCore$View_init(NULL))) {
		URGC_VAR_CLEANUP SuiView$__Block_35_40*  __var___Block_35_40 = (__var___Block_35_40=NULL,urgc_init_var((void**)&__var___Block_35_40, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_35_40) , __finiBlock___Block_35_40) ));
		urgc_set_field_class(__var___Block_35_40, (void * )offsetof(SuiView$__Block_35_40, v) , (SuiCore$View * )((SuiCore$Node * )self)->parent) ;
		URGC_VAR_CLEANUP SuiView$__Closure_37_33*  tmpReturn_1 = NULL;
		urgc_set_field(__var___Block_35_40->v, (void * )offsetof(SuiCore$ViewBase, cbOnHoverChanged) , __make___Closure_37_33(&tmpReturn_1, __var___Block_35_40, __var___Block_33_20) ) ;
		if (self->onClick || self->onHostEvent) {
			URGC_VAR_CLEANUP SuiView$__Closure_46_30*  tmpReturn_2 = NULL;
			urgc_set_field(__var___Block_35_40->v, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_46_30(&tmpReturn_2, __var___Block_33_20) ) ;
		}
	}
}


void  SuiView$HoverViewEffect$react(SuiView$HoverViewEffect *  self){
	self->applyEffect(self) ;
}


void  SuiView$HoverViewEffect$applyEffect(SuiView$HoverViewEffect *  self){
	if (Orc_instanceof((Object*)((SuiCore$Node * )self)->parent, (Vtable_Object*)Vtable_SuiCore$View_init(NULL))) {
		SuiCore$View *  v = (SuiCore$View * )((SuiCore$Node * )self)->parent;
		bool  hover = ((SuiCore$ViewBase * )v)->hover;
		int  bgColor = self->backgroundColor;
		SuiCore$Border *  border = self->border;
		if (self->isActive) {
			bgColor = self->activeBackgroundColor;
			border = self->activeBorder;
		}
		else if (hover) {
			bgColor = self->hoverBackgroundColor;
			border = self->hoverBorder;
		}
		v->backgroundColor = bgColor;
		v->border->copyFrom(v->border, border) ;
		((SuiCore$ViewBase * )v)->invalidDraw(v) ;
	}
}


void  SuiView$HoverViewEffect$onUnmounting(SuiView$HoverViewEffect *  self){
	if (Orc_instanceof((Object*)((SuiCore$Node * )self)->parent, (Vtable_Object*)Vtable_SuiCore$View_init(NULL))) {
		SuiCore$View *  v = (SuiCore$View * )((SuiCore$Node * )self)->parent;
		urgc_set_field(v, (void * )offsetof(SuiCore$ViewBase, cbOnHoverChanged) , NULL) ;
		self->applyEffect(self) ;
	}
}



static void  __finiBlock___Block_35_40(SuiView$__Block_35_40 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_35_40, v) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_33_20(SuiView$__Block_33_20 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_33_20, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_37_33(SuiView$__Closure_37_33 *  self){
	printf("HoverViewEffect. cbOnHoverChanged:%d\n", ((SuiCore$ViewBase * )self->__var___Block_35_40->v)->hover) ;
	self->__var___Block_33_20->self->applyEffect(self->__var___Block_33_20->self) ;
	if (self->__var___Block_33_20->self->cbOnHoverChanged) {
		(*(self->__var___Block_33_20->self->cbOnHoverChanged))((void * )(self->__var___Block_33_20->self->cbOnHoverChanged), self->__var___Block_35_40->v) ;
	}
}

static void  __fini___Closure_37_33(SuiView$__Closure_37_33 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_37_33, __var___Block_35_40) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_37_33, __var___Block_33_20) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_37_33*  __make___Closure_37_33(SuiView$__Closure_37_33 **  __outRef__, SuiView$__Block_35_40 *  __var___Block_35_40, SuiView$__Block_33_20 *  __var___Block_33_20){
	URGC_VAR_CLEANUP SuiView$__Closure_37_33*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_37_33) , __fini___Closure_37_33) ));
	self->invoke = __fn___Closure_37_33;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_37_33, __var___Block_35_40) , __var___Block_35_40) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_37_33, __var___Block_33_20) , __var___Block_33_20) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_46_30(SuiView$__Closure_46_30 *  self, SuiCore$Event *  e){
	if (self->__var___Block_33_20->self->onHostEvent) {
		if ((*(self->__var___Block_33_20->self->onHostEvent))((void * )(self->__var___Block_33_20->self->onHostEvent), e) ) {
			return ; 
		}
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClickInBubble(me) ) {
			if (self->__var___Block_33_20->self->onClick) {
				(*(self->__var___Block_33_20->self->onClick))((void * )(self->__var___Block_33_20->self->onClick), me) ;
			}
		}
	}
}

static void  __fini___Closure_46_30(SuiView$__Closure_46_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_46_30, __var___Block_33_20) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_46_30*  __make___Closure_46_30(SuiView$__Closure_46_30 **  __outRef__, SuiView$__Block_33_20 *  __var___Block_33_20){
	URGC_VAR_CLEANUP SuiView$__Closure_46_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_46_30) , __fini___Closure_46_30) ));
	self->invoke = __fn___Closure_46_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_46_30, __var___Block_33_20) , __var___Block_33_20) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$HoverViewEffect*  SuiView$mkHoverViewEffect(SuiView$HoverViewEffect **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$HoverViewEffect* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$HoverViewEffect_init(NULL)) ) ; 
}



