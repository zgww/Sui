
#include "Orc.h"
#include "ExtensionFunc_orc.h" 

#include "stdio.h";


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Project_Mod2$User_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Project_Mod2$User", sizeof( Project_Mod2$User ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "age", OrcMetaType_int, offsetof(Project_Mod2$User, age), 0, 0, 0, 0);//int
    }
}
	void  Project_Mod2$User$sayInExt(Project_Mod2$User *  self){
	
}

void  Project_Mod2$call(){
	Project_Mod2$User *  user;
	Project_Mod2$User$sayInExt(user) ;
}



