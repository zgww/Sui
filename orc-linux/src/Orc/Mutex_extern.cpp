#include "./Mutex_orc.h"

#include "./String_orc.h"
#include <unordered_map>
#include <string>
#include <mutex>
//#include <unordered_set>
 


void Orc$Mutex$lock(Orc$Mutex * self){
    std::mutex *m = (std::mutex*)self->data;
    m->lock();
}
void Orc$Mutex$unlock(Orc$Mutex * self){
    std::mutex *m = (std::mutex*)self->data;
    m->unlock();
}
bool Orc$Mutex$tryLock(Orc$Mutex * self){
    std::mutex *m = (std::mutex*)self->data;
    bool ret = m->try_lock();
    return ret;
}
void Orc$Mutex$freeData(Orc$Mutex * self){
    std::mutex *m = (std::mutex*)self->data;
    delete m;
    self->data = NULL;
}
void Orc$Mutex$initData(Orc$Mutex * self){
    self->data = new std::mutex();
}