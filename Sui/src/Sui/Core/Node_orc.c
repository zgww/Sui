
#include "Node_orc.h" 

#include "../../Orc/Orc.h"
#include <stdio.h>
#include "./Emitter_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Map_orc.h"
#include "../../Orc/Time_orc.h"
#include "../../Orc/ScopeData_orc.h"
#include "../../Orc/String_orc.h"
#include "./Window_orc.h"
#include "./Timer_orc.h"


// static struct 
typedef struct tagSuiCore$__Block_282_24 SuiCore$__Block_282_24;

typedef struct tagSuiCore$__Closure_290_30 SuiCore$__Closure_290_30;



struct tagSuiCore$__Block_282_24 {
	SuiCore$Node*  self ;
};





struct tagSuiCore$__Closure_290_30 {
	bool  (*invoke)(SuiCore$__Closure_290_30 *  self);
	Vtable_Object *  vtable ;
	SuiCore$__Block_282_24*  __var___Block_282_24 ;
};





// static function declaration
static void  __finiBlock___Block_282_24(SuiCore$__Block_282_24 *  self);
static bool  __fn___Closure_290_30(SuiCore$__Closure_290_30 *  self);
static void  __fini___Closure_290_30(SuiCore$__Closure_290_30 *  self);
static SuiCore$__Closure_290_30*  __make___Closure_290_30(SuiCore$__Closure_290_30 **  __outRef__, SuiCore$__Block_282_24 *  __var___Block_282_24);


int  SuiCore$Node_gReactDirty = true;

//vtable instance
Vtable_SuiCore$InnerReact _vtable_SuiCore$InnerReact;

// init meta

void SuiCore$InnerReact_initMeta(Vtable_SuiCore$InnerReact *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "old_unusedMap", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiCore$InnerReact, old_unusedMap), true, false, 1);
	orc_metaField_class(&pNext, "old_map", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiCore$InnerReact, old_map), true, false, 1);
	orc_metaField_class(&pNext, "unusedMap", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiCore$InnerReact, unusedMap), true, false, 1);
	orc_metaField_class(&pNext, "map", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiCore$InnerReact, map), true, false, 1);
	orc_metaField_primitive(&pNext, "_appendIndexForReact", OrcMetaType_int, offsetof(SuiCore$InnerReact, _appendIndexForReact), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiCore$InnerReact* Vtable_SuiCore$InnerReact_init(Vtable_SuiCore$InnerReact* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$InnerReact;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$InnerReact_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$InnerReact";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$InnerReact_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$InnerReact_fini(SuiCore$InnerReact *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiCore$InnerReact_init_fields(SuiCore$InnerReact *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$InnerReact_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiCore$InnerReact*)self)->old_unusedMap, NULL);
	urgc_set_field_class(self, (void**)&((SuiCore$InnerReact*)self)->old_map, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$InnerReact*)self)->unusedMap, Orc$Map_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$InnerReact*)self)->map, Orc$Map_new(&tmpNewOwner_2) );
	((SuiCore$InnerReact*)self)->_appendIndexForReact = 0;
    }
	
}

// init function

void SuiCore$InnerReact_init(SuiCore$InnerReact *self, void *pOwner){
    Vtable_SuiCore$InnerReact_init(&_vtable_SuiCore$InnerReact);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$InnerReact;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$InnerReact_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$InnerReact * SuiCore$InnerReact_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$InnerReact *self = calloc(1, sizeof(SuiCore$InnerReact));
	
    SuiCore$InnerReact_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiCore$Node _vtable_SuiCore$Node;

// init meta

void SuiCore$Node_initMeta(Vtable_SuiCore$Node *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "key", OrcMetaType_char, offsetof(SuiCore$Node, key), 0, 0, 1, 1);//char
	orc_metaField_class(&pNext, "children", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$Node, children), true, false, 1);
	orc_metaField_class(&pNext, "parent", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiCore$Node, parent), true, false, 1);
	orc_metaField_class(&pNext, "_mapForReact", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiCore$Node, _mapForReact), true, false, 1);
	orc_metaField_class(&pNext, "_unusedMapForReact", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiCore$Node, _unusedMapForReact), true, false, 1);
	orc_metaField_primitive(&pNext, "_appendIndexForReact", OrcMetaType_int, offsetof(SuiCore$Node, _appendIndexForReact), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "isNewForReact", OrcMetaType_bool, offsetof(SuiCore$Node, isNewForReact), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiCore$Node, name), true, false, 1);
	orc_metaField_class(&pNext, "innerReact", ((Vtable_Object*)Vtable_SuiCore$InnerReact_init(0)), offsetof(SuiCore$Node, innerReact), true, false, 1);
	orc_metaField_class(&pNext, "userdata", ((Vtable_Object*)Vtable_Object_init(0)), offsetof(SuiCore$Node, userdata), true, false, 1);
	orc_metaField_primitive(&pNext, "hasInnerReact", OrcMetaType_bool, offsetof(SuiCore$Node, hasInnerReact), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "outKids", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$Node, outKids), true, false, 1);
	orc_metaField_primitive(&pNext, "mounted", OrcMetaType_bool, offsetof(SuiCore$Node, mounted), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "ownerWindow", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(SuiCore$Node, ownerWindow), true, false, 1);
	orc_metaField_primitive(&pNext, "_reactDirty", OrcMetaType_bool, offsetof(SuiCore$Node, _reactDirty), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "startInnerReact", offsetof(SuiCore$Node, startInnerReact));
	orc_metaField_method(&pNext, "endInnerReact", offsetof(SuiCore$Node, endInnerReact));
	orc_metaField_method(&pNext, "setMounted", offsetof(SuiCore$Node, setMounted));
	orc_metaField_method(&pNext, "baseOnMounted", offsetof(SuiCore$Node, baseOnMounted));
	orc_metaField_method(&pNext, "baseOnUnmounting", offsetof(SuiCore$Node, baseOnUnmounting));
	orc_metaField_method(&pNext, "onMounted", offsetof(SuiCore$Node, onMounted));
	orc_metaField_method(&pNext, "onUnmounting", offsetof(SuiCore$Node, onUnmounting));
	orc_metaField_method(&pNext, "setOwnerWindow", offsetof(SuiCore$Node, setOwnerWindow));
	orc_metaField_method(&pNext, "getChild", offsetof(SuiCore$Node, getChild));
	orc_metaField_method(&pNext, "getWindow", offsetof(SuiCore$Node, getWindow));
	orc_metaField_method(&pNext, "getChildByType", offsetof(SuiCore$Node, getChildByType));
	orc_metaField_method(&pNext, "getChildrenCount", offsetof(SuiCore$Node, getChildrenCount));
	orc_metaField_method(&pNext, "appendChild", offsetof(SuiCore$Node, appendChild));
	orc_metaField_method(&pNext, "insertChild", offsetof(SuiCore$Node, insertChild));
	orc_metaField_method(&pNext, "removeChild", offsetof(SuiCore$Node, removeChild));
	orc_metaField_method(&pNext, "indexOf", offsetof(SuiCore$Node, indexOf));
	orc_metaField_method(&pNext, "removeSelf", offsetof(SuiCore$Node, removeSelf));
	orc_metaField_method(&pNext, "dissolveSubtree", offsetof(SuiCore$Node, dissolveSubtree));
	orc_metaField_method(&pNext, "getAncients", offsetof(SuiCore$Node, getAncients));
	orc_metaField_method(&pNext, "react", offsetof(SuiCore$Node, react));
	orc_metaField_method(&pNext, "invalidReact", offsetof(SuiCore$Node, invalidReact));
	orc_metaField_method(&pNext, "trigger_react", offsetof(SuiCore$Node, trigger_react));
	orc_metaField_method(&pNext, "toString", offsetof(SuiCore$Node, toString));
	orc_metaField_method(&pNext, "__exit__", offsetof(SuiCore$Node, __exit__));
}


// vtable init


Vtable_SuiCore$Node* Vtable_SuiCore$Node_init(Vtable_SuiCore$Node* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Node;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Emitter_init(&_vtable_SuiCore$Emitter);

	// init by super vtable init function
    Vtable_SuiCore$Emitter_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Emitter;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Node_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Node";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Node_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$Node_fini(SuiCore$Node *self){
	//super fini
    SuiCore$Emitter_fini((SuiCore$Emitter *)self);

    //字段释放


}

// init fields function


void SuiCore$Node_init_fields(SuiCore$Node *self){
	//super class
    SuiCore$Emitter_init_fields((SuiCore$Emitter*)self);

    ((Object*)self)->fini = (void*)SuiCore$Node_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$Node*)self)->children, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiCore$Node*)self)->parent, NULL);
	urgc_set_field_class(self, (void**)&((SuiCore$Node*)self)->_mapForReact, NULL);
	urgc_set_field_class(self, (void**)&((SuiCore$Node*)self)->_unusedMapForReact, NULL);
	((SuiCore$Node*)self)->_appendIndexForReact = 0;
	((SuiCore$Node*)self)->isNewForReact = true;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$Node*)self)->name, Orc$str(&tmpReturn_2, "") );
	urgc_set_field_class(self, (void**)&((SuiCore$Node*)self)->innerReact, NULL);
	urgc_set_field_class(self, (void**)&((SuiCore$Node*)self)->userdata, NULL);
	((SuiCore$Node*)self)->hasInnerReact = false;
	urgc_set_field_class(self, (void**)&((SuiCore$Node*)self)->outKids, NULL);
	((SuiCore$Node*)self)->mounted = false;
	urgc_set_field_class(self, (void**)&((SuiCore$Node*)self)->ownerWindow, NULL);
	((SuiCore$Node*)self)->_reactDirty = false;
    }
	((SuiCore$Node*)self)->startInnerReact = (void*)SuiCore$Node$startInnerReact;
	((SuiCore$Node*)self)->endInnerReact = (void*)SuiCore$Node$endInnerReact;
	((SuiCore$Node*)self)->setMounted = (void*)SuiCore$Node$setMounted;
	((SuiCore$Node*)self)->baseOnMounted = (void*)SuiCore$Node$baseOnMounted;
	((SuiCore$Node*)self)->baseOnUnmounting = (void*)SuiCore$Node$baseOnUnmounting;
	((SuiCore$Node*)self)->onMounted = (void*)SuiCore$Node$onMounted;
	((SuiCore$Node*)self)->onUnmounting = (void*)SuiCore$Node$onUnmounting;
	((SuiCore$Node*)self)->setOwnerWindow = (void*)SuiCore$Node$setOwnerWindow;
	((SuiCore$Node*)self)->getChild = (void*)SuiCore$Node$getChild;
	((SuiCore$Node*)self)->getWindow = (void*)SuiCore$Node$getWindow;
	((SuiCore$Node*)self)->getChildByType = (void*)SuiCore$Node$getChildByType;
	((SuiCore$Node*)self)->getChildrenCount = (void*)SuiCore$Node$getChildrenCount;
	((SuiCore$Node*)self)->appendChild = (void*)SuiCore$Node$appendChild;
	((SuiCore$Node*)self)->insertChild = (void*)SuiCore$Node$insertChild;
	((SuiCore$Node*)self)->removeChild = (void*)SuiCore$Node$removeChild;
	((SuiCore$Node*)self)->indexOf = (void*)SuiCore$Node$indexOf;
	((SuiCore$Node*)self)->removeSelf = (void*)SuiCore$Node$removeSelf;
	((SuiCore$Node*)self)->dissolveSubtree = (void*)SuiCore$Node$dissolveSubtree;
	((SuiCore$Node*)self)->getAncients = (void*)SuiCore$Node$getAncients;
	((SuiCore$Node*)self)->react = (void*)SuiCore$Node$react;
	((SuiCore$Node*)self)->invalidReact = (void*)SuiCore$Node$invalidReact;
	((SuiCore$Node*)self)->trigger_react = (void*)SuiCore$Node$trigger_react;
	((SuiCore$Node*)self)->toString = (void*)SuiCore$Node$toString;
	((SuiCore$Node*)self)->__exit__ = (void*)SuiCore$Node$__exit__;
}

// init function

void SuiCore$Node_init(SuiCore$Node *self, void *pOwner){
    Vtable_SuiCore$Node_init(&_vtable_SuiCore$Node);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Node;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Node_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Node * SuiCore$Node_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Node *self = calloc(1, sizeof(SuiCore$Node));
	
    SuiCore$Node_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$Node$startInnerReact(SuiCore$Node *  self){
	if (!self->innerReact) {
		URGC_VAR_CLEANUP_CLASS SuiCore$InnerReact*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiCore$Node, innerReact) , SuiCore$InnerReact_new(&tmpNewOwner_1) ) ;
	}
	SuiCore$InnerReact *  ir = self->innerReact;
	urgc_set_field_class(self->innerReact, (void * )offsetof(SuiCore$InnerReact, old_unusedMap) , self->_unusedMapForReact) ;
	urgc_set_field_class(self->innerReact, (void * )offsetof(SuiCore$InnerReact, old_map) , self->_mapForReact) ;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$Node, _unusedMapForReact) , self->innerReact->unusedMap) ;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$Node, _mapForReact) , self->innerReact->map) ;
	self->_appendIndexForReact = 0;
}


void  SuiCore$Node$endInnerReact(SuiCore$Node *  self){
	int  idx = self->_appendIndexForReact;
	SuiCore$Node$clearUnusedKids(self) ;
	self->_appendIndexForReact = idx;
	urgc_set_field_class(self->innerReact, (void * )offsetof(SuiCore$InnerReact, unusedMap) , self->_unusedMapForReact) ;
	urgc_set_field_class(self->innerReact, (void * )offsetof(SuiCore$InnerReact, map) , self->_mapForReact) ;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$Node, _unusedMapForReact) , self->innerReact->old_unusedMap) ;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$Node, _mapForReact) , self->innerReact->old_map) ;
}


void  SuiCore$Node$setMounted(SuiCore$Node *  self, bool  mounted){
	if (self->mounted == mounted) {
		return ; 
	}
	self->mounted = mounted;
	int  l = self->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$Node *  n = self->getChild(self, i) ;
		n->setMounted(n, mounted) ;
	}
	if (self->mounted) {
		self->baseOnMounted(self) ;
	}
	else {
		self->baseOnUnmounting(self) ;
	}
}


void  SuiCore$Node$baseOnMounted(SuiCore$Node *  self){
	if (self->parent != NULL) {
		self->setOwnerWindow(self, self->parent->ownerWindow) ;
		if (self->ownerWindow != NULL) {
			
		}
	}
	self->onMounted(self) ;
}


void  SuiCore$Node$baseOnUnmounting(SuiCore$Node *  self){
	self->setOwnerWindow(self, NULL) ;
	self->onUnmounting(self) ;
}


void  SuiCore$Node$onMounted(SuiCore$Node *  self){
	
}


void  SuiCore$Node$onUnmounting(SuiCore$Node *  self){
	
}


void  SuiCore$Node$setOwnerWindow(SuiCore$Node *  self, Sui$Window *  win){
	if (self->ownerWindow == win) {
		return ; 
	}
	urgc_set_field_class(self, (void * )offsetof(SuiCore$Node, ownerWindow) , win) ;
	int  l = self->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$Node *  kid = self->getChild(self, i) ;
		kid->setOwnerWindow(kid, win) ;
	}
}


SuiCore$Node *  SuiCore$Node$getChild(SuiCore$Node *  self, int  i){
	return (SuiCore$Node * )self->children->get(self->children, i) ; 
}


Sui$Window *  SuiCore$Node$getWindow(SuiCore$Node *  self){
	return self->ownerWindow; 
}


Object *  SuiCore$Node$getChildByType(SuiCore$Node *  self, Vtable_Object *  vt){
	for (int  i = self->getChildrenCount(self)  - 1; i >= 0; i--) {
		Object *  child = self->getChild(self, i) ;
		if (Orc_instanceof((Object*)child, (Vtable_Object*)vt)) {
			return child; 
		}
	}
	return NULL; 
}


int  SuiCore$Node$getChildrenCount(SuiCore$Node *  self){
	int  size = self->children->size(self->children) ;
	return size; 
}


void  SuiCore$Node$appendChild(SuiCore$Node *  self, SuiCore$Node *  child){
	if (child) {
		child->removeSelf(child) ;
		urgc_set_field_class(child, (void * )offsetof(SuiCore$Node, parent) , self) ;
		self->children->add(self->children, child) ;
		child->setMounted(child, self->mounted) ;
	}
}


void  SuiCore$Node$insertChild(SuiCore$Node *  self, SuiCore$Node *  child, int  at){
	if (child) {
		if (child->parent != self) {
			child->removeSelf(child) ;
			urgc_set_field_class(child, (void * )offsetof(SuiCore$Node, parent) , self) ;
			self->children->insert(self->children, child, at) ;
		}
		else {
			if (self->children->get(self->children, at)  == child) {
				return ; 
			}
			int  nowIndex = self->children->indexOf(self->children, child) ;
			if (nowIndex == -1) {
				self->children->insert(self->children, child, at) ;
			}
			else if (at < nowIndex) {
				self->children->removeAt(self->children, nowIndex) ;
				self->children->insert(self->children, child, at) ;
			}
			else {
				self->children->insert(self->children, child, at) ;
				self->children->removeAt(self->children, nowIndex) ;
			}
		}
		child->setMounted(child, self->mounted) ;
	}
}


void  SuiCore$Node$removeChild(SuiCore$Node *  self, SuiCore$Node *  child){
	if (child) {
		urgc_set_field_class(child, (void * )offsetof(SuiCore$Node, parent) , NULL) ;
		self->children->remove(self->children, child) ;
		child->setMounted(child, false) ;
	}
}


int  SuiCore$Node$indexOf(SuiCore$Node *  self, SuiCore$Node *  child){
	int  idx = self->children->indexOf(self->children, child) ;
	return idx; 
}


void  SuiCore$Node$removeSelf(SuiCore$Node *  self){
	if (self->parent) {
		self->parent->removeChild(self->parent, self) ;
	}
}


void  SuiCore$Node$dissolveSubtree(SuiCore$Node *  self){
	{
		int  l = self->getChildrenCount(self) ;
		for (int  i = l - 1; i >= 0; i--) {
			SuiCore$Node *  n = self->getChild(self, i) ;
			n->dissolveSubtree(n) ;
		}
		if (self->_mapForReact) {
			self->_mapForReact->clear(self->_mapForReact) ;
		}
		if (self->_unusedMapForReact) {
			self->_unusedMapForReact->clear(self->_unusedMapForReact) ;
		}
		self->removeSelf(self) ;
	}
}


Orc$List*  SuiCore$Node$getAncients(Orc$List **  __outRef__, SuiCore$Node *  self, bool  includeSelf){
	URGC_VAR_CLEANUP_CLASS Orc$List*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$List_new(&ret) ));
	if (includeSelf) {
		ret->add(ret, self) ;
	}
	SuiCore$Node *  cur = self;
	while (cur->parent) {
		cur = cur->parent;
		ret->add(ret, cur) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


void  SuiCore$Node$react(SuiCore$Node *  self){
	
}


void  SuiCore$Node$invalidReact(SuiCore$Node *  self){
	self->trigger_react(self) ;
}


void  SuiCore$Node$trigger_react(SuiCore$Node *  self){
	URGC_VAR_CLEANUP SuiCore$__Block_282_24*  __var___Block_282_24 = (__var___Block_282_24=NULL,urgc_init_var((void**)&__var___Block_282_24, orc_alloc_and_set_deleter(sizeof(SuiCore$__Block_282_24) , __finiBlock___Block_282_24) ));
	urgc_set_field_class(__var___Block_282_24, (void * )offsetof(SuiCore$__Block_282_24, self) , self) ;
	if (self->_reactDirty) {
		return ; 
	}
	self->_reactDirty = true;
	SuiCore$Node_gReactDirty = true;
	URGC_VAR_CLEANUP SuiCore$__Closure_290_30*  tmpReturn_1 = NULL;
	SuiCore$requestAnimationFrame(__make___Closure_290_30(&tmpReturn_1, __var___Block_282_24) ) ;
}


Orc$String*  SuiCore$Node$toString(Orc$String **  __outRef__, SuiCore$Node *  self){
	const char *  className = Object_getClassName(self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$addString(Orc$String$add(Orc$str(&tmpReturn_1, className) , ":") , self->name) ) ; 
}


Orc$ScopeData SuiCore$Node$__exit__(SuiCore$Node *  self){
	return Orc$mkScopeData(self, (void * )SuiCore$node_exit) ; 
}



static void  __finiBlock___Block_282_24(SuiCore$__Block_282_24 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiCore$__Block_282_24, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static bool  __fn___Closure_290_30(SuiCore$__Closure_290_30 *  self){
	self->__var___Block_282_24->self->_reactDirty = false;
	self->__var___Block_282_24->self->react(self->__var___Block_282_24->self) ;
	return true; 
}

static void  __fini___Closure_290_30(SuiCore$__Closure_290_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_290_30, __var___Block_282_24) , NULL) ;
	urgc_free_later(self) ;
}

static SuiCore$__Closure_290_30*  __make___Closure_290_30(SuiCore$__Closure_290_30 **  __outRef__, SuiCore$__Block_282_24 *  __var___Block_282_24){
	URGC_VAR_CLEANUP SuiCore$__Closure_290_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiCore$__Closure_290_30) , __fini___Closure_290_30) ));
	self->invoke = __fn___Closure_290_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_290_30, __var___Block_282_24) , __var___Block_282_24) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

void  SuiCore$node_exit(Orc$ScopeData *  scopeData){
	SuiCore$Node *  n = (SuiCore$Node * )scopeData->data;
	n->react(n) ;
	SuiCore$Node$clearUnusedKids(n) ;
}

Orc$Map*  SuiCore$get_mapForReact(Orc$Map **  __outRef__, SuiCore$Node *  n){
	if (!n->_mapForReact) {
		URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(n, (void * )offsetof(SuiCore$Node, _mapForReact) , Orc$Map_new(&tmpNewOwner_1) ) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, n->_mapForReact) ; 
}

Orc$Map*  SuiCore$get_unusedMapForReact(Orc$Map **  __outRef__, SuiCore$Node *  n){
	if (!n->_unusedMapForReact) {
		URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(n, (void * )offsetof(SuiCore$Node, _unusedMapForReact) , Orc$Map_new(&tmpNewOwner_1) ) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, n->_unusedMapForReact) ; 
}

void  SuiCore$clearInnerUnusedKids(SuiCore$Node *  n){
	
}

void  SuiCore$printNodesTree(Orc$List *  nodes, int  tab){
	for (int  i = 0; i < nodes->size(nodes) ; i++) {
		SuiCore$Node *  kid = (SuiCore$Node * )nodes->get(nodes, i) ;
		SuiCore$printNodeTree(kid, tab) ;
	}
}

void  SuiCore$printNodeTree(SuiCore$Node *  n, int  tab){
	const char *  className = Object_getClassName(n) ;
	for (int  i = 0; i < tab; i++) {
		printf("\t") ;
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("%s. p:%p\n", n->toString(&tmpReturn_1, n) ->str, n) ;
	for (int  i = 0; i < n->children->size(n->children) ; i++) {
		SuiCore$Node *  kid = (SuiCore$Node * )n->children->get(n->children, i) ;
		SuiCore$printNodeTree(kid, tab + 1) ;
	}
}

void  SuiCore$Node$walkIf(SuiCore$Node *  self, bool  (*fn)(void *  data, SuiCore$Node *  n), void *  ud){
	bool  walkChildren = fn(ud, self) ;
	if (walkChildren) {
		for (int  i = 0; i < self->children->size(self->children) ; i++) {
			SuiCore$Node *  kid = (SuiCore$Node * )self->children->get(self->children, i) ;
			SuiCore$Node$walkIf(kid, fn, ud) ;
		}
	}
}

void  SuiCore$Node$walk(SuiCore$Node *  self, void  (*fn)(void *  data, SuiCore$Node *  n), void *  ud){
	fn(ud, self) ;
	for (int  i = 0; i < self->children->size(self->children) ; i++) {
		SuiCore$Node *  kid = (SuiCore$Node * )self->children->get(self->children, i) ;
		SuiCore$Node$walk(kid, fn, ud) ;
	}
}

SuiCore$Node *  SuiCore$Node$getTopest(SuiCore$Node *  self){
	SuiCore$Node *  cur = self;
	while (cur) {
		if (!cur->parent) {
			break;
		}
		cur = cur->parent;
	}
	return cur; 
}

SuiCore$Node *  SuiCore$Node$getAncestorByClass(SuiCore$Node *  self, Vtable_Object *  o){
	SuiCore$Node *  cur = self;
	while (cur) {
		if (Orc_instanceof((Object*)cur, (Vtable_Object*)o)) {
			break;
		}
		cur = cur->parent;
	}
	return cur; 
}

SuiCore$Node *  SuiCore$Node$findNodeByClass(SuiCore$Node *  self, Vtable_Object *  o){
	if (Orc_instanceof((Object*)self, (Vtable_Object*)o)) {
		return self; 
	}
	int  l = self->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$Node *  kid = self->getChild(self, i) ;
		if (kid) {
			SuiCore$Node *  found = SuiCore$Node$findNodeByClass(kid, o) ;
			if (found) {
				return found; 
			}
		}
	}
	return NULL; 
}

void  SuiCore$Node$endReact(SuiCore$Node *  self){
	self->react(self) ;
	SuiCore$Node$clearUnusedKids(self) ;
}

void  SuiCore$Node$end(SuiCore$Node *  self){
	SuiCore$Node$clearUnusedKids(self) ;
}

void  SuiCore$Node$clearUnusedKids(SuiCore$Node *  self){
	SuiCore$Node *  n = self;
	URGC_VAR_CLEANUP_CLASS Orc$Map*  unused = SuiCore$get_unusedMapForReact((unused = NULL,&unused), n) ;
	URGC_VAR_CLEANUP_CLASS Orc$Map*  map = SuiCore$get_mapForReact((map = NULL,&map), n) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  keys = unused->keys((keys = NULL,&keys), unused) ;
	int  l = keys->size(keys) ;
	bool  needRmOutKids = self->hasInnerReact && self->outKids && !SuiCore$Node$isInInnerReact(self) ;
	for (int  i = 0; i < l; i++) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  key = (key=NULL,urgc_init_var_class((void**)&key, (Orc$String* )keys->get(keys, i) ));
		URGC_VAR_CLEANUP_CLASS SuiCore$Node*  unusedNode = (unusedNode=NULL,urgc_init_var_class((void**)&unusedNode, (SuiCore$Node * )unused->get(unused, key->str) ));
		unusedNode->removeSelf(unusedNode) ;
		if (needRmOutKids) {
			self->outKids->remove(self->outKids, unusedNode) ;
		}
	}
	unused->clear(unused) ;
	urgc_set_field_class(n, (void * )offsetof(SuiCore$Node, _mapForReact) , unused) ;
	urgc_set_field_class(n, (void * )offsetof(SuiCore$Node, _unusedMapForReact) , map) ;
	n->_appendIndexForReact = 0;
}

void  SuiCore$Node$placeKid(SuiCore$Node *  self, SuiCore$Node *  n){
	SuiCore$Node *  parent = self;
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpReturn_1 = NULL;
	Orc$Map *  unusedMap = SuiCore$get_unusedMapForReact(&tmpReturn_1, parent) ;
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpReturn_2 = NULL;
	Orc$Map *  map = SuiCore$get_mapForReact(&tmpReturn_2, parent) ;
	unusedMap->del(unusedMap, n->key) ;
	map->put(map, n->key, n) ;
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
	parent->_appendIndexForReact++;
}

void  SuiCore$Node$placeKids(SuiCore$Node *  self, Orc$List*  kids){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(kids);

	if (kids == NULL) {
		return ; 
	}
	int  l = kids->size(kids) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$Node *  n = (SuiCore$Node * )kids->get(kids, i) ;
		SuiCore$Node$placeKid(self, n) ;
	}
}

bool  SuiCore$Node$isInInnerReact(SuiCore$Node *  self){
	return self->innerReact && self->innerReact->map == self->_mapForReact; 
}



