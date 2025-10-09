
#include "Emitter_orc.h" 

#include <stdio.h>
#include "../../Orc/List_orc.h"
#include "../../Orc/String_orc.h"
#include "./Event_orc.h"


// static struct 
typedef struct tagSuiCore$__Closure_88_18 SuiCore$__Closure_88_18;



struct tagSuiCore$__Closure_88_18 {
	void  (*invoke)(SuiCore$__Closure_88_18 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





// static function declaration
static void  __fn___Closure_88_18(SuiCore$__Closure_88_18 *  self, SuiCore$Event *  e);
static void  __fini___Closure_88_18(SuiCore$__Closure_88_18 *  self);
static SuiCore$__Closure_88_18*  __make___Closure_88_18(SuiCore$__Closure_88_18 **  __outRef__);



//vtable instance
Vtable_SuiCore$Listener _vtable_SuiCore$Listener;

// init meta

void SuiCore$Listener_initMeta(Vtable_SuiCore$Listener *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "onListenerEvent", offsetof(SuiCore$Listener, onListenerEvent));
}


// vtable init


Vtable_SuiCore$Listener* Vtable_SuiCore$Listener_init(Vtable_SuiCore$Listener* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Listener;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Listener_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Listener";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Listener_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$Listener_fini(SuiCore$Listener *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$Listener_init_fields(SuiCore$Listener *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Listener_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)SuiCore$Listener$ctor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiCore$Listener$onListenerEvent;
}

// init function

void SuiCore$Listener_init(SuiCore$Listener *self, void *pOwner){
    Vtable_SuiCore$Listener_init(&_vtable_SuiCore$Listener);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Listener;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Listener_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Listener * SuiCore$Listener_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Listener *self = calloc(1, sizeof(SuiCore$Listener));
	
    SuiCore$Listener_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$Listener$ctor(SuiCore$Listener *  self){
	
}


void  SuiCore$Listener$onListenerEvent(SuiCore$Listener *  self, SuiCore$Event *  event){
	
}




//vtable instance
Vtable_SuiCore$Emitter _vtable_SuiCore$Emitter;

// init meta

void SuiCore$Emitter_initMeta(Vtable_SuiCore$Emitter *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "listeners", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$Emitter, listeners), true, false, 1);
	orc_metaField_class(&pNext, "listener", ((Vtable_Object*)Vtable_SuiCore$Listener_init(0)), offsetof(SuiCore$Emitter, listener), true, false, 1);

	orc_metaField_method(&pNext, "addListenerOnce", offsetof(SuiCore$Emitter, addListenerOnce));
	orc_metaField_method(&pNext, "addListener", offsetof(SuiCore$Emitter, addListener));
	orc_metaField_method(&pNext, "removeListener", offsetof(SuiCore$Emitter, removeListener));
	orc_metaField_method(&pNext, "emit", offsetof(SuiCore$Emitter, emit));
	orc_metaField_method(&pNext, "onEvent", offsetof(SuiCore$Emitter, onEvent));
}


// vtable init


Vtable_SuiCore$Emitter* Vtable_SuiCore$Emitter_init(Vtable_SuiCore$Emitter* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Emitter;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Listener_init(&_vtable_SuiCore$Listener);

	// init by super vtable init function
    Vtable_SuiCore$Listener_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Listener;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Emitter_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Emitter";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Emitter_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$Emitter_fini(SuiCore$Emitter *self){
	//super fini
    SuiCore$Listener_fini((SuiCore$Listener *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$Emitter*)self)->listeners);
	urgc_fini_field_class(self, (void**)&((SuiCore$Emitter*)self)->listener);

}

// init fields function


void SuiCore$Emitter_init_fields(SuiCore$Emitter *self){
	//super class
    SuiCore$Listener_init_fields((SuiCore$Listener*)self);

    ((Object*)self)->fini = (void*)SuiCore$Emitter_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$Emitter*)self)->listeners, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiCore$Emitter*)self)->listener, NULL);
	urgc_set_field(self, (void**)&((SuiCore$Emitter*)self)->cbOnEvent, NULL);
    }
	((SuiCore$Emitter*)self)->addListenerOnce = (void*)SuiCore$Emitter$addListenerOnce;
	((SuiCore$Emitter*)self)->addListener = (void*)SuiCore$Emitter$addListener;
	((SuiCore$Emitter*)self)->removeListener = (void*)SuiCore$Emitter$removeListener;
	((SuiCore$Emitter*)self)->emit = (void*)SuiCore$Emitter$emit;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiCore$Emitter$onEvent;
}

// init function

void SuiCore$Emitter_init(SuiCore$Emitter *self, void *pOwner){
    Vtable_SuiCore$Emitter_init(&_vtable_SuiCore$Emitter);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Emitter;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Emitter_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Emitter * SuiCore$Emitter_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Emitter *self = calloc(1, sizeof(SuiCore$Emitter));
	
    SuiCore$Emitter_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$Emitter$addListenerOnce(SuiCore$Emitter *  self, SuiCore$Listener *  listener){
	self->listeners->addOnce(self->listeners, listener) ;
}


void  SuiCore$Emitter$addListener(SuiCore$Emitter *  self, SuiCore$Listener *  listener){
	self->listeners->add(self->listeners, listener) ;
}


void  SuiCore$Emitter$removeListener(SuiCore$Emitter *  self, SuiCore$Listener *  listener){
	self->listeners->remove(self->listeners, listener) ;
}


void  SuiCore$Emitter$emit(SuiCore$Emitter *  self, SuiCore$Event *  event){
	if (self->cbOnEvent != NULL) {
		(*(self->cbOnEvent))((void * )(self->cbOnEvent), event) ;
	}
	if (event->isStopPropagation == 2) {
		return ; 
	}
	self->onEvent(self, event) ;
	if (event->isStopPropagation == 2) {
		return ; 
	}
	if (self->listener) {
		self->listener->onListenerEvent(self->listener, event) ;
	}
	if (event->isStopPropagation == 2) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmps = self->listeners->copy((tmps = NULL,&tmps), self->listeners) ;
	for (int  i = 0; i < tmps->size(tmps) ; i++) {
		URGC_VAR_CLEANUP_CLASS SuiCore$Listener*  listener = (listener=NULL,urgc_init_var_class((void**)&listener, (SuiCore$Listener* )tmps->get(tmps, i) ));
		if (listener) {
			listener->onListenerEvent(listener, event) ;
			if (event->isStopPropagation == 2) {
				return ; 
			}
		}
	}
}


void  SuiCore$Emitter$onEvent(SuiCore$Emitter *  self, SuiCore$Event *  event){
	
}



SuiCore$Emitter *  SuiCore$useEbus(){
	static URGC_VAR_CLEANUP_CLASS SuiCore$Emitter*  ins = NULL;
	if (!ins) {
		URGC_VAR_CLEANUP_CLASS SuiCore$Emitter*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&ins, SuiCore$Emitter_new(&tmpNewOwner_1) ) ;
	}
	return ins; 
}

void  SuiCore$testEmitter(){
	URGC_VAR_CLEANUP_CLASS SuiCore$Emitter*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiCore$Emitter_new(&e) ));
	URGC_VAR_CLEANUP SuiCore$__Closure_88_18*  tmpReturn_1 = NULL;
	urgc_set_field(e, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_88_18(&tmpReturn_1) ) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$Event*  ev = (ev=NULL,urgc_init_var_class((void**)&ev, SuiCore$Event_new(&ev) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(ev, (void * )offsetof(SuiCore$Event, name) , Orc$str(&tmpReturn_2, "点击事件") ) ;
	e->emit(e, ev) ;
	printf("test emitter\n") ;
}

static void  __fn___Closure_88_18(SuiCore$__Closure_88_18 *  self, SuiCore$Event *  e){
	printf("cbOnEvent: event Name:%s\n", e->name->str) ;
}

static void  __fini___Closure_88_18(SuiCore$__Closure_88_18 *  self){
	urgc_free_later(self) ;
}

static SuiCore$__Closure_88_18*  __make___Closure_88_18(SuiCore$__Closure_88_18 **  __outRef__){
	URGC_VAR_CLEANUP SuiCore$__Closure_88_18*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiCore$__Closure_88_18) , __fini___Closure_88_18) ));
	self->invoke = __fn___Closure_88_18;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



