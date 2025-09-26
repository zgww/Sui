
#include "LayoutCell_orc.h" 

#include <stdio.h>
#include "../../Orc/List_orc.h"
#include "./Node_orc.h"
#include "./ViewBase_orc.h"
#include "./Frame_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$LayoutCell _vtable_SuiCore$LayoutCell;

// init meta

void SuiCore$LayoutCell_initMeta(Vtable_SuiCore$LayoutCell *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "invalidLayout", offsetof(SuiCore$LayoutCell, invalidLayout));
}


// vtable init


Vtable_SuiCore$LayoutCell* Vtable_SuiCore$LayoutCell_init(Vtable_SuiCore$LayoutCell* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$LayoutCell;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Node_init(&_vtable_SuiCore$Node);

	// init by super vtable init function
    Vtable_SuiCore$Node_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Node;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$LayoutCell_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$LayoutCell";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$LayoutCell_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$LayoutCell_fini(SuiCore$LayoutCell *self){
	//super fini
    SuiCore$Node_fini((SuiCore$Node *)self);

    //字段释放


}

// init fields function


void SuiCore$LayoutCell_init_fields(SuiCore$LayoutCell *self){
	//super class
    SuiCore$Node_init_fields((SuiCore$Node*)self);

    ((Object*)self)->fini = (void*)SuiCore$LayoutCell_fini;
	//fields
    {
	
    }
	((SuiCore$LayoutCell*)self)->invalidLayout = (void*)SuiCore$LayoutCell$invalidLayout;
	((SuiCore$Node*)self)->onMounted = (void*)SuiCore$LayoutCell$onMounted;
	((SuiCore$Node*)self)->onUnmounting = (void*)SuiCore$LayoutCell$onUnmounting;
}

// init function

void SuiCore$LayoutCell_init(SuiCore$LayoutCell *self, void *pOwner){
    Vtable_SuiCore$LayoutCell_init(&_vtable_SuiCore$LayoutCell);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$LayoutCell;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$LayoutCell_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$LayoutCell * SuiCore$LayoutCell_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$LayoutCell *self = calloc(1, sizeof(SuiCore$LayoutCell));
	
    SuiCore$LayoutCell_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$LayoutCell$invalidLayout(SuiCore$LayoutCell *  self){
	if (Orc_instanceof((Object*)((SuiCore$Node * )self)->parent, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  parentView = (SuiCore$ViewBase * )((SuiCore$Node * )self)->parent;
		parentView->invalidLayout(parentView) ;
	}
}


void  SuiCore$LayoutCell$onMounted(SuiCore$LayoutCell *  self){
	if (Orc_instanceof((Object*)((SuiCore$Node * )self)->parent, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  parentView = (SuiCore$ViewBase * )((SuiCore$Node * )self)->parent;
		Orc$List *  layoutCells = parentView->gocLayoutCells(parentView) ;
		layoutCells->add(layoutCells, self) ;
		parentView->invalidLayout(parentView) ;
	}
}


void  SuiCore$LayoutCell$onUnmounting(SuiCore$LayoutCell *  self){
	if (Orc_instanceof((Object*)((SuiCore$Node * )self)->parent, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  parentView = (SuiCore$ViewBase * )((SuiCore$Node * )self)->parent;
		Orc$List *  cells = parentView->gocLayoutCells(parentView) ;
		cells->remove(cells, self) ;
		parentView->invalidLayout(parentView) ;
	}
}





