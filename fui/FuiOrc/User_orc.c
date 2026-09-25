
#include "User_orc.h" 

#include <stdio.h>
#include "./Orc/String_orc.h"


// static struct 
typedef struct tag__Closure_23_21 __Closure_23_21;



struct tag__Closure_23_21 {
	void  (*invoke)(__Closure_23_21 *  self);
	Vtable_Object *  vtable ;
};





// static function declaration
static void  __fn___Closure_23_21(__Closure_23_21 *  self);
static void  __fini___Closure_23_21(__Closure_23_21 *  self);
static __Closure_23_21*  __make___Closure_23_21(__Closure_23_21 **  __outRef__);


void  say(){
	printf("hi\n") ;
}


//vtable instance
Vtable_User _vtable_User;

// init meta

void User_initMeta(Vtable_User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "age", OrcMetaType_int, offsetof(User, age), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "say", offsetof(User, say));
	orc_metaField_method(&pNext, "hi", offsetof(User, hi));
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

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void User_fini(User *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_set_field(self, (void**)&((User*)self)->onSay, NULL);

}

// init fields function


void User_init_fields(User *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)User_fini;
	//fields
    {
	((User*)self)->age = 0;
	urgc_set_field(self, (void**)&((User*)self)->onSay, NULL);
    }
	((Object*)self)->ctor = (void*)User$ctor;
	((Object*)self)->dtor = (void*)User$dtor;
	((User*)self)->say = (void*)User$say;
	((User*)self)->hi = (void*)User$hi;
}

// init function

void User_init(User *self, void *pOwner){
    Vtable_User_init(&_vtable_User);

    ((Object*)self)->vtable = (void*)&_vtable_User;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    User_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
User * User_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    User *self = ORC_CALLOC(1, sizeof(User));
	
    User_init(self, pOwner);
    return self;
}


// class members
void  User$ctor(User *  self){
	printf("User.ctor\n") ;
}


void  User$dtor(User *  self){
	printf("User.dtor. age=%d\n", self->age) ;
}


void  User$say(User *  self, const char *  msg){
	printf("say msg:%s to User[age=%d]. 更新一下user。 小调整. 编译.c只需要2s, 编译.cpp需要5，6s \n", msg, self->age) ;
	URGC_VAR_CLEANUP __Closure_23_21*  tmpReturn_1 = NULL;
	urgc_set_field(self, (void * )offsetof(User, onSay) , __make___Closure_23_21(&tmpReturn_1) ) ;
	(*(self->onSay))((void * )(self->onSay)) ;
	int  status = 0;
	URGC_VAR_CLEANUP_CLASS Orc$String*  body = _httpGet((body = NULL,&body), "www.baidu.com", 80, "/", &status) ;
	printf("get www.baidu.com:%s\nstatus=%d\n", body->str, status) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_var_class(&body, _httpGet(&tmpReturn_2, "www.oschina.net", 80, "/", &status) ) ;
	printf("get www.baidu.com:%s\nstatus=%d\n", body->str, status) ;
}


void  User$hi(User *  self){
	
}



static void  __fn___Closure_23_21(__Closure_23_21 *  self){
	printf("on   Say\n") ;
}

static void  __fini___Closure_23_21(__Closure_23_21 *  self){
	urgc_free_later(self) ;
}

static __Closure_23_21*  __make___Closure_23_21(__Closure_23_21 **  __outRef__){
	URGC_VAR_CLEANUP __Closure_23_21*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_23_21) , __fini___Closure_23_21) ));
	self->invoke = __fn___Closure_23_21;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

User*  orcMain(User **  __outRef__){
	URGC_VAR_CLEANUP_CLASS User*  u = (u=NULL,urgc_init_var_class((void**)&u, User_new(&u) ));
	u->age = 349;
	return urgc_set_var_for_return_class((void ** )__outRef__, u) ; 
}



