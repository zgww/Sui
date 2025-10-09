
#include "TableView_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include <math.h>
#include "../../Orc/List_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "./ViewBuilder_orc.h"
#include "./TextView_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiView$TableViewColumn _vtable_SuiView$TableViewColumn;

// init meta

void SuiView$TableViewColumn_initMeta(Vtable_SuiView$TableViewColumn *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "width", OrcMetaType_int, offsetof(SuiView$TableViewColumn, width), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "label", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$TableViewColumn, label), true, false, 1);

	
}


// vtable init


Vtable_SuiView$TableViewColumn* Vtable_SuiView$TableViewColumn_init(Vtable_SuiView$TableViewColumn* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$TableViewColumn;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$TableViewColumn_new;
    ((Vtable_Object*)pvt)->className = "SuiView$TableViewColumn";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$TableViewColumn_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$TableViewColumn_fini(SuiView$TableViewColumn *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$TableViewColumn*)self)->label);

}

// init fields function


void SuiView$TableViewColumn_init_fields(SuiView$TableViewColumn *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$TableViewColumn_fini;
	//fields
    {
	((SuiView$TableViewColumn*)self)->width = 200;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TableViewColumn*)self)->label, Orc$str(&tmpReturn_1, "") );
    }
	
}

// init function

void SuiView$TableViewColumn_init(SuiView$TableViewColumn *self, void *pOwner){
    Vtable_SuiView$TableViewColumn_init(&_vtable_SuiView$TableViewColumn);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$TableViewColumn;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$TableViewColumn_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$TableViewColumn * SuiView$TableViewColumn_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$TableViewColumn *self = calloc(1, sizeof(SuiView$TableViewColumn));
	
    SuiView$TableViewColumn_init(self, pOwner);
    return self;
}


// class members

SuiView$TableViewColumn*  SuiView$mkTableViewColumn(SuiView$TableViewColumn **  __outRef__, int  width, Orc$String*  label){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(label);

	URGC_VAR_CLEANUP_CLASS SuiView$TableViewColumn*  col = (col=NULL,urgc_init_var_class((void**)&col, SuiView$TableViewColumn_new(&col) ));
	col->width = width;
	urgc_set_field_class(col, (void * )offsetof(SuiView$TableViewColumn, label) , label) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, col) ; 
}


//vtable instance
Vtable_SuiView$TableView _vtable_SuiView$TableView;

// init meta

void SuiView$TableView_initMeta(Vtable_SuiView$TableView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "rowHeight", OrcMetaType_int, offsetof(SuiView$TableView, rowHeight), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "rowCount", OrcMetaType_int, offsetof(SuiView$TableView, rowCount), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "columns", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiView$TableView, columns), true, false, 1);
	orc_metaField_primitive(&pNext, "hoverRow", OrcMetaType_int, offsetof(SuiView$TableView, hoverRow), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "hoverCol", OrcMetaType_int, offsetof(SuiView$TableView, hoverCol), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "hoverStartX", OrcMetaType_int, offsetof(SuiView$TableView, hoverStartX), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "hoverEndX", OrcMetaType_int, offsetof(SuiView$TableView, hoverEndX), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "renderHead", offsetof(SuiView$TableView, renderHead));
	orc_metaField_method(&pNext, "renderBody", offsetof(SuiView$TableView, renderBody));
	orc_metaField_method(&pNext, "onMouseEvent", offsetof(SuiView$TableView, onMouseEvent));
}


// vtable init


Vtable_SuiView$TableView* Vtable_SuiView$TableView_init(Vtable_SuiView$TableView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$TableView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$TableView_new;
    ((Vtable_Object*)pvt)->className = "SuiView$TableView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$TableView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$TableView_fini(SuiView$TableView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$TableView*)self)->columns);

}

// init fields function


void SuiView$TableView_init_fields(SuiView$TableView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$TableView_fini;
	//fields
    {
	urgc_set_field(self, (void**)&((SuiView$TableView*)self)->renderTh, NULL);
	urgc_set_field(self, (void**)&((SuiView$TableView*)self)->renderTd, NULL);
	((SuiView$TableView*)self)->rowHeight = 20;
	((SuiView$TableView*)self)->rowCount = 0;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TableView*)self)->columns, Orc$List_new(&tmpNewOwner_1) );
	((SuiView$TableView*)self)->hoverRow = -1;
	((SuiView$TableView*)self)->hoverCol = -1;
	((SuiView$TableView*)self)->hoverStartX = 0;
	((SuiView$TableView*)self)->hoverEndX = 0;
    }
	((SuiCore$Node*)self)->react = (void*)SuiView$TableView$react;
	((SuiView$TableView*)self)->renderHead = (void*)SuiView$TableView$renderHead;
	((SuiView$TableView*)self)->renderBody = (void*)SuiView$TableView$renderBody;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$TableView$draw_self;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$TableView$onEvent;
	((SuiView$TableView*)self)->onMouseEvent = (void*)SuiView$TableView$onMouseEvent;
}

// init function

void SuiView$TableView_init(SuiView$TableView *self, void *pOwner){
    Vtable_SuiView$TableView_init(&_vtable_SuiView$TableView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$TableView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$TableView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$TableView * SuiView$TableView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$TableView *self = calloc(1, sizeof(SuiView$TableView));
	
    SuiView$TableView_init(self, pOwner);
    return self;
}


// class members
void  SuiView$TableView$react(SuiView$TableView *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_1, "column") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_2, "start") ) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiCore$Node *  o = (SuiCore$Node * )self;
	self->renderHead(self) ;
	self->renderBody(self) ;
	((SuiCore$Node * )self)->endInnerReact(self) ;
	((SuiCore$View * )self)->height = self->rowHeight * (self->rowCount + 1);
}


void  SuiView$TableView$renderHead(SuiView$TableView *  self){
	SuiCore$Node *  o = (SuiCore$Node * )self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_58_2 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_58_2;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_58_2 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->height = self->rowHeight;
		Orc$String$set(o->direction, "row") ;
		int  l = self->columns->size(self->columns) ;
		for (int  i = 0; i < l; i++) {
			SuiView$TableViewColumn *  col = (SuiView$TableViewColumn * )self->columns->get(self->columns, i) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_2 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_65_4 = SuiLayout$layoutLinear(&tmpReturn_2, o, i) , *o = __scopeVar_65_4;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_65_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				Orc$String$set(o->direction, "row") ;
				Orc$String$set(o->justifyContent, "center") ;
				((SuiCore$View * )o)->width = col->width;
				((SuiCore$View * )o)->height = self->rowHeight;
				((SuiCore$View * )o)->padding.right = 5;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_3 = NULL;
				{
					SuiView$TextView*  __scopeVar_72_5 = SuiView$mkTextView(&tmpReturn_3, o, 0) , *o = __scopeVar_72_5;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_72_5 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->setColor(o, 0xffffffff) ;
					o->setText(o, col->label) ;
				}
			}
		}
	}
}


void  SuiView$TableView$renderBody(SuiView$TableView *  self){
	SuiCore$Node *  o = (SuiCore$Node * )self;
	for (int  r = 0; r < self->rowCount; r++) {
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_83_3 = SuiLayout$layoutLinear(&tmpReturn_1, o, r) , *o = __scopeVar_83_3;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_83_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->height = self->rowHeight;
			Orc$String$set(o->direction, "row") ;
			((SuiCore$View * )o)->backgroundColor = 0x3300ffff;
			int  l = self->columns->size(self->columns) ;
			for (int  i = 0; i < l; i++) {
				SuiView$TableViewColumn *  col = (SuiView$TableViewColumn * )self->columns->get(self->columns, i) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_2 = NULL;
				{
					SuiLayout$LayoutLinear*  __scopeVar_93_5 = SuiLayout$layoutLinear(&tmpReturn_2, o, i) , *o = __scopeVar_93_5;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_93_5 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					((SuiCore$View * )o)->backgroundColor = 0x33ffff00;
					Orc$String$set(o->direction, "row") ;
					Orc$String$set(o->justifyContent, "center") ;
					((SuiCore$View * )o)->width = col->width;
					((SuiCore$View * )o)->height = self->rowHeight;
					((SuiCore$View * )o)->padding.right = 5;
					if (self->renderTd != NULL) {
						(*(self->renderTd))((void * )(self->renderTd), o, r, i) ;
					}
					else {
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_3 = NULL;
						{
							SuiView$TextView*  __scopeVar_105_7 = SuiView$mkTextView(&tmpReturn_3, o, i) , *o = __scopeVar_105_7;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_105_7 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->setColor(o, 0xffffffff) ;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
							o->setText(o, Orc$str(&tmpReturn_4, "-") ) ;
						}
					}
				}
			}
		}
	}
}


void  SuiView$TableView$draw_self(SuiView$TableView *  self, SuiCore$Canvas *  canvas){
	SuiCore$View$draw_self(self, canvas) ;
	SuiCore$Rect r = ((SuiCore$View * )self)->getContentRect_baseViewRect(self) ;
	int  w = r.w;
	int  h = r.h;
	SuiCore$Canvas$save(canvas) ;
	SuiCore$Canvas$translate(canvas, r.x, r.y) ;
	SuiCore$Canvas$strokeWidth(canvas, 1) ;
	SuiCore$Canvas$strokeColor(canvas, 255, 255, 255, 128) ;
	SuiCore$Canvas$beginPath(canvas) ;
	int  colX = 0;
	int  l = self->columns->size(self->columns) ;
	for (int  i = 0; i < l - 1; i++) {
		SuiView$TableViewColumn *  col = (SuiView$TableViewColumn * )self->columns->get(self->columns, i) ;
		colX = colX + col->width;
		SuiCore$Canvas$moveTo(canvas, colX, 0) ;
		SuiCore$Canvas$lineTo(canvas, colX, h) ;
	}
	int  maxRow = ceil(h / self->rowHeight) ;
	int  rowToDraw = Orc$maxInt(maxRow, self->rowCount) ;
	for (int  r = 0; r < rowToDraw + 1; r++) {
		int  y = r * self->rowHeight;
		SuiCore$Canvas$moveTo(canvas, 0, y) ;
		SuiCore$Canvas$lineTo(canvas, w, y) ;
	}
	SuiCore$Canvas$stroke(canvas) ;
	SuiCore$Canvas$fillColor(canvas, 255, 255, 255, 16) ;
	SuiCore$Canvas$beginPath(canvas) ;
	for (int  r = 0; r < rowToDraw + 1; ) {
		int  y = r * self->rowHeight;
		SuiCore$Canvas$rect(canvas, 0, y, w, self->rowHeight) ;
		r = r + 2;
	}
	SuiCore$Canvas$fill(canvas) ;
	if (self->hoverRow != -1) {
		SuiCore$Canvas$fillColor(canvas, 255, 255, 255, 32) ;
		SuiCore$Canvas$beginPath(canvas) ;
		int  y = self->hoverRow * self->rowHeight;
		SuiCore$Canvas$rect(canvas, 0, y, w, self->rowHeight) ;
		SuiCore$Canvas$fill(canvas) ;
	}
	if (self->hoverCol != -1) {
		SuiCore$Canvas$fillColor(canvas, 255, 255, 255, 32) ;
		SuiCore$Canvas$beginPath(canvas) ;
		int  y = self->hoverRow * self->rowHeight;
		SuiCore$Canvas$rect(canvas, self->hoverStartX, 0, self->hoverEndX - self->hoverStartX, h) ;
		SuiCore$Canvas$fill(canvas) ;
	}
	SuiCore$Canvas$restore(canvas) ;
}


void  SuiView$TableView$onEvent(SuiView$TableView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		self->onMouseEvent(self, (SuiCore$MouseEvent * )e) ;
	}
}


void  SuiView$TableView$onMouseEvent(SuiView$TableView *  self, SuiCore$MouseEvent *  e){
	if (e->isMouseMove) {
		printf("mouse move TableView\n") ;
		SuiCore$Rect r = ((SuiCore$View * )self)->getContentClientRect(self) ;
		float  dy = e->clientY - r.y;
		float  dx = e->clientX - r.x;
		int  row = floor(dy / self->rowHeight) ;
		if (self->hoverRow != row && row >= 0 && row <= self->rowCount) {
			self->hoverRow = row;
			((SuiCore$ViewBase * )self)->invalidDraw(self) ;
		}
		int  col = -1;
		int  colX = 0;
		int  endX = 0;
		int  l = self->columns->size(self->columns) ;
		for (int  i = 0; i < l; i++) {
			SuiView$TableViewColumn *  column = (SuiView$TableViewColumn * )self->columns->get(self->columns, i) ;
			endX = colX + column->width;
			if (colX <= dx && dx < endX) {
				col = i;
				break;
			}
			colX = endX;
		}
		if (self->hoverCol != col && col >= 0 && col < self->columns->size(self->columns) ) {
			self->hoverCol = col;
			self->hoverStartX = colX;
			self->hoverEndX = endX;
			((SuiCore$ViewBase * )self)->invalidDraw(self) ;
		}
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseLeaveEvent_init(NULL))) {
		self->hoverRow = -1;
	}
}



SuiView$TableView*  SuiView$mkTableView(SuiView$TableView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$TableView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$TableView_init(NULL)) ) ; 
}



