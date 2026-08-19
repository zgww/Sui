#pragma once

#include "Predef.h"
#include "../Urgc/GcObj.h"

class BoxShadow : public GcObj {
public:
	float dx = 0.0f;
	float dy = 0.0f;
	float sigmaX = 0.0f;
	float sigmaY = 0.0f;
	int color = 0;
};
