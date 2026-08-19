#pragma once

#include "../Core/Predef.h"
#include "../Core/ViewBase.h"

class Menu : public ViewBase {
public:
	virtual const char* getClassName() const override { return "Menu"; }
};
