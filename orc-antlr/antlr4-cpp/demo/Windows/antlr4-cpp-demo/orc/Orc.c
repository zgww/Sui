#include <stdio.h>
#include <stdbool.h>
#include "./Orc.h"



//虚表实例
Vtable_Object __vtable_Object;

//虚表初始化函数
void Vtable_Object_init(Vtable_Object* pvt){
    //已经初始化
    if (((Vtable_Object*)pvt)->inited){
        return;
    }
    //虚表赋值
    // char flag[4] = "ORCO";
    pvt->flag[0] = 'O';
    pvt->flag[1] = 'R';
    pvt->flag[2] = 'C';
    pvt->flag[3] = 'O';
    pvt->inited = true;
}

// 结束处理
void Object_fini(Object *this){
    if (this->dtor){
        this->dtor(this);
    }

    //调用父类清理函数

    //字段清理
}
void Object_init_fields(Object *this){
    this->fini = Object_fini;
    // this->dtor = Object_dtor;
}
void Object_init(Object *this){
    //虚表初始化
    Vtable_Object_init(&__vtable_Object);
    //虚表指针初始化
    this->vtable = &__vtable_Object;

    //urgc保护指针，防止循环
    urgc_guard(this);

    //成员初始化
    Object_init_fields(this);

    urgc_deguard(this);
}
Object * Object_new(){
    Object *this = calloc(sizeof(Object));
    Object_init(this);

    return this;
}
//统一的清理和释放内存
void orc_delete(Object **pthis){
    Object*this = *pthis;
    this->fini(this);

    free(this);
    *pthis = NULL;
}