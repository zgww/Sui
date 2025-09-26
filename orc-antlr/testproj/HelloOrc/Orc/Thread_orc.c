
#include "Thread_orc.h" 

#include <stdio.h>
#include "./Time_orc.h"


// static struct 
typedef struct tagOrcLang$__Block_32_17 OrcLang$__Block_32_17;

typedef struct tagOrcLang$__Closure_35_16 OrcLang$__Closure_35_16;



struct tagOrcLang$__Block_32_17 {
	int  age ;
};



struct tagOrcLang$__Closure_35_16 {
	void  (*invoke)();
	OrcLang$__Block_32_17*  __var___Block_32_17 ;
};



// static function declaration
static void  OrcLang$__fn___Closure_35_16(OrcLang$__Closure_35_16 *  self);
static OrcLang$__Closure_35_16*  OrcLang$__make___Closure_35_16(OrcLang$__Closure_35_16 **  __outRef__, OrcLang$__Block_32_17 *  __var___Block_32_17);



//vtable instance
Vtable_OrcLang$Thread _vtable_OrcLang$Thread;

// init meta

void OrcLang$Thread_initMeta(Vtable_OrcLang$Thread *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "run", offsetof(OrcLang$Thread, run));
	orc_metaField_method(&pNext, "initData", offsetof(OrcLang$Thread, initData));
	orc_metaField_method(&pNext, "freeData", offsetof(OrcLang$Thread, freeData));
	orc_metaField_method(&pNext, "start", offsetof(OrcLang$Thread, start));
	orc_metaField_method(&pNext, "join", offsetof(OrcLang$Thread, join));
}


// vtable init


Vtable_OrcLang$Thread* Vtable_OrcLang$Thread_init(Vtable_OrcLang$Thread* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$Thread;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$Thread_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$Thread";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$Thread_initMeta;

    return pvt;
}


// fini function

void OrcLang$Thread_fini(OrcLang$Thread *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void OrcLang$Thread_init_fields(OrcLang$Thread *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)OrcLang$Thread_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)OrcLang$Thread$ctor;
	((Object*)self)->dtor = (void*)OrcLang$Thread$dtor;
	((OrcLang$Thread*)self)->run = (void*)OrcLang$Thread$run;
	((OrcLang$Thread*)self)->initData = (void*)OrcLang$Thread$initData;
	((OrcLang$Thread*)self)->freeData = (void*)OrcLang$Thread$freeData;
	((OrcLang$Thread*)self)->start = (void*)OrcLang$Thread$start;
	((OrcLang$Thread*)self)->join = (void*)OrcLang$Thread$join;
}

// init function

void OrcLang$Thread_init(OrcLang$Thread *self){
    Vtable_OrcLang$Thread_init(&_vtable_OrcLang$Thread);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$Thread;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$Thread_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$Thread * OrcLang$Thread_new(){
    OrcLang$Thread *self = calloc(1, sizeof(OrcLang$Thread));
    OrcLang$Thread_init(self);
    return self;
}


// class members
void  OrcLang$Thread$ctor(OrcLang$Thread *  self){
	self->initData(self) ;
}


void  OrcLang$Thread$dtor(OrcLang$Thread *  self){
	printf("free Thread %p\n", self) ;
	self->freeData(self) ;
}


void  OrcLang$Thread$run(OrcLang$Thread *  self){
	if (self->runFunc != NULL) {
		(*(self->runFunc))((void * )(self->runFunc)) ;
	}
}



void  OrcLang$testThread(){
	URGC_VAR_CLEANUP OrcLang$__Block_32_17*  __var___Block_32_17 = urgc_init_var((void**)&__var___Block_32_17, orc_alloc_and_set_deleter(sizeof(OrcLang$__Block_32_17) ) );
	URGC_VAR_CLEANUP OrcLang$Thread*  t = urgc_init_var((void**)&t, OrcLang$Thread_new() );
	__var___Block_32_17->age = 102;
	URGC_VAR_CLEANUP OrcLang$__Closure_35_16*  tmpReturn_1 = NULL;
	urgc_set_field(t, (void * )offsetof(OrcLang$Thread, runFunc) , OrcLang$__make___Closure_35_16(&tmpReturn_1, __var___Block_32_17) ) ;
	t->start(t) ;
	OrcLang$Time_sleepMs(4000) ;
	printf("in main: age:%d runFunc:%p\n", __var___Block_32_17->age, t->runFunc) ;
}

static void  OrcLang$__fn___Closure_35_16(OrcLang$__Closure_35_16 *  self){
	printf("in thread start age :%d\n", self->__var___Block_32_17->age) ;
	for (int  i = 0; i < 10; i++) {
		self->__var___Block_32_17->age = i;
		OrcLang$Time_sleepMs(1000) ;
		printf("hi in thread : i:%d, age:%d\n", i, self->__var___Block_32_17->age) ;
	}
	printf("thread end\n") ;
}

static OrcLang$__Closure_35_16*  OrcLang$__make___Closure_35_16(OrcLang$__Closure_35_16 **  __outRef__, OrcLang$__Block_32_17 *  __var___Block_32_17){
	URGC_VAR_CLEANUP OrcLang$__Closure_35_16*  self = urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(OrcLang$__Closure_35_16) ) );
	self->invoke = OrcLang$__fn___Closure_35_16;
	urgc_set_field(self, (void * )offsetof(OrcLang$__Closure_35_16, __var___Block_32_17) , __var___Block_32_17) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



