#pragma once

#include "Core/Predef.h"
#include "Core/View.h"
#include "Core/Image.h"
#include "Urgc/GcMap.h"

#include <rttr/rttr_enable.h>

class ImageCanvasView : public View {
public:
	std::string src;
	float zoom = 1.0f;
	float rotation = 0.0f;
	float panX = 0.0f;
	float panY = 0.0f;

	Ref<Closure<void(float)>> onZoomChanged{nullptr, this};
	Ref<Closure<void(float)>> onRotationChanged{nullptr, this};

	ImageCanvasView();

	virtual const char* getClassName() const override { return "ImageCanvasView"; }

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

	void fitImage();
	void drawCheckerboard(Canvas* canvas);
	void showContextMenu(float clientX, float clientY);
	void fireZoomChanged();
	void fireRotationChanged();
};
