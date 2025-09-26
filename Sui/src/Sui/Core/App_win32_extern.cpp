#include "App_orc.h"
#include <Windows.h>
#include "../../Orc/Time_orc.h"
#include <stdio.h>
#include <psapi.h>
#include <stdlib.h>

static void loopEvent() {
	MSG msg = { 0 };
	int cnt = 0;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		// printf("PeedMessage:%d. msg:%d, keydown:%d,%d, char=%d,%d wParam:%c\n", 
		// cnt++,
		// msg.message,
		// WM_KEYDOWN,
		// WM_KEYUP,
		// WM_CHAR,
		// WM_IME_CHAR,
		// (char)msg.wParam
		// );
		auto type = msg.message;
		if (type == WM_QUIT) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	// printf("PeedMessage: done\n");
}
void SuiCore$App$runEventLoop(SuiCore$App* self) {
	bool first_draw = false;
	//SDL_Event evt;
	//EventLoop loop;
	//auto styleEngine = NSStyleEngine::StyleEngine::ins();
	bool running = true;
	int frameIndex = 0;
	while (running) {
		if (frameIndex > 0) {
			//TimeStat::ins()->stat("loop start");
		}
		if (frameIndex % 30 == 0){
			// printf("frameIndex:%d\n", frameIndex);
		}
		// if (frameIndex % 300 == 0){
		// 	// malloc_stats();//打印内存信息 
		// 	HANDLE hProcess = GetCurrentProcess();
		// 	PROCESS_MEMORY_COUNTERS_EX pmc;
		// 	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);
		// 	if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))){
		// 		int WIDTH = 20;
		// 		float MB = 1024 * 1024.f;
		// 		printf("%*d -发生页错误次数\n", WIDTH, pmc.PageFaultCount);
		// 		printf("%*.2fMB -指定进程工作集内存峰值\n", WIDTH, pmc.PeakWorkingSetSize / MB);
		// 		printf("%*.2fMB -指定进程工作集内存\n", WIDTH, pmc.WorkingSetSize / MB);
		// 		printf("\n");
		// 		printf("%*.2fMB -指定进程已经提交的私有内存总量(PagefileUsage)\n", WIDTH, pmc.PagefileUsage / MB);
		// 		printf("%*.2fMB -指定进程已经提交的私有内存总量\n", WIDTH, pmc.PeakPagefileUsage / MB);
		// 		printf("%*.2fMB -指定进程已经提交的私有内存总量(PrivateUsage)\n", WIDTH, pmc.PrivateUsage / MB);
		// 	}
		// }
		long long startMs = Orc$Time_unixMs();
		loopEvent();
		SuiCore$App$processMessageList(self);
		//while (SDL_PollEvent(&evt)) {
		//	if (SDL_QUIT == evt.type) {
		//		return;
		//	}
		//	//printf("evt.type:%d %d\n", evt.type, SDL_APP_DIDENTERBACKGROUND);
		//	//if (evt.type == SDL_KEYDOWN) {
		//	//}
		//	handleEvent(this, evt);
		//}
		//if (!first_draw) {
		//	//TimeStat::ins()->stat("PollEvent");
		//}
		//Timer::tick_on_main_loop();
		//if (!first_draw) {
		//	//TimeStat::ins()->stat("Timer tick ");
		//}
		//run_cbs_on_ui_thread();

		//if (!first_draw) {
		//	/*string str = "run cbs on ui thread";
		//	str = str + std::to_string(cbs_on_ui_thread->size());
		//	TimeStat::ins()->stat(str);*/
		//}
		//ViewUniteCallback::handleBeforeDraw();

		//self->layoutAndDrawAllWindows(self);

		self->processDirtyReacts(self);

		if (self->_invalidDraw) {
			// self->_invalidDraw = false;
			self->layoutAndDrawAllWindows(self);
		}

		long long endMs = Orc$Time_unixMs();
		long long costMs = endMs - startMs;
		// 30帧即可
		long long sleepMs = 16 - costMs;
		// printf("sleepMs:%lld. costMs:%lld\n", sleepMs, costMs);

		long long tick = GetTickCount();
		while (true){
			long long nowtick = GetTickCount();
			long long passTick = nowtick - tick;
			if (passTick >= sleepMs){
				break;
			}
			Orc$Time_sleepMs(1);
			loopEvent();
		}
		// Orc$Time_sleepMs(15);
		// Orc$Time_sleepMs(sleepMs > 0 ? sleepMs : 0);
		frameIndex++;

		//run_cbs_after_draw();

		//if (!first_draw) {
		//	//TimeStat::ins()->stat("draw");
		//	//TimeStat::ins()->report();
		//	first_draw = true;
		//}
	}



    //while (true)
    //{
    //    HWND hasWin = FindWindowA(CLASS_NAME, NULL);

    //    if (!hasWin)
    //    {
    //        printf("no window opened\n");
    //        break;
    //    }
    //    /* bool ok = IsWindowEnabled(hasWin);
    //        printf("ok:%d\n", ok);*/
    //    pollMessage();
        //Sleep(5);
    //}
}