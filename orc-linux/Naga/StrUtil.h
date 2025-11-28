#pragma once

#include "./NagaPredef.h"


#ifdef __cplusplus

template<typename T>
class AutoFree {
public:
	AutoFree() {

	}
	AutoFree(T data) {
		this->data = data;
	}
	~AutoFree() {
		free(this->data);
	}
	T data;
};


#endif


#ifdef __cplusplus
extern "C" {
#endif


	/*class NAGA_DLLAPI StrUtil
	{
	public:
		template<typename ... Args>
		static std::string format(const std::string& format, Args ... args)
		{
			auto size_buf = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
			std::unique_ptr<char[]> buf(new(std::nothrow) char[size_buf]);

			if (!buf)
				return std::string("");

			std::snprintf(buf.get(), size_buf, format.c_str(), args ...);
			return std::string(buf.get(), buf.get() + size_buf - 1);
		}*/

		//static std::vector<std::string> split_by_re(std::string source,
		//	std::string pattern);
		NAGA_DLLAPI  char* StrUtil_replace_by_re(const char* source, const char* pattern, const char* replaceStr);
		NAGA_DLLAPI  char* StrUtil_trim(const char* source, const char* eraseTarget);
		NAGA_DLLAPI  bool StrUtil_starts_with(const char* s, const char* sub);
		NAGA_DLLAPI  bool StrUtil_ends_with(const char* s, const char* sub);
		NAGA_DLLAPI  char* StrUtil_tolower(const char* data);
		NAGA_DLLAPI  char* StrUtil_toupper(const char* data);
		//NAGA_DLLAPI  char* StrUtil_join(std::vector<std::string> strs, char* separator);
		
		//都是返回新副本
		NAGA_DLLAPI  char* StrUtil_insert_at(const char* str, int at, const char* newstr);

	//};



#ifdef __cplusplus
}
#endif
