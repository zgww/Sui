package Orc
#include <stdio.h>
import * from "./List.orc"
import * from "./String.orc"

//受urgc管理的map
class Map {

    extern void ctor()
    extern void dtor()

    extern void put(const char *key, Object *obj) 
    extern void del(const char *key) 

    bool has(const char *key){
        return self.get(key) != NULL
    }

    extern Object* get(const char *key)

    void clear(){
        List@ keys = self.keys()
        int l = keys.size();
        for (int i = 0; i < l; i++){
            String@ key = (String@)keys.get(i)
            self.del(key.str)
        }
    }

    // //List<String>@
    extern List@ keys()

    extern int size()
    
    void *data
}


void Map_test(){
    Map@ l = new Map();
    l.put("id", str("id"))
    l.put("name", str("zgwww"))
    

    printf("new map:%p\n", l);

    String@ id = (String@)l.get("id")
    String@ name = (String@)l.get("name")
    printf("id:%s %s\n", id.str, name.str)

}