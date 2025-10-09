
#include "RowWrap_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
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
Vtable_SuiLayout$RowWrap _vtable_SuiLayout$RowWrap;

// init meta

void SuiLayout$RowWrap_initMeta(Vtable_SuiLayout$RowWrap *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "alignItems", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiLayout$RowWrap, alignItems), true, false, 1);
	orc_metaField_primitive(&pNext, "rowGap", OrcMetaType_float, offsetof(SuiLayout$RowWrap, rowGap), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "colGap", OrcMetaType_float, offsetof(SuiLayout$RowWrap, colGap), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "alignItems_ofRow", offsetof(SuiLayout$RowWrap, alignItems_ofRow));
	orc_metaField_method(&pNext, "positionChildren", offsetof(SuiLayout$RowWrap, positionChildren));
}


// vtable init


Vtable_SuiLayout$RowWrap* Vtable_SuiLayout$RowWrap_init(Vtable_SuiLayout$RowWrap* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$RowWrap;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$RowWrap_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$RowWrap";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$RowWrap_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiLayout$RowWrap_fini(SuiLayout$RowWrap *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiLayout$RowWrap*)self)->alignItems);

}

// init fields function


void SuiLayout$RowWrap_init_fields(SuiLayout$RowWrap *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiLayout$RowWrap_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiLayout$RowWrap*)self)->alignItems, Orc$str(&tmpReturn_1, "center") );
	((SuiLayout$RowWrap*)self)->rowGap = 0.f;
	((SuiLayout$RowWrap*)self)->colGap = 0.f;
    }
	((SuiLayout$RowWrap*)self)->alignItems_ofRow = (void*)SuiLayout$RowWrap$alignItems_ofRow;
	((SuiLayout$RowWrap*)self)->positionChildren = (void*)SuiLayout$RowWrap$positionChildren;
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiLayout$RowWrap$layoutContent;
}

// init function

void SuiLayout$RowWrap_init(SuiLayout$RowWrap *self, void *pOwner){
    Vtable_SuiLayout$RowWrap_init(&_vtable_SuiLayout$RowWrap);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$RowWrap;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$RowWrap_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$RowWrap * SuiLayout$RowWrap_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$RowWrap *self = calloc(1, sizeof(SuiLayout$RowWrap));
	
    SuiLayout$RowWrap_init(self, pOwner);
    return self;
}


// class members
void  SuiLayout$RowWrap$alignItems_ofRow(SuiLayout$RowWrap *  self, int  rowStartIdx, int  rowEndIdx, float  rowHeight){
	if (Orc$String$equals(self->alignItems, "start") ) {
		return ; 
	}
	bool  center = Orc$String$equals(self->alignItems, "center") ;
	bool  end = Orc$String$equals(self->alignItems, "end") ;
	for (int  i = rowStartIdx; i < rowEndIdx; i++) {
		SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (view && view->canLayoutByParent(view) ) {
			if (center) {
				view->frame.y = view->frame.y + (rowHeight - view->frame.height) / 2.f;
			}
			else if (end) {
				view->frame.y = view->frame.y + (rowHeight - view->frame.height);
			}
		}
	}
}


void  SuiLayout$RowWrap$positionChildren(SuiLayout$RowWrap *  self, SuiCore$Frame *  ctx){
	SuiCore$Rect contentRect = ((SuiCore$View * )self)->getContentLocalRect(self) ;
	float  x = 0.f;
	float  y = 0.f;
	float  rowHeight = 0.f;
	float  rowStartIdx = 0;
	float  maxWidth = 0.f;
	for (int  i = 0; i < ((SuiCore$Node * )self)->getChildrenCount(self) ; i++) {
		SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (view && view->canLayoutByParent(view) ) {
			SuiCore$Frame *  lc = &view->frame;
			if (x + lc->width > ctx->maxWidth) {
				self->alignItems_ofRow(self, rowStartIdx, i, rowHeight) ;
				y = y + rowHeight + self->rowGap;
				x = 0.f;
				rowStartIdx = i;
				rowHeight = 0.f;
			}
			lc->x = x + contentRect.x;
			lc->y = y + contentRect.y;
			x = x + lc->width + self->colGap;
			maxWidth = Orc$maxFloat(x, maxWidth) ;
			rowHeight = Orc$maxFloat(rowHeight, lc->height) ;
		}
	}
	self->alignItems_ofRow(self, rowStartIdx, ((SuiCore$Node * )self)->getChildrenCount(self) , rowHeight) ;
	SuiCore$Frame$setSize(ctx, maxWidth, y + rowHeight) ;
}


void  SuiLayout$RowWrap$layoutContent(SuiLayout$RowWrap *  self, SuiCore$Frame *  contentCtx){
	for (int  i = 0; i < ((SuiCore$Node * )self)->getChildrenCount(self) ; i++) {
		SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (view && view->canLayoutByParent(view) ) {
			SuiCore$Frame *  kidCtx = &view->frame;
			kidCtx->maxWidth = INFINITY;
			kidCtx->maxHeight = INFINITY;
			view->layout(view, kidCtx) ;
		}
	}
	self->positionChildren(self, contentCtx) ;
}



SuiLayout$RowWrap*  SuiLayout$mkRowWrap(SuiLayout$RowWrap **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiLayout$RowWrap* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiLayout$RowWrap_init(NULL)) ) ; 
}



