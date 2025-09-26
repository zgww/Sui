#include <stdio.h>
#include <string.h>
#include "Main.h"

#ifdef GCC
#define CLEAN __attribute__ ((__cleanup__(destroy_string)))
#else
#define CLEAN
#endif

void main_sayhi(){
    printf("hi\n");
}
void main(){
    CLEAN int * data ;
    int *id;
    int v = 2 * *id;
    main_sayhi();
}