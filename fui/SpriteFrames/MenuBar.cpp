// Converted from MenuBar.ixx (C++20 module) to classic header/source.
#include "MenuBar.h"

#include <stdio.h>

MenuBar::MenuBar() {
	//backgroundColor = 0xff2d2d2d;
	height = 28;
	direction = "row";
	alignItems = "center";
	padding.setHor(4);

	initInnerReact();
}

const char* MenuBar::getClassName() const {
	return "MenuBar";
}

void MenuBar::setMenus(const std::vector<MenuItem>& m) {
	menus = m;
	invalidReact();
}

void MenuBar::react() {
	auto self = Ref(this);
	auto& o = startInnerReact();


	for (int i = 0; i < (int)menus.size(); i++) {
		RN(TextView, i) {
			o.setText(menus[i].label);
			o.setColor(0xffe0e0e0);
			o.setFontSize(13);
			o.padding.setAxis(4, 10);
			//o.height = 22;
			o.cursor = "pointer";

			RN(HoverViewEffect) {
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

void MenuBar::showPopup(int index) {
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

void MenuBar::closePopup() {
	curIndex = -1;
	if (popup) {
		popup->destroy();
		popup = nullptr;
	}
	invalidReact();
}
