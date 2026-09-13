#pragma once

#include <string>
#include <vector>

#include "Core/Predef.h"
#include "Core/Window.h"
#include "Core/Node.h"
#include "Core/Timer.h"
#include "Layout/LayoutLinear.h"
#include "Layout/LayoutAlign.h"
#include "Layout/RowWrap.h"
#include "View/ScrollArea.h"

// 一个“独立窗口”实例：窗口生命周期由 App 的窗口列表持有，这里只保留裸指针与
// 一份 HWND(id) 拷贝；窗口被用户关闭后 IsWindow(hwndId)==false，由定时器统一剔除。
struct StandaloneEntry {
	Window* win = nullptr;
	int64_t hwndId = 0;
	std::string path;
	int64_t stamp = 0;
	bool borderless = false;
};

class PrefabState : public GcObj {
public:
	// ---- 项目列表管理页面 ----
	Ref<Window> listWin{nullptr, this};
	Ref<LayoutLinear> listRoot{nullptr, this};
	std::vector<std::string> projects;   // 项目目录列表
	int selProject = -1;                 // 当前选中项目下标

	// ---- realtimeViewer 主页面 ----
	Ref<Window> mainWin{nullptr, this};
	Ref<LayoutLinear> mainRoot{nullptr, this};
	std::string currentDir;              // 主页面当前浏览的目录
	std::string previewPath;             // 当前打开的 xx.prefab.json
	int64_t previewStamp = 0;            // 预览文件修改时间戳
	Ref<Node> previewRoot{nullptr, this};// 当前预览节点树
	Ref<ScrollArea> previewScroll{nullptr, this}; // 预览滚动区（双向滚动）
	Ref<LayoutLinear> previewContainer{nullptr, this}; // ScrollArea 内的普通线性容器，命令式挂载 JSON 节点
	std::vector<StandaloneEntry> standalone;       // 已打开的独立窗口（普通/无边框）
	Ref<RowWrap> dirWrap{nullptr, this}; // 目录文件视图容器
	std::vector<std::string> dirNames;   // 目录条目缓存（"D:name"/"F:name"）
	std::string dirSelectedPath;         // 目录视图中选中的项
	std::string previewHint;             // 预览区空态提示文本

	Ref<Timer> watchTimer{nullptr, this};

	PrefabState();

	// 项目列表页
	void loadProjects();
	void saveProjects();
	void renderProjectList();
	void openProjectDialog();   // 工具栏：打开项目
	void deleteSelectedProject();
	void enterProject();

	// 主页面
	void renderMain();
	void renderMenuBar();
	void renderToolbar();
	void renderPreview();
	void renderDirPanel();
	void refreshDirView();
	void updatePathLabel();
	void setPreviewHint(const std::string& text);

	void openPrefab(const std::string& path);   // 打开并预览 xx.prefab.json
	void openStandalone(const std::string& path, bool borderless); // 在独立窗口打开（borderless=无边框）
	void reloadStandalone(StandaloneEntry& e);  // 独立窗口热刷新
	void tickStandalone();                      // 独立窗口：关闭回收 + 文件变化热刷新
	void enterDir(const std::string& dir);
	void backDir();
	void deleteEntry(const std::string& path);  // 删除目录/文件（带确认）
	void showProjectRowMenu(int index);         // 列表页行右键菜单
	void showDirItemMenu(const std::string& path, bool isDir); // 目录项右键菜单

	void showMainWindow(const std::string& projectDir);
	void closeMainWindow();

	void tickWatch(); // 文件监听轮询
};

void runPrefabRealtimeViewer();
