#include "./List_orc.h"
#include <vector>


static std::vector<Object*>* getData(OrcLang$List *self) {
	return (std::vector<Object*>*)self->data;
}

void OrcLang$List$ctor(OrcLang$List* self) {
    self->data = new std::vector<Object*>();
}
void OrcLang$List$dtor(OrcLang$List* self) {
    //self->clear(self);//不用调用clear的  析构函数执行时，内部的引用关系不用释放。因为析构执行时，urgc已经知道是孤岛了

    if (self->data) {
        //TODO需要clear
        //printf("释放List   \n");
        delete getData(self);
        self->data = NULL;
    }
}
void OrcLang$List$add(OrcLang$List * self, Object * obj){
    auto data = getData(self);
    data->push_back(obj);
    //记录引用

    urgc_ref(self, obj, NULL);
}
int OrcLang$List$indexOf(OrcLang$List * self, Object * obj){
    auto& vector = *getData(self);

	for (int i = 0, l = vector.size(); i < l; i++){
		if (vector[i] == obj){
			return i;
		}
	}
	return -1;
}
void OrcLang$List$insert(OrcLang$List * self, Object *ele, int idx){
    auto& vector = *getData(self);
    if (idx == -1 || idx >= vector.size()) {
        vector.push_back(ele);
    }
    else {
        vector.insert(vector.begin() + idx, ele);
    }
    urgc_ref(self, ele, NULL);//, typeid(T).name()); //不使用typeid(T),这样才不会一定要有定义

}
Object * OrcLang$List$_get(OrcLang$List * self, int index){
    auto vec = getData(self);
    return vec->at(index);
}
int OrcLang$List$size(OrcLang$List* self) {
    auto vec = getData(self);
    return vec->size();

}
void OrcLang$List$removeAt(OrcLang$List* self, int index) {
    auto vector = getData(self);
    int size = (int)vector->size();
    if (size > 0 && index < size) {
        if (vector->at(index) != nullptr) {
            urgc_deref(self, vector->at(index));//, typeid(T).name());
        }
        vector->erase(vector->begin() + index);
        //return true;
    }
    //return false;
}

int OrcLang$_getPointerSize(){
    return sizeof(void *);
}