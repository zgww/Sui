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

export class ImageCanvasView : public View {
public:
	std::string src;
	float zoom = 1.0f;
	float rotation = 0.0f;
	float panX = 0.0f;
	float panY = 0.0f;

	Ref<Closure<void(float)>> onZoomChanged{nullptr, this};
	Ref<Closure<void(float)>> onRotationChanged{nullptr, this};

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
			float mx = we->clientX - frame.x - cx;
			float my = we->clientY - frame.y - cy;
			panX = mx - (mx - panX) * (zoom / oldZoom);
			panY = my - (my - panY) * (zoom / oldZoom);

			invalidDraw();
			fireZoomChanged();
			ev->stopPropagation();
			return;
		}

		if (auto me = dynamic_cast<MouseEvent*>(ev)) {
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
					// 右键点击：显示上下文菜单
					showContextMenu(me->clientX, me->clientY);
				}
				ev->stopPropagation();
				return;
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
