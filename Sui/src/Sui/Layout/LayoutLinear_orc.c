
#include "LayoutLinear_orc.h" 

#include <stdio.h>
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
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
Vtable_SuiLayout$LayoutLinearCell _vtable_SuiLayout$LayoutLinearCell;

// init meta

void SuiLayout$LayoutLinearCell_initMeta(Vtable_SuiLayout$LayoutLinearCell *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "grow", OrcMetaType_float, offsetof(SuiLayout$LayoutLinearCell, grow), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "alignSelf", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiLayout$LayoutLinearCell, alignSelf), true, false, 1);

	
}


// vtable init


Vtable_SuiLayout$LayoutLinearCell* Vtable_SuiLayout$LayoutLinearCell_init(Vtable_SuiLayout$LayoutLinearCell* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutLinearCell;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$LayoutCell_init(&_vtable_SuiCore$LayoutCell);

	// init by super vtable init function
    Vtable_SuiCore$LayoutCell_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$LayoutCell;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutLinearCell_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutLinearCell";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutLinearCell_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiLayout$LayoutLinearCell_fini(SuiLayout$LayoutLinearCell *self){
	//super fini
    SuiCore$LayoutCell_fini((SuiCore$LayoutCell *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiLayout$LayoutLinearCell*)self)->alignSelf);

}

// init fields function


void SuiLayout$LayoutLinearCell_init_fields(SuiLayout$LayoutLinearCell *self){
	//super class
    SuiCore$LayoutCell_init_fields((SuiCore$LayoutCell*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutLinearCell_fini;
	//fields
    {
	((SuiLayout$LayoutLinearCell*)self)->grow = 1.f;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiLayout$LayoutLinearCell*)self)->alignSelf, Orc$str(&tmpReturn_1, "") );
    }
	
}

// init function

void SuiLayout$LayoutLinearCell_init(SuiLayout$LayoutLinearCell *self, void *pOwner){
    Vtable_SuiLayout$LayoutLinearCell_init(&_vtable_SuiLayout$LayoutLinearCell);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutLinearCell;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutLinearCell_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutLinearCell * SuiLayout$LayoutLinearCell_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutLinearCell *self = calloc(1, sizeof(SuiLayout$LayoutLinearCell));
	
    SuiLayout$LayoutLinearCell_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiLayout$LayoutLinear _vtable_SuiLayout$LayoutLinear;

// init meta

void SuiLayout$LayoutLinear_initMeta(Vtable_SuiLayout$LayoutLinear *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "direction", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiLayout$LayoutLinear, direction), true, false, 1);
	orc_metaField_class(&pNext, "justifyContent", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiLayout$LayoutLinear, justifyContent), true, false, 1);
	orc_metaField_class(&pNext, "alignItems", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiLayout$LayoutLinear, alignItems), true, false, 1);
	orc_metaField_primitive(&pNext, "maxCrossSize", OrcMetaType_float, offsetof(SuiLayout$LayoutLinear, maxCrossSize), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "isMax_in_maxOrStretch", offsetof(SuiLayout$LayoutLinear, isMax_in_maxOrStretch));
	orc_metaField_method(&pNext, "layoutCross", offsetof(SuiLayout$LayoutLinear, layoutCross));
	orc_metaField_method(&pNext, "calcIsHor", offsetof(SuiLayout$LayoutLinear, calcIsHor));
	orc_metaField_method(&pNext, "getCrossAlign_ofKid", offsetof(SuiLayout$LayoutLinear, getCrossAlign_ofKid));
	orc_metaField_method(&pNext, "positionChildren", offsetof(SuiLayout$LayoutLinear, positionChildren));
	orc_metaField_method(&pNext, "setMainConstraints", offsetof(SuiLayout$LayoutLinear, setMainConstraints));
	orc_metaField_method(&pNext, "setCrossConstraints", offsetof(SuiLayout$LayoutLinear, setCrossConstraints));
	orc_metaField_method(&pNext, "getMainMaxConstraint", offsetof(SuiLayout$LayoutLinear, getMainMaxConstraint));
	orc_metaField_method(&pNext, "getCrossMaxConstraint", offsetof(SuiLayout$LayoutLinear, getCrossMaxConstraint));
	orc_metaField_method(&pNext, "update_maxCrossSize", offsetof(SuiLayout$LayoutLinear, update_maxCrossSize));
	orc_metaField_method(&pNext, "layout_mainInf", offsetof(SuiLayout$LayoutLinear, layout_mainInf));
	orc_metaField_method(&pNext, "layout_mainLimit", offsetof(SuiLayout$LayoutLinear, layout_mainLimit));
	orc_metaField_method(&pNext, "jcc", offsetof(SuiLayout$LayoutLinear, jcc));
	orc_metaField_method(&pNext, "jcs", offsetof(SuiLayout$LayoutLinear, jcs));
	orc_metaField_method(&pNext, "jce", offsetof(SuiLayout$LayoutLinear, jce));
	orc_metaField_method(&pNext, "jcsb", offsetof(SuiLayout$LayoutLinear, jcsb));
	orc_metaField_method(&pNext, "jcsa", offsetof(SuiLayout$LayoutLinear, jcsa));
	orc_metaField_method(&pNext, "jcse", offsetof(SuiLayout$LayoutLinear, jcse));
	orc_metaField_method(&pNext, "ais", offsetof(SuiLayout$LayoutLinear, ais));
	orc_metaField_method(&pNext, "aic", offsetof(SuiLayout$LayoutLinear, aic));
	orc_metaField_method(&pNext, "aie", offsetof(SuiLayout$LayoutLinear, aie));
	orc_metaField_method(&pNext, "aiStretch", offsetof(SuiLayout$LayoutLinear, aiStretch));
	orc_metaField_method(&pNext, "aiMaxOrStretch", offsetof(SuiLayout$LayoutLinear, aiMaxOrStretch));
	orc_metaField_method(&pNext, "column", offsetof(SuiLayout$LayoutLinear, column));
	orc_metaField_method(&pNext, "row", offsetof(SuiLayout$LayoutLinear, row));
}


// vtable init


Vtable_SuiLayout$LayoutLinear* Vtable_SuiLayout$LayoutLinear_init(Vtable_SuiLayout$LayoutLinear* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutLinear;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutLinear_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutLinear";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutLinear_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiLayout$LayoutLinear_fini(SuiLayout$LayoutLinear *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiLayout$LayoutLinear*)self)->direction);
	urgc_fini_field_class(self, (void**)&((SuiLayout$LayoutLinear*)self)->justifyContent);
	urgc_fini_field_class(self, (void**)&((SuiLayout$LayoutLinear*)self)->alignItems);

}

// init fields function


void SuiLayout$LayoutLinear_init_fields(SuiLayout$LayoutLinear *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutLinear_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiLayout$LayoutLinear*)self)->direction, Orc$str(&tmpReturn_1, "row") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiLayout$LayoutLinear*)self)->justifyContent, Orc$str(&tmpReturn_2, "start") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiLayout$LayoutLinear*)self)->alignItems, Orc$str(&tmpReturn_3, "center") );
	((SuiLayout$LayoutLinear*)self)->maxCrossSize = 0.f;
    }
	((SuiLayout$LayoutLinear*)self)->isMax_in_maxOrStretch = (void*)SuiLayout$LayoutLinear$isMax_in_maxOrStretch;
	((SuiLayout$LayoutLinear*)self)->layoutCross = (void*)SuiLayout$LayoutLinear$layoutCross;
	((SuiLayout$LayoutLinear*)self)->calcIsHor = (void*)SuiLayout$LayoutLinear$calcIsHor;
	((SuiLayout$LayoutLinear*)self)->getCrossAlign_ofKid = (void*)SuiLayout$LayoutLinear$getCrossAlign_ofKid;
	((SuiLayout$LayoutLinear*)self)->positionChildren = (void*)SuiLayout$LayoutLinear$positionChildren;
	((SuiLayout$LayoutLinear*)self)->setMainConstraints = (void*)SuiLayout$LayoutLinear$setMainConstraints;
	((SuiLayout$LayoutLinear*)self)->setCrossConstraints = (void*)SuiLayout$LayoutLinear$setCrossConstraints;
	((SuiLayout$LayoutLinear*)self)->getMainMaxConstraint = (void*)SuiLayout$LayoutLinear$getMainMaxConstraint;
	((SuiLayout$LayoutLinear*)self)->getCrossMaxConstraint = (void*)SuiLayout$LayoutLinear$getCrossMaxConstraint;
	((SuiLayout$LayoutLinear*)self)->update_maxCrossSize = (void*)SuiLayout$LayoutLinear$update_maxCrossSize;
	((SuiLayout$LayoutLinear*)self)->layout_mainInf = (void*)SuiLayout$LayoutLinear$layout_mainInf;
	((SuiLayout$LayoutLinear*)self)->layout_mainLimit = (void*)SuiLayout$LayoutLinear$layout_mainLimit;
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiLayout$LayoutLinear$layoutContent;
	((SuiLayout$LayoutLinear*)self)->jcc = (void*)SuiLayout$LayoutLinear$jcc;
	((SuiLayout$LayoutLinear*)self)->jcs = (void*)SuiLayout$LayoutLinear$jcs;
	((SuiLayout$LayoutLinear*)self)->jce = (void*)SuiLayout$LayoutLinear$jce;
	((SuiLayout$LayoutLinear*)self)->jcsb = (void*)SuiLayout$LayoutLinear$jcsb;
	((SuiLayout$LayoutLinear*)self)->jcsa = (void*)SuiLayout$LayoutLinear$jcsa;
	((SuiLayout$LayoutLinear*)self)->jcse = (void*)SuiLayout$LayoutLinear$jcse;
	((SuiLayout$LayoutLinear*)self)->ais = (void*)SuiLayout$LayoutLinear$ais;
	((SuiLayout$LayoutLinear*)self)->aic = (void*)SuiLayout$LayoutLinear$aic;
	((SuiLayout$LayoutLinear*)self)->aie = (void*)SuiLayout$LayoutLinear$aie;
	((SuiLayout$LayoutLinear*)self)->aiStretch = (void*)SuiLayout$LayoutLinear$aiStretch;
	((SuiLayout$LayoutLinear*)self)->aiMaxOrStretch = (void*)SuiLayout$LayoutLinear$aiMaxOrStretch;
	((SuiLayout$LayoutLinear*)self)->column = (void*)SuiLayout$LayoutLinear$column;
	((SuiLayout$LayoutLinear*)self)->row = (void*)SuiLayout$LayoutLinear$row;
	((SuiCore$ViewBase*)self)->layout = (void*)SuiLayout$LayoutLinear$layout;
}

// init function

void SuiLayout$LayoutLinear_init(SuiLayout$LayoutLinear *self, void *pOwner){
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutLinear;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutLinear_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutLinear * SuiLayout$LayoutLinear_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutLinear *self = calloc(1, sizeof(SuiLayout$LayoutLinear));
	
    SuiLayout$LayoutLinear_init(self, pOwner);
    return self;
}


// class members
bool  SuiLayout$LayoutLinear$isMax_in_maxOrStretch(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx, bool  isHor){
	if (Orc$String$equals(self->alignItems, "maxOrStretch") ) {
		if (isHor && ctx->maxHeight != INFINITY) {
			return true; 
		}
		if (!isHor && ctx->maxWidth != INFINITY) {
			return true; 
		}
	}
	return false; 
}


void  SuiLayout$LayoutLinear$layoutCross(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx){
	bool  isHor = self->calcIsHor(self) ;
	bool  isStretch = Orc$String$equals(self->alignItems, "stretch")  || Orc$String$equals(self->alignItems, "maxOrStretch") ;
	if (self->isMax_in_maxOrStretch(self, ctx, isHor) ) {
		return ; 
	}
	for (int  i = 0; i < ((SuiCore$Node * )self)->getChildrenCount(self) ; i++) {
		SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (view && view->canLayoutByParent(view) ) {
			SuiLayout$LayoutLinearCell *  cell = (SuiLayout$LayoutLinearCell * )view->getLayoutCellByType(view, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ;
			bool  isKidStretch = false;
			if (cell != NULL && Orc$String$notEquals(cell->alignSelf, "") ) {
				isKidStretch = Orc$String$equals(cell->alignSelf, "stretch") ;
			}
			else {
				isKidStretch = isStretch;
			}
			if (isKidStretch) {
				SuiCore$Frame *  kidCtx = &view->frame;
				if (isHor) {
					if (kidCtx->height == ctx->height) {
						continue;
					}
					SuiCore$Frame$setTightWidth(kidCtx, kidCtx->width) ;
					kidCtx->maxHeight = ctx->height;
					kidCtx->minHeight = kidCtx->maxHeight;
				}
				else {
					if (kidCtx->width == ctx->width) {
						continue;
					}
					SuiCore$Frame$setTightHeight(kidCtx, kidCtx->height) ;
					kidCtx->maxWidth = ctx->width;
					kidCtx->minWidth = kidCtx->maxWidth;
				}
				view->layout(view, kidCtx) ;
				if (0) {
					printf("haha\n") ;
				}
			}
		}
	}
}


bool  SuiLayout$LayoutLinear$calcIsHor(SuiLayout$LayoutLinear *  self){
	bool  isHor = Orc$String$equals(self->direction, "row")  || Orc$String$equals(self->direction, "row-reverse") ;
	return isHor; 
}


Orc$String *  SuiLayout$LayoutLinear$getCrossAlign_ofKid(SuiLayout$LayoutLinear *  self, SuiCore$ViewBase *  view){
	if (view) {
		SuiLayout$LayoutLinearCell *  cell = (SuiLayout$LayoutLinearCell * )view->getLayoutCellByType(view, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ;
		if (cell && !Orc$String$empty(cell->alignSelf) ) {
			return cell->alignSelf; 
		}
	}
	return self->alignItems; 
}


void  SuiLayout$LayoutLinear$positionChildren(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx){
	bool  isHor = self->calcIsHor(self) ;
	float  crossPos = 0.f;
	float  width = ctx->width;
	float  height = ctx->height;
	float  sumMainSize = 0.f;
	int  viewCount = ((SuiCore$ViewBase * )self)->getChildrenViewCount(self) ;
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  v = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (v && v->canLayoutByParent(v) ) {
			float  addSize = 0.f;
			if (isHor) {
				addSize = v->frame.width;
			}
			else {
				addSize = v->frame.height;
			}
			sumMainSize = sumMainSize + addSize;
		}
	}
	float  idleSpace = ctx->width - sumMainSize;
	if (!isHor) {
		idleSpace = ctx->height - sumMainSize;
	}
	float  mainPos = 0.f;
	float  delta = 0.f;
	if (Orc$String$equals(self->justifyContent, "center") ) {
		mainPos = mainPos + idleSpace / 2.f;
	}
	else if (Orc$String$equals(self->justifyContent, "end") ) {
		mainPos = mainPos + idleSpace;
	}
	else if (Orc$String$equals(self->justifyContent, "space-between") ) {
		if (viewCount > 1) {
			delta = idleSpace / (viewCount - 1);
		}
		else {
			delta = 0.f;
		}
		delta = Orc$maxFloat(0.f, delta) ;
	}
	else if (Orc$String$equals(self->justifyContent, "space-around") ) {
		if (viewCount > 0) {
			delta = idleSpace / (viewCount);
		}
		else {
			delta = 0.f;
		}
		delta = Orc$maxFloat(0.f, delta) ;
		mainPos = mainPos + delta / 2.f;
	}
	else if (Orc$String$equals(self->justifyContent, "space-evenly") ) {
		delta = idleSpace / (viewCount + 1);
		delta = Orc$maxFloat(0.f, delta) ;
		mainPos = mainPos + delta;
	}
	bool  isReverse = Orc$String$equals(self->direction, "row-reverse")  || Orc$String$equals(self->direction, "column-reverse") ;
	int  len = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	if (isHor) {
		mainPos = mainPos;
		for (int  i = 0; i < len; i++) {
			int  idx = i;
			if (isReverse) {
				idx = len - i;
			}
			SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, idx) ;
			if (view) {
				SuiLayout$LayoutLinearCell *  cell = (SuiLayout$LayoutLinearCell * )view->getLayoutCellByType(view, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ;
				Orc$String *  crossAlign = self->getCrossAlign_ofKid(self, view) ;
				view->frame.x = mainPos;
				mainPos = mainPos + view->frame.width + delta;
				if (Orc$String$equals(crossAlign, "start") ) {
					view->frame.y = 0.f;
				}
				else if (Orc$String$equals(crossAlign, "center") ) {
					view->frame.y = (height - view->frame.height) / 2.0f;
				}
				else if (Orc$String$equals(crossAlign, "end") ) {
					view->frame.y = (height - view->frame.height);
				}
				else if (Orc$String$equals(crossAlign, "stretch") ) {
					view->frame.y = 0.f;
				}
			}
		}
	}
	else {
		mainPos = mainPos;
		for (int  i = 0; i < len; i++) {
			int  idx = isReverse ? len - i : i;
			SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, idx) ;
			if (view) {
				SuiLayout$LayoutLinearCell *  cell = (SuiLayout$LayoutLinearCell * )view->getLayoutCellByType(view, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ;
				Orc$String *  crossAlign = self->getCrossAlign_ofKid(self, view) ;
				view->frame.y = mainPos;
				mainPos = mainPos + view->frame.height + delta;
				if (Orc$String$equals(crossAlign, "start") ) {
					view->frame.x = 0.f;
				}
				else if (Orc$String$equals(crossAlign, "center") ) {
					view->frame.x = (width - view->frame.width) / 2.0f;
				}
				else if (Orc$String$equals(crossAlign, "start") ) {
					view->frame.x = (width - view->frame.width);
				}
				else if (Orc$String$equals(crossAlign, "stretch") ) {
					view->frame.x = 0.f;
				}
				else {
					view->frame.x = 0.f;
				}
			}
		}
	}
}


void  SuiLayout$LayoutLinear$setMainConstraints(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor, float  minV, float  maxV){
	if (isHor) {
		kidCtx->minWidth = minV;
		kidCtx->maxWidth = maxV;
	}
	else {
		kidCtx->minHeight = minV;
		kidCtx->maxHeight = maxV;
	}
}


void  SuiLayout$LayoutLinear$setCrossConstraints(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor, float  minV, float  maxV){
	if (!isHor) {
		kidCtx->minWidth = minV;
		kidCtx->maxWidth = maxV;
	}
	else {
		kidCtx->minHeight = 0.f;
		kidCtx->maxHeight = maxV;
	}
}


float  SuiLayout$LayoutLinear$getMainMaxConstraint(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor){
	if (isHor) {
		return kidCtx->maxWidth; 
	}
	return kidCtx->maxHeight; 
}


float  SuiLayout$LayoutLinear$getCrossMaxConstraint(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor){
	if (!isHor) {
		return kidCtx->maxWidth; 
	}
	return kidCtx->maxHeight; 
}


void  SuiLayout$LayoutLinear$update_maxCrossSize(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  kidCtx, bool  isHor){
	if (isHor) {
		self->maxCrossSize = Orc$maxFloat(kidCtx->height, self->maxCrossSize) ;
	}
	else {
		self->maxCrossSize = Orc$maxFloat(kidCtx->width, self->maxCrossSize) ;
	}
}


bool  SuiLayout$LayoutLinear$layout_mainInf(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx){
	bool  isHor = self->calcIsHor(self) ;
	bool  isMainInf = isHor ? ctx->maxWidth == INFINITY : ctx->maxHeight == INFINITY;
	bool  isCrossInf = !isHor ? ctx->maxWidth == INFINITY : ctx->maxHeight == INFINITY;
	if (!isMainInf) {
		return false; 
	}
	float  mainSize = 0.f;
	float  crossMinContraints = 0.f;
	if (self->isMax_in_maxOrStretch(self, ctx, isHor) ) {
		crossMinContraints = self->getCrossMaxConstraint(self, ctx, isHor) ;
	}
	for (int  i = 0; i < ((SuiCore$Node * )self)->getChildrenCount(self) ; i++) {
		SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (view && view->canLayoutByParent(view) ) {
			SuiLayout$LayoutLinearCell *  cell = (SuiLayout$LayoutLinearCell * )view->getLayoutCellByType(view, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ;
			SuiCore$Frame *  kidCtx = &view->frame;
			self->setMainConstraints(self, kidCtx, isHor, 0.f, INFINITY) ;
			self->setCrossConstraints(self, kidCtx, isHor, crossMinContraints, self->getCrossMaxConstraint(self, ctx, isHor) ) ;
			view->layout(view, kidCtx) ;
			mainSize = mainSize + (isHor ? kidCtx->width : kidCtx->height);
			self->update_maxCrossSize(self, kidCtx, isHor) ;
		}
	}
	SuiCore$Frame$clampWidth(ctx, isHor ? mainSize : self->maxCrossSize, ((SuiCore$View * )self)->minWidth, ((SuiCore$View * )self)->maxWidth) ;
	SuiCore$Frame$clampHeight(ctx, !isHor ? mainSize : self->maxCrossSize, ((SuiCore$View * )self)->minHeight, ((SuiCore$View * )self)->maxHeight) ;
	self->positionChildren(self, ctx) ;
	self->layoutCross(self, ctx) ;
	return true; 
}


bool  SuiLayout$LayoutLinear$layout_mainLimit(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx){
	bool  isHor = self->calcIsHor(self) ;
	float  maxMain = isHor ? ctx->maxWidth : ctx->maxHeight;
	URGC_VAR_CLEANUP_CLASS Orc$PointerArray*  growNodes = (growNodes=NULL,urgc_init_var_class((void**)&growNodes, Orc$PointerArray_new(&growNodes) ));
	float  sumGrow = 0.f;
	float  plainMainSum = 0.f;
	float  crossMinContraints = 0.f;
	if (self->isMax_in_maxOrStretch(self, ctx, isHor) ) {
		crossMinContraints = self->getCrossMaxConstraint(self, ctx, isHor) ;
	}
	for (int  i = 0; i < ((SuiCore$Node * )self)->getChildrenCount(self) ; i++) {
		SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (view && view->canLayoutByParent(view) ) {
			SuiLayout$LayoutLinearCell *  cell = (SuiLayout$LayoutLinearCell * )view->getLayoutCellByType(view, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ;
			if (cell) {
				if (cell->grow > 0.f) {
					sumGrow = sumGrow + cell->grow;
					growNodes->add(growNodes, (Object * )view) ;
					continue;
				}
			}
			SuiCore$Frame *  kidCtx = &view->frame;
			self->setMainConstraints(self, kidCtx, isHor, 0.f, INFINITY) ;
			self->setCrossConstraints(self, kidCtx, isHor, crossMinContraints, self->getCrossMaxConstraint(self, ctx, isHor) ) ;
			view->layout(view, kidCtx) ;
			plainMainSum = plainMainSum + (isHor ? kidCtx->width : kidCtx->height);
			self->update_maxCrossSize(self, kidCtx, isHor) ;
		}
	}
	float  remainMain = maxMain - plainMainSum;
	for (int  i = 0; i < growNodes->size(growNodes) ; i++) {
		SuiCore$ViewBase *  view = (SuiCore$ViewBase * )growNodes->get(growNodes, i) ;
		if (remainMain <= 0) {
			if (isHor) {
				view->frame.width = 0.f;
			}
			else {
				view->frame.height = 0.f;
			}
		}
		else {
			SuiLayout$LayoutLinearCell *  cell = (SuiLayout$LayoutLinearCell * )view->getLayoutCellByType(view, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ;
			float  ratio = cell->grow / sumGrow;
			float  mainSpace = remainMain * ratio;
			SuiCore$Frame *  kidCtx = &view->frame;
			self->setMainConstraints(self, kidCtx, isHor, mainSpace, mainSpace) ;
			self->setCrossConstraints(self, kidCtx, isHor, crossMinContraints, self->getCrossMaxConstraint(self, ctx, isHor) ) ;
			view->layout(view, kidCtx) ;
			self->update_maxCrossSize(self, kidCtx, isHor) ;
		}
	}
	float  mainSize = growNodes->size(growNodes)  > 0 ? maxMain : plainMainSum;
	ctx->width = Orc$clampFloat(isHor ? mainSize : self->maxCrossSize, ctx->minWidth, ctx->maxWidth) ;
	ctx->height = Orc$clampFloat(!isHor ? mainSize : self->maxCrossSize, ctx->minHeight, ctx->maxHeight) ;
	self->positionChildren(self, ctx) ;
	self->layoutCross(self, ctx) ;
	return true; 
}


void  SuiLayout$LayoutLinear$layoutContent(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx){
	if (self->layout_mainInf(self, ctx) ) {
		return ; 
	}
	self->layout_mainLimit(self, ctx) ;
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcc(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->justifyContent, "center") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcs(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->justifyContent, "start") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jce(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->justifyContent, "end") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcsb(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->justifyContent, "space-between") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcsa(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->justifyContent, "space-around") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$jcse(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->justifyContent, "space-evenly") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$ais(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->alignItems, "start") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$aic(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->alignItems, "center") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$aie(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->alignItems, "end") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$aiStretch(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->alignItems, "stretch") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$aiMaxOrStretch(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->alignItems, "maxOrStretch") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$column(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->direction, "column") ;
	return self; 
}


SuiLayout$LayoutLinear *  SuiLayout$LayoutLinear$row(SuiLayout$LayoutLinear *  self){
	Orc$String$set(self->direction, "row") ;
	return self; 
}


void  SuiLayout$LayoutLinear$layout(SuiLayout$LayoutLinear *  self, SuiCore$Frame *  ctx){
	self->maxCrossSize = 0.f;
	SuiCore$View$layout(self, ctx) ;
}



SuiLayout$LayoutLinear*  SuiLayout$layoutLinear(SuiLayout$LayoutLinear **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiLayout$LayoutLinear* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiLayout$LayoutLinear_init(NULL)) ) ; 
}

SuiLayout$LayoutLinearCell*  SuiLayout$layoutLinearCell(SuiLayout$LayoutLinearCell **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiLayout$LayoutLinearCell* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ) ; 
}



