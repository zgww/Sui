
#include "Clipboard_orc.h" 

#include <stdio.h>
#include "../../Orc/String_orc.h"


// static struct 


// static function declaration


void  SuiCore$testClipboard(){
	URGC_VAR_CLEANUP_CLASS Orc$String*  text = SuiCore$clipboard_getText((text = NULL,&text)) ;
	printf("clipboard:%s\n", text->str) ;
	SuiCore$clipboard_setText("hi") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  text2 = SuiCore$clipboard_getText((text2 = NULL,&text2)) ;
	printf("clipboard2??:%s\n", text2->str) ;
}



