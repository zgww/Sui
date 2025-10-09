
#include "Skybox_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./Obj3d_orc.h"
#include "./Tex2d_orc.h"
#include "./DrawCtx_orc.h"
#include "./Buffer_orc.h"
#include "./Vao_orc.h"


// static struct 
typedef struct tagSgl$__Block_49_24 Sgl$__Block_49_24;

typedef struct tagSgl$__Closure_mkPlane_55 Sgl$__Closure_mkPlane_55;



struct tagSgl$__Block_49_24 {
	Sgl$Buffer*  vtxBuf ;
	Sgl$Buffer*  uvBuf ;
	Sgl$Buffer*  faceBuf ;
};





struct tagSgl$__Closure_mkPlane_55 {
	void  (*invoke)(Sgl$__Closure_mkPlane_55 *  self, float  texIdx, SuiCore$Vec3 lb, SuiCore$Vec3 rb, SuiCore$Vec3 rt, SuiCore$Vec3 lt);
	Vtable_Object *  vtable ;
	Sgl$__Block_49_24*  __var___Block_49_24 ;
};





// static function declaration
static void  __finiBlock___Block_49_24(Sgl$__Block_49_24 *  self);
static void  __fn___Closure_mkPlane_55(Sgl$__Closure_mkPlane_55 *  self, float  texIdx, SuiCore$Vec3 lb, SuiCore$Vec3 rb, SuiCore$Vec3 rt, SuiCore$Vec3 lt);
static void  __fini___Closure_mkPlane_55(Sgl$__Closure_mkPlane_55 *  self);
static Sgl$__Closure_mkPlane_55*  __make___Closure_mkPlane_55(Sgl$__Closure_mkPlane_55 **  __outRef__, Sgl$__Block_49_24 *  __var___Block_49_24);



//vtable instance
Vtable_Sgl$Skybox _vtable_Sgl$Skybox;

// init meta

void Sgl$Skybox_initMeta(Vtable_Sgl$Skybox *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "material", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$Skybox, material), true, false, 1);
	orc_metaField_class(&pNext, "geometry", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(Sgl$Skybox, geometry), true, false, 1);
	orc_metaField_class(&pNext, "front", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Skybox, front), true, false, 1);
	orc_metaField_class(&pNext, "back", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Skybox, back), true, false, 1);
	orc_metaField_class(&pNext, "left", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Skybox, left), true, false, 1);
	orc_metaField_class(&pNext, "right", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Skybox, right), true, false, 1);
	orc_metaField_class(&pNext, "upTex", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Skybox, upTex), true, false, 1);
	orc_metaField_class(&pNext, "down", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Skybox, down), true, false, 1);
	orc_metaField_class(&pNext, "vao", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$Skybox, vao), true, false, 1);

	orc_metaField_method(&pNext, "buildGeometry", offsetof(Sgl$Skybox, buildGeometry));
}


// vtable init


Vtable_Sgl$Skybox* Vtable_Sgl$Skybox_init(Vtable_Sgl$Skybox* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Skybox;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Skybox_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Skybox";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Skybox_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Skybox_fini(Sgl$Skybox *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$Skybox*)self)->material);
	urgc_fini_field_class(self, (void**)&((Sgl$Skybox*)self)->geometry);
	urgc_fini_field_class(self, (void**)&((Sgl$Skybox*)self)->front);
	urgc_fini_field_class(self, (void**)&((Sgl$Skybox*)self)->back);
	urgc_fini_field_class(self, (void**)&((Sgl$Skybox*)self)->left);
	urgc_fini_field_class(self, (void**)&((Sgl$Skybox*)self)->right);
	urgc_fini_field_class(self, (void**)&((Sgl$Skybox*)self)->upTex);
	urgc_fini_field_class(self, (void**)&((Sgl$Skybox*)self)->down);
	urgc_fini_field_class(self, (void**)&((Sgl$Skybox*)self)->vao);

}

// init fields function


void Sgl$Skybox_init_fields(Sgl$Skybox *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$Skybox_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Skybox*)self)->material, Sgl$Material_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((Sgl$Skybox*)self)->geometry, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Skybox*)self)->front, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Skybox*)self)->back, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Skybox*)self)->left, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Skybox*)self)->right, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Skybox*)self)->upTex, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Skybox*)self)->down, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Skybox*)self)->vao, Sgl$Vao_new(&tmpNewOwner_2) );
    }
	((Object*)self)->ctor = (void*)Sgl$Skybox$ctor;
	((Sgl$Skybox*)self)->buildGeometry = (void*)Sgl$Skybox$buildGeometry;
	((Sgl$Obj3d*)self)->draw = (void*)Sgl$Skybox$draw;
}

// init function

void Sgl$Skybox_init(Sgl$Skybox *self, void *pOwner){
    Vtable_Sgl$Skybox_init(&_vtable_Sgl$Skybox);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Skybox;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Skybox_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Skybox * Sgl$Skybox_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Skybox *self = calloc(1, sizeof(Sgl$Skybox));
	
    Sgl$Skybox_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Skybox$ctor(Sgl$Skybox *  self){
	self->material->load(self->material, "../asset/skybox.matl.json") ;
	self->buildGeometry(self) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Skybox, front) , Sgl$mkTex2dByPathCstr(&tmpReturn_1, "../asset/skybox/front.png") ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Skybox, back) , Sgl$mkTex2dByPathCstr(&tmpReturn_2, "../asset/skybox/back.png") ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Skybox, left) , Sgl$mkTex2dByPathCstr(&tmpReturn_3, "../asset/skybox/left.png") ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tmpReturn_4 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Skybox, right) , Sgl$mkTex2dByPathCstr(&tmpReturn_4, "../asset/skybox/right.png") ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tmpReturn_5 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Skybox, upTex) , Sgl$mkTex2dByPathCstr(&tmpReturn_5, "../asset/skybox/up.png") ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tmpReturn_6 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Skybox, down) , Sgl$mkTex2dByPathCstr(&tmpReturn_6, "../asset/skybox/down.png") ) ;
}


void  Sgl$Skybox$buildGeometry(Sgl$Skybox *  self){
	URGC_VAR_CLEANUP Sgl$__Block_49_24*  __var___Block_49_24 = (__var___Block_49_24=NULL,urgc_init_var((void**)&__var___Block_49_24, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_49_24) , __finiBlock___Block_49_24) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(__var___Block_49_24, (void * )offsetof(Sgl$__Block_49_24, vtxBuf) , Sgl$Buffer_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(__var___Block_49_24, (void * )offsetof(Sgl$__Block_49_24, faceBuf) , Sgl$Buffer_new(&tmpNewOwner_2) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(__var___Block_49_24, (void * )offsetof(Sgl$__Block_49_24, uvBuf) , Sgl$Buffer_new(&tmpNewOwner_3) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  texIdxBuf = (texIdxBuf=NULL,urgc_init_var_class((void**)&texIdxBuf, Sgl$Buffer_new(&texIdxBuf) ));
	URGC_VAR_CLEANUP void  (**mkPlane)(void *  self, float  texIdx, SuiCore$Vec3 lb, SuiCore$Vec3 rb, SuiCore$Vec3 rt, SuiCore$Vec3 lt) = NULL;
	URGC_VAR_CLEANUP Sgl$__Closure_mkPlane_55*  tmpReturn_4 = NULL;
	(urgc_set_var(&mkPlane, __make___Closure_mkPlane_55(&tmpReturn_4, __var___Block_49_24) ) );
	float  h = 500;
	SuiCore$Vec3 f0 = SuiCore$mkVec3(-h, -h, h) ;
	SuiCore$Vec3 f1 = SuiCore$mkVec3(h, -h, h) ;
	SuiCore$Vec3 f2 = SuiCore$mkVec3(h, h, h) ;
	SuiCore$Vec3 f3 = SuiCore$mkVec3(-h, h, h) ;
	SuiCore$Vec3 b0 = SuiCore$mkVec3(-h, -h, -h) ;
	SuiCore$Vec3 b1 = SuiCore$mkVec3(h, -h, -h) ;
	SuiCore$Vec3 b2 = SuiCore$mkVec3(h, h, -h) ;
	SuiCore$Vec3 b3 = SuiCore$mkVec3(-h, h, -h) ;
	if (0) {
		(*(mkPlane))((void * )(mkPlane), 0, f0, f1, f2, f3) ;
		(*(mkPlane))((void * )(mkPlane), 1, b1, b0, b3, b2) ;
		(*(mkPlane))((void * )(mkPlane), 2, b0, f0, f3, b3) ;
		(*(mkPlane))((void * )(mkPlane), 3, f1, b1, b2, f2) ;
		(*(mkPlane))((void * )(mkPlane), 4, f3, f2, b2, b3) ;
		(*(mkPlane))((void * )(mkPlane), 5, b0, b1, f1, f0) ;
	}
	if (1) {
		(*(mkPlane))((void * )(mkPlane), 0, f0, f1, f2, f3) ;
		(*(mkPlane))((void * )(mkPlane), 1, b0, b1, b2, b3) ;
		(*(mkPlane))((void * )(mkPlane), 2, b0, f0, f3, b3) ;
		(*(mkPlane))((void * )(mkPlane), 3, f1, b1, b2, f2) ;
		(*(mkPlane))((void * )(mkPlane), 4, f3, f2, b2, b3) ;
		(*(mkPlane))((void * )(mkPlane), 5, b0, b1, f1, f0) ;
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Skybox, geometry) , Sgl$Geometry_new(&tmpNewOwner_5) ) ;
	{
		Sgl$Geometry*  o = self->geometry;
		
	
		o->setAttrByBuffer(o, "position", __var___Block_49_24->vtxBuf, 3) ;
		o->setAttrByBuffer(o, "idxUv", __var___Block_49_24->uvBuf, 3) ;
		o->setIboByBuffer(o, __var___Block_49_24->faceBuf) ;
	}
}


void  Sgl$Skybox$draw(Sgl$Skybox *  self, Sgl$DrawCtx *  ctx){
	if (self->material == NULL || self->geometry == NULL) {
		return ; 
	}
	self->material->setUniformTex2d(self->material, "tex[0]", self->front) ;
	self->material->setUniformTex2d(self->material, "tex[1]", self->back) ;
	self->material->setUniformTex2d(self->material, "tex[2]", self->left) ;
	self->material->setUniformTex2d(self->material, "tex[3]", self->right) ;
	self->material->setUniformTex2d(self->material, "tex[4]", self->upTex) ;
	self->material->setUniformTex2d(self->material, "tex[5]", self->down) ;
	ctx->setMvpToMaterial(ctx, self, self->material) ;
	self->material->view.data[12] = 0;
	self->material->view.data[13] = 0;
	self->material->view.data[14] = 0;
	self->material->updateMvp(self->material) ;
	self->vao->draw(self->vao, self->geometry, self->material) ;
}



static void  __finiBlock___Block_49_24(Sgl$__Block_49_24 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_49_24, vtxBuf) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_49_24, uvBuf) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_49_24, faceBuf) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_mkPlane_55(Sgl$__Closure_mkPlane_55 *  self, float  texIdx, SuiCore$Vec3 lb, SuiCore$Vec3 rb, SuiCore$Vec3 rt, SuiCore$Vec3 lt){
	int  idx = Sgl$Buffer$floatSize(self->__var___Block_49_24->vtxBuf)  / 3;
	Sgl$Buffer$appendVec3(self->__var___Block_49_24->vtxBuf, lb) ;
	Sgl$Buffer$appendVec3(self->__var___Block_49_24->vtxBuf, rb) ;
	Sgl$Buffer$appendVec3(self->__var___Block_49_24->vtxBuf, rt) ;
	Sgl$Buffer$appendVec3(self->__var___Block_49_24->vtxBuf, lt) ;
	Sgl$Buffer$appendFloat3(self->__var___Block_49_24->uvBuf, texIdx, 0, 0) ;
	Sgl$Buffer$appendFloat3(self->__var___Block_49_24->uvBuf, texIdx, 1, 0) ;
	Sgl$Buffer$appendFloat3(self->__var___Block_49_24->uvBuf, texIdx, 1, 1) ;
	Sgl$Buffer$appendFloat3(self->__var___Block_49_24->uvBuf, texIdx, 0, 1) ;
	int  a = idx;
	int  b = idx + 1;
	int  c = idx + 2;
	int  d = idx + 3;
	Sgl$Buffer$appendInt3(self->__var___Block_49_24->faceBuf, a, b, c) ;
	Sgl$Buffer$appendInt3(self->__var___Block_49_24->faceBuf, a, c, d) ;
}

static void  __fini___Closure_mkPlane_55(Sgl$__Closure_mkPlane_55 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_mkPlane_55, __var___Block_49_24) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_mkPlane_55*  __make___Closure_mkPlane_55(Sgl$__Closure_mkPlane_55 **  __outRef__, Sgl$__Block_49_24 *  __var___Block_49_24){
	URGC_VAR_CLEANUP Sgl$__Closure_mkPlane_55*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_mkPlane_55) , __fini___Closure_mkPlane_55) ));
	self->invoke = __fn___Closure_mkPlane_55;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_mkPlane_55, __var___Block_49_24) , __var___Block_49_24) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



