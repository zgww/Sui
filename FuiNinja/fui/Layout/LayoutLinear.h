#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/LayoutCell.h"
#include "../Core/Vec2.h"
#include "../Core/Frame.h"
#include "../Urgc/GcList.h"
#include <vector>

class LayoutLinearCell : public LayoutCell {
public:
	float grow = 1.0f;
	std::string alignSelf;

	virtual const char* getClassName() const override { return "LayoutLinearCell"; }
};

class LayoutLinear : public View {
public:
	std::string direction = "row";
	std::string justifyContent = "start";
	std::string alignItems = "center";
	float maxCrossSize = 0.0f;

	std::vector<ViewBase*> growNodes;

	bool isMax_in_maxOrStretch(Frame* ctx, bool isHor);
	void layoutCross(Frame* ctx);
	bool calcIsHor();
	std::string getCrossAlign_ofKid(ViewBase* view);
	void positionChildren(Frame* ctx);
	void setMainConstraints(Frame* kidCtx, bool isHor, float minV, float maxV);
	void setCrossConstraints(Frame* kidCtx, bool isHor, float minV, float maxV);
	float getMainMaxConstraint(Frame* kidCtx, bool isHor);
	float getCrossMaxConstraint(Frame* kidCtx, bool isHor);
	void update_maxCrossSize(Frame* kidCtx, bool isHor);
	bool layout_mainInf(Frame* ctx);
	bool layout_mainLimit(Frame* ctx);
	void layoutContent(Frame* ctx) override;
	void layout(Frame* ctx) override;

	LayoutLinear& jcc() { justifyContent = "center"; return *this; }
	LayoutLinear& jcs() { justifyContent = "start"; return *this; }
	LayoutLinear& jce() { justifyContent = "end"; return *this; }
	LayoutLinear& jcsb() { justifyContent = "space-between"; return *this; }
	LayoutLinear& jcsa() { justifyContent = "space-around"; return *this; }
	LayoutLinear& jcse() { justifyContent = "space-evenly"; return *this; }
	LayoutLinear& ais() { alignItems = "start"; return *this; }
	LayoutLinear& aic() { alignItems = "center"; return *this; }
	LayoutLinear& aie() { alignItems = "end"; return *this; }
	LayoutLinear& aiStretch() { alignItems = "stretch"; return *this; }
	LayoutLinear& aiMaxOrStretch() { alignItems = "maxOrStretch"; return *this; }
	LayoutLinear& column() { direction = "column"; return *this; }
	LayoutLinear& row() { direction = "row"; return *this; }

	virtual const char* getClassName() const override { return "LayoutLinear"; }
};
