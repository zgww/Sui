
#include "Edge_orc.h" 

#include <stdio.h>


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$Edge _vtable_SuiCore$Edge;

// init meta

void SuiCore$Edge_initMeta(Vtable_SuiCore$Edge *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "w", OrcMetaType_float, offsetof(SuiCore$Edge, w), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(SuiCore$Edge, color), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "copyFrom", offsetof(SuiCore$Edge, copyFrom));
	orc_metaField_method(&pNext, "set", offsetof(SuiCore$Edge, set));
}


// vtable init


Vtable_SuiCore$Edge* Vtable_SuiCore$Edge_init(Vtable_SuiCore$Edge* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Edge;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Edge_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Edge";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Edge_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$Edge_fini(SuiCore$Edge *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$Edge_init_fields(SuiCore$Edge *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Edge_fini;
	//fields
    {
	((SuiCore$Edge*)self)->w = 0.f;
	((SuiCore$Edge*)self)->color = 0x00000000;
    }
	((SuiCore$Edge*)self)->copyFrom = (void*)SuiCore$Edge$copyFrom;
	((SuiCore$Edge*)self)->set = (void*)SuiCore$Edge$set;
}

// init function

void SuiCore$Edge_init(SuiCore$Edge *self, void *pOwner){
    Vtable_SuiCore$Edge_init(&_vtable_SuiCore$Edge);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Edge;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Edge_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Edge * SuiCore$Edge_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Edge *self = calloc(1, sizeof(SuiCore$Edge));
	
    SuiCore$Edge_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$Edge$copyFrom(SuiCore$Edge *  self, SuiCore$Edge *  v){
	self->w = v->w;
	self->color = v->color;
}


void  SuiCore$Edge$set(SuiCore$Edge *  self, float  w, int  color){
	self->w = w;
	self->color = color;
}



void  SuiCore$testEdge(){
	URGC_VAR_CLEANUP_CLASS SuiCore$Edge*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiCore$Edge_new(&e) ));
	e->w = 12.f;
	e->color = 0x234;
	printf("edge:%f, %x\n", e->w, e->color) ;
}



