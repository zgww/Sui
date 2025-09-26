
#include "ColorPicker_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Window_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Core/Event_orc.h"
#include "../Dialog/Toast_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/TextView_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Drag_orc.h"
#include "./ColorPalete_orc.h"
#include "./ViewBuilder_orc.h"


// static struct 
typedef struct tagSuiView$__Block_48_30 SuiView$__Block_48_30;

typedef struct tagSuiView$__Closure_66_19 SuiView$__Closure_66_19;



struct tagSuiView$__Block_48_30 {
	SuiView$ColorPicker*  self ;
};





struct tagSuiView$__Closure_66_19 {
	void  (*invoke)(SuiView$__Closure_66_19 *  self, int  c);
	Vtable_Object *  vtable ;
	SuiView$__Block_48_30*  __var___Block_48_30 ;
};





// static function declaration
static void  __finiBlock___Block_48_30(SuiView$__Block_48_30 *  self);
static void  __fn___Closure_66_19(SuiView$__Closure_66_19 *  self, int  c);
static void  __fini___Closure_66_19(SuiView$__Closure_66_19 *  self);
static SuiView$__Closure_66_19*  __make___Closure_66_19(SuiView$__Closure_66_19 **  __outRef__, SuiView$__Block_48_30 *  __var___Block_48_30);



//vtable instance
Vtable_SuiView$ColorPicker _vtable_SuiView$ColorPicker;

// init meta

void SuiView$ColorPicker_initMeta(Vtable_SuiView$ColorPicker *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "fire_onChanged", offsetof(SuiView$ColorPicker, fire_onChanged));
	orc_metaField_method(&pNext, "showWindow_colorPalete", offsetof(SuiView$ColorPicker, showWindow_colorPalete));
	orc_metaField_method(&pNext, "onMouseEvent", offsetof(SuiView$ColorPicker, onMouseEvent));
}


// vtable init


Vtable_SuiView$ColorPicker* Vtable_SuiView$ColorPicker_init(Vtable_SuiView$ColorPicker* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$ColorPicker;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$ColorPicker_new;
    ((Vtable_Object*)pvt)->className = "SuiView$ColorPicker";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$ColorPicker_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$ColorPicker_fini(SuiView$ColorPicker *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiView$ColorPicker_init_fields(SuiView$ColorPicker *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$ColorPicker_fini;
	//fields
    {
	urgc_set_field(self, (void**)&((SuiView$ColorPicker*)self)->onChanged, NULL);
    }
	((SuiView$ColorPicker*)self)->fire_onChanged = (void*)SuiView$ColorPicker$fire_onChanged;
	((Object*)self)->ctor = (void*)SuiView$ColorPicker$ctor;
	((SuiView$ColorPicker*)self)->showWindow_colorPalete = (void*)SuiView$ColorPicker$showWindow_colorPalete;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$ColorPicker$onEvent;
	((SuiView$ColorPicker*)self)->onMouseEvent = (void*)SuiView$ColorPicker$onMouseEvent;
}

// init function

void SuiView$ColorPicker_init(SuiView$ColorPicker *self, void *pOwner){
    Vtable_SuiView$ColorPicker_init(&_vtable_SuiView$ColorPicker);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$ColorPicker;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$ColorPicker_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$ColorPicker * SuiView$ColorPicker_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$ColorPicker *self = calloc(1, sizeof(SuiView$ColorPicker));
	
    SuiView$ColorPicker_init(self, pOwner);
    return self;
}


// class members
void  SuiView$ColorPicker$fire_onChanged(SuiView$ColorPicker *  self, int  newcolor){
	if (self->onChanged) {
		(*(self->onChanged))((void * )(self->onChanged), newcolor) ;
	}
}


void  SuiView$ColorPicker$ctor(SuiView$ColorPicker *  self){
	SuiCore$Listener$ctor(self) ;
	((SuiCore$View * )self)->width = 14;
	((SuiCore$View * )self)->height = 14;
	((SuiCore$View * )self)->border->setAll(((SuiCore$View * )self)->border, 2, 0xffffffff) ;
	((SuiCore$View * )self)->backgroundColor = 0xff00ff00;
}


void  SuiView$ColorPicker$showWindow_colorPalete(SuiView$ColorPicker *  self){
	URGC_VAR_CLEANUP SuiView$__Block_48_30*  __var___Block_48_30 = (__var___Block_48_30=NULL,urgc_init_var((void**)&__var___Block_48_30, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_48_30) , __finiBlock___Block_48_30) ));
	urgc_set_field_class(__var___Block_48_30, (void * )offsetof(SuiView$__Block_48_30, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	{
		Sui$Window*  o = win;
		
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_1 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_1) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_51_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			win->setRootView(win, o) ;
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "center") ;
			SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 8) ;
			URGC_VAR_CLEANUP_CLASS SuiView$ColorView*  tmpReturn_2 = NULL;
			{
				SuiView$ColorView*  __scopeVar_62_4 = SuiView$mkColorView(&tmpReturn_2, o, 0) , *o = __scopeVar_62_4;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_62_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				if (((SuiCore$Node * )o)->isNewForReact) {
					o->hsva = SuiCore$mkHsva_byInt(((SuiCore$View * )self)->backgroundColor) ;
				}
				URGC_VAR_CLEANUP SuiView$__Closure_66_19*  tmpReturn_3 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$ColorView, onChanged) , __make___Closure_66_19(&tmpReturn_3, __var___Block_48_30) ) ;
			}
		}
		o->setOwner(o, ((SuiCore$Node * )self)->getWindow(self) ) ;
		o->setTitle(o, "ColorPicker") ;
		o->setSize(o, 300, 300) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}


void  SuiView$ColorPicker$onEvent(SuiView$ColorPicker *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		self->onMouseEvent(self, (SuiCore$MouseEvent * )e) ;
	}
}


void  SuiView$ColorPicker$onMouseEvent(SuiView$ColorPicker *  self, SuiCore$MouseEvent *  me){
	if (me->isClickInBubble(me) ) {
		self->showWindow_colorPalete(self) ;
	}
}



static void  __finiBlock___Block_48_30(SuiView$__Block_48_30 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_48_30, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_66_19(SuiView$__Closure_66_19 *  self, int  c){
	((SuiCore$View * )self->__var___Block_48_30->self)->backgroundColor = c;
	self->__var___Block_48_30->self->fire_onChanged(self->__var___Block_48_30->self, c) ;
	((SuiCore$ViewBase * )self->__var___Block_48_30->self)->invalidDraw(self->__var___Block_48_30->self) ;
}

static void  __fini___Closure_66_19(SuiView$__Closure_66_19 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_66_19, __var___Block_48_30) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_66_19*  __make___Closure_66_19(SuiView$__Closure_66_19 **  __outRef__, SuiView$__Block_48_30 *  __var___Block_48_30){
	URGC_VAR_CLEANUP SuiView$__Closure_66_19*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_66_19) , __fini___Closure_66_19) ));
	self->invoke = __fn___Closure_66_19;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_66_19, __var___Block_48_30) , __var___Block_48_30) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$ColorPicker*  SuiView$mkColorPicker(SuiView$ColorPicker **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$ColorPicker* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$ColorPicker_init(NULL)) ) ; 
}



