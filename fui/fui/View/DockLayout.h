#pragma once

#include "../Core/Predef.h"
#include "../Core/View.h"
#include "../Core/ViewBase.h"
#include "../Core/Node.h"
#include "../Core/Vec2.h"
#include "../Core/Rect.h"
#include "../Core/Inset.h"
#include "../Core/Event.h"
#include "../Core/Mouse.h"
#include "../Core/MouseEvent.h"
#include "../Core/Frame.h"
#include "../Core/Canvas.h"
#include "../Core/Window.h"
#include "../Layout/LayoutLinear.h"
#include "Drag.h"
#include <vector>
#include <string>

static const char* DOCK_SPLITTER = "splitter";
static const char* DOCK_TAB = "tab";
static const char* DOCK_ITEM = "item";

class DockItem : public GcObj {
public:
	int intId = 0;
	std::string id;
	Ref<ViewBase> view{nullptr, this};
	bool isHorizontal = false;
	std::string type = DOCK_ITEM;
	float width = 0;
	float weight = 1;

	float _sumContentSize = 0;
	float _sumFlexSize = 0;
	float _sumWeight = 0;

	Ref<GcList<DockItem>> children{new GcList<DockItem>(), this};
	Ref<DockItem> parent{nullptr, this};
	Ref<ViewBase> nextSplitterView{nullptr, this};
	Ref<ViewBase> prevSplitterView{nullptr, this};

	int tabActiveIndex = 0;

	void setTabActiveIndex(int index);
	void setSelfActive_inTab();
	float calcWeight_ofKid_forDragSplitter(DockItem* kid, float delta, float minSize);
	void appendChild(DockItem* item);
	void removeSelf();
	bool insertBefore(DockItem* newItem, DockItem* relChild);
	bool insertAfter(DockItem* newItem, DockItem* relChild);
	bool insertOffset(DockItem* newItem, DockItem* relChild, int offset);
	void removeChild(DockItem* kid);
	DockItem* tryGetParentTab();
	bool isEmptySplitter();
	bool isEmptyTab();

	virtual const char* getClassName() const { return "DockItem"; }
};

DockItem* mkDockItem(DockItem* parent, const std::string& id);
DockItem* mkDockItemSplitter(DockItem* parent, const std::string& id, bool isHorizontal);
DockItem* mkDockItemTab(DockItem* parent, const std::string& id);

class DockLayout : public View {
public:
	int splitterSize = 1;
	float minItemSize = 10;
	int tabHeadBg = 0xff2d2d2d;

	Ref<DockItem> root{nullptr, this};
	Ref<DockItem> rootHolder{nullptr, this};

	Ref<Closure<ViewBase*(DockItem*, ViewBase*)>> cbRenderItemContentView{nullptr, this};
	Ref<Closure<void(DockItem*, ViewBase*, int)>> cbRenderItemHeadView{nullptr, this};

	Ref<Drag> dragTab{new Drag(), this};

	DockLayout();
	void doDrop();
	void react() override;
	void onDragSplitter(Drag* drag, DockItem* parentDockItem, DockItem* prevDockItem, DockItem* nextDockItem);
	void _reactDockItem(DockItem* item);
	void _onClickTabItemHead(DockItem* kid);
	void _onEvent_tabItemHead(Event* e, DockItem* kid);
	void _reactTabHeads(DockItem* tab, ViewBase* parent);
	void _reactTabContent(DockItem* tab, ViewBase* parent);
	void layoutContent(Frame* frame) override;
	void layoutContentDockItem(Frame* frame, DockItem* item, float px, float py);
	void drawSelfBorder(Canvas* canvas);
	void drawDndIndicator(Canvas* canvas);
	DockItem* findDockItem_containsVec2(DockItem* item, float clientX, float clientY);
	DockItem* upto_findMostAncestorInDockItemSplitter(DockItem* item);
	bool dropInSplitter(DockItem* source, DockItem* target, bool isHorizontal, bool isBefore);
	DockItem* upto_getOrWrap_DockItemTab(DockItem* item);
	void clearAllEmptyTab(DockItem* item);
	void eachThenWrapTab_forNakeDockItemInSplitter(DockItem* item);
	ViewBase* hitTestChildren(float x, float y) override;

	virtual const char* getClassName() const override { return "DockLayout"; }
};

class DockSplitterView : public View {
public:
	Ref<Drag> drag{new Drag(), this};
	int hoverBg = 0xff007aff;
	int normalBg = 0xffcdcdcf;

	DockSplitterView();
	void react() override;
	void onEvent(Event* e) override;
	void onHoverChanged() override;

	virtual const char* getClassName() const override { return "DockSplitterView"; }
};
