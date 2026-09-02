#pragma once

#include "Predef.h"
#include "../Urgc/GcObj.h"
#include "./Vec2.h"

class Image : public GcObj {
public:
	// Direct2D位图指针 (ID2D1Bitmap*)
	void* bitmap = nullptr;

	// 如果是纹理，需要保持对纹理对象的引用
	Ref<GcObj> data{ nullptr, this };

	Vec2 size();

	float width();
	float height();
};
