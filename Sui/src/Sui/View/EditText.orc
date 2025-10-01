package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"

#include "../../nanovg/nanovg.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/View.orc"
import * from "../Core/Node.orc"
import * from "../Core/Timer.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Inset.orc"
import * from "../Core/Color.orc"
import * from "../Core/Event.orc"
import * from "../Core/Canvas.orc"
import * from "../Core/Frame.orc"
import * from "../Core/KeyEvent.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Focus.orc"
import * from "../Core/MouseEvent.orc"
import * from "../Core/Mouse.orc"
import * from "../Core/Clipboard.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "./ViewBuilder.orc"

// TODO: 拖选 draw editing 
struct Range {
	int start
	int end 
}

Range mkRange(int start, int end){
	Range r;
	r.start = start;
	r.end = end;
	return r;
}

class Selection {
	int start = 0//单位rune
	int end = 0//rune
	^String@ () get_value = null
	^void (const char *string) set_value = null
	//std::function<string()> get_value = []() {return ""; };
	//std::function<void(string)> set_value = [](string v) {};
	String@ get_range_value(){
		String@ tmp = self.get_value()
		return tmp.substring(self.start, self.end)
		// return Utf8Util::substr(get_value(), start, end - start);
	}
	bool is_collapse(){
		return self.end == self.start;
	}
	bool is_range(){
		return self.end != self.start;
	}
	Range get_asc_range(){
		if (self.end < self.start) {
			return mkRange( self.end, self.start );
		}
		else {
			return mkRange( self.start, self.end );
		}
	}
	int clamp_pos(int pos){
		int l = self.get_value().length()
		// int l = s.length()
		pos = clampInt(pos, 0, l)
		// int pos = clampInt(pos, 0, self.get_value().size()); 
		return pos;
		// return 0
	}
	void set_collapse_pos(int pos){
		pos = self.clamp_pos(pos);
		self.start = pos;
		self.end = pos;
	}
	void set_start(int pos){
		pos = self.clamp_pos(pos);
		self.start = pos;
	}
	void set_end(int pos){
		pos = self.clamp_pos(pos);
		self.end = pos;
	}
	void move_delta(int delta, bool shift){
		if (shift) {
			self.set_end(self.end + delta);
			return;
		}
		if (self.is_collapse()) {
			self.set_collapse_pos(self.end + delta);
		}
		else {
			Range r = self.get_asc_range();
			self.set_collapse_pos(delta < 0 ? r.start : r.end);
		}

	}

	String@ backspace(){
		if (self.is_range()) {
			return self.del_range();
		}
		else {
			//删除前一个字符
			String@ val = self.get_value();
			if (self.start == 0) {
				return val;
			}
			String@ nval = val.substring(0, self.start - 1) .addString( val.substring(self.start, val.length()));
			self.set_collapse_pos(self.start - 1);
			return nval;
		}
	}
	String@ del_range(){
		Range r = self.get_asc_range();
		String@ val = self.get_value();
		self.set_collapse_pos(r.start);
		String@ ret = val.substring(0, r.start).addString(val.substringToEnd(r.end));
		return ret
		// return Utf8Util::substr(val, 0, r.start) + Utf8Util::substr(val, r.end);
		// return null
	}
	String@ delete_act(){
		if (self.is_range()) {
			return self.del_range();
		}
		else {
			String@ val = self.get_value();
			String@ ret = val.substring(0, self.start).addString(val.substringToEnd(self.start + 1));
			return ret
			// return Utf8Util::substr(val, 0, start) + Utf8Util::substr(val, start + 1);
		}
		return null
	}
	String@ insert(const char* text){
		String@ val = self.get_value();
		Range r = self.get_asc_range();
		String@ start = val.substring(0, r.start)
		String@ end = val.substringToEnd(r.end)
		String@ nval = start
			.add(text)
			.addString(
				end
			);


		self.set_value(nval.str);
		self.set_collapse_pos(self.start + utf8RuneLength(text));
		return nval;
		// return null
	}
}

class Caret{
	bool show = true;
	Timer@ blink_timer = null
	ViewBase@ view = null
	^void (Caret *ins) cb_notify = null

	void ctor(){
		self.blink_timer = mkTimerInterval_noStart(^void() {
			self.blink();
		}, 600);
	}
	bool isBlinking(){
		return self.blink_timer.alive

	}

	// Ref<Timer> blink_timer{ nullptr, this };

	// Ref<ViewBase> view{ 0, this };
	// Ref<Closure<void(Caret*)>> cb_notify = { 0, this };

	// Caret();
	void setShow(bool _show){
		if (_show == self.show) {
			return;
		}
		self.show = _show;
		//printf("光标blink:%d\n", show);
		if (self.view) {
			//Window::markDirtyByView(view);
			self.view->invalidDraw();
		}
		if (self.cb_notify != null) {
			self.cb_notify(self)
		}
	}
	void blink(){
		self.setShow(!self.show);
	}
	void start(){
		printf("光标blink:start\n");
		self.blink_timer.start();
	}
	void stop(){
		printf("光标blink:stop\n");
		self.setShow(false);
		self.blink_timer.cancel();
	}
	void restart(){
		self.stop();
		self.start();

		self.show = true;

		if (self.cb_notify != null) {
			self.cb_notify(self);
		}
	}
}
/// 布局上下文
class EditText extends View {
	String@ value = str("")
	int font_size = 17;
	String@ font_face = str("");
	int color = 0xff000000;
	int caret_color = 0xff000000;
	int font_weight = 400;
	String@ placeholder = str("please input");
	int placeholder_color = 0xff999999;
	^void(String*value) onchanged = null

	int draw_offset = 0; //绘制偏移:[-n, 0]. 单位：像素
	int _caret_x = 0;

	Selection@ selection = new Selection()
	Timer@ drag_timer = null
	Caret@ caret = new Caret()

	//输入法合成状态
	TextEditingEvent@ text_editing = null


	void layoutContent(Frame *ctx){
	}
    void setValue_notInFocus(String* v){ 
		if !insFocus().isFocus(self){
			self.setValue(v)
		}
	}
    void setValue(String* v){ 
        if (self.value.notEquals(v.str)){
            self->value = v; 
			self.invalidLayout();
        }
    }
    String* getValue(){ return self.value; }

    void setFont_size(int v){ 
        if (v != self->font_size){
            self->font_size = v; 
			self.invalidLayout();
        }
    }
    int getFont_size(){ return self.font_size; }

    void setFont_face(String* v){ 
        if (self->font_face.notEquals(v.str)){
            self->font_face = v; 
			self.invalidLayout();
        }
    }
    String* getFont_face(){ return self.font_face; }

    void setColor(int v){ 
        if (v != self->color){
            self->color = v; 
			self.invalidDraw();
        }
    }
    int getColor(){ return self.color; }

    void setCaret_color(int v){ 
        if (v != self->caret_color){
            self->caret_color = v; 
			self.invalidDraw();
        }
    }
    int getCaret_color(){ return self.caret_color; }

    void setFont_weight(int v){ 
        if (v != self->font_weight){
            self->font_weight = v; 
			self.invalidLayout();
        }
    }
    int getFont_weight(){ return self.font_weight; }

    void setPlaceholder(String* v){ 
        if (v != self->placeholder){
            self->placeholder = v; 
			self.invalidLayout();
        }
    }
    String* getPlaceholder(){ return self.placeholder; }

    void setPlaceholder_color(int v){ 
        if (v != self->placeholder_color){
            self->placeholder_color = v; 
			self.invalidDraw();
        }
    }
    int getPlaceholder_color(){ return self.placeholder_color; }


	^void (EditText* et) onValueChanged;
	void notify_changed(bool by_user_event){
		if (self.onValueChanged){
			self.onValueChanged(self)
		}
	}
	void set_value(String@ nvalue, bool by_user_event){
		if (nvalue == null){
			if (self.value.equals("")){
				return;
			}
			else {
				nvalue = str("")
			}
			// return;
		}
		// if (self.value && self.value.equals(nvalue.str)){
		// 	return;
		// }
		printf("EditText.set_value:%s=>%s\n", self.value.str, nvalue.str);
		self.value = nvalue
		self.notify_changed(by_user_event)
	}

	Timer* gocDragTimer(){
		if (self.drag_timer == null){
			self.drag_timer = mkTimerInterval_noStart(^void (){
				printf("drag_timer.....定时器\n")
				self._update_drag()
			}, 10)
		}
		return self.drag_timer
	}

	void ctor(){
		self.selection.get_value = ^String@ () {
			return self.value;
		}
		self.selection.set_value = ^void (const char *text) {
			self.value = str(text)
		}


		// self.get_value = ^String@ () {
		// 	return str("")
		// }
		// self.set_value = ^void(const char *string) {
		// }
		self.caret.view = self
		self.width = 50
		self.height = 26

		self.needClip = true
	}
	void react(){

	}
    void draw_self(Canvas *canvas){
		self._canvas = canvas

		int x = 0//self.layoutCtx.x
		int y = 0//self.layoutCtx.y
		int w = self.frame.width
		int h = self.frame.height
		int cornerRadius = 5

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
		canvas.beginPath();
		canvas.roundRect( x+1,y+1, w-2,h-2, 4-1);
		canvas.boxGradient(true, x+1,y+1+1.5f, w-2,h-2, 3,4, mkIntByRgba(53,64,64,32), mkIntByRgba(0,0,0,32));
		canvas.fill();

		canvas.beginPath();
		canvas.roundRect( x+0.5f,y+0.5f, w-1,h-1, 4-0.5f);
		canvas.strokeColorByInt32( mkIntByRgba(0,0,0,48));
		canvas.stroke();

		canvas.fontSize( self.font_size);
		// nvgFontFace(vg, "sans");

        // float x = self.margin.left
        // float y = self.margin.top
        // float w = self.layoutCtx.width - self.margin.hor()
        // float h = self.layoutCtx.height - self.margin.ver()
		float hor = self.margin.hor()
		float ver = self.margin.ver()
		float startOffset = 0.0 //h * 0.3
		float scissorW = w - startOffset * 2// h * 0.3 

		Range range = self.selection.get_asc_range()
		float caretY = 4


		//绘制光标
		if (self.caret.isBlinking() && self.caret.show){
			// float draw_offset = 0 //绘制偏移，用来处理溢出
			float caretX = startOffset 
				- 2  // x of position是绘制开始的位置，所以要向左偏一点到中间
				+ self.draw_offset
				+ self.get_x_of_position(range.start) 
			canvas.fillColorByInt32( (self.caret_color))//nvgRGBA(255, 255, 255, 128));
			canvas.beginPath()
			canvas.rect( minFloat(0, caretX + 1), caretY, 2, h - caretY * 2) // 2 )
			canvas.fill()
		}

		//裁切
        canvas.intersectScissor(startOffset, 0.0f, scissorW, h );

		//绘制选区
		if (self.selection.is_range()){
			float x = self.get_x_of_position(range.start) + self.draw_offset;
			float end_x = self.get_x_of_position(range.end) + self.draw_offset;
			// Rect rect = SkRect::MakeXYWH(x, 0, end_x - x, content_size.h);
			//绘制选中区域
			// SkPaint p;
			// p.setColor(0xc97ed3ff);
			// canvas->drawRect(rect, p);
			canvas.fillColorByInt32(0xc97ed3ff) //nvgRGBA(255, 255, 255, 128));
			// nvgFillColor(vg, mkNVGColorByInt(0xffdddddd)) //nvgRGBA(255, 255, 255, 128));
			canvas.beginPath()
			canvas.rect( x, caretY, end_x - x, h - caretY * 2)
			canvas.fill()
		}
		//绘制ime合成
		self.draw_editing(canvas, h)


		//占位内容
		if (self.value.empty() && !self.placeholder.empty()){
			// nvgFillColor(vg, nvgRGBA(255,255,255,64));
			canvas.fillColorByInt32( (self.color));
			canvas.textAlign( NVG_ALIGN_LEFT|NVG_ALIGN_MIDDLE);
			canvas.text( x+h*0.3f,y+h*0.5f, self.placeholder.str);
		}
		//绘制文本
		if (!self.value.empty()){	
			// nvgFillColor(vg, nvgRGBA(255,255,255,255));
			canvas.fillColorByInt32( self.color);
			canvas.textAlign( NVG_ALIGN_LEFT|NVG_ALIGN_MIDDLE);
			float textX = x+startOffset + self.draw_offset
			canvas.text( textX, y+h*0.5f, self.value.str);
		}

    }


	void onEvent(Event *evt){
		if (evt instanceof MouseEvent){
			MouseEvent *me = (MouseEvent*)evt;
			self.on_mouse_event(me);
		}
		else if (evt instanceof KeyEvent){
			KeyEvent *ke = (KeyEvent*)evt;
			self.on_key_event(ke);
		}
		else if (evt instanceof FocusEvent){
			FocusEvent *fe = (FocusEvent*)evt;
			self.on_focus_event(fe)
		}
		else if (evt instanceof TextEditingEvent){
			TextEditingEvent *e2 = (TextEditingEvent*)evt;
			self.on_editing_event(e2)
		}
		else if (evt instanceof TextInputEvent){
			TextInputEvent *e2 = (TextInputEvent*)evt;
			self.on_input_event(e2)
		}
		else if (evt instanceof WindowFocusEvent){
			WindowFocusEvent *e2 = (WindowFocusEvent*)evt;
			self.on_window_focus_event(e2)
		}
	}
	void on_window_focus_event(WindowFocusEvent *e){
		if (e.isFocus){
		}
		else if (e.isBlur){
			self.blur()
		}
	}
	//键盘事件，注意区分字符事件
	void on_key_event(KeyEvent *e){
		if (e.isKeyDown){
			if (e.key.equals("left")){
				self.selection.move_delta(-1, e->shift);
				self.caret->restart();
				self.update_draw_offset_by_keydown_move_with_default();
				//Window::markDirtyByView(this);
				self.invalidDraw();
				e->stopPropagation();
			}
			else if (e.key.equals("right")){
				self.selection.move_delta(1, e->shift);
				self.caret->restart();
				self.update_draw_offset_by_keydown_move_with_default();
				//Window::markDirtyByView(this);
				self.invalidDraw();
			}
			else if (e.key.equals("backspace")){
				self.set_value ( self.selection.backspace(), true);
				self.caret->restart();
				self.update_draw_offset_by_keydown_move(0.5, true);
				//Window::markDirtyByView(this);
				self.invalidDraw();
			}
			else if (e.key.equals("delete")){

				self.set_value ( self.selection.delete_act(), true);
				self.caret->restart();
				self.update_draw_offset_by_keydown_move(0.5, true);
				self.invalidDraw();
			}
			else if (e.key.equals("return")){
				// insFocus().blurNode(self)
				// self.invalidDraw();
				self.blur()
			}
			else if (e.ctrl && e.key.equalsIgnoreCase("c")){ //copy
				if (self.selection.is_range()){
					String@ v = self.selection.get_range_value()
					clipboard_setText(v.str)
					printf("\n已复制:%s\n\n", v.str)
				}
				// if (self.selection.is_range()) {
				// 	//SDL_SetClipboardText(selection.get_range_value().c_str());
				// 	// Clipboard::ins()->set_text(selection.get_range_value().c_str());
				// 	printf("\ncopy\n\n")
				// }
			}
			else if (e.ctrl && e.key.equalsIgnoreCase("v")){ //paste
				String@ v = clipboard_getText()
				String@ nv = self.selection.insert(v.str)
				printf("paste nv:%s\n", nv.str)
				self.set_value(nv, true)
				self.caret->restart()
				self.update_draw_offset_by_keydown_move_with_default()
				self.invalidDraw()
			}
			else if (e.ctrl && e.key.equalsIgnoreCase("x")){ //cut
				if (self.selection.is_range()){
					String@ nv = self.selection.delete_act()
					printf("cut 选区。 nv:%s\n", nv.str)
					self.set_value(nv, true)
					self.caret.restart()
					self.invalidDraw()
				}
			}
			else if (e.ctrl && e.key.equalsIgnoreCase("a")){//全选
				self.selection.set_start(0)
				self.selection.set_end(self.value.size())
				self.caret.restart()
				self.invalidDraw()
				e.stopPropagation()
			}
		}
	}
	//焦点事件
	void on_focus_event(FocusEvent *evt){
		printf("EditText 焦点事件 isFocus:%d, isBlur:%d\n", evt.isFocus, evt.isBlur);
		if (evt.isFocus){
			self.caret.restart()
			self._update_text_input_rect()
		}
		else if (evt.isBlur){
			self.selection.set_collapse_pos(self.selection.start)
			self.caret.stop()
		}
		self.invalidDraw()
	}
	// ime合成事件
	void on_editing_event(TextEditingEvent *evt){
		printf("EditText 收到IME合成事件:%s, start:%d\n", evt.text.str, evt.start);
		self.set_text_editing(evt)
	}
	//输入字符（含中文）, 所有的字符都从这里插入的,不管是英文还是中文
	void on_input_event(TextInputEvent *e){
		printf("EditText 收到字符事件:%s\n", e.text.str);
		if (e.text.size() == 1){
			char c = e->text.str[0];
			//排除特殊符号
			//0x08 = backspace, 0x0a: lf, 0x1b:escape, 0x09:tab, 0x0d:cr
			if (c == 0x08 || c == 0x0a || c == 0x1b || c == 0x0d) {
				return;
			}
		}

		//插入字符
		String@ new_value = self.selection.insert(e.text.str);
		self.set_value(new_value, true)

		self.update_draw_offset_by_keydown_move_with_default()
		self.caret.restart()

		self.invalidDraw()
	}
	void onUnmounting(){
		self.blur()
	}
	//取消聚焦
	void blur(){
		insFocus().blurNode(self)
		self.caret.stop()
		self.invalidDraw()
	}
	Canvas* _canvas = null
	//取得字符位置的像素x坐标
	float get_x_of_position(int pos){
		if (self._canvas == null){
			return 0
		}
		if (pos == 0) {
			return 0;
		}
		// auto f = get_font();
		// auto tmp = Utf8Util::substr(value, 0, pos);
		// auto w = f.measureText(tmp.c_str(), tmp.size(), SkTextEncoding::kUTF8);

		float bounds[4]
		bounds[0] = 0.0
		bounds[1] = 0.0
		bounds[2] = 0.0
		bounds[3] = 0.0
		int charLen = utf8NumberCharLen(self.value.str, pos)//self.selection.start)
		self._canvas.fontSize(self.font_size);
		float w = self._canvas.textBounds(0, 0, self.value.str, self.value.str + charLen, bounds)

// Measures the specified text string. Parameter bounds should be a pointer to float[4],
// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
// Returns the horizontal advance of the measured text (i.e. where the next character should drawn).
// Measured values are returned in local coordinate space.
		// float w = 0;
		return w;
		// return 0
	}

	// 更新Ime合成输入矩形？
	void _update_text_input_rect(){
	}
	void update_draw_offset_by_keydown_move_with_default(){
		self.update_draw_offset_by_keydown_move(0.5, false)
	}
	//键盘操作后，更新滚动偏移
	void update_draw_offset_by_keydown_move(float target_caret_ratio, bool force){
		Rect rect = self.getContentLocalRect();
		float x_from_start = self.get_x_of_position(self.selection.end);
		float x = x_from_start + self.draw_offset;//显示出来的x
		//将进入隐藏区
		if (force || x < self.font_size / 2.0 || x >= rect.w - self.font_size / 2.0){
			//让position居中
			int new_draw_offset = self.clamp_draw_offset(-x_from_start + rect.w * target_caret_ratio);
			printf("更新滚动偏移:%d -> %d\n", self.draw_offset, new_draw_offset);
			self.draw_offset = new_draw_offset
			self.invalidDraw()
		}
	}

	int clamp_draw_offset(int offset){
		float full_w = self.get_x_of_position(self.value.size())
		Rect rect = self.getContentLocalRect();

		return clampFloat(
			offset,
			minFloat(0.0, -full_w + rect.w), 
			0.0
		)
	}
	//根据像素x找到字符位置，用于点击时，查找鼠标所在位置
	int get_char_position_by_client_x(int client_x){
		Rect absRect = self.get_abs_rect()
		Rect lr = self.getContentLocalRect()
		float dx = client_x - absRect.x// + lr.x;// lr.get_content_client_pos().x;
		float x_from_start = dx - self.draw_offset; //相对于字符串原点
		int guess_pos = (int)(x_from_start / maxInt(1, self.font_size + 2));

		// 找到第一个大于的位置
		int l = self.value.size() + 1
		for (int i = maxInt(guess_pos, 1); i < l; i++){
			float width = self.get_x_of_position(i)
			if (width >= x_from_start){
				float prevWidth = self.get_x_of_position(i - 1)
				float charWidth = width - prevWidth
				float dx_to_end = width - x_from_start
				if (dx_to_end > charWidth / 2.0){//偏左
					return maxInt(0, i - 1)
				}
				else {
					return i
				}
			}
		}

		return self.value.size()
	}
	void on_mouse_event(MouseEvent *e){
		if (e.isMouseDown){
			self.on_mouse_down(e)
		}
	}
	void on_mouse_down(MouseEvent *e){
		int position = self.get_char_position_by_client_x(e.clientX);
		printf("EditText.mousedown position:%d. shift:%d\n", position, e.shift);

		if (e.shift) {
			self.selection.set_end(position);
		}
		else {
			self.selection.set_collapse_pos(position);
		}
		// 取得焦点
		Focus* f = insFocus()
		f.focus(self)
		//让光标显示
		self.caret.restart()
		//不再传播事件
		e.stopPropagation()
		self.invalidDraw()

		self.gocDragTimer().start()

		if (e.window != null && e.window.rootView != null){
			e.window.rootView.addListenerOnce(self)
		}
	}

	void onListenerEvent(Event *e){
		if (e instanceof MouseEvent){
			MouseEvent *me = (MouseEvent*)e;
			//根视图的事件
			if (me.isCapture && me.isMouseMove && me.currentTarget == me.window.rootView){
				self.on_rootView_mouse_move(me)
			}
			//根视图的事件
			if (me.isCapture && me.isMouseUp && me.currentTarget == me.window.rootView){
				self.on_rootView_mouse_up(me)
			}
		}
	}



	void on_rootView_mouse_up(MouseEvent *e){
		e.stopPropagation()
		if (e.window != null && e.window.rootView != null){
			e.window.rootView.removeListener(self)
		}
		printf("\n\n\nEditText 处理rootView mouse_up事件\n\n\n");
		self.gocDragTimer().cancel()
	}
	void on_rootView_mouse_move(MouseEvent *e){
		e.stopPropagation()
		printf("EditText 处理rootView mouse_move事件\n");

		int position = self.get_char_position_by_client_x(e->clientX);
		if (self.selection.end != position) {
			self.selection.set_end(position);
			//Window::markDirtyByView(this);
			self.invalidDraw();
		}
	}

	void _update_drag(){
		if (self.ownerWindow == null){
			return
		}
		Rect abs = self.get_abs_rect()
		Rect lr = self.getContentLocalRect()
		Vec2 pos = Mouse_getPosOfWindow(self.ownerWindow)
		int client_x = pos.x
		int client_y = pos.y;
		int dx = client_x - abs.x+lr.x;// lr.get_content_client_pos().x;
		int noffset = self.draw_offset;

		if (dx < self.font_size / 2.0f) { //左偏
			noffset = self.clamp_draw_offset(self.draw_offset + self.font_size / 2.0f);
		}
		else if (dx > lr.w - self.font_size / 2.0f) {//右偏
			noffset = self.clamp_draw_offset(self.draw_offset - self.font_size / 2.0f);
		}
		printf("_update_drag ============= old:%d, new:%d, dx:%d clientX:%d abs.x:%f, lr.x:%f\n", self.draw_offset, noffset, dx, client_x, abs.x, lr.x)
		if (noffset != self.draw_offset) {
			self.draw_offset = noffset;
			//Window::markDirtyByView(this);
		}
		self.invalidDraw();
	}
	void reset_text_editing(){
		// self.text_editing = null
		self.set_text_editing(null)
		self.invalidDraw()
	}
	void draw_editing(Canvas *canvas, int h){
		if (self.text_editing == null){
			return
		}
		int start = self.selection.start - self.text_editing.start;
		int runelen = self.text_editing.start + self.text_editing.length;

		String@ pre = self.value.substring(0, start)
		String@ subfix = self.value.substringToEnd(start + runelen)

		int x0 = self.get_x_of_position(start) + self.draw_offset;
		int x1 = self.get_x_of_position(start + runelen) + self.draw_offset;

		float caretY = 8
		// int h = self.layoutCtx.height

		canvas.fillColorByInt32((0xc97ed3ff)) //nvgRGBA(255, 255, 255, 128));
		canvas.beginPath()
		canvas.rect( x0, caretY, x1 - x0, h - caretY * 2)
		canvas.fill()
	}
	void set_text_editing(TextEditingEvent *evt){

		TextEditingEvent* prev = self.text_editing
		int start = self.selection.start
		int runelen = 0
		if (prev != null){
			start = self.selection.start - prev.start
			runelen = prev.start + prev.length
		}

		// //@TEST evt
		// for (int i = 0, l = evt.text.size(); i < l; i++){
		// 	evt.text.str[i] = 'A'
		// 	evt.text.str[i+1] = 0
		// }

		String@ pre = self.value.substring(0, start)
		String@ subfix = self.value.substringToEnd(start + runelen)
		self.value = pre
			.addString(evt.text)
			.addString(subfix)
		self.notify_changed(evt != null)
		self.selection.set_collapse_pos(start + evt.start)

		self.text_editing = evt
		self.invalidDraw()
		self._update_text_input_rect()
	}
	// 选择全部
	void selectAll(){
		self.selection.set_start(0);
		self.selection.set_end(self.value.size());
		self.caret->restart();
		//Window::markDirtyByView(this);
		self.invalidDraw();
	}
}

EditText@ mkEditText(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (EditText@)gocNode(sp, (Node*)parent, EditText)
}
