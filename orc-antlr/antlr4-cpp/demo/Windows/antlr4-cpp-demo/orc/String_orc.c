#include "Orc.h"
#include "./String_orc.h"
//package OrcLang
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//字符串需要用对象管理起来
//直接用char@ xx = ""  会导致内存异常释放



//虚表实例
Vtable_OrcLang$String _vtable_OrcLang$String;


//虚表初始化函数
 Vtable_OrcLang$String* Vtable_OrcLang$String_init(Vtable_OrcLang$String* pvt){
    if (pvt == NULL){ //未指定变量
        pvt = &_vtable_OrcLang$String;
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
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$String_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$String";

    return pvt;
}

//释放
void OrcLang$String_fini(OrcLang$String *self){
    //调用父类析构函数，根Object_fini会调用dtor成员函数
    Object_fini((Object *)self);

    //字段释放
    

    // return self;
}


//初始化字段
void OrcLang$String_init_fields(OrcLang$String *self){
    //父类初始化字段
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)OrcLang$String_fini;

    {
        ((OrcLang$String*)self)->_size= -1;
        ((OrcLang$String*)self)->data= NULL;
    }
    ((Object*)self)->dtor = (void*)&OrcLang$String$dtor;
    ((OrcLang$String*)self)->add = (void*)&OrcLang$String$add;
    ((OrcLang$String*)self)->size = (void*)&OrcLang$String$size;
    ((OrcLang$String*)self)->expand = (void*)&OrcLang$String$expand;
}
//初始化函数
void OrcLang$String_init(OrcLang$String *self){
    //虚表初始化
    Vtable_OrcLang$String_init(&_vtable_OrcLang$String);

    //初始化虚表指针
    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$String;

    //urgc保护指针，防止循环
    urgc_guard(self, (void*)orc_delete);

    //初始化字段
    OrcLang$String_init_fields(self);

    //调用构造函数
    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}
OrcLang$String * OrcLang$String_new(){
    OrcLang$String *self = calloc(1, sizeof(OrcLang$String));
    OrcLang$String_init(self);
    return self;
}



//成员函数
[object Promise]
[object Promise]
[object Promise]
[object Promise]


OrcLang$String* OrcLang$str(OrcLang$String * * __outRef__, char const * data) {
    URGC_VAR_CLEANUP OrcLang$String* ret = urgc_init_var((void**)&ret, OrcLang$String_new());
    ret.add(ret, data);
    return urgc_set_var_for_return((void**)__outRef__, ret);
}