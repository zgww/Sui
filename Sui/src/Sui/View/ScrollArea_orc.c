
#include "ScrollArea_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "./ViewBuilder_orc.h"
#include "./Drag_orc.h"
#include "../../SuiDesigner/Theme_orc.h"


// static struct 
typedef struct tagSuiView$__Block_182_12 SuiView$__Block_182_12;

typedef struct tagSuiView$__Block_374_12 SuiView$__Block_374_12;

typedef struct tagSuiView$__Block_416_38 SuiView$__Block_416_38;

typedef struct tagSuiView$__Closure_187_38 SuiView$__Closure_187_38;

typedef struct tagSuiView$__Closure_190_38 SuiView$__Closure_190_38;

typedef struct tagSuiView$__Closure_378_21 SuiView$__Closure_378_21;

typedef struct tagSuiView$__Closure_423_25 SuiView$__Closure_423_25;



struct tagSuiView$__Block_182_12 {
	SuiView$ScrollArea*  self ;
};





struct tagSuiView$__Block_374_12 {
	SuiView$ScrollBar*  self ;
};





struct tagSuiView$__Block_416_38 {
	SuiView$ScrollBar*  self ;
};





struct tagSuiView$__Closure_187_38 {
	SuiCore$Vec2 (*invoke)(SuiView$__Closure_187_38 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_182_12*  __var___Block_182_12 ;
};





struct tagSuiView$__Closure_190_38 {
	SuiCore$Vec2 (*invoke)(SuiView$__Closure_190_38 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_182_12*  __var___Block_182_12 ;
};





struct tagSuiView$__Closure_378_21 {
	void  (*invoke)(SuiView$__Closure_378_21 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiView$__Block_374_12*  __var___Block_374_12 ;
};





struct tagSuiView$__Closure_423_25 {
	void  (*invoke)(SuiView$__Closure_423_25 *  self, SuiView$ScrollArea *  area);
	Vtable_Object *  vtable ;
	SuiView$__Block_416_38*  __var___Block_416_38 ;
};





// static function declaration
static void  __finiBlock___Block_182_12(SuiView$__Block_182_12 *  self);
static void  __finiBlock___Block_374_12(SuiView$__Block_374_12 *  self);
static void  __finiBlock___Block_416_38(SuiView$__Block_416_38 *  self);
static SuiCore$Vec2 __fn___Closure_187_38(SuiView$__Closure_187_38 *  self);
static void  __fini___Closure_187_38(SuiView$__Closure_187_38 *  self);
static SuiView$__Closure_187_38*  __make___Closure_187_38(SuiView$__Closure_187_38 **  __outRef__, SuiView$__Block_182_12 *  __var___Block_182_12);
static SuiCore$Vec2 __fn___Closure_190_38(SuiView$__Closure_190_38 *  self);
static void  __fini___Closure_190_38(SuiView$__Closure_190_38 *  self);
static SuiView$__Closure_190_38*  __make___Closure_190_38(SuiView$__Closure_190_38 **  __outRef__, SuiView$__Block_182_12 *  __var___Block_182_12);
static void  __fn___Closure_378_21(SuiView$__Closure_378_21 *  self, SuiView$Drag *  d);
static void  __fini___Closure_378_21(SuiView$__Closure_378_21 *  self);
static SuiView$__Closure_378_21*  __make___Closure_378_21(SuiView$__Closure_378_21 **  __outRef__, SuiView$__Block_374_12 *  __var___Block_374_12);
static void  __fn___Closure_423_25(SuiView$__Closure_423_25 *  self, SuiView$ScrollArea *  area);
static void  __fini___Closure_423_25(SuiView$__Closure_423_25 *  self);
static SuiView$__Closure_423_25*  __make___Closure_423_25(SuiView$__Closure_423_25 **  __outRef__, SuiView$__Block_416_38 *  __var___Block_416_38);


static float  ScrollView_delta_factor = 0.5;

//vtable instance
Vtable_SuiView$ScrollModel _vtable_SuiView$ScrollModel;

// init meta

void SuiView$ScrollModel_initMeta(Vtable_SuiView$ScrollModel *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "scroll_left", OrcMetaType_float, offsetof(SuiView$ScrollModel, scroll_left), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "scroll_top", OrcMetaType_float, offsetof(SuiView$ScrollModel, scroll_top), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "clampScrollOffsetValid", offsetof(SuiView$ScrollModel, clampScrollOffsetValid));
	orc_metaField_method(&pNext, "on_wheel_event", offsetof(SuiView$ScrollModel, on_wheel_event));
	orc_metaField_method(&pNext, "get_h_rate", offsetof(SuiView$ScrollModel, get_h_rate));
	orc_metaField_method(&pNext, "get_v_rate", offsetof(SuiView$ScrollModel, get_v_rate));
	orc_metaField_method(&pNext, "get_h_length", offsetof(SuiView$ScrollModel, get_h_length));
	orc_metaField_method(&pNext, "get_v_length", offsetof(SuiView$ScrollModel, get_v_length));
	orc_metaField_method(&pNext, "get_v_pos", offsetof(SuiView$ScrollModel, get_v_pos));
	orc_metaField_method(&pNext, "calc_scroll_left_by_bar_pos", offsetof(SuiView$ScrollModel, calc_scroll_left_by_bar_pos));
	orc_metaField_method(&pNext, "calc_scroll_top_by_bar_pos", offsetof(SuiView$ScrollModel, calc_scroll_top_by_bar_pos));
	orc_metaField_method(&pNext, "get_h_pos", offsetof(SuiView$ScrollModel, get_h_pos));
	orc_metaField_method(&pNext, "bar_length", offsetof(SuiView$ScrollModel, bar_length));
}


// vtable init


Vtable_SuiView$ScrollModel* Vtable_SuiView$ScrollModel_init(Vtable_SuiView$ScrollModel* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$ScrollModel;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$ScrollModel_new;
    ((Vtable_Object*)pvt)->className = "SuiView$ScrollModel";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$ScrollModel_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$ScrollModel_fini(SuiView$ScrollModel *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiView$ScrollModel_init_fields(SuiView$ScrollModel *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$ScrollModel_fini;
	//fields
    {
	((SuiView$ScrollModel*)self)->scroll_left = 0;
	((SuiView$ScrollModel*)self)->scroll_top = 0;
	urgc_set_field(self, (void**)&((SuiView$ScrollModel*)self)->get_scroll_size, NULL);
	urgc_set_field(self, (void**)&((SuiView$ScrollModel*)self)->get_client_size, NULL);
    }
	((SuiView$ScrollModel*)self)->clampScrollOffsetValid = (void*)SuiView$ScrollModel$clampScrollOffsetValid;
	((SuiView$ScrollModel*)self)->on_wheel_event = (void*)SuiView$ScrollModel$on_wheel_event;
	((SuiView$ScrollModel*)self)->get_h_rate = (void*)SuiView$ScrollModel$get_h_rate;
	((SuiView$ScrollModel*)self)->get_v_rate = (void*)SuiView$ScrollModel$get_v_rate;
	((SuiView$ScrollModel*)self)->get_h_length = (void*)SuiView$ScrollModel$get_h_length;
	((SuiView$ScrollModel*)self)->get_v_length = (void*)SuiView$ScrollModel$get_v_length;
	((SuiView$ScrollModel*)self)->get_v_pos = (void*)SuiView$ScrollModel$get_v_pos;
	((SuiView$ScrollModel*)self)->calc_scroll_left_by_bar_pos = (void*)SuiView$ScrollModel$calc_scroll_left_by_bar_pos;
	((SuiView$ScrollModel*)self)->calc_scroll_top_by_bar_pos = (void*)SuiView$ScrollModel$calc_scroll_top_by_bar_pos;
	((SuiView$ScrollModel*)self)->get_h_pos = (void*)SuiView$ScrollModel$get_h_pos;
	((SuiView$ScrollModel*)self)->bar_length = (void*)SuiView$ScrollModel$bar_length;
}

// init function

void SuiView$ScrollModel_init(SuiView$ScrollModel *self, void *pOwner){
    Vtable_SuiView$ScrollModel_init(&_vtable_SuiView$ScrollModel);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$ScrollModel;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$ScrollModel_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$ScrollModel * SuiView$ScrollModel_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$ScrollModel *self = calloc(1, sizeof(SuiView$ScrollModel));
	
    SuiView$ScrollModel_init(self, pOwner);
    return self;
}


// class members
bool  SuiView$ScrollModel$clampScrollOffsetValid(SuiView$ScrollModel *  self){
	SuiCore$Vec2 client_size = (*(self->get_client_size))((void * )(self->get_client_size)) ;
	SuiCore$Vec2 scroll_size = (*(self->get_scroll_size))((void * )(self->get_scroll_size)) ;
	int  max_left = scroll_size.x - client_size.x;
	int  l = Orc$clampInt(self->scroll_left, 0, Orc$maxInt(0, max_left) ) ;
	bool  changed = false;
	if (l != self->scroll_left) {
		changed = true;
		self->scroll_left = l;
	}
	int  max_top = scroll_size.y - client_size.y;
	int  t = Orc$clampInt(self->scroll_top, 0, Orc$maxInt(0, max_top) ) ;
	if (t != self->scroll_top) {
		changed = true;
		self->scroll_top = t;
	}
	return changed; 
}


void  SuiView$ScrollModel$on_wheel_event(SuiView$ScrollModel *  self, SuiCore$WheelEvent *  evt){
	SuiCore$Vec2 client_size = (*(self->get_client_size))((void * )(self->get_client_size)) ;
	SuiCore$Vec2 scroll_size = (*(self->get_scroll_size))((void * )(self->get_scroll_size)) ;
	if (((SuiCore$MouseEvent * )evt)->shift) {
		float  max_left = scroll_size.x - client_size.x;
		self->scroll_left = Orc$clampInt(self->scroll_left - evt->deltaY * Orc$minFloat(ScrollView_delta_factor, client_size.x / 2.0f) , 0.0f, Orc$maxInt(0.0f, max_left) ) ;
	}
	else {
		float  max_top = scroll_size.y - client_size.y;
		self->scroll_top = Orc$clampInt(self->scroll_top - evt->deltaY * Orc$minFloat(ScrollView_delta_factor, client_size.y / 2.0f) , 0.0f, Orc$maxInt(0.0f, max_top) ) ;
	}
	printf("ScrollModel 更新 scroll:%d, %d; delta:%d, shift:%d\n", self->scroll_left, self->scroll_top, evt->deltaY, ((SuiCore$MouseEvent * )evt)->shift) ;
}


float  SuiView$ScrollModel$get_h_rate(SuiView$ScrollModel *  self){
	SuiCore$Vec2 ss = (*(self->get_scroll_size))((void * )(self->get_scroll_size)) ;
	SuiCore$Vec2 cs = (*(self->get_client_size))((void * )(self->get_client_size)) ;
	float  ret = Orc$minFloat(1.0, cs.x / (float )ss.x) ;
	return ret; 
}


float  SuiView$ScrollModel$get_v_rate(SuiView$ScrollModel *  self){
	SuiCore$Vec2 ss = (*(self->get_scroll_size))((void * )(self->get_scroll_size)) ;
	SuiCore$Vec2 cs = (*(self->get_client_size))((void * )(self->get_client_size)) ;
	float  ret = Orc$minFloat(1.0, cs.y / (float )ss.y) ;
	return ret; 
}


float  SuiView$ScrollModel$get_h_length(SuiView$ScrollModel *  self, int  full_size){
	return (float )self->bar_length(self, self->get_h_rate(self) , full_size, 30) ; 
}


float  SuiView$ScrollModel$get_v_length(SuiView$ScrollModel *  self, int  full_size){
	return (float )self->bar_length(self, self->get_v_rate(self) , full_size, 30) ; 
}


float  SuiView$ScrollModel$get_v_pos(SuiView$ScrollModel *  self, float  full_size){
	SuiCore$Vec2 ss = (*(self->get_scroll_size))((void * )(self->get_scroll_size)) ;
	float  position = (self->scroll_top / (float )ss.y * full_size);
	return position; 
}


float  SuiView$ScrollModel$calc_scroll_left_by_bar_pos(SuiView$ScrollModel *  self, float  full_size, float  position){
	SuiCore$Vec2 ss = (*(self->get_scroll_size))((void * )(self->get_scroll_size)) ;
	float  left = position / (float )full_size * ss.x;
	return left; 
}


float  SuiView$ScrollModel$calc_scroll_top_by_bar_pos(SuiView$ScrollModel *  self, float  full_size, float  position){
	SuiCore$Vec2 ss = (*(self->get_scroll_size))((void * )(self->get_scroll_size)) ;
	float  top = position / (float )full_size * ss.y;
	return top; 
}


float  SuiView$ScrollModel$get_h_pos(SuiView$ScrollModel *  self, float  full_size){
	SuiCore$Vec2 ss = (*(self->get_scroll_size))((void * )(self->get_scroll_size)) ;
	float  position = (self->scroll_left / (float )ss.x * full_size);
	return position; 
}


float  SuiView$ScrollModel$bar_length(SuiView$ScrollModel *  self, float  rate, float  full_size, float  min_size){
	return Orc$maxFloat(min_size, rate * full_size) ; 
}




//vtable instance
Vtable_SuiView$ScrollArea _vtable_SuiView$ScrollArea;

// init meta

void SuiView$ScrollArea_initMeta(Vtable_SuiView$ScrollArea *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "scroll_model", ((Vtable_Object*)Vtable_SuiView$ScrollModel_init(0)), offsetof(SuiView$ScrollArea, scroll_model), true, false, 1);
	orc_metaField_struct(&pNext, "contentCtx", SuiCore$Frame_getOrInitMetaStruct(), offsetof(SuiView$ScrollArea, contentCtx), false, false, 0);
	orc_metaField_primitive(&pNext, "useMaxWidthConstraint", OrcMetaType_bool, offsetof(SuiView$ScrollArea, useMaxWidthConstraint), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "useMinWidthConstraint", OrcMetaType_bool, offsetof(SuiView$ScrollArea, useMinWidthConstraint), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "scrollDirection", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$ScrollArea, scrollDirection), true, false, 1);
	orc_metaField_class(&pNext, "verScrollBar", ((Vtable_Object*)Vtable_SuiView$ScrollBar_init(0)), offsetof(SuiView$ScrollArea, verScrollBar), true, false, 1);
	orc_metaField_class(&pNext, "horScrollBar", ((Vtable_Object*)Vtable_SuiView$ScrollBar_init(0)), offsetof(SuiView$ScrollArea, horScrollBar), true, false, 1);

	orc_metaField_method(&pNext, "calc_scroll_size", offsetof(SuiView$ScrollArea, calc_scroll_size));
	orc_metaField_method(&pNext, "fireScrollChanged", offsetof(SuiView$ScrollArea, fireScrollChanged));
	orc_metaField_method(&pNext, "onWheelEvent", offsetof(SuiView$ScrollArea, onWheelEvent));
}


// vtable init


Vtable_SuiView$ScrollArea* Vtable_SuiView$ScrollArea_init(Vtable_SuiView$ScrollArea* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$ScrollArea;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$ScrollArea_new;
    ((Vtable_Object*)pvt)->className = "SuiView$ScrollArea";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$ScrollArea_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$ScrollArea_fini(SuiView$ScrollArea *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$ScrollArea*)self)->scroll_model);
	urgc_fini_field_class(self, (void**)&((SuiView$ScrollArea*)self)->scrollDirection);
	urgc_fini_field_class(self, (void**)&((SuiView$ScrollArea*)self)->verScrollBar);
	urgc_fini_field_class(self, (void**)&((SuiView$ScrollArea*)self)->horScrollBar);

}

// init fields function


void SuiView$ScrollArea_init_fields(SuiView$ScrollArea *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$ScrollArea_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollModel*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$ScrollArea*)self)->scroll_model, SuiView$ScrollModel_new(&tmpNewOwner_1) );
	((SuiView$ScrollArea*)self)->contentCtx = SuiCore$mkFrame() ;
	((SuiView$ScrollArea*)self)->useMaxWidthConstraint = false;
	((SuiView$ScrollArea*)self)->useMinWidthConstraint = true;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$ScrollArea*)self)->scrollDirection, Orc$str(&tmpReturn_2, "vertical") );
	urgc_set_field(self, (void**)&((SuiView$ScrollArea*)self)->onScrollChanged, NULL);
	urgc_set_field_class(self, (void**)&((SuiView$ScrollArea*)self)->verScrollBar, NULL);
	urgc_set_field_class(self, (void**)&((SuiView$ScrollArea*)self)->horScrollBar, NULL);
    }
	((SuiView$ScrollArea*)self)->calc_scroll_size = (void*)SuiView$ScrollArea$calc_scroll_size;
	((Object*)self)->ctor = (void*)SuiView$ScrollArea$ctor;
	((SuiCore$Node*)self)->react = (void*)SuiView$ScrollArea$react;
	((SuiCore$ViewBase*)self)->layout = (void*)SuiView$ScrollArea$layout;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$ScrollArea$onEvent;
	((SuiView$ScrollArea*)self)->fireScrollChanged = (void*)SuiView$ScrollArea$fireScrollChanged;
	((SuiView$ScrollArea*)self)->onWheelEvent = (void*)SuiView$ScrollArea$onWheelEvent;
	((SuiCore$ViewBase*)self)->draw_children = (void*)SuiView$ScrollArea$draw_children;
	((SuiCore$ViewBase*)self)->draw = (void*)SuiView$ScrollArea$draw;
	((SuiCore$ViewBase*)self)->hitTest = (void*)SuiView$ScrollArea$hitTest;
}

// init function

void SuiView$ScrollArea_init(SuiView$ScrollArea *self, void *pOwner){
    Vtable_SuiView$ScrollArea_init(&_vtable_SuiView$ScrollArea);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$ScrollArea;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$ScrollArea_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$ScrollArea * SuiView$ScrollArea_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$ScrollArea *self = calloc(1, sizeof(SuiView$ScrollArea));
	
    SuiView$ScrollArea_init(self, pOwner);
    return self;
}


// class members
SuiCore$Vec2 SuiView$ScrollArea$calc_scroll_size(SuiView$ScrollArea *  self){
	return SuiCore$mkVec2(self->contentCtx.width, self->contentCtx.height) ; 
}


void  SuiView$ScrollArea$ctor(SuiView$ScrollArea *  self){
	URGC_VAR_CLEANUP SuiView$__Block_182_12*  __var___Block_182_12 = (__var___Block_182_12=NULL,urgc_init_var((void**)&__var___Block_182_12, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_182_12) , __finiBlock___Block_182_12) ));
	urgc_set_field_class(__var___Block_182_12, (void * )offsetof(SuiView$__Block_182_12, self) , self) ;
	((SuiCore$Node * )self)->hasInnerReact = true;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->direction, "column") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->alignItems, "start") ;
	URGC_VAR_CLEANUP SuiView$__Closure_187_38*  tmpReturn_1 = NULL;
	urgc_set_field(self->scroll_model, (void * )offsetof(SuiView$ScrollModel, get_scroll_size) , __make___Closure_187_38(&tmpReturn_1, __var___Block_182_12) ) ;
	URGC_VAR_CLEANUP SuiView$__Closure_190_38*  tmpReturn_2 = NULL;
	urgc_set_field(self->scroll_model, (void * )offsetof(SuiView$ScrollModel, get_client_size) , __make___Closure_190_38(&tmpReturn_2, __var___Block_182_12) ) ;
}


void  SuiView$ScrollArea$react(SuiView$ScrollArea *  self){
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiCore$Node *  o = self;
	SuiCore$Node$placeKids((SuiCore$Node * )self, ((SuiCore$Node * )self)->outKids) ;
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollBar*  tmpReturn_1 = NULL;
	{
		SuiView$ScrollBar*  __scopeVar_204_2 = SuiView$mkScrollBar(&tmpReturn_1, o, 0) , *o = __scopeVar_204_2;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_204_2 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->bindScrollArea(o, self) ;
		o->isVer = false;
		urgc_set_field_class(self, (void * )offsetof(SuiView$ScrollArea, horScrollBar) , o) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollBar*  tmpReturn_2 = NULL;
	{
		SuiView$ScrollBar*  __scopeVar_210_2 = SuiView$mkScrollBar(&tmpReturn_2, o, 0) , *o = __scopeVar_210_2;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_210_2 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->bindScrollArea(o, self) ;
		urgc_set_field_class(self, (void * )offsetof(SuiView$ScrollArea, verScrollBar) , o) ;
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}


void  SuiView$ScrollArea$layout(SuiView$ScrollArea *  self, SuiCore$Frame *  ctx){
	((SuiCore$View * )self)->updateFrame_forSelfWidthHeight(self, ctx) ;
	SuiCore$Frame$setSize_ifAnyTight(ctx) ;
	if (((SuiCore$View * )self)->callCbLayout(self, ctx) ) {
		return ; 
	}
	if (self->useMinWidthConstraint && self->useMaxWidthConstraint) {
		SuiCore$Frame tmpCtx = ((SuiCore$View * )self)->makeContentLayoutCtx(self, ctx) ;
		SuiCore$Frame$setWidthConstraint(&self->contentCtx, tmpCtx.maxWidth, tmpCtx.maxWidth) ;
	}
	else if (self->useMaxWidthConstraint) {
		SuiCore$Frame tmpCtx = ((SuiCore$View * )self)->makeContentLayoutCtx(self, ctx) ;
		SuiCore$Frame$setWidthConstraint(&self->contentCtx, 0.0, tmpCtx.maxWidth) ;
	}
	else if (self->useMinWidthConstraint) {
		SuiCore$Frame tmpCtx = ((SuiCore$View * )self)->makeContentLayoutCtx(self, ctx) ;
		SuiCore$Frame$setWidthConstraint(&self->contentCtx, tmpCtx.maxWidth, INFINITY) ;
	}
	else {
		SuiCore$Frame$setWidthConstraint(&self->contentCtx, 0.0, INFINITY) ;
	}
	SuiLayout$LayoutLinear$layoutContent(self, &self->contentCtx) ;
}


void  SuiView$ScrollArea$onEvent(SuiView$ScrollArea *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$WheelEvent_init(NULL))) {
		self->onWheelEvent(self, (SuiCore$WheelEvent * )e) ;
	}
}


void  SuiView$ScrollArea$fireScrollChanged(SuiView$ScrollArea *  self){
	if (self->onScrollChanged != NULL) {
		(*(self->onScrollChanged))((void * )(self->onScrollChanged), self) ;
	}
}


void  SuiView$ScrollArea$onWheelEvent(SuiView$ScrollArea *  self, SuiCore$WheelEvent *  e){
	self->scroll_model->on_wheel_event(self->scroll_model, e) ;
	self->fireScrollChanged(self) ;
	((SuiCore$ViewBase * )self)->invalidLayout(self) ;
}


void  SuiView$ScrollArea$draw_children(SuiView$ScrollArea *  self, SuiCore$Canvas *  canvas){
	{
		float  w = SuiDesigner$themeIns() ->scrollbar_size;
		bool  hasV = self->scroll_model->get_v_rate(self->scroll_model)  < 1.0;
		float  horDeltaW = hasV ? -w : 0;
		((SuiCore$ViewBase * )self->verScrollBar)->frame.x = ((SuiCore$ViewBase * )self)->frame.width - SuiCore$Inset$hor(&((SuiCore$View * )self)->margin)  - w + self->scroll_model->scroll_left;
		((SuiCore$ViewBase * )self->verScrollBar)->frame.y = 0 + self->scroll_model->scroll_top;
		((SuiCore$ViewBase * )self->verScrollBar)->frame.width = w;
		((SuiCore$ViewBase * )self->verScrollBar)->frame.height = ((SuiCore$ViewBase * )self)->frame.height;
		((SuiCore$ViewBase * )self->horScrollBar)->frame.x = 0 + self->scroll_model->scroll_left;
		((SuiCore$ViewBase * )self->horScrollBar)->frame.y = ((SuiCore$ViewBase * )self)->frame.height - SuiCore$Inset$ver(&((SuiCore$View * )self)->margin)  - w + self->scroll_model->scroll_top;
		((SuiCore$ViewBase * )self->horScrollBar)->frame.width = ((SuiCore$ViewBase * )self)->frame.width + horDeltaW;
		((SuiCore$ViewBase * )self->horScrollBar)->frame.height = w;
	}
	SuiCore$Canvas$save(canvas) ;
	((SuiCore$View * )self)->clip(self, canvas) ;
	SuiCore$Canvas$translate(canvas, -self->scroll_model->scroll_left, -self->scroll_model->scroll_top) ;
	SuiCore$ViewBase$draw_children(self, canvas) ;
	SuiCore$Canvas$restore(canvas) ;
}


void  SuiView$ScrollArea$draw(SuiView$ScrollArea *  self, SuiCore$Canvas *  canvas){
	if (self->scroll_model->clampScrollOffsetValid(self->scroll_model) ) {
		self->fireScrollChanged(self) ;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
	SuiCore$Canvas$save(canvas) ;
	SuiCore$Canvas$translate(canvas, ((SuiCore$ViewBase * )self)->frame.x + ((SuiCore$View * )self)->margin.left, ((SuiCore$ViewBase * )self)->frame.y + ((SuiCore$View * )self)->margin.top) ;
	SuiCore$Canvas$transform(canvas, ((SuiCore$ViewBase * )self)->transform) ;
	SuiCore$Canvas$currentTransform(canvas, &((SuiCore$ViewBase * )self)->_world_transform) ;
	((SuiCore$ViewBase * )self)->draw_self(self, canvas) ;
	SuiCore$Canvas$save(canvas) ;
	SuiCore$Canvas$translate(canvas, ((SuiCore$View * )self)->padding.left + ((SuiCore$View * )self)->border->l->w, ((SuiCore$View * )self)->padding.top + ((SuiCore$View * )self)->border->t->w) ;
	((SuiCore$ViewBase * )self)->draw_children(self, canvas) ;
	SuiCore$Canvas$restore(canvas) ;
	SuiCore$Canvas$restore(canvas) ;
}


SuiCore$ViewBase *  SuiView$ScrollArea$hitTest(SuiView$ScrollArea *  self, float  x, float  y){
	SuiCore$Rect r = ((SuiCore$ViewBase * )self)->get_abs_rect(self) ;
	if (!SuiCore$Rect$containsPosition(&r, x, y) ) {
		return NULL; 
	}
	return SuiCore$ViewBase$hitTest(self, x, y) ; 
}




//vtable instance
Vtable_SuiView$ScrollBar _vtable_SuiView$ScrollBar;

// init meta

void SuiView$ScrollBar_initMeta(Vtable_SuiView$ScrollBar *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiView$ScrollBar, drag), true, false, 1);
	orc_metaField_primitive(&pNext, "isVer", OrcMetaType_bool, offsetof(SuiView$ScrollBar, isVer), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "scrollArea", ((Vtable_Object*)Vtable_SuiView$ScrollArea_init(0)), offsetof(SuiView$ScrollBar, scrollArea), true, false, 1);

	orc_metaField_method(&pNext, "bindScrollArea", offsetof(SuiView$ScrollBar, bindScrollArea));
}


// vtable init


Vtable_SuiView$ScrollBar* Vtable_SuiView$ScrollBar_init(Vtable_SuiView$ScrollBar* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$ScrollBar;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$ScrollBar_new;
    ((Vtable_Object*)pvt)->className = "SuiView$ScrollBar";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$ScrollBar_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$ScrollBar_fini(SuiView$ScrollBar *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$ScrollBar*)self)->drag);
	urgc_fini_field_class(self, (void**)&((SuiView$ScrollBar*)self)->scrollArea);

}

// init fields function


void SuiView$ScrollBar_init_fields(SuiView$ScrollBar *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$ScrollBar_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$ScrollBar*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	((SuiView$ScrollBar*)self)->isVer = true;
	urgc_set_field_class(self, (void**)&((SuiView$ScrollBar*)self)->scrollArea, NULL);
    }
	((Object*)self)->ctor = (void*)SuiView$ScrollBar$ctor;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$ScrollBar$onEvent;
	((SuiCore$ViewBase*)self)->setHover = (void*)SuiView$ScrollBar$setHover;
	((SuiCore$ViewBase*)self)->canLayoutByParent = (void*)SuiView$ScrollBar$canLayoutByParent;
	((SuiView$ScrollBar*)self)->bindScrollArea = (void*)SuiView$ScrollBar$bindScrollArea;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$ScrollBar$draw_self;
}

// init function

void SuiView$ScrollBar_init(SuiView$ScrollBar *self, void *pOwner){
    Vtable_SuiView$ScrollBar_init(&_vtable_SuiView$ScrollBar);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$ScrollBar;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$ScrollBar_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$ScrollBar * SuiView$ScrollBar_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$ScrollBar *self = calloc(1, sizeof(SuiView$ScrollBar));
	
    SuiView$ScrollBar_init(self, pOwner);
    return self;
}


// class members
void  SuiView$ScrollBar$ctor(SuiView$ScrollBar *  self){
	URGC_VAR_CLEANUP SuiView$__Block_374_12*  __var___Block_374_12 = (__var___Block_374_12=NULL,urgc_init_var((void**)&__var___Block_374_12, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_374_12) , __finiBlock___Block_374_12) ));
	urgc_set_field_class(__var___Block_374_12, (void * )offsetof(SuiView$__Block_374_12, self) , self) ;
	((SuiCore$View * )self)->width = 10;
	((SuiCore$View * )self)->height = 204;
	URGC_VAR_CLEANUP SuiView$__Closure_378_21*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_378_21(&tmpReturn_1, __var___Block_374_12) ) ;
}


void  SuiView$ScrollBar$onEvent(SuiView$ScrollBar *  self, SuiCore$Event *  e){
	self->drag->onMouseDown(self->drag, e) ;
}


void  SuiView$ScrollBar$setHover(SuiView$ScrollBar *  self, bool  v){
	SuiCore$ViewBase$setHover(self, v) ;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


bool  SuiView$ScrollBar$canLayoutByParent(SuiView$ScrollBar *  self){
	return false; 
}


void  SuiView$ScrollBar$bindScrollArea(SuiView$ScrollBar *  self, SuiView$ScrollArea *  area){
	URGC_VAR_CLEANUP SuiView$__Block_416_38*  __var___Block_416_38 = (__var___Block_416_38=NULL,urgc_init_var((void**)&__var___Block_416_38, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_416_38) , __finiBlock___Block_416_38) ));
	urgc_set_field_class(__var___Block_416_38, (void * )offsetof(SuiView$__Block_416_38, self) , self) ;
	if (area == self->scrollArea) {
		return ; 
	}
	printf("\n\n========================================绑定ScrollArea\n\n") ;
	urgc_set_field_class(self, (void * )offsetof(SuiView$ScrollBar, scrollArea) , area) ;
	URGC_VAR_CLEANUP SuiView$__Closure_423_25*  tmpReturn_1 = NULL;
	urgc_set_field(area, (void * )offsetof(SuiView$ScrollArea, onScrollChanged) , __make___Closure_423_25(&tmpReturn_1, __var___Block_416_38) ) ;
}


void  SuiView$ScrollBar$draw_self(SuiView$ScrollBar *  self, SuiCore$Canvas *  canvas){
	if (self->scrollArea == NULL) {
		return ; 
	}
	int  x = 0;
	int  w = ((SuiCore$ViewBase * )self)->frame.width;
	int  y = 0;
	int  h = ((SuiCore$ViewBase * )self)->frame.height;
	SuiView$ScrollModel *  model = self->scrollArea->scroll_model;
	float  d = 0;
	float  r = Orc$minFloat(w, h)  / 2.0;
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	int  bg = t->scrollbar_bg;
	int  barBg = t->scrollbar_barBg;
	if (self->isVer) {
		if (model->get_v_rate(model)  >= 0.9999999) {
			return ; 
		}
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$roundRect(canvas, x, y, w, h, 3) ;
		SuiCore$Canvas$fillColorByInt32(canvas, bg) ;
		SuiCore$Canvas$fill(canvas) ;
		float  fullSize = h - 0;
		float  barLen = model->get_v_length(model, fullSize) ;
		float  barPos = model->get_v_pos(model, fullSize)  + 0;
		float  barX = x + d;
		float  barW = w - d * 2;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$fillColorByInt32(canvas, barBg) ;
		SuiCore$Canvas$roundRect(canvas, barX, barPos, barW, barLen, r) ;
		SuiCore$Canvas$fill(canvas) ;
	}
	else {
		if (model->get_h_rate(model)  >= 0.9999999) {
			return ; 
		}
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$roundRect(canvas, x, y, w, h, 3) ;
		SuiCore$Canvas$fillColorByInt32(canvas, bg) ;
		SuiCore$Canvas$fill(canvas) ;
		float  fullSize = w;
		float  barLen = model->get_h_length(model, fullSize) ;
		float  barPos = model->get_h_pos(model, fullSize) ;
		float  barY = y + d;
		float  barH = h - d * 2;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$fillColorByInt32(canvas, barBg) ;
		SuiCore$Canvas$roundRect(canvas, barPos, barY, barLen, barH, r) ;
		SuiCore$Canvas$fill(canvas) ;
	}
}



static void  __finiBlock___Block_182_12(SuiView$__Block_182_12 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_182_12, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_374_12(SuiView$__Block_374_12 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_374_12, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_416_38(SuiView$__Block_416_38 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_416_38, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static SuiCore$Vec2 __fn___Closure_187_38(SuiView$__Closure_187_38 *  self){
	return self->__var___Block_182_12->self->calc_scroll_size(self->__var___Block_182_12->self) ; 
}

static void  __fini___Closure_187_38(SuiView$__Closure_187_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_187_38, __var___Block_182_12) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_187_38*  __make___Closure_187_38(SuiView$__Closure_187_38 **  __outRef__, SuiView$__Block_182_12 *  __var___Block_182_12){
	URGC_VAR_CLEANUP SuiView$__Closure_187_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_187_38) , __fini___Closure_187_38) ));
	self->invoke = __fn___Closure_187_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_187_38, __var___Block_182_12) , __var___Block_182_12) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiCore$Vec2 __fn___Closure_190_38(SuiView$__Closure_190_38 *  self){
	SuiCore$Rect r = ((SuiCore$View * )self->__var___Block_182_12->self)->getContentLocalRect(self->__var___Block_182_12->self) ;
	return SuiCore$mkVec2(r.w, r.h) ; 
}

static void  __fini___Closure_190_38(SuiView$__Closure_190_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_190_38, __var___Block_182_12) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_190_38*  __make___Closure_190_38(SuiView$__Closure_190_38 **  __outRef__, SuiView$__Block_182_12 *  __var___Block_182_12){
	URGC_VAR_CLEANUP SuiView$__Closure_190_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_190_38) , __fini___Closure_190_38) ));
	self->invoke = __fn___Closure_190_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_190_38, __var___Block_182_12) , __var___Block_182_12) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_378_21(SuiView$__Closure_378_21 *  self, SuiView$Drag *  d){
	printf("drag scrollbar\n") ;
	if (self->__var___Block_374_12->self->scrollArea == NULL) {
		return ; 
	}
	SuiView$ScrollModel *  model = self->__var___Block_374_12->self->scrollArea->scroll_model;
	if (self->__var___Block_374_12->self->isVer) {
		float  fullSize = ((SuiCore$ViewBase * )self->__var___Block_374_12->self)->frame.height;
		float  barPos = model->get_v_pos(model, fullSize) ;
		float  newBarPos = barPos + d->deltaPos.y;
		model->scroll_top = model->calc_scroll_top_by_bar_pos(model, fullSize, newBarPos) ;
	}
	else {
		float  fullSize = ((SuiCore$ViewBase * )self->__var___Block_374_12->self)->frame.width;
		float  barPos = model->get_h_pos(model, fullSize) ;
		float  newBarPos = barPos + d->deltaPos.x;
		printf("newBarPos:%f. delta:%f left:%d\n", newBarPos, d->deltaPos.x, model->scroll_left) ;
		model->scroll_left = model->calc_scroll_left_by_bar_pos(model, fullSize, newBarPos) ;
		printf("\tnew left:%d\n", model->scroll_left) ;
	}
	model->clampScrollOffsetValid(model) ;
	self->__var___Block_374_12->self->scrollArea->fireScrollChanged(self->__var___Block_374_12->self->scrollArea) ;
}

static void  __fini___Closure_378_21(SuiView$__Closure_378_21 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_378_21, __var___Block_374_12) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_378_21*  __make___Closure_378_21(SuiView$__Closure_378_21 **  __outRef__, SuiView$__Block_374_12 *  __var___Block_374_12){
	URGC_VAR_CLEANUP SuiView$__Closure_378_21*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_378_21) , __fini___Closure_378_21) ));
	self->invoke = __fn___Closure_378_21;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_378_21, __var___Block_374_12) , __var___Block_374_12) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_423_25(SuiView$__Closure_423_25 *  self, SuiView$ScrollArea *  area){
	((SuiCore$ViewBase * )self->__var___Block_416_38->self)->invalidDraw(self->__var___Block_416_38->self) ;
}

static void  __fini___Closure_423_25(SuiView$__Closure_423_25 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_423_25, __var___Block_416_38) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_423_25*  __make___Closure_423_25(SuiView$__Closure_423_25 **  __outRef__, SuiView$__Block_416_38 *  __var___Block_416_38){
	URGC_VAR_CLEANUP SuiView$__Closure_423_25*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_423_25) , __fini___Closure_423_25) ));
	self->invoke = __fn___Closure_423_25;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_423_25, __var___Block_416_38) , __var___Block_416_38) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$ScrollArea*  SuiView$mkScrollArea(SuiView$ScrollArea **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$ScrollArea* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$ScrollArea_init(NULL)) ) ; 
}

SuiView$ScrollBar*  SuiView$mkScrollBar(SuiView$ScrollBar **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$ScrollBar* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$ScrollBar_init(NULL)) ) ; 
}



