
#include "List_orc.h" 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./Math_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_OrcLang$List _vtable_OrcLang$List;

// init meta

void OrcLang$List_initMeta(Vtable_OrcLang$List *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "add", offsetof(OrcLang$List, add));
	orc_metaField_method(&pNext, "addOnce", offsetof(OrcLang$List, addOnce));
	orc_metaField_method(&pNext, "remove", offsetof(OrcLang$List, remove));
	orc_metaField_method(&pNext, "has", offsetof(OrcLang$List, has));
	orc_metaField_method(&pNext, "indexOf", offsetof(OrcLang$List, indexOf));
	orc_metaField_method(&pNext, "insert", offsetof(OrcLang$List, insert));
	orc_metaField_method(&pNext, "_get", offsetof(OrcLang$List, _get));
	orc_metaField_method(&pNext, "get", offsetof(OrcLang$List, get));
	orc_metaField_method(&pNext, "size", offsetof(OrcLang$List, size));
	orc_metaField_method(&pNext, "removeAt", offsetof(OrcLang$List, removeAt));
	orc_metaField_method(&pNext, "clear", offsetof(OrcLang$List, clear));
	orc_metaField_method(&pNext, "removeRange", offsetof(OrcLang$List, removeRange));
	orc_metaField_method(&pNext, "removeFromStart", offsetof(OrcLang$List, removeFromStart));
	orc_metaField_method(&pNext, "copy", offsetof(OrcLang$List, copy));
}


// vtable init


Vtable_OrcLang$List* Vtable_OrcLang$List_init(Vtable_OrcLang$List* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$List;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$List_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$List";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$List_initMeta;

    return pvt;
}


// fini function

void OrcLang$List_fini(OrcLang$List *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void OrcLang$List_init_fields(OrcLang$List *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)OrcLang$List_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)OrcLang$List$ctor;
	((Object*)self)->dtor = (void*)OrcLang$List$dtor;
	((OrcLang$List*)self)->add = (void*)OrcLang$List$add;
	((OrcLang$List*)self)->addOnce = (void*)OrcLang$List$addOnce;
	((OrcLang$List*)self)->remove = (void*)OrcLang$List$remove;
	((OrcLang$List*)self)->has = (void*)OrcLang$List$has;
	((OrcLang$List*)self)->indexOf = (void*)OrcLang$List$indexOf;
	((OrcLang$List*)self)->insert = (void*)OrcLang$List$insert;
	((OrcLang$List*)self)->_get = (void*)OrcLang$List$_get;
	((OrcLang$List*)self)->get = (void*)OrcLang$List$get;
	((OrcLang$List*)self)->size = (void*)OrcLang$List$size;
	((OrcLang$List*)self)->removeAt = (void*)OrcLang$List$removeAt;
	((OrcLang$List*)self)->clear = (void*)OrcLang$List$clear;
	((OrcLang$List*)self)->removeRange = (void*)OrcLang$List$removeRange;
	((OrcLang$List*)self)->removeFromStart = (void*)OrcLang$List$removeFromStart;
	((OrcLang$List*)self)->copy = (void*)OrcLang$List$copy;
}

// init function

void OrcLang$List_init(OrcLang$List *self){
    Vtable_OrcLang$List_init(&_vtable_OrcLang$List);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$List;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$List_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$List * OrcLang$List_new(){
    OrcLang$List *self = calloc(1, sizeof(OrcLang$List));
    OrcLang$List_init(self);
    return self;
}


// class members
bool  OrcLang$List$addOnce(OrcLang$List *  self, Object *  obj){
	if (self->has(self, obj) ) {
		return false; 
	}
	self->add(self, obj) ;
	return true; 
}


bool  OrcLang$List$remove(OrcLang$List *  self, Object *  obj){
	int  idx = self->indexOf(self, obj) ;
	if (idx != -1) {
		self->removeAt(self, idx) ;
		return true; 
	}
	return false; 
}


bool  OrcLang$List$has(OrcLang$List *  self, Object *  obj){
	int  idx = self->indexOf(self, obj) ;
	return idx != -1; 
}


Object *  OrcLang$List$get(OrcLang$List *  self, int  index){
	if (index >= 0 && index < self->size(self) ) {
		return self->_get(self, index) ; 
	}
	return NULL; 
}


void  OrcLang$List$clear(OrcLang$List *  self){
	for (int  i = self->size(self)  - 1; i >= 0; i--) {
		self->removeAt(self, i) ;
	}
}


void  OrcLang$List$removeRange(OrcLang$List *  self, int  start, int  end){
	for (int  i = start; i < end; i++) {
		self->removeAt(self, start) ;
	}
}


void  OrcLang$List$removeFromStart(OrcLang$List *  self, int  start){
	self->removeRange(self, start, self->size(self) ) ;
}


OrcLang$List*  OrcLang$List$copy(OrcLang$List **  __outRef__, OrcLang$List *  self){
	URGC_VAR_CLEANUP OrcLang$List*  ret = urgc_init_var((void**)&ret, OrcLang$List_new() );
	for (int  i = 0; i < self->size(self) ; i++) {
		Object *  ele = self->get(self, i) ;
		ret->add(ret, ele) ;
	}
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}




//vtable instance
Vtable_OrcLang$PointerArray _vtable_OrcLang$PointerArray;

// init meta

void OrcLang$PointerArray_initMeta(Vtable_OrcLang$PointerArray *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "capacity", OrcMetaType_int, offsetof(OrcLang$PointerArray, capacity), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "length", OrcMetaType_int, offsetof(OrcLang$PointerArray, length), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "calcExpandNewCapacity", offsetof(OrcLang$PointerArray, calcExpandNewCapacity));
	orc_metaField_method(&pNext, "expand", offsetof(OrcLang$PointerArray, expand));
	orc_metaField_method(&pNext, "expandIfNeed", offsetof(OrcLang$PointerArray, expandIfNeed));
	orc_metaField_method(&pNext, "size", offsetof(OrcLang$PointerArray, size));
	orc_metaField_method(&pNext, "add", offsetof(OrcLang$PointerArray, add));
	orc_metaField_method(&pNext, "insert", offsetof(OrcLang$PointerArray, insert));
	orc_metaField_method(&pNext, "removeAt", offsetof(OrcLang$PointerArray, removeAt));
}


// vtable init


Vtable_OrcLang$PointerArray* Vtable_OrcLang$PointerArray_init(Vtable_OrcLang$PointerArray* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$PointerArray;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$PointerArray_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$PointerArray";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$PointerArray_initMeta;

    return pvt;
}


// fini function

void OrcLang$PointerArray_fini(OrcLang$PointerArray *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void OrcLang$PointerArray_init_fields(OrcLang$PointerArray *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)OrcLang$PointerArray_fini;
	//fields
    {
	((OrcLang$PointerArray*)self)->capacity = 40;
	((OrcLang$PointerArray*)self)->length = 0;
    }
	((Object*)self)->ctor = (void*)OrcLang$PointerArray$ctor;
	((OrcLang$PointerArray*)self)->calcExpandNewCapacity = (void*)OrcLang$PointerArray$calcExpandNewCapacity;
	((OrcLang$PointerArray*)self)->expand = (void*)OrcLang$PointerArray$expand;
	((OrcLang$PointerArray*)self)->expandIfNeed = (void*)OrcLang$PointerArray$expandIfNeed;
	((Object*)self)->dtor = (void*)OrcLang$PointerArray$dtor;
	((OrcLang$PointerArray*)self)->size = (void*)OrcLang$PointerArray$size;
	((OrcLang$PointerArray*)self)->add = (void*)OrcLang$PointerArray$add;
	((OrcLang$PointerArray*)self)->insert = (void*)OrcLang$PointerArray$insert;
	((OrcLang$PointerArray*)self)->removeAt = (void*)OrcLang$PointerArray$removeAt;
}

// init function

void OrcLang$PointerArray_init(OrcLang$PointerArray *self){
    Vtable_OrcLang$PointerArray_init(&_vtable_OrcLang$PointerArray);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$PointerArray;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$PointerArray_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$PointerArray * OrcLang$PointerArray_new(){
    OrcLang$PointerArray *self = calloc(1, sizeof(OrcLang$PointerArray));
    OrcLang$PointerArray_init(self);
    return self;
}


// class members
void  OrcLang$PointerArray$ctor(OrcLang$PointerArray *  self){
	self->data = calloc(self->capacity, OrcLang$_getPointerSize() ) ;
}


int  OrcLang$PointerArray$calcExpandNewCapacity(OrcLang$PointerArray *  self, int  newCount){
	int  newCapacity = self->capacity + newCount;
	if (self->capacity < 1000) {
		return OrcLang$maxInt(newCapacity, self->capacity * 2) ; 
	}
	return OrcLang$maxInt(newCapacity, self->capacity + 1000) ; 
}


void  OrcLang$PointerArray$expand(OrcLang$PointerArray *  self, int  newCapacity){
	if (newCapacity > self->capacity) {
		self->capacity = newCapacity;
		self->data = realloc(self->data, self->capacity * OrcLang$_getPointerSize() ) ;
	}
}


void  OrcLang$PointerArray$expandIfNeed(OrcLang$PointerArray *  self, int  newCount){
	if (self->length + newCount > self->capacity) {
		int  newCapacity = self->calcExpandNewCapacity(self, newCount) ;
		self->expand(self, newCapacity) ;
	}
}


void  OrcLang$PointerArray$dtor(OrcLang$PointerArray *  self){
	if (self->data) {
		free(self->data) ;
		self->data = NULL;
	}
}


int  OrcLang$PointerArray$size(OrcLang$PointerArray *  self){
	return self->length; 
}


void  OrcLang$PointerArray$add(OrcLang$PointerArray *  self, void *  ptr){
	self->expandIfNeed(self, 1) ;
	self->data[self->length] = ptr;
	self->length = self->length + 1;
}


void  OrcLang$PointerArray$insert(OrcLang$PointerArray *  self, void *  ptr, int  i){
	if (i > self->length) {
		i = self->length;
	}
	if (i < 0) {
		i = 0;
	}
	self->expandIfNeed(self, 1) ;
	if (i < self->length) {
		memmove(self->data + i + 1, self->data + i, OrcLang$_getPointerSize()  * (self->length - i - 1)) ;
	}
	self->data[i] = ptr;
	self->length = self->length + 1;
}


void  OrcLang$PointerArray$removeAt(OrcLang$PointerArray *  self, int  i){
	if (i < 0) {
		return ; 
	}
	if (self->length > i) {
		memmove(self->data + i, self->data + i + 1, OrcLang$_getPointerSize()  * (self->length - i - 1)) ;
		self->length = self->length - 1;
	}
}



void  OrcLang$List_test(){
	URGC_VAR_CLEANUP OrcLang$List*  l = urgc_init_var((void**)&l, OrcLang$List_new() );
	printf("new list:%p, size:%d\n", l, l->size(l) ) ;
	URGC_VAR_CLEANUP OrcLang$PointerArray*  parr = urgc_init_var((void**)&parr, OrcLang$PointerArray_new() );
	parr->add(parr, (void * )2) ;
	parr->add(parr, (void * )3) ;
	parr->add(parr, (void * )4) ;
	parr->insert(parr, (void * )1, 0) ;
	parr->removeAt(parr, 2) ;
	printf("你好parr size:%d p:%p\n", parr->size(parr) , parr) ;
}



