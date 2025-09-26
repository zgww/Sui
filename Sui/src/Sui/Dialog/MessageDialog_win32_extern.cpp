#include "./MessageDialog_orc.h"


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <string>


#include <Naga/StrUtil.h>
#include <Naga/Utf8Util.h>



void SuiDialog$MessageDialog_alert(char const* content, char const* title) {
	AutoFree<wchar_t*> wcontent = new_Utf8Util_toutf16(content);
	AutoFree<wchar_t*> wtitle = new_Utf8Util_toutf16(title);
	HWND win = GetActiveWindow();
	MessageBoxW(win, wcontent.data, wtitle.data, MB_OK | MB_ICONINFORMATION);
}
void SuiDialog$MessageDialog_alert_error(char const* content, char const* title) {
	AutoFree<wchar_t*> wcontent = new_Utf8Util_toutf16(content);
	AutoFree<wchar_t*> wtitle = new_Utf8Util_toutf16(title);
	MessageBoxW(GetActiveWindow(), wcontent.data, wtitle.data, MB_OK | MB_ICONERROR);

}
void SuiDialog$MessageDialog_alert_warn(char const* content, char const* title) {
	AutoFree<wchar_t*> wcontent = new_Utf8Util_toutf16(content);
	AutoFree<wchar_t*> wtitle = new_Utf8Util_toutf16(title);
	MessageBoxW(GetActiveWindow(), wcontent.data, wtitle.data, MB_OK | MB_ICONWARNING);
}
bool SuiDialog$MessageDialog_confirm(char const* content, char const* title) {
	AutoFree<wchar_t*> wcontent = new_Utf8Util_toutf16(content);
	AutoFree<wchar_t*> wtitle = new_Utf8Util_toutf16(title);
	auto ret = MessageBoxW(GetActiveWindow(), wcontent.data, wtitle.data, MB_OKCANCEL | MB_ICONWARNING);
	if (ret == IDOK){
		return true;
	}
	return false;
}
/*
extern "C" void testSuiDialog() {
	SuiDialog$MessageDialog_alert("hi222", "title");
	SuiDialog$MessageDialog_alert_error("hi中文内容", "title");
	SuiDialog$MessageDialog_alert_warn("hi", "中文");
	SuiDialog$MessageDialog_alert("hi内容", "title标234234题");

}*/
