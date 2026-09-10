#pragma once

#include "../Core/Predef.h"
#include "../Core/ViewBase.h"
#include <rttr/rttr_enable.h>

class Menu : public ViewBase {
public:
	virtual const char* getClassName() const override { return "Menu"; }

	RTTR_ENABLE(ViewBase)
};
