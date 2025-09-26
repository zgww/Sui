package OrcLang


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

import * from "./Math.orc"
//受urgc管理的列表


class List {
    void *data 
    extern void ctor()
    extern void dtor()
    
    extern void add(Object *obj) 

    // @return true:添加成功， false: 已存在，没有再添加
    bool addOnce(Object *obj) {
        if (self.has(obj)){
            return false
        }
        self.add(obj)
        return true
    }
    bool remove(Object *obj){
        int idx = self.indexOf(obj);
        if (idx != -1){
            self.removeAt(idx);
            return true
        }
        return false;
    }
    
    bool has(Object *obj){
        int idx = self.indexOf(obj)
        return idx != -1
    }

    extern int indexOf(Object *obj) 
    extern void insert(Object *obj, int at) 
    extern Object* _get(int index)
    Object* get(int index){
        if (index >= 0 && index < self.size()){
            return self._get(index)
        }
        return null
    }
    extern int size() 
    
    extern void removeAt(int idx)

    void clear(){
        for (int i = self.size() - 1; i >= 0; i--){
            self.removeAt(i);
        }
    }

    void removeRange(int start, int end){
        for (int i = start; i < end; i++){
            self.removeAt(start);
        }
    }
    void removeFromStart(int start){
        self.removeRange(start, self.size())
    }
  
    List@ copy(){
        List@ ret = new List()
        for (int i = 0; i < self.size(); i++){
            Object* ele = self.get(i);
            ret.add(ele)
        }

        return ret
    }
}

extern int _getPointerSize();
//指针（不是引用） 数组列表
class PointerArray{
    void **data
    int capacity = 40
    int length = 0

    void ctor(){
        self.data = calloc(self.capacity, _getPointerSize())
    }
    int calcExpandNewCapacity(int newCount){
        int newCapacity = self.capacity + newCount
        if (self.capacity < 1000){
            return maxInt(newCapacity, self.capacity * 2)
        }
        return maxInt(newCapacity, self.capacity + 1000)
    }
    void expand(int newCapacity){
        if (newCapacity > self.capacity){
            self.capacity = newCapacity
            self.data = realloc(self.data, self.capacity * _getPointerSize())
        }
    }
    void expandIfNeed(int newCount){
        if (self.length + newCount > self.capacity){
            int newCapacity = self.calcExpandNewCapacity(newCount)
            self.expand(newCapacity)
        }
    }
    void dtor(){
        if (self.data){
            free(self.data)
            self.data = null
        }
    }

    int size(){
        return self.length
    }

    void add(void *ptr){
        self.expandIfNeed(1)
        self.data[self.length] = ptr;
        self.length = self.length + 1
    }
    void insert(void *ptr, int i){
        if (i > self.length){
            i = self.length
        }
        if (i < 0){
            i = 0
        }

        self.expandIfNeed(1)

        if (i < self.length){
            memmove(self.data + i + 1, self.data+i,  _getPointerSize() * (self.length - i - 1))
        }
        self.data[i] = ptr;
        self.length = self.length + 1
    }
    void removeAt(int i){
        if (i < 0){
            return;
        }
        if (self.length > i){
            memmove(self.data + i, self.data+i+1,  _getPointerSize() * (self.length - i - 1))
            self.length = self.length - 1
        }
    }
}

void List_test(){
    List@ l = new List();

    printf("new list:%p, size:%d\n", l, l.size());


    PointerArray@ parr = new PointerArray()
    parr.add((void*)2)
    parr.add((void*)3)
    parr.add((void*)4)
    parr.insert((void*)1, 0)
    parr.removeAt(2)
    printf("你好parr size:%d p:%p\n", parr.size(), parr);
}