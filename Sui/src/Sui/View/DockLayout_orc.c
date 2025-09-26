
#include "DockLayout_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Mouse_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "./ViewBuilder_orc.h"
#include "./Drag_orc.h"
#include "../../Json/Json_orc.h"


// static struct 
typedef struct tagSuiView$__Block_281_15 SuiView$__Block_281_15;

typedef struct tagSuiView$__Block_427_39 SuiView$__Block_427_39;

typedef struct tagSuiView$__Block_432_39 SuiView$__Block_432_39;

typedef struct tagSuiView$__Block_439_30 SuiView$__Block_439_30;

typedef struct tagSuiView$__Block_507_56 SuiView$__Block_507_56;

typedef struct tagSuiView$__Block_513_39 SuiView$__Block_513_39;

typedef struct tagSuiView$__Closure_285_30 SuiView$__Closure_285_30;

typedef struct tagSuiView$__Closure_447_40 SuiView$__Closure_447_40;

typedef struct tagSuiView$__Closure_518_38 SuiView$__Closure_518_38;



struct tagSuiView$__Block_281_15 {
	SuiView$DockLayout*  self ;
};





struct tagSuiView$__Block_427_39 {
	SuiView$DockLayout*  self ;
	SuiView$DockItem*  parentItem ;
};





struct tagSuiView$__Block_432_39 {
	SuiView$DockItem *  kid ;
};





struct tagSuiView$__Block_439_30 {
	SuiView$DockItem *  nextKid ;
};





struct tagSuiView$__Block_507_56 {
	SuiView$DockLayout*  self ;
};





struct tagSuiView$__Block_513_39 {
	SuiView$DockItem*  kid ;
};





struct tagSuiView$__Closure_285_30 {
	void  (*invoke)(SuiView$__Closure_285_30 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiView$__Block_281_15*  __var___Block_281_15 ;
};





struct tagSuiView$__Closure_447_40 {
	void  (*invoke)(SuiView$__Closure_447_40 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiView$__Block_427_39*  __var___Block_427_39 ;
	SuiView$__Block_432_39*  __var___Block_432_39 ;
	SuiView$__Block_439_30*  __var___Block_439_30 ;
};





struct tagSuiView$__Closure_518_38 {
	void  (*invoke)(SuiView$__Closure_518_38 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiView$__Block_507_56*  __var___Block_507_56 ;
	SuiView$__Block_513_39*  __var___Block_513_39 ;
};





// static function declaration
static void  __finiBlock___Block_281_15(SuiView$__Block_281_15 *  self);
static void  __finiBlock___Block_427_39(SuiView$__Block_427_39 *  self);
static void  __finiBlock___Block_432_39(SuiView$__Block_432_39 *  self);
static void  __finiBlock___Block_439_30(SuiView$__Block_439_30 *  self);
static void  __finiBlock___Block_507_56(SuiView$__Block_507_56 *  self);
static void  __finiBlock___Block_513_39(SuiView$__Block_513_39 *  self);
static void  __fn___Closure_285_30(SuiView$__Closure_285_30 *  self, SuiView$Drag *  d);
static void  __fini___Closure_285_30(SuiView$__Closure_285_30 *  self);
static SuiView$__Closure_285_30*  __make___Closure_285_30(SuiView$__Closure_285_30 **  __outRef__, SuiView$__Block_281_15 *  __var___Block_281_15);
static void  __fn___Closure_447_40(SuiView$__Closure_447_40 *  self, SuiView$Drag *  d);
static void  __fini___Closure_447_40(SuiView$__Closure_447_40 *  self);
static SuiView$__Closure_447_40*  __make___Closure_447_40(SuiView$__Closure_447_40 **  __outRef__, SuiView$__Block_427_39 *  __var___Block_427_39, SuiView$__Block_432_39 *  __var___Block_432_39, SuiView$__Block_439_30 *  __var___Block_439_30);
static void  __fn___Closure_518_38(SuiView$__Closure_518_38 *  self, SuiCore$Event *  e);
static void  __fini___Closure_518_38(SuiView$__Closure_518_38 *  self);
static SuiView$__Closure_518_38*  __make___Closure_518_38(SuiView$__Closure_518_38 **  __outRef__, SuiView$__Block_507_56 *  __var___Block_507_56, SuiView$__Block_513_39 *  __var___Block_513_39);


static const char *  SPLITTER = "splitter";
static const char *  TAB = "tab";
static const char *  ITEM = "item";

//vtable instance
Vtable_SuiView$DockItem _vtable_SuiView$DockItem;

// init meta

void SuiView$DockItem_initMeta(Vtable_SuiView$DockItem *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "intId", OrcMetaType_int, offsetof(SuiView$DockItem, intId), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "id", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$DockItem, id), true, false, 1);
	orc_metaField_class(&pNext, "view", ((Vtable_Object*)Vtable_SuiCore$ViewBase_init(0)), offsetof(SuiView$DockItem, view), true, false, 1);
	orc_metaField_primitive(&pNext, "isHorizontal", OrcMetaType_bool, offsetof(SuiView$DockItem, isHorizontal), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "type", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$DockItem, type), true, false, 1);
	orc_metaField_primitive(&pNext, "width", OrcMetaType_float, offsetof(SuiView$DockItem, width), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "weight", OrcMetaType_float, offsetof(SuiView$DockItem, weight), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "_sumContentSize", OrcMetaType_float, offsetof(SuiView$DockItem, _sumContentSize), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "_sumFlexSize", OrcMetaType_float, offsetof(SuiView$DockItem, _sumFlexSize), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "_sumWeight", OrcMetaType_float, offsetof(SuiView$DockItem, _sumWeight), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "children", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiView$DockItem, children), true, false, 1);
	orc_metaField_class(&pNext, "parent", ((Vtable_Object*)Vtable_SuiView$DockItem_init(0)), offsetof(SuiView$DockItem, parent), true, false, 1);
	orc_metaField_class(&pNext, "nextSplitterView", ((Vtable_Object*)Vtable_SuiCore$ViewBase_init(0)), offsetof(SuiView$DockItem, nextSplitterView), true, false, 1);
	orc_metaField_class(&pNext, "prevSplitterView", ((Vtable_Object*)Vtable_SuiCore$ViewBase_init(0)), offsetof(SuiView$DockItem, prevSplitterView), true, false, 1);
	orc_metaField_primitive(&pNext, "tabActiveIndex", OrcMetaType_int, offsetof(SuiView$DockItem, tabActiveIndex), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "fromJson", offsetof(SuiView$DockItem, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiView$DockItem, toJson));
	orc_metaField_method(&pNext, "setTabActiveIndex", offsetof(SuiView$DockItem, setTabActiveIndex));
	orc_metaField_method(&pNext, "setSelfActive_inTab", offsetof(SuiView$DockItem, setSelfActive_inTab));
	orc_metaField_method(&pNext, "calcWeight_ofKid_forDragSplitter", offsetof(SuiView$DockItem, calcWeight_ofKid_forDragSplitter));
	orc_metaField_method(&pNext, "appendChild", offsetof(SuiView$DockItem, appendChild));
	orc_metaField_method(&pNext, "removeSelf", offsetof(SuiView$DockItem, removeSelf));
	orc_metaField_method(&pNext, "insertBefore", offsetof(SuiView$DockItem, insertBefore));
	orc_metaField_method(&pNext, "insertAfter", offsetof(SuiView$DockItem, insertAfter));
	orc_metaField_method(&pNext, "insertOffset", offsetof(SuiView$DockItem, insertOffset));
	orc_metaField_method(&pNext, "removeChild", offsetof(SuiView$DockItem, removeChild));
	orc_metaField_method(&pNext, "tryGetParentTab", offsetof(SuiView$DockItem, tryGetParentTab));
	orc_metaField_method(&pNext, "printTree", offsetof(SuiView$DockItem, printTree));
	orc_metaField_method(&pNext, "isEmptySplitter", offsetof(SuiView$DockItem, isEmptySplitter));
	orc_metaField_method(&pNext, "isEmptyTab", offsetof(SuiView$DockItem, isEmptyTab));
}


// vtable init


Vtable_SuiView$DockItem* Vtable_SuiView$DockItem_init(Vtable_SuiView$DockItem* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$DockItem;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$DockItem_new;
    ((Vtable_Object*)pvt)->className = "SuiView$DockItem";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$DockItem_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$DockItem_fini(SuiView$DockItem *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiView$DockItem_init_fields(SuiView$DockItem *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$DockItem_fini;
	//fields
    {
	((SuiView$DockItem*)self)->intId = 0;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$DockItem*)self)->id, Orc$str(&tmpReturn_1, "") );
	urgc_set_field_class(self, (void**)&((SuiView$DockItem*)self)->view, NULL);
	((SuiView$DockItem*)self)->isHorizontal = false;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$DockItem*)self)->type, Orc$str(&tmpReturn_2, ITEM) );
	((SuiView$DockItem*)self)->width = 0;
	((SuiView$DockItem*)self)->weight = 1;
	((SuiView$DockItem*)self)->_sumContentSize = 0;
	((SuiView$DockItem*)self)->_sumFlexSize = 0;
	((SuiView$DockItem*)self)->_sumWeight = 0;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$DockItem*)self)->children, Orc$List_new(&tmpNewOwner_3) );
	urgc_set_field_class(self, (void**)&((SuiView$DockItem*)self)->parent, NULL);
	urgc_set_field_class(self, (void**)&((SuiView$DockItem*)self)->nextSplitterView, NULL);
	urgc_set_field_class(self, (void**)&((SuiView$DockItem*)self)->prevSplitterView, NULL);
	((SuiView$DockItem*)self)->tabActiveIndex = 0;
    }
	((SuiView$DockItem*)self)->fromJson = (void*)SuiView$DockItem$fromJson;
	((SuiView$DockItem*)self)->toJson = (void*)SuiView$DockItem$toJson;
	((SuiView$DockItem*)self)->setTabActiveIndex = (void*)SuiView$DockItem$setTabActiveIndex;
	((Object*)self)->dtor = (void*)SuiView$DockItem$dtor;
	((SuiView$DockItem*)self)->setSelfActive_inTab = (void*)SuiView$DockItem$setSelfActive_inTab;
	((SuiView$DockItem*)self)->calcWeight_ofKid_forDragSplitter = (void*)SuiView$DockItem$calcWeight_ofKid_forDragSplitter;
	((SuiView$DockItem*)self)->appendChild = (void*)SuiView$DockItem$appendChild;
	((SuiView$DockItem*)self)->removeSelf = (void*)SuiView$DockItem$removeSelf;
	((SuiView$DockItem*)self)->insertBefore = (void*)SuiView$DockItem$insertBefore;
	((SuiView$DockItem*)self)->insertAfter = (void*)SuiView$DockItem$insertAfter;
	((SuiView$DockItem*)self)->insertOffset = (void*)SuiView$DockItem$insertOffset;
	((SuiView$DockItem*)self)->removeChild = (void*)SuiView$DockItem$removeChild;
	((SuiView$DockItem*)self)->tryGetParentTab = (void*)SuiView$DockItem$tryGetParentTab;
	((SuiView$DockItem*)self)->printTree = (void*)SuiView$DockItem$printTree;
	((SuiView$DockItem*)self)->isEmptySplitter = (void*)SuiView$DockItem$isEmptySplitter;
	((SuiView$DockItem*)self)->isEmptyTab = (void*)SuiView$DockItem$isEmptyTab;
}

// init function

void SuiView$DockItem_init(SuiView$DockItem *self, void *pOwner){
    Vtable_SuiView$DockItem_init(&_vtable_SuiView$DockItem);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$DockItem;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$DockItem_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$DockItem * SuiView$DockItem_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$DockItem *self = calloc(1, sizeof(SuiView$DockItem));
	
    SuiView$DockItem_init(self, pOwner);
    return self;
}


// class members
void  SuiView$DockItem$fromJson(SuiView$DockItem *  self, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	self->intId = jo->getNumber(jo, "intId") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiView$DockItem, id) , jo->getString(&tmpReturn_1, jo, "id") ) ;
	self->isHorizontal = jo->getBool(jo, "isHorizontal") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiView$DockItem, type) , jo->getString(&tmpReturn_2, jo, "type") ) ;
	self->width = jo->getNumber(jo, "width") ;
	self->weight = jo->getNumber(jo, "weight") ;
}


Json$Json*  SuiView$DockItem$toJson(Json$Json **  __outRef__, SuiView$DockItem *  self){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	jo->putNumber(jo, "intId", self->intId) ;
	jo->putString(jo, "id", self->id) ;
	jo->putBool(jo, "isHorizontal", self->isHorizontal) ;
	jo->putString(jo, "type", self->type) ;
	jo->putNumber(jo, "width", self->width) ;
	jo->putNumber(jo, "weight", self->weight) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  kids = Json$Json_mkArray((kids = NULL,&kids)) ;
	jo->put(jo, "children", kids) ;
	for (int  i = 0; i < self->children->size(self->children) ; i++) {
		SuiView$DockItem *  kid = (SuiView$DockItem * )self->children->get(self->children, i) ;
		URGC_VAR_CLEANUP_CLASS Json$Json*  kidJo = kid->toJson((kidJo = NULL,&kidJo), kid) ;
		kids->add(kids, kidJo) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, jo) ; 
}


void  SuiView$DockItem$setTabActiveIndex(SuiView$DockItem *  self, int  index){
	self->tabActiveIndex = Orc$clampInt(index, 0, self->children->size(self->children)  - 1) ;
}


void  SuiView$DockItem$dtor(SuiView$DockItem *  self){
	printf("释放DockItem:%p %s\n", self, self->id->str) ;
	if (self->parent) {
		self->parent->printTree(self->parent, 0) ;
	}
}


void  SuiView$DockItem$setSelfActive_inTab(SuiView$DockItem *  self){
	if (self->parent && Orc$String$equals(self->parent->type, TAB) ) {
		int  idx = self->parent->children->indexOf(self->parent->children, self) ;
		self->parent->setTabActiveIndex(self->parent, idx) ;
	}
}


float  SuiView$DockItem$calcWeight_ofKid_forDragSplitter(SuiView$DockItem *  self, SuiView$DockItem *  kid, float  delta, float  minSize){
	if (kid->width > 0) {
		return 0; 
	}
	float  actualSize = kid->weight / self->_sumWeight * self->_sumFlexSize;
	float  newSize = Orc$maxFloat(minSize, actualSize + delta) ;
	float  newWeight = newSize / self->_sumFlexSize * self->_sumWeight;
	return newWeight; 
}


void  SuiView$DockItem$appendChild(SuiView$DockItem *  self, SuiView$DockItem *  item){
	item->removeSelf(item) ;
	self->children->add(self->children, item) ;
	urgc_set_field_class(item, (void * )offsetof(SuiView$DockItem, parent) , self) ;
}


void  SuiView$DockItem$removeSelf(SuiView$DockItem *  self){
	if (self->parent) {
		self->parent->removeChild(self->parent, self) ;
	}
}


bool  SuiView$DockItem$insertBefore(SuiView$DockItem *  self, SuiView$DockItem *  newItem, SuiView$DockItem *  relChild){
	return self->insertOffset(self, newItem, relChild, 0) ; 
}


bool  SuiView$DockItem$insertAfter(SuiView$DockItem *  self, SuiView$DockItem *  newItem, SuiView$DockItem *  relChild){
	return self->insertOffset(self, newItem, relChild, 1) ; 
}


bool  SuiView$DockItem$insertOffset(SuiView$DockItem *  self, SuiView$DockItem *  newItem, SuiView$DockItem *  relChild, int  offset){
	if (newItem == NULL) {
		return false; 
	}
	int  idx = self->children->indexOf(self->children, relChild) ;
	if (idx == -1) {
		return false; 
	}
	newItem->removeSelf(newItem) ;
	self->children->insert(self->children, newItem, idx + offset) ;
	urgc_set_field_class(newItem, (void * )offsetof(SuiView$DockItem, parent) , self) ;
	return true; 
}


void  SuiView$DockItem$removeChild(SuiView$DockItem *  self, SuiView$DockItem *  kid){
	if (kid->parent == self) {
		self->children->remove(self->children, kid) ;
		urgc_set_field_class(kid, (void * )offsetof(SuiView$DockItem, parent) , NULL) ;
	}
}


SuiView$DockItem *  SuiView$DockItem$tryGetParentTab(SuiView$DockItem *  self){
	SuiView$DockItem *  cur = self->parent;
	if (Orc$String$equals(cur->type, TAB) ) {
		return cur; 
	}
	return NULL; 
}


void  SuiView$DockItem$printTree(SuiView$DockItem *  self, int  tab){
	for (int  i = 0; i < tab; i++) {
		printf("\t") ;
	}
	printf("%s@%p#%d[%f,%f]\n", self->id->str, self, self->intId, self->width, self->weight) ;
	for (int  i = 0; i < self->children->size(self->children) ; i++) {
		SuiView$DockItem *  kid = (SuiView$DockItem * )self->children->get(self->children, i) ;
		kid->printTree(kid, tab + 1) ;
	}
}


bool  SuiView$DockItem$isEmptySplitter(SuiView$DockItem *  self){
	if (Orc$String$equals(self->type, SPLITTER) ) {
		if (self->children->size(self->children)  == 0) {
			return true; 
		}
	}
	return false; 
}


bool  SuiView$DockItem$isEmptyTab(SuiView$DockItem *  self){
	if (Orc$String$equals(self->type, TAB) ) {
		if (self->children->size(self->children)  == 0) {
			return true; 
		}
	}
	return false; 
}



SuiView$DockItem*  SuiView$DockItem_fromJson(SuiView$DockItem **  __outRef__, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  di = (di=NULL,urgc_init_var_class((void**)&di, SuiView$DockItem_new(&di) ));
	di->fromJson(di, jo) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  children = jo->get((children = NULL,&children), jo, "children") ;
	if (children) {
		int  l = children->arraySize(children) ;
		for (int  i = 0; i < l; i++) {
			URGC_VAR_CLEANUP_CLASS Json$Json*  kid = children->at((kid = NULL,&kid), children, i) ;
			URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  kidDi = SuiView$DockItem_fromJson((kidDi = NULL,&kidDi), kid) ;
			di->appendChild(di, kidDi) ;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, di) ; 
}

SuiView$DockItem*  SuiView$mkDockItem(SuiView$DockItem **  __outRef__, SuiView$DockItem *  parent, Orc$String*  id){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(id);

	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  ins = (ins=NULL,urgc_init_var_class((void**)&ins, SuiView$DockItem_new(&ins) ));
	if (id) {
		urgc_set_field_class(ins, (void * )offsetof(SuiView$DockItem, id) , id) ;
	}
	if (parent) {
		parent->appendChild(parent, ins) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ins) ; 
}

SuiView$DockItem*  SuiView$mkDockItemSplitter(SuiView$DockItem **  __outRef__, SuiView$DockItem *  parent, Orc$String*  id, bool  isHorizontal){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(id);

	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  ins = SuiView$mkDockItem((ins = NULL,&ins), parent, id) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(ins, (void * )offsetof(SuiView$DockItem, type) , Orc$str(&tmpReturn_1, SPLITTER) ) ;
	ins->isHorizontal = isHorizontal;
	return urgc_set_var_for_return_class((void ** )__outRef__, ins) ; 
}

SuiView$DockItem*  SuiView$mkDockItemTab(SuiView$DockItem **  __outRef__, SuiView$DockItem *  parent, Orc$String*  id){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(id);

	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  ins = SuiView$mkDockItem((ins = NULL,&ins), parent, id) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(ins, (void * )offsetof(SuiView$DockItem, type) , Orc$str(&tmpReturn_1, TAB) ) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ins) ; 
}


//vtable instance
Vtable_SuiView$DockLayout _vtable_SuiView$DockLayout;

// init meta

void SuiView$DockLayout_initMeta(Vtable_SuiView$DockLayout *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "splitterSize", OrcMetaType_int, offsetof(SuiView$DockLayout, splitterSize), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "minItemSize", OrcMetaType_float, offsetof(SuiView$DockLayout, minItemSize), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "tabHeadBg", OrcMetaType_int, offsetof(SuiView$DockLayout, tabHeadBg), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "root", ((Vtable_Object*)Vtable_SuiView$DockItem_init(0)), offsetof(SuiView$DockLayout, root), true, false, 1);
	orc_metaField_class(&pNext, "dragTab", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiView$DockLayout, dragTab), true, false, 1);

	orc_metaField_method(&pNext, "doDrop", offsetof(SuiView$DockLayout, doDrop));
	orc_metaField_method(&pNext, "onDragSplitter", offsetof(SuiView$DockLayout, onDragSplitter));
	orc_metaField_method(&pNext, "_reactDockItem", offsetof(SuiView$DockLayout, _reactDockItem));
	orc_metaField_method(&pNext, "_onClickTabItemHead", offsetof(SuiView$DockLayout, _onClickTabItemHead));
	orc_metaField_method(&pNext, "_onEvent_tabItemHead", offsetof(SuiView$DockLayout, _onEvent_tabItemHead));
	orc_metaField_method(&pNext, "_reactTabHeads", offsetof(SuiView$DockLayout, _reactTabHeads));
	orc_metaField_method(&pNext, "_reactTabContent", offsetof(SuiView$DockLayout, _reactTabContent));
	orc_metaField_method(&pNext, "layoutContentDockItem", offsetof(SuiView$DockLayout, layoutContentDockItem));
	orc_metaField_method(&pNext, "drawDndIndicator", offsetof(SuiView$DockLayout, drawDndIndicator));
	orc_metaField_method(&pNext, "findDockItem_containsVec2", offsetof(SuiView$DockLayout, findDockItem_containsVec2));
	orc_metaField_method(&pNext, "upto_findMostAncestorInDockItemSplitter", offsetof(SuiView$DockLayout, upto_findMostAncestorInDockItemSplitter));
	orc_metaField_method(&pNext, "dropInSplitter", offsetof(SuiView$DockLayout, dropInSplitter));
	orc_metaField_method(&pNext, "upto_getOrWrap_DockItemTab", offsetof(SuiView$DockLayout, upto_getOrWrap_DockItemTab));
	orc_metaField_method(&pNext, "clearAllEmptyTab", offsetof(SuiView$DockLayout, clearAllEmptyTab));
	orc_metaField_method(&pNext, "eachThenWrapTab_forNakeDockItemInSplitter", offsetof(SuiView$DockLayout, eachThenWrapTab_forNakeDockItemInSplitter));
}


// vtable init


Vtable_SuiView$DockLayout* Vtable_SuiView$DockLayout_init(Vtable_SuiView$DockLayout* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$DockLayout;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$DockLayout_new;
    ((Vtable_Object*)pvt)->className = "SuiView$DockLayout";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$DockLayout_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$DockLayout_fini(SuiView$DockLayout *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiView$DockLayout_init_fields(SuiView$DockLayout *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$DockLayout_fini;
	//fields
    {
	((SuiView$DockLayout*)self)->splitterSize = 1;
	((SuiView$DockLayout*)self)->minItemSize = 10;
	((SuiView$DockLayout*)self)->tabHeadBg = 0x33ff0000;
	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$DockLayout*)self)->root, SuiView$mkDockItemSplitter(&tmpReturn_1, NULL, Orc$str(&tmpReturn_2, "") , true) );
	urgc_set_field(self, (void**)&((SuiView$DockLayout*)self)->cbRenderItemContentView, NULL);
	urgc_set_field(self, (void**)&((SuiView$DockLayout*)self)->cbRenderItemHeadView, NULL);
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$DockLayout*)self)->dragTab, SuiView$Drag_new(&tmpNewOwner_3) );
    }
	((Object*)self)->ctor = (void*)SuiView$DockLayout$ctor;
	((SuiView$DockLayout*)self)->doDrop = (void*)SuiView$DockLayout$doDrop;
	((SuiCore$Node*)self)->react = (void*)SuiView$DockLayout$react;
	((SuiView$DockLayout*)self)->onDragSplitter = (void*)SuiView$DockLayout$onDragSplitter;
	((SuiView$DockLayout*)self)->_reactDockItem = (void*)SuiView$DockLayout$_reactDockItem;
	((SuiView$DockLayout*)self)->_onClickTabItemHead = (void*)SuiView$DockLayout$_onClickTabItemHead;
	((SuiView$DockLayout*)self)->_onEvent_tabItemHead = (void*)SuiView$DockLayout$_onEvent_tabItemHead;
	((SuiView$DockLayout*)self)->_reactTabHeads = (void*)SuiView$DockLayout$_reactTabHeads;
	((SuiView$DockLayout*)self)->_reactTabContent = (void*)SuiView$DockLayout$_reactTabContent;
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiView$DockLayout$layoutContent;
	((SuiView$DockLayout*)self)->layoutContentDockItem = (void*)SuiView$DockLayout$layoutContentDockItem;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$DockLayout$draw_self;
	((SuiView$DockLayout*)self)->drawDndIndicator = (void*)SuiView$DockLayout$drawDndIndicator;
	((SuiView$DockLayout*)self)->findDockItem_containsVec2 = (void*)SuiView$DockLayout$findDockItem_containsVec2;
	((SuiView$DockLayout*)self)->upto_findMostAncestorInDockItemSplitter = (void*)SuiView$DockLayout$upto_findMostAncestorInDockItemSplitter;
	((SuiView$DockLayout*)self)->dropInSplitter = (void*)SuiView$DockLayout$dropInSplitter;
	((SuiView$DockLayout*)self)->upto_getOrWrap_DockItemTab = (void*)SuiView$DockLayout$upto_getOrWrap_DockItemTab;
	((SuiView$DockLayout*)self)->clearAllEmptyTab = (void*)SuiView$DockLayout$clearAllEmptyTab;
	((SuiView$DockLayout*)self)->eachThenWrapTab_forNakeDockItemInSplitter = (void*)SuiView$DockLayout$eachThenWrapTab_forNakeDockItemInSplitter;
	((SuiCore$ViewBase*)self)->hitTestChildren = (void*)SuiView$DockLayout$hitTestChildren;
}

// init function

void SuiView$DockLayout_init(SuiView$DockLayout *self, void *pOwner){
    Vtable_SuiView$DockLayout_init(&_vtable_SuiView$DockLayout);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$DockLayout;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$DockLayout_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$DockLayout * SuiView$DockLayout_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$DockLayout *self = calloc(1, sizeof(SuiView$DockLayout));
	
    SuiView$DockLayout_init(self, pOwner);
    return self;
}


// class members
void  SuiView$DockLayout$ctor(SuiView$DockLayout *  self){
	URGC_VAR_CLEANUP SuiView$__Block_281_15*  __var___Block_281_15 = (__var___Block_281_15=NULL,urgc_init_var((void**)&__var___Block_281_15, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_281_15) , __finiBlock___Block_281_15) ));
	urgc_set_field_class(__var___Block_281_15, (void * )offsetof(SuiView$__Block_281_15, self) , self) ;
	URGC_VAR_CLEANUP SuiView$__Closure_285_30*  tmpReturn_1 = NULL;
	urgc_set_field(self->dragTab, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_285_30(&tmpReturn_1, __var___Block_281_15) ) ;
}


void  SuiView$DockLayout$doDrop(SuiView$DockLayout *  self){
	SuiCore$Vec2 mousePos = SuiCore$Mouse_getPosOfWindow(((SuiCore$Node * )self)->ownerWindow) ;
	SuiView$DockItem *  target = self->findDockItem_containsVec2(self, self->root, mousePos.x, mousePos.y) ;
	if (target && target->view) {
		SuiCore$Rect absRect = target->view->get_abs_rect(target->view) ;
		printf("mousePos.:%f,%f abs:%f,%f,%f,%f\n", mousePos.x, mousePos.y, absRect.x, absRect.y, absRect.w, absRect.h) ;
		int  geoType = -1;
		SuiCore$Rect geo = SuiCore$Rect$containsPositionIn5Patch_withOutType(&absRect, mousePos.x, mousePos.y, SuiCore$mkRect(0.2, 0.2, 0.6, 0.6) , &geoType) ;
		if (geo.x == -1) {
			printf("放置tab无效，未找到目标\n") ;
			return ; 
		}
		if (Orc_instanceof((Object*)self->dragTab->data, (Vtable_Object*)Vtable_SuiView$DockItem_init(NULL))) {
			URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  source = (source=NULL,urgc_init_var_class((void**)&source, (SuiView$DockItem * )self->dragTab->data));
			printf("do Drop source:%s, target:%s, geoType:%d\n", source->id->str, target->id->str, geoType) ;
			if (source == target) {
				return ; 
			}
			if (geoType == 0) {
				self->dropInSplitter(self, source, target, false, true) ;
			}
			if (geoType == 1) {
				self->dropInSplitter(self, source, target, true, true) ;
			}
			if (geoType == 2) {
				URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tab = self->upto_getOrWrap_DockItemTab((tab = NULL,&tab), self, target) ;
				if (tab) {
					printf("doDrop. create tab:%p %s\n", tab, tab->id->str) ;
					tab->appendChild(tab, source) ;
					((SuiCore$Node * )self)->invalidReact(self) ;
				}
			}
			if (geoType == 3) {
				self->dropInSplitter(self, source, target, true, false) ;
			}
			if (geoType == 4) {
				self->dropInSplitter(self, source, target, false, false) ;
			}
			self->clearAllEmptyTab(self, self->root) ;
		}
	}
	self->root->printTree(self->root, 0) ;
}


void  SuiView$DockLayout$react(SuiView$DockLayout *  self){
	((SuiCore$Node * )self)->startInnerReact(self) ;
	self->eachThenWrapTab_forNakeDockItemInSplitter(self, self->root) ;
	self->_reactDockItem(self, self->root) ;
	((SuiCore$Node * )self)->endInnerReact(self) ;
}


void  SuiView$DockLayout$onDragSplitter(SuiView$DockLayout *  self, SuiView$Drag *  drag, SuiView$DockItem *  parentDockItem, SuiView$DockItem *  prevDockItem, SuiView$DockItem *  nextDockItem){
	printf("drag SPlitter. parent:%s, prev:%s, next:%s\n", parentDockItem->id->str, prevDockItem->id->str, nextDockItem->id->str) ;
	if (drag->isDragChecking) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(drag, (void * )offsetof(SuiView$Drag, cursor) , parentDockItem->isHorizontal ? Orc$str(&tmpReturn_1, "sizewe")  : Orc$str(&tmpReturn_2, "sizens") ) ;
	}
	if (drag->isDragging) {
		float  delta = drag->deltaPos.y;
		if (parentDockItem->isHorizontal) {
			delta = drag->deltaPos.x;
		}
		if (prevDockItem->width > 0 && nextDockItem->width > 0) {
			prevDockItem->width = Orc$maxFloat(self->minItemSize, prevDockItem->width + delta) ;
			nextDockItem->width = Orc$maxFloat(self->minItemSize, nextDockItem->width - delta) ;
		}
		else if (prevDockItem->width > 0 && nextDockItem->width == 0) {
			prevDockItem->width = Orc$maxFloat(self->minItemSize, prevDockItem->width + delta) ;
		}
		else if (prevDockItem->width == 0 && nextDockItem->width > 0) {
			nextDockItem->width = Orc$maxFloat(self->minItemSize, nextDockItem->width - delta) ;
		}
		else {
			prevDockItem->weight = parentDockItem->calcWeight_ofKid_forDragSplitter(parentDockItem, prevDockItem, delta, self->minItemSize) ;
			nextDockItem->weight = parentDockItem->calcWeight_ofKid_forDragSplitter(parentDockItem, nextDockItem, -delta, self->minItemSize) ;
		}
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


void  SuiView$DockLayout$_reactDockItem(SuiView$DockLayout *  self, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP SuiView$__Block_427_39*  __var___Block_427_39 = (__var___Block_427_39=NULL,urgc_init_var((void**)&__var___Block_427_39, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_427_39) , __finiBlock___Block_427_39) ));
	urgc_set_field_class(__var___Block_427_39, (void * )offsetof(SuiView$__Block_427_39, self) , self) ;
	urgc_set_field_class(__var___Block_427_39, (void * )offsetof(SuiView$__Block_427_39, parentItem) , item) ;
	if (Orc$String$equals(item->type, SPLITTER) ) {
		SuiCore$View *  splitterView = NULL;
		int  l = item->children->size(item->children) ;
		for (int  i = 0; i < l; i++) {
			URGC_VAR_CLEANUP SuiView$__Block_432_39*  __var___Block_432_39 = (__var___Block_432_39=NULL,urgc_init_var((void**)&__var___Block_432_39, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_432_39) , __finiBlock___Block_432_39) ));
			int  index = i;
			__var___Block_432_39->kid = (SuiView$DockItem * )item->children->get(item->children, i) ;
			urgc_set_field_class(__var___Block_432_39->kid, (void * )offsetof(SuiView$DockItem, prevSplitterView) , splitterView) ;
			self->_reactDockItem(self, __var___Block_432_39->kid) ;
			if (i < l - 1) {
				URGC_VAR_CLEANUP SuiView$__Block_439_30*  __var___Block_439_30 = (__var___Block_439_30=NULL,urgc_init_var((void**)&__var___Block_439_30, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_439_30) , __finiBlock___Block_439_30) ));
				__var___Block_439_30->nextKid = (SuiView$DockItem * )item->children->get(item->children, i + 1) ;
				URGC_VAR_CLEANUP_CLASS SuiView$DockSplitterView*  tmpReturn_1 = NULL;
				{
					SuiView$DockSplitterView*  o = SuiView$dockSplitterView(&tmpReturn_1, self, ((long long )item) + 2000 + i) ;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_445_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					((SuiCore$ViewBase * )o)->z = 10;
					URGC_VAR_CLEANUP SuiView$__Closure_447_40*  tmpReturn_2 = NULL;
					urgc_set_field(o->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_447_40(&tmpReturn_2, __var___Block_427_39, __var___Block_432_39, __var___Block_439_30) ) ;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiCore$ViewBase, cursor) , item->isHorizontal ? Orc$str(&tmpReturn_3, "sizewe")  : Orc$str(&tmpReturn_4, "sizens") ) ;
					urgc_set_field_class(__var___Block_432_39->kid, (void * )offsetof(SuiView$DockItem, nextSplitterView) , o) ;
					splitterView = o;
				}
			}
		}
	}
	if (Orc$String$equals(item->type, TAB) ) {
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_5 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$layoutLinear(&tmpReturn_5, self, (long long )item) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_464_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->needClip = true;
			urgc_set_field_class(item, (void * )offsetof(SuiView$DockItem, view) , o) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_6, "column") ) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_7, "stretch") ) ;
			self->_reactTabHeads(self, item, o) ;
			self->_reactTabContent(self, item, o) ;
		}
	}
	if (Orc$String$equals(item->type, ITEM) ) {
		if (self->cbRenderItemContentView) {
			SuiCore$ViewBase *  v = (*(self->cbRenderItemContentView))((void * )(self->cbRenderItemContentView), item, self) ;
			urgc_set_field_class(item, (void * )offsetof(SuiView$DockItem, view) , v) ;
		}
	}
}


void  SuiView$DockLayout$_onClickTabItemHead(SuiView$DockLayout *  self, SuiView$DockItem *  kid){
	kid->setSelfActive_inTab(kid) ;
	((SuiCore$Node * )self)->invalidReact(self) ;
}


void  SuiView$DockLayout$_onEvent_tabItemHead(SuiView$DockLayout *  self, SuiCore$Event *  e, SuiView$DockItem *  kid){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->isMouseDown) {
			self->_onClickTabItemHead(self, kid) ;
		}
		urgc_set_field_class(self->dragTab, (void * )offsetof(SuiView$Drag, data) , kid) ;
		self->dragTab->onMouseDown(self->dragTab, me) ;
	}
}


void  SuiView$DockLayout$_reactTabHeads(SuiView$DockLayout *  self, SuiView$DockItem *  tab, SuiCore$ViewBase *  parent){
	URGC_VAR_CLEANUP SuiView$__Block_507_56*  __var___Block_507_56 = (__var___Block_507_56=NULL,urgc_init_var((void**)&__var___Block_507_56, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_507_56) , __finiBlock___Block_507_56) ));
	urgc_set_field_class(__var___Block_507_56, (void * )offsetof(SuiView$__Block_507_56, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  o = SuiLayout$layoutLinear(&tmpReturn_1, parent, 0) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_508_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_2, "row") ) ;
		((SuiCore$View * )o)->backgroundColor = self->tabHeadBg;
		int  l = tab->children->size(tab->children) ;
		for (int  i = 0; i < l; i++) {
			URGC_VAR_CLEANUP SuiView$__Block_513_39*  __var___Block_513_39 = (__var___Block_513_39=NULL,urgc_init_var((void**)&__var___Block_513_39, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_513_39) , __finiBlock___Block_513_39) ));
			urgc_set_field_class(__var___Block_513_39, (void * )offsetof(SuiView$__Block_513_39, kid) , (SuiView$DockItem* )tab->children->get(tab->children, i) ) ;
			if (Orc$String$equals(__var___Block_513_39->kid->type, ITEM) ) {
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_3 = NULL;
				{
					SuiLayout$LayoutLinear*  __scopeVar_516_20 = SuiLayout$layoutLinear(&tmpReturn_3, o, (long long )__var___Block_513_39->kid) , *o = __scopeVar_516_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_516_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP SuiView$__Closure_518_38*  tmpReturn_4 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_518_38(&tmpReturn_4, __var___Block_507_56, __var___Block_513_39) ) ;
					if (self->cbRenderItemHeadView) {
						(*(self->cbRenderItemHeadView))((void * )(self->cbRenderItemHeadView), __var___Block_513_39->kid, o, i) ;
					}
				}
			}
		}
	}
}


void  SuiView$DockLayout$_reactTabContent(SuiView$DockLayout *  self, SuiView$DockItem *  tab, SuiCore$ViewBase *  parent){
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  o = SuiLayout$layoutLinear(&tmpReturn_1, parent, 0) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_530_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_2, "column") ) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_3, "stretch") ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_4 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_536_12 = SuiLayout$layoutLinearCell(&tmpReturn_4, o, 0) , *o = __scopeVar_536_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_536_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		SuiView$DockItem *  kid = (SuiView$DockItem * )tab->children->get(tab->children, tab->tabActiveIndex) ;
		if (kid) {
			if (self->cbRenderItemContentView) {
				SuiCore$ViewBase *  view = (*(self->cbRenderItemContentView))((void * )(self->cbRenderItemContentView), kid, o) ;
				urgc_set_field_class(kid, (void * )offsetof(SuiView$DockItem, view) , view) ;
			}
		}
	}
}


void  SuiView$DockLayout$layoutContent(SuiView$DockLayout *  self, SuiCore$Frame *  frame){
	if (!SuiCore$Frame$isTight(frame) ) {
		printf("\n\nDockLayout layoutContent. 非tight\n") ;
		return ; 
	}
	self->layoutContentDockItem(self, frame, self->root, 0, 0) ;
}


void  SuiView$DockLayout$layoutContentDockItem(SuiView$DockLayout *  self, SuiCore$Frame *  frame, SuiView$DockItem *  item, int  px, int  py){
	if (Orc$String$equals(item->type, SPLITTER) ) {
		int  kidsSize = item->children->size(item->children) ;
		float  sumSplitterSize = (kidsSize - 1) * self->splitterSize;
		float  mainSize = item->isHorizontal ? frame->width : frame->height;
		float  sumContentSize = mainSize - sumSplitterSize;
		float  sumWeight = 0;
		float  sumWidth = 0;
		int  l = kidsSize;
		for (int  i = 0; i < l; i++) {
			SuiView$DockItem *  kid = (SuiView$DockItem * )item->children->get(item->children, i) ;
			float  w = Orc$maxFloat(0.0, kid->width) ;
			if (w > 0) {
				sumWidth = sumWidth + w;
			}
			else {
				sumWeight = sumWeight + Orc$maxFloat(0.0, kid->weight) ;
			}
		}
		if (sumWeight <= 0) {
			sumWeight = 1.0;
		}
		float  flexSpaceSize = Orc$maxFloat(0.0, sumContentSize - sumWidth) ;
		item->_sumContentSize = sumContentSize;
		item->_sumFlexSize = flexSpaceSize;
		item->_sumWeight = sumWeight;
		float  pos = 0.0;
		l = kidsSize;
		for (int  i = 0; i < l; i++) {
			SuiView$DockItem *  kid = (SuiView$DockItem * )item->children->get(item->children, i) ;
			SuiCore$Frame tmpFrame = SuiCore$mkFrame() ;
			SuiCore$Frame *  kidFrame = kid->view ? &kid->view->frame : &tmpFrame;
			float  kidSize = 0.0;
			if (item->isHorizontal) {
				kidFrame->x = pos + px;
				kidFrame->y = 0.0 + py;
				kidSize = kid->width > 0 ? kid->width : Orc$maxFloat(0.0, kid->weight)  / sumWeight * flexSpaceSize;
				SuiCore$Frame$setTight(kidFrame, kidSize, frame->height) ;
			}
			else {
				kidFrame->x = 0.0 + px;
				kidFrame->y = pos + py;
				kidSize = kid->width > 0 ? kid->width : Orc$maxFloat(0.0, kid->weight)  / sumWeight * flexSpaceSize;
				SuiCore$Frame$setTight(kidFrame, frame->width, kidSize) ;
			}
			if (Orc$String$equals(kid->type, SPLITTER) ) {
				self->layoutContentDockItem(self, kidFrame, kid, kidFrame->x, kidFrame->y) ;
			}
			else {
				if (kid->view) {
					kid->view->layout(kid->view, kidFrame) ;
				}
			}
			pos = pos + kidSize;
			if (kid->nextSplitterView) {
				SuiCore$Frame *  f = &kid->nextSplitterView->frame;
				if (item->isHorizontal) {
					f->x = pos + px;
					f->y = 0 + py;
					SuiCore$Frame$setTight(f, self->splitterSize, frame->height) ;
				}
				else {
					f->x = 0 + px;
					f->y = pos + py;
					SuiCore$Frame$setTight(f, frame->width, self->splitterSize) ;
				}
				kid->nextSplitterView->layout(kid->nextSplitterView, f) ;
				pos = pos + self->splitterSize;
			}
		}
	}
}


void  SuiView$DockLayout$draw_self(SuiView$DockLayout *  self, SuiCore$Canvas *  canvas){
	SuiCore$View$draw_self(self, canvas) ;
	self->drawDndIndicator(self, canvas) ;
}


void  SuiView$DockLayout$drawDndIndicator(SuiView$DockLayout *  self, SuiCore$Canvas *  canvas){
	SuiView$Drag *  drag = self->dragTab;
	if (!drag->isDragging) {
		return ; 
	}
	if (!((SuiCore$Node * )self)->ownerWindow) {
		return ; 
	}
	SuiCore$Vec2 mousePos = SuiCore$Mouse_getPosOfWindow(((SuiCore$Node * )self)->ownerWindow) ;
	SuiView$DockItem *  target = self->findDockItem_containsVec2(self, self->root, mousePos.x, mousePos.y) ;
	if (target && target->view) {
		SuiCore$Canvas$save(canvas) ;
		SuiCore$Canvas$translate(canvas, ((SuiCore$View * )self)->padding.left + ((SuiCore$View * )self)->border->l->w, ((SuiCore$View * )self)->padding.top + ((SuiCore$View * )self)->border->t->w) ;
		SuiCore$Rect absRect = target->view->get_abs_rect(target->view) ;
		printf("mousePos.:%f,%f abs:%f,%f,%f,%f\n", mousePos.x, mousePos.y, absRect.x, absRect.y, absRect.w, absRect.h) ;
		SuiCore$Rect geo = SuiCore$Rect$containsPositionIn5Patch(&absRect, mousePos.x, mousePos.y, SuiCore$mkRect(0.2, 0.2, 0.6, 0.6) ) ;
		SuiCore$Rect r = SuiCore$Frame$toRect(&target->view->frame) ;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$fillColor(canvas, 255, 0, 0, 64) ;
		SuiCore$Canvas$rect(canvas, r.x + r.w * geo.x, r.y + r.h * geo.y, r.w * geo.w, r.h * geo.h) ;
		SuiCore$Canvas$fill(canvas) ;
		SuiCore$Canvas$restore(canvas) ;
	}
}


SuiView$DockItem *  SuiView$DockLayout$findDockItem_containsVec2(SuiView$DockLayout *  self, SuiView$DockItem *  item, int  clientX, int  clientY){
	if (item->view) {
		SuiCore$Rect r = item->view->get_abs_rect(item->view) ;
		bool  ok = SuiCore$Rect$containsPosition(&r, clientX, clientY) ;
		if (ok) {
			return item; 
		}
	}
	int  l = item->children->size(item->children) ;
	for (int  i = 0; i < l; i++) {
		SuiView$DockItem *  kid = (SuiView$DockItem * )item->children->get(item->children, i) ;
		SuiView$DockItem *  ret = self->findDockItem_containsVec2(self, kid, clientX, clientY) ;
		if (ret) {
			return ret; 
		}
	}
	return NULL; 
}


SuiView$DockItem*  SuiView$DockLayout$upto_findMostAncestorInDockItemSplitter(SuiView$DockItem **  __outRef__, SuiView$DockLayout *  self, SuiView$DockItem*  item){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(item);

	SuiView$DockItem *  cur = item;
	while (cur && cur->parent) {
		if (Orc$String$equals(cur->parent->type, SPLITTER) ) {
			return urgc_set_var_for_return_class((void ** )__outRef__, cur) ; 
		}
		cur = cur->parent;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


bool  SuiView$DockLayout$dropInSplitter(SuiView$DockLayout *  self, SuiView$DockItem*  source, SuiView$DockItem*  target, bool  isHorizontal, bool  isBefore){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(source);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(target);

	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  ancestor = self->upto_findMostAncestorInDockItemSplitter((ancestor = NULL,&ancestor), self, target) ;
	if (!ancestor) {
		return false; 
	}
	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  splitter = (splitter=NULL,urgc_init_var_class((void**)&splitter, ancestor->parent));
	if (!Orc$String$equals(splitter->type, SPLITTER) ) {
		return false; 
	}
	source->removeSelf(source) ;
	if (splitter->isHorizontal == isHorizontal) {
		splitter->insertOffset(splitter, source, ancestor, isBefore ? 0 : 1) ;
	}
	else {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  newSplitter = SuiView$mkDockItemSplitter((newSplitter = NULL,&newSplitter), NULL, Orc$String$addString(Orc$str(&tmpReturn_1, "splitter-of-") , ancestor->id) , isHorizontal) ;
		splitter->insertOffset(splitter, newSplitter, ancestor, 0) ;
		newSplitter->appendChild(newSplitter, ancestor) ;
		newSplitter->insertOffset(newSplitter, source, ancestor, isBefore ? 0 : 1) ;
	}
	((SuiCore$Node * )self)->invalidReact(self) ;
	return true; 
}


SuiView$DockItem*  SuiView$DockLayout$upto_getOrWrap_DockItemTab(SuiView$DockItem **  __outRef__, SuiView$DockLayout *  self, SuiView$DockItem*  item){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(item);

	if (Orc$String$equals(item->type, SPLITTER) ) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	if (Orc$String$equals(item->type, TAB) ) {
		return urgc_set_var_for_return_class((void ** )__outRef__, item) ; 
	}
	if (Orc$String$equals(item->type, ITEM) ) {
		SuiView$DockItem *  parent = item->parent;
		if (parent) {
			if (Orc$String$equals(parent->type, TAB) ) {
				return urgc_set_var_for_return_class((void ** )__outRef__, parent) ; 
			}
			if (Orc$String$equals(parent->type, SPLITTER) ) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
				URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tab = SuiView$mkDockItemTab((tab = NULL,&tab), NULL, Orc$String$addString(Orc$str(&tmpReturn_1, "tab-of-") , item->id) ) ;
				tab->width = item->width;
				tab->weight = item->weight;
				parent->insertBefore(parent, tab, item) ;
				tab->appendChild(tab, item) ;
				return urgc_set_var_for_return_class((void ** )__outRef__, tab) ; 
			}
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


void  SuiView$DockLayout$clearAllEmptyTab(SuiView$DockLayout *  self, SuiView$DockItem *  item){
	for (int  i = item->children->size(item->children)  - 1; i >= 0; i--) {
		SuiView$DockItem *  kid = (SuiView$DockItem * )item->children->get(item->children, i) ;
		if (Orc$String$equals(kid->type, SPLITTER) ) {
			self->clearAllEmptyTab(self, kid) ;
			if (kid->children->size(kid->children)  == 0) {
				kid->removeSelf(kid) ;
			}
			else if (kid->children->size(kid->children)  == 1) {
				if (kid->parent) {
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  solo = (solo=NULL,urgc_init_var_class((void**)&solo, (SuiView$DockItem* )kid->children->get(kid->children, 0) ));
					if (solo) {
						kid->parent->insertBefore(kid->parent, solo, kid) ;
						kid->removeSelf(kid) ;
					}
				}
			}
		}
		else if (kid->isEmptyTab(kid) ) {
			kid->removeSelf(kid) ;
		}
		if (Orc$String$equals(kid->type, TAB) ) {
			kid->setTabActiveIndex(kid, kid->tabActiveIndex) ;
		}
	}
}


void  SuiView$DockLayout$eachThenWrapTab_forNakeDockItemInSplitter(SuiView$DockLayout *  self, SuiView$DockItem*  item){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(item);

	for (int  i = item->children->size(item->children)  - 1; i >= 0; i--) {
		SuiView$DockItem *  kid = (SuiView$DockItem * )item->children->get(item->children, i) ;
		if (Orc$String$equals(kid->type, SPLITTER) ) {
			self->eachThenWrapTab_forNakeDockItemInSplitter(self, kid) ;
		}
		else if (Orc$String$equals(kid->type, ITEM) ) {
			URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_1 = NULL;
			self->upto_getOrWrap_DockItemTab(&tmpReturn_1, self, kid) ;
		}
	}
}


SuiCore$ViewBase *  SuiView$DockLayout$hitTestChildren(SuiView$DockLayout *  self, float  x, float  y){
	return SuiCore$hitTestChildren_withZ(self, x, y) ; 
}



static void  __finiBlock___Block_281_15(SuiView$__Block_281_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_281_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_427_39(SuiView$__Block_427_39 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_427_39, self) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_427_39, parentItem) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_432_39(SuiView$__Block_432_39 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_439_30(SuiView$__Block_439_30 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_507_56(SuiView$__Block_507_56 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_507_56, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_513_39(SuiView$__Block_513_39 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_513_39, kid) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_285_30(SuiView$__Closure_285_30 *  self, SuiView$Drag *  d){
	if (d->isDragging || d->isDragEnd) {
		printf("\n\n\t drag tab\n") ;
		((SuiCore$ViewBase * )self->__var___Block_281_15->self)->invalidDraw(self->__var___Block_281_15->self) ;
	}
	if (d->isDragEnd) {
		self->__var___Block_281_15->self->doDrop(self->__var___Block_281_15->self) ;
	}
}

static void  __fini___Closure_285_30(SuiView$__Closure_285_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_285_30, __var___Block_281_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_285_30*  __make___Closure_285_30(SuiView$__Closure_285_30 **  __outRef__, SuiView$__Block_281_15 *  __var___Block_281_15){
	URGC_VAR_CLEANUP SuiView$__Closure_285_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_285_30) , __fini___Closure_285_30) ));
	self->invoke = __fn___Closure_285_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_285_30, __var___Block_281_15) , __var___Block_281_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_447_40(SuiView$__Closure_447_40 *  self, SuiView$Drag *  d){
	self->__var___Block_427_39->self->onDragSplitter(self->__var___Block_427_39->self, d, self->__var___Block_427_39->parentItem, self->__var___Block_432_39->kid, self->__var___Block_439_30->nextKid) ;
}

static void  __fini___Closure_447_40(SuiView$__Closure_447_40 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_447_40, __var___Block_427_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_447_40, __var___Block_432_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_447_40, __var___Block_439_30) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_447_40*  __make___Closure_447_40(SuiView$__Closure_447_40 **  __outRef__, SuiView$__Block_427_39 *  __var___Block_427_39, SuiView$__Block_432_39 *  __var___Block_432_39, SuiView$__Block_439_30 *  __var___Block_439_30){
	URGC_VAR_CLEANUP SuiView$__Closure_447_40*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_447_40) , __fini___Closure_447_40) ));
	self->invoke = __fn___Closure_447_40;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_447_40, __var___Block_427_39) , __var___Block_427_39) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_447_40, __var___Block_432_39) , __var___Block_432_39) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_447_40, __var___Block_439_30) , __var___Block_439_30) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_518_38(SuiView$__Closure_518_38 *  self, SuiCore$Event *  e){
	self->__var___Block_507_56->self->_onEvent_tabItemHead(self->__var___Block_507_56->self, e, self->__var___Block_513_39->kid) ;
}

static void  __fini___Closure_518_38(SuiView$__Closure_518_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_518_38, __var___Block_507_56) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_518_38, __var___Block_513_39) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_518_38*  __make___Closure_518_38(SuiView$__Closure_518_38 **  __outRef__, SuiView$__Block_507_56 *  __var___Block_507_56, SuiView$__Block_513_39 *  __var___Block_513_39){
	URGC_VAR_CLEANUP SuiView$__Closure_518_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_518_38) , __fini___Closure_518_38) ));
	self->invoke = __fn___Closure_518_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_518_38, __var___Block_507_56) , __var___Block_507_56) ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_518_38, __var___Block_513_39) , __var___Block_513_39) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}


//vtable instance
Vtable_SuiView$DockSplitterView _vtable_SuiView$DockSplitterView;

// init meta

void SuiView$DockSplitterView_initMeta(Vtable_SuiView$DockSplitterView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiView$DockSplitterView, drag), true, false, 1);
	orc_metaField_primitive(&pNext, "hoverBg", OrcMetaType_int, offsetof(SuiView$DockSplitterView, hoverBg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "normalBg", OrcMetaType_int, offsetof(SuiView$DockSplitterView, normalBg), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiView$DockSplitterView* Vtable_SuiView$DockSplitterView_init(Vtable_SuiView$DockSplitterView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$DockSplitterView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$DockSplitterView_new;
    ((Vtable_Object*)pvt)->className = "SuiView$DockSplitterView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$DockSplitterView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$DockSplitterView_fini(SuiView$DockSplitterView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiView$DockSplitterView_init_fields(SuiView$DockSplitterView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$DockSplitterView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$DockSplitterView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	((SuiView$DockSplitterView*)self)->hoverBg = 0xff007aff;
	((SuiView$DockSplitterView*)self)->normalBg = 0xffcdcdcf;
    }
	((Object*)self)->ctor = (void*)SuiView$DockSplitterView$ctor;
	((SuiCore$Node*)self)->react = (void*)SuiView$DockSplitterView$react;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$DockSplitterView$onEvent;
	((SuiCore$ViewBase*)self)->onHoverChanged = (void*)SuiView$DockSplitterView$onHoverChanged;
}

// init function

void SuiView$DockSplitterView_init(SuiView$DockSplitterView *self, void *pOwner){
    Vtable_SuiView$DockSplitterView_init(&_vtable_SuiView$DockSplitterView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$DockSplitterView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$DockSplitterView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$DockSplitterView * SuiView$DockSplitterView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$DockSplitterView *self = calloc(1, sizeof(SuiView$DockSplitterView));
	
    SuiView$DockSplitterView_init(self, pOwner);
    return self;
}


// class members
void  SuiView$DockSplitterView$ctor(SuiView$DockSplitterView *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_1, "pointer") ) ;
	((SuiCore$ViewBase * )self)->hitTestPadding = SuiCore$mkInset(3, 3, 3, 3) ;
}


void  SuiView$DockSplitterView$react(SuiView$DockSplitterView *  self){
	((SuiCore$View * )self)->backgroundColor = ((SuiCore$ViewBase * )self)->hover ? self->hoverBg : self->normalBg;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


void  SuiView$DockSplitterView$onEvent(SuiView$DockSplitterView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		if (self->drag) {
			self->drag->onMouseDown(self->drag, (SuiCore$MouseEvent * )e) ;
		}
	}
}


void  SuiView$DockSplitterView$onHoverChanged(SuiView$DockSplitterView *  self){
	((SuiCore$Node * )self)->invalidReact(self) ;
}



SuiView$DockLayout*  SuiView$dockLayout(SuiView$DockLayout **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$DockLayout* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$DockLayout_init(NULL)) ) ; 
}

SuiView$DockSplitterView*  SuiView$dockSplitterView(SuiView$DockSplitterView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$DockSplitterView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$DockSplitterView_init(NULL)) ) ; 
}



