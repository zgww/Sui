
#include "TreeView_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include "../Core/ViewBase_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../Core/Node_orc.h"
#include "./ViewBuilder_orc.h"
#include "./TextView_orc.h"
#include "./HoverViewEffect_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/String_orc.h"
#include "../Dialog/MessageDialog_orc.h"


// static struct 
typedef struct tagSuiView$__Block_211_59 SuiView$__Block_211_59;

typedef struct tagSuiView$__Block_220_35 SuiView$__Block_220_35;

typedef struct tagSuiView$__Block_225_69 SuiView$__Block_225_69;

typedef struct tagSuiView$__Closure_226_30 SuiView$__Closure_226_30;



struct tagSuiView$__Block_211_59 {
	SuiView$TreeView*  self ;
};





struct tagSuiView$__Block_220_35 {
	Object *  item ;
};





struct tagSuiView$__Block_225_69 {
	SuiLayout$LayoutLinear*  o ;
};





struct tagSuiView$__Closure_226_30 {
	void  (*invoke)(SuiView$__Closure_226_30 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiView$__Block_211_59*  __var___Block_211_59 ;
	SuiView$__Block_220_35*  __var___Block_220_35 ;
	SuiView$__Block_225_69*  __var___Block_225_69 ;
};





// static function declaration
static void  __finiBlock___Block_211_59(SuiView$__Block_211_59 *  self);
static void  __finiBlock___Block_220_35(SuiView$__Block_220_35 *  self);
static void  __finiBlock___Block_225_69(SuiView$__Block_225_69 *  self);
static void  __fn___Closure_226_30(SuiView$__Closure_226_30 *  self, SuiCore$Event *  e);
static void  __fini___Closure_226_30(SuiView$__Closure_226_30 *  self);
static SuiView$__Closure_226_30*  __make___Closure_226_30(SuiView$__Closure_226_30 **  __outRef__, SuiView$__Block_211_59 *  __var___Block_211_59, SuiView$__Block_220_35 *  __var___Block_220_35, SuiView$__Block_225_69 *  __var___Block_225_69);



//vtable instance
Vtable_SuiView$TreeState _vtable_SuiView$TreeState;

// init meta

void SuiView$TreeState_initMeta(Vtable_SuiView$TreeState *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "roots", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiView$TreeState, roots), true, false, 1);
	orc_metaField_class(&pNext, "selectedIds", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiView$TreeState, selectedIds), true, false, 1);
	orc_metaField_class(&pNext, "opendIds", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiView$TreeState, opendIds), true, false, 1);

	orc_metaField_method(&pNext, "getById", offsetof(SuiView$TreeState, getById));
	orc_metaField_method(&pNext, "_flatTree", offsetof(SuiView$TreeState, _flatTree));
	orc_metaField_method(&pNext, "flatTree", offsetof(SuiView$TreeState, flatTree));
	orc_metaField_method(&pNext, "_getById", offsetof(SuiView$TreeState, _getById));
	orc_metaField_method(&pNext, "getFirstSelected", offsetof(SuiView$TreeState, getFirstSelected));
	orc_metaField_method(&pNext, "isSelected", offsetof(SuiView$TreeState, isSelected));
	orc_metaField_method(&pNext, "isOpend", offsetof(SuiView$TreeState, isOpend));
	orc_metaField_method(&pNext, "setSelectedWithShiftAndCtrl", offsetof(SuiView$TreeState, setSelectedWithShiftAndCtrl));
	orc_metaField_method(&pNext, "fire_cbSelectedIdChanged", offsetof(SuiView$TreeState, fire_cbSelectedIdChanged));
	orc_metaField_method(&pNext, "setAncestorsOpen", offsetof(SuiView$TreeState, setAncestorsOpen));
	orc_metaField_method(&pNext, "setSelected", offsetof(SuiView$TreeState, setSelected));
	orc_metaField_method(&pNext, "setOpen", offsetof(SuiView$TreeState, setOpen));
}


// vtable init


Vtable_SuiView$TreeState* Vtable_SuiView$TreeState_init(Vtable_SuiView$TreeState* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$TreeState;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$TreeState_new;
    ((Vtable_Object*)pvt)->className = "SuiView$TreeState";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$TreeState_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$TreeState_fini(SuiView$TreeState *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$TreeState*)self)->roots);
	urgc_fini_field_class(self, (void**)&((SuiView$TreeState*)self)->selectedIds);
	urgc_fini_field_class(self, (void**)&((SuiView$TreeState*)self)->opendIds);

}

// init fields function


void SuiView$TreeState_init_fields(SuiView$TreeState *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$TreeState_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiView$TreeState*)self)->roots, NULL);
	urgc_set_field(self, (void**)&((SuiView$TreeState*)self)->getId, NULL);
	urgc_set_field(self, (void**)&((SuiView$TreeState*)self)->getItemChildren, NULL);
	urgc_set_field(self, (void**)&((SuiView$TreeState*)self)->cbSelectedIdChanged, NULL);
	urgc_set_field(self, (void**)&((SuiView$TreeState*)self)->getParent, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TreeState*)self)->selectedIds, Orc$List_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TreeState*)self)->opendIds, Orc$List_new(&tmpNewOwner_2) );
    }
	((SuiView$TreeState*)self)->getById = (void*)SuiView$TreeState$getById;
	((SuiView$TreeState*)self)->_flatTree = (void*)SuiView$TreeState$_flatTree;
	((SuiView$TreeState*)self)->flatTree = (void*)SuiView$TreeState$flatTree;
	((SuiView$TreeState*)self)->_getById = (void*)SuiView$TreeState$_getById;
	((SuiView$TreeState*)self)->getFirstSelected = (void*)SuiView$TreeState$getFirstSelected;
	((SuiView$TreeState*)self)->isSelected = (void*)SuiView$TreeState$isSelected;
	((SuiView$TreeState*)self)->isOpend = (void*)SuiView$TreeState$isOpend;
	((SuiView$TreeState*)self)->setSelectedWithShiftAndCtrl = (void*)SuiView$TreeState$setSelectedWithShiftAndCtrl;
	((SuiView$TreeState*)self)->fire_cbSelectedIdChanged = (void*)SuiView$TreeState$fire_cbSelectedIdChanged;
	((SuiView$TreeState*)self)->setAncestorsOpen = (void*)SuiView$TreeState$setAncestorsOpen;
	((SuiView$TreeState*)self)->setSelected = (void*)SuiView$TreeState$setSelected;
	((SuiView$TreeState*)self)->setOpen = (void*)SuiView$TreeState$setOpen;
}

// init function

void SuiView$TreeState_init(SuiView$TreeState *self, void *pOwner){
    Vtable_SuiView$TreeState_init(&_vtable_SuiView$TreeState);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$TreeState;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$TreeState_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$TreeState * SuiView$TreeState_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$TreeState *self = calloc(1, sizeof(SuiView$TreeState));
	
    SuiView$TreeState_init(self, pOwner);
    return self;
}


// class members
Object *  SuiView$TreeState$getById(SuiView$TreeState *  self, Orc$String*  id){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(id);

	Object *  obj = self->_getById(self, id, self->roots) ;
	return obj; 
}


void  SuiView$TreeState$_flatTree(SuiView$TreeState *  self, Orc$List*  items, Orc$List *  out){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(items);

	if (!items || !self->getId) {
		return ; 
	}
	int  l = items->size(items) ;
	for (int  i = 0; i < l; i++) {
		Object *  item = items->get(items, i) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  id = (*(self->getId))((id = NULL,&id), (void * )(self->getId), item) ;
		out->add(out, id) ;
		if (self->getItemChildren) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  kids = (*(self->getItemChildren))((kids = NULL,&kids), (void * )(self->getItemChildren), item) ;
			self->_flatTree(self, kids, out) ;
		}
	}
}


Orc$List*  SuiView$TreeState$flatTree(Orc$List **  __outRef__, SuiView$TreeState *  self){
	URGC_VAR_CLEANUP_CLASS Orc$List*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$List_new(&ret) ));
	self->_flatTree(self, self->roots, ret) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


Object *  SuiView$TreeState$_getById(SuiView$TreeState *  self, Orc$String*  id, Orc$List *  list){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(id);

	if (!id) {
		return NULL; 
	}
	if (!list) {
		return NULL; 
	}
	int  l = list->size(list) ;
	for (int  i = 0; i < l; i++) {
		Object *  obj = list->get(list, i) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  curId = (*(self->getId))((curId = NULL,&curId), (void * )(self->getId), obj) ;
		if (Orc$String$equalsString(id, curId) ) {
			return obj; 
		}
		URGC_VAR_CLEANUP_CLASS Orc$List*  children = (*(self->getItemChildren))((children = NULL,&children), (void * )(self->getItemChildren), obj) ;
		obj = self->_getById(self, id, children) ;
		if (obj) {
			return obj; 
		}
	}
	return NULL; 
}


Object *  SuiView$TreeState$getFirstSelected(SuiView$TreeState *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  id = (id=NULL,urgc_init_var_class((void**)&id, (Orc$String* )self->selectedIds->get(self->selectedIds, 0) ));
	Object *  obj = self->getById(self, id) ;
	return obj; 
}


bool  SuiView$TreeState$isSelected(SuiView$TreeState *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return self->selectedIds->has(self->selectedIds, (*(self->getId))(&tmpReturn_1, (void * )(self->getId), item) ) ; 
}


bool  SuiView$TreeState$isOpend(SuiView$TreeState *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return self->opendIds->has(self->opendIds, (*(self->getId))(&tmpReturn_1, (void * )(self->getId), item) ) ; 
}


void  SuiView$TreeState$setSelectedWithShiftAndCtrl(SuiView$TreeState *  self, Object *  item, bool  shift, bool  ctrl){
	if (!shift && !ctrl) {
		self->setSelected(self, item) ;
		return ; 
	}
	if (ctrl) {
		if (item != NULL) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  id = (*(self->getId))((id = NULL,&id), (void * )(self->getId), item) ;
			self->selectedIds->add(self->selectedIds, id) ;
			self->fire_cbSelectedIdChanged(self) ;
		}
		return ; 
	}
	if (shift) {
		if (self->selectedIds->size(self->selectedIds)  == 0) {
			self->setSelected(self, item) ;
			return ; 
		}
		URGC_VAR_CLEANUP_CLASS Orc$List*  flatIds = self->flatTree((flatIds = NULL,&flatIds), self) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  lastId = (lastId=NULL,urgc_init_var_class((void**)&lastId, (Orc$String* )self->selectedIds->last(self->selectedIds) ));
		self->selectedIds->clear(self->selectedIds) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  id = (*(self->getId))((id = NULL,&id), (void * )(self->getId), item) ;
		int  index0 = 0;
		int  index1 = 0;
		int  status = 0;
		for (int  i = 0; i < flatIds->size(flatIds) ; i++) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  curId = (curId=NULL,urgc_init_var_class((void**)&curId, (Orc$String* )flatIds->get(flatIds, i) ));
			if (Orc$String$equalsString(curId, lastId)  || Orc$String$equalsString(curId, id) ) {
				if (status == 0) {
					index0 = i;
					status++;
				}
				else {
					status++;
					index1 = i;
				}
			}
			if (status >= 1) {
				self->selectedIds->add(self->selectedIds, curId) ;
			}
			if (status == 2) {
				break;
			}
		}
		self->selectedIds->add(self->selectedIds, lastId) ;
		self->fire_cbSelectedIdChanged(self) ;
	}
}


void  SuiView$TreeState$fire_cbSelectedIdChanged(SuiView$TreeState *  self){
	if (self->cbSelectedIdChanged) {
		(*(self->cbSelectedIdChanged))((void * )(self->cbSelectedIdChanged), self) ;
	}
}


void  SuiView$TreeState$setAncestorsOpen(SuiView$TreeState *  self, Object *  item){
	if (item && self->getParent) {
		item = (*(self->getParent))((void * )(self->getParent), item) ;
		while (item) {
			self->setOpen(self, item, true) ;
			item = (*(self->getParent))((void * )(self->getParent), item) ;
		}
	}
}


void  SuiView$TreeState$setSelected(SuiView$TreeState *  self, Object *  item){
	self->selectedIds->clear(self->selectedIds) ;
	if (item != NULL) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  id = (*(self->getId))((id = NULL,&id), (void * )(self->getId), item) ;
		self->selectedIds->add(self->selectedIds, id) ;
	}
	self->fire_cbSelectedIdChanged(self) ;
}


void  SuiView$TreeState$setOpen(SuiView$TreeState *  self, Object *  item, bool  open){
	URGC_VAR_CLEANUP_CLASS Orc$String*  id = (*(self->getId))((id = NULL,&id), (void * )(self->getId), item) ;
	if (open) {
		self->opendIds->addOnce(self->opendIds, id) ;
	}
	else {
		self->opendIds->remove(self->opendIds, id) ;
	}
}




//vtable instance
Vtable_SuiView$TreeView _vtable_SuiView$TreeView;

// init meta

void SuiView$TreeView_initMeta(Vtable_SuiView$TreeView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "state", ((Vtable_Object*)Vtable_SuiView$TreeState_init(0)), offsetof(SuiView$TreeView, state), true, false, 1);

	orc_metaField_method(&pNext, "reactChildren", offsetof(SuiView$TreeView, reactChildren));
}


// vtable init


Vtable_SuiView$TreeView* Vtable_SuiView$TreeView_init(Vtable_SuiView$TreeView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$TreeView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$TreeView_new;
    ((Vtable_Object*)pvt)->className = "SuiView$TreeView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$TreeView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$TreeView_fini(SuiView$TreeView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$TreeView*)self)->state);

}

// init fields function


void SuiView$TreeView_init_fields(SuiView$TreeView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$TreeView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiView$TreeState*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$TreeView*)self)->state, SuiView$TreeState_new(&tmpNewOwner_1) );
	urgc_set_field(self, (void**)&((SuiView$TreeView*)self)->reactItem, NULL);
	urgc_set_field(self, (void**)&((SuiView$TreeView*)self)->cbOnEvent_forItemView, NULL);
    }
	((Object*)self)->ctor = (void*)SuiView$TreeView$ctor;
	((SuiCore$Node*)self)->react = (void*)SuiView$TreeView$react;
	((SuiView$TreeView*)self)->reactChildren = (void*)SuiView$TreeView$reactChildren;
}

// init function

void SuiView$TreeView_init(SuiView$TreeView *self, void *pOwner){
    Vtable_SuiView$TreeView_init(&_vtable_SuiView$TreeView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$TreeView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$TreeView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$TreeView * SuiView$TreeView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$TreeView *self = calloc(1, sizeof(SuiView$TreeView));
	
    SuiView$TreeView_init(self, pOwner);
    return self;
}


// class members
void  SuiView$TreeView$ctor(SuiView$TreeView *  self){
	SuiCore$Listener$ctor(self) ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->direction, "column") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->alignItems, "start") ;
}


void  SuiView$TreeView$react(SuiView$TreeView *  self){
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiCore$Node *  o = self;
	self->reactChildren(self, self, self->state->roots, 0) ;
	((SuiCore$Node * )self)->endInnerReact(self) ;
	((SuiCore$ViewBase * )self)->invalidLayout(self) ;
}


void  SuiView$TreeView$reactChildren(SuiView$TreeView *  self, SuiCore$Node *  parent, Orc$List *  items, int  deep){
	URGC_VAR_CLEANUP SuiView$__Block_211_59*  __var___Block_211_59 = (__var___Block_211_59=NULL,urgc_init_var((void**)&__var___Block_211_59, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_211_59) , __finiBlock___Block_211_59) ));
	urgc_set_field_class(__var___Block_211_59, (void * )offsetof(SuiView$__Block_211_59, self) , self) ;
	if (items == NULL) {
		return ; 
	}
	int  l = items->size(items) ;
	for (int  i = 0; i < l; i++) {
		URGC_VAR_CLEANUP SuiView$__Block_220_35*  __var___Block_220_35 = (__var___Block_220_35=NULL,urgc_init_var((void**)&__var___Block_220_35, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_220_35) , __finiBlock___Block_220_35) ));
		__var___Block_220_35->item = items->get(items, i) ;
		bool  isOpend = self->state->isOpend(self->state, __var___Block_220_35->item) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$layoutLinear(&tmpReturn_1, parent, ((long long )__var___Block_220_35->item) + deep * 1000 + i) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_225_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP SuiView$__Block_225_69*  __var___Block_225_69 = (__var___Block_225_69=NULL,urgc_init_var((void**)&__var___Block_225_69, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_225_69) , __finiBlock___Block_225_69) ));
			urgc_set_field_class(__var___Block_225_69, (void * )offsetof(SuiView$__Block_225_69, o) , o) ;
			URGC_VAR_CLEANUP SuiView$__Closure_226_30*  tmpReturn_2 = NULL;
			urgc_set_field(__var___Block_225_69->o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_226_30(&tmpReturn_2, __var___Block_211_59, __var___Block_220_35, __var___Block_225_69) ) ;
			((SuiCore$View * )__var___Block_225_69->o)->padding.left = deep * 20;
			bool  isSelected = self->state->isSelected(self->state, __var___Block_220_35->item) ;
			((SuiCore$View * )__var___Block_225_69->o)->backgroundColor = isSelected ? 0x330088ff : 0x00000000;
			((SuiCore$View * )__var___Block_225_69->o)->height = 20;
			Orc$String$set(__var___Block_225_69->o->alignItems, "center") ;
			Orc$String$set(__var___Block_225_69->o->justifyContent, "start") ;
			if (self->reactItem != NULL) {
				(*(self->reactItem))((void * )(self->reactItem), __var___Block_225_69->o, __var___Block_220_35->item, deep) ;
			}
			else {
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_3 = NULL;
				{
					SuiView$TextView*  o = SuiView$mkTextView(&tmpReturn_3, __var___Block_225_69->o, 0) ;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_258_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
					o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_4, "item-") , i) ) ;
				}
			}
		}
		if (self->state->isOpend(self->state, __var___Block_220_35->item) ) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  kids = (*(self->state->getItemChildren))((kids = NULL,&kids), (void * )(self->state->getItemChildren), __var___Block_220_35->item) ;
			self->reactChildren(self, parent, kids, deep + 1) ;
		}
	}
}



static void  __finiBlock___Block_211_59(SuiView$__Block_211_59 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_211_59, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_220_35(SuiView$__Block_220_35 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_225_69(SuiView$__Block_225_69 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_225_69, o) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_226_30(SuiView$__Closure_226_30 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->isClickInBubble(me)  && me->button == 1) {
			self->__var___Block_211_59->self->state->setSelectedWithShiftAndCtrl(self->__var___Block_211_59->self->state, self->__var___Block_220_35->item, me->shift, me->ctrl) ;
			((SuiCore$Node * )self->__var___Block_211_59->self)->invalidReact(self->__var___Block_211_59->self) ;
		}
		if (me->isDblClickInBubble(me) ) {
			self->__var___Block_211_59->self->state->setOpen(self->__var___Block_211_59->self->state, self->__var___Block_220_35->item, !self->__var___Block_211_59->self->state->isOpend(self->__var___Block_211_59->self->state, self->__var___Block_220_35->item) ) ;
			((SuiCore$Node * )self->__var___Block_211_59->self)->invalidReact(self->__var___Block_211_59->self) ;
		}
	}
	if (self->__var___Block_211_59->self->cbOnEvent_forItemView) {
		(*(self->__var___Block_211_59->self->cbOnEvent_forItemView))((void * )(self->__var___Block_211_59->self->cbOnEvent_forItemView), e, self->__var___Block_225_69->o, self->__var___Block_220_35->item) ;
	}
}

static void  __fini___Closure_226_30(SuiView$__Closure_226_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_226_30, __var___Block_211_59) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_226_30, __var___Block_220_35) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_226_30, __var___Block_225_69) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_226_30*  __make___Closure_226_30(SuiView$__Closure_226_30 **  __outRef__, SuiView$__Block_211_59 *  __var___Block_211_59, SuiView$__Block_220_35 *  __var___Block_220_35, SuiView$__Block_225_69 *  __var___Block_225_69){
	URGC_VAR_CLEANUP SuiView$__Closure_226_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_226_30) , __fini___Closure_226_30) ));
	self->invoke = __fn___Closure_226_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_226_30, __var___Block_211_59) , __var___Block_211_59) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_226_30, __var___Block_220_35) , __var___Block_220_35) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_226_30, __var___Block_225_69) , __var___Block_225_69) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$TreeView*  SuiView$mkTreeView(SuiView$TreeView **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$TreeView* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$TreeView_init(NULL)) ) ; 
}



