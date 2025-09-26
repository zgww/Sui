#pragma once


#include <string>
#include <vector>
#include <regex>

#include <algorithm>

class StrUtil
{
public:

	template<typename ... Args>
	static std::string format(const std::string &format, Args ... args)
	{
		auto size_buf = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		std::unique_ptr<char[]> buf(new(std::nothrow) char[size_buf]);

		if (!buf)
			return std::string("");

		std::snprintf(buf.get(), size_buf, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size_buf - 1);
	}

	static std::vector<std::string> split_by_re(std::string source,
		std::string pattern);
	static std::string replace_by_re(std::string source, std::string pattern, std::string replaceStr);
	static std::string trim(std::string source, std::string eraseTarget=" ");
	static bool starts_with(std::string s, std::string sub);
	static bool ends_with(std::string s, std::string sub);
	static std::string tolower(std::string data);
	static std::string toupper(std::string data);
	static std::string join(std::vector<std::string> strs, std::string separator);
	static std::string insert_at(std::string str, int at, std::string newstr);

	static std::string addPrefixPerLine(std::string str, std::string prefix);



	//逐字符匹配  通常用于代码提示时，匹配大写字符
	static bool matchChars_withOrder(std::string longStr, std::string shortStr);

};

