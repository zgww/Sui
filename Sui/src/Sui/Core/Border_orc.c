
#include "Border_orc.h" 

#include <stdio.h>
#include "./Edge_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$Border _vtable_SuiCore$Border;

// init meta

void SuiCore$Border_initMeta(Vtable_SuiCore$Border *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "t", ((Vtable_Object*)Vtable_SuiCore$Edge_init(0)), offsetof(SuiCore$Border, t), true, false, 1);
	orc_metaField_class(&pNext, "r", ((Vtable_Object*)Vtable_SuiCore$Edge_init(0)), offsetof(SuiCore$Border, r), true, false, 1);
	orc_metaField_class(&pNext, "b", ((Vtable_Object*)Vtable_SuiCore$Edge_init(0)), offsetof(SuiCore$Border, b), true, false, 1);
	orc_metaField_class(&pNext, "l", ((Vtable_Object*)Vtable_SuiCore$Edge_init(0)), offsetof(SuiCore$Border, l), true, false, 1);

	orc_metaField_method(&pNext, "isAllHasWidth", offsetof(SuiCore$Border, isAllHasWidth));
	orc_metaField_method(&pNext, "copyFrom", offsetof(SuiCore$Border, copyFrom));
	orc_metaField_method(&pNext, "setAll", offsetof(SuiCore$Border, setAll));
	orc_metaField_method(&pNext, "hor", offsetof(SuiCore$Border, hor));
	orc_metaField_method(&pNext, "ver", offsetof(SuiCore$Border, ver));
}


// vtable init


Vtable_SuiCore$Border* Vtable_SuiCore$Border_init(Vtable_SuiCore$Border* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Border;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Border_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Border";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Border_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$Border_fini(SuiCore$Border *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$Border*)self)->t);
	urgc_fini_field_class(self, (void**)&((SuiCore$Border*)self)->r);
	urgc_fini_field_class(self, (void**)&((SuiCore$Border*)self)->b);
	urgc_fini_field_class(self, (void**)&((SuiCore$Border*)self)->l);

}

// init fields function


void SuiCore$Border_init_fields(SuiCore$Border *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Border_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiCore$Edge*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$Border*)self)->t, SuiCore$Edge_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS SuiCore$Edge*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$Border*)self)->r, SuiCore$Edge_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS SuiCore$Edge*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$Border*)self)->b, SuiCore$Edge_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS SuiCore$Edge*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$Border*)self)->l, SuiCore$Edge_new(&tmpNewOwner_4) );
    }
	((SuiCore$Border*)self)->isAllHasWidth = (void*)SuiCore$Border$isAllHasWidth;
	((SuiCore$Border*)self)->copyFrom = (void*)SuiCore$Border$copyFrom;
	((SuiCore$Border*)self)->setAll = (void*)SuiCore$Border$setAll;
	((SuiCore$Border*)self)->hor = (void*)SuiCore$Border$hor;
	((SuiCore$Border*)self)->ver = (void*)SuiCore$Border$ver;
}

// init function

void SuiCore$Border_init(SuiCore$Border *self, void *pOwner){
    Vtable_SuiCore$Border_init(&_vtable_SuiCore$Border);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Border;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Border_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Border * SuiCore$Border_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Border *self = calloc(1, sizeof(SuiCore$Border));
	
    SuiCore$Border_init(self, pOwner);
    return self;
}


// class members
bool  SuiCore$Border$isAllHasWidth(SuiCore$Border *  self){
	return self->t->w > 0 && self->r->w > 0 && self->b->w > 0 && self->l->w > 0; 
}


void  SuiCore$Border$copyFrom(SuiCore$Border *  self, SuiCore$Border *  b){
	self->t->copyFrom(self->t, b->t) ;
	self->r->copyFrom(self->r, b->r) ;
	self->b->copyFrom(self->b, b->b) ;
	self->l->copyFrom(self->l, b->l) ;
}


void  SuiCore$Border$setAll(SuiCore$Border *  self, float  w, int  color){
	self->t->w = w;
	self->t->color = color;
	self->r->w = w;
	self->r->color = color;
	self->b->w = w;
	self->b->color = color;
	self->l->w = w;
	self->l->color = color;
}


float  SuiCore$Border$hor(SuiCore$Border *  self){
	return self->l->w + self->r->w; 
}


float  SuiCore$Border$ver(SuiCore$Border *  self){
	return self->t->w + self->b->w; 
}



SuiCore$Border*  SuiCore$mkBorder(SuiCore$Border **  __outRef__, float  w, int  color){
	URGC_VAR_CLEANUP_CLASS SuiCore$Border*  b = (b=NULL,urgc_init_var_class((void**)&b, SuiCore$Border_new(&b) ));
	b->setAll(b, w, color) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, b) ; 
}

void  SuiCore$testBorder(){
	URGC_VAR_CLEANUP_CLASS SuiCore$Border*  ent = SuiCore$mkBorder((ent = NULL,&ent), 10, 0xff0000ff) ;
	printf("testBorder\n") ;
}



