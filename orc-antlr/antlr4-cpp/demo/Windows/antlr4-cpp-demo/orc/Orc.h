#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
// #include "urgc_api.h"

#ifdef __INTELLISENSE__
#define URGC_VAR_CLEANUP
#else
#define URGC_VAR_CLEANUP
#endif


#ifdef __cplusplus
extern "C"{
#endif

//表示此变量是引用类型
#define REF_TYPE



//虚表
typedef struct Vtable_Object Vtable_Object;
struct Vtable_Object {
    char flag[4];
    bool inited;
    Vtable_Object* super;//指向父虚表

} ;

//虚表实例
extern Vtable_Object _vtable_Object;

//数据表
typedef struct Object Object;
struct Object{
    //父类
    Vtable_Object *vtable;
    //清理函数，会调用dtor
    void (*fini)(Object *self);
    //析构函数 用户定义的
    void (*dtor)(Object *self);
};

//虚表初始化函数
void Vtable_Object_init(Vtable_Object* pvt);

// 结束处理
void Object_fini(Object *self);
// 初始化字段
void Object_init_fields(Object *self);
// 初始化对象
void Object_init(Object *self);
// 在堆上分配对象，并初始化
Object * Object_new();


//统一的清理和释放内存
void orc_delete(Object *self);

//用于__attribute__((cleanup(Orc_cleanup_ref))) 用来实现defer 解引用的效果
void Orc_cleanup_ref(void* p);


#ifdef __cplusplus
}
#endif
