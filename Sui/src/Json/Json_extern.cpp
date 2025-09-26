
#include "./Json_orc.h"
#include <unordered_map>
#include <string>
#include <stdatomic.h>

#include "../Orc/Time_orc.h"
#include "Orc/Orc.h"


static 
// Json$Json* 
void 
fromCJson(Json$Json** __outRef__, cJSON* jo){
    // NEW_CLASS_VAR(Json$Json, ret);
    if (__outRef__ == NULL){
        return;
    }
    //直接使用outRef使用owner, 减少引用事件
    Json$Json* ret = Json$Json_new(__outRef__);

    if (cJSON_IsNull(jo)){
        ret->setNull(ret);
    }
    else if (cJSON_IsNumber(jo)){
        ret->setNumber(ret, cJSON_GetNumberValue(jo));
    }
    else if (cJSON_IsBool(jo)){
        ret->setBool(ret, cJSON_IsTrue(jo));
    }
    else if (cJSON_IsString(jo)){
        ret->setCstr(ret, cJSON_GetStringValue(jo));
    }
    else if (cJSON_IsArray(jo)){
        int l = cJSON_GetArraySize(jo);
        ret->initList(ret);

        cJSON* child = jo->child;

        while (child){
            URGC_VAR_CLEANUP_CLASS Json$Json *kid = NULL;
            fromCJson(&kid, child);
            ret->add(ret, kid);

            child = child->next;
        }
        
        // for (int i = 0; i< l; i++){
        //     URGC_VAR_CLEANUP_CLASS Json$Json *kid = NULL;
        //     auto kidJo = cJSON_GetArrayItem(jo, i);
        //     fromCJson(&kid, kidJo);

        //     ret->add(ret, kid);
        // }
    }
    else if (cJSON_IsObject(jo)){
        ret->initMap(ret);
        cJSON* child = jo->child;


        while (child){
            const char *key = child->string;

            URGC_VAR_CLEANUP_CLASS Json$Json *kid = NULL;
            fromCJson(&kid, child);
            ret->put(ret, key, kid);

            child = child->next;
        }
    }
    // return (Json$Json*)URGC_RETURN_CLASS(ret);
}

static cJSON * toCJson(Json$Json* self){
    if (self->kind == 0){
        return cJSON_CreateNull();
    }
    if (self->kind == 1){
        return cJSON_CreateBool(self->boolValue);
    }
    if (self->kind == 2){
        return cJSON_CreateNumber(self->numberValue);
    }
    if (self->kind == 3){
        return cJSON_CreateString(self->stringValue ? self->stringValue->str : "");
    }
    if (self->kind == 4){
        if (self->map == NULL){
            return  cJSON_CreateNull();
        }

        auto obj = cJSON_CreateObject();
        URGC_VAR_CLEANUP_CLASS Orc$List* keys = NULL;
        self->map->keys(&keys, self->map);

        for (int i = 0, l = keys->size(keys); i < l; i++){
            Orc$String* key = (Orc$String*)keys->get(keys, i);
            Json$Json* val = (Json$Json*)self->map->get(self->map, key->str);
            auto valCJson = toCJson(val);
            cJSON_AddItemToObject(obj, key->str, valCJson);
        }

        return obj;
    }
    if (self->kind == 5){
        if (self->list == NULL){
            return cJSON_CreateNull();
        }
        auto arr = cJSON_CreateArray();

        for (int i = 0, l = self->list->size(self->list); i < l; i++){
            Json$Json* val = (Json$Json*)self->list->get(self->list, i);
            auto valCJson = toCJson(val);
            cJSON_AddItemToArray(arr, valCJson);
        }
        return arr;
    }
    return NULL;
}

Orc$String*  Json$Json$dump(
    Orc$String **  __outRef__, 
    Json$Json *  self)
{
    auto cjo = toCJson(self);
    char *s = cJSON_Print(cjo);
    cJSON_Delete(cjo);

    NEW_CLASS_VAR(Orc$String, ret);
    Orc$String$set_as_own(ret, s);

    return (Orc$String*)URGC_RETURN_CLASS(ret);
}
Json$Json*  Json$Json_parse(Json$Json **  __outRef__, const char *  s){
    auto tz0 = Orc$Time_unixMs();
    // printf("#%d Json_parse\n", __LINE__);
    cJSON *jo = cJSON_Parse(s);
    auto tz1 = Orc$Time_unixMs();
    // printf("#%d Json_parse cjson parse:%lldms\n", __LINE__, tz1 - tz0);

    URGC_VAR_CLEANUP_CLASS Json$Json *ret = NULL;
    // printf("#%d Json_parse\n", __LINE__);

    auto t0 = Orc$Time_unixMs();
    fromCJson(&ret, jo);
    auto t1 = Orc$Time_unixMs();
    // printf("#%d Json_parse:%lld\n", __LINE__, t1 - t0);

    cJSON_Delete(jo);
    // printf("#%d Json_parse\n", __LINE__);

    return (Json$Json*)URGC_RETURN_CLASS(ret);
}
