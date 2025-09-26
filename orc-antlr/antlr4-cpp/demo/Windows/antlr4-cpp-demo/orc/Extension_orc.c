
#include "Orc.h"
#include "Extension_orc.h" 



// static struct 


// static function declaration



// get or init meta 
MetaStruct* Project_Mod$User_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Project_Mod$User", sizeof( Project_Mod$User ));
        OrcMetaField **pNext = &meta->headMetaField;

		
    }
}
	

