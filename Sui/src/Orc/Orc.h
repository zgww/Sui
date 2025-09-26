#pragma once


#include "../../UrgcDll/urgc_api.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdatomic.h>

// #ifndef infinity
// #define infinity INFINITY
// #endif
// #ifndef nan
// #define nan NAN
// #endif

#define NEW_CLASS_VAR(TYPE, VAR) URGC_VAR_CLEANUP TYPE* VAR = (VAR=NULL,TYPE##_new(&VAR))

#define URGC_NEW_VAR(TYPE, VAR, INIT) URGC_VAR_CLEANUP TYPE VAR = (TYPE) urgc_init_var_class((void**)&VAR, INIT)
#define URGC_RETURN_CLASS(VAR) urgc_set_var_for_return_class((void**)__outRef__, (Object*)VAR)
#define URGC_REF_ARG_WITH_CLEANUP_CLASS(value) URGC_VAR_CLEANUP void* ARG_SCOPE() = urgc_init_var_class(&ARG_SCOPE(), (value))

// 类有另外的cleanup。 因为有refc
#define URGC_VAR_CLEANUP_CLASS  __attribute__((cleanup(urgc_refvar_cleanup_class)))

#define metaStructOf(name) name##_getOrInitMetaStruct()

#ifdef __cplusplus
extern "C"{
#endif


//#define INSTANCE_OF(ins, type) Orc_instanceof((Object*)(void*)ins, (Vtable_Object*)&_vtable_##type)

typedef struct tagOrcMetaField OrcMetaField;
typedef struct tagObject Object;
typedef struct tagMetaStruct MetaStruct;
//虚表
typedef struct tagVtable_Object Vtable_Object;
struct tagVtable_Object {
    char flag[4];
    bool inited;
    bool refc; //是否使用引用计数
    const char* className;
    Vtable_Object* super;//指向父虚表


    Object* (*make)(void *pOwner); //创建实例

    //反射信息
    OrcMetaField *headMetaField;//不含父类的。
    void (*initMeta)(Vtable_Object *vt);//初始化元数据
} ;

//虚表实例
extern Vtable_Object _vtable_Closure;

//虚表实例
extern Vtable_Object _vtable_Object;

//结构体的元数据
struct tagMetaStruct {
    char flag[4];
    bool inited;
    const char* structName;
    int size;

    OrcMetaField *headMetaField;//头

    // Object* (*make)(); //创建实例
};

//分配内存，创建结构体的新备份; 需要free
void * MetaStruct_dupStruct(MetaStruct* metaStruct, void *pStruct);

Vtable_Object *orc_Vtable_Closure_init();

//数据表
//typedef struct Object Object;
struct tagObject{
    //构造函数 用户定义的
    void (*ctor)(Object *self);

    //父类 // vtable放在第二位，是为了与closure一致？
    Vtable_Object *vtable;

    _Atomic int refCount;//引用计数

    //清理函数，会调用dtor
    void (*fini)(struct tagObject *self);

    //析构函数 用户定义的
    void (*dtor)(Object *self);
} ;

//虚表初始化函数
Vtable_Object* Vtable_Object_init(Vtable_Object* pvt);
// 反射初始化，每个虚表都会有一个初始化函数，并返回头
// 反射和虚表的初始化是分开的，因为虚表更常用， 特别是在instanceof
// 反射相对少用，通常用于序列化。 分开初始化，就可以在需要用的时候才初始化

// OrcMetaField* Vtable_Object_meta_init(Vtable_Object *pvt);


const char* Object_getClassName(Object* self);

// 结束处理
void Object_fini(Object *self);
// 初始化字段. pOwner owner的地址. 如局部变量的地址
void Object_init_fields(Object *self);
// 初始化对象
void Object_init(Object *self, void *pOwner);
// 在堆上分配对象，并初始化
Object * Object_new(void *pOwner);


//统一的清理和释放内存; 继承于Object的对象都要使用此函数进行释放
void orc_delete(void *self);
//释放字符串资源 
void str_delete(void *self);

//用于__attribute__((cleanup(Orc_cleanup_ref))) 用来实现defer 解引用的效果
void Orc_cleanup_ref(void* p);

bool Orc_instanceof(Object *p, Vtable_Object *vtable);


void *orc_alloc_and_set_deleter(int size, void *deleter);

//离开scope
void Orc_scopeExit(void* p);


//============反射

typedef enum {
    OrcMetaType_void,
    OrcMetaType_bool,
    OrcMetaType_char,
    OrcMetaType_short,
    OrcMetaType_int,
    OrcMetaType_long,
    OrcMetaType_long_long,
    OrcMetaType_float,
    OrcMetaType_double,
    OrcMetaType_struct,
    OrcMetaType_class,
    OrcMetaType_method,
    OrcMetaType_function,
} OrcMetaType;

struct tagOrcMetaField{
    const char *name; //名称，必须是指向常量区
    OrcMetaType type;//char/short/int/long/long long/struct/class
    Vtable_Object *classVtable;//如果是class,就需要有虚表
    bool isPointer;//是指针
    bool isRef; //是不是引用
    bool isArray; //是不是数组
    MetaStruct *metaStruct;//结构体的元数据
    int pointerLevel; //几级指针. int *是1， int**是2
    int arrayLength; //目前只支持一维数组
    int address; //字段地址
    int size; //字段 长度
    bool isUnsigned;//无符号类型
    // bool isConst;//无符号类型

    OrcMetaField *next; //指向下一个字段
};

void orc_initMetaStruct(MetaStruct **pmeta, const char *name, int size);
OrcMetaField* orc_getOrInitMeta(Vtable_Object *pvt);
OrcMetaField* orc_newMetaField(OrcMetaField ***pNext);

const char * OrcMetaField_getName(OrcMetaField *self);
int OrcMetaField_getAddress(OrcMetaField *self);

//取得int*指针，，该指针指向字段
void* OrcMetaField_getPtr(OrcMetaField *self, void *obj);

bool* OrcMetaField_getBoolPtr(OrcMetaField *self, Object *obj);
char* OrcMetaField_getCharPtr(OrcMetaField *self, Object *obj);
int* OrcMetaField_getIntPtr(OrcMetaField *self, Object *obj);
long* OrcMetaField_getLongPtr(OrcMetaField *self, Object *obj);
long long* OrcMetaField_getLongLongPtr(OrcMetaField *self, Object *obj);
float* OrcMetaField_getFloatPtr(OrcMetaField *self, Object *obj);
double* OrcMetaField_getDoublePtr(OrcMetaField *self, Object *obj);

int OrcMetaField_getType(OrcMetaField *self);
bool OrcMetaField_isPrimitive(OrcMetaField *self);
bool OrcMetaField_isStringRef(OrcMetaField *self);
OrcMetaField * OrcMetaField_getNext(OrcMetaField *self);

void orc_metaField_primitive(
    OrcMetaField ***pppmf, //三级指针。为了可以在内部修改pNext的值  OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//不含父类的。
    const char *name,
    OrcMetaType type, int address, bool isUnsigned,
    bool isRef,
    bool isPointer,
    int pointerLevel
);

void orc_metaField_method(
    OrcMetaField ***pppmf, 
    const char *name,
    int address);

void orc_metaField_class(
    OrcMetaField ***pppmf, 
    const char *name,
    Vtable_Object *vt,
    int address,
    bool isRef,
    bool isPointer,
    int pointerLevel
    );

void orc_metaField_struct(
    OrcMetaField ***pppmf, 
    const char *name,
    MetaStruct *mtStruct,
    int address,
    bool isRef,
    bool isPointer,
    int pointerLevel
    );

//普通的c结构体，没有MetaStruct
void orc_metaField_plainStruct(
    OrcMetaField ***pppmf, 
    const char *name,
    size_t size,
    int address,
    bool isRef,
    bool isPointer,
    int pointerLevel
    );

//根据字段名取得字段的元数据
OrcMetaField *orc_getMetaField(Vtable_Object *vt, const char *name);
OrcMetaField *orc_getMetaField_byHeadMetaField(OrcMetaField *cur, const char *name);

OrcMetaField *MetaStruct_getMetaFieldByFieldName(MetaStruct *ms, const char *name);

Vtable_Object *orc_getVtableByObject(Object* obj);
OrcMetaField *orc_getMetaFieldByObject(Object *obj, const char *name);

Vtable_Object *Vtable_getSuper(Vtable_Object* vt);
const char * Vtable_getClassName(Vtable_Object* vt);


bool orc_setFieldInt(Object* vt, const char* name, int val);
bool orc_setFieldDouble(Object* obj, const char* name, double val);

int orc_getFieldInt(Object* vt, const char* name);
double orc_getFieldDouble(Object* obj, const char* name);
void *orc_getFieldPtr(Object *obj, const char *name);

//===================支持rc的  内存管理==============
void urgc_deref_class(void *pvar, Object* p);
void urgc_ref_class(void *pvar, Object* p, void (*deleter)(void*));
//初始化类引用变量
void * urgc_init_var_class(void **pvar, Object* p);
void * urgc_set_var_class(void** pvar, Object* p);
void * urgc_set_var_for_return_class(void** pvar, Object* p);
void* urgc_set_field_class(void* host, void** field, Object* p);

//加引用计数
void orc_addRefc(Object *p);
//减引用计数
void orc_delRefc(Object *p);


//类专用的cleanup
void urgc_refvar_cleanup_class(void *p) ;


//<<<<<<<<<<<<

#ifdef __cplusplus
}
#endif