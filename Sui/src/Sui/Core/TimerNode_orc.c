
#include "TimerNode_orc.h" 

#include <stdio.h>
#include "./Node_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$TimerNode _vtable_SuiCore$TimerNode;

// init meta

void SuiCore$TimerNode_initMeta(Vtable_SuiCore$TimerNode *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiCore$TimerNode* Vtable_SuiCore$TimerNode_init(Vtable_SuiCore$TimerNode* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$TimerNode;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Node_init(&_vtable_SuiCore$Node);

	// init by super vtable init function
    Vtable_SuiCore$Node_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Node;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$TimerNode_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$TimerNode";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$TimerNode_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$TimerNode_fini(SuiCore$TimerNode *self){
	//super fini
    SuiCore$Node_fini((SuiCore$Node *)self);

    //字段释放
	

}

// init fields function


void SuiCore$TimerNode_init_fields(SuiCore$TimerNode *self){
	//super class
    SuiCore$Node_init_fields((SuiCore$Node*)self);

    ((Object*)self)->fini = (void*)SuiCore$TimerNode_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiCore$TimerNode_init(SuiCore$TimerNode *self, void *pOwner){
    Vtable_SuiCore$TimerNode_init(&_vtable_SuiCore$TimerNode);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$TimerNode;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$TimerNode_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$TimerNode * SuiCore$TimerNode_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$TimerNode *self = calloc(1, sizeof(SuiCore$TimerNode));
	
    SuiCore$TimerNode_init(self, pOwner);
    return self;
}


// class members



