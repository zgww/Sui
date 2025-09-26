
#include "Bezier_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Vec2_orc.h"


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



