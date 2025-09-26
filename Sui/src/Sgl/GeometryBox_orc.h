
typedef struct tagSgl$GeometryBox Sgl$GeometryBox;
typedef struct tagVtable_Sgl$GeometryBox Vtable_Sgl$GeometryBox;


#ifndef define_struct___Sgl__GeometryBox_orc_h__
#define define_struct___Sgl__GeometryBox_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryBox_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryBox_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryBox_orc_h__
#define __Sgl__GeometryBox_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$GeometryBox {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryBox _vtable_Sgl$GeometryBox;

// class refc:0
struct tagSgl$GeometryBox {
	Sgl$Geometry super; 
	SuiCore$Vec3 center ;
	float  width ;
	float  height ;
	float  depth ;
	int  widthSegments ;
	int  heightSegments ;
	int  depthSegments ;
	int  color ;
	void  (*mkPlane) (Sgl$GeometryBox *  self, int  segcols, int  segrows, float  dx, float  dy, SuiCore$Vec3 xfactor, SuiCore$Vec3 yfactor, SuiCore$Vec3 p0, SuiCore$Vec3 normalVec3, Sgl$Buffer *  position, Sgl$Buffer *  normal, Sgl$Buffer *  uv, Sgl$Buffer *  face, Sgl$Buffer *  color);
	void  (*build) (Sgl$GeometryBox *  self);
};
Vtable_Sgl$GeometryBox* Vtable_Sgl$GeometryBox_init(Vtable_Sgl$GeometryBox* pvt);
void Sgl$GeometryBox_init_fields(Sgl$GeometryBox *self);
void Sgl$GeometryBox_init(Sgl$GeometryBox *self, void *pOwner);
Sgl$GeometryBox * Sgl$GeometryBox_new(void *pOwner);
void Sgl$GeometryBox_fini(Sgl$GeometryBox *self);

void  Sgl$GeometryBox$mkPlane(Sgl$GeometryBox *  self, int  segcols, int  segrows, float  dx, float  dy, SuiCore$Vec3 xfactor, SuiCore$Vec3 yfactor, SuiCore$Vec3 p0, SuiCore$Vec3 normalVec3, Sgl$Buffer *  position, Sgl$Buffer *  normal, Sgl$Buffer *  uv, Sgl$Buffer *  face, Sgl$Buffer *  color);
void  Sgl$GeometryBox$build(Sgl$GeometryBox *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
