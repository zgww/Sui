#include "PrefabRealtimeViewerApp.h"

#include <Windows.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <cstdio>
#include <cstring>

#include "Core/App.h"
#include "Core/Canvas.h"
#include "Core/View.h"
#include "Core/MouseEvent.h"
#include "Core/Event.h"
#include "Core/Theme.h"
#include "View/Button.h"
#include "View/TextView.h"
#include "View/ScrollArea.h"
#include "View/MenuNative.h"
#include "Dialog/FileDialog.h"
#include "Json/cJSON.h"
#include "Naga/Path.h"
#include "Urgc/Urgc.h"
#include "JsonSerialization/NodeTreeIO.h"

#include <Windows.h>
#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")

namespace fs = std::filesystem;

// ==================== 工具函数 ====================

static std::string exeDir() {
	char exePath[MAX_PATH];
	GetModuleFileNameA(nullptr, exePath, MAX_PATH);
	std::string dir(exePath);
	size_t pos = dir.find_last_of("\\/");
	if (pos != std::string::npos) dir = dir.substr(0, pos + 1);
	return dir;
}

static std::string readFileText(const std::string& path) {
	std::ifstream ifs(path, std::ios::binary);
	if (!ifs) return std::string();
	std::stringstream ss;
	ss << ifs.rdbuf();
	return ss.str();
}

static bool endsWith(const std::string& s, const std::string& suf) {
	if (s.size() < suf.size()) return false;
	return s.compare(s.size() - suf.size(), suf.size(), suf) == 0;
}

static int64_t fileStamp(const std::string& path) {
	try {
		auto t = fs::last_write_time(path);
		return (int64_t)t.time_since_epoch().count();
	} catch (...) {
		return 0;
	}
}

// 扫描目录，返回 (name, isDir, fullPath)；目录在前、按名字排序；只保留目录与 *.prefab.json 文件
static std::vector<std::tuple<std::string, bool, std::string>> scanDir(const std::string& dir) {
	std::vector<std::tuple<std::string, bool, std::string>> out;
	if (dir.empty() || !fs::exists(dir) || !fs::is_directory(dir)) return out;
	for (const auto& de : fs::directory_iterator(dir)) {
		std::string name = de.path().filename().string();
		bool isDir = de.is_directory();
		if (isDir) {
			if (name.empty() || name[0] == '.') continue; // 隐藏点目录
			out.emplace_back(name, true, de.path().string());
		} else {
			if (!endsWith(name, ".prefab.json")) continue;
			out.emplace_back(name, false, de.path().string());
		}
	}
	std::sort(out.begin(), out.end(), [](const auto& a, const auto& b) {
		if (std::get<1>(a) != std::get<1>(b)) return std::get<1>(a) > std::get<1>(b); // 目录在前
		return std::get<0>(a) < std::get<0>(b);
	});
	return out;
}

static std::vector<std::string> scanDirNames(const std::string& dir) {
	std::vector<std::string> names;
	for (auto& e : scanDir(dir)) {
		names.push_back((std::get<1>(e) ? "D:" : "F:") + std::get<0>(e));
	}
	return names;
}

// 让窗口客户区精确等于 cw×ch：borderless=true 时去掉标题栏/边框（WS_POPUP，
// 保留 WS_SYSMENU 以支持 Alt+F4，任务栏仍显示图标）；false 时为普通可缩放窗口。
// fui 的 Window 构造时固定用 WS_OVERLAPPEDWINDOW 建窗，这里在 show 之前改样式，
// 并由目标客户区尺寸经 AdjustWindowRectEx 反推整窗尺寸，保证 prefab 1:1 显示。
static void applyStandaloneStyle(Window* win, float cw, float ch, bool borderless) {
	HWND hwnd = (HWND)win->id;
	if (!hwnd) return;
	if (0) {
		return;
	}

	DWORD style = borderless
		? (WS_POPUP | WS_THICKFRAME | WS_SYSMENU)
		: (DWORD)WS_OVERLAPPEDWINDOW;
	DWORD ex = (DWORD)GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
	if (borderless) ex |= WS_EX_APPWINDOW; // 无边框也在任务栏留图标，方便关闭

	SetWindowLongPtrW(hwnd, GWL_STYLE, (LONG_PTR)style);
	SetWindowLongPtrW(hwnd, GWL_EXSTYLE, (LONG_PTR)ex);
	// 无边框窗口：fui WM_NCCALCSIZE 返回 0 使客户区=整窗，直接按设计尺寸设置即可精确 1:1；
	// 普通窗口：需经 AdjustWindowRectEx 反推整窗尺寸，让客户区等于设计尺寸。
	float setW = cw, setH = ch;
	if (!borderless) {
		RECT rc{ 0, 0, (LONG)cw, (LONG)ch };
		AdjustWindowRectEx(&rc, style, FALSE, ex);
		setW = (float)(rc.right - rc.left);
		setH = (float)(rc.bottom - rc.top);
	}
	win->setSize(setW, setH);
	// 让样式（去标题栏/边框）立即生效，但保持刚设置的尺寸与位置不变
	SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

	// ================= 新增：恢复 DWM 阴影 =================
	if (borderless) {
		// 将非客户区向客户区内部扩展 1 像素
		// 这会触发 DWM 绘制窗口阴影，且不会改变你计算好的 outerW/outerH
		//MARGINS margins = { 1, 1, 1, 1 }; // 左, 右, 上, 下
		MARGINS margins = {0, 0, 0, 1 }; // 左, 右, 上, 下
		DwmExtendFrameIntoClientArea(hwnd, &margins);


		// 无边框窗口必须关闭 Win11 原生圆角 (DWMWA_WINDOW_CORNER_PREFERENCE = 33)：
		// 圆角外沿是 DWM 绘制的 1px 描边，切换窗口（激活态变化）时会被重绘出来，
		// 与框架层 WM_NCACTIVATE/WM_NCPAINT 拦截配合才能做到真正无边框。
		enum DWM_WINDOW_CORNER_PREFERENCE {
			DWMWCP_DEFAULT = 0,
			DWMWCP_DONOTROUND = 1,
			DWMWCP_ROUND = 2,
			DWMWCP_ROUNDSMALL = 3
		};
		DWM_WINDOW_CORNER_PREFERENCE pref = DWMWCP_DONOTROUND;
		DwmSetWindowAttribute(hwnd, 33, &pref, sizeof(pref));
	}
}

// ==================== 自绘图标 ====================

// 目录/文件小图标（draw_self 坐标系原点在视图内 margin 偏移处）
class DirIconView : public View {
public:
	bool isDir = true;

	void draw_self(Canvas* canvas) override {
		float w = frame.width;
		float h = frame.height;
		if (isDir) {
			// 文件夹：后盖 + 前盖 + 底
			canvas->beginPath();
			canvas->roundRect(3, 16, 22, 10, 2);
			canvas->fillColorByInt32(0xfff0b85c);
			canvas->fill();

			canvas->beginPath();
			canvas->roundRect(3, 14, w - 6, h - 18, 4);
			canvas->fillColorByInt32(0xffe8a33d);
			canvas->fill();

			canvas->beginPath();
			canvas->roundRect(3, 22, w - 6, h - 26, 3);
			canvas->fillColorByInt32(0xfff2b24e);
			canvas->fill();
		} else {
			// 文件：深色底 + 浅色纸 + 折角 + 行示意
			canvas->beginPath();
			canvas->roundRect(8, 3, w - 16, h - 6, 3);
			canvas->fillColorByInt32(0xff3a3f4b);
			canvas->fill();

			canvas->beginPath();
			canvas->roundRect(10, 5, w - 20, h - 10, 2);
			canvas->fillColorByInt32(0xffd9dde6);
			canvas->fill();

			canvas->beginPath();
			canvas->roundRect(15, 11, w - 34, 4, 2);
			canvas->fillColorByInt32(0xff9aa3b2);
			canvas->fill();
			canvas->beginPath();
			canvas->roundRect(15, 20, w - 30, 4, 2);
			canvas->fillColorByInt32(0xffaeb6c4);
			canvas->fill();
			canvas->beginPath();
			canvas->roundRect(15, 29, w - 24, 4, 2);
			canvas->fillColorByInt32(0xffc3cad6);
			canvas->fill();
		}
	}
};

// ==================== 项目列表行 ====================

class ProjectRowView : public LayoutLinear {
public:
	PrefabState* state = nullptr;
	int index = -1;
	std::string path;
	bool selected = false;
};

// ==================== 目录/文件项 ====================

class DirItemView : public LayoutLinear {
public:
	PrefabState* state = nullptr;
	std::string path;
	std::string name;
	bool isDir = true;
	bool selected = false;
};

// ==================== 项目列表持久化 ====================

static std::string projectsFile() {
	return exeDir() + "prefab_projects.json";
}

void PrefabState::saveProjects() {
	cJSON* arr = cJSON_CreateArray();
	for (auto& p : projects) {
		cJSON_AddItemToArray(arr, cJSON_CreateString(p.c_str()));
	}
	char* s = cJSON_Print(arr);
	if (s) {
		std::ofstream ofs(projectsFile(), std::ios::binary);
		if (ofs) ofs.write(s, (std::streamsize)strlen(s));
		free(s);
	}
	cJSON_Delete(arr);
}

void PrefabState::loadProjects() {
	projects.clear();
	std::string txt = readFileText(projectsFile());
	if (txt.empty()) return;
	cJSON* root = cJSON_Parse(txt.c_str());
	if (!root) return;
	if (cJSON_IsArray(root)) {
		for (cJSON* it = root->child; it; it = it->next) {
			if (it->valuestring) {
				projects.push_back(Path_normal(it->valuestring));
			}
		}
	}
	cJSON_Delete(root);
}

// ==================== PrefabState ====================

PrefabState::PrefabState() {
	CtorGuard _(this);
	auto self = Ref(this);
	// 文件监听轮询：500ms 检查预览文件与目录内容变化
	watchTimer = mkTimerInterval(CLOSURE([=]() {
		self->tickWatch();
	}), 500);
}

void PrefabState::tickWatch() {
	// 独立窗口的回收/热刷新不依赖主窗口是否打开
	tickStandalone();
	if (!mainWin || !mainRoot) return;
	// 预览文件变化 → 重新导入刷新预览
	if (!previewPath.empty()) {
		int64_t st = fileStamp(previewPath);
		if (st != 0 && st != previewStamp) {
			previewStamp = st;
			openPrefab(previewPath);
		}
	}
	// 目录内容变化 → 刷新目录文件视图
	if (!currentDir.empty()) {
		std::vector<std::string> names = scanDirNames(currentDir);
		if (names != dirNames) refreshDirView();
	}
}

// ---------------- 项目列表页 ----------------

void PrefabState::renderProjectList() {
	if (!listRoot) return;
	RINS(listRoot.get()) {
		o.direction = "column";
		o.alignItems = "stretch";
		// ---- 顶部工具栏 ----
		RN(LayoutLinear) {
			RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
			o.direction = "row";
			o.alignItems = "center";
			o.backgroundColor = 0xff2a2f3a;
			o.height = 46;
			RN(Button) {
				o.label = "打开项目";
				o.width = 100; o.height = 30;
				o.margin.setAll(0); o.margin.left = 12;
				o.onClick = CLOSURE([=](MouseEvent*) { openProjectDialog(); });
			} REND;
			RN(Button) {
				o.label = "删除选中项目";
				o.width = 122; o.height = 30;
				o.margin.left = 8;
				o.onClick = CLOSURE([=](MouseEvent*) { deleteSelectedProject(); });
			} REND;
			RN(Button) {
				o.label = "进入项目";
				o.width = 100; o.height = 30;
				o.margin.left = 8;
				o.onClick = CLOSURE([=](MouseEvent*) { enterProject(); });
			} REND;
		} REND;
		// ---- 项目列表 ----
		RN(ScrollArea) {
			RN(LayoutLinearCell) { o.grow = 1.0f; } REND;
			o.direction = "column";
			o.alignItems = "stretch";
			o.scrollDirection = "vertical";
			o.backgroundColor = 0xff1b1f27;
			for (int i = 0; i < (int)projects.size(); i++) {
				// key 必须用稳定且唯一的项目路径：列表会在中间删除，若用数组索引 i 做 key，
				// 删除后节点按位置错位复用，视觉上会变成“删掉最后一行”。
				RN(ProjectRowView, projects[i]) {
					o.state = this;
					o.index = i;
					o.path = projects[i];
					o.selected = (i == selProject);
					o.direction = "row";
					o.alignItems = "center";
					o.height = 36;
					o.backgroundColor = (i == selProject) ? 0xff2d5b8f : 0x00000000;
					o.cursor = "pointer";
					RN(TextView) {
						o.text = Path_basename(projects[i]);
						o.fontSize = 14;
						o.color = 0xffe8eaed;
						o.margin.left = 14;
					} REND;
					RN(TextView) {
						o.text = projects[i];
						o.fontSize = 12;
						o.color = 0xff7a8291;
						o.margin.left = 18;
					} REND;
					o.cbOnEvent = CLOSURE([=](Event* ev) {
						if (auto* me = dynamic_cast<MouseEvent*>(ev)) {
							if (me->isDblClickInBubble()) {
								selProject = i;
								enterProject();
							} else if (me->isClickInBubble()) {
								selProject = i;
								renderProjectList();
							} else if (me->isMouseUp && me->button == 2) {
								selProject = i;
								renderProjectList();
								showProjectRowMenu(i);
							}
						}
					});
				} REND;
			}
		} REND;
	} REND;
	App_use()->invalidDraw();
}

void PrefabState::openProjectDialog() {
	std::string dir = FileDialog_getExistingDirectory("", "选择项目目录");
	if (dir.empty()) return;
	dir = Path_normal(dir);
	for (auto& p : projects) {
		if (p == dir) return; // 已存在
	}
	projects.push_back(dir);
	saveProjects();
	renderProjectList();
}

void PrefabState::deleteSelectedProject() {
	if (selProject < 0 || selProject >= (int)projects.size()) return;
	int r = MessageBoxW(nullptr, L"确定从项目列表中移除该项目？(不会删除磁盘上的文件)", L"删除项目",
		MB_YESNO | MB_ICONWARNING);
	if (r != IDYES) return;
	projects.erase(projects.begin() + selProject);
	if (selProject >= (int)projects.size()) selProject = (int)projects.size() - 1;
	saveProjects();
	renderProjectList();
}

void PrefabState::enterProject() {
	if (selProject < 0 || selProject >= (int)projects.size()) return;
	std::string dir = projects[selProject];
	if (!fs::exists(dir) || !fs::is_directory(dir)) {
		MessageBoxW(nullptr, L"项目目录不存在", L"PrefabRealtimeViewer", MB_OK | MB_ICONWARNING);
		return;
	}
	if (mainWin) {
		mainWin->close();
		mainWin = nullptr;
		mainRoot = nullptr;
		previewScroll = nullptr;
		previewContainer = nullptr;
		dirWrap = nullptr;
	}
	currentDir = dir;
	previewPath.clear();
	previewStamp = 0;
	previewRoot = nullptr;
	dirNames.clear();

	mainWin = Ref(new Window());
	mainRoot = Ref(new LayoutLinear());
	renderMain();
	refreshDirView();

	mainWin->setRootView(mainRoot);
	mainWin->setTitle(("Prefab Realtime Viewer - " + Path_basename(dir)).c_str());
	mainWin->setSize(1280, 820);
	mainWin->moveToCenter();
	mainWin->show();
	mainWin->onClosed = CLOSURE([=](Window*) {
		printf("[PrefabRealtimeViewer] main window closed\n");
	});
}

void PrefabState::showProjectRowMenu(int index) {
	auto root = Ref(new MenuNativeItem());
	mkMenuNativeItem(root.get(), "打开项目", CLOSURE([=](MenuNativeItem*) {
		selProject = index;
		openProjectDialog();
	}));
	mkMenuNativeItem(root.get(), "删除选中项目", CLOSURE([=](MenuNativeItem*) {
		selProject = index;
		deleteSelectedProject();
	}));
	mkMenuNativeItem(root.get(), "进入项目", CLOSURE([=](MenuNativeItem*) {
		selProject = index;
		enterProject();
	}));
	auto menu = MenuNative::mk(root.get());
	menu->showAtMouse();
}

// ---------------- 主页面 ----------------

void PrefabState::renderMain() {
	if (!mainRoot) return;
	RINS(mainRoot.get()) {
		o.direction = "column";
		o.alignItems = "stretch";
		// ---- 菜单栏 ----
		RN(LayoutLinear) {
			RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
			o.direction = "row";
			o.alignItems = "center";
			o.backgroundColor = 0xff20242c;
			o.height = 26;
			RN(Button) {
				o.label = "文件";
				o.width = 56; o.height = 24;
				o.normalBg = 0x00000000;
				o.hoverBg = 0x33167ff7;
				o.activeBg = 0x55167ff7;
				o.labelColor = 0xffd0d5dd;
				o.fontSize = 13;
				o.onClick = CLOSURE([=](MouseEvent*) {
					auto root = Ref(new MenuNativeItem());
					mkMenuNativeItem(root.get(), "返回项目列表", CLOSURE([=](MenuNativeItem*) {
						closeMainWindow();
					}));
					mkMenuNativeItem(root.get(), "退出", CLOSURE([=](MenuNativeItem*) {
						if (mainWin) mainWin->close();
						if (listWin) listWin->close();
					}));
					auto menu = MenuNative::mk(root.get());
					menu->showAtMouse();
				});
			} REND;
			RN(Button) {
				o.label = "视图";
				o.width = 56; o.height = 24;
				o.normalBg = 0x00000000;
				o.hoverBg = 0x33167ff7;
				o.activeBg = 0x55167ff7;
				o.labelColor = 0xffd0d5dd;
				o.fontSize = 13;
				o.onClick = CLOSURE([=](MouseEvent*) {
					auto root = Ref(new MenuNativeItem());
					mkMenuNativeItem(root.get(), "刷新目录", CLOSURE([=](MenuNativeItem*) {
						dirNames.clear();
						refreshDirView();
					}));
					mkMenuNativeItem(root.get(), "刷新预览", CLOSURE([=](MenuNativeItem*) {
						if (!previewPath.empty()) openPrefab(previewPath);
					}));
					mkMenuNativeItem(root.get(), "当前 Prefab · 独立窗口打开", CLOSURE([=](MenuNativeItem*) {
						if (!previewPath.empty()) openStandalone(previewPath, false);
					}));
					mkMenuNativeItem(root.get(), "当前 Prefab · 无边框窗口打开", CLOSURE([=](MenuNativeItem*) {
						if (!previewPath.empty()) openStandalone(previewPath, true);
					}));
					auto menu = MenuNative::mk(root.get());
					menu->showAtMouse();
				});
			} REND;
		} REND;
		// ---- 工具栏 ----
		RN(LayoutLinear) {
			RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
			o.direction = "row";
			o.alignItems = "center";
			o.backgroundColor = 0xff2a2f3a;
			o.height = 40;
			RN(Button) {
				o.label = "返回项目列表";
				o.width = 116; o.height = 30;
				o.margin.left = 12;
				o.onClick = CLOSURE([=](MouseEvent*) { closeMainWindow(); });
			} REND;
			RN(Button) {
				o.label = "上级目录";
				o.width = 90; o.height = 30;
				o.margin.left = 8;
				o.onClick = CLOSURE([=](MouseEvent*) { backDir(); });
			} REND;
			RN(Button) {
				o.label = "刷新目录";
				o.width = 90; o.height = 30;
				o.margin.left = 8;
				o.onClick = CLOSURE([=](MouseEvent*) {
					dirNames.clear();
					refreshDirView();
				});
			} REND;
			RN(Button) {
				o.label = "打开Prefab…";
				o.width = 110; o.height = 30;
				o.margin.left = 8;
				o.onClick = CLOSURE([=](MouseEvent*) {
					std::string f = FileDialog_getFirstOpenFileName(currentDir.c_str(), "选择 Prefab JSON");
					if (!f.empty()) openPrefab(f);
				});
			} REND;
			RN(TextView) {
				o.text = currentDir;
				o.fontSize = 12;
				o.color = 0xff9aa3b2;
				o.margin.left = 18;
			} REND;
		} REND;
		// ---- 预览视图（双向可滚动：prefab 大于视口时可滚轮/滚动条查看，小时水平居中）----
		RN(ScrollArea) {
			RN(LayoutLinearCell) { o.grow = 1.0f; o.alignSelf = "stretch"; } REND;
			o.scrollDirection = "both";
			o.direction = "column";
			o.alignItems = "center";
			o.padding.setAll(28);
			o.backgroundColor = 0xff15181e;
			previewScroll = &o;
			// 内容容器：普通 LayoutLinear（不重写 react、_flagUseOutKids=false），命令式
			// appendChild 的 JSON 节点会直接进入 children（直接挂 ScrollArea 只会进 outKids、
			// 不参与布局绘制）——与底部“ScrollArea>RowWrap>文件项”同一模式。
			RN(LayoutLinear) {
				RN(LayoutLinearCell) { o.grow = -1.0f; } REND; // 自然内容尺寸，不弹性拉伸
				o.direction = "column";
				o.alignItems = "center";
				previewContainer = &o;
				if (!previewRoot) {
					RN(TextView) {
						o.text = previewHint;
						o.textAlign = "center";
						o.fontSize = 14;
						o.color = 0xff7a8291;
						o.wrap = true;
						o.width = 720;
						o.margin.top = 120;
					} REND;
				}
			} REND;
		} REND;
		// ---- 目录文件视图 ----
		RN(LayoutLinear) {
			RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
			o.direction = "column";
			o.backgroundColor = 0xff1b1f27;
			o.height = 250;
			// 路径栏
			RN(LayoutLinear) {
				RN(LayoutLinearCell) { o.grow = -1.0f; o.alignSelf = "stretch"; } REND;
				o.direction = "row";
				o.alignItems = "center";
				o.backgroundColor = 0xff232833;
				o.height = 32;
				RN(Button) {
					o.label = "上级";
					o.width = 60; o.height = 24;
					o.margin.left = 8;
					o.normalBg = 0xff3a4250;
					o.hoverBg = 0xff4a5465;
					o.labelColor = 0xffe0e4ea;
					o.fontSize = 12;
					o.onClick = CLOSURE([=](MouseEvent*) { backDir(); });
				} REND;
				RN(TextView) {
					o.text = currentDir;
					o.fontSize = 12;
					o.color = 0xffaeb6c4;
					o.margin.left = 12;
				} REND;
			} REND;
			// 目录文件滚动区
			RN(ScrollArea) {
				RN(LayoutLinearCell) { o.grow = 1.0f; o.alignSelf = "stretch"; } REND;
				o.direction = "column";
				o.scrollDirection = "both";
				o.backgroundColor = 0xff181c24;
				RN(RowWrap) {
					RN(LayoutLinearCell) { o.grow = 1.0f; o.alignSelf = "stretch"; } REND;
					o.rowGap = 4.0f;
					o.colGap = 6.0f;
					o.alignItems = "center";
					o.padding.setAll(8);
					dirWrap = &o;
				} REND;
			} REND;
		} REND;
	} REND;
	App_use()->invalidDraw();
}

void PrefabState::refreshDirView() {
	if (!dirWrap) return;
	std::vector<std::string> names = scanDirNames(currentDir);
	if (names == dirNames && dirWrap->getChildrenCount() > 1) return;
	dirNames = names;
	auto entries = scanDir(currentDir);
	RINS(dirWrap.get()) {
		RN(LayoutLinearCell) { o.grow = 1.0f; o.alignSelf = "stretch"; } REND;
		for (auto& e : entries) {
			std::string itemName = std::get<0>(e);
			bool itemIsDir = std::get<1>(e);
			std::string itemPath = std::get<2>(e);
			const std::string& name = itemName;
			bool isDir = itemIsDir;
			const std::string& fullPath = itemPath;
			RN(DirItemView, name) {
				o.state = this;
				o.path = fullPath;
				o.name = name;
				o.isDir = isDir;
				o.selected = (fullPath == dirSelectedPath);
				o.direction = "column";
				o.alignItems = "center";
				o.justifyContent = "center";
				o.width = 104;
				o.height = 94;
				o.margin.setAll(4);
				o.cursor = "pointer";
				o.backgroundColor = o.selected ? 0x552d5b8f : 0x00000000;
				RN(DirIconView) {
					o.isDir = isDir;
					o.width = 52;
					o.height = 46;
					o.margin.top = 2;
				} REND;
				RN(TextView) {
					o.text = name;
					o.fontSize = 12;
					o.color = 0xffe8eaed;
					o.textAlign = "center";
					o.wrap = false;
					o.maxLine = 1;
					o.overflowEllipsis = true;
					o.width = 96;
					o.margin.top = 4;
				} REND;
				o.cbOnEvent = CLOSURE([=](Event* ev) {
					if (auto* me = dynamic_cast<MouseEvent*>(ev)) {
						if (me->isDblClickInBubble()) {
							if (itemIsDir) {
								enterDir(itemPath);
							} else {
								openPrefab(itemPath);
							}
						} else if (me->isClickInBubble()) {
							dirSelectedPath = itemPath;
							refreshDirView();
						} else if (me->isMouseUp && me->button == 2) {
							dirSelectedPath = itemPath;
							refreshDirView();
							showDirItemMenu(itemPath, itemIsDir);
						}
					}
				});
			} REND;
		}
	} REND;
	App_use()->invalidDraw();
}

void PrefabState::enterDir(const std::string& dir) {
	if (!fs::exists(dir) || !fs::is_directory(dir)) return;
	currentDir = dir;
	dirSelectedPath.clear();
	dirNames.clear();
	refreshDirView();
	// 更新路径栏与标题
	if (mainWin) {
		mainWin->setTitle(("Prefab Realtime Viewer - " + Path_basename(currentDir)).c_str());
	}
	renderMain();      // 重建骨架以更新路径栏
	renderPreview();   // 重新挂载预览（骨架重建会清掉旧挂载）
	refreshDirView();
}

void PrefabState::backDir() {
	fs::path p(currentDir);
	fs::path parent = p.parent_path();
	if (parent.empty() || parent == p) return;
	enterDir(parent.string());
}

void PrefabState::showDirItemMenu(const std::string& path, bool isDir) {
	auto root = Ref(new MenuNativeItem());
	if (!isDir) {
		mkMenuNativeItem(root.get(), "在独立窗口打开", CLOSURE([=](MenuNativeItem*) {
			openStandalone(path, false);
		}));
		mkMenuNativeItem(root.get(), "在无边框窗口打开", CLOSURE([=](MenuNativeItem*) {
			openStandalone(path, true);
		}));
	}
	mkMenuNativeItem(root.get(), isDir ? "删除目录" : "删除文件", CLOSURE([=](MenuNativeItem*) {
		deleteEntry(path);
	}));
	auto menu = MenuNative::mk(root.get());
	menu->showAtMouse();
}

void PrefabState::deleteEntry(const std::string& path) {
	if (path.empty() || !fs::exists(path)) return;
	std::wstring wmsg;
	{
		std::string msg = "确定删除?\n\n" + path;
		int wlen = MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, nullptr, 0);
		wmsg.resize(wlen > 0 ? wlen : 0);
		if (wlen > 0) MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, &wmsg[0], wlen);
	}
	int r = MessageBoxW(nullptr, wmsg.c_str(), L"删除", MB_YESNO | MB_ICONWARNING);
	if (r != IDYES) return;
	try {
		if (fs::is_directory(path)) {
			fs::remove_all(path);
		} else {
			fs::remove(path);
		}
	} catch (const std::exception& ex) {
		printf("[PrefabRealtimeViewer] delete failed: %s\n", ex.what());
		return;
	}
	// 若删除的正是预览中的文件，清空预览
	if (Path_normal(path) == previewPath) {
		previewPath.clear();
		previewStamp = 0;
		previewRoot = nullptr;
		renderPreview();
	}
	dirSelectedPath.clear();
	dirNames.clear();
	refreshDirView();
}

// ---------------- 预览 ----------------

void PrefabState::setPreviewHint(const std::string& text) {
	previewHint = text;
	if (previewScroll) {
		previewRoot = nullptr;
		renderPreview();
	}
}

void PrefabState::renderPreview() {
	if (!previewContainer) return;
	previewContainer->removeAllChildren();
	// 复位滚动偏移
	if (previewScroll) {
		previewScroll->scroll_model.scroll_left = 0;
		previewScroll->scroll_model.scroll_top = 0;
	}
	if (!previewRoot) {
		Ref<TextView> hint{ new TextView() };
		hint->text = previewHint;
		hint->textAlign = "center";
		hint->fontSize = 14;
		hint->color = 0xff7a8291;
		hint->wrap = true;
		hint->width = 720;
		hint->margin.top = 120;
		Ref<LayoutLinearCell> hc{ new LayoutLinearCell() }; hc->grow = -1.0f;
		hint->appendChild(hc.get());
		previewContainer->appendChild(hint.get());
		App_use()->invalidDraw();
		return;
	}
	// previewContainer 是普通 LayoutLinear（非 react 节点），命令式 appendChild 直接进
	// children，可正常参与布局/绘制。previewRoot 是 JSON 导入的外部节点、不会自动配 cell，
	// 这里补一个 grow=-1（固定设计尺寸、不弹性分配）、alignSelf 留空（继承容器
	// alignItems=center 水平居中）的 LayoutLinearCell。
	previewContainer->appendChild(previewRoot.get());
	if (auto* vb = dynamic_cast<ViewBase*>(previewRoot.get())) {
		if (!vb->getLayoutCellByType<LayoutLinearCell>()) {
			Ref<LayoutLinearCell> cell{ new LayoutLinearCell() };
			cell->grow = -1.0f;
			vb->appendChild(cell.get());
		}
	}
	App_use()->invalidDraw();
}

void PrefabState::openPrefab(const std::string& path) {
	std::string json = readFileText(path);
	if (json.empty()) {
		setPreviewHint("无法读取文件:\n" + path);
		return;
	}
	std::string err;
	Ref<Node> root = io::nodeTreeFromJson(json, &err);
	if (!root) {
		std::string msg = "Prefab 导入失败";
		if (!err.empty()) msg += ":\n" + err;
		printf("[PrefabRealtimeViewer] %s\n", msg.c_str());
		setPreviewHint(msg);
		return;
	}
	previewPath = path;
	previewStamp = fileStamp(path);
	previewRoot = root;
	renderPreview();
	if (mainWin) {
		mainWin->setTitle(("Prefab Realtime Viewer - " + Path_basename(previewPath)).c_str());
	}
}

// 在独立窗口打开 prefab：borderless=false 为普通带标题栏窗口；true 为无边框窗口。
// 窗口客户区尺寸取 prefab 根节点的设计宽高（缺省 1280×800），做到 1:1 呈现。
void PrefabState::openStandalone(const std::string& path, bool borderless) {
	std::string json = readFileText(path);
	if (json.empty()) {
		MessageBoxW(nullptr, L"无法读取文件", L"独立窗口", MB_OK | MB_ICONWARNING);
		return;
	}
	std::string err;
	Ref<Node> root = io::nodeTreeFromJson(json, &err);
	if (!root) {
		std::string msg = "Prefab 导入失败";
		if (!err.empty()) msg += ":\n" + err;
		std::wstring wmsg;
		int wlen = MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, nullptr, 0);
		if (wlen > 0) { wmsg.resize(wlen); MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, &wmsg[0], wlen); }
		MessageBoxW(nullptr, wmsg.c_str(), L"独立窗口", MB_OK | MB_ICONWARNING);
		return;
	}
	// 取 prefab 设计尺寸（NaN/非法时回退 1280×800）
	float dw = 1280.0f, dh = 800.0f;
	if (auto* v = dynamic_cast<View*>(root.get())) {
		if (v->width == v->width && v->width > 1.0f) dw = v->width;   // NaN != NaN
		if (v->height == v->height && v->height > 1.0f) dh = v->height;

		//v->backgroundColor = 0xffff0000;
	}

	auto win = Ref(new Window());
	win->borderless = borderless;
	win->setRootView(dynamic_cast<ViewBase*>(root.get()));
	applyStandaloneStyle(win, dw, dh, borderless);
	std::string title = (borderless ? std::string("[无边框] ") : std::string()) + Path_basename(path);
	win->setTitle(title.c_str());
	win->moveToCenter();
	win->show();

	StandaloneEntry e;
	e.win = win;
	e.hwndId = win->id;
	e.path = path;
	e.stamp = fileStamp(path);
	e.borderless = borderless;
	standalone.push_back(e);
	printf("[PrefabRealtimeViewer] open standalone (%s): %s\n", borderless ? "borderless" : "normal", path.c_str());
}

void PrefabState::reloadStandalone(StandaloneEntry& e) {
	if (!e.win || !IsWindow((HWND)e.hwndId)) return;
	std::string json = readFileText(e.path);
	if (json.empty()) return;
	std::string err;
	Ref<Node> root = io::nodeTreeFromJson(json, &err);
	if (!root) { printf("[PrefabRealtimeViewer] standalone reload failed: %s\n", err.c_str()); return; }
	e.win->setRootView(dynamic_cast<ViewBase*>(root.get()));
	App_use()->invalidDraw();
}

void PrefabState::tickStandalone() {
	// 用户已关闭的窗口（IsWindow=false）剔除；仍开着的按文件时间戳热刷新
	standalone.erase(std::remove_if(standalone.begin(), standalone.end(),
		[&](StandaloneEntry& e) -> bool {
			if (!IsWindow((HWND)e.hwndId)) return true;
			int64_t st = fileStamp(e.path);
			if (st != 0 && st != e.stamp) {
				e.stamp = st;
				reloadStandalone(e);
			}
			return false;
		}), standalone.end());
}

void PrefabState::closeMainWindow() {
	if (mainWin) {
		mainWin->close();
	}
	mainWin = nullptr;
	mainRoot = nullptr;
	previewScroll = nullptr;
	previewContainer = nullptr;
	dirWrap = nullptr;
	previewRoot = nullptr;
	previewPath.clear();
	previewStamp = 0;
	dirNames.clear();
}

// ==================== 入口 ====================

void runPrefabRealtimeViewer() {
	SetConsoleOutputCP(65001);
	urgc.start_process_thread();

	App* app = App_use();

	Ref<PrefabState> state{new PrefabState()};
	state->loadProjects();
	state->previewHint = "双击右侧目录中的 .prefab.json 文件开始预览";

	state->listWin = Ref(new Window());
	state->listRoot = Ref(new LayoutLinear());
	state->renderProjectList();

	state->listWin->setRootView(state->listRoot);
	state->listWin->setTitle("Prefab Realtime Viewer - 项目列表");
	state->listWin->setSize(780, 560);
	state->listWin->moveToCenter();
	state->listWin->show();
	state->listWin->onClosed = CLOSURE([=](Window*) {
		printf("[PrefabRealtimeViewer] project list closed\n");
	});

	app->runEventLoop();
}
