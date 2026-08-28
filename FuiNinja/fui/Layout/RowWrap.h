#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/Vec2.h"
#include "../Core/Frame.h"
#include "../Core/Rect.h"

class RowWrap : public View {
public:
	std::string alignItems = "center";
	float rowGap = 0.0f;
	float colGap = 0.0f;

	void alignItems_ofRow(int rowStartIdx, int rowEndIdx, float rowHeight);
	void positionChildren(Frame* ctx);
	void layoutContent(Frame* contentCtx) override;

	virtual const char* getClassName() const override { return "RowWrap"; }
};
