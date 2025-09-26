
#include "Main_orc.h" 

#include <stdio.h>

#include <math.h>


// static struct 
typedef struct tag__Block_102_14 __Block_102_14;

typedef struct tag__Closure_hi_104 __Closure_hi_104;



struct tag__Block_102_14 {
	User *  self ;
	int  v2 ;
};



struct tag__Closure_hi_104 {
	void  (*invoke)();
	__Block_102_14*  __var___Block_102_14 ;
};



// static function declaration
static void  __fn___Closure_hi_104(__Closure_hi_104 *  self);
static __Closure_hi_104*  __make___Closure_hi_104(__Closure_hi_104 **  __outRef__, __Block_102_14 *  __var___Block_102_14);



//vtable instance
Vtable_User _vtable_User;

// init meta

void User_initMeta(Vtable_User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "id", OrcMetaType_int, offsetof(User, id), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "say", offsetof(User, say));
    isnan(10);
}


// vtable init


Vtable_User* Vtable_User_init(Vtable_User* pvt){
    if (pvt == NULL){
        pvt = &_vtable_User;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&User_new;
    ((Vtable_Object*)pvt)->className = "User";

    ((Vtable_Object*)pvt)->initMeta = (void*)User_initMeta;

    return pvt;
}


// fini function

void User_fini(User *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void User_init_fields(User *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)User_fini;
	//fields
    {
	((User*)self)->id = 0;
    }
	((User*)self)->say = (void*)User$say;
}

// init function

void User_init(User *self){
    Vtable_User_init(&_vtable_User);

    ((Object*)self)->vtable = (void*)&_vtable_User;

    urgc_guard(self, (void*)orc_delete);

    User_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
User * User_new(){
    User *self = calloc(1, sizeof(User));
    User_init(self);
    return self;
}


// class members
void  User$say(User *  self){
	URGC_VAR_CLEANUP __Block_102_14*  __var___Block_102_14 = urgc_init_var((void**)&__var___Block_102_14, orc_alloc_and_set_deleter(sizeof(__Block_102_14) ) );
	__var___Block_102_14->self = self;
	__var___Block_102_14->v2 = 3;
	URGC_VAR_CLEANUP void  (**hi)(void *  self) = NULL;
	URGC_VAR_CLEANUP __Closure_hi_104*  tmpReturn_1 = NULL;
	(urgc_set_var(&hi, __make___Closure_hi_104(&tmpReturn_1, __var___Block_102_14) ) );
}



static void  __fn___Closure_hi_104(__Closure_hi_104 *  self){
	self->__var___Block_102_14->self->id = 10;
	self->__var___Block_102_14->v2 = self->__var___Block_102_14->self->id;
	printf("", self->__var___Block_102_14->self->id) ;
}

static __Closure_hi_104*  __make___Closure_hi_104(__Closure_hi_104 **  __outRef__, __Block_102_14 *  __var___Block_102_14){
	URGC_VAR_CLEANUP __Closure_hi_104*  self = urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_hi_104) ) );
	self->invoke = __fn___Closure_hi_104;
	urgc_set_field(self, (void * )offsetof(__Closure_hi_104, __var___Block_102_14) , __var___Block_102_14) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

int  main(){
	return 0; 
}



