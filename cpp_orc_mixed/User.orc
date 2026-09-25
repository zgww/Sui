#include <stdio.h>


void say(){
    printf("hi\n")
}

class User {
    int age = 0
    void ctor(){
        printf("User.ctor\n")
    }
    void dtor(){
        printf("User.dtor. age=%d\n", self.age)
    }
    void say(const char *msg){
        printf("say msg:%s to User[age=%d]\n", msg, self.age)
    }
}
User@ orcMain(){
    User@ u = new User()
    u.age = 349
    return u
}