#pragma once

#include "Predef.h"
#include "../Urgc/GcObj.h"

struct Radius  {
public:
	float tl = 0.0f;
	float tr = 0.0f;
	float bl = 0.0f;
	float br = 0.0f;

	void setAll(float r) {
		tl = r;
		tr = r;
		bl = r;
		br = r;
	}
};
