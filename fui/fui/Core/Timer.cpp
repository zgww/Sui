#include "Timer.h"
#include "Node.h"
#include "../Urgc/GcList.h"
#include <thread>

#include <rttr/registration>

void Timer::restart() {
	cancel();
	start();
}

void Timer::start() {
	if (alive) return;
	remainMs = intervalMs;
	alive = true;
	TimerMgr* mgr = insTimerMgr();
	mgr->addItemOnce(this);
}

void Timer::cancel() {
	alive = false;
}

void Timer::fire() {
	if (remainMs <= 0) {
		if (alive) {
			if (runFunc) {
				runFunc->invoke();
			}
		}
		if (isInterval) {
			remainMs = intervalMs;
		} else {
			alive = false;
		}
	}
}

bool Timer::onTick(int dtMs) {
	if (remainMs < 0) return false;
	remainMs -= dtMs;
	return remainMs < 0;
}

static Ref<TimerMgr> g_timerMgr;

// 保护 TimerMgr items/fireings 的复合操作（tick 遍历 / fire 遍历 / addItem 并发）。
// GcListWithLock 只保证单次方法内原子，跨方法复合遍历无整体锁，
// 主线程创建 Timer 与后台 tick 线程并发时会导致索引错位、Timer 丢失或
// vector 越界（表现：第二个 Timer 创建后其他 Timer 停止 fire）。
// 注意：不能用 TimerMgr 成员锁 —— rttr 反射要求类可拷贝（variant<T>），
// std::recursive_mutex 不可拷贝会触发 C2338 static_assert。
static std::recursive_mutex g_timerMutex;

TimerMgr* insTimerMgr() {
	if (!g_timerMgr) {
		g_timerMgr = new TimerMgr();
	}
	return g_timerMgr;
}

void TimerMgr::addItemOnce(Timer* timer) {
	std::lock_guard<std::recursive_mutex> g(g_timerMutex);
	if (!items->include(timer)) {
		items->push(timer);
	}
}

void TimerMgr::addItem(Timer* timer) {
	std::lock_guard<std::recursive_mutex> g(g_timerMutex);
	items->push(timer);
}

void TimerMgr::fire() {
	std::lock_guard<std::recursive_mutex> g(g_timerMutex);
	if (fireings->size() > 0) {
		int l = fireings->size();
		for (int i = 0; i < l; i++) {
			Timer* timer = fireings->get(i);
			if (timer) {
				timer->fire();
			}
		}
		fireings->clear();
	}
}

void TimerMgr::tick(int dtMs) {
	std::lock_guard<std::recursive_mutex> g(g_timerMutex);
	int l = items->size();
	for (int i = 0; i < l; i++) {
		Timer* timer = items->get(i);
		if (timer && timer->alive) {
			bool fireing = timer->onTick(dtMs);
			if (fireing) {
				fireings->push(timer);
			}
		}
	}
	clearDeadTimers();
}

void TimerMgr::clearDeadTimers() {
	std::lock_guard<std::recursive_mutex> g(g_timerMutex);
	for (int i = items->size() - 1; i >= 0; i--) {
		Timer* timer = items->get(i);
		if (timer && !timer->alive) {
			items->remove_at(i);
		}
	}
}

void TimerMgr::startThreadTick() {
	Ref<TimerMgr> self = this;
	std::thread([self]() {
		int64_t prevMs = time_unixMs();
		while (true) {
			time_sleepMs(60);
			int64_t nowMs = time_unixMs();
			int64_t elapsedMs = nowMs - prevMs;
			prevMs = nowMs;
			self->tick((int)elapsedMs);
		}
	}).detach();
}

void TimerMgr::startThreadTickAndFire() {
	Ref<TimerMgr> self = this;
	std::thread([self]() {
		int64_t prevMs = time_unixMs();
		while (true) {
			time_sleepMs(16);
			int64_t nowMs = time_unixMs();
			int64_t elapsedMs = nowMs - prevMs;
			prevMs = nowMs;
			self->tick((int)elapsedMs);
			self->fire();
		}
	}).detach();
}

Ref<Timer> mkTimerTimeout_notStart(Ref<Closure<void()>> fn, int milliSecond) {
	Ref<Timer> t{ new Timer() };
	t->runFunc = fn;
	t->intervalMs = milliSecond;
	t->remainMs = milliSecond;
	//t->start();
	return t;
}
Ref<Timer> mkTimerTimeout(Ref<Closure<void()>> fn, int milliSecond) {
	Ref<Timer> t{new Timer()};
	t->runFunc = fn;
	t->intervalMs = milliSecond;
	t->remainMs = milliSecond;
	t->start();
	return t;
}

Ref<Timer> mkTimerInterval(Ref<Closure<void()>> fn, int milliSecond) {
	Ref<Timer> t{new Timer()};
	t->isInterval = true;
	t->runFunc = fn;
	t->intervalMs = milliSecond;
	t->remainMs = milliSecond;
	t->start();
	return t;
}

Ref<Timer> mkTimerInterval_notStart(Ref<Closure<void()>> fn, int milliSecond) {
	Ref<Timer> t{new Timer()};
	t->isInterval = true;
	t->runFunc = fn;
	t->intervalMs = milliSecond;
	t->remainMs = milliSecond;
	return t;
}

void AnimStep::start(Ref<Closure<void()>> fn) {
	update = fn;
	_start();
}

float AnimStep::nextByMs(float x, float to, float ms) {
	if (absFloat(x - to) <= 0.0001f) return to;
	float ratio = (float)prevElapsedMs / ms;
	if (ratio >= 1.0f) return to;
	float f = (x - to * ratio) / (1 - ratio);
	float nowRatio = minFloat(1.0f, (float)elapsedMs / ms);
	float nv = lerpFloat(f, to, nowRatio);
	if (nowRatio < 1.0f) {
		runningCnt++;
	}
	return nv;
}

float AnimStep::next(float x, float to, float absStep) {
	if (x == to) return to;
	float step = absStep * (to - x > 0 ? 1 : -1);
	float nv = x + step;
	float d0 = nv - to;
	float d1 = to - x;
	float m = d0 * d1;
	bool isEnd = m >= 0;
	if (isEnd) {
		nv = to;
	} else {
		runningCnt++;
	}
	return nv;
}

void AnimStep::tick() {
	int64_t nowMs = time_unixMs();
	int64_t dMs = nowMs - prevMs;
	elapsedMs = prevElapsedMs + dMs;
	runningCnt = 0;
	if (update) {
		update->invoke();
	}
	running = runningCnt > 0;
	prevElapsedMs = elapsedMs;
	prevMs = nowMs;
}

void AnimStep::_start() {
	if (running) return;
	running = true;
	elapsedMs = 0;
	prevElapsedMs = 0;
	prevMs = time_unixMs();
	Ref<AnimStep> self = this;
	requestAnimationFrame(CLOSURE([=]() -> bool {
		self->tick();
		return !self->running;
	}));
}

void AnimStep::cancel() {
	running = false;
}

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Timer>("Timer")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("alive", &Timer::alive)
		.property("isInterval", &Timer::isInterval)
		.property("intervalMs", &Timer::intervalMs)
		.property("remainMs", &Timer::remainMs)
		.property("name", &Timer::name)
		.method("restart", &Timer::restart)
		.method("start", &Timer::start)
		.method("cancel", &Timer::cancel)
		.method("fire", &Timer::fire)
		.method("onTick", &Timer::onTick);

	registration::class_<TimerMgr>("TimerMgr")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.method("addItemOnce", &TimerMgr::addItemOnce)
		.method("addItem", &TimerMgr::addItem)
		.method("fire", &TimerMgr::fire)
		.method("tick", &TimerMgr::tick)
		.method("clearDeadTimers", &TimerMgr::clearDeadTimers)
		.method("startThreadTick", &TimerMgr::startThreadTick)
		.method("startThreadTickAndFire", &TimerMgr::startThreadTickAndFire);

	registration::class_<AnimStep>("AnimStep")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("running", &AnimStep::running)
		.property("runningCnt", &AnimStep::runningCnt)
		.property("elapsedMs", &AnimStep::elapsedMs)
		.property("prevElapsedMs", &AnimStep::prevElapsedMs)
		.property("prevMs", &AnimStep::prevMs)
		.method("start", &AnimStep::start)
		.method("nextByMs", &AnimStep::nextByMs)
		.method("next", &AnimStep::next)
		.method("tick", &AnimStep::tick)
		.method("_start", &AnimStep::_start)
		.method("cancel", &AnimStep::cancel);
}
