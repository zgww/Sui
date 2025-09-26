
typedef struct tagSgl$GeometryLine Sgl$GeometryLine;
typedef struct tagVtable_Sgl$GeometryLine Vtable_Sgl$GeometryLine;


#ifndef define_struct___Sgl__GeometryLine_orc_h__
#define define_struct___Sgl__GeometryLine_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__GeometryLine_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__GeometryLine_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__GeometryLine_orc_h__
#define __Sgl__GeometryLine_orc_h__

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
struct tagVtable_Sgl$GeometryLine {
	Vtable_Sgl$Geometry super;
};
//虚表实例
extern Vtable_Sgl$GeometryLine _vtable_Sgl$GeometryLine;

// class refc:0
struct tagSgl$GeometryLine {
	Sgl$Geometry super; 
	float  lineWidth ;
	Sgl$Buffer*  vtxBuf ;
	Sgl$Buffer*  colorBuf ;
	int  color ;
	SuiCore$Vec3 lastVtx ;
	bool  hasLastVtx ;
	void  (*clear) (Sgl$GeometryLine *  self);
	void  (*moveToVec3_color) (Sgl$GeometryLine *  self, SuiCore$Vec3 v, int  color);
	void  (*moveToVec3) (Sgl$GeometryLine *  self, SuiCore$Vec3 v);
	void  (*lineToVec3) (Sgl$GeometryLine *  self, SuiCore$Vec3 v);
	void  (*lineToVec3_color) (Sgl$GeometryLine *  self, SuiCore$Vec3 v, int  color);
	void  (*moveTo_color) (Sgl$GeometryLine *  self, float  x, float  y, float  z, int  color);
	void  (*moveTo) (Sgl$GeometryLine *  self, float  x, float  y, float  z);
	void  (*lineTo) (Sgl$GeometryLine *  self, float  x, float  y, float  z);
	void  (*lineTo_color) (Sgl$GeometryLine *  self, float  x, float  y, float  z, int  color);
	void  (*appendVertex) (Sgl$GeometryLine *  self, SuiCore$Vec3 pos);
	void  (*appendVertexAndColor) (Sgl$GeometryLine *  self, SuiCore$Vec3 pos, int  color);
	void  (*updateBuffer) (Sgl$GeometryLine *  self);
	void  (*draw) (Sgl$GeometryLine *  self, Sgl$Material *  matl);
	void  (*build) (Sgl$GeometryLine *  self);
	void  (*buildSpotLightHelper) (Sgl$GeometryLine *  self, Sgl$SpotLight *  sl);
	void  (*buildCameraHelper) (Sgl$GeometryLine *  self, Sgl$Camera *  camera);
};
Vtable_Sgl$GeometryLine* Vtable_Sgl$GeometryLine_init(Vtable_Sgl$GeometryLine* pvt);
void Sgl$GeometryLine_init_fields(Sgl$GeometryLine *self);
void Sgl$GeometryLine_init(Sgl$GeometryLine *self, void *pOwner);
Sgl$GeometryLine * Sgl$GeometryLine_new(void *pOwner);
void Sgl$GeometryLine_fini(Sgl$GeometryLine *self);

void  Sgl$GeometryLine$clear(Sgl$GeometryLine *  self);
void  Sgl$GeometryLine$moveToVec3_color(Sgl$GeometryLine *  self, SuiCore$Vec3 v, int  color);
void  Sgl$GeometryLine$moveToVec3(Sgl$GeometryLine *  self, SuiCore$Vec3 v);
void  Sgl$GeometryLine$lineToVec3(Sgl$GeometryLine *  self, SuiCore$Vec3 v);
void  Sgl$GeometryLine$lineToVec3_color(Sgl$GeometryLine *  self, SuiCore$Vec3 v, int  color);
void  Sgl$GeometryLine$moveTo_color(Sgl$GeometryLine *  self, float  x, float  y, float  z, int  color);
void  Sgl$GeometryLine$moveTo(Sgl$GeometryLine *  self, float  x, float  y, float  z);
void  Sgl$GeometryLine$lineTo(Sgl$GeometryLine *  self, float  x, float  y, float  z);
void  Sgl$GeometryLine$lineTo_color(Sgl$GeometryLine *  self, float  x, float  y, float  z, int  color);
void  Sgl$GeometryLine$appendVertex(Sgl$GeometryLine *  self, SuiCore$Vec3 pos);
void  Sgl$GeometryLine$appendVertexAndColor(Sgl$GeometryLine *  self, SuiCore$Vec3 pos, int  color);
void  Sgl$GeometryLine$updateBuffer(Sgl$GeometryLine *  self);
void  Sgl$GeometryLine$draw(Sgl$GeometryLine *  self, Sgl$Material *  matl);
void  Sgl$GeometryLine$build(Sgl$GeometryLine *  self);
void  Sgl$GeometryLine$buildSpotLightHelper(Sgl$GeometryLine *  self, Sgl$SpotLight *  sl);
void  Sgl$GeometryLine$buildCameraHelper(Sgl$GeometryLine *  self, Sgl$Camera *  camera);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
