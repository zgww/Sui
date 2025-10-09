
#include "GeometryCone_orc.h" 

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"
#include "./GeometryCylinder_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeometryCone _vtable_Sgl$GeometryCone;

// init meta

void Sgl$GeometryCone_initMeta(Vtable_Sgl$GeometryCone *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_Sgl$GeometryCone* Vtable_Sgl$GeometryCone_init(Vtable_Sgl$GeometryCone* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryCone;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$GeometryCylinder_init(&_vtable_Sgl$GeometryCylinder);

	// init by super vtable init function
    Vtable_Sgl$GeometryCylinder_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$GeometryCylinder;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryCone_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryCone";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryCone_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryCone_fini(Sgl$GeometryCone *self){
	//super fini
    Sgl$GeometryCylinder_fini((Sgl$GeometryCylinder *)self);

    //字段释放
	

}

// init fields function


void Sgl$GeometryCone_init_fields(Sgl$GeometryCone *self){
	//super class
    Sgl$GeometryCylinder_init_fields((Sgl$GeometryCylinder*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryCone_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Sgl$GeometryCone$ctor;
}

// init function

void Sgl$GeometryCone_init(Sgl$GeometryCone *self, void *pOwner){
    Vtable_Sgl$GeometryCone_init(&_vtable_Sgl$GeometryCone);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryCone;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryCone_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryCone * Sgl$GeometryCone_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryCone *self = calloc(1, sizeof(Sgl$GeometryCone));
	
    Sgl$GeometryCone_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryCone$ctor(Sgl$GeometryCone *  self){
	((Sgl$GeometryCylinder * )self)->radiusTop = 0;
}





