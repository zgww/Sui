
//类型预声明，可以处理循环引用的问题
typedef struct tagTest$User Test$User;
typedef struct tagVtable_Test$User Vtable_Test$User;



#ifndef INCLUDE_ONLY_TYPE

#ifndef __test_orc_h__
#define __test_orc_h__

#include "Orc.h"
//package Test



#ifdef __cplusplus
extern "C"{
#endif




//虚表
// typedef struct tagVtable_Test$User Vtable_Test$User;
struct tagVtable_Test$User {
    Vtable_Object super;

};
//虚表实例
extern Vtable_Test$User _vtable_Test$User;

//数据表
struct tagTest$User{
    //父类
    Object super;
	void (*say)(Test$User * self);

};

//虚表初始化函数
Vtable_Test$User* Vtable_Test$User_init(Vtable_Test$User* pvt);
//初始化字段
void Test$User_init_fields(Test$User *self);

//初始化函数
void Test$User_init(Test$User *self);
Test$User * Test$User_new();
//释放
void Test$User_fini(Test$User *self);
// void Test$User_delete(Test$User **self);

//成员函数
void Test$User$say(Test$User * self);


void Test$testUser(Test$User * self);
void Test$printMyName();

#ifdef __cplusplus
}
#endif

#endif

#endif
