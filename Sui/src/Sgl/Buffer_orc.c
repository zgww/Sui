
#include "Buffer_orc.h" 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Quat_orc.h"
#include "../Json/Json_orc.h"
#include "./Mat_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$StructArrayBase _vtable_Sgl$StructArrayBase;

// init meta

void Sgl$StructArrayBase_initMeta(Vtable_Sgl$StructArrayBase *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "size", OrcMetaType_int, offsetof(Sgl$StructArrayBase, size), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "capacity", OrcMetaType_int, offsetof(Sgl$StructArrayBase, capacity), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "elementSize", OrcMetaType_int, offsetof(Sgl$StructArrayBase, elementSize), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "getPtrData", offsetof(Sgl$StructArrayBase, getPtrData));
	orc_metaField_method(&pNext, "getRaw", offsetof(Sgl$StructArrayBase, getRaw));
	orc_metaField_method(&pNext, "equalsRaw", offsetof(Sgl$StructArrayBase, equalsRaw));
	orc_metaField_method(&pNext, "distinct", offsetof(Sgl$StructArrayBase, distinct));
	orc_metaField_method(&pNext, "hasByRaw", offsetof(Sgl$StructArrayBase, hasByRaw));
	orc_metaField_method(&pNext, "getPtrRawAtElement", offsetof(Sgl$StructArrayBase, getPtrRawAtElement));
	orc_metaField_method(&pNext, "setRawAtElement", offsetof(Sgl$StructArrayBase, setRawAtElement));
	orc_metaField_method(&pNext, "setByPtr", offsetof(Sgl$StructArrayBase, setByPtr));
	orc_metaField_method(&pNext, "appendByCount", offsetof(Sgl$StructArrayBase, appendByCount));
	orc_metaField_method(&pNext, "clear", offsetof(Sgl$StructArrayBase, clear));
	orc_metaField_method(&pNext, "expandToSize", offsetof(Sgl$StructArrayBase, expandToSize));
	orc_metaField_method(&pNext, "expandIfNeed", offsetof(Sgl$StructArrayBase, expandIfNeed));
	orc_metaField_method(&pNext, "expandCapacity", offsetof(Sgl$StructArrayBase, expandCapacity));
}


// vtable init


Vtable_Sgl$StructArrayBase* Vtable_Sgl$StructArrayBase_init(Vtable_Sgl$StructArrayBase* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$StructArrayBase;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$StructArrayBase_new;
    ((Vtable_Object*)pvt)->className = "Sgl$StructArrayBase";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$StructArrayBase_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Sgl$StructArrayBase_fini(Sgl$StructArrayBase *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$StructArrayBase_init_fields(Sgl$StructArrayBase *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$StructArrayBase_fini;
	//fields
    {
	((Sgl$StructArrayBase*)self)->size = 0;
	((Sgl$StructArrayBase*)self)->capacity = 0;
	((Sgl$StructArrayBase*)self)->elementSize = 1;
    }
	((Sgl$StructArrayBase*)self)->getPtrData = (void*)Sgl$StructArrayBase$getPtrData;
	((Sgl$StructArrayBase*)self)->getRaw = (void*)Sgl$StructArrayBase$getRaw;
	((Sgl$StructArrayBase*)self)->equalsRaw = (void*)Sgl$StructArrayBase$equalsRaw;
	((Sgl$StructArrayBase*)self)->distinct = (void*)Sgl$StructArrayBase$distinct;
	((Sgl$StructArrayBase*)self)->hasByRaw = (void*)Sgl$StructArrayBase$hasByRaw;
	((Sgl$StructArrayBase*)self)->getPtrRawAtElement = (void*)Sgl$StructArrayBase$getPtrRawAtElement;
	((Sgl$StructArrayBase*)self)->setRawAtElement = (void*)Sgl$StructArrayBase$setRawAtElement;
	((Sgl$StructArrayBase*)self)->setByPtr = (void*)Sgl$StructArrayBase$setByPtr;
	((Sgl$StructArrayBase*)self)->appendByCount = (void*)Sgl$StructArrayBase$appendByCount;
	((Sgl$StructArrayBase*)self)->clear = (void*)Sgl$StructArrayBase$clear;
	((Sgl$StructArrayBase*)self)->expandToSize = (void*)Sgl$StructArrayBase$expandToSize;
	((Sgl$StructArrayBase*)self)->expandIfNeed = (void*)Sgl$StructArrayBase$expandIfNeed;
	((Sgl$StructArrayBase*)self)->expandCapacity = (void*)Sgl$StructArrayBase$expandCapacity;
}

// init function

void Sgl$StructArrayBase_init(Sgl$StructArrayBase *self, void *pOwner){
    Vtable_Sgl$StructArrayBase_init(&_vtable_Sgl$StructArrayBase);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$StructArrayBase;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$StructArrayBase_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$StructArrayBase * Sgl$StructArrayBase_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$StructArrayBase *self = calloc(1, sizeof(Sgl$StructArrayBase));
	
    Sgl$StructArrayBase_init(self, pOwner);
    return self;
}


// class members
void **  Sgl$StructArrayBase$getPtrData(Sgl$StructArrayBase *  self){
	return NULL; 
}


char *  Sgl$StructArrayBase$getRaw(Sgl$StructArrayBase *  self){
	return NULL; 
}


bool  Sgl$StructArrayBase$equalsRaw(Sgl$StructArrayBase *  self, char *  a, char *  b){
	for (int  j = 0; j < self->elementSize; j++) {
		if (b[j] != a[j]) {
			return false; 
		}
	}
	return true; 
}


void  Sgl$StructArrayBase$distinct(Sgl$StructArrayBase *  self){
	char *  raw = self->getRaw(self) ;
	for (int  i = 0; i < self->size; i++) {
		char *  ele = raw + (i * self->elementSize);
		for (int  j = self->size - 1; j >= i + 1; j++) {
			char *  b = raw + (i * self->elementSize);
			if (self->equalsRaw(self, ele, b) ) {
				memmove(b, b + self->elementSize, (self->size - 1 - j) * self->elementSize) ;
				self->size--;
			}
		}
	}
}


bool  Sgl$StructArrayBase$hasByRaw(Sgl$StructArrayBase *  self, char *  data){
	char *  raw = self->getRaw(self) ;
	for (int  i = 0; i < self->size; i++) {
		char *  ele = raw + (i * self->elementSize);
		bool  eq = true;
		for (int  j = 0; j < self->elementSize; j++) {
			if (ele[j] != data[j]) {
				eq = false;
				break;
			}
		}
		if (eq) {
			return true; 
		}
	}
	return false; 
}


char *  Sgl$StructArrayBase$getPtrRawAtElement(Sgl$StructArrayBase *  self, int  index){
	return self->getRaw(self)  + index * self->elementSize; 
}


void  Sgl$StructArrayBase$setRawAtElement(Sgl$StructArrayBase *  self, int  index, char *  data){
	char *  p = self->getRaw(self)  + index * self->elementSize;
	memcpy(p, data, self->elementSize) ;
}


void  Sgl$StructArrayBase$setByPtr(Sgl$StructArrayBase *  self, int  index, void *  data){
	char *  p = self->getRaw(self)  + index * self->elementSize;
	memcpy(p, data, self->elementSize) ;
}


void  Sgl$StructArrayBase$appendByCount(Sgl$StructArrayBase *  self, void *  data, int  count){
	self->expandIfNeed(self, count) ;
	memcpy(self->getRaw(self)  + self->size * self->elementSize, data, count * self->elementSize) ;
	self->size += count;
}


void  Sgl$StructArrayBase$clear(Sgl$StructArrayBase *  self){
	self->size = 0;
}


void  Sgl$StructArrayBase$expandToSize(Sgl$StructArrayBase *  self, int  toSize){
	if (self->size < toSize) {
		self->expandIfNeed(self, toSize - self->size) ;
		self->size = toSize;
	}
}


void  Sgl$StructArrayBase$expandIfNeed(Sgl$StructArrayBase *  self, int  addEleSize){
	int  newSize = self->size + addEleSize;
	if (newSize > self->capacity) {
		int  cap = Orc$maxInt(self->capacity * 2, 32) ;
		if (self->capacity < 1000 && cap >= newSize) {
			self->expandCapacity(self, cap) ;
		}
		else {
			int  exp = Orc$maxInt(addEleSize, 10240) ;
			int  toCap = self->size + exp;
			self->expandCapacity(self, toCap) ;
		}
	}
}


void  Sgl$StructArrayBase$expandCapacity(Sgl$StructArrayBase *  self, int  needSize){
	if (needSize > self->capacity) {
		self->capacity = needSize;
		void **  pp = self->getPtrData(self) ;
		if (*pp == NULL) {
			*pp = calloc(1, needSize * self->elementSize) ;
			return ; 
		}
		*pp = realloc(*pp, needSize * self->elementSize) ;
	}
}




//vtable instance
Vtable_Sgl$CharArray _vtable_Sgl$CharArray;

// init meta

void Sgl$CharArray_initMeta(Vtable_Sgl$CharArray *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_char, offsetof(Sgl$CharArray, data), 0, 0, 1, 1);//char

	orc_metaField_method(&pNext, "toString", offsetof(Sgl$CharArray, toString));
	orc_metaField_method(&pNext, "get", offsetof(Sgl$CharArray, get));
	orc_metaField_method(&pNext, "set", offsetof(Sgl$CharArray, set));
	orc_metaField_method(&pNext, "add", offsetof(Sgl$CharArray, add));
	orc_metaField_method(&pNext, "has", offsetof(Sgl$CharArray, has));
}


// vtable init


Vtable_Sgl$CharArray* Vtable_Sgl$CharArray_init(Vtable_Sgl$CharArray* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$CharArray;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$StructArrayBase_init(&_vtable_Sgl$StructArrayBase);

	// init by super vtable init function
    Vtable_Sgl$StructArrayBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$StructArrayBase;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$CharArray_new;
    ((Vtable_Object*)pvt)->className = "Sgl$CharArray";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$CharArray_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$CharArray_fini(Sgl$CharArray *self){
	//super fini
    Sgl$StructArrayBase_fini((Sgl$StructArrayBase *)self);

    //字段释放


}

// init fields function


void Sgl$CharArray_init_fields(Sgl$CharArray *self){
	//super class
    Sgl$StructArrayBase_init_fields((Sgl$StructArrayBase*)self);

    ((Object*)self)->fini = (void*)Sgl$CharArray_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Sgl$CharArray$ctor;
	((Sgl$CharArray*)self)->toString = (void*)Sgl$CharArray$toString;
	((Sgl$StructArrayBase*)self)->getPtrData = (void*)Sgl$CharArray$getPtrData;
	((Sgl$StructArrayBase*)self)->getRaw = (void*)Sgl$CharArray$getRaw;
	((Sgl$CharArray*)self)->get = (void*)Sgl$CharArray$get;
	((Sgl$CharArray*)self)->set = (void*)Sgl$CharArray$set;
	((Sgl$CharArray*)self)->add = (void*)Sgl$CharArray$add;
	((Sgl$CharArray*)self)->has = (void*)Sgl$CharArray$has;
}

// init function

void Sgl$CharArray_init(Sgl$CharArray *self, void *pOwner){
    Vtable_Sgl$CharArray_init(&_vtable_Sgl$CharArray);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$CharArray;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$CharArray_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$CharArray * Sgl$CharArray_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$CharArray *self = calloc(1, sizeof(Sgl$CharArray));
	
    Sgl$CharArray_init(self, pOwner);
    return self;
}


// class members
void  Sgl$CharArray$ctor(Sgl$CharArray *  self){
	((Sgl$StructArrayBase * )self)->elementSize = 1;
}


Orc$String*  Sgl$CharArray$toString(Orc$String **  __outRef__, Sgl$CharArray *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$str((ret = NULL,&ret), "") ;
	char *  tmp = self->data;
	int  l = ((Sgl$StructArrayBase * )self)->size;
	for (int  i = 0; i < l; i++) {
		Orc$String$add(Orc$String$addi(ret, tmp[i]) , " ") ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


void **  Sgl$CharArray$getPtrData(Sgl$CharArray *  self){
	return (void ** )(&self->data); 
}


char *  Sgl$CharArray$getRaw(Sgl$CharArray *  self){
	return (char * )self->data; 
}


char  Sgl$CharArray$get(Sgl$CharArray *  self, int  i){
	if (i >= ((Sgl$StructArrayBase * )self)->size) {
		return 0.0; 
	}
	return self->data[i]; 
}


bool  Sgl$CharArray$set(Sgl$CharArray *  self, int  i, char  v){
	if (i < ((Sgl$StructArrayBase * )self)->size) {
		self->data[i] = v;
		return true; 
	}
	return false; 
}


void  Sgl$CharArray$add(Sgl$CharArray *  self, char  v){
	((Sgl$StructArrayBase * )self)->expandIfNeed(self, 1) ;
	self->data[((Sgl$StructArrayBase * )self)->size] = v;
	((Sgl$StructArrayBase * )self)->size++;
}


bool  Sgl$CharArray$has(Sgl$CharArray *  self, char  v){
	return ((Sgl$StructArrayBase * )self)->hasByRaw(self, (char * )&v) ; 
}




//vtable instance
Vtable_Sgl$ShortArray _vtable_Sgl$ShortArray;

// init meta

void Sgl$ShortArray_initMeta(Vtable_Sgl$ShortArray *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_short, offsetof(Sgl$ShortArray, data), 0, 0, 1, 1);//short

	orc_metaField_method(&pNext, "get", offsetof(Sgl$ShortArray, get));
	orc_metaField_method(&pNext, "set", offsetof(Sgl$ShortArray, set));
	orc_metaField_method(&pNext, "add", offsetof(Sgl$ShortArray, add));
	orc_metaField_method(&pNext, "has", offsetof(Sgl$ShortArray, has));
}


// vtable init


Vtable_Sgl$ShortArray* Vtable_Sgl$ShortArray_init(Vtable_Sgl$ShortArray* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$ShortArray;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$StructArrayBase_init(&_vtable_Sgl$StructArrayBase);

	// init by super vtable init function
    Vtable_Sgl$StructArrayBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$StructArrayBase;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$ShortArray_new;
    ((Vtable_Object*)pvt)->className = "Sgl$ShortArray";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$ShortArray_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$ShortArray_fini(Sgl$ShortArray *self){
	//super fini
    Sgl$StructArrayBase_fini((Sgl$StructArrayBase *)self);

    //字段释放


}

// init fields function


void Sgl$ShortArray_init_fields(Sgl$ShortArray *self){
	//super class
    Sgl$StructArrayBase_init_fields((Sgl$StructArrayBase*)self);

    ((Object*)self)->fini = (void*)Sgl$ShortArray_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Sgl$ShortArray$ctor;
	((Sgl$StructArrayBase*)self)->getPtrData = (void*)Sgl$ShortArray$getPtrData;
	((Sgl$StructArrayBase*)self)->getRaw = (void*)Sgl$ShortArray$getRaw;
	((Sgl$ShortArray*)self)->get = (void*)Sgl$ShortArray$get;
	((Sgl$ShortArray*)self)->set = (void*)Sgl$ShortArray$set;
	((Sgl$ShortArray*)self)->add = (void*)Sgl$ShortArray$add;
	((Sgl$ShortArray*)self)->has = (void*)Sgl$ShortArray$has;
}

// init function

void Sgl$ShortArray_init(Sgl$ShortArray *self, void *pOwner){
    Vtable_Sgl$ShortArray_init(&_vtable_Sgl$ShortArray);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$ShortArray;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$ShortArray_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$ShortArray * Sgl$ShortArray_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$ShortArray *self = calloc(1, sizeof(Sgl$ShortArray));
	
    Sgl$ShortArray_init(self, pOwner);
    return self;
}


// class members
void  Sgl$ShortArray$ctor(Sgl$ShortArray *  self){
	((Sgl$StructArrayBase * )self)->elementSize = 2;
}


void **  Sgl$ShortArray$getPtrData(Sgl$ShortArray *  self){
	return (void ** )(&self->data); 
}


char *  Sgl$ShortArray$getRaw(Sgl$ShortArray *  self){
	return (char * )self->data; 
}


short  Sgl$ShortArray$get(Sgl$ShortArray *  self, int  i){
	if (i >= ((Sgl$StructArrayBase * )self)->size) {
		return 0.0; 
	}
	return self->data[i]; 
}


bool  Sgl$ShortArray$set(Sgl$ShortArray *  self, int  i, short  v){
	if (i < ((Sgl$StructArrayBase * )self)->size) {
		self->data[i] = v;
		return true; 
	}
	return false; 
}


void  Sgl$ShortArray$add(Sgl$ShortArray *  self, short  v){
	((Sgl$StructArrayBase * )self)->expandIfNeed(self, 1) ;
	self->data[((Sgl$StructArrayBase * )self)->size] = v;
	((Sgl$StructArrayBase * )self)->size++;
}


bool  Sgl$ShortArray$has(Sgl$ShortArray *  self, short  v){
	return ((Sgl$StructArrayBase * )self)->hasByRaw(self, (char * )&v) ; 
}




//vtable instance
Vtable_Sgl$FloatArray _vtable_Sgl$FloatArray;

// init meta

void Sgl$FloatArray_initMeta(Vtable_Sgl$FloatArray *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_float, offsetof(Sgl$FloatArray, data), 0, 0, 1, 1);//float

	orc_metaField_method(&pNext, "get", offsetof(Sgl$FloatArray, get));
	orc_metaField_method(&pNext, "set", offsetof(Sgl$FloatArray, set));
	orc_metaField_method(&pNext, "appendFloat3", offsetof(Sgl$FloatArray, appendFloat3));
	orc_metaField_method(&pNext, "add", offsetof(Sgl$FloatArray, add));
	orc_metaField_method(&pNext, "has", offsetof(Sgl$FloatArray, has));
}


// vtable init


Vtable_Sgl$FloatArray* Vtable_Sgl$FloatArray_init(Vtable_Sgl$FloatArray* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$FloatArray;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$StructArrayBase_init(&_vtable_Sgl$StructArrayBase);

	// init by super vtable init function
    Vtable_Sgl$StructArrayBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$StructArrayBase;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$FloatArray_new;
    ((Vtable_Object*)pvt)->className = "Sgl$FloatArray";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$FloatArray_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$FloatArray_fini(Sgl$FloatArray *self){
	//super fini
    Sgl$StructArrayBase_fini((Sgl$StructArrayBase *)self);

    //字段释放


}

// init fields function


void Sgl$FloatArray_init_fields(Sgl$FloatArray *self){
	//super class
    Sgl$StructArrayBase_init_fields((Sgl$StructArrayBase*)self);

    ((Object*)self)->fini = (void*)Sgl$FloatArray_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Sgl$FloatArray$ctor;
	((Sgl$StructArrayBase*)self)->getPtrData = (void*)Sgl$FloatArray$getPtrData;
	((Sgl$StructArrayBase*)self)->getRaw = (void*)Sgl$FloatArray$getRaw;
	((Sgl$FloatArray*)self)->get = (void*)Sgl$FloatArray$get;
	((Sgl$FloatArray*)self)->set = (void*)Sgl$FloatArray$set;
	((Sgl$FloatArray*)self)->appendFloat3 = (void*)Sgl$FloatArray$appendFloat3;
	((Sgl$FloatArray*)self)->add = (void*)Sgl$FloatArray$add;
	((Sgl$FloatArray*)self)->has = (void*)Sgl$FloatArray$has;
}

// init function

void Sgl$FloatArray_init(Sgl$FloatArray *self, void *pOwner){
    Vtable_Sgl$FloatArray_init(&_vtable_Sgl$FloatArray);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$FloatArray;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$FloatArray_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$FloatArray * Sgl$FloatArray_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$FloatArray *self = calloc(1, sizeof(Sgl$FloatArray));
	
    Sgl$FloatArray_init(self, pOwner);
    return self;
}


// class members
void  Sgl$FloatArray$ctor(Sgl$FloatArray *  self){
	((Sgl$StructArrayBase * )self)->elementSize = 4;
}


void **  Sgl$FloatArray$getPtrData(Sgl$FloatArray *  self){
	return (void ** )(&self->data); 
}


char *  Sgl$FloatArray$getRaw(Sgl$FloatArray *  self){
	return (char * )self->data; 
}


float  Sgl$FloatArray$get(Sgl$FloatArray *  self, int  i){
	if (i >= ((Sgl$StructArrayBase * )self)->size) {
		return 0.0; 
	}
	return self->data[i]; 
}


bool  Sgl$FloatArray$set(Sgl$FloatArray *  self, int  i, float  v){
	if (i < ((Sgl$StructArrayBase * )self)->size) {
		self->data[i] = v;
		return true; 
	}
	return false; 
}


void  Sgl$FloatArray$appendFloat3(Sgl$FloatArray *  self, float  a, float  b, float  c){
	self->add(self, a) ;
	self->add(self, b) ;
	self->add(self, c) ;
}


void  Sgl$FloatArray$add(Sgl$FloatArray *  self, float  v){
	((Sgl$StructArrayBase * )self)->expandIfNeed(self, 1) ;
	self->data[((Sgl$StructArrayBase * )self)->size] = v;
	((Sgl$StructArrayBase * )self)->size++;
}


bool  Sgl$FloatArray$has(Sgl$FloatArray *  self, float  v){
	return ((Sgl$StructArrayBase * )self)->hasByRaw(self, (char * )&v) ; 
}




//vtable instance
Vtable_Sgl$MatArray _vtable_Sgl$MatArray;

// init meta

void Sgl$MatArray_initMeta(Vtable_Sgl$MatArray *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "data", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$MatArray, data), false, true, 1);

	orc_metaField_method(&pNext, "get", offsetof(Sgl$MatArray, get));
	orc_metaField_method(&pNext, "set", offsetof(Sgl$MatArray, set));
	orc_metaField_method(&pNext, "add", offsetof(Sgl$MatArray, add));
	orc_metaField_method(&pNext, "has", offsetof(Sgl$MatArray, has));
}


// vtable init


Vtable_Sgl$MatArray* Vtable_Sgl$MatArray_init(Vtable_Sgl$MatArray* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$MatArray;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$StructArrayBase_init(&_vtable_Sgl$StructArrayBase);

	// init by super vtable init function
    Vtable_Sgl$StructArrayBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$StructArrayBase;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$MatArray_new;
    ((Vtable_Object*)pvt)->className = "Sgl$MatArray";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$MatArray_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$MatArray_fini(Sgl$MatArray *self){
	//super fini
    Sgl$StructArrayBase_fini((Sgl$StructArrayBase *)self);

    //字段释放


}

// init fields function


void Sgl$MatArray_init_fields(Sgl$MatArray *self){
	//super class
    Sgl$StructArrayBase_init_fields((Sgl$StructArrayBase*)self);

    ((Object*)self)->fini = (void*)Sgl$MatArray_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Sgl$MatArray$ctor;
	((Sgl$StructArrayBase*)self)->getPtrData = (void*)Sgl$MatArray$getPtrData;
	((Sgl$StructArrayBase*)self)->getRaw = (void*)Sgl$MatArray$getRaw;
	((Sgl$MatArray*)self)->get = (void*)Sgl$MatArray$get;
	((Sgl$MatArray*)self)->set = (void*)Sgl$MatArray$set;
	((Sgl$MatArray*)self)->add = (void*)Sgl$MatArray$add;
	((Sgl$MatArray*)self)->has = (void*)Sgl$MatArray$has;
}

// init function

void Sgl$MatArray_init(Sgl$MatArray *self, void *pOwner){
    Vtable_Sgl$MatArray_init(&_vtable_Sgl$MatArray);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$MatArray;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$MatArray_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$MatArray * Sgl$MatArray_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$MatArray *self = calloc(1, sizeof(Sgl$MatArray));
	
    Sgl$MatArray_init(self, pOwner);
    return self;
}


// class members
void  Sgl$MatArray$ctor(Sgl$MatArray *  self){
	((Sgl$StructArrayBase * )self)->elementSize = sizeof(Sgl$Mat) ;
}


void **  Sgl$MatArray$getPtrData(Sgl$MatArray *  self){
	return (void ** )(&self->data); 
}


char *  Sgl$MatArray$getRaw(Sgl$MatArray *  self){
	return (char * )self->data; 
}


Sgl$Mat Sgl$MatArray$get(Sgl$MatArray *  self, int  i){
	if (i >= ((Sgl$StructArrayBase * )self)->size) {
		Sgl$Mat m;
		Sgl$Mat$identity(&m) ;
		return m; 
	}
	return self->data[i]; 
}


bool  Sgl$MatArray$set(Sgl$MatArray *  self, int  i, Sgl$Mat v){
	if (i >= ((Sgl$StructArrayBase * )self)->size) {
		((Sgl$StructArrayBase * )self)->expandToSize(self, i + 1) ;
	}
	if (i < ((Sgl$StructArrayBase * )self)->size) {
		self->data[i] = v;
		return true; 
	}
	return false; 
}


void  Sgl$MatArray$add(Sgl$MatArray *  self, Sgl$Mat v){
	((Sgl$StructArrayBase * )self)->expandIfNeed(self, 1) ;
	self->data[((Sgl$StructArrayBase * )self)->size] = v;
	((Sgl$StructArrayBase * )self)->size++;
}


bool  Sgl$MatArray$has(Sgl$MatArray *  self, Sgl$Mat v){
	return ((Sgl$StructArrayBase * )self)->hasByRaw(self, (char * )&v) ; 
}




//vtable instance
Vtable_Sgl$Vec4Array _vtable_Sgl$Vec4Array;

// init meta

void Sgl$Vec4Array_initMeta(Vtable_Sgl$Vec4Array *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "data", SuiCore$Vec4_getOrInitMetaStruct(), offsetof(Sgl$Vec4Array, data), false, true, 1);

	orc_metaField_method(&pNext, "get", offsetof(Sgl$Vec4Array, get));
	orc_metaField_method(&pNext, "set", offsetof(Sgl$Vec4Array, set));
	orc_metaField_method(&pNext, "add", offsetof(Sgl$Vec4Array, add));
	orc_metaField_method(&pNext, "has", offsetof(Sgl$Vec4Array, has));
}


// vtable init


Vtable_Sgl$Vec4Array* Vtable_Sgl$Vec4Array_init(Vtable_Sgl$Vec4Array* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Vec4Array;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$StructArrayBase_init(&_vtable_Sgl$StructArrayBase);

	// init by super vtable init function
    Vtable_Sgl$StructArrayBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$StructArrayBase;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Vec4Array_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Vec4Array";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Vec4Array_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Vec4Array_fini(Sgl$Vec4Array *self){
	//super fini
    Sgl$StructArrayBase_fini((Sgl$StructArrayBase *)self);

    //字段释放


}

// init fields function


void Sgl$Vec4Array_init_fields(Sgl$Vec4Array *self){
	//super class
    Sgl$StructArrayBase_init_fields((Sgl$StructArrayBase*)self);

    ((Object*)self)->fini = (void*)Sgl$Vec4Array_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Sgl$Vec4Array$ctor;
	((Sgl$StructArrayBase*)self)->getPtrData = (void*)Sgl$Vec4Array$getPtrData;
	((Sgl$StructArrayBase*)self)->getRaw = (void*)Sgl$Vec4Array$getRaw;
	((Sgl$Vec4Array*)self)->get = (void*)Sgl$Vec4Array$get;
	((Sgl$Vec4Array*)self)->set = (void*)Sgl$Vec4Array$set;
	((Sgl$Vec4Array*)self)->add = (void*)Sgl$Vec4Array$add;
	((Sgl$Vec4Array*)self)->has = (void*)Sgl$Vec4Array$has;
}

// init function

void Sgl$Vec4Array_init(Sgl$Vec4Array *self, void *pOwner){
    Vtable_Sgl$Vec4Array_init(&_vtable_Sgl$Vec4Array);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Vec4Array;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Vec4Array_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Vec4Array * Sgl$Vec4Array_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Vec4Array *self = calloc(1, sizeof(Sgl$Vec4Array));
	
    Sgl$Vec4Array_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Vec4Array$ctor(Sgl$Vec4Array *  self){
	((Sgl$StructArrayBase * )self)->elementSize = sizeof(SuiCore$Vec4) ;
}


void **  Sgl$Vec4Array$getPtrData(Sgl$Vec4Array *  self){
	return (void ** )(&self->data); 
}


char *  Sgl$Vec4Array$getRaw(Sgl$Vec4Array *  self){
	return (char * )self->data; 
}


SuiCore$Vec4 Sgl$Vec4Array$get(Sgl$Vec4Array *  self, int  i){
	if (i >= ((Sgl$StructArrayBase * )self)->size) {
		return SuiCore$mkVec4(0, 0, 0, 0) ; 
	}
	return self->data[i]; 
}


bool  Sgl$Vec4Array$set(Sgl$Vec4Array *  self, int  i, SuiCore$Vec4 v){
	if (i < ((Sgl$StructArrayBase * )self)->size) {
		self->data[i] = v;
		return true; 
	}
	return false; 
}


void  Sgl$Vec4Array$add(Sgl$Vec4Array *  self, SuiCore$Vec4 v){
	((Sgl$StructArrayBase * )self)->expandIfNeed(self, 1) ;
	self->data[((Sgl$StructArrayBase * )self)->size] = v;
	((Sgl$StructArrayBase * )self)->size++;
}


bool  Sgl$Vec4Array$has(Sgl$Vec4Array *  self, SuiCore$Vec4 v){
	return ((Sgl$StructArrayBase * )self)->hasByRaw(self, (char * )&v) ; 
}




//vtable instance
Vtable_Sgl$Vec3Array _vtable_Sgl$Vec3Array;

// init meta

void Sgl$Vec3Array_initMeta(Vtable_Sgl$Vec3Array *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "data", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Vec3Array, data), false, true, 1);

	orc_metaField_method(&pNext, "toString", offsetof(Sgl$Vec3Array, toString));
	orc_metaField_method(&pNext, "get", offsetof(Sgl$Vec3Array, get));
	orc_metaField_method(&pNext, "set", offsetof(Sgl$Vec3Array, set));
	orc_metaField_method(&pNext, "add", offsetof(Sgl$Vec3Array, add));
	orc_metaField_method(&pNext, "has", offsetof(Sgl$Vec3Array, has));
}


// vtable init


Vtable_Sgl$Vec3Array* Vtable_Sgl$Vec3Array_init(Vtable_Sgl$Vec3Array* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Vec3Array;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$StructArrayBase_init(&_vtable_Sgl$StructArrayBase);

	// init by super vtable init function
    Vtable_Sgl$StructArrayBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$StructArrayBase;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Vec3Array_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Vec3Array";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Vec3Array_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Vec3Array_fini(Sgl$Vec3Array *self){
	//super fini
    Sgl$StructArrayBase_fini((Sgl$StructArrayBase *)self);

    //字段释放


}

// init fields function


void Sgl$Vec3Array_init_fields(Sgl$Vec3Array *self){
	//super class
    Sgl$StructArrayBase_init_fields((Sgl$StructArrayBase*)self);

    ((Object*)self)->fini = (void*)Sgl$Vec3Array_fini;
	//fields
    {
	
    }
	((Sgl$Vec3Array*)self)->toString = (void*)Sgl$Vec3Array$toString;
	((Object*)self)->ctor = (void*)Sgl$Vec3Array$ctor;
	((Sgl$StructArrayBase*)self)->getPtrData = (void*)Sgl$Vec3Array$getPtrData;
	((Sgl$StructArrayBase*)self)->getRaw = (void*)Sgl$Vec3Array$getRaw;
	((Sgl$Vec3Array*)self)->get = (void*)Sgl$Vec3Array$get;
	((Sgl$Vec3Array*)self)->set = (void*)Sgl$Vec3Array$set;
	((Sgl$Vec3Array*)self)->add = (void*)Sgl$Vec3Array$add;
	((Sgl$Vec3Array*)self)->has = (void*)Sgl$Vec3Array$has;
}

// init function

void Sgl$Vec3Array_init(Sgl$Vec3Array *self, void *pOwner){
    Vtable_Sgl$Vec3Array_init(&_vtable_Sgl$Vec3Array);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Vec3Array;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Vec3Array_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Vec3Array * Sgl$Vec3Array_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Vec3Array *self = calloc(1, sizeof(Sgl$Vec3Array));
	
    Sgl$Vec3Array_init(self, pOwner);
    return self;
}


// class members
Orc$String*  Sgl$Vec3Array$toString(Orc$String **  __outRef__, Sgl$Vec3Array *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = Orc$str((s = NULL,&s), "") ;
	for (int  i = 0; i < ((Sgl$StructArrayBase * )self)->size; i++) {
		SuiCore$Vec3 v = self->get(self, i) ;
		Orc$String$addf(s, v.x) ;
		Orc$String$add(s, ",") ;
		Orc$String$addf(s, v.y) ;
		Orc$String$add(s, ",") ;
		Orc$String$addf(s, v.z) ;
		Orc$String$add(s, "; ") ;
		if (i % 3 == 2) {
			Orc$String$add(s, "\n") ;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, s) ; 
}


void  Sgl$Vec3Array$ctor(Sgl$Vec3Array *  self){
	((Sgl$StructArrayBase * )self)->elementSize = sizeof(SuiCore$Vec3) ;
}


void **  Sgl$Vec3Array$getPtrData(Sgl$Vec3Array *  self){
	return (void ** )(&self->data); 
}


char *  Sgl$Vec3Array$getRaw(Sgl$Vec3Array *  self){
	return (char * )self->data; 
}


SuiCore$Vec3 Sgl$Vec3Array$get(Sgl$Vec3Array *  self, int  i){
	if (i >= ((Sgl$StructArrayBase * )self)->size) {
		return SuiCore$mkVec3(0, 0, 0) ; 
	}
	return self->data[i]; 
}


bool  Sgl$Vec3Array$set(Sgl$Vec3Array *  self, int  i, SuiCore$Vec3 v){
	if (i < ((Sgl$StructArrayBase * )self)->size) {
		self->data[i] = v;
		return true; 
	}
	return false; 
}


void  Sgl$Vec3Array$add(Sgl$Vec3Array *  self, SuiCore$Vec3 v){
	((Sgl$StructArrayBase * )self)->expandIfNeed(self, 1) ;
	self->data[((Sgl$StructArrayBase * )self)->size] = v;
	((Sgl$StructArrayBase * )self)->size++;
}


bool  Sgl$Vec3Array$has(Sgl$Vec3Array *  self, SuiCore$Vec3 v){
	return ((Sgl$StructArrayBase * )self)->hasByRaw(self, (char * )&v) ; 
}




//vtable instance
Vtable_Sgl$Vec2Array _vtable_Sgl$Vec2Array;

// init meta

void Sgl$Vec2Array_initMeta(Vtable_Sgl$Vec2Array *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "data", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(Sgl$Vec2Array, data), false, true, 1);

	orc_metaField_method(&pNext, "get", offsetof(Sgl$Vec2Array, get));
	orc_metaField_method(&pNext, "set", offsetof(Sgl$Vec2Array, set));
	orc_metaField_method(&pNext, "add", offsetof(Sgl$Vec2Array, add));
	orc_metaField_method(&pNext, "has", offsetof(Sgl$Vec2Array, has));
}


// vtable init


Vtable_Sgl$Vec2Array* Vtable_Sgl$Vec2Array_init(Vtable_Sgl$Vec2Array* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Vec2Array;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$StructArrayBase_init(&_vtable_Sgl$StructArrayBase);

	// init by super vtable init function
    Vtable_Sgl$StructArrayBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$StructArrayBase;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Vec2Array_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Vec2Array";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Vec2Array_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Vec2Array_fini(Sgl$Vec2Array *self){
	//super fini
    Sgl$StructArrayBase_fini((Sgl$StructArrayBase *)self);

    //字段释放


}

// init fields function


void Sgl$Vec2Array_init_fields(Sgl$Vec2Array *self){
	//super class
    Sgl$StructArrayBase_init_fields((Sgl$StructArrayBase*)self);

    ((Object*)self)->fini = (void*)Sgl$Vec2Array_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Sgl$Vec2Array$ctor;
	((Sgl$StructArrayBase*)self)->getPtrData = (void*)Sgl$Vec2Array$getPtrData;
	((Sgl$StructArrayBase*)self)->getRaw = (void*)Sgl$Vec2Array$getRaw;
	((Sgl$Vec2Array*)self)->get = (void*)Sgl$Vec2Array$get;
	((Sgl$Vec2Array*)self)->set = (void*)Sgl$Vec2Array$set;
	((Sgl$Vec2Array*)self)->add = (void*)Sgl$Vec2Array$add;
	((Sgl$Vec2Array*)self)->has = (void*)Sgl$Vec2Array$has;
}

// init function

void Sgl$Vec2Array_init(Sgl$Vec2Array *self, void *pOwner){
    Vtable_Sgl$Vec2Array_init(&_vtable_Sgl$Vec2Array);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Vec2Array;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Vec2Array_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Vec2Array * Sgl$Vec2Array_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Vec2Array *self = calloc(1, sizeof(Sgl$Vec2Array));
	
    Sgl$Vec2Array_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Vec2Array$ctor(Sgl$Vec2Array *  self){
	((Sgl$StructArrayBase * )self)->elementSize = sizeof(SuiCore$Vec2) ;
}


void **  Sgl$Vec2Array$getPtrData(Sgl$Vec2Array *  self){
	return (void ** )(&self->data); 
}


char *  Sgl$Vec2Array$getRaw(Sgl$Vec2Array *  self){
	return (char * )self->data; 
}


SuiCore$Vec2 Sgl$Vec2Array$get(Sgl$Vec2Array *  self, int  i){
	if (i >= ((Sgl$StructArrayBase * )self)->size) {
		return SuiCore$mkVec2(0, 0) ; 
	}
	return self->data[i]; 
}


bool  Sgl$Vec2Array$set(Sgl$Vec2Array *  self, int  i, SuiCore$Vec2 v){
	if (i < ((Sgl$StructArrayBase * )self)->size) {
		self->data[i] = v;
		return true; 
	}
	return false; 
}


void  Sgl$Vec2Array$add(Sgl$Vec2Array *  self, SuiCore$Vec2 v){
	((Sgl$StructArrayBase * )self)->expandIfNeed(self, 1) ;
	self->data[((Sgl$StructArrayBase * )self)->size] = v;
	((Sgl$StructArrayBase * )self)->size++;
}


bool  Sgl$Vec2Array$has(Sgl$Vec2Array *  self, SuiCore$Vec2 v){
	return ((Sgl$StructArrayBase * )self)->hasByRaw(self, (char * )&v) ; 
}




//vtable instance
Vtable_Sgl$IntArray _vtable_Sgl$IntArray;

// init meta

void Sgl$IntArray_initMeta(Vtable_Sgl$IntArray *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_int, offsetof(Sgl$IntArray, data), 0, 0, 1, 1);//int
	orc_metaField_primitive(&pNext, "size", OrcMetaType_int, offsetof(Sgl$IntArray, size), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "capacity", OrcMetaType_int, offsetof(Sgl$IntArray, capacity), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_Sgl$IntArray* Vtable_Sgl$IntArray_init(Vtable_Sgl$IntArray* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$IntArray;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$IntArray_new;
    ((Vtable_Object*)pvt)->className = "Sgl$IntArray";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$IntArray_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$IntArray_fini(Sgl$IntArray *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$IntArray_init_fields(Sgl$IntArray *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$IntArray_fini;
	//fields
    {
	((Sgl$IntArray*)self)->size = 0;
	((Sgl$IntArray*)self)->capacity = 0;
    }
	((Object*)self)->dtor = (void*)Sgl$IntArray$dtor;
}

// init function

void Sgl$IntArray_init(Sgl$IntArray *self, void *pOwner){
    Vtable_Sgl$IntArray_init(&_vtable_Sgl$IntArray);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$IntArray;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$IntArray_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$IntArray * Sgl$IntArray_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$IntArray *self = calloc(1, sizeof(Sgl$IntArray));
	
    Sgl$IntArray_init(self, pOwner);
    return self;
}


// class members
void  Sgl$IntArray$dtor(Sgl$IntArray *  self){
	if (self->data) {
		free(self->data) ;
		self->data = NULL;
	}
}



Orc$String*  Sgl$IntArray$toString(Orc$String **  __outRef__, Sgl$IntArray *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$str((ret = NULL,&ret), "") ;
	int *  tmp = (int * )self->data;
	int  l = self->size;
	for (int  i = 0; i < l; i++) {
		Orc$String$add(Orc$String$addi(ret, tmp[i]) , " ") ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

bool  Sgl$IntArray$removeFirst(Sgl$IntArray *  self, int  v){
	for (int  i = 0; i < self->size; i++) {
		int  cv = self->data[i];
		if (cv == v) {
			Sgl$IntArray$removeRange(self, i, i + 1) ;
			return true; 
		}
	}
	return false; 
}

bool  Sgl$IntArray$has(Sgl$IntArray *  self, int  v){
	for (int  i = 0; i < self->size; i++) {
		int  cv = self->data[i];
		if (cv == v) {
			return true; 
		}
	}
	return false; 
}

int  Sgl$IntArray$get(Sgl$IntArray *  self, int  idx){
	return Sgl$IntArray$at(self, idx) ; 
}

int  Sgl$IntArray$at(Sgl$IntArray *  self, int  idx){
	if (idx >= self->size) {
		return 0; 
	}
	return self->data[idx]; 
}

void  Sgl$IntArray$set(Sgl$IntArray *  self, int  idx, int  v){
	if (idx >= self->size) {
		Sgl$IntArray$appendValueByCount(self, 0, idx - self->size + 1) ;
	}
	self->data[idx] = v;
}

void  Sgl$IntArray$clear(Sgl$IntArray *  self){
	self->size = 0;
}

void  Sgl$IntArray$pop(Sgl$IntArray *  self, int  count){
	self->size = Orc$maxInt(self->size - count, 0) ;
}

void  Sgl$IntArray$initSize(Sgl$IntArray *  self, int  size){
	Sgl$IntArray$expandCapacity(self, size) ;
	self->size = size;
}

Sgl$IntArray *  Sgl$IntArray$appendByCount(Sgl$IntArray *  self, void *  data, int  cnt){
	Sgl$IntArray$expandIfNeed(self, cnt) ;
	memcpy(self->data + self->size, data, cnt * 4) ;
	self->size += cnt;
	return self; 
}

Sgl$IntArray *  Sgl$IntArray$appendValueByCount(Sgl$IntArray *  self, int  v, int  cnt){
	Sgl$IntArray$expandIfNeed(self, cnt) ;
	if (v != 0) {
		for (int  i = 0; i < cnt; i++) {
			self->data[self->size + i] = v;
		}
	}
	self->size += cnt;
	return self; 
}

Sgl$IntArray *  Sgl$IntArray$append(Sgl$IntArray *  self, int  v){
	Sgl$IntArray$expandIfNeed(self, 1) ;
	self->data[self->size] = v;
	self->size++;
	return self; 
}

bool  Sgl$IntArray$removeRange(Sgl$IntArray *  self, int  fromIndex, int  to){
	if (fromIndex < 0) {
		return false; 
	}
	if (to > self->size) {
		return false; 
	}
	int  cnt = to - fromIndex;
	if (cnt == self->size) {
		self->size = 0;
		return true; 
	}
	memmove(self->data + fromIndex, self->data + to, (self->size - to) * 4) ;
	self->size -= cnt;
	return true; 
}

void  Sgl$IntArray$expandIfNeed(Sgl$IntArray *  self, int  addIntSize){
	int  newSize = self->size + addIntSize;
	if (newSize > self->capacity) {
		int  cap = self->capacity * 2;
		if (self->capacity < 1000 && cap >= newSize) {
			Sgl$IntArray$expandCapacity(self, cap) ;
		}
		else {
			int  exp = Orc$maxInt(addIntSize, 10240) ;
			int  toCap = self->size + exp;
			Sgl$IntArray$expandCapacity(self, toCap) ;
		}
	}
}

void  Sgl$IntArray$expandCapacity(Sgl$IntArray *  self, int  needSize){
	if (needSize > self->capacity) {
		self->capacity = needSize;
		if (self->data == NULL) {
			self->data = calloc(1, needSize * 4) ;
			return ; 
		}
		self->data = realloc(self->data, needSize * 4) ;
	}
}

void  Sgl$IntArray$fromJson(Sgl$IntArray *  self, Json$Json *  ja){
	if (ja->isArray(ja) ) {
		Sgl$IntArray$clear(self) ;
		Sgl$IntArray$expandCapacity(self, ja->size(ja) ) ;
		int  l = ja->size(ja) ;
		for (int  i = 0; i < l; i++) {
			int  v = ja->atAsInt(ja, i) ;
			Sgl$IntArray$append(self, v) ;
		}
	}
}

Json$Json*  Sgl$IntArray$mkJson(Json$Json **  __outRef__, Sgl$IntArray *  self){
	URGC_VAR_CLEANUP_CLASS Json$Json*  ja = Json$Json_mkArray((ja = NULL,&ja)) ;
	for (int  i = 0; i < self->size; i++) {
		ja->addNumber(ja, self->data[i]) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ja) ; 
}


//vtable instance
Vtable_Sgl$Buffer _vtable_Sgl$Buffer;

// init meta

void Sgl$Buffer_initMeta(Vtable_Sgl$Buffer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_char, offsetof(Sgl$Buffer, data), 0, 0, 1, 1);//unsignedchar
	orc_metaField_primitive(&pNext, "size", OrcMetaType_int, offsetof(Sgl$Buffer, size), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "capacity", OrcMetaType_int, offsetof(Sgl$Buffer, capacity), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_Sgl$Buffer* Vtable_Sgl$Buffer_init(Vtable_Sgl$Buffer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Buffer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Buffer_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Buffer";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Buffer_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Buffer_fini(Sgl$Buffer *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$Buffer_init_fields(Sgl$Buffer *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Buffer_fini;
	//fields
    {
	((Sgl$Buffer*)self)->size = 0;
	((Sgl$Buffer*)self)->capacity = 0;
    }
	((Object*)self)->dtor = (void*)Sgl$Buffer$dtor;
}

// init function

void Sgl$Buffer_init(Sgl$Buffer *self, void *pOwner){
    Vtable_Sgl$Buffer_init(&_vtable_Sgl$Buffer);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Buffer;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Buffer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Buffer * Sgl$Buffer_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Buffer *self = calloc(1, sizeof(Sgl$Buffer));
	
    Sgl$Buffer_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Buffer$dtor(Sgl$Buffer *  self){
	if (self->data) {
		free(self->data) ;
		self->data = NULL;
	}
}



void  Sgl$Buffer$initSize(Sgl$Buffer *  self, int  size){
	Sgl$Buffer$expandCapacity(self, size) ;
	self->size = size;
}

Orc$String*  Sgl$Buffer$toFloatString(Orc$String **  __outRef__, Sgl$Buffer *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$str((ret = NULL,&ret), "") ;
	float *  tmp = (float * )self->data;
	int  l = Sgl$Buffer$floatSize(self) ;
	for (int  i = 0; i < l; i++) {
		Orc$String$add(Orc$String$addf(ret, tmp[i]) , " ") ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  Sgl$Buffer$toIntString(Orc$String **  __outRef__, Sgl$Buffer *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$str((ret = NULL,&ret), "") ;
	int *  tmp = (int * )self->data;
	int  l = Sgl$Buffer$intSize(self) ;
	for (int  i = 0; i < l; i++) {
		Orc$String$add(Orc$String$addi(ret, tmp[i]) , " ") ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

int  Sgl$Buffer$doubleSize(Sgl$Buffer *  self){
	return self->size / Orc$doubleSize() ; 
}

int  Sgl$Buffer$floatSize(Sgl$Buffer *  self){
	return self->size / Orc$floatSize() ; 
}

int  Sgl$Buffer$intSize(Sgl$Buffer *  self){
	return self->size / Orc$intSize() ; 
}

Sgl$Buffer *  Sgl$Buffer$appendBuffer(Sgl$Buffer *  self, Sgl$Buffer *  buf){
	if (buf->data) {
		Sgl$Buffer$append(self, buf->data, buf->size) ;
	}
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendChars(Sgl$Buffer *  self, char *  data, int  size){
	Sgl$Buffer$append(self, (unsigned char * )data, size) ;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$append(Sgl$Buffer *  self, unsigned char *  data, int  size){
	Sgl$Buffer$expandIfNeed(self, size) ;
	memcpy(self->data + self->size, data, size) ;
	self->size += size;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendFloat(Sgl$Buffer *  self, float  v){
	Sgl$Buffer$expandIfNeed(self, 4) ;
	float *  p = (float * )(self->data + self->size);
	*p = v;
	self->size += 4;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendFloat4(Sgl$Buffer *  self, float  a, float  b, float  c, float  d){
	Sgl$Buffer$expandIfNeed(self, 16) ;
	float *  p = (float * )(self->data + self->size);
	*p = a;
	*(p + 1) = b;
	*(p + 2) = c;
	*(p + 3) = d;
	self->size += 16;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendVec3(Sgl$Buffer *  self, SuiCore$Vec3 v3){
	Sgl$Buffer$expandIfNeed(self, 12) ;
	float *  p = (float * )(self->data + self->size);
	*p = v3.x;
	*(p + 1) = v3.y;
	*(p + 2) = v3.z;
	self->size += 12;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendFloat3(Sgl$Buffer *  self, float  a, float  b, float  c){
	Sgl$Buffer$expandIfNeed(self, 12) ;
	float *  p = (float * )(self->data + self->size);
	*p = a;
	*(p + 1) = b;
	*(p + 2) = c;
	self->size += 12;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendFloat2(Sgl$Buffer *  self, float  v, float  b){
	Sgl$Buffer$expandIfNeed(self, 8) ;
	float *  p = (float * )(self->data + self->size);
	*p = v;
	*(p + 1) = b;
	self->size += 8;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendFloats(Sgl$Buffer *  self, float *  data, int  floatCount){
	Sgl$Buffer$append(self, (unsigned char * )data, floatCount * 4) ;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendCstr(Sgl$Buffer *  self, char *  str){
	int  len = strlen(str) ;
	Sgl$Buffer$expandIfNeed(self, len + 1) ;
	memcpy(self->data + self->size, str, len + 1) ;
	self->size += len;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendInt(Sgl$Buffer *  self, int  v){
	Sgl$Buffer$expandIfNeed(self, 4) ;
	int *  p = (int * )(self->data + self->size);
	*p = v;
	self->size += 4;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendInt3(Sgl$Buffer *  self, int  a, int  b, int  c){
	Sgl$Buffer$expandIfNeed(self, 12) ;
	int *  p = (int * )(self->data + self->size);
	*p = a;
	*(p + 1) = b;
	*(p + 2) = c;
	self->size += 12;
	return self; 
}

Sgl$Buffer *  Sgl$Buffer$appendInts(Sgl$Buffer *  self, int *  data, int  intCount){
	Sgl$Buffer$append(self, (unsigned char * )data, intCount * 4) ;
	return self; 
}

void  Sgl$Buffer$clear(Sgl$Buffer *  self){
	self->size = 0;
}

void  Sgl$Buffer$pop(Sgl$Buffer *  self, int  count){
	self->size = Orc$maxInt(self->size - count, 0) ;
}

bool  Sgl$Buffer$removeRange(Sgl$Buffer *  self, int  fromIndex, int  to){
	if (fromIndex < 0) {
		return false; 
	}
	if (to > self->size) {
		return false; 
	}
	int  cnt = to - fromIndex;
	if (cnt == self->size) {
		self->size = 0;
		return true; 
	}
	memmove(self->data + fromIndex, self->data + to, self->size - to) ;
	self->size -= cnt;
	return true; 
}

void  Sgl$Buffer$expandIfNeed(Sgl$Buffer *  self, int  addByteSize){
	int  newSize = self->size + addByteSize;
	if (newSize > self->capacity) {
		int  cap = self->capacity * 2;
		if (cap < 10000 && cap >= newSize) {
			Sgl$Buffer$expandCapacity(self, cap) ;
		}
		else {
			Sgl$Buffer$expandCapacity(self, newSize) ;
		}
	}
}

void  Sgl$Buffer$expandCapacity(Sgl$Buffer *  self, int  needSize){
	self->capacity = needSize;
	if (self->data == NULL) {
		self->data = calloc(1, needSize) ;
		return ; 
	}
	self->data = realloc(self->data, needSize) ;
}


//vtable instance
Vtable_Sgl$BufferReader _vtable_Sgl$BufferReader;

// init meta

void Sgl$BufferReader_initMeta(Vtable_Sgl$BufferReader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "buffer", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$BufferReader, buffer), true, false, 1);
	orc_metaField_primitive(&pNext, "index", OrcMetaType_int, offsetof(Sgl$BufferReader, index), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "init", offsetof(Sgl$BufferReader, init));
	orc_metaField_method(&pNext, "remaining", offsetof(Sgl$BufferReader, remaining));
	orc_metaField_method(&pNext, "advance", offsetof(Sgl$BufferReader, advance));
	orc_metaField_method(&pNext, "readBinary", offsetof(Sgl$BufferReader, readBinary));
	orc_metaField_method(&pNext, "readString", offsetof(Sgl$BufferReader, readString));
	orc_metaField_method(&pNext, "readUint8", offsetof(Sgl$BufferReader, readUint8));
	orc_metaField_method(&pNext, "readChars", offsetof(Sgl$BufferReader, readChars));
	orc_metaField_method(&pNext, "readByte", offsetof(Sgl$BufferReader, readByte));
	orc_metaField_method(&pNext, "readInt16", offsetof(Sgl$BufferReader, readInt16));
	orc_metaField_method(&pNext, "readShort", offsetof(Sgl$BufferReader, readShort));
	orc_metaField_method(&pNext, "readInt", offsetof(Sgl$BufferReader, readInt));
	orc_metaField_method(&pNext, "readLongLong", offsetof(Sgl$BufferReader, readLongLong));
	orc_metaField_method(&pNext, "readCharArray", offsetof(Sgl$BufferReader, readCharArray));
	orc_metaField_method(&pNext, "readShortArray", offsetof(Sgl$BufferReader, readShortArray));
	orc_metaField_method(&pNext, "readIntArray", offsetof(Sgl$BufferReader, readIntArray));
	orc_metaField_method(&pNext, "readVec2Array", offsetof(Sgl$BufferReader, readVec2Array));
	orc_metaField_method(&pNext, "readVec4Array", offsetof(Sgl$BufferReader, readVec4Array));
	orc_metaField_method(&pNext, "readVec3Array", offsetof(Sgl$BufferReader, readVec3Array));
	orc_metaField_method(&pNext, "readVec3", offsetof(Sgl$BufferReader, readVec3));
	orc_metaField_method(&pNext, "readVec4", offsetof(Sgl$BufferReader, readVec4));
	orc_metaField_method(&pNext, "readQuat", offsetof(Sgl$BufferReader, readQuat));
	orc_metaField_method(&pNext, "readFloat", offsetof(Sgl$BufferReader, readFloat));
	orc_metaField_method(&pNext, "readDouble", offsetof(Sgl$BufferReader, readDouble));
}


// vtable init


Vtable_Sgl$BufferReader* Vtable_Sgl$BufferReader_init(Vtable_Sgl$BufferReader* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$BufferReader;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$BufferReader_new;
    ((Vtable_Object*)pvt)->className = "Sgl$BufferReader";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$BufferReader_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$BufferReader_fini(Sgl$BufferReader *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$BufferReader_init_fields(Sgl$BufferReader *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$BufferReader_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$BufferReader*)self)->buffer, NULL);
	((Sgl$BufferReader*)self)->index = 0;
    }
	((Sgl$BufferReader*)self)->init = (void*)Sgl$BufferReader$init;
	((Sgl$BufferReader*)self)->remaining = (void*)Sgl$BufferReader$remaining;
	((Sgl$BufferReader*)self)->advance = (void*)Sgl$BufferReader$advance;
	((Sgl$BufferReader*)self)->readBinary = (void*)Sgl$BufferReader$readBinary;
	((Sgl$BufferReader*)self)->readString = (void*)Sgl$BufferReader$readString;
	((Sgl$BufferReader*)self)->readUint8 = (void*)Sgl$BufferReader$readUint8;
	((Sgl$BufferReader*)self)->readChars = (void*)Sgl$BufferReader$readChars;
	((Sgl$BufferReader*)self)->readByte = (void*)Sgl$BufferReader$readByte;
	((Sgl$BufferReader*)self)->readInt16 = (void*)Sgl$BufferReader$readInt16;
	((Sgl$BufferReader*)self)->readShort = (void*)Sgl$BufferReader$readShort;
	((Sgl$BufferReader*)self)->readInt = (void*)Sgl$BufferReader$readInt;
	((Sgl$BufferReader*)self)->readLongLong = (void*)Sgl$BufferReader$readLongLong;
	((Sgl$BufferReader*)self)->readCharArray = (void*)Sgl$BufferReader$readCharArray;
	((Sgl$BufferReader*)self)->readShortArray = (void*)Sgl$BufferReader$readShortArray;
	((Sgl$BufferReader*)self)->readIntArray = (void*)Sgl$BufferReader$readIntArray;
	((Sgl$BufferReader*)self)->readVec2Array = (void*)Sgl$BufferReader$readVec2Array;
	((Sgl$BufferReader*)self)->readVec4Array = (void*)Sgl$BufferReader$readVec4Array;
	((Sgl$BufferReader*)self)->readVec3Array = (void*)Sgl$BufferReader$readVec3Array;
	((Sgl$BufferReader*)self)->readVec3 = (void*)Sgl$BufferReader$readVec3;
	((Sgl$BufferReader*)self)->readVec4 = (void*)Sgl$BufferReader$readVec4;
	((Sgl$BufferReader*)self)->readQuat = (void*)Sgl$BufferReader$readQuat;
	((Sgl$BufferReader*)self)->readFloat = (void*)Sgl$BufferReader$readFloat;
	((Sgl$BufferReader*)self)->readDouble = (void*)Sgl$BufferReader$readDouble;
}

// init function

void Sgl$BufferReader_init(Sgl$BufferReader *self, void *pOwner){
    Vtable_Sgl$BufferReader_init(&_vtable_Sgl$BufferReader);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$BufferReader;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$BufferReader_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$BufferReader * Sgl$BufferReader_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$BufferReader *self = calloc(1, sizeof(Sgl$BufferReader));
	
    Sgl$BufferReader_init(self, pOwner);
    return self;
}


// class members
Sgl$BufferReader *  Sgl$BufferReader$init(Sgl$BufferReader *  self, Sgl$Buffer *  buffer){
	urgc_set_field_class(self, (void * )offsetof(Sgl$BufferReader, buffer) , buffer) ;
	return self; 
}


int  Sgl$BufferReader$remaining(Sgl$BufferReader *  self){
	return self->buffer->size - self->index; 
}


void  Sgl$BufferReader$advance(Sgl$BufferReader *  self, int  byteLen){
	self->index += byteLen;
}


void  Sgl$BufferReader$readBinary(Sgl$BufferReader *  self, void *  p, int  byteLen){
	unsigned char *  pdata = self->buffer->data + self->index;
	memcpy(p, pdata, byteLen) ;
	self->index += byteLen;
}


Orc$String*  Sgl$BufferReader$readString(Orc$String **  __outRef__, Sgl$BufferReader *  self, int  byteLen){
	URGC_VAR_CLEANUP_CLASS Orc$String*  r = Orc$str((r = NULL,&r), "") ;
	unsigned char *  pdata = self->buffer->data + self->index;
	Orc$String$addBytesWithCount(r, (char * )pdata, byteLen) ;
	self->index += byteLen;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


unsigned char  Sgl$BufferReader$readUint8(Sgl$BufferReader *  self){
	unsigned char  c = self->buffer->data[self->index];
	self->index++;
	return c; 
}


void  Sgl$BufferReader$readChars(Sgl$BufferReader *  self, char *  dst, int  cnt, bool  setNullTail){
	memcpy(dst, self->buffer->data + self->index, cnt) ;
	if (setNullTail) {
		dst[cnt] = 0;
	}
	self->index += cnt;
}


unsigned char  Sgl$BufferReader$readByte(Sgl$BufferReader *  self){
	unsigned char  c = self->buffer->data[self->index];
	self->index++;
	return c; 
}


short  Sgl$BufferReader$readInt16(Sgl$BufferReader *  self){
	short *  p = (short * )(self->buffer->data + self->index);
	short  v = *p;
	self->index += 2;
	return v; 
}


short  Sgl$BufferReader$readShort(Sgl$BufferReader *  self){
	short *  p = (short * )(self->buffer->data + self->index);
	short  v = *p;
	self->index += 2;
	return v; 
}


int  Sgl$BufferReader$readInt(Sgl$BufferReader *  self){
	int *  p = (int * )(self->buffer->data + self->index);
	int  v = *p;
	self->index += 4;
	return v; 
}


long long  Sgl$BufferReader$readLongLong(Sgl$BufferReader *  self){
	long long *  p = (long long * )(self->buffer->data + self->index);
	long long  v = *p;
	self->index += 8;
	return v; 
}


Sgl$CharArray*  Sgl$BufferReader$readCharArray(Sgl$CharArray **  __outRef__, Sgl$BufferReader *  self, int  cnt){
	URGC_VAR_CLEANUP_CLASS Sgl$CharArray*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$CharArray_new(&r) ));
	((Sgl$StructArrayBase * )r)->appendByCount(r, self->buffer->data + self->index, cnt) ;
	self->index += cnt * 1;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


Sgl$ShortArray*  Sgl$BufferReader$readShortArray(Sgl$ShortArray **  __outRef__, Sgl$BufferReader *  self, int  cnt){
	URGC_VAR_CLEANUP_CLASS Sgl$ShortArray*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$ShortArray_new(&r) ));
	((Sgl$StructArrayBase * )r)->appendByCount(r, self->buffer->data + self->index, cnt) ;
	self->index += cnt * 2;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


Sgl$IntArray*  Sgl$BufferReader$readIntArray(Sgl$IntArray **  __outRef__, Sgl$BufferReader *  self, int  cnt){
	URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$IntArray_new(&r) ));
	Sgl$IntArray$appendByCount(r, self->buffer->data + self->index, cnt) ;
	self->index += cnt * 4;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


Sgl$Vec2Array*  Sgl$BufferReader$readVec2Array(Sgl$Vec2Array **  __outRef__, Sgl$BufferReader *  self, int  cnt){
	URGC_VAR_CLEANUP_CLASS Sgl$Vec2Array*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$Vec2Array_new(&r) ));
	((Sgl$StructArrayBase * )r)->appendByCount(r, self->buffer->data + self->index, cnt) ;
	self->index += cnt * 8;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


Sgl$Vec4Array*  Sgl$BufferReader$readVec4Array(Sgl$Vec4Array **  __outRef__, Sgl$BufferReader *  self, int  cnt){
	URGC_VAR_CLEANUP_CLASS Sgl$Vec4Array*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$Vec4Array_new(&r) ));
	((Sgl$StructArrayBase * )r)->appendByCount(r, self->buffer->data + self->index, cnt) ;
	self->index += cnt * 16;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


Sgl$Vec3Array*  Sgl$BufferReader$readVec3Array(Sgl$Vec3Array **  __outRef__, Sgl$BufferReader *  self, int  cnt){
	URGC_VAR_CLEANUP_CLASS Sgl$Vec3Array*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$Vec3Array_new(&r) ));
	((Sgl$StructArrayBase * )r)->appendByCount(r, self->buffer->data + self->index, cnt) ;
	self->index += cnt * 12;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


SuiCore$Vec3 Sgl$BufferReader$readVec3(Sgl$BufferReader *  self){
	SuiCore$Vec3 r;
	float *  p = (float * )(self->buffer->data + self->index);
	memcpy(&r, p, 12) ;
	self->index += 12;
	return r; 
}


SuiCore$Vec4 Sgl$BufferReader$readVec4(Sgl$BufferReader *  self){
	SuiCore$Vec4 r;
	float *  p = (float * )(self->buffer->data + self->index);
	memcpy(&r, p, 16) ;
	self->index += 16;
	return r; 
}


SuiCore$Quat Sgl$BufferReader$readQuat(Sgl$BufferReader *  self){
	SuiCore$Quat r;
	float *  p = (float * )(self->buffer->data + self->index);
	memcpy(&r, p, 16) ;
	self->index += 16;
	return r; 
}


float  Sgl$BufferReader$readFloat(Sgl$BufferReader *  self){
	float *  p = (float * )(self->buffer->data + self->index);
	float  v = *p;
	self->index += 4;
	return v; 
}


double  Sgl$BufferReader$readDouble(Sgl$BufferReader *  self){
	double *  p = (double * )(self->buffer->data + self->index);
	double  v = *p;
	self->index += 8;
	return v; 
}



Sgl$BufferReader*  Sgl$mkBufferReader(Sgl$BufferReader **  __outRef__, Sgl$Buffer *  buffer){
	URGC_VAR_CLEANUP_CLASS Sgl$BufferReader*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$BufferReader_new(&r) ));
	urgc_set_field_class(r, (void * )offsetof(Sgl$BufferReader, buffer) , buffer) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}

Sgl$Buffer*  Sgl$mkBufferFloatByJsonArray(Sgl$Buffer **  __outRef__, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  buf = (buf=NULL,urgc_init_var_class((void**)&buf, Sgl$Buffer_new(&buf) ));
	if (jo->isArray(jo) ) {
		int  l = jo->size(jo) ;
		for (int  i = 0; i < l; i++) {
			float  v = (float )jo->atAsNumber(jo, i) ;
			Sgl$Buffer$appendFloats(buf, &v, 1) ;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, buf) ; 
}

Sgl$Buffer*  Sgl$mkBufferIntByJsonArray(Sgl$Buffer **  __outRef__, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  buf = (buf=NULL,urgc_init_var_class((void**)&buf, Sgl$Buffer_new(&buf) ));
	if (jo->isArray(jo) ) {
		int  l = jo->size(jo) ;
		for (int  i = 0; i < l; i++) {
			int  v = (int )jo->atAsNumber(jo, i) ;
			Sgl$Buffer$appendInts(buf, &v, 1) ;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, buf) ; 
}


// get or init meta 
MetaStruct* Sgl$FloatsProxy_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$FloatsProxy", sizeof( Sgl$FloatsProxy ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "data", OrcMetaType_float, offsetof(Sgl$FloatsProxy, data), 0, 0, 1, 1);//float
		orc_metaField_primitive(&pNext, "capacity", OrcMetaType_int, offsetof(Sgl$FloatsProxy, capacity), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "size", OrcMetaType_int, offsetof(Sgl$FloatsProxy, size), 0, 0, 0, 0);//int
    }
	return meta;
}
Sgl$FloatsProxy Sgl$mkFloatsProxy(float *  floats, int  capacity){
	Sgl$FloatsProxy r;
	r.data = floats;
	r.capacity = capacity;
	r.size = 0;
	return r; 
}

void  Sgl$FloatsProxy$fillRemainsByValue(Sgl$FloatsProxy *  self, float  v){
	for (int  i = self->size; i < self->capacity; i++) {
		self->data[i] = v;
	}
}

void  Sgl$FloatsProxy$appendFloats(Sgl$FloatsProxy *  self, float *  a, int  cnt){
	if (self->size + cnt <= self->capacity) {
		for (int  i = 0; i < cnt; i++) {
			self->data[self->size] = a[i];
			self->size++;
		}
	}
}

void  Sgl$FloatsProxy$appendFloat(Sgl$FloatsProxy *  self, float  v){
	if (self->size + 1 <= self->capacity) {
		self->data[self->size] = v;
		self->size++;
	}
}

void  Sgl$FloatsProxy$appendFloat2(Sgl$FloatsProxy *  self, float  a, float  b){
	if (self->size + 2 <= self->capacity) {
		self->data[self->size] = a;
		self->size++;
		self->data[self->size] = b;
		self->size++;
	}
}

void  Sgl$FloatsProxy$appendFloat3(Sgl$FloatsProxy *  self, float  a, float  b, float  c){
	if (self->size + 3 <= self->capacity) {
		self->data[self->size] = a;
		self->size++;
		self->data[self->size] = b;
		self->size++;
		self->data[self->size] = c;
		self->size++;
	}
}

void  Sgl$FloatsProxy$appendFloat4(Sgl$FloatsProxy *  self, float  a, float  b, float  c, float  d){
	if (self->size + 4 <= self->capacity) {
		self->data[self->size] = a;
		self->size++;
		self->data[self->size] = b;
		self->size++;
		self->data[self->size] = c;
		self->size++;
		self->data[self->size] = d;
		self->size++;
	}
}

void  Sgl$FloatsProxy$distinctSelf(Sgl$FloatsProxy *  self){
	self->size = Sgl$Floats_distinct(self->data, self->size) ;
}

bool  Sgl$FloatsProxy$distinctTo(Sgl$FloatsProxy *  self, Sgl$FloatsProxy *  fp){
	if (fp->capacity < self->size) {
		return false; 
	}
	fp->size = Sgl$Floats_distinctTo(self->data, fp->data, self->size) ;
	return true; 
}

bool  Sgl$FloatsProxy$has(Sgl$FloatsProxy *  self, float  v){
	return Sgl$Floats_has(self->data, self->size, v) ; 
}

void  Sgl$FloatsProxy$setAllCapacity(Sgl$FloatsProxy *  self, float  v){
	Sgl$Floats_set(self->data, self->capacity, v) ;
	self->size = self->capacity;
}

void  Sgl$FloatsProxy$set(Sgl$FloatsProxy *  self, int  i, float  v){
	if (i < self->size) {
		self->data[i] = v;
	}
}

void  Sgl$FloatsProxy$append(Sgl$FloatsProxy *  self, float  v){
	if (self->size < self->capacity) {
		self->data[self->size] = v;
		self->size++;
	}
}

void  Sgl$FloatsProxy$clear(Sgl$FloatsProxy *  self){
	self->size = 0;
}

bool  Sgl$FloatsProxy$removeRange(Sgl$FloatsProxy *  self, int  fromIndex, int  toExcludeIndex){
	toExcludeIndex = Orc$minInt(self->size, toExcludeIndex) ;
	fromIndex = Orc$maxInt(0, fromIndex) ;
	if (fromIndex > toExcludeIndex) {
		return false; 
	}
	if (fromIndex == toExcludeIndex) {
		return true; 
	}
	int  cnt = self->size - toExcludeIndex;
	memmove(self->data + fromIndex, self->data + toExcludeIndex, cnt) ;
	self->size -= cnt;
	return true; 
}

void  Sgl$Floats_bubbleSort(float *  arr, int  len, bool  asc){
	if (asc) {
		for (int  i = 0; i < len - 1; i++) {
			for (int  j = 0; j < len - 1 - i; j++) {
				if (arr[j] > arr[j + 1]) {
					float  temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}
	else {
		for (int  i = 0; i < len - 1; i++) {
			for (int  j = 0; j < len - 1 - i; j++) {
				if (arr[j] < arr[j + 1]) {
					float  temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}
}

int  Sgl$Floats_distinct(float *  floats, int  cnt){
	int  dstIdx = 0;
	for (int  i = 0; i < cnt; i++) {
		float  v = floats[i];
		if (!Sgl$Floats_has(floats, dstIdx, v) ) {
			floats[dstIdx] = v;
			dstIdx++;
		}
	}
	return dstIdx; 
}

int  Sgl$Floats_distinctTo(float *  floats, float *  target, int  cnt){
	int  targetCnt = 0;
	for (int  i = 0; i < cnt; i++) {
		float  v = floats[i];
		if (!Sgl$Floats_has(target, targetCnt, v) ) {
			target[targetCnt] = v;
			targetCnt++;
		}
	}
	return targetCnt; 
}

bool  Sgl$Floats_has(float *  floats, int  cnt, float  value){
	for (int  i = 0; i < cnt; i++) {
		if (floats[i] == value) {
			return true; 
		}
	}
	return false; 
}

void  Sgl$Floats_set(float *  floats, int  cnt, float  value){
	for (int  i = 0; i < cnt; i++) {
		floats[i] = value;
	}
}

void  Sgl$testIntArray(){
	URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  ia = (ia=NULL,urgc_init_var_class((void**)&ia, Sgl$IntArray_new(&ia) ));
	Sgl$IntArray$expandCapacity(ia, 1500) ;
	for (int  i = 0; i < 2000; i++) {
		Sgl$IntArray$append(ia, i) ;
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("ia:%s\n", Sgl$IntArray$toString(&tmpReturn_1, ia) ->str) ;
}

void  Sgl$testBuffer(){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  buf = Sgl$Buffer_readFile((buf = NULL,&buf), "../asset/100.w3e") ;
	Sgl$Buffer$appendChars(buf, "", 1) ;
	printf("content:%s\n", buf->data) ;
	URGC_VAR_CLEANUP_CLASS Sgl$BufferReader*  br = Sgl$mkBufferReader((br = NULL,&br), buf) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  head = br->readString((head = NULL,&head), br, 4) ;
	printf("head:%s. eq:%d\n", head->str, Orc$String$equals(head, "W3E!") ) ;
}



