package Sui

#include <stdio.h>

import * from "../Core/Vec2.orc"
import * from "../Core/ViewBase.orc"
import * from "../Core/Node.orc"
import * from "../Core/Emitter.orc"
import type * from "../Core/View.orc"
import * from "../Core/Inset.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Frame.orc"
import * from "../Core/Screen.orc"
import * from "../Core/Timer.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/Time.orc"
import * from "./App.orc"
import * from "./Event.orc"
import type * from "./KeyEvent.orc"
// import type * from "./MouseEvent.orc"
import * from "./Focus.orc"
import * from "./Fps.orc"
import * from "./Canvas.orc"


//用法
//Window@ win = new Window()
//win.initData()
//win.show()
//win.setTitle("hi")
//win.setPos(200, 200)
//win.setSize(600, 400)
//win.layoutAndDraw()
class Window extends Emitter{

    long long id = 0
    Fps fps
  
    ViewBase@ rootView = new View()

    Canvas@ canvas = new Canvas()

    // 无边框
    bool borderless = false;


 
    //各平台自己的data
    void *data;
    void ctor(){
        self.rootView.setOwnerWindow(self)
        self.rootView.setMounted(true)

        if (self.rootView instanceof View){
            View *div = (View*)self.rootView;
            div.backgroundColor = 0x00000000;//0xffefefc0;
            printf("bg :  %x\n", div.backgroundColor);
        }
        App@ app = App_use();
        app.addWindow(self)
        self.initData()
    }
    extern void setTransparent()
    void setRootView(ViewBase *v){
        if (v == self.rootView){
            return
        }
        //取消设置
        if (self.rootView){
            self.rootView.setMounted(false)
            self.rootView.setOwnerWindow(null)
        }

        self.rootView = v

        //初始化
        if (self.rootView){
            self.rootView.setOwnerWindow(self)
            self.rootView.setMounted(true)
        }

    }
    void dtor(){
        self.cleanData()
        
        printf("释放Window%p\n", self);
    }
    // void (*cleanData)(void *data);
    extern void cleanData()
    extern void initData()

    //显示
    extern void show()
    //从任务栏中隐藏
    extern void hide()
    //最大化
    extern void maximize()
    //最小化
    extern void minimize()
    //普通化
    extern void normal() 
    //禁用/启用
    extern void enable(bool enable)

    //关闭窗口
    extern void close()

    //设置拥有者窗口,配合widnow.enable 可以用来实现 模态窗体
    extern void setOwner(Window *ownerWindow)

    int layoutTimes = 0

    void layoutAndDraw(){
        if !self.isVisible() {
            return;
        }

        // printf("\n====================window.layoutAndDraw %p\n", self);
        self.layoutTimes ++
        // printf("window:%lld layoutAndDraw\n", self.id)
        long long t0 = Time_unixMs()
        // self.rootView.markLayoutStart()

        {
            self.fps.startFrame()
            {
                self.fps.startLayout()
                self.layout()
                self.fps.endLayout()
            }
            long long t1 = Time_unixMs()

            {
                self.fps.startDraw()
                self.draw()
                self.fps.endDraw()
            }
            self.fps.endFrame()
        }

        long long t2 = Time_unixMs()
        // printf("layout and draw cost %lldms %lldms\n", t1- t0, t2-t1);

        // if (self.layoutTimes % 20 == 1){
        //     printf("===========layout times===========\n")
        //     self.rootView.printLayoutTimes(0)
        //     printf("\n")
        // }
    }
    extern void layout()
    extern void draw()
    extern bool isVisible();

    void onDestroy(){
        App@ app = App_use();
        app.removeWindow(self)
    }

    extern void setTitle(const char *title)
    extern String@ getTitle()

    //取得屏幕坐标
    // Vec2 getPos(){
    //     Vec2 ret =mkVec2(0, 0)
    //     self._getPos(&ret.x, &ret.y)
    //     return ret
    // }
    //取到的是
    extern Vec2 getPos()
    extern void setPos(float x, float y)

    extern Vec2 getSize()
    extern void setSize(float x, float y)
    extern void setRect(float x, float y, float w, float h)
    
    //客户区尺寸
    extern Vec2 getClientSize()

    void moveToCenter(){
        Vec2 screenSize =  Screen_get_usable_size()
        Vec2 size = self.getSize()
        self.setPos(
            (screenSize.x - size.x ) / 2.0,
            (screenSize.y - size.y ) / 2.0,
        )
    }
    


    //取得非客户区的Inset
    extern Inset getNonClientInset()
    
}


//全局初始化
// extern void Window_initGlobal();
// //创建一个窗口
// extern long long Window_create();
// extern void Window_setSize(long long id, int w, int h);
// extern Vec2 Window_getSize(long long id);

// extern void Window_setPos(long long id, int w, int h);
// extern Vec2 Window_getPos(long long id);
// extern void Window_show(long long id);
// extern Vec2 Window_hide(long long id);

// extern void Window_maximize(long long id);
// extern Vec2 Window_minimize(long long id);
// extern Vec2 Window_normal(long long id);
// extern Vec2 Window_close(long long id);
// extern Vec2 Window_setTitle(long long id, const char *title);
// extern const char * Window_getTitle(long long id);
// extern Vec2 Window_getClientSize(long long id);
// extern Inset@ Window_getNonClientInset(long long id);



void testWindow(){
    printf("test Window\n")
    Window@ win = new Window()
    win.setTitle("title from orc中文啊")
    win.setSize(200, 200)
    win.setPos(400, 400)
    win.show();
}


void dispatchWindowFocusGainedEvent(long long windowId){
    printf("取得窗口 焦点。。。。\n");

    App@ app = App_use()
    Window@ win = app.findWindowById(windowId)

    WindowFocusEvent@ e = new WindowFocusEvent() 
    e.isFocus = true
    e.isBlur = false
    e.window = win

    dispatchWindowFocusEvent(e)
}

void dispatchWindowFocusLostEvent(long long windowId){
    printf("丢失窗口 焦点。。。。\n");

    App@ app = App_use()
    Window@ win = app.findWindowById(windowId)

    WindowFocusEvent@ e = new WindowFocusEvent() 
    e.isFocus = false
    e.isBlur = true
    e.window = win

    dispatchWindowFocusEvent(e)
}


//跨窗体的 拖拽指示器
class DragCrossWindowIndicator {
    extern void _start();
    extern void _end();
    extern void _dragMove();

    bool dragging = false;

    void start(){
        self.dragging = true
        self._start()
        requestAnimationFrame(^bool (){
            self.onDragMove(mkVec2(0, 0))
            return !self.dragging
        })
    }
    void end(){
        self.dragging = false
        self._end()
    }
    void onDragMove(Vec2 clientPos){
        self._dragMove()
    }
}