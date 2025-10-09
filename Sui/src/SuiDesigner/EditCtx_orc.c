
#include "EditCtx_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Json/Json_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "./RegisterNodes_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "./ANode_orc.h"
#include "./Prefab_orc.h"
#include "./SceneView_orc.h"
#include "./SceneHierView_orc.h"
#include "./EventANodeChanged_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_68_35 SuiDesigner$__Block_68_35;

typedef struct tagSuiDesigner$__Block_110_15 SuiDesigner$__Block_110_15;

typedef struct tagSuiDesigner$__Closure_70_36 SuiDesigner$__Closure_70_36;

typedef struct tagSuiDesigner$__Closure_112_23 SuiDesigner$__Closure_112_23;



struct tagSuiDesigner$__Block_68_35 {
	SuiDesigner$EditCtx*  self ;
};





struct tagSuiDesigner$__Block_110_15 {
	SuiDesigner$EditCtx*  self ;
};





struct tagSuiDesigner$__Closure_70_36 {
	void  (*invoke)(SuiDesigner$__Closure_70_36 *  self, SuiView$TreeState *  state);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_68_35*  __var___Block_68_35 ;
};





struct tagSuiDesigner$__Closure_112_23 {
	void  (*invoke)(SuiDesigner$__Closure_112_23 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_110_15*  __var___Block_110_15 ;
};





// static function declaration
static void  __finiBlock___Block_68_35(SuiDesigner$__Block_68_35 *  self);
static void  __finiBlock___Block_110_15(SuiDesigner$__Block_110_15 *  self);
static void  __fn___Closure_70_36(SuiDesigner$__Closure_70_36 *  self, SuiView$TreeState *  state);
static void  __fini___Closure_70_36(SuiDesigner$__Closure_70_36 *  self);
static SuiDesigner$__Closure_70_36*  __make___Closure_70_36(SuiDesigner$__Closure_70_36 **  __outRef__, SuiDesigner$__Block_68_35 *  __var___Block_68_35);
static void  __fn___Closure_112_23(SuiDesigner$__Closure_112_23 *  self);
static void  __fini___Closure_112_23(SuiDesigner$__Closure_112_23 *  self);
static SuiDesigner$__Closure_112_23*  __make___Closure_112_23(SuiDesigner$__Closure_112_23 **  __outRef__, SuiDesigner$__Block_110_15 *  __var___Block_110_15);



//vtable instance
Vtable_SuiDesigner$EditEventBase _vtable_SuiDesigner$EditEventBase;

// init meta

void SuiDesigner$EditEventBase_initMeta(Vtable_SuiDesigner$EditEventBase *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$EditEventBase* Vtable_SuiDesigner$EditEventBase_init(Vtable_SuiDesigner$EditEventBase* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EditEventBase;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EditEventBase_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EditEventBase";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EditEventBase_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EditEventBase_fini(SuiDesigner$EditEventBase *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$EditEventBase_init_fields(SuiDesigner$EditEventBase *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EditEventBase_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$EditEventBase_init(SuiDesigner$EditEventBase *self, void *pOwner){
    Vtable_SuiDesigner$EditEventBase_init(&_vtable_SuiDesigner$EditEventBase);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EditEventBase;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EditEventBase_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EditEventBase * SuiDesigner$EditEventBase_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EditEventBase *self = calloc(1, sizeof(SuiDesigner$EditEventBase));
	
    SuiDesigner$EditEventBase_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$EditEventSelectedChanged _vtable_SuiDesigner$EditEventSelectedChanged;

// init meta

void SuiDesigner$EditEventSelectedChanged_initMeta(Vtable_SuiDesigner$EditEventSelectedChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$EditEventSelectedChanged* Vtable_SuiDesigner$EditEventSelectedChanged_init(Vtable_SuiDesigner$EditEventSelectedChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EditEventSelectedChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$EditEventBase_init(&_vtable_SuiDesigner$EditEventBase);

	// init by super vtable init function
    Vtable_SuiDesigner$EditEventBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$EditEventBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EditEventSelectedChanged_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EditEventSelectedChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EditEventSelectedChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EditEventSelectedChanged_fini(SuiDesigner$EditEventSelectedChanged *self){
	//super fini
    SuiDesigner$EditEventBase_fini((SuiDesigner$EditEventBase *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$EditEventSelectedChanged_init_fields(SuiDesigner$EditEventSelectedChanged *self){
	//super class
    SuiDesigner$EditEventBase_init_fields((SuiDesigner$EditEventBase*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EditEventSelectedChanged_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$EditEventSelectedChanged_init(SuiDesigner$EditEventSelectedChanged *self, void *pOwner){
    Vtable_SuiDesigner$EditEventSelectedChanged_init(&_vtable_SuiDesigner$EditEventSelectedChanged);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EditEventSelectedChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EditEventSelectedChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EditEventSelectedChanged * SuiDesigner$EditEventSelectedChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EditEventSelectedChanged *self = calloc(1, sizeof(SuiDesigner$EditEventSelectedChanged));
	
    SuiDesigner$EditEventSelectedChanged_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$EditCtx _vtable_SuiDesigner$EditCtx;

// init meta

void SuiDesigner$EditCtx_initMeta(Vtable_SuiDesigner$EditCtx *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "root", ((Vtable_Object*)Vtable_SuiDesigner$ANode_init(0)), offsetof(SuiDesigner$EditCtx, root), true, false, 1);
	orc_metaField_class(&pNext, "roots", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$EditCtx, roots), true, false, 1);
	orc_metaField_class(&pNext, "state", ((Vtable_Object*)Vtable_SuiView$TreeState_init(0)), offsetof(SuiDesigner$EditCtx, state), true, false, 1);
	orc_metaField_class(&pNext, "hoverNode", ((Vtable_Object*)Vtable_SuiDesigner$ANode_init(0)), offsetof(SuiDesigner$EditCtx, hoverNode), true, false, 1);
	orc_metaField_class(&pNext, "prefab", ((Vtable_Object*)Vtable_SuiDesigner$Prefab_init(0)), offsetof(SuiDesigner$EditCtx, prefab), true, false, 1);
	orc_metaField_class(&pNext, "sceneView", ((Vtable_Object*)Vtable_SuiDesigner$SceneView_init(0)), offsetof(SuiDesigner$EditCtx, sceneView), true, false, 1);

	orc_metaField_method(&pNext, "findANodeByNode", offsetof(SuiDesigner$EditCtx, findANodeByNode));
	orc_metaField_method(&pNext, "setState", offsetof(SuiDesigner$EditCtx, setState));
	orc_metaField_method(&pNext, "onSelectedChanged", offsetof(SuiDesigner$EditCtx, onSelectedChanged));
	orc_metaField_method(&pNext, "closeCurrentPrefab", offsetof(SuiDesigner$EditCtx, closeCurrentPrefab));
	orc_metaField_method(&pNext, "openPrefab", offsetof(SuiDesigner$EditCtx, openPrefab));
	orc_metaField_method(&pNext, "init", offsetof(SuiDesigner$EditCtx, init));
}


// vtable init


Vtable_SuiDesigner$EditCtx* Vtable_SuiDesigner$EditCtx_init(Vtable_SuiDesigner$EditCtx* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EditCtx;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Emitter_init(&_vtable_SuiCore$Emitter);

	// init by super vtable init function
    Vtable_SuiCore$Emitter_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Emitter;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EditCtx_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EditCtx";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EditCtx_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EditCtx_fini(SuiDesigner$EditCtx *self){
	//super fini
    SuiCore$Emitter_fini((SuiCore$Emitter *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->root);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->roots);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->state);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->hoverNode);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->prefab);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->sceneView);

}

// init fields function


void SuiDesigner$EditCtx_init_fields(SuiDesigner$EditCtx *self){
	//super class
    SuiCore$Emitter_init_fields((SuiCore$Emitter*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EditCtx_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->root, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->roots, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->state, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->hoverNode, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->prefab, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$EditCtx*)self)->sceneView, NULL);
    }
	((SuiDesigner$EditCtx*)self)->findANodeByNode = (void*)SuiDesigner$EditCtx$findANodeByNode;
	((SuiDesigner$EditCtx*)self)->setState = (void*)SuiDesigner$EditCtx$setState;
	((SuiDesigner$EditCtx*)self)->onSelectedChanged = (void*)SuiDesigner$EditCtx$onSelectedChanged;
	((SuiDesigner$EditCtx*)self)->closeCurrentPrefab = (void*)SuiDesigner$EditCtx$closeCurrentPrefab;
	((SuiDesigner$EditCtx*)self)->openPrefab = (void*)SuiDesigner$EditCtx$openPrefab;
	((SuiDesigner$EditCtx*)self)->init = (void*)SuiDesigner$EditCtx$init;
}

// init function

void SuiDesigner$EditCtx_init(SuiDesigner$EditCtx *self, void *pOwner){
    Vtable_SuiDesigner$EditCtx_init(&_vtable_SuiDesigner$EditCtx);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EditCtx;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EditCtx_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EditCtx * SuiDesigner$EditCtx_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EditCtx *self = calloc(1, sizeof(SuiDesigner$EditCtx));
	
    SuiDesigner$EditCtx_init(self, pOwner);
    return self;
}


// class members
SuiDesigner$ANode*  SuiDesigner$EditCtx$findANodeByNode(SuiDesigner$ANode **  __outRef__, SuiDesigner$EditCtx *  self, SuiCore$Node *  node){
	if (self->root && self->root->node) {
		SuiCore$Node *  scene = self->root->node->parent;
		SuiCore$Node *  n = node;
		while (n && n != scene) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  found = self->root->findANodeByNode((found = NULL,&found), self->root, n) ;
			if (found) {
				return urgc_set_var_for_return_class((void ** )__outRef__, found) ; 
			}
			n = n->parent;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


void  SuiDesigner$EditCtx$setState(SuiDesigner$EditCtx *  self, SuiView$TreeState*  state){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(state);

	URGC_VAR_CLEANUP SuiDesigner$__Block_68_35*  __var___Block_68_35 = (__var___Block_68_35=NULL,urgc_init_var((void**)&__var___Block_68_35, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_68_35) , __finiBlock___Block_68_35) ));
	urgc_set_field_class(__var___Block_68_35, (void * )offsetof(SuiDesigner$__Block_68_35, self) , self) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$EditCtx, state) , state) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_70_36*  tmpReturn_1 = NULL;
	urgc_set_field(state, (void * )offsetof(SuiView$TreeState, cbSelectedIdChanged) , __make___Closure_70_36(&tmpReturn_1, __var___Block_68_35) ) ;
}


void  SuiDesigner$EditCtx$onSelectedChanged(SuiDesigner$EditCtx *  self){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditEventSelectedChanged*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner$EditEventSelectedChanged_new(&e) ));
	((SuiCore$Emitter * )self)->emit(self, e) ;
}


void  SuiDesigner$EditCtx$closeCurrentPrefab(SuiDesigner$EditCtx *  self){
	if (!self->prefab) {
		return ; 
	}
	if (self->root) {
		self->root->removeSelf(self->root) ;
	}
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$EditCtx, root) , NULL) ;
	self->roots->clear(self->roots) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$EditCtx, prefab) , NULL) ;
}


void  SuiDesigner$EditCtx$openPrefab(SuiDesigner$EditCtx *  self, const char *  path){
	self->closeCurrentPrefab(self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Prefab*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$Prefab*  o = SuiDesigner$Prefab_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$EditCtx, prefab) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$Prefab*  tmpReturn_2 = NULL;
		o->loadByPathCstr(&tmpReturn_2, o, "../asset/button.prefab.json") ;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$EditCtx, root) , o->root) ;
		self->root->printTree(self->root, 0) ;
		self->root->updateSubTreeNodes(self->root) ;
		self->roots->clear(self->roots) ;
		self->roots->add(self->roots, self->root) ;
	}
}


void  SuiDesigner$EditCtx$init(SuiDesigner$EditCtx *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_110_15*  __var___Block_110_15 = (__var___Block_110_15=NULL,urgc_init_var((void**)&__var___Block_110_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_110_15) , __finiBlock___Block_110_15) ));
	urgc_set_field_class(__var___Block_110_15, (void * )offsetof(SuiDesigner$__Block_110_15, self) , self) ;
	SuiDesigner$registerNodes() ;
	URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_112_23*  tmpReturn_2 = NULL;
	SuiCore$mkTimerTimeout(&tmpReturn_1, __make___Closure_112_23(&tmpReturn_2, __var___Block_110_15) , 300) ;
}



static void  __finiBlock___Block_68_35(SuiDesigner$__Block_68_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_68_35, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_110_15(SuiDesigner$__Block_110_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_110_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_70_36(SuiDesigner$__Closure_70_36 *  self, SuiView$TreeState *  state){
	self->__var___Block_68_35->self->onSelectedChanged(self->__var___Block_68_35->self) ;
}

static void  __fini___Closure_70_36(SuiDesigner$__Closure_70_36 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_70_36, __var___Block_68_35) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_70_36*  __make___Closure_70_36(SuiDesigner$__Closure_70_36 **  __outRef__, SuiDesigner$__Block_68_35 *  __var___Block_68_35){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_70_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_70_36) , __fini___Closure_70_36) ));
	self->invoke = __fn___Closure_70_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_70_36, __var___Block_68_35) , __var___Block_68_35) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_112_23(SuiDesigner$__Closure_112_23 *  self){
	printf("========================================timer open prefab\n") ;
	self->__var___Block_110_15->self->openPrefab(self->__var___Block_110_15->self, "../asset/button.prefab.json") ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeChanged*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$EventANodeChanged*  o = SuiDesigner$EventANodeChanged_new(&tmpNewOwner_1) ;
		
	
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeChanged, anode) , SuiDesigner$EditCtx_ins(&tmpReturn_2) ->root) ;
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

static void  __fini___Closure_112_23(SuiDesigner$__Closure_112_23 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_112_23, __var___Block_110_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_112_23*  __make___Closure_112_23(SuiDesigner$__Closure_112_23 **  __outRef__, SuiDesigner$__Block_110_15 *  __var___Block_110_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_112_23*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_112_23) , __fini___Closure_112_23) ));
	self->invoke = __fn___Closure_112_23;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_112_23, __var___Block_110_15) , __var___Block_110_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiDesigner$EditCtx*  SuiDesigner$EditCtx_ins(SuiDesigner$EditCtx **  __outRef__){
	static URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  ins = NULL;
	if (!ins) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&ins, SuiDesigner$EditCtx_new(&tmpNewOwner_1) ) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ins) ; 
}



