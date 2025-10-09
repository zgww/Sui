
#include "Light_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Material_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$Light _vtable_Sgl$Light;

// init meta

void Sgl$Light_initMeta(Vtable_Sgl$Light *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_Sgl$Light* Vtable_Sgl$Light_init(Vtable_Sgl$Light* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Light;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Light_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Light";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Light_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Light_fini(Sgl$Light *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	

}

// init fields function


void Sgl$Light_init_fields(Sgl$Light *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$Light_fini;
	//fields
    {
	
    }
	
}

// init function

void Sgl$Light_init(Sgl$Light *self, void *pOwner){
    Vtable_Sgl$Light_init(&_vtable_Sgl$Light);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Light;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Light_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Light * Sgl$Light_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Light *self = calloc(1, sizeof(Sgl$Light));
	
    Sgl$Light_init(self, pOwner);
    return self;
}


// class members



