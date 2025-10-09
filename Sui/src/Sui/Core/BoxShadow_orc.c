
#include "BoxShadow_orc.h" 



// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$BoxShadow _vtable_SuiCore$BoxShadow;

// init meta

void SuiCore$BoxShadow_initMeta(Vtable_SuiCore$BoxShadow *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "dx", OrcMetaType_float, offsetof(SuiCore$BoxShadow, dx), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "dy", OrcMetaType_float, offsetof(SuiCore$BoxShadow, dy), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "sigmaX", OrcMetaType_float, offsetof(SuiCore$BoxShadow, sigmaX), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "sigmaY", OrcMetaType_float, offsetof(SuiCore$BoxShadow, sigmaY), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(SuiCore$BoxShadow, color), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiCore$BoxShadow* Vtable_SuiCore$BoxShadow_init(Vtable_SuiCore$BoxShadow* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$BoxShadow;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$BoxShadow_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$BoxShadow";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$BoxShadow_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$BoxShadow_fini(SuiCore$BoxShadow *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$BoxShadow_init_fields(SuiCore$BoxShadow *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$BoxShadow_fini;
	//fields
    {
	((SuiCore$BoxShadow*)self)->dx = 0.f;
	((SuiCore$BoxShadow*)self)->dy = 0.f;
	((SuiCore$BoxShadow*)self)->sigmaX = 0.f;
	((SuiCore$BoxShadow*)self)->sigmaY = 0.f;
	((SuiCore$BoxShadow*)self)->color = 0;
    }
	
}

// init function

void SuiCore$BoxShadow_init(SuiCore$BoxShadow *self, void *pOwner){
    Vtable_SuiCore$BoxShadow_init(&_vtable_SuiCore$BoxShadow);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$BoxShadow;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$BoxShadow_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$BoxShadow * SuiCore$BoxShadow_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$BoxShadow *self = calloc(1, sizeof(SuiCore$BoxShadow));
	
    SuiCore$BoxShadow_init(self, pOwner);
    return self;
}


// class members



