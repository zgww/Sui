#include "./Time_orc.h"

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif
#include <chrono>

void Orc$Time_sleepMs(int milliSecond) {
    #ifdef _WIN32
    	Sleep(milliSecond);
    #else
        usleep(milliSecond * 1000);
    #endif
}

long long  Orc$Time_unixMs() {
	auto ret = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	return ret;
}