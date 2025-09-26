
typedef struct tagSgl$Vao Sgl$Vao;
typedef struct tagVtable_Sgl$Vao Vtable_Sgl$Vao;


#ifndef define_struct___Sgl__Vao_orc_h__
#define define_struct___Sgl__Vao_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Vao_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__Vao_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Vao_orc_h__
#define __Sgl__Vao_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "../Sui/Core/Timer_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Vao {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Vao _vtable_Sgl$Vao;

// class refc:0
struct tagSgl$Vao {
	Object super; 
	Sgl$Material*  material ;
	Sgl$Geometry*  geometry ;
	GLuint id ;
	int  geometryVersion ;
	void  (*regen) (Sgl$Vao *  self);
	bool  (*isNeedBuild) (Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  material);
	bool  (*build) (Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  material);
	void  (*gen) (Sgl$Vao *  self);
	void  (*bind) (Sgl$Vao *  self);
	void  (*unbind) (Sgl$Vao *  self);
	void  (*draw) (Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  matl);
	void  (*drawInstanced) (Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  matl);
};
Vtable_Sgl$Vao* Vtable_Sgl$Vao_init(Vtable_Sgl$Vao* pvt);
void Sgl$Vao_init_fields(Sgl$Vao *self);
void Sgl$Vao_init(Sgl$Vao *self, void *pOwner);
Sgl$Vao * Sgl$Vao_new(void *pOwner);
void Sgl$Vao_fini(Sgl$Vao *self);

void  Sgl$Vao$regen(Sgl$Vao *  self);
void  Sgl$Vao$dtor(Sgl$Vao *  self);
bool  Sgl$Vao$isNeedBuild(Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  material);
bool  Sgl$Vao$build(Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  material);
extern void  Sgl$Vao$gen(Sgl$Vao *  self);
extern void  Sgl$Vao$bind(Sgl$Vao *  self);
extern void  Sgl$Vao$unbind(Sgl$Vao *  self);
void  Sgl$Vao$draw(Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  matl);
extern void  Sgl$Vao$drawInstanced(Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  matl);

extern void  Sgl$deleteVertexArray(GLuint id);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
