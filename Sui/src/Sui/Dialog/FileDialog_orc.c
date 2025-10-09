
#include "FileDialog_orc.h" 

#include <stdio.h>
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Path_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDialog$FileDialog _vtable_SuiDialog$FileDialog;

// init meta

void SuiDialog$FileDialog_initMeta(Vtable_SuiDialog$FileDialog *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDialog$FileDialog* Vtable_SuiDialog$FileDialog_init(Vtable_SuiDialog$FileDialog* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDialog$FileDialog;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDialog$FileDialog_new;
    ((Vtable_Object*)pvt)->className = "SuiDialog$FileDialog";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDialog$FileDialog_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDialog$FileDialog_fini(SuiDialog$FileDialog *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDialog$FileDialog_init_fields(SuiDialog$FileDialog *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDialog$FileDialog_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDialog$FileDialog_init(SuiDialog$FileDialog *self, void *pOwner){
    Vtable_SuiDialog$FileDialog_init(&_vtable_SuiDialog$FileDialog);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDialog$FileDialog;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDialog$FileDialog_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDialog$FileDialog * SuiDialog$FileDialog_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDialog$FileDialog *self = calloc(1, sizeof(SuiDialog$FileDialog));
	
    SuiDialog$FileDialog_init(self, pOwner);
    return self;
}


// class members

Orc$List*  SuiDialog$FileDialog_getOpenFileName(Orc$List **  __outRef__, const char *  dir, const char *  title){
	URGC_VAR_CLEANUP_CLASS Orc$String*  cwd = Orc$Path_getcwd((cwd = NULL,&cwd)) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  ret = SuiDialog$fileDialog_getOpenFileName((ret = NULL,&ret), dir, title) ;
	Orc$Path_setcwd(cwd->str) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  SuiDialog$FileDialog_getFirstOpenFileName(Orc$String **  __outRef__, const char *  dir, const char *  title){
	URGC_VAR_CLEANUP_CLASS Orc$List*  list = SuiDialog$FileDialog_getOpenFileName((list = NULL,&list), dir, title) ;
	if (list->size(list)  > 0) {
		return urgc_set_var_for_return_class((void ** )__outRef__, (Orc$String* )list->get(list, 0) ) ; 
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}

void  SuiDialog$test(){
	URGC_VAR_CLEANUP_CLASS Orc$String*  saveFileName = SuiDialog$fileDialog_getSaveFileName((saveFileName = NULL,&saveFileName), ".", "title") ;
	printf("save fileName:%s\n", saveFileName->str) ;
}



