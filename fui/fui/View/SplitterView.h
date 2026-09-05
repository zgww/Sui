#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/Event.h"
#include "../Core/MouseEvent.h"
#include "Drag.h"
#include "../Layout/LayoutLinear.h"

class SplitterView : public View {
public:
	Ref<Drag> drag{new Drag(), this};

	int hoverBg = 0xff007aff;
	int normalBg = 0xffcdcdcf;

	float prevGrow = 0;
	float nextGrow = 0;

	SplitterView();
	void onEvent(Event* ev) override;
	void onHoverChanged() override;
	void react() override;

	void updateSiblingsGrow(Drag* d);

	virtual const char* getClassName() const override { return "SplitterView"; }
};
