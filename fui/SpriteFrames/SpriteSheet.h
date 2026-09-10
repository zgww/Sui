// Converted from SpriteSheet.ixx (C++20 module) to classic header/source.
#pragma once

#include <string>

#include "Urgc/Urgc.h"
#include "Urgc/GcList.h"

// 精灵表中的一个帧坐标（列, 行）
class SpriteSheetFrameCoord : public GcObj {
public:
    int x = 0;
    int y = 0;
};

// 一段帧动画：按顺序排列的一组帧坐标
class SpriteSheetAnim : public GcObj {
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
class SpriteSheetInfo : public GcObj {
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

// 序列化为 JSON 字符串
std::string SpriteSheetInfo_toJsonString(SpriteSheetInfo* info);

// 从 JSON 字符串反序列化（覆盖 info 内容）
void SpriteSheetInfo_fromJsonString(SpriteSheetInfo* info, const std::string& text);
