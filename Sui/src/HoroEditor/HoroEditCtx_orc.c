
#include "HoroEditCtx_orc.h" 

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
#include "../SuiDesigner/Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/RegisterNodes_orc.h"
#include "../SuiDesigner/DrawDegree_orc.h"
#include "../SuiDesigner/UiAction_orc.h"
#include "../SuiDesigner/EventFileItemChanged_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Obj3d_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_63_35 SuiDesigner$__Block_63_35;

typedef struct tagSuiDesigner$__Closure_65_36 SuiDesigner$__Closure_65_36;



struct tagSuiDesigner$__Block_63_35 {
	SuiDesigner$HoroEditCtx*  self ;
};





struct tagSuiDesigner$__Closure_65_36 {
	void  (*invoke)(SuiDesigner$__Closure_65_36 *  self, SuiView$TreeState *  state);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_63_35*  __var___Block_63_35 ;
};





// static function declaration
static void  __finiBlock___Block_63_35(SuiDesigner$__Block_63_35 *  self);
static void  __fn___Closure_65_36(SuiDesigner$__Closure_65_36 *  self, SuiView$TreeState *  state);
static void  __fini___Closure_65_36(SuiDesigner$__Closure_65_36 *  self);
static SuiDesigner$__Closure_65_36*  __make___Closure_65_36(SuiDesigner$__Closure_65_36 **  __outRef__, SuiDesigner$__Block_63_35 *  __var___Block_63_35);



//vtable instance
Vtable_SuiDesigner$EventHoroSceneChanged _vtable_SuiDesigner$EventHoroSceneChanged;

// init meta

void SuiDesigner$EventHoroSceneChanged_initMeta(Vtable_SuiDesigner$EventHoroSceneChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$EventHoroSceneChanged* Vtable_SuiDesigner$EventHoroSceneChanged_init(Vtable_SuiDesigner$EventHoroSceneChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EventHoroSceneChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EventHoroSceneChanged_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EventHoroSceneChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EventHoroSceneChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EventHoroSceneChanged_fini(SuiDesigner$EventHoroSceneChanged *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放


}

// init fields function


void SuiDesigner$EventHoroSceneChanged_init_fields(SuiDesigner$EventHoroSceneChanged *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EventHoroSceneChanged_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$EventHoroSceneChanged_init(SuiDesigner$EventHoroSceneChanged *self, void *pOwner){
    Vtable_SuiDesigner$EventHoroSceneChanged_init(&_vtable_SuiDesigner$EventHoroSceneChanged);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EventHoroSceneChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EventHoroSceneChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EventHoroSceneChanged * SuiDesigner$EventHoroSceneChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EventHoroSceneChanged *self = calloc(1, sizeof(SuiDesigner$EventHoroSceneChanged));
	
    SuiDesigner$EventHoroSceneChanged_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$EventHoroSelectedChanged _vtable_SuiDesigner$EventHoroSelectedChanged;

// init meta

void SuiDesigner$EventHoroSelectedChanged_initMeta(Vtable_SuiDesigner$EventHoroSelectedChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$EventHoroSelectedChanged* Vtable_SuiDesigner$EventHoroSelectedChanged_init(Vtable_SuiDesigner$EventHoroSelectedChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EventHoroSelectedChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EventHoroSelectedChanged_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EventHoroSelectedChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EventHoroSelectedChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EventHoroSelectedChanged_fini(SuiDesigner$EventHoroSelectedChanged *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放


}

// init fields function


void SuiDesigner$EventHoroSelectedChanged_init_fields(SuiDesigner$EventHoroSelectedChanged *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EventHoroSelectedChanged_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$EventHoroSelectedChanged_init(SuiDesigner$EventHoroSelectedChanged *self, void *pOwner){
    Vtable_SuiDesigner$EventHoroSelectedChanged_init(&_vtable_SuiDesigner$EventHoroSelectedChanged);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EventHoroSelectedChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EventHoroSelectedChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EventHoroSelectedChanged * SuiDesigner$EventHoroSelectedChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EventHoroSelectedChanged *self = calloc(1, sizeof(SuiDesigner$EventHoroSelectedChanged));
	
    SuiDesigner$EventHoroSelectedChanged_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$HoroEditCtx _vtable_SuiDesigner$HoroEditCtx;

// init meta

void SuiDesigner$HoroEditCtx_initMeta(Vtable_SuiDesigner$HoroEditCtx *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "state", ((Vtable_Object*)Vtable_SuiView$TreeState_init(0)), offsetof(SuiDesigner$HoroEditCtx, state), true, false, 1);
	orc_metaField_class(&pNext, "sceneView", ((Vtable_Object*)Vtable_Sgl$SglSceneView_init(0)), offsetof(SuiDesigner$HoroEditCtx, sceneView), true, false, 1);
	orc_metaField_class(&pNext, "roots", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$HoroEditCtx, roots), true, false, 1);
	orc_metaField_class(&pNext, "hoverNode", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$HoroEditCtx, hoverNode), true, false, 1);

	orc_metaField_method(&pNext, "setState", offsetof(SuiDesigner$HoroEditCtx, setState));
	orc_metaField_method(&pNext, "onSelectedChanged", offsetof(SuiDesigner$HoroEditCtx, onSelectedChanged));
	orc_metaField_method(&pNext, "setSceneView", offsetof(SuiDesigner$HoroEditCtx, setSceneView));
	orc_metaField_method(&pNext, "getScene", offsetof(SuiDesigner$HoroEditCtx, getScene));
}


// vtable init


Vtable_SuiDesigner$HoroEditCtx* Vtable_SuiDesigner$HoroEditCtx_init(Vtable_SuiDesigner$HoroEditCtx* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$HoroEditCtx;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$HoroEditCtx_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$HoroEditCtx";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$HoroEditCtx_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$HoroEditCtx_fini(SuiDesigner$HoroEditCtx *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$HoroEditCtx_init_fields(SuiDesigner$HoroEditCtx *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$HoroEditCtx_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$HoroEditCtx*)self)->state, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$HoroEditCtx*)self)->sceneView, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$HoroEditCtx*)self)->roots, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$HoroEditCtx*)self)->hoverNode, NULL);
    }
	((SuiDesigner$HoroEditCtx*)self)->setState = (void*)SuiDesigner$HoroEditCtx$setState;
	((SuiDesigner$HoroEditCtx*)self)->onSelectedChanged = (void*)SuiDesigner$HoroEditCtx$onSelectedChanged;
	((SuiDesigner$HoroEditCtx*)self)->setSceneView = (void*)SuiDesigner$HoroEditCtx$setSceneView;
	((SuiDesigner$HoroEditCtx*)self)->getScene = (void*)SuiDesigner$HoroEditCtx$getScene;
}

// init function

void SuiDesigner$HoroEditCtx_init(SuiDesigner$HoroEditCtx *self, void *pOwner){
    Vtable_SuiDesigner$HoroEditCtx_init(&_vtable_SuiDesigner$HoroEditCtx);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$HoroEditCtx;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$HoroEditCtx_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$HoroEditCtx * SuiDesigner$HoroEditCtx_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$HoroEditCtx *self = calloc(1, sizeof(SuiDesigner$HoroEditCtx));
	
    SuiDesigner$HoroEditCtx_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$HoroEditCtx$setState(SuiDesigner$HoroEditCtx *  self, SuiView$TreeState*  state){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(state);

	URGC_VAR_CLEANUP SuiDesigner$__Block_63_35*  __var___Block_63_35 = (__var___Block_63_35=NULL,urgc_init_var((void**)&__var___Block_63_35, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_63_35) , __finiBlock___Block_63_35) ));
	urgc_set_field_class(__var___Block_63_35, (void * )offsetof(SuiDesigner$__Block_63_35, self) , self) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$HoroEditCtx, state) , state) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_65_36*  tmpReturn_1 = NULL;
	urgc_set_field(state, (void * )offsetof(SuiView$TreeState, cbSelectedIdChanged) , __make___Closure_65_36(&tmpReturn_1, __var___Block_63_35) ) ;
}


void  SuiDesigner$HoroEditCtx$onSelectedChanged(SuiDesigner$HoroEditCtx *  self){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventHoroSelectedChanged*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner$EventHoroSelectedChanged_new(&e) ));
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, e) ;
}


void  SuiDesigner$HoroEditCtx$setSceneView(SuiDesigner$HoroEditCtx *  self, Sgl$SglSceneView *  sceneView){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$HoroEditCtx, sceneView) , sceneView) ;
	self->roots->clear(self->roots) ;
	if (sceneView) {
		self->roots->add(self->roots, self->sceneView->scene) ;
	}
}


Sgl$Scene *  SuiDesigner$HoroEditCtx$getScene(SuiDesigner$HoroEditCtx *  self){
	if (self->sceneView) {
		return self->sceneView->scene; 
	}
	return NULL; 
}



static void  __finiBlock___Block_63_35(SuiDesigner$__Block_63_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_63_35, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_65_36(SuiDesigner$__Closure_65_36 *  self, SuiView$TreeState *  state){
	self->__var___Block_63_35->self->onSelectedChanged(self->__var___Block_63_35->self) ;
}

static void  __fini___Closure_65_36(SuiDesigner$__Closure_65_36 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_65_36, __var___Block_63_35) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_65_36*  __make___Closure_65_36(SuiDesigner$__Closure_65_36 **  __outRef__, SuiDesigner$__Block_63_35 *  __var___Block_63_35){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_65_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_65_36) , __fini___Closure_65_36) ));
	self->invoke = __fn___Closure_65_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_65_36, __var___Block_63_35) , __var___Block_63_35) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



