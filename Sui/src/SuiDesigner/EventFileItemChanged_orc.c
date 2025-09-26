
#include "EventFileItemChanged_orc.h" 

#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "./FileItem_orc.h"
#include "./EventANodeChanged_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$EventFileItemChanged _vtable_SuiDesigner$EventFileItemChanged;

// init meta

void SuiDesigner$EventFileItemChanged_initMeta(Vtable_SuiDesigner$EventFileItemChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "fileItem", ((Vtable_Object*)Vtable_SuiDesigner$FileItem_init(0)), offsetof(SuiDesigner$EventFileItemChanged, fileItem), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$EventFileItemChanged* Vtable_SuiDesigner$EventFileItemChanged_init(Vtable_SuiDesigner$EventFileItemChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EventFileItemChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$EventToEbus_init(&_vtable_SuiDesigner$EventToEbus);

	// init by super vtable init function
    Vtable_SuiDesigner$EventToEbus_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$EventToEbus;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EventFileItemChanged_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EventFileItemChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EventFileItemChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EventFileItemChanged_fini(SuiDesigner$EventFileItemChanged *self){
	//super fini
    SuiDesigner$EventToEbus_fini((SuiDesigner$EventToEbus *)self);

    //字段释放


}

// init fields function


void SuiDesigner$EventFileItemChanged_init_fields(SuiDesigner$EventFileItemChanged *self){
	//super class
    SuiDesigner$EventToEbus_init_fields((SuiDesigner$EventToEbus*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EventFileItemChanged_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$EventFileItemChanged*)self)->fileItem, NULL);
    }
	
}

// init function

void SuiDesigner$EventFileItemChanged_init(SuiDesigner$EventFileItemChanged *self, void *pOwner){
    Vtable_SuiDesigner$EventFileItemChanged_init(&_vtable_SuiDesigner$EventFileItemChanged);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EventFileItemChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EventFileItemChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EventFileItemChanged * SuiDesigner$EventFileItemChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EventFileItemChanged *self = calloc(1, sizeof(SuiDesigner$EventFileItemChanged));
	
    SuiDesigner$EventFileItemChanged_init(self, pOwner);
    return self;
}


// class members



