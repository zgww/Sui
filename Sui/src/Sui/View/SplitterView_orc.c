
#include "SplitterView_orc.h" 

#include <stdio.h>
#include "../../Orc/String_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/Drag_orc.h"
#include "../View/ViewBuilder_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../SuiDesigner/Theme_orc.h"


// static struct 
typedef struct tagSuiView$__Block_30_15 SuiView$__Block_30_15;

typedef struct tagSuiView$__Closure_32_27 SuiView$__Closure_32_27;



struct tagSuiView$__Block_30_15 {
	SuiView$SplitterView*  self ;
};





struct tagSuiView$__Closure_32_27 {
	void  (*invoke)(SuiView$__Closure_32_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiView$__Block_30_15*  __var___Block_30_15 ;
};





// static function declaration
static void  __finiBlock___Block_30_15(SuiView$__Block_30_15 *  self);
static void  __fn___Closure_32_27(SuiView$__Closure_32_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_32_27(SuiView$__Closure_32_27 *  self);
static SuiView$__Closure_32_27*  __make___Closure_32_27(SuiView$__Closure_32_27 **  __outRef__, SuiView$__Block_30_15 *  __var___Block_30_15);



//vtable instance
Vtable_SuiView$SplitterView _vtable_SuiView$SplitterView;

// init meta

void SuiView$SplitterView_initMeta(Vtable_SuiView$SplitterView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiView$SplitterView, drag), true, false, 1);
	orc_metaField_primitive(&pNext, "hoverBg", OrcMetaType_int, offsetof(SuiView$SplitterView, hoverBg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "normalBg", OrcMetaType_int, offsetof(SuiView$SplitterView, normalBg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "prevGrow", OrcMetaType_float, offsetof(SuiView$SplitterView, prevGrow), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "nextGrow", OrcMetaType_float, offsetof(SuiView$SplitterView, nextGrow), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_SuiView$SplitterView* Vtable_SuiView$SplitterView_init(Vtable_SuiView$SplitterView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$SplitterView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$SplitterView_new;
    ((Vtable_Object*)pvt)->className = "SuiView$SplitterView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$SplitterView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$SplitterView_fini(SuiView$SplitterView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$SplitterView*)self)->drag);

}

// init fields function


void SuiView$SplitterView_init_fields(SuiView$SplitterView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$SplitterView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$SplitterView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	((SuiView$SplitterView*)self)->hoverBg = SuiDesigner$themeIns() ->dock_splitterBgHover;
	((SuiView$SplitterView*)self)->normalBg = SuiDesigner$themeIns() ->dock_splitterBg;
	((SuiView$SplitterView*)self)->prevGrow = 0;
	((SuiView$SplitterView*)self)->nextGrow = 0;
    }
	((Object*)self)->ctor = (void*)SuiView$SplitterView$ctor;
	((SuiCore$Node*)self)->react = (void*)SuiView$SplitterView$react;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$SplitterView$onEvent;
	((SuiCore$ViewBase*)self)->onHoverChanged = (void*)SuiView$SplitterView$onHoverChanged;
}

// init function

void SuiView$SplitterView_init(SuiView$SplitterView *self, void *pOwner){
    Vtable_SuiView$SplitterView_init(&_vtable_SuiView$SplitterView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$SplitterView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$SplitterView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$SplitterView * SuiView$SplitterView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$SplitterView *self = calloc(1, sizeof(SuiView$SplitterView));
	
    SuiView$SplitterView_init(self, pOwner);
    return self;
}


// class members
void  SuiView$SplitterView$ctor(SuiView$SplitterView *  self){
	URGC_VAR_CLEANUP SuiView$__Block_30_15*  __var___Block_30_15 = (__var___Block_30_15=NULL,urgc_init_var((void**)&__var___Block_30_15, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_30_15) , __finiBlock___Block_30_15) ));
	urgc_set_field_class(__var___Block_30_15, (void * )offsetof(SuiView$__Block_30_15, self) , self) ;
	((SuiCore$ViewBase * )self)->hitTestPadding = SuiCore$mkInset(3, 3, 3, 3) ;
	URGC_VAR_CLEANUP SuiView$__Closure_32_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_32_27(&tmpReturn_1, __var___Block_30_15) ) ;
}


void  SuiView$SplitterView$react(SuiView$SplitterView *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_1, "sizewe") ) ;
	((SuiCore$View * )self)->backgroundColor = ((SuiCore$ViewBase * )self)->hover ? self->hoverBg : self->normalBg;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


void  SuiView$SplitterView$onEvent(SuiView$SplitterView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		if (self->drag) {
			self->drag->onMouseDown(self->drag, (SuiCore$MouseEvent * )e) ;
		}
	}
}


void  SuiView$SplitterView$onHoverChanged(SuiView$SplitterView *  self){
	((SuiCore$Node * )self)->invalidReact(self) ;
}



static void  __finiBlock___Block_30_15(SuiView$__Block_30_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_30_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_32_27(SuiView$__Closure_32_27 *  self, SuiView$Drag *  d){
	SuiLayout$LayoutLinear *  ll = (SuiLayout$LayoutLinear * )((SuiCore$Node * )self->__var___Block_30_15->self)->parent;
	if (Orc_instanceof((Object*)ll, (Vtable_Object*)Vtable_SuiLayout$LayoutLinear_init(NULL))) {
		bool  isHor = ll->calcIsHor(ll) ;
		int  idx = ((SuiCore$Node * )self->__var___Block_30_15->self)->parent->indexOf(((SuiCore$Node * )self->__var___Block_30_15->self)->parent, self->__var___Block_30_15->self) ;
		if (idx == 0 || idx == ((SuiCore$Node * )self->__var___Block_30_15->self)->parent->getChildrenCount(((SuiCore$Node * )self->__var___Block_30_15->self)->parent)  - 1) {
			return ; 
		}
		SuiCore$ViewBase *  prev = (SuiCore$ViewBase * )((SuiCore$Node * )self->__var___Block_30_15->self)->parent->getChild(((SuiCore$Node * )self->__var___Block_30_15->self)->parent, idx - 1) ;
		SuiCore$ViewBase *  next = (SuiCore$ViewBase * )((SuiCore$Node * )self->__var___Block_30_15->self)->parent->getChild(((SuiCore$Node * )self->__var___Block_30_15->self)->parent, idx + 1) ;
		if (Orc_instanceof((Object*)prev, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL)) && Orc_instanceof((Object*)next, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
			SuiLayout$LayoutLinearCell *  prevCell = (SuiLayout$LayoutLinearCell * )((SuiCore$Node * )prev)->getChildByType(prev, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ;
			SuiLayout$LayoutLinearCell *  nextCell = (SuiLayout$LayoutLinearCell * )((SuiCore$Node * )next)->getChildByType(next, Vtable_SuiLayout$LayoutLinearCell_init(NULL)) ;
			if (prevCell && nextCell) {
				if (d->isDragStart) {
					if (isHor) {
						self->__var___Block_30_15->self->prevGrow = prev->frame.width;
						self->__var___Block_30_15->self->nextGrow = next->frame.width;
					}
					else {
						self->__var___Block_30_15->self->prevGrow = prev->frame.height;
						self->__var___Block_30_15->self->nextGrow = next->frame.height;
					}
				}
				if (d->isDragging) {
					if (isHor) {
						self->__var___Block_30_15->self->prevGrow += d->deltaPos.x;
						self->__var___Block_30_15->self->nextGrow -= d->deltaPos.x;
					}
					else {
						self->__var___Block_30_15->self->prevGrow += d->deltaPos.y;
						self->__var___Block_30_15->self->nextGrow -= d->deltaPos.y;
					}
					printf("更新Spliiter左右的cell.grow. :%f,%f\n", self->__var___Block_30_15->self->prevGrow, self->__var___Block_30_15->self->nextGrow) ;
					prevCell->grow = self->__var___Block_30_15->self->prevGrow;
					nextCell->grow = self->__var___Block_30_15->self->nextGrow;
				}
			}
		}
	}
}

static void  __fini___Closure_32_27(SuiView$__Closure_32_27 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_32_27, __var___Block_30_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_32_27*  __make___Closure_32_27(SuiView$__Closure_32_27 **  __outRef__, SuiView$__Block_30_15 *  __var___Block_30_15){
	URGC_VAR_CLEANUP SuiView$__Closure_32_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_32_27) , __fini___Closure_32_27) ));
	self->invoke = __fn___Closure_32_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_32_27, __var___Block_30_15) , __var___Block_30_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$SplitterView*  SuiView$mkSplitterView(SuiView$SplitterView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$SplitterView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$SplitterView_init(NULL)) ) ; 
}



