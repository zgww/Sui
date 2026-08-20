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


class  ImageModeCalc {
public:
	Rect getSrcRect() {
		return mkRect(sx, sy, sw, sh);
	}
	Rect getDstRect() {
		return mkRect(dx, dy, dw, dh);
	}

	int sw = 0;
	int sh = 0;
	int dw = 0;
	int dh = 0;

	int sx = 0;
	int sy = 0;
	int dx = 0;
	int dy = 0;
	float sr = 0.f;
	float dr = 0.f;
	float scale = 1.f;
	void calc(
		int sw, int sh, int dw, int dh, ImageMode mode
	);
	void calc_contain();
	void calc_cover();
};


class ImageView : public View {
public:
	std::string src;
	ImageMode imageMode = ImageMode_WrapContent;
	Ref<Image> _img{nullptr, this};

	ImageModeCalc calc;


	virtual const char* getClassName() const override { return "ImageView"; }


	Vec2 pos;
	float ratio = 10.0;
	void setRatio(float v) {
		ratio = v;
		printf("set ratio:%f\n", ratio);
	}


	void layout(Frame* ctx);
		
	void setSrc(std::string src);
	void setImageMode(ImageMode mode);
	bool _isImageValid() {
		return this->_img != NULL;
	}

	virtual void draw_self(Canvas* canvas) override;
};


//此函数用来在nvg支持类似于skia的  绘制源图像 某区域 到目标区域的功能。
void drawImage_atRect(Canvas* canvas, Image* imgId, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);