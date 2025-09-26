
#include "Map_orc.h" 

#include <stdio.h>
#include "./List_orc.h"
#include "./String_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Orc$Map _vtable_Orc$Map;

// init meta

void Orc$Map_initMeta(Vtable_Orc$Map *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_void, offsetof(Orc$Map, data), 0, 0, 1, 1);//void

	orc_metaField_method(&pNext, "put", offsetof(Orc$Map, put));
	orc_metaField_method(&pNext, "del", offsetof(Orc$Map, del));
	orc_metaField_method(&pNext, "has", offsetof(Orc$Map, has));
	orc_metaField_method(&pNext, "get", offsetof(Orc$Map, get));
	orc_metaField_method(&pNext, "clear", offsetof(Orc$Map, clear));
	orc_metaField_method(&pNext, "keys", offsetof(Orc$Map, keys));
	orc_metaField_method(&pNext, "size", offsetof(Orc$Map, size));
}


// vtable init


Vtable_Orc$Map* Vtable_Orc$Map_init(Vtable_Orc$Map* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$Map;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$Map_new;
    ((Vtable_Object*)pvt)->className = "Orc$Map";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$Map_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Orc$Map_fini(Orc$Map *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Orc$Map_init_fields(Orc$Map *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Orc$Map_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Orc$Map$ctor;
	((Object*)self)->dtor = (void*)Orc$Map$dtor;
	((Orc$Map*)self)->put = (void*)Orc$Map$put;
	((Orc$Map*)self)->del = (void*)Orc$Map$del;
	((Orc$Map*)self)->has = (void*)Orc$Map$has;
	((Orc$Map*)self)->get = (void*)Orc$Map$get;
	((Orc$Map*)self)->clear = (void*)Orc$Map$clear;
	((Orc$Map*)self)->keys = (void*)Orc$Map$keys;
	((Orc$Map*)self)->size = (void*)Orc$Map$size;
}

// init function

void Orc$Map_init(Orc$Map *self, void *pOwner){
    Vtable_Orc$Map_init(&_vtable_Orc$Map);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$Map;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$Map_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$Map * Orc$Map_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$Map *self = calloc(1, sizeof(Orc$Map));
	
    Orc$Map_init(self, pOwner);
    return self;
}


// class members
bool  Orc$Map$has(Orc$Map *  self, const char *  key){
	return self->get(self, key)  != NULL; 
}


void  Orc$Map$clear(Orc$Map *  self){
	URGC_VAR_CLEANUP_CLASS Orc$List*  keys = self->keys((keys = NULL,&keys), self) ;
	int  l = keys->size(keys) ;
	for (int  i = 0; i < l; i++) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  key = (key=NULL,urgc_init_var_class((void**)&key, (Orc$String* )keys->get(keys, i) ));
		self->del(self, key->str) ;
	}
}



void  Orc$Map_test(){
	URGC_VAR_CLEANUP_CLASS Orc$Map*  l = (l=NULL,urgc_init_var_class((void**)&l, Orc$Map_new(&l) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	l->put(l, "id", Orc$str(&tmpReturn_1, "id") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	l->put(l, "name", Orc$str(&tmpReturn_2, "zgwww") ) ;
	printf("new map:%p\n", l) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  id = (id=NULL,urgc_init_var_class((void**)&id, (Orc$String* )l->get(l, "id") ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  name = (name=NULL,urgc_init_var_class((void**)&name, (Orc$String* )l->get(l, "name") ));
	printf("id:%s %s\n", id->str, name->str) ;
}



