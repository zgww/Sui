#include "ViewBase.h"
#include "Canvas.h"
#include "Window.h"
#include "App.h"
#include "LayoutCell.h"
#include "../Urgc/GcList.h"
#include "../Meta/MetaRegistry.h"

Ref<GcList<LayoutCell>> ViewBase::gocLayoutCells() {
	if (!layoutCells) {
		layoutCells = new GcList<LayoutCell>();
	}
	return layoutCells;
}

ViewBase* ViewBase::getChildViewAt(int at) {
	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		ViewBase* view = getChildAsView(i);
		if (view) {
			at--;
			if (at < 0) {
				return view;
			}
		}
	}
	return nullptr;
}

ViewBase* ViewBase::getChildAsView(int at) {
	Node* o = children->get(at);
	if (o) {
		ViewBase* vb = dynamic_cast<ViewBase*>(o);
		return vb;
	}
	return nullptr;
}

int ViewBase::getChildrenViewCount() {
	int count = 0;
	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->visible) {
			count++;
		}
	}
	return count;
}

Rect ViewBase::getScreenRect() {
	Rect r = get_abs_rect();
	Window* win = getWindow();
	if (win) {
		Vec2 wr = win->getPos();
		r.offset(wr.x, wr.y);
	}
	return r;
}

Rect ViewBase::get_abs_rect() {
	Vec2 pos = localToWorld(0.0f, 0.0f);
	Vec2 sizePos = localToWorld(frame.width, frame.height);
	Vec2 sz = sizePos.sub(pos);
	return mkRect(pos.x, pos.y, sz.x, sz.y);
}

bool ViewBase::_hitTestClientRect(Rect* r, float x, float y) {
	r->x = r->x - hitTestPadding.left;
	r->y = r->y - hitTestPadding.top;
	r->w = r->w + hitTestPadding.hor();
	r->h = r->h + hitTestPadding.ver();
	return r->containsPosition(x, y);
}

bool ViewBase::_hitTestSelf(float x, float y) {
	Rect r = get_abs_rect();
	return _hitTestClientRect(&r, x, y);
}

void ViewBase::invalidReact() {
	Node::invalidReact();
	invalidLayout();
}

Vec2 ViewBase::localToWorld(float x, float y) {
	Vec2 ret = mkVec2(0, 0);
	Vec3 p = _world_transform.transformPoint(x, y, 0.0f);
	ret.x = p.x;
	ret.y = p.y;
	return ret;
}

Vec2 ViewBase::worldToLocal(float x, float y) {
	Vec2 ret = mkVec2(0, 0);
	Mat2d inv = _world_transform;
	inv.inverse();
	Vec3 p = inv.transformPoint(x, y, 0.0f);
	ret.x = p.x;
	ret.y = p.y;
	return ret;
}

ViewBase* ViewBase::hitTest(float x, float y) {
	if (hitTestType == "none") {
		return nullptr;
	}
	if (hitTestType == "nochildren") {
		if (_hitTestSelf(x, y)) {
			return this;
		}
		return nullptr;
	}
	ViewBase* found = hitTestChildren(x, y);
	if (found) {
		return found;
	}
	if (hitTestType == "onlychildren") {
		return nullptr;
	}
	if (_hitTestSelf(x, y)) {
		return this;
	}
	return nullptr;
}

ViewBase* ViewBase::hitTestChildren(float x, float y) {
	int l = children->size();
	for (int i = l - 1; i >= 0; i--) {
		ViewBase* kid_view = getChildAsView(i);
		if (kid_view && kid_view->visible) {
			ViewBase* found = kid_view->hitTest(x, y);
			if (found) {
				return found;
			}
		}
	}
	return nullptr;
}

int ViewBase::viewIndexOf(Node* child) {
	ViewBase* vb = dynamic_cast<ViewBase*>(child);
	if (!vb) return -1;
	int at = -1;
	int l = children->size();
	for (int i = 0; i < l; i++) {
		Node* n = children->get(i);
		if (dynamic_cast<ViewBase*>(n)) {
			at++;
		}
		if (n == child) {
			return at;
		}
	}
	return -1;
}

int ViewBase::viewIndexInParent() {
	if (parent) {
		ViewBase* vb = dynamic_cast<ViewBase*>(parent.get());
		if (vb) {
			return vb->viewIndexOf(this);
		}
	}
	return -1;
}

void ViewBase::markLayoutStart() {
	frame.timesInOneLayout = 0;
	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		ViewBase* v = getChildAsView(i);
		if (v) {
			v->markLayoutStart();
		}
	}
}

void ViewBase::printLayoutTimes(int tab) {
	for (int i = 0; i < tab; i++) {
		printf("\t");
	}
	printf("%s:%d\n", getClassName(), frame.timesInOneLayout);
	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		ViewBase* v = getChildAsView(i);
		if (v) {
			v->printLayoutTimes(tab + 1);
		}
	}
}

void ViewBase::layoutContent(Frame* contentCtx) {
	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		ViewBase* v = getChildAsView(i);
		if (v) {
			v->frame.minWidth = 0;
			v->frame.minHeight = 0;
			v->frame.maxWidth = infinity;
			v->frame.maxHeight = infinity;
			v->layout(&v->frame);
		}
	}
}

void ViewBase::layout(Frame* ctx) {
	ctx->incTimesInOneLayout();
	layoutContent(ctx);
}

void ViewBase::invalidLayout() {
	App_use()->invalidLayout();
}

void ViewBase::draw(Canvas* canvas) {
	canvas->save();

	float l = frame.x;
	float t = frame.y;

	canvas->translate(l, t);
	canvas->transform(transform);
	canvas->currentTransform(&_world_transform);

	{
		draw_self(canvas);
		draw_children(canvas);
	}

	canvas->restore();
}

void ViewBase::draw_children(Canvas* canvas) {
	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		ViewBase* view = getChildAsView(i);
		if (view && view->visible) {
			view->draw(canvas);
		}
	}
}

void ViewBase::draw_self(Canvas* canvas) {
	canvas->fillColorByInt32(0xff00ff33);
	canvas->strokeColorByInt32(0xffff0033);
	canvas->strokeWidth(10);
	canvas->beginPath();
	canvas->rect(10, 10, 100, 100);
	canvas->fill();
	canvas->stroke();
}

void ViewBase::invalidDraw() {
	App_use()->invalidDraw();
}

void ViewBase::setVisible(bool v) {
	if (v != visible) {
		visible = v;
		invalidLayout();
	}
}

void ViewBase::setHover(bool v) {
	if (hover != v) {
		hover = v;
		onHoverChanged();
	}
}

void ViewBase::onHoverChanged() {
	if (cbOnHoverChanged) {
		cbOnHoverChanged->invoke();
	}
}

std::string ViewBase::toString() {
	char tmp[256];
	snprintf(tmp, sizeof(tmp), "[%f,%f,%f,%f]",
		frame.x, frame.y, frame.width, frame.height);
	return std::string(getClassName()) + ":" + name + tmp;
}

ViewBase* hitTestChildren_withZ(ViewBase* ins, float x, float y) {
	int l = ins->children->size();
	ViewBase* ret = nullptr;
	for (int i = l - 1; i >= 0; i--) {
		ViewBase* kid_view = ins->getChildAsView(i);
		if (kid_view && kid_view->visible) {
			ViewBase* found = kid_view->hitTest(x, y);
			if (found) {
				if (ret == nullptr || found->z > ret->z) {
					ret = found;
				}
			}
		}
	}
	return ret;
}

void ViewBase::registerMeta() {
	auto reg = MetaRegistry::instance()->registerClass<ViewBase, Node>();

	reg.property("visible", &ViewBase::visible);
	reg.property("cursor", &ViewBase::cursor);
	reg.property("hover", &ViewBase::hover);
	reg.property("z", &ViewBase::z);
}
