package OrcLang

#include <stdio.h>


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

float lerpFloat(float f, float t, float r){
    return (t - f) * r + f
}


float minFloat(float a, float b){
    if (a < b){
        return a;
    }
    return b;
}

float maxFloat(float a, float b){
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

void Math_test(){
    printf("max float:%f\n", maxFloat(10.f, 12.f));
}

