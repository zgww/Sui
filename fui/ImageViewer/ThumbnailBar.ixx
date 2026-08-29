module;
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "View/ScrollArea.h"
#include "View/ImageView.h"
#include "Core/Node.h"
#include "Core/Vec2.h"
#include "Core/MouseEvent.h"
#include "Core/Event.h"
#include "Urgc/Urgc.h"

export module ThumbnailBar;

export class ThumbnailBar : public ScrollArea {
public:
	std::string directory;
	std::vector<std::string> imageFiles;
	int selectedIndex = -1;

	Ref<Closure<void(int)>> onSelect{nullptr, this};

	ThumbnailBar() {
		scrollDirection = "horizontal";
		backgroundColor = 0xff222222;
		height = 80;
	}

	virtual const char* getClassName() const override { return "ThumbnailBar"; }

	void setDirectory(const std::string& dir) {
		if (directory == dir) return;
		directory = dir;
		scanImages();
		rebuild();
	}

	void setSelectedIndex(int index) {
		if (selectedIndex == index) return;
		int old = selectedIndex;
		selectedIndex = index;
		updateHighlight(old);
		updateHighlight(index);
		invalidDraw();
	}

private:
	void scanImages() {
		imageFiles.clear();
		namespace fs = std::filesystem;
		if (!fs::exists(directory) || !fs::is_directory(directory)) return;

		static const std::vector<std::string> validExts = {
			".jpg", ".jpeg", ".png", ".bmp", ".gif",
			".webp", ".tga", ".tiff", ".tif", ".ico", ".psd"
		};

		std::vector<std::string> files;
		for (const auto& entry : fs::directory_iterator(directory)) {
			if (!entry.is_regular_file()) continue;
			std::string ext = entry.path().extension().string();
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
			for (const auto& ve : validExts) {
				if (ext == ve) {
					files.push_back(entry.path().string());
					break;
				}
			}
		}
		std::sort(files.begin(), files.end());
		imageFiles = std::move(files);
	}

	void rebuild() {
		gocIdx = 0;
		RINS(this) {
			o.direction = "row";
			o.alignItems = "center";
			o.scrollDirection = "horizontal";

			for (int i = 0; i < (int)imageFiles.size(); i++) {
				R(ImageView, i) {
					o.setSrc(imageFiles[i]);
					o.setImageMode(ImageMode_HeightFix);
					o.height = 60;
					o.margin.setHor(4);
					o.margin.setVer(4);
					o.backgroundColor = (i == selectedIndex) ? 0xffcc6600 : 0xff333333;
					if (i == selectedIndex) {
						o.margin.setAll(2);
					}
					o.cbOnEvent = CLOSURE([=](Event* ev) {
						if (auto me = dynamic_cast<MouseEvent*>(ev)) {
							if (me->isClickInBubble()) {
								int old = selectedIndex;
								selectedIndex = i;
								updateHighlight(old);
								updateHighlight(i);
								if (onSelect) onSelect->invoke(i);
								invalidDraw();
							}
						}
					});
				} REND;
			}
		} REND;
		invalidLayout();
	}

	void updateHighlight(int index) {
		if (index < 0 || index >= (int)imageFiles.size()) return;
		auto child = dynamic_cast<View*>(getChildAsView(index));
		if (child) {
			child->backgroundColor = (index == selectedIndex) ? 0xffcc6600 : 0xff333333;
		}
	}
};
