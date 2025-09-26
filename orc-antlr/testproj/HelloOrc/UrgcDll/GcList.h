#pragma once

#include <vector>
#include <functional>
#include "Urgc.h"
#include <mutex>

/*
用来存放可gc的指针
元素只能存放new出来的指针 
*/
template <typename T>
class GcList:public GcObj{
public:
    GcList() {
    }
    GcList(std::initializer_list<T*> init_list) {
        CtorGuard g(this);

        for (auto e : init_list) {
            push(e);
        }
    }
    virtual ~GcList(){
        // printf("~GcList\n");
        for (auto p: vector){
            urgc.deref(this, p, ""/*typeid(T).name()*/);
        }
        vector.clear();
    }
    void push_all(GcList<T>* src){
        // printf("GcList.push_all:%p\n", src);
        // printf("GcList.push_all:%p:%d\n", src, src->size());
        for (int i = 0, l = src->size(); i < l; i++){
            auto e = src->get(i);
            // printf("GcList.get:%p\n", e);
            if (e != nullptr){
                push(e);
            }
        }
    }
    void push(T *ele)
    {
        set_at(size(), ele);
    }
    void push_once(T *ele)
    {
        if (!include(ele)) {
			set_at(size(), ele);
        }
    }
    int size()
    {
        return (int)vector.size();
    }
    void insert_before(T* ele, T* rel) {
        auto idx = index_of(rel);
        //-1时，就附到最后
        //

        if (idx == -1) {
            push(ele);
        }
        else {
			insert_at(idx, ele);
        }
    }
    void insert_after(T* ele, T* rel) {
        auto idx = index_of(rel);
        //-1时，就插入到0位
        insert_at(idx + 1, ele);
    }
    void insert_at(int idx, T*ele){
        if (idx == -1 || idx >= vector.size()){
            vector.push_back(ele);
        } else {
            vector.insert(vector.begin() + idx, ele);
        }
        urgc.ref(this, ele, deleter);//, typeid(T).name()); //不使用typeid(T),这样才不会一定要有定义
    }
    std::function<void(void*)> deleter = [](void *p){
        auto obj = (GcObj*)p;
        printf("GcListDeleter:%s\n", typeid(*(GcObj*)p).name());
        delete obj;
    };
    void set_at(int idx, T *ele)
    {
        if (idx >= vector.size())
        {
            vector.push_back(ele);
            urgc.ref(this, ele, deleter );//, typeid(ele).name());
        }
        else
        {
            if (vector[idx] != nullptr){
                urgc.deref(this, vector[idx]);//, typeid(T).name());
            }
            vector[idx] = ele;
            urgc.ref(this, ele, deleter);// , typeid(ele).name());
        }
    }

    //用Ref引用。 因为pop,有可能导致对象被释放了
    //
    Ref<T> pop()
    {
        Ref<T> ele = last();
        auto size = vector.size();
        remove_at(size - 1);
        return ele;
    }
    Ref<T> last() {
        return get(size() - 1);
    }
    T* get(int index){
        if (index < 0 || index >= size()){
            return nullptr;
        }
        return vector[index];
    }
    bool include(T* ele) {
        return index_of(ele) != -1;
    }

    GcList<T>& clear(){
        while (size() > 0){
            pop();
        }
        return *this;
    }
    template <typename TARGET>
    T* get_by_fn(std::function<bool(T*, TARGET)> fn, TARGET t) {
        auto idx = index_of_by_fn(fn, t);
        return get(idx);
    }
    template <typename TARGET>
    int index_of_by_fn(std::function<bool(T*, TARGET)> fn, TARGET t) {
        for (int i = 0, l = size(); i < l; i++){
            if (fn(vector[i], t)) {
                return i;
            }
        }
        return -1;
    }
    int index_of(T*ele){
        for (int i = 0, l = size(); i < l; i++){
            if (vector[i] == ele){
                return i;
            }
        }
        return -1;
    }
    template <typename TARGET>
    bool remove_first_by_fn(std::function<bool(T*, TARGET)> fn, TARGET t) {
        for (int i = 0, l = size(); i < l; i++){
            if (fn(vector[i], t)) {
                return remove_at(i);
            }
        }
        return false;
    }
    bool remove(T* ele){
        int idx = index_of(ele);
        if (idx != -1){
            return remove_at(idx);
        }
        return false;
    }
    bool remove_at(int index)
    {
        int size = (int)vector.size();
        if (size > 0 && index < size)
        {
            if (vector[index] != nullptr){
                urgc.deref(this, vector[index]);//, typeid(T).name());
            }
            vector.erase(vector.begin() + index);
            return true;
        }
        return false;
    }

//protected:
    std::vector<T*> vector;
};


template <typename T>
class GcListWithLock :public GcObj {
public:
    GcListWithLock() {
    }
    GcListWithLock(std::initializer_list<T*> init_list) {
        CtorGuard g(this);

        for (auto e : init_list) {
            push(e);
        }
    }
    virtual ~GcListWithLock() {
        // printf("~GcList\n");
        for (auto p : vector) {
            urgc.deref(this, p);//, typeid(T).name());
        }
        vector.clear();
    }
    void push_all(GcListWithLock<T>* src) {

        // printf("GcList.push_all:%p\n", src);
        // printf("GcList.push_all:%p:%d\n", src, src->size());
        for (int i = 0, l = src->size(); i < l; i++) {
            auto e = src->get(i);
            // printf("GcList.get:%p\n", e);
            if (e != nullptr) {
                push(e);
            }
        }
    }
    void push(T* ele)
    {
        std::lock_guard<std::recursive_mutex> g(mutex);

        set_at(size(), ele);
    }
    void push_once(T* ele)
    {
        std::lock_guard<std::recursive_mutex> g(mutex);

        if (!include(ele)) {
            set_at(size(), ele);
        }
    }
    int size()
    {
        std::lock_guard<std::recursive_mutex> g(mutex);
        return (int)vector.size();
    }
    void insert_before(T* ele, T* rel) {
        std::lock_guard<std::recursive_mutex> g(mutex);

        auto idx = index_of(rel);
        //-1时，就附到最后
        if (idx == -1) {
            push(ele);
        }
        else {
            insert_at(idx, ele);
        }
    }
    void insert_after(T* ele, T* rel) {
        std::lock_guard<std::recursive_mutex> g(mutex);

        auto idx = index_of(rel);
        //-1时，就插入到0位
        insert_at(idx + 1, ele);
    }
    void insert_at(int idx, T* ele) {
        std::lock_guard<std::recursive_mutex> g(mutex);

        if (idx >= vector.size()) {
            vector.push_back(ele);
        }
        else {
            vector.insert(vector.begin() + idx, ele);
        }
        urgc.ref(this, ele, deleter);// , typeid(T).name());
    }
    std::function<void(void*)> deleter = [](void* p) {
        delete (GcObj*)p;
    };
    void set_at(int idx, T* ele)
    {
        std::lock_guard<std::recursive_mutex> g(mutex);


        if (idx >= vector.size())
        {
            vector.push_back(ele);
            urgc.ref(this, ele, deleter);// , typeid(T).name());
        }
        else
        {
            if (vector[idx] != nullptr) {
                urgc.deref(this, vector[idx]);//, typeid(T).name());
            }
            vector[idx] = ele;
            urgc.ref(this, ele, deleter);// , typeid(T).name());
        }
    }

    //用Ref引用。 因为pop,有可能导致对象被释放了
    Ref<T> pop()
    {
        std::lock_guard<std::recursive_mutex> g(mutex);

        Ref<T> ele = last();
        auto size = vector.size();
        remove_at(size - 1);
        return ele;
    }
    Ref<T> last() {
        return get(size() - 1);
    }
    T* get(int index) {
        std::lock_guard<std::recursive_mutex> g(mutex);

        if (index < 0 || index >= size()) {
            return nullptr;
        }
        return vector[index];
    }
    bool include(T* ele) {
        return index_of(ele) != -1;
    }

    void clear() {
        std::lock_guard<std::recursive_mutex> g(mutex);

        while (size() > 0) {
            pop();
        }
    }
    template <typename TARGET>
    T* get_by_fn(std::function<bool(T*, TARGET)> fn, TARGET t) {
        std::lock_guard<std::recursive_mutex> g(mutex);

        auto idx = index_of_by_fn(fn, t);
        return get(idx);
    }
    template <typename TARGET>
    int index_of_by_fn(std::function<bool(T*, TARGET)> fn, TARGET t) {
        std::lock_guard<std::recursive_mutex> g(mutex);

        for (int i = 0, l = size(); i < l; i++) {
            if (fn(vector[i], t)) {
                return i;
            }
        }
        return -1;
    }
    int index_of(T* ele) {
        std::lock_guard<std::recursive_mutex> g(mutex);

        for (int i = 0, l = size(); i < l; i++) {
            if (vector[i] == ele) {
                return i;
            }
        }
        return -1;
    }
    template <typename TARGET>
    bool remove_first_by_fn(std::function<bool(T*, TARGET)> fn, TARGET t) {
        std::lock_guard<std::recursive_mutex> g(mutex);

        for (int i = 0, l = size(); i < l; i++) {
            if (fn(vector[i], t)) {
                return remove_at(i);
            }
        }
        return false;
    }
    bool remove(T* ele) {
        std::lock_guard<std::recursive_mutex> g(mutex);

        int idx = index_of(ele);
        if (idx != -1) {
            return remove_at(idx);
        }
        return false;
    }
    bool remove_at(int index)
    {
        std::lock_guard<std::recursive_mutex> g(mutex);

        int size = (int)vector.size();
        if (size > 0 && index < size)
        {
            if (vector[index] != nullptr) {
                urgc.deref(this, vector[index]);//, typeid(T).name());
            }
            vector.erase(vector.begin() + index);
            return true;
        }
        return false;
    }

    std::recursive_mutex mutex;
protected:
    std::vector<T*> vector;
};