#pragma once

#include "../Core/Predef.h"
#include "../Layout/LayoutLinear.h"
#include "../Core/Event.h"
#include "../Core/MouseEvent.h"
#include "../Core/Rect.h"
#include "../Core/Canvas.h"
#include "../Core/Node.h"
#include <vector>
#include <string>
#include <functional>

class TableViewColumn : public GcObj {
public:
	int width = 200;
	std::string label;
};

class TableView : public LayoutLinear {
public:
	Ref<Closure<void()>> renderTh{nullptr, this};
	Ref<Closure<void(Node*, int, int)>> renderTd{nullptr, this};

	int rowHeight = 20;
	int rowCount = 0;

	std::vector<TableViewColumn*> columns;

	int hoverRow = -1;
	int hoverCol = -1;
	int hoverStartX = 0;
	int hoverEndX = 0;

	TableView();
	void react() override;
	void renderHead();
	void renderBody();
	void draw_self(Canvas* canvas) override;
	void onEvent(Event* e) override;
	void onMouseEvent(MouseEvent* e);
	void addColumn(int width, const std::string& label);

	virtual const char* getClassName() const override { return "TableView"; }
};
