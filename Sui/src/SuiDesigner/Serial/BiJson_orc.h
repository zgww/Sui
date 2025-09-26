
typedef struct tagSuiDesigner$Inner SuiDesigner$Inner;
typedef struct tagSuiDesigner$BiJsonExporter SuiDesigner$BiJsonExporter;
typedef struct tagVtable_SuiDesigner$BiJsonExporter Vtable_SuiDesigner$BiJsonExporter;
typedef struct tagSuiDesigner$User SuiDesigner$User;
typedef struct tagVtable_SuiDesigner$User Vtable_SuiDesigner$User;
typedef struct tagSuiDesigner$User2 SuiDesigner$User2;
typedef struct tagVtable_SuiDesigner$User2 Vtable_SuiDesigner$User2;
typedef struct tagSuiDesigner$TestBi SuiDesigner$TestBi;
typedef struct tagVtable_SuiDesigner$TestBi Vtable_SuiDesigner$TestBi;


#ifndef define_struct___SuiDesigner__BiJson_orc_h__
#define define_struct___SuiDesigner__BiJson_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__BiJson_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../../Orc/Orc.h"
#include <stdio.h>
#include <string.h>
#include "../../Json/cJSON.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__BiJson_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiDesigner$Inner {
	int  xx ;
	int  yy ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__BiJson_orc_h__
#define __SuiDesigner__BiJson_orc_h__

//include  importHeadCode
#include "../../Orc/Path_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Map_orc.h"
#include "../../Json/Json_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
extern Object*  SuiDesigner$BiJson_fromJsonStringAndVtable(Object **  __outRef__, const char *  text, Vtable_Object *  vt);
extern cJSON *  SuiDesigner$BiJson_toJsonObject_needToDelete(Object *  obj);
extern Orc$String*  SuiDesigner$BiJson_toJsonString(Orc$String **  __outRef__, Object *  obj);
extern void  SuiDesigner$BiJson_registerClass(Vtable_Object *  vt);
extern Vtable_Object *  SuiDesigner$BiJson_findClass(const char *  className);


//结构体元数据获取即初始化
MetaStruct* SuiDesigner$Inner_getOrInitMetaStruct();


// 虚表
struct tagVtable_SuiDesigner$BiJsonExporter {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$BiJsonExporter _vtable_SuiDesigner$BiJsonExporter;

// class refc:0
struct tagSuiDesigner$BiJsonExporter {
	Object super; 
	Object *  obj ;
	cJSON *  jo ;
	void  (*exportFieldByOrcMetaField) (SuiDesigner$BiJsonExporter *  self, OrcMetaField *  mf);
	void  (*exportField) (SuiDesigner$BiJsonExporter *  self, const char *  fieldStr);
	void  (*exportFields) (SuiDesigner$BiJsonExporter *  self, const char *  fieldsStr);
};
Vtable_SuiDesigner$BiJsonExporter* Vtable_SuiDesigner$BiJsonExporter_init(Vtable_SuiDesigner$BiJsonExporter* pvt);
void SuiDesigner$BiJsonExporter_init_fields(SuiDesigner$BiJsonExporter *self);
void SuiDesigner$BiJsonExporter_init(SuiDesigner$BiJsonExporter *self, void *pOwner);
SuiDesigner$BiJsonExporter * SuiDesigner$BiJsonExporter_new(void *pOwner);
void SuiDesigner$BiJsonExporter_fini(SuiDesigner$BiJsonExporter *self);

extern void  SuiDesigner$BiJsonExporter$exportFieldByOrcMetaField(SuiDesigner$BiJsonExporter *  self, OrcMetaField *  mf);
extern void  SuiDesigner$BiJsonExporter$exportField(SuiDesigner$BiJsonExporter *  self, const char *  fieldStr);
void  SuiDesigner$BiJsonExporter$exportFields(SuiDesigner$BiJsonExporter *  self, const char *  fieldsStr);


// 虚表
struct tagVtable_SuiDesigner$User {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$User _vtable_SuiDesigner$User;

// class refc:1
struct tagSuiDesigner$User {
	Object super; 
	float  go ;
	double  nice ;
	void  (*exportFields) (SuiDesigner$User *  self, SuiDesigner$BiJsonExporter *  exp);
	void  (*say) (SuiDesigner$User *  self);
};
Vtable_SuiDesigner$User* Vtable_SuiDesigner$User_init(Vtable_SuiDesigner$User* pvt);
void SuiDesigner$User_init_fields(SuiDesigner$User *self);
void SuiDesigner$User_init(SuiDesigner$User *self, void *pOwner);
SuiDesigner$User * SuiDesigner$User_new(void *pOwner);
void SuiDesigner$User_fini(SuiDesigner$User *self);

void  SuiDesigner$User$exportFields(SuiDesigner$User *  self, SuiDesigner$BiJsonExporter *  exp);
void  SuiDesigner$User$say(SuiDesigner$User *  self);


// 虚表
struct tagVtable_SuiDesigner$User2 {
	Vtable_SuiDesigner$User super;
};
//虚表实例
extern Vtable_SuiDesigner$User2 _vtable_SuiDesigner$User2;

// class refc:1
struct tagSuiDesigner$User2 {
	SuiDesigner$User super; 
	
};
Vtable_SuiDesigner$User2* Vtable_SuiDesigner$User2_init(Vtable_SuiDesigner$User2* pvt);
void SuiDesigner$User2_init_fields(SuiDesigner$User2 *self);
void SuiDesigner$User2_init(SuiDesigner$User2 *self, void *pOwner);
SuiDesigner$User2 * SuiDesigner$User2_new(void *pOwner);
void SuiDesigner$User2_fini(SuiDesigner$User2 *self);

void  SuiDesigner$User2$say(SuiDesigner$User2 *  self);


// 虚表
struct tagVtable_SuiDesigner$TestBi {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$TestBi _vtable_SuiDesigner$TestBi;

// class refc:0
struct tagSuiDesigner$TestBi {
	Object super; 
	bool  a ;
	char  b ;
	short  c ;
	int  d ;
	long  e ;
	long long  f ;
	float  g ;
	double  h ;
	SuiDesigner$Inner inner ;
	SuiDesigner$User*  u ;
};
Vtable_SuiDesigner$TestBi* Vtable_SuiDesigner$TestBi_init(Vtable_SuiDesigner$TestBi* pvt);
void SuiDesigner$TestBi_init_fields(SuiDesigner$TestBi *self);
void SuiDesigner$TestBi_init(SuiDesigner$TestBi *self, void *pOwner);
SuiDesigner$TestBi * SuiDesigner$TestBi_new(void *pOwner);
void SuiDesigner$TestBi_fini(SuiDesigner$TestBi *self);


void  SuiDesigner$testBiJson();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
