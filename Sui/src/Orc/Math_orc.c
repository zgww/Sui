
#include "Math_orc.h" 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// static struct 


// static function declaration


int  Orc$absInt(int  a){
	if (a < 0) {
		return -a; 
	}
	return a; 
}

float  Orc$absFloat(float  a){
	if (a < 0.0) {
		return -a; 
	}
	return a; 
}

int  Orc$minInt(int  a, int  b){
	if (a < b) {
		return a; 
	}
	return b; 
}

int  Orc$maxInt(int  a, int  b){
	if (a < b) {
		return b; 
	}
	return a; 
}

float  Orc$calcRatio(float  value, float  left, float  right){
	float  range = right - left;
	if (range == 0.0) {
		return 1.0; 
	}
	return (value - left) / range; 
}

float  Orc$lerpFloat(float  f, float  t, float  r){
	return (t - f) * r + f; 
}

float  Orc$minFloat(float  a, float  b){
	if (a < b) {
		return a; 
	}
	return b; 
}

float  Orc$maxFloat3(float  a, float  b, float  c){
	float  t = a > b ? a : b;
	return t > c ? t : c; 
}

float  Orc$maxFloat(float  a, float  b){
	if (a < b) {
		return b; 
	}
	return a; 
}

double  Orc$minDouble(double  a, double  b){
	if (a < b) {
		return a; 
	}
	return b; 
}

double  Orc$maxDouble(double  a, double  b){
	if (a < b) {
		return b; 
	}
	return a; 
}

float  Orc$clampInt(int  x, int  min, int  max){
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

float  Orc$clampFloat(float  x, float  min, float  max){
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

float  Orc$floorFloat(float  v){
	return floor(v) ; 
}

void  Orc$Math_test(){
	printf("max float:%f\n", Orc$maxFloat(10.f, 12.f) ) ;
}

double  Orc$EPSILON = 0.000000001;
bool  Orc$eqFloat(float  a, float  b){
	float  d = a - b;
	if (d < 0) {
		d = -d;
	}
	return d < Orc$EPSILON; 
}

const double  Orc$LN2 = 0.6931471805599453;
const double  Orc$PI = 3.141592653589793;
double  Orc$toRad(double  degree){
	return degree / 180.0 * Orc$PI; 
}

double  Orc$toDeg(double  rad){
	return rad / Orc$PI * 180.0; 
}

int  Orc$randRange(int  fromV, int  toV){
	int  v = rand()  % (toV - fromV) + fromV;
	return v; 
}

float  Orc$random(){
	return Orc$rand01f() ; 
}

float  Orc$randRangef(float  fromV, float  toV){
	float  ratio = Orc$rand01f() ;
	float  v = ratio * (toV - fromV) + fromV;
	return v; 
}

float  Orc$randRadiusf(float  radius){
	float  v = Orc$randRangef(-radius, radius) ;
	return v; 
}

float  Orc$euclideanModulo(float  n, float  m){
	return fmodf((fmodf(n, m)  + m), m) ; 
}

float  Orc$mapLinear(float  x, float  a1, float  a2, float  b1, float  b2){
	return b1 + (x - a1) * (b2 - b1) / (a2 - a1); 
}

float  Orc$inverseLerp(float  x, float  y, float  value){
	if (x != y) {
		return (value - x) / (y - x); 
	}
	else {
		return 0; 
	}
}

float  Orc$damp(float  x, float  y, float  lambda, float  dt){
	return Orc$lerpFloat(x, y, 1 - exp(-lambda * dt) ) ; 
}

float  Orc$pingpong(float  x, float  length){
	return length - Orc$absFloat(Orc$euclideanModulo(x, length * 2)  - length) ; 
}

float  Orc$smoothstep(float  x, float  min, float  max){
	if (x <= min) {
		return 0; 
	}
	if (x >= max) {
		return 1; 
	}
	x = (x - min) / (max - min);
	return x * x * (3 - 2 * x); 
}

float  Orc$smootherstep(float  x, float  min, float  max){
	if (x <= min) {
		return 0; 
	}
	if (x >= max) {
		return 1; 
	}
	x = (x - min) / (max - min);
	return x * x * x * (x * (x * 6 - 15) + 10); 
}

bool  Orc$isPowerOfTwo(int  value){
	return (value & (value - 1)) == 0 && value != 0; 
}

float  Orc$ceilPowerOfTwo(float  value){
	return pow(2, ceil(log(value)  / Orc$LN2) ) ; 
}

float  Orc$floorPowerOfTwo(float  value){
	return pow(2, floor(log(value)  / Orc$LN2) ) ; 
}



