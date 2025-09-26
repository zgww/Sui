package SuiCore

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


import * from "./Node.orc"
import * from "./Rect.orc"
import * from "./Frame.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Math.orc"
import * from "./Vec2.orc"
import * from "./Inset.orc"   
import * from "./ViewBase.orc"
import type * from "./Window.orc"
import * from "./BoxShadow.orc"

import * from "./Border.orc"
import * from "./Edge.orc"
import * from "./Radius.orc"
import * from "./Color.orc"
import * from "./Rect.orc"
import * from "./Canvas.orc"

//回调
class ViewCallback {
    bool cbLayout(View *div, Frame *ctx){
        return false
    }
    bool cbDraw(View *div, Canvas *canvas){
        return false
    }
    // 如果返回true,会屏蔽原来的draw_self
    bool cbDrawSelf(View *div, Canvas *canvas){
        return false
    }
    void afterDrawSelf(View *div, Canvas *canvas){
    }
}
/// 布局上下文
class View extends ViewBase {

    Vec2 size = mkVec2(0, 0)
    bool needClip = false

    //这是指view宽高,包括border,padding,content,类似于css的box-sizing: border-box
    float width = nan
    float height = nan

    //期望的宽高，不包括margin
    float desiredWidth = nan
    float desiredHeight = nan

    float minWidth = 0.f
    float maxWidth = infinity
    float minHeight = 0.f
    float maxHeight = infinity

    Border@ border = new Border()
    Radius@ radius = new Radius()
    Inset padding = mkInset0()
    Inset margin = mkInset0()
    BoxShadow@ boxShadow = new BoxShadow()
    int backgroundColor = 0x00000000

    ViewCallback@ cb = NULL;

    //取得视图矩形区的绝对坐标
    Rect getViewRect_baseClient(){
        Rect vr = self.getViewRect()

        Vec2 pos = self.localToWorld(vr.x, vr.y);
        Vec2 sizePos = self.localToWorld(vr.x + vr.w, vr.y + vr.h);
        Vec2 size = sizePos.sub(pos);
  
        return mkRect( pos.x, pos.y, size.x, size.y );
    }   
    //因为View的margin的存在，所以需要改写hitTestSelf
    bool _hitTestSelf(float x, float y){
        Rect r = self.getViewRect_baseClient();
        return self._hitTestClientRect(&r, x, y)
    }

    //外框矩形,坐标相对于父内容区
    Rect getFrameRect(){
        Rect r = mkRect(self.frame.x, self.frame.y, self.frame.width, self.frame.height);
        return r
    }
    //视图区矩形, 不含margin, 相对于自己的frame区
	Rect getViewRect(){
        float w = self.frame.width - self.margin.hor();
        float h = self.frame.height - self.margin.ver();
        return mkRect( 
            (float)self.margin.left, 
            (float)self.margin.top, 
            w, h 
        );
    }
    //内容区矩形， 坐标相对于自己的frame区
	Rect getContentRect(){
        return mkRect( 
            self.margin.left + self.border.l.w + self.padding.left,
            self.margin.top + self.border.t.w + self.padding.top,
            maxFloat(0.f, 
            self.frame.width - self.margin.hor() - self.border.hor() - self.padding.hor()),

            maxFloat(0.f,
            self.frame.height - self.margin.ver() - self.border.ver() - self.padding.ver())
        );
    }

    //取得非内容区的宽高
	Vec2 getNonContentSize(){
        float w = self.margin.hor() + self.border.l.w + self.border.r.w + self.padding.hor();
        float h = self.margin.ver() + self.border.l.w + self.border.r.w + self.padding.ver();
        return mkVec2(w, h );
    }
    //返回从Frame到content的inset
	Inset getInsetOfFrameToContent(){
        float l = self.margin.left + self.border.l.w + self.padding.left
        float t = self.margin.top + self.border.t.w + self.padding.top
        float r = self.margin.right + self.border.r.w + self.padding.right
        float b = self.margin.bottom + self.border.b.w + self.padding.bottom
        return mkInset(t, r, b, l);
    }

    // void dtor(){
    //     printf("~View %p\n", self);
    // }
    Vec2 getSizeWithoutMargin(){
        float w = self.frame.width;
        float h = self.frame.height;
        return mkVec2(
            w - self.margin.hor(),
            h - self.margin.ver()
        )
    }
	float getOutWidth(){
        if (isNaN(self.width)) {
            return nan;
        }
        return self.width + self.margin.hor();
    }
	float getOutHeight(){
        if (isNaN(self.height)) {
            return nan;
        }
        return self.height + self.margin.ver();
    }
	float getOutMinWidth(){
        if (isNaN(self.minWidth)) {
            return nan;
        }
        return self.minWidth + self.margin.hor();
    }
	float getOutMinHeight(){
        if (isNaN(self.minHeight)) {
            return nan;
        }
        return self.minHeight + self.margin.ver();
    }
	float getOutMaxWidth(){
        if (isNaN(self.maxWidth)) {
            return nan;
        }
        return self.maxWidth + self.margin.hor();
    }
	float getOutMaxHeight(){
        if (isNaN(self.maxHeight)) {
            return nan;
        }
        return self.maxHeight + self.margin.ver();
    }
	void updateFrame_forSelfWidthHeight(Frame* ctx){
        //auto ncSize = getNonContentSize();
        float w = self.getOutWidth();
        float h = self.getOutHeight();
        if (!isNaN(w)) {
            ctx->clampTightWidthConstraint(w);
        }
        if (!isNaN(h)) {
            ctx->clampTightHeightConstraint(h);
        }
        ctx->plusConstraints(
            self.getOutMinWidth(), 
            self.getOutMaxWidth(), 
            self.getOutMinHeight(), 
            self.getOutMaxHeight()
        );
    }

    //相对于marignBox
	Rect getContentLocalRect(){
        return mkRect( 
            self.margin.left + self.border.l.w + self.padding.left,
            self.margin.top + self.border.t.w + self.padding.top,
            maxFloat(0.f, 
            self.frame.width - self.margin.hor() - self.border.hor() - self.padding.hor()),

            maxFloat(0.f,
            self.frame.height - self.margin.ver() - self.border.ver() - self.padding.ver())
        );
    }
    //相对于ViewRect,不含margin
	Rect getContentRect_baseViewRect(){
        return mkRect(
            self.border.l.w + self.padding.left,
            self.border.t.w + self.padding.top,
            self.frame.width - self.margin.hor() - self.border.hor() - self.padding.hor(),
            self.frame.height - self.margin.ver() - self.border.ver() - self.padding.ver()
        );
    }
	Vec2 getViewSize(){
        float w = self.frame.width - self.margin.hor();
        float h = self.frame.height - self.margin.ver();
        return mkVec2( w, h );
    }
    // ctx是自身的ctx
	void layoutContent_fromOutBox(Frame* ctx){
        //收缩约束得到contentframe
        Inset inset = self.getInsetOfFrameToContent();
        Frame contentCtx = ctx.inset(inset);

        //执行内容布局
        self.layoutContent(&contentCtx);

        //内容Frame传播给自身Frame
        *ctx = contentCtx.outset(inset);
    }
	void layoutContent(Frame *contentCtx){
        float right = 0.f;
        float bottom = 0.f;
 
        //递归布局
        int  l = self.getChildrenCount()
        for (int i = 0; i < l; i++) {
            ViewBase* v = self.getChildAsView(i);
            if (v) {
                //只复制最大约束
                v.frame.minWidth = 0
                v.frame.minHeight = 0

                v.frame.maxWidth = infinity
                v.frame.maxHeight = infinity

                // v->frame.copyMaxConstraints(contentCtx);
                v->layout(&v->frame);

                right = maxFloat(v->frame.getRight(), right);
                bottom = maxFloat(v->frame.getBottom(), bottom);
            }
        }
        //内容期望的尺寸默认为子视图的最右和最下
        contentCtx->setSize(right, bottom);
    }
	void initLayoutSize(Frame* ctx){
        //默认情况: 
        ctx->width = ctx->minWidth;
        ctx->height = ctx->minHeight;

        ctx->setSize_ifAnyTight();
    }
	bool callCbLayout(Frame* ctx){
        if (self.cb && self.cb.cbLayout(self, ctx)) {
            return true;
        }
        return false;
    }
	// void performLayout(Frame* ctx){
    //     //内容约束  
    //     //生成内容约束
    //     Frame contentCtx = self.makeContentLayoutCtx(ctx);
    //     self.layoutContent(&contentCtx);


    //     //if (ctx->isTight()) {//tight，尺寸是固定的
    //     //	return;
    //     //}

    //     //内容约束,传播给外约束
    //     self.updateFrame_byContentCtx(ctx, &contentCtx);
    // }
	void layout(Frame* ctx) {
        // 采用缓存，不用重新布局
        // if ctx.checkAndUseCacheResult() { 
        //     return
        // }

        // ctx.incTimesInOneLayout()
        
        //布局是不管位置的.位置是由父布局决定的
        // ctx.x = 0
        // ctx.y = 0
        //应用属性到frame上
        //根据自身的宽高声明，进一步约束
        self.updateFrame_forSelfWidthHeight(ctx);
        //默认情况
        self.initLayoutSize(ctx); 

        //允许自定义布局流程
        if (self.cb && self.cb.cbLayout(self, ctx)) {
            return;
        }

        // //收缩约束得到contentframe
        // Inset inset = self.getInsetOfFrameToContent();
        // Frame contentCtx = ctx.inset(inset);

        // //执行内容布局
        // self.layoutContent(&contentCtx);

        // //内容Frame传播给自身Frame
        // *ctx = contentCtx.outset(inset);
        self.layoutContent_fromOutBox(ctx)

        //保存约束
        ctx.saveConstraints()


        //应用desiredSize到frame上

        // ctx.setDesiredSize_withMargin(
        //     self.desiredWidth,
        //     self.desiredHeight,
        //     &self.margin
        // )

        //能不能应用desiredSize，自己是不知道的，需要由父布局决定
        //如layoutLinear，只有空间够时，才能应用desiredSize
        // ctx.applyDesiredSize();

        // if (ctx != &self.frame) {
        //     printf("use diff frame\n");
        // }


        // self.performLayout(ctx);

        // if (self.frame.width == 0.0 && self.name.equals("div")) {
        //     printf("draw root\n");
        // }
    }
	void updateFrame_byContentCtx(Frame *targetCtx, Frame *contentCtx){
        //有bugW
        if (targetCtx->isTight()) {//tight，尺寸是固定的
            return;
        }
        
        //确定自身的尺寸
        Vec2 ncSize = self.getNonContentSize();
        targetCtx->setSize(
            contentCtx->width + ncSize.x,
            contentCtx->height + ncSize.y
        );
        //frame.width = ;
        //frame.height = ;
    }
	Frame makeContentLayoutCtx(Frame *ctx){
        Frame ret = mkFrame()
        Vec2 ncSize = self.getNonContentSize();
        ret.setMinWidth(ctx->minWidth - ncSize.x);
        if (ctx->maxWidth != infinity) {
            ret.maxWidth = ctx->maxWidth - ncSize.x;
        }

        ret.setMinHeight(ctx->minHeight - ncSize.y);
        if (ctx->maxHeight != infinity) {
            ret.maxHeight = ctx->maxHeight - ncSize.y;
        }
        ret.setSize_ifAnyTight();

        return ret;
    }
	Rect get_abs_rect() {
    	//auto pos = localToWorld(margin.left, margin.top);
        Vec2 pos = self.localToWorld(0.f, 0.f);
        Vec2 viewSize = self.getViewSize();
        Vec2 sizePos = self.localToWorld(viewSize.x, viewSize.y);
        Vec2 size = sizePos.sub( pos );

        return mkRect(pos.x, pos.y, size.x, size.y );
    }
    
    //取得内容区的绝对位置
    Rect getContentClientRect(){
        Rect lr = self.getContentLocalRect()
        Vec2 pos = self.localToWorld(lr.x, lr.y);
        lr.x = pos.x
        lr.y = pos.y
        // Rect r = self.get_abs_rect()
        // lr.x = pos.x + lr.x
        // lr.y = pos.y + lr.y
        return lr
    }
	void clip(Canvas* canvas){

        // Rect r = self.get_abs_rect()
        // // Vec2 size = self.getViewSize();
        // // //clip;
        // // auto cliprr = RadiusUtil::makeRRect(radius, size.w, size.h);
        // // canvas->clipRRect(cliprr);

        float x = self.margin.left
        float y = self.margin.top
        float w = self.frame.width - self.margin.hor()
        float h = self.frame.height - self.margin.ver()
        canvas.intersectScissor(
            0.f, 0.f, w , h 
        )
    }
 
    
    void draw(Canvas* canvas) {
        if (self.cb && self.cb.cbDraw(self, canvas)) {
            return;
        }
        canvas.save()

        float l = self.frame.x;
        float t = self.frame.y;

        //auto ml = get_taitank_node_layout_margin(yg, CSS_LEFT);
        //auto mt = get_taitank_node_layout_margin(yg, CSS_TOP);


        canvas.translate(l , t );

        // float *m = self.transform.data
        canvas.transform(self.transform);
        canvas.currentTransform(&self._world_transform);


        canvas.translate(self.margin.left,  self.margin.top);

        // printf("draw position view:%f,%f,%f,%f margin:%f, %f\n", 
        //     l, t, self.frame.width, self.frame.height
        //     , self.margin.left, self.margin.top
        //     );

        //transform.setIdentity();
        // canvas->concat(transform);
        // _world_transform = canvas->getLocalToDevice();


        //auto need_draw = !do_not_draw;
        bool need_draw = true;

        //溢出时clip
        //if (style.overflow == OVERFLOW_HIDDEN && need_draw) {
        //	clip(canvas);
        //}
        if (self.needClip && need_draw) {
            self.clip(canvas);
        }

        {
            //if (style.visibility == "visible" && style.display != DISPLAY_TYPE_NONE) {
                //判断在不在窗体中
            if (need_draw) { //在窗体内
                // self.draw_self(canvas);
                if self.cb && self.cb.cbDrawSelf(self, canvas){
                }
                else {
                    self.draw_self(canvas);
                    if self.cb {
                        self.cb.afterDrawSelf(self, canvas)
                    }
                }
            }

            //内容区开始位置； 并不用考虑内容区原点。布局出来的原点就是相对视图原点
            canvas.save();
            canvas.translate(
                // vg,
                self.padding.left + self.border.l.w, 
                self.padding.top + self.border.t.w
            );
            //不管要不要画，draw_children还是要走，因为要更新矩阵，坐标
            self.draw_children(canvas);
            canvas.restore();

            if (need_draw) { //在窗体内
                self.drawSelfBorder(canvas);
            }

        }

        canvas.restore();
        // canvas->restore();
    }
    void drawSelfBorder(Canvas *canvas){

        int tc = self.border.t.color;
        int rc = self.border.r.color;
        int bc = self.border.b.color;
        int lc = self.border.l.color;
        //不透明边框
        if (
            // self.border.t.w > 0 && 
            (
                colorGetA(tc) > 0 ||
                colorGetA(rc) > 0 ||
                colorGetA(bc) > 0 ||
                colorGetA(lc) > 0
                )
            ) {

            // Vec2 size = self.getSizeWithoutMargin();
            Rect viewRect = self.getViewRect()
            float w = viewRect.w;
            float h = viewRect.h;

            // SkRRect rr = RadiusUtil::makeRRect(radius, w, h);
            //边框以stroke绘制。 导致边框可以溢出,所以需要内缩一半
            // float inset_dx = border.t.w / 2.f;
            // float inset_dy = border.t.w / 2.f;
            // rr.inset(inset_dx, inset_dy);
            //rr.inset(0.5f, 0.5f); //配合hairline,好像真的1像素左右了
            //TODO 暂不支持边框有分别的颜色
            // SkPaint paint;
            // if (border.t.w >= 1.001f) {
            //     paint.setAntiAlias(true);
            // }

            // paint.setColor(tc);
            // paint.setStrokeWidth(border.t.w <= 1.001f ? 0.0f : border.t.w);//0.0f for hairline
            // paint.setStyle(SkPaint::kStroke_Style);

            // canvas->drawRRect(rr, paint);

            if (self.border.isAllHasWidth()){
                canvas.beginPath()
                if (self.border.t.w <= 1.001f ){
                    canvas.strokeWidth( 1.0f)
                    // https://github.com/memononen/nanovg/issues/282
                    // 绘制一像素的线
                    canvas.roundRect( 0.5f, 0.5f, w - 0.5, h - 0.5, self.radius.tl);
                } else {
                    canvas.roundRect( 0.5f, 0.5f, w - 0.5, h - 0.5, self.radius.tl);
                    canvas.strokeWidth( self.border.t.w)
                }
                canvas.strokeColorByInt32((self.border.t.color))
                canvas.stroke();
            } 
            else {//单边
                if (self.border.t.w > 0.f){
                    canvas.beginPath()
                    canvas.moveTo( 0.5f, 0.5f)
                    canvas.lineTo( w + 0.5f, 0.5f)

                    canvas.strokeWidth( self.border.t.w)
                    canvas.strokeColorByInt32( (self.border.t.color))
                    canvas.stroke();
                }
                if (self.border.r.w > 0.f){
                    canvas.beginPath()
                    canvas.moveTo( w + 0.5f, 0.5f)
                    canvas.lineTo( w + 0.5f, h + 0.5f)

                    canvas.strokeWidth( self.border.r.w)
                    canvas.strokeColorByInt32( (self.border.r.color))
                    canvas.stroke();
                }
                if (self.border.b.w > 0.f){
                    canvas.beginPath()
                    canvas.moveTo( 0.5f, h + 0.5f)
                    canvas.lineTo( w + 0.5f, h + 0.5f)

                    canvas.strokeWidth( self.border.b.w)
                    canvas.strokeColorByInt32( (self.border.b.color))
                    canvas.stroke();
                }
                if (self.border.l.w > 0.f){

                    canvas.beginPath()
                    canvas.moveTo( 0.5f, 0.5f)
                    canvas.lineTo( 0.5f, h + 0.5f)

                    canvas.strokeWidth( self.border.l.w)
                    canvas.strokeColorByInt32( (self.border.l.color))
                    canvas.stroke();
                }
            }

        }
    }
    void draw_self(Canvas* canvas) {
        // SkPaint paint;
        // paint.setAntiAlias(true);
        // paint.setColor(backgroundColor);

        // 不透明的背景
        float bga = colorGetA(self.backgroundColor);
        if (bga > 0.f) {//不透明

            Vec2 size = self.getSizeWithoutMargin();
            float w = size.x;
            float h = size.y;
            // SkRRect rr = RadiusUtil::makeRRect(radius, w, h);
            canvas.beginPath();
            
            canvas.roundRect(0.f, 0.f, w, h, self.radius.tl);
            
            canvas.fillColorByInt32(self.backgroundColor)
            canvas.fill();

            //极度消耗性能，开boxShadow之前10ms,开之后60ms
            // boxShadow.applyToPaint(paint);
            // canvas->drawRRect(rr, paint);
        }
    }

}
