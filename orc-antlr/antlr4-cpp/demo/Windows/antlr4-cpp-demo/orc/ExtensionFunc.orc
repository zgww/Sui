package Project_Mod2;

#include "stdio.h"
//import * from './Mod.orc'

struct User{
    int age;
}



extension User {
    void sayInExt(){
    }
};

void call(){
    User*user;
    user.sayInExt();
}