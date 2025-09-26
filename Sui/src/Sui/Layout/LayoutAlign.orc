package SuiLayout
#include <stdio.h>

import * from "../Core/ViewBase.orc"
import * from "../Core/Node.orc"
import * from "../Core/View.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Vec2.orc"
import * from "../Core/Inset.orc"
import * from "../Core/Frame.orc"
import * from "../Core/LayoutCell.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/List.orc"
import * from "../View/ViewBuilder.orc"

//使用定位来决定size
//适合size依赖父视图的情况
class LayoutAlignPositionCell extends LayoutCell {
    float left = 0
    float top = 0
    float right = nan
    float bottom = nan
}
//适合size固定，或者使用contentSize
class LayoutAlignCell extends LayoutCell {
    //锚点， 0-1, 表示 子view的指定位置
    Vec2 anchor = mkVec2(0, 0);
    //对齐，0-1, 表示 LayoutAlign的指定位置
    Vec2 align = mkVec2(0, 0);

    Vec2 sizeRatio = mkVec2(nan, nan)

    void setSameRatio(float x, float y){
        self.anchor.x = x
        self.anchor.y = y
        self.align.x = x
        self.align.y = y
    }

    //9宫格位置
    void setTopLeft(){
        self.setSameRatio(0.0, 0.0)
    }
    void setTopCenter(){
        self.setSameRatio(0.5, 0.0)
    }
    void setTopRight(){
        self.setSameRatio(1.0, 0.0)
    }

    void setBottomLeft(){
        self.setSameRatio(0.0, 1.0)
    }
    void setBottomCenter(){
        self.setSameRatio(0.5, 1.0)
    }
    void setBottomRight(){
        self.setSameRatio(1.0, 1.0)
    }

    void setMiddleLeft(){
        self.setSameRatio(0.0, 0.5)
    }
    void setCenter(){
        self.setSameRatio(0.5, 0.5)
    }
    void setMiddleRight(){
        self.setSameRatio(1.0, 0.5)
    }

}

//让子view的锚点位置对到LayoutAlign的align位置
class LayoutAlign extends View {
    //这是基础配置，各个子view也可以通过LayoutAlignCell指定
    Vec2 anchor = mkVec2(0, 0);
    Vec2 align = mkVec2(0, 0);
    bool useMaxConstraint = true;

    void setSameRatio(float x, float y){
        self.anchor.x = x
        self.anchor.y = y
        self.align.x = x
        self.align.y = y
    }

    //9宫格位置
    void setTopLeft(){
        self.setSameRatio(0.0, 0.0)
    }
    void setTopCenter(){
        self.setSameRatio(0.5, 0.0)
    }
    void setTopRight(){
        self.setSameRatio(1.0, 0.0)
    }

    void setBottomLeft(){
        self.setSameRatio(0.0, 1.0)
    }
    void setBottomCenter(){
        self.setSameRatio(0.5, 1.0)
    }
    void setBottomRight(){
        self.setSameRatio(1.0, 1.0)
    }

    void setMiddleLeft(){
        self.setSameRatio(0.0, 0.5)
    }
    void setCenter(){
        self.setSameRatio(0.5, 0.5)
    }
    void setMiddleRight(){
        self.setSameRatio(1.0, 0.5)
    }


    void layoutContent(Frame *ctx){
        float maxWidth = 0
        float maxHeight = 0
        int l = self.getChildrenCount()
        //确认宽高
		for (int i = 0; i < l; i++) {
			ViewBase* view = self.getChildAsView(i);
			if (view && view->canLayoutByParent()) {
				// LayoutAlignCell* cell = (LayoutAlignCell*)view->getChildByType(LayoutAlignCell);
				LayoutCell* cell = (LayoutCell*)view->getChildByType(LayoutCell);

                if (cell instanceof LayoutAlignPositionCell){
                } 
                else  {
                // if (cell instanceof LayoutAlignCell){
                    if self.useMaxConstraint {
                        view.frame.copyMaxConstraints(ctx)
                    }
                    if cell instanceof LayoutAlignCell {
                        LayoutAlignCell * ac = (LayoutAlignCell*) cell
                        //宽度按比例直接定死
                        if !isNaN(ac.sizeRatio.x){
                            view.frame.setTightWidth(ctx.width * ac.sizeRatio.x)
                        }
                        if !isNaN(ac.sizeRatio.y){
                            view.frame.setTightHeight(ctx.height * ac.sizeRatio.y)
                        }
                    }

                    view.layout(&view.frame);

                    maxWidth = maxFloat(maxWidth, view.frame.width)
                    maxHeight = maxFloat(maxHeight, view.frame.height)
                }
            }
        }
        //在约束下设置size.这句话是为了在不明确size的情况下，采用最大的子节点的size作为size
        ctx.setSize(maxWidth, maxHeight)
        l = self.getChildrenCount()
        //定位
		for (int i = 0 ; i < l; i++) {
			ViewBase* view = self.getChildAsView(i);
			if (view && view->canLayoutByParent()) {
				LayoutCell* cell = (LayoutCell*)view->getChildByType(LayoutCell);

                // positionCell需要在父视图size已知时去做布局和定位
                if (cell instanceof LayoutAlignPositionCell){
                    LayoutAlignPositionCell* pcell = (LayoutAlignPositionCell*)cell;

                    view.frame.reset()
                    // view.frame.copyMaxConstraints(ctx)

                    //限定了宽
                    if (!isNaN(pcell.left ) && !isNaN(pcell.right)){
                        float w = ctx.width - pcell.left - pcell.right
                        view.frame.setWidthConstraint(w, w)
                    }
                    //限定了高
                    if (!isNaN(pcell.top ) && !isNaN(pcell.bottom)){
                        float h = ctx.height - pcell.top - pcell.bottom
                        view.frame.setHeightConstraint(h, h)
                    }

                    view.layout(&view.frame);

                    //定位
                    if (!isNaN(pcell.left)){
                        view.frame.x = pcell.left
                    }
                    if (!isNaN(pcell.top)){
                        view.frame.y = pcell.top
                    }
                    if (!isNaN(pcell.right)){
                        view.frame.x = ctx.width - pcell.right - view.frame.width
                    }
                    if (!isNaN(pcell.bottom)){
                        view.frame.y = ctx.height - pcell.bottom - view.frame.height
                    }
                }
                else {
                    Vec2 anchor ;
                    Vec2 align ;
                    self.getAnchorAndAlign_byView(view, &anchor, &align)
                    //计算位置
                    view.frame.x = ctx.width * align.x - view.frame.width * anchor.x;
                    view.frame.y = ctx.height * align.y - view.frame.height * anchor.y;
                }
            }
        }
    }
    void getAnchorAndAlign_byView(ViewBase *view, Vec2 *anchor, Vec2 *align){
        LayoutAlignCell* cell = (LayoutAlignCell*)view->getChildByType(LayoutAlignCell);
        if (cell != null){
            *anchor = cell.anchor;
            *align = cell.align;
        } else {
            *anchor = self.anchor;
            *align = self.align;
        }
    }
}



LayoutAlign@ layoutAlign(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (LayoutAlign@)gocNode(sp, (Node*)parent, LayoutAlign)
}

LayoutAlignCell@ layoutAlignCell(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (LayoutAlignCell@)gocNode(sp, (Node*)parent, LayoutAlignCell)
}
LayoutAlignPositionCell@ layoutAlignPositionCell(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (LayoutAlignPositionCell@)gocNode(sp, (Node*)parent, LayoutAlignPositionCell)
}