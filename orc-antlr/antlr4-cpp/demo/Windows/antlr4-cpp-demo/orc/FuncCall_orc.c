#include "Orc.h"
#include "./FuncCall_orc.h"
//package Project_Mod

static void st();
int Project_Mod$say() {
    return 10;
}



//虚表实例
Vtable_Project_Mod$Father _vtable_Project_Mod$Father;


//虚表初始化函数
 Vtable_Project_Mod$Father* Vtable_Project_Mod$Father_init(Vtable_Project_Mod$Father* pvt){
    if (pvt == NULL){ //未指定变量
        pvt = &_vtable_Project_Mod$Father;
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
    ((Vtable_Object*)pvt)->make = (void*)&Project_Mod$Father_new;
    ((Vtable_Object*)pvt)->className = "Project_Mod$Father";

    return pvt;
}

//释放
void Project_Mod$Father_fini(Project_Mod$Father *self){
    //调用父类析构函数，根Object_fini会调用dtor成员函数
    Object_fini((Object *)self);

    //字段释放
    

    // return self;
}


//初始化字段
void Project_Mod$Father_init_fields(Project_Mod$Father *self){
    //父类初始化字段
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Project_Mod$Father_fini;

    {
        
    }
    ((Project_Mod$Father*)self)->lala = (void*)&Project_Mod$Father$lala;
}
//初始化函数
void Project_Mod$Father_init(Project_Mod$Father *self){
    //虚表初始化
    Vtable_Project_Mod$Father_init(&_vtable_Project_Mod$Father);

    //初始化虚表指针
    ((Object*)self)->vtable = (void*)&_vtable_Project_Mod$Father;

    //urgc保护指针，防止循环
    urgc_guard(self, (void*)orc_delete);

    //初始化字段
    Project_Mod$Father_init_fields(self);

    //调用构造函数
    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}
Project_Mod$Father * Project_Mod$Father_new(){
    Project_Mod$Father *self = calloc(1, sizeof(Project_Mod$Father));
    Project_Mod$Father_init(self);
    return self;
}



//成员函数
void Project_Mod$Father$lala(Project_Mod$Father * self) {
    
}





//虚表实例
Vtable_Project_Mod$User _vtable_Project_Mod$User;


//虚表初始化函数
 Vtable_Project_Mod$User* Vtable_Project_Mod$User_init(Vtable_Project_Mod$User* pvt){
    if (pvt == NULL){ //未指定变量
        pvt = &_vtable_Project_Mod$User;
    }
    //已经初始化
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }

    //确保父虚表实例已经初始化
    Vtable_Project_Mod$Father_init(&_vtable_Project_Mod$Father);


    //父虚表初始化
    Vtable_Project_Mod$Father_init((void*)pvt);

    //虚表赋值
    //记录虚表的父
    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Project_Mod$Father;
    ((Vtable_Object*)pvt)->make = (void*)&Project_Mod$User_new;
    ((Vtable_Object*)pvt)->className = "Project_Mod$User";

    return pvt;
}

//释放
void Project_Mod$User_fini(Project_Mod$User *self){
    //调用父类析构函数，根Object_fini会调用dtor成员函数
    Project_Mod$Father_fini((Project_Mod$Father *)self);

    //字段释放
    

    // return self;
}


//初始化字段
void Project_Mod$User_init_fields(Project_Mod$User *self){
    //父类初始化字段
    Project_Mod$Father_init_fields((Project_Mod$Father*)self);

    ((Object*)self)->fini = (void*)Project_Mod$User_fini;

    {
        
    }
    ((Project_Mod$User*)self)->print = (void*)&Project_Mod$User$print;
}
//初始化函数
void Project_Mod$User_init(Project_Mod$User *self){
    //虚表初始化
    Vtable_Project_Mod$User_init(&_vtable_Project_Mod$User);

    //初始化虚表指针
    ((Object*)self)->vtable = (void*)&_vtable_Project_Mod$User;

    //urgc保护指针，防止循环
    urgc_guard(self, (void*)orc_delete);

    //初始化字段
    Project_Mod$User_init_fields(self);

    //调用构造函数
    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}
Project_Mod$User * Project_Mod$User_new(){
    Project_Mod$User *self = calloc(1, sizeof(Project_Mod$User));
    Project_Mod$User_init(self);
    return self;
}



//成员函数
void Project_Mod$User$print(Project_Mod$User * self) {
    
}


static void st() {
    
}
void Project_Mod$User$calc(Project_Mod$User * self) {
    
}
void Project_Mod$main() {
    Project_Mod$User * user;
    Project_Mod$main();
    Project_Mod$say();
    st();
    user->print(user);
    Project_Mod$User$calc(user);
    Project_Mod$say(Project_Mod$main());
    Project_Mod$say(Project_Mod$User$calc(user));
    Project_Mod$say(user->print(user));
    if (Project_Mod$User$calc(user)) {
        
    }else if (user->print(user)) {
        
    }else if (user->print(user)) {
        
    } else {
        user->print(user);
    }
    for (; user->print(user); ) {
        
    }
    while (user->print(user)) {
        
    }
    ((Project_Mod$Father *)user)->lala(user);
}