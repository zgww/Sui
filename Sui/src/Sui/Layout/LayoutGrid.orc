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


class refc LayoutGridItem{
	ViewBase* view;
    int col
    int row
    int rowSpan
    int colSpan
    float width = 0.f//宽度
    float x = 0.f
    //对于wrapHeight模式，此布局会确保空间足够。 所有第一次布局计算出每行各个item的期望高度
    //第二次布局，拉伸每个item的高度去匹配每行的最高度，再次布局
    float desiredHeight = 0.f //第一次布局出来的期望的高度
}
class LayoutGridRowInfo{
    float height = 0.f
    float y = 0.f
}
 
class LayoutGridOccupyCell {
    bool occupy = 0 //占据
    float desiredHeight = 0.f //期望高
    int restRowSpan = 0 //后面还有几行，跟此单元格归属同一个视图单元
}


class LayoutGridCell extends LayoutCell {
	int colSpan = 1
	int rowSpan = 1
}  
  

/// 布局上下文
class LayoutGrid extends View {
	void layout(Frame* ctx){
		self.updateFrame_forSelfWidthHeight(ctx)
		self.initLayoutSize(ctx)

		//非tight不布局
		if (!ctx->isTightWidth()) {
			return;
		}
		if (self.rowCount > 0 && !ctx->isTightHeight()) {
			return;
		}
  
		//layoutContent(ctx);
		super.layout(ctx);
	}
	void resetOccupyGrid(){
		int l = self.occupyGrid.size()
		for (int i = 0; i < l; i++) {
			LayoutGridOccupyCell *ele = (LayoutGridOccupyCell*)self.occupyGrid.get(i)
			ele.occupy = 0;
		}
	}
	void extendOccupyGrid(int row, bool erase){
		int cnt = row * self.colCount;
		if (cnt > self.occupyGrid.size()) {
			for (int i = self.occupyGrid.size(); i < cnt; i++) {
				LayoutGridOccupyCell @cell = new LayoutGridOccupyCell()
				self.occupyGrid.add((Object*)cell);
			}
		}
		else if (erase && cnt < self.occupyGrid.size()) {
			self.occupyGrid.removeFromStart(cnt)
			// occupyGrid.erase(occupyGrid.begin() + cnt, occupyGrid.end());
		}
	}
	void occupy(int _c, int _r, int colSpan, int rowSpan){
		for (int r = 0; r < rowSpan; r++) {
			for (int c = 0; c < colSpan; c++) {
				int posR = r + _r;
				int posC = c + _c;
				int idx = posR * self.colCount + posC;
				LayoutGridOccupyCell *cell = (LayoutGridOccupyCell*)self.occupyGrid.get(idx)
				cell.occupy = 1;
			}
		}
	}
	bool checkFreeSpace(int _c, int _r, int colSpan, int rowSpan){
		int gridRowCount = self.occupyGrid.size() / self.colCount;
		for (int r = 0; r < rowSpan; r++) {
			for (int c = 0; c < colSpan; c++) {
				int posR = r + _r;
				int posC = c + _c;
				//越界
				if (posR >= gridRowCount || posC >= self.colCount) {
					return false;
				}
				int idx = posR * self.colCount + posC;
				LayoutGridOccupyCell *cell = (LayoutGridOccupyCell*)self.occupyGrid.get(idx)
				int occupy = cell.occupy;
				if (occupy) {
					return false;
				}
			}
		}
		return true;
	}
	bool findNextAvailableGridPos(int _c, int _r, int colSpan, int rowSpan, int *outC, int* outR){
		int c = _c;
		for (int ri = 0; true; ri++) {
			int r = ri + _r;
			if (self.rowCount < 1) { //不是固定行的，可以扩展
				self.extendOccupyGrid(r + rowSpan, true);
			}
			else if (r >= self.rowCount) {//有指定行数
				break;
			}

			for (; c < self.colCount; c++) {
				if (self.checkFreeSpace(c, r, colSpan, rowSpan)) {
					*outC = c;
					*outR = r;
					return true; 
				} 
			}
			c = 0;//回到0
		}
		return false;
	}
	void updateOccupyViewInfo(Frame* kidctx, int c, int r, int colSpan, int rowSpan){
		float desiredHeight = (kidctx->height - (rowSpan - 1) * self.rowGap) / rowSpan; //初始值采用均分高度法
		for (int j = 0; j < rowSpan; j++) {
			for (int i = 0; i < colSpan; i++) {
				int idx = (j + r) * self.colCount + c + i;
				LayoutGridOccupyCell *occupy = (LayoutGridOccupyCell*)self.occupyGrid.get(idx)
				occupy.desiredHeight = desiredHeight;
				occupy.restRowSpan = rowSpan - 1 - j; //后面还有几行
			}
		}
	}
	float calcMaxHeight_ofRow(int r){
		float maxHeight = 0.f;
		for (int c = 0; c < self.colCount; c++) {
			int idx = r * self.colCount + c;
			LayoutGridOccupyCell *occupy = (LayoutGridOccupyCell*)self.occupyGrid.get(idx)
			// auto& occupy = occupyGrid[idx];
			maxHeight = maxFloat(maxHeight, occupy.desiredHeight);
		}
		return maxHeight;
	}
	void adjustRestRowsDesiredHeight(int r, float maxHeight){
		for (int c = 0; c < self.colCount; c++) {
			int idx = r * self.colCount + c;
			LayoutGridOccupyCell *occupy = (LayoutGridOccupyCell*)self.occupyGrid.get(idx)
			// auto& occupy = occupyGrid[idx];
			float delta = maxHeight - occupy.desiredHeight; //偏差值。 偏差值由后续均分

			if (delta > 0.001f && occupy.restRowSpan > 0) {
				//均分偏差
				float averDelta = delta / occupy.restRowSpan;
				for (int j = 0; j < occupy.restRowSpan; j++) {
					int restIdx = (r + j + 1) * self.colCount + c;
					LayoutGridOccupyCell *target = (LayoutGridOccupyCell*)self.occupyGrid.get(restIdx)
					target.desiredHeight = maxFloat(0.f, target.desiredHeight - averDelta);
				}
			}

		}
	}
	void layoutContent(Frame* ctx) {
		if (self.colCount < 1) {
			printf("warning: LayoutGrid invalid colCount:%d, rowCount:%d\n", self.colCount, self.rowCount);
			return;
		}
		float colSize = (ctx->width - self.colGap * (self.colCount - 1)) / self.colCount;
		float rowSize = 10.f;
		bool wrapHeight = false; //自适应高度
		if (self->rowSizeRatio > 0.001f) {
			rowSize = colSize * self->rowSizeRatio;
		}
		else if (self->rowSize > 0.001f) {
			rowSize = self->rowSize;
		}
		else if (self.rowCount > 0 && ctx->isTightHeight()){ //高度是紧约束
			rowSize = (ctx->height - self.rowGap * (self.rowCount - 1)) / self.rowCount;
		}
		else {//使用自适应cell高度的方案
			wrapHeight = true;
		}
		
		// std::vector<LayoutGridItem> items;
		// PointerArray@ items = new PointerArray();
		List@ items = new List();

		self.resetOccupyGrid();
		if (self.rowCount > 0) {
			self.extendOccupyGrid(self.rowCount, true);
		}

		//从左到右，从上到下占据
		int c = 0;
		int r = 0;
		int maxRowCount = 0;
		int l = self.getChildrenCount()
		for (int i = 0; i < l; i++) {
			ViewBase* view = self.getChildAsView(i);
			if (view && view->canLayoutByParent()) {

				int colSpan = self->colSpan;
				int rowSpan = self->rowSpan;
				LayoutGridCell* cell = (LayoutGridCell*)view->getChildByType(LayoutGridCell);
				if (cell) {
					colSpan = cell->colSpan;
					rowSpan = cell->rowSpan;
				}
				if (colSpan < 1) {
					colSpan = 1;//处理 无效值
				}
				if (rowSpan < 1) {
					rowSpan = 1;//处理 无效值
				}
				
				if (self.findNextAvailableGridPos(c, r, colSpan, rowSpan, &c, &r)) {
					self.occupy(c, r, colSpan, rowSpan);
					//先收集相关参数
					LayoutGridItem@ item = new LayoutGridItem()
					items.add((Object*)item);
					// auto& item = items.back();
					item.col = c;
					item.row = r;
					item.colSpan = colSpan;
					item.rowSpan = rowSpan;
					item.view = view;
					item.width = colSpan * colSize + (colSpan - 1) * self.colGap;//宽度固定
					item.x = item.col * colSize + (item.col - 1) * self.colGap;//x固定

					//更新occupyGrid信息

					maxRowCount = maxFloat(r + rowSpan, maxRowCount);

					c = c + colSpan;
					//r += rowSpan;
				}
				else {
					view->frame.setTight(0, 0);
				}
			}
		}

		float maxHeight = 0.f;

		if (wrapHeight) {//自适应高度，可能需要2次布局调整
			//记录每行的高度
			// std::vector<LayoutGridRowInfo> rowHeights(maxRowCount, LayoutGridRowInfo{});
			List@ rowHeights = new List()
			for (int i = 0; i < maxRowCount; i++){
				LayoutGridRowInfo @ele = new LayoutGridRowInfo()
				rowHeights.add((Object*)ele)
			}


			for (int i = 0; i < items.size(); i++){
				LayoutGridItem* item = (LayoutGridItem*)items.get(i)
			// for (auto& item : items) {
				ViewBase* view = item.view;
				float colSpan = item.colSpan;
				float rowSpan = item.rowSpan;
				view->frame.setTightWidth(item.width);
				view->frame.setHeightConstraint(0.f, ctx->maxHeight);//传递约束
				//布局子视图
				view->layout(&view->frame);

				item.desiredHeight = view->frame.height;

				//高度由item跨的多行均分
				//TODO可能产生多余的高度。 因为有可能前面的行更高，后面的行就不用再那么高了
				//可以优化为： 将每个单元格的期望高度，期望rowSpan总高度，rowSpan记录到occupyGrid中，
				//从第0行开始遍历： 每行取该行单元格最大高。 同时，对于有rowSpan的，如果该行高大于该单元格高，则降低相应的后续的rowSpan单元格高度（均分)
				//这样，就整体是最优的了。比现有的均分view height要更优
				// 方案2 记录各单元的期望高，后续再整合计算,调整后面行的高度
				self.updateOccupyViewInfo(&view->frame, item.col, item.row, item.colSpan, item.rowSpan);

				// 方案1 直接均分高度,不考虑前面和后面单元格的影响
				//float rowHeight = (view->layoutCtx.height - (rowSpan - 1) * rowGap) / rowSpan;
				//for (int _r = item.row, l = item.row + item.rowSpan; _r < l; _r++) {
				//	rowHeights[_r].height = std::max(rowHeight, rowHeights[_r].height);
				//}
			}
			//根据各单元格，决定各行的高度
			for (int j = 0; j < rowHeights.size(); j++) {
				LayoutGridRowInfo* rowHeight = (LayoutGridRowInfo*) rowHeights.get(j);
				float height = self.calcMaxHeight_ofRow(j);
				rowHeight.height = height;
				//偏差分配到后续的行
				self.adjustRestRowsDesiredHeight(j, height);
			}

			//更新各行的位置
			float y = 0.f;
			for (int j = 0; j < rowHeights.size(); j++) {
				LayoutGridRowInfo* rowHeight = (LayoutGridRowInfo*) rowHeights.get(j);
				rowHeight.y = y;
				y = y + rowHeight.height + self.rowGap;
			}
 
			//二次布局
			for (int i = 0; i < items.size(); i++){
				LayoutGridItem* item = (LayoutGridItem*)items.get(i)
			// for (auto& item : items) {
				float actualHeight = (item.rowSpan - 1) * self.rowGap;//实际的高度
				int l = item.row + item.rowSpan
				for (int _r = item.row; _r < l; _r++) {
					LayoutGridRowInfo* rowHeight = (LayoutGridRowInfo*)rowHeights.get(r);
					actualHeight = actualHeight + rowHeight.height;
				}
				if (actualHeight != item.desiredHeight) {//不同，所以需要重新布局
					item.view->frame.setTight(item.width, actualHeight);
					//布局子视图
					item.view->layout(&item.view->frame);
				}
				
				//定位
				LayoutGridRowInfo* rowHeightOfRow = (LayoutGridRowInfo*)rowHeights.get(item.row);
				item.view->frame.setPosition(
					item.x,
					rowHeightOfRow.y);
				maxHeight = maxFloat(maxHeight, item.view->frame.getBottom());
			}
		}
		else {//高度已知
			for (int i = 0; i < items.size(); i++){
				LayoutGridItem* item = (LayoutGridItem*)items.get(i)

				ViewBase* view = item.view;
				float colSpan = item.colSpan;
				float rowSpan = item.rowSpan;

				view->frame.setTight(
					item.width,
					rowSpan * rowSize + (rowSpan - 1) * self.rowGap);
				//布局子视图
				view->layout(&view->frame);
				//定位
				view->frame.setPosition(
					item.x,
					item.row * rowSize + (item.row - 1) * self.rowGap);
				maxHeight = maxFloat(maxHeight, view->frame.getBottom());
			}
		}
		ctx->setHeight(maxHeight);
	}

	//LayoutGridOccupyCell
    List@ occupyGrid = new List();

	float maxCrossSize = 0.f; //侧轴最大长

	//默认情况下的cell的colSpan/rowSpan。 之所以有这两个字段，是希望单元格可以比默认的格视图更小，
	//从而允许格视图可以占用奇数的单元数.也可以理解为允许格视图占据带小数的单元格
	//允许某一格视图colSpan=1.5之类的。
	int colSpan = 1;
   
	int rowSpan = 1;
    
	int colCount = 3;
    
    //rowSizeRatio/rowSize/rowCount 三者互斥。 对于rowCount,需要tightHeight. 如果3个都是0，则采用适应内容高度的模式
    //对于rowCount,要求高度是紧约束，才能计算出rowSize
    float rowSize = 0.f;
    
    float rowSizeRatio = 0.f;

	int rowCount = 0; //有设置就采用

	//倾向尺寸。直接用width/height即可
	//PROPERTY(g, s) float preferWidth = 200;
	//PROPERTY(g, s) float preferHeight = 200;
	//PROPERTY(g, s) int rowCount = -1; //y轴可以任意增加

    float colGap = 4;
    float rowGap = 4;
}

LayoutGrid@ mkLayoutGrid(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (LayoutGrid@)gocNode(sp, (Node*)parent, LayoutGrid)
}
LayoutGridCell@ mkLayoutGridCell(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (LayoutGridCell@)gocNode(sp, (Node*)parent, LayoutGridCell)
}