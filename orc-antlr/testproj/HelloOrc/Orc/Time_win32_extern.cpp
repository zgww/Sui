#include "./Time_orc.h"

#include <Windows.h>
#include <chrono>

void OrcLang$Time_sleepMs(int milliSecond) {
	Sleep(milliSecond);
}

long long  OrcLang$Time_unixMs() {
	auto ret = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	return ret;
}