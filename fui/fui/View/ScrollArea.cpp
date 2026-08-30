#include "ScrollArea.h"
#include "../Core/Canvas.h"

//确保偏移在有效的范围内,返回是否有变
bool ScrollModel::clampScrollOffsetValid() {
	Vec2 client_size = this->get_client_size();
	Vec2 scroll_size = this->get_scroll_size();

	int max_left = scroll_size.x - client_size.x;
	//约束水平轴
	int l = clampInt(
		this->scroll_left,
		0,
		maxInt(0, max_left)
	);
	bool changed = false;
	if (l != this->scroll_left) {
		changed = true;
		this->scroll_left = l;
	}
	//约束垂直轴
	int max_top = scroll_size.y - client_size.y;
	int t = clampInt(
		this->scroll_top,
		0,
		maxInt(0, max_top)
	);
	if (t != this->scroll_top) {
		changed = true;
		this->scroll_top = t;
	}
	return changed;
}

void ScrollModel::on_wheel_event(WheelEvent* evt) {
	Vec2 client_size = this->get_client_size();
	Vec2 scroll_size = this->get_scroll_size();
	if (evt->shift) { //水平
		float max_left = scroll_size.x - client_size.x;
		this->scroll_left = clampInt(
			this->scroll_left - evt->deltaY * minFloat(ScrollView_delta_factor, client_size.x / 2.0f),
			0.0f,
			maxInt(0.0f, max_left)
		);
	}
	else { //垂直
		float max_top = scroll_size.y - client_size.y;
		this->scroll_top = clampInt(
			this->scroll_top - evt->deltaY * minFloat(ScrollView_delta_factor, client_size.y / 2.0f),
			0.0f,
			maxInt(0.0f, max_top)
		);
	}
	printf("ScrollModel 更新 scroll:%f, %f; delta:%d, shift:%d\n"
		, this->scroll_left, this->scroll_top
		, evt->deltaY, evt->shift
	);

}

// }
float ScrollModel::get_h_rate() {
	Vec2 ss = this->get_scroll_size();
	Vec2 cs = this->get_client_size();
	float ret = minFloat(1.0, cs.x / (float)ss.x);
	return ret;
}

float ScrollModel::get_v_rate() {
	Vec2 ss = this->get_scroll_size();
	Vec2 cs = this->get_client_size();
	float ret = minFloat(1.0, cs.y / (float)ss.y);
	return ret;
}

float ScrollModel::get_h_length(int full_size) {
	return (float)this->bar_length(
		this->get_h_rate(), full_size, 30);
}

float ScrollModel::get_v_length(int full_size) {
	return (float)this->bar_length(
		this->get_v_rate(), full_size, 30);

}

float ScrollModel::get_v_pos(float full_size) {
	Vec2 ss = this->get_scroll_size();
	float position = (this->scroll_top / (float)ss.y * full_size);
	return position;
}

float ScrollModel::calc_scroll_left_by_bar_pos(float full_size, float position) {
	Vec2 ss = this->get_scroll_size();
	float left = position / (float)full_size * ss.x;
	return left;
}

float ScrollModel::calc_scroll_top_by_bar_pos(float full_size, float position) {
	Vec2 ss = this->get_scroll_size();
	float top = position / (float)full_size * ss.y;
	return top;
}

float ScrollModel::get_h_pos(float full_size) {
	Vec2 ss = this->get_scroll_size();
	float position = (this->scroll_left / (float)ss.x * full_size);
	return position;
}

///*按比例,最小值,计算滚动条的尺寸*/
// min_size = 30
float ScrollModel::bar_length(float rate, float full_size, float min_size) {
	return maxFloat(min_size, rate * full_size);
}

Vec2 ScrollArea::calc_scroll_size() {
	return mkVec2(
		this->contentCtx.width,
		this->contentCtx.height
	);
}

ScrollArea::ScrollArea() {
	CtorGuard g(this);

	this->direction = ("column");
	this->alignItems = ("start");

	this->scroll_model.get_scroll_size = [this]() {
		return this->calc_scroll_size();
		};
	this->scroll_model.get_client_size = [this]() {
		Rect r = this->getContentLocalRect();
		return mkVec2(r.w, r.h);
		};

	initInnerReact();
}

void ScrollArea::react() {
	auto& o = startInnerReact();

	o.placeKids(this->gocOutKids());
	_reactScrollBar();

	this->endInnerReact();
}

void ScrollArea::_reactScrollBar() {
	auto& o = *this;
	//horizontal
	R(ScrollBar) {
		o.bindScrollArea(this);
		o.isVer = false;
		this->horScrollBar = &o;
	} REND;
	//vertical
	R(ScrollBar) {
		o.bindScrollArea(this);
		this->verScrollBar = &o;
	} REND;
}
//布局
void ScrollArea::layout(Frame* ctx) {
	//自身如果有配置width/height，则需要调整为tight约束
	this->updateFrame_forSelfWidthHeight(ctx);
	ctx->setSize_ifAnyTight();
	if (this->callCbLayout(ctx)) {
		return;
	}

	//使用宽度约束
	if (this->useMinWidthConstraint && this->useMaxWidthConstraint) {
		Frame tmpCtx = this->makeContentLayoutCtx(ctx);
		this->contentCtx.setWidthConstraint(
			tmpCtx.maxWidth,
			tmpCtx.maxWidth
		);
	}
	else if (this->useMaxWidthConstraint) {
		Frame tmpCtx = this->makeContentLayoutCtx(ctx);
		this->contentCtx.setWidthConstraint(
			0.0,
			tmpCtx.maxWidth
		);
	}
	else if (this->useMinWidthConstraint) {
		Frame tmpCtx = this->makeContentLayoutCtx(ctx);
		this->contentCtx.setWidthConstraint(
			tmpCtx.maxWidth,
			infinity
		);
	}
	else {
		this->contentCtx.setWidthConstraint(
			0.0,
			infinity
		);
	}

	//布局
	LayoutLinear::layoutContent(&this->contentCtx);
	//printf("contentCtx:%s\n", contentCtx.toString().c_str());
}

void ScrollArea::onEvent(Event* e) {
	if (auto we = dynamic_cast<WheelEvent*>(e)) {
		this->onWheelEvent(we);
	}
}

void ScrollArea::fireScrollChanged() {
	if (this->onScrollChanged != nullptr) {
		this->onScrollChanged->invoke(this);
	}

}

void ScrollArea::onWheelEvent(WheelEvent* e) {
	this->scroll_model.on_wheel_event(e);
	this->fireScrollChanged();
	this->invalidLayout();
}

void ScrollArea::draw_children(Canvas* canvas) {
	{
		float w = themeIns()->scrollbar_size;
		bool hasV = this->scroll_model.get_v_rate() < 1.0;
		float horDeltaW = hasV ? -w : 0; //如果有垂直滚动条，让水平滚动条宽小一点,防止交叉

		// scrollbar的布局在此决定
		this->verScrollBar->frame.x = this->frame.width - this->margin.hor() - w + this->scroll_model.scroll_left;
		this->verScrollBar->frame.y = 0 + this->scroll_model.scroll_top;
		this->verScrollBar->frame.width = w;
		this->verScrollBar->frame.height = this->frame.height;

		this->horScrollBar->frame.x = 0 + this->scroll_model.scroll_left;
		this->horScrollBar->frame.y = this->frame.height - this->margin.ver() - w + this->scroll_model.scroll_top;
		this->horScrollBar->frame.width = this->frame.width + horDeltaW;
		this->horScrollBar->frame.height = w;
	}

	//偏移到scroll原点
	canvas->save();
	this->clip(canvas);
	canvas->translate(
		-this->scroll_model.scroll_left,
		-this->scroll_model.scroll_top
	);

	LayoutLinear::draw_children(canvas);
	canvas->restore();
}

void ScrollArea::draw(Canvas* canvas) {
	//确保偏移正常
	if (this->scroll_model.clampScrollOffsetValid()) {
		this->fireScrollChanged();
		this->invalidLayout();
	}

	canvas->save();

	//应用基础偏移
	canvas->translate(
		this->frame.x + this->margin.left,
		this->frame.y + this->margin.top);

	// //绘制margin示意
	// canvas->beginPath()
	// canvas->rect(-this->margin.left, 0, this->margin.left, this->frame.height)
	// canvas->fillColorByInt32(0x3300ff00)
	// canvas->fill()

	// canvas->beginPath()
	// canvas->rect(this->frame.width - this->margin.left - this->margin.right, 0, this->margin.right, this->frame.height)
	// canvas->fillColorByInt32(0x3300ff00)
	// canvas->fill()

	canvas->transform(this->transform);
	canvas->currentTransform(&this->_world_transform);

	//绘制自己
	this->draw_self(canvas);
	canvas->save();
	canvas->translate(
		// vg,
		this->padding.left + this->border.l.w,
		this->padding.top + this->border.t.w
	);
	//绘制内容
	this->draw_children(canvas);
	canvas->restore();

	canvas->restore();
}

ViewBase* ScrollArea::hitTest(float x, float y) {
	Rect r = this->get_abs_rect();
	if (!r.containsPosition(x, y)) {
		return nullptr;
	}
	return LayoutLinear::hitTest(x, y);
}

// void onEvent(Event *e){
// 	if (e instanceof MouseEnterEvent){
// 	}	
// }
// void onMouseEnterEvent(MouseEnterEvent *e){ 
// }
ScrollBar::ScrollBar() {
	CtorGuard g(this);
	auto self = Ref(this);
	// super.ctor()
	this->width = 10;
	this->height = 204;
	this->drag->onDrag = CLOSURE([=](Drag* d) {
		printf("drag scrollbar\n");
		if (self->scrollArea == nullptr) {
			return;
		}
		ScrollModel& model = self->scrollArea->scroll_model;
		if (this->isVer) {
			float fullSize = self->frame.height;
			float barPos = model.get_v_pos(fullSize);
			float newBarPos = barPos + d->deltaPos.y;
			//计算有误。
			model.scroll_top = model.calc_scroll_top_by_bar_pos(fullSize, newBarPos);
		}
		else {
			float fullSize = self->frame.width;
			float barPos = model.get_h_pos(fullSize);
			float newBarPos = barPos + d->deltaPos.x;
			printf("newBarPos:%f. delta:%f left:%f\n", newBarPos, d->deltaPos.x, model.scroll_left);
			model.scroll_left = model.calc_scroll_left_by_bar_pos(fullSize, newBarPos);
			printf("\tnew left:%f\n", model.scroll_left);
		}

		model.clampScrollOffsetValid();
		self->scrollArea->fireScrollChanged();
		});
}

void ScrollBar::onEvent(Event* e) {
	this->drag->onMouseDown(e);
}

void ScrollBar::setHover(bool v) {
	View::setHover(v);
	this->invalidDraw();
}

bool ScrollBar::canLayoutByParent() {
	return false;
}

void ScrollBar::bindScrollArea(ScrollArea* area) {
	if (area == this->scrollArea.get()) {
		return;
	}

	printf("\n\n========================================绑定ScrollArea\n\n");
	this->scrollArea = area;
	//auto self = Ref(this);
	//area->onScrollChanged = CLOSURE([=](ScrollArea* area) {
	//	this->invalidDraw();
	//	});
}

void ScrollBar::draw_self(Canvas* canvas) {
	if (this->scrollArea == nullptr) {
		return;
	}

	int x = 0;
	int w = this->frame.width;
	int y = 0;
	int h = this->frame.height;

	ScrollModel& model = this->scrollArea->scroll_model;
	float d = 0;
	float r = minFloat(w, h) / 2.0;

	Theme* t = themeIns();
	int bg = t->scrollbar_bg;
	int barBg = t->scrollbar_barBg;

	if (this->isVer) {
		if (model.get_v_rate() >= 0.9999999) { //不用滚动
			return;
		}

		//背景

		//绘制滚动条背景
		// canvas->boxGradient(
		// 	true,
		// 	0,y,w,h,
		// 	3,4, 
		// 	mkIntByRgba(0,0,0, this->hover ? 32: 16), 
		// 	mkIntByRgba(0,0,0, this->hover ? 92 : 64)
		// 	);
		canvas->beginPath();
		canvas->roundRect(x, y, w, h, 3);
		canvas->fillColorByInt32(bg);//0x13ff0000)
		canvas->fill();

		float fullSize = h - 0;
		float barLen = model.get_v_length(fullSize);
		float barPos = model.get_v_pos(fullSize) + 0;
		float barX = x + d;
		float barW = w - d * 2;
		//条
		// canvas->boxGradient(
		// 	true, 
		// 	barX, barPos, barW, barLen,
		// 	3, 4, 
		// 	mkIntByRgba(255,255,255,128), 
		// 	mkIntByRgba(128,128,128,128),
		// 	);
		canvas->beginPath();
		canvas->fillColorByInt32(barBg);//0x44ff0000)
		canvas->roundRect(barX, barPos, barW, barLen, r);
		canvas->fill();
	}
	else {
		if (model.get_h_rate() >= 0.9999999) { //不用滚动
			return;
		}

		//背景
		// canvas->boxGradient(
		// 	true,
		// 	0,0, w,h,
		// 	3,4, 
		// 	mkIntByRgba(0,0,0, this->hover ? 32: 16), 
		// 	mkIntByRgba(0,0,0, this->hover ? 92 : 64)
		// 	);
		canvas->beginPath();
		canvas->roundRect(x, y, w, h, 3);
		canvas->fillColorByInt32(bg);//0x13ff0000)
		canvas->fill();



		//条
		float fullSize = w;
		float barLen = model.get_h_length(fullSize);
		float barPos = model.get_h_pos(fullSize);
		float barY = y + d;
		float barH = h - d * 2;

		// canvas->boxGradient(
		// 	true, 
		// 	x, y, w, h,
		// 	3, 4, 
		// 	mkIntByRgba(255,255,255,128), 
		// 	mkIntByRgba(128,128,128,128),
		// 	);
		canvas->beginPath();
		canvas->fillColorByInt32(barBg);//0x44ff0000)
		canvas->roundRect(barPos, barY, barLen, barH, r);
		canvas->fill();
	}
}
