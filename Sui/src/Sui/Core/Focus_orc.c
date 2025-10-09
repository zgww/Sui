
#include "Focus_orc.h" 

#include <stdio.h>
#include "./Node_orc.h"
#include "./Event_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$FocusEvent _vtable_SuiCore$FocusEvent;

// init meta

void SuiCore$FocusEvent_initMeta(Vtable_SuiCore$FocusEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "isFocus", OrcMetaType_bool, offsetof(SuiCore$FocusEvent, isFocus), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isBlur", OrcMetaType_bool, offsetof(SuiCore$FocusEvent, isBlur), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "source", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiCore$FocusEvent, source), true, false, 1);

	orc_metaField_method(&pNext, "init", offsetof(SuiCore$FocusEvent, init));
}


// vtable init


Vtable_SuiCore$FocusEvent* Vtable_SuiCore$FocusEvent_init(Vtable_SuiCore$FocusEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$FocusEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$FocusEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$FocusEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$FocusEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$FocusEvent_fini(SuiCore$FocusEvent *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$FocusEvent*)self)->source);

}

// init fields function


void SuiCore$FocusEvent_init_fields(SuiCore$FocusEvent *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiCore$FocusEvent_fini;
	//fields
    {
	((SuiCore$FocusEvent*)self)->isFocus = false;
	((SuiCore$FocusEvent*)self)->isBlur = false;
	urgc_set_field_class(self, (void**)&((SuiCore$FocusEvent*)self)->source, NULL);
    }
	((SuiCore$FocusEvent*)self)->init = (void*)SuiCore$FocusEvent$init;
}

// init function

void SuiCore$FocusEvent_init(SuiCore$FocusEvent *self, void *pOwner){
    Vtable_SuiCore$FocusEvent_init(&_vtable_SuiCore$FocusEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$FocusEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$FocusEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$FocusEvent * SuiCore$FocusEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$FocusEvent *self = calloc(1, sizeof(SuiCore$FocusEvent));
	
    SuiCore$FocusEvent_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$FocusEvent$init(SuiCore$FocusEvent *  self, SuiCore$Node *  source, bool  b){
	urgc_set_field_class(self, (void * )offsetof(SuiCore$FocusEvent, source) , source) ;
	self->isFocus = b;
	self->isBlur = !b;
}




//vtable instance
Vtable_SuiCore$Focus _vtable_SuiCore$Focus;

// init meta

void SuiCore$Focus_initMeta(Vtable_SuiCore$Focus *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "focusNode", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiCore$Focus, focusNode), true, false, 1);

	orc_metaField_method(&pNext, "focus", offsetof(SuiCore$Focus, focus));
	orc_metaField_method(&pNext, "blurNode", offsetof(SuiCore$Focus, blurNode));
	orc_metaField_method(&pNext, "blur", offsetof(SuiCore$Focus, blur));
	orc_metaField_method(&pNext, "getFocusNode", offsetof(SuiCore$Focus, getFocusNode));
	orc_metaField_method(&pNext, "isFocus", offsetof(SuiCore$Focus, isFocus));
	orc_metaField_method(&pNext, "hasFocus", offsetof(SuiCore$Focus, hasFocus));
}


// vtable init


Vtable_SuiCore$Focus* Vtable_SuiCore$Focus_init(Vtable_SuiCore$Focus* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Focus;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Focus_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Focus";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Focus_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$Focus_fini(SuiCore$Focus *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$Focus*)self)->focusNode);

}

// init fields function


void SuiCore$Focus_init_fields(SuiCore$Focus *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Focus_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiCore$Focus*)self)->focusNode, NULL);
    }
	((SuiCore$Focus*)self)->focus = (void*)SuiCore$Focus$focus;
	((SuiCore$Focus*)self)->blurNode = (void*)SuiCore$Focus$blurNode;
	((SuiCore$Focus*)self)->blur = (void*)SuiCore$Focus$blur;
	((SuiCore$Focus*)self)->getFocusNode = (void*)SuiCore$Focus$getFocusNode;
	((SuiCore$Focus*)self)->isFocus = (void*)SuiCore$Focus$isFocus;
	((SuiCore$Focus*)self)->hasFocus = (void*)SuiCore$Focus$hasFocus;
}

// init function

void SuiCore$Focus_init(SuiCore$Focus *self, void *pOwner){
    Vtable_SuiCore$Focus_init(&_vtable_SuiCore$Focus);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Focus;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Focus_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Focus * SuiCore$Focus_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Focus *self = calloc(1, sizeof(SuiCore$Focus));
	
    SuiCore$Focus_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$Focus$focus(SuiCore$Focus *  self, SuiCore$Node *  node){
	if (node == self->focusNode) {
		return ; 
	}
	if (self->focusNode != NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$FocusEvent*  ev = (ev=NULL,urgc_init_var_class((void**)&ev, SuiCore$FocusEvent_new(&ev) ));
		ev->init(ev, self->focusNode, false) ;
		((SuiCore$Emitter * )self->focusNode)->emit(self->focusNode, ev) ;
	}
	urgc_set_field_class(self, (void * )offsetof(SuiCore$Focus, focusNode) , node) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$FocusEvent*  ev = (ev=NULL,urgc_init_var_class((void**)&ev, SuiCore$FocusEvent_new(&ev) ));
	ev->init(ev, self->focusNode, true) ;
	((SuiCore$Emitter * )self->focusNode)->emit(self->focusNode, ev) ;
}


void  SuiCore$Focus$blurNode(SuiCore$Focus *  self, SuiCore$Node *  n){
	if (self->focusNode == n) {
		self->blur(self) ;
	}
}


void  SuiCore$Focus$blur(SuiCore$Focus *  self){
	if (self->focusNode != NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$FocusEvent*  ev = (ev=NULL,urgc_init_var_class((void**)&ev, SuiCore$FocusEvent_new(&ev) ));
		ev->init(ev, self->focusNode, false) ;
		((SuiCore$Emitter * )self->focusNode)->emit(self->focusNode, ev) ;
		urgc_set_field_class(self, (void * )offsetof(SuiCore$Focus, focusNode) , NULL) ;
	}
}


SuiCore$Node *  SuiCore$Focus$getFocusNode(SuiCore$Focus *  self){
	return self->focusNode; 
}


bool  SuiCore$Focus$isFocus(SuiCore$Focus *  self, SuiCore$Node *  node){
	return self->focusNode == node; 
}


bool  SuiCore$Focus$hasFocus(SuiCore$Focus *  self){
	return self->focusNode != NULL; 
}



SuiCore$Focus *  SuiCore$insFocus(){
	static URGC_VAR_CLEANUP_CLASS SuiCore$Focus*  ins = NULL;
	if (ins == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$Focus*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&ins, SuiCore$Focus_new(&tmpNewOwner_1) ) ;
	}
	return ins; 
}



