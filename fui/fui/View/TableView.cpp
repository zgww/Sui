#include "TableView.h"
#include "TextView.h"
#include "../Core/NodeLib.h"
#include <cmath>

std::shared_ptr<TableViewColumn> mkTableViewColumn(int width, const std::string& label) {
	auto col = std::make_shared<TableViewColumn>();
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

	R(LayoutLinear){
		o->height = rowHeight;
		o->direction = ("row");

		int l = columns.size();
		for (int i = 0; i < l; i++) {
			auto col = columns[i];
			R(LayoutLinear, i) {
				o->direction = ("row");
				o->justifyContent = ("center");
				o->width = col->width;
				o->height = rowHeight;
				o->padding.right = 5;

				R(TextView) {
					o->setColor(0xffffffff);
					o->setText(col->label);
				} REND;
			} REND;
		}
	} REND;
}

void TableView::renderBody() {
	Node* o = this;
	for (int r = 0; r < rowCount; r++) {
		R(LayoutLinear, r){
			o->height = rowHeight;
				// o->width = 400
			o->direction=("row");
				// o->justifyContent.set("center")
			o->backgroundColor = 0x3300ffff;

			int l = columns.size();
			for (int i = 0; i < l; i++) {
				auto col = columns[i];
				R(LayoutLinear, i){
					o->backgroundColor = 0x33ffff00;
					o->direction=("row");
					o->justifyContent=("center");
					o->width = col->width;
					o->height = rowHeight;
					o->padding.right = 5;

					if (renderTd != nullptr) {
						renderTd->invoke(o, r, i);
					}
					else {
						R(TextView, i) {
							o->setColor(0xffffffff);
							o->setText(("-"));
						} REND;
					}
				} REND;
			}
		} REND;
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
		auto col = columns[i];
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
			auto column = columns[i];
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
