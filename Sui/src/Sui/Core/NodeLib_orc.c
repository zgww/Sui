
#include "NodeLib_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Map_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$NodeRegisterInfo _vtable_SuiCore$NodeRegisterInfo;

// init meta

void SuiCore$NodeRegisterInfo_initMeta(Vtable_SuiCore$NodeRegisterInfo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "className", OrcMetaType_char, offsetof(SuiCore$NodeRegisterInfo, className), 0, 0, 1, 1);//char

	orc_metaField_method(&pNext, "init", offsetof(SuiCore$NodeRegisterInfo, init));
	orc_metaField_method(&pNext, "mk", offsetof(SuiCore$NodeRegisterInfo, mk));
}


// vtable init


Vtable_SuiCore$NodeRegisterInfo* Vtable_SuiCore$NodeRegisterInfo_init(Vtable_SuiCore$NodeRegisterInfo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$NodeRegisterInfo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$NodeRegisterInfo_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$NodeRegisterInfo";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$NodeRegisterInfo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$NodeRegisterInfo_fini(SuiCore$NodeRegisterInfo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$NodeRegisterInfo_init_fields(SuiCore$NodeRegisterInfo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$NodeRegisterInfo_fini;
	//fields
    {
	((SuiCore$NodeRegisterInfo*)self)->className = "";
	((SuiCore$NodeRegisterInfo*)self)->vtable = NULL;
    }
	((SuiCore$NodeRegisterInfo*)self)->init = (void*)SuiCore$NodeRegisterInfo$init;
	((SuiCore$NodeRegisterInfo*)self)->mk = (void*)SuiCore$NodeRegisterInfo$mk;
}

// init function

void SuiCore$NodeRegisterInfo_init(SuiCore$NodeRegisterInfo *self, void *pOwner){
    Vtable_SuiCore$NodeRegisterInfo_init(&_vtable_SuiCore$NodeRegisterInfo);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$NodeRegisterInfo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$NodeRegisterInfo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$NodeRegisterInfo * SuiCore$NodeRegisterInfo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$NodeRegisterInfo *self = calloc(1, sizeof(SuiCore$NodeRegisterInfo));
	
    SuiCore$NodeRegisterInfo_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$NodeRegisterInfo$init(SuiCore$NodeRegisterInfo *  self, Vtable_Object *  vt){
	self->className = vt->className;
	self->vtable = vt;
}


Object*  SuiCore$NodeRegisterInfo$mk(Object **  __outRef__, SuiCore$NodeRegisterInfo *  self){
	URGC_VAR_CLEANUP_CLASS Object*  obj = NULL;
	self->vtable->make(&obj) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
}




//vtable instance
Vtable_SuiCore$NodeLib _vtable_SuiCore$NodeLib;

// init meta

void SuiCore$NodeLib_initMeta(Vtable_SuiCore$NodeLib *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "map", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiCore$NodeLib, map), true, false, 1);
	orc_metaField_class(&pNext, "list", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$NodeLib, list), true, false, 1);

	orc_metaField_method(&pNext, "findByClassName", offsetof(SuiCore$NodeLib, findByClassName));
	orc_metaField_method(&pNext, "registerClass", offsetof(SuiCore$NodeLib, registerClass));
}


// vtable init


Vtable_SuiCore$NodeLib* Vtable_SuiCore$NodeLib_init(Vtable_SuiCore$NodeLib* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$NodeLib;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$NodeLib_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$NodeLib";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$NodeLib_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$NodeLib_fini(SuiCore$NodeLib *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$NodeLib*)self)->map);
	urgc_fini_field_class(self, (void**)&((SuiCore$NodeLib*)self)->list);

}

// init fields function


void SuiCore$NodeLib_init_fields(SuiCore$NodeLib *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$NodeLib_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$NodeLib*)self)->map, Orc$Map_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$NodeLib*)self)->list, Orc$List_new(&tmpNewOwner_2) );
    }
	((SuiCore$NodeLib*)self)->findByClassName = (void*)SuiCore$NodeLib$findByClassName;
	((SuiCore$NodeLib*)self)->registerClass = (void*)SuiCore$NodeLib$registerClass;
}

// init function

void SuiCore$NodeLib_init(SuiCore$NodeLib *self, void *pOwner){
    Vtable_SuiCore$NodeLib_init(&_vtable_SuiCore$NodeLib);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$NodeLib;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$NodeLib_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$NodeLib * SuiCore$NodeLib_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$NodeLib *self = calloc(1, sizeof(SuiCore$NodeLib));
	
    SuiCore$NodeLib_init(self, pOwner);
    return self;
}


// class members
SuiCore$NodeRegisterInfo*  SuiCore$NodeLib$findByClassName(SuiCore$NodeRegisterInfo **  __outRef__, SuiCore$NodeLib *  self, const char *  className){
	URGC_VAR_CLEANUP_CLASS SuiCore$NodeRegisterInfo*  info = (info=NULL,urgc_init_var_class((void**)&info, (SuiCore$NodeRegisterInfo* )self->map->get(self->map, className) ));
	return urgc_set_var_for_return_class((void ** )__outRef__, info) ; 
}


void  SuiCore$NodeLib$registerClass(SuiCore$NodeLib *  self, Vtable_Object *  vt){
	URGC_VAR_CLEANUP_CLASS SuiCore$NodeRegisterInfo*  info = (info=NULL,urgc_init_var_class((void**)&info, SuiCore$NodeRegisterInfo_new(&info) ));
	info->init(info, vt) ;
	if (self->map->has(self->map, vt->className) ) {
		printf("重复注册节点类:%s\n", vt->className) ;
		return ; 
	}
	self->map->put(self->map, vt->className, info) ;
	self->list->add(self->list, info) ;
}



SuiCore$NodeLib *  SuiCore$NodeLib_use(){
	static URGC_VAR_CLEANUP_CLASS SuiCore$NodeLib*  lib = NULL;
	if (!lib) {
		URGC_VAR_CLEANUP_CLASS SuiCore$NodeLib*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&lib, SuiCore$NodeLib_new(&tmpNewOwner_1) ) ;
	}
	return lib; 
}



