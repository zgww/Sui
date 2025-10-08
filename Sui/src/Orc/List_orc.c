
#include "List_orc.h" 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./Math_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Orc$List _vtable_Orc$List;

// init meta

void Orc$List_initMeta(Vtable_Orc$List *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_void, offsetof(Orc$List, data), 0, 0, 1, 1);//void

	orc_metaField_method(&pNext, "add", offsetof(Orc$List, add));
	orc_metaField_method(&pNext, "swap", offsetof(Orc$List, swap));
	orc_metaField_method(&pNext, "resize", offsetof(Orc$List, resize));
	orc_metaField_method(&pNext, "set", offsetof(Orc$List, set));
	orc_metaField_method(&pNext, "addOnce", offsetof(Orc$List, addOnce));
	orc_metaField_method(&pNext, "remove", offsetof(Orc$List, remove));
	orc_metaField_method(&pNext, "removeAll", offsetof(Orc$List, removeAll));
	orc_metaField_method(&pNext, "span", offsetof(Orc$List, span));
	orc_metaField_method(&pNext, "has", offsetof(Orc$List, has));
	orc_metaField_method(&pNext, "indexOfFrom", offsetof(Orc$List, indexOfFrom));
	orc_metaField_method(&pNext, "indexOf", offsetof(Orc$List, indexOf));
	orc_metaField_method(&pNext, "insert", offsetof(Orc$List, insert));
	orc_metaField_method(&pNext, "_get", offsetof(Orc$List, _get));
	orc_metaField_method(&pNext, "get", offsetof(Orc$List, get));
	orc_metaField_method(&pNext, "size", offsetof(Orc$List, size));
	orc_metaField_method(&pNext, "at", offsetof(Orc$List, at));
	orc_metaField_method(&pNext, "removeAt", offsetof(Orc$List, removeAt));
	orc_metaField_method(&pNext, "first", offsetof(Orc$List, first));
	orc_metaField_method(&pNext, "last", offsetof(Orc$List, last));
	orc_metaField_method(&pNext, "clear", offsetof(Orc$List, clear));
	orc_metaField_method(&pNext, "removeRange", offsetof(Orc$List, removeRange));
	orc_metaField_method(&pNext, "removeFromStart", offsetof(Orc$List, removeFromStart));
	orc_metaField_method(&pNext, "copy", offsetof(Orc$List, copy));
	orc_metaField_method(&pNext, "push", offsetof(Orc$List, push));
	orc_metaField_method(&pNext, "pop", offsetof(Orc$List, pop));
}


// vtable init


Vtable_Orc$List* Vtable_Orc$List_init(Vtable_Orc$List* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$List;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$List_new;
    ((Vtable_Object*)pvt)->className = "Orc$List";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$List_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Orc$List_fini(Orc$List *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Orc$List_init_fields(Orc$List *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Orc$List_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Orc$List$ctor;
	((Object*)self)->dtor = (void*)Orc$List$dtor;
	((Orc$List*)self)->add = (void*)Orc$List$add;
	((Orc$List*)self)->swap = (void*)Orc$List$swap;
	((Orc$List*)self)->resize = (void*)Orc$List$resize;
	((Orc$List*)self)->set = (void*)Orc$List$set;
	((Orc$List*)self)->addOnce = (void*)Orc$List$addOnce;
	((Orc$List*)self)->remove = (void*)Orc$List$remove;
	((Orc$List*)self)->removeAll = (void*)Orc$List$removeAll;
	((Orc$List*)self)->span = (void*)Orc$List$span;
	((Orc$List*)self)->has = (void*)Orc$List$has;
	((Orc$List*)self)->indexOfFrom = (void*)Orc$List$indexOfFrom;
	((Orc$List*)self)->indexOf = (void*)Orc$List$indexOf;
	((Orc$List*)self)->insert = (void*)Orc$List$insert;
	((Orc$List*)self)->_get = (void*)Orc$List$_get;
	((Orc$List*)self)->get = (void*)Orc$List$get;
	((Orc$List*)self)->size = (void*)Orc$List$size;
	((Orc$List*)self)->at = (void*)Orc$List$at;
	((Orc$List*)self)->removeAt = (void*)Orc$List$removeAt;
	((Orc$List*)self)->first = (void*)Orc$List$first;
	((Orc$List*)self)->last = (void*)Orc$List$last;
	((Orc$List*)self)->clear = (void*)Orc$List$clear;
	((Orc$List*)self)->removeRange = (void*)Orc$List$removeRange;
	((Orc$List*)self)->removeFromStart = (void*)Orc$List$removeFromStart;
	((Orc$List*)self)->copy = (void*)Orc$List$copy;
	((Orc$List*)self)->push = (void*)Orc$List$push;
	((Orc$List*)self)->pop = (void*)Orc$List$pop;
}

// init function

void Orc$List_init(Orc$List *self, void *pOwner){
    Vtable_Orc$List_init(&_vtable_Orc$List);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$List;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$List_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$List * Orc$List_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$List *self = calloc(1, sizeof(Orc$List));
	
    Orc$List_init(self, pOwner);
    return self;
}


// class members
bool  Orc$List$addOnce(Orc$List *  self, Object *  obj){
	if (self->has(self, obj) ) {
		return false; 
	}
	self->add(self, obj) ;
	return true; 
}


bool  Orc$List$remove(Orc$List *  self, Object *  obj){
	int  idx = self->indexOf(self, obj) ;
	if (idx != -1) {
		self->removeAt(self, idx) ;
		return true; 
	}
	return false; 
}


int  Orc$List$removeAll(Orc$List *  self, Object *  obj){
	int  cnt = 0;
	int  start = 0;
	while (true) {
		int  idx = self->indexOfFrom(self, obj, start) ;
		if (idx != -1) {
			start = idx;
			cnt++;
			self->removeAt(self, idx) ;
		}
		else {
			break;
		}
	}
	return cnt; 
}


Orc$List*  Orc$List$span(Orc$List **  __outRef__, Orc$List *  self, int  fromIndex, int  toIndex){
	if (fromIndex > toIndex) {
		int  tmp = fromIndex;
		fromIndex = toIndex;
		toIndex = tmp;
	}
	if (fromIndex < 0) {
		fromIndex = 0;
	}
	if (toIndex >= self->size(self) ) {
		toIndex = self->size(self)  - 1;
	}
	URGC_VAR_CLEANUP_CLASS Orc$List*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$List_new(&ret) ));
	for (int  i = fromIndex; i <= toIndex; i++) {
		Object *  obj = self->get(self, i) ;
		ret->add(ret, obj) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


bool  Orc$List$has(Orc$List *  self, Object *  obj){
	int  idx = self->indexOf(self, obj) ;
	return idx != -1; 
}


int  Orc$List$indexOfFrom(Orc$List *  self, Object *  obj, int  start){
	int  size = self->size(self) ;
	for (int  i = start; i < size; i++) {
		Object *  cur = self->get(self, i) ;
		if (cur == obj) {
			return i; 
		}
	}
	return -1; 
}


Object *  Orc$List$get(Orc$List *  self, int  index){
	if (index >= 0 && index < self->size(self) ) {
		return self->_get(self, index) ; 
	}
	return NULL; 
}


Object *  Orc$List$at(Orc$List *  self, int  index){
	if (index >= 0 && index < self->size(self) ) {
		return self->_get(self, index) ; 
	}
	return NULL; 
}


Object *  Orc$List$first(Orc$List *  self){
	if (self->size(self)  <= 0) {
		return NULL; 
	}
	return self->get(self, 0) ; 
}


Object *  Orc$List$last(Orc$List *  self){
	if (self->size(self)  <= 0) {
		return NULL; 
	}
	return self->get(self, self->size(self)  - 1) ; 
}


void  Orc$List$clear(Orc$List *  self){
	for (int  i = self->size(self)  - 1; i >= 0; i--) {
		self->removeAt(self, i) ;
	}
}


void  Orc$List$removeRange(Orc$List *  self, int  start, int  end){
	for (int  i = start; i < end; i++) {
		self->removeAt(self, start) ;
	}
}


void  Orc$List$removeFromStart(Orc$List *  self, int  start){
	self->removeRange(self, start, self->size(self) ) ;
}


Orc$List*  Orc$List$copy(Orc$List **  __outRef__, Orc$List *  self){
	URGC_VAR_CLEANUP_CLASS Orc$List*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$List_new(&ret) ));
	for (int  i = 0; i < self->size(self) ; i++) {
		Object *  ele = self->get(self, i) ;
		ret->add(ret, ele) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


void  Orc$List$push(Orc$List *  self, Object *  obj){
	self->add(self, obj) ;
}


void  Orc$List$pop(Orc$List *  self){
	self->removeAt(self, self->size(self)  - 1) ;
}




//vtable instance
Vtable_Orc$PointerArray _vtable_Orc$PointerArray;

// init meta

void Orc$PointerArray_initMeta(Vtable_Orc$PointerArray *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_void, offsetof(Orc$PointerArray, data), 0, 0, 1, 2);//void
	orc_metaField_primitive(&pNext, "capacity", OrcMetaType_int, offsetof(Orc$PointerArray, capacity), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "length", OrcMetaType_int, offsetof(Orc$PointerArray, length), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "get", offsetof(Orc$PointerArray, get));
	orc_metaField_method(&pNext, "calcExpandNewCapacity", offsetof(Orc$PointerArray, calcExpandNewCapacity));
	orc_metaField_method(&pNext, "expand", offsetof(Orc$PointerArray, expand));
	orc_metaField_method(&pNext, "expandIfNeed", offsetof(Orc$PointerArray, expandIfNeed));
	orc_metaField_method(&pNext, "size", offsetof(Orc$PointerArray, size));
	orc_metaField_method(&pNext, "add", offsetof(Orc$PointerArray, add));
	orc_metaField_method(&pNext, "insert", offsetof(Orc$PointerArray, insert));
	orc_metaField_method(&pNext, "removeAt", offsetof(Orc$PointerArray, removeAt));
	orc_metaField_method(&pNext, "clear", offsetof(Orc$PointerArray, clear));
}


// vtable init


Vtable_Orc$PointerArray* Vtable_Orc$PointerArray_init(Vtable_Orc$PointerArray* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$PointerArray;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$PointerArray_new;
    ((Vtable_Object*)pvt)->className = "Orc$PointerArray";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$PointerArray_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Orc$PointerArray_fini(Orc$PointerArray *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Orc$PointerArray_init_fields(Orc$PointerArray *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Orc$PointerArray_fini;
	//fields
    {
	((Orc$PointerArray*)self)->capacity = 40;
	((Orc$PointerArray*)self)->length = 0;
    }
	((Object*)self)->ctor = (void*)Orc$PointerArray$ctor;
	((Orc$PointerArray*)self)->get = (void*)Orc$PointerArray$get;
	((Orc$PointerArray*)self)->calcExpandNewCapacity = (void*)Orc$PointerArray$calcExpandNewCapacity;
	((Orc$PointerArray*)self)->expand = (void*)Orc$PointerArray$expand;
	((Orc$PointerArray*)self)->expandIfNeed = (void*)Orc$PointerArray$expandIfNeed;
	((Object*)self)->dtor = (void*)Orc$PointerArray$dtor;
	((Orc$PointerArray*)self)->size = (void*)Orc$PointerArray$size;
	((Orc$PointerArray*)self)->add = (void*)Orc$PointerArray$add;
	((Orc$PointerArray*)self)->insert = (void*)Orc$PointerArray$insert;
	((Orc$PointerArray*)self)->removeAt = (void*)Orc$PointerArray$removeAt;
	((Orc$PointerArray*)self)->clear = (void*)Orc$PointerArray$clear;
}

// init function

void Orc$PointerArray_init(Orc$PointerArray *self, void *pOwner){
    Vtable_Orc$PointerArray_init(&_vtable_Orc$PointerArray);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$PointerArray;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$PointerArray_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$PointerArray * Orc$PointerArray_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$PointerArray *self = calloc(1, sizeof(Orc$PointerArray));
	
    Orc$PointerArray_init(self, pOwner);
    return self;
}


// class members
void  Orc$PointerArray$ctor(Orc$PointerArray *  self){
	self->data = calloc(self->capacity, Orc$_getPointerSize() ) ;
}


void *  Orc$PointerArray$get(Orc$PointerArray *  self, int  idx){
	if (idx < 0 || idx >= self->length) {
		return NULL; 
	}
	return self->data[idx]; 
}


int  Orc$PointerArray$calcExpandNewCapacity(Orc$PointerArray *  self, int  newCount){
	int  newCapacity = self->capacity + newCount;
	if (self->capacity < 1000) {
		return Orc$maxInt(newCapacity, self->capacity * 2) ; 
	}
	return Orc$maxInt(newCapacity, self->capacity + 1000) ; 
}


void  Orc$PointerArray$expand(Orc$PointerArray *  self, int  newCapacity){
	if (newCapacity > self->capacity) {
		self->capacity = newCapacity;
		self->data = realloc(self->data, self->capacity * Orc$_getPointerSize() ) ;
	}
}


void  Orc$PointerArray$expandIfNeed(Orc$PointerArray *  self, int  newCount){
	if (self->length + newCount > self->capacity) {
		int  newCapacity = self->calcExpandNewCapacity(self, newCount) ;
		self->expand(self, newCapacity) ;
	}
}


void  Orc$PointerArray$dtor(Orc$PointerArray *  self){
	if (self->data) {
		free(self->data) ;
		self->data = NULL;
	}
}


int  Orc$PointerArray$size(Orc$PointerArray *  self){
	return self->length; 
}


void  Orc$PointerArray$add(Orc$PointerArray *  self, void *  ptr){
	self->expandIfNeed(self, 1) ;
	self->data[self->length] = ptr;
	self->length = self->length + 1;
}


void  Orc$PointerArray$insert(Orc$PointerArray *  self, void *  ptr, int  i){
	if (i > self->length) {
		i = self->length;
	}
	if (i < 0) {
		i = 0;
	}
	self->expandIfNeed(self, 1) ;
	if (i < self->length) {
		memmove((void * )(self->data + i + 1), self->data + i, Orc$_getPointerSize()  * (self->length - i - 1)) ;
	}
	self->data[i] = ptr;
	self->length = self->length + 1;
}


void  Orc$PointerArray$removeAt(Orc$PointerArray *  self, int  i){
	if (i < 0) {
		return ; 
	}
	if (self->length > i) {
		memmove(self->data + i, self->data + i + 1, Orc$_getPointerSize()  * (self->length - i - 1)) ;
		self->length = self->length - 1;
	}
}


void  Orc$PointerArray$clear(Orc$PointerArray *  self){
	self->length = 0;
}



void  Orc$List_test(){
	URGC_VAR_CLEANUP_CLASS Orc$List*  l = (l=NULL,urgc_init_var_class((void**)&l, Orc$List_new(&l) ));
	printf("new list:%p, size:%d\n", l, l->size(l) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$PointerArray*  parr = (parr=NULL,urgc_init_var_class((void**)&parr, Orc$PointerArray_new(&parr) ));
	parr->add(parr, (void * )2) ;
	parr->add(parr, (void * )3) ;
	parr->add(parr, (void * )4) ;
	parr->insert(parr, (void * )1, 0) ;
	parr->removeAt(parr, 2) ;
	printf("你好parr size:%d p:%p\n", parr->size(parr) , parr) ;
}



