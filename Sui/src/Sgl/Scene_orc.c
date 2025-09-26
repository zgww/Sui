
#include "Scene_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Sgl$SceneGlobal_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$SceneGlobal", sizeof( Sgl$SceneGlobal ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "cameraDirty", OrcMetaType_bool, offsetof(Sgl$SceneGlobal, cameraDirty), 0, 0, 0, 0);//bool
    }
	return meta;
}
Sgl$SceneGlobal Sgl$sceneGlobal;

//vtable instance
Vtable_Sgl$Scene _vtable_Sgl$Scene;

// init meta

void Sgl$Scene_initMeta(Vtable_Sgl$Scene *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_Sgl$Scene* Vtable_Sgl$Scene_init(Vtable_Sgl$Scene* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Scene;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Scene_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Scene";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Scene_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Scene_fini(Sgl$Scene *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放


}

// init fields function


void Sgl$Scene_init_fields(Sgl$Scene *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$Scene_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Sgl$Scene$ctor;
}

// init function

void Sgl$Scene_init(Sgl$Scene *self, void *pOwner){
    Vtable_Sgl$Scene_init(&_vtable_Sgl$Scene);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Scene;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Scene_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Scene * Sgl$Scene_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Scene *self = calloc(1, sizeof(Sgl$Scene));
	
    Sgl$Scene_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Scene$ctor(Sgl$Scene *  self){
	((SuiCore$Node * )self)->mounted = true;
}





