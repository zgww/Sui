package Orc


#include <stdio.h>

// 锁

class Mutex {
    void *data;


    void ctor(){
        self.initData()
    }
    void dtor(){
        self.freeData()
        printf("free Mutex:%p\n", self)
    }
    extern void lock()
    extern void unlock()
    extern bool tryLock()
    extern void freeData()
    extern void initData()
}