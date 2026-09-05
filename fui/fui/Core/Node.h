#pragma once

#include "Predef.h"
#include "Emitter.h"
#include "../Urgc/GcList.h"
#include "../Urgc/GcMap.h"
#include <string>
#include <format>
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
#define LINE_KEY (TO_STRING(__LINE__)  "L")

// 根据类型 get or create
#define R(Type, ...) {auto _tmp = Node_getOrCreate<Type>(&o, ##__VA_ARGS__); auto& o = *_tmp.get();
// 参数就是节点了，不需要再get or create. 主要是在匹配REND进行清理
#define RINS(n) {auto& o = *n;
#define REND Node_removeUnusedKids(&o); o.react();} 

template <class T>
bool isSameNodeType(Node* curNode) {
	auto typeName = typeid(T).name();
	auto nodeTypeName = typeid(*curNode).name();
	return _strcmpi(typeName, nodeTypeName) == 0;
}

void Node_removeUnusedKids(Node* o);
Node* Node_findChildByKeyAfterIndexBeforeStaticChild(Node* parent, int start, std::string& key);


void requestAnimationFrame(Ref<Closure<bool()>> fn);
void tickAnimationFrames();

class Node : public Emitter {
public:
	Ref<GcList<Node>> children{ new GcList<Node>(), this };
	Ref<Node> parent{nullptr, this};
	Ref<GcList<Node>> outKids{ nullptr, this };

	std::string name;
	std::string slot; //用于placeKids

	//用于goc
	int gocIdx = 0; 
	std::string gocKey; 

	bool mounted = false;
	Ref<Window> ownerWindow{nullptr, this};

	bool _flagUseOutKids = false;

	bool _reactDirty = false;

	//标记是不是新建的节点,用于react时判断节点是create/update
	bool created = true;

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
	virtual void invalidReact();
	void placeKid(Node* n);
	void placeKids(Ref<GcList<Node>> kids);
	void placeKidsOfSlot(Ref<GcList<Node>> kids, std::string slot);
	void placeOutKids(std::string slot="");
	// innerReact适用于有内部子树，有槽节点的情况
	void initInnerReact();
	Node& startInnerReact();
	void endInnerReact();
	Ref<GcList<Node>> gocOutKids();

	void removeOutChildAt(int idx);
	//根据_flagUseOutKids,取得对应的child
	Node* getOutChild(int i);
	int getOutChildrenCount();
	void insertOutChild(Node* child, int at);


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
	template<typename T>
	T* findChildByClass() {
		int l = getChildrenCount();
		for (int i = 0; i < l; i++) {
			Node* kid = getChild(i);
			if (kid) {
				T* found = dynamic_cast<T*>(kid);
				if (found) return found;
			}
		}
		return nullptr;
	}

	virtual std::string toString();

	virtual const char* getClassName() const { return "Node"; }
};



template <class T>
Ref<T> Node_getOrCreate(Node* o, std::string key = "") {
	if (key == "") { //期望静态节点
		while (true) {
			auto curNode = o->getOutChild(o->gocIdx);
			if (curNode == nullptr) {
				break; //需要创建
			}
			if (curNode->gocKey.empty()) {//是静态节点
				if (isSameNodeType<T>(curNode)) { //匹配一致
					o->gocIdx++;
					curNode->created = false; //标记为update
					return (T*)curNode;
				}
				else {
					throw std::runtime_error(std::format("static node type is different {}", o->gocIdx));
				}
			}
			else { //非静态节点
				o->removeOutChildAt(o->gocIdx); //直接移除
			}

		}
	}
	else { //带key节点
		while (true) {
			auto curNode = o->getOutChild(o->gocIdx);
			if (curNode == nullptr) {
				break; //需要创建
			}
			if (curNode->gocKey == key) { //key匹配
				if (isSameNodeType<T>(curNode)) { //匹配一致
					o->gocIdx++;
					curNode->created = false; //标记为update
					return (T*)curNode;
				}
				else {
					auto typeName = typeid(T).name();
					auto nodeTypeName = typeid(*curNode).name();
					throw std::runtime_error(std::format("dynamic node type is different gocIdx:{}, key:{}", o->gocIdx, key));
				}
			}
			else { // key不匹配，向后查找 
				auto found = Node_findChildByKeyAfterIndexBeforeStaticChild(o, o->gocIdx + 1, key);
				if (found) {
					if (isSameNodeType<T>(found)) { //类型匹配一致,需要移位回来
						o->insertOutChild(found, o->gocIdx);
						o->gocIdx++;
						found->created = false;//标记为update
						return (T*)found;
					}
					else {
						throw std::runtime_error(std::format("dynamic founded node type is different gocIdx:{}, key:{}", o->gocIdx, key));
					}
				}
				else { //未找到，需要新增
					break;
				}
				//需要删除的就会一直被移到后面，如果后面还有静态节点，就会把无效的动态节点删除，如果后面已经没有静态节点了， 那就会剩下一些无效节点，需要删除
			}
		}
	}

	//创建新节点
	Ref<T> ret{ new T() };
	ret->gocKey = key;
	o->insertOutChild(ret.get(), o->gocIdx);
	o->gocIdx++;
	return ret;
}
template <class T>
Ref<T> Node_getOrCreate(Ref<Node>& o, std::string key = "") {
	auto n = o.get();
	return Node_getOrCreate<T>(n, key);
}
template <class T>
Ref<T> Node_getOrCreate(Node* o, long long key) {
	return Node_getOrCreate<T>(o, std::to_string(key));
}
template <class T>
Ref<T> Node_getOrCreate(Ref<Node>& o, long long key) {
	auto n = o.get();
	return Node_getOrCreate<T>(n, std::to_string(key));
}

