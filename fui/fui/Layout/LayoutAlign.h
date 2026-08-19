#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/LayoutCell.h"
#include "../Core/Vec2.h"
#include "../Core/Frame.h"

class LayoutAlignCell : public LayoutCell {
public:
	Vec2 anchor = mkVec2(0, 0);
	Vec2 align = mkVec2(0, 0);
	Vec2 sizeRatio = mkVec2(NAN_F, NAN_F);

	void setSameRatio(float x, float y) {
		anchor.x = x; anchor.y = y;
		align.x = x; align.y = y;
	}
	void setTopLeft() { setSameRatio(0.0f, 0.0f); }
	void setTopCenter() { setSameRatio(0.5f, 0.0f); }
	void setTopRight() { setSameRatio(1.0f, 0.0f); }
	void setBottomLeft() { setSameRatio(0.0f, 1.0f); }
	void setBottomCenter() { setSameRatio(0.5f, 1.0f); }
	void setBottomRight() { setSameRatio(1.0f, 1.0f); }
	void setMiddleLeft() { setSameRatio(0.0f, 0.5f); }
	void setCenter() { setSameRatio(0.5f, 0.5f); }
	void setMiddleRight() { setSameRatio(1.0f, 0.5f); }

	virtual const char* getClassName() const override { return "LayoutAlignCell"; }
};

class LayoutAlignPositionCell : public LayoutCell {
public:
	float left = 0.0f;
	float top = 0.0f;
	float right = NAN_F;
	float bottom = NAN_F;

	virtual const char* getClassName() const override { return "LayoutAlignPositionCell"; }
};

class LayoutAlign : public View {
public:
	Vec2 anchor = mkVec2(0, 0);
	Vec2 align = mkVec2(0, 0);
	bool useMaxConstraint = true;

	void setSameRatio(float x, float y) {
		anchor.x = x; anchor.y = y;
		align.x = x; align.y = y;
	}
	void setTopLeft() { setSameRatio(0.0f, 0.0f); }
	void setTopCenter() { setSameRatio(0.5f, 0.0f); }
	void setTopRight() { setSameRatio(1.0f, 0.0f); }
	void setBottomLeft() { setSameRatio(0.0f, 1.0f); }
	void setBottomCenter() { setSameRatio(0.5f, 1.0f); }
	void setBottomRight() { setSameRatio(1.0f, 1.0f); }
	void setMiddleLeft() { setSameRatio(0.0f, 0.5f); }
	void setCenter() { setSameRatio(0.5f, 0.5f); }
	void setMiddleRight() { setSameRatio(1.0f, 0.5f); }

	void layoutContent(Frame* ctx) override;
	void getAnchorAndAlign_byView(ViewBase* view, Vec2* anchor, Vec2* align);

	virtual const char* getClassName() const override { return "LayoutAlign"; }
};
