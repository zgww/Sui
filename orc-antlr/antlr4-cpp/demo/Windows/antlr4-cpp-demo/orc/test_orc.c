#include "Orc.h"
#include "./test_orc.h"
//package Test


// #include <stdio.h>
// class Parent {
//     int box = 10;
//     void print(){
//         printf("i'm parent. my box is :%d. my age is :\n", self->box);
//     }
// }
// class User extends Parent {
//     // int box= 10;
//     int age = 10;
//     char *name = "zgww";
//     void print(){
//         super->print();
//         super.print();
//         printf("my name is :%s. my age is :%d box:%d\n", self->name, self->age, self->box);
//     }
// }
// static void stSay(){
// }



//虚表实例
Vtable_Test$User _vtable_Test$User;


//虚表初始化函数
 Vtable_Test$User* Vtable_Test$User_init(Vtable_Test$User* pvt){
    if (pvt == NULL){ //未指定变量
        pvt = &_vtable_Test$User;
    }
    //已经初始化
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }

    //确保父虚表实例已经初始化
    Vtable_Object_init(&_vtable_Object);


    //父虚表初始化
    Vtable_Object_init((void*)pvt);

    //虚表赋值
    //记录虚表的父
    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Test$User_new;
    ((Vtable_Object*)pvt)->className = "Test$User";

    return pvt;
}

//释放
void Test$User_fini(Test$User *self){
    //调用父类析构函数，根Object_fini会调用dtor成员函数
    Object_fini((Object *)self);

    //字段释放
    

    // return self;
}


//初始化字段
void Test$User_init_fields(Test$User *self){
    //父类初始化字段
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Test$User_fini;

    {
        
    }
    ((Test$User*)self)->say = (void*)&Test$User$say;
}
//初始化函数
void Test$User_init(Test$User *self){
    //虚表初始化
    Vtable_Test$User_init(&_vtable_Test$User);

    //初始化虚表指针
    ((Object*)self)->vtable = (void*)&_vtable_Test$User;

    //urgc保护指针，防止循环
    urgc_guard(self, (void*)orc_delete);

    //初始化字段
    Test$User_init_fields(self);

    //调用构造函数
    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}
Test$User * Test$User_new(){
    Test$User *self = calloc(1, sizeof(Test$User));
    Test$User_init(self);
    return self;
}



//成员函数
[object Promise]


void Test$testUser(Test$User * self) {
    
}
void Test$printMyName() {
    Test$User * user = Test$User_new();
    //&user => new User()
    URGC_VAR_CLEANUP Test$User* user = urgc_init_var((void**)&user, Test$User_new());
    user.say(user);
    Test$testUser(user);
    Test$testUser(user);
    user.say(user);
    user.say(user);
    user->say(user);
    //char data[100][10];
    //data[0][0] = 10;
    //data[1][0] = 10;
    //data[2][0] = 10;
    //data[3][0] = 10;
    // User@ user = new User();
    // user->print();
    // user->name = "new name";
    // user->print();
    // stSay();
}