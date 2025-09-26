#include "./Clipboard_orc.h"


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <string>


#include <Naga/StrUtil.h>
#include <Naga/Utf8Util.h>



void SuiCore$clipboard_setText(char const * text){
	auto hwnd = GetDesktopWindow();

	AutoFree<wchar_t*> wstr = new_Utf8Util_toutf16(text);

	HANDLE hGlobalMemory = GlobalAlloc(GHND, (wcslen(wstr.data) + 1) * sizeof(wchar_t)); // 分配内存

	LPBYTE lpGlobalMemory = (LPBYTE)GlobalLock(hGlobalMemory); // 锁定内存
	memcpy(lpGlobalMemory, wstr.data, (wcslen(wstr.data)+1) * sizeof(wchar_t));
	GlobalUnlock(hGlobalMemory); // 锁定内存块解锁

	::OpenClipboard(hwnd); // 打开剪贴板
	::EmptyClipboard(); // 清空剪贴板
	//::SetClipboardData(CF_TEXT, hGlobalMemory); // 将内存中的数据放置到剪贴板
	::SetClipboardData(CF_UNICODETEXT, hGlobalMemory); // 将内存中的数据放置到剪贴板
	::CloseClipboard(); // 关闭剪贴板
}
Orc$String* SuiCore$clipboard_getText(Orc$String * * __outRef__){
	auto hwnd = GetDesktopWindow();
	::OpenClipboard(hwnd); // 打开剪贴板
	//::SetClipboardData(CF_TEXT, hGlobalMemory); // 将内存中的数据放置到剪贴板
	HGLOBAL hglb = ::GetClipboardData(CF_UNICODETEXT); // 将内存中的数据放置到剪贴板
	auto mem = GlobalLock(hglb);
	std::wstring wstr((wchar_t*)mem);
	//AutoFree<wchar_t*> wstr((wchar_t*)mem);

	GlobalUnlock(hglb);
	::CloseClipboard(); // 关闭剪贴板

	std::string str = new_Utf8Util_toutf8(wstr.c_str());

	return Orc$str(__outRef__, str.c_str());
}