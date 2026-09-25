#include "TimeUtil.h"
#include <chrono>




int64_t TimeUtil_unixMs() {

	auto ret = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	return ret;
}
int64_t TimeUtil_unixUs() {

	auto ret = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	return ret;
}