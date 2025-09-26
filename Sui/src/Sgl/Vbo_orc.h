
typedef struct tagSgl$Vbo Sgl$Vbo;
typedef struct tagVtable_Sgl$Vbo Vtable_Sgl$Vbo;


#ifndef define_struct___Sgl__Vbo_orc_h__
#define define_struct___Sgl__Vbo_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Vbo_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__Vbo_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Vbo_orc_h__
#define __Sgl__Vbo_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "../Sui/Core/Timer_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Vbo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Vbo _vtable_Sgl$Vbo;

// class refc:0
struct tagSgl$Vbo {
	Object super; 
	GLuint id ;
	GLuint usage ;
	int  byteSize ;
	int  elementCount ;
	bool  isFloat ;
	bool  isInt ;
	int  vaIndex ;
	int  vaCount ;
	int  divide ;
	int  drawInstanceCount ;
	bool  isIndices ;
	Sgl$Buffer*  buf ;
	void  (*setInstancedRender) (Sgl$Vbo *  self, int  elementCount, int  drawInstanceCount);
	int  (*calcInstanceCount) (Sgl$Vbo *  self);
	int  (*calcIndexCount) (Sgl$Vbo *  self);
	void  (*bind) (Sgl$Vbo *  self);
	void  (*genBuffer) (Sgl$Vbo *  self);
	void  (*setVertexAttrib) (Sgl$Vbo *  self);
	void  (*intArrayBuffer) (Sgl$Vbo *  self, Sgl$Buffer *  buf);
	void  (*arrayBuffer) (Sgl$Vbo *  self, Sgl$Buffer *  buf);
	void  (*elementBuffer) (Sgl$Vbo *  self, Sgl$Buffer *  buf);
	void  (*arrayBufferData) (Sgl$Vbo *  self, int  byteSize, float *  vertices);
	void  (*elementBufferData) (Sgl$Vbo *  self, int  byteSize, int *  indices);
};
Vtable_Sgl$Vbo* Vtable_Sgl$Vbo_init(Vtable_Sgl$Vbo* pvt);
void Sgl$Vbo_init_fields(Sgl$Vbo *self);
void Sgl$Vbo_init(Sgl$Vbo *self, void *pOwner);
Sgl$Vbo * Sgl$Vbo_new(void *pOwner);
void Sgl$Vbo_fini(Sgl$Vbo *self);

void  Sgl$Vbo$setInstancedRender(Sgl$Vbo *  self, int  elementCount, int  drawInstanceCount);
int  Sgl$Vbo$calcInstanceCount(Sgl$Vbo *  self);
int  Sgl$Vbo$calcIndexCount(Sgl$Vbo *  self);
void  Sgl$Vbo$ctor(Sgl$Vbo *  self);
void  Sgl$Vbo$dtor(Sgl$Vbo *  self);
extern void  Sgl$Vbo$bind(Sgl$Vbo *  self);
extern void  Sgl$Vbo$genBuffer(Sgl$Vbo *  self);
extern void  Sgl$Vbo$setVertexAttrib(Sgl$Vbo *  self);
void  Sgl$Vbo$intArrayBuffer(Sgl$Vbo *  self, Sgl$Buffer *  buf);
void  Sgl$Vbo$arrayBuffer(Sgl$Vbo *  self, Sgl$Buffer *  buf);
void  Sgl$Vbo$elementBuffer(Sgl$Vbo *  self, Sgl$Buffer *  buf);
extern void  Sgl$Vbo$arrayBufferData(Sgl$Vbo *  self, int  byteSize, float *  vertices);
extern void  Sgl$Vbo$elementBufferData(Sgl$Vbo *  self, int  byteSize, int *  indices);

extern void  Sgl$deleteBuffer(GLuint id);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
