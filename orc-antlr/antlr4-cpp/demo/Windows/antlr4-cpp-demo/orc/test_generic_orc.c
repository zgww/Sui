
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


//vtable instance
Vtable_SuiCore$User _vtable_SuiCore$User;

// init meta

void SuiCore$User_initMeta(Vtable_SuiCore$User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "say", offsetof(SuiCore$User, say));
}


// vtable init


Vtable_SuiCore$User* Vtable_SuiCore$User_init(Vtable_SuiCore$User* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$User;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$User_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$User";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$User_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$User_fini(SuiCore$User *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$User_init_fields(SuiCore$User *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$User_fini;
	//fields
    {
	
    }
	((SuiCore$User*)self)->say = (void*)SuiCore$User$say;
}

// init function

void SuiCore$User_init(SuiCore$User *self, void *pOwner){
    Vtable_SuiCore$User_init(&_vtable_SuiCore$User);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$User;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$User_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$User * SuiCore$User_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$User *self = ORC_CALLOC(1, sizeof(SuiCore$User));
	
    SuiCore$User_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$User$say(SuiCore$User *  self){
	
}



void  SuiCore$main(){
	SuiCore$User *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$User*  tmpReturn_1 = NULL;
	(tmpThis_1 = (SuiCore$User*)SuiCore$mkObj((Object ** )&tmpReturn_1, Vtable_SuiCore$User_init(NULL)) )->say(tmpThis_1) ;
}



