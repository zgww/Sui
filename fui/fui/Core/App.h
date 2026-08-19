#pragma once

#include "Predef.h"
#include <mutex>
#include "../Urgc/GcList.h"

class Window;
class Node;
class Timer;

class AppEventLoopMessage : public GcObj {
};

class App : public GcObj {
public:
	Ref<GcList<Window>> windows{new GcList<Window>(), this};
	std::recursive_mutex messageList_mutex;
	Ref<GcList<AppEventLoopMessage>> messageList{new GcList<AppEventLoopMessage>(), this};

	Window* findWindowById(int64_t id);
	void addWindow(Window* win);
	void eachWindow(Ref<Closure<void(Window*)>> onWin);
	void removeWindow(Window* win);
	void layoutAndDrawAllWindows();
	void quit();

	bool _invalidDraw = false;

	void invalidDraw();
	void invalidLayout();
	void processDirtyReacts();
	void processRecuDirtyReacts(Node* n);
	void postMessage_toEventLoop_threadSafe(Ref<AppEventLoopMessage> msg);
	Ref<AppEventLoopMessage> peekFromMessageList();
	void processMessageList();
	void init();
	void runEventLoop();
};

App* App_use();
void App_onDestroyWindow(int64_t id);
bool App_repaintWindowById(int64_t id);
