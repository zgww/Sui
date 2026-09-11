// Converted from ImageCanvasView.ixx (C++20 module) to classic header/source.
#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <string>
#include <algorithm>
#include <cmath>

#include "Core/View.h"
#include "Core/Canvas.h"
#include "Core/Image.h"
#include "Core/Vec2.h"
#include "Core/Mat2d.h"
#include "Core/MouseEvent.h"
#include "Core/Event.h"
#include "Core/Node.h"
#include "Core/App.h"
#include "Core/Window.h"
#include "View/MenuNative.h"
#include "Urgc/Urgc.h"
#include "Urgc/GcMap.h"

#include "SpriteSheet.h"

class ImageCanvasView : public View {
public:
	std::string src;
	float zoom = 1.0f;
	float rotation = 0.0f;
	float panX = 0.0f;
	float panY = 0.0f;

	// 精灵表信息与当前动画（由外部注入，非拥有）
	SpriteSheetInfo* info = nullptr;
	SpriteSheetAnim* curAnim = nullptr;

	Ref<Closure<void(float)>> onZoomChanged{nullptr, this};
	Ref<Closure<void(float)>> onRotationChanged{nullptr, this};
	// 点击某个单元格时回调：参数为 (列 x, 行 y, 是否按了 ctrl)
	Ref<Closure<void(int, int, bool)>> onCellClicked{nullptr, this};

	ImageCanvasView();

	virtual const char* getClassName() const override;

	void setSrc(const std::string& path);

	void zoomIn();

	void zoomOut();

	void center();

	void rotate90();

	void setZoom(float z);

	void onEvent(Event* ev) override;

	void draw_self(Canvas* canvas) override;

private:
	Ref<Image> _img{nullptr, this};
	Ref<GcMap<Image>> _imgCache{nullptr, this};
	bool needFit = false;
	bool isPanning = false;
	bool panMoved = false;
	float panStartX = 0, panStartY = 0;
	float panOffsetStartX = 0, panOffsetStartY = 0;

	bool hasHover = false;
	int hoverCellX = -1, hoverCellY = -1;

	void fitImage();

	void drawCheckerboard(Canvas* canvas);

	// 将鼠标 client 坐标换算到源图左上角坐标
	bool toImageCoord(MouseEvent* me, float* ix, float* iy);

	// 命中检测：返回 (列 x, 行 y)，命中失败返回 false
	bool getCellAt(MouseEvent* me, int* gx, int* gy);

	void updateHover(MouseEvent* me);

	void fillRect(Canvas* canvas, float x, float y, float w, float h, int color);

	void drawSpriteOverlay(Canvas* canvas, float imgW, float imgH);

	void showContextMenu(float clientX, float clientY);

	void fireZoomChanged();

	void fireRotationChanged();
};
