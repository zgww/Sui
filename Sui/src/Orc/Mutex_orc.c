
#include "Mutex_orc.h" 

#include <stdio.h>


// static struct 


// static function declaration



//vtable instance
Vtable_Orc$Mutex _vtable_Orc$Mutex;

// init meta

void Orc$Mutex_initMeta(Vtable_Orc$Mutex *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_void, offsetof(Orc$Mutex, data), 0, 0, 1, 1);//void

	orc_metaField_method(&pNext, "lock", offsetof(Orc$Mutex, lock));
	orc_metaField_method(&pNext, "unlock", offsetof(Orc$Mutex, unlock));
	orc_metaField_method(&pNext, "tryLock", offsetof(Orc$Mutex, tryLock));
	orc_metaField_method(&pNext, "freeData", offsetof(Orc$Mutex, freeData));
	orc_metaField_method(&pNext, "initData", offsetof(Orc$Mutex, initData));
}


// vtable init


Vtable_Orc$Mutex* Vtable_Orc$Mutex_init(Vtable_Orc$Mutex* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$Mutex;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$Mutex_new;
    ((Vtable_Object*)pvt)->className = "Orc$Mutex";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$Mutex_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Orc$Mutex_fini(Orc$Mutex *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void Orc$Mutex_init_fields(Orc$Mutex *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Orc$Mutex_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Orc$Mutex$ctor;
	((Object*)self)->dtor = (void*)Orc$Mutex$dtor;
	((Orc$Mutex*)self)->lock = (void*)Orc$Mutex$lock;
	((Orc$Mutex*)self)->unlock = (void*)Orc$Mutex$unlock;
	((Orc$Mutex*)self)->tryLock = (void*)Orc$Mutex$tryLock;
	((Orc$Mutex*)self)->freeData = (void*)Orc$Mutex$freeData;
	((Orc$Mutex*)self)->initData = (void*)Orc$Mutex$initData;
}

// init function

void Orc$Mutex_init(Orc$Mutex *self, void *pOwner){
    Vtable_Orc$Mutex_init(&_vtable_Orc$Mutex);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$Mutex;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$Mutex_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$Mutex * Orc$Mutex_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$Mutex *self = calloc(1, sizeof(Orc$Mutex));
	
    Orc$Mutex_init(self, pOwner);
    return self;
}


// class members
void  Orc$Mutex$ctor(Orc$Mutex *  self){
	self->initData(self) ;
}


void  Orc$Mutex$dtor(Orc$Mutex *  self){
	self->freeData(self) ;
	printf("free Mutex:%p\n", self) ;
}





