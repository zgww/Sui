

#include <string> 
#include "Utf8Util.h"


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef min
#undef max
#endif


const unsigned char kFirstBitMask = 128; // 1000000
const unsigned char kSecondBitMask = 64; // 0100000
const unsigned char kThirdBitMask = 32; // 0010000
const unsigned char kFourthBitMask = 16; // 0001000
const unsigned char kFifthBitMask = 8; // 0000100

//wchar_t* _strdup_wstring(const wchar_t * ret) {
//	wchar_t* data = (wchar_t*)malloc((ret.size() + 2) * sizeof(wchar_t));
//	memcpy(data, ret.c_str(), ret.size() * sizeof(wchar_t));
//	data[ret.size()] = 0;
//	return data;
//}

int Utf8Util_charLen(const char* str) {
	char firstByte = str[0];
	int offset = 1;

	if (firstByte & kFirstBitMask) // This means the first byte has a value greater than 127, and so is beyond the ASCII range.
	{
		if (firstByte & kThirdBitMask) // This means that the first byte has a value greater than 224, and so it must be at least a three-octet code point.
		{
			if (firstByte & kFourthBitMask) // This means that the first byte has a value greater than 240, and so it must be a four-octet code point.
				offset = 4;
			else
				offset = 3;
		}
		else
		{
			offset = 2;
		}
	}
	return offset;
}
int Utf8Util_numCharLen(const char* str, int n) {
	int len = 0;
	for (int i = 0; *str && i < n; i++) {
		int cl = Utf8Util_charLen(str);
		str += cl;
		len += cl;
	}
	return len;
}
int Utf8Util_length(const char * str) {
	int len = 0;
	auto cur = str;// str.c_str();
	while (*cur) {
		len++;
		int cl = Utf8Util_charLen(cur);
		cur += cl;
	}
	return len;
}

//取指定位置字符的字节偏移
int Utf8Util_byteOffsetAt(const char * text, int rune_offset) {
	const char* str = text;// .c_str();
	const char* tmp = str;

	for (int i = 0; *tmp && i < rune_offset; i++) {
		int cl = Utf8Util_charLen(tmp);
		tmp += cl;
	}

	return tmp - str;
}

char* new_Utf8Util_substr(const char * text0, int at, int n) {
	std::string text(text0);
	const char* str = text.c_str();

	if (n == 0) {
		return _strdup("");
	}
	if (at < 0) at = 0;
	int len = Utf8Util_length(text.c_str());

	if (n < 0) {
		n = len;
	}

	if (at >= len) return _strdup("");

	int start = Utf8Util_byteOffsetAt(text.c_str(), at);
	int max_n = len - at;
	n = n > max_n ? max_n : n;

	int end_n = Utf8Util_numCharLen(str + start, n);
	auto ret = text.substr(start, end_n);

	return _strdup(ret.c_str());
}
char* new_Utf8Util_insert_at(char* str, int at, char * newstr) {
	auto pre = new_Utf8Util_substr(str, 0, at);
	auto post = new_Utf8Util_substr(str, at, -1);
	auto ret = std::string(pre) + newstr + post;
	free(pre);
	free(post);

	//return pre + newstr + post;
	return _strdup(ret.c_str());
}
std::string _concat(std::string a, std::string b) {
	return a + b;
}
char* new_Utf8Util_backspace(char* str, int at, int cnt) {
	auto pre = new_Utf8Util_substr(str, 0, at - cnt);
	auto post = new_Utf8Util_substr(str, at, -1);
	auto ret = _concat(pre, post);
	free(pre);
	free(post);

	return _strdup(ret.c_str());
}
char* new_Utf8Util_delete_rune(const char* str, int at, int cnt) {
	auto pre = new_Utf8Util_substr(str, 0, at);
	auto post = new_Utf8Util_substr(str, at+cnt, -1);

	auto ret = _concat(pre, post);

	free(pre);
	free(post);

	return _strdup(ret.c_str());
}
STATIC wchar_t* new_Utf8Util_toutf16(const char* str) {
#ifdef _WIN32
	if (str == "") return _wcsdup(L"");
	 
	// 计算缓冲区需要的大小, 如果函数成功, 则返回 UTF-8 字符数量, 所以无法确定具体字节数
	int cBuf = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	if (cBuf == 0) return _wcsdup(L"(null)");
	wchar_t* buf = (wchar_t*)calloc(cBuf * 4, 1);// malloc(cBuf * 4);
	if (cBuf != MultiByteToWideChar(CP_UTF8, 0, str, -1, buf, cBuf)) {
		delete [] buf;
		return _wcsdup(L"");
	}
	//std::wstring ret = buf;
	//delete [] buf;
	return buf;
	//return _strdup_wstring(buf);// ret;
#else//其他平台统一走utf8
	return _strdup_wstring(L"");
#endif
}

char* new_Utf8Util_utf8_to_active_code_page(const char* str) {
	auto utf16 = new_Utf8Util_toutf16(str);
	auto ret = new_Utf8Util_utf16_to_active_code_page(utf16);
	free(utf16);
	return ret;
}
char* new_Utf8Util_utf16_to_active_code_page(const wchar_t* str) {
#ifdef _WIN32
	if (str == L"") return _strdup("");
	// 计算缓冲区需要的大小, 如果函数成功, 则返回具体字节数, 所以 cBuf 至少是 1 (UTF-8以0x00结尾)
	int cBuf = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	if (cBuf < 1) return _strdup("");
	char* buf = (char*)calloc( cBuf, 1) ; // 分配缓冲区
	if (cBuf != WideCharToMultiByte(CP_ACP, 0, str, -1, buf, cBuf, NULL, NULL)) {
		//delete[] buf;
		free(buf);
		return _strdup("");
	}
	//std::string ret = buf;
	//delete[] buf;
	//return ret;
	return buf;
#else
	return "";
#endif
}
STATIC char * new_Utf8Util_toutf8(const wchar_t* str) {
#ifdef _WIN32
	if (str == L"") return _strdup("");
	// 计算缓冲区需要的大小, 如果函数成功, 则返回具体字节数, 所以 cBuf 至少是 1 (UTF-8以0x00结尾)
	int cBuf = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	if (cBuf < 1) return _strdup("");
	char* buf = new char [cBuf] ; // 分配缓冲区
	if (cBuf != WideCharToMultiByte(CP_UTF8, 0, str, -1, buf, cBuf, NULL, NULL)) {
		delete[] buf;
		return _strdup("");
	}
	//std::string ret = buf;
	//delete[] buf;
	return buf;
#else
	return "";
#endif
}

char*
new_Utf8Util_utf32ToUtf8(uint32_t codepoint)
{
	char text[5] = { 0 };
	if (codepoint <= 0x7F) {
		text[0] = (char)codepoint;
		text[1] = '\0';
	}
	else if (codepoint <= 0x7FF) {
		text[0] = 0xC0 | (char)((codepoint >> 6) & 0x1F);
		text[1] = 0x80 | (char)(codepoint & 0x3F);
		text[2] = '\0';
	}
	else if (codepoint <= 0xFFFF) {
		text[0] = 0xE0 | (char)((codepoint >> 12) & 0x0F);
		text[1] = 0x80 | (char)((codepoint >> 6) & 0x3F);
		text[2] = 0x80 | (char)(codepoint & 0x3F);
		text[3] = '\0';
	}
	else if (codepoint <= 0x10FFFF) {
		text[0] = 0xF0 | (char)((codepoint >> 18) & 0x0F);
		text[1] = 0x80 | (char)((codepoint >> 12) & 0x3F);
		text[2] = 0x80 | (char)((codepoint >> 6) & 0x3F);
		text[3] = 0x80 | (char)(codepoint & 0x3F);
		text[4] = '\0';
	}
	//std::string ret = text;
	//return ret;
	return _strdup(text);
}

/*
std::string Utf8Util::utf32_to_utf8(uint32_t utf32)
{
	char pbUTF8[8] = { 0 };
	const BYTE  abPrefix[] = { 0, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
	const int adwCodeUp[] = {
		0x80,           // U+00000000 ～ U+0000007F  
		0x800,          // U+00000080 ～ U+000007FF  
		0x10000,        // U+00000800 ～ U+0000FFFF  
		0x200000,       // U+00010000 ～ U+001FFFFF  
		0x4000000,      // U+00200000 ～ U+03FFFFFF  
		0x80000000      // U+04000000 ～ U+7FFFFFFF  
	};
	int i, iLen;

	// 根据UCS4编码范围确定对应的UTF-8编码字节数  
	iLen = sizeof(adwCodeUp) / sizeof(int);
	for (i = 0; i < iLen; i++)
	{
		if (utf32 < adwCodeUp[i] )	{
			break;
		}
	}

	if (i == iLen)return 0;    // 无效的UCS4编码  

	iLen = i + 1;   // UTF-8编码字节数  
	if (pbUTF8 != NULL)
	{   // 转换为UTF-8编码  
		for (; i > 0; i--)
		{
			pbUTF8[i] = static_cast<BYTE>((utf32 & 0x3F) | 0x80);
			utf32 >>= 6;
		}

		pbUTF8[0] = static_cast<BYTE>(utf32 | abPrefix[iLen - 1]);
	}

	return pbUTF8;
}
*/
//
//Utf8StringView::~Utf8StringView() {
//	if (runeIndexes != NULL) {
//		delete[] runeIndexes;
//	}
//}
//Utf8StringView::Utf8StringView(std::string utf8string) {
//	this->utf8string = utf8string;
//}
///*启用rune索引*/
//API void Utf8StringView::enableRuneIndexes() {
//	if (runeIndexes != NULL) {
//		return;
//	}
//	updateRuneIndexes();
//}
//API void Utf8StringView::updateRuneIndexes() {
//	int _runeLength = length();
//	if (runeIndexes != NULL) {
//		delete[] runeIndexes;
//	}
//	runeIndexes = new int[_runeLength];
//	const char* s = utf8string.c_str();
//	int charLen = utf8string.size();
//	int start = 0;
//	int runeIndex = 0;
//	while (start < charLen) {
//		runeIndexes[runeIndex] = start;
//		runeIndex++;
//		start += Utf8Util::char_len(s + start);
//	}
//}
//
//int Utf8StringView::length() {
//	if (_length == -1) {
//		_length = Utf8Util::length(utf8string);
//	}
//	return _length;
//}
//
//std::string Utf8StringView::substr(int start, int len) {
//	if (start < 0) {
//		start = 0;
//	}
//
//	if (runeIndexes != NULL) { //带索引
//		if (start >= length()) {
//			return "";
//		}
//
//		int cstart = runeIndexes[start];
//
//		if (len == -1) {
//			return utf8string.substr(cstart);
//		}
//
//		int end = start + len;
//		end = std::min(length(), end);
//
//		int cend = runeIndexes[end - 1] + 1;
//		int clen = cend - cstart;
//		if (clen > 0) {
//			return utf8string.substr(cstart, clen);
//		}
//		return "";
//	}
//	return Utf8Util::substr(utf8string, start, len);
//}
//
//void Utf8Util_registerMeta(){
//    ///REGISTER_META
//	
//    ///REGISTER_META$
//}
