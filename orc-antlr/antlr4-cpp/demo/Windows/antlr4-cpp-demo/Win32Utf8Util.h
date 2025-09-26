#pragma once

#include "Utf8Util.h"
class Win32Utf8Util : public Utf8Util
{
public:
	//当前代码页转utf16
	static std::wstring acp_to_utf16(std::string str);
	static std::string acp_to_utf8(std::string str);
};

