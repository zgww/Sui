#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/Vec2.h"
#include "../Core/Frame.h"
#include <vector>
#include <string>


/**
 * @export
 */
class TextView : public View {
public:
	/**
	 * @property
	 * @brief text
	 */
	std::string text;
	/**
	 * @property
	 */
	float fontSize = 14.0f;
	std::string fontFace = "sans";
	int color = 0xff000000;
	std::string textAlign = "left";
	float lineHeight = 1.4f;
	bool wrap = false;
	int maxLine = 0;
	bool overflowEllipsis = false;

	struct TextLine {
		std::string text;
		float x = 0;
		float y = 0;
		float w = 0;
		float h = 0;
	};
	std::vector<TextLine> lineInfos;
	float areaX = 0;
	bool layoutDirty = true;

	void setText(const std::string& t);
	void setFontSize(float s);
	void setColor(int c);
	void setTextAlign(const std::string& a);
	void setWrap(bool w);
	void setMaxLine(int m);
	void setLineHeight(float h);

	void measureText(Canvas* canvas, const char* str, float* bounds);
	void doTextLayout(float maxW, float maxH, Canvas* canvas);
	void layout(Frame* ctx) override;
	void draw_self(Canvas* canvas) override;
	void invalidLayout() override;

	virtual const char* getClassName() const override { return "TextView"; }

	static void registerMeta();
};
