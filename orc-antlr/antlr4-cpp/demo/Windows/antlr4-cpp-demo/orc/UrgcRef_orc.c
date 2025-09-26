
#include "Orc.h"
#include "UrgcRef_orc.h" 



// static struct 


// static function declaration
static void  st();


int  Project_Mod$say(){
	return 10; 
}


//vtable instance
Vtable_Project_Mod$Father _vtable_Project_Mod$Father;

// init meta

void Project_Mod$Father_initMeta(Vtable_Project_Mod$Father *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "lala", offsetof(Project_Mod$Father, lala));
}


// vtable init


Vtable_Project_Mod$Father* Vtable_Project_Mod$Father_init(Vtable_Project_Mod$Father* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Project_Mod$Father;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Project_Mod$Father_new;
    ((Vtable_Object*)pvt)->className = "Project_Mod$Father";

    ((Vtable_Object*)pvt)->initMeta = (void*)Project_Mod$Father_initMeta;

    return pvt;
}


// fini function

void Project_Mod$Father_fini(Project_Mod$Father *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Project_Mod$Father_init_fields(Project_Mod$Father *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Project_Mod$Father_fini;
	//fields
    {
	
    }
	((Project_Mod$Father*)self)->lala = (void*)&Project_Mod$Father$lala;
}

// init function

void Project_Mod$Father_init(Project_Mod$Father *self){
    Vtable_Project_Mod$Father_init(&_vtable_Project_Mod$Father);

    ((Object*)self)->vtable = (void*)&_vtable_Project_Mod$Father;

    urgc_guard(self, (void*)orc_delete);

    Project_Mod$Father_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
Project_Mod$Father * Project_Mod$Father_new(){
    Project_Mod$Father *self = calloc(1, sizeof(Project_Mod$Father));
    Project_Mod$Father_init(self);
    return self;
}


// class members
void  Project_Mod$Father$lala(Project_Mod$Father *  self){
	
}




//vtable instance
Vtable_Project_Mod$User _vtable_Project_Mod$User;

// init meta

void Project_Mod$User_initMeta(Vtable_Project_Mod$User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "print", offsetof(Project_Mod$User, print));
}


// vtable init


Vtable_Project_Mod$User* Vtable_Project_Mod$User_init(Vtable_Project_Mod$User* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Project_Mod$User;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Project_Mod$Father_init(&_vtable_Project_Mod$Father);

	// init by super vtable init function
    Vtable_Project_Mod$Father_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Project_Mod$Father;
    ((Vtable_Object*)pvt)->make = (void*)&Project_Mod$User_new;
    ((Vtable_Object*)pvt)->className = "Project_Mod$User";

    ((Vtable_Object*)pvt)->initMeta = (void*)Project_Mod$User_initMeta;

    return pvt;
}


// fini function

void Project_Mod$User_fini(Project_Mod$User *self){
	//super fini
    Project_Mod$Father_fini((Project_Mod$Father *)self);

    //字段释放


}

// init fields function


void Project_Mod$User_init_fields(Project_Mod$User *self){
	//super class
    Project_Mod$Father_init_fields((Project_Mod$Father*)self);

    ((Object*)self)->fini = (void*)Project_Mod$User_fini;
	//fields
    {
	
    }
	((Project_Mod$User*)self)->print = (void*)&Project_Mod$User$print;
}

// init function

void Project_Mod$User_init(Project_Mod$User *self){
    Vtable_Project_Mod$User_init(&_vtable_Project_Mod$User);

    ((Object*)self)->vtable = (void*)&_vtable_Project_Mod$User;

    urgc_guard(self, (void*)orc_delete);

    Project_Mod$User_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
Project_Mod$User * Project_Mod$User_new(){
    Project_Mod$User *self = calloc(1, sizeof(Project_Mod$User));
    Project_Mod$User_init(self);
    return self;
}


// class members
void  Project_Mod$User$print(Project_Mod$User *  self){
	
}



static void  st(){
	
}

void  Project_Mod$User$calc(Project_Mod$User *  self){
	
}

Project_Mod$User*  Project_Mod$useRef(Project_Mod$User **  __outRef__, Project_Mod$User*  u){
	URGC_REF_ARG_WITH_CLEANUP(u);

	return urgc_set_var_for_return((void ** )__outRef__, u) ; 
}

void  Project_Mod$main(){
	URGC_VAR_CLEANUP Project_Mod$User*  a = NULL;
	URGC_VAR_CLEANUP Project_Mod$User*  b = urgc_init_var((void**)&b, a);
	Project_Mod$User *  c = NULL;
	urgc_set_var(&b, c) ;
	URGC_VAR_CLEANUP Project_Mod$User*  tmpReturn_1 = NULL;
	Project_Mod$useRef(&tmpReturn_1, b) ;
}



