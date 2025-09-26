
#include "Frustum_orc.h" 

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Mat_orc.h"
#include "./Mat3_orc.h"
#include "./Vec3_orc.h"
#include "./Plane_orc.h"
#include "./Spherical_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Frustum_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Frustum", sizeof( SuiCore$Frustum ));
        OrcMetaField **pNext = &meta->headMetaField;

		
    }
	return meta;
}


