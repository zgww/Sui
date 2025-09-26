#pragma once
#include <stdlib.h>
template <typename T>
class Result {
public:
	Result() {
	}
	Result(T v) {
		succ = true;
		result = v;
	}

	T result;
	const char* msg = NULL;
	bool succ = false;
};
