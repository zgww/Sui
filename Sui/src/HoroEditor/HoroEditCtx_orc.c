
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
#include "../SuiDesigner/Prefab_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Obj3d_orc.h"


// static struct 
typedef struct tagHoroEditor$__Block_66_35 HoroEditor$__Block_66_35;

typedef struct tagHoroEditor$__Closure_68_36 HoroEditor$__Closure_68_36;



struct tagHoroEditor$__Block_66_35 {
	HoroEditor$HoroEditCtx*  self ;
};





struct tagHoroEditor$__Closure_68_36 {
	void  (*invoke)(HoroEditor$__Closure_68_36 *  self, SuiView$TreeState *  state);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_66_35*  __var___Block_66_35 ;
};





// static function declaration
static void  __finiBlock___Block_66_35(HoroEditor$__Block_66_35 *  self);
static void  __fn___Closure_68_36(HoroEditor$__Closure_68_36 *  self, SuiView$TreeState *  state);
static void  __fini___Closure_68_36(HoroEditor$__Closure_68_36 *  self);
static HoroEditor$__Closure_68_36*  __make___Closure_68_36(HoroEditor$__Closure_68_36 **  __outRef__, HoroEditor$__Block_66_35 *  __var___Block_66_35);



//vtable instance
Vtable_HoroEditor$EventHoroSceneChanged _vtable_HoroEditor$EventHoroSceneChanged;

// init meta

void HoroEditor$EventHoroSceneChanged_initMeta(Vtable_HoroEditor$EventHoroSceneChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_HoroEditor$EventHoroSceneChanged* Vtable_HoroEditor$EventHoroSceneChanged_init(Vtable_HoroEditor$EventHoroSceneChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$EventHoroSceneChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$EventHoroSceneChanged_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$EventHoroSceneChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$EventHoroSceneChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$EventHoroSceneChanged_fini(HoroEditor$EventHoroSceneChanged *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放


}

// init fields function


void HoroEditor$EventHoroSceneChanged_init_fields(HoroEditor$EventHoroSceneChanged *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)HoroEditor$EventHoroSceneChanged_fini;
	//fields
    {
	
    }
	
}

// init function

void HoroEditor$EventHoroSceneChanged_init(HoroEditor$EventHoroSceneChanged *self, void *pOwner){
    Vtable_HoroEditor$EventHoroSceneChanged_init(&_vtable_HoroEditor$EventHoroSceneChanged);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$EventHoroSceneChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$EventHoroSceneChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$EventHoroSceneChanged * HoroEditor$EventHoroSceneChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$EventHoroSceneChanged *self = calloc(1, sizeof(HoroEditor$EventHoroSceneChanged));
	
    HoroEditor$EventHoroSceneChanged_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_HoroEditor$EventHoroSelectedChanged _vtable_HoroEditor$EventHoroSelectedChanged;

// init meta

void HoroEditor$EventHoroSelectedChanged_initMeta(Vtable_HoroEditor$EventHoroSelectedChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_HoroEditor$EventHoroSelectedChanged* Vtable_HoroEditor$EventHoroSelectedChanged_init(Vtable_HoroEditor$EventHoroSelectedChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$EventHoroSelectedChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$EventHoroSelectedChanged_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$EventHoroSelectedChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$EventHoroSelectedChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$EventHoroSelectedChanged_fini(HoroEditor$EventHoroSelectedChanged *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放


}

// init fields function


void HoroEditor$EventHoroSelectedChanged_init_fields(HoroEditor$EventHoroSelectedChanged *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)HoroEditor$EventHoroSelectedChanged_fini;
	//fields
    {
	
    }
	
}

// init function

void HoroEditor$EventHoroSelectedChanged_init(HoroEditor$EventHoroSelectedChanged *self, void *pOwner){
    Vtable_HoroEditor$EventHoroSelectedChanged_init(&_vtable_HoroEditor$EventHoroSelectedChanged);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$EventHoroSelectedChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$EventHoroSelectedChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$EventHoroSelectedChanged * HoroEditor$EventHoroSelectedChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$EventHoroSelectedChanged *self = calloc(1, sizeof(HoroEditor$EventHoroSelectedChanged));
	
    HoroEditor$EventHoroSelectedChanged_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_HoroEditor$HoroEditCtx _vtable_HoroEditor$HoroEditCtx;

// init meta

void HoroEditor$HoroEditCtx_initMeta(Vtable_HoroEditor$HoroEditCtx *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "state", ((Vtable_Object*)Vtable_SuiView$TreeState_init(0)), offsetof(HoroEditor$HoroEditCtx, state), true, false, 1);
	orc_metaField_class(&pNext, "sceneView", ((Vtable_Object*)Vtable_Sgl$SglSceneView_init(0)), offsetof(HoroEditor$HoroEditCtx, sceneView), true, false, 1);
	orc_metaField_class(&pNext, "roots", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(HoroEditor$HoroEditCtx, roots), true, false, 1);
	orc_metaField_class(&pNext, "hoverNode", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(HoroEditor$HoroEditCtx, hoverNode), true, false, 1);
	orc_metaField_class(&pNext, "prefab", ((Vtable_Object*)Vtable_SuiDesigner$Prefab_init(0)), offsetof(HoroEditor$HoroEditCtx, prefab), true, false, 1);

	orc_metaField_method(&pNext, "setState", offsetof(HoroEditor$HoroEditCtx, setState));
	orc_metaField_method(&pNext, "findANodeByNode", offsetof(HoroEditor$HoroEditCtx, findANodeByNode));
	orc_metaField_method(&pNext, "onSelectedChanged", offsetof(HoroEditor$HoroEditCtx, onSelectedChanged));
	orc_metaField_method(&pNext, "setSceneView", offsetof(HoroEditor$HoroEditCtx, setSceneView));
	orc_metaField_method(&pNext, "getScene", offsetof(HoroEditor$HoroEditCtx, getScene));
	orc_metaField_method(&pNext, "closeCurrentPrefab", offsetof(HoroEditor$HoroEditCtx, closeCurrentPrefab));
	orc_metaField_method(&pNext, "openPrefab", offsetof(HoroEditor$HoroEditCtx, openPrefab));
	orc_metaField_method(&pNext, "getRoot", offsetof(HoroEditor$HoroEditCtx, getRoot));
}


// vtable init


Vtable_HoroEditor$HoroEditCtx* Vtable_HoroEditor$HoroEditCtx_init(Vtable_HoroEditor$HoroEditCtx* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroEditCtx;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroEditCtx_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroEditCtx";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroEditCtx_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroEditCtx_fini(HoroEditor$HoroEditCtx *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void HoroEditor$HoroEditCtx_init_fields(HoroEditor$HoroEditCtx *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroEditCtx_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditCtx*)self)->state, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditCtx*)self)->sceneView, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditCtx*)self)->roots, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditCtx*)self)->hoverNode, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditCtx*)self)->prefab, NULL);
    }
	((HoroEditor$HoroEditCtx*)self)->setState = (void*)HoroEditor$HoroEditCtx$setState;
	((HoroEditor$HoroEditCtx*)self)->findANodeByNode = (void*)HoroEditor$HoroEditCtx$findANodeByNode;
	((HoroEditor$HoroEditCtx*)self)->onSelectedChanged = (void*)HoroEditor$HoroEditCtx$onSelectedChanged;
	((HoroEditor$HoroEditCtx*)self)->setSceneView = (void*)HoroEditor$HoroEditCtx$setSceneView;
	((HoroEditor$HoroEditCtx*)self)->getScene = (void*)HoroEditor$HoroEditCtx$getScene;
	((HoroEditor$HoroEditCtx*)self)->closeCurrentPrefab = (void*)HoroEditor$HoroEditCtx$closeCurrentPrefab;
	((HoroEditor$HoroEditCtx*)self)->openPrefab = (void*)HoroEditor$HoroEditCtx$openPrefab;
	((HoroEditor$HoroEditCtx*)self)->getRoot = (void*)HoroEditor$HoroEditCtx$getRoot;
}

// init function

void HoroEditor$HoroEditCtx_init(HoroEditor$HoroEditCtx *self, void *pOwner){
    Vtable_HoroEditor$HoroEditCtx_init(&_vtable_HoroEditor$HoroEditCtx);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroEditCtx;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroEditCtx_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroEditCtx * HoroEditor$HoroEditCtx_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroEditCtx *self = calloc(1, sizeof(HoroEditor$HoroEditCtx));
	
    HoroEditor$HoroEditCtx_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$HoroEditCtx$setState(HoroEditor$HoroEditCtx *  self, SuiView$TreeState*  state){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(state);

	URGC_VAR_CLEANUP HoroEditor$__Block_66_35*  __var___Block_66_35 = (__var___Block_66_35=NULL,urgc_init_var((void**)&__var___Block_66_35, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_66_35) , __finiBlock___Block_66_35) ));
	urgc_set_field_class(__var___Block_66_35, (void * )offsetof(HoroEditor$__Block_66_35, self) , self) ;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditCtx, state) , state) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_68_36*  tmpReturn_1 = NULL;
	urgc_set_field(state, (void * )offsetof(SuiView$TreeState, cbSelectedIdChanged) , __make___Closure_68_36(&tmpReturn_1, __var___Block_66_35) ) ;
}


SuiDesigner$ANode*  HoroEditor$HoroEditCtx$findANodeByNode(SuiDesigner$ANode **  __outRef__, HoroEditor$HoroEditCtx *  self, SuiCore$Node *  node){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  tmpReturn_1 = NULL;
	SuiDesigner$ANode *  root = self->getRoot(&tmpReturn_1, self) ;
	if (root && root->node) {
		SuiCore$Node *  scene = root->node->parent;
		SuiCore$Node *  n = node;
		while (n && n != scene) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  found = root->findANodeByNode((found = NULL,&found), root, n) ;
			if (found) {
				return urgc_set_var_for_return_class((void ** )__outRef__, found) ; 
			}
			n = n->parent;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


void  HoroEditor$HoroEditCtx$onSelectedChanged(HoroEditor$HoroEditCtx *  self){
	URGC_VAR_CLEANUP_CLASS HoroEditor$EventHoroSelectedChanged*  e = (e=NULL,urgc_init_var_class((void**)&e, HoroEditor$EventHoroSelectedChanged_new(&e) ));
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, e) ;
}


void  HoroEditor$HoroEditCtx$setSceneView(HoroEditor$HoroEditCtx *  self, Sgl$SglSceneView *  sceneView){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditCtx, sceneView) , sceneView) ;
	if (sceneView) {
		
	}
}


Sgl$Scene *  HoroEditor$HoroEditCtx$getScene(HoroEditor$HoroEditCtx *  self){
	if (self->sceneView) {
		return self->sceneView->scene; 
	}
	return NULL; 
}


void  HoroEditor$HoroEditCtx$closeCurrentPrefab(HoroEditor$HoroEditCtx *  self){
	if (!self->prefab) {
		return ; 
	}
	for (int  i = 0; i < self->roots->size(self->roots) ; i++) {
		SuiDesigner$ANode *  root = (SuiDesigner$ANode * )self->roots->get(self->roots, i) ;
		root->removeSelf(root) ;
	}
	self->roots->clear(self->roots) ;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditCtx, prefab) , NULL) ;
}


void  HoroEditor$HoroEditCtx$openPrefab(HoroEditor$HoroEditCtx *  self, const char *  path){
	self->closeCurrentPrefab(self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Prefab*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$Prefab*  o = SuiDesigner$Prefab_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditCtx, prefab) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$Prefab*  tmpReturn_2 = NULL;
		o->loadByPathCstr(&tmpReturn_2, o, path) ;
		SuiDesigner$ANode *  tmpThis_1 = NULL;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  tmpReturn_3 = NULL;
		(tmpThis_1 = self->getRoot(&tmpReturn_3, self) )->printTree(tmpThis_1, 0) ;
		SuiDesigner$ANode *  tmpThis_2 = NULL;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  tmpReturn_4 = NULL;
		(tmpThis_2 = self->getRoot(&tmpReturn_4, self) )->updateSubTreeNodes(tmpThis_2) ;
		self->roots->clear(self->roots) ;
		self->roots->add(self->roots, self->prefab->root) ;
		int  size = self->roots->size(self->roots) ;
		printf("HoroEdit roots. size:%d\n", size) ;
	}
}


SuiDesigner$ANode*  HoroEditor$HoroEditCtx$getRoot(SuiDesigner$ANode **  __outRef__, HoroEditor$HoroEditCtx *  self){
	if (self->prefab) {
		return urgc_set_var_for_return_class((void ** )__outRef__, self->prefab->root) ; 
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}



static void  __finiBlock___Block_66_35(HoroEditor$__Block_66_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_66_35, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_68_36(HoroEditor$__Closure_68_36 *  self, SuiView$TreeState *  state){
	self->__var___Block_66_35->self->onSelectedChanged(self->__var___Block_66_35->self) ;
}

static void  __fini___Closure_68_36(HoroEditor$__Closure_68_36 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_68_36, __var___Block_66_35) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_68_36*  __make___Closure_68_36(HoroEditor$__Closure_68_36 **  __outRef__, HoroEditor$__Block_66_35 *  __var___Block_66_35){
	URGC_VAR_CLEANUP HoroEditor$__Closure_68_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_68_36) , __fini___Closure_68_36) ));
	self->invoke = __fn___Closure_68_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_68_36, __var___Block_66_35) , __var___Block_66_35) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



