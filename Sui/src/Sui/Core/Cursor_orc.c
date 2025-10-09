
#include "Cursor_orc.h" 

#include <stdio.h>
#include "../../Orc/String_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$Cursor _vtable_SuiCore$Cursor;

// init meta

void SuiCore$Cursor_initMeta(Vtable_SuiCore$Cursor *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "isLocked", OrcMetaType_bool, offsetof(SuiCore$Cursor, isLocked), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "cursor", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiCore$Cursor, cursor), true, false, 1);

	orc_metaField_method(&pNext, "init", offsetof(SuiCore$Cursor, init));
	orc_metaField_method(&pNext, "setCursor", offsetof(SuiCore$Cursor, setCursor));
	orc_metaField_method(&pNext, "setIsLocked", offsetof(SuiCore$Cursor, setIsLocked));
	orc_metaField_method(&pNext, "_updateCursor", offsetof(SuiCore$Cursor, _updateCursor));
}


// vtable init


Vtable_SuiCore$Cursor* Vtable_SuiCore$Cursor_init(Vtable_SuiCore$Cursor* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Cursor;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Cursor_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Cursor";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Cursor_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$Cursor_fini(SuiCore$Cursor *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$Cursor*)self)->cursor);

}

// init fields function


void SuiCore$Cursor_init_fields(SuiCore$Cursor *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Cursor_fini;
	//fields
    {
	((SuiCore$Cursor*)self)->isLocked = false;
	urgc_set_field_class(self, (void**)&((SuiCore$Cursor*)self)->cursor, NULL);
    }
	((SuiCore$Cursor*)self)->init = (void*)SuiCore$Cursor$init;
	((SuiCore$Cursor*)self)->setCursor = (void*)SuiCore$Cursor$setCursor;
	((SuiCore$Cursor*)self)->setIsLocked = (void*)SuiCore$Cursor$setIsLocked;
	((SuiCore$Cursor*)self)->_updateCursor = (void*)SuiCore$Cursor$_updateCursor;
}

// init function

void SuiCore$Cursor_init(SuiCore$Cursor *self, void *pOwner){
    Vtable_SuiCore$Cursor_init(&_vtable_SuiCore$Cursor);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Cursor;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Cursor_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Cursor * SuiCore$Cursor_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Cursor *self = calloc(1, sizeof(SuiCore$Cursor));
	
    SuiCore$Cursor_init(self, pOwner);
    return self;
}


// class members
bool  SuiCore$Cursor$setCursor(SuiCore$Cursor *  self, const char *  cursor){
	if (self->isLocked) {
		return false; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$Cursor, cursor) , Orc$str(&tmpReturn_1, cursor) ) ;
	self->_updateCursor(self) ;
	return true; 
}


void  SuiCore$Cursor$setIsLocked(SuiCore$Cursor *  self, bool  v){
	self->isLocked = v;
}



static URGC_VAR_CLEANUP_CLASS SuiCore$Cursor*  cursor = NULL;
SuiCore$Cursor*  SuiCore$Cursor_ins(SuiCore$Cursor **  __outRef__){
	if (cursor == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$Cursor*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&cursor, SuiCore$Cursor_new(&tmpNewOwner_1) ) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, cursor) ; 
}

void  SuiCore$testCursor(){
	URGC_VAR_CLEANUP_CLASS SuiCore$Cursor*  tmp = SuiCore$Cursor_ins((tmp = NULL,&tmp)) ;
	tmp->setCursor(tmp, "sizeall") ;
	printf("test cursor\n") ;
}



