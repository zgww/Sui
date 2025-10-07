
#include "AssetDirView_orc.h" 

#include <stdio.h>
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Path_orc.h"
#include "../../Sui/Core/View_orc.h"
#include "../../Sui/Core/ViewBase_orc.h"
#include "../../Sui/Core/Node_orc.h"
#include "../../Sui/Core/Event_orc.h"
#include "../../Sui/Core/Emitter_orc.h"
#include "../../Sui/Dialog/MessageDialog_orc.h"
#include "../../Sui/Dialog/Toast_orc.h"
#include "../../Sui/Core/MouseEvent_orc.h"
#include "../../Sui/View/TextView_orc.h"
#include "../../Sui/View/TreeView_orc.h"
#include "../../Sui/View/ImageView_orc.h"
#include "../../Sui/View/ViewBuilder_orc.h"
#include "../../Sui/View/ScrollArea_orc.h"
#include "../../Sui/View/MenuNative_orc.h"
#include "../../Sui/View/HoverViewEffect_orc.h"
#include "../../Sui/Layout/LayoutLinear_orc.h"
#include "../../Sui/Layout/RowWrap_orc.h"
#include "../../Sui/Layout/LayoutAlign_orc.h"
#include "../FileItem_orc.h"
#include "../UiAction_orc.h"
#include "../../HoroEditor/UiAct_orc.h"
#include "../Theme_orc.h"
#include "../Project_orc.h"
#include "../EventANodeChanged_orc.h"
#include "../EventFileItemChanged_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_97_15 SuiDesigner$__Block_97_15;

typedef struct tagSuiDesigner$__Block_264_43 SuiDesigner$__Block_264_43;

typedef struct tagSuiDesigner$__Block_293_50 SuiDesigner$__Block_293_50;

typedef struct tagSuiDesigner$__Block_368_44 SuiDesigner$__Block_368_44;

typedef struct tagSuiDesigner$__Closure_99_38 SuiDesigner$__Closure_99_38;

typedef struct tagSuiDesigner$__Closure_onActive_267 SuiDesigner$__Closure_onActive_267;

typedef struct tagSuiDesigner$__Closure_onActive_310 SuiDesigner$__Closure_onActive_310;

typedef struct tagSuiDesigner$__Closure_378_26 SuiDesigner$__Closure_378_26;



struct tagSuiDesigner$__Block_97_15 {
	SuiDesigner$AssetDirView*  self ;
};





struct tagSuiDesigner$__Block_264_43 {
	SuiDesigner$AssetDirView*  self ;
};





struct tagSuiDesigner$__Block_293_50 {
	SuiDesigner$FileItem*  tmpFi ;
	SuiDesigner$AssetDirView*  self ;
};





struct tagSuiDesigner$__Block_368_44 {
	SuiDesigner$AssetDirView*  self ;
	SuiDesigner$FileItem*  tmpFi ;
};





struct tagSuiDesigner$__Closure_99_38 {
	Orc$List*  (*invoke)(SuiDesigner$__Closure_99_38 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_97_15*  __var___Block_97_15 ;
};





struct tagSuiDesigner$__Closure_onActive_267 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_267 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_264_43*  __var___Block_264_43 ;
};





struct tagSuiDesigner$__Closure_onActive_310 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_310 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_293_50*  __var___Block_293_50 ;
};





struct tagSuiDesigner$__Closure_378_26 {
	void  (*invoke)(SuiDesigner$__Closure_378_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_368_44*  __var___Block_368_44 ;
};





// static function declaration
static void  __finiBlock___Block_97_15(SuiDesigner$__Block_97_15 *  self);
static void  __finiBlock___Block_264_43(SuiDesigner$__Block_264_43 *  self);
static void  __finiBlock___Block_293_50(SuiDesigner$__Block_293_50 *  self);
static void  __finiBlock___Block_368_44(SuiDesigner$__Block_368_44 *  self);
static Orc$List*  __fn___Closure_99_38(Orc$List **  __outRef__, SuiDesigner$__Closure_99_38 *  self);
static void  __fini___Closure_99_38(SuiDesigner$__Closure_99_38 *  self);
static SuiDesigner$__Closure_99_38*  __make___Closure_99_38(SuiDesigner$__Closure_99_38 **  __outRef__, SuiDesigner$__Block_97_15 *  __var___Block_97_15);
static void  __fn___Closure_onActive_267(SuiDesigner$__Closure_onActive_267 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_267(SuiDesigner$__Closure_onActive_267 *  self);
static SuiDesigner$__Closure_onActive_267*  __make___Closure_onActive_267(SuiDesigner$__Closure_onActive_267 **  __outRef__, SuiDesigner$__Block_264_43 *  __var___Block_264_43);
static void  __fn___Closure_onActive_310(SuiDesigner$__Closure_onActive_310 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_310(SuiDesigner$__Closure_onActive_310 *  self);
static SuiDesigner$__Closure_onActive_310*  __make___Closure_onActive_310(SuiDesigner$__Closure_onActive_310 **  __outRef__, SuiDesigner$__Block_293_50 *  __var___Block_293_50);
static void  __fn___Closure_378_26(SuiDesigner$__Closure_378_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_378_26(SuiDesigner$__Closure_378_26 *  self);
static SuiDesigner$__Closure_378_26*  __make___Closure_378_26(SuiDesigner$__Closure_378_26 **  __outRef__, SuiDesigner$__Block_368_44 *  __var___Block_368_44);



//vtable instance
Vtable_SuiDesigner$SelectFileItems _vtable_SuiDesigner$SelectFileItems;

// init meta

void SuiDesigner$SelectFileItems_initMeta(Vtable_SuiDesigner$SelectFileItems *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "list", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$SelectFileItems, list), true, false, 1);

	orc_metaField_method(&pNext, "select", offsetof(SuiDesigner$SelectFileItems, select));
	orc_metaField_method(&pNext, "fire_onChanged", offsetof(SuiDesigner$SelectFileItems, fire_onChanged));
	orc_metaField_method(&pNext, "selectMulti", offsetof(SuiDesigner$SelectFileItems, selectMulti));
}


// vtable init


Vtable_SuiDesigner$SelectFileItems* Vtable_SuiDesigner$SelectFileItems_init(Vtable_SuiDesigner$SelectFileItems* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SelectFileItems;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SelectFileItems_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SelectFileItems";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SelectFileItems_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SelectFileItems_fini(SuiDesigner$SelectFileItems *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$SelectFileItems_init_fields(SuiDesigner$SelectFileItems *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SelectFileItems_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SelectFileItems*)self)->list, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field(self, (void**)&((SuiDesigner$SelectFileItems*)self)->getAll, NULL);
	urgc_set_field(self, (void**)&((SuiDesigner$SelectFileItems*)self)->onChanged, NULL);
    }
	((SuiDesigner$SelectFileItems*)self)->select = (void*)SuiDesigner$SelectFileItems$select;
	((SuiDesigner$SelectFileItems*)self)->fire_onChanged = (void*)SuiDesigner$SelectFileItems$fire_onChanged;
	((SuiDesigner$SelectFileItems*)self)->selectMulti = (void*)SuiDesigner$SelectFileItems$selectMulti;
}

// init function

void SuiDesigner$SelectFileItems_init(SuiDesigner$SelectFileItems *self, void *pOwner){
    Vtable_SuiDesigner$SelectFileItems_init(&_vtable_SuiDesigner$SelectFileItems);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SelectFileItems;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SelectFileItems_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SelectFileItems * SuiDesigner$SelectFileItems_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SelectFileItems *self = calloc(1, sizeof(SuiDesigner$SelectFileItems));
	
    SuiDesigner$SelectFileItems_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SelectFileItems$select(SuiDesigner$SelectFileItems *  self, SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	self->list->clear(self->list) ;
	self->list->add(self->list, fi) ;
	self->fire_onChanged(self) ;
}


void  SuiDesigner$SelectFileItems$fire_onChanged(SuiDesigner$SelectFileItems *  self){
	if (self->onChanged) {
		(*(self->onChanged))((void * )(self->onChanged)) ;
	}
}


void  SuiDesigner$SelectFileItems$selectMulti(SuiDesigner$SelectFileItems *  self, SuiDesigner$FileItem*  fi, bool  ctrl, bool  shift){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	if (!ctrl && !shift) {
		self->select(self, fi) ;
		return ; 
	}
	if (ctrl) {
		self->list->addOnce(self->list, fi) ;
		self->fire_onChanged(self) ;
		return ; 
	}
	if (shift) {
		if (!self->list->first(self->list) ) {
			self->select(self, fi) ;
			return ; 
		}
		if (self->getAll) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  all = (*(self->getAll))((all = NULL,&all), (void * )(self->getAll)) ;
			if (all) {
				SuiDesigner$FileItem *  last = self->list->last(self->list) ;
				if (last) {
					int  idx = all->indexOf(all, last) ;
					int  idx2 = all->indexOf(all, fi) ;
					URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_1 = NULL;
					urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SelectFileItems, list) , all->span(&tmpReturn_1, all, idx, idx2) ) ;
					self->list->add(self->list, last) ;
					self->fire_onChanged(self) ;
				}
			}
		}
	}
}



URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirView*  SuiDesigner$curAssetDirView = NULL;

//vtable instance
Vtable_SuiDesigner$AssetDirView _vtable_SuiDesigner$AssetDirView;

// init meta

void SuiDesigner$AssetDirView_initMeta(Vtable_SuiDesigner$AssetDirView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "activeFileItems", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$AssetDirView, activeFileItems), true, false, 1);
	orc_metaField_class(&pNext, "parentFileItem", ((Vtable_Object*)Vtable_SuiDesigner$FileItem_init(0)), offsetof(SuiDesigner$AssetDirView, parentFileItem), true, false, 1);
	orc_metaField_class(&pNext, "selectFileItems", ((Vtable_Object*)Vtable_SuiDesigner$SelectFileItems_init(0)), offsetof(SuiDesigner$AssetDirView, selectFileItems), true, false, 1);

	orc_metaField_method(&pNext, "getCurrentDirFileItem", offsetof(SuiDesigner$AssetDirView, getCurrentDirFileItem));
	orc_metaField_method(&pNext, "_openDirectory", offsetof(SuiDesigner$AssetDirView, _openDirectory));
	orc_metaField_method(&pNext, "_routeMenuNativeItem", offsetof(SuiDesigner$AssetDirView, _routeMenuNativeItem));
	orc_metaField_method(&pNext, "_self_onRightClick", offsetof(SuiDesigner$AssetDirView, _self_onRightClick));
	orc_metaField_method(&pNext, "_fileItem_onEvent", offsetof(SuiDesigner$AssetDirView, _fileItem_onEvent));
	orc_metaField_method(&pNext, "reactFileItem", offsetof(SuiDesigner$AssetDirView, reactFileItem));
}


// vtable init


Vtable_SuiDesigner$AssetDirView* Vtable_SuiDesigner$AssetDirView_init(Vtable_SuiDesigner$AssetDirView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$AssetDirView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$AssetDirView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$AssetDirView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$AssetDirView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$AssetDirView_fini(SuiDesigner$AssetDirView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void SuiDesigner$AssetDirView_init_fields(SuiDesigner$AssetDirView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$AssetDirView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$AssetDirView*)self)->activeFileItems, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$AssetDirView*)self)->parentFileItem, NULL);
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SelectFileItems*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$AssetDirView*)self)->selectFileItems, SuiDesigner$SelectFileItems_new(&tmpNewOwner_2) );
    }
	((Object*)self)->ctor = (void*)SuiDesigner$AssetDirView$ctor;
	((SuiDesigner$AssetDirView*)self)->getCurrentDirFileItem = (void*)SuiDesigner$AssetDirView$getCurrentDirFileItem;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiDesigner$AssetDirView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)SuiDesigner$AssetDirView$onMounted;
	((SuiCore$Node*)self)->onUnmounting = (void*)SuiDesigner$AssetDirView$onUnmounting;
	((SuiCore$Node*)self)->react = (void*)SuiDesigner$AssetDirView$react;
	((SuiDesigner$AssetDirView*)self)->_openDirectory = (void*)SuiDesigner$AssetDirView$_openDirectory;
	((SuiDesigner$AssetDirView*)self)->_routeMenuNativeItem = (void*)SuiDesigner$AssetDirView$_routeMenuNativeItem;
	((SuiDesigner$AssetDirView*)self)->_self_onRightClick = (void*)SuiDesigner$AssetDirView$_self_onRightClick;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiDesigner$AssetDirView$onEvent;
	((SuiDesigner$AssetDirView*)self)->_fileItem_onEvent = (void*)SuiDesigner$AssetDirView$_fileItem_onEvent;
	((SuiDesigner$AssetDirView*)self)->reactFileItem = (void*)SuiDesigner$AssetDirView$reactFileItem;
}

// init function

void SuiDesigner$AssetDirView_init(SuiDesigner$AssetDirView *self, void *pOwner){
    Vtable_SuiDesigner$AssetDirView_init(&_vtable_SuiDesigner$AssetDirView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$AssetDirView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$AssetDirView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$AssetDirView * SuiDesigner$AssetDirView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$AssetDirView *self = calloc(1, sizeof(SuiDesigner$AssetDirView));
	
    SuiDesigner$AssetDirView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$AssetDirView$ctor(SuiDesigner$AssetDirView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_97_15*  __var___Block_97_15 = (__var___Block_97_15=NULL,urgc_init_var((void**)&__var___Block_97_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_97_15) , __finiBlock___Block_97_15) ));
	urgc_set_field_class(__var___Block_97_15, (void * )offsetof(SuiDesigner$__Block_97_15, self) , self) ;
	SuiCore$Listener$ctor(self) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_99_38*  tmpReturn_1 = NULL;
	urgc_set_field(self->selectFileItems, (void * )offsetof(SuiDesigner$SelectFileItems, getAll) , __make___Closure_99_38(&tmpReturn_1, __var___Block_97_15) ) ;
}


SuiDesigner$FileItem *  SuiDesigner$AssetDirView$getCurrentDirFileItem(SuiDesigner$AssetDirView *  self){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpReturn_1 = NULL;
	SuiDesigner$Project *  project = SuiDesigner$Project_ins(&tmpReturn_1) ;
	SuiDesigner$FileItem *  curDirFileItem = self->parentFileItem ? self->parentFileItem : project->dirFileItem;
	return curDirFileItem; 
}


void  SuiDesigner$AssetDirView$onListenerEvent(SuiDesigner$AssetDirView *  self, SuiCore$Event *  event){
	if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventANodeChanged_init(NULL))) {
		SuiDesigner$EventANodeChanged *  e = (SuiDesigner$EventANodeChanged * )e;
	}
	else if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventFileItemChanged_init(NULL))) {
		SuiDesigner$EventFileItemChanged *  e = (SuiDesigner$EventFileItemChanged * )e;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  SuiDesigner$AssetDirView$onMounted(SuiDesigner$AssetDirView *  self){
	SuiCore$Node$onMounted(self) ;
	urgc_set_var_class(&SuiDesigner$curAssetDirView, self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->addListener(tmpThis_1, self) ;
}


void  SuiDesigner$AssetDirView$onUnmounting(SuiDesigner$AssetDirView *  self){
	SuiCore$Node$onUnmounting(self) ;
	if (SuiDesigner$curAssetDirView == self) {
		urgc_set_var_class(&SuiDesigner$curAssetDirView, NULL) ;
	}
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  SuiDesigner$AssetDirView$react(SuiDesigner$AssetDirView *  self){
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_1, "column") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_2, "stretch") ) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  project = SuiDesigner$Project_ins((project = NULL,&project)) ;
	SuiDesigner$FileItem *  curDirFileItem = self->parentFileItem ? self->parentFileItem : project->dirFileItem;
	SuiDesigner$AssetDirView *  o = (SuiDesigner$AssetDirView * )self;
	((SuiCore$View * )o)->backgroundColor = t->dir_bg;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutLinearCell*  __scopeVar_153_8 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_153_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_153_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->grow = 1;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_4 = NULL;
	{
		SuiView$ScrollArea*  __scopeVar_163_8 = SuiView$mkScrollArea(&tmpReturn_4, o, 0) , *o = __scopeVar_163_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_163_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_5, "stretch") ) ;
		o->useMaxWidthConstraint = true;
		SuiCore$Inset$setAll(&((SuiCore$View * )o)->margin, 6) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_173_12 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_173_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_173_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$RowWrap*  tmpReturn_7 = NULL;
		{
			SuiLayout$RowWrap*  __scopeVar_177_12 = SuiLayout$mkRowWrap(&tmpReturn_7, o, 0) , *o = __scopeVar_177_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_177_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->alignItems, "start") ;
			int  l = curDirFileItem->children->size(curDirFileItem->children) ;
			for (int  i = 0; i < l; i++) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  fi = (fi=NULL,urgc_init_var_class((void**)&fi, (SuiDesigner$FileItem* )curDirFileItem->children->get(curDirFileItem->children, i) ));
				self->reactFileItem(self, o, fi) ;
			}
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}


void  SuiDesigner$AssetDirView$_openDirectory(SuiDesigner$AssetDirView *  self, SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	if (fi->isDirectory) {
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$AssetDirView, parentFileItem) , fi) ;
		((SuiCore$Node * )self)->invalidReact(self) ;
	}
}


void  SuiDesigner$AssetDirView$_routeMenuNativeItem(SuiDesigner$AssetDirView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	if (item->cmd) {
		if (Orc$String$equals(item->cmd, "OpenFile") ) {
			SuiDesigner$UiAction_openFile(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "CreatePrefab2d") ) {
			SuiDesigner$UiAction_createPrefab(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "CreatePrefab3d") ) {
			HoroEditor$UiAct_createPrefab3d(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "DeleteFileItem") ) {
			SuiDesigner$UiAction_delete(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "RenameFileItem") ) {
			SuiDesigner$UiAction_renameFileItem(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "CreateDirectory") ) {
			SuiDesigner$UiAction_createDirectory(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "OpenDirectory") ) {
			self->_openDirectory(self, fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "ShowImageInNewWindow") ) {
			SuiDesigner$UiAction_showImageInNewWindow(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "ShowFileInfoInNewWindow") ) {
			SuiDesigner$UiAction_showFileInfoInNewWindow(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "ShowFileTextInNewWindow") ) {
			SuiDesigner$UiAction_showFileTextInNewWindow(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "CreateMaterial") ) {
			SuiDesigner$UiAction_createMaterial(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "ShowMaterialInspectorWindow") ) {
			SuiDesigner$UiAction_showMaterialInspectorWindow(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "GotoParentDirectory") ) {
			if (self->parentFileItem && self->parentFileItem->parent) {
				urgc_set_field_class(self, (void * )offsetof(SuiDesigner$AssetDirView, parentFileItem) , self->parentFileItem->parent) ;
				((SuiCore$Node * )self)->invalidReact(self) ;
			}
			return ; 
		}
	}
	SuiDialog$MessageDialog_alert(item->label->str, "tip") ;
}


void  SuiDesigner$AssetDirView$_self_onRightClick(SuiDesigner$AssetDirView *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP SuiDesigner$__Block_264_43*  __var___Block_264_43 = (__var___Block_264_43=NULL,urgc_init_var((void**)&__var___Block_264_43, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_264_43) , __finiBlock___Block_264_43) ));
	urgc_set_field_class(__var___Block_264_43, (void * )offsetof(SuiDesigner$__Block_264_43, self) , self) ;
	if (me->isClickInBubble(me)  && me->button == 3) {
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_1 = NULL;
		{
			SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_1, NULL, NULL, NULL) ;
			
		
			URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_267*  tmpReturn_2 = NULL;
			(urgc_set_var(&onActive, __make___Closure_onActive_267(&tmpReturn_2, __var___Block_264_43) ) );
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_275_16 = SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "返回上级目录") , onActive) , *o = __scopeVar_275_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_5, "GotoParentDirectory") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_276_16 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "创建Prefab2d") , onActive) , *o = __scopeVar_276_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_8, "CreatePrefab2d") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_9 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_277_16 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "创建Prefab3d") , onActive) , *o = __scopeVar_277_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_11, "CreatePrefab3d") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_12 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_278_16 = SuiView$mkMenuNativeItem(&tmpReturn_12, o, Orc$str(&tmpReturn_13, "创建目录") , onActive) , *o = __scopeVar_278_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_14, "CreateDirectory") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
			n->create(n, o) ;
			n->showAtMouse(n) ;
		}
	}
}


void  SuiDesigner$AssetDirView$onEvent(SuiDesigner$AssetDirView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		self->_self_onRightClick(self, (SuiCore$MouseEvent * )e) ;
	}
}


void  SuiDesigner$AssetDirView$_fileItem_onEvent(SuiDesigner$AssetDirView *  self, SuiCore$Event *  e, SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP SuiDesigner$__Block_293_50*  __var___Block_293_50 = (__var___Block_293_50=NULL,urgc_init_var((void**)&__var___Block_293_50, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_293_50) , __finiBlock___Block_293_50) ));
	urgc_set_field_class(__var___Block_293_50, (void * )offsetof(SuiDesigner$__Block_293_50, self) , self) ;
	urgc_set_field_class(__var___Block_293_50, (void * )offsetof(SuiDesigner$__Block_293_50, tmpFi) , fi) ;
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->isClickInBubble(me) ) {
			if (me->isDblClick) {
				self->_openDirectory(self, fi) ;
			}
			else if (me->button == 1) {
				self->selectFileItems->selectMulti(self->selectFileItems, fi, me->ctrl, me->shift) ;
				((SuiCore$Node * )self)->invalidReact(self) ;
			}
			else if (me->button == 3) {
				e->stopPropagation(e) ;
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_1 = NULL;
				{
					SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_1, NULL, NULL, NULL) ;
					
				
					URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
					URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_310*  tmpReturn_2 = NULL;
					(urgc_set_var(&onActive, __make___Closure_onActive_310(&tmpReturn_2, __var___Block_293_50) ) );
					URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
					{
						SuiView$MenuNativeItem*  __scopeVar_319_24 = SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "创建目录") , onActive) , *o = __scopeVar_319_24;
						
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_5, "CreateDirectory") ) ;
					}
					if (fi->isDirectory) {
						URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
						{
							SuiView$MenuNativeItem*  __scopeVar_321_28 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "打开目录") , onActive) , *o = __scopeVar_321_28;
							
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_8, "OpenDirectory") ) ;
						}
					}
					else {
						URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_9 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
						{
							SuiView$MenuNativeItem*  __scopeVar_324_28 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "打开") , onActive) , *o = __scopeVar_324_28;
							
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_11, "OpenFile") ) ;
						}
					}
					if (Orc$Path_isUsualImage(fi->path->str) ) {
						URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_12 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
						{
							SuiView$MenuNativeItem*  __scopeVar_329_28 = SuiView$mkMenuNativeItem(&tmpReturn_12, o, Orc$str(&tmpReturn_13, "新窗口显示图片") , onActive) , *o = __scopeVar_329_28;
							
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_14, "ShowImageInNewWindow") ) ;
						}
					}
					if (!fi->isDirectory) {
						URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_15 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
						{
							SuiView$MenuNativeItem*  __scopeVar_332_28 = SuiView$mkMenuNativeItem(&tmpReturn_15, o, Orc$str(&tmpReturn_16, "属性") , onActive) , *o = __scopeVar_332_28;
							
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_17 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_17, "ShowFileInfoInNewWindow") ) ;
						}
					}
					if (Orc$String$endsWith(fi->filename, ".txt")  || Orc$String$endsWith(fi->filename, ".json")  || Orc$String$endsWith(fi->filename, ".yml")  || Orc$String$endsWith(fi->filename, ".ini")  || Orc$String$endsWith(fi->filename, ".js")  || Orc$String$endsWith(fi->filename, ".lua") ) {
						URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_18 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_19 = NULL;
						{
							SuiView$MenuNativeItem*  __scopeVar_341_28 = SuiView$mkMenuNativeItem(&tmpReturn_18, o, Orc$str(&tmpReturn_19, "新窗口显示文本内容") , onActive) , *o = __scopeVar_341_28;
							
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_20 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_20, "ShowFileTextInNewWindow") ) ;
						}
					}
					if (Orc$String$endsWith(fi->filename, ".vs")  || Orc$String$endsWith(fi->filename, ".fs") ) {
						URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_21 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_22 = NULL;
						{
							SuiView$MenuNativeItem*  __scopeVar_346_28 = SuiView$mkMenuNativeItem(&tmpReturn_21, o, Orc$str(&tmpReturn_22, "创建材质") , onActive) , *o = __scopeVar_346_28;
							
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_23 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_23, "CreateMaterial") ) ;
						}
					}
					if (Orc$String$endsWith(fi->filename, ".matl.json") ) {
						URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_24 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_25 = NULL;
						{
							SuiView$MenuNativeItem*  __scopeVar_350_28 = SuiView$mkMenuNativeItem(&tmpReturn_24, o, Orc$str(&tmpReturn_25, "检视材质") , onActive) , *o = __scopeVar_350_28;
							
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_26 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_26, "ShowMaterialInspectorWindow") ) ;
						}
					}
					URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_27 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_28 = NULL;
					{
						SuiView$MenuNativeItem*  __scopeVar_353_24 = SuiView$mkMenuNativeItem(&tmpReturn_27, o, Orc$str(&tmpReturn_28, "创建Prefab") , onActive) , *o = __scopeVar_353_24;
						
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_29 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_29, "CreatePrefab") ) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_30 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_31 = NULL;
					{
						SuiView$MenuNativeItem*  __scopeVar_354_24 = SuiView$mkMenuNativeItem(&tmpReturn_30, o, Orc$str(&tmpReturn_31, "重命名") , onActive) , *o = __scopeVar_354_24;
						
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_32 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_32, "RenameFileItem") ) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_33 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_34 = NULL;
					{
						SuiView$MenuNativeItem*  __scopeVar_356_24 = SuiView$mkMenuNativeItem(&tmpReturn_33, o, Orc$str(&tmpReturn_34, "删除") , onActive) , *o = __scopeVar_356_24;
						
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_35 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_35, "DeleteFileItem") ) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_36 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_37 = NULL;
					{
						SuiView$MenuNativeItem*  __scopeVar_358_24 = SuiView$mkMenuNativeItem(&tmpReturn_36, o, Orc$str(&tmpReturn_37, "返回上级目录") , onActive) , *o = __scopeVar_358_24;
						
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_38 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_38, "GotoParentDirectory") ) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
					n->create(n, o) ;
					n->showAtMouse(n) ;
				}
			}
		}
	}
}


void  SuiDesigner$AssetDirView$reactFileItem(SuiDesigner$AssetDirView *  self, SuiCore$Node *  o, SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP SuiDesigner$__Block_368_44*  __var___Block_368_44 = (__var___Block_368_44=NULL,urgc_init_var((void**)&__var___Block_368_44, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_368_44) , __finiBlock___Block_368_44) ));
	urgc_set_field_class(__var___Block_368_44, (void * )offsetof(SuiDesigner$__Block_368_44, self) , self) ;
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	urgc_set_field_class(__var___Block_368_44, (void * )offsetof(SuiDesigner$__Block_368_44, tmpFi) , fi) ;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_372_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )fi) , *o = __scopeVar_372_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_372_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->width = 80;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_2, "column") ) ;
		SuiCore$Inset$setHor(&((SuiCore$View * )o)->margin, 6) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_3, "pointer") ) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_378_26*  tmpReturn_4 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_378_26(&tmpReturn_4, __var___Block_368_44) ) ;
		URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_5 = NULL;
		{
			SuiView$HoverViewEffect*  __scopeVar_382_12 = SuiView$mkHoverViewEffect(&tmpReturn_5, o, 0) , *o = __scopeVar_382_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_382_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->isActive = self->selectFileItems->list->has(self->selectFileItems->list, fi) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_6 = NULL;
		{
			SuiView$ImageView*  __scopeVar_388_12 = SuiView$mkImageView(&tmpReturn_6, o, 0) , *o = __scopeVar_388_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_388_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			if (Orc$String$endsWith(fi->path, ".png") ) {
				o->setSrc(o, fi->path) ;
			}
			else if (Orc$String$endsWith(fi->path, ".prefab.json") ) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
				o->setSrc(o, Orc$Path_resolveFromExecutionDir(&tmpReturn_7, "../asset/icon/prefab.png") ) ;
			}
			else {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_9 = NULL;
				o->setSrc(o, fi->isDirectory ? Orc$Path_resolveFromExecutionDir(&tmpReturn_8, "../asset/icon/dir.png")  : Orc$Path_resolveFromExecutionDir(&tmpReturn_9, "../asset/icon/file.png") ) ;
			}
			((SuiCore$View * )o)->width = 60;
			((SuiCore$View * )o)->height = 60;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_10 = NULL;
		{
			SuiView$TextView*  __scopeVar_405_12 = SuiView$mkTextView(&tmpReturn_10, o, 0) , *o = __scopeVar_405_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_405_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			SuiCore$Inset$setVer(&((SuiCore$View * )o)->margin, 6) ;
			o->setText(o, fi->filename) ;
			o->setFont_size(o, t->dir_fontSize) ;
			o->color = t->dir_color;
		}
	}
}



static void  __finiBlock___Block_97_15(SuiDesigner$__Block_97_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_97_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_264_43(SuiDesigner$__Block_264_43 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_264_43, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_293_50(SuiDesigner$__Block_293_50 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_293_50, tmpFi) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_293_50, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_368_44(SuiDesigner$__Block_368_44 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_368_44, self) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_368_44, tmpFi) , NULL) ;
	return urgc_free_later(self) ; 
}

static Orc$List*  __fn___Closure_99_38(Orc$List **  __outRef__, SuiDesigner$__Closure_99_38 *  self){
	return urgc_set_var_for_return_class((void ** )__outRef__, self->__var___Block_97_15->self->getCurrentDirFileItem(self->__var___Block_97_15->self) ->children) ; 
}

static void  __fini___Closure_99_38(SuiDesigner$__Closure_99_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_99_38, __var___Block_97_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_99_38*  __make___Closure_99_38(SuiDesigner$__Closure_99_38 **  __outRef__, SuiDesigner$__Block_97_15 *  __var___Block_97_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_99_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_99_38) , __fini___Closure_99_38) ));
	self->invoke = __fn___Closure_99_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_99_38, __var___Block_97_15) , __var___Block_97_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_267(SuiDesigner$__Closure_onActive_267 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu on AssetDirView cmd:%s item:%s\n", item->cmd->str, item->label->str) ;
	self->__var___Block_264_43->self->_routeMenuNativeItem(self->__var___Block_264_43->self, item, self->__var___Block_264_43->self->getCurrentDirFileItem(self->__var___Block_264_43->self) ) ;
}

static void  __fini___Closure_onActive_267(SuiDesigner$__Closure_onActive_267 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_267, __var___Block_264_43) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_267*  __make___Closure_onActive_267(SuiDesigner$__Closure_onActive_267 **  __outRef__, SuiDesigner$__Block_264_43 *  __var___Block_264_43){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_267*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_267) , __fini___Closure_onActive_267) ));
	self->invoke = __fn___Closure_onActive_267;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_267, __var___Block_264_43) , __var___Block_264_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_310(SuiDesigner$__Closure_onActive_310 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu cmd:%s item:%s, fi:%s\n", item->cmd->str, item->label->str, self->__var___Block_293_50->tmpFi->path->str) ;
	self->__var___Block_293_50->self->_routeMenuNativeItem(self->__var___Block_293_50->self, item, self->__var___Block_293_50->tmpFi) ;
}

static void  __fini___Closure_onActive_310(SuiDesigner$__Closure_onActive_310 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_310, __var___Block_293_50) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_310*  __make___Closure_onActive_310(SuiDesigner$__Closure_onActive_310 **  __outRef__, SuiDesigner$__Block_293_50 *  __var___Block_293_50){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_310*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_310) , __fini___Closure_onActive_310) ));
	self->invoke = __fn___Closure_onActive_310;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_310, __var___Block_293_50) , __var___Block_293_50) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_378_26(SuiDesigner$__Closure_378_26 *  self, SuiCore$Event *  e){
	self->__var___Block_368_44->self->_fileItem_onEvent(self->__var___Block_368_44->self, e, self->__var___Block_368_44->tmpFi) ;
}

static void  __fini___Closure_378_26(SuiDesigner$__Closure_378_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_378_26, __var___Block_368_44) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_378_26*  __make___Closure_378_26(SuiDesigner$__Closure_378_26 **  __outRef__, SuiDesigner$__Block_368_44 *  __var___Block_368_44){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_378_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_378_26) , __fini___Closure_378_26) ));
	self->invoke = __fn___Closure_378_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_378_26, __var___Block_368_44) , __var___Block_368_44) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiDesigner$AssetDirView*  SuiDesigner$mkAssetDirView(SuiDesigner$AssetDirView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$AssetDirView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiDesigner$AssetDirView_init(NULL)) ) ; 
}



