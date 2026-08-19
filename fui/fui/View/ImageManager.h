#pragma once

#include "../Core/Predef.h"
#include "../Core/Canvas.h"
#include "../Core/Image.h"
#include <string>
#include <unordered_map>

class ImageManager : public GcObj {
public:
	std::unordered_map<std::string, Ref<Image>> cache;

	Ref<Image> get(Canvas* canvas, const std::string& path);
	void clear();

	virtual const char* getClassName() const { return "ImageManager"; }
};

ImageManager* insImageManager();
