
#include "Time_orc.h" 

#include <stdio.h>


// static struct 


// static function declaration


long long  OrcLang$Time_unixSec(){
	long long  ms = OrcLang$Time_unixMs() ;
	long long  sec = ms / 1000;
	return sec; 
}

void  OrcLang$Time_test(){
	printf("now ms:%lld\n", OrcLang$Time_unixMs() ) ;
	OrcLang$Time_sleepMs(1000) ;
	printf("中文now ms:%lld\n", OrcLang$Time_unixMs() ) ;
}



