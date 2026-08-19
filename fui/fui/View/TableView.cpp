#include "TableView.h"
#include "TextView.h"
#include "../Core/NodeLib.h"
#include <cmath>

TableViewColumn* mkTableViewColumn(int width, const std::string& label) {
	TableViewColumn* col = new TableViewColumn();
	col->width = width;
	col->label = label;
	return col;
}

TableView::TableView() {
	direction = "column";
	alignItems = "start";
}

void TableView::addColumn(int width, const std::string& label) {
	columns.push_back(mkTableViewColumn(width, label));
}

void TableView::react() {
	direction = "column";
	alignItems = "start";

	startInnerReact();
	Node* o = this;
	renderHead();
	renderBody();
	endInnerReact();

	height = (float)(rowHeight * (rowCount + 1));
}

void TableView::renderHead() {
	Node* o = this;
	LayoutLinear* head = gocLayoutLinear(o, 0);
	if (!head) return;
	head->height = (float)rowHeight;
	head->direction = "row";

	int l = (int)columns.size();
	for (int i = 0; i < l; i++) {
		TableViewColumn* col = columns[i];
		LayoutLinear* cell = gocLayoutLinear(head, i + 1);
		if (!cell) continue;
		cell->direction = "row";
		cell->justifyContent = "center";
		cell->width = (float)col->width;
		cell->height = (float)rowHeight;
		cell->padding.right = 5;

		TextView* tv = gocTextView(cell, 0);
		if (tv) {
			tv->setColor(0xffffffff);
			tv->setText(col->label);
		}
	}
}

void TableView::renderBody() {
	Node* o = this;
	for (int r = 0; r < rowCount; r++) {
		LayoutLinear* rowView = gocLayoutLinear(o, 1000 + r);
		if (!rowView) continue;
		rowView->height = (float)rowHeight;
		rowView->direction = "row";
		rowView->backgroundColor = 0x3300ffff;

		int l = (int)columns.size();
		for (int i = 0; i < l; i++) {
			TableViewColumn* col = columns[i];
			LayoutLinear* cell = gocLayoutLinear(rowView, i + 1);
			if (!cell) continue;
			cell->backgroundColor = 0x33ffff00;
			cell->direction = "row";
			cell->justifyContent = "center";
			cell->width = (float)col->width;
			cell->height = (float)rowHeight;
			cell->padding.right = 5;

			if (renderTd) {
				renderTd->invoke(cell, r, i);
			} else {
				TextView* tv = gocTextView(cell, 0);
				if (tv) {
					tv->setColor(0xffffffff);
					tv->setText("-");
				}
			}
		}
	}
}

void TableView::draw_self(Canvas* canvas) {
	LayoutLinear::draw_self(canvas);

	Rect r = getContentRect_baseViewRect();
	int w = (int)r.w;
	int h = (int)r.h;

	canvas->save();
	canvas->translate(r.x, r.y);

	canvas->strokeWidth(1);
	canvas->strokeColor(255, 255, 255, 128);
	canvas->beginPath();

	int colX = 0;
	int l = (int)columns.size();
	for (int i = 0; i < l - 1; i++) {
		TableViewColumn* col = columns[i];
		colX += col->width;
		canvas->moveTo((float)colX, 0);
		canvas->lineTo((float)colX, (float)h);
	}

	int maxRow = (int)ceil((float)h / (float)rowHeight);
	int rowToDraw = maxRow > rowCount ? maxRow : rowCount;

	for (int r = 0; r < rowToDraw + 1; r++) {
		int y = r * rowHeight;
		canvas->moveTo(0, (float)y);
		canvas->lineTo((float)w, (float)y);
	}

	canvas->stroke();

	canvas->fillColor(255, 255, 255, 16);
	canvas->beginPath();
	for (int r = 0; r < rowToDraw + 1; r += 2) {
		int y = r * rowHeight;
		canvas->rect(0, (float)y, (float)w, (float)rowHeight);
	}
	canvas->fill();

	if (hoverRow != -1) {
		canvas->fillColor(255, 255, 255, 32);
		canvas->beginPath();
		int y = hoverRow * rowHeight;
		canvas->rect(0, (float)y, (float)w, (float)rowHeight);
		canvas->fill();
	}
	if (hoverCol != -1) {
		canvas->fillColor(255, 255, 255, 32);
		canvas->beginPath();
		int y = hoverRow * rowHeight;
		canvas->rect((float)hoverStartX, 0, (float)(hoverEndX - hoverStartX), (float)h);
		canvas->fill();
	}

	canvas->restore();
}

void TableView::onEvent(Event* e) {
	LayoutLinear::onEvent(e);
	MouseEvent* me = dynamic_cast<MouseEvent*>(e);
	if (me) {
		onMouseEvent(me);
	}
}

void TableView::onMouseEvent(MouseEvent* e) {
	if (e->isMouseMove) {
		Rect r = getContentClientRect();
		float dy = e->clientY - r.y;
		float dx = e->clientX - r.x;
		int row = (int)floor(dy / (float)rowHeight);
		if (hoverRow != row && row >= 0 && row <= rowCount) {
			hoverRow = row;
			invalidDraw();
		}
		int col = -1;
		int colX = 0;
		int endX = 0;
		int l = (int)columns.size();
		for (int i = 0; i < l; i++) {
			TableViewColumn* column = columns[i];
			endX = colX + column->width;
			if (colX <= (int)dx && (int)dx < endX) {
				col = i;
				break;
			}
			colX = endX;
		}
		if (hoverCol != col && col >= 0 && col < (int)columns.size()) {
			hoverCol = col;
			hoverStartX = colX;
			hoverEndX = endX;
			invalidDraw();
		}
	}
	MouseLeaveEvent* le = dynamic_cast<MouseLeaveEvent*>(e);
	if (le) {
		hoverRow = -1;
		invalidDraw();
	}
}
