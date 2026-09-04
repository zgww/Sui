module;
#define NOMINMAX
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

export module ImageCanvasView;
import SpriteSheet;

export class ImageCanvasView : public View {
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

	ImageCanvasView() {
		backgroundColor = 0xff1a1a1a;
		needClip = true;
		_imgCache = new GcMap<Image>();
	}

	virtual const char* getClassName() const override { return "ImageCanvasView"; }

	void setSrc(const std::string& path) {
		if (src == path) return;
		src = path;
		_img = _imgCache->get(src);
		needFit = true;
		invalidDraw();
	}

	void zoomIn() {
		zoom *= 1.2f;
		invalidDraw();
		fireZoomChanged();
	}

	void zoomOut() {
		zoom /= 1.2f;
		if (zoom < 0.02f) zoom = 0.02f;
		invalidDraw();
		fireZoomChanged();
	}

	void center() {
		needFit = true;
		rotation = 0.0f;
		panX = 0;
		panY = 0;
		invalidDraw();
		fireZoomChanged();
		fireRotationChanged();
	}

	void rotate90() {
		rotation += 3.14159265358979f / 2.0f;
		invalidDraw();
		fireRotationChanged();
	}

	void setZoom(float z) {
		zoom = z;
		if (zoom < 0.02f) zoom = 0.02f;
		invalidDraw();
		fireZoomChanged();
	}

	void onEvent(Event* ev) override {
		View::onEvent(ev);
		if (ev->isStopPropagation) return;

		if (auto le = dynamic_cast<MouseLeaveEvent*>(ev)) {
			if (hasHover) {
				hasHover = false;
				invalidDraw();
			}
			return;
		}

		if (auto we = dynamic_cast<WheelEvent*>(ev)) {
			if (we->isCapture) return;
			float delta = we->deltaY;
			float oldZoom = zoom;
			if (delta < 0) {
				zoom *= 1.15f;
			} else {
				zoom /= 1.15f;
			}
			if (zoom < 0.02f) zoom = 0.02f;
			if (zoom > 200.0f) zoom = 200.0f;

			Vec2 sz = getSizeWithoutMargin();
			float cx = sz.x / 2.0f;
			float cy = sz.y / 2.0f;
			Vec2 absPos = localToWorld(margin.left, margin.top);
			float mx = we->clientX - absPos.x - cx;
			float my = we->clientY - absPos.y - cy;
			panX = mx - (mx - panX) * (zoom / oldZoom);
			panY = my - (my - panY) * (zoom / oldZoom);

			invalidDraw();
			fireZoomChanged();
			ev->stopPropagation();
			return;
		}

		if (auto me = dynamic_cast<MouseEvent*>(ev)) {
			// 悬停追踪
			if (me->isMouseMove) {
				updateHover(me);
			}

			// 右键按下开始平移
			if (me->isMouseDown && me->button == 2) {
				isPanning = true;
				panMoved = false;
				panStartX = me->clientX;
				panStartY = me->clientY;
				panOffsetStartX = panX;
				panOffsetStartY = panY;
				ev->stopPropagation();
				return;
			}
			// 右键拖动平移
			if (me->isMouseMove && isPanning) {
				float dx = me->clientX - panStartX;
				float dy = me->clientY - panStartY;
				if (std::abs(dx) > 3 || std::abs(dy) > 3) {
					panMoved = true;
				}
				panX = panOffsetStartX + dx;
				panY = panOffsetStartY + dy;
				invalidDraw();
				return;
			}
			// 右键弹起
			if (me->isMouseUp && me->button == 2) {
				bool wasPanning = isPanning;
				isPanning = false;
				if (wasPanning && !panMoved) {
					showContextMenu(me->clientX, me->clientY);
				}
				ev->stopPropagation();
				return;
			}

			// 左键点击选帧（button 0 = 左键）
			if (me->isMouseDown && me->button == 0) {
				int gx = 0, gy = 0;
				if (getCellAt(me, &gx, &gy)) {
					if (onCellClicked) onCellClicked->invoke(gx, gy, me->ctrl);
					ev->stopPropagation();
					return;
				}
			}
		}
	}

	void draw_self(Canvas* canvas) override {
		View::draw_self(canvas);

		drawCheckerboard(canvas);

		if (needFit) {
			fitImage();
			needFit = false;
		}

		if (!_img && !src.empty()) {
			_img = _imgCache->get(src);
			if (!_img) {
				_img = canvas->createImage(src.c_str());
				if (_img) {
					_imgCache->set(src, _img.get());
				}
			}
			if (_img) {
				needFit = true;
				fitImage();
				needFit = false;
			}
		}

		if (!_img) return;

		Vec2 sz = getSizeWithoutMargin();
		float imgW = _img->width();
		float imgH = _img->height();
		if (imgW <= 0 || imgH <= 0) return;

		canvas->save();
		canvas->translate(sz.x / 2.0f + panX, sz.y / 2.0f + panY);
		canvas->rotate(rotation);
		canvas->scale(zoom, zoom);
		canvas->drawImage(_img.get(), -imgW / 2.0f, -imgH / 2.0f, 1.0f);

		drawSpriteOverlay(canvas, imgW, imgH);

		canvas->restore();
	}

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

	void fitImage() {
		if (!_img) return;
		float imgW = _img->width();
		float imgH = _img->height();
		if (imgW <= 0 || imgH <= 0) return;

		Vec2 sz = getSizeWithoutMargin();
		if (sz.x <= 0 || sz.y <= 0) return;

		float scaleX = sz.x / imgW;
		float scaleY = sz.y / imgH;
		zoom = std::min(scaleX, scaleY) * 0.9f;
		if (zoom < 0.02f) zoom = 0.02f;
		panX = 0;
		panY = 0;
		fireZoomChanged();
	}

	void drawCheckerboard(Canvas* canvas) {
		const float size = 20.0f;
		const int c1 = 0xff1a1a1a;
		const int c2 = 0xff262626;

		Vec2 sz = getSizeWithoutMargin();
		if (sz.x <= 0 || sz.y <= 0) return;

		int cols = (int)(sz.x / size) + 1;
		int rows = (int)(sz.y / size) + 1;

		canvas->fillColorByInt32(c1);
		canvas->beginPath();
		canvas->rect(0, 0, sz.x, sz.y);
		canvas->fill();

		canvas->fillColorByInt32(c2);
		canvas->beginPath();
		for (int r = 0; r < rows; r++) {
			int startC = (r % 2 == 0) ? 0 : 1;
			for (int c = startC; c < cols; c += 2) {
				canvas->rect(c * size, r * size, size, size);
			}
		}
		canvas->fill();
	}

	// 将鼠标 client 坐标换算到源图左上角坐标
	bool toImageCoord(MouseEvent* me, float* ix, float* iy) {
		if (!_img) return false;
		float imgW = _img->width();
		float imgH = _img->height();
		if (imgW <= 0 || imgH <= 0) return false;

		Vec2 sz = getSizeWithoutMargin();
		// frame.x/y 是相对父容器的局部坐标，需用 localToWorld 取内容原点在窗口客户区的全局位置
		Vec2 absPos = localToWorld(margin.left, margin.top);
		float vx = me->clientX - absPos.x;
		float vy = me->clientY - absPos.y;
		float cx = vx - (sz.x / 2.0f + panX);
		float cy = vy - (sz.y / 2.0f + panY);

		float c = std::cos(-rotation);
		float s = std::sin(-rotation);
		float lx = (cx * c - cy * s) / zoom;
		float ly = (cx * s + cy * c) / zoom;

		*ix = lx + imgW / 2.0f;
		*iy = ly + imgH / 2.0f;
		return true;
	}

	// 命中检测：返回 (列 x, 行 y)，命中失败返回 false
	bool getCellAt(MouseEvent* me, int* gx, int* gy) {
		if (!info) return false;
		float ix, iy;
		if (!toImageCoord(me, &ix, &iy)) return false;

		float imgW = _img->width();
		float imgH = _img->height();
		float cellW = info->getCellWidth((int)imgW);
		float cellH = info->getCellHeight((int)imgH);
		if (cellW <= 0 || cellH <= 0) return false;

		int col = (int)std::floor(ix / (cellW + info->colGap));
		int row = (int)std::floor(iy / (cellH + info->rowGap));
		if (col < 0 || col >= info->cols || row < 0 || row >= info->rows) return false;

		float cx = col * (cellW + info->colGap);
		float cy = row * (cellH + info->rowGap);
		if (ix >= cx && ix < cx + cellW && iy >= cy && iy < cy + cellH) {
			*gx = col;
			*gy = row;
			return true;
		}
		return false;
	}

	void updateHover(MouseEvent* me) {
		int gx = 0, gy = 0;
		bool ok = getCellAt(me, &gx, &gy);
		if (ok) {
			if (!hasHover || hoverCellX != gx || hoverCellY != gy) {
				hasHover = true;
				hoverCellX = gx;
				hoverCellY = gy;
				invalidDraw();
			}
		} else {
			if (hasHover) {
				hasHover = false;
				invalidDraw();
			}
		}
	}

	void fillRect(Canvas* canvas, float x, float y, float w, float h, int color) {
		canvas->fillColorByInt32(color);
		canvas->beginPath();
		canvas->rect(x, y, w, h);
		canvas->fill();
	}

	void drawSpriteOverlay(Canvas* canvas, float imgW, float imgH) {
		if (!info) return;
		float cellW = info->getCellWidth((int)imgW);
		float cellH = info->getCellHeight((int)imgH);
		if (cellW <= 0 || cellH <= 0) return;

		float lw = 1.0f / zoom; // 屏幕约 1px 的线宽

		// 悬停高亮
		if (hasHover) {
			float hx = -imgW / 2.0f + hoverCellX * (cellW + info->colGap);
			float hy = -imgH / 2.0f + hoverCellY * (cellH + info->rowGap);
			fillRect(canvas, hx, hy, cellW, cellH, 0x33ffffff);
		}

		// 当前动画帧高亮 + 顺序编号
		if (curAnim) {
			for (int i = 0; i < curAnim->coords->size(); i++) {
				SpriteSheetFrameCoord* c = curAnim->coords->get(i);
				if (!c) continue;
				float fx = -imgW / 2.0f + c->x * (cellW + info->colGap);
				float fy = -imgH / 2.0f + c->y * (cellH + info->rowGap);
				fillRect(canvas, fx, fy, cellW, cellH, 0x66ff0000);

				canvas->fontFace("sans");
				canvas->fontSize(16.0f / zoom);
				canvas->textAlign(CANVAS_ALIGN_CENTER | CANVAS_ALIGN_MIDDLE);
				canvas->fillColorByInt32(0xffffffff);
				canvas->text(fx + cellW / 2.0f, fy + cellH / 2.0f, std::to_string(i).c_str());
			}
		}

		// 网格线（行线 + 列线，含间隔边界）
		for (int c = 0; c <= info->cols; c++) {
			float x = -imgW / 2.0f + c * (cellW + info->colGap);
			fillRect(canvas, x, -imgH / 2.0f, lw, imgH, 0xffff0000);
		}
		for (int c = 0; c < info->cols; c++) {
			float x = -imgW / 2.0f + c * (cellW + info->colGap) + cellW;
			fillRect(canvas, x, -imgH / 2.0f, lw, imgH, 0xffff0000);
		}
		for (int r = 0; r <= info->rows; r++) {
			float y = -imgH / 2.0f + r * (cellH + info->rowGap);
			fillRect(canvas, -imgW / 2.0f, y, imgW, lw, 0xffff0000);
		}
		for (int r = 0; r < info->rows; r++) {
			float y = -imgH / 2.0f + r * (cellH + info->rowGap) + cellH;
			fillRect(canvas, -imgW / 2.0f, y, imgW, lw, 0xffff0000);
		}
	}

	void showContextMenu(float clientX, float clientY) {
		auto root = mkMenuNativeItem(nullptr, "", nullptr);
		HIER(root) {
			mkMenuNativeItem(o, "放大 (+)", CLOSURE([=](MenuNativeItem* item) {
				zoomIn();
			}));
			mkMenuNativeItem(o, "缩小 (-)", CLOSURE([=](MenuNativeItem* item) {
				zoomOut();
			}));
			mkMenuNativeItem(o, "适应窗口", CLOSURE([=](MenuNativeItem* item) {
				center();
			}));
			mkMenuNativeItem(o, "实际大小 (100%)", CLOSURE([=](MenuNativeItem* item) {
				setZoom(1.0f);
				panX = 0;
				panY = 0;
				invalidDraw();
			}));
			mkMenuNativeItem(o, "旋转 90°", CLOSURE([=](MenuNativeItem* item) {
				rotate90();
			}));
		} HEND;

		auto menu = MenuNative::mk(root.get());
		Window* win = getWindow();
		if (win) {
			menu->windowId = win->id;
		}
		menu->create(root.get());
		menu->showAt((int)clientX, (int)clientY);
	}

	void fireZoomChanged() {
		if (onZoomChanged) onZoomChanged->invoke(zoom);
	}

	void fireRotationChanged() {
		if (onRotationChanged) onRotationChanged->invoke(rotation);
	}
};