package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"

import * from "../Core/ViewBase.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Event.orc"
import * from "../Core/ViewBase.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Color.orc"
import * from "../Core/Frame.orc"
import * from "../Core/MouseEvent.orc"
import * from "../Core/View.orc"
import * from "../Core/Node.orc"
import * from "../Core/Canvas.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "./ViewBuilder.orc"
import * from "./Drag.orc"

import * from "../../SuiDesigner/Theme.orc"

static float ScrollView_delta_factor = 0.5

// class ScrollValue {
// 	int pos = 0
// 	int scroll = 0
// 	int client = 0
// }

class ScrollModel {
	float scroll_left = 0;
	float scroll_top = 0;
	^Vec2 () get_scroll_size
	^Vec2 () get_client_size
	
	//确保偏移在有效的范围内,返回是否有变
	bool clampScrollOffsetValid(){
		Vec2 client_size = self.get_client_size();
		Vec2 scroll_size = self.get_scroll_size();

		int max_left = scroll_size.x - client_size.x;
		//约束水平轴
		int l = clampInt(
			self.scroll_left,
			0,
			maxInt(0, max_left)
		);
		bool changed = false;
		if (l != self.scroll_left) {
			changed = true;
			self.scroll_left = l;
		}
		//约束垂直轴
		int max_top = scroll_size.y - client_size.y;
		int t = clampInt(
			self.scroll_top,
			0,
			maxInt(0, max_top)
		);
		if (t != self.scroll_top) {
			changed = true;
			self.scroll_top = t;
		}
		return changed;
	}

	void on_wheel_event(WheelEvent* evt){
		Vec2 client_size = self.get_client_size();
		Vec2 scroll_size = self.get_scroll_size();
		if (evt->shift) { //水平
			float max_left = scroll_size.x - client_size.x;
			self.scroll_left = clampInt(
				self.scroll_left - evt->deltaY * minFloat(ScrollView_delta_factor, client_size.x / 2.0f),
				0.0f,
				maxInt(0.0f, max_left)
			);
		}
		else { //垂直
			float max_top = scroll_size.y - client_size.y;
			self.scroll_top = clampInt(
				self.scroll_top - evt->deltaY * minFloat(ScrollView_delta_factor, client_size.y / 2.0f),
				0.0f,
				maxInt(0.0f, max_top)
			);
		}
		printf("ScrollModel 更新 scroll:%d, %d; delta:%d, shift:%d\n"
			, self.scroll_left, self.scroll_top
			, evt->deltaY, evt->shift
		);

	}
	// PureScrollBarVo hbar_of(int full_size){

	// }
	// PureScrollBarVo vbar_of(int full_size){

	// }
	float get_h_rate(){
		Vec2 ss = self.get_scroll_size();
		Vec2 cs = self.get_client_size();
		float ret = minFloat(1.0, cs.x / (float)ss.x)
		return ret
	}
	float get_v_rate(){
		Vec2 ss = self.get_scroll_size();
		Vec2 cs = self.get_client_size();
		float ret = minFloat(1.0, cs.y / (float)ss.y)
		return ret
	}
	float get_h_length(int full_size){
		return (float)self.bar_length(
			self.get_h_rate(), full_size, 30);
	}
	float get_v_length(int full_size){
		return (float)self.bar_length(
			self.get_v_rate(), full_size, 30);

	}
	float get_v_pos(float full_size){
		Vec2 ss = self.get_scroll_size();
		float position = (self.scroll_top /  (float) ss.y * full_size)
		return position
		// Vec2 cs = self.get_client_size();
		// float rate = self.get_v_rate();
		// float len = self.get_v_length(full_size);
		// float pos = (float)self.scroll_top / (ss.y - cs.y) * (full_size - len);
		// return pos
	}
	float calc_scroll_left_by_bar_pos(float full_size, float position){
		Vec2 ss = self.get_scroll_size();
		float left = position / (float)full_size * ss.x 
		return left
	}
	float calc_scroll_top_by_bar_pos(float full_size, float position){
		Vec2 ss = self.get_scroll_size();
		float top = position / (float)full_size * ss.y
		return top
	}
	float get_h_pos(float full_size){
		Vec2 ss = self.get_scroll_size();
		float position = (self.scroll_left /  (float) ss.x * full_size)
		return position
		// Vec2 cs = self.get_client_size();
		// float rate = self.get_v_rate();
		// float len = self.get_v_length(full_size);
		// float pos = (float)self.scroll_top / (ss.y - cs.y) * (full_size - len);
		// return pos
	}
	///*按比例,最小值,计算滚动条的尺寸*/
	// min_size = 30
	float bar_length(float rate, float full_size, float min_size){
		return maxFloat(min_size, rate * full_size);
	}
}


/// 滚动区域
class ScrollArea extends LayoutLinear {
	ScrollModel@ scroll_model = new ScrollModel()

	//内容约束, 默认是完全无约束的
	Frame contentCtx = mkFrame()
	//使用宽度约束,内容宽度最大为ScrollArea的宽
	bool useMaxWidthConstraint = false
	//使用最小宽度约束,内容宽度最小为ScrollArea的宽
	bool useMinWidthConstraint = true

	//vertical|horizontal|both
	String@ scrollDirection = str("vertical");
	//滚动变化回调
	^void (ScrollArea *area) onScrollChanged

	Vec2 calc_scroll_size() {
		return mkVec2(
			self.contentCtx.width,
			self.contentCtx.height,
		);
	}
	void ctor(){
		self.hasInnerReact = true

		self.direction.set("column")
		self.alignItems .set("start")
		self.scroll_model.get_scroll_size = ^Vec2 () {
			return self.calc_scroll_size();
		}
		self.scroll_model.get_client_size = ^Vec2 () {
			Rect r = self.getContentLocalRect()
			return mkVec2(r.w, r.h)
		}
	}
	void react(){
		self.startInnerReact()
		Node* o = self


		self.placeKids(self.outKids)


		//horizontal
		mkScrollBar(o, 0).{
			o.bindScrollArea(self)
			o.isVer = false
			self.horScrollBar = o
		}
		//vertical
		mkScrollBar(o, 0).{
			o.bindScrollArea(self)
			self.verScrollBar = o
		}

		self.endInnerReact()
	}
	ScrollBar@ verScrollBar
	ScrollBar@ horScrollBar


	//布局
	void layout(Frame* ctx) {
		//自身如果有配置width/height，则需要调整为tight约束
		self.updateFrame_forSelfWidthHeight(ctx)
		ctx->setSize_ifAnyTight();
		if (self.callCbLayout(ctx)) {
			return;
		}

		//使用宽度约束
		if (self.useMinWidthConstraint && self.useMaxWidthConstraint){
			Frame tmpCtx = self.makeContentLayoutCtx(ctx);
			self.contentCtx.setWidthConstraint(
				tmpCtx.maxWidth,
				tmpCtx.maxWidth
			)
		}
		else if (self.useMaxWidthConstraint){
			Frame tmpCtx = self.makeContentLayoutCtx(ctx);
			self.contentCtx.setWidthConstraint(
				0.0, 
				tmpCtx.maxWidth
			)
		}
		else if (self.useMinWidthConstraint){
			Frame tmpCtx = self.makeContentLayoutCtx(ctx);
			self.contentCtx.setWidthConstraint(
				tmpCtx.maxWidth,
				infinity,
			)
		}
		else {
			self.contentCtx.setWidthConstraint(
				0.0, 
				infinity
			)
		}

		//布局
		super.layoutContent(&self.contentCtx)

	}
	void onEvent(Event *e){
		if (e instanceof WheelEvent){
			self.onWheelEvent((WheelEvent*)e)
		}
	}
	void fireScrollChanged(){
		if (self.onScrollChanged != null){
			self.onScrollChanged(self)
		}

	}
	void onWheelEvent(WheelEvent *e){
		self.scroll_model.on_wheel_event(e)
		self.fireScrollChanged()
		self.invalidLayout()
	}

	void draw_children(Canvas *canvas){
		{
			float w = themeIns().scrollbar_size
			bool hasV = self.scroll_model.get_v_rate() < 1.0
			float horDeltaW = hasV ? -w : 0 //如果有垂直滚动条，让水平滚动条宽小一点,防止交叉

			// scrollbar的布局在此决定
			self.verScrollBar.frame.x = self.frame.width - self.margin.hor() - w + self.scroll_model.scroll_left 
			self.verScrollBar.frame.y = 0 + self.scroll_model.scroll_top
			self.verScrollBar.frame.width = w
			self.verScrollBar.frame.height = self.frame.height

			self.horScrollBar.frame.x = 0 + self.scroll_model.scroll_left
			self.horScrollBar.frame.y = self.frame.height - self.margin.ver() - w + self.scroll_model.scroll_top
			self.horScrollBar.frame.width = self.frame.width + horDeltaW
			self.horScrollBar.frame.height = w
		}

		//偏移到scroll原点
		canvas.save()
		self.clip(canvas)
		canvas.translate(
			-self.scroll_model.scroll_left,
			-self.scroll_model.scroll_top,
		)

		super.draw_children(canvas)
		canvas.restore()
	}
	void draw(Canvas *canvas){
		//确保偏移正常
		if (self.scroll_model.clampScrollOffsetValid()) {
			self.fireScrollChanged()
			self.invalidLayout()
		}

		canvas.save()

		//应用基础偏移
		canvas.translate(
			self.frame.x + self.margin.left, 
			self.frame.y + self.margin.top);

		// //绘制margin示意
		// canvas.beginPath()
		// canvas.rect(-self.margin.left, 0, self.margin.left, self.frame.height)
		// canvas.fillColorByInt32(0x3300ff00)
		// canvas.fill()

		// canvas.beginPath()
		// canvas.rect(self.frame.width - self.margin.left - self.margin.right, 0, self.margin.right, self.frame.height)
		// canvas.fillColorByInt32(0x3300ff00)
		// canvas.fill()

        canvas.transform(self.transform)
        canvas.currentTransform(&self._world_transform);

		//绘制自己
		self.draw_self(canvas)
		canvas.save();
		canvas.translate(
			// vg,
			self.padding.left + self.border.l.w, 
			self.padding.top + self.border.t.w
		);
		//绘制内容
		self.draw_children(canvas)
		canvas.restore();

		canvas.restore()
	}
	ViewBase * hitTest(float x, float y){
		Rect r = self.get_abs_rect();
		if (!r.containsPosition(x, y)) {
			return null;
		}
		return super.hitTest(x, y);
	}

}
 
class ScrollBar extends View{

	Drag@ drag = new Drag()



	bool isVer = true
	// void onEvent(Event *e){
	// 	if (e instanceof MouseEnterEvent){
	// 	}	
	// }
	// void onMouseEnterEvent(MouseEnterEvent *e){ 
	// }
	void ctor(){
		// super.ctor()
		self.width = 10
		self.height = 204
		self.drag.onDrag = ^void(Drag*d){
			printf("drag scrollbar\n")
			if self.scrollArea == null{
				return
			}
			ScrollModel *model = self.scrollArea.scroll_model
			if self.isVer {
				float fullSize = self.frame.height
				float barPos = model.get_v_pos(fullSize) 
				float newBarPos = barPos + d.deltaPos.y
				//计算有误。
				model.scroll_top = model.calc_scroll_top_by_bar_pos(fullSize, newBarPos)
			}
			else {
				float fullSize = self.frame.width
				float barPos = model.get_h_pos(fullSize) 
				float newBarPos = barPos + d.deltaPos.x
				printf("newBarPos:%f. delta:%f left:%d\n", newBarPos, d.deltaPos.x, model.scroll_left);
				model.scroll_left = model.calc_scroll_left_by_bar_pos(fullSize, newBarPos)
				printf("\tnew left:%d\n",  model.scroll_left);
			}

			model.clampScrollOffsetValid()
			self.scrollArea.fireScrollChanged()
		}
	}
	void onEvent(Event*e){
		self.drag.onMouseDown(e)
	}
	void setHover(bool v){
		super.setHover(v)
		self.invalidDraw()
	}
    bool canLayoutByParent(){
        return false
    }

	ScrollArea@ scrollArea = null
	void bindScrollArea(ScrollArea *area){
		if area == self.scrollArea {
			return
		}

		printf("\n\n========================================绑定ScrollArea\n\n")
		self.scrollArea = area
		area.onScrollChanged = ^void (ScrollArea *area){
			self.invalidDraw()
		}
	}
	void draw_self(Canvas *canvas){
		if self.scrollArea == null{
			return
		}

		int x = 0
		int w = self.frame.width
		int y = 0
		int h = self.frame.height

		ScrollModel *model = self.scrollArea.scroll_model
		float d = 0
		float r = minFloat(w, h) / 2.0

		Theme* t = themeIns()
		int bg = t.scrollbar_bg
		int barBg = t.scrollbar_barBg

		if self.isVer {
			if model.get_v_rate() >= 0.9999999{ //不用滚动
				return
			}

			//背景

			//绘制滚动条背景
			// canvas.boxGradient(
			// 	true,
			// 	0,y,w,h,
			// 	3,4, 
			// 	mkIntByRgba(0,0,0, self.hover ? 32: 16), 
			// 	mkIntByRgba(0,0,0, self.hover ? 92 : 64)
			// 	);
			canvas.beginPath();
			canvas.roundRect( x, y, w, h, 3);
			canvas.fillColorByInt32(bg)//0x13ff0000)
			canvas.fill();

			float fullSize = h - 0
			float barLen = model.get_v_length(fullSize)
			float barPos = model.get_v_pos(fullSize) + 0
			float barX = x + d;
			float barW = w - d * 2;
			//条
			// canvas.boxGradient(
			// 	true, 
			// 	barX, barPos, barW, barLen,
			// 	3, 4, 
			// 	mkIntByRgba(255,255,255,128), 
			// 	mkIntByRgba(128,128,128,128),
			// 	);
			canvas.beginPath();
			canvas.fillColorByInt32(barBg)//0x44ff0000)
			canvas.roundRect( barX, barPos, barW, barLen, r);
			canvas.fill();
		} 
		else {
			if model.get_h_rate() >= 0.9999999{ //不用滚动
				return
			}

			//背景
			// canvas.boxGradient(
			// 	true,
			// 	0,0, w,h,
			// 	3,4, 
			// 	mkIntByRgba(0,0,0, self.hover ? 32: 16), 
			// 	mkIntByRgba(0,0,0, self.hover ? 92 : 64)
			// 	);
			canvas.beginPath();
			canvas.roundRect( x, y, w, h, 3);
			canvas.fillColorByInt32(bg)//0x13ff0000)
			canvas.fill();



			//条
			float fullSize = w 
			float barLen = model.get_h_length(fullSize)
			float barPos = model.get_h_pos(fullSize) 
			float barY = y + d;
			float barH = h - d * 2;

				// canvas.boxGradient(
				// 	true, 
				// 	x, y, w, h,
				// 	3, 4, 
				// 	mkIntByRgba(255,255,255,128), 
				// 	mkIntByRgba(128,128,128,128),
				// 	);
			canvas.beginPath();
			canvas.fillColorByInt32(barBg)//0x44ff0000)
			canvas.roundRect( barPos, barY, barLen, barH, r);
			canvas.fill();
		}
	}
}

ScrollArea@ mkScrollArea(void* parent, long long key){
    return (ScrollArea@)gocNode(
		key ? (void*)key: __builtin_return_address(0)
		, (Node*)parent, ScrollArea)
}



ScrollBar@ mkScrollBar(void* parent, long long key){
    return (ScrollBar@)gocNode(
		key ? (void*)key: __builtin_return_address(0)
		, (Node*)parent, ScrollBar)
}