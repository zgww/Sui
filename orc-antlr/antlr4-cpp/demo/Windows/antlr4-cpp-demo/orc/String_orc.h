
//类型预声明，可以处理循环引用的问题
typedef struct tagOrcLang$String OrcLang$String;
typedef struct tagVtable_OrcLang$String Vtable_OrcLang$String;


#ifndef INCLUDE_ONLY_TYPE

#ifndef __String_orc_h__
#define __String_orc_h__

#include "Orc.h"
//package OrcLang
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#ifdef __cplusplus
extern "C"{
#endif




//虚表
// typedef struct tagVtable_OrcLang$String Vtable_OrcLang$String;
struct tagVtable_OrcLang$String {
    Vtable_Object super;

};
//虚表实例
extern Vtable_OrcLang$String _vtable_OrcLang$String;

//数据表
struct tagOrcLang$String{
    //父类
    Object super;
	int _size;
	char * data;
	void (*dtor)(OrcLang$String * self);
	OrcLang$String * (*add)(OrcLang$String * self, char const * str);
	int (*size)(OrcLang$String * self);
	void (*expand)(OrcLang$String * self, int needSize);

};

//虚表初始化函数
Vtable_OrcLang$String* Vtable_OrcLang$String_init(Vtable_OrcLang$String* pvt);
//初始化字段
void OrcLang$String_init_fields(OrcLang$String *self);

//初始化函数
void OrcLang$String_init(OrcLang$String *self);
OrcLang$String * OrcLang$String_new();
//释放
void OrcLang$String_fini(OrcLang$String *self);
// void OrcLang$String_delete(OrcLang$String **self);

//成员函数
void OrcLang$String$dtor(OrcLang$String * self);
OrcLang$String * OrcLang$String$add(OrcLang$String * self, char const * str);
int OrcLang$String$size(OrcLang$String * self);
void OrcLang$String$expand(OrcLang$String * self, int needSize);


OrcLang$String* OrcLang$str(OrcLang$String * * __outRef__, char const * data);

#ifdef __cplusplus
}
#endif

#endif

#endif
