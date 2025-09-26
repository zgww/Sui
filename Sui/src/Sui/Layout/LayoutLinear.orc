package SuiLayout

#include <stdio.h>
import * from "../Core/ViewBase.orc"
import * from "../Core/Node.orc"
import * from "../Core/View.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Inset.orc"
import * from "../Core/Frame.orc"
import * from "../Core/LayoutCell.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/List.orc"
import * from "../View/ViewBuilder.orc"


class LayoutLinearCell extends LayoutCell {
	float grow = 1.f //默认1
	String@ alignSelf = str("")
}

/// 布局上下文
class LayoutLinear extends View {
	// void dtor(){
	// 	printf("~LayoutLinear:%p\n", self);
	// }

	bool isMax_in_maxOrStretch(Frame *ctx, bool isHor){
		//auto isHor = calcIsHor();
		if (self.alignItems.equals("maxOrStretch")) { //maxOrStretch中的max模式. 不需要二次布局
			if (isHor && ctx->maxHeight != infinity) {
				return true;
			}
			if (!isHor && ctx->maxWidth != infinity) {
				return true;
			}
		}
		return false; 
	}
	void layoutCross(Frame* ctx){
		
		bool isHor = self.calcIsHor();
		bool isStretch = self.alignItems.equals("stretch") || self.alignItems .equals( "maxOrStretch" );

		if (self.isMax_in_maxOrStretch(ctx, isHor)) { //maxOrStretch中的max模式. 不需要二次布局
			return;
		}

		for (int i = 0; i < self.getChildrenCount(); i++) {
			ViewBase* view = self.getChildAsView(i);
			if (view && view->canLayoutByParent()) {

				LayoutLinearCell* cell = (LayoutLinearCell*)view->getLayoutCellByType(LayoutLinearCell);
				bool isKidStretch = false 
				
				if (cell != null && cell->alignSelf .notEquals( "" )){
					isKidStretch = cell->alignSelf.equals("stretch")	
				}  else {
					isKidStretch = isStretch
				}  

				if (isKidStretch) {
					Frame* kidCtx = &view->frame;

					if (isHor) {
						if (kidCtx.height == ctx->height) { //侧轴同长，没必要再layout了
							continue;
						}
						kidCtx.setTightWidth(kidCtx.width); //主轴固定了

						kidCtx.maxHeight = ctx->height;
						//if (isKidStretch) { //强制侧轴长
							kidCtx.minHeight = kidCtx.maxHeight;
						//}
					}
					else { 
						if (kidCtx.width == ctx->width) { //侧轴同长，没必要再layout了
							continue;
						}
 
						kidCtx.setTightHeight(kidCtx.height); //主轴固定了


						kidCtx.maxWidth = ctx->width;
						//if (isKidStretch) { //强制侧轴长
							kidCtx.minWidth = kidCtx.maxWidth;
						//}
					}
			
					//kidCtx.setSize_ifAnyTight();
					//auto oldSize = kidCtx.getSize();
					view->layout(kidCtx);
					if (0) {
						printf("haha\n");
					}
					//if (oldSize != kidCtx.getSize()) {//尺寸有变化
					//}
				}
			}
		}
	}
	bool calcIsHor(){
		bool isHor = self.direction .equals( "row") || self.direction .equals("row-reverse");
		return isHor;
	}
	String* getCrossAlign_ofKid(ViewBase *view){
		if (view) {
			LayoutLinearCell* cell =  (LayoutLinearCell*)view->getLayoutCellByType(LayoutLinearCell);
			if (cell && !cell->alignSelf.empty()) {
				return cell->alignSelf;
			} 
		}
		return self.alignItems; 
	}
	void positionChildren(Frame *ctx){

		bool isHor = self.calcIsHor();
		float crossPos = 0.f;
		float width = ctx->width;
		float height = ctx->height;
		float sumMainSize = 0.f;
		int viewCount = self.getChildrenViewCount();
		int l = self.getChildrenCount()
		for (int i = 0; i < l; i++) {
			ViewBase* v = self.getChildAsView(i);
			if (v && v->canLayoutByParent()) {//要可见
				float addSize = 0.f;
				if (isHor){
					addSize = v->frame.width
				} else {
					addSize = v->frame.height
				}
				sumMainSize = sumMainSize + addSize;
			}
		}
		// Rect contentRect = self.getContentRect_baseViewRect();//注意此处取得宽高是无意义的。因为不是由ctx算出来的
		float idleSpace = ctx->width  - sumMainSize;
		if (!isHor){
			idleSpace = ctx->height - sumMainSize;
		}
		float mainPos = 0.f;
		

		float delta = 0.f;
		if (self.justifyContent .equals( "center") ) {
			mainPos = mainPos + idleSpace / 2.f;
		}
		else if (self.justifyContent .equals( "end") ) {
			mainPos = mainPos + idleSpace;
		}
		else if (self.justifyContent  .equals( "space-between")) {
			if (viewCount > 1){
				delta = idleSpace / (viewCount - 1) 
			} else {
				delta = 0.f
			}
			delta = maxFloat(0.f, delta);
		}
		else if (self.justifyContent  .equals(  "space-around")) {//前后只有一半
			if (viewCount > 0){
				delta = idleSpace / (viewCount) ;
			} else {
				delta = 0.f;
			}
			delta = maxFloat(0.f, delta);
			mainPos = mainPos + delta / 2.f;
		}
		else if (self.justifyContent  .equals( "space-evenly")) {
			delta = idleSpace / (viewCount + 1);
			delta = maxFloat(0.f, delta);
			mainPos = mainPos + delta;
		}
		bool isReverse = self.direction  .equals(  "row-reverse") || self.direction  .equals(  "column-reverse");
		int len = self.getChildrenCount();

		if (isHor) { //水平
			mainPos = mainPos;//不用再额外考虑padding/border的偏移// + contentRect.x;  //相对于内容区原点。

			for (int i = 0; i < len; i++) {
				int idx = i
				if (isReverse){
					idx = len - i ;//处理reverse
				}
				ViewBase* view = self.getChildAsView(idx);
				if (view) {
					LayoutLinearCell* cell = (LayoutLinearCell*)view->getLayoutCellByType(LayoutLinearCell);
					String * crossAlign = self.getCrossAlign_ofKid(view);
 

					view->frame.x = mainPos;
					mainPos = mainPos + view->frame.width + delta;
					if (crossAlign .equals( "start")) {
						view->frame.y = 0.f;// + contentRect.y;
					}
					else if (crossAlign  .equals( "center")) {
						view->frame.y = (height - view->frame.height) / 2.0f;// + contentRect.y;
					}
					else if (crossAlign  .equals( "end")) {
						view->frame.y = (height - view->frame.height) ;//+ contentRect.y;
					}
					else if (crossAlign  .equals( "stretch")) {
						view->frame.y = 0.f ;//+ contentRect.y;
					}
					// view->layoutCtx.x = view->layoutCtx.x + self.margin.left;
					// view->layoutCtx.y = view->layoutCtx.y + self.margin.top;
				}
			}
		}

		else { //垂直
			mainPos = mainPos;// 不用再额外考虑padding/border //+ contentRect.y;  //相对于内容区原点。
			for (int i = 0; i < len; i++) {
				int idx = isReverse ? len - i : i; //处理reverse
				ViewBase* view = self.getChildAsView(idx);
				if (view) {
					LayoutLinearCell* cell =  (LayoutLinearCell*)view->getLayoutCellByType(LayoutLinearCell);
					String* crossAlign = self.getCrossAlign_ofKid(view);

					view->frame.y = mainPos;
					mainPos = mainPos + view->frame.height + delta;
					if (crossAlign .equals( "start") ){
						view->frame.x = 0.f ;//+ contentRect.x;
					}
					else if (crossAlign .equals( "center")) {
						view->frame.x = (width - view->frame.width) / 2.0f ;//+ contentRect.x;
					}
					else if (crossAlign .equals( "start") ) {
						view->frame.x = (width - view->frame.width) ;//+ contentRect.x;
					}
					else if (crossAlign .equals( "stretch") ) {
						view->frame.x = 0.f ;//+ contentRect.x;
					}
					else {
						view->frame.x = 0.f;
					}
					// view->layoutCtx.x = view->layoutCtx.x + self.margin.left;
					// view->layoutCtx.y = view->layoutCtx.y + self.margin.top;
				}
			}
		}
	}
	void setMainConstraints(Frame * kidCtx, bool isHor, float minV, float maxV){
		if (isHor) {
			kidCtx.minWidth = minV;
			kidCtx.maxWidth = maxV;
		}
		else {
			kidCtx.minHeight = minV;
			kidCtx.maxHeight = maxV;
		}
	}
	void setCrossConstraints(Frame* kidCtx, bool isHor, float minV, float maxV){
		if (!isHor) {
			kidCtx.minWidth = minV;
			kidCtx.maxWidth = maxV;
		}
		else {
			kidCtx.minHeight = 0.f;
			kidCtx.maxHeight = maxV;
		}
	}
	float getMainMaxConstraint(Frame* kidCtx, bool isHor){
		if (isHor) {
			return kidCtx.maxWidth;
		}
		return kidCtx.maxHeight;
	}
	float getCrossMaxConstraint(Frame* kidCtx, bool isHor){
		if (!isHor) {
			return kidCtx.maxWidth;
		}
		return kidCtx.maxHeight;
	}
	void update_maxCrossSize(Frame* kidCtx, bool isHor){
		if (isHor) {
			//plainMainSum += kidCtx.width;
			self.maxCrossSize = maxFloat(kidCtx.height, self.maxCrossSize);
		}
		else {
			//plainMainSum += kidCtx.height;
			self.maxCrossSize = maxFloat(kidCtx.width, self.maxCrossSize);
		}
	}
	bool layout_mainInf(Frame* ctx){

		bool isHor = self.calcIsHor();
		bool isMainInf = isHor ? ctx->maxWidth == infinity : ctx->maxHeight == infinity;
		bool isCrossInf = !isHor ? ctx->maxWidth == infinity : ctx->maxHeight == infinity;
		if (!isMainInf) {
			return false;
		}
		float mainSize = 0.f;
		//侧轴约束
		float crossMinContraints = 0.f;
		if (self.isMax_in_maxOrStretch(ctx, isHor)) { //侧轴为max模式
			crossMinContraints = self.getCrossMaxConstraint(ctx, isHor);
		}


		for (int i = 0; i < self.getChildrenCount(); i++) {
			ViewBase *view = self.getChildAsView(i);
			if (view && view->canLayoutByParent()) {
				LayoutLinearCell* cell = (LayoutLinearCell*)view->getLayoutCellByType(LayoutLinearCell);

				Frame* kidCtx = &view->frame;
				self.setMainConstraints(kidCtx, isHor, 0.f, INFINITY);
				self.setCrossConstraints(kidCtx, isHor, crossMinContraints, self.getCrossMaxConstraint(ctx, isHor));
				view->layout(kidCtx);

				mainSize = mainSize + (isHor ? kidCtx.width : kidCtx.height);
				self.update_maxCrossSize(kidCtx, isHor);
			}
		}

		//确定尺寸
		ctx->clampWidth(isHor ? mainSize : self.maxCrossSize, self->minWidth, self->maxWidth);
		ctx->clampHeight(!isHor ? mainSize : self.maxCrossSize, self->minHeight, self->maxHeight);

		//确定自身的尺寸
		//updateLayoutCtx_byContentCtx(fullctx, ctx);

		//定位子视图集
		self.positionChildren(ctx);

		//侧轴根据需要，再次布局；要在ctx确定了侧轴尺寸之后
		self.layoutCross(ctx);

		return true;
	}
	bool layout_mainLimit(Frame* ctx){
		bool isHor = self.calcIsHor();
		float maxMain = isHor ? ctx->maxWidth : ctx->maxHeight;

		// List@ growNodes = new List(); //自适应的nodes
		PointerArray@ growNodes = new PointerArray(); //自适应的nodes

		float sumGrow = 0.f;//总权重 
		float plainMainSum = 0.f; //非grow的主轴合长

		//侧轴约束
		float crossMinContraints = 0.f;
		if (self.isMax_in_maxOrStretch(ctx, isHor)) { //侧轴为max模式
			crossMinContraints = self.getCrossMaxConstraint(ctx, isHor);
		}

		for (int i = 0; i < self.getChildrenCount(); i++) {
			ViewBase* view = self.getChildAsView(i);
			if (view && view->canLayoutByParent()) {
				LayoutLinearCell* cell = (LayoutLinearCell*)view->getLayoutCellByType(LayoutLinearCell);

				if (cell) {
					if (cell->grow > 0.f) {
						sumGrow = sumGrow + cell->grow;
						growNodes.add((Object*)view);
						continue;
					}
				}

				Frame* kidCtx = &view->frame;
				self.setMainConstraints(kidCtx, isHor, 0.f, infinity);
				self.setCrossConstraints(kidCtx, isHor, crossMinContraints, self.getCrossMaxConstraint(ctx, isHor));
				view->layout(kidCtx);

				plainMainSum = plainMainSum + (isHor ? kidCtx.width : kidCtx.height);

				self.update_maxCrossSize(kidCtx, isHor);
			}
		}
		//动态伸缩的节点，分配空间并布局
		float remainMain = maxMain - plainMainSum;
		for (int i = 0; i < growNodes.size(); i++){
			ViewBase *view = (ViewBase *)growNodes.get(i);
		// for (auto view : growNodes) {

			if (remainMain <= 0) { //空间不足, 直接全部不显示
				if (isHor) {
					view->frame.width = 0.f;
				}
				else {
					view->frame.height = 0.f;
				}
			} 
			else {//按比例均分空间
				LayoutLinearCell* cell = (LayoutLinearCell*)view->getLayoutCellByType(LayoutLinearCell);
				float ratio = cell->grow / sumGrow;
				float mainSpace = remainMain * ratio;
				Frame* kidCtx = &view->frame;
				self.setMainConstraints(kidCtx, isHor, mainSpace, mainSpace);
				self.setCrossConstraints(kidCtx, isHor, crossMinContraints, self.getCrossMaxConstraint(ctx, isHor));
				view->layout(kidCtx);
				self.update_maxCrossSize(kidCtx, isHor);
			}
		}


		//确定主轴使用空间
		float mainSize = growNodes.size() > 0 ? maxMain : plainMainSum;
		//确定内容尺寸
		ctx->width = clampFloat(isHor ? mainSize : self.maxCrossSize, ctx->minWidth, ctx->maxWidth);
		ctx->height = clampFloat(!isHor ? mainSize : self.maxCrossSize, ctx->minHeight, ctx->maxHeight);

		//定位子视图集
		self.positionChildren(ctx);

		//侧轴根据需要，再次布局，要在ctx确定侧轴尺寸后
		self.layoutCross(ctx);

		//按内容尺寸确定自身的尺寸
		//updateLayoutCtx_byContentCtx(fullctx, ctx);

		return true;
	}

	void layoutContent(Frame* ctx) {
		if (self.layout_mainInf(ctx)) { //主轴无限长
			return;
		}
		//主轴有限长
		self.layout_mainLimit(ctx);
	}
	
	/// 朝向 row|column|row-reverse|column-reverse
	String@ direction = str("row");

	//start|end|center|space-between|space-around|space-evenly
	String@ justifyContent = str("start");
	//start|end|center|stretch|maxOrStretch
    //maxOrStretch：如果侧轴最大约束不是INFINITY,就直接使用侧轴最大约束，否则跟stretch一样
	String@ alignItems = str("center");

	LayoutLinear* jcc(){
		self.justifyContent.set("center")
		return self
	}
	LayoutLinear* jcs(){
		self.justifyContent.set("start")
		return self
	}
	LayoutLinear* jce(){
		self.justifyContent.set("end")
		return self
	}
	LayoutLinear* jcsb(){
		self.justifyContent.set("space-between")
		return self
	}
	LayoutLinear* jcsa(){
		self.justifyContent.set("space-around")
		return self
	}
	LayoutLinear* jcse(){
		self.justifyContent.set("space-evenly")
		return self
	}
	LayoutLinear* ais(){
		self.alignItems.set("start")
		return self
	}
	LayoutLinear* aic(){
		self.alignItems.set("center")
		return self
	}
	LayoutLinear* aie(){
		self.alignItems.set("end")
		return self
	}
	LayoutLinear* aiStretch(){
		self.alignItems.set("stretch")
		return self
	}
	LayoutLinear* aiMaxOrStretch(){
		self.alignItems.set("maxOrStretch")
		return self
	}

	LayoutLinear* column(){
		self.direction.set("column")
		return self
	}
	LayoutLinear* row(){
		self.direction.set("row")
		return self
	}
	void layout(Frame *ctx) {
		//自身如果有配置width/height，则需要调整为tight约束
		// self.updateFrame_forSelfWidthHeight(ctx);
		// ctx->setSize_ifAnyTight();

		// if (self.callCbLayout(ctx)) {
		// 	return;
		// }

		self.maxCrossSize = 0.f; //侧轴最大长
		super.layout(ctx)

		//layoutContent(ctx);
		// self.performLayout(ctx);
	}

	float maxCrossSize = 0.f; //侧轴最大长
}



LayoutLinear@ layoutLinear(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (LayoutLinear@)gocNode(sp, (Node*)parent, LayoutLinear)
}
LayoutLinearCell@ layoutLinearCell(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (LayoutLinearCell@)gocNode(sp, (Node*)parent, LayoutLinearCell)
}

