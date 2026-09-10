#pragma once

#include "Predef.h"
#include <rttr/rttr_enable.h>
#include "Node.h"

class TimerNode : public Node {
	RTTR_ENABLE(Node)
public:
	virtual const char* getClassName() const override { return "TimerNode"; }
};
