
#include "SglEditCtx_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
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
#include "./EventFileItemChanged_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Obj3d_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_62_35 SuiDesigner$__Block_62_35;

typedef struct tagSuiDesigner$__Closure_64_36 SuiDesigner$__Closure_64_36;



struct tagSuiDesigner$__Block_62_35 {
	SuiDesigner$SglEditCtx*  self ;
};





struct tagSuiDesigner$__Closure_64_36 {
	void  (*invoke)(SuiDesigner$__Closure_64_36 *  self, SuiView$TreeState *  state);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_62_35*  __var___Block_62_35 ;
};





// static function declaration
static void  __finiBlock___Block_62_35(SuiDesigner$__Block_62_35 *  self);
static void  __fn___Closure_64_36(SuiDesigner$__Closure_64_36 *  self, SuiView$TreeState *  state);
static void  __fini___Closure_64_36(SuiDesigner$__Closure_64_36 *  self);
static SuiDesigner$__Closure_64_36*  __make___Closure_64_36(SuiDesigner$__Closure_64_36 **  __outRef__, SuiDesigner$__Block_62_35 *  __var___Block_62_35);



//vtable instance
Vtable_SuiDesigner$EventSglSceneChanged _vtable_SuiDesigner$EventSglSceneChanged;

// init meta

void SuiDesigner$EventSglSceneChanged_initMeta(Vtable_SuiDesigner$EventSglSceneChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$EventSglSceneChanged* Vtable_SuiDesigner$EventSglSceneChanged_init(Vtable_SuiDesigner$EventSglSceneChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EventSglSceneChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EventSglSceneChanged_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EventSglSceneChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EventSglSceneChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EventSglSceneChanged_fini(SuiDesigner$EventSglSceneChanged *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$EventSglSceneChanged_init_fields(SuiDesigner$EventSglSceneChanged *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EventSglSceneChanged_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$EventSglSceneChanged_init(SuiDesigner$EventSglSceneChanged *self, void *pOwner){
    Vtable_SuiDesigner$EventSglSceneChanged_init(&_vtable_SuiDesigner$EventSglSceneChanged);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EventSglSceneChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EventSglSceneChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EventSglSceneChanged * SuiDesigner$EventSglSceneChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EventSglSceneChanged *self = calloc(1, sizeof(SuiDesigner$EventSglSceneChanged));
	
    SuiDesigner$EventSglSceneChanged_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$EventSglSelectedChanged _vtable_SuiDesigner$EventSglSelectedChanged;

// init meta

void SuiDesigner$EventSglSelectedChanged_initMeta(Vtable_SuiDesigner$EventSglSelectedChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$EventSglSelectedChanged* Vtable_SuiDesigner$EventSglSelectedChanged_init(Vtable_SuiDesigner$EventSglSelectedChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EventSglSelectedChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EventSglSelectedChanged_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EventSglSelectedChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EventSglSelectedChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EventSglSelectedChanged_fini(SuiDesigner$EventSglSelectedChanged *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$EventSglSelectedChanged_init_fields(SuiDesigner$EventSglSelectedChanged *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EventSglSelectedChanged_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$EventSglSelectedChanged_init(SuiDesigner$EventSglSelectedChanged *self, void *pOwner){
    Vtable_SuiDesigner$EventSglSelectedChanged_init(&_vtable_SuiDesigner$EventSglSelectedChanged);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EventSglSelectedChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EventSglSelectedChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EventSglSelectedChanged * SuiDesigner$EventSglSelectedChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EventSglSelectedChanged *self = calloc(1, sizeof(SuiDesigner$EventSglSelectedChanged));
	
    SuiDesigner$EventSglSelectedChanged_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$SglEditCtx _vtable_SuiDesigner$SglEditCtx;

// init meta

void SuiDesigner$SglEditCtx_initMeta(Vtable_SuiDesigner$SglEditCtx *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "state", ((Vtable_Object*)Vtable_SuiView$TreeState_init(0)), offsetof(SuiDesigner$SglEditCtx, state), true, false, 1);
	orc_metaField_class(&pNext, "sceneView", ((Vtable_Object*)Vtable_Sgl$SglSceneView_init(0)), offsetof(SuiDesigner$SglEditCtx, sceneView), true, false, 1);
	orc_metaField_class(&pNext, "roots", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$SglEditCtx, roots), true, false, 1);
	orc_metaField_class(&pNext, "hoverNode", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$SglEditCtx, hoverNode), true, false, 1);

	orc_metaField_method(&pNext, "setState", offsetof(SuiDesigner$SglEditCtx, setState));
	orc_metaField_method(&pNext, "onSelectedChanged", offsetof(SuiDesigner$SglEditCtx, onSelectedChanged));
	orc_metaField_method(&pNext, "setSceneView", offsetof(SuiDesigner$SglEditCtx, setSceneView));
	orc_metaField_method(&pNext, "getScene", offsetof(SuiDesigner$SglEditCtx, getScene));
}


// vtable init


Vtable_SuiDesigner$SglEditCtx* Vtable_SuiDesigner$SglEditCtx_init(Vtable_SuiDesigner$SglEditCtx* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SglEditCtx;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SglEditCtx_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SglEditCtx";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SglEditCtx_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SglEditCtx_fini(SuiDesigner$SglEditCtx *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SglEditCtx*)self)->state);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SglEditCtx*)self)->sceneView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SglEditCtx*)self)->roots);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SglEditCtx*)self)->hoverNode);

}

// init fields function


void SuiDesigner$SglEditCtx_init_fields(SuiDesigner$SglEditCtx *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SglEditCtx_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$SglEditCtx*)self)->state, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$SglEditCtx*)self)->sceneView, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SglEditCtx*)self)->roots, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$SglEditCtx*)self)->hoverNode, NULL);
    }
	((SuiDesigner$SglEditCtx*)self)->setState = (void*)SuiDesigner$SglEditCtx$setState;
	((SuiDesigner$SglEditCtx*)self)->onSelectedChanged = (void*)SuiDesigner$SglEditCtx$onSelectedChanged;
	((SuiDesigner$SglEditCtx*)self)->setSceneView = (void*)SuiDesigner$SglEditCtx$setSceneView;
	((SuiDesigner$SglEditCtx*)self)->getScene = (void*)SuiDesigner$SglEditCtx$getScene;
}

// init function

void SuiDesigner$SglEditCtx_init(SuiDesigner$SglEditCtx *self, void *pOwner){
    Vtable_SuiDesigner$SglEditCtx_init(&_vtable_SuiDesigner$SglEditCtx);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SglEditCtx;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SglEditCtx_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SglEditCtx * SuiDesigner$SglEditCtx_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SglEditCtx *self = calloc(1, sizeof(SuiDesigner$SglEditCtx));
	
    SuiDesigner$SglEditCtx_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SglEditCtx$setState(SuiDesigner$SglEditCtx *  self, SuiView$TreeState*  state){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(state);

	URGC_VAR_CLEANUP SuiDesigner$__Block_62_35*  __var___Block_62_35 = (__var___Block_62_35=NULL,urgc_init_var((void**)&__var___Block_62_35, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_62_35) , __finiBlock___Block_62_35) ));
	urgc_set_field_class(__var___Block_62_35, (void * )offsetof(SuiDesigner$__Block_62_35, self) , self) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SglEditCtx, state) , state) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_64_36*  tmpReturn_1 = NULL;
	urgc_set_field(state, (void * )offsetof(SuiView$TreeState, cbSelectedIdChanged) , __make___Closure_64_36(&tmpReturn_1, __var___Block_62_35) ) ;
}


void  SuiDesigner$SglEditCtx$onSelectedChanged(SuiDesigner$SglEditCtx *  self){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventSglSelectedChanged*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner$EventSglSelectedChanged_new(&e) ));
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, e) ;
}


void  SuiDesigner$SglEditCtx$setSceneView(SuiDesigner$SglEditCtx *  self, Sgl$SglSceneView *  sceneView){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SglEditCtx, sceneView) , sceneView) ;
	self->roots->clear(self->roots) ;
	if (sceneView) {
		self->roots->add(self->roots, self->sceneView->scene) ;
	}
}


Sgl$Scene *  SuiDesigner$SglEditCtx$getScene(SuiDesigner$SglEditCtx *  self){
	if (self->sceneView) {
		return self->sceneView->scene; 
	}
	return NULL; 
}



static void  __finiBlock___Block_62_35(SuiDesigner$__Block_62_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_62_35, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_64_36(SuiDesigner$__Closure_64_36 *  self, SuiView$TreeState *  state){
	self->__var___Block_62_35->self->onSelectedChanged(self->__var___Block_62_35->self) ;
}

static void  __fini___Closure_64_36(SuiDesigner$__Closure_64_36 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_64_36, __var___Block_62_35) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_64_36*  __make___Closure_64_36(SuiDesigner$__Closure_64_36 **  __outRef__, SuiDesigner$__Block_62_35 *  __var___Block_62_35){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_64_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_64_36) , __fini___Closure_64_36) ));
	self->invoke = __fn___Closure_64_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_64_36, __var___Block_62_35) , __var___Block_62_35) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



