
#include "Select_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../Core/Node_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Timer_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Mouse_orc.h"
#include "../Core/Cursor_orc.h"
#include "./ViewBuilder_orc.h"
#include "./TextView_orc.h"
#include "./MenuNative_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Dialog/MessageDialog_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"


// static struct 
typedef struct tagSuiView$__Block_133_24 SuiView$__Block_133_24;

typedef struct tagSuiView$__Block_144_50 SuiView$__Block_144_50;

typedef struct tagSuiView$__Closure_onActive_136 SuiView$__Closure_onActive_136;

typedef struct tagSuiView$__Closure_158_28 SuiView$__Closure_158_28;

typedef struct tagSuiView$__Closure_170_34 SuiView$__Closure_170_34;



struct tagSuiView$__Block_133_24 {
	SuiView$Select*  self ;
};





struct tagSuiView$__Block_144_50 {
	SuiView$MenuNative*  n ;
};





struct tagSuiView$__Closure_onActive_136 {
	void  (*invoke)(SuiView$__Closure_onActive_136 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiView$__Block_133_24*  __var___Block_133_24 ;
};





struct tagSuiView$__Closure_158_28 {
	void  (*invoke)(SuiView$__Closure_158_28 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_133_24*  __var___Block_133_24 ;
};





struct tagSuiView$__Closure_170_34 {
	bool  (*invoke)(SuiView$__Closure_170_34 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_133_24*  __var___Block_133_24 ;
	SuiView$__Block_144_50*  __var___Block_144_50 ;
};





// static function declaration
static void  __finiBlock___Block_133_24(SuiView$__Block_133_24 *  self);
static void  __finiBlock___Block_144_50(SuiView$__Block_144_50 *  self);
static void  __fn___Closure_onActive_136(SuiView$__Closure_onActive_136 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_136(SuiView$__Closure_onActive_136 *  self);
static SuiView$__Closure_onActive_136*  __make___Closure_onActive_136(SuiView$__Closure_onActive_136 **  __outRef__, SuiView$__Block_133_24 *  __var___Block_133_24);
static void  __fn___Closure_158_28(SuiView$__Closure_158_28 *  self);
static void  __fini___Closure_158_28(SuiView$__Closure_158_28 *  self);
static SuiView$__Closure_158_28*  __make___Closure_158_28(SuiView$__Closure_158_28 **  __outRef__, SuiView$__Block_133_24 *  __var___Block_133_24);
static bool  __fn___Closure_170_34(SuiView$__Closure_170_34 *  self);
static void  __fini___Closure_170_34(SuiView$__Closure_170_34 *  self);
static SuiView$__Closure_170_34*  __make___Closure_170_34(SuiView$__Closure_170_34 **  __outRef__, SuiView$__Block_133_24 *  __var___Block_133_24, SuiView$__Block_144_50 *  __var___Block_144_50);



//vtable instance
Vtable_SuiView$Select _vtable_SuiView$Select;

// init meta

void SuiView$Select_initMeta(Vtable_SuiView$Select *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "isActive", OrcMetaType_bool, offsetof(SuiView$Select, isActive), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "options", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiView$Select, options), true, false, 1);
	orc_metaField_primitive(&pNext, "value", OrcMetaType_int, offsetof(SuiView$Select, value), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "fire_onChanged", offsetof(SuiView$Select, fire_onChanged));
	orc_metaField_method(&pNext, "appendOptionCStr", offsetof(SuiView$Select, appendOptionCStr));
	orc_metaField_method(&pNext, "appendOption", offsetof(SuiView$Select, appendOption));
	orc_metaField_method(&pNext, "setIsActive", offsetof(SuiView$Select, setIsActive));
	orc_metaField_method(&pNext, "setValue", offsetof(SuiView$Select, setValue));
	orc_metaField_method(&pNext, "showPopupMenu", offsetof(SuiView$Select, showPopupMenu));
}


// vtable init


Vtable_SuiView$Select* Vtable_SuiView$Select_init(Vtable_SuiView$Select* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Select;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Select_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Select";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Select_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Select_fini(SuiView$Select *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void SuiView$Select_init_fields(SuiView$Select *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$Select_fini;
	//fields
    {
	((SuiView$Select*)self)->isActive = false;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$Select*)self)->options, Orc$List_new(&tmpNewOwner_1) );
	((SuiView$Select*)self)->value = -1;
	urgc_set_field(self, (void**)&((SuiView$Select*)self)->onChanged, NULL);
    }
	((SuiView$Select*)self)->fire_onChanged = (void*)SuiView$Select$fire_onChanged;
	((Object*)self)->ctor = (void*)SuiView$Select$ctor;
	((SuiView$Select*)self)->appendOptionCStr = (void*)SuiView$Select$appendOptionCStr;
	((SuiView$Select*)self)->appendOption = (void*)SuiView$Select$appendOption;
	((SuiCore$Node*)self)->react = (void*)SuiView$Select$react;
	((SuiView$Select*)self)->setIsActive = (void*)SuiView$Select$setIsActive;
	((SuiView$Select*)self)->setValue = (void*)SuiView$Select$setValue;
	((SuiView$Select*)self)->showPopupMenu = (void*)SuiView$Select$showPopupMenu;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$Select$onEvent;
}

// init function

void SuiView$Select_init(SuiView$Select *self, void *pOwner){
    Vtable_SuiView$Select_init(&_vtable_SuiView$Select);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Select;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Select_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Select * SuiView$Select_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Select *self = calloc(1, sizeof(SuiView$Select));
	
    SuiView$Select_init(self, pOwner);
    return self;
}


// class members
void  SuiView$Select$fire_onChanged(SuiView$Select *  self){
	if (self->onChanged) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  label = (label=NULL,urgc_init_var_class((void**)&label, self->options->get(self->options, self->value) ));
		(*(self->onChanged))((void * )(self->onChanged), self->value, label) ;
	}
}


void  SuiView$Select$ctor(SuiView$Select *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_1, "pointer") ) ;
	((SuiCore$View * )self)->border->setAll(((SuiCore$View * )self)->border, 1, 0xff999999) ;
	((SuiCore$View * )self)->radius->setAll(((SuiCore$View * )self)->radius, 6) ;
	SuiCore$Inset$setAxis(&((SuiCore$View * )self)->padding, 4, 8) ;
}


void  SuiView$Select$appendOptionCStr(SuiView$Select *  self, const char *  text){
	if (text) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		self->options->add(self->options, Orc$str(&tmpReturn_1, text) ) ;
	}
}


void  SuiView$Select$appendOption(SuiView$Select *  self, Orc$String *  text){
	if (text) {
		self->options->add(self->options, text) ;
	}
}


void  SuiView$Select$react(SuiView$Select *  self){
	((SuiCore$Node * )self)->startInnerReact(self) ;
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  o = SuiView$mkTextView(&tmpReturn_1, self, 0) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_62_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  text = (text=NULL,urgc_init_var_class((void**)&text, (Orc$String* )self->options->get(self->options, self->value) ));
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		o->setText(o, text == NULL ? Orc$str(&tmpReturn_2, "please select")  : text) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_3 = NULL;
	{
		SuiView$TextView*  o = SuiView$mkTextView(&tmpReturn_3, self, 0) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_66_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		o->setText(o, self->isActive ? Orc$str(&tmpReturn_4, " ^ ")  : Orc$str(&tmpReturn_5, " v ") ) ;
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}


void  SuiView$Select$setIsActive(SuiView$Select *  self, bool  v){
	self->isActive = v;
	((SuiCore$Node * )self)->react(self) ;
	((SuiCore$ViewBase * )self)->invalidLayout(self) ;
}


void  SuiView$Select$setValue(SuiView$Select *  self, int  i){
	self->value = i;
	((SuiCore$Node * )self)->invalidReact(self) ;
}


void  SuiView$Select$showPopupMenu(SuiView$Select *  self){
	URGC_VAR_CLEANUP SuiView$__Block_133_24*  __var___Block_133_24 = (__var___Block_133_24=NULL,urgc_init_var((void**)&__var___Block_133_24, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_133_24) , __finiBlock___Block_133_24) ));
	urgc_set_field_class(__var___Block_133_24, (void * )offsetof(SuiView$__Block_133_24, self) , self) ;
	self->setIsActive(self, true) ;
	URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
	URGC_VAR_CLEANUP SuiView$__Closure_onActive_136*  tmpReturn_1 = NULL;
	(urgc_set_var(&onActive, __make___Closure_onActive_136(&tmpReturn_1, __var___Block_133_24) ) );
	URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	{
		SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, Orc$str(&tmpReturn_3, "") , onActive) ;
		
	
		URGC_VAR_CLEANUP SuiView$__Block_144_50*  __var___Block_144_50 = (__var___Block_144_50=NULL,urgc_init_var((void**)&__var___Block_144_50, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_144_50) , __finiBlock___Block_144_50) ));
		for (int  i = 0; i < self->options->size(self->options) ; i++) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  text = (text=NULL,urgc_init_var_class((void**)&text, self->options->get(self->options, i) ));
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_4 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_147_16 = SuiView$mkMenuNativeItem(&tmpReturn_4, o, text, onActive) , *o = __scopeVar_147_16;
				
			
				o->id = i;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  tmpNewOwner_5 = NULL;
		urgc_set_field_class(__var___Block_144_50, (void * )offsetof(SuiView$__Block_144_50, n) , SuiView$MenuNative_new(&tmpNewOwner_5) ) ;
		__var___Block_144_50->n->create(__var___Block_144_50->n, o) ;
		URGC_VAR_CLEANUP SuiView$__Closure_158_28*  tmpReturn_6 = NULL;
		urgc_set_field(__var___Block_144_50->n, (void * )offsetof(SuiView$MenuNative, cbOnDismiss) , __make___Closure_158_28(&tmpReturn_6, __var___Block_133_24) ) ;
		SuiCore$Vec2 p = SuiCore$Mouse_getPos() ;
		URGC_VAR_CLEANUP SuiView$__Closure_170_34*  tmpReturn_7 = NULL;
		SuiCore$requestAnimationFrame(__make___Closure_170_34(&tmpReturn_7, __var___Block_133_24, __var___Block_144_50) ) ;
	}
}


void  SuiView$Select$onEvent(SuiView$Select *  self, SuiCore$Event *  ev){
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
		if (me->isClickInBubble(me) ) {
			printf("Click Select\n") ;
			self->showPopupMenu(self) ;
			ev->stopPropagation(ev) ;
		}
	}
}



static void  __finiBlock___Block_133_24(SuiView$__Block_133_24 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_133_24, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_144_50(SuiView$__Block_144_50 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_144_50, n) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_onActive_136(SuiView$__Closure_onActive_136 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\nactive menu:%d, %s\n\n", item->id, item->label == NULL ? "null" : item->label->str) ;
	self->__var___Block_133_24->self->setValue(self->__var___Block_133_24->self, item->id) ;
	self->__var___Block_133_24->self->fire_onChanged(self->__var___Block_133_24->self) ;
}

static void  __fini___Closure_onActive_136(SuiView$__Closure_onActive_136 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_onActive_136, __var___Block_133_24) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_onActive_136*  __make___Closure_onActive_136(SuiView$__Closure_onActive_136 **  __outRef__, SuiView$__Block_133_24 *  __var___Block_133_24){
	URGC_VAR_CLEANUP SuiView$__Closure_onActive_136*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_onActive_136) , __fini___Closure_onActive_136) ));
	self->invoke = __fn___Closure_onActive_136;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_onActive_136, __var___Block_133_24) , __var___Block_133_24) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_158_28(SuiView$__Closure_158_28 *  self){
	printf("cbOnDismiss\n") ;
	self->__var___Block_133_24->self->setIsActive(self->__var___Block_133_24->self, false) ;
}

static void  __fini___Closure_158_28(SuiView$__Closure_158_28 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_158_28, __var___Block_133_24) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_158_28*  __make___Closure_158_28(SuiView$__Closure_158_28 **  __outRef__, SuiView$__Block_133_24 *  __var___Block_133_24){
	URGC_VAR_CLEANUP SuiView$__Closure_158_28*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_158_28) , __fini___Closure_158_28) ));
	self->invoke = __fn___Closure_158_28;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_158_28, __var___Block_133_24) , __var___Block_133_24) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static bool  __fn___Closure_170_34(SuiView$__Closure_170_34 *  self){
	SuiCore$Rect r = ((SuiCore$ViewBase * )self->__var___Block_133_24->self)->get_abs_rect(self->__var___Block_133_24->self) ;
	self->__var___Block_144_50->n->showAt(self->__var___Block_144_50->n, r.x, SuiCore$Rect$bottom(&r) ) ;
	return true; 
}

static void  __fini___Closure_170_34(SuiView$__Closure_170_34 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_170_34, __var___Block_133_24) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_170_34, __var___Block_144_50) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_170_34*  __make___Closure_170_34(SuiView$__Closure_170_34 **  __outRef__, SuiView$__Block_133_24 *  __var___Block_133_24, SuiView$__Block_144_50 *  __var___Block_144_50){
	URGC_VAR_CLEANUP SuiView$__Closure_170_34*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_170_34) , __fini___Closure_170_34) ));
	self->invoke = __fn___Closure_170_34;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_170_34, __var___Block_133_24) , __var___Block_133_24) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_170_34, __var___Block_144_50) , __var___Block_144_50) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$Select*  SuiView$mkSelect(SuiView$Select **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$Select* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$Select_init(NULL)) ) ; 
}



