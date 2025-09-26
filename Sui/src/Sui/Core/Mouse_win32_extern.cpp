#include "./Mouse_orc.h"


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <string>


#include <Naga/StrUtil.h>
#include <Naga/Utf8Util.h>




SuiCore$Vec2 SuiCore$Mouse_getPos() {
	POINT point;
	GetCursorPos(&point);
	return SuiCore$mkVec2(point.x, point.y);
}
