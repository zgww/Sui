#include "Win32Utf8Util.h"
#include <Windows.h>
#include <string>
#include "./Utf8Util.h"



wchar_t* new_Win32Utf8Util_acpToUtf16(char* str0)
{
	std::string str(str0);
	if (str == "") return _wcsdup(L"");

	// 计算缓冲区需要的大小, 如果函数成功, 则返回 UTF-8 字符数量, 所以无法确定具体字节数
	int cBuf = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	if (cBuf == 0) return _wcsdup(L"(null)");

	wchar_t* buf = new wchar_t[cBuf * 4];// malloc(cBuf * 4);
	if (cBuf != MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buf, cBuf)) {
		delete[] buf;
		return _wcsdup(L"");
	}
	//std::wstring ret = buf;
	//delete[] buf;

	//return _wcsdup(ret.c_str());
	return buf;
}

char* new_Win32Utf8Util_acpToUtf8(char* str0)
{
	auto wstr = new_Win32Utf8Util_acpToUtf16(str0);
	auto ret = new_Utf8Util_toutf8(wstr);
	free(wstr);
	return ret;
}
