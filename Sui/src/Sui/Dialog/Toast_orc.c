
#include "Toast_orc.h" 

#include "./MessageDialog_orc.h"


// static struct 


// static function declaration


void  SuiDialog$Toast_make(const char *  label){
	SuiDialog$MessageDialog_alert(label, "提示") ;
}

void  SuiDialog$testToast(){
	SuiDialog$Toast_make("你好") ;
}



