#pragma once

#include "../Core/Predef.h"
#include "../Layout/LayoutLinear.h"
#include "../Core/Node.h"
#include "../Core/Event.h"
#include "../Core/MouseEvent.h"
#include <vector>
#include <string>
#include <functional>
//
//class TreeState : public GcObj {
//public:
//	std::vector<void*> roots;
//	std::function<std::string(void*)> getId;
//	std::function<std::vector<void*>(void*)> getItemChildren;
//	std::function<void(TreeState*)> cbSelectedIdChanged;
//	std::function<void*(void*)> getParent;
//
//	std::vector<std::string> selectedIds;
//	std::vector<std::string> opendIds;
//
//	void* getById(const std::string& id);
//	void _flatTree(std::vector<void*>* items, std::vector<std::string>* out);
//	std::vector<std::string> flatTree();
//	void* _getById(const std::string& id, std::vector<void*>* list);
//	void* getFirstSelected();
//	bool isSelected(void* item);
//	bool isOpend(void* item);
//	void setSelectedWithShiftAndCtrl(void* item, bool shift, bool ctrl);
//	void fire_cbSelectedIdChanged();
//	void setAncestorsOpen(void* item);
//	void setSelected(void* item);
//	void setOpen(void* item, bool open);
//
//	virtual const char* getClassName() const { return "TreeState"; }
//};
//
//class TreeView : public LayoutLinear {
//public:
//	Ref<TreeState> state{new TreeState(), this};
//	Ref<Closure<void(Node*, void*, int)>> reactItem{nullptr, this};
//	Ref<Closure<void(Event*, ViewBase*, void*)>> cbOnEvent_forItemView{nullptr, this};
//
//	TreeView();
//	void react() override;
//	void reactChildren(Node* parent, std::vector<void*>* items, int deep);
//
//	virtual const char* getClassName() const override { return "TreeView"; }
//};

class TreeSelfCtrlView : public LayoutLinear {
public:
	bool open = true;
	bool hasKids = true;
	int deep = 0;
	bool isSelected = false;

	TreeSelfCtrlView();
	void onEvent(Event* e) override;
	bool calcVisible();
	void clearSelect();
	void updateForOpen();
	void react() override;

	virtual const char* getClassName() const override { return "TreeSelfCtrlView"; }
};
