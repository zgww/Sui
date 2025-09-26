#include "./Map_orc.h"

#include "./String_orc.h"
#include <unordered_map>
#include <string>
//#include <unordered_set>
 

std::unordered_map<std::string, Object*>* getData(OrcLang$Map* self) {
	return (std::unordered_map<std::string, Object*>*)self->data;
}

void OrcLang$Map$ctor(OrcLang$Map* self) {
	self->data = new std::unordered_map<std::string, Object*>();
}
void OrcLang$Map$dtor(OrcLang$Map* self) {
	auto map = getData(self);
	if (map) {
        //printf("release Map.data\n");
		delete map;
		self->data = NULL;
	}

}
void OrcLang$Map$put(OrcLang$Map* self, char const* key, Object* ele) {
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
        urgc_deref(self, map[key]);// , typeid(T).name());
    }
    if (ele != nullptr) {
        map[key] = ele;
        urgc_ref(self, map[key], NULL);// , typeid(T).name());
    }
    else if (exists) {
        map.erase(it);
    }
}
void OrcLang$Map$del(OrcLang$Map* self, char const* key) {
    OrcLang$Map$put(self, key, NULL);
}
Object* OrcLang$Map$get(OrcLang$Map* self, char const* key) {
    auto& map = *getData(self);
    auto it = map.find(key);
    auto end = map.end();
    auto exists = it != end;
    if (!exists) {
        return NULL;
    }
    return it->second;
}
int OrcLang$Map$size(OrcLang$Map* self) {
    auto& map = *getData(self);
    return map.size();
}



OrcLang$List* OrcLang$Map$keys(OrcLang$List * *__outRef__, OrcLang$Map * self){
    OrcLang$List* list = OrcLang$List_new();

    auto& map = *getData(self);
    for (auto& it : map) {
        URGC_VAR_CLEANUP OrcLang$String* str = NULL;
        OrcLang$str(&str, it.first.c_str());
        list->add(list, (Object*)str);
    }
    return (OrcLang$List*)urgc_set_var_for_return((void**)__outRef__, list);
}