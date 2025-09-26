
//类型预声明，可以处理循环引用的问题
typedef struct tagProject_Mod$Father Project_Mod$Father;
typedef struct tagVtable_Project_Mod$Father Vtable_Project_Mod$Father;
typedef struct tagProject_Mod$User Project_Mod$User;
typedef struct tagVtable_Project_Mod$User Vtable_Project_Mod$User;



#ifndef INCLUDE_ONLY_TYPE

#ifndef __FuncCall_orc_h__
#define __FuncCall_orc_h__

#include "Orc.h"
//package Project_Mod



#ifdef __cplusplus
extern "C"{
#endif


int Project_Mod$say();


//虚表
// typedef struct tagVtable_Project_Mod$Father Vtable_Project_Mod$Father;
struct tagVtable_Project_Mod$Father {
    Vtable_Object super;

};
//虚表实例
extern Vtable_Project_Mod$Father _vtable_Project_Mod$Father;

//数据表
struct tagProject_Mod$Father{
    //父类
    Object super;
	void (*lala)(Project_Mod$Father * self);

};

//虚表初始化函数
Vtable_Project_Mod$Father* Vtable_Project_Mod$Father_init(Vtable_Project_Mod$Father* pvt);
//初始化字段
void Project_Mod$Father_init_fields(Project_Mod$Father *self);

//初始化函数
void Project_Mod$Father_init(Project_Mod$Father *self);
Project_Mod$Father * Project_Mod$Father_new();
//释放
void Project_Mod$Father_fini(Project_Mod$Father *self);
// void Project_Mod$Father_delete(Project_Mod$Father **self);

//成员函数
void Project_Mod$Father$lala(Project_Mod$Father * self);




//虚表
// typedef struct tagVtable_Project_Mod$User Vtable_Project_Mod$User;
struct tagVtable_Project_Mod$User {
    Vtable_Project_Mod$Father super;

};
//虚表实例
extern Vtable_Project_Mod$User _vtable_Project_Mod$User;

//数据表
struct tagProject_Mod$User{
    //父类
    Project_Mod$Father super;
	void (*print)(Project_Mod$User * self);

};

//虚表初始化函数
Vtable_Project_Mod$User* Vtable_Project_Mod$User_init(Vtable_Project_Mod$User* pvt);
//初始化字段
void Project_Mod$User_init_fields(Project_Mod$User *self);

//初始化函数
void Project_Mod$User_init(Project_Mod$User *self);
Project_Mod$User * Project_Mod$User_new();
//释放
void Project_Mod$User_fini(Project_Mod$User *self);
// void Project_Mod$User_delete(Project_Mod$User **self);

//成员函数
void Project_Mod$User$print(Project_Mod$User * self);


void Project_Mod$User$calc(Project_Mod$User * self);
void Project_Mod$main();

#ifdef __cplusplus
}
#endif

#endif

#endif
