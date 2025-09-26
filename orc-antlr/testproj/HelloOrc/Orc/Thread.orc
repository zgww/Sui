package OrcLang

#include <stdio.h>
import * from "./Time.orc"

class Thread {
    ^void () runFunc;

    void *data;

    void ctor(){
        self.initData()
    }
    void dtor(){
        printf("free Thread %p\n", self) 
        self.freeData()
    }

    void run(){
        if (self.runFunc != null){

            self.runFunc()
        }
    }
    extern void initData()
    extern void freeData()
    extern void start()
    extern void join()
}


void testThread(){
    Thread@ t = new Thread()
    int age = 102;
    t.runFunc = ^void (){
        printf("in thread start age :%d\n", age);

        for (int i = 0; i < 10; i++){
            age = i;
            Time_sleepMs(1000)
            printf("hi in thread : i:%d, age:%d\n", i, age)
        }
        printf("thread end\n")
    }
    t.start()

    Time_sleepMs(4000)
    printf("in main: age:%d runFunc:%p\n", age, t.runFunc)
}