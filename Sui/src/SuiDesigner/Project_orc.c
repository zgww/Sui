
#include "Project_orc.h" 

#include <stdio.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Path_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/RowWrap_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "./FileItem_orc.h"
#include "./UiAction_orc.h"
#include "./EditCtx_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./EventFileItemChanged_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$Project _vtable_SuiDesigner$Project;

// init meta

void SuiDesigner$Project_initMeta(Vtable_SuiDesigner$Project *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "projectDir", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$Project, projectDir), true, false, 1);
	orc_metaField_class(&pNext, "dirFileItem", ((Vtable_Object*)Vtable_SuiDesigner$FileItem_init(0)), offsetof(SuiDesigner$Project, dirFileItem), true, false, 1);

	orc_metaField_method(&pNext, "init", offsetof(SuiDesigner$Project, init));
}


// vtable init


Vtable_SuiDesigner$Project* Vtable_SuiDesigner$Project_init(Vtable_SuiDesigner$Project* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$Project;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$Project_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$Project";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$Project_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$Project_fini(SuiDesigner$Project *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$Project_init_fields(SuiDesigner$Project *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$Project_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$Project*)self)->projectDir, Orc$str(&tmpReturn_1, "") );
	urgc_set_field_class(self, (void**)&((SuiDesigner$Project*)self)->dirFileItem, NULL);
    }
	((SuiDesigner$Project*)self)->init = (void*)SuiDesigner$Project$init;
}

// init function

void SuiDesigner$Project_init(SuiDesigner$Project *self, void *pOwner){
    Vtable_SuiDesigner$Project_init(&_vtable_SuiDesigner$Project);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$Project;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$Project_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$Project * SuiDesigner$Project_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$Project *self = calloc(1, sizeof(SuiDesigner$Project));
	
    SuiDesigner$Project_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$Project$init(SuiDesigner$Project *  self, const char *  projectDir){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Project, projectDir) , Orc$str(&tmpReturn_1, projectDir) ) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Project, dirFileItem) , SuiDesigner$FileItem_loadDirectoryTree(&tmpReturn_2, projectDir) ) ;
	printf("\n\n打印项目根文件目录树: %s\n", projectDir) ;
	self->dirFileItem->printTree(self->dirFileItem, 0) ;
}



SuiDesigner$Project*  SuiDesigner$Project_ins(SuiDesigner$Project **  __outRef__){
	static URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  ins = NULL;
	if (ins == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&ins, SuiDesigner$Project_new(&tmpNewOwner_1) ) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ins) ; 
}



