
#include "Particle_orc.h" 

#include <stdio.h>
#include <math.h>
#include "./Obj3d_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./DrawCtx_orc.h"
#include "./Vao_orc.h"
#include "./Buffer_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./GeometryRect_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$Particle _vtable_Sgl$Particle;

// init meta

void Sgl$Particle_initMeta(Vtable_Sgl$Particle *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "health", OrcMetaType_float, offsetof(Sgl$Particle, health), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "tail", OrcMetaType_float, offsetof(Sgl$Particle, tail), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "gravity", OrcMetaType_float, offsetof(Sgl$Particle, gravity), 0, 0, 0, 0);//float
	orc_metaField_struct(&pNext, "location", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Particle, location), false, false, 0);
	orc_metaField_struct(&pNext, "velocity", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Particle, velocity), false, false, 0);
	orc_metaField_struct(&pNext, "scale", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Particle, scale), false, false, 0);
	orc_metaField_primitive(&pNext, "facing", OrcMetaType_int, offsetof(Sgl$Particle, facing), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_Sgl$Particle* Vtable_Sgl$Particle_init(Vtable_Sgl$Particle* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Particle;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Particle_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Particle";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Particle_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Sgl$Particle_fini(Sgl$Particle *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void Sgl$Particle_init_fields(Sgl$Particle *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Particle_fini;
	//fields
    {
	((Sgl$Particle*)self)->health = 0;
	((Sgl$Particle*)self)->tail = 0;
	((Sgl$Particle*)self)->gravity = 0;
	((Sgl$Particle*)self)->facing = 0;
    }
	
}

// init function

void Sgl$Particle_init(Sgl$Particle *self, void *pOwner){
    Vtable_Sgl$Particle_init(&_vtable_Sgl$Particle);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Particle;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Particle_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Particle * Sgl$Particle_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Particle *self = calloc(1, sizeof(Sgl$Particle));
	
    Sgl$Particle_init(self, pOwner);
    return self;
}


// class members

void  Sgl$Particle$init(Sgl$Particle *  self, Sgl$ParticleEmitter *  em){
	self->health = em->lifeSpan;
	self->gravity = em->gravity;
	SuiCore$Vec3$copy(&self->scale, em->segmentScaling) ;
	SuiCore$Vec3$set(&self->location, Orc$randRadiusf(em->length) , 0, Orc$randRadiusf(em->width) ) ;
	SuiCore$Vec3$set(&self->velocity, 0, 1, 0) ;
	if (!em->modelSpace) {
		self->location = Sgl$Mat$mulVec3(&((Sgl$Obj3d * )em)->_world_transform, self->location) ;
	}
	else {
		
	}
	float  velocityLen = em->speed + Orc$randRadiusf(em->variation) ;
	self->velocity = SuiCore$Vec3$scale(&self->velocity, velocityLen) ;
}

void  Sgl$Particle$update(Sgl$Particle *  self, float  dtInSec){
	self->health -= dtInSec;
	if (self->health > 0) {
		self->velocity.y -= self->gravity * dtInSec;
		self->location.x += self->velocity.x * dtInSec;
		self->location.y += self->velocity.y * dtInSec;
		self->location.z += self->velocity.z * dtInSec;
	}
}


//vtable instance
Vtable_Sgl$ParticleEmitter _vtable_Sgl$ParticleEmitter;

// init meta

void Sgl$ParticleEmitter_initMeta(Vtable_Sgl$ParticleEmitter *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "particles", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$ParticleEmitter, particles), true, false, 1);
	orc_metaField_class(&pNext, "particlePool", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$ParticleEmitter, particlePool), true, false, 1);
	orc_metaField_primitive(&pNext, "timeMiddle", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, timeMiddle), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "speed", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, speed), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "variation", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, variation), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "latitude", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, latitude), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "gravity", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, gravity), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "lifeSpan", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, lifeSpan), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "emissionRate", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, emissionRate), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "width", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, width), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "length", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, length), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "rows", OrcMetaType_int, offsetof(Sgl$ParticleEmitter, rows), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "columns", OrcMetaType_int, offsetof(Sgl$ParticleEmitter, columns), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "emitting", OrcMetaType_bool, offsetof(Sgl$ParticleEmitter, emitting), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "modelSpace", OrcMetaType_bool, offsetof(Sgl$ParticleEmitter, modelSpace), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "currentEmission", OrcMetaType_float, offsetof(Sgl$ParticleEmitter, currentEmission), 0, 0, 0, 0);//float
	orc_metaField_struct(&pNext, "lookAtCameraMat", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$ParticleEmitter, lookAtCameraMat), false, false, 0);
	orc_metaField_struct(&pNext, "worldScaleMatrix", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$ParticleEmitter, worldScaleMatrix), false, false, 0);
	orc_metaField_struct(&pNext, "noTranslateWorldMatrix", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$ParticleEmitter, noTranslateWorldMatrix), false, false, 0);
	orc_metaField_struct(&pNext, "segmentScaling", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$ParticleEmitter, segmentScaling), false, false, 0);
	orc_metaField_class(&pNext, "material", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$ParticleEmitter, material), true, false, 1);
	orc_metaField_class(&pNext, "geometry", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(Sgl$ParticleEmitter, geometry), true, false, 1);
	orc_metaField_class(&pNext, "vao", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$ParticleEmitter, vao), true, false, 1);
	orc_metaField_class(&pNext, "insPosBuf", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ParticleEmitter, insPosBuf), true, false, 1);

	orc_metaField_method(&pNext, "build", offsetof(Sgl$ParticleEmitter, build));
	orc_metaField_method(&pNext, "cleanup", offsetof(Sgl$ParticleEmitter, cleanup));
	orc_metaField_method(&pNext, "updateEmitter", offsetof(Sgl$ParticleEmitter, updateEmitter));
	orc_metaField_method(&pNext, "updateEmission", offsetof(Sgl$ParticleEmitter, updateEmission));
	orc_metaField_method(&pNext, "updateEmit", offsetof(Sgl$ParticleEmitter, updateEmit));
	orc_metaField_method(&pNext, "updateParticles", offsetof(Sgl$ParticleEmitter, updateParticles));
	orc_metaField_method(&pNext, "updateMesh", offsetof(Sgl$ParticleEmitter, updateMesh));
	orc_metaField_method(&pNext, "_emit", offsetof(Sgl$ParticleEmitter, _emit));
	orc_metaField_method(&pNext, "createParticle", offsetof(Sgl$ParticleEmitter, createParticle));
}


// vtable init


Vtable_Sgl$ParticleEmitter* Vtable_Sgl$ParticleEmitter_init(Vtable_Sgl$ParticleEmitter* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$ParticleEmitter;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$ParticleEmitter_new;
    ((Vtable_Object*)pvt)->className = "Sgl$ParticleEmitter";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$ParticleEmitter_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$ParticleEmitter_fini(Sgl$ParticleEmitter *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->particles);
	urgc_fini_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->particlePool);
	urgc_fini_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->material);
	urgc_fini_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->geometry);
	urgc_fini_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->vao);
	urgc_fini_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->insPosBuf);

}

// init fields function


void Sgl$ParticleEmitter_init_fields(Sgl$ParticleEmitter *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$ParticleEmitter_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->particles, Orc$List_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->particlePool, Orc$List_new(&tmpNewOwner_2) );
	((Sgl$ParticleEmitter*)self)->timeMiddle = 0;
	((Sgl$ParticleEmitter*)self)->speed = 100;
	((Sgl$ParticleEmitter*)self)->variation = 50;
	((Sgl$ParticleEmitter*)self)->latitude = 0;
	((Sgl$ParticleEmitter*)self)->gravity = 0;
	((Sgl$ParticleEmitter*)self)->lifeSpan = 2;
	((Sgl$ParticleEmitter*)self)->emissionRate = 3;
	((Sgl$ParticleEmitter*)self)->width = 100;
	((Sgl$ParticleEmitter*)self)->length = 100;
	((Sgl$ParticleEmitter*)self)->rows = 0;
	((Sgl$ParticleEmitter*)self)->columns = 0;
	((Sgl$ParticleEmitter*)self)->emitting = true;
	((Sgl$ParticleEmitter*)self)->modelSpace = false;
	((Sgl$ParticleEmitter*)self)->currentEmission = 0;
	urgc_set_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->material, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->geometry, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->vao, Sgl$Vao_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ParticleEmitter*)self)->insPosBuf, Sgl$Buffer_new(&tmpNewOwner_4) );
    }
	((SuiCore$Node*)self)->onMounted = (void*)Sgl$ParticleEmitter$onMounted;
	((Sgl$ParticleEmitter*)self)->build = (void*)Sgl$ParticleEmitter$build;
	((Sgl$ParticleEmitter*)self)->cleanup = (void*)Sgl$ParticleEmitter$cleanup;
	((Sgl$Obj3d*)self)->drawSelf = (void*)Sgl$ParticleEmitter$drawSelf;
	((Sgl$ParticleEmitter*)self)->updateEmitter = (void*)Sgl$ParticleEmitter$updateEmitter;
	((Sgl$ParticleEmitter*)self)->updateEmission = (void*)Sgl$ParticleEmitter$updateEmission;
	((Sgl$ParticleEmitter*)self)->updateEmit = (void*)Sgl$ParticleEmitter$updateEmit;
	((Sgl$ParticleEmitter*)self)->updateParticles = (void*)Sgl$ParticleEmitter$updateParticles;
	((Sgl$ParticleEmitter*)self)->updateMesh = (void*)Sgl$ParticleEmitter$updateMesh;
	((Sgl$ParticleEmitter*)self)->_emit = (void*)Sgl$ParticleEmitter$_emit;
	((Sgl$ParticleEmitter*)self)->createParticle = (void*)Sgl$ParticleEmitter$createParticle;
}

// init function

void Sgl$ParticleEmitter_init(Sgl$ParticleEmitter *self, void *pOwner){
    Vtable_Sgl$ParticleEmitter_init(&_vtable_Sgl$ParticleEmitter);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$ParticleEmitter;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$ParticleEmitter_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$ParticleEmitter * Sgl$ParticleEmitter_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$ParticleEmitter *self = calloc(1, sizeof(Sgl$ParticleEmitter));
	
    Sgl$ParticleEmitter_init(self, pOwner);
    return self;
}


// class members
void  Sgl$ParticleEmitter$onMounted(Sgl$ParticleEmitter *  self){
	self->build(self) ;
}


void  Sgl$ParticleEmitter$build(Sgl$ParticleEmitter *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$GeometryRect*  tmpNewOwner_1 = NULL;
	{
		Sgl$GeometryRect*  o = Sgl$GeometryRect_new(&tmpNewOwner_1) ;
		
	
		o->build(o) ;
		urgc_set_field_class(self, (void * )offsetof(Sgl$ParticleEmitter, geometry) , o) ;
		Sgl$GeoAttr *  attr = self->geometry->gocInstanceAttr(self->geometry, "insPos") ;
		attr->vbo->setInstancedRender(attr->vbo, 3, self->particles->size(self->particles) ) ;
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$ParticleEmitter, material) , Sgl$Material_new(&tmpNewOwner_2) ) ;
	self->material->load(self->material, "../asset/particle.matl.json") ;
}


void  Sgl$ParticleEmitter$cleanup(Sgl$ParticleEmitter *  self){
	
}


void  Sgl$ParticleEmitter$drawSelf(Sgl$ParticleEmitter *  self, Sgl$DrawCtx *  ctx){
	self->updateEmitter(self, ctx) ;
	ctx->setMvpToMaterial(ctx, self, self->material) ;
	self->vao->draw(self->vao, self->geometry, self->material) ;
}


void  Sgl$ParticleEmitter$updateEmitter(Sgl$ParticleEmitter *  self, Sgl$DrawCtx *  ctx){
	self->updateEmit(self, ctx->dtSec) ;
	self->updateParticles(self, ctx->dtSec) ;
	self->updateMesh(self) ;
}


void  Sgl$ParticleEmitter$updateEmission(Sgl$ParticleEmitter *  self, float  dtSec){
	self->currentEmission += self->emissionRate * dtSec;
}


void  Sgl$ParticleEmitter$updateEmit(Sgl$ParticleEmitter *  self, float  dtSec){
	self->updateEmission(self, dtSec) ;
	for (int  i = 1; i < self->currentEmission; i++) {
		self->_emit(self) ;
	}
	self->currentEmission = fmod(self->currentEmission, 1) ;
}


void  Sgl$ParticleEmitter$updateParticles(Sgl$ParticleEmitter *  self, float  dtSec){
	for (int  i = self->particles->size(self->particles)  - 1; i >= 0; i--) {
		Sgl$Particle *  p = (Sgl$Particle * )self->particles->get(self->particles, i) ;
		Sgl$Particle$update(p, dtSec) ;
		if (p->health <= 0) {
			self->particlePool->add(self->particlePool, p) ;
			self->particles->removeAt(self->particles, i) ;
		}
	}
}


void  Sgl$ParticleEmitter$updateMesh(Sgl$ParticleEmitter *  self){
	if (self->particles->size(self->particles)  > 0) {
		Sgl$GeoAttr *  attr = self->geometry->gocInstanceAttr(self->geometry, "insPos") ;
		attr->vbo->setInstancedRender(attr->vbo, 3, self->particles->size(self->particles) ) ;
		Sgl$Buffer$clear(self->insPosBuf) ;
		for (int  i = 0; i < self->particles->size(self->particles) ; i++) {
			Sgl$Particle *  p = (Sgl$Particle * )self->particles->get(self->particles, i) ;
			Sgl$Buffer$appendFloat3(self->insPosBuf, p->location.x, p->location.y, p->location.z) ;
		}
		attr->vbo->arrayBuffer(attr->vbo, self->insPosBuf) ;
	}
}


void  Sgl$ParticleEmitter$_emit(Sgl$ParticleEmitter *  self){
	if (self->emitting) {
		self->createParticle(self) ;
	}
	self->currentEmission--;
}


void  Sgl$ParticleEmitter$createParticle(Sgl$ParticleEmitter *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Particle*  p = NULL;
	if (self->particlePool->size(self->particlePool)  > 0) {
		urgc_set_var_class(&p, self->particlePool->last(self->particlePool) ) ;
		self->particlePool->removeAt(self->particlePool, self->particlePool->size(self->particlePool)  - 1) ;
	}
	else {
		URGC_VAR_CLEANUP_CLASS Sgl$Particle*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&p, Sgl$Particle_new(&tmpNewOwner_1) ) ;
	}
	Sgl$Particle$init(p, self) ;
	self->particles->add(self->particles, p) ;
}





