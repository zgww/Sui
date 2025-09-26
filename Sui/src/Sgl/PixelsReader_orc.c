
#include "PixelsReader_orc.h" 

#include <stdio.h>
#include "./UnitOpengl.h"
#include "./Buffer_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$DepthFloatPixlesReader _vtable_Sgl$DepthFloatPixlesReader;

// init meta

void Sgl$DepthFloatPixlesReader_initMeta(Vtable_Sgl$DepthFloatPixlesReader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "buffer", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$DepthFloatPixlesReader, buffer), true, false, 1);
	orc_metaField_primitive(&pNext, "x", OrcMetaType_int, offsetof(Sgl$DepthFloatPixlesReader, x), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "y", OrcMetaType_int, offsetof(Sgl$DepthFloatPixlesReader, y), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "w", OrcMetaType_int, offsetof(Sgl$DepthFloatPixlesReader, w), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "h", OrcMetaType_int, offsetof(Sgl$DepthFloatPixlesReader, h), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "read", offsetof(Sgl$DepthFloatPixlesReader, read));
}


// vtable init


Vtable_Sgl$DepthFloatPixlesReader* Vtable_Sgl$DepthFloatPixlesReader_init(Vtable_Sgl$DepthFloatPixlesReader* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$DepthFloatPixlesReader;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$DepthFloatPixlesReader_new;
    ((Vtable_Object*)pvt)->className = "Sgl$DepthFloatPixlesReader";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$DepthFloatPixlesReader_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$DepthFloatPixlesReader_fini(Sgl$DepthFloatPixlesReader *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$DepthFloatPixlesReader_init_fields(Sgl$DepthFloatPixlesReader *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$DepthFloatPixlesReader_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$DepthFloatPixlesReader*)self)->buffer, Sgl$Buffer_new(&tmpNewOwner_1) );
	((Sgl$DepthFloatPixlesReader*)self)->x = 0;
	((Sgl$DepthFloatPixlesReader*)self)->y = 0;
	((Sgl$DepthFloatPixlesReader*)self)->w = 0;
	((Sgl$DepthFloatPixlesReader*)self)->h = 0;
    }
	((Sgl$DepthFloatPixlesReader*)self)->read = (void*)Sgl$DepthFloatPixlesReader$read;
}

// init function

void Sgl$DepthFloatPixlesReader_init(Sgl$DepthFloatPixlesReader *self, void *pOwner){
    Vtable_Sgl$DepthFloatPixlesReader_init(&_vtable_Sgl$DepthFloatPixlesReader);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$DepthFloatPixlesReader;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$DepthFloatPixlesReader_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$DepthFloatPixlesReader * Sgl$DepthFloatPixlesReader_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$DepthFloatPixlesReader *self = calloc(1, sizeof(Sgl$DepthFloatPixlesReader));
	
    Sgl$DepthFloatPixlesReader_init(self, pOwner);
    return self;
}


// class members
float *  Sgl$DepthFloatPixlesReader$read(Sgl$DepthFloatPixlesReader *  self, int  x, int  y, int  w, int  h){
	Sgl$Buffer$initSize(self->buffer, w * h * 4) ;
	self->x = x;
	self->y = y;
	self->w = w;
	self->h = h;
	glReadPixels(x, y, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, self->buffer->data) ;
	return (float * )self->buffer->data; 
}





