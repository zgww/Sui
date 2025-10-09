
#include "Slider_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Frame_orc.h"
#include "../View/Drag_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Canvas_orc.h"
#include "../../Orc/Math_orc.h"


// static struct 
typedef struct tagSuiView$__Block_117_24 SuiView$__Block_117_24;

typedef struct tagSuiView$__Closure_122_23 SuiView$__Closure_122_23;



struct tagSuiView$__Block_117_24 {
	SuiView$Slider*  self ;
};





struct tagSuiView$__Closure_122_23 {
	void  (*invoke)(SuiView$__Closure_122_23 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiView$__Block_117_24*  __var___Block_117_24 ;
};





// static function declaration
static void  __finiBlock___Block_117_24(SuiView$__Block_117_24 *  self);
static void  __fn___Closure_122_23(SuiView$__Closure_122_23 *  self, SuiView$Drag *  d);
static void  __fini___Closure_122_23(SuiView$__Closure_122_23 *  self);
static SuiView$__Closure_122_23*  __make___Closure_122_23(SuiView$__Closure_122_23 **  __outRef__, SuiView$__Block_117_24 *  __var___Block_117_24);



//vtable instance
Vtable_SuiView$Slider _vtable_SuiView$Slider;

// init meta

void SuiView$Slider_initMeta(Vtable_SuiView$Slider *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "circle", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiView$Slider, circle), true, false, 1);
	orc_metaField_primitive(&pNext, "ratio", OrcMetaType_float, offsetof(SuiView$Slider, ratio), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "fromValue", OrcMetaType_float, offsetof(SuiView$Slider, fromValue), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "toValue", OrcMetaType_float, offsetof(SuiView$Slider, toValue), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiView$Slider, drag), true, false, 1);

	orc_metaField_method(&pNext, "fire_onChanged", offsetof(SuiView$Slider, fire_onChanged));
	orc_metaField_method(&pNext, "setRatioByValue", offsetof(SuiView$Slider, setRatioByValue));
	orc_metaField_method(&pNext, "getValue", offsetof(SuiView$Slider, getValue));
	orc_metaField_method(&pNext, "calcToX", offsetof(SuiView$Slider, calcToX));
	orc_metaField_method(&pNext, "calcToY", offsetof(SuiView$Slider, calcToY));
	orc_metaField_method(&pNext, "setRatio", offsetof(SuiView$Slider, setRatio));
}


// vtable init


Vtable_SuiView$Slider* Vtable_SuiView$Slider_init(Vtable_SuiView$Slider* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Slider;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Slider_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Slider";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Slider_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Slider_fini(SuiView$Slider *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$Slider*)self)->circle);
	urgc_fini_field_class(self, (void**)&((SuiView$Slider*)self)->drag);

}

// init fields function


void SuiView$Slider_init_fields(SuiView$Slider *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$Slider_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$Slider*)self)->circle, SuiCore$View_new(&tmpNewOwner_1) );
	((SuiView$Slider*)self)->ratio = 0.5;
	((SuiView$Slider*)self)->fromValue = 0;
	((SuiView$Slider*)self)->toValue = 1;
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$Slider*)self)->drag, SuiView$Drag_new(&tmpNewOwner_2) );
	urgc_set_field(self, (void**)&((SuiView$Slider*)self)->onChanged, NULL);
    }
	((SuiView$Slider*)self)->fire_onChanged = (void*)SuiView$Slider$fire_onChanged;
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiView$Slider$layoutContent;
	((SuiView$Slider*)self)->setRatioByValue = (void*)SuiView$Slider$setRatioByValue;
	((SuiView$Slider*)self)->getValue = (void*)SuiView$Slider$getValue;
	((Object*)self)->ctor = (void*)SuiView$Slider$ctor;
	((SuiView$Slider*)self)->calcToX = (void*)SuiView$Slider$calcToX;
	((SuiView$Slider*)self)->calcToY = (void*)SuiView$Slider$calcToY;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$Slider$draw_self;
	((SuiCore$Node*)self)->react = (void*)SuiView$Slider$react;
	((SuiView$Slider*)self)->setRatio = (void*)SuiView$Slider$setRatio;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$Slider$onEvent;
}

// init function

void SuiView$Slider_init(SuiView$Slider *self, void *pOwner){
    Vtable_SuiView$Slider_init(&_vtable_SuiView$Slider);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Slider;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Slider_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Slider * SuiView$Slider_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Slider *self = calloc(1, sizeof(SuiView$Slider));
	
    SuiView$Slider_init(self, pOwner);
    return self;
}


// class members
void  SuiView$Slider$fire_onChanged(SuiView$Slider *  self){
	if (self->onChanged) {
		float  v = self->getValue(self) ;
		(*(self->onChanged))((void * )(self->onChanged), v) ;
	}
}


void  SuiView$Slider$layoutContent(SuiView$Slider *  self, SuiCore$Frame *  f){
	SuiCore$Frame tmp = *f;
	SuiCore$View$layoutContent(self, f) ;
	*f = tmp;
}


void  SuiView$Slider$setRatioByValue(SuiView$Slider *  self, float  value){
	self->ratio = (value - self->fromValue) / (self->toValue - self->fromValue);
}


float  SuiView$Slider$getValue(SuiView$Slider *  self){
	return (self->toValue - self->fromValue) * self->ratio + self->fromValue; 
}


void  SuiView$Slider$ctor(SuiView$Slider *  self){
	((SuiCore$View * )self)->height = 16;
	((SuiCore$Node * )self)->appendChild(self, self->circle) ;
	self->circle->width = 16;
	self->circle->height = 16;
	((SuiCore$ViewBase * )self->circle)->frame.x = self->calcToX(self) ;
	((SuiCore$Node * )self)->react(self) ;
}


float  SuiView$Slider$calcToX(SuiView$Slider *  self){
	SuiCore$Rect r = ((SuiCore$View * )self)->getViewRect(self) ;
	float  x = r.w * self->ratio;
	return x - self->circle->width / 2.0; 
}


float  SuiView$Slider$calcToY(SuiView$Slider *  self){
	return ((SuiCore$ViewBase * )self)->frame.height / 2.0 - ((SuiCore$ViewBase * )self->circle)->frame.height / 2.0; 
}


void  SuiView$Slider$draw_self(SuiView$Slider *  self, SuiCore$Canvas *  canvas){
	SuiCore$View$draw_self(self, canvas) ;
	((SuiCore$ViewBase * )self->circle)->frame.x = self->calcToX(self) ;
	((SuiCore$ViewBase * )self->circle)->frame.y = self->calcToY(self) ;
	float  barH = 6;
	SuiCore$Rect r = ((SuiCore$View * )self)->getViewRect(self) ;
	float  w = r.w;
	float  y = (((SuiCore$ViewBase * )self)->frame.height - barH) / 2.0;
	SuiCore$Canvas$fillColorByInt32(canvas, (0x33000000)) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 0, y, w, barH) ;
	SuiCore$Canvas$fill(canvas) ;
	SuiCore$Canvas$fillColorByInt32(canvas, (0xff1677ff)) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 0, y, w * self->ratio, barH) ;
	SuiCore$Canvas$fill(canvas) ;
}


void  SuiView$Slider$react(SuiView$Slider *  self){
	self->circle->backgroundColor = 0xffffffff;
	self->circle->radius->setAll(self->circle->radius, 11) ;
	self->circle->border->setAll(self->circle->border, 4, 0xff1677ff) ;
}


void  SuiView$Slider$setRatio(SuiView$Slider *  self, float  v){
	self->ratio = v;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


void  SuiView$Slider$onEvent(SuiView$Slider *  self, SuiCore$Event *  ev){
	URGC_VAR_CLEANUP SuiView$__Block_117_24*  __var___Block_117_24 = (__var___Block_117_24=NULL,urgc_init_var((void**)&__var___Block_117_24, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_117_24) , __finiBlock___Block_117_24) ));
	urgc_set_field_class(__var___Block_117_24, (void * )offsetof(SuiView$__Block_117_24, self) , self) ;
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
		if (((SuiCore$ViewEvent * )me)->isBubble(me)  && me->isMouseDown) {
			self->drag->onMouseDown(self->drag, me) ;
			URGC_VAR_CLEANUP SuiView$__Closure_122_23*  tmpReturn_1 = NULL;
			urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_122_23(&tmpReturn_1, __var___Block_117_24) ) ;
		}
	}
}



static void  __finiBlock___Block_117_24(SuiView$__Block_117_24 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_117_24, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_122_23(SuiView$__Closure_122_23 *  self, SuiView$Drag *  d){
	SuiCore$Rect r = ((SuiCore$View * )self->__var___Block_117_24->self)->getViewRect_baseClient(self->__var___Block_117_24->self) ;
	float  v = (d->currentClientPos.x - r.x) / r.w;
	printf("ondrag...v:%f, w:%f\n", v, r.w) ;
	v = Orc$clampFloat(v, 0.0, 1.0) ;
	self->__var___Block_117_24->self->setRatio(self->__var___Block_117_24->self, v) ;
}

static void  __fini___Closure_122_23(SuiView$__Closure_122_23 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_122_23, __var___Block_117_24) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_122_23*  __make___Closure_122_23(SuiView$__Closure_122_23 **  __outRef__, SuiView$__Block_117_24 *  __var___Block_117_24){
	URGC_VAR_CLEANUP SuiView$__Closure_122_23*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_122_23) , __fini___Closure_122_23) ));
	self->invoke = __fn___Closure_122_23;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_122_23, __var___Block_117_24) , __var___Block_117_24) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$Slider*  SuiView$mkSlider(SuiView$Slider **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$Slider* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$Slider_init(NULL)) ) ; 
}



