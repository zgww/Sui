package Project

#include "stdio.h"
void printf(){}

void main(){
    printf("hello world\n");
}


class Parent {
    int superField = 0;
    User@ superTmp;
    void lala(){

    }
}
class User extends Parent{
    int age = 2;
    User@ tmp;
    void say(){
    }
}
extension User {
    void globalFn(User@ xx){
    }
    User@ returnRef(User@ other){
        return null;
    }
}

int getMyAge(int b){
    return b + 1;
}
User@ createUser(){
    return new User()
}
void hi(){
    User *user;
    user->globalFn(); //扩展函数
    user->say(); //成员函数
    user->lala(); //继承的函数

    user->returnRef(null);

    User@ tmp = createUser();
    user->tmp = createUser();
    user->superField = 2;
    user->superTmp = createUser();
    user->returnRef(user)->tmp = createUser();

    int a = 1;
    int age = a * 2 + 3 / (4  * 2 * getMyAge(a));
    char *name = "zgww";
    unsigned int ok = 10;
    unsigned long long bigv = 10L
    printf("my name is :%s\n", name)
}