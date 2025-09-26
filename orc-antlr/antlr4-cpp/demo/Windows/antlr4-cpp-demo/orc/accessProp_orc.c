
#include "Orc.h"
#include "accessProp_orc.h" 

#include "stdio.h";


// static struct 


// static function declaration


void  Project$printf(){
	
}

void  Project$main(){
	Project$printf("hello world\n") ;
}


//vtable instance
Vtable_Project$Parent _vtable_Project$Parent;

// init meta

void Project$Parent_initMeta(Vtable_Project$Parent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "superField", OrcMetaType_int, offsetof(Project$Parent, superField), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "superTmp", ((Vtable_Object*)Vtable_Project$User_init(0)), offsetof(Project$Parent, superTmp), true, false, 1);

	orc_metaField_method(&pNext, "lala", offsetof(Project$Parent, lala));
}


// vtable init


Vtable_Project$Parent* Vtable_Project$Parent_init(Vtable_Project$Parent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Project$Parent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Project$Parent_new;
    ((Vtable_Object*)pvt)->className = "Project$Parent";

    ((Vtable_Object*)pvt)->initMeta = (void*)Project$Parent_initMeta;

    return pvt;
}


// fini function

void Project$Parent_fini(Project$Parent *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
urgc_set_field(self, (void**)&((Project$Parent*)self)->superTmp, NULL);

}

// init fields function


void Project$Parent_init_fields(Project$Parent *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Project$Parent_fini;
	//fields
    {
	((Project$Parent*)self)->superField = 0;
	urgc_set_field(self, (void**)&((Project$Parent*)self)->superTmp, NULL);
    }
	((Project$Parent*)self)->lala = (void*)Project$Parent$lala;
}

// init function

void Project$Parent_init(Project$Parent *self){
    Vtable_Project$Parent_init(&_vtable_Project$Parent);

    ((Object*)self)->vtable = (void*)&_vtable_Project$Parent;

    urgc_guard(self, (void*)orc_delete);

    Project$Parent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
Project$Parent * Project$Parent_new(){
    Project$Parent *self = calloc(1, sizeof(Project$Parent));
    Project$Parent_init(self);
    return self;
}


// class members
void  Project$Parent$lala(Project$Parent *  self){
	
}




//vtable instance
Vtable_Project$User _vtable_Project$User;

// init meta

void Project$User_initMeta(Vtable_Project$User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "age", OrcMetaType_int, offsetof(Project$User, age), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "tmp", ((Vtable_Object*)Vtable_Project$User_init(0)), offsetof(Project$User, tmp), true, false, 1);

	orc_metaField_method(&pNext, "say", offsetof(Project$User, say));
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
    Vtable_Project$Parent_init(&_vtable_Project$Parent);

	// init by super vtable init function
    Vtable_Project$Parent_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Project$Parent;
    ((Vtable_Object*)pvt)->make = (void*)&Project$User_new;
    ((Vtable_Object*)pvt)->className = "Project$User";

    ((Vtable_Object*)pvt)->initMeta = (void*)Project$User_initMeta;

    return pvt;
}


// fini function

void Project$User_fini(Project$User *self){
	//super fini
    Project$Parent_fini((Project$Parent *)self);

    //字段释放
urgc_set_field(self, (void**)&((Project$User*)self)->tmp, NULL);

}

// init fields function


void Project$User_init_fields(Project$User *self){
	//super class
    Project$Parent_init_fields((Project$Parent*)self);

    ((Object*)self)->fini = (void*)Project$User_fini;
	//fields
    {
	((Project$User*)self)->age = 2;
	urgc_set_field(self, (void**)&((Project$User*)self)->tmp, NULL);
    }
	((Project$User*)self)->say = (void*)Project$User$say;
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
void  Project$User$say(Project$User *  self){
	
}



void  Project$User$globalFn(Project$User *  self, Project$User*  xx){
	URGC_REF_ARG_WITH_CLEANUP(xx);

	
}

Project$User*  Project$User$returnRef(Project$User **  __outRef__, Project$User *  self, Project$User*  other){
	URGC_REF_ARG_WITH_CLEANUP(other);

	return urgc_set_var_for_return((void ** )__outRef__, NULL) ; 
}

int  Project$getMyAge(int  b){
	return b + 1; 
}

Project$User*  Project$createUser(Project$User **  __outRef__){
	return urgc_set_var_for_return((void ** )__outRef__, Project$User_new() ) ; 
}

void  Project$hi(){
	Project$User *  user;
	Project$User$globalFn(user) ;
	user->say(user) ;
	((Project$Parent * )user)->lala(user) ;
	URGC_VAR_CLEANUP Project$User*  tmpReturn_1 = NULL;
	Project$User$returnRef(&tmpReturn_1, user, NULL) ;
	URGC_VAR_CLEANUP Project$User*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP Project$User*  tmp = urgc_init_var((void**)&tmp, Project$createUser(&tmpReturn_2) );
	URGC_VAR_CLEANUP Project$User*  tmpReturn_3 = NULL;
	urgc_set_field(user, &user->tmp, Project$createUser(&tmpReturn_3) ) ;
	((Project$Parent * )user)->superField = 2;
	URGC_VAR_CLEANUP Project$User*  tmpReturn_4 = NULL;
	urgc_set_field(user, &((Project$Parent * )user)->superTmp, Project$createUser(&tmpReturn_4) ) ;
	Project$User *  tmpValue_5 = NULL;
	URGC_VAR_CLEANUP Project$User*  tmpReturn_6 = NULL;
	URGC_VAR_CLEANUP Project$User*  tmpReturn_7 = NULL;
	urgc_set_field(tmpValue_5 = Project$User$returnRef(&tmpReturn_6, user, user) , &tmpValue_5->tmp, Project$createUser(&tmpReturn_7) ) ;
	int  a = 1;
	int  age = a * 2 + 3 / (4 * 2 * Project$getMyAge(a) );
	char *  name = "zgww";
	unsigned int  ok = 10;
	unsigned long long  bigv = 10L;
	Project$printf("my name is :%s\n", name) ;
}



