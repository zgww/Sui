#pragma once

#include "../Core/Predef.h"
#include "../Core/Emitter.h"
#include "../Core/Vec2.h"
#include "../Core/MouseEvent.h"

class Drag : public Listener {
public:
	Ref<Closure<void(Drag*)>> onDrag{nullptr, this};
	Vec2 currentClientPos;
	Vec2 downClientPos;
	Vec2 deltaPos;
	std::string cursor;
	bool isDragChecking = false;
	bool isDragStart = false;
	bool isDragging = false;
	bool isDragEnd = false;
	float moveThreshold = 5.0f;
	Ref<MouseEvent> mouseEvent{nullptr, this};
	int mouseDownButton = 1;
	Ref<GcObj> data{ nullptr, this };

	void setStatus(const char* status);
	void onMouseDown(Event* e);
	void onMouseDown_byPrefer(Event* e, int button, bool cap, bool bubble);
	void onListenerEvent(Event* ev) override;

	virtual const char* getClassName() const override { return "Drag"; }
};
