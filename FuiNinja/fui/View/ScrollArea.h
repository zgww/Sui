#pragma once

#include "../Core/Predef.h"
#include "../Layout/LayoutLinear.h"
#include "../Core/Vec2.h"
#include "../Core/Frame.h"
#include "../Core/MouseEvent.h"
#include "../Core/View.h"
#include "../View/Drag.h"

#include "../Core/Theme.h"
#include <functional>

class ScrollBar;

static float ScrollView_delta_factor = 0.5;

// class ScrollValue {
// 	int pos = 0
// 	int scroll = 0
// 	int client = 0
// }

class ScrollModel {
public:
	float scroll_left = 0;
	float scroll_top = 0;
	std::function< Vec2()> get_scroll_size;
	std::function< Vec2()> get_client_size;

	//确保偏移在有效的范围内,返回是否有变
	bool clampScrollOffsetValid();

	void on_wheel_event(WheelEvent* evt);
	// PureScrollBarVo hbar_of(int full_size){

	// }
	// PureScrollBarVo vbar_of(int full_size){

	// }
	float get_h_rate();
	float get_v_rate();
	float get_h_length(int full_size);
	float get_v_length(int full_size);
	float get_v_pos(float full_size);
	float calc_scroll_left_by_bar_pos(float full_size, float position);
	float calc_scroll_top_by_bar_pos(float full_size, float position);
	float get_h_pos(float full_size);
	///*按比例,最小值,计算滚动条的尺寸*/
	// min_size = 30
	float bar_length(float rate, float full_size, float min_size);
};


/// 滚动区域
class ScrollArea :public LayoutLinear {
public:
	ScrollModel scroll_model;

	//内容约束, 默认是完全无约束的
	Frame contentCtx = mkFrame();
	//使用宽度约束,内容宽度最大为ScrollArea的宽
	bool useMaxWidthConstraint = false;
	//使用最小宽度约束,内容宽度最小为ScrollArea的宽
	bool useMinWidthConstraint = true;

	//vertical|horizontal|both
	std::string scrollDirection = ("vertical");
	//滚动变化回调
	Ref<Closure< void(ScrollArea* area) >>  onScrollChanged{ nullptr, this };

	Vec2 calc_scroll_size();
	ScrollArea();
	void react();
	Ref<ScrollBar> verScrollBar{ nullptr, this };
	Ref < ScrollBar> horScrollBar{ nullptr, this };


	//布局
	void layout(Frame* ctx);
	void onEvent(Event* e);
	void fireScrollChanged();
	void onWheelEvent(WheelEvent* e);

	void draw_children(Canvas* canvas);
	void draw(Canvas* canvas);
	ViewBase* hitTest(float x, float y);

};

class ScrollBar :public View {
public:
	Ref<Drag> drag{ new Drag(), this };


	bool isVer = true;
	// void onEvent(Event *e){
	// 	if (e instanceof MouseEnterEvent){
	// 	}	
	// }
	// void onMouseEnterEvent(MouseEnterEvent *e){ 
	// }
	ScrollBar();
	void onEvent(Event* e);
	void setHover(bool v);
	bool canLayoutByParent();

	Ref<ScrollArea> scrollArea{ nullptr, this };

	void bindScrollArea(ScrollArea* area);
	void draw_self(Canvas* canvas);
};
