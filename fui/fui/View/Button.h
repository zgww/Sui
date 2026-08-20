#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Layout/LayoutLinear.h"
#include "../Core/MouseEvent.h"

class ImageView;
class TextView;

class Button : public LayoutLinear {
public:
	std::string label = "Button";
	std::string src;
	int iconSize = 16;
	int labelColor = 0xffffffff;
	float fontSize = 14.0f;
	int normalBg = 0xff1677ff;
	int hoverBg = 0xee1677ff;
	int activeBg = 0xdd1677ff;

	Ref<Closure<void(MouseEvent*)>> onClick{nullptr, this};

	Button();
	void setLabel(const std::string& l);
	void setSrc(const std::string& s);
	void setFontSize(float s);
	void setLabelColor(int c);
	void setNormalBg(int c);
	void onEvent(Event* ev) override;
	void react() override;

	virtual const char* getClassName() const override { return "Button"; }
};
