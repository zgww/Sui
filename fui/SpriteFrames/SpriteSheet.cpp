// Converted from SpriteSheet.ixx (C++20 module) to classic header/source.
#include "SpriteSheet.h"

#include "Json/cJSON.h"

// 内部辅助：coord <-> cJSON（不导出）
static cJSON* coordToJson(SpriteSheetFrameCoord* c) {
    cJSON* jo = cJSON_CreateObject();
    cJSON_AddNumberToObject(jo, "x", c->x);
    cJSON_AddNumberToObject(jo, "y", c->y);
    return jo;
}

static void coordFromJson(SpriteSheetFrameCoord* c, cJSON* jo) {
    cJSON* v = cJSON_GetObjectItem(jo, "x");
    if (cJSON_IsNumber(v)) c->x = (int)v->valuedouble;
    v = cJSON_GetObjectItem(jo, "y");
    if (cJSON_IsNumber(v)) c->y = (int)v->valuedouble;
}

static cJSON* animToJson(SpriteSheetAnim* anim) {
    cJSON* jo = cJSON_CreateObject();
    cJSON_AddStringToObject(jo, "name", anim->name.c_str());
    cJSON* arr = cJSON_CreateArray();
    for (int i = 0; i < anim->coords->size(); i++) {
        cJSON_AddItemToArray(arr, coordToJson(anim->coords->get(i)));
    }
    cJSON_AddItemToObject(jo, "coords", arr);
    return jo;
}

static void animFromJson(SpriteSheetAnim* anim, cJSON* jo) {
    cJSON* v = cJSON_GetObjectItem(jo, "name");
    if (cJSON_IsString(v) && v->valuestring) {
        anim->name = v->valuestring;
    }
    anim->coords->clear();
    cJSON* arr = cJSON_GetObjectItem(jo, "coords");
    if (cJSON_IsArray(arr)) {
        int n = cJSON_GetArraySize(arr);
        for (int i = 0; i < n; i++) {
            cJSON* e = cJSON_GetArrayItem(arr, i);
            Ref<SpriteSheetFrameCoord> c{new SpriteSheetFrameCoord()};
            coordFromJson(c.get(), e);
            anim->coords->push(c.get());
        }
    }
}

// 序列化为 JSON 字符串
std::string SpriteSheetInfo_toJsonString(SpriteSheetInfo* info) {
    cJSON* jo = cJSON_CreateObject();
    cJSON_AddStringToObject(jo, "image", info->image.c_str());
    cJSON_AddNumberToObject(jo, "fps", info->fps);
    cJSON_AddNumberToObject(jo, "rows", info->rows);
    cJSON_AddNumberToObject(jo, "cols", info->cols);
    cJSON_AddNumberToObject(jo, "rowGap", info->rowGap);
    cJSON_AddNumberToObject(jo, "colGap", info->colGap);

    cJSON* arr = cJSON_CreateArray();
    for (int i = 0; i < info->anims->size(); i++) {
        cJSON_AddItemToArray(arr, animToJson(info->anims->get(i)));
    }
    cJSON_AddItemToObject(jo, "anims", arr);

    char* text = cJSON_Print(jo);
    std::string ret = text ? text : "";
    if (text) cJSON_free(text);
    cJSON_Delete(jo);
    return ret;
}

// 从 JSON 字符串反序列化（覆盖 info 内容）
void SpriteSheetInfo_fromJsonString(SpriteSheetInfo* info, const std::string& text) {
    cJSON* jo = cJSON_Parse(text.c_str());
    if (!jo) {
        return;
    }

    cJSON* v = cJSON_GetObjectItem(jo, "image");
    info->image = (cJSON_IsString(v) && v->valuestring) ? v->valuestring : "";

    v = cJSON_GetObjectItem(jo, "fps");
    if (cJSON_IsNumber(v)) info->fps = (float)v->valuedouble;
    v = cJSON_GetObjectItem(jo, "rows");
    if (cJSON_IsNumber(v)) info->rows = (int)v->valuedouble;
    v = cJSON_GetObjectItem(jo, "cols");
    if (cJSON_IsNumber(v)) info->cols = (int)v->valuedouble;
    v = cJSON_GetObjectItem(jo, "rowGap");
    if (cJSON_IsNumber(v)) info->rowGap = (int)v->valuedouble;
    v = cJSON_GetObjectItem(jo, "colGap");
    if (cJSON_IsNumber(v)) info->colGap = (int)v->valuedouble;

    info->anims->clear();
    cJSON* arr = cJSON_GetObjectItem(jo, "anims");
    if (cJSON_IsArray(arr)) {
        int n = cJSON_GetArraySize(arr);
        for (int i = 0; i < n; i++) {
            cJSON* e = cJSON_GetArrayItem(arr, i);
            Ref<SpriteSheetAnim> a{new SpriteSheetAnim()};
            animFromJson(a.get(), e);
            info->anims->push(a.get());
        }
    }

    cJSON_Delete(jo);
}
