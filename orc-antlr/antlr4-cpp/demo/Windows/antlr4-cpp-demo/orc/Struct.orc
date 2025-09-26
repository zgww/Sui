package Project_Mod;

//#include "stdio.h"
//import * from 'Mod'



struct Main{
    int a;
    int b;
    char *data;
    bool isUser;
};


struct User{
    int a;
    int b;
    char *data;
    bool isUser;
    Main@ main;
};


/*
extension Main {
    void sayhi(){

    }
}
*/