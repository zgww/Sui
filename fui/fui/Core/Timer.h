#pragma once

#include "Predef.h"

class Timer : public GcObj {
public:
	Ref<Closure<void()>> runFunc{nullptr, this};

	bool alive = false;
	bool isInterval = false;
	int intervalMs = 0;
	int remainMs = 0;
	std::string name;

	void restart();
	void start();
	void cancel();
	void fire();
	bool onTick(int dtMs);
};

class TimerMgr : public GcObj {
public:
	Ref<GcListWithLock<Timer>> items{new GcListWithLock<Timer>(), this};
	Ref<GcListWithLock<Timer>> fireings{new GcListWithLock<Timer>(), this};

	void addItemOnce(Timer* timer);
	void addItem(Timer* timer);
	void fire();
	void tick(int dtMs);
	void clearDeadTimers();
	void startThreadTick();
	void startThreadTickAndFire();
};

TimerMgr* insTimerMgr();
Ref<Timer> mkTimerTimeout(Ref<Closure<void()>> fn, int milliSecond);
Ref<Timer> mkTimerInterval(Ref<Closure<void()>> fn, int milliSecond);
Ref<Timer> mkTimerInterval_noStart(Ref<Closure<void()>> fn, int milliSecond);

class AnimStep : public GcObj {
public:
	Ref<Closure<void()>> update{nullptr, this};
	bool running = false;
	int runningCnt = 0;
	int64_t elapsedMs = 0;
	int64_t prevElapsedMs = 0;
	int64_t prevMs = 0;

	void start(Ref<Closure<void()>> fn);
	float nextByMs(float x, float to, float ms);
	float next(float x, float to, float absStep);
	void tick();
	void _start();
	void cancel();
};
