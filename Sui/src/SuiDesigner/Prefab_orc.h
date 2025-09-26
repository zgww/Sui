
typedef struct tagSuiDesigner$Prefab SuiDesigner$Prefab;
typedef struct tagVtable_SuiDesigner$Prefab Vtable_SuiDesigner$Prefab;


#ifndef define_struct___SuiDesigner__Prefab_orc_h__
#define define_struct___SuiDesigner__Prefab_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__Prefab_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__Prefab_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__Prefab_orc_h__
#define __SuiDesigner__Prefab_orc_h__

//include  importHeadCode
#include "../Json/Json_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "./ANode_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$Prefab {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$Prefab _vtable_SuiDesigner$Prefab;

// class refc:0
struct tagSuiDesigner$Prefab {
	Object super; 
	Orc$String*  version ;
	SuiDesigner$ANode*  root ;
	Orc$String*  _path ;
	void  (*fromJson) (SuiDesigner$Prefab *  self, Json$Json*  jo);
	Json$Json*  (*toJson) (Json$Json **  __outRef__, SuiDesigner$Prefab *  self);
	SuiDesigner$Prefab*  (*loadByPathCstr) (SuiDesigner$Prefab **  __outRef__, SuiDesigner$Prefab *  self, const char *  path);
	bool  (*save) (SuiDesigner$Prefab *  self);
	bool  (*saveTo) (SuiDesigner$Prefab *  self, const char *  path);
};
Vtable_SuiDesigner$Prefab* Vtable_SuiDesigner$Prefab_init(Vtable_SuiDesigner$Prefab* pvt);
void SuiDesigner$Prefab_init_fields(SuiDesigner$Prefab *self);
void SuiDesigner$Prefab_init(SuiDesigner$Prefab *self, void *pOwner);
SuiDesigner$Prefab * SuiDesigner$Prefab_new(void *pOwner);
void SuiDesigner$Prefab_fini(SuiDesigner$Prefab *self);

void  SuiDesigner$Prefab$fromJson(SuiDesigner$Prefab *  self, Json$Json*  jo);
Json$Json*  SuiDesigner$Prefab$toJson(Json$Json **  __outRef__, SuiDesigner$Prefab *  self);
SuiDesigner$Prefab*  SuiDesigner$Prefab$loadByPathCstr(SuiDesigner$Prefab **  __outRef__, SuiDesigner$Prefab *  self, const char *  path);
bool  SuiDesigner$Prefab$save(SuiDesigner$Prefab *  self);
bool  SuiDesigner$Prefab$saveTo(SuiDesigner$Prefab *  self, const char *  path);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
