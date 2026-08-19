#pragma once

#include "Predef.h"
#include "../Urgc/GcObj.h"

class Edge : public GcObj {
public:
	float w = 0.0f;
	int color = 0x00000000;

	void copyFrom(Edge* v) {
		w = v->w;
		color = v->color;
	}
	void set(float w, int color) {
		this->w = w;
		this->color = color;
	}
};
