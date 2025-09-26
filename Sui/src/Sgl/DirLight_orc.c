
#include "DirLight_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Light_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$DirLight _vtable_Sgl$DirLight;

// init meta

void Sgl$DirLight_initMeta(Vtable_Sgl$DirLight *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "ambient", OrcMetaType_int, offsetof(Sgl$DirLight, ambient), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "diffuse", OrcMetaType_int, offsetof(Sgl$DirLight, diffuse), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "specular", OrcMetaType_int, offsetof(Sgl$DirLight, specular), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_Sgl$DirLight* Vtable_Sgl$DirLight_init(Vtable_Sgl$DirLight* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$DirLight;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Light_init(&_vtable_Sgl$Light);

	// init by super vtable init function
    Vtable_Sgl$Light_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Light;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$DirLight_new;
    ((Vtable_Object*)pvt)->className = "Sgl$DirLight";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$DirLight_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$DirLight_fini(Sgl$DirLight *self){
	//super fini
    Sgl$Light_fini((Sgl$Light *)self);

    //字段释放


}

// init fields function


void Sgl$DirLight_init_fields(Sgl$DirLight *self){
	//super class
    Sgl$Light_init_fields((Sgl$Light*)self);

    ((Object*)self)->fini = (void*)Sgl$DirLight_fini;
	//fields
    {
	((Sgl$DirLight*)self)->ambient = 0xff333333;
	((Sgl$DirLight*)self)->diffuse = 0xff999999;
	((Sgl$DirLight*)self)->specular = 0xffffffff;
    }
	
}

// init function

void Sgl$DirLight_init(Sgl$DirLight *self, void *pOwner){
    Vtable_Sgl$DirLight_init(&_vtable_Sgl$DirLight);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$DirLight;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$DirLight_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$DirLight * Sgl$DirLight_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$DirLight *self = calloc(1, sizeof(Sgl$DirLight));
	
    Sgl$DirLight_init(self, pOwner);
    return self;
}


// class members



