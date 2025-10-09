
#include "Event_orc.h" 

#include <stdio.h>
#include "../../Orc/String_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$Event _vtable_SuiCore$Event;

// init meta

void SuiCore$Event_initMeta(Vtable_SuiCore$Event *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiCore$Event, name), true, false, 1);
	orc_metaField_primitive(&pNext, "isStopPropagation", OrcMetaType_int, offsetof(SuiCore$Event, isStopPropagation), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "stopPropagation", offsetof(SuiCore$Event, stopPropagation));
	orc_metaField_method(&pNext, "stopImmediatePropagation", offsetof(SuiCore$Event, stopImmediatePropagation));
}


// vtable init


Vtable_SuiCore$Event* Vtable_SuiCore$Event_init(Vtable_SuiCore$Event* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Event;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Event_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Event";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Event_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$Event_fini(SuiCore$Event *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$Event*)self)->name);

}

// init fields function


void SuiCore$Event_init_fields(SuiCore$Event *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Event_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$Event*)self)->name, Orc$str(&tmpReturn_1, "") );
	((SuiCore$Event*)self)->isStopPropagation = 0;
    }
	((SuiCore$Event*)self)->stopPropagation = (void*)SuiCore$Event$stopPropagation;
	((SuiCore$Event*)self)->stopImmediatePropagation = (void*)SuiCore$Event$stopImmediatePropagation;
}

// init function

void SuiCore$Event_init(SuiCore$Event *self, void *pOwner){
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Event;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Event_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Event * SuiCore$Event_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Event *self = calloc(1, sizeof(SuiCore$Event));
	
    SuiCore$Event_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$Event$stopPropagation(SuiCore$Event *  self){
	self->isStopPropagation = 1;
}


void  SuiCore$Event$stopImmediatePropagation(SuiCore$Event *  self){
	self->isStopPropagation = 2;
}



void  SuiCore$testEvent(){
	URGC_VAR_CLEANUP_CLASS SuiCore$Event*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiCore$Event_new(&e) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(e, (void * )offsetof(SuiCore$Event, name) , Orc$str(&tmpReturn_1, "test") ) ;
	printf("testEvent:%s\n", e->name->str) ;
	e->stopPropagation(e) ;
	printf("testEvent stopPropagation:%d\n", e->isStopPropagation) ;
}



