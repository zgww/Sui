package SuiCore

#include <stdint.h>
#include <stdio.h>
#include "../../../UrgcDll/urgc_api.h"

// import * from "./Node.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Time.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Thread.orc"
import * from "../../Orc/Mutex.orc"



/// 定时器
class Timer{
    ^void() runFunc

    bool alive = false
    bool isInterval = false
    int intervalMs = 0
    int remainMs = 0

    // //用户数据
    // char userdata[32];

    String@ name = null

    void dtor(){
        // printf("释放定时器 name = %s, intervalMs:%d\n", 
        // self.name == null ? "": self.name.str,
        // self.intervalMs);
    }

    void restart(){
        self.cancel()
        self.start()
    }

    void start(){
        if (self.alive){
            return;
        }
        self.remainMs = self.intervalMs
        self.alive = true

        TimerMgr@ mgr = insTimerMgr()
        mgr.addItemOnce(self)
    }

    void cancel(){
        self.alive = false
    }
    void fire(){
        if (self.remainMs <= 0){ //触发中
            if (self.alive){
                // printf("timer到时:%d\n", self.intervalMs)
                if (self.runFunc != null){
                    self.runFunc();
                }
            }

            if (self.isInterval){
                self.remainMs = self.intervalMs
            } else {
                self.alive = false
            }
        }
    }

    // return true if become fireing
    bool onTick(int dtMs){
        if (self.remainMs < 0){ //触发中
            return false;
        }
        self.remainMs = self.remainMs - dtMs

        //if (self.remainMs <= 0){
            //printf("timer到时:%d\n", self.intervalMs)
            ////self.runFunc()
        //}
        
        return self.remainMs < 0
    }
}
class TimerMgr {
    List@ items = new List()
    Mutex@ itemsMutex = new Mutex()

    List@ fireings = new List()
    Mutex@ fireingsMutex = new Mutex()

    void dtor(){
        printf("free TimerMgr:%p\n", self)
    }

    void addItemOnce(Timer* timer){
        self.itemsMutex.lock();
        if (!self.items.has(timer)){
            self.items.add(timer)
        }
        self.itemsMutex.unlock();
    }
    void addItem(Timer* timer){
        self.itemsMutex.lock();
        self.items.add(timer)
        self.itemsMutex.unlock();
    }
    //定时器回调触发
    void fire(){
        if (self.fireings.size() > 0){
            self.fireingsMutex.lock();
            int  l = self.fireings.size()
            // Timer* t = null;
            for (int i = 0; i < l; i++){
                Timer* timer = (Timer*)self.fireings.get(i);
                // t = timer;
                // urgc_report_sources_of(t);
                timer.fire();
            }
            self.fireings.clear()
            // printf("fireings.size:%d. fireings:%p,items:%p self:%p\n", self.fireings.size(), self.fireings, self.items, self);
            self.fireingsMutex.unlock();


            // for (int i = 0; i < 10; i++){

            // Time_sleepMs(100);
            // printf("fireings.size:%d. fireings:%p,items:%p self:%p\n", self.fireings.size(), self.fireings, self.items, self);
            // // printf("report sou...\n");
            // urgc_report_sources_of(t);
            // }

        }
    }

    //每个tick更新计时
    void tick(int dtMs){
        self.itemsMutex.lock();
        int  l = self.items.size()
        for (int i = 0; i < l; i++ ){
            Timer* timer = (Timer*)self.items.get(i);
            if (timer != null && timer.alive){
                bool fireing = timer.onTick(dtMs)
                if (fireing){
                    self.fireingsMutex.lock();
                    self.fireings.add(timer);
                    self.fireingsMutex.unlock();
                }
            }
        }
        self.clearDeadTimers()
        self.itemsMutex.unlock();
    }

    void clearDeadTimers(){
        for (int i = self.items.size() - 1; i >= 0; i--){
            Timer* timer = (Timer*)self.items.get(i);
            if (!timer.alive){
                self.items.removeAt(i)
                // printf("删除timer:%d\n", i)
            }
        }
        // printf("final size:%d. %d \n", self.fireings.size(), self.items.size());
    }

    void startThreadTick(){
        Thread@ t = new Thread()
        //TimerMgr@ tmp = self;
        t.runFunc = ^void (){
            long long prevMs = Time_unixMs()
            while (true){
                Time_sleepMs(60)
                long long nowMs = Time_unixMs()
                long long elapsedMs = nowMs - prevMs
                prevMs = nowMs
                //printf("elapsedms:%lld\n", elapsedMs)
                self.tick((int)elapsedMs)
            }
        }
        t.start()
    }
    void startThreadTickAndFire(){
        Thread@ t = new Thread()
        //TimerMgr@ tmp = self;
        t.runFunc = ^void (){
            long long prevMs = Time_unixMs()
            while (true){
                Time_sleepMs(16)
                long long nowMs = Time_unixMs()
                long long elapsedMs = nowMs - prevMs
                prevMs = nowMs
                //printf("elapsedms:%lld\n", elapsedMs)
                self.tick((int)elapsedMs)
                self.fire()
            }
        }
        t.start()
    }
}
TimerMgr@ insTimerMgr(){
    static TimerMgr@ mgr = null
    if (mgr == null){
        mgr = new TimerMgr();
        printf("==========实例化TimerMgr:%p\n", mgr)
    } 
    return mgr;
}

Timer@ mkTimerTimeout(^void() fn, int milliSecond){
    Timer@ t = new Timer();
    t.runFunc = fn
    t.intervalMs = milliSecond
    t.remainMs = milliSecond

    //TimerMgr@ mgr = insTimerMgr()
    //mgr.addItem(t)
    t.start()
    return t
}
Timer@ mkTimerInterval(^void() fn, int milliSecond){
    Timer@ t = new Timer();
    t.isInterval = true
    t.runFunc = fn
    t.intervalMs = milliSecond
    t.remainMs = milliSecond

    //TimerMgr@ mgr = insTimerMgr()
    //mgr.addItem(t)
    t.start()

    return t
}
Timer@ mkTimerInterval_noStart(^void() fn, int milliSecond){
    Timer@ t = new Timer();
    t.isInterval = true
    t.runFunc = fn
    t.intervalMs = milliSecond
    t.remainMs = milliSecond
    return t
}



List* gocAnimationFrameList(){
    static List@ animationFrameList = null;
    if (animationFrameList == null){
        animationFrameList = new List();
    }
    return animationFrameList
}
//[fn] return true if end
void requestAnimationFrame(^bool () fn){
    List* lst = gocAnimationFrameList();
    //不能用insert 0, 因为如果在定时器内部insert了，可能 导致误删除
    //这跟tickAimationFrames的循环方式有关
    // lst.insert(fn, 0) 
    lst.add((Object*)fn) 
}

void tickAnimationFrames(){
    List* lst = gocAnimationFrameList();
    int l = lst.size()
    if (l > 0){
        // printf("\n\n tick Animation Frame size:%d\n\n", l)
        for (int i = l - 1; i >= 0; i--){
            ^bool() fn = (^bool())lst.get(i)
            bool end = fn();
            if (end){
                lst.removeAt(i);
            }
        }
    }
}

//定速步进式float值动画
///*
//用法:
//
//AnimStep@ a = new AnimStep()
//a.start(^void(){
//    self.x = a.next(self.x, 100, 1)
//})
//
//*/
class AnimStep{
    ^void () update;
    bool running = false

    int runningCnt = 0

    long long elapsedMs = 0;
    long long prevElapsedMs = 0;
    long long prevMs = 0;

    void start(^void () fn){
        // printf("\n\nAnimStep.start\n\n")
        self.update = fn
        self._start()
    }
    //根据时长
    //问题：由于依赖prevElapsedMs, 如果上次动画未完成，就开新动画，可能导致跳变;此问题暂且忽略
    float nextByMs(float x, float to, float ms){
        //已经到位了
        if (absFloat(x - to) <= 0.0001){
            return to
        }

        //根据x, to, prevElapsedMs， ms 计算出初始的x
        // (to - from) * ratio + from = x
        // to * ratio - from * ratio + from = x
        // (1 - ratio) * from = x - to * ratio
        float ratio = self.prevElapsedMs / ms
        if (ratio >= 1.0){
            return to;
        }

        float f = (x - to * ratio) / (1 - ratio)
        float nowRatio = minFloat(1.0, self.elapsedMs / ms)
        float nv = lerpFloat(f, to, nowRatio)
        //printf("nextByMs x:%f, to:%f, ms:%f, elapsedMs:%lld ratio:%f, nowRatio:%f, f:%f, nv:%f\n"
        //, x, to, ms, self.elapsedMs, ratio, nowRatio, f, nv);
        if (nowRatio < 1.0){ 
            self.runningCnt = self.runningCnt + 1 //未完成
        }
        return nv
    }
    float next(float x, float to, float absStep){
        if (x == to 
        ){
            return to;
        }
        float step = absStep * (to - x > 0 ? 1 : -1)

        float nv = x + step
        float d0 = nv - to
        float d1 = to - x
        float m = d0 * d1
        bool isEnd = m >= 0 //说明异向，说明到位,说明结束了
        printf("\nx:%f, to:%f, step:%f, nv:%f, d0:%f, d1:%f, m:%f, isEnd:%d\n\n"
        , x, to, step
        , nv, d0, d1, m, isEnd)
        if (isEnd){
            nv = to
        } else {
            self.runningCnt = self.runningCnt + 1 //还未完成的数量
        }
        return nv
    }
    void tick(){
        long long nowMs = Time_unixMs()
        long long dMs = nowMs - self.prevMs
        self.elapsedMs = self.prevElapsedMs + dMs

        self.runningCnt = 0
        if (self.update != null){
            self.update()
        }
        self.running = self.runningCnt > 0 //还有属性未完成

        self.prevElapsedMs = self.elapsedMs
        self.prevMs = nowMs
    }
    void _start(){
        // printf("\n\nAnimStep _start:%d\n\n", self.running)
        if (self.running){
            return;
        }
        self.running = true
        self.elapsedMs = 0
        self.prevElapsedMs = 0
        self.prevMs = Time_unixMs()
        requestAnimationFrame(^bool (){
            // printf("tick AnimStepFloat\n");
            self.tick();
            return !self.running
        })
    }
    void cancel(){
        self.running = false
    }
}


class TimerTestEnt {
    int i = 1000;

    void dtor(){
        printf("释放TestEnt\n");
    }
}
void testTimer(){
    TimerMgr@ mgr = insTimerMgr()
    mgr.startThreadTickAndFire()
    Timer@ t = mkTimerTimeout(^void(){
        printf("timeout after 5s\n");
    }, 5000)
    t.name = str("测试")
    {
        TimerTestEnt@ ent = new TimerTestEnt()
        Timer@ t = mkTimerInterval(^void(){
            printf("interval i:%d, sec:%lld\n", ent.i, Time_unixSec());
            ent.i = ent.i + 1
            if (ent.i > 1010){
                t.cancel()
            }
        }, 1000)
    }
}

