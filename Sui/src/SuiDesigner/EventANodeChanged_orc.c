
#include "EventANodeChanged_orc.h" 

#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "./ANode_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$EventToEbus _vtable_SuiDesigner$EventToEbus;

// init meta

void SuiDesigner$EventToEbus_initMeta(Vtable_SuiDesigner$EventToEbus *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "emitToEbus", offsetof(SuiDesigner$EventToEbus, emitToEbus));
}


// vtable init


Vtable_SuiDesigner$EventToEbus* Vtable_SuiDesigner$EventToEbus_init(Vtable_SuiDesigner$EventToEbus* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EventToEbus;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EventToEbus_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EventToEbus";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EventToEbus_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EventToEbus_fini(SuiDesigner$EventToEbus *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放


}

// init fields function


void SuiDesigner$EventToEbus_init_fields(SuiDesigner$EventToEbus *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EventToEbus_fini;
	//fields
    {
	
    }
	((SuiDesigner$EventToEbus*)self)->emitToEbus = (void*)SuiDesigner$EventToEbus$emitToEbus;
}

// init function

void SuiDesigner$EventToEbus_init(SuiDesigner$EventToEbus *self, void *pOwner){
    Vtable_SuiDesigner$EventToEbus_init(&_vtable_SuiDesigner$EventToEbus);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EventToEbus;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EventToEbus_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EventToEbus * SuiDesigner$EventToEbus_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EventToEbus *self = calloc(1, sizeof(SuiDesigner$EventToEbus));
	
    SuiDesigner$EventToEbus_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$EventToEbus$emitToEbus(SuiDesigner$EventToEbus *  self){
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, self) ;
}




//vtable instance
Vtable_SuiDesigner$EventANodeChanged _vtable_SuiDesigner$EventANodeChanged;

// init meta

void SuiDesigner$EventANodeChanged_initMeta(Vtable_SuiDesigner$EventANodeChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "anode", ((Vtable_Object*)Vtable_SuiDesigner$ANode_init(0)), offsetof(SuiDesigner$EventANodeChanged, anode), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$EventANodeChanged* Vtable_SuiDesigner$EventANodeChanged_init(Vtable_SuiDesigner$EventANodeChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EventANodeChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$EventToEbus_init(&_vtable_SuiDesigner$EventToEbus);

	// init by super vtable init function
    Vtable_SuiDesigner$EventToEbus_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$EventToEbus;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EventANodeChanged_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EventANodeChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EventANodeChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EventANodeChanged_fini(SuiDesigner$EventANodeChanged *self){
	//super fini
    SuiDesigner$EventToEbus_fini((SuiDesigner$EventToEbus *)self);

    //字段释放


}

// init fields function


void SuiDesigner$EventANodeChanged_init_fields(SuiDesigner$EventANodeChanged *self){
	//super class
    SuiDesigner$EventToEbus_init_fields((SuiDesigner$EventToEbus*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EventANodeChanged_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$EventANodeChanged*)self)->anode, NULL);
    }
	
}

// init function

void SuiDesigner$EventANodeChanged_init(SuiDesigner$EventANodeChanged *self, void *pOwner){
    Vtable_SuiDesigner$EventANodeChanged_init(&_vtable_SuiDesigner$EventANodeChanged);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EventANodeChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EventANodeChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EventANodeChanged * SuiDesigner$EventANodeChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EventANodeChanged *self = calloc(1, sizeof(SuiDesigner$EventANodeChanged));
	
    SuiDesigner$EventANodeChanged_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$EventANodeAttrChanged _vtable_SuiDesigner$EventANodeAttrChanged;

// init meta

void SuiDesigner$EventANodeAttrChanged_initMeta(Vtable_SuiDesigner$EventANodeAttrChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "anode", ((Vtable_Object*)Vtable_SuiDesigner$ANode_init(0)), offsetof(SuiDesigner$EventANodeAttrChanged, anode), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$EventANodeAttrChanged* Vtable_SuiDesigner$EventANodeAttrChanged_init(Vtable_SuiDesigner$EventANodeAttrChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EventANodeAttrChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$EventToEbus_init(&_vtable_SuiDesigner$EventToEbus);

	// init by super vtable init function
    Vtable_SuiDesigner$EventToEbus_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$EventToEbus;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EventANodeAttrChanged_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EventANodeAttrChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EventANodeAttrChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EventANodeAttrChanged_fini(SuiDesigner$EventANodeAttrChanged *self){
	//super fini
    SuiDesigner$EventToEbus_fini((SuiDesigner$EventToEbus *)self);

    //字段释放


}

// init fields function


void SuiDesigner$EventANodeAttrChanged_init_fields(SuiDesigner$EventANodeAttrChanged *self){
	//super class
    SuiDesigner$EventToEbus_init_fields((SuiDesigner$EventToEbus*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EventANodeAttrChanged_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$EventANodeAttrChanged*)self)->anode, NULL);
    }
	
}

// init function

void SuiDesigner$EventANodeAttrChanged_init(SuiDesigner$EventANodeAttrChanged *self, void *pOwner){
    Vtable_SuiDesigner$EventANodeAttrChanged_init(&_vtable_SuiDesigner$EventANodeAttrChanged);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EventANodeAttrChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EventANodeAttrChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EventANodeAttrChanged * SuiDesigner$EventANodeAttrChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EventANodeAttrChanged *self = calloc(1, sizeof(SuiDesigner$EventANodeAttrChanged));
	
    SuiDesigner$EventANodeAttrChanged_init(self, pOwner);
    return self;
}


// class members



