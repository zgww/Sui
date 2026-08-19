#include "DockLayout.h"
#include "TextView.h"
#include "../Core/NodeLib.h"

void DockItem::setTabActiveIndex(int index) {
	int sz = children->size();
	tabActiveIndex = index < 0 ? 0 : (index >= sz ? sz - 1 : index);
}

void DockItem::setSelfActive_inTab() {
	if (parent && parent->type == DOCK_TAB) {
		int idx = parent->children->index_of(this);
		parent->setTabActiveIndex(idx);
	}
}

float DockItem::calcWeight_ofKid_forDragSplitter(DockItem* kid, float delta, float minSize) {
	if (kid->width > 0) return 0;
	float actualSize = kid->weight / _sumWeight * _sumFlexSize;
	float newSize = maxFloat(minSize, actualSize + delta);
	float newWeight = newSize / _sumFlexSize * _sumWeight;
	return newWeight;
}

void DockItem::appendChild(DockItem* item) {
	if (!item) return;
	item->removeSelf();
	children->push(item);
	item->parent = this;
}

void DockItem::removeSelf() {
	if (parent) {
		parent->removeChild(this);
	}
}

bool DockItem::insertBefore(DockItem* newItem, DockItem* relChild) {
	return insertOffset(newItem, relChild, 0);
}

bool DockItem::insertAfter(DockItem* newItem, DockItem* relChild) {
	return insertOffset(newItem, relChild, 1);
}

bool DockItem::insertOffset(DockItem* newItem, DockItem* relChild, int offset) {
	if (!newItem) return false;
	int idx = children->index_of(relChild);
	if (idx == -1) return false;
	newItem->removeSelf();
	children->insert_at(idx + offset, newItem);
	newItem->parent = this;
	return true;
}

void DockItem::removeChild(DockItem* kid) {
	if (kid && kid->parent == this) {
		children->remove(kid);
		kid->parent = nullptr;
	}
}

DockItem* DockItem::tryGetParentTab() {
	DockItem* cur = parent;
	if (cur && cur->type == DOCK_TAB) return cur;
	return nullptr;
}

bool DockItem::isEmptySplitter() {
	if (type == DOCK_SPLITTER) return children->size() == 0;
	return false;
}

bool DockItem::isEmptyTab() {
	if (type == DOCK_TAB) return children->size() == 0;
	return false;
}

DockItem* mkDockItem(DockItem* parent, const std::string& id) {
	DockItem* ins = new DockItem();
	ins->id = id;
	if (parent) parent->appendChild(ins);
	return ins;
}

DockItem* mkDockItemSplitter(DockItem* parent, const std::string& id, bool isHorizontal) {
	DockItem* ins = mkDockItem(parent, id);
	ins->type = DOCK_SPLITTER;
	ins->isHorizontal = isHorizontal;
	return ins;
}

DockItem* mkDockItemTab(DockItem* parent, const std::string& id) {
	DockItem* ins = mkDockItem(parent, id);
	ins->type = DOCK_TAB;
	return ins;
}

DockLayout::DockLayout() {
	DockItem* r = mkDockItemSplitter(nullptr, "", true);
	rootHolder = r;
	root = r;

	auto selfRef = this;
	dragTab->onDrag = CLOSURE([=](Drag* d) {
		DockLayout* self = selfRef;
		if (!self) return;
		if (d->isDragging || d->isDragEnd) {
			self->invalidDraw();
		}
		if (d->isDragEnd) {
			self->doDrop();
		}
	});
}

void DockLayout::doDrop() {
	if (!ownerWindow) return;
	Vec2 mousePos = Mouse_getPosOfWindow(ownerWindow ? ownerWindow->id : 0);
	DockItem* target = findDockItem_containsVec2(root, mousePos.x, mousePos.y);
	if (target && target->view) {
		Rect absRect = target->view->get_abs_rect();
		int geoType = -1;
		Rect geo = absRect.containsPositionIn5Patch_withOutType(mousePos.x, mousePos.y,
			Rect(0.2f, 0.2f, 0.6f, 0.6f), &geoType);
		if (geo.x == -1) return;

		DockItem* source = (DockItem*)dragTab->data;
		if (source && source != target) {
			if (geoType == 0) dropInSplitter(source, target, false, true);
			if (geoType == 1) dropInSplitter(source, target, true, true);
			if (geoType == 2) {
				DockItem* tab = upto_getOrWrap_DockItemTab(target);
				if (tab) {
					tab->appendChild(source);
					invalidReact();
				}
			}
			if (geoType == 3) dropInSplitter(source, target, true, false);
			if (geoType == 4) dropInSplitter(source, target, false, false);
			clearAllEmptyTab(root);
		}
	}
}

void DockLayout::react() {
	startInnerReact();
	eachThenWrapTab_forNakeDockItemInSplitter(root);
	_reactDockItem(root);
	endInnerReact();
}

void DockLayout::onDragSplitter(Drag* drag, DockItem* parentDockItem,
	DockItem* prevDockItem, DockItem* nextDockItem) {
	if (drag->isDragChecking) {
		drag->cursor = parentDockItem->isHorizontal ? "sizewe" : "sizens";
	}
	if (drag->isDragging) {
		float delta = drag->deltaPos.y;
		if (parentDockItem->isHorizontal) delta = drag->deltaPos.x;

		if (prevDockItem->width > 0 && nextDockItem->width > 0) {
			prevDockItem->width = maxFloat(minItemSize, prevDockItem->width + delta);
			nextDockItem->width = maxFloat(minItemSize, nextDockItem->width - delta);
		} else if (prevDockItem->width > 0 && nextDockItem->width == 0) {
			prevDockItem->width = maxFloat(minItemSize, prevDockItem->width + delta);
		} else if (prevDockItem->width == 0 && nextDockItem->width > 0) {
			nextDockItem->width = maxFloat(minItemSize, nextDockItem->width - delta);
		} else {
			prevDockItem->weight = parentDockItem->calcWeight_ofKid_forDragSplitter(prevDockItem, delta, minItemSize);
			nextDockItem->weight = parentDockItem->calcWeight_ofKid_forDragSplitter(nextDockItem, -delta, minItemSize);
		}
		invalidLayout();
	}
}

void DockLayout::_reactDockItem(DockItem* item) {
	if (!item) return;
	if (item->type == DOCK_SPLITTER) {
		ViewBase* splitterView = nullptr;
		int l = item->children->size();
		for (int i = 0; i < l; i++) {
			DockItem* kid = item->children->get(i);
			kid->prevSplitterView = splitterView;
			_reactDockItem(kid);
			if (i < l - 1) {
				DockItem* nextKid = item->children->get(i + 1);
				DockSplitterView* sv = gocNode<DockSplitterView>(this, ((int64_t)(intptr_t)item) + 2000 + i);
				if (sv) {
					sv->z = 10;
					auto selfRef = this;
					auto parentItem = item;
					auto curKid = kid;
					auto nextKidItem = nextKid;
					sv->drag->onDrag = CLOSURE([=](Drag* d) {
						DockLayout* self = selfRef;
						if (!self) return;
						self->onDragSplitter(d, parentItem, curKid, nextKidItem);
					});
					sv->cursor = item->isHorizontal ? "sizewe" : "sizens";
					kid->nextSplitterView = sv;
					splitterView = sv;
				}
			}
		}
	}
	if (item->type == DOCK_TAB) {
		LayoutLinear* tabView = gocLayoutLinear(this, (int64_t)(intptr_t)item);
		if (tabView) {
			tabView->needClip = true;
			item->view = tabView;
			tabView->direction = "column";
			tabView->alignItems = "stretch";
			_reactTabHeads(item, tabView);
			_reactTabContent(item, tabView);
		}
	}
	if (item->type == DOCK_ITEM) {
		if (cbRenderItemContentView) {
			ViewBase* v = cbRenderItemContentView->invoke(item, this);
			item->view = v;
		}
	}
}

void DockLayout::_onClickTabItemHead(DockItem* kid) {
	kid->setSelfActive_inTab();
	invalidReact();
}

void DockLayout::_onEvent_tabItemHead(Event* e, DockItem* kid) {
	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
	if (me) {
		if (me->isMouseDown) {
			_onClickTabItemHead(kid);
		}
		dragTab->data = (void*)kid;
		dragTab->onMouseDown(me);
	}
}

void DockLayout::_reactTabHeads(DockItem* tab, ViewBase* parent) {
	LayoutLinear* head = gocLayoutLinear(parent, 0);
	if (!head) return;
	head->direction = "row";
	head->backgroundColor = tabHeadBg;
	int l = tab->children->size();
	for (int i = 0; i < l; i++) {
		DockItem* kid = tab->children->get(i);
		if (kid->type == DOCK_ITEM) {
			LayoutLinear* headItem = gocLayoutLinear(head, (int64_t)(intptr_t)kid);
			if (!headItem) continue;
			auto selfRef = this;
			headItem->cbOnEvent = CLOSURE([=](Event* e) {
				DockLayout* self = selfRef;
				if (!self) return;
				self->_onEvent_tabItemHead(e, kid);
			});
			if (cbRenderItemHeadView) {
				cbRenderItemHeadView->invoke(kid, headItem, i);
			}
		}
	}
}

void DockLayout::_reactTabContent(DockItem* tab, ViewBase* parent) {
	LayoutLinear* content = gocLayoutLinear(parent, 1);
	if (!content) return;
	content->direction = "column";
	content->alignItems = "stretch";

	LayoutLinearCell* cell = content->gocChild<LayoutLinearCell>(0);
	if (cell) {
		cell->grow = 1;
	}

	DockItem* kid = tab->children->get(tab->tabActiveIndex);
	if (kid) {
		if (cbRenderItemContentView) {
			ViewBase* view = cbRenderItemContentView->invoke(kid, content);
			kid->view = view;
		}
	}
}

void DockLayout::layoutContent(Frame* frame) {
	if (!frame->isTight()) return;
	layoutContentDockItem(frame, root, 0, 0);
}

void DockLayout::layoutContentDockItem(Frame* frame, DockItem* item, float px, float py) {
	if (!item || item->type != DOCK_SPLITTER) return;
	int kidsSize = item->children->size();
	float sumSplitterSize = (kidsSize - 1) * (float)splitterSize;
	float mainSize = item->isHorizontal ? frame->width : frame->height;
	float sumContentSize = mainSize - sumSplitterSize;
	float sumWeight = 0;
	float sumWidth = 0;
	for (int i = 0; i < kidsSize; i++) {
		DockItem* kid = item->children->get(i);
		float w = maxFloat(0.0f, kid->width);
		if (w > 0) sumWidth += w;
		else sumWeight += maxFloat(0.0f, kid->weight);
	}
	if (sumWeight <= 0) sumWeight = 1.0f;
	float flexSpaceSize = maxFloat(0.0f, sumContentSize - sumWidth);

	item->_sumContentSize = sumContentSize;
	item->_sumFlexSize = flexSpaceSize;
	item->_sumWeight = sumWeight;

	float pos = 0.0f;
	for (int i = 0; i < kidsSize; i++) {
		DockItem* kid = item->children->get(i);
		Frame tmpFrame;
		Frame* kidFrame = kid->view ? &kid->view->frame : &tmpFrame;

		float kidSize = 0.0f;
		if (item->isHorizontal) {
			kidFrame->x = pos + px;
			kidFrame->y = 0.0f + py;
			kidSize = kid->width > 0 ? kid->width : maxFloat(0.0f, kid->weight) / sumWeight * flexSpaceSize;
			kidFrame->setTight(kidSize, frame->height);
		} else {
			kidFrame->x = 0.0f + px;
			kidFrame->y = pos + py;
			kidSize = kid->width > 0 ? kid->width : maxFloat(0.0f, kid->weight) / sumWeight * flexSpaceSize;
			kidFrame->setTight(frame->width, kidSize);
		}

		if (kid->type == DOCK_SPLITTER) {
			layoutContentDockItem(kidFrame, kid, kidFrame->x, kidFrame->y);
		} else {
			if (kid->view) kid->view->layout(kidFrame);
		}
		pos += kidSize;

		if (kid->nextSplitterView) {
			Frame* f = &kid->nextSplitterView->frame;
			if (item->isHorizontal) {
				f->x = pos + px;
				f->y = 0 + py;
				f->setTight((float)splitterSize, frame->height);
			} else {
				f->x = 0 + px;
				f->y = pos + py;
				f->setTight(frame->width, (float)splitterSize);
			}
			kid->nextSplitterView->layout(f);
			pos += (float)splitterSize;
		}
	}
}

void DockLayout::drawSelfBorder(Canvas* canvas) {
	View::drawSelfBorder(canvas);
	drawDndIndicator(canvas);
}

void DockLayout::drawDndIndicator(Canvas* canvas) {
	Drag* drag = dragTab.get();
	if (!drag || !drag->isDragging) return;
	if (!ownerWindow) return;

	Vec2 mousePos = Mouse_getPosOfWindow(ownerWindow ? ownerWindow->id : 0);
	DockItem* target = findDockItem_containsVec2(root, mousePos.x, mousePos.y);
	if (target && target->view) {
		canvas->save();
		canvas->translate(padding.left + border->l->w, padding.top + border->t->w);

		Rect absRect = target->view->get_abs_rect();
		Rect geo = absRect.containsPositionIn5Patch(mousePos.x, mousePos.y,
			Rect(0.2f, 0.2f, 0.6f, 0.6f));
		Rect r = target->view->frame.toRect();

		canvas->beginPath();
		canvas->fillColor(255, 0, 0, 64);
		canvas->rect(r.x + r.w * geo.x, r.y + r.h * geo.y, r.w * geo.w, r.h * geo.h);
		canvas->fill();
		canvas->restore();
	}
}

DockItem* DockLayout::findDockItem_containsVec2(DockItem* item, float clientX, float clientY) {
	if (!item) return nullptr;
	if (item->view) {
		Rect r = item->view->get_abs_rect();
		if (r.containsPosition(clientX, clientY)) return item;
	}
	int l = item->children->size();
	for (int i = 0; i < l; i++) {
		DockItem* kid = item->children->get(i);
		DockItem* ret = findDockItem_containsVec2(kid, clientX, clientY);
		if (ret) return ret;
	}
	return nullptr;
}

DockItem* DockLayout::upto_findMostAncestorInDockItemSplitter(DockItem* item) {
	DockItem* cur = item;
	while (cur && cur->parent) {
		if (cur->parent->type == DOCK_SPLITTER) return cur;
		cur = cur->parent;
	}
	return nullptr;
}

bool DockLayout::dropInSplitter(DockItem* source, DockItem* target, bool isHorizontal, bool isBefore) {
	DockItem* ancestor = upto_findMostAncestorInDockItemSplitter(target);
	if (!ancestor) return false;
	DockItem* splitter = ancestor->parent;
	if (!splitter || splitter->type != DOCK_SPLITTER) return false;
	source->removeSelf();
	if (splitter->isHorizontal == isHorizontal) {
		splitter->insertOffset(source, ancestor, isBefore ? 0 : 1);
	} else {
		DockItem* newSplitter = mkDockItemSplitter(nullptr, "splitter-of-" + ancestor->id, isHorizontal);
		splitter->insertOffset(newSplitter, ancestor, 0);
		newSplitter->appendChild(ancestor);
		newSplitter->insertOffset(source, ancestor, isBefore ? 0 : 1);
	}
	invalidReact();
	return true;
}

DockItem* DockLayout::upto_getOrWrap_DockItemTab(DockItem* item) {
	if (!item) return nullptr;
	if (item->type == DOCK_SPLITTER) return nullptr;
	if (item->type == DOCK_TAB) return item;
	if (item->type == DOCK_ITEM) {
		DockItem* parent = item->parent;
		if (parent) {
			if (parent->type == DOCK_TAB) return parent;
			if (parent->type == DOCK_SPLITTER) {
				DockItem* tab = mkDockItemTab(nullptr, "tab-of-" + item->id);
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
	if (!item) return;
	for (int i = item->children->size() - 1; i >= 0; i--) {
		DockItem* kid = item->children->get(i);
		if (kid->type == DOCK_SPLITTER) {
			clearAllEmptyTab(kid);
			if (kid->children->size() == 0) kid->removeSelf();
			else if (kid->children->size() == 1) {
				if (kid->parent) {
					DockItem* solo = kid->children->get(0);
					if (solo) {
						kid->parent->insertBefore(solo, kid);
						kid->removeSelf();
					}
				}
			}
		} else if (kid->isEmptyTab()) {
			kid->removeSelf();
		}
		if (kid->type == DOCK_TAB) {
			kid->setTabActiveIndex(kid->tabActiveIndex);
		}
	}
}

void DockLayout::eachThenWrapTab_forNakeDockItemInSplitter(DockItem* item) {
	if (!item) return;
	for (int i = item->children->size() - 1; i >= 0; i--) {
		DockItem* kid = item->children->get(i);
		if (kid->type == DOCK_SPLITTER) {
			eachThenWrapTab_forNakeDockItemInSplitter(kid);
		} else if (kid->type == DOCK_ITEM) {
			upto_getOrWrap_DockItemTab(kid);
		}
	}
}

ViewBase* DockLayout::hitTestChildren(float x, float y) {
	return hitTestChildren_withZ(this, x, y);
}

DockSplitterView::DockSplitterView() {
	cursor = "pointer";
	hitTestPadding.setAll(3);
}

void DockSplitterView::react() {
	backgroundColor = hover ? hoverBg : normalBg;
	invalidDraw();
}

void DockSplitterView::onEvent(Event* e) {
	View::onEvent(e);
	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
	if (me && drag) {
		drag->onMouseDown(me);
	}
}

void DockSplitterView::onHoverChanged() {
	invalidReact();
}
