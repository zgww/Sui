
#include "Screen_orc.h" 

#include <stdio.h>
#include "./Vec2_orc.h"


// static struct 


// static function declaration


void  SuiCore$testScreen(){
	SuiCore$Vec2 usableSize = SuiCore$Screen_get_usable_size() ;
	SuiCore$Vec2 size = SuiCore$Screen_get_size() ;
	printf("usable size:%f, %f; size:%f, %f\n", usableSize.x, usableSize.y, size.x, size.y) ;
}



