package SuiLayout
#include <stdio.h>
#include "../../Orc/Orc.h"

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


/// 布局上下文
class RowWrap extends View {
	void alignItems_ofRow(int rowStartIdx, int rowEndIdx, float rowHeight){
		if (self.alignItems .equals("start")) {
			return;
		}
		bool center = self.alignItems .equals( "center");
		bool end = self.alignItems .equals( "end");

		for (int i = rowStartIdx; i < rowEndIdx; i++) {
			ViewBase* view = self->getChildAsView(i);
			if (view && view->canLayoutByParent()) {
				if (center) {
					view->frame.y = view->frame.y + (rowHeight - view->frame.height) / 2.f;
				} else if (end){
					view->frame.y = view->frame.y + (rowHeight - view->frame.height);
				}
			}
		}
	}
	void positionChildren(Frame*ctx) {
		Rect contentRect = self.getContentLocalRect();//注意此处取得宽高是无意义的。因为不是由ctx算出来的
		float x = 0.f;
		float y = 0.f;

		float rowHeight = 0.f;
		float rowStartIdx = 0;
		float maxWidth = 0.f;

		for (int i = 0; i < self.getChildrenCount(); i++) {
			ViewBase* view = self->getChildAsView(i);
			if (view && view->canLayoutByParent()) {
				Frame* lc = &view->frame;

				if (x + lc.width > ctx->maxWidth) {//加上此项后，行宽超限

					self.alignItems_ofRow(rowStartIdx, i, rowHeight);
					//新行
					y = y + rowHeight + self.rowGap;
					x = 0.f;

					rowStartIdx = i;
					rowHeight = 0.f;
				}

				lc.x = x + contentRect.x; //+内容区的偏移
				lc.y = y + contentRect.y;
				x = x + lc.width + self.colGap;

				maxWidth = maxFloat(x, maxWidth);
				rowHeight = maxFloat(rowHeight, lc.height);
			}
		}
		//最后一行
		self.alignItems_ofRow(rowStartIdx, self.getChildrenCount(), rowHeight);

		//可以确认ctx的宽和高了
		ctx->setSize(
			maxWidth, y + rowHeight
		);
	}
	void layoutContent(Frame*contentCtx) {
		for (int i = 0; i < self.getChildrenCount(); i++) {
			ViewBase* view = self->getChildAsView(i);
			if (view && view->canLayoutByParent()) {
				//无约束布局
				Frame* kidCtx = &view->frame;
				kidCtx.maxWidth = infinity;
				kidCtx.maxHeight = infinity;
				view->layout(kidCtx);
			}
		}
		self.positionChildren(contentCtx);
	}
	
	//start|end|center
	String@ alignItems = str("center");

	//行间距
	float rowGap = 0.f;
	//列间距
	float colGap = 0.f;
}
RowWrap@ mkRowWrap(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (RowWrap@)gocNode(sp, (Node*)parent, RowWrap)
}
