#include "Select.h"
#include "./MenuNative.h"

void Select::appendOptionCStr(const char* text) {
	if (text) {
		this->options.push_back((text));
	}
}

void Select::appendOption(std::string text) {
	if (text != "") {
		this->options.push_back(text);
	}
}

void Select::react() {
	auto& o = startInnerReact();

	R(TextView) {
		std::string text = getLabel();
		o.setText(text == "" ? ("please select") : text);
	} REND;

	R(TextView) {
		o.setText(
			this->isActive
			? (" ^ ")
			: (" v ")
		);
	} REND;

	endInnerReact();
}

std::string Select::getLabel() {
	if (value >= 0 && value < options.size()) {
		return options[value];
	}
	return "";
}

void Select::setIsActive(bool v) {
	this->isActive = v;
	this->invalidReact();
	//this->invalidLayout();
}

void Select::setValue(int i) {
	this->value = i;
	// this->text = text == null ? str(""): text
	this->invalidReact();
}

void Select::showPopupMenu() {
	auto self = Ref(this);
	this->setIsActive(true);

	auto onActive = CLOSURE([=](MenuNativeItem* item) {
		printf("\n\nactive menu:%d, %s\n\n", item->id,
			item->label == "" ? "null" : item->label.c_str());
		// this->setText(item.label)
		this->setValue(item->id);
		this->fire_onChanged();
		});


	HIER(mkMenuNativeItem(nullptr, "", nullptr)) {
		for (int i = 0; i < this->options.size(); i++) {
			std::string text = this->options[(i)];
			HIER(mkMenuNativeItem(o, text, onActive)) { o->id = i; } HEND;

		}

		Vec2 p = Mouse_getPos();
		Rect r = self->get_abs_rect();
		auto menu = MenuNative::mk(o);
		menu->cbOnDismiss = CLOSURE([=]() {

			printf("cbOnDismiss\n");;
			self->setIsActive(false);
			});
		menu->showAt(r.x, r.bottom());
		//menu->showAtMouse();

	}HEND;
}

void Select::onEvent(Event* ev) {
	if (auto me = dynamic_cast< MouseEvent*>(ev)) {
		if (me->isClickInBubble()) {
			printf("Click Select\n");
			this->showPopupMenu();
			// this->setChecked(!this->checked)
			// MessageDialog_alert("content", "title")

			ev->stopPropagation();
		}
	}
}


void Select::fire_onChanged() {
	if (this->onChanged) {
		std::string label = getLabel();
		this->onChanged->invoke(this->value, label);
	}
}

Select::Select() {
	CtorGuard g(this);


	this->cursor = "pointer";

	this->border.setAll(1, 0xff999999);
	this->radius.setAll(6);
	this->padding.setAxis(4, 8);

	initInnerReact();
}
