
#include "callReturnStructExtension_orc.h" 

#include "./Struct_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Test$Vec3_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Test$Vec3", sizeof( Test$Vec3 ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "main", Project_Mod$Main_getOrInitMetaStruct(), offsetof(Test$Vec3, main), false, false, 0);
		orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(Test$Vec3, x), 0, 0, 0, 0);//float
    }
	return meta;
}
Test$Vec3 Test$mkVec3(){
	Test$Vec3 v;
	return v; 
}

Test$Vec3 Test$Vec3$print(Test$Vec3 *  self){
	return Test$mkVec3() ; 
}

Test$Vec3 Test$Vec3$gogo(Test$Vec3 *  self){
	return Test$mkVec3() ; 
}

void  Test$printMyName(){
	Test$Vec3 tmpStructThis1;
	Test$Vec3 tmpStructThis2;
	Test$Vec3$gogo((tmpStructThis1 = Test$Vec3$print((tmpStructThis2 = Test$mkVec3() ,&tmpStructThis2)) ,&tmpStructThis1)) ;
}



