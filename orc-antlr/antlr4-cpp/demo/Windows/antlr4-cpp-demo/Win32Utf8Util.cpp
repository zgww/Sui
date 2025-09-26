#include "Win32Utf8Util.h"
#include <Windows.h>

std::wstring Win32Utf8Util::acp_to_utf16(std::string str)
{
	if (str == "") return L"";
	// 计算缓冲区需要的大小, 如果函数成功, 则返回 UTF-8 字符数量, 所以无法确定具体字节数
	int cBuf = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	if (cBuf == 0) return L"(null)";
	wchar_t* buf = new wchar_t[cBuf * 4];// malloc(cBuf * 4);
	if (cBuf != MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buf, cBuf)) {
		delete[] buf;
		return L"";
	}
	std::wstring ret = buf;
	delete[] buf;
	return ret;
}

std::string Win32Utf8Util::acp_to_utf8(std::string str)
{
	auto wstr = acp_to_utf16(str);
	return Utf8Util::toutf8(wstr);
}
