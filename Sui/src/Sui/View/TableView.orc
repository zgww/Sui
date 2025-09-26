package SuiView

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include <math.h>

import * from "../../Orc/List.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../Core/Node.orc"
import * from "../Core/Event.orc"
import * from "../Core/MouseEvent.orc"
import * from "../Core/View.orc"
import * from "../Core/Rect.orc"
import * from "../Core/Canvas.orc"
import * from "../Layout/LayoutLinear.orc"
import * from "./ViewBuilder.orc"
import * from "./TextView.orc"


 
//表格列
class TableViewColumn {
	int width = 200
	String@ label = str("")
}
TableViewColumn@ mkTableViewColumn(int width, String@ label){
	TableViewColumn@ col = new TableViewColumn()
	col.width = width
	col.label = label
	return col
}
/// 
class TableView extends LayoutLinear {
	^void () renderTh 
	^void (Node *o, int row, int column) renderTd

	int rowHeight = 20
	int rowCount = 0

	List@ columns = new List()
	void react(){
		self.direction = str("column")
		self.alignItems = str("start")
		// self.{
		// }
		self.startInnerReact()
		Node* o = (Node*)self
		self.renderHead()
		self.renderBody()
		self.endInnerReact()

		self.height= self.rowHeight * (self.rowCount + 1)
	}
	void renderHead(){
		Node* o = (Node*)self
		layoutLinear(o, 0).{
			o.height = self.rowHeight
			o.direction.set("row")

			int l = self.columns.size()
			for (int i = 0; i < l; i++){
				TableViewColumn* col = (TableViewColumn*)self.columns.get(i)
				layoutLinear(o, i).{
					o.direction.set("row")
					o.justifyContent.set("center")
					o.width = col.width
					o.height = self.rowHeight
					o.padding.right = 5

					mkTextView(o, 0).{
						o.setColor(0xffffffff)
						o.setText(col.label)
					}
				}
			}
		}
	}
	void renderBody(){
		Node* o = (Node*)self
		for (int r = 0; r < self.rowCount; r++){
			layoutLinear(o, r).{
				o.height = self.rowHeight
				// o.width = 400
				o.direction.set("row")
				// o.justifyContent.set("center")
				o.backgroundColor = 0x3300ffff

				int l = self.columns.size()
				for (int i = 0; i < l; i++){
					TableViewColumn* col = (TableViewColumn*)self.columns.get(i)
					layoutLinear(o, i).{
						o.backgroundColor = 0x33ffff00
						o.direction.set("row")
						o.justifyContent.set("center")
						o.width = col.width
						o.height = self.rowHeight
						o.padding.right = 5

						if (self.renderTd != null){
							self.renderTd(o, r, i)
						}
						else {
							mkTextView(o, i).{
								o.setColor(0xffffffff)
								o.setText(str("-"))
							}
						}
					}
				}
			}
		}
	}

	void draw_self(Canvas *canvas){
		super.draw_self(canvas)

		// int w = self.layoutCtx.width
		// int h = self.layoutCtx.height
		Rect r = self.getContentRect_baseViewRect()
		int w = r.w
		int h = r.h


		canvas.save()
		canvas.translate(r.x, r.y)

		//绘制网格线
		canvas.strokeWidth( 1)
		canvas.strokeColor( 255, 255, 255, 128)
		canvas.beginPath()


		int colX = 0
		//竖线
		int l = self.columns.size() 
		for (int i = 0; i < l - 1; i++){
			TableViewColumn* col = (TableViewColumn*)self.columns.get(i)
			colX = colX + col.width

			canvas.moveTo( colX, 0)
			canvas.lineTo( colX, h)
			// if (i < l){
			// 	TableViewColumn* col = self.columns.get(i)
			// 	colX = colX + col.width
			// }
		}

		int maxRow = ceil(h / self.rowHeight)
		int rowToDraw = maxInt(maxRow, self.rowCount)

		//横线
		for (int r = 0; r < rowToDraw + 1; r++){
			int y = r * self.rowHeight
			canvas.moveTo( 0, y)
			canvas.lineTo( w, y)
		}

		canvas.stroke()

		canvas.fillColor( 255, 255, 255, 16)
		canvas.beginPath()
		//隔行绘制
		for (int r = 0; r < rowToDraw + 1; ){
			int y = r * self.rowHeight
			canvas.rect( 0, y, w, self.rowHeight)
			r = r + 2
		}
		canvas.fill()

		//绘制hover
		if (self.hoverRow != -1){
			canvas.fillColor( 255, 255, 255, 32)
			canvas.beginPath()
			//隔行绘制
			int y = self.hoverRow * self.rowHeight
			canvas.rect( 0, y, w, self.rowHeight)
			canvas.fill()
		}
		if (self.hoverCol != -1){
			canvas.fillColor( 255, 255, 255, 32)
			canvas.beginPath()
			//隔行绘制
			int y = self.hoverRow * self.rowHeight
			canvas.rect( self.hoverStartX, 0, self.hoverEndX - self.hoverStartX, h)
			canvas.fill()
		}

		canvas.restore()
	}

	void onEvent(Event *e){
		if(e instanceof MouseEvent){
			self.onMouseEvent((MouseEvent*)e)
		}
	}
	void onMouseEvent(MouseEvent *e){
		if (e.isMouseMove){
			printf("mouse move TableView\n")
			Rect r = self.getContentClientRect()
			float dy = e.clientY - r.y
			float dx = e.clientX - r.x
			int row = floor(dy / self.rowHeight) //相对于头
			if (self.hoverRow != row && row >= 0 && row <= self.rowCount){
				self.hoverRow = row
				self.invalidDraw()
			}
			int col = -1
			int colX = 0
			int endX = 0
			int l = self.columns.size()
			for (int i = 0; i < l; i++){
				TableViewColumn* column = (TableViewColumn*)self.columns.get(i)
				endX = colX + column.width
				if (colX <= dx && dx < endX){
					col = i
					break
				}
				colX = endX
			}
			if (self.hoverCol != col && col >= 0 && col < self.columns.size()){
				self.hoverCol = col
				self.hoverStartX = colX
				self.hoverEndX = endX
				self.invalidDraw()
			}
		}
		if (e instanceof MouseLeaveEvent){
			self.hoverRow = -1
		}
	}
	int hoverRow = -1
	int hoverCol = -1
	int hoverStartX = 0
	int hoverEndX = 0
}

TableView@ mkTableView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (TableView@)gocNode(sp, (Node*)parent, TableView)
}
