#include "Toast.h"
#include "../Core/Window.h"
#include "../Core/App.h"

Toast::Toast() {
	backgroundColor = bgColor;
	radius.setAll(8);
	padding.setAxis(10, 16);
	visible = false;
}

void Toast::showMessage(const std::string& msg, int durationMs) {
	message = msg;
	duration = durationMs;
	visible = true;
	invalidLayout();

	Ref<Toast> self = this;
	dismissTimer = mkTimerTimeout(CLOSURE([=]() {
		self->visible = false;
		self->invalidLayout();
	}), duration);
}

void Toast::draw_self(Canvas* canvas) {
	View::draw_self(canvas);
	if (!canvas || !canvas->data || message.empty()) return;

	Vec2 size = getSizeWithoutMargin();
	float w = size.x;
	float h = size.y;

	canvas->fontSize(14);
	canvas->fontFace("sans");
	canvas->fillColorByInt32(textColor);
	canvas->textAlign(NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
	canvas->text(padding.left + border.l.w, h / 2.0f + padding.top + border.t.w - padding.top, message.c_str());
}

static Ref<Toast> g_toast;

void showToast(const std::string& message, int durationMs) {
	if (!g_toast) {
		g_toast = new Toast();
	}
	g_toast->showMessage(message, durationMs);
}
