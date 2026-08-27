

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

std::string Str::lower(std::string data0) {
	std::string data(data0);
	std::for_each(
		data.begin(),
		data.end(),
		[](char& c) {
			c = ::tolower(c);
		});
	return data;
}
bool Str::startsWith(const char* s, const char* find) {
	if (s == nullptr || find == nullptr) {
		return false;
	}
	int slen = strlen(s);
	int findLen = strlen(find);
	if (slen < findLen) {
		return false;
	}
	for (int i = 0; i < findLen; i++) {
		if (s[i] != find[i]) {
			return false;
		}
	}
	return true;
}
//注意，返回的是以字节为单位的
int Str::lastIndexByteOf(std::string source, const char* cstr) {
	if ( cstr == nullptr || strlen(cstr) == 0) {
		return -1;
	}
	for (int i = source.size() - 1; i >= 0; i--) {
		bool ok = Str::startsWith( source.c_str() + i, cstr);
		if (ok) {
			return i;
		}
	}
	return -1;
}


static std::string& replace_all(
	std::string& str,
	const std::string& old_value,
	const std::string& new_value)
{
	int offset = 0;
	while (true) {
		int pos = 0;
		if ((pos = str.find(old_value, offset)) != std::string::npos) {
			str.replace(pos, old_value.length(), new_value);
			offset = pos + new_value.length();
		}
		else {
			break;
		}
	}
	return str;
}

std::string Str::replaceAll(
	std::string source,
	char const* find,
	char const* newStr) {

	std::string s = replace_all(source, std::string(find), std::string(newStr));
	return s;
}
std::string  Str::replaceAllByRe(
	std::string source,
	char const* pattern,
	char const* newStr) {

	std::regex re(pattern);
	std::string replacement(newStr);
	std::string s = std::regex_replace(source, re, replacement);

	return s;
}

std::vector<std::string> Str::splitToLines(std::string content) {
	std::vector<std::string> ret;
	int start = 0;
	int len = content.size();
	for (int i = 0; i < len; i++) {
		if (content[i] == '\n' || content[i] == '\r') {
			std::string line = content.substr(start, i - start);// self.substringByByteRange(start, i);
			ret.push_back(line);

			if (content[i] == '\r' && i + 1 < len && content[i + 1] == '\n') {
				i++;
			}
			start = i + 1; //跳过换行符
		}
	}

	return ret;
}
std::vector<std::string> Str::splitByRe(std::string source, char const* pattern) {
	std::vector<std::string> ret;
	std::regex re(pattern);
	std::vector<std::string> parts(
		std::sregex_token_iterator(source.begin(), source.end(), re, -1),
		std::sregex_token_iterator());

	for (int i = 0; i < parts.size(); i++) {
		ret.push_back(parts[i]);
	}
	return ret;
}


std::string Str::join(std::vector<std::string>& strs, std::string sep) {
	std::string ret = "";
	for (int i = 0, l = strs.size(); i < l; i++) {
		ret += strs[i];
	}
	return ret;
}