#include "ImageManager.h"

Ref<Image> ImageManager::get(Canvas* canvas, const std::string& path) {
	auto it = cache.find(path);
	if (it != cache.end()) {
		return it->second;
	}
	Ref<Image> img = canvas->createImage(path.c_str());
	if (img) {
		cache[path] = img;
	}
	return img;
}

void ImageManager::clear() {
	cache.clear();
}

ImageManager* insImageManager() {
	static Ref<ImageManager> ins{new ImageManager()};
	return ins.get();
}
