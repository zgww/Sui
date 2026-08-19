#pragma once

#include "Predef.h"
#include "Node.h"

class TimerNode : public Node {
public:
	virtual const char* getClassName() const override { return "TimerNode"; }
};
