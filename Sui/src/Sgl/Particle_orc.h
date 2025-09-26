
typedef struct tagSgl$Particle Sgl$Particle;
typedef struct tagVtable_Sgl$Particle Vtable_Sgl$Particle;
typedef struct tagSgl$ParticleEmitter Sgl$ParticleEmitter;
typedef struct tagVtable_Sgl$ParticleEmitter Vtable_Sgl$ParticleEmitter;


#ifndef define_struct___Sgl__Particle_orc_h__
#define define_struct___Sgl__Particle_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Particle_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Particle_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Particle_orc_h__
#define __Sgl__Particle_orc_h__

//include  importHeadCode
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


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Particle {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Particle _vtable_Sgl$Particle;

// class refc:1
struct tagSgl$Particle {
	Object super; 
	float  health ;
	float  tail ;
	float  gravity ;
	SuiCore$Vec3 location ;
	SuiCore$Vec3 velocity ;
	SuiCore$Vec3 scale ;
	int  facing ;
};
Vtable_Sgl$Particle* Vtable_Sgl$Particle_init(Vtable_Sgl$Particle* pvt);
void Sgl$Particle_init_fields(Sgl$Particle *self);
void Sgl$Particle_init(Sgl$Particle *self, void *pOwner);
Sgl$Particle * Sgl$Particle_new(void *pOwner);
void Sgl$Particle_fini(Sgl$Particle *self);


void  Sgl$Particle$init(Sgl$Particle *  self, Sgl$ParticleEmitter *  em);
void  Sgl$Particle$update(Sgl$Particle *  self, float  dtInSec);

// 虚表
struct tagVtable_Sgl$ParticleEmitter {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$ParticleEmitter _vtable_Sgl$ParticleEmitter;

// class refc:0
struct tagSgl$ParticleEmitter {
	Sgl$Obj3d super; 
	Orc$List*  particles ;
	Orc$List*  particlePool ;
	float  timeMiddle ;
	float  speed ;
	float  variation ;
	float  latitude ;
	float  gravity ;
	float  lifeSpan ;
	float  emissionRate ;
	float  width ;
	float  length ;
	int  rows ;
	int  columns ;
	bool  emitting ;
	bool  modelSpace ;
	float  currentEmission ;
	Sgl$Mat lookAtCameraMat ;
	Sgl$Mat worldScaleMatrix ;
	Sgl$Mat noTranslateWorldMatrix ;
	SuiCore$Vec3 segmentScaling ;
	Sgl$Material*  material ;
	Sgl$Geometry*  geometry ;
	Sgl$Vao*  vao ;
	Sgl$Buffer*  insPosBuf ;
	void  (*build) (Sgl$ParticleEmitter *  self);
	void  (*cleanup) (Sgl$ParticleEmitter *  self);
	void  (*updateEmitter) (Sgl$ParticleEmitter *  self, Sgl$DrawCtx *  ctx);
	void  (*updateEmission) (Sgl$ParticleEmitter *  self, float  dtSec);
	void  (*updateEmit) (Sgl$ParticleEmitter *  self, float  dtSec);
	void  (*updateParticles) (Sgl$ParticleEmitter *  self, float  dtSec);
	void  (*updateMesh) (Sgl$ParticleEmitter *  self);
	void  (*_emit) (Sgl$ParticleEmitter *  self);
	void  (*createParticle) (Sgl$ParticleEmitter *  self);
};
Vtable_Sgl$ParticleEmitter* Vtable_Sgl$ParticleEmitter_init(Vtable_Sgl$ParticleEmitter* pvt);
void Sgl$ParticleEmitter_init_fields(Sgl$ParticleEmitter *self);
void Sgl$ParticleEmitter_init(Sgl$ParticleEmitter *self, void *pOwner);
Sgl$ParticleEmitter * Sgl$ParticleEmitter_new(void *pOwner);
void Sgl$ParticleEmitter_fini(Sgl$ParticleEmitter *self);

void  Sgl$ParticleEmitter$onMounted(Sgl$ParticleEmitter *  self);
void  Sgl$ParticleEmitter$build(Sgl$ParticleEmitter *  self);
void  Sgl$ParticleEmitter$cleanup(Sgl$ParticleEmitter *  self);
void  Sgl$ParticleEmitter$drawSelf(Sgl$ParticleEmitter *  self, Sgl$DrawCtx *  ctx);
void  Sgl$ParticleEmitter$updateEmitter(Sgl$ParticleEmitter *  self, Sgl$DrawCtx *  ctx);
void  Sgl$ParticleEmitter$updateEmission(Sgl$ParticleEmitter *  self, float  dtSec);
void  Sgl$ParticleEmitter$updateEmit(Sgl$ParticleEmitter *  self, float  dtSec);
void  Sgl$ParticleEmitter$updateParticles(Sgl$ParticleEmitter *  self, float  dtSec);
void  Sgl$ParticleEmitter$updateMesh(Sgl$ParticleEmitter *  self);
void  Sgl$ParticleEmitter$_emit(Sgl$ParticleEmitter *  self);
void  Sgl$ParticleEmitter$createParticle(Sgl$ParticleEmitter *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
