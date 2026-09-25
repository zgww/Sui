#include "./Math_orc.h"

#include "./String_orc.h"
#include <unordered_map>
#include <string>
#include <mutex>
#include <math.h>
//#include <unordered_set>


 
bool Orc$isNaN(float v){
   return isnan(v);
}

int Orc$floatSize(){
   return sizeof(float);
}
int Orc$doubleSize(){
   return sizeof(double);
}
int Orc$shortSize(){
   return sizeof(short);
}
int Orc$intSize(){
   return sizeof(int);
}
int Orc$longSize(){
   return sizeof(long);
}
int Orc$longLongSize(){
   return sizeof(long long);
}
float Orc$rand01f(){
   float b =rand()/(RAND_MAX+1.0);
   return b;
}
int Orc$pointerSize(){
   return sizeof(void*);
}