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
#include "../Core/canvas.h"
#include "../Core/Theme.h"
#include "../Core/Window.h"
#include "../Layout/LayoutLinear.h"
#include "drag.h"
#include <vector>
#include <string>

#define SPLITTER "splitter"
#define TAB "tab"
#define ITEM "item"

class DockItem : public GcObj {
public:
	int intId = 0;
	std::string id = ("");
	Ref<ViewBase> view = nullptr;

	//水平还是垂直方向,用于splitter
	bool isHorizontal = false;
	// item|splitter|tab
	std::string type = (ITEM);
	float width = 0;
	float weight = 1; //放大

	//>>帮助计算dragSplitter
	//实际的内容尺寸
	float _sumContentSize = 0;
	//累计用来动态分配的空间
	float _sumFlexSize = 0;
	//累加的权重
	float _sumWeight = 0;
	//<<

	// Frame frame = mkFrame();

	// float shrink = 0 //缩小
	// bool isFixedWidth = false

	Ref<GcList<DockItem>> children{ new GcList<DockItem>(), this };
	Ref < DockItem> parent{ nullptr, this };
	// 对于tab需要有spliiterView
	Ref<ViewBase> nextSplitterView{ nullptr, this };
	Ref<ViewBase> prevSplitterView{ nullptr, this };

	//对于type=splitter,需要记录splitterViews
	// Ref<GcList<>> splitterViews = new List();

	void fromJson();
	void toJson();

	//对于tab的当前tab索引
	int tabActiveIndex = 0;

	void setTabActiveIndex(int index);

	~DockItem();

	//设置为当前tab项
	void setSelfActive_inTab();

	//拖拽splitter，如果左右都是weight模式,
	//就需要计算新的weight值
	float calcWeight_ofKid_forDragSplitter(
		DockItem* kid,
		float delta,
		float minSize
	);

	void appendChild(DockItem* item);
	void removeSelf();
	bool insertBefore(DockItem* newItem, DockItem* relChild);
	bool insertAfter(DockItem* newItem, DockItem* relChild);
	bool insertOffset(DockItem* newItem, DockItem* relChild, int offset);

	void removeChild(DockItem* kid);

	DockItem* tryGetParentTab();
	void printTree(int tab);
	bool isEmptySplitter();
	bool isEmptyTab();
};

//
//Ref<DockItem> DockItem_fromJson(Json@ jo) {
//    Ref<DockItem> di = new DockItem()
//
//        di.fromJson(jo)
//
//        Json@ children = jo.get("children")
//        if children {
//            int l = children->arraySize()
//                for (int i = 0; i < l; i++) {
//                    Json@ kid = children->at(i)
//                        Ref<DockItem> kidDi = DockItem_fromJson(kid)
//                        di.appendChild(kidDi)
//                }
//
//        }
//    return di
//}
//用法
//mkDockItemSplitter(nullptr, ("")).{
//    mkDockItem(o, ("hier"))
//    mkDockItem(o, ("console"))
//    mkDockItem(o, ("scene"))
//    mkDockItem(o, (""))
//}
Ref<DockItem> mkDockItem(DockItem* parent, std::string id);
Ref<DockItem> mkDockItemSplitter(DockItem* parent, std::string id, bool isHorizontal);
Ref<DockItem> mkDockItemTab(DockItem* parent, std::string id);

/// 可停靠窗口
class DockLayout : public View {
public:
	//分隔条占据的空间
	int splitterSize = 1;
	float minItemSize = 10;

	int tabHeadBg = themeIns()->dock_headbar_bg;//0x33ff0000

	Ref<DockItem> root{ mkDockItemSplitter(nullptr, ("DockLayout_root"), true), this }; //new DockItem()
	// List<DockSplitterInfo>
	// Ref<GcList<>> splitterInfos = new List()

	Ref<Closure< ViewBase* (DockItem* item, ViewBase& parent)>> cbRenderItemContentView{ nullptr, this };
	Ref<Closure< void(DockItem* item, ViewBase& parent, int kidIndex)>> cbRenderItemHeadView{ nullptr, this };

	// Ref<Drag> dragSplitter = new Drag()
	Ref<Drag> dragTab{ new Drag(), this };

	Ref < Closure< void()>> _afterDrawChildren{ nullptr, this };

	DockLayout();

	void doDrop();

	void react();

	//用来唯一标识一个
	// int viewIndex = 1000

	void onDragSplitter(Drag* drag, DockItem* parentDockItem,
		DockItem* prevDockItem,
		DockItem* nextDockItem);

	void _reactDockItem(DockItem* item);

	//处理事件：点击tab项
	void _onClickTabItemHead(DockItem* kid);
	//处理事件：tab项
	void _onEvent_tabItemHead(Event* e, DockItem* kid);

	// ^void (Event *e) _onEvent_tabItem 
	void _reactTabHeads(DockItem* tab, ViewBase& parent);
	void _reactTabContent(DockItem* tab, ViewBase& parent);

	void layoutContent(Frame* frame);
	void layoutContentDockItem(Frame* frame, DockItem* item, int px, int py);

	// void draw_self(Canvas *canvas){
	//     super.draw_self(canvas)
	//     this->drawDndIndicator(canvas)
	// }
	virtual void drawSelfBorder(Canvas* canvas) override;
	virtual void drawDndIndicator(Canvas* canvas);
	DockItem* findDockItem_containsVec2(DockItem* item, int clientX, int clientY);

	//向上找到离splitter最近 dockItem(非splitter)
	Ref<DockItem> upto_findMostAncestorInDockItemSplitter(Ref<DockItem> item);

	bool dropInSplitter(Ref<DockItem> source, Ref<DockItem> target, bool isHorizontal, bool isBefore);

	//向上，找到或者包装一下dockItemTab
	// 对于Splitter,返回nullptr
	Ref<DockItem> upto_getOrWrap_DockItemTab(Ref<DockItem> item);

	void clearAllEmptyTab(DockItem* item);
	//为splitter下的裸的dockitem包装个tab
	void eachThenWrapTab_forNakeDockItemInSplitter(DockItem* item);


	ViewBase* hitTestChildren(float x, float y);

};

class DockSplitterView :public View {
public:
	Ref<Drag> drag{ new Drag() , this };

	int hoverBg = themeIns()->dock_splitterBgHover;//0xff007aff//0xff00ff00
	int normalBg = themeIns()->dock_splitterBg; //0xffcdcdcf

	DockSplitterView();
	void react();
	void onEvent(Event* e);
	// void draw_self(Canvas *canvas){
	//     if this->hover {
	//         canvas->save()
	//         this->frame->width += 4
	//         canvas->translate(-2, 0)
	//     }
	//     super.draw_self(canvas)
	//     if this->hover {
	//         canvas->restore()
	//     }
	// }

	void onHoverChanged();
};
