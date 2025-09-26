
#include "Inset_orc.h" 

#include <stdlib.h>
#include <stdio.h>
#include "../../Orc/List_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Inset_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Inset", sizeof( SuiCore$Inset ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "left", OrcMetaType_float, offsetof(SuiCore$Inset, left), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "top", OrcMetaType_float, offsetof(SuiCore$Inset, top), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "right", OrcMetaType_float, offsetof(SuiCore$Inset, right), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "bottom", OrcMetaType_float, offsetof(SuiCore$Inset, bottom), 0, 0, 0, 0);//float
    }
	return meta;
}
void  SuiCore$Inset$setAll(SuiCore$Inset *  self, float  v){
	self->left = v;
	self->top = v;
	self->right = v;
	self->bottom = v;
}

void  SuiCore$Inset$setAxis(SuiCore$Inset *  self, float  v, float  h){
	self->left = h;
	self->right = h;
	self->top = v;
	self->bottom = v;
}

void  SuiCore$Inset$setHor(SuiCore$Inset *  self, float  v){
	self->left = v;
	self->right = v;
}

void  SuiCore$Inset$setVer(SuiCore$Inset *  self, float  v){
	self->top = v;
	self->bottom = v;
}

float  SuiCore$Inset$hor(SuiCore$Inset *  self){
	return self->left + self->right; 
}

float  SuiCore$Inset$ver(SuiCore$Inset *  self){
	return self->top + self->bottom; 
}

void  SuiCore$Inset$invert(SuiCore$Inset *  self){
	self->left = -self->left;
	self->top = -self->top;
	self->right = -self->right;
	self->bottom = -self->bottom;
}

SuiCore$Inset SuiCore$mkInset0(){
	SuiCore$Inset ret;
	ret.top = 0.0;
	ret.right = 0.0;
	ret.bottom = 0.0;
	ret.left = 0.0;
	return ret; 
}

SuiCore$Inset SuiCore$mkInset(float  t, float  r, float  b, float  l){
	SuiCore$Inset ret;
	ret.top = t;
	ret.right = r;
	ret.bottom = b;
	ret.left = l;
	return ret; 
}

void  SuiCore$testInset(){
	SuiCore$Inset inset = SuiCore$mkInset(1, 2, 3, 4) ;
	printf("inset:%f,%f,%f,%f\n", inset.top, inset.right, inset.bottom, inset.left) ;
	SuiCore$Inset$setAll(&inset, 1) ;
	printf("inset:%f,%f,%f,%f\n", inset.top, inset.right, inset.bottom, inset.left) ;
	SuiCore$Inset$setVer(&inset, 3) ;
	printf("inset:%f,%f,%f,%f\n", inset.top, inset.right, inset.bottom, inset.left) ;
	SuiCore$Inset$setHor(&inset, 4) ;
	printf("inset:%f,%f,%f,%f\n", inset.top, inset.right, inset.bottom, inset.left) ;
}



