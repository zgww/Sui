
#include "SkinMesh_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Bone_orc.h"
#include "./Geometry_orc.h"
#include "./Material_orc.h"
#include "./Vao_orc.h"
#include "./DrawCtx_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$SkinMesh _vtable_Sgl$SkinMesh;

// init meta

void Sgl$SkinMesh_initMeta(Vtable_Sgl$SkinMesh *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "material", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$SkinMesh, material), true, false, 1);
	orc_metaField_class(&pNext, "geometry", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(Sgl$SkinMesh, geometry), true, false, 1);
	orc_metaField_class(&pNext, "skeleton", ((Vtable_Object*)Vtable_Sgl$Skeleton_init(0)), offsetof(Sgl$SkinMesh, skeleton), true, false, 1);
	orc_metaField_class(&pNext, "vao", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$SkinMesh, vao), true, false, 1);

	orc_metaField_method(&pNext, "initRootBoneIfNeed", offsetof(Sgl$SkinMesh, initRootBoneIfNeed));
}


// vtable init


Vtable_Sgl$SkinMesh* Vtable_Sgl$SkinMesh_init(Vtable_Sgl$SkinMesh* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$SkinMesh;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$SkinMesh_new;
    ((Vtable_Object*)pvt)->className = "Sgl$SkinMesh";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$SkinMesh_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$SkinMesh_fini(Sgl$SkinMesh *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放


}

// init fields function


void Sgl$SkinMesh_init_fields(Sgl$SkinMesh *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$SkinMesh_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$SkinMesh*)self)->material, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$SkinMesh*)self)->geometry, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$SkinMesh*)self)->skeleton, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$SkinMesh*)self)->vao, Sgl$Vao_new(&tmpNewOwner_1) );
    }
	((Sgl$SkinMesh*)self)->initRootBoneIfNeed = (void*)Sgl$SkinMesh$initRootBoneIfNeed;
	((SuiCore$Node*)self)->onMounted = (void*)Sgl$SkinMesh$onMounted;
	((Sgl$Obj3d*)self)->tick = (void*)Sgl$SkinMesh$tick;
	((Sgl$Obj3d*)self)->draw = (void*)Sgl$SkinMesh$draw;
}

// init function

void Sgl$SkinMesh_init(Sgl$SkinMesh *self, void *pOwner){
    Vtable_Sgl$SkinMesh_init(&_vtable_Sgl$SkinMesh);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$SkinMesh;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$SkinMesh_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$SkinMesh * Sgl$SkinMesh_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$SkinMesh *self = calloc(1, sizeof(Sgl$SkinMesh));
	
    Sgl$SkinMesh_init(self, pOwner);
    return self;
}


// class members
void  Sgl$SkinMesh$initRootBoneIfNeed(Sgl$SkinMesh *  self){
	if (self->skeleton) {
		return ; 
	}
	urgc_set_field_class(self, (void * )offsetof(Sgl$SkinMesh, skeleton) , SuiCore$Node$getAncestorByClass((SuiCore$Node * )self, Vtable_Sgl$Skeleton_init(NULL)) ) ;
}


void  Sgl$SkinMesh$onMounted(Sgl$SkinMesh *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$SkinMesh, skeleton) , NULL) ;
}


void  Sgl$SkinMesh$tick(Sgl$SkinMesh *  self, Sgl$DrawCtx *  ctx){
	
}


void  Sgl$SkinMesh$draw(Sgl$SkinMesh *  self, Sgl$DrawCtx *  ctx){
	self->initRootBoneIfNeed(self) ;
	if (self->skeleton == NULL) {
		return ; 
	}
	Sgl$Material *  matl = self->material;
	ctx->setMvpToMaterial(ctx, self, matl) ;
	ctx->setGlobalInfosToMaterial(ctx, matl) ;
	matl->setUniformMatArray(matl, "boneMatrix", self->skeleton->offsetMatrixArray) ;
	self->vao->draw(self->vao, self->geometry, matl) ;
}





