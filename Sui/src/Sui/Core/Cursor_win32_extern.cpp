#include "./Cursor_orc.h"


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <string>


#include <Naga/StrUtil.h>
#include <Naga/Utf8Util.h>

HCURSOR arrow;
HCURSOR pointer;
HCURSOR sizewe;
HCURSOR sizens;
HCURSOR sizeall;


void SuiCore$Cursor$init(SuiCore$Cursor* self) {
	if (arrow) {
		return;
	}
	arrow = LoadCursor(NULL, IDC_ARROW);;
	pointer = LoadCursor(NULL, IDC_HAND);
	sizewe = LoadCursor(NULL, IDC_SIZEWE);
	sizens = LoadCursor(NULL, IDC_SIZENS);
	sizeall = LoadCursor(NULL, IDC_SIZEALL);
}
void SuiCore$Cursor$_updateCursor(SuiCore$Cursor* self) {
	self->init(self);
	auto real = self->cursor ;

	if (strcmp(real->str, "pointer") == 0) {
		SetCursor(pointer);
	}
	else if (strcmp(real->str, "sizewe") == 0) {
		SetCursor(sizewe);
	}
	else if (strcmp(real->str, "sizens") == 0) {
		SetCursor(sizens);
	}
	else if (strcmp(real->str, "sizeall") == 0) {
		SetCursor(sizeall);
	}
	else {
		SetCursor(arrow);
	}
}