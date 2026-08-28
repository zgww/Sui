#include "LayoutCell.h"
#include "ViewBase.h"
#include "App.h"

void LayoutCell::invalidLayout() {
	if (parent) {
		ViewBase* parentView = dynamic_cast<ViewBase*>(parent.get());
		if (parentView) {
			parentView->invalidLayout();
		}
	}
}

void LayoutCell::onMounted() {
	if (parent) {
		ViewBase* parentView = dynamic_cast<ViewBase*>(parent.get());
		if (parentView) {
			Ref<GcList<LayoutCell>> cells = parentView->gocLayoutCells();
			cells->push(this);
			parentView->invalidLayout();
		}
	}
}

void LayoutCell::onUnmounting() {
	if (parent) {
		ViewBase* parentView = dynamic_cast<ViewBase*>(parent.get());
		if (parentView) {
			if (parentView->layoutCells) {
				parentView->layoutCells->remove(this);
			}
			parentView->invalidLayout();
		}
	}
}
