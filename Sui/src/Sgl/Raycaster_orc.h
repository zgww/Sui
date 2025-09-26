
typedef struct tagSgl$RayCheckResult Sgl$RayCheckResult;
typedef struct tagSgl$Raycaster Sgl$Raycaster;
typedef struct tagVtable_Sgl$Raycaster Vtable_Sgl$Raycaster;


#ifndef define_struct___Sgl__Raycaster_orc_h__
#define define_struct___Sgl__Raycaster_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Raycaster_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INCLUDE_ONLY_TYPE
#include "../Sui/Core/Vec3_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Obj3d_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___Sgl__Raycaster_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$RayCheckResult {
	bool  succ ;
	float  distance ;
	SuiCore$Vec3 point ;
	Sgl$Obj3d *  obj ;
	const char *  desc ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Raycaster_orc_h__
#define __Sgl__Raycaster_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Node_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./Sphere_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "./Box3_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./Mat_orc.h"
#include "./Geometry_orc.h"
#include "./Ray_orc.h"
#include "./Obj3d_orc.h"
#include "./Buffer_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Sgl$RayCheckResult_getOrInitMetaStruct();

Sgl$RayCheckResult Sgl$mkRayCheckResultFail();

// 虚表
struct tagVtable_Sgl$Raycaster {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Raycaster _vtable_Sgl$Raycaster;

// class refc:1
struct tagSgl$Raycaster {
	Object super; 
	float  nearDistance ;
	float  farDistance ;
	Sgl$Ray ray ;
	Sgl$RayCheckResult result ;
	Sgl$RayCheckResult (*raycastTree) (Sgl$Raycaster *  self, Sgl$Obj3d *  root);
	bool  (*raycastNode) (Sgl$Raycaster *  self, SuiCore$Node *  n);
	Sgl$RayCheckResult (*checkIntersection) (Sgl$Raycaster *  self, Sgl$Obj3d *  obj, Sgl$Ray localRay, SuiCore$Vec3 pA, SuiCore$Vec3 pB, SuiCore$Vec3 pC);
	Sgl$RayCheckResult (*raycastGeometry) (Sgl$Raycaster *  self, Sgl$Obj3d *  obj, Sgl$Geometry *  geom);
};
Vtable_Sgl$Raycaster* Vtable_Sgl$Raycaster_init(Vtable_Sgl$Raycaster* pvt);
void Sgl$Raycaster_init_fields(Sgl$Raycaster *self);
void Sgl$Raycaster_init(Sgl$Raycaster *self, void *pOwner);
Sgl$Raycaster * Sgl$Raycaster_new(void *pOwner);
void Sgl$Raycaster_fini(Sgl$Raycaster *self);

Sgl$RayCheckResult Sgl$Raycaster$raycastTree(Sgl$Raycaster *  self, Sgl$Obj3d *  root);
bool  Sgl$Raycaster$raycastNode(Sgl$Raycaster *  self, SuiCore$Node *  n);
Sgl$RayCheckResult Sgl$Raycaster$checkIntersection(Sgl$Raycaster *  self, Sgl$Obj3d *  obj, Sgl$Ray localRay, SuiCore$Vec3 pA, SuiCore$Vec3 pB, SuiCore$Vec3 pC);
Sgl$RayCheckResult Sgl$Raycaster$raycastGeometry(Sgl$Raycaster *  self, Sgl$Obj3d *  obj, Sgl$Geometry *  geom);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
