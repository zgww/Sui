#include "App.h"
#include "Window.h"
#include "Node.h"
#include "ViewBase.h"
#include "Timer.h"
#include "../Urgc/GcList.h"
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif

static Ref<App> g_app;

App* App_use() {
	if (!g_app) {
		g_app = new App();
		g_app->init();
	}
	return g_app;
}

Window* App::findWindowById(int64_t id) {
	for (int i = 0; i < windows->size(); i++) {
		Window* window = windows->get(i);
		if (window && window->id == id) {
			return window;
		}
	}
	return nullptr;
}

void App::addWindow(Window* win) {
	windows->push(win);
}

void App::eachWindow(Ref<Closure<void(Window*)>> onWin) {
	for (int i = 0; i < windows->size(); i++) {
		Window* window = windows->get(i);
		if (window && onWin) {
			onWin->invoke(window);
		}
	}
}

void App::removeWindow(Window* win) {
	if (!win) return;

	if (win->onClosed) {
		win->onClosed->invoke(win);
	}

	windows->remove(win);

	if (win->rootView) {
		win->rootView->dissolveSubtree();
		win->setRootView(nullptr);
	}

	if (windows->size() == 0) {
		printf("App.windows.size == 0\n");
		quit();
	}
}

void App::layoutAndDrawAllWindows() {
	for (int i = 0; i < windows->size(); i++) {
		Window* win = windows->get(i);
		if (win) {
			win->layoutAndDraw();
		}
	}
}

void App::quit() {
	exit(0);
}

void App::invalidDraw() {
	_invalidDraw = true;
}

void App::invalidLayout() {
	_invalidDraw = true;
}

void App::processDirtyReacts() {
	// Simplified - react processing
	for (int i = 0; i < windows->size(); i++) {
		Window* win = windows->get(i);
		if (win && win->rootView) {
			processRecuDirtyReacts(win->rootView);
		}
	}
}

void App::processRecuDirtyReacts(Node* n) {
	if (!n) return;
	if (n->_reactDirty) {
		n->_reactDirty = false;
		n->react();
	}
	int l = n->getChildrenCount();
	for (int i = 0; i < l; i++) {
		Node* kid = n->getChild(i);
		if (kid) {
			processRecuDirtyReacts(kid);
		}
	}
}

void App::postMessage_toEventLoop_threadSafe(Ref<AppEventLoopMessage> msg) {
	messageList_mutex.lock();
	messageList->push(msg);
	messageList_mutex.unlock();
}

Ref<AppEventLoopMessage> App::peekFromMessageList() {
	messageList_mutex.lock();
	Ref<AppEventLoopMessage> msg;
	if (messageList->size() > 0) {
		msg = messageList->get(0);
		messageList->remove_at(0);
	}
	messageList_mutex.unlock();
	return msg;
}

void App::processMessageList() {
	while (true) {
		Ref<AppEventLoopMessage> msg = peekFromMessageList();
		if (!msg) break;
	}

	TimerMgr* mgr = insTimerMgr();
	if (mgr) {
		mgr->fire();
	}
	tickAnimationFrames();
}

void App::init() {
	TimerMgr* mgr = insTimerMgr();
	if (mgr) {
		mgr->startThreadTick();
	}
}

#ifdef _WIN32
void App::runEventLoop() {
	for (;;) {
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		processMessageList();
		processDirtyReacts();

		if (_invalidDraw) {
			_invalidDraw = false;
			layoutAndDrawAllWindows();
		}

		Sleep(1);
	}
}
#else
void App::runEventLoop() {
	while (true) {
		processMessageList();
		processDirtyReacts();
		if (_invalidDraw) {
			_invalidDraw = false;
			layoutAndDrawAllWindows();
		}
		time_sleepMs(16);
	}
}
#endif

void App_onDestroyWindow(int64_t id) {
	App* app = App_use();
	Window* win = app->findWindowById(id);
	if (!win) return;
	app->removeWindow(win);
}

bool App_repaintWindowById(int64_t id) {
	if (!id) return false;
	App* app = App_use();
	Window* win = app->findWindowById(id);
	if (!win) return false;
	win->layoutAndDraw();
	return true;
}
