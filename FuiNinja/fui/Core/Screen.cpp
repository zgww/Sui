#include "Screen.h"

#ifdef _WIN32
#include <windows.h>

Vec2 Screen_get_usable_size() {
	return mkVec2((float)GetSystemMetrics(SM_CXFULLSCREEN), (float)GetSystemMetrics(SM_CYFULLSCREEN));
}

Vec2 Screen_get_size() {
	return mkVec2((float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN));
}
#else
Vec2 Screen_get_usable_size() { return mkVec2(1920, 1080); }
Vec2 Screen_get_size() { return mkVec2(1920, 1080); }
#endif
