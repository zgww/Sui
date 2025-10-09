
#include "Thread_orc.h" 

#include <stdio.h>
#include "./Orc.h"
#include "./Time_orc.h"


// static struct 
typedef struct tagOrc$__Block_33_17 Orc$__Block_33_17;

typedef struct tagOrc$__Closure_36_16 Orc$__Closure_36_16;



struct tagOrc$__Block_33_17 {
	int  age ;
};





struct tagOrc$__Closure_36_16 {
	void  (*invoke)(Orc$__Closure_36_16 *  self);
	Vtable_Object *  vtable ;
	Orc$__Block_33_17*  __var___Block_33_17 ;
};





// static function declaration
static void  __finiBlock___Block_33_17(Orc$__Block_33_17 *  self);
static void  __fn___Closure_36_16(Orc$__Closure_36_16 *  self);
static void  __fini___Closure_36_16(Orc$__Closure_36_16 *  self);
static Orc$__Closure_36_16*  __make___Closure_36_16(Orc$__Closure_36_16 **  __outRef__, Orc$__Block_33_17 *  __var___Block_33_17);



//vtable instance
Vtable_Orc$Thread _vtable_Orc$Thread;

// init meta

void Orc$Thread_initMeta(Vtable_Orc$Thread *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_void, offsetof(Orc$Thread, data), 0, 0, 1, 1);//void

	orc_metaField_method(&pNext, "run", offsetof(Orc$Thread, run));
	orc_metaField_method(&pNext, "initData", offsetof(Orc$Thread, initData));
	orc_metaField_method(&pNext, "freeData", offsetof(Orc$Thread, freeData));
	orc_metaField_method(&pNext, "start", offsetof(Orc$Thread, start));
	orc_metaField_method(&pNext, "join", offsetof(Orc$Thread, join));
}


// vtable init


Vtable_Orc$Thread* Vtable_Orc$Thread_init(Vtable_Orc$Thread* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$Thread;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$Thread_new;
    ((Vtable_Object*)pvt)->className = "Orc$Thread";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$Thread_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Orc$Thread_fini(Orc$Thread *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void Orc$Thread_init_fields(Orc$Thread *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Orc$Thread_fini;
	//fields
    {
	urgc_set_field(self, (void**)&((Orc$Thread*)self)->runFunc, NULL);
    }
	((Object*)self)->ctor = (void*)Orc$Thread$ctor;
	((Object*)self)->dtor = (void*)Orc$Thread$dtor;
	((Orc$Thread*)self)->run = (void*)Orc$Thread$run;
	((Orc$Thread*)self)->initData = (void*)Orc$Thread$initData;
	((Orc$Thread*)self)->freeData = (void*)Orc$Thread$freeData;
	((Orc$Thread*)self)->start = (void*)Orc$Thread$start;
	((Orc$Thread*)self)->join = (void*)Orc$Thread$join;
}

// init function

void Orc$Thread_init(Orc$Thread *self, void *pOwner){
    Vtable_Orc$Thread_init(&_vtable_Orc$Thread);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$Thread;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$Thread_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$Thread * Orc$Thread_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$Thread *self = calloc(1, sizeof(Orc$Thread));
	
    Orc$Thread_init(self, pOwner);
    return self;
}


// class members
void  Orc$Thread$ctor(Orc$Thread *  self){
	self->initData(self) ;
}


void  Orc$Thread$dtor(Orc$Thread *  self){
	printf("free Thread %p\n", self) ;
	self->freeData(self) ;
}


void  Orc$Thread$run(Orc$Thread *  self){
	if (self->runFunc != NULL) {
		(*(self->runFunc))((void * )(self->runFunc)) ;
	}
}



void  Orc$testThread(){
	URGC_VAR_CLEANUP Orc$__Block_33_17*  __var___Block_33_17 = (__var___Block_33_17=NULL,urgc_init_var((void**)&__var___Block_33_17, orc_alloc_and_set_deleter(sizeof(Orc$__Block_33_17) , __finiBlock___Block_33_17) ));
	URGC_VAR_CLEANUP_CLASS Orc$Thread*  t = (t=NULL,urgc_init_var_class((void**)&t, Orc$Thread_new(&t) ));
	__var___Block_33_17->age = 102;
	URGC_VAR_CLEANUP Orc$__Closure_36_16*  tmpReturn_1 = NULL;
	urgc_set_field(t, (void * )offsetof(Orc$Thread, runFunc) , __make___Closure_36_16(&tmpReturn_1, __var___Block_33_17) ) ;
	t->start(t) ;
	Orc$Time_sleepMs(4000) ;
	printf("in main: age:%d runFunc:%p\n", __var___Block_33_17->age, t->runFunc) ;
}

static void  __finiBlock___Block_33_17(Orc$__Block_33_17 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_36_16(Orc$__Closure_36_16 *  self){
	printf("in thread start age :%d\n", self->__var___Block_33_17->age) ;
	for (int  i = 0; i < 10; i++) {
		self->__var___Block_33_17->age = i;
		Orc$Time_sleepMs(1000) ;
		printf("hi in thread : i:%d, age:%d\n", i, self->__var___Block_33_17->age) ;
	}
	printf("thread end\n") ;
}

static void  __fini___Closure_36_16(Orc$__Closure_36_16 *  self){
	urgc_set_field(self, (void * )offsetof(Orc$__Closure_36_16, __var___Block_33_17) , NULL) ;
	urgc_free_later(self) ;
}

static Orc$__Closure_36_16*  __make___Closure_36_16(Orc$__Closure_36_16 **  __outRef__, Orc$__Block_33_17 *  __var___Block_33_17){
	URGC_VAR_CLEANUP Orc$__Closure_36_16*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Orc$__Closure_36_16) , __fini___Closure_36_16) ));
	self->invoke = __fn___Closure_36_16;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Orc$__Closure_36_16, __var___Block_33_17) , __var___Block_33_17) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



