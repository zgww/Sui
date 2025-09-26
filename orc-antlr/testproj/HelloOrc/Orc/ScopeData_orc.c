
#include "ScopeData_orc.h" 



// static struct 


// static function declaration



// get or init meta 
MetaStruct* OrcLang$ScopeData_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "OrcLang$ScopeData", sizeof( OrcLang$ScopeData ));
        OrcMetaField **pNext = &meta->headMetaField;

		
    }
	return meta;
}
OrcLang$ScopeData OrcLang$mkScopeData(void *  data, void *  onExitScope){
	OrcLang$ScopeData ret;
	ret.data = data;
	ret.onExitScope = onExitScope;
	return ret; 
}



