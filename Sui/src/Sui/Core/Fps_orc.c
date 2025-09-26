
#include "Fps_orc.h" 

#include <stdio.h>
#include "../../nanovg/nanovg.h"
#include "../../Orc/Time_orc.h"
#include "../Core/Canvas_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Fps_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Fps", sizeof( SuiCore$Fps ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "fps", OrcMetaType_float, offsetof(SuiCore$Fps, fps), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "layoutFps", OrcMetaType_float, offsetof(SuiCore$Fps, layoutFps), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "drawFps", OrcMetaType_float, offsetof(SuiCore$Fps, drawFps), 0, 0, 0, 0);//float
		orc_metaField_primitive(&pNext, "costMs", OrcMetaType_long_long, offsetof(SuiCore$Fps, costMs), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "layoutCostMs", OrcMetaType_long_long, offsetof(SuiCore$Fps, layoutCostMs), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "drawCostMs", OrcMetaType_long_long, offsetof(SuiCore$Fps, drawCostMs), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "startMs", OrcMetaType_long_long, offsetof(SuiCore$Fps, startMs), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "endMs", OrcMetaType_long_long, offsetof(SuiCore$Fps, endMs), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "layoutStartMs", OrcMetaType_long_long, offsetof(SuiCore$Fps, layoutStartMs), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "layoutEndMs", OrcMetaType_long_long, offsetof(SuiCore$Fps, layoutEndMs), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "drawStartMs", OrcMetaType_long_long, offsetof(SuiCore$Fps, drawStartMs), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "drawEndMs", OrcMetaType_long_long, offsetof(SuiCore$Fps, drawEndMs), 0, 0, 0, 0);//longlong
    }
	return meta;
}
void  SuiCore$Fps$startFrame(SuiCore$Fps *  self){
	self->startMs = Orc$Time_unixMs() ;
}

void  SuiCore$Fps$endFrame(SuiCore$Fps *  self){
	self->endMs = Orc$Time_unixMs() ;
	self->drawCostMs = self->drawEndMs - self->drawStartMs;
	self->layoutCostMs = self->layoutEndMs - self->layoutStartMs;
	self->costMs = self->endMs - self->startMs;
	self->fps = self->costMs > 0 ? 1000.f / self->costMs : 1000;
	self->layoutFps = self->layoutCostMs > 0 ? 1000.f / self->layoutCostMs : 1000;
	self->drawFps = self->drawCostMs > 0 ? 1000.f / self->drawCostMs : 1000;
}

void  SuiCore$Fps$startLayout(SuiCore$Fps *  self){
	self->layoutStartMs = Orc$Time_unixMs() ;
}

void  SuiCore$Fps$endLayout(SuiCore$Fps *  self){
	self->layoutEndMs = Orc$Time_unixMs() ;
}

void  SuiCore$Fps$startDraw(SuiCore$Fps *  self){
	self->drawStartMs = Orc$Time_unixMs() ;
}

void  SuiCore$Fps$endDraw(SuiCore$Fps *  self){
	self->drawEndMs = Orc$Time_unixMs() ;
}

void  SuiCore$Fps$draw(SuiCore$Fps *  self, SuiCore$Canvas *  canvas, int  h){
	SuiCore$Canvas$save(canvas) ;
	SuiCore$Canvas$translate(canvas, 0, h - 30) ;
	char  text[60];
	sprintf(text, "fps:%.1f/%.1f/%.1f", self->fps, self->layoutFps, self->drawFps) ;
	SuiCore$Canvas$fillColor(canvas, 0, 0, 0, 64) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 0, 0, 200, 30) ;
	SuiCore$Canvas$fill(canvas) ;
	SuiCore$Canvas$fillColor(canvas, 255, 255, 255, 255) ;
	SuiCore$Canvas$text(canvas, 6, 12, text) ;
	sprintf(text, "ms:%lld/%lld/%lld", self->costMs, self->layoutCostMs, self->drawCostMs) ;
	SuiCore$Canvas$text(canvas, 6, 26, text) ;
	SuiCore$Canvas$restore(canvas) ;
}



