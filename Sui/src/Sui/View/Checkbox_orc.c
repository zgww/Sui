
#include "Checkbox_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../Orc/String_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../View/ImageView_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/MouseEvent_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiView$Checkbox _vtable_SuiView$Checkbox;

// init meta

void SuiView$Checkbox_initMeta(Vtable_SuiView$Checkbox *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "onSrc", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$Checkbox, onSrc), true, false, 1);
	orc_metaField_class(&pNext, "offSrc", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$Checkbox, offSrc), true, false, 1);
	orc_metaField_primitive(&pNext, "checked", OrcMetaType_bool, offsetof(SuiView$Checkbox, checked), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "setChecked", offsetof(SuiView$Checkbox, setChecked));
}


// vtable init


Vtable_SuiView$Checkbox* Vtable_SuiView$Checkbox_init(Vtable_SuiView$Checkbox* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Checkbox;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiView$ImageView_init(&_vtable_SuiView$ImageView);

	// init by super vtable init function
    Vtable_SuiView$ImageView_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiView$ImageView;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Checkbox_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Checkbox";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Checkbox_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Checkbox_fini(SuiView$Checkbox *self){
	//super fini
    SuiView$ImageView_fini((SuiView$ImageView *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$Checkbox*)self)->onSrc);
	urgc_fini_field_class(self, (void**)&((SuiView$Checkbox*)self)->offSrc);

}

// init fields function


void SuiView$Checkbox_init_fields(SuiView$Checkbox *self){
	//super class
    SuiView$ImageView_init_fields((SuiView$ImageView*)self);

    ((Object*)self)->fini = (void*)SuiView$Checkbox_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$Checkbox*)self)->onSrc, Orc$str(&tmpReturn_1, "./checkbox-checked.png") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$Checkbox*)self)->offSrc, Orc$str(&tmpReturn_2, "./checkbox-unchecked.png") );
	((SuiView$Checkbox*)self)->checked = false;
    }
	((Object*)self)->ctor = (void*)SuiView$Checkbox$ctor;
	((SuiView$Checkbox*)self)->setChecked = (void*)SuiView$Checkbox$setChecked;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$Checkbox$onEvent;
}

// init function

void SuiView$Checkbox_init(SuiView$Checkbox *self, void *pOwner){
    Vtable_SuiView$Checkbox_init(&_vtable_SuiView$Checkbox);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Checkbox;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Checkbox_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Checkbox * SuiView$Checkbox_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Checkbox *self = calloc(1, sizeof(SuiView$Checkbox));
	
    SuiView$Checkbox_init(self, pOwner);
    return self;
}


// class members
void  SuiView$Checkbox$ctor(SuiView$Checkbox *  self){
	self->setChecked(self, false) ;
}


void  SuiView$Checkbox$setChecked(SuiView$Checkbox *  self, bool  v){
	self->checked = v;
	if (self->checked) {
		if (self->onSrc != NULL) {
			((SuiView$ImageView * )self)->setSrc(self, self->onSrc) ;
		}
	}
	else {
		if (self->offSrc != NULL) {
			((SuiView$ImageView * )self)->setSrc(self, self->offSrc) ;
		}
	}
	printf("setChecked:%d\n", self->checked) ;
	((SuiCore$ViewBase * )self)->invalidLayout(self) ;
}


void  SuiView$Checkbox$onEvent(SuiView$Checkbox *  self, SuiCore$Event *  ev){
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$ViewEvent_init(NULL))) {
		SuiCore$ViewEvent *  ve = (SuiCore$ViewEvent * )ev;
		printf("Button.onEvent: %s isCapture:%d\n", Object_getClassName(ev) , ve->isCapture) ;
		if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
			SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
			if (me->isClick(me)  && !((SuiCore$ViewEvent * )me)->isCapture) {
				self->setChecked(self, !self->checked) ;
				((SuiCore$Event * )me)->stopPropagation(me) ;
			}
		}
	}
}



SuiView$Checkbox*  SuiView$checkbox(SuiView$Checkbox **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$Checkbox* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$Checkbox_init(NULL)) ) ; 
}



