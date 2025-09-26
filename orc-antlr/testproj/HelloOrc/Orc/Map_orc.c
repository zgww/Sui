
#include "Map_orc.h" 

#include <stdio.h>
#include "./List_orc.h"
#include "./String_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_OrcLang$Map _vtable_OrcLang$Map;

// init meta

void OrcLang$Map_initMeta(Vtable_OrcLang$Map *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "put", offsetof(OrcLang$Map, put));
	orc_metaField_method(&pNext, "del", offsetof(OrcLang$Map, del));
	orc_metaField_method(&pNext, "has", offsetof(OrcLang$Map, has));
	orc_metaField_method(&pNext, "get", offsetof(OrcLang$Map, get));
	orc_metaField_method(&pNext, "clear", offsetof(OrcLang$Map, clear));
	orc_metaField_method(&pNext, "keys", offsetof(OrcLang$Map, keys));
	orc_metaField_method(&pNext, "size", offsetof(OrcLang$Map, size));
}


// vtable init


Vtable_OrcLang$Map* Vtable_OrcLang$Map_init(Vtable_OrcLang$Map* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$Map;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$Map_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$Map";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$Map_initMeta;

    return pvt;
}


// fini function

void OrcLang$Map_fini(OrcLang$Map *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void OrcLang$Map_init_fields(OrcLang$Map *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)OrcLang$Map_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)OrcLang$Map$ctor;
	((Object*)self)->dtor = (void*)OrcLang$Map$dtor;
	((OrcLang$Map*)self)->put = (void*)OrcLang$Map$put;
	((OrcLang$Map*)self)->del = (void*)OrcLang$Map$del;
	((OrcLang$Map*)self)->has = (void*)OrcLang$Map$has;
	((OrcLang$Map*)self)->get = (void*)OrcLang$Map$get;
	((OrcLang$Map*)self)->clear = (void*)OrcLang$Map$clear;
	((OrcLang$Map*)self)->keys = (void*)OrcLang$Map$keys;
	((OrcLang$Map*)self)->size = (void*)OrcLang$Map$size;
}

// init function

void OrcLang$Map_init(OrcLang$Map *self){
    Vtable_OrcLang$Map_init(&_vtable_OrcLang$Map);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$Map;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$Map_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$Map * OrcLang$Map_new(){
    OrcLang$Map *self = calloc(1, sizeof(OrcLang$Map));
    OrcLang$Map_init(self);
    return self;
}


// class members
bool  OrcLang$Map$has(OrcLang$Map *  self, const char *  key){
	return self->get(self, key)  != NULL; 
}


void  OrcLang$Map$clear(OrcLang$Map *  self){
	URGC_VAR_CLEANUP OrcLang$List*  keys = self->keys((keys = NULL,&keys), self) ;
	int  l = keys->size(keys) ;
	for (int  i = 0; i < l; i++) {
		URGC_VAR_CLEANUP OrcLang$String*  key = urgc_init_var((void**)&key, keys->get(keys, i) );
		self->del(self, key->str) ;
	}
}



void  OrcLang$Map_test(){
	URGC_VAR_CLEANUP OrcLang$Map*  l = urgc_init_var((void**)&l, OrcLang$Map_new() );
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	l->put(l, "id", OrcLang$str(&tmpReturn_1, "id") ) ;
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_2 = NULL;
	l->put(l, "name", OrcLang$str(&tmpReturn_2, "zgwww") ) ;
	printf("new map:%p\n", l) ;
	URGC_VAR_CLEANUP OrcLang$String*  id = urgc_init_var((void**)&id, (OrcLang$String* )l->get(l, "id") );
	URGC_VAR_CLEANUP OrcLang$String*  name = urgc_init_var((void**)&name, (OrcLang$String* )l->get(l, "name") );
	printf("id:%s %s\n", id->str, name->str) ;
}



