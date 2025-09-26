package SuiCore

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

import * from "./Vec2.orc"



/// 矩形
struct Rect {
	float x 
	float y 
	float w 
	float h 
}

	//void dtor(){
		//// printf("释放Rect:%f,%f,%f,%f\n", self.x, self.y, self.w, self.h)
	//}

extension Rect {
    void setAll(float x, float y, float w, float h){
		self.x = x
		self.y = y
		self.w = w
		self.h = h
	}
	bool isEmpty(){ 
		return fabsf(self.w) < 0.00001 
		&&  fabsf(self.h) < 0.00001
	}

	void set_ltrb(float left, float top, float right, float bottom){
	    if (left > right) {
		    float tmp = left
		    left = right
		    right = tmp
	    }
	    if (top > bottom) {
			float tmp = top
		    top = bottom
		    bottom = tmp
	    }
		self.x = left;
	    self.y = top;
	    self.w = right - left;
	    self.h = bottom - top;
    }

    bool containsPosition(float px, float py) {
       return self.x <= px && px <= self.x + self.w
		&& self.y <= py && py <= self.y + self.h;
    }
    Rect containsPositionIn5Patch(float px, float py, Rect centerRect) {
		Rect ret = self.containsPositionIn5Patch_withOutType(
			px, py, centerRect, null) 
		return ret
	}

	//是否包含位置在9宫格内
	// 0 0 0
	// 1 2 3
	// 4 4 4
	// -1 表示 不包含
	// [centerRect]表示中间区域，以比例的方式表示
	// [return] 返回以比例表示的rect
    Rect containsPositionIn5Patch_withOutType(float px, float py, Rect centerRect, int *outType) {
		if (outType){
			*outType = -1
		}

		if (self.w == 0 || self.h == 0 || !self.containsPosition(px, py)){
			return mkRect(-1, -1, -1, -1)
		}
		float dx = px - self.x
		float dy = py - self.y

		float x = dx / self.w
		float y = dy / self.h

		float x1 = centerRect.x
		float x2 = centerRect.x + centerRect.w
		float y1 = centerRect.y
		float y2 = centerRect.y + centerRect.h
		if (y < y1){
			if (outType){
				*outType = 0
			}
			return mkRect(0, 0, 1, y1)
		}
		else if (y < y2){
			if (x < x1){
				if (outType){
					*outType = 1
				}
				return mkRect(0, y1, x1, centerRect.h)
			}
			else if (x < x2){
				if (outType){
					*outType = 2
				}
				return mkRect(x1, y1, centerRect.w, centerRect.h)

			} else {
				if (outType){
					*outType = 3
				}
				return mkRect(x2, y1, 1.0 - x2, centerRect.h)
			}
		}
		else {
			if (outType){
				*outType = 4
			}
			return mkRect(0, y2, 1, 1.0 - y2)
		}
	}

	//是否包含位置在9宫格内
	// 0 1 2
	// 3 4 5
	// 6 7 8
	// -1 表示 不包含
    Vec2 containsPositionIn9Patch(float px, float py) {
		if (!self.containsPosition(px, py)){
			return mkVec2(-1, -1)
		}
		float dx = px - self.x
		float dy = py - self.y
		float w0_3 = 1 / 3.0 * self.w
		float h0_3 = 1 / 3.0 * self.h
		if (dx < w0_3){
			if (dy < h0_3){
				return mkVec2(0, 0)
			}
			if (dy < h0_3 * 2){
				// return 3
				return mkVec2(0, 1)
			}
			if (dy < h0_3 * 3){
				// return 6
				return mkVec2(0, 2)
			}
		}
		if (dx < w0_3 * 2){
			if (dy < h0_3){
				// return 1
				return mkVec2(1, 0)
			}
			if (dy < h0_3 * 2){
				// return 4
				return mkVec2(1, 1)
			}
			if (dy < h0_3 * 3){
				// return 7
				return mkVec2(1, 2)
			}
		}

		if (dy < h0_3){
			// return 2
			return mkVec2(2, 0)
		}
		if (dy < h0_3 * 2){
			// return 5
			return mkVec2(2, 1)
		}
		if (dy < h0_3 * 3){
			// return 8
			return mkVec2(2, 2)
		}
		// return -1
		return mkVec2(-1,-1)
    }

	float right(){
		return self.x + self.w
	}
	float bottom(){
		return self.y + self.h
	}
	float centerX(){
		return self.x + self.w / 2.f
	}
	float centerY(){
		return self.y + self.h / 2.f
	}
	Vec2 centerPos(){
		Vec2 ret
		ret.x = self.centerX()
		ret.y = self.centerY()
		return ret
	}
	Vec2 leftTop(){
		Vec2 ret
		ret.x = self.x
		ret.y = self.y
		return ret
	}
	Vec2 leftBottom(){
		Vec2 ret
		ret.x = self.x
		ret.y = self.bottom()
		return ret
	}
	Vec2 rightTop(){
		Vec2 ret
		ret.x = self.right()
		ret.y = self.y
		return ret
	}
	Vec2 rightBottom(){
		Vec2 ret
		ret.x = self.right()
		ret.y = self.bottom()
		return ret
	}
	void offset(float x, float y){
        self.x = self.x + x
		self.y = self.y + y
	}
	Rect inset(float dx, float dy){
		Rect ret
		ret.x = self.x + dx
		ret.y = self.y + dy
		ret.w = self.w - dx * 2.f
		ret.h = self.h - dy * 2.f
		return ret
	}
	//对w,h负值处理
	void normal(){	
		Rect *r = self;
	    if (r.w < 0) {
		    r.x = r.x + r.w;
		    r.w = -r.w;
	    }
	    if (r.h < 0) {
		    r.y = r.y+ r.h;
		    r.h = -r.h;
	    }
	}
	// 两个中心点间的距离肯定小等于AB边长和的一半
    bool isIntersect(Rect* b) {
	    float cx = fabsf(self.centerX() - b.centerX());
	    float cy = fabsf(self.centerY() - b.centerY());
	    float hw = (self.w + b.w) / 2.0f;
	    float hh = (self.h + b.h) / 2.0f;
	    return cx <= hw && cy <= hh;
    }
	
	// bool hasNan() { 
	// 	return isnan(self.x) || isnan(self.y); 
	// }
	bool equals(Rect *b){
		return fabsf(self.x - b.x) < 0.00001 
		&&  fabsf(self.y - b.y) < 0.00001
		&&  fabsf(self.w - b.w) < 0.00001
		&&  fabsf(self.h - b.h) < 0.00001
	}
}

///叉乘。 可以用于计算点在矩形内
float cross(float x1, float y1, float x2, float y2, float x, float y){
    float a0 = x2 - x1
	float a1 = y2 - y1
	float b0 = x - x1
	float b1 = y - y1

	return a0 * b1 - a1 * b0
}

bool isInRect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y) {
	return cross(x1, y1, x2, y2, x, y)
		* cross(x3, y3, x4, y4, x, y) >= 0
		&& cross(x2, y2, x3, y3, x, y)
		* cross(x4, y4, x1, y1, x, y) >= 0;
}
Rect mkRect0() {
	Rect r;
	r.x = 0;
	r.y = 0;
	r.w = 0;
	r.h = 0;
	return r
}
Rect mkRect(float x, float y, float w, float h) {
	Rect r
	r.x = x
	r.y = y
	r.w = w;
	r.h = h
	return r
}
Rect mkRectByCenterWH(float cx, float cy, float w, float h) {
	Rect r
	r.x = cx - w / 2.0f
	r.y = cy - h / 2.0f
	r.w = w;
	r.h = h
	return r
}

 Rect mkRectByCenterRadius(float cx, float cy, float rad) {
	Rect r
	r.x = cx - rad
	r.y = cy - rad
	r.w = rad * 2
	r.h = rad * 2
	return r
}


void testRect(){
	Rect a = mkRectByCenterWH(100.f, 100.f, 200.f, 200.f)
	Rect b = mkRectByCenterRadius(100.f, 100.f, 200.f)
	printf("rect isEquals:%d\n", a.equals(&b))
	printf("a.right :%f\n", a.right())
}