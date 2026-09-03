module;
#define NOMINMAX
#include <Windows.h>
#include <string>
#include <vector>
#include <functional>

#include "Core/View.h"
#include "Core/Node.h"
#include "Core/Rect.h"
#include "Core/MouseEvent.h"
#include "Core/Event.h"
#include "Core/App.h"
#include "Core/Window.h"
#include "View/TextView.h"
#include "View/MenuNative.h"
#include "View/HoverViewEffect.h"
#include "Layout/LayoutLinear.h"
#include "Urgc/UrgcIndex.h"

export module MenuBar;

export class MenuBar : public LayoutLinear {
public:
	struct MenuItem {
		std::string label;
		std::vector<std::pair<std::string, std::function<void()>>> actions;
	};

	std::vector<MenuItem> menus;

	MenuBar() {
		//backgroundColor = 0xff2d2d2d;
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
				o.setColor(0xffe0e0e0);
				o.setFontSize(13);
				o.padding.setAxis(4, 10);
				//o.height = 22;
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
						} else {
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
		if (index < 0 || index >= (int)menus.size() ) return;

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
	Ref<MenuNative> popup{nullptr, this};
};
