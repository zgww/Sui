#pragma once

#include "Predef.h"
#include "Emitter.h"
#include "Fps.h"
#include "Canvas.h"
#include "Inset.h"
#include "Vec2.h"

class ViewBase;
class View;
class App;

class Window : public Emitter {
public:
	int64_t id = 0;
	Fps fps;

	Ref<ViewBase> rootView{nullptr, this};
	Ref<Canvas> canvas{nullptr, this};

	bool borderless = false;
	Ref<Closure<void(Window*)>> onClosed{nullptr, this};

	void* data = nullptr;
	int layoutTimes = 0;

	Window();
	virtual ~Window();

	void setTransparent();
	void initData();
	void cleanData();
	void setRootView(ViewBase* v);

	void show();
	void hide();
	void maximize();
	void minimize();
	void normal();
	void enable(bool enable);
	void close();
	void setOwner(Window* ownerWindow);

	void layoutAndDraw();
	void layout();
	void draw();
	bool isVisible();

	void onDestroy();

	void setTitle(const char* title);
	std::string getTitle();

	Vec2 getPos();
	void setPos(float x, float y);
	Vec2 getSize();
	void setSize(float x, float y);
	void setRect(float x, float y, float w, float h);
	Vec2 getClientSize();
	Inset getNonClientInset();

	void moveToCenter();

	virtual const char* getClassName() const override { return "Window"; }
};

class DragCrossWindowIndicator : public GcObj {
public:
	bool dragging = false;

	void _start();
	void _end();
	void _dragMove();

	void start();
	void end();
	void onDragMove(Vec2 clientPos);
};
