
#include "Orc.h"
#include "StructFields_orc.h" 

#include "stdio.h";
#include "missing StringLit_orc.h";


// static struct 


// static function declaration
static void  staticSay();



// get or init meta 
MetaStruct* Project_Mod$User_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Project_Mod$User", sizeof( Project_Mod$User ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "age", OrcMetaType_int, offsetof(Project_Mod$User, age), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "isMale", OrcMetaType_bool, offsetof(Project_Mod$User, isMale), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "p_age", OrcMetaType_int, offsetof(Project_Mod$User, p_age), 0, 0, 1, 1);//int
    }
}
	void  Project_Mod$User$say(Project_Mod$User *  self){

}

void  Project_Mod$User$print(Project_Mod$User *  self){

}

int  age = 0;
static static bool  nice = false;
static void  staticSay(){

}

void  Project_Mod$say(){

}



