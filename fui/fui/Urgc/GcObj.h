#pragma once

#include "UrgcPredef.h"

class  URGC_DLLAPI  GcObj {
public:
	virtual ~GcObj() {};
	//如果析构函数依赖了其他对象，其他对象可能在此对象前释放了，这样就会导致引用了被释放的对象异常
	//所以将析构函数要做的事情移到finalize, 析构函数中，不要引用其他urgc管理的对象

	//finalize中可能产生新的deref， 那么process时，要忽略无效的target
	//确认不需要此函数
	//virtual void finalize() {}; 
};

