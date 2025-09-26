
#include "KeyEvent_orc.h" 

#include <stdio.h>
#include "./Event_orc.h"
#include "./MouseEvent_orc.h"
#include "../../Orc/String_orc.h"
#include "./Window_orc.h"
#include "./App_orc.h"
#include "./Focus_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$TextEventBase _vtable_SuiCore$TextEventBase;

// init meta

void SuiCore$TextEventBase_initMeta(Vtable_SuiCore$TextEventBase *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "window", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(SuiCore$TextEventBase, window), true, false, 1);

	orc_metaField_method(&pNext, "dispatch", offsetof(SuiCore$TextEventBase, dispatch));
}


// vtable init


Vtable_SuiCore$TextEventBase* Vtable_SuiCore$TextEventBase_init(Vtable_SuiCore$TextEventBase* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$TextEventBase;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$ViewEvent_init(&_vtable_SuiCore$ViewEvent);

	// init by super vtable init function
    Vtable_SuiCore$ViewEvent_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$ViewEvent;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$TextEventBase_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$TextEventBase";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$TextEventBase_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$TextEventBase_fini(SuiCore$TextEventBase *self){
	//super fini
    SuiCore$ViewEvent_fini((SuiCore$ViewEvent *)self);

    //字段释放


}

// init fields function


void SuiCore$TextEventBase_init_fields(SuiCore$TextEventBase *self){
	//super class
    SuiCore$ViewEvent_init_fields((SuiCore$ViewEvent*)self);

    ((Object*)self)->fini = (void*)SuiCore$TextEventBase_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiCore$TextEventBase*)self)->window, NULL);
    }
	((SuiCore$TextEventBase*)self)->dispatch = (void*)SuiCore$TextEventBase$dispatch;
}

// init function

void SuiCore$TextEventBase_init(SuiCore$TextEventBase *self, void *pOwner){
    Vtable_SuiCore$TextEventBase_init(&_vtable_SuiCore$TextEventBase);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$TextEventBase;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$TextEventBase_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$TextEventBase * SuiCore$TextEventBase_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$TextEventBase *self = calloc(1, sizeof(SuiCore$TextEventBase));
	
    SuiCore$TextEventBase_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$TextEventBase$dispatch(SuiCore$TextEventBase *  self){
	SuiCore$Focus *  f = SuiCore$insFocus() ;
	if (f->focusNode != NULL) {
		((SuiCore$Emitter * )f->focusNode)->emit(f->focusNode, self) ;
	}
	if (!((SuiCore$Event * )self)->isStopPropagation && self->window != NULL) {
		((SuiCore$Emitter * )self->window)->emit(self->window, self) ;
	}
}




//vtable instance
Vtable_SuiCore$TextEditingEvent _vtable_SuiCore$TextEditingEvent;

// init meta

void SuiCore$TextEditingEvent_initMeta(Vtable_SuiCore$TextEditingEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "text", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiCore$TextEditingEvent, text), true, false, 1);
	orc_metaField_primitive(&pNext, "start", OrcMetaType_int, offsetof(SuiCore$TextEditingEvent, start), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "length", OrcMetaType_int, offsetof(SuiCore$TextEditingEvent, length), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "reset", offsetof(SuiCore$TextEditingEvent, reset));
	orc_metaField_method(&pNext, "is_editing", offsetof(SuiCore$TextEditingEvent, is_editing));
	orc_metaField_method(&pNext, "total_rune_length", offsetof(SuiCore$TextEditingEvent, total_rune_length));
}


// vtable init


Vtable_SuiCore$TextEditingEvent* Vtable_SuiCore$TextEditingEvent_init(Vtable_SuiCore$TextEditingEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$TextEditingEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$TextEventBase_init(&_vtable_SuiCore$TextEventBase);

	// init by super vtable init function
    Vtable_SuiCore$TextEventBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$TextEventBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$TextEditingEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$TextEditingEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$TextEditingEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$TextEditingEvent_fini(SuiCore$TextEditingEvent *self){
	//super fini
    SuiCore$TextEventBase_fini((SuiCore$TextEventBase *)self);

    //字段释放


}

// init fields function


void SuiCore$TextEditingEvent_init_fields(SuiCore$TextEditingEvent *self){
	//super class
    SuiCore$TextEventBase_init_fields((SuiCore$TextEventBase*)self);

    ((Object*)self)->fini = (void*)SuiCore$TextEditingEvent_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiCore$TextEditingEvent*)self)->text, NULL);
	((SuiCore$TextEditingEvent*)self)->start = 0;
	((SuiCore$TextEditingEvent*)self)->length = 0;
    }
	((SuiCore$TextEditingEvent*)self)->reset = (void*)SuiCore$TextEditingEvent$reset;
	((SuiCore$TextEditingEvent*)self)->is_editing = (void*)SuiCore$TextEditingEvent$is_editing;
	((SuiCore$TextEditingEvent*)self)->total_rune_length = (void*)SuiCore$TextEditingEvent$total_rune_length;
}

// init function

void SuiCore$TextEditingEvent_init(SuiCore$TextEditingEvent *self, void *pOwner){
    Vtable_SuiCore$TextEditingEvent_init(&_vtable_SuiCore$TextEditingEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$TextEditingEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$TextEditingEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$TextEditingEvent * SuiCore$TextEditingEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$TextEditingEvent *self = calloc(1, sizeof(SuiCore$TextEditingEvent));
	
    SuiCore$TextEditingEvent_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$TextEditingEvent$reset(SuiCore$TextEditingEvent *  self){
	self->start = 0;
	self->length = 0;
}


bool  SuiCore$TextEditingEvent$is_editing(SuiCore$TextEditingEvent *  self){
	return self->start + self->length > 0; 
}


int  SuiCore$TextEditingEvent$total_rune_length(SuiCore$TextEditingEvent *  self){
	return self->start + self->length; 
}



void  SuiCore$dispatchImeEndComposition(long long  windowId){
	printf("输入法合成结束事件\n") ;
}

void  SuiCore$dispatchImeComposition(const char *  text, int  start, int  length, long long  windowId){
	printf("输入法合成事件 text:%s, start:%d, length:%d, windowId:%lld\n", text, start, length, windowId) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, app->findWindowById(app, windowId) ));
	URGC_VAR_CLEANUP_CLASS SuiCore$TextEditingEvent*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiCore$TextEditingEvent_new(&e) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(e, (void * )offsetof(SuiCore$TextEditingEvent, text) , Orc$str(&tmpReturn_1, text) ) ;
	e->start = start;
	e->length = length;
	urgc_set_field_class(e, (void * )offsetof(SuiCore$TextEventBase, window) , win) ;
	SuiCore$dispatchEventToFocusNode(e, win) ;
}


//vtable instance
Vtable_SuiCore$TextInputEvent _vtable_SuiCore$TextInputEvent;

// init meta

void SuiCore$TextInputEvent_initMeta(Vtable_SuiCore$TextInputEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "text", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiCore$TextInputEvent, text), true, false, 1);

	
}


// vtable init


Vtable_SuiCore$TextInputEvent* Vtable_SuiCore$TextInputEvent_init(Vtable_SuiCore$TextInputEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$TextInputEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$TextEventBase_init(&_vtable_SuiCore$TextEventBase);

	// init by super vtable init function
    Vtable_SuiCore$TextEventBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$TextEventBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$TextInputEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$TextInputEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$TextInputEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$TextInputEvent_fini(SuiCore$TextInputEvent *self){
	//super fini
    SuiCore$TextEventBase_fini((SuiCore$TextEventBase *)self);

    //字段释放


}

// init fields function


void SuiCore$TextInputEvent_init_fields(SuiCore$TextInputEvent *self){
	//super class
    SuiCore$TextEventBase_init_fields((SuiCore$TextEventBase*)self);

    ((Object*)self)->fini = (void*)SuiCore$TextInputEvent_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiCore$TextInputEvent*)self)->text, NULL);
    }
	
}

// init function

void SuiCore$TextInputEvent_init(SuiCore$TextInputEvent *self, void *pOwner){
    Vtable_SuiCore$TextInputEvent_init(&_vtable_SuiCore$TextInputEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$TextInputEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$TextInputEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$TextInputEvent * SuiCore$TextInputEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$TextInputEvent *self = calloc(1, sizeof(SuiCore$TextInputEvent));
	
    SuiCore$TextInputEvent_init(self, pOwner);
    return self;
}


// class members

void  SuiCore$dispatchTextInputEvent(const char *  text, long long  windowId){
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, app->findWindowById(app, windowId) ));
	URGC_VAR_CLEANUP_CLASS SuiCore$TextInputEvent*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiCore$TextInputEvent_new(&e) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(e, (void * )offsetof(SuiCore$TextInputEvent, text) , Orc$str(&tmpReturn_1, text) ) ;
	urgc_set_field_class(e, (void * )offsetof(SuiCore$TextEventBase, window) , win) ;
	printf("dispatchTextInputEvent:%s\n", e->text->str) ;
	SuiCore$dispatchEventToFocusNode(e, win) ;
}


//vtable instance
Vtable_SuiCore$KeyEvent _vtable_SuiCore$KeyEvent;

// init meta

void SuiCore$KeyEvent_initMeta(Vtable_SuiCore$KeyEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "char_code", OrcMetaType_int, offsetof(SuiCore$KeyEvent, char_code), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "key", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiCore$KeyEvent, key), true, false, 1);
	orc_metaField_primitive(&pNext, "isKeyDown", OrcMetaType_bool, offsetof(SuiCore$KeyEvent, isKeyDown), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isKeyUp", OrcMetaType_bool, offsetof(SuiCore$KeyEvent, isKeyUp), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "shift", OrcMetaType_bool, offsetof(SuiCore$KeyEvent, shift), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "ctrl", OrcMetaType_bool, offsetof(SuiCore$KeyEvent, ctrl), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "alt", OrcMetaType_bool, offsetof(SuiCore$KeyEvent, alt), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "window", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(SuiCore$KeyEvent, window), true, false, 1);

	orc_metaField_method(&pNext, "setIsKeyDown", offsetof(SuiCore$KeyEvent, setIsKeyDown));
	orc_metaField_method(&pNext, "dispatch", offsetof(SuiCore$KeyEvent, dispatch));
}


// vtable init


Vtable_SuiCore$KeyEvent* Vtable_SuiCore$KeyEvent_init(Vtable_SuiCore$KeyEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$KeyEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$KeyEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$KeyEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$KeyEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$KeyEvent_fini(SuiCore$KeyEvent *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放


}

// init fields function


void SuiCore$KeyEvent_init_fields(SuiCore$KeyEvent *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiCore$KeyEvent_fini;
	//fields
    {
	((SuiCore$KeyEvent*)self)->char_code = 0;
	urgc_set_field_class(self, (void**)&((SuiCore$KeyEvent*)self)->key, NULL);
	((SuiCore$KeyEvent*)self)->isKeyDown = false;
	((SuiCore$KeyEvent*)self)->isKeyUp = false;
	((SuiCore$KeyEvent*)self)->shift = false;
	((SuiCore$KeyEvent*)self)->ctrl = false;
	((SuiCore$KeyEvent*)self)->alt = false;
	urgc_set_field_class(self, (void**)&((SuiCore$KeyEvent*)self)->window, NULL);
    }
	((SuiCore$KeyEvent*)self)->setIsKeyDown = (void*)SuiCore$KeyEvent$setIsKeyDown;
	((SuiCore$KeyEvent*)self)->dispatch = (void*)SuiCore$KeyEvent$dispatch;
}

// init function

void SuiCore$KeyEvent_init(SuiCore$KeyEvent *self, void *pOwner){
    Vtable_SuiCore$KeyEvent_init(&_vtable_SuiCore$KeyEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$KeyEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$KeyEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$KeyEvent * SuiCore$KeyEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$KeyEvent *self = calloc(1, sizeof(SuiCore$KeyEvent));
	
    SuiCore$KeyEvent_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$KeyEvent$setIsKeyDown(SuiCore$KeyEvent *  self, bool  isKeyDown){
	self->isKeyDown = isKeyDown;
	self->isKeyUp = !isKeyDown;
}


void  SuiCore$KeyEvent$dispatch(SuiCore$KeyEvent *  self){
	SuiCore$dispatchEventToFocusNode(self, self->window) ;
}



void  SuiCore$dispatchEventToFocusNode(SuiCore$Event *  evt, Sui$Window *  window){
	SuiCore$Focus *  f = SuiCore$insFocus() ;
	if (f->focusNode != NULL) {
		((SuiCore$Emitter * )f->focusNode)->emit(f->focusNode, evt) ;
	}
	if (!evt->isStopPropagation && window != NULL) {
		((SuiCore$Emitter * )window)->emit(window, evt) ;
	}
}


//vtable instance
Vtable_SuiCore$WindowFocusEvent _vtable_SuiCore$WindowFocusEvent;

// init meta

void SuiCore$WindowFocusEvent_initMeta(Vtable_SuiCore$WindowFocusEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "isFocus", OrcMetaType_bool, offsetof(SuiCore$WindowFocusEvent, isFocus), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isBlur", OrcMetaType_bool, offsetof(SuiCore$WindowFocusEvent, isBlur), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "window", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(SuiCore$WindowFocusEvent, window), true, false, 1);

	
}


// vtable init


Vtable_SuiCore$WindowFocusEvent* Vtable_SuiCore$WindowFocusEvent_init(Vtable_SuiCore$WindowFocusEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$WindowFocusEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$WindowFocusEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$WindowFocusEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$WindowFocusEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$WindowFocusEvent_fini(SuiCore$WindowFocusEvent *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放


}

// init fields function


void SuiCore$WindowFocusEvent_init_fields(SuiCore$WindowFocusEvent *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiCore$WindowFocusEvent_fini;
	//fields
    {
	((SuiCore$WindowFocusEvent*)self)->isFocus = false;
	((SuiCore$WindowFocusEvent*)self)->isBlur = false;
	urgc_set_field_class(self, (void**)&((SuiCore$WindowFocusEvent*)self)->window, NULL);
    }
	
}

// init function

void SuiCore$WindowFocusEvent_init(SuiCore$WindowFocusEvent *self, void *pOwner){
    Vtable_SuiCore$WindowFocusEvent_init(&_vtable_SuiCore$WindowFocusEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$WindowFocusEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$WindowFocusEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$WindowFocusEvent * SuiCore$WindowFocusEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$WindowFocusEvent *self = calloc(1, sizeof(SuiCore$WindowFocusEvent));
	
    SuiCore$WindowFocusEvent_init(self, pOwner);
    return self;
}


// class members

void  SuiCore$dispatchWindowFocusEvent(SuiCore$WindowFocusEvent *  e){
	SuiCore$Focus *  f = SuiCore$insFocus() ;
	if (f->focusNode != NULL) {
		((SuiCore$Emitter * )f->focusNode)->emit(f->focusNode, e) ;
	}
	Sui$Window *  window = e->window;
	if (!((SuiCore$Event * )e)->isStopPropagation && window != NULL) {
		((SuiCore$Emitter * )window)->emit(window, e) ;
	}
}



