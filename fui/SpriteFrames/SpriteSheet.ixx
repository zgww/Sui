module;
#include <string>
#include "Urgc/Urgc.h"
#include "Urgc/GcList.h"
#include "Json/cJSON.h"

export module SpriteSheet;

// 精灵表中的一个帧坐标（列, 行）
export class SpriteSheetFrameCoord : public GcObj {
public:
    int x = 0;
    int y = 0;
};

// 一段帧动画：按顺序排列的一组帧坐标
export class SpriteSheetAnim : public GcObj {
public:
    std::string name;
    Ref<GcList<SpriteSheetFrameCoord>> coords{nullptr, this};

    SpriteSheetAnim() {
        CtorGuard g(this);
        coords = new GcList<SpriteSheetFrameCoord>();
    }

    // 查找帧 (x, y) 在动画中的顺序索引，不存在返回 -1
    int getIndexOfFrame(int x, int y) {
        for (int i = 0; i < coords->size(); i++) {
            SpriteSheetFrameCoord* e = coords->get(i);
            if (e->x == x && e->y == y) {
                return i;
            }
        }
        return -1;
    }

    // 按顺序追加一帧，若已存在则忽略
    void addFrame(int x, int y) {
        if (getIndexOfFrame(x, y) != -1) {
            return;
        }
        Ref<SpriteSheetFrameCoord> e{new SpriteSheetFrameCoord()};
        e->x = x;
        e->y = y;
        coords->push(e.get());
    }

    // 移除坐标 (x, y) 对应的全部帧
    void removeFrame(int x, int y) {
        for (int i = 0; i < coords->size(); i++) {
            SpriteSheetFrameCoord* e = coords->get(i);
            if (e->x == x && e->y == y) {
                coords->remove_at(i);
                i--;
            }
        }
    }
};

// 精灵表信息：切片参数 + 所有动画
export class SpriteSheetInfo : public GcObj {
public:
    std::string image; // 精灵表图片路径（可选）
    float fps = 10;
    int rows = 9;
    int cols = 8;
    int rowGap = 0; // 行间隔（一般为 0）
    int colGap = 0; // 列间隔（一般为 0）
    Ref<GcList<SpriteSheetAnim>> anims{nullptr, this};

    SpriteSheetInfo() {
        CtorGuard g(this);
        anims = new GcList<SpriteSheetAnim>();
    }

    SpriteSheetAnim* getAnimByName(const std::string& name) {
        for (int i = 0; i < anims->size(); i++) {
            SpriteSheetAnim* anim = anims->get(i);
            if (anim->name == name) {
                return anim;
            }
        }
        return nullptr;
    }

    // 单个单元格的宽度（扣除列间隔后均分）
    float getCellWidth(int imgW) const {
        if (cols <= 0) return 0.0f;
        return (float)(imgW - (cols - 1) * colGap) / cols;
    }

    // 单个单元格的高度（扣除行间隔后均分）
    float getCellHeight(int imgH) const {
        if (rows <= 0) return 0.0f;
        return (float)(imgH - (rows - 1) * rowGap) / rows;
    }

    // 第 col 列帧在源图上的 x 偏移（含列间隔）
    int getFrameSrcX(int col, int imgW) const {
        return (int)(col * (getCellWidth(imgW) + colGap));
    }

    // 第 row 行帧在源图上的 y 偏移（含行间隔）
    int getFrameSrcY(int row, int imgH) const {
        return (int)(row * (getCellHeight(imgH) + rowGap));
    }
};

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
export std::string SpriteSheetInfo_toJsonString(SpriteSheetInfo* info) {
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
export void SpriteSheetInfo_fromJsonString(SpriteSheetInfo* info, const std::string& text) {
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