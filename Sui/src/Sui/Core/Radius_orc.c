
#include "Radius_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$Radius _vtable_SuiCore$Radius;

// init meta

void SuiCore$Radius_initMeta(Vtable_SuiCore$Radius *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "tl", OrcMetaType_float, offsetof(SuiCore$Radius, tl), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "tr", OrcMetaType_float, offsetof(SuiCore$Radius, tr), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "bl", OrcMetaType_float, offsetof(SuiCore$Radius, bl), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "br", OrcMetaType_float, offsetof(SuiCore$Radius, br), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "setAll", offsetof(SuiCore$Radius, setAll));
}


// vtable init


Vtable_SuiCore$Radius* Vtable_SuiCore$Radius_init(Vtable_SuiCore$Radius* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Radius;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Radius_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Radius";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Radius_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$Radius_fini(SuiCore$Radius *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$Radius_init_fields(SuiCore$Radius *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Radius_fini;
	//fields
    {
	((SuiCore$Radius*)self)->tl = 0.f;
	((SuiCore$Radius*)self)->tr = 0.f;
	((SuiCore$Radius*)self)->bl = 0.f;
	((SuiCore$Radius*)self)->br = 0.f;
    }
	((Object*)self)->dtor = (void*)SuiCore$Radius$dtor;
	((SuiCore$Radius*)self)->setAll = (void*)SuiCore$Radius$setAll;
}

// init function

void SuiCore$Radius_init(SuiCore$Radius *self, void *pOwner){
    Vtable_SuiCore$Radius_init(&_vtable_SuiCore$Radius);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Radius;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Radius_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Radius * SuiCore$Radius_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Radius *self = calloc(1, sizeof(SuiCore$Radius));
	
    SuiCore$Radius_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$Radius$dtor(SuiCore$Radius *  self){
	printf("释放Radius:%f,%f,%f,%f\n", self->tl, self->tr, self->bl, self->br) ;
}


void  SuiCore$Radius$setAll(SuiCore$Radius *  self, float  r){
	self->tl = r;
	self->tr = r;
	self->bl = r;
	self->br = r;
}



void  SuiCore$testRadius(){
	URGC_VAR_CLEANUP_CLASS SuiCore$Radius*  a = (a=NULL,urgc_init_var_class((void**)&a, SuiCore$Radius_new(&a) ));
	a->setAll(a, 10.0f) ;
	printf("Radius: %f,%f,%f,%f\n", a->tl, a->tr, a->bl, a->br) ;
}



