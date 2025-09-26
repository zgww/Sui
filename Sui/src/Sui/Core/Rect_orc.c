
#include "Rect_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Vec2_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Rect_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Rect", sizeof( SuiCore$Rect ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(SuiCore$Rect, x), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "y", OrcMetaType_float, offsetof(SuiCore$Rect, y), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "w", OrcMetaType_float, offsetof(SuiCore$Rect, w), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "h", OrcMetaType_float, offsetof(SuiCore$Rect, h), 0, 0, 0, 0);//float
    }
	return meta;
}
void  SuiCore$Rect$setAll(SuiCore$Rect *  self, float  x, float  y, float  w, float  h){
	self->x = x;
	self->y = y;
	self->w = w;
	self->h = h;
}

bool  SuiCore$Rect$isEmpty(SuiCore$Rect *  self){
	return fabsf(self->w)  < 0.00001 && fabsf(self->h)  < 0.00001; 
}

void  SuiCore$Rect$set_ltrb(SuiCore$Rect *  self, float  left, float  top, float  right, float  bottom){
	if (left > right) {
		float  tmp = left;
		left = right;
		right = tmp;
	}
	if (top > bottom) {
		float  tmp = top;
		top = bottom;
		bottom = tmp;
	}
	self->x = left;
	self->y = top;
	self->w = right - left;
	self->h = bottom - top;
}

bool  SuiCore$Rect$containsPosition(SuiCore$Rect *  self, float  px, float  py){
	return self->x <= px && px <= self->x + self->w && self->y <= py && py <= self->y + self->h; 
}

SuiCore$Rect SuiCore$Rect$containsPositionIn5Patch(SuiCore$Rect *  self, float  px, float  py, SuiCore$Rect centerRect){
	SuiCore$Rect ret = SuiCore$Rect$containsPositionIn5Patch_withOutType(self, px, py, centerRect, NULL) ;
	return ret; 
}

SuiCore$Rect SuiCore$Rect$containsPositionIn5Patch_withOutType(SuiCore$Rect *  self, float  px, float  py, SuiCore$Rect centerRect, int *  outType){
	if (outType) {
		*outType = -1;
	}
	if (self->w == 0 || self->h == 0 || !SuiCore$Rect$containsPosition(self, px, py) ) {
		return SuiCore$mkRect(-1, -1, -1, -1) ; 
	}
	float  dx = px - self->x;
	float  dy = py - self->y;
	float  x = dx / self->w;
	float  y = dy / self->h;
	float  x1 = centerRect.x;
	float  x2 = centerRect.x + centerRect.w;
	float  y1 = centerRect.y;
	float  y2 = centerRect.y + centerRect.h;
	if (y < y1) {
		if (outType) {
			*outType = 0;
		}
		return SuiCore$mkRect(0, 0, 1, y1) ; 
	}
	else if (y < y2) {
		if (x < x1) {
			if (outType) {
				*outType = 1;
			}
			return SuiCore$mkRect(0, y1, x1, centerRect.h) ; 
		}
		else if (x < x2) {
			if (outType) {
				*outType = 2;
			}
			return SuiCore$mkRect(x1, y1, centerRect.w, centerRect.h) ; 
		}
		else {
			if (outType) {
				*outType = 3;
			}
			return SuiCore$mkRect(x2, y1, 1.0 - x2, centerRect.h) ; 
		}
	}
	else {
		if (outType) {
			*outType = 4;
		}
		return SuiCore$mkRect(0, y2, 1, 1.0 - y2) ; 
	}
}

SuiCore$Vec2 SuiCore$Rect$containsPositionIn9Patch(SuiCore$Rect *  self, float  px, float  py){
	if (!SuiCore$Rect$containsPosition(self, px, py) ) {
		return SuiCore$mkVec2(-1, -1) ; 
	}
	float  dx = px - self->x;
	float  dy = py - self->y;
	float  w0_3 = 1 / 3.0 * self->w;
	float  h0_3 = 1 / 3.0 * self->h;
	if (dx < w0_3) {
		if (dy < h0_3) {
			return SuiCore$mkVec2(0, 0) ; 
		}
		if (dy < h0_3 * 2) {
			return SuiCore$mkVec2(0, 1) ; 
		}
		if (dy < h0_3 * 3) {
			return SuiCore$mkVec2(0, 2) ; 
		}
	}
	if (dx < w0_3 * 2) {
		if (dy < h0_3) {
			return SuiCore$mkVec2(1, 0) ; 
		}
		if (dy < h0_3 * 2) {
			return SuiCore$mkVec2(1, 1) ; 
		}
		if (dy < h0_3 * 3) {
			return SuiCore$mkVec2(1, 2) ; 
		}
	}
	if (dy < h0_3) {
		return SuiCore$mkVec2(2, 0) ; 
	}
	if (dy < h0_3 * 2) {
		return SuiCore$mkVec2(2, 1) ; 
	}
	if (dy < h0_3 * 3) {
		return SuiCore$mkVec2(2, 2) ; 
	}
	return SuiCore$mkVec2(-1, -1) ; 
}

float  SuiCore$Rect$right(SuiCore$Rect *  self){
	return self->x + self->w; 
}

float  SuiCore$Rect$bottom(SuiCore$Rect *  self){
	return self->y + self->h; 
}

float  SuiCore$Rect$centerX(SuiCore$Rect *  self){
	return self->x + self->w / 2.f; 
}

float  SuiCore$Rect$centerY(SuiCore$Rect *  self){
	return self->y + self->h / 2.f; 
}

SuiCore$Vec2 SuiCore$Rect$centerPos(SuiCore$Rect *  self){
	SuiCore$Vec2 ret;
	ret.x = SuiCore$Rect$centerX(self) ;
	ret.y = SuiCore$Rect$centerY(self) ;
	return ret; 
}

SuiCore$Vec2 SuiCore$Rect$leftTop(SuiCore$Rect *  self){
	SuiCore$Vec2 ret;
	ret.x = self->x;
	ret.y = self->y;
	return ret; 
}

SuiCore$Vec2 SuiCore$Rect$leftBottom(SuiCore$Rect *  self){
	SuiCore$Vec2 ret;
	ret.x = self->x;
	ret.y = SuiCore$Rect$bottom(self) ;
	return ret; 
}

SuiCore$Vec2 SuiCore$Rect$rightTop(SuiCore$Rect *  self){
	SuiCore$Vec2 ret;
	ret.x = SuiCore$Rect$right(self) ;
	ret.y = self->y;
	return ret; 
}

SuiCore$Vec2 SuiCore$Rect$rightBottom(SuiCore$Rect *  self){
	SuiCore$Vec2 ret;
	ret.x = SuiCore$Rect$right(self) ;
	ret.y = SuiCore$Rect$bottom(self) ;
	return ret; 
}

void  SuiCore$Rect$offset(SuiCore$Rect *  self, float  x, float  y){
	self->x = self->x + x;
	self->y = self->y + y;
}

SuiCore$Rect SuiCore$Rect$inset(SuiCore$Rect *  self, float  dx, float  dy){
	SuiCore$Rect ret;
	ret.x = self->x + dx;
	ret.y = self->y + dy;
	ret.w = self->w - dx * 2.f;
	ret.h = self->h - dy * 2.f;
	return ret; 
}

void  SuiCore$Rect$normal(SuiCore$Rect *  self){
	SuiCore$Rect *  r = self;
	if (r->w < 0) {
		r->x = r->x + r->w;
		r->w = -r->w;
	}
	if (r->h < 0) {
		r->y = r->y + r->h;
		r->h = -r->h;
	}
}

bool  SuiCore$Rect$isIntersect(SuiCore$Rect *  self, SuiCore$Rect *  b){
	float  cx = fabsf(SuiCore$Rect$centerX(self)  - SuiCore$Rect$centerX(b) ) ;
	float  cy = fabsf(SuiCore$Rect$centerY(self)  - SuiCore$Rect$centerY(b) ) ;
	float  hw = (self->w + b->w) / 2.0f;
	float  hh = (self->h + b->h) / 2.0f;
	return cx <= hw && cy <= hh; 
}

bool  SuiCore$Rect$equals(SuiCore$Rect *  self, SuiCore$Rect *  b){
	return fabsf(self->x - b->x)  < 0.00001 && fabsf(self->y - b->y)  < 0.00001 && fabsf(self->w - b->w)  < 0.00001 && fabsf(self->h - b->h)  < 0.00001; 
}

float  SuiCore$cross(float  x1, float  y1, float  x2, float  y2, float  x, float  y){
	float  a0 = x2 - x1;
	float  a1 = y2 - y1;
	float  b0 = x - x1;
	float  b1 = y - y1;
	return a0 * b1 - a1 * b0; 
}

bool  SuiCore$isInRect(float  x1, float  y1, float  x2, float  y2, float  x3, float  y3, float  x4, float  y4, float  x, float  y){
	return SuiCore$cross(x1, y1, x2, y2, x, y)  * SuiCore$cross(x3, y3, x4, y4, x, y)  >= 0 && SuiCore$cross(x2, y2, x3, y3, x, y)  * SuiCore$cross(x4, y4, x1, y1, x, y)  >= 0; 
}

SuiCore$Rect SuiCore$mkRect0(){
	SuiCore$Rect r;
	r.x = 0;
	r.y = 0;
	r.w = 0;
	r.h = 0;
	return r; 
}

SuiCore$Rect SuiCore$mkRect(float  x, float  y, float  w, float  h){
	SuiCore$Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r; 
}

SuiCore$Rect SuiCore$mkRectByCenterWH(float  cx, float  cy, float  w, float  h){
	SuiCore$Rect r;
	r.x = cx - w / 2.0f;
	r.y = cy - h / 2.0f;
	r.w = w;
	r.h = h;
	return r; 
}

SuiCore$Rect SuiCore$mkRectByCenterRadius(float  cx, float  cy, float  rad){
	SuiCore$Rect r;
	r.x = cx - rad;
	r.y = cy - rad;
	r.w = rad * 2;
	r.h = rad * 2;
	return r; 
}

void  SuiCore$testRect(){
	SuiCore$Rect a = SuiCore$mkRectByCenterWH(100.f, 100.f, 200.f, 200.f) ;
	SuiCore$Rect b = SuiCore$mkRectByCenterRadius(100.f, 100.f, 200.f) ;
	printf("rect isEquals:%d\n", SuiCore$Rect$equals(&a, &b) ) ;
	printf("a.right :%f\n", SuiCore$Rect$right(&a) ) ;
}



