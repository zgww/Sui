// Converted from ImageViewerApp.ixx (C++20 module) to classic header/source.
#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <string>
#include <functional>

#include "Core/Window.h"
#include "Core/Node.h"
#include "Layout/LayoutAlign.h"
#include "View/Button.h"
#include "Urgc/Urgc.h"

#include "SpriteSheet.h"
#include "ImageCanvasView.h"

// 以下两个类定义在 ImageViewerApp.cpp 内部使用（原模块中未导出）
class SpritePreviewView;
class AnimationListView;

class SpriteEditorState : public GcObj {
public:
	Ref<Window> win{nullptr, this};
	Ref<LayoutAlign> root{nullptr, this};
	Ref<SpriteSheetInfo> info{nullptr, this};

	std::string currentFile;               // 当前 SpriteFrames 文件路径（空表示未保存）
	SpriteSheetAnim* curAnim = nullptr;
	int curAnimIndex = 0;
	bool previewPlaying = true;

	ImageCanvasView* canvasPtr = nullptr;
	SpritePreviewView* previewPtr = nullptr;
	AnimationListView* listPtr = nullptr;

	SpriteEditorState();

	// ---------- 动作 ----------
	void onNewAnim();
	void onDeleteAnim();
	void onSelectAnim(int index);
	void onCellClicked(int gx, int gy, bool ctrl);
	void onOpenImage();
	void onOpenSpriteFile();
	void onSave();
	void onSaveAs();
	void onAbout();

	// ---------- 文件操作 ----------
	void openImage(const std::string& path);
	void openSpriteFile(const std::string& path);
	void saveToFile(const std::string& path);

	// ---------- 预览 ----------
	void startPreview();
	void stopPreview();
	void restartPreview();
	void onGridChanged();

	// ---------- 渲染 ----------
	void render();

private:
	// 工具栏按钮样式
	void styleToolBtn(Button& b);

	// 表单一行：标签 + 输入框（parent 为父容器）
	void formField(Node& parent, const std::string& label, const std::string& key, std::function<void(const std::string&)> onChange);
};

void runImageViewer(const std::string& initialFile);
