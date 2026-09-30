#pragma once

//非Windows平台: MSVC CRT函数名映射为POSIX等价物
#ifndef _WIN32
#include <string.h>
#include <wchar.h>
#include <strings.h>
#ifndef _strdup
#define _strdup strdup
#endif
#ifndef _wcsdup
#define _wcsdup wcsdup
#endif
#ifndef _stricmp
#define _stricmp strcasecmp
#endif
#endif

#ifndef NAGA_DLLAPI 
	#ifdef NAGA_DLL_EXPORT
		#define NAGA_DLLAPI 
	#else
		#define NAGA_DLLAPI 
	#endif
#endif

#ifndef API
	#define API
	#define VIRTUAL
	#define OVERRIDE
	#define STATIC
	#define CLASS(...)
	// PROPERTY(obj|embed, g, s, inspect=Inspect::color)  g表示生成getter, s表示生成setter
	// obj表示此字段类型为obj,embed表示此字段类型为嵌入式. inspect=xx表示指定inspect函数
	#define PROPERTY(...)
#endif
