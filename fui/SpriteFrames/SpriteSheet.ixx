module;
#include <string>
#include "Urgc/Urgc.h"
#include "Urgc/GcList.h"

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
    float fps = 10;
    int rows = 9;
    int cols = 8;
    int rowGap = 0; // 行间隔（一般为 0）
    int colGap = 0; // 列间隔（一般为 0）
    Ref<GcList<SpriteSheetAnim>> anims{nullptr, this};

    SpriteSheetInfo() {
        CtorGuard(this);
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
};