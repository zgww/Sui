#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/Image.h"
#include "../Core/Canvas.h"

enum ImageMode {
	ImageMode_WrapContent,
	ImageMode_WidthFix,
	ImageMode_HeightFix,
	ImageMode_Contain,
	ImageMode_Cover,
	ImageMode_Fill
};

class ImageView : public View {
public:
	std::string src;
	ImageMode imageMode = ImageMode_WrapContent;
	Ref<Image> _img{nullptr, this};

	void setSrc(const std::string& s);
	void setImageMode(ImageMode mode);
	bool isImageValid();
	void layout(Frame* ctx) override;
	void draw_self(Canvas* canvas) override;

	virtual const char* getClassName() const override { return "ImageView"; }
};
