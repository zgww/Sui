module;
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <cmath>

#include "Core/App.h"
#include "Core/Window.h"
#include "Core/Canvas.h"
#include "Core/Node.h"
#include "Core/View.h"
#include "Core/Theme.h"
#include "Core/Vec2.h"
#include "Core/Mat2d.h"
#include "Core/MouseEvent.h"
#include "Core/Event.h"
#include "Core/Predef.h"
#include "Naga/Path.h"
#include "Layout/LayoutLinear.h"
#include "Layout/LayoutAlign.h"
#include "View/Button.h"
#include "View/TextView.h"
#include "View/ImageView.h"
#include "View/ScrollArea.h"
#include "View/MenuNative.h"
#include "Dialog/FileDialog.h"
#include "Urgc/Urgc.h"

export module ImageViewerApp;
import ImageCanvasView;
import ThumbnailBar;
import ShellExt;
import MenuBar;

static std::string getIconPath(const std::string& name) {
	char exePath[MAX_PATH];
	GetModuleFileNameA(nullptr, exePath, MAX_PATH);
	std::string dir(exePath);
	size_t pos = dir.find_last_of("\\/");
	if (pos != std::string::npos) dir = dir.substr(0, pos + 1);
	//return dir + "..\\..\\icons\\" + name;
	return dir + "icons\\" + name;
}

static void openConsole() {
	HWND con = GetConsoleWindow();
	if (con) {
		if (IsIconic(con)) ShowWindow(con, SW_RESTORE);
		SetForegroundWindow(con);
		return;
	}
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	freopen_s(&f, "CONOUT$", "w", stderr);
	freopen_s(&f, "CONIN$", "r", stdin);
	SetConsoleOutputCP(65001);
}

class ImageViewerState;

class TooltipCallback : public ViewCallback {
public:
	ImageViewerState* state = nullptr;
	bool cbDrawSelf(View* div, Canvas* canvas) override;
};

export class ImageViewerState : public GcObj {
public:
	Ref<Window> win{nullptr, this};
	Ref<LayoutLinear> root{nullptr, this};

	std::string currentPath;
	std::string currentDir;
	int currentIndex = -1;
	float currentZoom = 1.0f;

	ImageCanvasView* canvasPtr = nullptr;
	ThumbnailBar* thumbPtr = nullptr;

	std::string tooltipText;
	float tooltipX = 0;
	float tooltipY = 0;
	View* tooltipOverlay = nullptr;

	void showTooltip(const std::string& text, float x, float y) {
		tooltipText = text;
		tooltipX = x;
		tooltipY = y + 22;
		if (tooltipOverlay) {
			tooltipOverlay->setVisible(true);
		}
	}

	void hideTooltip() {
		tooltipText.clear();
		if (tooltipOverlay) {
			tooltipOverlay->setVisible(false);
		}
	}

	void render() {
		hideTooltip();
		auto& t = *themeIns();
		t.scrollbar_barBg = 0x99ffffff;

		RINS(root.get()) {
			o.direction = "column";
			o.aiStretch();

			// 菜单栏 + 工具栏（同一行）
			R(LayoutLinear) {
				o.direction = "row";
				o.height = 32;
				o.backgroundColor = 0xff2d2d2d;
				o.aic();

				R(MenuBar) {
					R(LayoutLinearCell) { o.grow = 1; } REND;
					if (o.created) {
						std::vector<MenuBar::MenuItem> items = {
							{ "文件", {
								{ "打开", [=]() { onOpenFile(); } },
								{ "退出", [=]() {
									if (win) win->close();
								} }
							}},
							{ "关于", {
								{ "软件版本", [=]() {
									MessageBoxW(nullptr, L"ImageViewer v1.0\n\n基于 fui GUI 框架", L"软件版本", MB_OK | MB_ICONINFORMATION);
								} },
								{ "关于我们", [=]() {
									MessageBoxW(nullptr, L"ImageViewer\n\n一个简洁高效的图片查看器\n使用 fui GUI 框架开发", L"关于我们", MB_OK | MB_ICONINFORMATION);
								} },
								{ "打开控制台", [=]() {
									openConsole();
								} }
							}}
						};
						o.setMenus(items);
					}
				} REND;

				//占满
				R(View) { 
					R(LayoutLinearCell) {} REND;
				} REND;

				// Open
				R(Button) {
					o.setSrc(getIconPath("open.png"));
					o.setLabel("");
					o.setNormalBg(0xff2d2d2d);
					o.hoverBg = 0xff404040;
					o.padding.setAxis(0, 0);
					o.width = 32;
					o.height = 32;
					o.onClick = CLOSURE([=](MouseEvent* me) {
						onOpenFile();
					});
					o.cbOnEvent = CLOSURE([=](Event* ev) {
						if (auto* me = dynamic_cast<MouseEnterEvent*>(ev)) showTooltip("打开", me->clientX, me->clientY);
						else if (dynamic_cast<MouseLeaveEvent*>(ev)) hideTooltip();
					});
				} REND;

				R(View) { o.width = 2; o.height = 20; o.backgroundColor = 0xff1a1a1a; o.margin.setHor(4); } REND;

				// Zoom In
				R(Button) {
					o.setSrc(getIconPath("zoom-in.png"));
					o.setLabel("");
					o.setNormalBg(0xff2d2d2d);
					o.hoverBg = 0xff404040;
					o.padding.setAxis(0, 0);
					o.width = 32;
					o.height = 32;
					o.onClick = CLOSURE([=](MouseEvent* me) {
						if (canvasPtr) canvasPtr->zoomIn();
					});
					o.cbOnEvent = CLOSURE([=](Event* ev) {
						if (auto* me = dynamic_cast<MouseEnterEvent*>(ev)) showTooltip("放大", me->clientX, me->clientY);
						else if (dynamic_cast<MouseLeaveEvent*>(ev)) hideTooltip();
					});
				} REND;

				// Zoom Out
				R(Button) {
					o.setSrc(getIconPath("zoom-out.png"));
					o.setLabel("");
					o.setNormalBg(0xff2d2d2d);
					o.hoverBg = 0xff404040;
					o.padding.setAxis(0, 0);
					o.width = 32;
					o.height = 32;
					o.onClick = CLOSURE([=](MouseEvent* me) {
						if (canvasPtr) canvasPtr->zoomOut();
					});
					o.cbOnEvent = CLOSURE([=](Event* ev) {
						if (auto* me = dynamic_cast<MouseEnterEvent*>(ev)) showTooltip("缩小", me->clientX, me->clientY);
						else if (dynamic_cast<MouseLeaveEvent*>(ev)) hideTooltip();
					});
				} REND;

				// Fit
				R(Button) {
					o.setSrc(getIconPath("fit.png"));
					o.setLabel("");
					o.setNormalBg(0xff2d2d2d);
					o.hoverBg = 0xff404040;
					o.padding.setAxis(0, 0);
					o.width = 32;
					o.height = 32;
					o.onClick = CLOSURE([=](MouseEvent* me) {
						if (canvasPtr) canvasPtr->center();
					});
					o.cbOnEvent = CLOSURE([=](Event* ev) {
						if (auto* me = dynamic_cast<MouseEnterEvent*>(ev)) showTooltip("适应窗口", me->clientX, me->clientY);
						else if (dynamic_cast<MouseLeaveEvent*>(ev)) hideTooltip();
					});
				} REND;

				// Rotate
				R(Button) {
					o.setSrc(getIconPath("rotate.png"));
					o.setLabel("");
					o.setNormalBg(0xff2d2d2d);
					o.hoverBg = 0xff404040;
					o.padding.setAxis(0, 0);
					o.width = 32;
					o.height = 32;
					o.onClick = CLOSURE([=](MouseEvent* me) {
						if (canvasPtr) canvasPtr->rotate90();
					});
					o.cbOnEvent = CLOSURE([=](Event* ev) {
						if (auto* me = dynamic_cast<MouseEnterEvent*>(ev)) showTooltip("旋转 90°", me->clientX, me->clientY);
						else if (dynamic_cast<MouseLeaveEvent*>(ev)) hideTooltip();
					});
				} REND;

				R(View) { o.width = 2; o.height = 20; o.backgroundColor = 0xff1a1a1a; o.margin.setHor(4); } REND;

				// Register Shell Menu
				R(Button) {
					o.setSrc(getIconPath("register.png"));
					o.setLabel("");
					o.setNormalBg(0xff2d2d2d);
					o.hoverBg = 0xff404040;
					o.padding.setAxis(0, 0);
					o.width = 32;
					o.height = 32;
					o.onClick = CLOSURE([=](MouseEvent* me) {
						char exePath[MAX_PATH];
						GetModuleFileNameA(nullptr, exePath, MAX_PATH);
						shellExt::registerShellMenu(std::string(exePath));
					});
					o.cbOnEvent = CLOSURE([=](Event* ev) {
						if (auto* me = dynamic_cast<MouseEnterEvent*>(ev)) showTooltip("注册右键菜单", me->clientX, me->clientY);
						else if (dynamic_cast<MouseLeaveEvent*>(ev)) hideTooltip();
					});
				} REND;

				R(TextView) {
					std::string label;
					if (!currentPath.empty()) {
						std::string fname = Path_basename(currentPath);
						int zoomPct = (int)std::round(currentZoom * 100);
						label = fname + "  " + std::to_string(zoomPct) + "%";
					} else {
						label = "No image loaded";
					}
					o.setText(label);
					o.setColor(0xffcccccc);
					o.setFontSize(13);
					o.margin.setHor(12);
				} REND;
			} REND;

			R(ImageCanvasView) {
				canvasPtr = &o;
				if (o.created) {
					o.onZoomChanged = CLOSURE([=](float z) {
						currentZoom = z;
						render();
					});
				}
				if (!currentPath.empty()) {
					o.setSrc(currentPath);
				}
				R(LayoutLinearCell) {
					o.grow = 1;
				} REND;
			} REND;

			R(ThumbnailBar) {
				thumbPtr = &o;
				if (o.created) {
					o.onSelect = CLOSURE([=](int index) {
						onThumbnailSelect(index);
					});
				}
				if (!currentDir.empty() && thumbPtr) {
					thumbPtr->setDirectory(currentDir);
					thumbPtr->setSelectedIndex(currentIndex);
				}
			} REND;

			// Tooltip overlay (drawn on top, compensates for frame position)
			R(View) {
				o.width = 0;
				o.height = 0;
				o.needClip = false;
				o.visible = false;
				tooltipOverlay = &o;
				if (o.created) {
					auto tc = new TooltipCallback();
					tc->state = this;
					o.cb = tc;
				}
			} REND;
		} REND;
	}

	void openFile(const std::string& path) {
		currentPath = path;
		namespace fs = std::filesystem;
		currentDir = fs::path(path).parent_path().string();

		if (thumbPtr && !currentDir.empty()) {
			thumbPtr->setDirectory(currentDir);
			auto& files = thumbPtr->imageFiles;
			currentIndex = -1;
			for (int i = 0; i < (int)files.size(); i++) {
				if (files[i] == currentPath) {
					currentIndex = i;
					break;
				}
			}
			thumbPtr->setSelectedIndex(currentIndex);
		}
		render();
	}

	void onThumbnailSelect(int index) {
		if (!thumbPtr || index < 0 || index >= (int)thumbPtr->imageFiles.size()) return;
		currentPath = thumbPtr->imageFiles[index];
		currentIndex = index;
		thumbPtr->setSelectedIndex(index);
		render();
	}

	void onOpenFile() {
		auto result = FileDialog_getFirstOpenFileName("./", "Select an image file");
		if (!result.empty()) {
			openFile(result);
		}
	}
};

export void runImageViewer(const std::string& initialFile) {
	SetConsoleOutputCP(65001);
	urgc.start_process_thread();

	App* app = App_use();

	Ref<ImageViewerState> state{new ImageViewerState()};

	state->win = Ref(new Window());
	state->root = Ref(new LayoutLinear());

	state->currentPath = initialFile;
	if (!initialFile.empty()) {
		namespace fs = std::filesystem;
		state->currentDir = fs::path(initialFile).parent_path().string();
	}

	state->render();

	state->win->setRootView(state->root);
	state->win->setTitle("ImageViewer");
	state->win->setSize(1200, 800);
	state->win->moveToCenter();
	state->win->show();

	state->win->onClosed = CLOSURE([=](Window* win) {
		printf("ImageViewer closed\n");
	});

	if (!initialFile.empty()) {
		state->openFile(initialFile);
	}

	app->runEventLoop();
}

bool TooltipCallback::cbDrawSelf(View* div, Canvas* canvas) {
	if (!state || state->tooltipText.empty()) return true;

	canvas->save();
	canvas->translate(-div->frame.x, -div->frame.y);

	const char* text = state->tooltipText.c_str();
	float x = state->tooltipX;
	float y = state->tooltipY;

	canvas->fontSize(13);
	canvas->fontFace("sans");
	float bounds[4];
	canvas->textBounds(0, 0, text, nullptr, bounds);
	float textW = bounds[2] - bounds[0];

	float pad = 6.0f;
	float bgH = 22.0f;

	canvas->beginPath();
	canvas->roundRect(x, y, textW + pad * 2, bgH, 4.0f);
	canvas->fillColorByInt32(0xe6000000);
	canvas->fill();

	canvas->fillColorByInt32(0xffffffff);
	canvas->text(x + pad, y + 16, text);

	canvas->restore();
	return true;
}
