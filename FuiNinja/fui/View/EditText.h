#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/MouseEvent.h"
#include "../Core/KeyEvent.h"
#include "../Core/Timer.h"
#include "../Core/Focus.h"
#include "../Core/Theme.h"
#include <string>
//
//class EditText : public View {
//public:
//	std::string value;
//	std::string placeholder;
//	int fontSize = 14;
//	int color = 0xff333333;
//	int caretColor = 0xff1677ff;
//	int placeholderColor = 0xff999999;
//	int bgColor = 0xffffffff;
//
//	int caretPos = 0;
//	bool caretVisible = false;
//	bool focused = false;
//	Ref<Timer> caretTimer{nullptr, this};
//
//	Ref<Closure<void(const std::string&)>> onChanged{nullptr, this};
//
//	EditText();
//	void setValue(const std::string& v);
//	void focus();
//	void blur();
//	void insertText(const std::string& text);
//	void deleteBackward();
//	void deleteForward();
//	void moveCaret(int delta);
//	void draw_self(Canvas* canvas) override;
//	void onEvent(Event* ev) override;
//	void onUnmounting() override;
//
//	virtual const char* getClassName() const override { return "EditText"; }
//};

struct Range {
	int start;
	int end;
};
Range mkRange(int start, int end);



class Selection: public GcObj {
public:
	int start = 0;//单位rune
	int end = 0;//rune
	//Ref<Closure<std::string()>> get_value{ nullptr, this };
	//Ref<Closure<void(std::string)>> set_value{ nullptr, this };
	std::function<std::string()> get_value;
	std::function<void(std::string)> set_value;

	//std::function<string()> get_value = []() {return ""; };
//std::function<void(string)> set_value = [](string v) {};
	std::string get_range_value();
	bool is_collapse();
	bool is_range();
	Range get_asc_range();
	int clamp_pos(int pos);
	void set_collapse_pos(int pos);
	void set_start(int pos);
	void set_end(int pos);
	void move_delta(int delta, bool shift);

	std::string backspace();
	std::string del_range();
	std::string delete_act();
	std::string insert(const char* text);
};

class Caret : public GcObj {
public:
	bool show = true;
	Ref<Timer> blink_timer{ nullptr, this };
	Ref < ViewBase> view{ nullptr, this };
	Ref<Closure<void(Caret* ins)>> cb_notify{ nullptr, this };

	Caret();
	bool isBlinking();

	// Ref<Timer> blink_timer{ nullptr, this };

	// Ref<ViewBase> view{ 0, this };
	// Ref<Closure<void(Caret*)>> cb_notify = { 0, this };

	// Caret();
	void setShow(bool _show);
	void blink();
	void start();
	void stop();
	void restart();
};



/// 布局上下文
class EditText : public View {

public:
	std::string value;
	int font_size = themeIns()->edittext_fontSize;//17;
	std::string font_face;
	int color = themeIns()->edittext_color; // 0xff000000;
	int caret_color = themeIns()->edittext_caretColor;//0xff000000;
	int font_weight = 400;
	std::string placeholder = "please input";
	int placeholder_color = 0xff999999;

	Ref<Closure<void(std::string value)>> onchanged{ nullptr, this };

	int draw_offset = 0; //绘制偏移:[-n, 0]. 单位：像素
	int _caret_x = 0;

	Selection selection;
	Ref<Timer> drag_timer{ nullptr, this };
	Ref<Caret> caret{ new Caret(), this };

	//输入法合成状态
	Ref<TextEditingEvent> text_editing{ nullptr, this };

	EditText();


	void layoutContent(Frame* ctx);
	void setValue_notInFocus(std::string v);
	void setValue(std::string v);
	std::string getValue() { return this->value; }

	void setFont_size(int v);
	int getFont_size();

	void setFont_face(std::string v);
	std::string getFont_face() { return this->font_face; }

	void setColor(int v);
	int getColor() { return this->color; }

	void setCaret_color(int v);
	int getCaret_color() { return this->caret_color; }

	void setFont_weight(int v);
	int getFont_weight() { return this->font_weight; }

	void setPlaceholder(std::string v);
	std::string getPlaceholder() { return this->placeholder; }

	void setPlaceholder_color(int v);
	int getPlaceholder_color() { return this->placeholder_color; }


	Ref<Closure<void(EditText* et)>> onValueChanged{ nullptr, this };
	void notify_changed(bool by_user_event);
	void set_value(std::string nvalue, bool by_user_event);

	Timer* gocDragTimer();

	void react();
	void draw_self(Canvas* canvas);


	void onEvent(Event* evt);
	void on_window_focus_event(WindowFocusEvent* e);
	//键盘事件，注意区分字符事件
	void on_key_event(KeyEvent* e);
	//焦点事件
	void on_focus_event(FocusEvent* evt);
	// ime合成事件
	void on_editing_event(TextEditingEvent* evt);
	//输入字符（含中文）, 所有的字符都从这里插入的,不管是英文还是中文
	void on_input_event(TextInputEvent* e);
	void onUnmounting();
	//取消聚焦
	void blur();
	Ref<Canvas> _canvas{ nullptr, this };
	//取得字符位置的像素x坐标
	float get_x_of_position(int pos);

	// 更新Ime合成输入矩形？
	void _update_text_input_rect();
	void update_draw_offset_by_keydown_move_with_default();
	//键盘操作后，更新滚动偏移
	void update_draw_offset_by_keydown_move(float target_caret_ratio, bool force);

	int clamp_draw_offset(int offset);
	//根据像素x找到字符位置，用于点击时，查找鼠标所在位置
	int get_char_position_by_client_x(int client_x);
	void on_mouse_event(MouseEvent* e);
	void on_mouse_down(MouseEvent* e);

	void onListenerEvent(Event* e);



	void on_rootView_mouse_up(MouseEvent* e);
	void on_rootView_mouse_move(MouseEvent* e);

	void _update_drag();
	void reset_text_editing();
	void draw_editing(Canvas* canvas, int h);
	void set_text_editing(TextEditingEvent* evt);
	// 选择全部
	void selectAll();
};