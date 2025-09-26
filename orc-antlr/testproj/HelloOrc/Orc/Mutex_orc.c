
#include "Mutex_orc.h" 

#include <stdio.h>


// static struct 


// static function declaration



//vtable instance
Vtable_OrcLang$Mutex _vtable_OrcLang$Mutex;

// init meta

void OrcLang$Mutex_initMeta(Vtable_OrcLang$Mutex *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "lock", offsetof(OrcLang$Mutex, lock));
	orc_metaField_method(&pNext, "unlock", offsetof(OrcLang$Mutex, unlock));
	orc_metaField_method(&pNext, "tryLock", offsetof(OrcLang$Mutex, tryLock));
	orc_metaField_method(&pNext, "freeData", offsetof(OrcLang$Mutex, freeData));
	orc_metaField_method(&pNext, "initData", offsetof(OrcLang$Mutex, initData));
}


// vtable init


Vtable_OrcLang$Mutex* Vtable_OrcLang$Mutex_init(Vtable_OrcLang$Mutex* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$Mutex;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$Mutex_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$Mutex";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$Mutex_initMeta;

    return pvt;
}


// fini function

void OrcLang$Mutex_fini(OrcLang$Mutex *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void OrcLang$Mutex_init_fields(OrcLang$Mutex *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)OrcLang$Mutex_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)OrcLang$Mutex$ctor;
	((Object*)self)->dtor = (void*)OrcLang$Mutex$dtor;
	((OrcLang$Mutex*)self)->lock = (void*)OrcLang$Mutex$lock;
	((OrcLang$Mutex*)self)->unlock = (void*)OrcLang$Mutex$unlock;
	((OrcLang$Mutex*)self)->tryLock = (void*)OrcLang$Mutex$tryLock;
	((OrcLang$Mutex*)self)->freeData = (void*)OrcLang$Mutex$freeData;
	((OrcLang$Mutex*)self)->initData = (void*)OrcLang$Mutex$initData;
}

// init function

void OrcLang$Mutex_init(OrcLang$Mutex *self){
    Vtable_OrcLang$Mutex_init(&_vtable_OrcLang$Mutex);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$Mutex;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$Mutex_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$Mutex * OrcLang$Mutex_new(){
    OrcLang$Mutex *self = calloc(1, sizeof(OrcLang$Mutex));
    OrcLang$Mutex_init(self);
    return self;
}


// class members
void  OrcLang$Mutex$ctor(OrcLang$Mutex *  self){
	self->initData(self) ;
}


void  OrcLang$Mutex$dtor(OrcLang$Mutex *  self){
	self->freeData(self) ;
	printf("free Mutex:%p\n", self) ;
}





