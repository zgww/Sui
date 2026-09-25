#include <stdio.h>

import * from "./Orc/String.orc"

extern String@ _httpGet(const char *url, int port, const char *path, int *status)


void say(){
    printf("hi\n")
}

class  User {
    int age = 0
    void ctor(){
        printf("User.ctor\n")
    }
    void dtor(){
        printf("User.dtor. age=%d\n", self.age)
    }
    void say(const char *msg){
        printf("say msg:%s to User[age=%d]. 更新一下user。 小调整. 编译.c只需要2s, 编译.cpp需要5，6s \n", msg, self.age)
        
        self.onSay = ^void(){
            printf("on   Say\n");
        } 
        self.onSay(); 

        int status = 0;
        String@ body = _httpGet("www.baidu.com", 80, "/", &status)
        printf("get www.baidu.com:%s\nstatus=%d\n", body.str, status)

        body = _httpGet("www.oschina.net", 80, "/", &status)
        printf("get www.baidu.com:%s\nstatus=%d\n", body.str, status)
    }
    void hi(){
    }
    ^void () onSay;
}

User@ orcMain(){
    User@ u = new User()
    u.age = 349
    return u
}