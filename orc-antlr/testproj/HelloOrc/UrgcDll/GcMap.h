

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "Urgc.h"

/*
用来存放可gc的指针
元素只能存放new出来的指针 
*/
template <typename T>
class GcMap : public GcObj
{
public:
    ~GcMap(){
        //printf("~GcMap\n");
        clear();
        //for (auto entry: map){
        //    urgc.deref(this, entry.second, typeid(T).name());
        //}
        //map.clear();
    }
    bool contains(T* ele) {
        auto exists = map.contains(ele);
        return exists;
	}
    //按value反查key
    string findKey(T*ele) {
        for (auto &entry: map){
            if (entry.second == ele) {
                return entry.first;
            }
        }
        return "";
    }
    void set(std::string key, T *ele)
    {
        auto deleter = [](void *p){
            //auto tmp = (GcObj*)p;
            //printf("GcMap delete by Deleter:%s\n", typeid(*tmp).name());
            delete (T*)p;
        };
        auto it = map.find(key);
        auto end = map.end();
        auto exists = it != end;
        auto old = exists ? it->second : nullptr;

        if (old == ele) {
            return;
        }


        if (old != nullptr){
            urgc.deref(this, map[key]);// , typeid(T).name());
        }
        if (ele != nullptr){
            map[key] = ele;
            urgc.ref(this, map[key], deleter);// , typeid(T).name());
        } else if (exists) {
            map.erase(it);
        }
    }

    void remove(std::string key){
        set(key, nullptr);
    }
    void clear() {
        for (auto entry: map){
            urgc.deref(this, entry.second);// , typeid(T).name());
        }
        map.clear();
    }
    int size()
    {
        return map.size();
    }
    bool hasKey(string key) {
        auto it = map.find(key);
        auto end = map.end();
        auto exists = it != end;
        return exists;
    }
    Ref<T> get(string key){
        auto it = map.find(key);
        auto end = map.end();
        auto exists = it != end;
        if (!exists){
            return nullptr;
        }
        return it->second;
    }

//protected:
    std::unordered_map<string, T*> map;
};

/*
用来存放可gc的指针
元素只能存放new出来的指针 
*/
template <typename T>
class GcSet : public GcObj
{
public:
    ~GcSet(){
        //printf("~GcMap\n");
        clear();
        //for (auto entry: map){
        //    urgc.deref(this, entry.second, typeid(T).name());
        //}
        //map.clear();
    }
	void insert(T* obj) {
		auto it = set.find(obj);
        if (it == set.end()) {//不存在
            urgc.ref(this, obj, nullptr);// , typeid(T).name());
            set.insert(obj);
        }
	}
    void remove(T* obj){
		auto it = set.find(obj);
        if (it != set.end()) {//存在
            urgc.deref(this, obj);// , typeid(T).name());
            set.erase(it);
        }
    }
    void clear() {
        for (auto e: set){
            urgc.deref(this, e);// , typeid(T).name());
        }
        set.clear();
    }
    int size()
    {
        return set.size();
    }
    bool contains(T* obj) {
        return set.contains(obj);
    }

//protected:
    std::unordered_set<T*> set;
};