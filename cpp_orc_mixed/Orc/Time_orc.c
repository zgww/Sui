
#include "Time_orc.h" 

#include <stdio.h>


// static struct 


// static function declaration


void  Orc$Time_sleepSec(float  sec){
	Orc$Time_sleepMs(sec * 1000) ;
}

long long  Orc$Time_unixSec(){
	long long  ms = Orc$Time_unixMs() ;
	long long  sec = ms / 1000;
	return sec; 
}

void  Orc$Time_test(){
	printf("now ms:%lld\n", Orc$Time_unixMs() ) ;
	Orc$Time_sleepMs(1000) ;
	printf("中文now ms:%lld\n", Orc$Time_unixMs() ) ;
}



