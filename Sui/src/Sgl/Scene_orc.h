
typedef struct tagSgl$SceneGlobal Sgl$SceneGlobal;
typedef struct tagSgl$Scene Sgl$Scene;
typedef struct tagVtable_Sgl$Scene Vtable_Sgl$Scene;


#ifndef define_struct___Sgl__Scene_orc_h__
#define define_struct___Sgl__Scene_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Scene_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Scene_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$SceneGlobal {
	bool  cameraDirty ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Scene_orc_h__
#define __Sgl__Scene_orc_h__

//include  importHeadCode
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容


//结构体元数据获取即初始化
MetaStruct* Sgl$SceneGlobal_getOrInitMetaStruct();

extern Sgl$SceneGlobal Sgl$sceneGlobal;

// 虚表
struct tagVtable_Sgl$Scene {
	Vtable_Sgl$Obj3d super;
};
//虚表实例
extern Vtable_Sgl$Scene _vtable_Sgl$Scene;

// class refc:0
struct tagSgl$Scene {
	Sgl$Obj3d super; 
	
};
Vtable_Sgl$Scene* Vtable_Sgl$Scene_init(Vtable_Sgl$Scene* pvt);
void Sgl$Scene_init_fields(Sgl$Scene *self);
void Sgl$Scene_init(Sgl$Scene *self, void *pOwner);
Sgl$Scene * Sgl$Scene_new(void *pOwner);
void Sgl$Scene_fini(Sgl$Scene *self);

void  Sgl$Scene$ctor(Sgl$Scene *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
