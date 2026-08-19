#pragma once

#include "Predef.h"
#include "Event.h"

class FocusEvent : public Event {
public:
	bool isFocus = false;
	bool isBlur = false;
	Ref<Node> source{nullptr, this};

	void init(Node* src, bool b) {
		source = src;
		isFocus = b;
		isBlur = !b;
	}
};

class Focus : public GcObj {
public:
	Ref<Node> focusNode{nullptr, this};

	void focus(Node* node);
	void blurNode(Node* n);
	void blur();
	Node* getFocusNode() { return focusNode; }
	bool isFocus(Node* node) { return focusNode == node; }
	bool hasFocus() { return focusNode != nullptr; }
};

Focus* insFocus();
