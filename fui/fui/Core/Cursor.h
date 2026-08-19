#pragma once

#include "Predef.h"

class Cursor : public GcObj {
public:
	bool isLocked = false;
	std::string cursor;

	void init();
	bool setCursor(const char* c);
	void setIsLocked(bool v);
	void _updateCursor();
};

Cursor* Cursor_ins();
