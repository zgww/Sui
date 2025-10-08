#include "./Map_orc.h"

#include "./String_orc.h"
#include "Orc/Orc.h"
#include <unordered_map>
#include <string>
//#include <unordered_set>
 

std::unordered_map<std::string, Object*>* getData(Orc$Map* self) {
	return (std::unordered_map<std::string, Object*>*)self->data;
}

void Orc$Map$ctor(Orc$Map* self) {
	self->data = new std::unordered_map<std::string, Object*>();
}
void Orc$Map$dtor(Orc$Map* self) {
	auto map = getData(self);

    //对于引用计数类型的，需要在这里手动解除引用
    for (auto& it : *map) {
        auto obj = it.second;
        if (obj && obj->vtable->refc){
            orc_delRefc(obj);
        }
    }

	if (map) {
        //printf("release Map.data\n");
		delete map;
		self->data = NULL;
	}

}
void Orc$Map$put(Orc$Map* self, char const* key, Object* ele) {
    auto& map = *getData(self);

    //auto deleter = [](void* p) {
    //    //auto tmp = (GcObj*)p;
    //    //printf("GcMap delete by Deleter:%s\n", typeid(*tmp).name());
    //    delete (T*)p;
    //};
    auto it = map.find(key);
    auto end = map.end();
    auto exists = it != end;
    auto old = exists ? it->second : nullptr;

    if (old == ele) {
        return;
    }


    if (old != nullptr) {
        urgc_deref_class(self, map[key]);// , typeid(T).name());
    }
    if (ele != nullptr) {
        map[key] = ele;
        urgc_ref_class(self, map[key], NULL);// , typeid(T).name());
    }
    else if (exists) {
        map.erase(it);
    }
}
void Orc$Map$del(Orc$Map* self, char const* key) {
    Orc$Map$put(self, key, NULL);
}
Object* Orc$Map$get(Orc$Map* self, char const* key) {
    auto& map = *getData(self);
    auto it = map.find(key);
    auto end = map.end();
    auto exists = it != end;
    if (!exists) {
        return NULL;
    }
    return it->second;
}
int Orc$Map$size(Orc$Map* self) {
    auto& map = *getData(self);
    return map.size();
}



Orc$List* Orc$Map$keys(Orc$List * *__outRef__, Orc$Map * self){
    NEW_CLASS_VAR( Orc$List, list);

    auto& map = *getData(self);
    for (auto& it : map) {
        URGC_VAR_CLEANUP Orc$String* str = NULL;
        Orc$str(&str, it.first.c_str());
        list->add(list, (Object*)str);
    }

    return (Orc$List*)urgc_set_var_for_return_class((void**)__outRef__, (Object*)list);
}