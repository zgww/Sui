
#include "Frame_orc.h" 

#include <stdio.h>
#include "./Node_orc.h"
#include "./Inset_orc.h"
#include "./Vec2_orc.h"
#include "./Rect_orc.h"
#include "./LayoutCell_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/List_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Frame_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Frame", sizeof( SuiCore$Frame ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "timesInOneLayout", OrcMetaType_int, offsetof(SuiCore$Frame, timesInOneLayout), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "applyCacheTimes", OrcMetaType_int, offsetof(SuiCore$Frame, applyCacheTimes), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "minWidth", OrcMetaType_float, offsetof(SuiCore$Frame, minWidth), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "minHeight", OrcMetaType_float, offsetof(SuiCore$Frame, minHeight), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "maxWidth", OrcMetaType_float, offsetof(SuiCore$Frame, maxWidth), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "maxHeight", OrcMetaType_float, offsetof(SuiCore$Frame, maxHeight), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "prevMinWidth", OrcMetaType_float, offsetof(SuiCore$Frame, prevMinWidth), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "prevMinHeight", OrcMetaType_float, offsetof(SuiCore$Frame, prevMinHeight), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "prevMaxWidth", OrcMetaType_float, offsetof(SuiCore$Frame, prevMaxWidth), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "prevMaxHeight", OrcMetaType_float, offsetof(SuiCore$Frame, prevMaxHeight), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(SuiCore$Frame, x), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "y", OrcMetaType_float, offsetof(SuiCore$Frame, y), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "width", OrcMetaType_float, offsetof(SuiCore$Frame, width), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "height", OrcMetaType_float, offsetof(SuiCore$Frame, height), 0, 0, 0, 0);//float
    }
	return meta;
}
SuiCore$Frame SuiCore$mkFrame(){
	SuiCore$Frame f;
	f.minWidth = .0f;
	f.minHeight = 0.f;
	f.maxWidth = INFINITY;
	f.maxHeight = INFINITY;
	f.prevMinWidth = -1.f;
	f.prevMinHeight = -1.f;
	f.prevMaxWidth = -1.f;
	f.prevMaxHeight = -1.f;
	f.x = 0.f;
	f.y = 0.f;
	f.width = 0.f;
	f.height = 0.f;
	return f; 
}

SuiCore$Frame SuiCore$Frame$copy(SuiCore$Frame *  self){
	SuiCore$Frame ret;
	ret.minWidth = self->minWidth;
	ret.minHeight = self->minHeight;
	ret.maxWidth = self->maxWidth;
	ret.maxHeight = self->maxHeight;
	ret.x = self->x;
	ret.y = self->y;
	ret.width = self->width;
	ret.height = self->height;
	return ret; 
}

bool  SuiCore$Frame$isConstraintsNotChanged(SuiCore$Frame *  self){
	return self->prevMinWidth == self->minWidth && self->prevMinHeight == self->minHeight && self->prevMaxWidth == self->maxWidth && self->prevMaxHeight == self->maxHeight; 
}

bool  SuiCore$Frame$checkAndUseCacheResult(SuiCore$Frame *  self){
	if (SuiCore$Frame$isConstraintsNotChanged(self) ) {
		self->applyCacheTimes++;
		return true; 
	}
	return false; 
}

void  SuiCore$Frame$saveConstraints(SuiCore$Frame *  self){
	self->prevMinWidth = self->minWidth;
	self->prevMinHeight = self->minHeight;
	self->prevMaxWidth = self->maxWidth;
	self->prevMaxHeight = self->maxHeight;
}

void  SuiCore$Frame$incTimesInOneLayout(SuiCore$Frame *  self){
	self->timesInOneLayout++;
}

SuiCore$Frame SuiCore$Frame$inset(SuiCore$Frame *  self, SuiCore$Inset inset){
	SuiCore$Frame ret = SuiCore$Frame$copy(self) ;
	ret.minWidth = ret.minWidth - SuiCore$Inset$hor(&inset) ;
	ret.minHeight = ret.minHeight - SuiCore$Inset$ver(&inset) ;
	if (ret.maxWidth != INFINITY) {
		ret.maxWidth = Orc$maxFloat(ret.minWidth, ret.maxWidth - SuiCore$Inset$hor(&inset) ) ;
	}
	if (ret.maxHeight != INFINITY) {
		ret.maxHeight = Orc$maxFloat(ret.minHeight, ret.maxHeight - SuiCore$Inset$ver(&inset) ) ;
	}
	ret.x = ret.x + inset.left;
	ret.y = ret.y + inset.top;
	ret.width = Orc$maxFloat(0.0f, ret.width - SuiCore$Inset$hor(&inset) ) ;
	ret.height = Orc$maxFloat(0.0f, ret.height - SuiCore$Inset$ver(&inset) ) ;
	return ret; 
}

SuiCore$Frame SuiCore$Frame$outset(SuiCore$Frame *  self, SuiCore$Inset inset){
	SuiCore$Inset$invert(&inset) ;
	return SuiCore$Frame$inset(self, inset) ; 
}

SuiCore$Rect SuiCore$Frame$toRect(SuiCore$Frame *  self){
	SuiCore$Rect r = SuiCore$mkRect(self->x, self->y, self->width, self->height) ;
	return r; 
}

void  SuiCore$Frame$copyConstraints(SuiCore$Frame *  self, SuiCore$Frame *  ctx){
	SuiCore$Frame$copyWidthConstraint(self, ctx) ;
	SuiCore$Frame$copyHeightConstraint(self, ctx) ;
}

void  SuiCore$Frame$copyMaxConstraints(SuiCore$Frame *  self, SuiCore$Frame *  ctx){
	self->maxHeight = ctx->maxHeight;
	self->maxWidth = ctx->maxWidth;
}

void  SuiCore$Frame$copyMinConstraints(SuiCore$Frame *  self, SuiCore$Frame *  ctx){
	self->minHeight = ctx->minHeight;
	self->minWidth = ctx->minWidth;
}

void  SuiCore$Frame$setMinConstraints(SuiCore$Frame *  self, float  w, float  h){
	self->minWidth = w;
	self->minHeight = h;
}

void  SuiCore$Frame$setMaxConstraints(SuiCore$Frame *  self, float  w, float  h){
	self->maxWidth = w;
	self->maxHeight = h;
}

void  SuiCore$Frame$setMinWidth(SuiCore$Frame *  self, float  minV){
	self->minWidth = Orc$maxFloat(0.f, minV) ;
}

void  SuiCore$Frame$setMinHeight(SuiCore$Frame *  self, float  minV){
	self->minHeight = Orc$maxFloat(0.f, minV) ;
}

void  SuiCore$Frame$setWidthConstraint(SuiCore$Frame *  self, float  minv, float  maxv){
	self->minWidth = minv;
	self->maxWidth = maxv;
}

void  SuiCore$Frame$setHeightConstraint(SuiCore$Frame *  self, float  minv, float  maxv){
	self->minHeight = minv;
	self->maxHeight = maxv;
}

void  SuiCore$Frame$clampTightWidthConstraint(SuiCore$Frame *  self, float  v){
	v = Orc$clampFloat(v, self->minWidth, self->maxWidth) ;
	self->minWidth = Orc$maxFloat(self->minWidth, v) ;
	self->maxWidth = Orc$minFloat(self->maxWidth, v) ;
}

void  SuiCore$Frame$clampTightHeightConstraint(SuiCore$Frame *  self, float  v){
	v = Orc$clampFloat(v, self->minHeight, self->maxHeight) ;
	self->minHeight = Orc$maxFloat(self->minHeight, v) ;
	self->maxHeight = Orc$minFloat(self->maxHeight, v) ;
}

void  SuiCore$Frame$plusWidthConstraint(SuiCore$Frame *  self, float  minW, float  maxW){
	if (self->minWidth < minW) {
		self->minWidth = Orc$minFloat(minW, self->maxWidth) ;
	}
	if (maxW < self->maxWidth) {
		self->maxWidth = Orc$maxFloat(maxW, self->minWidth) ;
	}
	self->minWidth = Orc$minFloat(self->minWidth, self->maxWidth) ;
}

void  SuiCore$Frame$plusHeightConstraint(SuiCore$Frame *  self, float  minW, float  maxW){
	if (self->minHeight < minW) {
		self->minHeight = Orc$minFloat(minW, self->maxHeight) ;
	}
	if (maxW < self->maxHeight) {
		self->maxHeight = Orc$maxFloat(maxW, self->minHeight) ;
	}
	self->minHeight = Orc$minFloat(self->minHeight, self->maxHeight) ;
}

void  SuiCore$Frame$plusConstraints(SuiCore$Frame *  self, float  minW, float  maxW, float  minH, float  maxH){
	SuiCore$Frame$plusWidthConstraint(self, minW, maxW) ;
	SuiCore$Frame$plusHeightConstraint(self, minH, maxH) ;
}

void  SuiCore$Frame$clampWidth(SuiCore$Frame *  self, float  v, float  minW, float  maxW){
	self->width = Orc$clampFloat(v, Orc$maxFloat(minW, self->minWidth) , Orc$minFloat(maxW, self->maxWidth) ) ;
}

void  SuiCore$Frame$clampHeight(SuiCore$Frame *  self, float  v, float  minW, float  maxW){
	self->height = Orc$clampFloat(v, Orc$maxFloat(minW, self->minHeight) , Orc$minFloat(maxW, self->maxHeight) ) ;
}

void  SuiCore$Frame$setSize(SuiCore$Frame *  self, float  w, float  h){
	self->width = Orc$clampFloat(w, self->minWidth, self->maxWidth) ;
	self->height = Orc$clampFloat(h, self->minHeight, self->maxHeight) ;
}

SuiCore$Vec2 SuiCore$Frame$getSize(SuiCore$Frame *  self){
	return SuiCore$mkVec2(self->width, self->height) ; 
}

void  SuiCore$Frame$setWidth(SuiCore$Frame *  self, float  w){
	self->width = Orc$clampFloat(w, self->minWidth, self->maxWidth) ;
}

void  SuiCore$Frame$setHeight(SuiCore$Frame *  self, float  h){
	self->height = Orc$clampFloat(h, self->minHeight, self->maxHeight) ;
}

void  SuiCore$Frame$setRect(SuiCore$Frame *  self, float  x, float  y, float  w, float  h){
	self->x = x;
	self->y = y;
	SuiCore$Frame$setSize(self, w, h) ;
}

void  SuiCore$Frame$setPosition(SuiCore$Frame *  self, float  x, float  y){
	self->x = x;
	self->y = y;
}

float  SuiCore$Frame$getBottom(SuiCore$Frame *  self){
	return self->y + self->height; 
}

float  SuiCore$Frame$getRight(SuiCore$Frame *  self){
	return self->x + self->width; 
}

bool  SuiCore$Frame$setSize_ifAnyTight(SuiCore$Frame *  self){
	bool  ret = false;
	if (SuiCore$Frame$isTightWidth(self) ) {
		self->width = self->minWidth;
		ret = true;
	}
	if (SuiCore$Frame$isTightHeight(self) ) {
		self->height = self->minHeight;
		ret = true;
	}
	return ret; 
}

bool  SuiCore$Frame$setSize_ifTight(SuiCore$Frame *  self){
	if (SuiCore$Frame$isTight(self) ) {
		self->width = self->minWidth;
		self->height = self->minHeight;
		return true; 
	}
	return false; 
}

void  SuiCore$Frame$copyWidthConstraint(SuiCore$Frame *  self, SuiCore$Frame *  ctx){
	self->minWidth = ctx->minWidth;
	self->maxWidth = ctx->maxWidth;
}

void  SuiCore$Frame$copyHeightConstraint(SuiCore$Frame *  self, SuiCore$Frame *  ctx){
	self->minHeight = ctx->minHeight;
	self->maxHeight = ctx->maxHeight;
}

void  SuiCore$Frame$setTightWidth(SuiCore$Frame *  self, float  w){
	self->width = self->minWidth = self->maxWidth = w;
}

void  SuiCore$Frame$setTightHeight(SuiCore$Frame *  self, float  h){
	self->height = self->minHeight = self->maxHeight = h;
}

void  SuiCore$Frame$setTight(SuiCore$Frame *  self, float  w, float  h){
	self->width = self->minWidth = self->maxWidth = w;
	self->height = self->minHeight = self->maxHeight = h;
}

bool  SuiCore$Frame$isTightWidth(SuiCore$Frame *  self){
	return self->minWidth == self->maxWidth; 
}

bool  SuiCore$Frame$isTightHeight(SuiCore$Frame *  self){
	return self->minHeight == self->maxHeight; 
}

bool  SuiCore$Frame$isTight(SuiCore$Frame *  self){
	return self->minWidth == self->maxWidth && self->minHeight == self->maxHeight; 
}

bool  SuiCore$Frame$isLoose(SuiCore$Frame *  self){
	return !SuiCore$Frame$isTight(self) ; 
}

void  SuiCore$Frame$reset(SuiCore$Frame *  self){
	*self = SuiCore$mkFrame() ;
}

bool  SuiCore$Frame$isSizeSatisfy_otherFrameConstraints(SuiCore$Frame *  self, SuiCore$Frame *  ctx){
	if (self->width < ctx->minWidth || self->width > ctx->maxWidth) {
		return false; 
	}
	if (self->height < ctx->minHeight || self->height > ctx->maxHeight) {
		return false; 
	}
	return true; 
}



