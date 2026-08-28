#include "EditText.h"
#include "../Core/Canvas.h"
#include "../Core/Window.h"
#include "../Core/Focus.h"
#include "../Core/Clipboard.h"
#include "../Naga/Utf8Util.h"
#include "../Naga/StrUtil.h"
#include "../Naga/MathEx.h"
#include "../Core/Theme.h"
#include "../Core/Mouse.h"
#include <string>


Range mkRange(int start, int end) {
	Range r;
	r.start = start;
	r.end = end;
	return r;
}







//std::function<string()> get_value = []() {return ""; };
//std::function<void(string)> set_value = [](string v) {};
 std::string Selection::get_range_value() {
	//std::string tmp = this->get_value();
	//return tmp.substring(this->start, this->end);
	return Utf8Util::substr(get_value(), start, end - start);
}

 bool Selection::is_collapse() {
	 return this->end == this->start;
 }

 bool Selection::is_range() {
	 return this->end != this->start;
 }

 Range Selection::get_asc_range() {
	 if (this->end < this->start) {
		 return mkRange(this->end, this->start);
	 }
	 else {
		 return mkRange(this->start, this->end);
	 }
 }

 int Selection::clamp_pos(int pos) {
	 int l = this->get_value().length();
	 // int l = s.length()
	 pos = clampInt(pos, 0, l);
	 // int pos = clampInt(pos, 0, this->get_value().size()); 
	 return pos;
	 // return 0
 }

 void Selection::set_collapse_pos(int pos) {
	 pos = this->clamp_pos(pos);
	 this->start = pos;
	 this->end = pos;
 }

 void Selection::set_start(int pos) {
	 pos = this->clamp_pos(pos);
	 this->start = pos;
 }

 void Selection::set_end(int pos) {
	 pos = this->clamp_pos(pos);
	 this->end = pos;
 }

 void Selection::move_delta(int delta, bool shift) {
	 if (shift) {
		 this->set_end(this->end + delta);
		 return;
	 }
	 if (this->is_collapse()) {
		 this->set_collapse_pos(this->end + delta);
	 }
	 else {
		 Range r = this->get_asc_range();
		 this->set_collapse_pos(delta < 0 ? r.start : r.end);
	 }

 }

 std::string Selection::backspace() {
	 if (this->is_range()) {
		 return this->del_range();
	 }
	 else {
		 //删除前一个字符
		 std::string val = this->get_value();
		 if (this->start == 0) {
			 return val;
		 }
		 //std::string nval = val.substring(0, this->start - 1).addString(val.substring(this->start, val.length()));
		 auto nval = Utf8Util::substr(val, 0, this->start - 1) + Utf8Util::substr(val, this->start, val.length());
		 this->set_collapse_pos(this->start - 1);
		 return nval;
	 }
 }

 std::string Selection::del_range() {
	 Range r = this->get_asc_range();
	 std::string val = this->get_value();
	 this->set_collapse_pos(r.start);
	 //std::string ret = val.substring(0, r.start).addString(val.substringToEnd(r.end));
	 //return ret;
	 return Utf8Util::substr(val, 0, r.start) + Utf8Util::substr(val, r.end);
	 // return null
 }

 std::string Selection::delete_act() {
	 if (this->is_range()) {
		 return this->del_range();
	 }
	 else {
		 std::string val = this->get_value();
		 //std::string ret = val.substring(0, this->start).addString(val.substringToEnd(this->start + 1));
		 //return ret;
		 return Utf8Util::substr(val, 0, start) + Utf8Util::substr(val, start + 1);
	 }
	 return "";
 }

 std::string Selection::insert(const char* text) {
	 std::string val = this->get_value();
	 Range r = this->get_asc_range();
	 std::string start = Utf8Util::substr(val, 0, r.start); //val.substring(0, r.start);
	 std::string end = Utf8Util::substr(val, r.end); //val.substringToEnd(r.end);
	 std::string nval = start + text + end;


	 this->set_value(nval);
	 this->set_collapse_pos(this->start + Utf8Util_length(text));
	 return nval;
	 // return null
 }

 EditText::EditText() {
	 CtorGuard g(this);

	 this->backgroundColor = themeIns()->edittext_bg;

	 this->selection.get_value = [=]() {return this->value;};
	 this->selection.set_value = [=](std::string v) {
		 this->value = v;	
	};


	 // this->get_value = ^std::string () {
	 // 	return str("")
	 // }
	 // this->set_value = ^void(const char *string) {
	 // }
	 this->caret->view = this;
	 this->width = 50;
	 this->height = 26;

	 this->needClip = true;
 }

 void EditText::layoutContent(Frame* ctx) {
 }

 void EditText::setValue_notInFocus(std::string v) {
	 if (!insFocus()->isFocus(this)) {
		 this->setValue(v);
	 }
 }

 void EditText::setValue(std::string v) {
	 if (this->value != (v)) {
		 this->value = v;
		 this->invalidLayout();
	 }
 }

 void EditText::setFont_size(int v) {
	 if (v != this->font_size) {
		 this->font_size = v;
		 this->invalidLayout();
	 }
 }

 int EditText::getFont_size() { return this->font_size; }

 void EditText::setFont_face(std::string v) {
	 if (this->font_face != (v)) {
		 this->font_face = v;
		 this->invalidLayout();
	 }
 }

 void EditText::setColor(int v) {
	 if (v != this->color) {
		 this->color = v;
		 this->invalidDraw();
	 }
 }

 void EditText::setCaret_color(int v) {
	 if (v != this->caret_color) {
		 this->caret_color = v;
		 this->invalidDraw();
	 }
 }

 void EditText::setFont_weight(int v) {
	 if (v != this->font_weight) {
		 this->font_weight = v;
		 this->invalidLayout();
	 }
 }

 void EditText::setPlaceholder(std::string v) {
	 if (v != this->placeholder) {
		 this->placeholder = v;
		 this->invalidLayout();
	 }
 }

 void EditText::setPlaceholder_color(int v) {
	 if (v != this->placeholder_color) {
		 this->placeholder_color = v;
		 this->invalidDraw();
	 }
 }

 void EditText::notify_changed(bool by_user_event) {
	 if (this->onValueChanged) {
		 this->onValueChanged->invoke(this);
	 }
 }

 void EditText::set_value(std::string nvalue, bool by_user_event) {
	 if (nvalue == "") {
		 if (this->value == ("")) {
			 return;
		 }
		 else {
			 nvalue = ("");
		 }
		 // return;
	 }
	 // if (this->value && this->value.equals(nvalue.str)){
	 // 	return;
	 // }
	 printf("EditText.set_value:%s=>%s\n", this->value.c_str(), nvalue.c_str());
	 this->value = nvalue;
	 this->notify_changed(by_user_event);
 }

 Timer* EditText::gocDragTimer() {
	 if (this->drag_timer == nullptr) {
		 auto self = Ref(this);
		 this->drag_timer = mkTimerInterval_noStart(CLOSURE([=]() {
			 printf("drag_timer.....定时器\n");
			 self->_update_drag();
			 }), 10);
	 }
	 return this->drag_timer;
 }

 void EditText::react() {

 }

 void EditText::draw_self(Canvas* canvas) {
	 this->_canvas = canvas;

	 int x = 0;//this->layoutCtx.x
	 int y = 0;//this->layoutCtx.y
	 int w = this->frame.width;
	 int h = this->frame.height;
	 int cornerRadius = 5;
	 auto contentRect = this->getContentRect();

	 // NVGpaint bg = nvgLinearGradient(vg, x,y,x,y+h, nvgRGBA(0,0,0,128), nvgRGBA(0,0,0,200));
	 // nvgBeginPath(vg);
	 // nvgRoundedRect(vg, x+1,y+1, w-2,h-2, cornerRadius-1);
	 // //if (!isBlack(col)) {
	 // 	//nvgFillColor(vg, col);
	 // 	//nvgFill(vg);
	 // //}
	 // nvgFillPaint(vg, bg);
	 // nvgFill(vg);

	 // Edit
	 // bg = nvgBoxGradient(vg, x+1,y+1+1.5f, w-2,h-2, 3,4, nvgRGBA(255,255,255,32), nvgRGBA(32,32,32,32));
	 canvas->beginPath();
	 canvas->roundRect(x + 1, y + 1, w - 2, h - 2, 4 - 1);
	 canvas->boxGradient(true, x + 1, y + 1 + 1.5f, w - 2, h - 2, 3, 4, mkIntByRgba(255, 255, 255, 32), mkIntByRgba(0, 0, 0, 32));
	 canvas->fill();

	 // canvas->beginPath();
	 // canvas->roundRect( x+0.5f,y+0.5f, w-1,h-1, 4-0.5f);
	 // canvas->strokeColorByInt32( mkIntByRgba(255,255,255, 48));
	 // canvas->stroke();

	 canvas->fontSize(this->font_size);
	 // nvgFontFace(vg, "sans");

	 // float x = this->margin.left
	 // float y = this->margin.top
	 // float w = this->layoutCtx.width - this->margin.hor()
	 // float h = this->layoutCtx.height - this->margin.ver()
	 float hor = this->margin.hor();
	 float ver = this->margin.ver();
	 float startOffset = 0.0; //h * 0.3
	 float scissorW = w - startOffset * 2;// h * 0.3 

	 Range range = this->selection.get_asc_range();
	 float caretY = 4;


	 //绘制光标
	 if (this->caret->isBlinking() && this->caret->show) {
		 // float draw_offset = 0 //绘制偏移，用来处理溢出
		 float caretX = startOffset
			 - 2  // x of position是绘制开始的位置，所以要向左偏一点到中间
			 + this->draw_offset
			 + this->get_x_of_position(range.start);
		 canvas->fillColorByInt32((this->caret_color));//nvgRGBA(255, 255, 255, 128));
		 canvas->beginPath();
		 canvas->rect(maxFloat(0, caretX + 1), caretY, 2, h - caretY * 2); // 2 )
		 canvas->fill();
	 }

	 //裁切
	 canvas->intersectScissor(startOffset, 0.0f, scissorW, h);

	 //绘制选区
	 if (this->selection.is_range()) {
		 float x = this->get_x_of_position(range.start) + this->draw_offset;
		 float end_x = this->get_x_of_position(range.end) + this->draw_offset;
		 // Rect rect = SkRect::MakeXYWH(x, 0, end_x - x, content_size.h);
		 //绘制选中区域
		 // SkPaint p;
		 // p.setColor(0xc97ed3ff);
		 // canvas->drawRect(rect, p);
		 canvas->fillColorByInt32(0xc97ed3ff); //nvgRGBA(255, 255, 255, 128));
		 // nvgFillColor(vg, mkNVGColorByInt(0xffdddddd)) //nvgRGBA(255, 255, 255, 128));
		 canvas->beginPath();
		 canvas->rect(x, caretY, end_x - x, h - caretY * 2);
		 canvas->fill();
	 }
	 //绘制ime合成
	 this->draw_editing(canvas, h);


	 auto metrics = canvas->textMetrics();
	 float lineYStart = (contentRect.h - metrics.lineh) / 2.0f;
	 //占位内容
	 if (this->value.empty() && !this->placeholder.empty()) {
		 // nvgFillColor(vg, nvgRGBA(255,255,255,64));
		 canvas->fillColorByInt32((this->color));
		 canvas->textAlign(NVG_ALIGN_LEFT | NVG_ALIGN_BASELINE);
		 canvas->text(x + h * 0.3f, 
			 y + lineYStart  + metrics.ascender, //h * 0.5f, 
			 this->placeholder.c_str());
	 }
	 //绘制文本
	 if (!this->value.empty()) {
		 // nvgFillColor(vg, nvgRGBA(255,255,255,255));
		 //canvas->beginPath();
		 //canvas->rect(0, lineYStart, 100, metrics.lineh);
		 //canvas->fillColorByInt32(0x33ff0000);
		 //canvas->fill();

		 canvas->fillColorByInt32(this->color);
		 canvas->textAlign(NVG_ALIGN_LEFT | NVG_ALIGN_BASELINE);
		 float textX = x + startOffset + this->draw_offset;

		 canvas->text(textX,
			 y + lineYStart  + metrics.ascender, //h * 0.5f, 
			 this->value.c_str());
	 }

 }

 void EditText::onEvent(Event* evt) {
	 if (auto me = dynamic_cast<MouseEvent*>(evt)) {
		 //MouseEvent* me = (MouseEvent*)evt;
		 this->on_mouse_event(me);
	 }
	 else if (auto ke = dynamic_cast<KeyEvent*>(evt)) {
		 this->on_key_event(ke);
	 }
	 else if (auto fe = dynamic_cast<FocusEvent*>(evt)) {
		 this->on_focus_event(fe);
	 }
	 else if (auto e2 = dynamic_cast<TextEditingEvent*>(evt)) {
		 this->on_editing_event(e2);
	 }
	 else if (auto e2 = dynamic_cast<TextInputEvent*>(evt)) {
		 this->on_input_event(e2);
	 }
	 else if (auto e2 = dynamic_cast<WindowFocusEvent*>(evt)) {
		 this->on_window_focus_event(e2);
	 }
 }

 void EditText::on_window_focus_event(WindowFocusEvent* e) {
	 if (e->isFocus) {
	 }
	 else if (e->isBlur) {
		 this->blur();
	 }
 }

 //键盘事件，注意区分字符事件
 void EditText::on_key_event(KeyEvent* e) {
	 if (e->isKeyDown) {
		 auto key = Str::lower(e->key);
		 if (key == ("left") || key == "arrowleft") {
			 this->selection.move_delta(-1, e->shift);
			 this->caret->restart();
			 this->update_draw_offset_by_keydown_move_with_default();
			 //Window::markDirtyByView(this);
			 this->invalidDraw();
			 e->stopPropagation();
		 }
		 else if (key == ("right")) {
			 this->selection.move_delta(1, e->shift);
			 this->caret->restart();
			 this->update_draw_offset_by_keydown_move_with_default();
			 //Window::markDirtyByView(this);
			 this->invalidDraw();
		 }
		 else if (key == ("backspace")) {
			 this->set_value(this->selection.backspace(), true);
			 this->caret->restart();
			 this->update_draw_offset_by_keydown_move(0.5, true);
			 //Window::markDirtyByView(this);
			 this->invalidDraw();
		 }
		 else if (key == ("delete")) {

			 this->set_value(this->selection.delete_act(), true);
			 this->caret->restart();
			 this->update_draw_offset_by_keydown_move(0.5, true);
			 this->invalidDraw();
		 }
		 else if (key == ("return")) {
			 // insFocus()->blurNode(this)
			 // this->invalidDraw();
			 this->blur();
		 }
		 else if (e->ctrl && Utf8Util::equalIgnoreCase(e->key, "c")) { //copy
			 if (this->selection.is_range()) {
				 std::string v = this->selection.get_range_value();
				 Clipboard_setText(v.c_str());
				 printf("\n已复制:%s\n\n", v.c_str());
			 }
			 // if (this->selection.is_range()) {
			 // 	//SDL_SetClipboardText(selection.get_range_value().c_str());
			 // 	// Clipboard::ins()->set_text(selection.get_range_value().c_str());
			 // 	printf("\ncopy\n\n")
			 // }
		 }
		 else if (e->ctrl && Utf8Util::equalIgnoreCase(e->key, "v")) { //paste
			 std::string v = Clipboard_getText();
			 std::string nv = this->selection.insert(v.c_str());
			 printf("paste nv:%s\n", nv.c_str());
			 this->set_value(nv, true);
			 this->caret->restart();
			 this->update_draw_offset_by_keydown_move_with_default();
			 this->invalidDraw();
		 }
		 else if (e->ctrl && Utf8Util::equalIgnoreCase(e->key, "x")) { //cut
			 if (this->selection.is_range()) {
				 std::string nv = this->selection.delete_act();
				 printf("cut 选区。 nv:%s\n", nv.c_str());
				 this->set_value(nv, true);
				 this->caret->restart();
				 this->invalidDraw();
			 }
		 }
		 else if (e->ctrl && Utf8Util::equalIgnoreCase(e->key, "a")) {//全选
			 this->selection.set_start(0);
			 this->selection.set_end(this->value.size());
			 this->caret->restart();
			 this->invalidDraw();
			 e->stopPropagation();
		 }
	 }
 }

 //焦点事件
 void EditText::on_focus_event(FocusEvent* evt) {
	 printf("EditText 焦点事件 isFocus:%d, isBlur:%d\n", evt->isFocus, evt->isBlur);
	 if (evt->isFocus) {
		 this->caret->restart();
		 this->_update_text_input_rect();
	 }
	 else if (evt->isBlur) {
		 this->selection.set_collapse_pos(this->selection.start);
		 this->caret->stop();
	 }
	 this->invalidDraw();
 }

 // ime合成事件
 void EditText::on_editing_event(TextEditingEvent* evt) {
	 printf("EditText 收到IME合成事件:%s, start:%d\n", evt->text.c_str(), evt->start);
	 this->set_text_editing(evt);
 }

 //输入字符（含中文）, 所有的字符都从这里插入的,不管是英文还是中文
 void EditText::on_input_event(TextInputEvent* e) {
	 printf("EditText 收到字符事件:%s\n", e->text.c_str());
	 if (e->text.size() == 1) {
		 char c = e->text[0];
		 //排除特殊符号
		 //0x08 = backspace, 0x0a: lf, 0x1b:escape, 0x09:tab, 0x0d:cr
		 if (c == 0x08 || c == 0x0a || c == 0x1b || c == 0x0d) {
			 return;
		 }
	 }

	 //插入字符
	 std::string new_value = this->selection.insert(e->text.c_str());
	 this->set_value(new_value, true);

	 this->update_draw_offset_by_keydown_move_with_default();
	 this->caret->restart();

	 this->invalidDraw();
 }

 void EditText::onUnmounting() {
	 this->blur();
 }

 //取消聚焦
 void EditText::blur() {
	 insFocus()->blurNode(this);
	 this->caret->stop();
	 this->invalidDraw();
 }

 //取得字符位置的像素x坐标
 float EditText::get_x_of_position(int pos) {
	 if (this->_canvas == nullptr) {
		 return 0;
	 }
	 if (pos == 0) {
		 return 0;
	 }
	 // auto f = get_font();
	 // auto tmp = Utf8Util::substr(value, 0, pos);
	 // auto w = f.measureText(tmp.c_str(), tmp.size(), SkTextEncoding::kUTF8);

	 float bounds[4];
	 bounds[0] = 0.0;
	 bounds[1] = 0.0;
	 bounds[2] = 0.0;
	 bounds[3] = 0.0;
	 int charLen = Utf8Util_numCharLen(this->value.c_str(), pos);//this->selection.start)
	 this->_canvas->fontSize(this->font_size);
	 float w = this->_canvas->textBounds(0, 0, this->value.c_str(), this->value.c_str() + charLen, bounds);

	 // Measures the specified text string. Parameter bounds should be a pointer to float[4],
	 // if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
	 // Returns the horizontal advance of the measured text (i.e. where the next character should drawn).
	 // Measured values are returned in local coordinate space.
	 // float w = 0;
	 return w;
	 // return 0
 }

 // 更新Ime合成输入矩形？
 void EditText::_update_text_input_rect() {
 }

 void EditText::update_draw_offset_by_keydown_move_with_default() {
	 this->update_draw_offset_by_keydown_move(0.5, false);
 }

 //键盘操作后，更新滚动偏移
 void EditText::update_draw_offset_by_keydown_move(float target_caret_ratio, bool force) {
	 Rect rect = this->getContentLocalRect();
	 float x_from_start = this->get_x_of_position(this->selection.end);
	 float x = x_from_start + this->draw_offset;//显示出来的x
	 //将进入隐藏区
	 if (force || x < this->font_size / 2.0 || x >= rect.w - this->font_size / 2.0) {
		 //让position居中
		 int new_draw_offset = this->clamp_draw_offset(-x_from_start + rect.w * target_caret_ratio);
		 printf("更新滚动偏移:%d -> %d\n", this->draw_offset, new_draw_offset);
		 this->draw_offset = new_draw_offset;
		 this->invalidDraw();
	 }
 }

 int EditText::clamp_draw_offset(int offset) {
	 float full_w = this->get_x_of_position(this->value.size());
	 Rect rect = this->getContentLocalRect();

	 return clampFloat(
		 offset,
		 minFloat(0.0, -full_w + rect.w),
		 0.0
	 );
 }

 //根据像素x找到字符位置，用于点击时，查找鼠标所在位置
 int EditText::get_char_position_by_client_x(int client_x) {
	 Rect absRect = this->get_abs_rect();
	 Rect lr = this->getContentLocalRect();
	 float dx = client_x - absRect.x;// + lr.x;// lr.get_content_client_pos().x;
	 float x_from_start = dx - this->draw_offset; //相对于字符串原点
	 int guess_pos = (int)(x_from_start / maxInt(1, this->font_size + 2));

	 // 找到第一个大于的位置
	 int l = this->value.size() + 1;
	 for (int i = maxInt(guess_pos, 1); i < l; i++) {
		 float width = this->get_x_of_position(i);
		 if (width >= x_from_start) {
			 float prevWidth = this->get_x_of_position(i - 1);
			 float charWidth = width - prevWidth;
			 float dx_to_end = width - x_from_start;
			 if (dx_to_end > charWidth / 2.0) {//偏左
				 return maxInt(0, i - 1);
			 }
			 else {
				 return i;
			 }
		 }
	 }

	 return this->value.size();
 }

 void EditText::on_mouse_event(MouseEvent* e) {
	 if (e->isMouseDown) {
		 this->on_mouse_down(e);
	 }
 }

 void EditText::on_mouse_down(MouseEvent* e) {
	 if (e->isBubble()) {
		 int position = this->get_char_position_by_client_x(e->clientX);
		 printf("EditText.mousedown position:%d. shift:%d\n", position, e->shift);

		 if (e->shift) {
			 this->selection.set_end(position);
		 }
		 else {
			 this->selection.set_collapse_pos(position);
		 }
		 // 取得焦点
		 Focus* f = insFocus();
		 f->focus(this);
		 //让光标显示
		 this->caret->restart();
		 //不再传播事件
		 e->stopPropagation();
		 this->invalidDraw();

		 this->gocDragTimer()->start();

		 if (e->window != nullptr && e->window->rootView != nullptr) {
			 e->window->rootView->addListenerOnce(this);
		 }
	 }
 }

 void EditText::onListenerEvent(Event* e) {
	 if (auto me = dynamic_cast<MouseEvent*>(e)) {
		 //根视图的事件
		 if (me->isCapture && me->isMouseMove && me->currentTarget == me->window->rootView) {
			 this->on_rootView_mouse_move(me);
		 }
		 //根视图的事件
		 if (me->isCapture && me->isMouseUp && me->currentTarget == me->window->rootView) {
			 this->on_rootView_mouse_up(me);
		 }
	 }
 }

 void EditText::on_rootView_mouse_up(MouseEvent* e) {
	 e->stopPropagation();
	 if (e->window != nullptr && e->window->rootView != nullptr) {
		 e->window->rootView->removeListener(this);
	 }
	 printf("\n\n\nEditText 处理rootView mouse_up事件\n\n\n");
	 this->gocDragTimer()->cancel();
 }

 void EditText::on_rootView_mouse_move(MouseEvent* e) {
	 e->stopPropagation();
	 printf("EditText 处理rootView mouse_move事件\n");

	 int position = this->get_char_position_by_client_x(e->clientX);
	 if (this->selection.end != position) {
		 this->selection.set_end(position);
		 //Window::markDirtyByView(this);
		 this->invalidDraw();
	 }
 }

 void EditText::_update_drag() {
	 if (this->ownerWindow == nullptr) {
		 return;
	 }
	 Rect abs = this->get_abs_rect();
	 Rect lr = this->getContentLocalRect();
	 Vec2 pos = Mouse_getPosOfWindow(this->ownerWindow);
	 int client_x = pos.x;
	 int client_y = pos.y;
	 int dx = client_x - abs.x + lr.x;// lr.get_content_client_pos().x;
	 int noffset = this->draw_offset;

	 if (dx < this->font_size / 2.0f) { //左偏
		 noffset = this->clamp_draw_offset(this->draw_offset + this->font_size / 2.0f);
	 }
	 else if (dx > lr.w - this->font_size / 2.0f) {//右偏
		 noffset = this->clamp_draw_offset(this->draw_offset - this->font_size / 2.0f);
	 }
	 printf("_update_drag ============= old:%d, new:%d, dx:%d clientX:%d abs.x:%f, lr.x:%f\n", this->draw_offset, noffset, dx, client_x, abs.x, lr.x);
	 if (noffset != this->draw_offset) {
		 this->draw_offset = noffset;
		 //Window::markDirtyByView(this);
	 }
	 this->invalidDraw();
 }

 void EditText::reset_text_editing() {
	 // this->text_editing = null
	 this->set_text_editing(nullptr);
	 this->invalidDraw();
 }

 void EditText::draw_editing(Canvas* canvas, int h) {
	 if (this->text_editing == nullptr) {
		 return;
	 }
	 int start = this->selection.start - this->text_editing->start;
	 int runelen = this->text_editing->start + this->text_editing->length;

	 std::string pre = Utf8Util::substr(this->value, 0, start);
	 std::string subfix = Utf8Util::substr(this->value, start + runelen);

	 int x0 = this->get_x_of_position(start) + this->draw_offset;
	 int x1 = this->get_x_of_position(start + runelen) + this->draw_offset;

	 float caretY = 8;
	 // int h = this->layoutCtx.height

	 canvas->fillColorByInt32((0xc97ed3ff)); //nvgRGBA(255, 255, 255, 128));
	 canvas->beginPath();
	 canvas->rect(x0, caretY, x1 - x0, h - caretY * 2);
	 canvas->fill();
 }

 void EditText::set_text_editing(TextEditingEvent* evt) {

	 TextEditingEvent* prev = this->text_editing;
	 int start = this->selection.start;
	 int runelen = 0;
	 if (prev != nullptr) {
		 start = this->selection.start - prev->start;
		 runelen = prev->start + prev->length;
	 }

	 // //@TEST evt
	 // for (int i = 0, l = evt.text.size(); i < l; i++){
	 // 	evt.text.str[i] = 'A'
	 // 	evt.text.str[i+1] = 0
	 // }

	 std::string pre = Utf8Util::substr(this->value, 0, start);
	 std::string subfix = Utf8Util::substr(this->value, start + runelen);
	 this->value = pre
		 + (evt->text)
		 + (subfix);
	 this->notify_changed(evt != nullptr);
	 this->selection.set_collapse_pos(start + evt->start);

	 this->text_editing = evt;
	 this->invalidDraw();
	 this->_update_text_input_rect();
 }

 // 选择全部
 void EditText::selectAll() {
	 this->selection.set_start(0);
	 this->selection.set_end(this->value.size());
	 this->caret->restart();
	 //Window::markDirtyByView(this);
	 this->invalidDraw();
 }

 Caret::Caret() {
	 CtorGuard g(this);

	 auto self = Ref(this);
	 self->blink_timer = mkTimerInterval_noStart(CLOSURE([=]() {
		 self->blink();
		 }), 600);
 }

 bool Caret::isBlinking() {
	 return this->blink_timer->alive;
 }

 // Caret();
 void Caret::setShow(bool _show) {
	 if (_show == this->show) {
		 return;
	 }
	 this->show = _show;
	 //printf("光标blink:%d\n", show);
	 if (this->view) {
		 //Window::markDirtyByView(view);
		 this->view->invalidDraw();
	 }
	 if (this->cb_notify != nullptr) {
		 this->cb_notify->invoke(this);
	 }
 }

 void Caret::blink() {
	 this->setShow(!this->show);
 }

 void Caret::start() {
	 printf("光标blink:start\n");
	 this->blink_timer->start();
 }

 void Caret::stop() {
	 printf("光标blink:stop\n");
	 this->setShow(false);
	 this->blink_timer->cancel();
 }

 void Caret::restart() {
	 this->stop();
	 this->start();

	 this->show = true;

	 if (this->cb_notify != nullptr) {
		 this->cb_notify->invoke(this);
	 }
 }
