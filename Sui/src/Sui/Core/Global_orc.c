
#include "Global_orc.h" 

#include <stdlib.h>
#include <stdio.h>
#include "../../nanovg/nanovg.h"
#include "./Canvas_orc.h"


// static struct 


// static function declaration


static URGC_VAR_CLEANUP_CLASS SuiCore$Canvas*  canvas = NULL;
NVGcontext *  SuiCore$Global_getVg(){
	if (canvas) {
		return (NVGcontext * )canvas->data; 
	}
	return NULL; 
}

SuiCore$Canvas *  SuiCore$Global_getCanvas(){
	return canvas; 
}

void  SuiCore$Global_setCanvas(SuiCore$Canvas *  c){
	urgc_set_var_class(&canvas, c) ;
}

void  SuiCore$testGlobal(){
	printf("getVg:%p\n", SuiCore$Global_getVg() ) ;
}



