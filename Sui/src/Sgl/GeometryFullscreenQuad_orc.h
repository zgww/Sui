
typedef struct tagSgl$GeometryFullscreenQuad Sgl$GeometryFullscreenQuad;
typedef struct tagVtable_Sgl$GeometryFullscreenQuad Vtable_Sgl$GeometryFullscreenQuad;


#ifndef define_struct___Sgl__GeometryFullscreenQuad_orc_h__
#define define_struct___Sgl__GeometryFullscreenQuad_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryFullscreenQuad_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryFullscreenQuad_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryFullscreenQuad_orc_h__
#define __Sgl__GeometryFullscreenQuad_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Camera_orc.h"
#include "./Mat_orc.h"
#include "./Program_orc.h"
#include "./SpotLight_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$GeometryFullscreenQuad {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryFullscreenQuad _vtable_Sgl$GeometryFullscreenQuad;

// class refc:0
struct tagSgl$GeometryFullscreenQuad {
	Sgl$Geometry super; 
	float  z ;
	void  (*build) (Sgl$GeometryFullscreenQuad *  self);
};
Vtable_Sgl$GeometryFullscreenQuad* Vtable_Sgl$GeometryFullscreenQuad_init(Vtable_Sgl$GeometryFullscreenQuad* pvt);
void Sgl$GeometryFullscreenQuad_init_fields(Sgl$GeometryFullscreenQuad *self);
void Sgl$GeometryFullscreenQuad_init(Sgl$GeometryFullscreenQuad *self, void *pOwner);
Sgl$GeometryFullscreenQuad * Sgl$GeometryFullscreenQuad_new(void *pOwner);
void Sgl$GeometryFullscreenQuad_fini(Sgl$GeometryFullscreenQuad *self);

void  Sgl$GeometryFullscreenQuad$build(Sgl$GeometryFullscreenQuad *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
