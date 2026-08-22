#include "TreeView.h"
#include "TextView.h"
#include "ImageView.h"
#include "HoverViewEffect.h"
#include "../Core/NodeLib.h"
#include "../Core/Rect.h"
#include "../Core/Frame.h"
#include "../Naga/Path.h"

//
//void* TreeState::getById(const std::string& id) {
//	return _getById(id, &roots);
//}
//
//void TreeState::_flatTree(std::vector<void*>* items, std::vector<std::string>* out) {
//	if (!items || !getId) return;
//	int l = (int)items->size();
//	for (int i = 0; i < l; i++) {
//		void* item = (*items)[i];
//		std::string id = getId(item);
//		out->push_back(id);
//		if (getItemChildren) {
//			std::vector<void*> kids = getItemChildren(item);
//			_flatTree(&kids, out);
//		}
//	}
//}
//
//std::vector<std::string> TreeState::flatTree() {
//	std::vector<std::string> ret;
//	_flatTree(&roots, &ret);
//	return ret;
//}
//
//void* TreeState::_getById(const std::string& id, std::vector<void*>* list) {
//	if (id.empty() || !list) return nullptr;
//	int l = (int)list->size();
//	for (int i = 0; i < l; i++) {
//		void* obj = (*list)[i];
//		std::string curId = getId(obj);
//		if (curId == id) return obj;
//		if (getItemChildren) {
//			std::vector<void*> children = getItemChildren(obj);
//			void* found = _getById(id, &children);
//			if (found) return found;
//		}
//	}
//	return nullptr;
//}
//
//void* TreeState::getFirstSelected() {
//	if (selectedIds.empty()) return nullptr;
//	std::string id = selectedIds[0];
//	return getById(id);
//}
//
//bool TreeState::isSelected(void* item) {
//	if (!item || !getId) return false;
//	std::string id = getId(item);
//	for (auto& s : selectedIds) {
//		if (s == id) return true;
//	}
//	return false;
//}
//
//bool TreeState::isOpend(void* item) {
//	if (!item || !getId) return false;
//	std::string id = getId(item);
//	for (auto& s : opendIds) {
//		if (s == id) return true;
//	}
//	return false;
//}
//
//void TreeState::setSelectedWithShiftAndCtrl(void* item, bool shift, bool ctrl) {
//	if (!shift && !ctrl) {
//		setSelected(item);
//		return;
//	}
//	if (ctrl) {
//		if (item) {
//			std::string id = getId(item);
//			selectedIds.push_back(id);
//			fire_cbSelectedIdChanged();
//		}
//		return;
//	}
//	if (shift) {
//		if (selectedIds.empty()) {
//			setSelected(item);
//			return;
//		}
//		std::vector<std::string> flatIds = flatTree();
//		std::string lastId = selectedIds.back();
//		selectedIds.clear();
//		std::string id = getId(item);
//		int index0 = 0, index1 = 0;
//		int status = 0;
//		for (int i = 0; i < (int)flatIds.size(); i++) {
//			std::string curId = flatIds[i];
//			if (curId == lastId || curId == id) {
//				if (status == 0) {
//					index0 = i;
//					status++;
//				} else {
//					status++;
//					index1 = i;
//				}
//			}
//			if (status >= 1) {
//				selectedIds.push_back(curId);
//			}
//			if (status == 2) break;
//		}
//		selectedIds.push_back(lastId);
//		fire_cbSelectedIdChanged();
//	}
//}
//
//void TreeState::fire_cbSelectedIdChanged() {
//	if (cbSelectedIdChanged) {
//		cbSelectedIdChanged(this);
//	}
//}
//
//void TreeState::setAncestorsOpen(void* item) {
//	if (item && getParent) {
//		item = getParent(item);
//		while (item) {
//			setOpen(item, true);
//			item = getParent(item);
//		}
//	}
//}
//
//void TreeState::setSelected(void* item) {
//	selectedIds.clear();
//	if (item) {
//		std::string id = getId(item);
//		selectedIds.push_back(id);
//	}
//	fire_cbSelectedIdChanged();
//}
//
//void TreeState::setOpen(void* item, bool open) {
//	if (!item || !getId) return;
//	std::string id = getId(item);
//	if (open) {
//		bool found = false;
//		for (auto& s : opendIds) {
//			if (s == id) { found = true; break; }
//		}
//		if (!found) opendIds.push_back(id);
//	} else {
//		for (auto it = opendIds.begin(); it != opendIds.end(); ++it) {
//			if (*it == id) { opendIds.erase(it); break; }
//		}
//	}
//}
//
//TreeView::TreeView() {
//	direction = "column";
//	alignItems = "start";
//}
//
//void TreeView::react() {
//	startInnerReact();
//	Node* o = this;
//	reactChildren(o, &state->roots, 0);
//	endInnerReact();
//	invalidLayout();
//}
//
//void TreeView::reactChildren(Node* parent, std::vector<void*>* items, int deep) {
//	if (!items) return;
//	int l = (int)items->size();
//	for (int i = 0; i < l; i++) {
//		void* item = (*items)[i];
//		bool isOpend = state->isOpend(item);
//
//		long long reactKey = ((long long)(intptr_t)item) + deep * 1000 + i;
//		LayoutLinear* row = gocLayoutLinear(parent, reactKey);
//		if (!row) continue;
//
//		auto selfRef = this;
//		row->cbOnEvent = CLOSURE([=](Event* e) {
//			TreeView* self = selfRef;
//			if (!self) return;
//			MouseEvent* me = dynamic_cast<MouseEvent*>(e);
//			if (me) {
//				if (me->isClickInBubble() && me->button == 1) {
//					self->state->setSelectedWithShiftAndCtrl(item, me->shift, me->ctrl);
//					self->invalidReact();
//				}
//				if (me->isDblClickInBubble()) {
//					self->state->setOpen(item, !self->state->isOpend(item));
//					self->invalidReact();
//				}
//			}
//			if (self->cbOnEvent_forItemView) {
//				self->cbOnEvent_forItemView->invoke(e, dynamic_cast<ViewBase*>(row), item);
//			}
//		});
//
//		row->padding.left = deep * 20;
//		bool isSelected = state->isSelected(item);
//		row->height = 20;
//		row->alignItems = "center";
//		row->justifyContent = "start";
//
//		HoverViewEffect* hve = gocHoverViewEffect(row, 0);
//		if (hve) {
//			hve->isActive = isSelected;
//			hve->backgroundColor = 0x00000000;
//			hve->hoverBackgroundColor = 0x22666666;
//			hve->activeBackgroundColor = 0x330088ff;
//			hve->applyEffect();
//		}
//
//		if (reactItem) {
//			reactItem->invoke(row, item, deep);
//		} else {
//			TextView* tv = gocTextView(row, 0);
//			if (tv) {
//				tv->setText("item-" + std::to_string(i));
//			}
//		}
//
//		if (isOpend) {
//			std::vector<void*> kids = state->getItemChildren(item);
//			reactChildren(parent, &kids, deep + 1);
//		}
//	}
//}

TreeSelfCtrlView::TreeSelfCtrlView() {



	initInnerReact();
}

void TreeSelfCtrlView::onEvent(Event* e) {
	LayoutLinear::onEvent(e);
	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
	if (me) {
		if (me->isClickInBubble() && me->button == 1) {
			clearSelect();
			isSelected = true;
			invalidReact();
		}
		if (me->isDblClickInBubble()) {
			open = !open;
			updateForOpen();
		}
	}
}

bool TreeSelfCtrlView::calcVisible() {
	if (parent) {
		if (deep == 0) return true;
		int l = parent->getChildrenCount();
		int idx = parent->indexOf(this);
		int targetDeep = deep - 1;
		for (int i = idx - 1; i >= 0; i--) {
			Node* kid = parent->getChild(i);
			TreeSelfCtrlView* upper = dynamic_cast<TreeSelfCtrlView*>(kid);
			if (upper && upper->deep == targetDeep) {
				if (!upper->open) return false;
				targetDeep--;
				if (targetDeep < 0) return true;
			}
		}
	}
	return false;
}

void TreeSelfCtrlView::clearSelect() {
	if (parent) {
		int l = parent->getChildrenCount();
		for (int i = 0; i < l; i++) {
			Node* kid = parent->getChild(i);
			TreeSelfCtrlView* next = dynamic_cast<TreeSelfCtrlView*>(kid);
			if (next && next->isSelected) {
				next->isSelected = false;
				next->invalidReact();
			}
		}
		invalidReact();
	}
}

void TreeSelfCtrlView::updateForOpen() {
	if (parent) {
		int l = parent->getChildrenCount();
		int idx = parent->indexOf(this);
		for (int i = idx + 1; i < l; i++) {
			Node* kid = parent->getChild(i);
			TreeSelfCtrlView* next = dynamic_cast<TreeSelfCtrlView*>(kid);
			if (next) {
				if (next->deep > deep) {
					next->visible = next->calcVisible();
				} else {
					break;
				}
			}
		}
		invalidReact();
	}
}

void TreeSelfCtrlView::react() {
	padding.left = deep * 20;
	auto self = Ref(this);
	auto& o = startInnerReact();


	R(HoverViewEffect){
		// o.backgroundColor = idx % 2 == 1 ? 0xffffffff: 0
		// o.backgroundColor =  0xffff0000
		o.isActive = isSelected;
		o.cbOnHoverChanged = CLOSURE([](ViewBase* v) {
			// if (v.hover){
			//     self.editCtx.hoverNode = s
			// } else {
			//     self.editCtx.hoverNode = null
			// }
			// self.invalidDraw()
			printf("Scene.cbOnHoverChanged:%d\n", v->hover);
			});
	} REND;
	R(ImageView){
		o.width = 12;
		o.height = 12;
		o.margin.right = 6;
		o.setSrc(
			hasKids
			?
				open
			? ("./asset/arrow-down.png")
			: ("./asset/arrow-right.png")
				//? Path_resolveFromExecutionDir("./asset/light-arrow-down.png")
				//: Path_resolveFromExecutionDir("./asset/light-arrow-right.png")
			: ""
		);
		o.cbOnEvent = CLOSURE([=](Event* e) {
			if (auto me = dynamic_cast<MouseEvent*>(e)) {
				if (me->isClickInBubble() && me->button == 0) {
					self->open = !self->open;
					self->updateForOpen();
				}
			}
			});
	}REND;

	placeKids(gocOutKids());
	endInnerReact();
}
