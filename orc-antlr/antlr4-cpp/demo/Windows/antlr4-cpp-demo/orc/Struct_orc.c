
#include "Orc.h"
#include "Struct_orc.h" 



// static struct 


// static function declaration



// get or init meta 
MetaStruct* Project_Mod$Main_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Project_Mod$Main", sizeof( Project_Mod$Main ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "a", OrcMetaType_int, offsetof(Project_Mod$Main, a), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "b", OrcMetaType_int, offsetof(Project_Mod$Main, b), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "data", OrcMetaType_char, offsetof(Project_Mod$Main, data), 0, 0, 1, 1);//char
		orc_metaField_primitive(&pNext, "isUser", OrcMetaType_bool, offsetof(Project_Mod$Main, isUser), 0, 0, 0, 0);//bool
    }
}
	
// get or init meta 
MetaStruct* Project_Mod$User_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Project_Mod$User", sizeof( Project_Mod$User ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "a", OrcMetaType_int, offsetof(Project_Mod$User, a), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "b", OrcMetaType_int, offsetof(Project_Mod$User, b), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "data", OrcMetaType_char, offsetof(Project_Mod$User, data), 0, 0, 1, 1);//char
		orc_metaField_primitive(&pNext, "isUser", OrcMetaType_bool, offsetof(Project_Mod$User, isUser), 0, 0, 0, 0);//bool
		orc_metaField_struct(&pNext, "main", Project_Mod$Main_getOrInitMetaStruct(), offsetof(Project_Mod$User, main), true, false, 1);
    }
}
	

