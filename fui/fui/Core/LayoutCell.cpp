#include "LayoutCell.h"
#include "ViewBase.h"
#include "App.h"

#include <rttr/registration>

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
RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<LayoutCell>("LayoutCell")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.method("invalidLayout", &LayoutCell::invalidLayout)
		.method("onMounted", &LayoutCell::onMounted)
		.method("onUnmounting", &LayoutCell::onUnmounting)
		.method("getClassName", &LayoutCell::getClassName);
}
