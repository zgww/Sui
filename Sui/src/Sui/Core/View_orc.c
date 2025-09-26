
#include "View_orc.h" 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "./Node_orc.h"
#include "./Rect_orc.h"
#include "./Frame_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Math_orc.h"
#include "./Vec2_orc.h"
#include "./Inset_orc.h"
#include "./ViewBase_orc.h"
#include "./Window_orc.h"
#include "./BoxShadow_orc.h"
#include "./Border_orc.h"
#include "./Edge_orc.h"
#include "./Radius_orc.h"
#include "./Color_orc.h"
#include "./Rect_orc.h"
#include "./Canvas_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$ViewCallback _vtable_SuiCore$ViewCallback;

// init meta

void SuiCore$ViewCallback_initMeta(Vtable_SuiCore$ViewCallback *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "cbLayout", offsetof(SuiCore$ViewCallback, cbLayout));
	orc_metaField_method(&pNext, "cbDraw", offsetof(SuiCore$ViewCallback, cbDraw));
	orc_metaField_method(&pNext, "cbDrawSelf", offsetof(SuiCore$ViewCallback, cbDrawSelf));
	orc_metaField_method(&pNext, "afterDrawSelf", offsetof(SuiCore$ViewCallback, afterDrawSelf));
}


// vtable init


Vtable_SuiCore$ViewCallback* Vtable_SuiCore$ViewCallback_init(Vtable_SuiCore$ViewCallback* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$ViewCallback;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$ViewCallback_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$ViewCallback";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$ViewCallback_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$ViewCallback_fini(SuiCore$ViewCallback *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiCore$ViewCallback_init_fields(SuiCore$ViewCallback *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$ViewCallback_fini;
	//fields
    {
	
    }
	((SuiCore$ViewCallback*)self)->cbLayout = (void*)SuiCore$ViewCallback$cbLayout;
	((SuiCore$ViewCallback*)self)->cbDraw = (void*)SuiCore$ViewCallback$cbDraw;
	((SuiCore$ViewCallback*)self)->cbDrawSelf = (void*)SuiCore$ViewCallback$cbDrawSelf;
	((SuiCore$ViewCallback*)self)->afterDrawSelf = (void*)SuiCore$ViewCallback$afterDrawSelf;
}

// init function

void SuiCore$ViewCallback_init(SuiCore$ViewCallback *self, void *pOwner){
    Vtable_SuiCore$ViewCallback_init(&_vtable_SuiCore$ViewCallback);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$ViewCallback;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$ViewCallback_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$ViewCallback * SuiCore$ViewCallback_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$ViewCallback *self = calloc(1, sizeof(SuiCore$ViewCallback));
	
    SuiCore$ViewCallback_init(self, pOwner);
    return self;
}


// class members
bool  SuiCore$ViewCallback$cbLayout(SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Frame *  ctx){
	return false; 
}


bool  SuiCore$ViewCallback$cbDraw(SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas){
	return false; 
}


bool  SuiCore$ViewCallback$cbDrawSelf(SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas){
	return false; 
}


void  SuiCore$ViewCallback$afterDrawSelf(SuiCore$ViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas){
	
}




//vtable instance
Vtable_SuiCore$View _vtable_SuiCore$View;

// init meta

void SuiCore$View_initMeta(Vtable_SuiCore$View *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "size", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiCore$View, size), false, false, 0);
	orc_metaField_primitive(&pNext, "needClip", OrcMetaType_bool, offsetof(SuiCore$View, needClip), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "width", OrcMetaType_float, offsetof(SuiCore$View, width), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "height", OrcMetaType_float, offsetof(SuiCore$View, height), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "desiredWidth", OrcMetaType_float, offsetof(SuiCore$View, desiredWidth), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "desiredHeight", OrcMetaType_float, offsetof(SuiCore$View, desiredHeight), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "minWidth", OrcMetaType_float, offsetof(SuiCore$View, minWidth), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "maxWidth", OrcMetaType_float, offsetof(SuiCore$View, maxWidth), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "minHeight", OrcMetaType_float, offsetof(SuiCore$View, minHeight), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "maxHeight", OrcMetaType_float, offsetof(SuiCore$View, maxHeight), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "border", ((Vtable_Object*)Vtable_SuiCore$Border_init(0)), offsetof(SuiCore$View, border), true, false, 1);
	orc_metaField_class(&pNext, "radius", ((Vtable_Object*)Vtable_SuiCore$Radius_init(0)), offsetof(SuiCore$View, radius), true, false, 1);
	orc_metaField_struct(&pNext, "padding", SuiCore$Inset_getOrInitMetaStruct(), offsetof(SuiCore$View, padding), false, false, 0);
	orc_metaField_struct(&pNext, "margin", SuiCore$Inset_getOrInitMetaStruct(), offsetof(SuiCore$View, margin), false, false, 0);
	orc_metaField_class(&pNext, "boxShadow", ((Vtable_Object*)Vtable_SuiCore$BoxShadow_init(0)), offsetof(SuiCore$View, boxShadow), true, false, 1);
	orc_metaField_primitive(&pNext, "backgroundColor", OrcMetaType_int, offsetof(SuiCore$View, backgroundColor), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "cb", ((Vtable_Object*)Vtable_SuiCore$ViewCallback_init(0)), offsetof(SuiCore$View, cb), true, false, 1);

	orc_metaField_method(&pNext, "getViewRect_baseClient", offsetof(SuiCore$View, getViewRect_baseClient));
	orc_metaField_method(&pNext, "getFrameRect", offsetof(SuiCore$View, getFrameRect));
	orc_metaField_method(&pNext, "getViewRect", offsetof(SuiCore$View, getViewRect));
	orc_metaField_method(&pNext, "getContentRect", offsetof(SuiCore$View, getContentRect));
	orc_metaField_method(&pNext, "getNonContentSize", offsetof(SuiCore$View, getNonContentSize));
	orc_metaField_method(&pNext, "getInsetOfFrameToContent", offsetof(SuiCore$View, getInsetOfFrameToContent));
	orc_metaField_method(&pNext, "getSizeWithoutMargin", offsetof(SuiCore$View, getSizeWithoutMargin));
	orc_metaField_method(&pNext, "getOutWidth", offsetof(SuiCore$View, getOutWidth));
	orc_metaField_method(&pNext, "getOutHeight", offsetof(SuiCore$View, getOutHeight));
	orc_metaField_method(&pNext, "getOutMinWidth", offsetof(SuiCore$View, getOutMinWidth));
	orc_metaField_method(&pNext, "getOutMinHeight", offsetof(SuiCore$View, getOutMinHeight));
	orc_metaField_method(&pNext, "getOutMaxWidth", offsetof(SuiCore$View, getOutMaxWidth));
	orc_metaField_method(&pNext, "getOutMaxHeight", offsetof(SuiCore$View, getOutMaxHeight));
	orc_metaField_method(&pNext, "updateFrame_forSelfWidthHeight", offsetof(SuiCore$View, updateFrame_forSelfWidthHeight));
	orc_metaField_method(&pNext, "getContentLocalRect", offsetof(SuiCore$View, getContentLocalRect));
	orc_metaField_method(&pNext, "getContentRect_baseViewRect", offsetof(SuiCore$View, getContentRect_baseViewRect));
	orc_metaField_method(&pNext, "getViewSize", offsetof(SuiCore$View, getViewSize));
	orc_metaField_method(&pNext, "layoutContent_fromOutBox", offsetof(SuiCore$View, layoutContent_fromOutBox));
	orc_metaField_method(&pNext, "initLayoutSize", offsetof(SuiCore$View, initLayoutSize));
	orc_metaField_method(&pNext, "callCbLayout", offsetof(SuiCore$View, callCbLayout));
	orc_metaField_method(&pNext, "updateFrame_byContentCtx", offsetof(SuiCore$View, updateFrame_byContentCtx));
	orc_metaField_method(&pNext, "makeContentLayoutCtx", offsetof(SuiCore$View, makeContentLayoutCtx));
	orc_metaField_method(&pNext, "getContentClientRect", offsetof(SuiCore$View, getContentClientRect));
	orc_metaField_method(&pNext, "clip", offsetof(SuiCore$View, clip));
	orc_metaField_method(&pNext, "drawSelfBorder", offsetof(SuiCore$View, drawSelfBorder));
}


// vtable init


Vtable_SuiCore$View* Vtable_SuiCore$View_init(Vtable_SuiCore$View* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$View;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$ViewBase_init(&_vtable_SuiCore$ViewBase);

	// init by super vtable init function
    Vtable_SuiCore$ViewBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$ViewBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$View_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$View";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$View_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$View_fini(SuiCore$View *self){
	//super fini
    SuiCore$ViewBase_fini((SuiCore$ViewBase *)self);

    //字段释放


}

// init fields function


void SuiCore$View_init_fields(SuiCore$View *self){
	//super class
    SuiCore$ViewBase_init_fields((SuiCore$ViewBase*)self);

    ((Object*)self)->fini = (void*)SuiCore$View_fini;
	//fields
    {
	((SuiCore$View*)self)->size = SuiCore$mkVec2(0, 0) ;
	((SuiCore$View*)self)->needClip = false;
	((SuiCore$View*)self)->width = NAN;
	((SuiCore$View*)self)->height = NAN;
	((SuiCore$View*)self)->desiredWidth = NAN;
	((SuiCore$View*)self)->desiredHeight = NAN;
	((SuiCore$View*)self)->minWidth = 0.f;
	((SuiCore$View*)self)->maxWidth = INFINITY;
	((SuiCore$View*)self)->minHeight = 0.f;
	((SuiCore$View*)self)->maxHeight = INFINITY;
	URGC_VAR_CLEANUP_CLASS SuiCore$Border*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$View*)self)->border, SuiCore$Border_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS SuiCore$Radius*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$View*)self)->radius, SuiCore$Radius_new(&tmpNewOwner_2) );
	((SuiCore$View*)self)->padding = SuiCore$mkInset0() ;
	((SuiCore$View*)self)->margin = SuiCore$mkInset0() ;
	URGC_VAR_CLEANUP_CLASS SuiCore$BoxShadow*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$View*)self)->boxShadow, SuiCore$BoxShadow_new(&tmpNewOwner_3) );
	((SuiCore$View*)self)->backgroundColor = 0x00000000;
	urgc_set_field_class(self, (void**)&((SuiCore$View*)self)->cb, NULL);
    }
	((SuiCore$View*)self)->getViewRect_baseClient = (void*)SuiCore$View$getViewRect_baseClient;
	((SuiCore$ViewBase*)self)->_hitTestSelf = (void*)SuiCore$View$_hitTestSelf;
	((SuiCore$View*)self)->getFrameRect = (void*)SuiCore$View$getFrameRect;
	((SuiCore$View*)self)->getViewRect = (void*)SuiCore$View$getViewRect;
	((SuiCore$View*)self)->getContentRect = (void*)SuiCore$View$getContentRect;
	((SuiCore$View*)self)->getNonContentSize = (void*)SuiCore$View$getNonContentSize;
	((SuiCore$View*)self)->getInsetOfFrameToContent = (void*)SuiCore$View$getInsetOfFrameToContent;
	((SuiCore$View*)self)->getSizeWithoutMargin = (void*)SuiCore$View$getSizeWithoutMargin;
	((SuiCore$View*)self)->getOutWidth = (void*)SuiCore$View$getOutWidth;
	((SuiCore$View*)self)->getOutHeight = (void*)SuiCore$View$getOutHeight;
	((SuiCore$View*)self)->getOutMinWidth = (void*)SuiCore$View$getOutMinWidth;
	((SuiCore$View*)self)->getOutMinHeight = (void*)SuiCore$View$getOutMinHeight;
	((SuiCore$View*)self)->getOutMaxWidth = (void*)SuiCore$View$getOutMaxWidth;
	((SuiCore$View*)self)->getOutMaxHeight = (void*)SuiCore$View$getOutMaxHeight;
	((SuiCore$View*)self)->updateFrame_forSelfWidthHeight = (void*)SuiCore$View$updateFrame_forSelfWidthHeight;
	((SuiCore$View*)self)->getContentLocalRect = (void*)SuiCore$View$getContentLocalRect;
	((SuiCore$View*)self)->getContentRect_baseViewRect = (void*)SuiCore$View$getContentRect_baseViewRect;
	((SuiCore$View*)self)->getViewSize = (void*)SuiCore$View$getViewSize;
	((SuiCore$View*)self)->layoutContent_fromOutBox = (void*)SuiCore$View$layoutContent_fromOutBox;
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiCore$View$layoutContent;
	((SuiCore$View*)self)->initLayoutSize = (void*)SuiCore$View$initLayoutSize;
	((SuiCore$View*)self)->callCbLayout = (void*)SuiCore$View$callCbLayout;
	((SuiCore$ViewBase*)self)->layout = (void*)SuiCore$View$layout;
	((SuiCore$View*)self)->updateFrame_byContentCtx = (void*)SuiCore$View$updateFrame_byContentCtx;
	((SuiCore$View*)self)->makeContentLayoutCtx = (void*)SuiCore$View$makeContentLayoutCtx;
	((SuiCore$ViewBase*)self)->get_abs_rect = (void*)SuiCore$View$get_abs_rect;
	((SuiCore$View*)self)->getContentClientRect = (void*)SuiCore$View$getContentClientRect;
	((SuiCore$View*)self)->clip = (void*)SuiCore$View$clip;
	((SuiCore$ViewBase*)self)->draw = (void*)SuiCore$View$draw;
	((SuiCore$View*)self)->drawSelfBorder = (void*)SuiCore$View$drawSelfBorder;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiCore$View$draw_self;
}

// init function

void SuiCore$View_init(SuiCore$View *self, void *pOwner){
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$View;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$View_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$View * SuiCore$View_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$View *self = calloc(1, sizeof(SuiCore$View));
	
    SuiCore$View_init(self, pOwner);
    return self;
}


// class members
SuiCore$Rect SuiCore$View$getViewRect_baseClient(SuiCore$View *  self){
	SuiCore$Rect vr = self->getViewRect(self) ;
	SuiCore$Vec2 pos = ((SuiCore$ViewBase * )self)->localToWorld(self, vr.x, vr.y) ;
	SuiCore$Vec2 sizePos = ((SuiCore$ViewBase * )self)->localToWorld(self, vr.x + vr.w, vr.y + vr.h) ;
	SuiCore$Vec2 size = SuiCore$Vec2$sub(&sizePos, pos) ;
	return SuiCore$mkRect(pos.x, pos.y, size.x, size.y) ; 
}


bool  SuiCore$View$_hitTestSelf(SuiCore$View *  self, float  x, float  y){
	SuiCore$Rect r = self->getViewRect_baseClient(self) ;
	return ((SuiCore$ViewBase * )self)->_hitTestClientRect(self, &r, x, y) ; 
}


SuiCore$Rect SuiCore$View$getFrameRect(SuiCore$View *  self){
	SuiCore$Rect r = SuiCore$mkRect(((SuiCore$ViewBase * )self)->frame.x, ((SuiCore$ViewBase * )self)->frame.y, ((SuiCore$ViewBase * )self)->frame.width, ((SuiCore$ViewBase * )self)->frame.height) ;
	return r; 
}


SuiCore$Rect SuiCore$View$getViewRect(SuiCore$View *  self){
	float  w = ((SuiCore$ViewBase * )self)->frame.width - SuiCore$Inset$hor(&self->margin) ;
	float  h = ((SuiCore$ViewBase * )self)->frame.height - SuiCore$Inset$ver(&self->margin) ;
	return SuiCore$mkRect((float )self->margin.left, (float )self->margin.top, w, h) ; 
}


SuiCore$Rect SuiCore$View$getContentRect(SuiCore$View *  self){
	return SuiCore$mkRect(self->margin.left + self->border->l->w + self->padding.left, self->margin.top + self->border->t->w + self->padding.top, Orc$maxFloat(0.f, ((SuiCore$ViewBase * )self)->frame.width - SuiCore$Inset$hor(&self->margin)  - self->border->hor(self->border)  - SuiCore$Inset$hor(&self->padding) ) , Orc$maxFloat(0.f, ((SuiCore$ViewBase * )self)->frame.height - SuiCore$Inset$ver(&self->margin)  - self->border->ver(self->border)  - SuiCore$Inset$ver(&self->padding) ) ) ; 
}


SuiCore$Vec2 SuiCore$View$getNonContentSize(SuiCore$View *  self){
	float  w = SuiCore$Inset$hor(&self->margin)  + self->border->l->w + self->border->r->w + SuiCore$Inset$hor(&self->padding) ;
	float  h = SuiCore$Inset$ver(&self->margin)  + self->border->l->w + self->border->r->w + SuiCore$Inset$ver(&self->padding) ;
	return SuiCore$mkVec2(w, h) ; 
}


SuiCore$Inset SuiCore$View$getInsetOfFrameToContent(SuiCore$View *  self){
	float  l = self->margin.left + self->border->l->w + self->padding.left;
	float  t = self->margin.top + self->border->t->w + self->padding.top;
	float  r = self->margin.right + self->border->r->w + self->padding.right;
	float  b = self->margin.bottom + self->border->b->w + self->padding.bottom;
	return SuiCore$mkInset(t, r, b, l) ; 
}


SuiCore$Vec2 SuiCore$View$getSizeWithoutMargin(SuiCore$View *  self){
	float  w = ((SuiCore$ViewBase * )self)->frame.width;
	float  h = ((SuiCore$ViewBase * )self)->frame.height;
	return SuiCore$mkVec2(w - SuiCore$Inset$hor(&self->margin) , h - SuiCore$Inset$ver(&self->margin) ) ; 
}


float  SuiCore$View$getOutWidth(SuiCore$View *  self){
	if (Orc$isNaN(self->width) ) {
		return NAN; 
	}
	return self->width + SuiCore$Inset$hor(&self->margin) ; 
}


float  SuiCore$View$getOutHeight(SuiCore$View *  self){
	if (Orc$isNaN(self->height) ) {
		return NAN; 
	}
	return self->height + SuiCore$Inset$ver(&self->margin) ; 
}


float  SuiCore$View$getOutMinWidth(SuiCore$View *  self){
	if (Orc$isNaN(self->minWidth) ) {
		return NAN; 
	}
	return self->minWidth + SuiCore$Inset$hor(&self->margin) ; 
}


float  SuiCore$View$getOutMinHeight(SuiCore$View *  self){
	if (Orc$isNaN(self->minHeight) ) {
		return NAN; 
	}
	return self->minHeight + SuiCore$Inset$ver(&self->margin) ; 
}


float  SuiCore$View$getOutMaxWidth(SuiCore$View *  self){
	if (Orc$isNaN(self->maxWidth) ) {
		return NAN; 
	}
	return self->maxWidth + SuiCore$Inset$hor(&self->margin) ; 
}


float  SuiCore$View$getOutMaxHeight(SuiCore$View *  self){
	if (Orc$isNaN(self->maxHeight) ) {
		return NAN; 
	}
	return self->maxHeight + SuiCore$Inset$ver(&self->margin) ; 
}


void  SuiCore$View$updateFrame_forSelfWidthHeight(SuiCore$View *  self, SuiCore$Frame *  ctx){
	float  w = self->getOutWidth(self) ;
	float  h = self->getOutHeight(self) ;
	if (!Orc$isNaN(w) ) {
		SuiCore$Frame$clampTightWidthConstraint(ctx, w) ;
	}
	if (!Orc$isNaN(h) ) {
		SuiCore$Frame$clampTightHeightConstraint(ctx, h) ;
	}
	SuiCore$Frame$plusConstraints(ctx, self->getOutMinWidth(self) , self->getOutMaxWidth(self) , self->getOutMinHeight(self) , self->getOutMaxHeight(self) ) ;
}


SuiCore$Rect SuiCore$View$getContentLocalRect(SuiCore$View *  self){
	return SuiCore$mkRect(self->margin.left + self->border->l->w + self->padding.left, self->margin.top + self->border->t->w + self->padding.top, Orc$maxFloat(0.f, ((SuiCore$ViewBase * )self)->frame.width - SuiCore$Inset$hor(&self->margin)  - self->border->hor(self->border)  - SuiCore$Inset$hor(&self->padding) ) , Orc$maxFloat(0.f, ((SuiCore$ViewBase * )self)->frame.height - SuiCore$Inset$ver(&self->margin)  - self->border->ver(self->border)  - SuiCore$Inset$ver(&self->padding) ) ) ; 
}


SuiCore$Rect SuiCore$View$getContentRect_baseViewRect(SuiCore$View *  self){
	return SuiCore$mkRect(self->border->l->w + self->padding.left, self->border->t->w + self->padding.top, ((SuiCore$ViewBase * )self)->frame.width - SuiCore$Inset$hor(&self->margin)  - self->border->hor(self->border)  - SuiCore$Inset$hor(&self->padding) , ((SuiCore$ViewBase * )self)->frame.height - SuiCore$Inset$ver(&self->margin)  - self->border->ver(self->border)  - SuiCore$Inset$ver(&self->padding) ) ; 
}


SuiCore$Vec2 SuiCore$View$getViewSize(SuiCore$View *  self){
	float  w = ((SuiCore$ViewBase * )self)->frame.width - SuiCore$Inset$hor(&self->margin) ;
	float  h = ((SuiCore$ViewBase * )self)->frame.height - SuiCore$Inset$ver(&self->margin) ;
	return SuiCore$mkVec2(w, h) ; 
}


void  SuiCore$View$layoutContent_fromOutBox(SuiCore$View *  self, SuiCore$Frame *  ctx){
	SuiCore$Inset inset = self->getInsetOfFrameToContent(self) ;
	SuiCore$Frame contentCtx = SuiCore$Frame$inset(ctx, inset) ;
	((SuiCore$ViewBase * )self)->layoutContent(self, &contentCtx) ;
	*ctx = SuiCore$Frame$outset(&contentCtx, inset) ;
}


void  SuiCore$View$layoutContent(SuiCore$View *  self, SuiCore$Frame *  contentCtx){
	float  right = 0.f;
	float  bottom = 0.f;
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  v = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (v) {
			v->frame.minWidth = 0;
			v->frame.minHeight = 0;
			v->frame.maxWidth = INFINITY;
			v->frame.maxHeight = INFINITY;
			v->layout(v, &v->frame) ;
			right = Orc$maxFloat(SuiCore$Frame$getRight(&v->frame) , right) ;
			bottom = Orc$maxFloat(SuiCore$Frame$getBottom(&v->frame) , bottom) ;
		}
	}
	SuiCore$Frame$setSize(contentCtx, right, bottom) ;
}


void  SuiCore$View$initLayoutSize(SuiCore$View *  self, SuiCore$Frame *  ctx){
	ctx->width = ctx->minWidth;
	ctx->height = ctx->minHeight;
	SuiCore$Frame$setSize_ifAnyTight(ctx) ;
}


bool  SuiCore$View$callCbLayout(SuiCore$View *  self, SuiCore$Frame *  ctx){
	if (self->cb && self->cb->cbLayout(self->cb, self, ctx) ) {
		return true; 
	}
	return false; 
}


void  SuiCore$View$layout(SuiCore$View *  self, SuiCore$Frame *  ctx){
	self->updateFrame_forSelfWidthHeight(self, ctx) ;
	self->initLayoutSize(self, ctx) ;
	if (self->cb && self->cb->cbLayout(self->cb, self, ctx) ) {
		return ; 
	}
	self->layoutContent_fromOutBox(self, ctx) ;
	SuiCore$Frame$saveConstraints(ctx) ;
}


void  SuiCore$View$updateFrame_byContentCtx(SuiCore$View *  self, SuiCore$Frame *  targetCtx, SuiCore$Frame *  contentCtx){
	if (SuiCore$Frame$isTight(targetCtx) ) {
		return ; 
	}
	SuiCore$Vec2 ncSize = self->getNonContentSize(self) ;
	SuiCore$Frame$setSize(targetCtx, contentCtx->width + ncSize.x, contentCtx->height + ncSize.y) ;
}


SuiCore$Frame SuiCore$View$makeContentLayoutCtx(SuiCore$View *  self, SuiCore$Frame *  ctx){
	SuiCore$Frame ret = SuiCore$mkFrame() ;
	SuiCore$Vec2 ncSize = self->getNonContentSize(self) ;
	SuiCore$Frame$setMinWidth(&ret, ctx->minWidth - ncSize.x) ;
	if (ctx->maxWidth != INFINITY) {
		ret.maxWidth = ctx->maxWidth - ncSize.x;
	}
	SuiCore$Frame$setMinHeight(&ret, ctx->minHeight - ncSize.y) ;
	if (ctx->maxHeight != INFINITY) {
		ret.maxHeight = ctx->maxHeight - ncSize.y;
	}
	SuiCore$Frame$setSize_ifAnyTight(&ret) ;
	return ret; 
}


SuiCore$Rect SuiCore$View$get_abs_rect(SuiCore$View *  self){
	SuiCore$Vec2 pos = ((SuiCore$ViewBase * )self)->localToWorld(self, 0.f, 0.f) ;
	SuiCore$Vec2 viewSize = self->getViewSize(self) ;
	SuiCore$Vec2 sizePos = ((SuiCore$ViewBase * )self)->localToWorld(self, viewSize.x, viewSize.y) ;
	SuiCore$Vec2 size = SuiCore$Vec2$sub(&sizePos, pos) ;
	return SuiCore$mkRect(pos.x, pos.y, size.x, size.y) ; 
}


SuiCore$Rect SuiCore$View$getContentClientRect(SuiCore$View *  self){
	SuiCore$Rect lr = self->getContentLocalRect(self) ;
	SuiCore$Vec2 pos = ((SuiCore$ViewBase * )self)->localToWorld(self, lr.x, lr.y) ;
	lr.x = pos.x;
	lr.y = pos.y;
	return lr; 
}


void  SuiCore$View$clip(SuiCore$View *  self, SuiCore$Canvas *  canvas){
	float  x = self->margin.left;
	float  y = self->margin.top;
	float  w = ((SuiCore$ViewBase * )self)->frame.width - SuiCore$Inset$hor(&self->margin) ;
	float  h = ((SuiCore$ViewBase * )self)->frame.height - SuiCore$Inset$ver(&self->margin) ;
	SuiCore$Canvas$intersectScissor(canvas, 0.f, 0.f, w, h) ;
}


void  SuiCore$View$draw(SuiCore$View *  self, SuiCore$Canvas *  canvas){
	if (self->cb && self->cb->cbDraw(self->cb, self, canvas) ) {
		return ; 
	}
	SuiCore$Canvas$save(canvas) ;
	float  l = ((SuiCore$ViewBase * )self)->frame.x;
	float  t = ((SuiCore$ViewBase * )self)->frame.y;
	SuiCore$Canvas$translate(canvas, l, t) ;
	SuiCore$Canvas$transform(canvas, ((SuiCore$ViewBase * )self)->transform) ;
	SuiCore$Canvas$currentTransform(canvas, &((SuiCore$ViewBase * )self)->_world_transform) ;
	SuiCore$Canvas$translate(canvas, self->margin.left, self->margin.top) ;
	bool  need_draw = true;
	if (self->needClip && need_draw) {
		self->clip(self, canvas) ;
	}
	{
		if (need_draw) {
			if (self->cb && self->cb->cbDrawSelf(self->cb, self, canvas) ) {
				
			}
			else {
				((SuiCore$ViewBase * )self)->draw_self(self, canvas) ;
				if (self->cb) {
					self->cb->afterDrawSelf(self->cb, self, canvas) ;
				}
			}
		}
		SuiCore$Canvas$save(canvas) ;
		SuiCore$Canvas$translate(canvas, self->padding.left + self->border->l->w, self->padding.top + self->border->t->w) ;
		((SuiCore$ViewBase * )self)->draw_children(self, canvas) ;
		SuiCore$Canvas$restore(canvas) ;
		if (need_draw) {
			self->drawSelfBorder(self, canvas) ;
		}
	}
	SuiCore$Canvas$restore(canvas) ;
}


void  SuiCore$View$drawSelfBorder(SuiCore$View *  self, SuiCore$Canvas *  canvas){
	int  tc = self->border->t->color;
	int  rc = self->border->r->color;
	int  bc = self->border->b->color;
	int  lc = self->border->l->color;
	if ((SuiCore$colorGetA(tc)  > 0 || SuiCore$colorGetA(rc)  > 0 || SuiCore$colorGetA(bc)  > 0 || SuiCore$colorGetA(lc)  > 0)) {
		SuiCore$Rect viewRect = self->getViewRect(self) ;
		float  w = viewRect.w;
		float  h = viewRect.h;
		if (self->border->isAllHasWidth(self->border) ) {
			SuiCore$Canvas$beginPath(canvas) ;
			if (self->border->t->w <= 1.001f) {
				SuiCore$Canvas$strokeWidth(canvas, 1.0f) ;
				SuiCore$Canvas$roundRect(canvas, 0.5f, 0.5f, w - 0.5, h - 0.5, self->radius->tl) ;
			}
			else {
				SuiCore$Canvas$roundRect(canvas, 0.5f, 0.5f, w - 0.5, h - 0.5, self->radius->tl) ;
				SuiCore$Canvas$strokeWidth(canvas, self->border->t->w) ;
			}
			SuiCore$Canvas$strokeColorByInt32(canvas, (self->border->t->color)) ;
			SuiCore$Canvas$stroke(canvas) ;
		}
		else {
			if (self->border->t->w > 0.f) {
				SuiCore$Canvas$beginPath(canvas) ;
				SuiCore$Canvas$moveTo(canvas, 0.5f, 0.5f) ;
				SuiCore$Canvas$lineTo(canvas, w + 0.5f, 0.5f) ;
				SuiCore$Canvas$strokeWidth(canvas, self->border->t->w) ;
				SuiCore$Canvas$strokeColorByInt32(canvas, (self->border->t->color)) ;
				SuiCore$Canvas$stroke(canvas) ;
			}
			if (self->border->r->w > 0.f) {
				SuiCore$Canvas$beginPath(canvas) ;
				SuiCore$Canvas$moveTo(canvas, w + 0.5f, 0.5f) ;
				SuiCore$Canvas$lineTo(canvas, w + 0.5f, h + 0.5f) ;
				SuiCore$Canvas$strokeWidth(canvas, self->border->r->w) ;
				SuiCore$Canvas$strokeColorByInt32(canvas, (self->border->r->color)) ;
				SuiCore$Canvas$stroke(canvas) ;
			}
			if (self->border->b->w > 0.f) {
				SuiCore$Canvas$beginPath(canvas) ;
				SuiCore$Canvas$moveTo(canvas, 0.5f, h + 0.5f) ;
				SuiCore$Canvas$lineTo(canvas, w + 0.5f, h + 0.5f) ;
				SuiCore$Canvas$strokeWidth(canvas, self->border->b->w) ;
				SuiCore$Canvas$strokeColorByInt32(canvas, (self->border->b->color)) ;
				SuiCore$Canvas$stroke(canvas) ;
			}
			if (self->border->l->w > 0.f) {
				SuiCore$Canvas$beginPath(canvas) ;
				SuiCore$Canvas$moveTo(canvas, 0.5f, 0.5f) ;
				SuiCore$Canvas$lineTo(canvas, 0.5f, h + 0.5f) ;
				SuiCore$Canvas$strokeWidth(canvas, self->border->l->w) ;
				SuiCore$Canvas$strokeColorByInt32(canvas, (self->border->l->color)) ;
				SuiCore$Canvas$stroke(canvas) ;
			}
		}
	}
}


void  SuiCore$View$draw_self(SuiCore$View *  self, SuiCore$Canvas *  canvas){
	float  bga = SuiCore$colorGetA(self->backgroundColor) ;
	if (bga > 0.f) {
		SuiCore$Vec2 size = self->getSizeWithoutMargin(self) ;
		float  w = size.x;
		float  h = size.y;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$roundRect(canvas, 0.f, 0.f, w, h, self->radius->tl) ;
		SuiCore$Canvas$fillColorByInt32(canvas, self->backgroundColor) ;
		SuiCore$Canvas$fill(canvas) ;
	}
}





