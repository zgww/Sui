#pragma once

#include "../Core/Predef.h"
#include "../Core/Node.h"
#include "../Core/ViewBase.h"
#include "../Core/View.h"
#include "../Core/Border.h"
#include "../Core/Event.h"
#include "../Core/MouseEvent.h"

class HoverViewEffect : public Node {
public:
	int backgroundColor = 0x00ffffff;
	Border border;

	int hoverBackgroundColor = 0x22666666;
	Border hoverBorder;

	int activeBackgroundColor = 0x53007aff;
	Border activeBorder;

	std::string hoverCursor = "pointer";

	bool isActive = false;

	Ref<Closure<void(MouseEvent*)>> onClick{nullptr, this};
	Ref<Closure<bool(Event*)>> onHostEvent{nullptr, this};
	Ref<Closure<void(ViewBase*)>> cbOnHoverChanged{nullptr, this};

	void onMounted() override;
	void react() override;
	void applyEffect();
	void onUnmounting() override;

	virtual const char* getClassName() const override { return "HoverViewEffect"; }
};
