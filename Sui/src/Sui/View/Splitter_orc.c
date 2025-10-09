
#include "Splitter_orc.h" 

#include "../Core/ViewBase_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiView$Splitter _vtable_SuiView$Splitter;

// init meta

void SuiView$Splitter_initMeta(Vtable_SuiView$Splitter *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiView$Splitter* Vtable_SuiView$Splitter_init(Vtable_SuiView$Splitter* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Splitter;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$ViewBase_init(&_vtable_SuiCore$ViewBase);

	// init by super vtable init function
    Vtable_SuiCore$ViewBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$ViewBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Splitter_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Splitter";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Splitter_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Splitter_fini(SuiView$Splitter *self){
	//super fini
    SuiCore$ViewBase_fini((SuiCore$ViewBase *)self);

    //字段释放
	

}

// init fields function


void SuiView$Splitter_init_fields(SuiView$Splitter *self){
	//super class
    SuiCore$ViewBase_init_fields((SuiCore$ViewBase*)self);

    ((Object*)self)->fini = (void*)SuiView$Splitter_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiView$Splitter_init(SuiView$Splitter *self, void *pOwner){
    Vtable_SuiView$Splitter_init(&_vtable_SuiView$Splitter);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Splitter;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Splitter_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Splitter * SuiView$Splitter_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Splitter *self = calloc(1, sizeof(SuiView$Splitter));
	
    SuiView$Splitter_init(self, pOwner);
    return self;
}


// class members



