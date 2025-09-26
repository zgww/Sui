
#include "Gizmo_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./RegisterNodes_orc.h"
#include "./DrawDegree_orc.h"
#include "./UiAction_orc.h"
#include "./ANode_orc.h"
#include "./EditCtx_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./EventFileItemChanged_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_80_15 SuiDesigner$__Block_80_15;

typedef struct tagSuiDesigner$__Block_151_27 SuiDesigner$__Block_151_27;

typedef struct tagSuiDesigner$__Closure_82_27 SuiDesigner$__Closure_82_27;

typedef struct tagSuiDesigner$__Closure_152_22 SuiDesigner$__Closure_152_22;



struct tagSuiDesigner$__Block_80_15 {
	SuiDesigner$GizmoRectView*  self ;
};





struct tagSuiDesigner$__Block_151_27 {
	SuiDesigner$GizmoRectView*  self ;
	SuiCore$View*  v ;
};





struct tagSuiDesigner$__Closure_82_27 {
	void  (*invoke)(SuiDesigner$__Closure_82_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_80_15*  __var___Block_80_15 ;
};





struct tagSuiDesigner$__Closure_152_22 {
	void  (*invoke)(SuiDesigner$__Closure_152_22 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_151_27*  __var___Block_151_27 ;
};





// static function declaration
static void  __finiBlock___Block_80_15(SuiDesigner$__Block_80_15 *  self);
static void  __finiBlock___Block_151_27(SuiDesigner$__Block_151_27 *  self);
static void  __fn___Closure_82_27(SuiDesigner$__Closure_82_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_82_27(SuiDesigner$__Closure_82_27 *  self);
static SuiDesigner$__Closure_82_27*  __make___Closure_82_27(SuiDesigner$__Closure_82_27 **  __outRef__, SuiDesigner$__Block_80_15 *  __var___Block_80_15);
static void  __fn___Closure_152_22(SuiDesigner$__Closure_152_22 *  self, SuiCore$Event *  e);
static void  __fini___Closure_152_22(SuiDesigner$__Closure_152_22 *  self);
static SuiDesigner$__Closure_152_22*  __make___Closure_152_22(SuiDesigner$__Closure_152_22 **  __outRef__, SuiDesigner$__Block_151_27 *  __var___Block_151_27);



//vtable instance
Vtable_SuiDesigner$GizmoRectView _vtable_SuiDesigner$GizmoRectView;

// init meta

void SuiDesigner$GizmoRectView_initMeta(Vtable_SuiDesigner$GizmoRectView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "targetRect", SuiCore$Rect_getOrInitMetaStruct(), offsetof(SuiDesigner$GizmoRectView, targetRect), false, false, 0);
	orc_metaField_class(&pNext, "lt", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiDesigner$GizmoRectView, lt), false, true, 1);
	orc_metaField_class(&pNext, "rt", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiDesigner$GizmoRectView, rt), false, true, 1);
	orc_metaField_class(&pNext, "rb", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiDesigner$GizmoRectView, rb), false, true, 1);
	orc_metaField_class(&pNext, "lb", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiDesigner$GizmoRectView, lb), false, true, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$GizmoRectView, drag), true, false, 1);
	orc_metaField_struct(&pNext, "_tmpRect", SuiCore$Rect_getOrInitMetaStruct(), offsetof(SuiDesigner$GizmoRectView, _tmpRect), false, false, 0);

	orc_metaField_method(&pNext, "bindEvent", offsetof(SuiDesigner$GizmoRectView, bindEvent));
}


// vtable init


Vtable_SuiDesigner$GizmoRectView* Vtable_SuiDesigner$GizmoRectView_init(Vtable_SuiDesigner$GizmoRectView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$GizmoRectView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$GizmoRectView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$GizmoRectView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$GizmoRectView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$GizmoRectView_fini(SuiDesigner$GizmoRectView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiDesigner$GizmoRectView_init_fields(SuiDesigner$GizmoRectView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$GizmoRectView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$GizmoRectView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	urgc_set_field(self, (void**)&((SuiDesigner$GizmoRectView*)self)->onRectChanged, NULL);
    }
	((SuiCore$ViewBase*)self)->layout = (void*)SuiDesigner$GizmoRectView$layout;
	((Object*)self)->ctor = (void*)SuiDesigner$GizmoRectView$ctor;
	((SuiCore$Node*)self)->react = (void*)SuiDesigner$GizmoRectView$react;
	((SuiDesigner$GizmoRectView*)self)->bindEvent = (void*)SuiDesigner$GizmoRectView$bindEvent;
}

// init function

void SuiDesigner$GizmoRectView_init(SuiDesigner$GizmoRectView *self, void *pOwner){
    Vtable_SuiDesigner$GizmoRectView_init(&_vtable_SuiDesigner$GizmoRectView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$GizmoRectView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$GizmoRectView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$GizmoRectView * SuiDesigner$GizmoRectView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$GizmoRectView *self = calloc(1, sizeof(SuiDesigner$GizmoRectView));
	
    SuiDesigner$GizmoRectView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$GizmoRectView$layout(SuiDesigner$GizmoRectView *  self, SuiCore$Frame *  ctx){
	
}


void  SuiDesigner$GizmoRectView$ctor(SuiDesigner$GizmoRectView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_80_15*  __var___Block_80_15 = (__var___Block_80_15=NULL,urgc_init_var((void**)&__var___Block_80_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_80_15) , __finiBlock___Block_80_15) ));
	urgc_set_field_class(__var___Block_80_15, (void * )offsetof(SuiDesigner$__Block_80_15, self) , self) ;
	SuiCore$Listener$ctor(self) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_82_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_82_27(&tmpReturn_1, __var___Block_80_15) ) ;
}


void  SuiDesigner$GizmoRectView$react(SuiDesigner$GizmoRectView *  self){
	SuiCore$Rect r = self->targetRect;
	SuiCore$View *  o = (SuiCore$View * )self;
	o->border->setAll(o->border, 1, 0xffffff) ;
	o->backgroundColor = 0x320088ff;
	((SuiCore$ViewBase * )o)->frame.width = self->targetRect.w;
	((SuiCore$ViewBase * )o)->frame.height = self->targetRect.h;
	((SuiCore$ViewBase * )o)->frame.x = r.x;
	((SuiCore$ViewBase * )o)->frame.y = r.y;
	((SuiCore$Node * )o)->startInnerReact(o) ;
	self->lt = SuiDesigner$Gizmo_reactRect(o, 0, 0, 0) ;
	self->rt = SuiDesigner$Gizmo_reactRect(o, r.w, 0, 1) ;
	self->rb = SuiDesigner$Gizmo_reactRect(o, r.w, r.h, 2) ;
	self->lb = SuiDesigner$Gizmo_reactRect(o, 0, r.h, 3) ;
	self->bindEvent(self, self->lt) ;
	self->bindEvent(self, self->rt) ;
	self->bindEvent(self, self->rb) ;
	self->bindEvent(self, self->lb) ;
	((SuiCore$Node * )o)->endInnerReact(o) ;
}


void  SuiDesigner$GizmoRectView$bindEvent(SuiDesigner$GizmoRectView *  self, SuiCore$View*  v){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(v);

	URGC_VAR_CLEANUP SuiDesigner$__Block_151_27*  __var___Block_151_27 = (__var___Block_151_27=NULL,urgc_init_var((void**)&__var___Block_151_27, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_151_27) , __finiBlock___Block_151_27) ));
	urgc_set_field_class(__var___Block_151_27, (void * )offsetof(SuiDesigner$__Block_151_27, v) , v) ;
	urgc_set_field_class(__var___Block_151_27, (void * )offsetof(SuiDesigner$__Block_151_27, self) , self) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_152_22*  tmpReturn_1 = NULL;
	urgc_set_field(__var___Block_151_27->v, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_152_22(&tmpReturn_1, __var___Block_151_27) ) ;
}



static void  __finiBlock___Block_80_15(SuiDesigner$__Block_80_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_80_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_151_27(SuiDesigner$__Block_151_27 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_151_27, self) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_151_27, v) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_82_27(SuiDesigner$__Closure_82_27 *  self, SuiView$Drag *  d){
	if (d->isDragStart) {
		self->__var___Block_80_15->self->_tmpRect = self->__var___Block_80_15->self->targetRect;
	}
	if (d->isDragging) {
		SuiCore$Rect *  r = &self->__var___Block_80_15->self->_tmpRect;
		if (d->data == self->__var___Block_80_15->self->lt) {
			r->x += d->deltaPos.x;
			r->y += d->deltaPos.y;
			r->w -= d->deltaPos.x;
			r->h -= d->deltaPos.y;
		}
		if (d->data == self->__var___Block_80_15->self->rt) {
			r->y += d->deltaPos.y;
			r->w += d->deltaPos.x;
			r->h -= d->deltaPos.y;
		}
		if (d->data == self->__var___Block_80_15->self->rb) {
			r->w += d->deltaPos.x;
			r->h += d->deltaPos.y;
		}
		if (d->data == self->__var___Block_80_15->self->lb) {
			r->x += d->deltaPos.x;
			r->w -= d->deltaPos.x;
			r->h += d->deltaPos.y;
		}
		printf("on drag========================================rect:%f,%f,%f,%f\n", r->x, r->y, r->w, r->h) ;
		if (self->__var___Block_80_15->self->onRectChanged) {
			(*(self->__var___Block_80_15->self->onRectChanged))((void * )(self->__var___Block_80_15->self->onRectChanged), *r) ;
		}
	}
}

static void  __fini___Closure_82_27(SuiDesigner$__Closure_82_27 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_82_27, __var___Block_80_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_82_27*  __make___Closure_82_27(SuiDesigner$__Closure_82_27 **  __outRef__, SuiDesigner$__Block_80_15 *  __var___Block_80_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_82_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_82_27) , __fini___Closure_82_27) ));
	self->invoke = __fn___Closure_82_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_82_27, __var___Block_80_15) , __var___Block_80_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_152_22(SuiDesigner$__Closure_152_22 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && ((SuiCore$ViewEvent * )me)->isCapture && me->isMouseDown) {
			urgc_set_field_class(self->__var___Block_151_27->self->drag, (void * )offsetof(SuiView$Drag, data) , self->__var___Block_151_27->v) ;
			self->__var___Block_151_27->self->drag->onMouseDown(self->__var___Block_151_27->self->drag, me) ;
		}
	}
}

static void  __fini___Closure_152_22(SuiDesigner$__Closure_152_22 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_152_22, __var___Block_151_27) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_152_22*  __make___Closure_152_22(SuiDesigner$__Closure_152_22 **  __outRef__, SuiDesigner$__Block_151_27 *  __var___Block_151_27){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_152_22*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_152_22) , __fini___Closure_152_22) ));
	self->invoke = __fn___Closure_152_22;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_152_22, __var___Block_151_27) , __var___Block_151_27) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiCore$View *  SuiDesigner$Gizmo_reactRect(SuiCore$Node *  o, float  x, float  y, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_1 = NULL;
	{
		SuiCore$View*  __scopeVar_174_4 = SuiView$mkView(&tmpReturn_1, o, key) , *o = __scopeVar_174_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_174_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->width = 8;
		o->height = 8;
		((SuiCore$ViewBase * )o)->frame.width = 8;
		((SuiCore$ViewBase * )o)->frame.height = 8;
		((SuiCore$ViewBase * )o)->frame.x = x - o->width / 2 - 1;
		((SuiCore$ViewBase * )o)->frame.y = y - o->height / 2 - 1;
		o->backgroundColor = 0xaaeeeeff;
		Orc$String$set(((SuiCore$ViewBase * )o)->cursor, "pointer") ;
		o->border->setAll(o->border, 1, 0xffffffff) ;
		return o; 
	}
}

SuiDesigner$GizmoRectView*  SuiDesigner$mkGizmoRectView(SuiDesigner$GizmoRectView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$GizmoRectView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiDesigner$GizmoRectView_init(NULL)) ) ; 
}



