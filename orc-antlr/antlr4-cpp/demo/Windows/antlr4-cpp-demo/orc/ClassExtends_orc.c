
#include "Orc.h"
#include "ClassExtends_orc.h" 



// static struct 


// static function declaration



//vtable instance
Vtable_Project_Mod$Parent _vtable_Project_Mod$Parent;

// init meta

void Project_Mod$Parent_initMeta(Vtable_Project_Mod$Parent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "age", OrcMetaType_int, offsetof(Project_Mod$Parent, age), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "say", offsetof(Project_Mod$Parent, say));
	orc_metaField_method(&pNext, "say2", offsetof(Project_Mod$Parent, say2));
}


// vtable init


Vtable_Project_Mod$Parent* Vtable_Project_Mod$Parent_init(Vtable_Project_Mod$Parent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Project_Mod$Parent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Project_Mod$Parent_new;
    ((Vtable_Object*)pvt)->className = "Project_Mod$Parent";

    ((Vtable_Object*)pvt)->initMeta = (void*)Project_Mod$Parent_initMeta;

    return pvt;
}


// fini function

void Project_Mod$Parent_fini(Project_Mod$Parent *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Project_Mod$Parent_init_fields(Project_Mod$Parent *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Project_Mod$Parent_fini;
	//fields
    {
	((Project_Mod$Parent*)self)->age = 10;
    }
	((Project_Mod$Parent*)self)->say = (void*)&Project_Mod$Parent$say;
	((Project_Mod$Parent*)self)->say2 = (void*)&Project_Mod$Parent$say2;
}

// init function

void Project_Mod$Parent_init(Project_Mod$Parent *self){
    Vtable_Project_Mod$Parent_init(&_vtable_Project_Mod$Parent);

    ((Object*)self)->vtable = (void*)&_vtable_Project_Mod$Parent;

    urgc_guard(self, (void*)orc_delete);

    Project_Mod$Parent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
Project_Mod$Parent * Project_Mod$Parent_new(){
    Project_Mod$Parent *self = calloc(1, sizeof(Project_Mod$Parent));
    Project_Mod$Parent_init(self);
    return self;
}


// class members
void  Project_Mod$Parent$say(Project_Mod$Parent *  self){
	
}


void  Project_Mod$Parent$say2(Project_Mod$Parent *  self){
	
}




//vtable instance
Vtable_Project_Mod$User _vtable_Project_Mod$User;

// init meta

void Project_Mod$User_initMeta(Vtable_Project_Mod$User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "level", OrcMetaType_int, offsetof(Project_Mod$User, level), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "name", OrcMetaType_char, offsetof(Project_Mod$User, name), 0, 0, 1, 1);//char
	orc_metaField_primitive(&pNext, "hint", OrcMetaType_char, offsetof(Project_Mod$User, hint), 0, 0, 1, 1);//char

	orc_metaField_method(&pNext, "say3", offsetof(Project_Mod$User, say3));
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
    Vtable_Project_Mod$Parent_init(&_vtable_Project_Mod$Parent);

	// init by super vtable init function
    Vtable_Project_Mod$Parent_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Project_Mod$Parent;
    ((Vtable_Object*)pvt)->make = (void*)&Project_Mod$User_new;
    ((Vtable_Object*)pvt)->className = "Project_Mod$User";

    ((Vtable_Object*)pvt)->initMeta = (void*)Project_Mod$User_initMeta;

    return pvt;
}


// fini function

void Project_Mod$User_fini(Project_Mod$User *self){
	//super fini
    Project_Mod$Parent_fini((Project_Mod$Parent *)self);

    //字段释放


}

// init fields function


void Project_Mod$User_init_fields(Project_Mod$User *self){
	//super class
    Project_Mod$Parent_init_fields((Project_Mod$Parent*)self);

    ((Object*)self)->fini = (void*)Project_Mod$User_fini;
	//fields
    {
	((Project_Mod$User*)self)->level = 3;
	((Project_Mod$User*)self)->hint = "hi";
    }
	((Project_Mod$Parent*)self)->say = (void*)&Project_Mod$User$say;
	((Project_Mod$Parent*)self)->say2 = (void*)&Project_Mod$User$say2;
	((Project_Mod$User*)self)->say3 = (void*)&Project_Mod$User$say3;
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
void  Project_Mod$User$say(Project_Mod$User *  self){
	
}


void  Project_Mod$User$say2(Project_Mod$User *  self){
	
}


int  Project_Mod$User$say3(Project_Mod$User *  self){
	
}





