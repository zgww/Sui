
#include "Orc.h"
#include "Closure_orc.h" 



// static struct 
typedef struct tagTest$__Closure_10_19 Test$__Closure_10_19;



struct tagTest$__Closure_10_19 {
void  (*invoke)();

};



// static function declaration
static void  Test$__fn___Closure_10_19(Test$__Closure_10_19 *  self);
static Test$__Closure_10_19*  Test$__make___Closure_10_19(Test$__Closure_10_19 **  __outRef__);



//vtable instance
Vtable_Test$User _vtable_Test$User;

// init meta

void Test$User_initMeta(Vtable_Test$User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_Test$User* Vtable_Test$User_init(Vtable_Test$User* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Test$User;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Test$User_new;
    ((Vtable_Object*)pvt)->className = "Test$User";

    ((Vtable_Object*)pvt)->initMeta = (void*)Test$User_initMeta;

    return pvt;
}


// fini function

void Test$User_fini(Test$User *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Test$User_init_fields(Test$User *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Test$User_fini;
	//fields
    {
	
    }
	
}

// init function

void Test$User_init(Test$User *self){
    Vtable_Test$User_init(&_vtable_Test$User);

    ((Object*)self)->vtable = (void*)&_vtable_Test$User;

    urgc_guard(self, (void*)orc_delete);

    Test$User_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
Test$User * Test$User_new(){
    Test$User *self = calloc(1, sizeof(Test$User));
    Test$User_init(self);
    return self;
}


// class members

void  Test$say(){
	URGC_VAR_CLEANUP Test$__Closure_10_19*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP void  (**hi2)() = urgc_init_var((void**)&hi2, Test$__make___Closure_10_19(&tmpReturn_1) );
	(*hi2)() ;
}

static void  Test$__fn___Closure_10_19(Test$__Closure_10_19 *  self){
	
}

static Test$__Closure_10_19*  Test$__make___Closure_10_19(Test$__Closure_10_19 **  __outRef__){
	URGC_VAR_CLEANUP Test$__Closure_10_19*  self = urgc_init_var((void**)&self, malloc(sizeof(Test$__Closure_10_19) ) );
	self->invoke = Test$__fn___Closure_10_19;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



