
#include "OutlineFx_orc.h" 

#include "../Orc/String_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "./Tex2d_orc.h"
#include "./Fbo_orc.h"
#include "./Buffer_orc.h"
#include "./Obj3d_orc.h"
#include "./DrawCtx_orc.h"
#include "./Material_orc.h"
#include "./Vao_orc.h"
#include "./GeometryFullscreenQuad_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$OutlineFx _vtable_Sgl$OutlineFx;

// init meta

void Sgl$OutlineFx_initMeta(Vtable_Sgl$OutlineFx *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(Sgl$OutlineFx, fbo), true, false, 1);
	orc_metaField_class(&pNext, "fboEdge", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(Sgl$OutlineFx, fboEdge), true, false, 1);
	orc_metaField_class(&pNext, "maskMatl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$OutlineFx, maskMatl), true, false, 1);
	orc_metaField_class(&pNext, "drawMatl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$OutlineFx, drawMatl), true, false, 1);
	orc_metaField_class(&pNext, "vao", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$OutlineFx, vao), true, false, 1);
	orc_metaField_class(&pNext, "vaoQuad", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$OutlineFx, vaoQuad), true, false, 1);
	orc_metaField_class(&pNext, "fsQuad", ((Vtable_Object*)Vtable_Sgl$GeometryFullscreenQuad_init(0)), offsetof(Sgl$OutlineFx, fsQuad), true, false, 1);

	orc_metaField_method(&pNext, "init", offsetof(Sgl$OutlineFx, init));
	orc_metaField_method(&pNext, "needUpdateFbo", offsetof(Sgl$OutlineFx, needUpdateFbo));
	orc_metaField_method(&pNext, "updateFbo", offsetof(Sgl$OutlineFx, updateFbo));
	orc_metaField_method(&pNext, "drawMask", offsetof(Sgl$OutlineFx, drawMask));
	orc_metaField_method(&pNext, "drawFxQuad", offsetof(Sgl$OutlineFx, drawFxQuad));
	orc_metaField_method(&pNext, "draw", offsetof(Sgl$OutlineFx, draw));
}


// vtable init


Vtable_Sgl$OutlineFx* Vtable_Sgl$OutlineFx_init(Vtable_Sgl$OutlineFx* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$OutlineFx;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$OutlineFx_new;
    ((Vtable_Object*)pvt)->className = "Sgl$OutlineFx";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$OutlineFx_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$OutlineFx_fini(Sgl$OutlineFx *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$OutlineFx_init_fields(Sgl$OutlineFx *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$OutlineFx_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$OutlineFx*)self)->fbo, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$OutlineFx*)self)->fboEdge, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$OutlineFx*)self)->maskMatl, Sgl$Material_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$OutlineFx*)self)->drawMatl, Sgl$Material_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$OutlineFx*)self)->vao, Sgl$Vao_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$OutlineFx*)self)->vaoQuad, Sgl$Vao_new(&tmpNewOwner_4) );
	URGC_VAR_CLEANUP_CLASS Sgl$GeometryFullscreenQuad*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$OutlineFx*)self)->fsQuad, Sgl$GeometryFullscreenQuad_new(&tmpNewOwner_5) );
    }
	((Sgl$OutlineFx*)self)->init = (void*)Sgl$OutlineFx$init;
	((Sgl$OutlineFx*)self)->needUpdateFbo = (void*)Sgl$OutlineFx$needUpdateFbo;
	((Sgl$OutlineFx*)self)->updateFbo = (void*)Sgl$OutlineFx$updateFbo;
	((Sgl$OutlineFx*)self)->drawMask = (void*)Sgl$OutlineFx$drawMask;
	((Sgl$OutlineFx*)self)->drawFxQuad = (void*)Sgl$OutlineFx$drawFxQuad;
	((Sgl$OutlineFx*)self)->draw = (void*)Sgl$OutlineFx$draw;
}

// init function

void Sgl$OutlineFx_init(Sgl$OutlineFx *self, void *pOwner){
    Vtable_Sgl$OutlineFx_init(&_vtable_Sgl$OutlineFx);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$OutlineFx;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$OutlineFx_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$OutlineFx * Sgl$OutlineFx_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$OutlineFx *self = calloc(1, sizeof(Sgl$OutlineFx));
	
    Sgl$OutlineFx_init(self, pOwner);
    return self;
}


// class members
void  Sgl$OutlineFx$init(Sgl$OutlineFx *  self){
	self->maskMatl->load(self->maskMatl, "../asset/outlineMask.matl.json") ;
	self->drawMatl->load(self->drawMatl, "../asset/outlineDraw.matl.json") ;
	self->fsQuad->build(self->fsQuad) ;
}


bool  Sgl$OutlineFx$needUpdateFbo(Sgl$OutlineFx *  self, SuiCore$Vec2 targetSize){
	if (self->fbo == NULL) {
		return true; 
	}
	SuiCore$Vec2 size = self->fbo->getSize(self->fbo) ;
	if (!SuiCore$Vec2$equals(&size, targetSize) ) {
		return true; 
	}
	return false; 
}


void  Sgl$OutlineFx$updateFbo(Sgl$OutlineFx *  self, SuiCore$Vec2 size){
	if (self->needUpdateFbo(self, size) ) {
		URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Sgl$OutlineFx, fbo) , Sgl$Fbo_new(&tmpNewOwner_1) ) ;
		self->fbo->buildWithColorDepthStencilTexture(self->fbo, SuiCore$Vec2$width(&size) , SuiCore$Vec2$height(&size) , true, false, false) ;
		self->fbo->tex2d->setWrapClampToBorder(self->fbo->tex2d, 0x00000000) ;
		self->fbo->tex2d->updateParameters(self->fbo->tex2d) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  tmpNewOwner_2 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Sgl$OutlineFx, fboEdge) , Sgl$Fbo_new(&tmpNewOwner_2) ) ;
		self->fboEdge->buildWithColorDepthStencilTexture(self->fboEdge, SuiCore$Vec2$width(&size) , SuiCore$Vec2$height(&size) , true, false, false) ;
	}
}


void  Sgl$OutlineFx$drawMask(Sgl$OutlineFx *  self, Sgl$DrawCtx *  ctx, Sgl$Obj3d *  obj3d){
	self->fbo->startDraw(self->fbo, 0.0, 0.0, 0.0, 0.0, true, true, true) ;
	obj3d->drawSelfRaw(obj3d, ctx, self->vao, self->maskMatl) ;
	self->fbo->endDraw(self->fbo) ;
}


void  Sgl$OutlineFx$drawFxQuad(Sgl$OutlineFx *  self){
	self->drawMatl->setUniformTex2d(self->drawMatl, "tex", self->fbo->tex2d) ;
	self->drawMatl->setUniformVec2(self->drawMatl, "texSize", self->fbo->getSize(self->fbo) ) ;
	self->vaoQuad->draw(self->vaoQuad, self->fsQuad, self->drawMatl) ;
}


void  Sgl$OutlineFx$draw(Sgl$OutlineFx *  self, Sgl$DrawCtx *  ctx, Sgl$Obj3d *  obj3d, Sgl$Fbo *  targetFbo){
	self->updateFbo(self, ctx->frameSize) ;
	self->drawMask(self, ctx, obj3d) ;
	if (targetFbo) {
		targetFbo->bind(targetFbo) ;
	}
	self->drawFxQuad(self) ;
}





