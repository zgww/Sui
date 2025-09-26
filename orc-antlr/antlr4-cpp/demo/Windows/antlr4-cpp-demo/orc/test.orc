package Test
// #include <stdio.h>


// class Parent {
//     int box = 10;
//     void print(){
//         printf("i'm parent. my box is :%d. my age is :\n", self->box);
//     }
// }
// class User extends Parent {
//     // int box= 10;
//     int age = 10;
//     char *name = "zgww";
//     void print(){
//         super->print();
//         super.print();
//         printf("my name is :%s. my age is :%d box:%d\n", self->name, self->age, self->box);
//     }
// }

// static void stSay(){

// }
class User {
    void say(){

    }
}
void testUser(User *self){
}
void printMyName(){

    User*user = new User();
    //&user => new User()



    User@ user = new User();
    user.say()
    testUser(user)
    user~testUser()

    user.say();
    user.say();
    user->say();

    //char data[100][10];
    //data[0][0] = 10;
    //data[1][0] = 10;
    //data[2][0] = 10;
    //data[3][0] = 10;
    // User@ user = new User();
    // user->print();
    // user->name = "new name";
    // user->print();
    // stSay();
}

