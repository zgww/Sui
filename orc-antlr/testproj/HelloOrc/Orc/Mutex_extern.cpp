#include "./Mutex_orc.h"

#include "./String_orc.h"
#include <unordered_map>
#include <string>
#include <mutex>
//#include <unordered_set>
 


void OrcLang$Mutex$lock(OrcLang$Mutex * self){
    std::mutex *m = (std::mutex*)self->data;
    m->lock();
}
void OrcLang$Mutex$unlock(OrcLang$Mutex * self){
    std::mutex *m = (std::mutex*)self->data;
    m->unlock();
}
bool OrcLang$Mutex$tryLock(OrcLang$Mutex * self){
    std::mutex *m = (std::mutex*)self->data;
    bool ret = m->try_lock();
    return ret;
}
void OrcLang$Mutex$freeData(OrcLang$Mutex * self){
    std::mutex *m = (std::mutex*)self->data;
    delete m;
    self->data = NULL;
}
void OrcLang$Mutex$initData(OrcLang$Mutex * self){
    self->data = new std::mutex();
}