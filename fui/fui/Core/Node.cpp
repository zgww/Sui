#include "Node.h"
#include "Timer.h"
#include "App.h"

// Global animation frame list
static Ref<GcList<Closure<bool()>>> g_animationFrameList;

static GcList<Closure<bool()>>* gocAnimationFrameList() {
	if (g_animationFrameList == nullptr) {
		g_animationFrameList = new GcList<Closure<bool()>>();
	}
	return g_animationFrameList;
}

void requestAnimationFrame(Ref<Closure<bool()>> fn) {
	gocAnimationFrameList()->push(fn);
}

void tickAnimationFrames() {
	GcList<Closure<bool()>>* lst = gocAnimationFrameList();
	int l = lst->size();
	if (l > 0) {
		for (int i = l - 1; i >= 0; i--) {
			Ref<Closure<bool()>> fn = lst->get(i);
			if (fn) {
				bool end = fn->invoke();
				if (end) {
					lst->remove_at(i);
				}
			}
		}
	}
}

void Node::setMounted(bool m) {
	if (mounted == m) return;
	mounted = m;
	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		Node* n = getChild(i);
		n->setMounted(m);
	}
	if (m) {
		baseOnMounted();
	} else {
		baseOnUnmounting();
	}
}

void Node::baseOnMounted() {
	if (parent != nullptr) {
		setOwnerWindow(parent->ownerWindow);
	}
	onMounted();
}

void Node::baseOnUnmounting() {
	setOwnerWindow(nullptr);
	onUnmounting();
}

void Node::setOwnerWindow(Window* win) {
	if (ownerWindow == win) return;
	ownerWindow = win;
	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		Node* kid = getChild(i);
		kid->setOwnerWindow(win);
	}
}

Node* Node::getChild(int i) {
	return children->get(i);
}

void Node::appendChild(Node* child) {
	if (child) {
		this->insertChild(child, this->getChildrenCount());
	}
}

void Node::insertChild(Node* child, int at) {
	if (!child) return;

	//作为outKids参数存在,适用于innerReact
	if (_flagUseOutKids) {
		auto outkids = gocOutKids();
		outkids->insert_at(at, child);
		return;
	}


	if (child->parent != this) {
		child->removeSelf();
		child->parent = this;
		children->insert_at(at, child);
	} else {
		if (children->get(at) == child) return;
		int nowIndex = children->index_of(child);
		if (nowIndex == -1) {
			children->insert_at(at, child);
		} else if (at < nowIndex) {
			children->remove_at(nowIndex);
			children->insert_at(at, child);
		} else {
			children->insert_at(at, child);
			children->remove_at(nowIndex);
		}
	}
	child->setMounted(mounted);
}
void Node::removeChildAt(int idx) {
	//作为outKids参数存在,适用于innerReact
	if (_flagUseOutKids) {
		auto outkids = gocOutKids();
		outkids->remove_at(idx);
		return;
	}


	auto child = this->getChild(idx);
	if (child) {
		child->parent = nullptr;
		children->remove_at(idx);
		child->setMounted(false);
	}
}
void Node::removeChild(Node* child) {
	if (child) {
		auto idx = this->indexOf(child);
		this->removeChildAt(idx);
	}
}
void Node::removeAllChildren() {
	for (int i = this->getChildrenCount()- 1; i >= 0; i--){
		this->removeChildAt(i);
	}
}

int Node::indexOf(Node* child) {
	return children->index_of(child);
}

void Node::removeSelf() {
	if (parent) {
		parent->removeChild(this);
	}
}

void Node::dissolveSubtree() {
	int l = getChildrenCount();
	for (int i = l - 1; i >= 0; i--) {
		Node* n = getChild(i);
		n->dissolveSubtree();
	}

	removeSelf();
}

Ref<GcList<Node>> Node::getAncients(bool includeSelf) {
	Ref<GcList<Node>> ret{new GcList<Node>()};
	if (includeSelf) {
		ret->push(this);
	}
	Node* cur = this;
	while (cur->parent) {
		cur = cur->parent;
		ret->push(cur);
	}
	return ret;
}



void Node::invalidReact() {
	if (_reactDirty) return;
	_reactDirty = true;

	App_use()->_reactDirty = true;

	Ref<Node> self = this;
	requestAnimationFrame(CLOSURE([=]() -> bool {
		self->_reactDirty = false;
		self->react();
		return true;
	}));
}

void Node::placeKid(Node* n) {
	//不需要goc Node, 因为参数就已经是Node了，只需要确定位置正确即可
	//原位置
	if (this->getChild(gocIdx) == n) {
		gocIdx++;
		return;
	}

	//不相等，就转移到位置
	this->insertChild(n, this->gocIdx);
	gocIdx++;
}

void Node::placeKids(Ref<GcList<Node>> kids) {
	if (!kids) return;
	int l = kids->size();
	for (int i = 0; i < l; i++) {
		Node* n = kids->get(i);
		placeKid(n);
	}
}

void Node::placeKidsOfSlot(Ref<GcList<Node>> kids, std::string slot)
{
	if (!kids) return;
	int l = kids->size();
	for (int i = 0; i < l; i++) {
		Node* n = kids->get(i);
		if (n->slot == slot) {
			placeKid(n);
		}
	}
}

void Node::startInnerReact() {
	_flagUseOutKids = false;
}

void Node::endInnerReact() {
	_flagUseOutKids = true;
	Node_removeUnusedKids(this);
}

void Node::initInnerReact()
{
	_flagUseOutKids = true;
	this->gocOutKids();
	//this->react();
}

Ref<GcList<Node>> Node::gocOutKids() {
	if (this->outKids == nullptr) {
		this->outKids = new GcList<Node>();
	}
	return this->outKids;
}

void Node::walkIf(std::function<bool(void* data, Node* n)> fn, void* ud) {
	bool walkChildren = fn(ud, this);
	if (walkChildren) {
		for (int i = 0; i < children->size(); i++) {
			Node* kid = children->get(i);
			kid->walkIf(fn, ud);
		}
	}
}

void Node::walk(std::function<void(void* data, Node* n)> fn, void* ud) {
	fn(ud, this);
	for (int i = 0; i < children->size(); i++) {
		Node* kid = children->get(i);
		kid->walk(fn, ud);
	}
}

Node* Node::getTopest() {
	Node* cur = this;
	while (cur) {
		if (!cur->parent) break;
		cur = cur->parent;
	}
	return cur;
}

std::string Node::toString() {
	return std::string(getClassName()) + ":" + name;
}



Node* Node_findChildByKeyAfterIndexBeforeStaticChild(Node* parent, int start, std::string& key) {
	for (int i = start, l = parent->children->size(); i < l; i++) {
		auto kid = parent->children->get(i);
		if (kid) {
			if (kid->gocKey == key) {
				return kid;
			}
			if (kid->gocKey == "") { //到达了静态节点，不在同一个动态块里了，可以直接pass
				return nullptr;
			}
		}
	}
	return nullptr;
}

void Node_removeUnusedKids(Node* o) {
	for (int start = o->gocIdx, i = o->getChildrenCount() - 1; i >= start; i--) {
		o->removeChildAt(i);
	}
	o->gocIdx = 0; //重置
}