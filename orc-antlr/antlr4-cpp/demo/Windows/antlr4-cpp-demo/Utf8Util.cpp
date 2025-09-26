

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

int Utf8Util::char_len(const char* str) {
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
int Utf8Util::num_char_len(const char* str, int n) {
	int len = 0;
	for (int i = 0; *str && i < n; i++) {
		int cl = char_len(str);
		str += cl;
		len += cl;
	}
	return len;
}
int Utf8Util::length(std::string str) {
	int len = 0;
	auto cur = str.c_str();
	while (*cur) {
		len++;
		int cl = char_len(cur);
		cur += cl;
	}
	return len;
}

//取指定位置字符的字节偏移
int Utf8Util::byte_offset_at(std::string text, int rune_offset) {
	const char* str = text.c_str();
	const char* tmp = str;

	for (int i = 0; *tmp && i < rune_offset; i++) {
		int cl = char_len(tmp);
		tmp += cl;
	}

	return tmp - str;
}

std::string Utf8Util::substr(std::string text, int at, int n) {
	const char* str = text.c_str();

	if (n == 0) {
		return "";
	}
	if (at < 0) at = 0;
	int len = length(text);

	if (n < 0) {
		n = len;
	}

	if (at >= len) return "";

	int start = byte_offset_at(text, at);
	int max_n = len - at;
	n = n > max_n ? max_n : n;

	int end_n = num_char_len(str + start, n);
	return text.substr(start, end_n);

}
std::string Utf8Util::insert_at(std::string str, int at, std::string newstr) {
	auto pre = substr(str, 0, at);
	auto post = substr(str, at);
	return pre + newstr + post;
}
std::string Utf8Util::backspace(std::string str, int at, int cnt) {
	auto pre = substr(str, 0, at - cnt);
	auto post = substr(str, at);
	return pre + post;
}
std::string Utf8Util::delete_rune(std::string str, int at, int cnt) {
	auto pre = substr(str, 0, at);
	auto post = substr(str, at+cnt);
	return pre + post;
}
std::wstring Utf8Util::toutf16(std::string str) {
#ifdef _WIN32
	if (str == "") return L"";

	// 计算缓冲区需要的大小, 如果函数成功, 则返回 UTF-8 字符数量, 所以无法确定具体字节数
	int cBuf = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if (cBuf == 0) return L"(null)";
	wchar_t* buf = new wchar_t[cBuf * 4];// malloc(cBuf * 4);
	if (cBuf != MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buf, cBuf)) {
		delete [] buf;
		return L"";
	}
	std::wstring ret = buf;
	delete [] buf;
	return ret;
#else//其他平台统一走utf8
	return L"";
#endif
}

std::string Utf8Util::utf8_to_active_code_page(std::string str) {
	auto utf16 = toutf16(str);
	auto ret = utf16_to_active_code_page(utf16);
	return ret;
}
std::string Utf8Util::utf16_to_active_code_page(std::wstring str) {
#ifdef _WIN32
	if (str == L"") return "";
	// 计算缓冲区需要的大小, 如果函数成功, 则返回具体字节数, 所以 cBuf 至少是 1 (UTF-8以0x00结尾)
	int cBuf = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	if (cBuf < 1) return "";
	char* buf = new char [cBuf] ; // 分配缓冲区
	if (cBuf != WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, buf, cBuf, NULL, NULL)) {
		delete[] buf;
		return "";
	}
	std::string ret = buf;
	delete[] buf;
	return ret;
#else
	return "";
#endif
}
std::string Utf8Util::toutf8(std::wstring str) {
#ifdef _WIN32
	if (str == L"") return "";
	// 计算缓冲区需要的大小, 如果函数成功, 则返回具体字节数, 所以 cBuf 至少是 1 (UTF-8以0x00结尾)
	int cBuf = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	if (cBuf < 1) return "";
	char* buf = new char [cBuf] ; // 分配缓冲区
	if (cBuf != WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, buf, cBuf, NULL, NULL)) {
		delete[] buf;
		return "";
	}
	std::string ret = buf;
	delete[] buf;
	return ret;
#else
	return "";
#endif
}

std::string
Utf8Util::utf32_to_utf8(uint32_t codepoint)
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
	std::string ret = text;
	return ret;
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

Utf8StringView::~Utf8StringView() {
	if (runeIndexes != NULL) {
		delete[] runeIndexes;
	}
}
Utf8StringView::Utf8StringView(std::string utf8string) {
	this->utf8string = utf8string;
}
/*启用rune索引*/
void Utf8StringView::enableRuneIndexes() {
	if (runeIndexes != NULL) {
		return;
	}
	updateRuneIndexes();
}
void Utf8StringView::updateRuneIndexes() {
	int _runeLength = length();
	if (runeIndexes != NULL) {
		delete[] runeIndexes;
	}
	runeIndexes = new int[_runeLength];
	const char* s = utf8string.c_str();
	int charLen = utf8string.size();
	int start = 0;
	int runeIndex = 0;
	while (start < charLen) {
		runeIndexes[runeIndex] = start;
		runeIndex++;
		start += Utf8Util::char_len(s + start);
	}
}

int Utf8StringView::length() {
	if (_length == -1) {
		_length = Utf8Util::length(utf8string);
	}
	return _length;
}

std::string Utf8StringView::substr(int start, int len) {
	if (start < 0) {
		start = 0;
	}

	if (runeIndexes != NULL) { //带索引
		if (start >= length()) {
			return "";
		}

		int cstart = runeIndexes[start];

		if (len == -1) {
			return utf8string.substr(cstart);
		}

		int end = start + len;
		end = std::min(length(), end);

		int cend = runeIndexes[end - 1] + 1;
		int clen = cend - cstart;
		if (clen > 0) {
			return utf8string.substr(cstart, clen);
		}
		return "";
	}
	return Utf8Util::substr(utf8string, start, len);
}

void Utf8Util_registerMeta(){
    ///REGISTER_META
	
    ///REGISTER_META$
}
