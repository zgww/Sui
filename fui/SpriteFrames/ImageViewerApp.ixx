module;
#define NOMINMAX
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "Core/App.h"
#include "Core/Window.h"
#include "Core/Canvas.h"
#include "Core/Node.h"
#include "Core/View.h"
#include "Core/Image.h"
#include "Core/Vec2.h"
#include "Core/MouseEvent.h"
#include "Core/Event.h"
#include "Core/Predef.h"
#include "Core/Timer.h"
#include "Core/Theme.h"
#include "Layout/LayoutLinear.h"
#include "Layout/LayoutAlign.h"
#include "View/Button.h"
#include "View/TextView.h"
#include "View/EditText.h"
#include "View/ScrollArea.h"
#include "View/HoverViewEffect.h"
#include "View/SplitterView.h"
#include "Dialog/FileDialog.h"
#include "Urgc/Urgc.h"

export module ImageViewerApp;
import ImageCanvasView;
import MenuBar;
import SpriteSheet;

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

static std::string fmtFloat(float v) {
	char buf[48];
	snprintf(buf, sizeof(buf), "%g", v);
	return buf;
}

static std::string readFileAll(const std::string& path) {
	std::ifstream in(path, std::ios::binary);
	if (!in) return "";
	std::ostringstream ss;
	ss << in.rdbuf();
	return ss.str();
}

static bool writeFileAll(const std::string& path, const std::string& data) {
	std::ofstream out(path, std::ios::binary | std::ios::trunc);
	if (!out) return false;
	out << data;
	return true;
}

static bool isSpriteExt(const std::string& path) {
	namespace fs = std::filesystem;
	std::string ext = fs::path(path).extension().string();
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
	return ext == ".json" || ext == ".sfs" || ext == ".sframes";
}

static std::string ensureJsonExt(const std::string& path) {
	namespace fs = std::filesystem;
	std::string ext = fs::path(path).extension().string();
	if (ext.empty()) return path + ".json";
	return path;
}

// 动画预览视图：从精灵表中裁剪出当前帧并循环播放
class SpritePreviewView : public View {
public:
	SpriteSheetInfo* info = nullptr;
	SpriteSheetAnim* anim = nullptr;

	void play();
	void stop();

	virtual const char* getClassName() const override { return "SpritePreviewView"; }

	void draw_self(Canvas* canvas) override {
		View::draw_self(canvas);

		Vec2 sz = getSizeWithoutMargin();
		if (sz.x <= 4 || sz.y <= 4) return;

		canvas->save();
		canvas->translate(frame.x + margin.left, frame.y + margin.top);

		// 背景
		canvas->beginPath();
		canvas->roundRect(0, 0, sz.x, sz.y, 4);
		canvas->fillColorByInt32(0xff1b1b1b);
		canvas->fill();

		if (!info || info->image.empty()) {
			drawEmpty(canvas, sz.x, sz.y, "无图片");
			canvas->restore();
			return;
		}

		if (!_img) {
			_img = canvas->createImage(info->image.c_str());
		}
		if (!_img) {
			drawEmpty(canvas, sz.x, sz.y, "加载失败");
			canvas->restore();
			return;
		}

		float imgW = _img->width();
		float imgH = _img->height();
		if (imgW <= 0 || imgH <= 0) {
			canvas->restore();
			return;
		}

		float cellW = info->getCellWidth((int)imgW);
		float cellH = info->getCellHeight((int)imgH);
		if (cellW <= 0 || cellH <= 0) {
			drawEmpty(canvas, sz.x, sz.y, "参数无效");
			canvas->restore();
			return;
		}

		int n = anim ? anim->coords->size() : 0;
		if (n <= 0) {
			drawEmpty(canvas, sz.x, sz.y, "无动画帧");
			canvas->restore();
			return;
		}

		int idx = frameIndex % n;
		SpriteSheetFrameCoord* c = anim->coords->get(idx);
		if (!c) {
			canvas->restore();
			return;
		}

		float sx = c->x * (cellW + info->colGap);
		float sy = c->y * (cellH + info->rowGap);

		float scale = std::min(sz.x / cellW, sz.y / cellH);
		float dw = cellW * scale;
		float dh = cellH * scale;
		float dx = (sz.x - dw) / 2.0f;
		float dy = (sz.y - dh) / 2.0f;

		canvas->drawImageAtRect(_img.get(), sx, sy, cellW, cellH, dx, dy, dw, dh, 1.0f);

		// 帧号提示
		canvas->fontFace("sans");
		canvas->fontSize(12);
		canvas->textAlign(CANVAS_ALIGN_RIGHT | CANVAS_ALIGN_BOTTOM);
		canvas->fillColorByInt32(0xffffffff);
		canvas->text(sz.x - 6, sz.y - 4, std::to_string(idx).c_str());

		canvas->restore();
	}

private:
	Ref<Image> _img{nullptr, this};
	Ref<Timer> timer{nullptr, this};
	int frameIndex = 0;
	SpriteSheetAnim* _playingAnim = nullptr;

	void drawEmpty(Canvas* canvas, float w, float h, const char* msg) {
		canvas->fontFace("sans");
		canvas->fontSize(13);
		canvas->textAlign(CANVAS_ALIGN_CENTER | CANVAS_ALIGN_MIDDLE);
		canvas->fillColorByInt32(0xff777777);
		canvas->text(w / 2.0f, h / 2.0f, msg);
	}
};

void SpritePreviewView::play() {
	if (!info || !anim) return;
	if (_playingAnim == anim && timer) return; // 已在播放同一动画

	stop();

	frameIndex = 0;
	int n = anim->coords->size();
	if (n <= 0) return;

	_playingAnim = anim;
	float fps = info->fps > 0.5f ? info->fps : 10.0f;
	int interval = std::max(1, (int)(1000.0f / fps + 0.5f));

	auto self = Ref(this);
	timer = mkTimerInterval(CLOSURE([=]() {
		if (!self->_playingAnim) return;
		int n = self->_playingAnim->coords->size();
		if (n <= 0) return;
		self->frameIndex = (self->frameIndex + 1) % n;
		self->invalidDraw();
	}), interval);
	invalidDraw();
}

void SpritePreviewView::stop() {
	if (timer) {
		timer->cancel();
		timer = nullptr;
	}
	_playingAnim = nullptr;
	frameIndex = 0;
	invalidDraw();
}

// 左侧动画列表
class AnimationListView : public ScrollArea {
public:
	SpriteSheetInfo* info = nullptr;
	int selectedIndex = -1;

	Ref<Closure<void(int)>> onSelect{nullptr, this};

	AnimationListView() {
		backgroundColor = 0x00262626;
		initInnerReact();
	}

	virtual const char* getClassName() const override { return "AnimationListView"; }

	void react() override {
		auto self = Ref(this);
		startInnerReact();
		auto& o = *this;

		o.direction = "column";
		o.alignItems = "stretch";
		o.placeKids(this->gocOutKids());

		int n = info ? info->anims->size() : 0;
		for (int i = 0; i < n; i++) {
			R(TextView, i) {
				SpriteSheetAnim* anim = self->info ? self->info->anims->get(i) : nullptr;
				std::string t;
				if (anim) {
					t = anim->name + " (" + std::to_string(anim->coords->size()) + "帧)";
				}
				o.setText(t);
				o.setColor(0xffe0e0e0);
				o.setFontSize(13);
				o.textAlign = "left";
				o.height = 32;
				o.padding.setHor(10);
				o.cursor = "pointer";

				R(HoverViewEffect) {
					o.backgroundColor = (i == self->selectedIndex) ? 0x60407fff : 0x00333333;
					o.hoverBackgroundColor = 0xff3a3a3a;
					o.activeBackgroundColor = 0xff3a6dcf;
					o.isActive = (i == self->selectedIndex);
					o.onClick = CLOSURE([=](MouseEvent* me) {
						if (self->onSelect) self->onSelect->invoke(i);
					});
				} REND;
			} REND;
		}

		_reactScrollBar();
		endInnerReact();
	}
};

export class SpriteEditorState : public GcObj {
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

	SpriteEditorState() {
		CtorGuard _(this);
		info = new SpriteSheetInfo();

		Ref<SpriteSheetAnim> a{new SpriteSheetAnim()};
		a->name = "anim_0";
		info->anims->push(a.get());
		curAnim = a.get();
		curAnimIndex = 0;
	}

	// ---------- 动作 ----------
	void onNewAnim() {
		int n = info->anims->size();
		Ref<SpriteSheetAnim> a{new SpriteSheetAnim()};
		a->name = "anim_" + std::to_string(n);
		info->anims->push(a.get());
		curAnim = a.get();
		curAnimIndex = info->anims->size() - 1;
		restartPreview();
		render();
	}

	void onDeleteAnim() {
		if (curAnimIndex < 0 || curAnimIndex >= info->anims->size()) return;
		if (info->anims->size() <= 1) return; // 至少保留一个动画

		info->anims->remove_at(curAnimIndex);
		if (curAnimIndex >= info->anims->size()) curAnimIndex = info->anims->size() - 1;
		curAnim = info->anims->get(curAnimIndex);
		restartPreview();
		render();
	}

	void onSelectAnim(int index) {
		if (index < 0 || index >= info->anims->size()) return;
		curAnimIndex = index;
		curAnim = info->anims->get(index);
		if (canvasPtr) {
			canvasPtr->curAnim = curAnim;
			canvasPtr->invalidDraw();
		}
		restartPreview();
		render();
	}

	void onCellClicked(int gx, int gy, bool ctrl) {
		if (!curAnim) return;
		if (ctrl) {
			curAnim->removeFrame(gx, gy);
		} else {
			curAnim->addFrame(gx, gy);
		}
		if (canvasPtr) canvasPtr->invalidDraw();
		render();
	}

	void onOpenImage() {
		auto result = FileDialog_getFirstOpenFileName("./", "选择精灵表图片");
		if (!result.empty()) {
			openImage(result);
		}
	}

	void onOpenSpriteFile() {
		auto result = FileDialog_getFirstOpenFileName("./", "打开 SpriteFrames 文件");
		if (!result.empty()) {
			openSpriteFile(result);
		}
	}

	void onSave() {
		if (currentFile.empty()) {
			onSaveAs();
			return;
		}
		saveToFile(currentFile);
	}

	void onSaveAs() {
		auto result = FileDialog_getSaveFileName("./", "保存 SpriteFrames 文件");
		if (result.empty()) return;
		result = ensureJsonExt(result);
		saveToFile(result);
	}

	void onAbout() {
		MessageBoxW(nullptr, L"SpriteFrames 编辑器\n\n基于 fui GUI 框架开发的精灵表帧动画编辑器\n使用 URGC 内存管理", L"关于我们", MB_OK | MB_ICONINFORMATION);
	}

	// ---------- 文件操作 ----------
	void openImage(const std::string& path) {
		info->image = path;
		currentFile.clear();
		if (canvasPtr) {
			canvasPtr->setSrc(path);
			canvasPtr->invalidDraw();
		}
		restartPreview();
		render();
	}

	void openSpriteFile(const std::string& path) {
		std::string text = readFileAll(path);
		if (text.empty()) {
			MessageBoxW(nullptr, L"读取文件失败或文件为空", L"打开失败", MB_OK | MB_ICONWARNING);
			return;
		}

		SpriteSheetInfo_fromJsonString(info.get(), text);
		currentFile = path;

		if (info->anims->size() == 0) {
			Ref<SpriteSheetAnim> a{new SpriteSheetAnim()};
			a->name = "anim_0";
			info->anims->push(a.get());
		}
		if (curAnimIndex >= info->anims->size()) curAnimIndex = 0;
		curAnim = info->anims->get(curAnimIndex);

		if (canvasPtr) {
			canvasPtr->setSrc(info->image);
			canvasPtr->info = info.get();
			canvasPtr->curAnim = curAnim;
			canvasPtr->invalidDraw();
		}
		restartPreview();
		render();
	}

	void saveToFile(const std::string& path) {
		std::string text = SpriteSheetInfo_toJsonString(info.get());
		if (writeFileAll(path, text)) {
			currentFile = path;
		} else {
			MessageBoxW(nullptr, L"写入文件失败", L"保存失败", MB_OK | MB_ICONWARNING);
		}
	}

	// ---------- 预览 ----------
	void startPreview() {
		previewPlaying = true;
		if (previewPtr) previewPtr->play();
	}

	void stopPreview() {
		previewPlaying = false;
		if (previewPtr) previewPtr->stop();
	}

	void restartPreview() {
		if (previewPtr) {
			previewPtr->stop();
			if (previewPlaying) previewPtr->play();
		}
	}

	void onGridChanged() {
		if (canvasPtr) canvasPtr->invalidDraw();
		restartPreview();
	}

	// ---------- 渲染 ----------
	void render() {
		auto self = Ref(this);
		auto& t = *themeIns();
		t.scrollbar_barBg = 0x99ffffff;

		RINS(root.get()) {
			// 主容器：纵向排列
			R(LayoutLinear) {
				R(LayoutAlignCell) {
					o.setCenter();
					o.sizeRatio.setScalar(1.0f);
				} REND;

				o.direction = "column";
				o.aiStretch();
				o.backgroundColor = 0xff1e1e1e;

				// 菜单栏
				R(MenuBar) {
					if (o.created) {
						std::vector<MenuBar::MenuItem> items = {
							{ "文件", {
								{ "打开 SpriteFrames", [=]() { self->onOpenSpriteFile(); } },
								{ "打开图片", [=]() { self->onOpenImage(); } },
								{ "保存", [=]() { self->onSave(); } },
								{ "另存为", [=]() { self->onSaveAs(); } },
								{ "退出", [=]() {
									if (self->win) self->win->close();
								} }
							}},
							{ "关于", {
								{ "关于我们", [=]() { self->onAbout(); } },
								{ "打开控制台", [=]() { openConsole(); } }
							}}
						};
						o.setMenus(items);
					}
				} REND;

				// 工具栏
				R(LayoutLinear) {
					o.direction = "row";
					o.aic();
					o.height = 40;
					o.backgroundColor = 0xff2d2d2d;
					o.padding.setHor(8);

					R(Button) {
						o.setLabel("打开图片");
						styleToolBtn(o);
						o.onClick = CLOSURE([=](MouseEvent* me) { self->onOpenImage(); });
					} REND;

					R(Button) {
						o.setLabel("保存");
						styleToolBtn(o);
						o.onClick = CLOSURE([=](MouseEvent* me) { self->onSave(); });
					} REND;

					R(View) { o.width = 1; o.height = 22; o.backgroundColor = 0xff3a3a3a; o.margin.setHor(5); } REND;

					R(Button) {
						o.setLabel("添加动画");
						styleToolBtn(o);
						o.onClick = CLOSURE([=](MouseEvent* me) { self->onNewAnim(); });
					} REND;

					R(Button) {
						o.setLabel("删除动画");
						styleToolBtn(o);
						o.onClick = CLOSURE([=](MouseEvent* me) { self->onDeleteAnim(); });
					} REND;
				} REND;

				// 主体：左列表 + 中间画布 + 右表单

				R(LayoutLinear) {
					o.direction = "row";
					o.aiStretch();

					R(LayoutLinearCell) { o.grow = 1; } REND;

					// ===== 左侧：动画列表 + 预览 =====
					R(LayoutLinear) {
						o.direction = "column";
						o.aiStretch();
						o.width = 230;
						o.backgroundColor = 0xff262626;
						o.padding.setAll(8);

						R(LayoutLinearCell) { o.grow = 1; } REND;


						R(LayoutLinear) {
							o.column();
							o.backgroundColor = 0xffff2626;

							R(LayoutLinearCell) { o.grow = 1; } REND;
							R(TextView) {
								o.setText("动画列表");
								o.setColor(0xffaaaaaa);
								o.setFontSize(12);
								o.margin.bottom = 6;
							} REND;

							R(AnimationListView) {
								o.backgroundColor = 0xffffff26;
								listPtr = &o;
								o.info = info.get();
								o.selectedIndex = curAnimIndex;
								if (o.created) {
									o.onSelect = CLOSURE([=](int i) {
										self->onSelectAnim(i);
									});
								}
								R(LayoutLinearCell) { o.grow = 1; } REND;
							} REND;
						} REND;

						R(SplitterView) {}REND;

						R(LayoutLinear) {
							o.column();

							R(LayoutLinearCell) { o.grow = 1; } REND;
							R(TextView) {
								o.setText("动画预览");
								o.setColor(0xffaaaaaa);
								o.setFontSize(12);
								o.margin.top = 8;
								o.margin.bottom = 2;
							} REND;

							R(SpritePreviewView) {
								previewPtr = &o;
								o.height = 150;
								o.backgroundColor = 0xff1b1b1b;
							} REND;

							R(LayoutLinear) {
								o.direction = "row";
								o.aic();
								o.margin.top = 6;

								R(Button) {
									o.setLabel("播放");
									styleToolBtn(o);
									o.onClick = CLOSURE([=](MouseEvent* me) { self->startPreview(); });
								} REND;

								R(Button) {
									o.setLabel("停止");
									styleToolBtn(o);
									o.onClick = CLOSURE([=](MouseEvent* me) { self->stopPreview(); });
								} REND;
							} REND;
						} REND;
					} REND;

					R(SplitterView) {}REND;
					// ===== 中间：画布 =====
					R(ImageCanvasView) {
						canvasPtr = &o;
						o.info = info.get();
						o.curAnim = curAnim;
						if (o.created) {
							o.onCellClicked = CLOSURE([=](int gx, int gy, bool ctrl) {
								self->onCellClicked(gx, gy, ctrl);
							});
						}
						if (!info->image.empty()) {
							o.setSrc(info->image);
						}
						R(LayoutLinearCell) { o.grow = 3; } REND;
					} REND;

					//R(SplitterView) {}REND;

					// ===== 右侧：表单 =====
					R(LayoutLinear) {
						o.direction = "column";
						o.aiStretch();
						o.width = 250;
						o.backgroundColor = 0xff262626;
						o.padding.setAll(8);

						//R(LayoutLinearCell) { o.grow = 1; } REND;

						R(TextView) {
							o.setText("精灵表属性");
							o.setColor(0xffaaaaaa);
							o.setFontSize(12);
							o.margin.bottom = 10;
						} REND;


						formField(o, "列数", "cols", [=](const std::string& v) {
							self->info->cols = std::atoi(v.c_str());
							self->onGridChanged();
						});
						formField(o, "行数", "rows", [=](const std::string& v) {
							self->info->rows = std::atoi(v.c_str());
							self->onGridChanged();
						});
						formField(o, "列间隔", "colGap", [=](const std::string& v) {
							self->info->colGap = std::atoi(v.c_str());
							self->onGridChanged();
						});
						formField(o, "行间隔", "rowGap", [=](const std::string& v) {
							self->info->rowGap = std::atoi(v.c_str());
							self->onGridChanged();
						});
						formField(o, "帧率 fps", "fps", [=](const std::string& v) {
							self->info->fps = (float)std::atof(v.c_str());
							self->restartPreview();
						});

						R(TextView) {
							std::string cur = curAnim ? curAnim->name : "无";
							std::string cnt = curAnim ? std::to_string(curAnim->coords->size()) : "0";
							//o.setText("当前动画: " + cur + " (" + cnt + " 帧)\n点击画布帧加入动画，Ctrl+点击移除");
							o.setText("当前动画");
							o.setColor(0xff999999);
							o.setFontSize(12);
							//o.setWrap(true);
							o.margin.top = 14;
						} REND;
					} REND;
				} REND;
			} REND;
		} REND;

		// 同步预览状态（幂等）
		if (previewPtr) {
			previewPtr->info = info.get();
			previewPtr->anim = curAnim;
			if (previewPlaying) previewPtr->play();
			else previewPtr->stop();
		}
	}

private:
	// 工具栏按钮样式
	void styleToolBtn(Button& b) {
		b.setFontSize(13);
		b.setNormalBg(0x002d2d2d);
		b.hoverBg = 0xff404040;
		b.activeBg = 0xff353535;
		b.setLabelColor(0xffe0e0e0);
		b.padding.setAxis(8, 4);
		b.margin.setHor(3);
	}

	// 表单一行：标签 + 输入框（parent 为父容器）
	void formField(Node& parent, const std::string& label, const std::string& key, std::function<void(const std::string&)> onChange) {
		auto self = Ref(this);
		auto& o = parent;
		R(LayoutLinear) {
			o.direction = "row";
			o.aic();
			o.height = 38;

			R(TextView) {
				o.setText(label);
				o.setColor(0xffcccccc);
				o.setFontSize(13);
				o.width = 60;
			} REND;

			R(EditText, key) {
				o.width = 90;
				o.height = 26;
				o.placeholder = label;
				o.setColor(0xffe0e0e0);
				o.setPlaceholder_color(0xff666666);
				if (o.created) {
					o.onValueChanged = CLOSURE([=](EditText* et) {
						onChange(et->getValue());
					});
				}
				// 更新初值（聚焦时不覆盖，避免打断输入）
				if (key == "fps") {
					o.setValue_notInFocus(fmtFloat(self->info->fps));
				} else {
					int iv = 0;
					if (key == "cols") iv = self->info->cols;
					else if (key == "rows") iv = self->info->rows;
					else if (key == "colGap") iv = self->info->colGap;
					else if (key == "rowGap") iv = self->info->rowGap;
					o.setValue_notInFocus(std::to_string(iv));
				}
			} REND;
		} REND;
	}
};

export void runImageViewer(const std::string& initialFile) {
	SetConsoleOutputCP(65001);
	urgc.start_process_thread();

	App* app = App_use();

	Ref<SpriteEditorState> state{new SpriteEditorState()};

	state->win = Ref(new Window());
	state->root = Ref(new LayoutAlign());

	state->render();

	state->win->setRootView(state->root);
	state->win->setTitle("SpriteFrames 编辑器");
	state->win->setSize(1280, 820);
	state->win->moveToCenter();
	state->win->show();

	state->win->onClosed = CLOSURE([=](Window* win) {
		printf("SpriteFrames closed\n");
	});

	if (!initialFile.empty()) {
		if (isSpriteExt(initialFile)) {
			state->openSpriteFile(initialFile);
		} else {
			state->openImage(initialFile);
		}
	}

	app->runEventLoop();
}