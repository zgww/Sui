#include "Naga/Utf8Util.h"
#include "Naga/StrUtil.h"
#include "./String_orc.h"
#include "./List_orc.h"
#include <regex>

int OrcLang$String$calcRuneSize(OrcLang$String* self) {
	return Utf8Util_length(self->str);
}

OrcLang$String* OrcLang$strByWcs(OrcLang$String** __outRef__, wchar_t const* data) {
	char* utf8 = new_Utf8Util_toutf8(data);
	OrcLang$String* str = OrcLang$String_new();
	str->add(str, utf8);
	free(utf8);

	return (OrcLang$String*)urgc_set_var_for_return((void**)__outRef__, str);
}

OrcLang$String* OrcLang$String_toActiveCodePage(OrcLang$String** __outRef__, const char *utf8){
	char* s = new_Utf8Util_utf8_to_active_code_page(utf8);

	URGC_NEW_VAR(OrcLang$String*, ret, OrcLang$String_new());
	ret->set_as_own(ret, s);

	return (OrcLang$String*)URGC_RETURN(ret);

}
OrcLang$String* OrcLang$String$_substringByCount(OrcLang$String** __outRef__, OrcLang$String* self, int start, int n){
	OrcLang$String* str = OrcLang$String_new();
	if (n == 0) {
		str->add(str, "");
	}
	else {
		char* utf8 = new_Utf8Util_substr(self->str, start, n);
		str->add(str, utf8);
		free(utf8);
	}
	return (OrcLang$String * )urgc_set_var_for_return((void**)__outRef__, str);
}


OrcLang$List* OrcLang$String$splitByRe(OrcLang$List** __outRef__, OrcLang$String* self, char const* pattern) {
	OrcLang$List* ret = OrcLang$List_new();

	std::string source(self->str);
	std::regex re(pattern);
	std::vector<std::string> parts(
		std::sregex_token_iterator(source.begin(), source.end(), re, -1),
		std::sregex_token_iterator());

	for (int i = 0; i < parts.size(); i++) {
		OrcLang$String* str = OrcLang$String_new();
		str->add(str, parts[i].c_str());
		ret->add(ret, (Object*)str);
	}
	return (OrcLang$List*)urgc_set_var_for_return((void**)__outRef__, ret);
}
int OrcLang$utf8RuneLength(char const* data) {
	if (!data) {
		return 0;
	}
	return Utf8Util_length(data);
}
int OrcLang$utf8CharLen(char const* data) {
	if (!data) {
		return 0;
	}
	return Utf8Util_charLen(data);
}


int OrcLang$utf8NumberCharLen(const char* data, int runeCnt) {
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

OrcLang$String* OrcLang$String$replaceAll(
	OrcLang$String * * __outRef__, 
	OrcLang$String * self, 
	char const * find, 
	char const * newStr){

	std::string source(self->str);
	std::string s = replace_all(source, std::string(find), std::string(newStr));

	OrcLang$String* ret = OrcLang$String_new();
	ret->add(ret, s.c_str());

	return (OrcLang$String*)urgc_set_var_for_return((void**)__outRef__, ret);
}
OrcLang$String* OrcLang$String$replaceAllByRe(
	OrcLang$String * * __outRef__, 
	OrcLang$String * self, 
	char const * pattern, 
	char const * newStr){

	std::string source(self->str);
	std::regex re(pattern);
	std::string replacement(newStr);
	std::string s = std::regex_replace(source, re, replacement);

	OrcLang$String* ret = OrcLang$String_new();
	ret->add(ret, s.c_str());

	return (OrcLang$String*)urgc_set_var_for_return((void**)__outRef__, ret);
}