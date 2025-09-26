package SuiCore

#include <stdio.h>
#include "../../Orc/Orc.h"

#include "../../nanovg/nanovg.h"
 
import * from "./Node.orc"
import * from "./Rect.orc"
import * from "./Frame.orc"
import type * from "./LayoutCell.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Math.orc"
import * from "./Vec2.orc"
import * from "./Vec3.orc"
import * from "./Mat2d.orc"   
import * from "./Inset.orc"   
import * from "./Window.orc"
import type * from "./App.orc"
import * from "./Color.orc"
import * from "./Canvas.orc"

   
/// <summary>
/// 基础view, 提供
/// 绘制、 
/// 布局(测量和定位)、
/// 事件分发(hitTest)、
/// 坐标转换、 
/// 定时器的统一入口  
/// </summary>
class ViewBase extends Node { 
    //normal|onlychildren|none|nochildren
    String@ hitTestType = str("normal")
    Inset hitTestPadding = mkInset0()

    Frame frame = mkFrame();
    List@ layoutCells = null;


    // LayoutCtx@ layoutCtx = new LayoutCtx();
    Mat2d transform = mkMat2d();
    Mat2d _world_transform = mkMat2d();
    bool visible = true
    String@ cursor = str("unset")
    bool hover = false

    // z轴值。会影响hitTest
    int z = 0

    //获取或者创建LayoutCells
    List* gocLayoutCells(){
        if (self.layoutCells == null){
            self.layoutCells = new List()
        }
        return self.layoutCells
    }


	LayoutCell* getLayoutCellByType(Vtable_Object* vt){
        List* cells = self.gocLayoutCells();

		for (int i = 0; i < cells.size(); i++){
			Object *cell = cells.get(i);
			if (cell instanceof vt){
				return (LayoutCell*)cell;
			}
		}
		return null
	}


    //at 只算viewChildren
    ViewBase* getChildViewAt(int at){
        int count = 0;

        int  l = self.getChildrenCount()
        for (int i = 0; i < l; i++) {
            ViewBase* view = self.getChildAsView(i);
            if (view) {
                at--;  
                if (at < 0) { 
                    return view;
                }
            } 
        }  
        return null; 
    } 
    //和getChildViewAt不同。 at是children的索引 
    ViewBase* getChildAsView(int at){ 
        Object *o = self.children.get(at); 

        if (o instanceof ViewBase){
            return (ViewBase*)o; 
        }
        return null;
	    // return (ViewBase*)(self.children.get(at)); 
    } 

    int getChildrenViewCount(){
        int count = 0;

        int  l = self.getChildrenCount()
        for (int i = 0; i < l; i++) {
            ViewBase* view = self.getChildAsView(i);
            if (view && view->visible) { //&& view->style.display != DISPLAY_TYPE_NONE) {
                count++;
            }
        }
        return count;
    }
   
    ///返回屏幕坐标
    Rect getScreenRect(){
        Rect r = self.get_abs_rect();
        Window* win = self.getWindow();
        //auto win = Window::getWindowOfView(this);
        
        if (win) {
            Vec2 wr = win->getPos();
            r.offset(wr.x, wr.y);
        }
        return r;
    } 
    ///返回客户区绝对坐标。 跟js的client区定义一致
    Rect get_abs_rect(){
        Vec2 pos = self.localToWorld(0.f, 0.f);
        Vec2 sizePos = self.localToWorld(self.frame.width, self.frame.height);
        Vec2 size = sizePos.sub(pos);
  
        return mkRect( pos.x, pos.y, size.x, size.y );
    }   
    bool _hitTestClientRect(Rect *r, float x, float y){
        //扩增padding
        r.x = r.x - self.hitTestPadding.left;
        r.y = r.y - self.hitTestPadding.top;
        r.w = r.w + self.hitTestPadding.hor();
        r.h = r.h + self.hitTestPadding.ver();
        if (r.containsPosition(x, y)) {
            //auto cm = meta->getByObj(this);
            //printf("hitTest:%s\n", cm->name.c_str());
            //std::cout << "hitTest:" << cm->name << "\n";
            //std::cout << std::format("hitTest::{}\n", cm->name);
            return true;
        }
        return false;
    }
    bool _hitTestSelf(float x, float y){
        Rect r = self.get_abs_rect();
        return self._hitTestClientRect(&r, x, y)
        // //扩增padding
        // r.x = r.x - self.hitTestPadding.left;
        // r.y = r.y - self.hitTestPadding.top;
        // r.w = r.w + self.hitTestPadding.hor();
        // r.h = r.h + self.hitTestPadding.ver();
        // if (r.containsPosition(x, y)) {
        //     //auto cm = meta->getByObj(this);
        //     //printf("hitTest:%s\n", cm->name.c_str());
        //     //std::cout << "hitTest:" << cm->name << "\n";
        //     //std::cout << std::format("hitTest::{}\n", cm->name);
        //     return true;
        // }
        // return false;
    }
    void _on_invalidLayout(){

    }
    void _on_invalidDraw(){ 

    }
    void resetViewTreeDirty(){

    }
    void invalidReact(){
        super.invalidReact()
        self.invalidLayout()
    }

    //将本地坐标转换为世界坐标. 注意本地坐标原点是FrameRect的左上角
    //对于View而言，同样也不是ViewRect的左上角
    //所以，不管是哪个节点，localToWorld的定义都是一致的
    Vec2 localToWorld(float x, float y){
        Vec2 ret = mkVec2(0,0);
        Vec3 p = self._world_transform.transformPoint(x, y, 0.f);
        ret.x = p.x
        ret.y = p.y
        return ret
    }

    Vec2 worldToLocal(float x, float y){
        Vec2 ret = mkVec2(0,0);
        Mat2d inv = self._world_transform;//.copy()
        inv.inverse()

        Vec3 p = inv.transformPoint(x, y, 0.f);
        ret.x = p.x
        ret.y = p.y
        return ret
    }

    ViewBase* hitTest(float x, float y){
        if (self.hitTestType.equals("none")) {
            return null;
        }
        //if (style.display == DISPLAY_TYPE_NONE) return nullptr;

        if (self.hitTestType.equals( "nochildren")) {
            if (self._hitTestSelf(x, y)) {
                return self;
            }
            return null;
     
        }
        ViewBase* found = self.hitTestChildren(x, y);
        if (found) {
            return found;
        }
        if (self.hitTestType.equals("onlychildren")) {
            return null;
        }
        if (self._hitTestSelf(x, y)) {
            return self;
        }
       
        return null;      
    }
    ViewBase* hitTestChildren(float x, float y){
        int l = self.children->size()
        //从后向前找到第一个hitTest满足的
        for (int i = l - 1; i >= 0; i--) {
            ViewBase* kid_view = self.getChildAsView(i);
            if (kid_view && kid_view->visible) {
                ViewBase* found = kid_view->hitTest(x, y);
                if (found) {
                    return found;
                }
            }
        } 
        return null; 
    }

    ///计算child在view子节点列表中的索引位置 
    int viewIndexOf(Node *child){
        if (!(child instanceof ViewBase)){ 
            return -1
        }
        int at = -1;
        int l = self.children->size()
        for (int i = 0 ; i < l; i++) {
            Node* n = (Node*)self.children->get(i);
            if (n instanceof ViewBase) {
                at++;
            }
            if (n == child) {
                return at;
            }
        }
        return -1;
    }
    int viewIndexInParent(){
        if (self.parent instanceof ViewBase){
            ViewBase *vb = (ViewBase*)self.parent
            return vb.viewIndexOf(self)
        }
        return -1
    }
    void markLayoutStart(){
        self.frame.timesInOneLayout = 0
        int l = self.getChildrenCount()
        for (int i = 0; i < l; i++){
            ViewBase *v = self.getChildAsView(i)
            if (v){
                v.markLayoutStart()
            }
        }
    }
    void printLayoutTimes(int tab){
        for (int i = 0; i < tab; i++){
            printf("\t");
        }
        const char *className = Object_getClassName(self)
        printf("%s:%d\n", className, self.frame.timesInOneLayout);

        int l = self.getChildrenCount()
        for (int i = 0; i < l; i++){
            ViewBase *v = self.getChildAsView(i)
            if (v){
                v.printLayoutTimes(tab + 1)
            }
        }
    }
	void layoutContent(Frame *contentCtx){
        // float right = 0.f;
        // float bottom = 0.f;
 
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
                v.layout(&v.frame);

                // right = maxFloat(v->frame.getRight(), right);
                // bottom = maxFloat(v->frame.getBottom(), bottom);
            }
        }
        //内容期望的尺寸默认为子视图的最右和最下
        // contentCtx.setSize(right, bottom);
    }
    void layout(Frame *ctx){
        ctx.incTimesInOneLayout();
        // float width = 0.f;
        // float height = 0.f;
        // Frame contentFrame = ctx.copy()
        self.layoutContent(ctx)

        // for (int i = 0, l = self.getChildrenCount(); i < l; i++) {
        //     ViewBase* v = self.getChildAsView(i);
        //     if (v) {
        //         //只复制约束, 传递约束
        //         v->frame.copyConstraints(ctx);
        //         v->layout(&v->frame);
        //         //采用最右的子节点的size
        //         width = maxFloat(width, v->frame.getRight());
        //         height = maxFloat(height, v->frame.getBottom());
        //     }
        // }
        // //向上告知尺寸
        // ctx->setSize(width, height);
    }
    void invalidLayout(){
        App_use().invalidLayout()
    }
    void draw(Canvas *canvas){
        canvas.save();

        float l = self.frame.x;
        float t = self.frame.y;

        //auto ml = get_taitank_node_layout_margin(yg, CSS_LEFT);
        //auto mt = get_taitank_node_layout_margin(yg, CSS_TOP);

        canvas.translate(l, t);

        //transform.setIdentity();
        // float *m = self.transform.data
        canvas.transform( self.transform);
        // canvas->concat(transform);
        // self._world_transform = canvas->getLocalToDevice();
        // nvgCurrentTransform(vg, self._world_transform.data);
        canvas.currentTransform( &self._world_transform);

        {
            self.draw_self(canvas);
            self.draw_children(canvas);
        }

        canvas.restore();
    }
    void draw_children(Canvas *canvas){
        int l = self.getChildrenCount()
        for (int i = 0; i < l; i++) {
            ViewBase* view = self.getChildAsView(i);
            if (view && view->visible){ //&& view->style.display != DISPLAY_TYPE_NONE) {
                view->draw(canvas);
            }
        }
    }


    void draw_self(Canvas *canvas){
        canvas.fillColorByInt32((0xff00ff33));
        canvas.strokeColorByInt32((0xffff0033));
        canvas.strokeWidth( 10);
        canvas.beginPath()
        canvas.rect(10, 10, 100, 100)
        canvas.fill()
        canvas.stroke()

    }
    void invalidDraw(){ 
        App_use().invalidDraw()
    }
    ///是否参与父节点的布局
    bool canLayoutByParent(){
        return self.visible
    }

    void setVisible(bool v){
        if (v != self.visible){
            self.visible = v
            self.invalidLayout()
        }
    }
    void setHover(bool v){
        if (self.hover != v){
            self.hover = v
            self.onHoverChanged()
            //TODO 通知hover changed
        }
    }

    ^void() cbOnHoverChanged = null

    void onHoverChanged(){
        // self.trigger_react()
        if (self.cbOnHoverChanged){
            self.cbOnHoverChanged()
        }
    }


    String@ toString(){
        const char *className = Object_getClassName(self);
        char tmp[256];
        snprintf(tmp, sizeof(tmp), "[%f,%f,%f,%f]",
            self.frame.x,
            self.frame.y,
            self.frame.width,
            self.frame.height
        );
        return str(className)
        .add(":")
        .addString(self.name)
        .add(tmp)
    }
}
//考虑z轴的hitTest
ViewBase* hitTestChildren_withZ(ViewBase *ins, float x, float y){
    int l = ins.children->size()
    ViewBase *ret = null
    //从后向前找到第一个hitTest满足的
    for (int i = l - 1; i >= 0; i--) {
        ViewBase* kid_view = ins.getChildAsView(i);
        if (kid_view && kid_view->visible) {
            ViewBase* found = kid_view->hitTest(x, y);
            if (found) {
                if ret == null || found.z > ret.z {
                    ret = found
                }
            }
        }
    } 
    return ret; 
}