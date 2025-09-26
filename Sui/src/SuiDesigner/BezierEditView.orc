package SuiDesigner
#include "../nanovg/nanovg.h"

#include <stdio.h>

import * from "../Orc/String.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Canvas.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Bezier.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sui/View/ViewBuilder.orc"

class BezierEditView extends View {
    Vec2 start = mkVec2(0.0, 0.0)
    Vec2 c0 = mkVec2(0.25, 0.5)
    Vec2 c1 = mkVec2(0.75, 0.5)
    Vec2 end = mkVec2(1.0, 1.0)

    View@ startView;
    View@ c0View;
    View@ c1View;
    View@ endView;

    Drag@ drag = new Drag()

    ^void (BezierEditView*v) onChanged

    float indicatorSize = 12

    void setBezier(Bezier v){
        self.start = v.start
        self.c0 = v.c0
        self.c1 = v.c1
        self.end = v.end
    }
    Bezier getBezier(){
        Bezier r;
        r.start = self.start
        r.c0 = self.c0
        r.c1 = self.c1
        r.end = self.end
        return r
    }

    void fire_onChanged(){
        if self.onChanged {
            self.onChanged(self)
        }
    }

	void layoutContent(Frame *f){
        // do nothing
		Frame tmp = *f
		super.layoutContent(f);
		// //不受子节点的影响
		*f = tmp
	}

    void ctor(){
        self.drag.onDrag = ^ void(Drag *d){
            if d.isDragging {
                // printf("dragging. delta:%f, %f\n", d.deltaPos.x, d.deltaPos.y)
                View* view = self.startView;
                String@ id = (String@)d.data
                if id.equals("0"){
                    view = self.startView;
                }
                if id.equals("1"){
                    view = self.c0View;
                }
                if id.equals("2"){
                    view = self.c1View;
                }
                if id.equals("3"){
                    view = self.endView;
                }
                // float tox = view.frame.x + d.deltaPos.x
                // float toy = view.frame.y + d.deltaPos.y

                Rect local = self.getContentLocalRect()
                Vec2 to = self.worldToLocal(d.currentClientPos.x, d.currentClientPos.y)
                to = to.sub(mkVec2(local.x, local.y))

                Rect r = self.getContentClientRect()
                float x = to.x / r.w
                float y = 1.0 - to.y / r.h

                if id.equals("0"){
                    self.start.set(x, y)
                }
                if id.equals("1"){
                    self.c0.set(x, y)
                }
                if id.equals("2"){
                    self.c1.set(x, y)
                }
                if id.equals("3"){
                    self.end.set(x, y)
                }
                self.fire_onChanged()
            }
        }
    }

    void _onIndicatorEvent(int id, Event *e){
        if e instanceof MouseEvent {
            MouseEvent* me = (MouseEvent*)e;
            if me.isMouseDown{
                self.drag.data = str("").addi(id)
                self.drag.onMouseDown(me)
            }
        }
    }

    void react(){
        Node* o = self
        self.startInnerReact()

        //start
        mkView(o, 0).{
            self.startView = o
            o.width = self.indicatorSize
            o.height = self.indicatorSize
            o.radius.setAll(6)
            o.border.setAll(2, 0xffffffff)
            o.cbOnEvent = ^ void (Event *e){
                self._onIndicatorEvent(0, e)
            }
        }
        //ctrl 0
        mkView(o, 0).{
            self.c0View = o
            o.width = self.indicatorSize
            o.height = self.indicatorSize
            o.radius.setAll(6)
            o.border.setAll(2, 0xffffffff)
            o.cbOnEvent = ^ void (Event *e){
                self._onIndicatorEvent(1, e)
            }
        }
        //ctrl 0
        mkView(o, 0).{
            self.c1View = o
            o.width = self.indicatorSize
            o.height = self.indicatorSize
            o.radius.setAll(6)
            o.border.setAll(2, 0xffffffff)
            o.cbOnEvent = ^ void (Event *e){
                self._onIndicatorEvent(2, e)
            }
        }
        mkView(o, 0).{
            self.endView = o
            o.width = self.indicatorSize
            o.height = self.indicatorSize
            o.radius.setAll(6)
            o.border.setAll(2, 0xffffffff)
            o.cbOnEvent = ^ void (Event *e){
                self._onIndicatorEvent(3, e)
            }
        }

        self.endInnerReact()
    }

    void draw_self(Canvas* c){
        super.draw_self(c)

        //更新


        // c.beginPath()
        // c.moveTo(0, 100)
        // c.bezierTo(100, 100, 300, 200, 400, 200)
        // c.closePath()

        // c.fillColorByInt32(0xffff0000)
        // c.strokeColorByInt32(0xffff0000)
        // c.strokeWidth(2)
        // c.fill()

        // c.stroke()
        Rect r = self.getContentLocalRect()
        if self.startView{
            &self.startView.frame.{
                o.x = r.w * self.start.x - self.indicatorSize / 2.0
                o.y = r.h * (1.0 - self.start.y) - self.indicatorSize / 2.0
            }
        }
        if self.c0View{
            &self.c0View.frame.{
                o.x = r.w * self.c0.x - self.indicatorSize / 2.0
                o.y = r.h * (1.0 - self.c0.y) - self.indicatorSize / 2.0
            }
        }
        if self.c1View{
            &self.c1View.frame.{
                o.x = r.w * self.c1.x - self.indicatorSize / 2.0
                o.y = r.h * (1.0 - self.c1.y) - self.indicatorSize / 2.0
            }
        }
        if self.endView{
            &self.endView.frame.{
                o.x = r.w * self.end.x - self.indicatorSize / 2.0
                o.y = r.h * (1.0 - self.end.y) - self.indicatorSize / 2.0
            }
        }

        float sx = r.w * self.start.x
        float sy = r.h * (1.0 - self.start.y)

        float c0x = r.w * self.c0.x
        float c0y = r.h * (1.0 - self.c0.y)

        float c1x = r.w * self.c1.x
        float c1y = r.h * (1.0 - self.c1.y)

        float ex = r.w * self.end.x
        float ey = r.h * (1.0 - self.end.y)

        // Rect r = self.getViewRect()

        // NVGpaint lg = nvgLinearGradient(vg, 
        //     0, 0, 
        //     0, r.h,
        //     nvgRGBA(255, 0, 0, 255), 
        //     nvgRGBA(255, 0, 0, 0), 
        // )
        // nvgFillPaint(vg, lg)

		c.linearGradient(true,
            0, 0, 
            0, r.h,
            mkIntByRgba(255, 0, 0, 255), 
            mkIntByRgba(255, 0, 0, 0), 
		)


        c.beginPath()
        // c.moveTo(0, r.h)
        // c.moveTo(r.w, r.h)
        // c.lineTo(r.w, r.h)
        // c.lineTo(ex, ey)
        c.moveTo(sx, sy)
        // c.lineTo(c1x, c1y)
        // c.lineTo(c0x, c0y)
        // c.lineTo(sx, sy)
        c.bezierTo(
            c0x, c0y,
            c1x, c1y,
            ex, ey
        )
        c.lineTo(r.w, r.h)
        c.lineTo(0, r.h)

        c.closePath()
        c.pathWinding( 1)

        c.strokeColorByInt32(0xffffffff)
        c.strokeWidth(2)
        c.stroke()
        c.fill()

        c.beginPath()
        c.moveTo(sx, sy)
        c.lineTo(c0x, c0y)
        c.strokeColorByInt32(0xffff0000)
        c.stroke()

        c.beginPath()
        c.moveTo(ex, ey)
        c.lineTo(c1x, c1y)
        c.strokeColorByInt32(0xffff0000)
        c.stroke()



        // canvas.fill()


        // nvgBeginPath(vg)
        // nvgMoveTo(vg, 0, 100)
        // nvgBezierTo(vg, 0, 200, 100, 300, 400, 200)
        // // nvgQuadTo(vg, 100, 300, 400, 200)
        // // nvgLineTo(vg, 300, 500)
        // nvgLineTo(vg, 300, 0)
        // // nvgLineTo(vg, 0, 300)
        // nvgPathWinding(vg, 1)
        // nvgClosePath(vg)

        // // nvgFillColor(vg, nvgRGBA(255, 0, 0, 128))
        // // nvgstrokeColorByInt32(0xffff0000)
        // // nvgStrokeWidth(vg, 2)
        // nvgFill(vg)


		// nvgBeginPath(vg);
		// nvgMoveTo(vg, 10, 10);
		// // nvgLineTo(vg, 100, 0);
		// nvgBezierTo(vg, 200, 0, 400, 30, 400, 200);
		// nvgClosePath(vg);
		// nvgFillColor(vg, nvgRGB(0, 255, 0));
		// nvgStrokeColor(vg, nvgRGB(255, 255, 0));
        // nvgFill(vg)
        // nvgStrokeWidth(vg, 4)
		// nvgStroke(vg);

    }
}


BezierEditView@ mkBezierEditView(void* parent, long long key){
    return (BezierEditView@)gocNode(
		key ? (void*)key: __builtin_return_address(0)
		, (Node*)parent, BezierEditView)
}