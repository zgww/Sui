#include "EditText.h"
#include "../Core/Canvas.h"
#include "../Core/Window.h"
#include "../Core/Focus.h"
#include "../Core/Clipboard.h"

EditText::EditText() {
	width = 200;
	height = 28;
	cursor = "text";
	backgroundColor = bgColor;
	border->setAll(1, 0xffcccccc);
	radius->setAll(4);
	padding.setAxis(4, 8);
	needClip = true;

	Ref<EditText> self = this;
	caretTimer = mkTimerInterval_noStart(CLOSURE([=]() {
		self->caretVisible = !self->caretVisible;
		self->invalidDraw();
	}), 500);
}

void EditText::setValue(const std::string& v) {
	if (value != v) {
		value = v;
		caretPos = clampInt(value.size(), 0, (int)value.size());
		invalidDraw();
		if (onChanged) {
			onChanged->invoke(value);
		}
	}
}

void EditText::focus() {
	if (!focused) {
		focused = true;
		border->setAll(1, 0xff1677ff);
		caretVisible = true;
		if (caretTimer) caretTimer->start();
		invalidDraw();
	}
}

void EditText::blur() {
	if (focused) {
		focused = false;
		border->setAll(1, 0xffcccccc);
		if (caretTimer) caretTimer->cancel();
		invalidDraw();
	}
}

void EditText::insertText(const std::string& text) {
	value.insert(caretPos, text);
	caretPos += (int)text.size();
	invalidDraw();
	if (onChanged) {
		onChanged->invoke(value);
	}
}

void EditText::deleteBackward() {
	if (caretPos > 0) {
		value.erase(caretPos - 1, 1);
		caretPos--;
		invalidDraw();
		if (onChanged) {
			onChanged->invoke(value);
		}
	}
}

void EditText::deleteForward() {
	if (caretPos < (int)value.size()) {
		value.erase(caretPos, 1);
		invalidDraw();
		if (onChanged) {
			onChanged->invoke(value);
		}
	}
}

void EditText::moveCaret(int delta) {
	caretPos = clampInt(caretPos + delta, 0, (int)value.size());
	caretVisible = true;
	if (caretTimer) caretTimer->restart();
	invalidDraw();
}

void EditText::draw_self(Canvas* canvas) {
	View::draw_self(canvas);
	if (!canvas || !canvas->data) return;

	Vec2 size = getSizeWithoutMargin();
	float w = size.x;
	float h = size.y;

	canvas->fontSize(fontSize);
	canvas->fontFace("sans");

	float pl = padding.left + border->l->w;
	float pt = padding.top + border->t->w;

	if (value.empty() && !placeholder.empty()) {
		canvas->fillColorByInt32(placeholderColor);
		canvas->textAlign(NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
		canvas->text(pl, h / 2.0f + pt - padding.top, placeholder.c_str());
	} else if (!value.empty()) {
		canvas->fillColorByInt32(color);
		canvas->textAlign(NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
		canvas->text(pl, h / 2.0f + pt - padding.top, value.c_str());

		if (focused && caretVisible) {
			float bounds[4] = {0};
			std::string leftText = value.substr(0, caretPos);
			canvas->textBounds(0, 0, leftText.c_str(), nullptr, bounds);
			float caretX = pl + (bounds[2] - bounds[0]);
			canvas->beginPath();
			canvas->rect(caretX, pt, 1, h - pt - padding.bottom);
			canvas->fillColorByInt32(caretColor);
			canvas->fill();
		}
	}
}

void EditText::onEvent(Event* ev) {
	View::onEvent(ev);
	if (ev->isStopPropagation) return;

	MouseEvent* me = dynamic_cast<MouseEvent*>(ev);
	if (me) {
		if (me->isMouseDown && me->isBubble()) {
			insFocus()->focus(this);
			focus();
		}
		return;
	}

	KeyEvent* ke = dynamic_cast<KeyEvent*>(ev);
	if (ke && ke->isKeyDown && focused) {
		if (ke->ctrl) {
			if (ke->key == "c" || ke->key == "C") {
				clipboard_setText(value.c_str());
			} else if (ke->key == "v" || ke->key == "V") {
				std::string clip = clipboard_getText();
				if (!clip.empty()) insertText(clip);
			} else if (ke->key == "a" || ke->key == "A") {
				caretPos = (int)value.size();
				invalidDraw();
			}
			return;
		}

		if (ke->key == "Backspace") {
			deleteBackward();
		} else if (ke->key == "Delete") {
			deleteForward();
		} else if (ke->key == "ArrowLeft") {
			moveCaret(-1);
		} else if (ke->key == "ArrowRight") {
			moveCaret(1);
		} else if (ke->key == "Enter") {
			blur();
			insFocus()->blurNode(this);
		} else if (ke->char_code >= 32 && ke->char_code < 127) {
			char ch = (char)ke->char_code;
			insertText(std::string(1, ch));
		}

		caretVisible = true;
		if (caretTimer) caretTimer->restart();
		invalidDraw();
		return;
	}

	FocusEvent* fe = dynamic_cast<FocusEvent*>(ev);
	if (fe) {
		if (fe->isFocus) {
			focus();
		} else if (fe->isBlur) {
			blur();
		}
	}
}

void EditText::onUnmounting() {
	blur();
}
