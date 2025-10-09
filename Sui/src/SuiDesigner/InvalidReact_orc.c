
#include "InvalidReact_orc.h" 

#include "../Orc/Orc.h"
#include <stdio.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "../Sui/View/DockLayout_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "./ChessBgViewCallback_orc.h"
#include "./Theme_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_32_18 SuiDesigner$__Block_32_18;

typedef struct tagSuiDesigner$__Closure_37_30 SuiDesigner$__Closure_37_30;



struct tagSuiDesigner$__Block_32_18 {
	SuiDesigner$InvalidReact*  self ;
};





struct tagSuiDesigner$__Closure_37_30 {
	bool  (*invoke)(SuiDesigner$__Closure_37_30 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_32_18*  __var___Block_32_18 ;
};





// static function declaration
static void  __finiBlock___Block_32_18(SuiDesigner$__Block_32_18 *  self);
static bool  __fn___Closure_37_30(SuiDesigner$__Closure_37_30 *  self);
static void  __fini___Closure_37_30(SuiDesigner$__Closure_37_30 *  self);
static SuiDesigner$__Closure_37_30*  __make___Closure_37_30(SuiDesigner$__Closure_37_30 **  __outRef__, SuiDesigner$__Block_32_18 *  __var___Block_32_18);



//vtable instance
Vtable_SuiDesigner$InvalidReact _vtable_SuiDesigner$InvalidReact;

// init meta

void SuiDesigner$InvalidReact_initMeta(Vtable_SuiDesigner$InvalidReact *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "_reactDirty", OrcMetaType_bool, offsetof(SuiDesigner$InvalidReact, _reactDirty), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "target", ((Vtable_Object*)Vtable_Object_init(0)), offsetof(SuiDesigner$InvalidReact, target), true, false, 1);

	orc_metaField_method(&pNext, "invalid", offsetof(SuiDesigner$InvalidReact, invalid));
}


// vtable init


Vtable_SuiDesigner$InvalidReact* Vtable_SuiDesigner$InvalidReact_init(Vtable_SuiDesigner$InvalidReact* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InvalidReact;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InvalidReact_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InvalidReact";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InvalidReact_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InvalidReact_fini(SuiDesigner$InvalidReact *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$InvalidReact*)self)->target);

}

// init fields function


void SuiDesigner$InvalidReact_init_fields(SuiDesigner$InvalidReact *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InvalidReact_fini;
	//fields
    {
	((SuiDesigner$InvalidReact*)self)->_reactDirty = false;
	urgc_set_field(self, (void**)&((SuiDesigner$InvalidReact*)self)->react, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$InvalidReact*)self)->target, NULL);
    }
	((SuiDesigner$InvalidReact*)self)->invalid = (void*)SuiDesigner$InvalidReact$invalid;
}

// init function

void SuiDesigner$InvalidReact_init(SuiDesigner$InvalidReact *self, void *pOwner){
    Vtable_SuiDesigner$InvalidReact_init(&_vtable_SuiDesigner$InvalidReact);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InvalidReact;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InvalidReact_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InvalidReact * SuiDesigner$InvalidReact_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InvalidReact *self = calloc(1, sizeof(SuiDesigner$InvalidReact));
	
    SuiDesigner$InvalidReact_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$InvalidReact$invalid(SuiDesigner$InvalidReact *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_32_18*  __var___Block_32_18 = (__var___Block_32_18=NULL,urgc_init_var((void**)&__var___Block_32_18, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_32_18) , __finiBlock___Block_32_18) ));
	urgc_set_field_class(__var___Block_32_18, (void * )offsetof(SuiDesigner$__Block_32_18, self) , self) ;
	if (self->_reactDirty) {
		return ; 
	}
	self->_reactDirty = true;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_37_30*  tmpReturn_1 = NULL;
	SuiCore$requestAnimationFrame(__make___Closure_37_30(&tmpReturn_1, __var___Block_32_18) ) ;
}



static void  __finiBlock___Block_32_18(SuiDesigner$__Block_32_18 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_32_18, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static bool  __fn___Closure_37_30(SuiDesigner$__Closure_37_30 *  self){
	self->__var___Block_32_18->self->_reactDirty = false;
	if (self->__var___Block_32_18->self->react) {
		(*(self->__var___Block_32_18->self->react))((void * )(self->__var___Block_32_18->self->react)) ;
	}
	else if (self->__var___Block_32_18->self->target) {
		void  (**pReact)(Object *  obj);
		OrcMetaField *  mf = orc_getMetaFieldByObject(self->__var___Block_32_18->self->target, "react") ;
		if (mf) {
			pReact = OrcMetaField_getPtr(mf, self->__var___Block_32_18->self->target) ;
			if (*pReact) {
				(*pReact)(self->__var___Block_32_18->self->target) ;
			}
		}
	}
	return true; 
}

static void  __fini___Closure_37_30(SuiDesigner$__Closure_37_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_37_30, __var___Block_32_18) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_37_30*  __make___Closure_37_30(SuiDesigner$__Closure_37_30 **  __outRef__, SuiDesigner$__Block_32_18 *  __var___Block_32_18){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_37_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_37_30) , __fini___Closure_37_30) ));
	self->invoke = __fn___Closure_37_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_37_30, __var___Block_32_18) , __var___Block_32_18) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiDesigner$InvalidReact*  SuiDesigner$mkInvalidReact(SuiDesigner$InvalidReact **  __outRef__, Object*  target){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(target);

	URGC_VAR_CLEANUP_CLASS SuiDesigner$InvalidReact*  invalidReact = (invalidReact=NULL,urgc_init_var_class((void**)&invalidReact, SuiDesigner$InvalidReact_new(&invalidReact) ));
	urgc_set_field_class(invalidReact, (void * )offsetof(SuiDesigner$InvalidReact, target) , target) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, invalidReact) ; 
}



