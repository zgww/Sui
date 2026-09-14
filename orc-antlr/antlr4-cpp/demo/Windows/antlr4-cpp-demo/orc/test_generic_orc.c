
#include "test_generic_orc.h" 
#include <chrono>



// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$Vtable_Object _vtable_SuiCore$Vtable_Object;

// init meta

void SuiCore$Vtable_Object_initMeta(Vtable_SuiCore$Vtable_Object *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "create", offsetof(SuiCore$Vtable_Object, create));
}


// vtable init


Vtable_SuiCore$Vtable_Object* Vtable_SuiCore$Vtable_Object_init(Vtable_SuiCore$Vtable_Object* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Vtable_Object;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Vtable_Object_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Vtable_Object";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Vtable_Object_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$Vtable_Object_fini(SuiCore$Vtable_Object *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$Vtable_Object_init_fields(SuiCore$Vtable_Object *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Vtable_Object_fini;
	//fields
    {
	
    }
	((SuiCore$Vtable_Object*)self)->create = (void*)SuiCore$Vtable_Object$create;
}

// init function

void SuiCore$Vtable_Object_init(SuiCore$Vtable_Object *self, void *pOwner){
    Vtable_SuiCore$Vtable_Object_init(&_vtable_SuiCore$Vtable_Object);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Vtable_Object;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Vtable_Object_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Vtable_Object * SuiCore$Vtable_Object_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Vtable_Object *self = ORC_CALLOC(1, sizeof(SuiCore$Vtable_Object));
	
    SuiCore$Vtable_Object_init(self, pOwner);
    return self;
}


// class members
Object*  SuiCore$Vtable_Object$create(Object **  __outRef__, SuiCore$Vtable_Object *  self){
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}



Object*  SuiCore$mkObj(Object **  __outRef__, SuiCore$Vtable_Object *  vt){
	URGC_VAR_CLEANUP Object*  obj = vt->create((obj = NULL,&obj), vt) ;
	return obj; 
}



