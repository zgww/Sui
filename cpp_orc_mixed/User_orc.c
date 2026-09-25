
#include "User_orc.h" 

#include <stdio.h>


// static struct 


// static function declaration


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

    ((Vtable_Object*)pvt)->refc = 1;

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
	((User*)self)->age = 0;
    }
	((Object*)self)->ctor = (void*)User$ctor;
	((Object*)self)->dtor = (void*)User$dtor;
	((User*)self)->say = (void*)User$say;
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
	printf("say msg:%s to User[age=%d]\n", msg, self->age) ;
}



User*  orcMain(User **  __outRef__){
	URGC_VAR_CLEANUP_CLASS User*  u = (u=NULL,urgc_init_var_class((void**)&u, User_new(&u) ));
	u->age = 349;
	return urgc_set_var_for_return_class((void ** )__outRef__, u) ; 
}



