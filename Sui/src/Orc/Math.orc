package Orc

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int absInt(int a){
    if (a < 0){
        return -a
    }
    return a;
}
float absFloat(float a){
    if (a < 0.0){
        return -a
    }
    return a;
}
int minInt(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

int maxInt(int a, int b){
    if (a < b){
        return b;
    }
    return a;
}


float calcRatio(float value, float left, float right){
    float range = right - left
    if range == 0.0 {
        return 1.0
    }
    return (value - left) / range
}

float lerpFloat(float f, float t, float r){
    return (t - f) * r + f
}


float minFloat(float a, float b){
    if (a < b){
        return a;
    }
    return b;
}

float maxFloat3(float a, float b, float c){
    float t = a > b ? a : b
    return t > c ? t : c;
}
float maxFloat(float a, float b){
    if (a < b){
        return b;
    }
    return a;
}
double minDouble(double a, double b){
    if (a < b){
        return a;
    }
    return b;
}

double maxDouble(double a, double b){
    if (a < b){
        return b;
    }
    return a;
}

float clampInt(int x, int min, int max){
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
float clampFloat(float x, float min, float max){
    if (min >= max) {
        return min;
        /*T tmp = min;
        min = max;
        max = tmp;*/
    }
    if (x > max) {
        return max;
    }
    if (x < min) {
        return min;
    }
    return x;
}
extern bool isNaN(float v);

float floorFloat(float v){
    return floor(v)
}

void Math_test(){
    printf("max float:%f\n", maxFloat(10.f, 12.f));
}


double EPSILON = 0.000000001

bool eqFloat(float a, float b){
    float d = a - b
    if d < 0 {
        d = -d
    }
    return d < EPSILON

}


const double LN2 = 0.6931471805599453
const double PI = 3.141592653589793

double toRad(double degree){
    return degree / 180.0 * PI
}
double toDeg(double rad){
    return rad / PI * 180.0
}


extern int doubleSize()
extern int floatSize()
extern int shortSize()
extern int intSize()
extern int longSize()
extern int longLongSize()
extern int pointerSize()

int randRange(int fromV, int toV){
    int v = rand() % (toV - fromV) + fromV
    return v
}
extern float rand01f()
float random(){
    return rand01f()
}
float randRangef(float fromV, float toV){
    float ratio = rand01f()
    // printf("randRangef ratio:%f\n", ratio)

    float v = ratio * (toV - fromV) + fromV
    return v
}
float randRadiusf(float radius){
    float v = randRangef(-radius, radius)
    return v
}


// compute euclidean modulo of m % n
// https://en.wikipedia.org/wiki/Modulo_operation
float euclideanModulo(float n, float m ) {

	return fmodf(( fmodf( n , m ) + m ) , m);

}

// Linear mapping from range <a1, a2> to range <b1, b2>
float mapLinear(float x, float a1, float a2, float b1, float b2 ) {

	return b1 + ( x - a1 ) * ( b2 - b1 ) / ( a2 - a1 );

}

// https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/inverse-lerp-a-super-useful-yet-often-overlooked-function-r5230/
float inverseLerp( float x,  float y, float value ) {

	if ( x != y ) {
		return ( value - x ) / ( y - x );

	} else {
		return 0;
	}

}

// http://www.rorydriscoll.com/2016/03/07/frame-rate-independent-damping-using-lerp/
float damp( float x, float y, float lambda, float dt ) {

	return lerpFloat( x, y, 1 - exp( - lambda * dt ) );

}

// https://www.desmos.com/calculator/vcsjnyz7x4
float pingpong(float x, float length  ) {
    //length defualt = 1

	return length - absFloat( euclideanModulo( x, length * 2 ) - length );

}

// http://en.wikipedia.org/wiki/Smoothstep
float smoothstep(float x, float min, float max ) {

	if ( x <= min ) {return 0;}
	if ( x >= max ) {return 1;}

	x = ( x - min ) / ( max - min );

	return x * x * ( 3 - 2 * x );

}

float smootherstep(float x, float min, float max ) {

	if ( x <= min ) {return 0;}
	if ( x >= max ) {return 1;}

	x = ( x - min ) / ( max - min );

	return x * x * x * ( x * ( x * 6 - 15 ) + 10 );

}


bool isPowerOfTwo(int value ) {

	return ( value & ( value - 1 ) ) == 0 && value != 0;

}

float ceilPowerOfTwo( float value ) {

	return pow( 2, ceil( log( value ) / LN2 ) );

}

float floorPowerOfTwo(float value ) {

	return pow( 2, floor( log( value ) / LN2 ) );

}