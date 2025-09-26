
#include "Orc.h"
#include "setExpr_orc.h" 



// static struct 


// static function declaration



//vtable instance
Vtable_Project$User _vtable_Project$User;

// init meta

void Project$User_initMeta(Vtable_Project$User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_Project$User* Vtable_Project$User_init(Vtable_Project$User* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Project$User;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Project$User_new;
    ((Vtable_Object*)pvt)->className = "Project$User";

    ((Vtable_Object*)pvt)->initMeta = (void*)Project$User_initMeta;

    return pvt;
}


// fini function

void Project$User_fini(Project$User *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Project$User_init_fields(Project$User *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Project$User_fini;
	//fields
    {
	
    }
	
}

// init function

void Project$User_init(Project$User *self){
    Vtable_Project$User_init(&_vtable_Project$User);

    ((Object*)self)->vtable = (void*)&_vtable_Project$User;

    urgc_guard(self, (void*)orc_delete);

    Project$User_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
Project$User * Project$User_new(){
    Project$User *self = calloc(1, sizeof(Project$User));
    Project$User_init(self);
    return self;
}


// class members

void  Project$hi(){
	URGC_VAR_CLEANUP Project$User*  user = NULL;
	urgc_set_var(&user, Project$User_new() ) ;
	urgc_set_var(&user, NULL) ;
}



