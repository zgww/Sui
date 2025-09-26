#pragma once
#ifndef NAGA_DLLAPI 
	#ifdef NAGA_DLL_EXPORT
		#define NAGA_DLLAPI __declspec(dllexport)
	#else
		#define NAGA_DLLAPI __declspec(dllimport)
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
