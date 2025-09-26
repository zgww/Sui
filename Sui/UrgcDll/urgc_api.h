#pragma once
#include "./UrgcPredef.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef ROOT_REF
//根引用。 
#define ROOT_REF ((unsigned long long)-1l)
#endif


/*
用于对参数引用和解引用
Project$User* Project$User$returnRef(Project$User * * __outRef__, Project$User * this, Project$User* other) {
    URGC_REF_ARG_WITH_CLEANUP(void *, __tmpArg_348, other);
    return urgc_set_var(__outRef__, NULL);
}
*/
//msvc代码提示器专用，msvc intellisense不理解 __attribute__
#ifdef __INTELLISENSE__
	#define URGC_VAR_CLEANUP  
	#define URGC_REF_ARG_WITH_CLEANUP(value) 

	#define DEFER_FREE
	#define DEFER(fn)
	#define UNUSED
#else
//if defined(__clang__) || defined(__GNUC__)
	#define URGC_VAR_CLEANUP  __attribute__((cleanup(urgc_refvar_cleanup)))
	#define __ARG_SCOPE(b) __argScope##b
	#define _ARG_SCOPE(a) __ARG_SCOPE(a)
	#define ARG_SCOPE() _ARG_SCOPE(__LINE__)
	#define URGC_REF_ARG_WITH_CLEANUP(value) URGC_VAR_CLEANUP void* ARG_SCOPE() = urgc_init_var(&ARG_SCOPE(), (value))

	#define DEFER_FREE  __attribute__((cleanup(urgc_defer_free)))
	#define DEFER(fn)  __attribute__((cleanup(fn)))
	#define UNUSED __attribute__((unused))
#endif

// 创建新的对象
// 例：URGC_VAR_CLEANUP SuiDesigner$BiJsonExporter* ret = urgc_init_var((void**)&ret, SuiDesigner$BiJsonExporter_new());
// #define URGC_NEW_VAR(TYPE, VAR, INIT) URGC_VAR_CLEANUP TYPE VAR = (TYPE) urgc_init_var((void**)&VAR, INIT)

// 返回对象的引用
// 例：    return urgc_set_var_for_return((void**)__outRef__, ret);
// #define URGC_RETURN(VAR) urgc_set_var_for_return((void**)__outRef__, VAR)

//表示这是引用。  纯表意用的
#define REF_TYPE

//声明并初始化urgc变量
#define URGC_VAR(type, name, initExpr)  URGC_VAR_CLEANUP type name = urgc_init_var((void**)&name, (initExpr))

//声明并初始化urgc变量,并指定deleter
// #define URGC_VAR_WITH_DELETER(type, name, initExpr, deleter)  URGC_VAR_CLEANUP type name = urgc_init_var_with_deleter(&name, (initExpr), deleter)

URGC_DLLAPI inline void urgc_ref(void* source, void *target, void (*deleter)(void*));
URGC_DLLAPI inline void urgc_deref(void* source, void *target);
URGC_DLLAPI void urgc_guard(void* p, void (*deleter)(void*));
URGC_DLLAPI void urgc_deguard(void* p);
URGC_DLLAPI void urgc_set_deleter(void* p, void (*deleter)(void*));

URGC_DLLAPI void* urgc_set_field_by_offset(void* host, int field_offset, void* p);
URGC_DLLAPI void * urgc_set_field(void* host, void** field, void* p);
URGC_DLLAPI void * urgc_set_var(void** pvar, void* p);
/*如果是要返回urgc引用，生命周期会出现外部和函数内部的交叉。 解决方案是外部将接收返回的变量指针(暂名为a)作为参数传入。为了处理可能的a为null的情况，
此函数会检测a，为空时， 触发引用和解引用。 
这是为了适配c的malloc。 考虑以下两种情况:
1. 
User@ b = malloc(sizeof(User));
return b;

2.
User*b = malloc(sizeof(User));
return b;

对于后者， 如果外部接收变量的指针a没有传入，则情况2会导致内存不释放。 因为没有b实际上没有接收者了。 但也没有机会触发解引用
*/
URGC_DLLAPI void * urgc_set_var_for_return(void** pvar, void* p);
// URGC_DLLAPI void * urgc_set_var_for_return_with_deleter(void** pvar, void* p, void (*deleter)(void*));
//设置初值时使用，因为初值时，pvar可能有脏数据
URGC_DLLAPI void * urgc_init_var(void** pvar, void* p);
//设置初值，同时绑定deleter
// URGC_DLLAPI void * urgc_init_var_with_deleter(void** pvar, void* p, void (*deleter)(void *));

URGC_DLLAPI void urgc_start_process_thread();
URGC_DLLAPI void urgc_stop_process_thread();

//在c中实现defer/RAII 退出作用域自动解引用的效果
URGC_DLLAPI void urgc_refvar_cleanup(void* p);


//返回当前的计数， 并重置为0
URGC_DLLAPI int urgc_countEvent();

URGC_DLLAPI void urgc_defer_free(void *p);
//由于orc引入了refc, 就会导致在deref class时，还会访问内存，而该内存可能已被释放
//所以需要延迟释放
//例： 
/*
LayoutLinear
	view
LayoutLinear已释放，现在要释放view,
释放view时，需要set parent null, set parent null中访问了parent->vtable->refc, 
就成访问非法内存了
*/
URGC_DLLAPI void urgc_free_later(void *p);

URGC_DLLAPI void urgc_report_sources_of(void *p);

#ifdef __cplusplus
}
#endif
