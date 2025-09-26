
#include "LayoutAlign_orc.h" 

#include <stdio.h>
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/LayoutCell_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/List_orc.h"
#include "../View/ViewBuilder_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiLayout$LayoutAlignPositionCell _vtable_SuiLayout$LayoutAlignPositionCell;

// init meta

void SuiLayout$LayoutAlignPositionCell_initMeta(Vtable_SuiLayout$LayoutAlignPositionCell *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "left", OrcMetaType_float, offsetof(SuiLayout$LayoutAlignPositionCell, left), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "top", OrcMetaType_float, offsetof(SuiLayout$LayoutAlignPositionCell, top), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "right", OrcMetaType_float, offsetof(SuiLayout$LayoutAlignPositionCell, right), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "bottom", OrcMetaType_float, offsetof(SuiLayout$LayoutAlignPositionCell, bottom), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_SuiLayout$LayoutAlignPositionCell* Vtable_SuiLayout$LayoutAlignPositionCell_init(Vtable_SuiLayout$LayoutAlignPositionCell* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutAlignPositionCell;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$LayoutCell_init(&_vtable_SuiCore$LayoutCell);

	// init by super vtable init function
    Vtable_SuiCore$LayoutCell_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$LayoutCell;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutAlignPositionCell_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutAlignPositionCell";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutAlignPositionCell_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiLayout$LayoutAlignPositionCell_fini(SuiLayout$LayoutAlignPositionCell *self){
	//super fini
    SuiCore$LayoutCell_fini((SuiCore$LayoutCell *)self);

    //字段释放


}

// init fields function


void SuiLayout$LayoutAlignPositionCell_init_fields(SuiLayout$LayoutAlignPositionCell *self){
	//super class
    SuiCore$LayoutCell_init_fields((SuiCore$LayoutCell*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutAlignPositionCell_fini;
	//fields
    {
	((SuiLayout$LayoutAlignPositionCell*)self)->left = 0;
	((SuiLayout$LayoutAlignPositionCell*)self)->top = 0;
	((SuiLayout$LayoutAlignPositionCell*)self)->right = NAN;
	((SuiLayout$LayoutAlignPositionCell*)self)->bottom = NAN;
    }
	
}

// init function

void SuiLayout$LayoutAlignPositionCell_init(SuiLayout$LayoutAlignPositionCell *self, void *pOwner){
    Vtable_SuiLayout$LayoutAlignPositionCell_init(&_vtable_SuiLayout$LayoutAlignPositionCell);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutAlignPositionCell;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutAlignPositionCell_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutAlignPositionCell * SuiLayout$LayoutAlignPositionCell_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutAlignPositionCell *self = calloc(1, sizeof(SuiLayout$LayoutAlignPositionCell));
	
    SuiLayout$LayoutAlignPositionCell_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiLayout$LayoutAlignCell _vtable_SuiLayout$LayoutAlignCell;

// init meta

void SuiLayout$LayoutAlignCell_initMeta(Vtable_SuiLayout$LayoutAlignCell *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "anchor", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiLayout$LayoutAlignCell, anchor), false, false, 0);
	orc_metaField_struct(&pNext, "align", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiLayout$LayoutAlignCell, align), false, false, 0);
	orc_metaField_struct(&pNext, "sizeRatio", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiLayout$LayoutAlignCell, sizeRatio), false, false, 0);

	orc_metaField_method(&pNext, "setSameRatio", offsetof(SuiLayout$LayoutAlignCell, setSameRatio));
	orc_metaField_method(&pNext, "setTopLeft", offsetof(SuiLayout$LayoutAlignCell, setTopLeft));
	orc_metaField_method(&pNext, "setTopCenter", offsetof(SuiLayout$LayoutAlignCell, setTopCenter));
	orc_metaField_method(&pNext, "setTopRight", offsetof(SuiLayout$LayoutAlignCell, setTopRight));
	orc_metaField_method(&pNext, "setBottomLeft", offsetof(SuiLayout$LayoutAlignCell, setBottomLeft));
	orc_metaField_method(&pNext, "setBottomCenter", offsetof(SuiLayout$LayoutAlignCell, setBottomCenter));
	orc_metaField_method(&pNext, "setBottomRight", offsetof(SuiLayout$LayoutAlignCell, setBottomRight));
	orc_metaField_method(&pNext, "setMiddleLeft", offsetof(SuiLayout$LayoutAlignCell, setMiddleLeft));
	orc_metaField_method(&pNext, "setCenter", offsetof(SuiLayout$LayoutAlignCell, setCenter));
	orc_metaField_method(&pNext, "setMiddleRight", offsetof(SuiLayout$LayoutAlignCell, setMiddleRight));
}


// vtable init


Vtable_SuiLayout$LayoutAlignCell* Vtable_SuiLayout$LayoutAlignCell_init(Vtable_SuiLayout$LayoutAlignCell* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutAlignCell;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$LayoutCell_init(&_vtable_SuiCore$LayoutCell);

	// init by super vtable init function
    Vtable_SuiCore$LayoutCell_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$LayoutCell;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutAlignCell_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutAlignCell";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutAlignCell_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiLayout$LayoutAlignCell_fini(SuiLayout$LayoutAlignCell *self){
	//super fini
    SuiCore$LayoutCell_fini((SuiCore$LayoutCell *)self);

    //字段释放


}

// init fields function


void SuiLayout$LayoutAlignCell_init_fields(SuiLayout$LayoutAlignCell *self){
	//super class
    SuiCore$LayoutCell_init_fields((SuiCore$LayoutCell*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutAlignCell_fini;
	//fields
    {
	((SuiLayout$LayoutAlignCell*)self)->anchor = SuiCore$mkVec2(0, 0) ;
	((SuiLayout$LayoutAlignCell*)self)->align = SuiCore$mkVec2(0, 0) ;
	((SuiLayout$LayoutAlignCell*)self)->sizeRatio = SuiCore$mkVec2(NAN, NAN) ;
    }
	((SuiLayout$LayoutAlignCell*)self)->setSameRatio = (void*)SuiLayout$LayoutAlignCell$setSameRatio;
	((SuiLayout$LayoutAlignCell*)self)->setTopLeft = (void*)SuiLayout$LayoutAlignCell$setTopLeft;
	((SuiLayout$LayoutAlignCell*)self)->setTopCenter = (void*)SuiLayout$LayoutAlignCell$setTopCenter;
	((SuiLayout$LayoutAlignCell*)self)->setTopRight = (void*)SuiLayout$LayoutAlignCell$setTopRight;
	((SuiLayout$LayoutAlignCell*)self)->setBottomLeft = (void*)SuiLayout$LayoutAlignCell$setBottomLeft;
	((SuiLayout$LayoutAlignCell*)self)->setBottomCenter = (void*)SuiLayout$LayoutAlignCell$setBottomCenter;
	((SuiLayout$LayoutAlignCell*)self)->setBottomRight = (void*)SuiLayout$LayoutAlignCell$setBottomRight;
	((SuiLayout$LayoutAlignCell*)self)->setMiddleLeft = (void*)SuiLayout$LayoutAlignCell$setMiddleLeft;
	((SuiLayout$LayoutAlignCell*)self)->setCenter = (void*)SuiLayout$LayoutAlignCell$setCenter;
	((SuiLayout$LayoutAlignCell*)self)->setMiddleRight = (void*)SuiLayout$LayoutAlignCell$setMiddleRight;
}

// init function

void SuiLayout$LayoutAlignCell_init(SuiLayout$LayoutAlignCell *self, void *pOwner){
    Vtable_SuiLayout$LayoutAlignCell_init(&_vtable_SuiLayout$LayoutAlignCell);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutAlignCell;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutAlignCell_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutAlignCell * SuiLayout$LayoutAlignCell_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutAlignCell *self = calloc(1, sizeof(SuiLayout$LayoutAlignCell));
	
    SuiLayout$LayoutAlignCell_init(self, pOwner);
    return self;
}


// class members
void  SuiLayout$LayoutAlignCell$setSameRatio(SuiLayout$LayoutAlignCell *  self, float  x, float  y){
	self->anchor.x = x;
	self->anchor.y = y;
	self->align.x = x;
	self->align.y = y;
}


void  SuiLayout$LayoutAlignCell$setTopLeft(SuiLayout$LayoutAlignCell *  self){
	self->setSameRatio(self, 0.0, 0.0) ;
}


void  SuiLayout$LayoutAlignCell$setTopCenter(SuiLayout$LayoutAlignCell *  self){
	self->setSameRatio(self, 0.5, 0.0) ;
}


void  SuiLayout$LayoutAlignCell$setTopRight(SuiLayout$LayoutAlignCell *  self){
	self->setSameRatio(self, 1.0, 0.0) ;
}


void  SuiLayout$LayoutAlignCell$setBottomLeft(SuiLayout$LayoutAlignCell *  self){
	self->setSameRatio(self, 0.0, 1.0) ;
}


void  SuiLayout$LayoutAlignCell$setBottomCenter(SuiLayout$LayoutAlignCell *  self){
	self->setSameRatio(self, 0.5, 1.0) ;
}


void  SuiLayout$LayoutAlignCell$setBottomRight(SuiLayout$LayoutAlignCell *  self){
	self->setSameRatio(self, 1.0, 1.0) ;
}


void  SuiLayout$LayoutAlignCell$setMiddleLeft(SuiLayout$LayoutAlignCell *  self){
	self->setSameRatio(self, 0.0, 0.5) ;
}


void  SuiLayout$LayoutAlignCell$setCenter(SuiLayout$LayoutAlignCell *  self){
	self->setSameRatio(self, 0.5, 0.5) ;
}


void  SuiLayout$LayoutAlignCell$setMiddleRight(SuiLayout$LayoutAlignCell *  self){
	self->setSameRatio(self, 1.0, 0.5) ;
}




//vtable instance
Vtable_SuiLayout$LayoutAlign _vtable_SuiLayout$LayoutAlign;

// init meta

void SuiLayout$LayoutAlign_initMeta(Vtable_SuiLayout$LayoutAlign *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "anchor", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiLayout$LayoutAlign, anchor), false, false, 0);
	orc_metaField_struct(&pNext, "align", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiLayout$LayoutAlign, align), false, false, 0);
	orc_metaField_primitive(&pNext, "useMaxConstraint", OrcMetaType_bool, offsetof(SuiLayout$LayoutAlign, useMaxConstraint), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "setSameRatio", offsetof(SuiLayout$LayoutAlign, setSameRatio));
	orc_metaField_method(&pNext, "setTopLeft", offsetof(SuiLayout$LayoutAlign, setTopLeft));
	orc_metaField_method(&pNext, "setTopCenter", offsetof(SuiLayout$LayoutAlign, setTopCenter));
	orc_metaField_method(&pNext, "setTopRight", offsetof(SuiLayout$LayoutAlign, setTopRight));
	orc_metaField_method(&pNext, "setBottomLeft", offsetof(SuiLayout$LayoutAlign, setBottomLeft));
	orc_metaField_method(&pNext, "setBottomCenter", offsetof(SuiLayout$LayoutAlign, setBottomCenter));
	orc_metaField_method(&pNext, "setBottomRight", offsetof(SuiLayout$LayoutAlign, setBottomRight));
	orc_metaField_method(&pNext, "setMiddleLeft", offsetof(SuiLayout$LayoutAlign, setMiddleLeft));
	orc_metaField_method(&pNext, "setCenter", offsetof(SuiLayout$LayoutAlign, setCenter));
	orc_metaField_method(&pNext, "setMiddleRight", offsetof(SuiLayout$LayoutAlign, setMiddleRight));
	orc_metaField_method(&pNext, "getAnchorAndAlign_byView", offsetof(SuiLayout$LayoutAlign, getAnchorAndAlign_byView));
}


// vtable init


Vtable_SuiLayout$LayoutAlign* Vtable_SuiLayout$LayoutAlign_init(Vtable_SuiLayout$LayoutAlign* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutAlign;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutAlign_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutAlign";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutAlign_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiLayout$LayoutAlign_fini(SuiLayout$LayoutAlign *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiLayout$LayoutAlign_init_fields(SuiLayout$LayoutAlign *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutAlign_fini;
	//fields
    {
	((SuiLayout$LayoutAlign*)self)->anchor = SuiCore$mkVec2(0, 0) ;
	((SuiLayout$LayoutAlign*)self)->align = SuiCore$mkVec2(0, 0) ;
	((SuiLayout$LayoutAlign*)self)->useMaxConstraint = true;
    }
	((SuiLayout$LayoutAlign*)self)->setSameRatio = (void*)SuiLayout$LayoutAlign$setSameRatio;
	((SuiLayout$LayoutAlign*)self)->setTopLeft = (void*)SuiLayout$LayoutAlign$setTopLeft;
	((SuiLayout$LayoutAlign*)self)->setTopCenter = (void*)SuiLayout$LayoutAlign$setTopCenter;
	((SuiLayout$LayoutAlign*)self)->setTopRight = (void*)SuiLayout$LayoutAlign$setTopRight;
	((SuiLayout$LayoutAlign*)self)->setBottomLeft = (void*)SuiLayout$LayoutAlign$setBottomLeft;
	((SuiLayout$LayoutAlign*)self)->setBottomCenter = (void*)SuiLayout$LayoutAlign$setBottomCenter;
	((SuiLayout$LayoutAlign*)self)->setBottomRight = (void*)SuiLayout$LayoutAlign$setBottomRight;
	((SuiLayout$LayoutAlign*)self)->setMiddleLeft = (void*)SuiLayout$LayoutAlign$setMiddleLeft;
	((SuiLayout$LayoutAlign*)self)->setCenter = (void*)SuiLayout$LayoutAlign$setCenter;
	((SuiLayout$LayoutAlign*)self)->setMiddleRight = (void*)SuiLayout$LayoutAlign$setMiddleRight;
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiLayout$LayoutAlign$layoutContent;
	((SuiLayout$LayoutAlign*)self)->getAnchorAndAlign_byView = (void*)SuiLayout$LayoutAlign$getAnchorAndAlign_byView;
}

// init function

void SuiLayout$LayoutAlign_init(SuiLayout$LayoutAlign *self, void *pOwner){
    Vtable_SuiLayout$LayoutAlign_init(&_vtable_SuiLayout$LayoutAlign);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutAlign;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutAlign_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutAlign * SuiLayout$LayoutAlign_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutAlign *self = calloc(1, sizeof(SuiLayout$LayoutAlign));
	
    SuiLayout$LayoutAlign_init(self, pOwner);
    return self;
}


// class members
void  SuiLayout$LayoutAlign$setSameRatio(SuiLayout$LayoutAlign *  self, float  x, float  y){
	self->anchor.x = x;
	self->anchor.y = y;
	self->align.x = x;
	self->align.y = y;
}


void  SuiLayout$LayoutAlign$setTopLeft(SuiLayout$LayoutAlign *  self){
	self->setSameRatio(self, 0.0, 0.0) ;
}


void  SuiLayout$LayoutAlign$setTopCenter(SuiLayout$LayoutAlign *  self){
	self->setSameRatio(self, 0.5, 0.0) ;
}


void  SuiLayout$LayoutAlign$setTopRight(SuiLayout$LayoutAlign *  self){
	self->setSameRatio(self, 1.0, 0.0) ;
}


void  SuiLayout$LayoutAlign$setBottomLeft(SuiLayout$LayoutAlign *  self){
	self->setSameRatio(self, 0.0, 1.0) ;
}


void  SuiLayout$LayoutAlign$setBottomCenter(SuiLayout$LayoutAlign *  self){
	self->setSameRatio(self, 0.5, 1.0) ;
}


void  SuiLayout$LayoutAlign$setBottomRight(SuiLayout$LayoutAlign *  self){
	self->setSameRatio(self, 1.0, 1.0) ;
}


void  SuiLayout$LayoutAlign$setMiddleLeft(SuiLayout$LayoutAlign *  self){
	self->setSameRatio(self, 0.0, 0.5) ;
}


void  SuiLayout$LayoutAlign$setCenter(SuiLayout$LayoutAlign *  self){
	self->setSameRatio(self, 0.5, 0.5) ;
}


void  SuiLayout$LayoutAlign$setMiddleRight(SuiLayout$LayoutAlign *  self){
	self->setSameRatio(self, 1.0, 0.5) ;
}


void  SuiLayout$LayoutAlign$layoutContent(SuiLayout$LayoutAlign *  self, SuiCore$Frame *  ctx){
	float  maxWidth = 0;
	float  maxHeight = 0;
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (view && view->canLayoutByParent(view) ) {
			SuiCore$LayoutCell *  cell = (SuiCore$LayoutCell * )((SuiCore$Node * )view)->getChildByType(view, Vtable_SuiCore$LayoutCell_init(NULL)) ;
			if (Orc_instanceof((Object*)cell, (Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(NULL))) {
				
			}
			else {
				if (self->useMaxConstraint) {
					SuiCore$Frame$copyMaxConstraints(&view->frame, ctx) ;
				}
				if (Orc_instanceof((Object*)cell, (Vtable_Object*)Vtable_SuiLayout$LayoutAlignCell_init(NULL))) {
					SuiLayout$LayoutAlignCell *  ac = (SuiLayout$LayoutAlignCell * )cell;
					if (!Orc$isNaN(ac->sizeRatio.x) ) {
						SuiCore$Frame$setTightWidth(&view->frame, ctx->width * ac->sizeRatio.x) ;
					}
					if (!Orc$isNaN(ac->sizeRatio.y) ) {
						SuiCore$Frame$setTightHeight(&view->frame, ctx->height * ac->sizeRatio.y) ;
					}
				}
				view->layout(view, &view->frame) ;
				maxWidth = Orc$maxFloat(maxWidth, view->frame.width) ;
				maxHeight = Orc$maxFloat(maxHeight, view->frame.height) ;
			}
		}
	}
	SuiCore$Frame$setSize(ctx, maxWidth, maxHeight) ;
	l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (view && view->canLayoutByParent(view) ) {
			SuiCore$LayoutCell *  cell = (SuiCore$LayoutCell * )((SuiCore$Node * )view)->getChildByType(view, Vtable_SuiCore$LayoutCell_init(NULL)) ;
			if (Orc_instanceof((Object*)cell, (Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(NULL))) {
				SuiLayout$LayoutAlignPositionCell *  pcell = (SuiLayout$LayoutAlignPositionCell * )cell;
				SuiCore$Frame$reset(&view->frame) ;
				if (!Orc$isNaN(pcell->left)  && !Orc$isNaN(pcell->right) ) {
					float  w = ctx->width - pcell->left - pcell->right;
					SuiCore$Frame$setWidthConstraint(&view->frame, w, w) ;
				}
				if (!Orc$isNaN(pcell->top)  && !Orc$isNaN(pcell->bottom) ) {
					float  h = ctx->height - pcell->top - pcell->bottom;
					SuiCore$Frame$setHeightConstraint(&view->frame, h, h) ;
				}
				view->layout(view, &view->frame) ;
				if (!Orc$isNaN(pcell->left) ) {
					view->frame.x = pcell->left;
				}
				if (!Orc$isNaN(pcell->top) ) {
					view->frame.y = pcell->top;
				}
				if (!Orc$isNaN(pcell->right) ) {
					view->frame.x = ctx->width - pcell->right - view->frame.width;
				}
				if (!Orc$isNaN(pcell->bottom) ) {
					view->frame.y = ctx->height - pcell->bottom - view->frame.height;
				}
			}
			else {
				SuiCore$Vec2 anchor;
				SuiCore$Vec2 align;
				self->getAnchorAndAlign_byView(self, view, &anchor, &align) ;
				view->frame.x = ctx->width * align.x - view->frame.width * anchor.x;
				view->frame.y = ctx->height * align.y - view->frame.height * anchor.y;
			}
		}
	}
}


void  SuiLayout$LayoutAlign$getAnchorAndAlign_byView(SuiLayout$LayoutAlign *  self, SuiCore$ViewBase *  view, SuiCore$Vec2 *  anchor, SuiCore$Vec2 *  align){
	SuiLayout$LayoutAlignCell *  cell = (SuiLayout$LayoutAlignCell * )((SuiCore$Node * )view)->getChildByType(view, Vtable_SuiLayout$LayoutAlignCell_init(NULL)) ;
	if (cell != NULL) {
		*anchor = cell->anchor;
		*align = cell->align;
	}
	else {
		*anchor = self->anchor;
		*align = self->align;
	}
}



SuiLayout$LayoutAlign*  SuiLayout$layoutAlign(SuiLayout$LayoutAlign **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiLayout$LayoutAlign* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiLayout$LayoutAlign_init(NULL)) ) ; 
}

SuiLayout$LayoutAlignCell*  SuiLayout$layoutAlignCell(SuiLayout$LayoutAlignCell **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiLayout$LayoutAlignCell* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiLayout$LayoutAlignCell_init(NULL)) ) ; 
}

SuiLayout$LayoutAlignPositionCell*  SuiLayout$layoutAlignPositionCell(SuiLayout$LayoutAlignPositionCell **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiLayout$LayoutAlignPositionCell* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiLayout$LayoutAlignPositionCell_init(NULL)) ) ; 
}



