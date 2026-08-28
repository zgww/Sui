#pragma once

#include "Predef.h"
#include "Node.h"
#include "Frame.h"
#include "Mat2d.h"
#include "Inset.h"
#include "Rect.h"
#include "Vec2.h"
#include "../Urgc/GcList.h"

class Canvas;
class Window;
class LayoutCell;
class App;

class ViewBase : public Node {
public:
	std::string hitTestType = "normal";
	Inset hitTestPadding;

	Frame frame;
	Ref<GcList<LayoutCell>> layoutCells{nullptr, this};

	Mat2d transform;
	Mat2d _world_transform;
	bool visible = true;
	std::string cursor = "unset";
	bool hover = false;
	int z = 0;

	Ref<Closure<void()>> cbOnHoverChanged{nullptr, this};

	Ref<GcList<LayoutCell>> gocLayoutCells();

	template<typename T>
	T* getLayoutCellByType() {
		if (!layoutCells) return nullptr;
		for (int i = 0; i < layoutCells->size(); i++) {
			LayoutCell* cell = layoutCells->get(i);
			if (cell) {
				T* casted = dynamic_cast<T*>(cell);
				if (casted) return casted;
			}
		}
		return nullptr;
	}

	ViewBase* getChildViewAt(int at);
	ViewBase* getChildAsView(int at);
	int getChildrenViewCount();

	Rect getScreenRect();
	virtual Rect get_abs_rect();
	bool _hitTestClientRect(Rect* r, float x, float y);
	virtual bool _hitTestSelf(float x, float y);

	virtual void _on_invalidLayout() {}
	virtual void _on_invalidDraw() {}
	virtual void resetViewTreeDirty() {}

	virtual void invalidReact() override;

	Vec2 localToWorld(float x, float y);
	Vec2 worldToLocal(float x, float y);

	virtual ViewBase* hitTest(float x, float y);
	virtual ViewBase* hitTestChildren(float x, float y);

	int viewIndexOf(Node* child);
	int viewIndexInParent();

	void markLayoutStart();
	void printLayoutTimes(int tab);

	virtual void layoutContent(Frame* contentCtx);
	virtual void layout(Frame* ctx);

	virtual void invalidLayout();
	virtual void draw(Canvas* canvas);
	virtual void draw_children(Canvas* canvas);
	virtual void draw_self(Canvas* canvas);
	void invalidDraw();

	virtual bool canLayoutByParent() { return visible; }

	virtual void setVisible(bool v);
	virtual void setHover(bool v);
	virtual void onHoverChanged();

	virtual std::string toString() override;

	virtual const char* getClassName() const override { return "ViewBase"; }
};

ViewBase* hitTestChildren_withZ(ViewBase* ins, float x, float y);
