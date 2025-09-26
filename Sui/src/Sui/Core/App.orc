package SuiCore

#include <stdlib.h>
#include <stdio.h>
#include "../../Orc/Orc.h"


import * from "../../Orc/List.orc"
import * from "../../Orc/Time.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Mutex.orc"
import type * from "./Window.orc"
import  * from "./Vec2.orc"
import  * from "./ViewBase.orc"
import  * from "./Node.orc"
import  * from "./Emitter.orc"
import type * from "./MouseEvent.orc"
import  * from "./Timer.orc"

class AppEventLoopMessage {
}


//管理整个应用
class App{
    List@ windows = new List()



    Window* findWindowById(long long id){
        for (int i = 0; i < self.windows.size(); i++){
            Window* window = (Window*)self.windows.get(i)
            if (window.id == id){
                return window;
            }
        }
        return null
    }
    void addWindow(Window *win){
        self.windows.add(win)
    }
    void eachWindow(^void (Window* win) onWin){
        for (int i = 0; i < self.windows.size(); i++){
            Window* window = (Window*)self.windows.get(i)
            onWin(window)
        }
    }
    void removeWindow(Window *win){
        sinsHoverSentive().clear()

        self.windows.remove(win)

        win.rootView.dissolveSubtree()
        win.setRootView(null)


        if (self.windows.size() == 0){
            printf("App.windows.size == 0\n")
            self.quit()
        }
    }

    void layoutAndDrawAllWindows(){
        long long t0 = Time_unixMs()
        for (int i = 0; i < self.windows.size(); i++){
            Window *win = (Window*)self.windows.get(i)

            win.layoutAndDraw()
        }
        long long t1 = Time_unixMs()
        // printf("layoutAndDrawAllWindows. cost:%lldms\n", t1-t0)

        // Time_sleepMs(1000)
    }
    //退出应用
    void quit(){
        exit(0)
    }
    
    bool _invalidDraw = false

    void invalidDraw(){
        self._invalidDraw = true
    }
    void invalidLayout(){
        self._invalidDraw = true
    }
    //遍历 节点，处理dirtyReact
    void processDirtyReacts(){
        if (1){
            return
        }

        for (int i = 0; i < self.windows.size(); i++){
            Window *win = (Window*)self.windows.get(i)
            self.processRecuDirtyReacts(win->rootView)
        }
    }
    void processRecuDirtyReacts(Node* n){
        if (n._reactDirty){
            n._reactDirty = false
            n.react()
        }
        //遍历 子节点
        int l = n.getChildrenCount()
        for (int i = 0; i < l;i++){
            Node *kid = n.getChild(i)
            if (kid){
                self.processRecuDirtyReacts(kid)
            }
        }
    }


    Mutex@ postMessageMutex = new Mutex()
    List@ messageList = new List()
    void postMessage_toEventLoop_threadSafe(AppEventLoopMessage@ msg){
        self.postMessageMutex.lock();

        self.messageList.add(msg);

        self.postMessageMutex.unlock();
    }
    
    //从消息列表弹出第一个消息
    AppEventLoopMessage@ peekFromMessageList(){
        self.postMessageMutex.lock();
        AppEventLoopMessage@ msg = null

        if (self.messageList.size() > 0){
            msg = self.messageList.get(0)
            self.messageList.removeAt(0)
        }
        self.postMessageMutex.unlock();

        return msg;
    }

    //逐一处理消息列表
    void processMessageList(){
        while (true){
            AppEventLoopMessage@ msg = self.peekFromMessageList()
            if (msg == null){
                break;
            }
            
            printf("process AppEventLoopMessage %p\n", msg);
        }

        //定时器处理
        insTimerMgr().fire();
        tickAnimationFrames()
        
    }
    void init(){
        TimerMgr@ mgr = insTimerMgr()
        mgr.startThreadTick()
    }
    
    //运行事件循环
    extern void runEventLoop()
}


static App@ gApp = null
App@ App_use(){
    if (gApp == null){
        gApp = new App()
        gApp.init();
    }
    return gApp
}

void App_onDestroyWindow(long long id){
    Window* tmp = null
    {
        App@ app = App_use()
        Window@ win = app.findWindowById(id)
        tmp = win;

        if (!win){
            return
        }

        app.removeWindow(win)
    }

    // Time_sleepMs(3000)
    // urgc_report_sources_of(tmp);
}

bool App_repaintWindowById(long long id){
    if (!id){
        return false
    }
    App@ app = App_use()
    Window@ win = app.findWindowById(id)
    if (!win){
        return false
    }
    String@ title = win.getTitle()
    // printf("repaintWindowById. 窗口标题:%s\n", title.str);
    win.layoutAndDraw()
    return true
}



void testApp(){
    App@ app = App_use();
    printf("testApp\n")
    app.runEventLoop()
}
