#pragma once
#pragma warning(disable:4251)

#include <string> 

extern const unsigned char kFirstBitMask ; // 1000000
extern const unsigned char kSecondBitMask; // 0100000
extern const unsigned char kThirdBitMask ; // 0010000
extern const unsigned char kFourthBitMask; // 0001000
extern const unsigned char kFifthBitMask; // 0000100


//以字符为单位
class Utf8StringView {
public:
	///API_SYNC
	void enableRuneIndexes();
	void updateRuneIndexes();
	///API_SYNC$
	Utf8StringView(std::string utf8string);
	~Utf8StringView();

	int length();
	//可优化：可以添加位置数组，从而加快?
	std::string substr(int start, int len=-1);

	int _length = -1;
	std::string utf8string;

	int* runeIndexes = NULL;
};
class  Utf8Util {
public:
	///API_SYNC
	static std::wstring toutf16(std::string str);
	static std::string utf8_to_active_code_page(std::string str);
	static std::string utf16_to_active_code_page(std::wstring str);
	static std::string toutf8(std::wstring str);
	///API_SYNC$

	static std::string utf32_to_utf8(uint32_t utf32);

	//一个字符几个字节
	static int char_len(const char* str);
	//n个字符几个字节
	static int num_char_len(const char* str, int n);
	//字符串中有几个字符
	static int length(std::string str);

	//取指定位置字符的字节偏移
	static int byte_offset_at(std::string text, int rune_offset);

	static std::string substr(std::string text, int at, int n = -1);



	static std::string insert_at(std::string str, int at, std::string newstr);
	static std::string backspace(std::string str, int at, int cnt);
	static std::string delete_rune(std::string str, int at, int cnt);
};
void Utf8Util_registerMeta();