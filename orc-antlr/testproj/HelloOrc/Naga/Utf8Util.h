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
