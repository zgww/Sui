
#include "ScopeData_orc.h" 



// static struct 


// static function declaration



// get or init meta 
MetaStruct* Orc$ScopeData_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Orc$ScopeData", sizeof( Orc$ScopeData ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "data", OrcMetaType_void, offsetof(Orc$ScopeData, data), 0, 0, 1, 1);//void
		orc_metaField_primitive(&pNext, "onExitScope", OrcMetaType_void, offsetof(Orc$ScopeData, onExitScope), 0, 0, 1, 1);//void
    }
	return meta;
}
Orc$ScopeData Orc$mkScopeData(void *  data, void *  onExitScope){
	Orc$ScopeData ret;
	ret.data = data;
	ret.onExitScope = onExitScope;
	return ret; 
}



