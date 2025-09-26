

#include <string>
#include <vector>
#include <regex>

#include <algorithm>
#include "StrUtil.h"
#include <unordered_map>

//缓存正则
static std::regex* gocRegexByPattern(std::string pattern) {
	static std::unordered_map<std::string, std::regex*> regexMap;
	if (regexMap.contains(pattern)) {
		return regexMap[pattern];
	}
	std::regex *re = new std::regex(pattern);
	regexMap[pattern] = re;
	return regexMap[pattern];
}

std::vector<std::string> StrUtil::split_by_re(std::string source,
	std::string pattern) {

	std::regex* re = gocRegexByPattern(pattern);
	std::vector<std::string> parts(
		std::sregex_token_iterator(source.begin(), source.end(), *re, -1),
		std::sregex_token_iterator());
	return parts;
}
std::string StrUtil::replace_by_re(std::string source, std::string pattern, std::string replaceStr)
{
	//std::regex re(pattern);
	std::regex* re = gocRegexByPattern(pattern);
	//auto ret = regex_replace(source, re, replaceStr, std::regex_constants::match_any);
	auto ret = regex_replace(source, *re, replaceStr);

	return ret;
}
std::string StrUtil::trim(std::string source, std::string eraseTarget) {
	if (source.empty())
	{
		return source;
	}
	source.erase(0, source.find_first_not_of(eraseTarget));
	source.erase(source.find_last_not_of(eraseTarget) + 1);

	return source;
}
bool StrUtil::starts_with(std::string s, std::string sub) {
	return s.find(sub) == 0;
}
bool StrUtil::ends_with(std::string s, std::string sub) {
	return s.rfind(sub) == s.length() - sub.length();
}
std::string StrUtil::tolower(std::string data) {
	std::for_each(
		data.begin(),
		data.end(),
		[](char& c) {
			c = ::tolower(c);
		});
	return data;
}
std::string StrUtil::toupper(std::string data) {
	std::for_each(
		data.begin(),
		data.end(),
		[](char& c) {
			c = ::toupper(c);
		});
	return data;
}

std::string StrUtil::join(std::vector<std::string> strs, std::string separator)
{
	std::string out;
	for (size_t i = 0, l = strs.size(); i < l; i++) {
		out += strs[i];
		if (i < l - 1) {
			out += separator;
		}
	}
	return out;
}

std::string StrUtil::insert_at(std::string str, int at, std::string newstr) {
	auto pre = str.substr(0, at);
	auto post = str.substr(at);
	return pre + newstr + post;
}


std::string StrUtil::addPrefixPerLine(std::string str, std::string prefix)
{
	auto lines = split_by_re(str, "\n");
	for (int i = 0; i < lines.size(); i++) {
		lines[i] = prefix + lines[i];
	}
	auto ret = join(lines, "\n");
	return ret;
}

bool StrUtil::matchChars_withOrder(std::string longStr, std::string shortStr)
{
	if (longStr.size() < shortStr.size()) {
		return false;
	}
	if (longStr.size() == shortStr.size() && longStr == shortStr) {
		return true;
	}

	int ls = 0;
	for (int ss = 0; ss < shortStr.size(); ss++) {
		for (; ls < longStr.size(); ls++) {
			if (::tolower(longStr[ls]) == ::tolower(shortStr[ss])) {
				break;
			}
		}
		// 到了最后一个字符之后了，说明没有匹配成功
		if (ls >= longStr.size()) {
			return false;
		}
	}
	return true;
}
