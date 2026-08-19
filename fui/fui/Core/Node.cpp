#include "Node.h"
#include "Timer.h"

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
		child->removeSelf();
		child->parent = this;
		children->push(child);
		child->setMounted(mounted);
	}
}

void Node::insertChild(Node* child, int at) {
	if (!child) return;
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

void Node::removeChild(Node* child) {
	if (child) {
		child->parent = nullptr;
		children->remove(child);
		child->setMounted(false);
	}
}
void Node::removeChildAt(int idx) {
	auto child = this->getChild(idx);
	if (child) {
		child->parent = nullptr;
		children->remove_at(idx);
		child->setMounted(false);
	}
}
void Node::removeAllChildren() {
	while (children->size() > 0) {
		Node* child = children->get(0);
		if (child) {
			removeChild(child);
		} else {
			break;
		}
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
	if (_mapForReact) {
		_mapForReact->clear();
	}
	if (_unusedMapForReact) {
		_unusedMapForReact->clear();
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

	Ref<Node> self = this;
	requestAnimationFrame(CLOSURE([=]() -> bool {
		self->_reactDirty = false;
		self->react();
		return true;
	}));
}

void Node::clearUnusedKids() {
	Node* n = this;
	if (!_unusedMapForReact) {
		_unusedMapForReact = new GcMap<Node>();
	}
	if (!_mapForReact) {
		_mapForReact = new GcMap<Node>();
	}

	GcMap<Node>* unused = _unusedMapForReact;
	GcMap<Node>* map = _mapForReact;

	std::vector<std::string> keys;
	for (auto& entry : unused->map) {
		keys.push_back(entry.first);
	}

	for (auto& key : keys) {
		Node* unusedNode = unused->get(key);
		if (unusedNode) {
			unusedNode->removeSelf();
		}
	}
	unused->clear();

	// Swap maps
	auto tmp = _mapForReact;
	_mapForReact = _unusedMapForReact;
	_unusedMapForReact = tmp;

	_appendIndexForReact = 0;
}

void Node::placeKid(Node* n) {
	Node* parent = this;
	if (!_unusedMapForReact) {
		_unusedMapForReact = new GcMap<Node>();
	}
	if (!_mapForReact) {
		_mapForReact = new GcMap<Node>();
	}

	GcMap<Node>* unusedMap = _unusedMapForReact;
	GcMap<Node>* map = _mapForReact;

	std::string keyStr(n->key);
	unusedMap->remove(keyStr);
	map->set(keyStr, n);

	parent->insertChild(n, parent->_appendIndexForReact);
	parent->_appendIndexForReact++;
}

void Node::placeKids(Ref<GcList<Node>> kids) {
	if (!kids) return;
	int l = kids->size();
	for (int i = 0; i < l; i++) {
		Node* n = kids->get(i);
		placeKid(n);
	}
}

bool Node::isInInnerReact() {
	return false;
}

void Node::startInnerReact() {
	if (!_unusedMapForReact) _unusedMapForReact = new GcMap<Node>();
	if (!_mapForReact) _mapForReact = new GcMap<Node>();

	auto tmp = _mapForReact;
	_mapForReact = _unusedMapForReact;
	_unusedMapForReact = tmp;

	_appendIndexForReact = 0;
}

void Node::endInnerReact() {
	clearUnusedKids();
}

Ref<GcList<Node>> Node::getOutKids() {
	Ref<GcList<Node>> ret{new GcList<Node>()};
	int l = getChildrenCount();
	for (int i = 0; i < l; i++) {
		Node* kid = getChild(i);
		if (kid && kid->key[0] == '\0') {
			ret->push(kid);
		}
	}
	return ret;
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
			if (kid->key == key) {
				return kid;
			}
			if (kid->key == "") { //到达了静态节点，不在同一个动态块里了，可以直接pass
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