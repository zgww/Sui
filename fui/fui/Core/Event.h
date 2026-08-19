#pragma once

#include "Predef.h"
#include "../Urgc/GcObj.h"

class Event : public GcObj {
public:
	std::string name;
	int isStopPropagation = 0;

	void stopPropagation() { isStopPropagation = 1; }
	void stopImmediatePropagation() { isStopPropagation = 2; }
};
