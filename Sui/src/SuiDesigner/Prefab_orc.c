
#include "Prefab_orc.h" 

#include <stdio.h>
#include "../Json/Json_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "./ANode_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$Prefab _vtable_SuiDesigner$Prefab;

// init meta

void SuiDesigner$Prefab_initMeta(Vtable_SuiDesigner$Prefab *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "version", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$Prefab, version), true, false, 1);
	orc_metaField_class(&pNext, "root", ((Vtable_Object*)Vtable_SuiDesigner$ANode_init(0)), offsetof(SuiDesigner$Prefab, root), true, false, 1);
	orc_metaField_class(&pNext, "_path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$Prefab, _path), true, false, 1);

	orc_metaField_method(&pNext, "fromJson", offsetof(SuiDesigner$Prefab, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$Prefab, toJson));
	orc_metaField_method(&pNext, "loadByPathCstr", offsetof(SuiDesigner$Prefab, loadByPathCstr));
	orc_metaField_method(&pNext, "save", offsetof(SuiDesigner$Prefab, save));
	orc_metaField_method(&pNext, "saveTo", offsetof(SuiDesigner$Prefab, saveTo));
}


// vtable init


Vtable_SuiDesigner$Prefab* Vtable_SuiDesigner$Prefab_init(Vtable_SuiDesigner$Prefab* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$Prefab;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$Prefab_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$Prefab";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$Prefab_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$Prefab_fini(SuiDesigner$Prefab *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Prefab*)self)->version);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Prefab*)self)->root);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Prefab*)self)->_path);

}

// init fields function


void SuiDesigner$Prefab_init_fields(SuiDesigner$Prefab *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$Prefab_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$Prefab*)self)->version, Orc$str(&tmpReturn_1, "0.0.3") );
	urgc_set_field_class(self, (void**)&((SuiDesigner$Prefab*)self)->root, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$Prefab*)self)->_path, Orc$str(&tmpReturn_2, "") );
    }
	((SuiDesigner$Prefab*)self)->fromJson = (void*)SuiDesigner$Prefab$fromJson;
	((SuiDesigner$Prefab*)self)->toJson = (void*)SuiDesigner$Prefab$toJson;
	((SuiDesigner$Prefab*)self)->loadByPathCstr = (void*)SuiDesigner$Prefab$loadByPathCstr;
	((SuiDesigner$Prefab*)self)->save = (void*)SuiDesigner$Prefab$save;
	((SuiDesigner$Prefab*)self)->saveTo = (void*)SuiDesigner$Prefab$saveTo;
}

// init function

void SuiDesigner$Prefab_init(SuiDesigner$Prefab *self, void *pOwner){
    Vtable_SuiDesigner$Prefab_init(&_vtable_SuiDesigner$Prefab);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$Prefab;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$Prefab_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$Prefab * SuiDesigner$Prefab_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$Prefab *self = calloc(1, sizeof(SuiDesigner$Prefab));
	
    SuiDesigner$Prefab_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$Prefab$fromJson(SuiDesigner$Prefab *  self, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Prefab, version) , jo->getString(&tmpReturn_1, jo, "version") ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  rootJo = jo->get((rootJo = NULL,&rootJo), jo, "root") ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  root = (root=NULL,urgc_init_var_class((void**)&root, SuiDesigner$ANode_new(&root) ));
	root->fromJson(root, rootJo) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Prefab, root) , root) ;
}


Json$Json*  SuiDesigner$Prefab$toJson(Json$Json **  __outRef__, SuiDesigner$Prefab *  self){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	jo->putString(jo, "version", self->version) ;
	if (self->root) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  rootJo = self->root->toJson((rootJo = NULL,&rootJo), self->root) ;
		jo->put(jo, "root", rootJo) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, jo) ; 
}


SuiDesigner$Prefab*  SuiDesigner$Prefab$loadByPathCstr(SuiDesigner$Prefab **  __outRef__, SuiDesigner$Prefab *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parseByPathCstr((jo = NULL,&jo), path) ;
	self->fromJson(self, jo) ;
	Orc$String$set(self->_path, path) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, self) ; 
}


bool  SuiDesigner$Prefab$save(SuiDesigner$Prefab *  self){
	if (self->_path && Orc$String$notEmpty(self->_path) ) {
		bool  ok = self->saveTo(self, self->_path->str) ;
		return ok; 
	}
	else {
		SuiDialog$Toast_make("保存路径未确定") ;
	}
	return false; 
}


bool  SuiDesigner$Prefab$saveTo(SuiDesigner$Prefab *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = self->toJson((jo = NULL,&jo), self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  text = jo->dump((text = NULL,&text), jo) ;
	bool  ok = Orc$Path_writeText(path, text->str) ;
	return ok; 
}





