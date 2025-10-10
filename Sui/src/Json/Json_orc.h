
typedef struct tagJson$Json Json$Json;
typedef struct tagVtable_Json$Json Vtable_Json$Json;


#ifndef define_struct___Json__Json_orc_h__
#define define_struct___Json__Json_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Json__Json_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "./cJSON.h"
#include "../Orc/Orc.h"
#include <stdio.h>
#include <string.h>




#ifdef INCLUDE_ONLY_TYPE___Json__Json_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Json__Json_orc_h__
#define __Json__Json_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Json$Json {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Json$Json _vtable_Json$Json;

// class refc:0
struct tagJson$Json {
	Object super; 
	int  kind ;
	bool  boolValue ;
	double  numberValue ;
	Orc$String*  stringValue ;
	Orc$List*  list ;
	Orc$Map*  map ;
	Orc$String*  (*dump) (Orc$String **  __outRef__, Json$Json *  self);
	void  (*dumpToFileByPathCstr) (Json$Json *  self, const char *  path);
	Orc$String*  (*toString) (Orc$String **  __outRef__, Json$Json *  self);
	void  (*setNull) (Json$Json *  self);
	bool  (*isBool) (Json$Json *  self);
	bool  (*isNumber) (Json$Json *  self);
	bool  (*isString) (Json$Json *  self);
	bool  (*isObject) (Json$Json *  self);
	bool  (*isArray) (Json$Json *  self);
	bool  (*isNull) (Json$Json *  self);
	Orc$String*  (*asString) (Orc$String **  __outRef__, Json$Json *  self);
	bool  (*asBool) (Json$Json *  self);
	int  (*asInt) (Json$Json *  self);
	double  (*asNumber) (Json$Json *  self);
	int  (*size) (Json$Json *  self);
	int  (*arraySize) (Json$Json *  self);
	int  (*keySize) (Json$Json *  self);
	Orc$List*  (*keys) (Orc$List **  __outRef__, Json$Json *  self);
	int  (*atAsInt) (Json$Json *  self, int  i);
	double  (*atAsNumber) (Json$Json *  self, int  i);
	bool  (*atAsBool) (Json$Json *  self, int  i);
	Orc$String*  (*atAsString) (Orc$String **  __outRef__, Json$Json *  self, int  i);
	Json$Json*  (*at) (Json$Json **  __outRef__, Json$Json *  self, int  i);
	bool  (*hasKey) (Json$Json *  self, const char *  key);
	Json$Json*  (*get) (Json$Json **  __outRef__, Json$Json *  self, const char *  key);
	int  (*getInt) (Json$Json *  self, const char *  key);
	double  (*getNumber) (Json$Json *  self, const char *  key);
	void  (*getToBool) (Json$Json *  self, const char *  key, bool *  p);
	void  (*getToInt) (Json$Json *  self, const char *  key, int *  p);
	void  (*getToFloat) (Json$Json *  self, const char *  key, float *  p);
	bool  (*getBool) (Json$Json *  self, const char *  key);
	Orc$String*  (*getString) (Orc$String **  __outRef__, Json$Json *  self, const char *  key);
	void  (*getToInts) (Json$Json *  self, const char *  key, int *  pInts, int  maxCount);
	void  (*getToFloats) (Json$Json *  self, const char *  key, float *  pInts, int  maxCount);
	void  (*getToStruct) (Json$Json *  self, const char *  key, void *  pStruct, MetaStruct *  metaStruct);
	void  (*setNumber) (Json$Json *  self, double  v);
	void  (*setBool) (Json$Json *  self, bool  v);
	void  (*setString) (Json$Json *  self, Orc$String*  v);
	void  (*setCstr) (Json$Json *  self, const char *  v);
	void  (*initList) (Json$Json *  self);
	void  (*initMap) (Json$Json *  self);
	void  (*add) (Json$Json *  self, Json$Json*  jo);
	void  (*addNumber) (Json$Json *  self, double  v);
	void  (*addBool) (Json$Json *  self, bool  v);
	void  (*addString) (Json$Json *  self, Orc$String*  v);
	void  (*putNumber) (Json$Json *  self, const char *  key, double  v);
	void  (*putBool) (Json$Json *  self, const char *  key, double  v);
	void  (*putString) (Json$Json *  self, const char *  key, Orc$String*  v);
	void  (*putCstr) (Json$Json *  self, const char *  key, const char *  v);
	void  (*put) (Json$Json *  self, const char *  key, Json$Json*  jo);
	void  (*putObject) (Json$Json *  self, const char *  key, Object *  jo);
	void  (*mergeToSelf) (Json$Json *  self, Json$Json*  jo);
	void  (*toObject) (Json$Json *  self, Object *  obj);
	Object*  (*toObjectByVtables) (Object **  __outRef__, Json$Json *  self, Orc$PointerArray*  vts);
	Object*  (*toObjectByVtable) (Object **  __outRef__, Json$Json *  self, Vtable_Object *  vt);
	Orc$List*  (*getObjectsByVtable) (Orc$List **  __outRef__, Json$Json *  self, const char *  key, Vtable_Object *  vt);
	Orc$List*  (*toObjectsByVtable) (Orc$List **  __outRef__, Json$Json *  self, Vtable_Object *  vt);
	void  (*toInts) (Json$Json *  self, int *  pInts, int  maxCount);
	void  (*toFloats) (Json$Json *  self, float *  pInts, int  maxCount);
};
Vtable_Json$Json* Vtable_Json$Json_init(Vtable_Json$Json* pvt);
void Json$Json_init_fields(Json$Json *self);
void Json$Json_init(Json$Json *self, void *pOwner);
Json$Json * Json$Json_new(void *pOwner);
void Json$Json_fini(Json$Json *self);

void  Json$Json$dtor(Json$Json *  self);
extern Orc$String*  Json$Json$dump(Orc$String **  __outRef__, Json$Json *  self);
void  Json$Json$dumpToFileByPathCstr(Json$Json *  self, const char *  path);
Orc$String*  Json$Json$toString(Orc$String **  __outRef__, Json$Json *  self);
void  Json$Json$setNull(Json$Json *  self);
bool  Json$Json$isBool(Json$Json *  self);
bool  Json$Json$isNumber(Json$Json *  self);
bool  Json$Json$isString(Json$Json *  self);
bool  Json$Json$isObject(Json$Json *  self);
bool  Json$Json$isArray(Json$Json *  self);
bool  Json$Json$isNull(Json$Json *  self);
Orc$String*  Json$Json$asString(Orc$String **  __outRef__, Json$Json *  self);
bool  Json$Json$asBool(Json$Json *  self);
int  Json$Json$asInt(Json$Json *  self);
double  Json$Json$asNumber(Json$Json *  self);
int  Json$Json$size(Json$Json *  self);
int  Json$Json$arraySize(Json$Json *  self);
int  Json$Json$keySize(Json$Json *  self);
Orc$List*  Json$Json$keys(Orc$List **  __outRef__, Json$Json *  self);
int  Json$Json$atAsInt(Json$Json *  self, int  i);
double  Json$Json$atAsNumber(Json$Json *  self, int  i);
bool  Json$Json$atAsBool(Json$Json *  self, int  i);
Orc$String*  Json$Json$atAsString(Orc$String **  __outRef__, Json$Json *  self, int  i);
Json$Json*  Json$Json$at(Json$Json **  __outRef__, Json$Json *  self, int  i);
bool  Json$Json$hasKey(Json$Json *  self, const char *  key);
Json$Json*  Json$Json$get(Json$Json **  __outRef__, Json$Json *  self, const char *  key);
int  Json$Json$getInt(Json$Json *  self, const char *  key);
double  Json$Json$getNumber(Json$Json *  self, const char *  key);
void  Json$Json$getToBool(Json$Json *  self, const char *  key, bool *  p);
void  Json$Json$getToInt(Json$Json *  self, const char *  key, int *  p);
void  Json$Json$getToFloat(Json$Json *  self, const char *  key, float *  p);
bool  Json$Json$getBool(Json$Json *  self, const char *  key);
Orc$String*  Json$Json$getString(Orc$String **  __outRef__, Json$Json *  self, const char *  key);
void  Json$Json$getToInts(Json$Json *  self, const char *  key, int *  pInts, int  maxCount);
void  Json$Json$getToFloats(Json$Json *  self, const char *  key, float *  pInts, int  maxCount);
void  Json$Json$getToStruct(Json$Json *  self, const char *  key, void *  pStruct, MetaStruct *  metaStruct);
void  Json$Json$setNumber(Json$Json *  self, double  v);
void  Json$Json$setBool(Json$Json *  self, bool  v);
void  Json$Json$setString(Json$Json *  self, Orc$String*  v);
void  Json$Json$setCstr(Json$Json *  self, const char *  v);
void  Json$Json$initList(Json$Json *  self);
void  Json$Json$initMap(Json$Json *  self);
void  Json$Json$add(Json$Json *  self, Json$Json*  jo);
void  Json$Json$addNumber(Json$Json *  self, double  v);
void  Json$Json$addBool(Json$Json *  self, bool  v);
void  Json$Json$addString(Json$Json *  self, Orc$String*  v);
void  Json$Json$putNumber(Json$Json *  self, const char *  key, double  v);
void  Json$Json$putBool(Json$Json *  self, const char *  key, double  v);
void  Json$Json$putString(Json$Json *  self, const char *  key, Orc$String*  v);
void  Json$Json$putCstr(Json$Json *  self, const char *  key, const char *  v);
void  Json$Json$put(Json$Json *  self, const char *  key, Json$Json*  jo);
void  Json$Json$putObject(Json$Json *  self, const char *  key, Object *  jo);
void  Json$Json$mergeToSelf(Json$Json *  self, Json$Json*  jo);
void  Json$Json$toObject(Json$Json *  self, Object *  obj);
Object*  Json$Json$toObjectByVtables(Object **  __outRef__, Json$Json *  self, Orc$PointerArray*  vts);
Object*  Json$Json$toObjectByVtable(Object **  __outRef__, Json$Json *  self, Vtable_Object *  vt);
Orc$List*  Json$Json$getObjectsByVtable(Orc$List **  __outRef__, Json$Json *  self, const char *  key, Vtable_Object *  vt);
Orc$List*  Json$Json$toObjectsByVtable(Orc$List **  __outRef__, Json$Json *  self, Vtable_Object *  vt);
void  Json$Json$toInts(Json$Json *  self, int *  pInts, int  maxCount);
void  Json$Json$toFloats(Json$Json *  self, float *  pInts, int  maxCount);

Json$Json*  Json$Json_mkNull(Json$Json **  __outRef__);
Json$Json*  Json$Json_mkNumber(Json$Json **  __outRef__, double  v);
Json$Json*  Json$Json_mkBool(Json$Json **  __outRef__, bool  v);
Json$Json*  Json$Json_mkStringByCstr(Json$Json **  __outRef__, const char *  v);
Json$Json*  Json$Json_mkString(Json$Json **  __outRef__, Orc$String*  v);
Json$Json*  Json$Json_mkArray(Json$Json **  __outRef__);
Json$Json*  Json$Json_mkObject(Json$Json **  __outRef__);
extern Json$Json*  Json$Json_parse(Json$Json **  __outRef__, const char *  s);
Json$Json*  Json$Json_toJsonNumberArrayByInts(Json$Json **  __outRef__, int *  ints, int  count);
Json$Json*  Json$Json_toJsonNumberArrayByFloats(Json$Json **  __outRef__, float *  ints, int  count);
Json$Json*  Json$Json_toJsonByMetaStruct(Json$Json **  __outRef__, void *  pStruct, MetaStruct *  metaStruct);
Json$Json*  Json$Json_toJson(Json$Json **  __outRef__, Object *  obj);
Json$Json*  Json$Json_toJsonArray(Json$Json **  __outRef__, Orc$List *  list);
void  Json$Json_setPrimitive(OrcMetaField *  mf, void *  obj, Json$Json *  value);
void  Json$Json_setStructField(void *  pStruct, MetaStruct *  metaStruct, const char *  key, Json$Json*  value);
void  Json$Json_setStructByJsonObject(void *  pStruct, MetaStruct *  metaStruct, Json$Json*  value);
Json$Json*  Json$Json_parseByPathCstr(Json$Json **  __outRef__, const char *  path);
void  Json$testJson();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
