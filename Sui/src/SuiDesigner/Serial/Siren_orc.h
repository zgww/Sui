
typedef struct tagSuiDesigner$ReflectionSerializer SuiDesigner$ReflectionSerializer;
typedef struct tagVtable_SuiDesigner$ReflectionSerializer Vtable_SuiDesigner$ReflectionSerializer;
typedef struct tagSuiDesigner$ReflectionDeserializer SuiDesigner$ReflectionDeserializer;
typedef struct tagVtable_SuiDesigner$ReflectionDeserializer Vtable_SuiDesigner$ReflectionDeserializer;


#ifndef define_struct___SuiDesigner__Siren_orc_h__
#define define_struct___SuiDesigner__Siren_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__Siren_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../../Orc/Orc.h"
#include <stdio.h>
#include <string.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__Siren_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__Siren_orc_h__
#define __SuiDesigner__Siren_orc_h__

//include  importHeadCode
#include "../../Orc/Path_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Map_orc.h"
#include "../../Json/Json_orc.h"
#include "./BiJson_orc.h"
#include "../../Sui/Core/Node_orc.h"
#include "../../Sgl/Scene_orc.h"
#include "../../Sgl/Obj3d_orc.h"
#include "../../Sgl/Mesh_orc.h"
#include "../../Sgl/Camera_orc.h"
#include "../../Sgl/PerspectiveCamera_orc.h"
#include "../../Sgl/Light_orc.h"
#include "../../Sgl/PointLight_orc.h"
#include "../../Sgl/DirLight_orc.h"
#include "../../Sgl/SpotLight_orc.h"
#include "../../Sui/Core/Vec3_orc.h"
#include "../../Sui/Core/Vec4_orc.h"
#include "../../Sui/Core/Color_orc.h"
#include "../../Sui/Core/Quaternion_orc.h"
#include "../../Sui/Core/Rect_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$ReflectionSerializer {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ReflectionSerializer _vtable_SuiDesigner$ReflectionSerializer;

// class refc:1
struct tagSuiDesigner$ReflectionSerializer {
	Object super; 
	Json$Json*  (*serializeObject) (Json$Json **  __outRef__, SuiDesigner$ReflectionSerializer *  self, Object*  obj);
	Json$Json*  (*serializePrimitiveValue) (Json$Json **  __outRef__, SuiDesigner$ReflectionSerializer *  self, void *  ptr, OrcMetaType type);
	bool  (*shouldSerializeField) (SuiDesigner$ReflectionSerializer *  self, Object*  obj, const char *  fieldName);
	void  (*serializeFields) (SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, Object*  obj, OrcMetaField *  mf);
	void  (*serializeField) (SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, Object*  obj, OrcMetaField *  mf, const char *  fieldName);
	void  (*serializePrimitiveField) (SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName, OrcMetaType type);
	void  (*serializeListField) (SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName);
	void  (*serializeClassField) (SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName);
	void  (*serializeStructField) (SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName);
	Json$Json*  (*serializeSceneWithChildren) (Json$Json **  __outRef__, SuiDesigner$ReflectionSerializer *  self, Sgl$Scene*  scene);
	void  (*serializeNodeChildren) (SuiDesigner$ReflectionSerializer *  self, Json$Json*  childrenArray, SuiCore$Node*  parent);
	bool  (*saveSceneToFile) (SuiDesigner$ReflectionSerializer *  self, Sgl$Scene*  scene, const char *  filepath);
	Orc$String*  (*serializeSceneToString) (Orc$String **  __outRef__, SuiDesigner$ReflectionSerializer *  self, Sgl$Scene*  scene);
};
Vtable_SuiDesigner$ReflectionSerializer* Vtable_SuiDesigner$ReflectionSerializer_init(Vtable_SuiDesigner$ReflectionSerializer* pvt);
void SuiDesigner$ReflectionSerializer_init_fields(SuiDesigner$ReflectionSerializer *self);
void SuiDesigner$ReflectionSerializer_init(SuiDesigner$ReflectionSerializer *self, void *pOwner);
SuiDesigner$ReflectionSerializer * SuiDesigner$ReflectionSerializer_new(void *pOwner);
void SuiDesigner$ReflectionSerializer_fini(SuiDesigner$ReflectionSerializer *self);

Json$Json*  SuiDesigner$ReflectionSerializer$serializeObject(Json$Json **  __outRef__, SuiDesigner$ReflectionSerializer *  self, Object*  obj);
Json$Json*  SuiDesigner$ReflectionSerializer$serializePrimitiveValue(Json$Json **  __outRef__, SuiDesigner$ReflectionSerializer *  self, void *  ptr, OrcMetaType type);
bool  SuiDesigner$ReflectionSerializer$shouldSerializeField(SuiDesigner$ReflectionSerializer *  self, Object*  obj, const char *  fieldName);
void  SuiDesigner$ReflectionSerializer$serializeFields(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, Object*  obj, OrcMetaField *  mf);
void  SuiDesigner$ReflectionSerializer$serializeField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, Object*  obj, OrcMetaField *  mf, const char *  fieldName);
void  SuiDesigner$ReflectionSerializer$serializePrimitiveField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName, OrcMetaType type);
void  SuiDesigner$ReflectionSerializer$serializeListField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName);
void  SuiDesigner$ReflectionSerializer$serializeClassField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName);
void  SuiDesigner$ReflectionSerializer$serializeStructField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName);
Json$Json*  SuiDesigner$ReflectionSerializer$serializeSceneWithChildren(Json$Json **  __outRef__, SuiDesigner$ReflectionSerializer *  self, Sgl$Scene*  scene);
void  SuiDesigner$ReflectionSerializer$serializeNodeChildren(SuiDesigner$ReflectionSerializer *  self, Json$Json*  childrenArray, SuiCore$Node*  parent);
bool  SuiDesigner$ReflectionSerializer$saveSceneToFile(SuiDesigner$ReflectionSerializer *  self, Sgl$Scene*  scene, const char *  filepath);
Orc$String*  SuiDesigner$ReflectionSerializer$serializeSceneToString(Orc$String **  __outRef__, SuiDesigner$ReflectionSerializer *  self, Sgl$Scene*  scene);


// 虚表
struct tagVtable_SuiDesigner$ReflectionDeserializer {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ReflectionDeserializer _vtable_SuiDesigner$ReflectionDeserializer;

// class refc:1
struct tagSuiDesigner$ReflectionDeserializer {
	Object super; 
	Object*  (*deserializeObject) (Object **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json);
	void  (*deserializeFields) (SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json, Object*  obj, Vtable_Object *  vt);
	void  (*deserializeFieldsByMetaField) (SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json, Object*  obj, OrcMetaField *  mf);
	void  (*deserializeField) (SuiDesigner$ReflectionDeserializer *  self, Object*  obj, OrcMetaField *  mf, const char *  fieldName, Json$Json*  fieldJson);
	void  (*deserializePrimitiveField) (SuiDesigner$ReflectionDeserializer *  self, void *  fieldPtr, OrcMetaField *  mf, OrcMetaType type, Json$Json*  fieldJson);
	void  (*deserializeClassField) (SuiDesigner$ReflectionDeserializer *  self, void *  fieldPtr, OrcMetaField *  mf, Json$Json*  fieldJson);
	void  (*deserializeStructField) (SuiDesigner$ReflectionDeserializer *  self, void *  fieldPtr, OrcMetaField *  mf, Json$Json*  fieldJson);
	Sgl$Scene*  (*deserializeSceneWithChildren) (Sgl$Scene **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json);
	void  (*deserializeNodeChildren) (SuiDesigner$ReflectionDeserializer *  self, SuiCore$Node*  parent, Json$Json*  childrenArray);
	Sgl$Scene*  (*loadSceneFromFile) (Sgl$Scene **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, const char *  filepath);
	Sgl$Scene*  (*deserializeScene) (Sgl$Scene **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, const char *  jsonString);
};
Vtable_SuiDesigner$ReflectionDeserializer* Vtable_SuiDesigner$ReflectionDeserializer_init(Vtable_SuiDesigner$ReflectionDeserializer* pvt);
void SuiDesigner$ReflectionDeserializer_init_fields(SuiDesigner$ReflectionDeserializer *self);
void SuiDesigner$ReflectionDeserializer_init(SuiDesigner$ReflectionDeserializer *self, void *pOwner);
SuiDesigner$ReflectionDeserializer * SuiDesigner$ReflectionDeserializer_new(void *pOwner);
void SuiDesigner$ReflectionDeserializer_fini(SuiDesigner$ReflectionDeserializer *self);

Object*  SuiDesigner$ReflectionDeserializer$deserializeObject(Object **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json);
void  SuiDesigner$ReflectionDeserializer$deserializeFields(SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json, Object*  obj, Vtable_Object *  vt);
void  SuiDesigner$ReflectionDeserializer$deserializeFieldsByMetaField(SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json, Object*  obj, OrcMetaField *  mf);
void  SuiDesigner$ReflectionDeserializer$deserializeField(SuiDesigner$ReflectionDeserializer *  self, Object*  obj, OrcMetaField *  mf, const char *  fieldName, Json$Json*  fieldJson);
void  SuiDesigner$ReflectionDeserializer$deserializePrimitiveField(SuiDesigner$ReflectionDeserializer *  self, void *  fieldPtr, OrcMetaField *  mf, OrcMetaType type, Json$Json*  fieldJson);
void  SuiDesigner$ReflectionDeserializer$deserializeClassField(SuiDesigner$ReflectionDeserializer *  self, void *  fieldPtr, OrcMetaField *  mf, Json$Json*  fieldJson);
void  SuiDesigner$ReflectionDeserializer$deserializeStructField(SuiDesigner$ReflectionDeserializer *  self, void *  fieldPtr, OrcMetaField *  mf, Json$Json*  fieldJson);
Sgl$Scene*  SuiDesigner$ReflectionDeserializer$deserializeSceneWithChildren(Sgl$Scene **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json);
void  SuiDesigner$ReflectionDeserializer$deserializeNodeChildren(SuiDesigner$ReflectionDeserializer *  self, SuiCore$Node*  parent, Json$Json*  childrenArray);
Sgl$Scene*  SuiDesigner$ReflectionDeserializer$loadSceneFromFile(Sgl$Scene **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, const char *  filepath);
Sgl$Scene*  SuiDesigner$ReflectionDeserializer$deserializeScene(Sgl$Scene **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, const char *  jsonString);

extern SuiDesigner$ReflectionSerializer SuiDesigner$reflectionSerializer;
extern SuiDesigner$ReflectionDeserializer SuiDesigner$reflectionDeserializer;
void  SuiDesigner$registerSglClasses();
Orc$String*  SuiDesigner$serializeSceneToString(Orc$String **  __outRef__, Sgl$Scene*  scene);
bool  SuiDesigner$saveSceneToFile(Sgl$Scene*  scene, const char *  filepath);
Sgl$Scene*  SuiDesigner$loadSceneFromFile(Sgl$Scene **  __outRef__, const char *  filepath);
Sgl$Scene*  SuiDesigner$deserializeSceneFromString(Sgl$Scene **  __outRef__, const char *  jsonString);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
