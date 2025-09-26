
#include "Math_orc.h" 

#include <stdio.h>


// static struct 


// static function declaration


int  OrcLang$absInt(int  a){
	if (a < 0) {
		return -a; 
	}
	return a; 
}

float  OrcLang$absFloat(float  a){
	if (a < 0.0) {
		return -a; 
	}
	return a; 
}

int  OrcLang$minInt(int  a, int  b){
	if (a < b) {
		return a; 
	}
	return b; 
}

int  OrcLang$maxInt(int  a, int  b){
	if (a < b) {
		return b; 
	}
	return a; 
}

float  OrcLang$lerpFloat(float  f, float  t, float  r){
	return (t - f) * r + f; 
}

float  OrcLang$minFloat(float  a, float  b){
	if (a < b) {
		return a; 
	}
	return b; 
}

float  OrcLang$maxFloat(float  a, float  b){
	if (a < b) {
		return b; 
	}
	return a; 
}

float  OrcLang$clampInt(int  x, int  min, int  max){
	if (min >= max) {
		return min; 
	}
	if (x > max) {
		return max; 
	}
	if (x < min) {
		return min; 
	}
	return x; 
}

float  OrcLang$clampFloat(float  x, float  min, float  max){
	if (min >= max) {
		return min; 
	}
	if (x > max) {
		return max; 
	}
	if (x < min) {
		return min; 
	}
	return x; 
}

void  OrcLang$Math_test(){
	printf("max float:%f\n", OrcLang$maxFloat(10.f, 12.f) ) ;
}



