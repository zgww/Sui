#include "./Time_orc.h"

#include <Windows.h>
#include <chrono>

void Orc$Time_sleepMs(int milliSecond) {
	Sleep(milliSecond);
}

long long  Orc$Time_unixMs() {
	auto ret = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	return ret;
}