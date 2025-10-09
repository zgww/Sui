#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "./Orc.h"

#include <Windows.h>
#include "Orc/Orc.h"
#include "UrgcDll/urgc_api.h"
#include "./ScopeData_orc.h"


//虚表实例
Vtable_Object _vtable_Object;
Vtable_Object _vtable_Closure;

struct SkPaint;

Vtable_Object *orc_Vtable_Closure_init(){
    if (!_vtable_Closure.inited){
        _vtable_Closure.flag[0] = 'C';
        _vtable_Closure.flag[1] = 'L';
        _vtable_Closure.flag[2] = 'O';
        _vtable_Closure.flag[3] = 'S';
        _vtable_Closure.inited = true;
        _vtable_Closure.refc = 0;//不使用rrefc
        _vtable_Closure.className = "Closure";//不使用rrefc
    }
    return &_vtable_Closure;
}

OrcMetaField * orc_newMetaField(OrcMetaField ***pNext){
    OrcMetaField *cur = calloc(1, sizeof(OrcMetaField));
    **pNext = cur;
    *pNext = &cur->next;
    return cur;
}
//初始化元数据
void Object_initMeta(Vtable_Object *pvt){
    //初始化自己的反射
    OrcMetaField **pNext = & pvt->headMetaField;//不含父类的。
    // orc_metaField_primitive(orc_newMetaField(&pNext), "id", OrcMetaType_char, offsetof(Object, vtable));
    // orc_metaField_primitive(orc_newMetaField(&pNext), "id", OrcMetaType_char, offsetof(Object, vtable));
    // orc_metaField_primitive(orc_newMetaField(&pNext), "id", OrcMetaType_char, offsetof(Object, vtable));
    // orc_metaField_primitive(orc_newMetaField(&pNext), "id", OrcMetaType_char, offsetof(Object, vtable));
    // orc_metaField_primitive(orc_newMetaField(&pNext), "id", OrcMetaType_char, offsetof(Object, vtable));
    // orc_metaField_primitive(orc_newMetaField(&pNext), "id", OrcMetaType_char, offsetof(Object, vtable));
}

void orc_initMetaStruct(MetaStruct **pmeta, const char *name, int size){
    *pmeta = calloc(1, sizeof(MetaStruct));
    MetaStruct *meta = *pmeta;
    meta->flag[0] = 'M';
    meta->flag[1] = 'T';
    meta->flag[2] = 'S';
    meta->flag[3] = 'T';
    meta->inited = true;
    meta->structName = name;
    meta->size = size;
}
// //对于结构体
// MetaStruct* XXStruct_getOrInitMetaStruct(){
//     static MetaStruct *meta = NULL;
//     if (meta == NULL){
//         //初始化
//         orc_initMetaStruct(meta, "XXSt", sizeof(int));

//         OrcMetaField **pNext = &meta->headMetaField;//不含父类的。
//         // orc_metaField_primitive(orc_newMetaField(&pNext), "id", OrcMetaType_char, offsetof(Object, vtable));
//     }
//     return meta;
// }


//虚表初始化函数
Vtable_Object* Vtable_Object_init(Vtable_Object* pvt) {
    if (pvt == NULL){
        pvt = &_vtable_Object;
    }
    //已经初始化
    if (((Vtable_Object*)pvt)->inited) {
        return pvt;
    }
    //虚表赋值
    // char flag[4] = "ORCO";

    pvt->flag[0] = 'O';
    pvt->flag[1] = 'R';
    pvt->flag[2] = 'C';
    pvt->flag[3] = 0;
    pvt->inited = true;
    pvt->super = NULL;

    pvt->className = "Object";

    pvt->make = Object_new;
    pvt->initMeta = Object_initMeta;//初始化元数据,延时调用
    return pvt;
}

const char* Object_getClassName(Object* self)
{
    return self->vtable->className;
}


//统一的清理和释放内存: this要求是 Object*类型
void orc_delete(void* p) {
    Object* this = (Object*)p;
    // printf("释放内存:%p %s\n", this, this->vtable->className);
    //Object*this = *pthis;
    this->fini(this);

    // free(this);
    urgc_free_later(this);
    //*pthis = NULL;
}
//统一的清理和释放字符串内存
void str_delete(void* p) {
    char* this = (char*)p;
    printf("释放字符串内存:%s\n", this);

    free(this);
    //*pthis = NULL;
}




// 结束处理
void Object_fini(Object* this) {
    if (this->dtor) {
        this->dtor(this);
    }

    //调用父类清理函数

    //字段清理
}
void Object_init_fields(Object* this) {
    this->fini = Object_fini;
    // this->dtor = Object_dtor;
}
void Object_init(Object* self, void *pOwner) {
    //虚表初始化
    Vtable_Object_init(&_vtable_Object);
    //虚表指针初始化
    self->vtable = &_vtable_Object;

	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc保护指针，防止循环
    // urgc_guard(this, (void*)orc_delete);

    //成员初始化
    Object_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }
    // urgc_deguard(this);
}
Object* Object_new(void *pOwner) {
	if (pOwner == NULL){ return NULL;}
    Object* a = calloc(1, sizeof(Object));
    Object_init(a, pOwner);

    return a;
}

bool Orc_instanceof(Object* p, Vtable_Object* vtable) {
    if (p == NULL) {
        return false;
    }
    //如果能通过super找到虚表
    Vtable_Object* cur = p->vtable;
    while (cur) {
        if (cur == vtable) {
            return true;
        }
        cur = cur->super;
    }
    return false;
}


void Orc_scopeExit(void* p) {
    Orc$ScopeData* sd = p;
    void (*onExitScope)(Orc$ScopeData * sd) = sd->onExitScope;
    onExitScope(sd);
}

static void _orc_free(void *p){
    // printf("_orc_free:%p\n", p);
    // free(p);
    urgc_free_later(p);
}
//有bug, 闭包对block的引用，没有解引用。。。看来闭包还是要先转为class来实现更完整，也更容易
void *orc_alloc_and_set_deleter(int size, void *deleter){
// void *orc_malloc_closure(int size){
    void *ret = calloc(1, size <= 0 ? 4 : size);

    if (deleter != NULL){
        urgc_set_deleter(ret, deleter);
    } else {
        urgc_set_deleter(ret, _orc_free);
    }

    return ret;
}

//获取即初始化类的元数据
//结构体使用另一个函数 ${StructName}_getOrInitMetaStruct()
//返回第一个字段信息
OrcMetaField* orc_getOrInitMeta(Vtable_Object *pvt){
    //已经初始化了
    if (pvt->headMetaField){
        return pvt->headMetaField;
    }
    if (pvt->super){//父类元数据初始化
        orc_getOrInitMeta(pvt->super);
    }
    if (pvt->initMeta){ //元数据初始化
        pvt->initMeta(pvt);
    }

    return pvt->headMetaField;
}
void orc_metaField_primitive(
    OrcMetaField ***pppmf, 
    const char *name,
    OrcMetaType type, int address, bool isUnsigned,
    bool isRef,
    bool isPointer,
    int pointerLevel){

    OrcMetaField *mf = orc_newMetaField(pppmf);


    mf->name = name; //名称，必须是指向常量区
    mf->type = type;//char/short/int/long/long long/struct/class
    // mf->classVtable;//如果是class,就需要有虚表
    // bool isPointer;//是指针
    // bool isRef; //是不是引用
    // bool isArray; //是不是数组
    // MetaStruct *metaStruct;//结构体的元数据
    // int pointerLevel; //几级指针
    // int arrayLength; //目前只支持一维数组
    mf->isRef = isRef;
    mf->isPointer = isPointer;
    mf->pointerLevel = pointerLevel;
    mf->address = address; //字段地址
    mf->size = 1; //字段 长度
    mf->isUnsigned = isUnsigned;

    switch (type){
        case OrcMetaType_bool: 
        case OrcMetaType_char: mf->size = sizeof(char); break;

        case OrcMetaType_short: mf->size = sizeof(short); break;
        case OrcMetaType_int: mf->size = sizeof(int); break;
        case OrcMetaType_long: mf->size = sizeof(long); break;
        case OrcMetaType_long_long: mf->size = sizeof(long long); break;
        case OrcMetaType_float: mf->size = sizeof(float); break;
        case OrcMetaType_double: mf->size = sizeof(double); break;
        case OrcMetaType_struct: mf->size = -1; break;
        case OrcMetaType_class: mf->size = sizeof(void *); break;
        default: break;
    }

    // OrcMetaField *next; //指向下一个字段

}
void orc_metaField_method(
    OrcMetaField ***pppmf, 
    const char *name,
    int address){

    OrcMetaField *mf = orc_newMetaField(pppmf);


    mf->name = name; //名称，必须是指向常量区
    mf->type = OrcMetaType_method;//char/short/int/long/long long/struct/class
    mf->address = address; //字段地址
    mf->size = sizeof(void*); //字段 长度
}
void orc_metaField_class(
    OrcMetaField ***pppmf, 
    const char *name,
    Vtable_Object *vt,
    int address,
    bool isRef,
    bool isPointer,
    int pointerLevel
    ){

    OrcMetaField *mf = orc_newMetaField(pppmf);

    mf->name = name; //名称，必须是指向常量区
    mf->type = OrcMetaType_class;//char/short/int/long/long long/struct/class
    mf->classVtable = vt;
    mf->isPointer = isPointer;
    mf->isRef = isRef;
    mf->pointerLevel = pointerLevel;
    mf->address = address; //字段地址
    mf->size = sizeof(void*); //字段 长度
}
void orc_metaField_struct(
    OrcMetaField ***pppmf, 
    const char *name,
    MetaStruct *mtStruct,
    int address,
    bool isRef,
    bool isPointer,
    int pointerLevel
    ){

    OrcMetaField *mf = orc_newMetaField(pppmf);

    mf->name = name; //名称，必须是指向常量区
    mf->type = OrcMetaType_struct;//char/short/int/long/long long/struct/class
    mf->metaStruct = mtStruct;
    mf->isPointer = isPointer;
    mf->isRef = isRef;
    mf->pointerLevel = pointerLevel;
    mf->address = address; //字段地址
    if (isRef || isPointer){
        mf->size = sizeof(void*); //字段 长度
    } else {
        mf->size = mtStruct->size;//结构体的长度
    }
}

//普通的c结构体，没有MetaStruct
void orc_metaField_plainStruct(
    OrcMetaField ***pppmf, 
    const char *name,
    size_t size,
    int address,
    bool isRef,
    bool isPointer,
    int pointerLevel
    ){

    OrcMetaField *mf = orc_newMetaField(pppmf);

    mf->name = name; //名称，必须是指向常量区
    mf->type = OrcMetaType_struct;//char/short/int/long/long long/struct/class
    mf->metaStruct = NULL;
    mf->isPointer = isPointer;
    mf->isRef = isRef;
    mf->pointerLevel = pointerLevel;
    mf->address = address; //字段地址
    if (isRef || isPointer){
        mf->size = sizeof(void*); //字段 长度
    } else {
        mf->size = size;//结构体的长度
    }
}

// OrcMetaField orc_mkMetaField_primitive(const char *name, enum OrcMetaType type, int address);
// OrcMetaField orc_mkMetaField_classRef(const char *name, Vtable_Object *vtable, int address);
// OrcMetaField orc_mkMetaField_pointer(const char *name, Vtable_Object *vtable, int address);
// OrcMetaField orc_mkMetaField_struct(const char *name, Vtable_Object *vtable, int address);

OrcMetaField *orc_getMetaField(Vtable_Object *vt, const char *name){
    //从自己的字段找起
    OrcMetaField *cur = orc_getOrInitMeta(vt);
    while (cur){
        if (strcmp(cur->name, name) == 0){
            return cur;
        }
        cur = cur->next;
    }

    //没找到，去找父类
    if (vt->super){
        OrcMetaField *ret = orc_getMetaField(vt->super, name);
        return ret;
    }
    return NULL;
}
OrcMetaField *orc_getMetaField_byHeadMetaField(OrcMetaField *cur, const char *name){
    //从自己的字段找起
    // OrcMetaField *cur = ms->headMetaField;
    while (cur){
        if (strcmp(cur->name, name) == 0){
            return cur;
        }
        cur = cur->next;
    }

    return NULL;
}
int OrcMetaField_getAddress(OrcMetaField *self){
    return self->address;
}
void* OrcMetaField_getPtr(OrcMetaField *self, void *obj){
    if (!self){
        return NULL;
    }
    int addr = OrcMetaField_getAddress(self);
    void *ptr = ((char*)obj) + addr;
    return ptr;
}
//取得int*指针，，该指针指向字段
bool* OrcMetaField_getBoolPtr(OrcMetaField *self, Object*obj){
    return (bool*)OrcMetaField_getPtr(self, obj);
}
char* OrcMetaField_getCharPtr(OrcMetaField *self, Object*obj){
    return OrcMetaField_getPtr(self, obj);
}
int* OrcMetaField_getIntPtr(OrcMetaField *self, Object*obj){
    return (int*)OrcMetaField_getPtr(self, obj);
}
long* OrcMetaField_getLongPtr(OrcMetaField *self, Object*obj){
    return (long*)OrcMetaField_getPtr(self, obj);
}
long long* OrcMetaField_getLongLongPtr(OrcMetaField *self, Object*obj){
    return (long long*)OrcMetaField_getPtr(self, obj);
}
float* OrcMetaField_getFloatPtr(OrcMetaField *self, Object*obj){
    return (float*)OrcMetaField_getPtr(self, obj);
}
double* OrcMetaField_getDoublePtr(OrcMetaField *self, Object*obj){
    return (double*)OrcMetaField_getPtr(self, obj);
}
Vtable_Object *orc_getVtableByObject(Object* obj){
    if (obj){
        return obj->vtable;
    }
    return NULL;
}
int OrcMetaField_getType(OrcMetaField *self){
    return self->type;
}
bool OrcMetaField_isPrimitive(OrcMetaField *self){
    if (!(self->isArray || self->isRef || self->isPointer)){
        bool yes = 
            self->type == OrcMetaType_bool ||
            self->type == OrcMetaType_char ||
            self->type == OrcMetaType_short ||
            self->type == OrcMetaType_int ||
            self->type == OrcMetaType_long ||
            self->type == OrcMetaType_long_long ||
            self->type == OrcMetaType_float ||
            self->type == OrcMetaType_double;
        return yes;
    }
    return false;
}
bool OrcMetaField_isStringRef(OrcMetaField *self){
    bool yes =  self->isRef && self->type == OrcMetaType_class;
    if (yes){
        if (strcmp(self->classVtable->className, "Orc$String") == 0){
            return true;
        }
    }
    return false;

}
Vtable_Object *Vtable_getSuper(Vtable_Object* vt)
{
    return vt->super;
}
const char * Vtable_getClassName(Vtable_Object* vt)
{
    return vt->className;
}
OrcMetaField * OrcMetaField_getNext(OrcMetaField *self)
{
    return self->next;
}
const char * OrcMetaField_getName(OrcMetaField *self){
    return self->name;
}
OrcMetaField* orc_getMetaFieldByObject(Object *obj, const char *name)
{
    Vtable_Object *vt = orc_getVtableByObject(obj);
    if (vt){
        OrcMetaField *mf = orc_getMetaField(vt, name);
        return mf;
    }
    return NULL;
}


bool orc_setFieldInt(Object* obj, const char* name, int val) {
    OrcMetaField *mf = orc_getMetaFieldByObject(obj, name);
    if (mf) {
        if (mf->type == OrcMetaType_bool) {
            bool* pInt = (bool*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_char) {
            char* pInt = (char*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_short) {
            short* pInt = (short*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_int) {
            int* pInt = (int*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_long) {
            long* pInt = (long*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_long_long) {
            long long* pInt = (long long*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_float) {
            float* pInt = (float*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_double) {
            double* pInt = (double*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        return true;
    }
    return false;
}

bool orc_setFieldDouble(Object* obj, const char* name, double val) {
    OrcMetaField* mf = orc_getMetaFieldByObject(obj, name);
    if (mf) {
        if (mf->type == OrcMetaType_bool) {
            bool* pInt = (bool*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_char) {
            char* pInt = (char*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_short) {
            short* pInt = (short*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_int) {
            int* pInt = (int*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_long) {
            long* pInt = (long*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_long_long) {
            long long* pInt = (long long*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_float) {
            float* pInt = (float*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        if (mf->type == OrcMetaType_double) {
            double* pInt = (double*)(((char*)obj) + mf->address);
            *pInt = val;
        }
        return true;
    }
    return false;
}



int orc_getFieldInt(Object* obj, const char* name) {
    OrcMetaField* mf = orc_getMetaFieldByObject(obj, name);
    if (mf) {
        if (mf->type == OrcMetaType_bool) {
            bool* pInt = (bool*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_char) {
            char* pInt = (char*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_short) {
            short* pInt = (short*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_int) {
            int* pInt = (int*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_long) {
            long* pInt = (long*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_long_long) {
            long long* pInt = (long long*)(((char*)obj) + mf->address);

            return *pInt;
        }
        if (mf->type == OrcMetaType_float) {
            float* pInt = (float*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_double) {
            double* pInt = (double*)(((char*)obj) + mf->address);
            return *pInt;
        }
    }
    return 0;
}
void *orc_getFieldPtr(Object *obj, const char *name){
    OrcMetaField* mf = orc_getMetaFieldByObject(obj, name);
    if (mf) {
        void *ret = OrcMetaField_getPtr(mf, obj);
        return ret;
    }
    return NULL;
}
double orc_getFieldDouble(Object* obj, const char* name) {
    OrcMetaField* mf = orc_getMetaFieldByObject(obj, name);
    if (mf) {
        if (mf->type == OrcMetaType_bool) {
            bool* pInt = (bool*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_char) {
            char* pInt = (char*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_short) {
            short* pInt = (short*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_int) {
            int* pInt = (int*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_long) {
            long* pInt = (long*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_long_long) {
            long long* pInt = (long long*)(((char*)obj) + mf->address);

            return *pInt;
        }
        if (mf->type == OrcMetaType_float) {
            float* pInt = (float*)(((char*)obj) + mf->address);
            return *pInt;
        }
        if (mf->type == OrcMetaType_double) {
            double* pInt = (double*)(((char*)obj) + mf->address);
            return *pInt;
        }
    }
    return 0.0;
}

void urgc_deref_class(void *pvar, Object* p){
    if (p){
        if (p->vtable->refc){//采用引用计数
            orc_delRefc(p);
        }
        else{
            urgc_deref(pvar, p);
        }
    }

}
void urgc_ref_class(void *pvar, Object* p, void (*deleter)(void*)){
    if (p){
        if (p->vtable->refc){
            orc_addRefc(p);
        } else {
            urgc_ref(pvar, p, deleter);
        }
    }

}
void * urgc_init_var_class(void **pvar, Object* p){
	#ifdef NO_URGC_REF
	*pvar = p;
	if (1) return p;
	#endif

	//已经引用上了。  在 Type *a = new Type() 时，会被转义为  Type*a = urgc_init_var(&a, Type_new(&a)); Type_new就会提前让a引用新对象
	if (*pvar == p){
		return p;
	}

	*pvar = p;
	if (*pvar != NULL) {
        if (p->vtable->refc){//采用引用计数
            orc_addRefc(p);
        } else {
            urgc_ref(pvar, p, NULL);
        }
	}
	return p;

}
//统计使用引用计数对象的数量
static int refcObjCount = 0;
int orc_getRefcObjCount(){
    return refcObjCount;
}
//加引用计数
void orc_addRefc(Object *p){
    atomic_fetch_add(&p->refCount, 1);
    int refc = atomic_load(&p->refCount);
    if (refc == 1){
        refcObjCount++;
    }
}
//减引用计数
void orc_delRefc(Object *p){
    atomic_fetch_sub(&p->refCount, 1);
    int refc = atomic_load(&p->refCount);
    // printf("减引用计数至%d， 释放内存:%p %s\n", refc, p, p->vtable->className);
    if (refc <= 0){//释放
        orc_delete(p);
        refcObjCount--;
    }
}

void urgc_refvar_cleanup_class(void *p) {
    Object** ppobj = (Object **)p;
    //printf("cleanup ref:p=%p obj=%p\n", pobj, *pobj);
    //urgc_set_var(pobj, NULL);//记录引用
	// urgc.deref(pobj, (GcObj*)(*pobj));
    urgc_deref_class(ppobj, *ppobj);
}
void * urgc_set_var_class(void** pvar, Object* p){
	#ifdef NO_URGC_REF
	*pvar = p;
	if (1) return p;
	#endif

	if (pvar != NULL) { //orc接收return值时， __outRef__可能值为NULL
        //已经引用上了。  在 Type *a = vt->make(&a) 时，
        //make自身就会先建立 了a到新对象的引用
        if (*pvar == p){
            return p;
        }

		//先解引用
		if (*pvar != NULL) {
            Object* oldp = (Object*)(*pvar);
            if (oldp->vtable->refc){//采用引用计数
                orc_delRefc(oldp);
            }
            else{
                urgc_deref(pvar, (*pvar));
            }
		}

		*pvar = p;
		if (*pvar != NULL) {
            if (p->vtable->refc){//采用引用计数
                orc_addRefc(p);
            }
            else{
                urgc_ref(pvar, p, NULL);
            }
		}
	}
	return p;
}
void * urgc_set_var_for_return_class(void** pvar, Object* p){
	#ifdef NO_URGC_REF
		*pvar = p;
	if (1) return p;
	#endif
	if (pvar != NULL) { //orc接收return值时， __outRef__可能值为NULL
		//先解引用
		if (*pvar != NULL) {
            Object* oldp = (Object*)(*pvar);
            if (oldp->vtable->refc){//采用引用计数
                orc_delRefc(oldp);
            }
            else{
                urgc_deref(pvar, (*pvar));
            }
		}

		*pvar = p;
		if (*pvar != NULL) {
            if (p->vtable->refc){//采用引用计数
                orc_addRefc(p);
            }
            else{
                urgc_ref(pvar, p, NULL);
            }
		}
	}
	else {//没有接收者时
        if (p->vtable->refc){//采用引用计数
            orc_addRefc(p); //这两行可以不用?
            orc_delRefc(p);
        }
        else {
            urgc_ref((void*)ROOT_REF, p, NULL);
            urgc_deref((void*)ROOT_REF, p);
        }
		//没有接收者，直接返回NULL。因为此值是失效的
		return NULL;
	}
	return p;
}
void urgc_fini_field_class(void* host, void** field){
	#ifdef NO_URGC_REF
	if (1) return ;
	#endif

    Object* hostobj = (Object*)(host);
    const char *hostClassName = hostobj->vtable->className;
    Object* oldp = (Object*)(*field);
	//先解引用
	if (*field != NULL) {
        const char *className = oldp->vtable->className;
        //引用计数对象的释放需要在此额外处理。  urgc对象则不用。因为urgc能识别孤岛
        if (oldp->vtable->refc){//采用引用计数
            orc_delRefc(oldp);
        }
	}

}
void* urgc_set_field_class(void* host, void** field, Object* p)
{
	if ((size_t)field < 10240) { //说明 field不是真实地址，是相对于0的偏移
		field = (void**)((size_t)host + (size_t)field);
	}


	#ifdef NO_URGC_REF
	*field = p;
	if (1) return p;
	#endif

	//先解引用
	if (*field != NULL) {
        Object* oldp = (Object*)(*field);
        if (oldp->vtable->refc){//采用引用计数
            orc_delRefc(oldp);
        }
        else{
            urgc_deref(host, (*field));
        }

	}
	*field = p;
	if (*field != NULL) {
        if (p->vtable->refc){//采用引用计数
            orc_addRefc(p);
        }
        else{
            urgc_ref(host, p, NULL);
        }
	}
	return p;
}
OrcMetaField *MetaStruct_getMetaFieldByFieldName(MetaStruct *ms, const char *name){
    OrcMetaField *mf = ms->headMetaField;
    while (mf){
        if (strcmp(mf->name, name) == 0){
            return mf;
        }
        mf = mf->next;
    }
    return NULL;
}
void * MetaStruct_dupStruct(MetaStruct* metaStruct, void *pStruct){
    void *dst = malloc(metaStruct->size);
    memcpy(dst, pStruct, metaStruct->size);

    return dst;
}