package Project_Mod;

#include "stdio.h"
import * from 'Mod'


enum UserType {
    UserType_DoIt,
    UserType_DoIt2,
}

struct User{
    int age;
    bool isMale;
    int *p_age;
}

extension User {
    void say(){
    }
    void print(){
    }
}

int age = 0

static bool nice = false
static void staticSay(){
    
}


void say(){

}