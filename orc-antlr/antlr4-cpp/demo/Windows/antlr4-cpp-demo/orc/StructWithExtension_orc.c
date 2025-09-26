
#include "Orc.h"
#include "StructWithExtension_orc.h" 



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
    }
}
	void  Project_Mod$Main$sayhi(Project_Mod$Main *  self){

}



