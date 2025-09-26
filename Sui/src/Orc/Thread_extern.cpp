#include "./Thread_orc.h"

#include "./String_orc.h"
#include <unordered_map>
#include <string>
#include <mutex>
#include <thread>
//#include <unordered_set>
 


void Orc$Thread$start(Orc$Thread * self){
    if (self->data != NULL){
        return;
    }
    // Ref<Orc$Thread> refSelf = self;
    //m属于self,所以可以直接用?
    // urgc_ref(-1, );

    //线段引用着self
    urgc_ref((void*)-1L, self, NULL);
    std::thread *m = new std::thread([self, m](){
        Orc$Thread$run(self);
        //线程结束，对self的引用也结束了
        urgc_deref((void*)-1L, self);
        // urgc_deref(self->m);
    });
    // urgc_ref(m, self, NULL);

    m->detach();
    self->data = m;
}
void Orc$Thread$join(Orc$Thread * self){
    std::thread *m = (std::thread*)self->data;
    if (m != NULL){
        m->join();
    }
    // std::mutex *m = (std::mutex*)self->data;
}
void Orc$Thread$freeData(Orc$Thread * self){
    std::thread *m = (std::thread*)self->data;
    if (m != NULL){
        delete m;
        self->data = NULL;
    }
}
void Orc$Thread$initData(Orc$Thread * self){
    // self->data = new std::mutex();
}