#include "Cursor.h"

#ifdef _WIN32
#include <windows.h>
#endif

static Ref<Cursor> g_cursor;

Cursor* Cursor_ins() {
	if (!g_cursor) {
		g_cursor = new Cursor();
		g_cursor->init();
	}
	return g_cursor;
}

#ifdef _WIN32
static HCURSOR g_hArrow = nullptr;
static HCURSOR g_hPointer = nullptr;
static HCURSOR g_hSizeWE = nullptr;
static HCURSOR g_hSizeNS = nullptr;
static HCURSOR g_hSizeAll = nullptr;

void Cursor::init() {
	g_hArrow = LoadCursor(nullptr, IDC_ARROW);
	g_hPointer = LoadCursor(nullptr, IDC_HAND);
	g_hSizeWE = LoadCursor(nullptr, IDC_SIZEWE);
	g_hSizeNS = LoadCursor(nullptr, IDC_SIZENS);
	g_hSizeAll = LoadCursor(nullptr, IDC_SIZEALL);
}

bool Cursor::setCursor(const char* c) {
	if (isLocked) return false;
	cursor = c;
	_updateCursor();
	return true;
}

void Cursor::setIsLocked(bool v) {
	isLocked = v;
}

void Cursor::_updateCursor() {
	if (cursor == "pointer") {
		SetCursor(g_hPointer);
	} else if (cursor == "sizewe") {
		SetCursor(g_hSizeWE);
	} else if (cursor == "sizens") {
		SetCursor(g_hSizeNS);
	} else if (cursor == "sizeall") {
		SetCursor(g_hSizeAll);
	} else {
		SetCursor(g_hArrow);
	}
}
#else
void Cursor::init() {}
bool Cursor::setCursor(const char* c) { if (isLocked) return false; cursor = c; return true; }
void Cursor::setIsLocked(bool v) { isLocked = v; }
void Cursor::_updateCursor() {}
#endif
