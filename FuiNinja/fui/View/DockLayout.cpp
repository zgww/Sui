#include "DockLayout.h"
#include "TextView.h"
#include "../Core/NodeLib.h"



void DockItem::fromJson() {
	//void fromJson(Json@ jo) {
	//this->intId = jo.getNumber("intId")
	//    this->id = jo.getString("id")
	//    this->isHorizontal = jo.getBool("isHorizontal")
	//    this->type = jo.getString("type")
	//    this->width = jo.getNumber("width")
	//    this->weight = jo.getNumber("weight")
}

void DockItem::toJson() {

	//Json@ toJson() {
	//Json@ jo = Json_mkObject()
	//    jo.putNumber("intId", this->intId)
	//    jo.putString("id", this->id)
	//    jo.putBool("isHorizontal", this->isHorizontal)
	//    jo.putString("type", this->type)
	//    jo.putNumber("width", this->width)
	//    jo.putNumber("weight", this->weight)

	//    Json@ kids = Json_mkArray()
	//    jo.put("children", kids)

	//    for (int i = 0; i < this->children->size(); i++) {
	//        DockItem* kid = (DockItem*)this->children->get(i)
	//            Json@ kidJo = kid->toJson()
	//            kids.add(kidJo)
	//    }

	//return jo
}

void DockItem::setTabActiveIndex(int index) {
	this->tabActiveIndex = clampInt(index, 0, this->children->size() - 1);
}

DockItem::~DockItem() {
	printf("释放DockItem:%p %s\n", this, this->id.c_str());
	if (this->parent) {
		this->parent->printTree(0);
	}
}

//设置为当前tab项
void DockItem::setSelfActive_inTab() {
	if (this->parent && this->parent->type == (TAB)) {
		int idx = this->parent->children->indexOf(this);
		this->parent->setTabActiveIndex(idx);
	}
}


//拖拽splitter，如果左右都是weight模式,
//就需要计算新的weight值
float DockItem::calcWeight_ofKid_forDragSplitter(DockItem* kid, float delta, float minSize) {
	if (kid->width > 0) {
		return 0;
	}

	float actualSize = kid->weight / this->_sumWeight * this->_sumFlexSize;
	float newSize = maxFloat(minSize, actualSize + delta);
	float newWeight = newSize / this->_sumFlexSize * this->_sumWeight;
	return newWeight;
}

void DockItem::appendChild(DockItem* item) {
	item->removeSelf();

	this->children->push(item);
	item->parent = this;
}

void DockItem::removeSelf() {
	if (this->parent) {
		this->parent->removeChild(this);
	}
}

bool DockItem::insertBefore(DockItem* newItem, DockItem* relChild) {
	return this->insertOffset(newItem, relChild, 0);
}

bool DockItem::insertAfter(DockItem* newItem, DockItem* relChild) {
	return this->insertOffset(newItem, relChild, 1);
}

bool DockItem::insertOffset(DockItem* newItem, DockItem* relChild, int offset) {
	if (newItem == nullptr) {
		return false;
	}

	int idx = this->children->indexOf(relChild);
	if (idx == -1) {
		return false;
	}
	newItem->removeSelf();
	this->children->insert_at(idx + offset, newItem);
	newItem->parent = this;
	return true;
}

void DockItem::removeChild(DockItem* kid) {
	if (kid->parent == this) {
		this->children->remove(kid);
		kid->parent = nullptr;
	}
}

DockItem* DockItem::tryGetParentTab() {
	DockItem* cur = this->parent;
	if (cur->type == (TAB)) {
		return cur;
	}
	return nullptr;
}

void DockItem::printTree(int tab) {
	for (int i = 0; i < tab; i++) {
		printf("\t");
	}
	printf("%s@%p#%d[%f,%f]\n", this->id.c_str(), this, this->intId, this->width, this->weight);
	for (int i = 0; i < this->children->size(); i++) {
		DockItem* kid = this->children->get(i);
		kid->printTree(tab + 1);
	}
}

bool DockItem::isEmptySplitter() {
	if (this->type == (SPLITTER)) {
		if (this->children->size() == 0) {
			return true;
		}
	}
	return false;
}

bool DockItem::isEmptyTab() {
	if (this->type == (TAB)) {
		if (this->children->size() == 0) {
			return true;
		}
	}
	return false;

}

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
Ref<DockItem> mkDockItem(DockItem* parent, std::string id) {
	Ref<DockItem> ins{ new DockItem() };
	if (id != "") {
		ins->id = id;
	}
	if (parent) {
		parent->appendChild(ins);
	}
	return ins;
}

Ref<DockItem> mkDockItemSplitter(DockItem* parent, std::string id, bool isHorizontal) {
	Ref<DockItem> ins = mkDockItem(parent, id);
	ins->type = (SPLITTER);
	ins->isHorizontal = isHorizontal;
	return ins;
}

Ref<DockItem> mkDockItemTab(DockItem* parent, std::string id) {
	Ref<DockItem> ins = mkDockItem(parent, id);
	ins->type = (TAB);
	return ins;
}

DockLayout::DockLayout() {
	CtorGuard _(this);

	// this->dragSplitter.onDrag =^ void(Drag *d){
	//     printf("drag->...\n");
	// }
	auto self = Ref(this);
	this->dragTab->onDrag = CLOSURE([=](Drag* pd) {
		auto& d = *pd;
		if (d.isDragging || d.isDragEnd) {
			printf("\n\n\t drag tab\n");
			self->invalidDraw();
		}
		if (d.isDragEnd) {
			self->doDrop();
		}
		});

	initInnerReact();
}

void DockLayout::doDrop() {
	Vec2 mousePos = Mouse_getPosOfWindow(this->ownerWindow);
	DockItem* target = this->findDockItem_containsVec2(this->root, mousePos.x, mousePos.y);

	if (target && target->view) {
		Rect absRect = target->view->get_abs_rect();
		printf("mousePos.:%f,%f abs:%f,%f,%f,%f\n", mousePos.x, mousePos.y
			, absRect.x, absRect.y, absRect.w, absRect.h
		);
		// drop type
		// Vec2 geo = absRect.containsPositionIn9Patch(mousePos.x, mousePos.y)
		int geoType = -1;
		Rect geo = absRect.containsPositionIn5Patch_withOutType(mousePos.x, mousePos.y,
			mkRect(0.2f, 0.2f, 0.6f, 0.6f), &geoType
		);
		if (geo.x == -1) {
			printf("放置tab无效，未找到目标\n");
			return;
		}

		if (dynamic_cast<DockItem*>(this->dragTab->data.get())) {
			DockItem* source = (DockItem*)this->dragTab->data.get();
			printf("do Drop source:%s, target:%s, geoType:%d\n"
				, source->id.c_str()
				, target->id.c_str()
				, geoType
			);

			if (source == target) { //如果目标就是自己，不处理
				return;
			}

			if (geoType == 0) { //上
				this->dropInSplitter(source, target, false, true);
			}
			if (geoType == 1) { //左
				this->dropInSplitter(source, target, true, true);
			}
			if (geoType == 2) { //中
				Ref<DockItem> tab = this->upto_getOrWrap_DockItemTab(target);
				if (tab) {
					printf("doDrop. create tab:%p %s\n", tab.get(), tab->id.c_str());
					tab->appendChild(source);
					this->invalidReact();
				}
			}
			if (geoType == 3) { //右
				this->dropInSplitter(source, target, true, false);
			}
			if (geoType == 4) { //下
				this->dropInSplitter(source, target, false, false);
			}
			this->clearAllEmptyTab(this->root);
		}
	}
	this->root->printTree(0);
}

void DockLayout::react() {
	this->startInnerReact();

	this->eachThenWrapTab_forNakeDockItemInSplitter(this->root);
	// this->root.printTree(0)

	this->_reactDockItem(this->root);

	this->endInnerReact();
	// printNodeTree(self, 0)
}

void DockLayout::onDragSplitter(Drag* drag, DockItem* parentDockItem, DockItem* prevDockItem, DockItem* nextDockItem) {

	printf("drag SPlitter. parent:%s, prev:%s, next:%s\n",
		parentDockItem->id.c_str(), prevDockItem->id.c_str()
		, nextDockItem->id.c_str());

	if (drag->isDragChecking) {
		drag->cursor =
			parentDockItem->isHorizontal ? ("sizewe")
			: ("sizens");
	}
	if (drag->isDragging) {
		float delta = drag->deltaPos.y;
		if (parentDockItem->isHorizontal) {
			delta = drag->deltaPos.x;
		}

		//根据width/weight的不同组合，有不同的反应
		if (prevDockItem->width > 0 && nextDockItem->width > 0) {
			// printf(">0, >0\n");
			prevDockItem->width = maxFloat(this->minItemSize, prevDockItem->width + delta);
			nextDockItem->width = maxFloat(this->minItemSize, nextDockItem->width - delta);
		}
		else if (prevDockItem->width > 0 && nextDockItem->width == 0) {
			// printf(">0, =0\n");
			prevDockItem->width = maxFloat(this->minItemSize, prevDockItem->width + delta);
		}
		else if (prevDockItem->width == 0 && nextDockItem->width > 0) {
			// printf("=0, >0\n");
			nextDockItem->width = maxFloat(this->minItemSize, nextDockItem->width - delta);
		}
		else {// 都是weight模式
			// (w - delta) / flexSize = weight / sumWeight
			// printf("=0, =0\n");
			prevDockItem->weight = parentDockItem->calcWeight_ofKid_forDragSplitter(
				prevDockItem,
				delta,
				this->minItemSize
			);
			nextDockItem->weight = parentDockItem->calcWeight_ofKid_forDragSplitter(
				nextDockItem,
				-delta,
				this->minItemSize
			);
			// printf("\t\t\t更新dock item weight:%f, %f\n",
			//     prevDockItem->weight,
			//     nextDockItem->weight,
			// );
		}

		// parentDockItem->printTree(2)

		this->invalidLayout();
	}
}

void DockLayout::_reactDockItem(DockItem* item) {
	auto self = Ref(this);
	auto& o = *this;

	DockItem* parentItem = item;
	if (item->type == (SPLITTER)) {
		View* splitterView = nullptr;
		int l = item->children->size();
		for (int i = 0; i < l; i++) {
			int index = i;

			DockItem* kid = item->children->get(i);

			kid->prevSplitterView = splitterView;
			this->_reactDockItem(kid);
			if (i < l - 1) {
				DockItem* nextKid = (DockItem*)item->children->get(i + 1);
				//创建splitterview
				// DockSplitterInfo@ info = new DockSplitterInfo()
				// 2000用来表示 splitterView
				// 这个key的选择，极端情况下可能会导致key重复? 如果item的值不同得很刚好
				R(DockSplitterView, ((long long)item) + 2000 + i) {
					o.z = 10;
					o.drag->onDrag = CLOSURE([=](Drag* d) {
						// printf("drag i:%d, index:%d\n", i, index);
						this->onDragSplitter(
							d, parentItem, kid, nextKid
						);
						});

					o.cursor = item->isHorizontal ? ("sizewe") : ("sizens");
					// kid->view = o
					// this->viewIndex = this->viewIndex + 1
					kid->nextSplitterView = &o;
					splitterView = &o;
				}REND;
			}
		}
	}
	if (item->type == (TAB)) {
		R(LayoutLinear, (long long)item) {
			// o.backgroundColor = 0xffffffff
			o.needClip = true;
			item->view = &o;

			o.direction = ("column");
			o.alignItems = ("stretch");

			//渲染头部视图
			this->_reactTabHeads(item, o);
			//渲染内容视图
			this->_reactTabContent(item, o);
		} REND;
	}
	if (item->type == (ITEM)) {
		if (this->cbRenderItemContentView) {
			ViewBase* v = this->cbRenderItemContentView->invoke(item, *this);
			item->view = v;
		}
	}
}

//处理事件：点击tab项
void DockLayout::_onClickTabItemHead(DockItem* kid) {
	kid->setSelfActive_inTab();
	this->invalidReact();
}

//处理事件：tab项
void DockLayout::_onEvent_tabItemHead(Event* e, DockItem* kid) {
	if (dynamic_cast<MouseEvent*>(e)) {
		MouseEvent* me = (MouseEvent*)e;

		if (me->isBubble()) {
			if (me->isMouseDown) {
				// MessageDialog_alert("click tab head", "title标题")
				this->_onClickTabItemHead(kid);
			}

			this->dragTab->data = kid;
			this->dragTab->onMouseDown(me);
		}
	}
}

// ^void (Event *e) _onEvent_tabItem 
void DockLayout::_reactTabHeads(DockItem* tab, ViewBase& o) {
	auto self = Ref(this);
	R(LayoutLinear) {
		o.direction = ("row");
		// o.backgroundColor = 0xff0000ff
		o.backgroundColor = this->tabHeadBg;
		int l = tab->children->size();
		for (int i = 0; i < l; i++) {
			Ref<DockItem> kid = tab->children->get(i);
			if (kid->type == (ITEM)) {
				R(LayoutLinear, (long long)kid.get()) {
					// printf("设置tabHead cbOnEvent:%p %s\n", kid, kid->id.c_str());
					o.cbOnEvent = CLOSURE(
						[=](Event* e) { 
							self->_onEvent_tabItemHead(e, kid.get());
						}
					);
					if (this->cbRenderItemHeadView) {
						this->cbRenderItemHeadView->invoke(kid, o, i);
					}
				} REND;
			}
		}
	} REND;
}

void DockLayout::_reactTabContent(DockItem* tab, ViewBase &o) {
	auto self = Ref(this);

	R(LayoutLinear) {
		o.direction = ("column");
		o.alignItems = ("stretch");
		// o.backgroundColor = 0xffffff00
		// o.padding.setAll(10)

		R(LayoutLinearCell) {
			o.grow = 1;
		} REND;

		Ref<DockItem> kid = tab->children->get(tab->tabActiveIndex);
		if (kid) {
			if (this->cbRenderItemContentView) {
				ViewBase* view = this->cbRenderItemContentView->invoke(kid, o);
				kid->view = view;;
			}
		}
	} REND;
}

void DockLayout::layoutContent(Frame* frame) {
	//不处理非tight的情况
	if (!frame->isTight()) {
		printf("\n\nDockLayout layoutContent. 非tight\n");
		return;
	}
	//tight模式
	// printf("\n\nDockLayout layoutContent. tight\n");
	// super.layoutContent(frame)
	this->layoutContentDockItem(frame, this->root, 0, 0);

	// printNodeTree(self, 0)
}

void DockLayout::layoutContentDockItem(Frame* frame, DockItem* item, int px, int py) {
	if (item->type == (SPLITTER)) {
		// Frame kidFrame = mkFrame()
		int kidsSize = item->children->size();
		float sumSplitterSize = (kidsSize - 1) * this->splitterSize;
		float mainSize = item->isHorizontal ? frame->width : frame->height;
		float sumContentSize = mainSize - sumSplitterSize;
		float sumWeight = 0;
		float sumWidth = 0;
		int l = kidsSize;
		for (int i = 0; i < l; i++) {
			Ref<DockItem> kid = item->children->get(i);
			float w = maxFloat(0.0, kid->width);
			if (w > 0) { //width优先
				sumWidth = sumWidth + w;
			}
			else {
				sumWeight = sumWeight + maxFloat(0.0, kid->weight);
			}
		}
		if (sumWeight <= 0) { //确保不为0
			sumWeight = 1.0;
		}
		// 动态分配的内容空间
		float flexSpaceSize = maxFloat(0.0, sumContentSize - sumWidth);


		item->_sumContentSize = sumContentSize;
		item->_sumFlexSize = flexSpaceSize;
		item->_sumWeight = sumWeight;

		float pos = 0.0;
		l = kidsSize;
		for (int i = 0; i < l; i++) {
			Ref<DockItem> kid = item->children->get(i);
			Frame tmpFrame = mkFrame();
			Frame* kidFrame = kid->view ? &kid->view->frame : &tmpFrame;

			float kidSize = 0.0;
			if (item->isHorizontal) { //水平方向
				kidFrame->x = pos + px;
				kidFrame->y = 0.0f + py;
				// float placeSize = maxFloat(0.0, kid->width)
				kidSize = kid->width > 0
					? kid->width
					: maxFloat(0.0, kid->weight) / sumWeight * flexSpaceSize;
				kidFrame->setTight(
					kidSize,
					frame->height
				);
			}
			else { //垂直方向
				kidFrame->x = 0.0f + px;
				kidFrame->y = pos + py;
				kidSize = kid->width > 0
					? kid->width
					: maxFloat(0.0, kid->weight) / sumWeight * flexSpaceSize;
				kidFrame->setTight(
					frame->width,
					kidSize
				);
			}

			if (kid->type == (SPLITTER)) {
				this->layoutContentDockItem(kidFrame, kid, kidFrame->x, kidFrame->y);
			}
			else {
				//布局子视图
				if (kid->view) {
					kid->view->layout(kidFrame);
				}
			}
			pos = pos + kidSize;
			//布局splitter
			if (kid->nextSplitterView) {
				// kid->nextSplitterView->frame->
				Frame* f = &kid->nextSplitterView->frame;
				if (item->isHorizontal) {
					f->x = pos + px;
					f->y = 0 + py;
					f->setTight(
						this->splitterSize,
						frame->height
					);
				}
				else {
					f->x = 0 + px;
					f->y = pos + py;
					f->setTight(
						frame->width,
						this->splitterSize
					);
				}
				kid->nextSplitterView->layout(f);
				pos = pos + this->splitterSize;
			}
		}
	}

}

// void draw_self(Canvas *canvas){
//     super.draw_self(canvas)
//     this->drawDndIndicator(canvas)
// }
void DockLayout::drawSelfBorder(Canvas* canvas) {
	View::drawSelfBorder(canvas);
	this->drawDndIndicator(canvas);
}

void DockLayout::drawDndIndicator(Canvas* canvas) {
	Drag* drag = this->dragTab;

	if (!drag->isDragging) {
		return;
	}
	if (!this->ownerWindow) {
		return;
	}
	//计算绘制的位置
	Vec2 mousePos = Mouse_getPosOfWindow(this->ownerWindow);
	DockItem* target = this->findDockItem_containsVec2(this->root, (int)mousePos.x, (int)mousePos.y);

	if (target && target->view) {
		canvas->save();

		canvas->translate(
			this->padding.left + this->border.l.w,
			this->padding.top + this->border.t.w
		);

		Rect absRect = target->view->get_abs_rect();
		//printf("DockLayout mousePos.:%f,%f abs:%f,%f,%f,%f\n", mousePos.x, mousePos.y
		//	, absRect.x, absRect.y, absRect.w, absRect.h
		//);
		// drop type
		// Vec2 geo = absRect.containsPositionIn9Patch(mousePos.x, mousePos.y)
		Rect geo = absRect.containsPositionIn5Patch(mousePos.x, mousePos.y,
			mkRect(0.2f, 0.2f, 0.6f, 0.6f)
		);

		Rect r = target->view->frame.toRect();

		canvas->beginPath();
		canvas->fillColor(0, 64, 255, 64);
		canvas->rect(
			r.x + r.w * geo.x
			, r.y + r.h * geo.y
			, r.w * geo.w
			, r.h * geo.h);
		canvas->fill();

		//printf("draw dndindicator:%f,%f,%f,%f\n",

		//	r.x + r.w * geo.x
		//	, r.y + r.h * geo.y
		//	, r.w * geo.w
		//	, r.h * geo.h
		//);

		canvas->restore();

	}
	else {
		//printf("no drawDndIndicator. no target or view\n");
	}
}

DockItem* DockLayout::findDockItem_containsVec2(DockItem* item, int clientX, int clientY) {
	if (item->view) {//是子视图
		Rect r = item->view->get_abs_rect();
		bool ok = r.containsPosition(clientX, clientY);
		if (ok) {
			return item;
		}
	}
	//不是子视图
	int l = item->children->size();
	for (int i = 0; i < l; i++) {
		Ref<DockItem> kid = item->children->get(i);
		DockItem* ret = this->findDockItem_containsVec2(kid, clientX, clientY);
		if (ret) {
			return ret;
		}
	}
	return nullptr;
}

//向上找到离splitter最近 dockItem(非splitter)
Ref<DockItem> DockLayout::upto_findMostAncestorInDockItemSplitter(Ref<DockItem> item) {
	DockItem* cur = item;
	while (cur && cur->parent) {
		if (cur->parent->type == (SPLITTER)) {
			return cur;
		}
		cur = cur->parent;
	}
	return nullptr;
}

bool DockLayout::dropInSplitter(Ref<DockItem> source, Ref<DockItem> target, bool isHorizontal, bool isBefore) {
	Ref<DockItem> ancestor = this->upto_findMostAncestorInDockItemSplitter(target);
	if (!ancestor) { //没有目标
		return false;
	}
	Ref<DockItem> splitter = ancestor->parent;
	if (splitter->type != (SPLITTER)) {
		return false;
	}
	source->removeSelf();

	if (splitter->isHorizontal == isHorizontal) { //同向
		splitter->insertOffset(source, ancestor, isBefore ? 0 : 1);
	}
	else { //异向，需要包裹一个splitter
		Ref<DockItem> newSplitter = mkDockItemSplitter(nullptr,
			std::format("splitter-of-{}", ancestor->id), isHorizontal);

		// 添加splitter
		splitter->insertOffset(newSplitter, ancestor, 0);

		//按顺序加入source/ancestor
		newSplitter->appendChild(ancestor);
		newSplitter->insertOffset(source, ancestor, isBefore ? 0 : 1);
	}
	this->invalidReact();

	return true;
}

//向上，找到或者包装一下dockItemTab
// 对于Splitter,返回nullptr
Ref<DockItem> DockLayout::upto_getOrWrap_DockItemTab(Ref<DockItem> item) {
	if (item->type == (SPLITTER)) {
		return nullptr;
	}
	//这是找到了
	if (item->type == (TAB)) {
		return item;
	}
	//这是未找到
	if (item->type == (ITEM)) {
		DockItem* parent = item->parent;
		if (parent) {
			if (parent->type == (TAB)) {
				return parent;
			}
			if (parent->type == (SPLITTER)) {
				//包装一下
				Ref<DockItem> tab = mkDockItemTab(nullptr, std::format("tab-of-{}", item->id));
				tab->width = item->width;
				tab->weight = item->weight;
				parent->insertBefore(tab, item);
				tab->appendChild(item);
				return tab;
			}
		}
	}
	return nullptr;
}

void DockLayout::clearAllEmptyTab(DockItem* item) {
	for (int i = item->children->size() - 1; i >= 0; i--) {
		DockItem* kid = (DockItem*)item->children->get(i);
		if (kid->type == (SPLITTER)) {
			this->clearAllEmptyTab(kid);

			if (kid->children->size() == 0) {//空的Splitter
				kid->removeSelf();
			}
			else if (kid->children->size() == 1) {//只有一个子的splitter,也没有意义
				if (kid->parent) {
					DockItem* solo = kid->children->get(0);
					if (solo) {
						kid->parent->insertBefore(solo, kid); //把子提出来
						kid->removeSelf(); //再把无效的splitter删掉
					}
				}
			}
		}
		else if (kid->isEmptyTab()) { //空的tab要删除
			kid->removeSelf();
		}
		//约束activeIndex
		if (kid->type == (TAB)) {
			kid->setTabActiveIndex(kid->tabActiveIndex);
		}
	}
}

//为splitter下的裸的dockitem包装个tab
void DockLayout::eachThenWrapTab_forNakeDockItemInSplitter(DockItem* item) {
	for (int i = item->children->size() - 1; i >= 0; i--) {
		DockItem* kid = (DockItem*)item->children->get(i);
		if (kid->type == (SPLITTER)) {
			//递归处理
			this->eachThenWrapTab_forNakeDockItemInSplitter(kid);
		}
		else if (kid->type == (ITEM)) {
			//包装在tab中
			this->upto_getOrWrap_DockItemTab(kid);
		}
	}
}

ViewBase* DockLayout::hitTestChildren(float x, float y) {
	return hitTestChildren_withZ(this, x, y);
}

DockSplitterView::DockSplitterView() {
	CtorGuard _(this);
	
	this->cursor = ("pointer");
	this->hitTestPadding = mkInset(3, 3, 3, 3);
}

void DockSplitterView::react() {
	this->backgroundColor = this->hover ? this->hoverBg : this->normalBg;
	this->invalidDraw();
}

void DockSplitterView::onEvent(Event* e) {
	if (dynamic_cast<MouseEvent*>(e)) {
		if (this->drag) {
			this->drag->onMouseDown((MouseEvent*)e);
		}
	}
}

void DockSplitterView::onHoverChanged() {
	this->invalidReact();
}
