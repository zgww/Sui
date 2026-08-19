#pragma once

#include "Predef.h"
#include "Node.h"

class LayoutCell : public Node {
public:
	void invalidLayout();
	void onMounted() override;
	void onUnmounting() override;

	virtual const char* getClassName() const override { return "LayoutCell"; }
};
