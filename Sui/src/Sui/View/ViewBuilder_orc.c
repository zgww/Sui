
#include "ViewBuilder_orc.h" 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../Orc/ScopeData_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Map_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Emitter_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/Window_orc.h"
#include "../Layout/LayoutLinear_orc.h"


// static struct 
typedef struct tagSuiView$__Block_180_17 SuiView$__Block_180_17;

typedef struct tagSuiView$__Closure_189_22 SuiView$__Closure_189_22;



struct tagSuiView$__Block_180_17 {
	Sui$Window *  win ;
};





struct tagSuiView$__Closure_189_22 {
	void  (*invoke)(SuiView$__Closure_189_22 *  self);
	Vtable_Object *  vtable ;
	SuiView$__Block_180_17*  __var___Block_180_17 ;
};





// static function declaration
static void  __finiBlock___Block_180_17(SuiView$__Block_180_17 *  self);
static void  __fn___Closure_189_22(SuiView$__Closure_189_22 *  self);
static void  __fini___Closure_189_22(SuiView$__Closure_189_22 *  self);
static SuiView$__Closure_189_22*  __make___Closure_189_22(SuiView$__Closure_189_22 **  __outRef__, SuiView$__Block_180_17 *  __var___Block_180_17);


SuiCore$Node*  SuiView$gocNode(SuiCore$Node **  __outRef__, void *  sp, SuiCore$Node *  parent, Vtable_Object *  vt){
	char  key[32];
	snprintf(key, 32, "%p", sp) ;
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpReturn_1 = NULL;
	Orc$Map *  unusedMap = SuiCore$get_unusedMapForReact(&tmpReturn_1, parent) ;
	SuiCore$View *  n = (SuiCore$View * )unusedMap->get(unusedMap, key) ;
	if (!n) {
		n = vt->make(&n) ;
	}
	else {
		((SuiCore$Node * )n)->isNewForReact = false;
	}
	strcpy(((SuiCore$Node * )n)->key, key) ;
	unusedMap->del(unusedMap, key) ;
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpReturn_2 = NULL;
	Orc$Map *  map = SuiCore$get_mapForReact(&tmpReturn_2, parent) ;
	map->put(map, key, n) ;
	if (parent->hasInnerReact && !SuiCore$Node$isInInnerReact(parent) ) {
		if (parent->outKids == NULL) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_3 = NULL;
			urgc_set_field_class(parent, (void * )offsetof(SuiCore$Node, outKids) , Orc$List_new(&tmpNewOwner_3) ) ;
		}
		parent->outKids->insert(parent->outKids, n, parent->_appendIndexForReact) ;
	}
	else {
		parent->insertChild(parent, n, parent->_appendIndexForReact) ;
	}
	parent->_appendIndexForReact = parent->_appendIndexForReact + 1;
	return urgc_set_var_for_return_class((void ** )__outRef__, n) ; 
}

SuiCore$View*  SuiView$mkView(SuiCore$View **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$View*  n = (n=NULL,urgc_init_var_class((void**)&n, (SuiCore$View* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiCore$View_init(NULL)) ));
	return urgc_set_var_for_return_class((void ** )__outRef__, n) ; 
}


//vtable instance
Vtable_SuiView$TestPlaceView _vtable_SuiView$TestPlaceView;

// init meta

void SuiView$TestPlaceView_initMeta(Vtable_SuiView$TestPlaceView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiView$TestPlaceView* Vtable_SuiView$TestPlaceView_init(Vtable_SuiView$TestPlaceView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$TestPlaceView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$TestPlaceView_new;
    ((Vtable_Object*)pvt)->className = "SuiView$TestPlaceView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$TestPlaceView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$TestPlaceView_fini(SuiView$TestPlaceView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiView$TestPlaceView_init_fields(SuiView$TestPlaceView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$TestPlaceView_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)SuiView$TestPlaceView$ctor;
	((SuiCore$Node*)self)->react = (void*)SuiView$TestPlaceView$react;
}

// init function

void SuiView$TestPlaceView_init(SuiView$TestPlaceView *self, void *pOwner){
    Vtable_SuiView$TestPlaceView_init(&_vtable_SuiView$TestPlaceView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$TestPlaceView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$TestPlaceView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$TestPlaceView * SuiView$TestPlaceView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$TestPlaceView *self = calloc(1, sizeof(SuiView$TestPlaceView));
	
    SuiView$TestPlaceView_init(self, pOwner);
    return self;
}


// class members
void  SuiView$TestPlaceView$ctor(SuiView$TestPlaceView *  self){
	((SuiCore$Node * )self)->hasInnerReact = true;
}


void  SuiView$TestPlaceView$react(SuiView$TestPlaceView *  self){
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiCore$Node *  o = self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_156_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_156_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_156_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
		(tmpThis_1 = o->asColumn(o) )->aic(tmpThis_1) ;
		SuiCore$Node$placeKid((SuiCore$Node * )o, ((SuiCore$Node * )self)->outKids->get(((SuiCore$Node * )self)->outKids, 2) ) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_2 = NULL;
		{
			SuiCore$View*  __scopeVar_160_12 = SuiView$mkView(&tmpReturn_2, o, 0) , *o = __scopeVar_160_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_160_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->width = 200;
			o->height = 100;
			SuiCore$Inset$setAll(&o->padding, 10) ;
			o->backgroundColor = 0x7f0000ff;
			SuiCore$Node$placeKid((SuiCore$Node * )o, ((SuiCore$Node * )self)->outKids->get(((SuiCore$Node * )self)->outKids, 0) ) ;
		}
		SuiCore$Node$placeKid((SuiCore$Node * )o, ((SuiCore$Node * )self)->outKids->get(((SuiCore$Node * )self)->outKids, 1) ) ;
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



SuiView$TestPlaceView*  SuiView$mkTestPlaceView(SuiView$TestPlaceView **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$TestPlaceView* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$TestPlaceView_init(NULL)) ) ; 
}

void  SuiView$testPlaceKidsTo(){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		URGC_VAR_CLEANUP SuiView$__Block_180_17*  __var___Block_180_17 = (__var___Block_180_17=NULL,urgc_init_var((void**)&__var___Block_180_17, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_180_17) , __finiBlock___Block_180_17) ));
		__var___Block_180_17->win = o;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_2 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_183_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
			(tmpThis_1 = o->jcc(o) )->aic(tmpThis_1) ;
			__var___Block_180_17->win->setRootView(__var___Block_180_17->win, o) ;
		}
		URGC_VAR_CLEANUP SuiView$__Closure_189_22*  tmpReturn_3 = NULL;
		URGC_VAR_CLEANUP void  (**react)(void *  self) = urgc_init_var((void**)&react, __make___Closure_189_22(&tmpReturn_3, __var___Block_180_17) );
		(*(react))((void * )(react)) ;
		(*(react))((void * )(react)) ;
		(*(react))((void * )(react)) ;
		(*(react))((void * )(react)) ;
		(*(react))((void * )(react)) ;
		o->setTransparent(o) ;
		o->setTitle(o, "测试outKids") ;
		o->setSize(o, 640, 480) ;
		o->show(o) ;
	}
}

static void  __finiBlock___Block_180_17(SuiView$__Block_180_17 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_189_22(SuiView$__Closure_189_22 *  self){
	{
		SuiCore$ViewBase*  o = self->__var___Block_180_17->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_190_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$TestPlaceView*  tmpReturn_1 = NULL;
		{
			SuiView$TestPlaceView*  __scopeVar_191_16 = SuiView$mkTestPlaceView(&tmpReturn_1, o, 0) , *o = __scopeVar_191_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_191_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = 0x6f00ff00;
			SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 20) ;
			URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_2 = NULL;
			{
				SuiCore$View*  __scopeVar_194_20 = SuiView$mkView(&tmpReturn_2, o, 0) , *o = __scopeVar_194_20;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_194_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->width = 100;
				o->height = 100;
				o->backgroundColor = 0x3fff0000;
			}
			URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_3 = NULL;
			{
				SuiCore$View*  __scopeVar_199_20 = SuiView$mkView(&tmpReturn_3, o, 0) , *o = __scopeVar_199_20;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_199_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->width = 100;
				o->height = 100;
				o->backgroundColor = 0x4fffff00;
			}
			URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_4 = NULL;
			{
				SuiCore$View*  __scopeVar_204_20 = SuiView$mkView(&tmpReturn_4, o, 0) , *o = __scopeVar_204_20;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_204_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->width = 100;
				o->height = 100;
				o->backgroundColor = 0x5fff00ff;
			}
		}
	}
}

static void  __fini___Closure_189_22(SuiView$__Closure_189_22 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_189_22, __var___Block_180_17) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_189_22*  __make___Closure_189_22(SuiView$__Closure_189_22 **  __outRef__, SuiView$__Block_180_17 *  __var___Block_180_17){
	URGC_VAR_CLEANUP SuiView$__Closure_189_22*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_189_22) , __fini___Closure_189_22) ));
	self->invoke = __fn___Closure_189_22;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_189_22, __var___Block_180_17) , __var___Block_180_17) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



