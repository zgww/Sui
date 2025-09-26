package SuiCore

#include <stdio.h>


import * from "./Node.orc"
import * from "./Inset.orc"
import * from "./Vec2.orc"
import * from "./Rect.orc"
import type * from "./LayoutCell.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/List.orc"

struct Frame {
	//int layoutId; //唯一标记一次布局。 用来确定是不是同一次布局中调用了多次的Layout
	int timesInOneLayout; //在一次布局，调用了几次布局
	int applyCacheTimes;// 应用缓存次数.可以认为是避免重复布局的次数
	//约束
	float minWidth;
	float minHeight;
	float maxWidth ;
	float maxHeight ;

    //记录frame, 用来避免重复布局. 如果再次请求布局，并且约束未改变时，就没必要再布局了
	float prevMinWidth;
	float prevMinHeight;
	float prevMaxWidth ;
	float prevMaxHeight ;

	//期望的宽高
	//满足最小最大尺寸约束后，可选的宽高还是有很多
	//可以使用内容宽高，也可以使用期望宽高
	//
	// 为什么去掉。
	// 因为期望的宽高很多时候是需要综合父布局的信息的
	// 并没有办法直接在自己的布局方法中决定。
	// 因为期望，是在有足够空间时，才能决定的。
	// 怎么判断是没有足够的空间，这需要父布局的信息。
	// 如LayoutLinear, 如果是无限空间，或者空间有足够时，
	// 才有desiredSize的可能
	// 而且想设置desiredSize,也是要设置minWidth/minHeight再重
	// 走一遍layout,不然可能跟layout自身的布局规则产生冲突
	// float desiredWidth;
	// float desiredHeight;

	//这是实际的frame矩形
	float x;
	float y;
	float width;
	float height; 
}
Frame mkFrame(){
	Frame f;
	//约束
	f.minWidth = .0f
	f.minHeight = 0.f
	f.maxWidth = infinity 
	f.maxHeight = infinity 

	f.prevMinWidth = -1.f;
	f.prevMinHeight = -1.f;
	f.prevMaxWidth  = -1.f;
	f.prevMaxHeight  = -1.f;

	// f.desiredWidth = nan
	// f.desiredHeight = nan
	//结果
	//注意：此处的矩形信息都是不考虑margin, padding, border啥的。 margin,padding/border都是视图内部概念。 不影响布局
	//布局是很清晰简洁的 传递约束，计算尺寸和位置。
	//这里的width就是布局矩形的尺寸，无关其他概念。对于div,就是outbox的尺寸
	f.x = 0.f;
	f.y = 0.f;
	f.width = 0.f;
	f.height = 0.f; 
	return f;
}

extension Frame {
	// //应用期望值:如果期望值在[max(min, current), max]之间，就可以应用了
	// void applyDesiredSize(){
	// 	if (!isnan(self.desiredWidth )){
	// 		self.width = clampFloat(self.desiredWidth, maxFloat(self.minWidth, self.width), self.maxWidth)
	// 	}
	// 	if (!isnan(self.desiredHeight) ){
	// 		self.height = clampFloat(self.desiredHeight, maxFloat(self.minHeight, self.height), self.maxHeight)
	// 	}
	// }
	Frame copy(){
		Frame ret;

		ret.minWidth = self.minWidth
		ret.minHeight  = self.minHeight 
		ret.maxWidth  = self.maxWidth 
		ret.maxHeight  = self.maxHeight 

		// ret.desiredWidth = self.desiredWidth
		// ret.desiredHeight  = self.desiredHeight 

		ret.x  = self.x 
		ret.y = self.y
		ret.width  = self.width 
		ret.height  = self.height 

		return ret
	}
	//约束是否有变化
	bool isConstraintsNotChanged(){
		return self.prevMinWidth == self.minWidth
		&& self.prevMinHeight  == self.minHeight 
		&& self.prevMaxWidth  == self.maxWidth 
		&& self.prevMaxHeight  == self.maxHeight 
	}
	// 检查，然后使用缓存的结果
	bool checkAndUseCacheResult(){
		if self.isConstraintsNotChanged() {
			self.applyCacheTimes++
			return true
		}
		return false
	}
	//保存约束
	void saveConstraints(){
		self.prevMinWidth = self.minWidth
		self.prevMinHeight  = self.minHeight 
		self.prevMaxWidth  = self.maxWidth 
		self.prevMaxHeight  = self.maxHeight 
	}

	
	void incTimesInOneLayout(){
		self.timesInOneLayout++
	}

	// void setDesiredSize_withMargin(
	// 	float desiredWidth,
	// 	float desiredHeight,
	// 	Inset *margin,
	// 	// float marginHor,
	// 	// float marginVer,
	// ){
    //     if (!isnan(desiredWidth)){
    //         self.desiredWidth = desiredWidth + (margin == null ? 0 : margin.hor())
    //     }
    //     if (!isnan(desiredWidth) ){
    //         self.desiredHeight = desiredHeight + (margin == null ? 0 : margin.ver());
    //     }
	// }

	// 向内传递约束, 宽高变化
	Frame inset(Inset inset){
		Frame ret = self.copy();
		ret.minWidth = ret.minWidth - inset.hor()
		ret.minHeight = ret.minHeight - inset.ver()

		if (ret.maxWidth != infinity){
			ret.maxWidth = maxFloat(ret.minWidth, ret.maxWidth - inset.hor())
		}
		if (ret.maxHeight != infinity){
			ret.maxHeight = maxFloat(ret.minHeight, ret.maxHeight - inset.ver())
		}

		// if (!isnan(ret.desiredWidth) ){
		// 	ret.desiredWidth  = maxFloat(self.minWidth, ret.desiredWidth - inset.hor())
		// }
		// if (!isnan(ret.desiredHeight )){
		// 	ret.desiredHeight = maxFloat(self.minHeight, ret.desiredHeight - inset.ver())
		// }

		ret.x = ret.x + inset.left
		ret.y = ret.y + inset.top
		ret.width = maxFloat(0.0f, ret.width - inset.hor())
		ret.height = maxFloat(0.0f, ret.height - inset.ver())
		return ret
	}
	//向外传递, 宽高变化
	Frame outset(Inset inset){
		inset.invert()
		return self.inset(inset)
	}
    //外框矩形,坐标相对于父内容区
    Rect toRect(){
        Rect r = mkRect(self.x, self.y, self.width, self.height);
        return r
    }

	void copyConstraints(Frame* ctx){
		self.copyWidthConstraint(ctx);
		self.copyHeightConstraint(ctx);
	}
	void copyMaxConstraints(Frame* ctx){
		self.maxHeight = ctx->maxHeight;
		self.maxWidth = ctx->maxWidth;
	}
	void copyMinConstraints(Frame* ctx){
		self.minHeight = ctx->minHeight;
		self.minWidth = ctx->minWidth;
	}
	void setMinConstraints(float w, float h){
		self.minWidth = w;
		self.minHeight = h;
	}
	void setMaxConstraints( float w, float h){
		self.maxWidth = w;
		self.maxHeight = h;
	}
	void setMinWidth(float minV){ 
		self.minWidth = maxFloat(0.f, minV)
	}
	void setMinHeight(float minV){
		self.minHeight = maxFloat(0.f, minV);
	}
	void setWidthConstraint(float minv, float maxv){
		self.minWidth = minv;
		self.maxWidth = maxv;
	}
	void setHeightConstraint(float minv, float maxv){
		self.minHeight = minv;
		self.maxHeight = maxv;
	}
	void clampTightWidthConstraint(float v){
		v = clampFloat(v, self.minWidth, self.maxWidth);
		self.minWidth = maxFloat(self.minWidth, v);
		self.maxWidth = minFloat(self.maxWidth, v);
	}
	void clampTightHeightConstraint(float v){
		v = clampFloat(v, self.minHeight, self.maxHeight);
		self.minHeight = maxFloat(self.minHeight, v);
		self.maxHeight = minFloat(self.maxHeight, v);
	}
	void plusWidthConstraint(float minW, float maxW){
		if (self.minWidth < minW) {
			self.minWidth = minFloat(minW, self.maxWidth);
		}
		if (maxW < self.maxWidth) {
			self.maxWidth = maxFloat(maxW, self.minWidth);
		}
		self.minWidth = minFloat(self.minWidth, self.maxWidth);
	}
	void plusHeightConstraint(float minW, float maxW){
		if (self.minHeight < minW) {
			self.minHeight = minFloat(minW, self.maxHeight);
		}
		if (maxW < self.maxHeight) {
			self.maxHeight = maxFloat(maxW, self.minHeight);
		}

		self.minHeight = minFloat(self.minHeight, self.maxHeight);
	}
	void plusConstraints(float minW, float maxW, float minH, float maxH){
		self.plusWidthConstraint(minW, maxW);
		self.plusHeightConstraint(minH, maxH);
	}
	void clampWidth(float v, float minW, float maxW){
		self.width = clampFloat(v, maxFloat(minW, self.minWidth), minFloat(maxW, self.maxWidth));
	}
	void clampHeight(float v, float minW, float maxW){
		self.height = clampFloat(v, maxFloat(minW, self.minHeight), minFloat(maxW, self.maxHeight));
	}
	void setSize(float w, float h){
		self.width = clampFloat(w, self.minWidth, self.maxWidth);
		self.height = clampFloat(h, self.minHeight, self.maxHeight);
	}
	Vec2 getSize(){
		return mkVec2(self.width, self.height);
	}
	void setWidth(float w){
		self.width = clampFloat(w, self.minWidth, self.maxWidth);
	}
	void setHeight(float h){
		self->height = clampFloat(h, self->minHeight, self->maxHeight);
	}
	void setRect(float x, float y, float w, float h){
		self->x = x;
		self->y = y;
		self->setSize(w, h);
	}
	void setPosition(float x, float y){
		self->x = x;
		self->y = y;
	}
	float getBottom(){
		return self.y + self.height;
	}
	float getRight(){
		return self.x + self.width;
	}
	//如果宽或者高的最小、最大限死了，就可以直接得出具体的宽高值
	bool setSize_ifAnyTight(){
		bool ret = false;
		if (self.isTightWidth()) {
			self.width = self.minWidth;
			ret = true;
		}
		if (self.isTightHeight()) {
			self.height = self.minHeight;
			ret = true;
		}
		return ret;
	}
	bool setSize_ifTight(){
		if (self.isTight()) {
			self.width = self.minWidth;
			self.height = self.minHeight;
			return true;
		}
		return false;
	}

	void copyWidthConstraint(Frame* ctx){
		self.minWidth = ctx->minWidth;
		self.maxWidth = ctx->maxWidth;
	}
	void copyHeightConstraint(Frame* ctx){
		self.minHeight = ctx->minHeight;
		self.maxHeight = ctx->maxHeight;
	}
	void setTightWidth(float w){
		self.width = self.minWidth = self.maxWidth = w; 
	}
	void setTightHeight(float h){
		self.height = self.minHeight = self.maxHeight = h;
	}
	void setTight(float w, float h){
		self.width = self.minWidth = self.maxWidth = w;
		self.height = self.minHeight = self.maxHeight = h; 
	}
	bool isTightWidth(){
		return  self.minWidth == self.maxWidth;
	} 
	bool isTightHeight(){
		return self.minHeight == self.maxHeight;
	}
	bool isTight(){
		return self.minWidth == self.maxWidth && self.minHeight == self.maxHeight;
	}
	bool isLoose(){
		return !self.isTight();
	}
	void reset(){
		*self = mkFrame()
	}
	//判断宽高是否满足约束
	bool isSizeSatisfy_otherFrameConstraints(Frame *ctx){
		if (self.width < ctx.minWidth || self.width > ctx.maxWidth){
			return false
		}
		if (self.height < ctx.minHeight || self.height > ctx.maxHeight){
			return false
		}
		return true
	}
}


///// 布局上下文
//class LayoutCtx {
	////宿主
	////Node *host = null
   
	////约束
	//float minWidth = .0f
	//float minHeight = 0.f
	//float maxWidth = infinity 
	//float maxHeight = infinity 

	////期望的宽高
	////满足最小最大尺寸约束后，可选的宽高还是有很多
	////可以使用内容宽高，也可以使用期望宽高
	//float desiredWidth = nan
	//float desiredHeight = nan

	////结果
	////注意：此处的矩形信息都是不考虑margin, padding, border啥的。 margin,padding/border都是视图内部概念。 不影响布局
	////布局是很清晰简洁的 传递约束，计算尺寸和位置。
	////这里的width就是布局矩形的尺寸，无关其他概念。对于div,就是outbox的尺寸
	//float x = 0.f;
	//float y = 0.f;
	//float width = 0.f;
	//float height = 0.f; 

	//List@ layoutCells = new List()
 
	//LayoutCell* getLayoutCellByType(Vtable_Object* vt){

		//for (int i = 0; i < self.layoutCells.size(); i++){
			//Object *cell = self.layoutCells.get(i);
			//if (cell instanceof vt){
				//return cell;
			//}
		//}
		//return null
	//}

	//void copyConstraints(LayoutCtx* ctx){
		//self.copyWidthConstraint(ctx);
		//self.copyHeightConstraint(ctx);
	//}
	//void copyMaxConstraints(LayoutCtx* ctx){
		//self.maxHeight = ctx->maxHeight;
		//self.maxWidth = ctx->maxWidth;
	//}
	//void copyMinConstraints(LayoutCtx* ctx){
		//self.minHeight = ctx->minHeight;
		//self.minWidth = ctx->minWidth;
	//}
	//void setMinConstraints(float w, float h){
		//self.minWidth = w;
		//self.minHeight = h;
	//}
	//void setMaxConstraints( float w, float h){
		//self.maxWidth = w;
		//self.maxHeight = h;
	//}
	//void setMinWidth(float minV){ 
		//self.minWidth = maxFloat(0.f, minV)
	//}
	//void setMinHeight(float minV){
		//self.minHeight = maxFloat(0.f, minV);
	//}
	//void setWidthConstraint(float minv, float maxv){
		//self.minWidth = minv;
		//self.maxWidth = maxv;
	//}
	//void setHeightConstraint(float minv, float maxv){
		//self.minHeight = minv;
		//self.maxHeight = maxv;
	//}
	//void clampTightWidthConstraint(float v){
		//v = clampFloat(v, self.minWidth, self.maxWidth);
		//self.minWidth = maxFloat(self.minWidth, v);
		//self.maxWidth = minFloat(self.maxWidth, v);
	//}
	//void clampTightHeightConstraint(float v){
		//v = clampFloat(v, self.minHeight, self.maxHeight);
		//self.minHeight = maxFloat(self.minHeight, v);
		//self.maxHeight = minFloat(self.maxHeight, v);
	//}
	//void plusWidthConstraint(float minW, float maxW){
		//if (self.minWidth < minW) {
			//self.minWidth = minFloat(minW, self.maxWidth);
		//}
		//if (maxW < self.maxWidth) {
			//self.maxWidth = maxFloat(maxW, self.minWidth);
		//}
		//self.minWidth = minFloat(self.minWidth, self.maxWidth);
	//}
	//void plusHeightConstraint(float minW, float maxW){
		//if (self.minHeight < minW) {
			//self.minHeight = minFloat(minW, self.maxHeight);
		//}
		//if (maxW < self.maxHeight) {
			//self.maxHeight = maxFloat(maxW, self.minHeight);
		//}

		//self.minHeight = minFloat(self.minHeight, self.maxHeight);
	//}
	//void plusConstraints(float minW, float maxW, float minH, float maxH){
		//self.plusWidthConstraint(minW, maxW);
		//self.plusHeightConstraint(minH, maxH);
	//}
	//void clampWidth(float v, float minW, float maxW){
		//self.width = clampFloat(v, maxFloat(minW, self.minWidth), minFloat(maxW, self.maxWidth));
	//}
	//void clampHeight(float v, float minW, float maxW){
		//self.height = clampFloat(v, maxFloat(minW, self.minHeight), minFloat(maxW, self.maxHeight));
	//}
	//void setSize(float w, float h){
		//self.width = clampFloat(w, self.minWidth, self.maxWidth);
		//self.height = clampFloat(h, self.minHeight, self.maxHeight);
	//}
	//Vec2 getSize(){
		//return mkVec2(self.width, self.height);
	//}
	//void setWidth(float w){
		//self.width = clampFloat(w, self.minWidth, self.maxWidth);
	//}
	//void setHeight(float h){
		//self->height = clampFloat(h, self->minHeight, self->maxHeight);
	//}
	//void setRect(float x, float y, float w, float h){
		//self->x = x;
		//self->y = y;
		//self->setSize(w, h);
	//}
	//void setPosition(float x, float y){
		//self->x = x;
		//self->y = y;
	//}
	//float getBottom(){
		//return self.y + self.height;
	//}
	//float getRight(){
		//return self.x + self.width;
	//}
	////如果宽或者高的最小、最大限死了，就可以直接得出具体的宽高值
	//bool setSize_ifAnyTight(){
		//bool ret = false;
		//if (self.isTightWidth()) {
			//self.width = self.minWidth;
			//ret = true;
		//}
		//if (self.isTightHeight()) {
			//self.height = self.minHeight;
			//ret = true;
		//}
		//return ret;
	//}
	//bool setSize_ifTight(){
		//if (self.isTight()) {
			//self.width = self.minWidth;
			//self.height = self.minHeight;
			//return true;
		//}
		//return false;
	//}

	//void copyWidthConstraint(LayoutCtx* ctx){
		//self.minWidth = ctx->minWidth;
		//self.maxWidth = ctx->maxWidth;
	//}
	//void copyHeightConstraint(LayoutCtx* ctx){
		//self.minHeight = ctx->minHeight;
		//self.maxHeight = ctx->maxHeight;
	//}
	//void setTightWidth(float w){
		//self.width = self.minWidth = self.maxWidth = w; 
	//}
	//void setTightHeight(float h){
		//self.height = self.minHeight = self.maxHeight = h;
	//}
	//void setTight(float w, float h){
		//self.width = self.minWidth = self.maxWidth = w;
		//self.height = self.minHeight = self.maxHeight = h; 
	//}
	//bool isTightWidth(){
		//return  self.minWidth == self.maxWidth;
	//} 
	//bool isTightHeight(){
		//return self.minHeight == self.maxHeight;
	//}
	//bool isTight(){
		//return self.minWidth == self.maxWidth && self.minHeight == self.maxHeight;
	//}
	//bool isLoose(){
		//return !self.isTight();
	//}


//}