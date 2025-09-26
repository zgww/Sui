
#include "Mat2d_orc.h" 

#include <stdio.h>
#include "./Node_orc.h"
#include "./Rect_orc.h"
#include "../../Orc/String_orc.h"
#include "./Vec2_orc.h"
#include "./Vec3_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Mat2d_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Mat2d", sizeof( SuiCore$Mat2d ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "data", OrcMetaType_float, offsetof(SuiCore$Mat2d, data), 0, 0, 1, 1);//float
    }
	return meta;
}
SuiCore$Mat2d SuiCore$Mat2d$inverseNew(SuiCore$Mat2d *  self){
	SuiCore$Mat2d m = *self;
	SuiCore$Mat2d$inverse(&m) ;
	return m; 
}

SuiCore$Vec3 SuiCore$Mat2d$localToLocal(SuiCore$Mat2d *  self, SuiCore$Mat2d *  invMat2d, float  x, float  y, float  z){
	SuiCore$Vec3 worldPos = SuiCore$Mat2d$transformPoint(self, x, y, z) ;
	SuiCore$Vec3 ret = SuiCore$Mat2d$transformPoint(invMat2d, worldPos.x, worldPos.y, worldPos.z) ;
	return ret; 
}

void  SuiCore$testMat2d(){
	SuiCore$Mat2d m = SuiCore$mkMat2d() ;
	SuiCore$Vec3 p = SuiCore$Mat2d$transformPoint(&m, 10.f, 10.f, 0.f) ;
	printf("2应用变换:%f, %f\n", p.x, p.y) ;
	SuiCore$Mat2d$translate(&m, 10.f, 1.f, 0.f) ;
	p = SuiCore$Mat2d$transformPoint(&m, 10.f, 10.f, 0.f) ;
	printf("2应用变换:%f, %f\n", p.x, p.y) ;
	SuiCore$Mat2d$scale(&m, 3.f, 3.f, 1.f) ;
	p = SuiCore$Mat2d$transformPoint(&m, 10.f, 10.f, 0.f) ;
	printf("2应用变换:%f, %f\n", p.x, p.y) ;
}



