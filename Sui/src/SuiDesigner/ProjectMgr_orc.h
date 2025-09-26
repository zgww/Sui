
typedef struct tagSuiDesigner$ProjectInfo SuiDesigner$ProjectInfo;
typedef struct tagVtable_SuiDesigner$ProjectInfo Vtable_SuiDesigner$ProjectInfo;
typedef struct tagSuiDesigner$ProjectMgr SuiDesigner$ProjectMgr;
typedef struct tagVtable_SuiDesigner$ProjectMgr Vtable_SuiDesigner$ProjectMgr;


#ifndef define_struct___SuiDesigner__ProjectMgr_orc_h__
#define define_struct___SuiDesigner__ProjectMgr_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__ProjectMgr_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__ProjectMgr_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__ProjectMgr_orc_h__
#define __SuiDesigner__ProjectMgr_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/List_orc.h"
#include "../Json/Json_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$ProjectInfo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ProjectInfo _vtable_SuiDesigner$ProjectInfo;

// class refc:0
struct tagSuiDesigner$ProjectInfo {
	Object super; 
	Orc$String*  path ;
	Orc$String*  version ;
	Orc$String*  icon ;
	Json$Json*  (*toJson) (Json$Json **  __outRef__, SuiDesigner$ProjectInfo *  self);
	void  (*fromJson) (SuiDesigner$ProjectInfo *  self, Json$Json*  jo);
	Orc$String*  (*getName) (Orc$String **  __outRef__, SuiDesigner$ProjectInfo *  self);
};
Vtable_SuiDesigner$ProjectInfo* Vtable_SuiDesigner$ProjectInfo_init(Vtable_SuiDesigner$ProjectInfo* pvt);
void SuiDesigner$ProjectInfo_init_fields(SuiDesigner$ProjectInfo *self);
void SuiDesigner$ProjectInfo_init(SuiDesigner$ProjectInfo *self, void *pOwner);
SuiDesigner$ProjectInfo * SuiDesigner$ProjectInfo_new(void *pOwner);
void SuiDesigner$ProjectInfo_fini(SuiDesigner$ProjectInfo *self);

Json$Json*  SuiDesigner$ProjectInfo$toJson(Json$Json **  __outRef__, SuiDesigner$ProjectInfo *  self);
void  SuiDesigner$ProjectInfo$fromJson(SuiDesigner$ProjectInfo *  self, Json$Json*  jo);
Orc$String*  SuiDesigner$ProjectInfo$getName(Orc$String **  __outRef__, SuiDesigner$ProjectInfo *  self);


// 虚表
struct tagVtable_SuiDesigner$ProjectMgr {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ProjectMgr _vtable_SuiDesigner$ProjectMgr;

// class refc:0
struct tagSuiDesigner$ProjectMgr {
	Object super; 
	Orc$List*  projects ;
	void  (*addTestProject) (SuiDesigner$ProjectMgr *  self, const char *  path);
	Json$Json*  (*toJson) (Json$Json **  __outRef__, SuiDesigner$ProjectMgr *  self);
	void  (*loadByJson) (SuiDesigner$ProjectMgr *  self, Json$Json*  jo);
	void  (*importProject) (SuiDesigner$ProjectMgr *  self, Orc$String*  projectRootDirPath);
	void  (*remove) (SuiDesigner$ProjectMgr *  self, SuiDesigner$ProjectInfo *  project);
	void  (*add) (SuiDesigner$ProjectMgr *  self, SuiDesigner$ProjectInfo*  project);
	void  (*save) (SuiDesigner$ProjectMgr *  self);
	void  (*load) (SuiDesigner$ProjectMgr *  self);
};
Vtable_SuiDesigner$ProjectMgr* Vtable_SuiDesigner$ProjectMgr_init(Vtable_SuiDesigner$ProjectMgr* pvt);
void SuiDesigner$ProjectMgr_init_fields(SuiDesigner$ProjectMgr *self);
void SuiDesigner$ProjectMgr_init(SuiDesigner$ProjectMgr *self, void *pOwner);
SuiDesigner$ProjectMgr * SuiDesigner$ProjectMgr_new(void *pOwner);
void SuiDesigner$ProjectMgr_fini(SuiDesigner$ProjectMgr *self);

void  SuiDesigner$ProjectMgr$ctor(SuiDesigner$ProjectMgr *  self);
void  SuiDesigner$ProjectMgr$addTestProject(SuiDesigner$ProjectMgr *  self, const char *  path);
Json$Json*  SuiDesigner$ProjectMgr$toJson(Json$Json **  __outRef__, SuiDesigner$ProjectMgr *  self);
void  SuiDesigner$ProjectMgr$loadByJson(SuiDesigner$ProjectMgr *  self, Json$Json*  jo);
void  SuiDesigner$ProjectMgr$importProject(SuiDesigner$ProjectMgr *  self, Orc$String*  projectRootDirPath);
void  SuiDesigner$ProjectMgr$remove(SuiDesigner$ProjectMgr *  self, SuiDesigner$ProjectInfo *  project);
void  SuiDesigner$ProjectMgr$add(SuiDesigner$ProjectMgr *  self, SuiDesigner$ProjectInfo*  project);
void  SuiDesigner$ProjectMgr$save(SuiDesigner$ProjectMgr *  self);
void  SuiDesigner$ProjectMgr$load(SuiDesigner$ProjectMgr *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
