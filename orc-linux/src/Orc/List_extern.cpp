#include "./List_orc.h"
#include <vector>


static std::vector<Object*>* getData(Orc$List *self) {
	return (std::vector<Object*>*)self->data;
}

void Orc$List$ctor(Orc$List* self) {
    self->data = new std::vector<Object*>();
}
void Orc$List$dtor(Orc$List* self) {
    //self->clear(self);//不用调用clear的  析构函数执行时，内部的引用关系不用释放。因为析构执行时，urgc已经知道是孤岛了

    //需要考虑，如果元素是refc类型的话，就需要手动解引用。因为refc不归urgc管...
    auto& vector = *getData(self);
	for (int i = 0, l = vector.size(); i < l; i++){
        auto obj = vector[i];
        if (obj && obj->vtable->refc){
            orc_delRefc(obj);
        }
    }

    if (self->data) {
        //TODO需要clear
        //printf("释放List   \n");
        delete getData(self);
        self->data = NULL;
    }
}
void Orc$List$add(Orc$List * self, Object * obj){
    auto data = getData(self);
    data->push_back(obj);
    //记录引用

    // urgc_ref(self, obj, NULL);
    urgc_ref_class(self, obj, NULL);
}
int Orc$List$indexOf(Orc$List * self, Object * obj){
    auto& vector = *getData(self);

	for (int i = 0, l = vector.size(); i < l; i++){
		if (vector[i] == obj){
			return i;
		}
	}
	return -1;
}
void Orc$List$insert(Orc$List * self, Object *ele, int idx){
    auto& vector = *getData(self);
    if (idx == -1 || idx >= vector.size()) {
        vector.push_back(ele);
    }
    else {
        vector.insert(vector.begin() + idx, ele);
    }
    urgc_ref_class(self, ele, NULL);//, typeid(T).name()); //不使用typeid(T),这样才不会一定要有定义

}
Object * Orc$List$_get(Orc$List * self, int index){
    auto vec = getData(self);
    return vec->at(index);
}
int Orc$List$size(Orc$List* self) {
    auto vec = getData(self);
    if (vec){
        int s = vec->size();
        return s;
    }
    return 0;

}
void Orc$List$removeAt(Orc$List* self, int index) {
    auto vector = getData(self);
    int size = (int)vector->size();
    if (size > 0 && index < size) {
        if (vector->at(index) != nullptr) {
            urgc_deref_class(self, vector->at(index));//, typeid(T).name());
            // printf("urgc_deref_class:%p=>%p\n", self, vector->at(index));
        }
        vector->erase(vector->begin() + index);
        //return true;
    }
    //return false;
}

int Orc$_getPointerSize(){
    return sizeof(void *);
}
bool  Orc$List$swap(Orc$List *  self, int  fIndex, int  tIndex){
    auto& vector = *getData(self);
    int size = (int)vector.size();

    if (fIndex >= 0 && fIndex < size && tIndex >= 0 &&
        tIndex < size && fIndex != tIndex) {
        Object *tmp = vector[fIndex];
        vector[fIndex] = vector[tIndex];
        vector[tIndex] = tmp;
        return true;
    }
    return false;
}
void  Orc$List$resize(Orc$List *  self, int  size){
    auto& vector = *getData(self);
    vector.resize(size);
}
void  Orc$List$set(Orc$List *  self, int  idx, Object *  obj){
    auto& vector = *getData(self);
    if (idx >= vector.size()){
        vector.resize(idx+1);
    }

    Object* prev = vector[idx];
    urgc_deref_class(self, prev);//, typeid(T).name());

    vector[idx] = obj;
    urgc_ref_class(self, obj, NULL);//, typeid(T).name()); //不使用typeid(T),这样才不会一定要有定义
}