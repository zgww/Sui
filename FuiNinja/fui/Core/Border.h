#pragma once

#include "Predef.h"
#include "Edge.h"

struct Border  {
public:
	Edge t;
	Edge r;
	Edge b;
	Edge l;

	bool isAllHasWidth() const {
		return t.w > 0 && r.w > 0 && b.w > 0 && l.w > 0;
	}

	void copyFrom(Border* other) {
		t.copyFrom(&other->t);
		r.copyFrom(&other->r);
		b.copyFrom(&other->b);
		l.copyFrom(&other->l);
	}

	void setAll(float w, int color) {
		t.w = w; t.color = color;
		r.w = w; r.color = color;
		b.w = w; b.color = color;
		l.w = w; l.color = color;
	}

	float hor() const { return l.w + r.w; }
	float ver() const { return t.w + b.w; }
};
