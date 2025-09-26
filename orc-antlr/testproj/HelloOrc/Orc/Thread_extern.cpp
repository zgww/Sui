#include "./Thread_orc.h"

#include "./String_orc.h"
#include <unordered_map>
#include <string>
#include <mutex>
#include <thread>
//#include <unordered_set>
 


void OrcLang$Thread$start(OrcLang$Thread * self){
    if (self->data != NULL){
        return;
    }
    // Ref<OrcLang$Thread> refSelf = self;
    //m属于self,所以可以直接用?
    // urgc_ref(-1, );

    //线段引用着self
    urgc_ref((void*)-1L, self, NULL);
    std::thread *m = new std::thread([self, m](){
        OrcLang$Thread$run(self);
        //线程结束，对self的引用也结束了
        urgc_deref((void*)-1L, self);
        // urgc_deref(self->m);
    });
    // urgc_ref(m, self, NULL);

    m->detach();
    self->data = m;
}
void OrcLang$Thread$join(OrcLang$Thread * self){
    std::thread *m = (std::thread*)self->data;
    if (m != NULL){
        m->join();
    }
    // std::mutex *m = (std::mutex*)self->data;
}
void OrcLang$Thread$freeData(OrcLang$Thread * self){
    std::thread *m = (std::thread*)self->data;
    if (m != NULL){
        delete m;
        self->data = NULL;
    }
}
void OrcLang$Thread$initData(OrcLang$Thread * self){
    // self->data = new std::mutex();
}