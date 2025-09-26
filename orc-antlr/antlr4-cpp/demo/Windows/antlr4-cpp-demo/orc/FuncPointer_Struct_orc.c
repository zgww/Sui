
#include "Orc.h"
#include "FuncPointer_Struct_orc.h" 



// static struct 


// static function declaration



// get or init meta 
MetaStruct* Project_Mod$Father_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Project_Mod$Father", sizeof( Project_Mod$Father ));
        OrcMetaField **pNext = &meta->headMetaField;

		
    }
}
	
// get or init meta 
MetaStruct* Project_Mod$User_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Project_Mod$User", sizeof( Project_Mod$User ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "p", Project_Mod$Father_getOrInitMetaStruct(), offsetof(Project_Mod$User, p), false, true, 1);
		orc_metaField_struct(&pNext, "p2", Project_Mod$Father_getOrInitMetaStruct(), offsetof(Project_Mod$User, p2), false, false, 0);
    }
}
	void  Project_Mod$main(){
	Project_Mod$Father f;
	f.hi() ;
}



