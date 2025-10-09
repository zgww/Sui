
#include "BezierEditView_orc.h" 

#include "../nanovg/nanovg.h"
#include <stdio.h>
#include "../Orc/String_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Bezier_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_66_15 SuiDesigner$__Block_66_15;

typedef struct tagSuiDesigner$__Block_122_16 SuiDesigner$__Block_122_16;

typedef struct tagSuiDesigner$__Closure_67_27 SuiDesigner$__Closure_67_27;

typedef struct tagSuiDesigner$__Closure_133_26 SuiDesigner$__Closure_133_26;

typedef struct tagSuiDesigner$__Closure_144_26 SuiDesigner$__Closure_144_26;

typedef struct tagSuiDesigner$__Closure_155_26 SuiDesigner$__Closure_155_26;

typedef struct tagSuiDesigner$__Closure_165_26 SuiDesigner$__Closure_165_26;



struct tagSuiDesigner$__Block_66_15 {
	SuiDesigner$BezierEditView*  self ;
};





struct tagSuiDesigner$__Block_122_16 {
	SuiDesigner$BezierEditView*  self ;
};





struct tagSuiDesigner$__Closure_67_27 {
	void  (*invoke)(SuiDesigner$__Closure_67_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_66_15*  __var___Block_66_15 ;
};





struct tagSuiDesigner$__Closure_133_26 {
	void  (*invoke)(SuiDesigner$__Closure_133_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_122_16*  __var___Block_122_16 ;
};





struct tagSuiDesigner$__Closure_144_26 {
	void  (*invoke)(SuiDesigner$__Closure_144_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_122_16*  __var___Block_122_16 ;
};





struct tagSuiDesigner$__Closure_155_26 {
	void  (*invoke)(SuiDesigner$__Closure_155_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_122_16*  __var___Block_122_16 ;
};





struct tagSuiDesigner$__Closure_165_26 {
	void  (*invoke)(SuiDesigner$__Closure_165_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_122_16*  __var___Block_122_16 ;
};





// static function declaration
static void  __finiBlock___Block_66_15(SuiDesigner$__Block_66_15 *  self);
static void  __finiBlock___Block_122_16(SuiDesigner$__Block_122_16 *  self);
static void  __fn___Closure_67_27(SuiDesigner$__Closure_67_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_67_27(SuiDesigner$__Closure_67_27 *  self);
static SuiDesigner$__Closure_67_27*  __make___Closure_67_27(SuiDesigner$__Closure_67_27 **  __outRef__, SuiDesigner$__Block_66_15 *  __var___Block_66_15);
static void  __fn___Closure_133_26(SuiDesigner$__Closure_133_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_133_26(SuiDesigner$__Closure_133_26 *  self);
static SuiDesigner$__Closure_133_26*  __make___Closure_133_26(SuiDesigner$__Closure_133_26 **  __outRef__, SuiDesigner$__Block_122_16 *  __var___Block_122_16);
static void  __fn___Closure_144_26(SuiDesigner$__Closure_144_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_144_26(SuiDesigner$__Closure_144_26 *  self);
static SuiDesigner$__Closure_144_26*  __make___Closure_144_26(SuiDesigner$__Closure_144_26 **  __outRef__, SuiDesigner$__Block_122_16 *  __var___Block_122_16);
static void  __fn___Closure_155_26(SuiDesigner$__Closure_155_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_155_26(SuiDesigner$__Closure_155_26 *  self);
static SuiDesigner$__Closure_155_26*  __make___Closure_155_26(SuiDesigner$__Closure_155_26 **  __outRef__, SuiDesigner$__Block_122_16 *  __var___Block_122_16);
static void  __fn___Closure_165_26(SuiDesigner$__Closure_165_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_165_26(SuiDesigner$__Closure_165_26 *  self);
static SuiDesigner$__Closure_165_26*  __make___Closure_165_26(SuiDesigner$__Closure_165_26 **  __outRef__, SuiDesigner$__Block_122_16 *  __var___Block_122_16);



//vtable instance
Vtable_SuiDesigner$BezierEditView _vtable_SuiDesigner$BezierEditView;

// init meta

void SuiDesigner$BezierEditView_initMeta(Vtable_SuiDesigner$BezierEditView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "start", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiDesigner$BezierEditView, start), false, false, 0);
	orc_metaField_struct(&pNext, "c0", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiDesigner$BezierEditView, c0), false, false, 0);
	orc_metaField_struct(&pNext, "c1", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiDesigner$BezierEditView, c1), false, false, 0);
	orc_metaField_struct(&pNext, "end", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiDesigner$BezierEditView, end), false, false, 0);
	orc_metaField_class(&pNext, "startView", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiDesigner$BezierEditView, startView), true, false, 1);
	orc_metaField_class(&pNext, "c0View", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiDesigner$BezierEditView, c0View), true, false, 1);
	orc_metaField_class(&pNext, "c1View", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiDesigner$BezierEditView, c1View), true, false, 1);
	orc_metaField_class(&pNext, "endView", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiDesigner$BezierEditView, endView), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$BezierEditView, drag), true, false, 1);
	orc_metaField_primitive(&pNext, "indicatorSize", OrcMetaType_float, offsetof(SuiDesigner$BezierEditView, indicatorSize), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "setBezier", offsetof(SuiDesigner$BezierEditView, setBezier));
	orc_metaField_method(&pNext, "getBezier", offsetof(SuiDesigner$BezierEditView, getBezier));
	orc_metaField_method(&pNext, "fire_onChanged", offsetof(SuiDesigner$BezierEditView, fire_onChanged));
	orc_metaField_method(&pNext, "_onIndicatorEvent", offsetof(SuiDesigner$BezierEditView, _onIndicatorEvent));
}


// vtable init


Vtable_SuiDesigner$BezierEditView* Vtable_SuiDesigner$BezierEditView_init(Vtable_SuiDesigner$BezierEditView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$BezierEditView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$BezierEditView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$BezierEditView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$BezierEditView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$BezierEditView_fini(SuiDesigner$BezierEditView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->startView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->c0View);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->c1View);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->endView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->drag);

}

// init fields function


void SuiDesigner$BezierEditView_init_fields(SuiDesigner$BezierEditView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$BezierEditView_fini;
	//fields
    {
	((SuiDesigner$BezierEditView*)self)->start = SuiCore$mkVec2(0.0, 0.0) ;
	((SuiDesigner$BezierEditView*)self)->c0 = SuiCore$mkVec2(0.25, 0.5) ;
	((SuiDesigner$BezierEditView*)self)->c1 = SuiCore$mkVec2(0.75, 0.5) ;
	((SuiDesigner$BezierEditView*)self)->end = SuiCore$mkVec2(1.0, 1.0) ;
	urgc_set_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->startView, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->c0View, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->c1View, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->endView, NULL);
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$BezierEditView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	urgc_set_field(self, (void**)&((SuiDesigner$BezierEditView*)self)->onChanged, NULL);
	((SuiDesigner$BezierEditView*)self)->indicatorSize = 12;
    }
	((SuiDesigner$BezierEditView*)self)->setBezier = (void*)SuiDesigner$BezierEditView$setBezier;
	((SuiDesigner$BezierEditView*)self)->getBezier = (void*)SuiDesigner$BezierEditView$getBezier;
	((SuiDesigner$BezierEditView*)self)->fire_onChanged = (void*)SuiDesigner$BezierEditView$fire_onChanged;
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiDesigner$BezierEditView$layoutContent;
	((Object*)self)->ctor = (void*)SuiDesigner$BezierEditView$ctor;
	((SuiDesigner$BezierEditView*)self)->_onIndicatorEvent = (void*)SuiDesigner$BezierEditView$_onIndicatorEvent;
	((SuiCore$Node*)self)->react = (void*)SuiDesigner$BezierEditView$react;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiDesigner$BezierEditView$draw_self;
}

// init function

void SuiDesigner$BezierEditView_init(SuiDesigner$BezierEditView *self, void *pOwner){
    Vtable_SuiDesigner$BezierEditView_init(&_vtable_SuiDesigner$BezierEditView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$BezierEditView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$BezierEditView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$BezierEditView * SuiDesigner$BezierEditView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$BezierEditView *self = calloc(1, sizeof(SuiDesigner$BezierEditView));
	
    SuiDesigner$BezierEditView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$BezierEditView$setBezier(SuiDesigner$BezierEditView *  self, SuiCore$Bezier v){
	self->start = v.start;
	self->c0 = v.c0;
	self->c1 = v.c1;
	self->end = v.end;
}


SuiCore$Bezier SuiDesigner$BezierEditView$getBezier(SuiDesigner$BezierEditView *  self){
	SuiCore$Bezier r;
	r.start = self->start;
	r.c0 = self->c0;
	r.c1 = self->c1;
	r.end = self->end;
	return r; 
}


void  SuiDesigner$BezierEditView$fire_onChanged(SuiDesigner$BezierEditView *  self){
	if (self->onChanged) {
		(*(self->onChanged))((void * )(self->onChanged), self) ;
	}
}


void  SuiDesigner$BezierEditView$layoutContent(SuiDesigner$BezierEditView *  self, SuiCore$Frame *  f){
	SuiCore$Frame tmp = *f;
	SuiCore$View$layoutContent(self, f) ;
	*f = tmp;
}


void  SuiDesigner$BezierEditView$ctor(SuiDesigner$BezierEditView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_66_15*  __var___Block_66_15 = (__var___Block_66_15=NULL,urgc_init_var((void**)&__var___Block_66_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_66_15) , __finiBlock___Block_66_15) ));
	urgc_set_field_class(__var___Block_66_15, (void * )offsetof(SuiDesigner$__Block_66_15, self) , self) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_67_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_67_27(&tmpReturn_1, __var___Block_66_15) ) ;
}


void  SuiDesigner$BezierEditView$_onIndicatorEvent(SuiDesigner$BezierEditView *  self, int  id, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->isMouseDown) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			urgc_set_field_class(self->drag, (void * )offsetof(SuiView$Drag, data) , Orc$String$addi(Orc$str(&tmpReturn_1, "") , id) ) ;
			self->drag->onMouseDown(self->drag, me) ;
		}
	}
}


void  SuiDesigner$BezierEditView$react(SuiDesigner$BezierEditView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_122_16*  __var___Block_122_16 = (__var___Block_122_16=NULL,urgc_init_var((void**)&__var___Block_122_16, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_122_16) , __finiBlock___Block_122_16) ));
	urgc_set_field_class(__var___Block_122_16, (void * )offsetof(SuiDesigner$__Block_122_16, self) , self) ;
	SuiCore$Node *  o = self;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_1 = NULL;
	{
		SuiCore$View*  __scopeVar_127_8 = SuiView$mkView(&tmpReturn_1, o, 0) , *o = __scopeVar_127_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_127_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$BezierEditView, startView) , o) ;
		o->width = self->indicatorSize;
		o->height = self->indicatorSize;
		o->radius->setAll(o->radius, 6) ;
		o->border->setAll(o->border, 2, 0xffffffff) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_133_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_133_26(&tmpReturn_2, __var___Block_122_16) ) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_3 = NULL;
	{
		SuiCore$View*  __scopeVar_138_8 = SuiView$mkView(&tmpReturn_3, o, 0) , *o = __scopeVar_138_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_138_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$BezierEditView, c0View) , o) ;
		o->width = self->indicatorSize;
		o->height = self->indicatorSize;
		o->radius->setAll(o->radius, 6) ;
		o->border->setAll(o->border, 2, 0xffffffff) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_144_26*  tmpReturn_4 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_144_26(&tmpReturn_4, __var___Block_122_16) ) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_5 = NULL;
	{
		SuiCore$View*  __scopeVar_149_8 = SuiView$mkView(&tmpReturn_5, o, 0) , *o = __scopeVar_149_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_149_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$BezierEditView, c1View) , o) ;
		o->width = self->indicatorSize;
		o->height = self->indicatorSize;
		o->radius->setAll(o->radius, 6) ;
		o->border->setAll(o->border, 2, 0xffffffff) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_155_26*  tmpReturn_6 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_155_26(&tmpReturn_6, __var___Block_122_16) ) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_7 = NULL;
	{
		SuiCore$View*  __scopeVar_159_8 = SuiView$mkView(&tmpReturn_7, o, 0) , *o = __scopeVar_159_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_159_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$BezierEditView, endView) , o) ;
		o->width = self->indicatorSize;
		o->height = self->indicatorSize;
		o->radius->setAll(o->radius, 6) ;
		o->border->setAll(o->border, 2, 0xffffffff) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_165_26*  tmpReturn_8 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_165_26(&tmpReturn_8, __var___Block_122_16) ) ;
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}


void  SuiDesigner$BezierEditView$draw_self(SuiDesigner$BezierEditView *  self, SuiCore$Canvas *  c){
	SuiCore$View$draw_self(self, c) ;
	SuiCore$Rect r = ((SuiCore$View * )self)->getContentLocalRect(self) ;
	if (self->startView) {
		{
			SuiCore$Frame *  o = &((SuiCore$ViewBase * )self->startView)->frame;
			
		
			o->x = r.w * self->start.x - self->indicatorSize / 2.0;
			o->y = r.h * (1.0 - self->start.y) - self->indicatorSize / 2.0;
		}
	}
	if (self->c0View) {
		{
			SuiCore$Frame *  o = &((SuiCore$ViewBase * )self->c0View)->frame;
			
		
			o->x = r.w * self->c0.x - self->indicatorSize / 2.0;
			o->y = r.h * (1.0 - self->c0.y) - self->indicatorSize / 2.0;
		}
	}
	if (self->c1View) {
		{
			SuiCore$Frame *  o = &((SuiCore$ViewBase * )self->c1View)->frame;
			
		
			o->x = r.w * self->c1.x - self->indicatorSize / 2.0;
			o->y = r.h * (1.0 - self->c1.y) - self->indicatorSize / 2.0;
		}
	}
	if (self->endView) {
		{
			SuiCore$Frame *  o = &((SuiCore$ViewBase * )self->endView)->frame;
			
		
			o->x = r.w * self->end.x - self->indicatorSize / 2.0;
			o->y = r.h * (1.0 - self->end.y) - self->indicatorSize / 2.0;
		}
	}
	float  sx = r.w * self->start.x;
	float  sy = r.h * (1.0 - self->start.y);
	float  c0x = r.w * self->c0.x;
	float  c0y = r.h * (1.0 - self->c0.y);
	float  c1x = r.w * self->c1.x;
	float  c1y = r.h * (1.0 - self->c1.y);
	float  ex = r.w * self->end.x;
	float  ey = r.h * (1.0 - self->end.y);
	SuiCore$Canvas$linearGradient(c, true, 0, 0, 0, r.h, SuiCore$mkIntByRgba(255, 0, 0, 255) , SuiCore$mkIntByRgba(255, 0, 0, 0) ) ;
	SuiCore$Canvas$beginPath(c) ;
	SuiCore$Canvas$moveTo(c, sx, sy) ;
	SuiCore$Canvas$bezierTo(c, c0x, c0y, c1x, c1y, ex, ey) ;
	SuiCore$Canvas$lineTo(c, r.w, r.h) ;
	SuiCore$Canvas$lineTo(c, 0, r.h) ;
	SuiCore$Canvas$closePath(c) ;
	SuiCore$Canvas$pathWinding(c, 1) ;
	SuiCore$Canvas$strokeColorByInt32(c, 0xffffffff) ;
	SuiCore$Canvas$strokeWidth(c, 2) ;
	SuiCore$Canvas$stroke(c) ;
	SuiCore$Canvas$fill(c) ;
	SuiCore$Canvas$beginPath(c) ;
	SuiCore$Canvas$moveTo(c, sx, sy) ;
	SuiCore$Canvas$lineTo(c, c0x, c0y) ;
	SuiCore$Canvas$strokeColorByInt32(c, 0xffff0000) ;
	SuiCore$Canvas$stroke(c) ;
	SuiCore$Canvas$beginPath(c) ;
	SuiCore$Canvas$moveTo(c, ex, ey) ;
	SuiCore$Canvas$lineTo(c, c1x, c1y) ;
	SuiCore$Canvas$strokeColorByInt32(c, 0xffff0000) ;
	SuiCore$Canvas$stroke(c) ;
}



static void  __finiBlock___Block_66_15(SuiDesigner$__Block_66_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_66_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_122_16(SuiDesigner$__Block_122_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_122_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_67_27(SuiDesigner$__Closure_67_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		SuiCore$View *  view = self->__var___Block_66_15->self->startView;
		URGC_VAR_CLEANUP_CLASS Orc$String*  id = (id=NULL,urgc_init_var_class((void**)&id, (Orc$String* )d->data));
		if (Orc$String$equals(id, "0") ) {
			view = self->__var___Block_66_15->self->startView;
		}
		if (Orc$String$equals(id, "1") ) {
			view = self->__var___Block_66_15->self->c0View;
		}
		if (Orc$String$equals(id, "2") ) {
			view = self->__var___Block_66_15->self->c1View;
		}
		if (Orc$String$equals(id, "3") ) {
			view = self->__var___Block_66_15->self->endView;
		}
		SuiCore$Rect local = ((SuiCore$View * )self->__var___Block_66_15->self)->getContentLocalRect(self->__var___Block_66_15->self) ;
		SuiCore$Vec2 to = ((SuiCore$ViewBase * )self->__var___Block_66_15->self)->worldToLocal(self->__var___Block_66_15->self, d->currentClientPos.x, d->currentClientPos.y) ;
		to = SuiCore$Vec2$sub(&to, SuiCore$mkVec2(local.x, local.y) ) ;
		SuiCore$Rect r = ((SuiCore$View * )self->__var___Block_66_15->self)->getContentClientRect(self->__var___Block_66_15->self) ;
		float  x = to.x / r.w;
		float  y = 1.0 - to.y / r.h;
		if (Orc$String$equals(id, "0") ) {
			SuiCore$Vec2$set(&self->__var___Block_66_15->self->start, x, y) ;
		}
		if (Orc$String$equals(id, "1") ) {
			SuiCore$Vec2$set(&self->__var___Block_66_15->self->c0, x, y) ;
		}
		if (Orc$String$equals(id, "2") ) {
			SuiCore$Vec2$set(&self->__var___Block_66_15->self->c1, x, y) ;
		}
		if (Orc$String$equals(id, "3") ) {
			SuiCore$Vec2$set(&self->__var___Block_66_15->self->end, x, y) ;
		}
		self->__var___Block_66_15->self->fire_onChanged(self->__var___Block_66_15->self) ;
	}
}

static void  __fini___Closure_67_27(SuiDesigner$__Closure_67_27 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_67_27, __var___Block_66_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_67_27*  __make___Closure_67_27(SuiDesigner$__Closure_67_27 **  __outRef__, SuiDesigner$__Block_66_15 *  __var___Block_66_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_67_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_67_27) , __fini___Closure_67_27) ));
	self->invoke = __fn___Closure_67_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_67_27, __var___Block_66_15) , __var___Block_66_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_133_26(SuiDesigner$__Closure_133_26 *  self, SuiCore$Event *  e){
	self->__var___Block_122_16->self->_onIndicatorEvent(self->__var___Block_122_16->self, 0, e) ;
}

static void  __fini___Closure_133_26(SuiDesigner$__Closure_133_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_133_26, __var___Block_122_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_133_26*  __make___Closure_133_26(SuiDesigner$__Closure_133_26 **  __outRef__, SuiDesigner$__Block_122_16 *  __var___Block_122_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_133_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_133_26) , __fini___Closure_133_26) ));
	self->invoke = __fn___Closure_133_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_133_26, __var___Block_122_16) , __var___Block_122_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_144_26(SuiDesigner$__Closure_144_26 *  self, SuiCore$Event *  e){
	self->__var___Block_122_16->self->_onIndicatorEvent(self->__var___Block_122_16->self, 1, e) ;
}

static void  __fini___Closure_144_26(SuiDesigner$__Closure_144_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_144_26, __var___Block_122_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_144_26*  __make___Closure_144_26(SuiDesigner$__Closure_144_26 **  __outRef__, SuiDesigner$__Block_122_16 *  __var___Block_122_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_144_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_144_26) , __fini___Closure_144_26) ));
	self->invoke = __fn___Closure_144_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_144_26, __var___Block_122_16) , __var___Block_122_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_155_26(SuiDesigner$__Closure_155_26 *  self, SuiCore$Event *  e){
	self->__var___Block_122_16->self->_onIndicatorEvent(self->__var___Block_122_16->self, 2, e) ;
}

static void  __fini___Closure_155_26(SuiDesigner$__Closure_155_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_155_26, __var___Block_122_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_155_26*  __make___Closure_155_26(SuiDesigner$__Closure_155_26 **  __outRef__, SuiDesigner$__Block_122_16 *  __var___Block_122_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_155_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_155_26) , __fini___Closure_155_26) ));
	self->invoke = __fn___Closure_155_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_155_26, __var___Block_122_16) , __var___Block_122_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_165_26(SuiDesigner$__Closure_165_26 *  self, SuiCore$Event *  e){
	self->__var___Block_122_16->self->_onIndicatorEvent(self->__var___Block_122_16->self, 3, e) ;
}

static void  __fini___Closure_165_26(SuiDesigner$__Closure_165_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_165_26, __var___Block_122_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_165_26*  __make___Closure_165_26(SuiDesigner$__Closure_165_26 **  __outRef__, SuiDesigner$__Block_122_16 *  __var___Block_122_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_165_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_165_26) , __fini___Closure_165_26) ));
	self->invoke = __fn___Closure_165_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_165_26, __var___Block_122_16) , __var___Block_122_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiDesigner$BezierEditView*  SuiDesigner$mkBezierEditView(SuiDesigner$BezierEditView **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$BezierEditView* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiDesigner$BezierEditView_init(NULL)) ) ; 
}



