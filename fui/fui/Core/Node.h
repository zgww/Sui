#pragma once

#include "Predef.h"
#include "Emitter.h"
#include "../Urgc/GcList.h"
#include "../Urgc/GcMap.h"

class Node;
class Window;

/*
* 一个简单的规则
* 对于静态的children, 都没有key,
* 对于非静态的，如if/for，都必须要有key
* 那么对于静态的child, 判断一下是不是静态节点，如果不是，就删掉，然后尝试下一个。 如果是，判断一下类型是否一致，一致就返回，不一致，就直接报错
* 如:
* Text1""
* Text2""
* Text3""
* KEY1
* KEY2
* KEY3
* Text4""
* Text5
*
* =>
* Text1""
* Text2""
* Text3""
* KEY2
* Text4""
* Text5
*
* * =>
* Text1""
* Text2""
* Text3""
* KEY4
* KEY3
* KEY2
* Text4""
* Text5
*/
#define TO_STRING_(x) #x
#define TO_STRING(x) TO_STRING_(x)
#define CONCAT(a, b) a##b
#define LINE_KEY TO_STRING(__LINE__)##"L"

#define R(Type, ...) {auto _tmp = r<Type>(o, ##__VA_ARGS__), o = _tmp;
#define REND Node_removeUnusedKids(o); o->react();} 

template <class T>
bool isSameNodeType(Node* curNode) {
	auto typeName = typeid(T).name;
	auto nodeTypeName = typeid(curNode).name;
	return _strcmpi(typeName, nodeTypeName) == 0;
}

void Node_removeUnusedKids(Node* o);
Node* Node_findChildByKeyAfterIndexBeforeStaticChild(Node* parent, int start, std::string& key);


template <class T>
Ref<T> r(Node* o, std::string key = "") {
	if (key == "") { //期望静态节点
		while (true) {
			auto curNode = o->getChild(o->gocIdx);
			if (curNode == nullptr) {
				break; //需要创建
			}
			if (curNode->gocKey.empty()) {//是静态节点
				if (isSameNodeType<T>(curNode)) { //匹配一致
					o->gocIdx++;
					return curNode;
				}
				else {
					throw std::exception(std::format("static node type is different {}", o->gocIdx));
				}
			}
			else { //非静态节点
				o->removeChild(o->gocIdx); //直接移除
			}

		}
	}
	else { //带key节点
		while (true) {
			auto curNode = o->getChild(o->gocIdx);
			if (curNode == nullptr) {
				break; //需要创建
			}
			if (curNode->gocKey == key) { //key匹配
				if (isSameNodeType<T>(curNode)) { //匹配一致
					o->gocIdx++;
					return curNode;
				}
				else {
					throw std::exception(std::format("dynamic node type is different gocIdx:{}, key:{}", o->gocIdx, key));
				}
			}
			else { // key不匹配，向后查找 
				auto found = Node_findChildByKeyAfterIndexBeforeStaticChild(o, o->gocIdx + 1, key);
				if (found) {
					if (isSameNodeType<T>(found)) { //类型匹配一致,需要移位回来
						o->insertChild(found, o->gocIdx);
						o->gocIdx++;
						return found;
					}
					else {
						throw std::exception(std::format("dynamic founded node type is different gocIdx:{}, key:{}", o->gocIdx, key));
					}
				}
				else { //未找到，需要新增

				}
				//需要删除的就会一直被移到后面，如果后面还有静态节点，就会把无效的动态节点删除，如果后面已经没有静态节点了， 那就会剩下一些无效节点，需要删除
			}
		}
	}

	//创建新节点
	Ref<T> ret{ new T() };
	ret->gocKey = key;
	o->insertChild(ret.get(), o->gocIdx);
	o->gocIdx++;
	return ret;
}
template <class T>
Ref<T> r(Ref<Node>& o, std::string key = "") {
	return r(o.get(), key);
}



void requestAnimationFrame(Ref<Closure<bool()>> fn);
void tickAnimationFrames();

class Node : public Emitter {
public:
	char key[32] = {0};

	Ref<GcList<Node>> children{new GcList<Node>(), this};
	Ref<Node> parent{nullptr, this};

	std::string name;

	//用于goc
	int gocIdx = 0; 
	std::string gocKey;

	bool mounted = false;
	Ref<Window> ownerWindow{nullptr, this};

	bool hasInnerReact = false;
	bool _reactDirty = false;

	Ref<GcMap<Node>> _mapForReact{nullptr, this};
	Ref<GcMap<Node>> _unusedMapForReact{nullptr, this};
	int _appendIndexForReact = 0;
	bool isNewForReact = true;

	// Lifecycle
	void setMounted(bool m);
	virtual void baseOnMounted();
	virtual void baseOnUnmounting();
	virtual void onMounted() {}
	virtual void onUnmounting() {}

	// Tree operations
	void setOwnerWindow(Window* win);
	Node* getChild(int i);
	Window* getWindow() { return ownerWindow; }
	int getChildrenCount() { return children->size(); }
	void appendChild(Node* child);
	void insertChild(Node* child, int at);
	void removeChild(Node* child);

	void removeChildAt(int idx);
	void removeAllChildren();
	int indexOf(Node* child);
	void removeSelf();
	void dissolveSubtree();

	Ref<GcList<Node>> getAncients(bool includeSelf);

	// React system
	virtual void react() {}
	void invalidReact();
	void clearUnusedKids();
	void placeKid(Node* n);
	void placeKids(Ref<GcList<Node>> kids);
	bool isInInnerReact();
	void startInnerReact();
	void endInnerReact();
	Ref<GcList<Node>> getOutKids();


	template<typename T>
	T* gocChild(long long key) {
		if (!_unusedMapForReact) _unusedMapForReact = new GcMap<Node>();
		if (!_mapForReact) _mapForReact = new GcMap<Node>();

		char keyStr[32];
		snprintf(keyStr, sizeof(keyStr), "%lld", key);

		Node* existing = _unusedMapForReact->get(keyStr);
		if (existing) {
			T* casted = dynamic_cast<T*>(existing);
			if (casted) {
				placeKid(casted);
				return casted;
			}
		}

		T* node = new T();
		snprintf(node->key, sizeof(node->key), "%lld", key);
		placeKid(node);
		return node;
	}

	template<typename T>
	T* gocChildStr(const std::string& key) {
		if (!_unusedMapForReact) _unusedMapForReact = new GcMap<Node>();
		if (!_mapForReact) _mapForReact = new GcMap<Node>();

		Node* existing = _unusedMapForReact->get(key);
		if (existing) {
			T* casted = dynamic_cast<T*>(existing);
			if (casted) {
				placeKid(casted);
				return casted;
			}
		}

		T* node = new T();
		snprintf(node->key, sizeof(node->key), "%s", key.c_str());
		placeKid(node);
		return node;
	}

	// Utility
	void walkIf(std::function<bool(void* data, Node* n)> fn, void* ud);
	void walk(std::function<void(void* data, Node* n)> fn, void* ud);
	Node* getTopest();
	template<typename T>
	T* getAncestorByClass() {
		Node* cur = this;
		while (cur) {
			if (dynamic_cast<T*>(cur)) break;
			cur = cur->parent;
		}
		return dynamic_cast<T*>(cur);
	}
	template<typename T>
	T* findNodeByClass() {
		if (dynamic_cast<T*>(this)) return dynamic_cast<T*>(this);
		int l = getChildrenCount();
		for (int i = 0; i < l; i++) {
			Node* kid = getChild(i);
			if (kid) {
				T* found = kid->findNodeByClass<T>();
				if (found) return found;
			}
		}
		return nullptr;
	}

	virtual std::string toString();

	virtual const char* getClassName() const { return "Node"; }
};
