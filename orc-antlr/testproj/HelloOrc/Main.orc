#include <stdio.h>
// #include <windows.h>
// #include "UrgcDll/urgc_api.h"
// #include "Orc/Orc.h"
// import * from "./Orc/Time.orc"
// import * from "./Orc/Thread.orc"
// import * from "./Orc/String.orc"

// import * from "./Orc/Mutex.orc"
// import * from "./Orc/Math.orc"
// import * from "./Orc/List.orc"
// import * from "./Orc/Map.orc"
// import * from "./Orc/Path.orc"

// struct Vec2 {
//     float x
//     float y
// }
// extension Vec2{
//     void set(float x, float y){
//         self.x = x
//         self.y = y
//     }
//     void print(){
//         printf("Vec2(%f,%f)\n", self.x, self.y)
//     }
//     void addSelf(float x, float y){
//         self.x += x
//         self.y += y
//     }
//     Vec2 clone(){
//         Vec2 v;
//         v.set(self.x, self.y)
//         return v;
//     }
// }
// class Monster {
//     char *name = null
// } 
// class User {
//     int age = 12;
//     ^User@ () createUser
//     void dtor(){
//         printf("free user age=%d,%p\n", self.age, self)
//     }
//     void ctor(){
//         printf("ctor user\n")
//     }
//     User@ clone(){
//         return new User()
//     }
//     void print(){
//         printf("User(age=%d)\n", self.age)
//     }
//     void fire(){
//         if (self.onEvent){
//             User@ ret = self.onEvent()
//             printf("ret user age:%d, %p\n", ret.age, ret);
//         }
//     }  
//     ^User@ onEvent
// }
// extension User {
//     int getUserAge(){
//         return self.age
//     }
// }  

// void testRef(){
//     printf("testRef\n")
//     User@ uv = new User()
//     uv.print()
//     //uv.age = 3423
//     //uv.print() 
//     int b = 10
//     uv.onEvent = ^User@ (){
//         printf("clos b:%d age:%d\n", b, uv->age)
//         User@ u = new User()
//         u.age = 999;
//         return u;
//     } 
//     ^User@ mkUser(){
//         return new User();
//     } 
//     ^User@ () hiUser;

//     uv.fire() 
    
//     printf("\t end testRef. user age:%d instanceof:%d %d\n",
//         uv.getUserAge(),
//         uv instanceof User,
//         uv instanceof Monster
//         )
//     OrcMetaField *ageMf = orc_getMetaFieldByObject(uv, "age");
//     int age = orc_getFieldInt(uv, "age");
//     orc_setFieldInt(uv, "age", 234);
//     int age2 = orc_getFieldInt(uv, "age");
//     printf("end %p %s age:%d=>%d\n", ageMf, ageMf.name, age, age2) ;
// } 
class User {
    int id = 0
    void say(){
        int v2 = 3
        ^void hi(){
            self.id = 10
            v2 = self.id
            printf("", self.id)
        }
    }
}
int main(){
    // SetConsoleOutputCP (65001)
    // urgc_start_process_thread();
    // Vec2 v 
    // v.set(10.0f, 20.0f)
    // v.print()
    // v.addSelf(10.f, 32.f)
    // v.print()
    // v.addSelf(10.f, 32.f)
    // v.print()
    // v.addSelf(10.f, 32.f)
    // v.print() 
     
    // Vec2 v2 = v.clone()
    // v2.print() 

    // testRef()
     
    // ;v2.{
    //     o.set(30, 99)
    //     o.print()
    //     ;&o.{
    //         o.set(66, 66)
    //         o.print();
    //     }
    //     o.print()
    // }
    // v2.print();


    // User@ tmpUser = null
    // tmpUser = new User()
    
    // User@ tmpUser2  = tmpUser.clone()

    // //Math_test();

    // {
    //     Mutex@ mutex = new Mutex();
    //     mutex.lock();
    
    //     testThread();

    //     mutex.unlock();
    // }

    // //Time_test()
    // List_test();
    // Map_test()
    // testPath()
    // testStr()

    // getchar()
    // printf("hi2\n")
    return 0

}
