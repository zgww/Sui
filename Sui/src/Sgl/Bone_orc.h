
typedef struct tagSgl$Bone Sgl$Bone;
typedef struct tagVtable_Sgl$Bone Vtable_Sgl$Bone;
typedef struct tagSgl$Skeleton Sgl$Skeleton;
typedef struct tagVtable_Sgl$Skeleton Vtable_Sgl$Skeleton;
typedef struct tagSgl$CalcData Sgl$CalcData;


#ifndef define_struct___Sgl__Bone_orc_h__
#define define_struct___Sgl__Bone_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Bone_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Bone_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$CalcData {
	Sgl$Skeleton *  skeleton ;
	int  index ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Bone_orc_h__
#define __Sgl__Bone_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Buffer_orc.h"
#include "./DrawCtx_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Bone {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$Bone _vtable_Sgl$Bone;

// class refc:0
struct tagSgl$Bone {
	Sgl$Obj3d super; 
	SuiCore$Vec3 originPosition ;
	Sgl$Mat animMatrix ;
	Sgl$Mat bindPose ;
	Sgl$Mat bindMatrixInverse ;
	int  index ;
	int  parentId ;
	int  id ;
};
Vtable_Sgl$Bone* Vtable_Sgl$Bone_init(Vtable_Sgl$Bone* pvt);
void Sgl$Bone_init_fields(Sgl$Bone *self);
void Sgl$Bone_init(Sgl$Bone *self, void *pOwner);
Sgl$Bone * Sgl$Bone_new(void *pOwner);
void Sgl$Bone_fini(Sgl$Bone *self);

void  Sgl$Bone$drawSelf(Sgl$Bone *  self, Sgl$DrawCtx *  ctx);


// 虚表
struct tagVtable_Sgl$Skeleton {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$Skeleton _vtable_Sgl$Skeleton;

// class refc:0
struct tagSgl$Skeleton {
	Sgl$Obj3d super; 
	Sgl$MatArray*  offsetMatrixArray ;
	void  (*calcBoneMatrixArray) (Sgl$Skeleton *  self);
};
Vtable_Sgl$Skeleton* Vtable_Sgl$Skeleton_init(Vtable_Sgl$Skeleton* pvt);
void Sgl$Skeleton_init_fields(Sgl$Skeleton *self);
void Sgl$Skeleton_init(Sgl$Skeleton *self, void *pOwner);
Sgl$Skeleton * Sgl$Skeleton_new(void *pOwner);
void Sgl$Skeleton_fini(Sgl$Skeleton *self);

void  Sgl$Skeleton$calcBoneMatrixArray(Sgl$Skeleton *  self);
void  Sgl$Skeleton$tick(Sgl$Skeleton *  self, Sgl$DrawCtx *  ctx);



//结构体元数据获取即初始化
MetaStruct* Sgl$CalcData_getOrInitMetaStruct();




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
