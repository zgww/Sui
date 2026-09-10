#pragma once

#include "Predef.h"
#include <rttr/rttr_enable.h>
#include "Node.h"

class LayoutCell : public Node {
	RTTR_ENABLE(Node)
public:
	void invalidLayout();
	void onMounted() override;
	void onUnmounting() override;

	virtual const char* getClassName() const override { return "LayoutCell"; }
};
