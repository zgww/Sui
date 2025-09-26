
#include "PointLight_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Light_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$PointLight _vtable_Sgl$PointLight;

// init meta

void Sgl$PointLight_initMeta(Vtable_Sgl$PointLight *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(Sgl$PointLight, color), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "intensity", OrcMetaType_float, offsetof(Sgl$PointLight, intensity), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "distance", OrcMetaType_float, offsetof(Sgl$PointLight, distance), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "decay", OrcMetaType_float, offsetof(Sgl$PointLight, decay), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_Sgl$PointLight* Vtable_Sgl$PointLight_init(Vtable_Sgl$PointLight* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$PointLight;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Light_init(&_vtable_Sgl$Light);

	// init by super vtable init function
    Vtable_Sgl$Light_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Light;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$PointLight_new;
    ((Vtable_Object*)pvt)->className = "Sgl$PointLight";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$PointLight_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$PointLight_fini(Sgl$PointLight *self){
	//super fini
    Sgl$Light_fini((Sgl$Light *)self);

    //字段释放


}

// init fields function


void Sgl$PointLight_init_fields(Sgl$PointLight *self){
	//super class
    Sgl$Light_init_fields((Sgl$Light*)self);

    ((Object*)self)->fini = (void*)Sgl$PointLight_fini;
	//fields
    {
	((Sgl$PointLight*)self)->color = 0xffff0000;
	((Sgl$PointLight*)self)->distance = 300;
	((Sgl$PointLight*)self)->decay = 2;
    }
	
}

// init function

void Sgl$PointLight_init(Sgl$PointLight *self, void *pOwner){
    Vtable_Sgl$PointLight_init(&_vtable_Sgl$PointLight);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$PointLight;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$PointLight_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$PointLight * Sgl$PointLight_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$PointLight *self = calloc(1, sizeof(Sgl$PointLight));
	
    Sgl$PointLight_init(self, pOwner);
    return self;
}


// class members



