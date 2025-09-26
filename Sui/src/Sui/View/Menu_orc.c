
#include "Menu_orc.h" 

#include "../Core/ViewBase_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiView$Menu _vtable_SuiView$Menu;

// init meta

void SuiView$Menu_initMeta(Vtable_SuiView$Menu *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiView$Menu* Vtable_SuiView$Menu_init(Vtable_SuiView$Menu* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Menu;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$ViewBase_init(&_vtable_SuiCore$ViewBase);

	// init by super vtable init function
    Vtable_SuiCore$ViewBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$ViewBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Menu_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Menu";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Menu_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Menu_fini(SuiView$Menu *self){
	//super fini
    SuiCore$ViewBase_fini((SuiCore$ViewBase *)self);

    //字段释放


}

// init fields function


void SuiView$Menu_init_fields(SuiView$Menu *self){
	//super class
    SuiCore$ViewBase_init_fields((SuiCore$ViewBase*)self);

    ((Object*)self)->fini = (void*)SuiView$Menu_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiView$Menu_init(SuiView$Menu *self, void *pOwner){
    Vtable_SuiView$Menu_init(&_vtable_SuiView$Menu);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Menu;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Menu_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Menu * SuiView$Menu_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Menu *self = calloc(1, sizeof(SuiView$Menu));
	
    SuiView$Menu_init(self, pOwner);
    return self;
}


// class members



