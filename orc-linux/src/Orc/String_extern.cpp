#include "Naga/Utf8Util.h"
#include "Naga/StrUtil.h"
#include "./String_orc.h"
#include "./List_orc.h"
#include "Orc/Orc.h"
#include <regex>
#include <stdarg.h>

int Orc$String$calcRuneSize(Orc$String* self) {
	return Utf8Util_length(self->str);
}

Orc$String* Orc$strByWcs(Orc$String** __outRef__, wchar_t const* data) {
	char* utf8 = new_Utf8Util_toutf8(data);
	NEW_CLASS_VAR(Orc$String, str);
	Orc$String$add(str, utf8);
	free(utf8);

	return (Orc$String*)urgc_set_var_for_return((void**)__outRef__, str);
}

Orc$String*  Orc$strf(Orc$String **  __outRef__, const char *  format, ...){
	NEW_CLASS_VAR(Orc$String, str);

	if (!format || !*format) {
		return (Orc$String*)URGC_RETURN_CLASS(str);
    }

    va_list args;
    va_start(args, format);

    // 先计算所需长度
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    if (length < 0) {
		return (Orc$String*)URGC_RETURN_CLASS(str);
    }

    // 分配内存 (+1 是为了结尾的 '\0')
    char *buffer = (char*)malloc(length + 1);
    if (!buffer) {
		return (Orc$String*)URGC_RETURN_CLASS(str); // 内存分配失败
    }

    va_start(args, format);
    vsnprintf(buffer, length + 1, format, args);
    va_end(args);

	Orc$String$set_as_own(str, buffer);

	return (Orc$String*)URGC_RETURN_CLASS(str); // 内存分配失败
}
Orc$String* Orc$String_toActiveCodePage(Orc$String** __outRef__, const char *utf8){
	char* s = new_Utf8Util_utf8_to_active_code_page(utf8);

	NEW_CLASS_VAR(Orc$String, ret);
	Orc$String$set_as_own(ret, s);

	return (Orc$String*)URGC_RETURN_CLASS(ret);

}
Orc$String* Orc$String$_substringByCount(Orc$String** __outRef__, Orc$String* self, int start, int n){
	NEW_CLASS_VAR(Orc$String, str);
	if (n == 0) {
		Orc$String$add(str, "");
	}
	else {
		char* utf8 = new_Utf8Util_substr(self->str, start, n);
		Orc$String$add(str, utf8);
		free(utf8);
	}
	return (Orc$String * )urgc_set_var_for_return((void**)__outRef__, str);
}


Orc$List* Orc$String$splitByRe(Orc$List** __outRef__, Orc$String* self, char const* pattern) {
	NEW_CLASS_VAR( Orc$List, ret );

	std::string source(self->str);
	std::regex re(pattern);
	std::vector<std::string> parts(
		std::sregex_token_iterator(source.begin(), source.end(), re, -1),
		std::sregex_token_iterator());

	for (int i = 0; i < parts.size(); i++) {
		NEW_CLASS_VAR(Orc$String, str);
		Orc$String$add(str, parts[i].c_str());
		ret->add(ret, (Object*)str);
	}
	return (Orc$List*)urgc_set_var_for_return((void**)__outRef__, ret);
}
int Orc$utf8RuneLength(char const* data) {
	if (!data) {
		return 0;
	}
	return Utf8Util_length(data);
}
int Orc$utf8CharLen(char const* data) {
	if (!data) {
		return 0;
	}
	return Utf8Util_charLen(data);
}


int Orc$utf8NumberCharLen(const char* data, int runeCnt) {
	if (!data) {
		return 0;
	}
	return Utf8Util_numCharLen(data, runeCnt);
}

static std::string& replace_all(
	std::string& str,
	const std::string& old_value,
	const std::string& new_value)
{
	int offset = 0;
    while(true) {
        int pos=0;
        if((pos=str.find(old_value, offset)) != std::string::npos){
            str.replace(pos, old_value.length(),new_value);
			offset = pos + new_value.length();
		}
        else {
			break;
		}
    }
    return str;
}

Orc$String* Orc$String$replaceAll(
	Orc$String * * __outRef__, 
	Orc$String * self, 
	char const * find, 
	char const * newStr){

	std::string source(self->str);
	std::string s = replace_all(source, std::string(find), std::string(newStr));

	NEW_CLASS_VAR(Orc$String, ret);
	Orc$String$add(ret, s.c_str());

	return (Orc$String*)urgc_set_var_for_return((void**)__outRef__, ret);
}
Orc$String* Orc$String$replaceAllByRe(
	Orc$String * * __outRef__, 
	Orc$String * self, 
	char const * pattern, 
	char const * newStr){

	std::string source(self->str);
	std::regex re(pattern);
	std::string replacement(newStr);
	std::string s = std::regex_replace(source, re, replacement);

	NEW_CLASS_VAR(Orc$String, ret);
	Orc$String$add(ret, s.c_str());

	return (Orc$String*)urgc_set_var_for_return((void**)__outRef__, ret);
}