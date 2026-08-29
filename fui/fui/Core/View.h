#pragma once

#include "Predef.h"
#include "ViewBase.h"
#include "Border.h"
#include "Radius.h"
#include "BoxShadow.h"
#include "Edge.h"
#include "Color.h"
#include "Inset.h"
#include "Vec2.h"
#include "Frame.h"
#include "Rect.h"

class Canvas;
class ViewCallback;
class View;

class ViewCallback : public GcObj {
public:
	virtual bool cbLayout(View* div, Frame* ctx) { return false; }
	virtual bool cbDraw(View* div, Canvas* canvas) { return false; }
	virtual bool cbDrawSelf(View* div, Canvas* canvas) { return false; }
	virtual void afterDrawSelf(View* div, Canvas* canvas) {}
};

class View : public ViewBase {
public:
	Vec2 size;
	bool needClip = false;

	float width = NAN_F;
	float height = NAN_F;
	float desiredWidth = NAN_F;
	float desiredHeight = NAN_F;
	float minWidth = 0.0f;
	float maxWidth = infinity;
	float minHeight = 0.0f;
	float maxHeight = infinity;

	Border border;
	Radius radius;
	Inset padding;
	Inset margin;
	BoxShadow boxShadow;
	int backgroundColor = 0x00000000;

	Ref<ViewCallback> cb{nullptr, this};

	void setHeight(float h) { height = h; invalidLayout(); }
	void setWidth(float v) { width = v; invalidLayout(); }

	Rect getViewRect_baseClient();
	bool _hitTestSelf(float x, float y) override;

	Rect getFrameRect();
	Rect getViewRect();
	Rect getContentRect();
	Vec2 getNonContentSize();
	Inset getInsetOfFrameToContent();
	Vec2 getSizeWithoutMargin();

	float getOutWidth();
	float getOutHeight();
	float getOutMinWidth();
	float getOutMinHeight();
	float getOutMaxWidth();
	float getOutMaxHeight();

	void updateFrame_forSelfWidthHeight(Frame* ctx);
	Rect getContentLocalRect();
	Rect getContentRect_baseViewRect();
	Vec2 getViewSize();

	void layoutContent_fromOutBox(Frame* ctx);
	void layoutContent(Frame* contentCtx) override;
	void initLayoutSize(Frame* ctx);
	bool callCbLayout(Frame* ctx);
	void layout(Frame* ctx) override;
	void updateFrame_byContentCtx(Frame* targetCtx, Frame* contentCtx);
	Frame makeContentLayoutCtx(Frame* ctx);
	Rect get_abs_rect() override;
	Rect getContentClientRect();

	void clip(Canvas* canvas);
	void draw(Canvas* canvas) override;
	virtual void drawSelfBorder(Canvas* canvas);
	virtual void draw_self(Canvas* canvas) override;

	virtual const char* getClassName() const override { return "View"; }

	static void registerMeta();
};
