#pragma once

#include "Predef.h"
#include "Node.h"
#include "ViewBase.h"
#include "View.h"

class LayoutLinear;
class TextView;
class ImageView;
class HoverViewEffect;
class Button;
class EditText;

template<typename T>
T* gocNode(Node* parent, long long key) {
	return nullptr;
}

LayoutLinear* gocLayoutLinear(Node* parent, long long key);
TextView* gocTextView(Node* parent, long long key);
ImageView* gocImageView(Node* parent, long long key);
HoverViewEffect* gocHoverViewEffect(Node* parent, long long key);
Button* gocButton(Node* parent, long long key);
EditText* gocEditText(Node* parent, long long key);
View* gocView(Node* parent, long long key);
