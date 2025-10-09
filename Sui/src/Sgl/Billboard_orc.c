
#include "Billboard_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Vao_orc.h"
#include "./Raycaster_orc.h"
#include "./DrawCtx_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Map_orc.h"
#include "../Json/Json_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$Billboard _vtable_Sgl$Billboard;

// init meta

void Sgl$Billboard_initMeta(Vtable_Sgl$Billboard *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "material", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$Billboard, material), true, false, 1);
	orc_metaField_class(&pNext, "geometry", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(Sgl$Billboard, geometry), true, false, 1);
	orc_metaField_class(&pNext, "vao", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$Billboard, vao), true, false, 1);
	orc_metaField_class(&pNext, "depthVao", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$Billboard, depthVao), true, false, 1);

	
}


// vtable init


Vtable_Sgl$Billboard* Vtable_Sgl$Billboard_init(Vtable_Sgl$Billboard* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Billboard;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Billboard_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Billboard";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Billboard_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Billboard_fini(Sgl$Billboard *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$Billboard*)self)->material);
	urgc_fini_field_class(self, (void**)&((Sgl$Billboard*)self)->geometry);
	urgc_fini_field_class(self, (void**)&((Sgl$Billboard*)self)->vao);
	urgc_fini_field_class(self, (void**)&((Sgl$Billboard*)self)->depthVao);

}

// init fields function


void Sgl$Billboard_init_fields(Sgl$Billboard *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$Billboard_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$Billboard*)self)->material, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Billboard*)self)->geometry, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Billboard*)self)->vao, Sgl$Vao_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Billboard*)self)->depthVao, Sgl$Vao_new(&tmpNewOwner_2) );
    }
	((Sgl$Obj3d*)self)->tick = (void*)Sgl$Billboard$tick;
	((Sgl$Obj3d*)self)->draw = (void*)Sgl$Billboard$draw;
	((Sgl$Obj3d*)self)->drawSelf = (void*)Sgl$Billboard$drawSelf;
	((Sgl$Obj3d*)self)->drawDepth = (void*)Sgl$Billboard$drawDepth;
	((Sgl$Obj3d*)self)->hitTestSelfByRaycaster = (void*)Sgl$Billboard$hitTestSelfByRaycaster;
}

// init function

void Sgl$Billboard_init(Sgl$Billboard *self, void *pOwner){
    Vtable_Sgl$Billboard_init(&_vtable_Sgl$Billboard);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Billboard;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Billboard_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Billboard * Sgl$Billboard_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Billboard *self = calloc(1, sizeof(Sgl$Billboard));
	
    Sgl$Billboard_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Billboard$tick(Sgl$Billboard *  self, Sgl$DrawCtx *  ctx){
	SuiCore$Vec3 pos = ((Sgl$Obj3d * )ctx->camera)->position;
	((Sgl$Obj3d * )self)->lookAt(self, pos.x, pos.y, pos.z) ;
}


void  Sgl$Billboard$draw(Sgl$Billboard *  self, Sgl$DrawCtx *  ctx){
	if (self->material == NULL || self->geometry == NULL) {
		return ; 
	}
	if (ctx->addTransparentObj3dIfIsTransparent(ctx, self, self->material) ) {
		
	}
	else {
		((Sgl$Obj3d * )self)->drawSelf(self, ctx) ;
	}
	((Sgl$Obj3d * )self)->drawChildren(self, ctx) ;
}


void  Sgl$Billboard$drawSelf(Sgl$Billboard *  self, Sgl$DrawCtx *  ctx){
	ctx->setMvpToMaterial(ctx, self, self->material) ;
	ctx->setGlobalInfosToMaterial(ctx, self->material) ;
	self->vao->draw(self->vao, self->geometry, self->material) ;
}


void  Sgl$Billboard$drawDepth(Sgl$Billboard *  self, Sgl$DrawCtx *  ctx){
	Sgl$Material *  matl = ctx->depthMatl;
	matl->model = ((Sgl$Obj3d * )self)->_world_transform;
	matl->view = ctx->camera->view;
	matl->projection = ctx->camera->projection;
	matl->updateMvp(matl) ;
	ctx->setGlobalInfosToMaterial(ctx, matl) ;
	self->depthVao->draw(self->depthVao, self->geometry, matl) ;
}


bool  Sgl$Billboard$hitTestSelfByRaycaster(Sgl$Billboard *  self, Sgl$Raycaster *  raycaster){
	Sgl$RayCheckResult r = raycaster->raycastGeometry(raycaster, self, self->geometry) ;
	raycaster->result = r;
	return r.succ; 
}



Sgl$Billboard*  Sgl$mkBillboard(Sgl$Billboard **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (Sgl$Billboard* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_Sgl$Billboard_init(NULL)) ) ; 
}



