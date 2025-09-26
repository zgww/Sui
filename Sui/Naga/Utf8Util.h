#pragma once
#pragma warning(disable:4251)
#include "NagaPredef.h"


#include <stdint.h>



#ifdef __cplusplus
extern "C" {
#endif

	extern const unsigned char kFirstBitMask; // 1000000
	extern const unsigned char kSecondBitMask; // 0100000
	extern const unsigned char kThirdBitMask; // 0010000
	extern const unsigned char kFourthBitMask; // 0001000
	extern const unsigned char kFifthBitMask; // 0000100


	////以字符为单位
	//class NAGA_DLLAPI Utf8StringView {
	//public:
	//	///API_SYNC
	//	void enableRuneIndexes();
	//	void updateRuneIndexes();
	//	///API_SYNC$
	//	Utf8StringView(std::string utf8string);
	//	~Utf8StringView();

	//	int length();
	//	//可优化：可以添加位置数组，从而加快?
	//	std::string substr(int start, int len = -1);

	//	int _length = -1;
	//	std::string utf8string;

	//	int* runeIndexes = NULL;
	//};
		///API_SYNC


NAGA_DLLAPI wchar_t* new_Utf8Util_toutf16(const char* str);
NAGA_DLLAPI char* new_Utf8Util_utf8_to_active_code_page(const char* str);


NAGA_DLLAPI char* new_Utf8Util_utf16_to_active_code_page(const wchar_t* str);
NAGA_DLLAPI char* new_Utf8Util_toutf8(const wchar_t* str);
///API_SYNC$

NAGA_DLLAPI char * new_Utf8Util_utf32ToUtf8(uint32_t utf32);

//一个字符几个字节
NAGA_DLLAPI int Utf8Util_charLen(const char* str);
//n个字符几个字节
NAGA_DLLAPI int Utf8Util_numCharLen(const char* str, int n);


//字符串中有几个字符
NAGA_DLLAPI int Utf8Util_length(const char * str);

//取指定位置字符的字节偏移
NAGA_DLLAPI int Utf8Util_byteOffsetAt(const char* text, int rune_offset);

NAGA_DLLAPI char* new_Utf8Util_substr(const char * text, int at, int n);



NAGA_DLLAPI char* new_Utf8Util_insert_at(const char* str, int at, const char* newstr);
NAGA_DLLAPI char* new_Utf8Util_backspace(const char* str, int at, int cnt);
NAGA_DLLAPI char* new_Utf8Util_delete_rune(const char* str, int at, int cnt);


//NAGA_DLLAPI wchar_t* _strdup_wstring(const wchar_t* ret);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <string>

class NAGA_DLLAPI  Utf8Util {
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

#endif
