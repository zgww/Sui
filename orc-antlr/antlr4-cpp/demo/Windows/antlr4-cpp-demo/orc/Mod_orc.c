
#include "Orc.h"
#include "Mod_orc.h" 



// static struct 


// static function declaration



//vtable instance
Vtable_Project_Mod$User _vtable_Project_Mod$User;

// init meta

void Project_Mod$User_initMeta(Vtable_Project_Mod$User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "age", OrcMetaType_int, offsetof(Project_Mod$User, age), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "name", OrcMetaType_char, offsetof(Project_Mod$User, name), 0, 0, 1, 1);//char

	orc_metaField_method(&pNext, "printInfo", offsetof(Project_Mod$User, printInfo));
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
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Project_Mod$User_new;
    ((Vtable_Object*)pvt)->className = "Project_Mod$User";

    ((Vtable_Object*)pvt)->initMeta = (void*)Project_Mod$User_initMeta;

    return pvt;
}


// fini function

void Project_Mod$User_fini(Project_Mod$User *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Project_Mod$User_init_fields(Project_Mod$User *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Project_Mod$User_fini;
	//fields
    {
	((Project_Mod$User*)self)->name = "skdfj";
    }
	((Project_Mod$User*)self)->printInfo = (void*)Project_Mod$User$printInfo;
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
void  Project_Mod$User$printInfo(Project_Mod$User *  self){
	
}




// get or init meta 
MetaStruct* Project_Mod$AVFrame_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Project_Mod$AVFrame", sizeof( Project_Mod$AVFrame ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "nbytes", OrcMetaType_int, offsetof(Project_Mod$AVFrame, nbytes), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "data", OrcMetaType_char, offsetof(Project_Mod$AVFrame, data), 0, 0, 1, 1);//char
    }
}
	int  user;
void  Project_Mod$sayok(){
	
}

void  Project_Mod$gogogo(){
	
}

Project_Mod$AVFrame Project_Mod$mkFrame(){
	
}



