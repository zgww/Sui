
#include "Bezier_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Vec2_orc.h"
#include "../../Orc/String_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Bezier_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Bezier", sizeof( SuiCore$Bezier ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_struct(&pNext, "start", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiCore$Bezier, start), false, false, 0);
		orc_metaField_struct(&pNext, "c0", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiCore$Bezier, c0), false, false, 0);
		orc_metaField_struct(&pNext, "c1", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiCore$Bezier, c1), false, false, 0);
		orc_metaField_struct(&pNext, "end", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiCore$Bezier, end), false, false, 0);
    }
	return meta;
}
SuiCore$Bezier SuiCore$mkBezier(){
	SuiCore$Vec2 start = SuiCore$mkVec2(0.0, 0.0) ;
	SuiCore$Vec2 c0 = SuiCore$mkVec2(0.25, 0.5) ;
	SuiCore$Vec2 c1 = SuiCore$mkVec2(0.75, 0.5) ;
	SuiCore$Vec2 end = SuiCore$mkVec2(1.0, 1.0) ;
	SuiCore$Bezier b;
	b.start = start;
	b.c0 = c0;
	b.c1 = c1;
	b.end = end;
	return b; 
}

Orc$String*  SuiCore$Bezier$toString(Orc$String **  __outRef__, SuiCore$Bezier *  self){
	char  tmp[256];
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
	sprintf(tmp, "Bezier(%s,%s,%s,%s)", SuiCore$Vec2$toString(&tmpReturn_1, &self->start) ->str, SuiCore$Vec2$toString(&tmpReturn_2, &self->c0) ->str, SuiCore$Vec2$toString(&tmpReturn_3, &self->c1) ->str, SuiCore$Vec2$toString(&tmpReturn_4, &self->end) ->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_5, tmp) ) ; 
}



