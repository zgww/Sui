
#include "SpotLight_orc.h" 

#include <stdio.h>
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Light_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$SpotLight _vtable_Sgl$SpotLight;

// init meta

void Sgl$SpotLight_initMeta(Vtable_Sgl$SpotLight *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "distance", OrcMetaType_float, offsetof(Sgl$SpotLight, distance), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "angle", OrcMetaType_float, offsetof(Sgl$SpotLight, angle), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_Sgl$SpotLight* Vtable_Sgl$SpotLight_init(Vtable_Sgl$SpotLight* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$SpotLight;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Light_init(&_vtable_Sgl$Light);

	// init by super vtable init function
    Vtable_Sgl$Light_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Light;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$SpotLight_new;
    ((Vtable_Object*)pvt)->className = "Sgl$SpotLight";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$SpotLight_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$SpotLight_fini(Sgl$SpotLight *self){
	//super fini
    Sgl$Light_fini((Sgl$Light *)self);

    //字段释放


}

// init fields function


void Sgl$SpotLight_init_fields(Sgl$SpotLight *self){
	//super class
    Sgl$Light_init_fields((Sgl$Light*)self);

    ((Object*)self)->fini = (void*)Sgl$SpotLight_fini;
	//fields
    {
	((Sgl$SpotLight*)self)->distance = 100;
	((Sgl$SpotLight*)self)->angle = Orc$PI / 3.0;
    }
	
}

// init function

void Sgl$SpotLight_init(Sgl$SpotLight *self, void *pOwner){
    Vtable_Sgl$SpotLight_init(&_vtable_Sgl$SpotLight);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$SpotLight;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$SpotLight_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$SpotLight * Sgl$SpotLight_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$SpotLight *self = calloc(1, sizeof(Sgl$SpotLight));
	
    Sgl$SpotLight_init(self, pOwner);
    return self;
}


// class members



