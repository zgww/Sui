#include <Windows.h>
#include <string>
#include <format>
#include <stdio.h>
#include "Core/App.h"
#include "Core/Window.h"
#include "Layout/RowWrap.h"
#include "Layout/LayoutLinear.h"
#include "View/TextView.h"
#include "View/ScrollArea.h"
#include "View/Button.h"
#include "View/MenuNative.h"
#include "View/HoverViewEffect.h"
#include "Naga/Path.h"

class MenuBar : public LayoutLinear {
public:
	struct MenuItem {
		std::string label;
		std::vector<std::pair<std::string, std::function<void()>>> actions;
	};

	std::vector<MenuItem> menus;

	MenuBar() {
		backgroundColor = 0xff2d2d2d;
		height = 28;
		direction = "row";
		alignItems = "center";
		padding.setHor(4);

		initInnerReact();
	}

	virtual const char* getClassName() const override { return "MenuBar"; }

	void setMenus(const std::vector<MenuItem>& m) {
		menus = m;
		invalidReact();
	}

	void react() override {
		auto self = Ref(this);
		auto& o = startInnerReact();


		for (int i = 0; i < (int)menus.size(); i++) {
			R(TextView, i) {
				o.setText(menus[i].label);
				//o.setColor(0xffe0e0e0);
				o.setColor(0xffe0e0e0);
				o.setFontSize(13);
				o.padding.setAxis(4, 10);
				o.height = 22;
				o.cursor = "pointer";

				R(HoverViewEffect) {
					o.backgroundColor = 0x00ffffff;
					o.hoverBackgroundColor = 0xff3a3a3a;
					o.activeBackgroundColor = 0xff3a6dcf;
					//o.isActive = (i == curIndex && self->popup != nullptr);
					o.onClick = CLOSURE([=](MouseEvent* me) {

						printf("OnCLick MenuItem===================================\n");
						if (self->popup != nullptr && self->curIndex == i) {
							self->closePopup();
						}
						else {
							self->showPopup(i);
						}
						});
					o.cbOnHoverChanged = CLOSURE([=](ViewBase* v) {
						printf("hover:%d,   \n", v->hover);
						//if (v->hover == 0) {
						//	self->closePopup();
						//}
						if (v->hover && self->popup != nullptr && self->curIndex != i) {
							self->closePopup();
							mkTimerTimeout(CLOSURE(
								[=]() {
									self->showPopup(i);
								}
							), 100);
						}
						});
				} REND;
			} REND;
		}

		this->placeOutKids();

		endInnerReact();
	}

	void showPopup(int index) {
		if (index < 0 || index >= (int)menus.size()) return;

		auto self = Ref(this);
		curIndex = index;
		invalidReact();

		auto item = mkMenuNativeItem(nullptr, "", nullptr);
		for (auto& action : menus[index].actions) {
			std::string label = action.first;
			auto fn = action.second;
			mkMenuNativeItem(item.get(), label,
				CLOSURE([=](MenuNativeItem* mi) {
					self->closePopup();
					fn();
					}));
		}

		auto tmpPopup = MenuNative::mk(item.get());

		tmpPopup->cbOnDismiss = CLOSURE(
			[=]() {
				self->closePopup();
			}
		);

		popup = tmpPopup;

		auto btn = dynamic_cast<ViewBase*>(getChildAsView(index));
		if (btn) {
			Rect r = btn->get_abs_rect();
			tmpPopup->showAt((int)r.x, (int)r.bottom());
		}
	}

	void closePopup() {
		curIndex = -1;
		if (popup) {
			popup->destroy();
			popup = nullptr;
		}
		invalidReact();
	}

private:
	int curIndex = -1;
	Ref<MenuNative> popup{ nullptr, this };
};



class ShadowView : public View {
public:
	virtual void draw_self(Canvas * canvas) override{
		canvas->shadowBlur( 10);
		canvas->shadowColor (0, 0, 0, 128);
		canvas->shadowOffset(5, 5);
		View::draw_self(canvas);
	}
};
void AppMain() {
	urgc.start_process_thread();
	auto app = App_use();
	auto win = Ref(new Window());

	auto root = Ref(new ScrollArea());
	RINS(root.get()) {
		o.useMaxWidthConstraint = true;
		o.backgroundColor = 0xffefefef;
		o.backgroundColor = 0xff999999;

		R(LayoutLinear) {
			o.row().aic();

			R(MenuBar) {
				R(LayoutLinearCell) { o.grow = 1; } REND;
				//o.backgroundColor = 0xfffd2d2d;

				if (o.created) {
					std::vector<MenuBar::MenuItem> items = {
						{ "文件", {
							{ "打开", [=]() { 
							//onOpenFile(); 
						} },
							{ "退出", [=]() {
								if (win.get()) win->close();
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
								//openConsole();
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
				o.setSrc(Path_resolveFromExecutionDir("icon/open.png"));
				o.setLabel("打开");
				o.labelColor = 0xffffffff;
				o.setNormalBg(0xff2d2d2d);
				o.hoverBg = 0xff404040;
				o.padding.setAxis(0, 0);
				//o.width = 32;
				//o.height = 32;
				o.onClick = CLOSURE([=](MouseEvent* me) {
					//onOpenFile();
					});
				//o.cbOnEvent = CLOSURE([=](Event* ev) {
					//if (auto* me = dynamic_cast<MouseEnterEvent*>(ev)) showTooltip("打开", me->clientX, me->clientY);
					//else if (dynamic_cast<MouseLeaveEvent*>(ev)) hideTooltip();
					//});
			} REND;
		} REND;

		R(RowWrap) {

			for (int i = 0; i < 10; i++) {
				R(TextView, i) {
					o.setText(std::format("第[{}]项", i));
				} REND;
			}

			for (int i = 0; i < 1000; i++) {
				R(ShadowView, i) {
					o.backgroundColor = 0xff2d2d2d;
					o.width = 40;
					o.height = 40;
					o.margin.setAll(10);
				} REND;
			}
		} REND;

		win->setRootView(root);
		win->setSize(600, 400);
		win->moveToCenter();
		win->setTitle("标题");
		win->show();
	} REND;
	app->runEventLoop();
}

int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {    
	//FreeConsole();//解除ide/vscode的控制台。否则AllocConsole无效
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	//printf("lpCmdLine:%s\n", lpCmdLine);

	std::string initialFile = lpCmdLine;
	AppMain();
	return 0;
}

int main(int argc, char* argv[]) {
	std::string initialFile;
	if (argc > 1) {
		initialFile = argv[1];
	}

	AppMain();
	return 0;
}
