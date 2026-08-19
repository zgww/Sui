#include "NodeLib.h"
#include "../Layout/LayoutLinear.h"
#include "../View/TextView.h"
#include "../View/ImageView.h"
#include "../View/HoverViewEffect.h"
#include "../View/Button.h"
#include "../View/EditText.h"

LayoutLinear* gocLayoutLinear(Node* parent, long long key) {
	return gocNode<LayoutLinear>(parent, key);
}

TextView* gocTextView(Node* parent, long long key) {
	return gocNode<TextView>(parent, key);
}

ImageView* gocImageView(Node* parent, long long key) {
	return gocNode<ImageView>(parent, key);
}

HoverViewEffect* gocHoverViewEffect(Node* parent, long long key) {
	return gocNode<HoverViewEffect>(parent, key);
}

Button* gocButton(Node* parent, long long key) {
	return gocNode<Button>(parent, key);
}

EditText* gocEditText(Node* parent, long long key) {
	return gocNode<EditText>(parent, key);
}

View* gocView(Node* parent, long long key) {
	return gocNode<View>(parent, key);
}
