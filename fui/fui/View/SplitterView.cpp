#include "SplitterView.h"
#include "../Core/Cursor.h"

SplitterView::SplitterView() {
	CtorGuard g(this);

	hitTestPadding.setAll(3);
	cursor = "sizewe";

	auto selfRef = this;
	drag->onDrag = CLOSURE([=](Drag* d) {
		SplitterView* self = selfRef;
		if (!self || !self->parent) return;

		LayoutLinear* ll = dynamic_cast<LayoutLinear*>(self->parent.get());
		if (!ll) return;

		bool isHor = ll->calcIsHor();
		int idx = self->parent->indexOf(self);
		if (idx == 0 || idx == self->parent->getChildrenCount() - 1) return;

		ViewBase* parentView = dynamic_cast<ViewBase*>(self->parent.get());
		if (!parentView) return;

		ViewBase* prev = parentView->getChildAsView(idx - 1);
		ViewBase* next = parentView->getChildAsView(idx + 1);
		if (!prev || !next) return;

		LayoutLinearCell* prevCell = prev->getLayoutCellByType<LayoutLinearCell>();
		LayoutLinearCell* nextCell = next->getLayoutCellByType<LayoutLinearCell>();
		if (!prevCell || !nextCell) return;

		if (d->isDragStart) {
			Cursor_ins()->setCursor(self->cursor.c_str());
			Cursor_ins()->setIsLocked(true);
			if (isHor) {
				self->prevGrow = prev->frame.width;
				self->nextGrow = next->frame.width;
			} else {
				self->prevGrow = prev->frame.height;
				self->nextGrow = next->frame.height;
			}
		}
		if (d->isDragging) {
			if (isHor) {
				self->prevGrow += d->deltaPos.x;
				self->nextGrow -= d->deltaPos.x;
			} else {
				self->prevGrow += d->deltaPos.y;
				self->nextGrow -= d->deltaPos.y;
			}
			if (self->prevGrow < 0) {
				self->nextGrow += self->prevGrow;
				self->prevGrow -= self->prevGrow;
			} else if (self->nextGrow < 0) {
				self->prevGrow += self->nextGrow;
				self->nextGrow -= self->nextGrow;
			}
			prevCell->grow = self->prevGrow;
			nextCell->grow = self->nextGrow;
		}
		if (d->isDragEnd) {
			Cursor_ins()->setIsLocked(false);
		}

		parentView->invalidLayout();
	});

	drag->onDrag = CLOSURE([=](Drag* d) {
		selfRef->updateSiblingsGrow(d);


		//SplitterView* self = selfRef;
		//if (!self || !self->parent) return;

		//LayoutLinear* ll = dynamic_cast<LayoutLinear*>(self->parent.get());
		//if (!ll) return;

		//bool isHor = ll->calcIsHor();
		//int idx = self->parent->indexOf(self);
		//if (idx == 0 || idx == self->parent->getChildrenCount() - 1) return;

		//ViewBase* parentView = dynamic_cast<ViewBase*>(self->parent.get());
		//if (!parentView) return;

		//ViewBase* prev = parentView->getChildAsView(idx - 1);
		//ViewBase* next = parentView->getChildAsView(idx + 1);
		//if (!prev || !next) return;

		//LayoutLinearCell* prevCell = prev->getLayoutCellByType<LayoutLinearCell>();
		//LayoutLinearCell* nextCell = next->getLayoutCellByType<LayoutLinearCell>();
		//if (!prevCell || !nextCell) return;

		//if (d->isDragStart) {
		//	Cursor_ins()->setCursor(self->cursor.c_str());
		//	Cursor_ins()->setIsLocked(true);
		//	if (isHor) {
		//		self->prevGrow = prev->frame.width;
		//		self->nextGrow = next->frame.width;
		//	} else {
		//		self->prevGrow = prev->frame.height;
		//		self->nextGrow = next->frame.height;
		//	}
		//}
		//if (d->isDragging) {
		//	if (isHor) {
		//		self->prevGrow += d->deltaPos.x;
		//		self->nextGrow -= d->deltaPos.x;
		//	} else {
		//		self->prevGrow += d->deltaPos.y;
		//		self->nextGrow -= d->deltaPos.y;
		//	}
		//	if (self->prevGrow < 0) {
		//		self->nextGrow += self->prevGrow;
		//		self->prevGrow -= self->prevGrow;
		//	} else if (self->nextGrow < 0) {
		//		self->prevGrow += self->nextGrow;
		//		self->nextGrow -= self->nextGrow;
		//	}
		//	prevCell->grow = self->prevGrow;
		//	nextCell->grow = self->nextGrow;
		//}
		//if (d->isDragEnd) {
		//	Cursor_ins()->setIsLocked(false);
		//}

		//parentView->invalidLayout();
	});
}

void SplitterView::updateSiblingsGrow(Drag* d) {
	auto parentView = parent.dy_cast<LayoutLinear*>();
	if (parentView == nullptr) {
		return;
	}
	std::vector<LayoutLinearCell*> cells;
	for (int i = 0; i < parentView->getChildrenCount(); i++) {
		auto cell = parentView->getChild(i)->findChildByClass<LayoutLinearCell>();
		if (cell) {
			cells.push_back(cell);
		}
	}


	bool isHor = parentView->calcIsHor();

	if (d->isDragStart) {
		//更新为所在视图的width
		for (auto cell : cells) {
			auto hostView = cell->parent.dy_cast<ViewBase*>();
			if (hostView) {
				cell->grow = isHor ? hostView->frame.width : hostView->frame.height;
			}
		}
	}
	if (d->isDragging) {
		int idx = parent->indexOf(this);

		ViewBase* prev = parentView->getChildAsView(idx - 1);
		ViewBase* next = parentView->getChildAsView(idx + 1);
		if (!prev || !next) {
			return;
		}

		LayoutLinearCell* prevCell = prev->getLayoutCellByType<LayoutLinearCell>();
		LayoutLinearCell* nextCell = next->getLayoutCellByType<LayoutLinearCell>();
		if (!prevCell || !nextCell) {
			return;
		}

		prevCell->grow += isHor ? d->deltaPos.x : d->deltaPos.y;
		nextCell->grow -= isHor ? d->deltaPos.x : d->deltaPos.y;
	}

	if (d->isDragEnd) {
		Cursor_ins()->setIsLocked(false);
	}
	parentView->invalidLayout();
}
void SplitterView::react() {
	backgroundColor = hover ? hoverBg : normalBg;

	LayoutLinear* ll = dynamic_cast<LayoutLinear*>(parent.get());
	if (ll) {
		bool isHor = ll->calcIsHor();
		cursor = isHor ? "sizewe" : "sizens";
	}


	invalidDraw();
}

void SplitterView::onEvent(Event* ev) {
	View::onEvent(ev);
	if (ev->isStopPropagation) return;

	MouseEvent* me = dynamic_cast<MouseEvent*>(ev);
	if (me && drag) {
		drag->onMouseDown(me);
	}
}

void SplitterView::onHoverChanged() {
	invalidReact();
}
