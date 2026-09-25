

#include <string>
#include <vector>
#include <regex>

#include <algorithm>
#include "StrUtil.h"

//std::vector<std::string> StrUtil::split_by_re(std::string source,
//	std::string pattern) {
//
//	std::regex re(pattern);
//	std::vector<std::string> parts(
//		std::sregex_token_iterator(source.begin(), source.end(), re, -1),
//		std::sregex_token_iterator());
//	return parts;
//}
char* StrUtil_replace_by_re(const char* source, const char* pattern, const char* replaceStr)
{
	std::regex re(pattern);
	//auto ret = regex_replace(source, re, replaceStr, std::regex_constants::match_any);
	auto ret = regex_replace(source, re, replaceStr);

	return _strdup(ret.c_str());
}
char* StrUtil_trim(char* source0, char* eraseTarget) {
	std::string source(source0);

	if (source.empty())
	{
		return _strdup(source.c_str());
	}
	source.erase(0, source.find_first_not_of(eraseTarget));
	source.erase(source.find_last_not_of(eraseTarget) + 1);

	return _strdup(source.c_str());
}
bool StrUtil_starts_with(char* s, char* sub) {
	return std::string(s).find(sub) == 0;
}
bool StrUtil_ends_with(char* s0, char* sub0) {
	std::string s(s0);
	std::string sub(sub0);
	return s.rfind(sub) == s.length() - sub.length();
}
char* StrUtil_tolower(char* data0) {
	std::string data(data0);
	std::for_each(
		data.begin(),
		data.end(),
		[](char& c) {
			c = ::tolower(c);
		});
	return _strdup(data.c_str());
}
char* StrUtil_toupper(char* data0) {
	std::string data(data0);
	std::for_each(
		data.begin(),
		data.end(),
		[](char& c) {
			c = ::toupper(c);
		});
	return _strdup(data.c_str());
}

//std::string StrUtil::join(std::vector<std::string> strs, std::string separator)
//{
//	std::string out;
//	for (size_t i = 0, l = strs.size(); i < l; i++) {
//		out += strs[i];
//		if (i < l - 1) {
//			out += separator;
//		}
//	}
//	return out;
//}

char* StrUtil_insert_at(char* str0, int at, char* newstr) {
	std::string str(str0);
	auto pre = str.substr(0, at);
	auto post = str.substr(at);
	auto ret = pre + newstr + post;

	return _strdup(ret.c_str());
}
