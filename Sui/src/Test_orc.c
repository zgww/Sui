
#include "Test_orc.h" 

#include <stdio.h>
#include <stdio.h>
#include "../UrgcDll/urgc_api.h"
#include "Orc/Orc.h"


// static struct 


// static function declaration


void  initMain(){
	urgc_start_process_thread() ;
}

int  main(){
	initMain() ;
	windowInit() ;
	testWindow() ;
	printf("glewINit:%d\n", 1) ;
	getchar() ;
	return 0; 
}



