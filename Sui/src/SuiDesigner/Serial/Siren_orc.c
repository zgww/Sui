
#include "Siren_orc.h" 

#include "../../Orc/Orc.h"
#include <stdio.h>
#include <string.h>
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


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$ReflectionSerializer _vtable_SuiDesigner$ReflectionSerializer;

// init meta

void SuiDesigner$ReflectionSerializer_initMeta(Vtable_SuiDesigner$ReflectionSerializer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "serializeObject", offsetof(SuiDesigner$ReflectionSerializer, serializeObject));
	orc_metaField_method(&pNext, "serializePrimitiveValue", offsetof(SuiDesigner$ReflectionSerializer, serializePrimitiveValue));
	orc_metaField_method(&pNext, "shouldSerializeField", offsetof(SuiDesigner$ReflectionSerializer, shouldSerializeField));
	orc_metaField_method(&pNext, "serializeFields", offsetof(SuiDesigner$ReflectionSerializer, serializeFields));
	orc_metaField_method(&pNext, "serializeField", offsetof(SuiDesigner$ReflectionSerializer, serializeField));
	orc_metaField_method(&pNext, "serializePrimitiveField", offsetof(SuiDesigner$ReflectionSerializer, serializePrimitiveField));
	orc_metaField_method(&pNext, "serializeListField", offsetof(SuiDesigner$ReflectionSerializer, serializeListField));
	orc_metaField_method(&pNext, "serializeClassField", offsetof(SuiDesigner$ReflectionSerializer, serializeClassField));
	orc_metaField_method(&pNext, "serializeStructField", offsetof(SuiDesigner$ReflectionSerializer, serializeStructField));
	orc_metaField_method(&pNext, "serializeSceneWithChildren", offsetof(SuiDesigner$ReflectionSerializer, serializeSceneWithChildren));
	orc_metaField_method(&pNext, "serializeNodeChildren", offsetof(SuiDesigner$ReflectionSerializer, serializeNodeChildren));
	orc_metaField_method(&pNext, "saveSceneToFile", offsetof(SuiDesigner$ReflectionSerializer, saveSceneToFile));
	orc_metaField_method(&pNext, "serializeSceneToString", offsetof(SuiDesigner$ReflectionSerializer, serializeSceneToString));
}


// vtable init


Vtable_SuiDesigner$ReflectionSerializer* Vtable_SuiDesigner$ReflectionSerializer_init(Vtable_SuiDesigner$ReflectionSerializer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ReflectionSerializer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ReflectionSerializer_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ReflectionSerializer";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ReflectionSerializer_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$ReflectionSerializer_fini(SuiDesigner$ReflectionSerializer *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$ReflectionSerializer_init_fields(SuiDesigner$ReflectionSerializer *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ReflectionSerializer_fini;
	//fields
    {
	
    }
	((SuiDesigner$ReflectionSerializer*)self)->serializeObject = (void*)SuiDesigner$ReflectionSerializer$serializeObject;
	((SuiDesigner$ReflectionSerializer*)self)->serializePrimitiveValue = (void*)SuiDesigner$ReflectionSerializer$serializePrimitiveValue;
	((SuiDesigner$ReflectionSerializer*)self)->shouldSerializeField = (void*)SuiDesigner$ReflectionSerializer$shouldSerializeField;
	((SuiDesigner$ReflectionSerializer*)self)->serializeFields = (void*)SuiDesigner$ReflectionSerializer$serializeFields;
	((SuiDesigner$ReflectionSerializer*)self)->serializeField = (void*)SuiDesigner$ReflectionSerializer$serializeField;
	((SuiDesigner$ReflectionSerializer*)self)->serializePrimitiveField = (void*)SuiDesigner$ReflectionSerializer$serializePrimitiveField;
	((SuiDesigner$ReflectionSerializer*)self)->serializeListField = (void*)SuiDesigner$ReflectionSerializer$serializeListField;
	((SuiDesigner$ReflectionSerializer*)self)->serializeClassField = (void*)SuiDesigner$ReflectionSerializer$serializeClassField;
	((SuiDesigner$ReflectionSerializer*)self)->serializeStructField = (void*)SuiDesigner$ReflectionSerializer$serializeStructField;
	((SuiDesigner$ReflectionSerializer*)self)->serializeSceneWithChildren = (void*)SuiDesigner$ReflectionSerializer$serializeSceneWithChildren;
	((SuiDesigner$ReflectionSerializer*)self)->serializeNodeChildren = (void*)SuiDesigner$ReflectionSerializer$serializeNodeChildren;
	((SuiDesigner$ReflectionSerializer*)self)->saveSceneToFile = (void*)SuiDesigner$ReflectionSerializer$saveSceneToFile;
	((SuiDesigner$ReflectionSerializer*)self)->serializeSceneToString = (void*)SuiDesigner$ReflectionSerializer$serializeSceneToString;
}

// init function

void SuiDesigner$ReflectionSerializer_init(SuiDesigner$ReflectionSerializer *self, void *pOwner){
    Vtable_SuiDesigner$ReflectionSerializer_init(&_vtable_SuiDesigner$ReflectionSerializer);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ReflectionSerializer;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ReflectionSerializer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ReflectionSerializer * SuiDesigner$ReflectionSerializer_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ReflectionSerializer *self = calloc(1, sizeof(SuiDesigner$ReflectionSerializer));
	
    SuiDesigner$ReflectionSerializer_init(self, pOwner);
    return self;
}


// class members
Json$Json*  SuiDesigner$ReflectionSerializer$serializeObject(Json$Json **  __outRef__, SuiDesigner$ReflectionSerializer *  self, Object*  obj){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(obj);

	if (!obj) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNull(&tmpReturn_1) ) ; 
	}
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Orc$String_init(NULL))) {
		Orc$String *  str = (Orc$String * )obj;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkStringByCstr(&tmpReturn_2, str->str) ) ; 
	}
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Orc$List_init(NULL))) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  listJson = Json$Json_mkArray((listJson = NULL,&listJson)) ;
		Orc$List *  list = (Orc$List * )obj;
		int  size = list->size(list) ;
		for (int  i = 0; i < size; i++) {
			URGC_VAR_CLEANUP_CLASS Object*  item = (item=NULL,urgc_init_var_class((void**)&item, list->get(list, i) ));
			URGC_VAR_CLEANUP_CLASS Json$Json*  itemJson = self->serializeObject((itemJson = NULL,&itemJson), self, item) ;
			listJson->add(listJson, itemJson) ;
		}
		return urgc_set_var_for_return_class((void ** )__outRef__, listJson) ; 
	}
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Orc$Map_init(NULL))) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  mapJson = Json$Json_mkObject((mapJson = NULL,&mapJson)) ;
		Orc$Map *  map = (Orc$Map * )obj;
		URGC_VAR_CLEANUP_CLASS Orc$List*  keys = map->keys((keys = NULL,&keys), map) ;
		int  size = keys->size(keys) ;
		for (int  i = 0; i < size; i++) {
			Orc$String *  key = (Orc$String * )keys->get(keys, i) ;
			URGC_VAR_CLEANUP_CLASS Object*  value = (value=NULL,urgc_init_var_class((void**)&value, map->get(map, key->str) ));
			URGC_VAR_CLEANUP_CLASS Json$Json*  valueJson = self->serializeObject((valueJson = NULL,&valueJson), self, value) ;
			mapJson->put(mapJson, key->str, valueJson) ;
		}
		return urgc_set_var_for_return_class((void ** )__outRef__, mapJson) ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  json = Json$Json_mkObject((json = NULL,&json)) ;
	const char *  className = Object_getClassName(obj) ;
	json->putCstr(json, "__class", className) ;
	Vtable_Object *  vt = orc_getVtableByObject(obj) ;
	OrcMetaField *  mf = orc_getOrInitMeta(vt) ;
	self->serializeFields(self, json, obj, mf) ;
	Vtable_Object *  superVt = Vtable_getSuper(vt) ;
	while (superVt) {
		OrcMetaField *  superMf = orc_getOrInitMeta(superVt) ;
		self->serializeFields(self, json, obj, superMf) ;
		superVt = Vtable_getSuper(superVt) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, json) ; 
}


Json$Json*  SuiDesigner$ReflectionSerializer$serializePrimitiveValue(Json$Json **  __outRef__, SuiDesigner$ReflectionSerializer *  self, void *  ptr, OrcMetaType type){
	if (!ptr) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNull(&tmpReturn_1) ) ; 
	}
	if (type == OrcMetaType_bool) {
		bool *  pv = (bool * )ptr;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkBool(&tmpReturn_2, *pv) ) ; 
	}
	else if (type == OrcMetaType_char) {
		char *  pv = (char * )ptr;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_3 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNumber(&tmpReturn_3, (double )*pv) ) ; 
	}
	else if (type == OrcMetaType_short) {
		short *  pv = (short * )ptr;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_4 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNumber(&tmpReturn_4, (double )*pv) ) ; 
	}
	else if (type == OrcMetaType_int) {
		int *  pv = (int * )ptr;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_5 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNumber(&tmpReturn_5, (double )*pv) ) ; 
	}
	else if (type == OrcMetaType_long) {
		long *  pv = (long * )ptr;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_6 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNumber(&tmpReturn_6, (double )*pv) ) ; 
	}
	else if (type == OrcMetaType_long_long) {
		long long *  pv = (long long * )ptr;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_7 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNumber(&tmpReturn_7, (double )*pv) ) ; 
	}
	else if (type == OrcMetaType_float) {
		float *  pv = (float * )ptr;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_8 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNumber(&tmpReturn_8, (double )*pv) ) ; 
	}
	else if (type == OrcMetaType_double) {
		double *  pv = (double * )ptr;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_9 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNumber(&tmpReturn_9, *pv) ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_10 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNull(&tmpReturn_10) ) ; 
}


bool  SuiDesigner$ReflectionSerializer$shouldSerializeField(SuiDesigner$ReflectionSerializer *  self, Object*  obj, const char *  fieldName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(obj);

	if (!obj || !fieldName) {
		return false; 
	}
	if (fieldName[0] == '_') {
		return false; 
	}
	Vtable_Object *  vt = orc_getVtableByObject(obj) ;
	if (vt) {
		
	}
	return true; 
}


void  SuiDesigner$ReflectionSerializer$serializeFields(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, Object*  obj, OrcMetaField *  mf){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(obj);

	if (!json || !obj || !mf) {
		return ; 
	}
	OrcMetaField *  cur = mf;
	while (cur) {
		const char *  fieldName = OrcMetaField_getName(cur) ;
		if (self->shouldSerializeField(self, obj, fieldName) ) {
			self->serializeField(self, json, obj, cur, fieldName) ;
		}
		cur = OrcMetaField_getNext(cur) ;
	}
}


void  SuiDesigner$ReflectionSerializer$serializeField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, Object*  obj, OrcMetaField *  mf, const char *  fieldName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(obj);

	if (!json || !obj || !mf || !fieldName) {
		return ; 
	}
	OrcMetaType type = (OrcMetaType)OrcMetaField_getType(mf) ;
	void *  fieldPtr = OrcMetaField_getPtr(mf, obj) ;
	if (OrcMetaField_isPrimitive(mf) ) {
		self->serializePrimitiveField(self, json, fieldPtr, mf, fieldName, type) ;
	}
	else if (type == OrcMetaType_class) {
		if (mf->classVtable && strcmp(mf->classVtable->className, "List")  == 0) {
			self->serializeListField(self, json, fieldPtr, mf, fieldName) ;
		}
		else {
			self->serializeClassField(self, json, fieldPtr, mf, fieldName) ;
		}
	}
	else if (type == OrcMetaType_struct) {
		self->serializeStructField(self, json, fieldPtr, mf, fieldName) ;
	}
}


void  SuiDesigner$ReflectionSerializer$serializePrimitiveField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName, OrcMetaType type){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);

	if (!json || !fieldPtr || !fieldName) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  value = self->serializePrimitiveValue((value = NULL,&value), self, fieldPtr, type) ;
	json->put(json, fieldName, value) ;
}


void  SuiDesigner$ReflectionSerializer$serializeListField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);

	if (!json || !fieldPtr || !fieldName) {
		return ; 
	}
	if (mf->isRef || mf->isPointer) {
		Orc$List **  listPtr = (Orc$List ** )fieldPtr;
		Orc$List *  list = *listPtr;
		if (list) {
			URGC_VAR_CLEANUP_CLASS Json$Json*  listJson = Json$Json_mkArray((listJson = NULL,&listJson)) ;
			int  size = list->size(list) ;
			for (int  i = 0; i < size; i++) {
				URGC_VAR_CLEANUP_CLASS Object*  item = (item=NULL,urgc_init_var_class((void**)&item, list->get(list, i) ));
				if (item) {
					URGC_VAR_CLEANUP_CLASS Json$Json*  itemJson = self->serializeObject((itemJson = NULL,&itemJson), self, item) ;
					listJson->add(listJson, itemJson) ;
				}
				else {
					URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
					listJson->add(listJson, Json$Json_mkNull(&tmpReturn_1) ) ;
				}
			}
			json->put(json, fieldName, listJson) ;
		}
		else {
			URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
			json->put(json, fieldName, Json$Json_mkNull(&tmpReturn_2) ) ;
		}
	}
}


void  SuiDesigner$ReflectionSerializer$serializeClassField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);

	if (!json || !fieldPtr || !fieldName) {
		return ; 
	}
	if (mf->isRef || mf->isPointer) {
		Object **  objPtr = (Object ** )fieldPtr;
		URGC_VAR_CLEANUP_CLASS Object*  childObj = (childObj=NULL,urgc_init_var_class((void**)&childObj, *objPtr));
		if (childObj) {
			URGC_VAR_CLEANUP_CLASS Json$Json*  childJson = self->serializeObject((childJson = NULL,&childJson), self, childObj) ;
			json->put(json, fieldName, childJson) ;
		}
		else {
			URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
			json->put(json, fieldName, Json$Json_mkNull(&tmpReturn_1) ) ;
		}
	}
}


void  SuiDesigner$ReflectionSerializer$serializeStructField(SuiDesigner$ReflectionSerializer *  self, Json$Json*  json, void *  fieldPtr, OrcMetaField *  mf, const char *  fieldName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);

	if (!json || !fieldPtr || !fieldName || !mf->metaStruct) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  structJson = Json$Json_mkObject((structJson = NULL,&structJson)) ;
	OrcMetaField *  structMf = mf->metaStruct->headMetaField;
	while (structMf) {
		const char *  structFieldName = OrcMetaField_getName(structMf) ;
		if (structFieldName) {
			void *  structFieldPtr = (void * )((char * )fieldPtr + OrcMetaField_getAddress(structMf) );
			OrcMetaType structFieldType = (OrcMetaType)OrcMetaField_getType(structMf) ;
			if (OrcMetaField_isPrimitive(structMf) ) {
				self->serializePrimitiveField(self, structJson, structFieldPtr, structMf, structFieldName, structFieldType) ;
			}
			else if (structFieldType == OrcMetaType_struct) {
				self->serializeStructField(self, structJson, structFieldPtr, structMf, structFieldName) ;
			}
			else if (structFieldType == OrcMetaType_class) {
				self->serializeClassField(self, structJson, structFieldPtr, structMf, structFieldName) ;
			}
		}
		structMf = OrcMetaField_getNext(structMf) ;
	}
	json->put(json, fieldName, structJson) ;
}


Json$Json*  SuiDesigner$ReflectionSerializer$serializeSceneWithChildren(Json$Json **  __outRef__, SuiDesigner$ReflectionSerializer *  self, Sgl$Scene*  scene){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(scene);

	if (!scene) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNull(&tmpReturn_1) ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  sceneJson = self->serializeObject((sceneJson = NULL,&sceneJson), self, (Object* )scene) ;
	if (scene->firstChild) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  childrenJson = Json$Json_mkArray((childrenJson = NULL,&childrenJson)) ;
		self->serializeNodeChildren(self, childrenJson, (SuiCore$Node* )scene) ;
		sceneJson->put(sceneJson, "children", childrenJson) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, sceneJson) ; 
}


void  SuiDesigner$ReflectionSerializer$serializeNodeChildren(SuiDesigner$ReflectionSerializer *  self, Json$Json*  childrenArray, SuiCore$Node*  parent){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(childrenArray);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(parent);

	if (!parent || !childrenArray) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  child = (child=NULL,urgc_init_var_class((void**)&child, parent->firstChild));
	while (child) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  childJson = NULL;
		if (Orc_instanceof((Object*)child, (Vtable_Object*)Vtable_Sgl$Scene_init(NULL))) {
			URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
			urgc_set_var_class(&childJson, self->serializeSceneWithChildren(&tmpReturn_1, self, (Sgl$Scene* )child) ) ;
		}
		else {
			URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
			urgc_set_var_class(&childJson, self->serializeObject(&tmpReturn_2, self, (Object* )child) ) ;
			if (child->firstChild) {
				URGC_VAR_CLEANUP_CLASS Json$Json*  grandChildrenJson = Json$Json_mkArray((grandChildrenJson = NULL,&grandChildrenJson)) ;
				self->serializeNodeChildren(self, grandChildrenJson, child) ;
				childJson->put(childJson, "children", grandChildrenJson) ;
			}
		}
		if (childJson) {
			childrenArray->add(childrenArray, childJson) ;
		}
		urgc_set_var_class(&child, child->next) ;
	}
}


bool  SuiDesigner$ReflectionSerializer$saveSceneToFile(SuiDesigner$ReflectionSerializer *  self, Sgl$Scene*  scene, const char *  filepath){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(scene);

	URGC_VAR_CLEANUP_CLASS Json$Json*  jsonObj = self->serializeSceneWithChildren((jsonObj = NULL,&jsonObj), self, scene) ;
	if (!jsonObj) {
		return false; 
	}
	jsonObj->dumpToFileByPathCstr(jsonObj, filepath) ;
	return true; 
}


Orc$String*  SuiDesigner$ReflectionSerializer$serializeSceneToString(Orc$String **  __outRef__, SuiDesigner$ReflectionSerializer *  self, Sgl$Scene*  scene){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(scene);

	URGC_VAR_CLEANUP_CLASS Json$Json*  jsonObj = self->serializeSceneWithChildren((jsonObj = NULL,&jsonObj), self, scene) ;
	if (!jsonObj) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, "{}") ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, jsonObj->dump(&tmpReturn_2, jsonObj) ) ; 
}




//vtable instance
Vtable_SuiDesigner$ReflectionDeserializer _vtable_SuiDesigner$ReflectionDeserializer;

// init meta

void SuiDesigner$ReflectionDeserializer_initMeta(Vtable_SuiDesigner$ReflectionDeserializer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "deserializeObject", offsetof(SuiDesigner$ReflectionDeserializer, deserializeObject));
	orc_metaField_method(&pNext, "deserializeFields", offsetof(SuiDesigner$ReflectionDeserializer, deserializeFields));
	orc_metaField_method(&pNext, "deserializeFieldsByMetaField", offsetof(SuiDesigner$ReflectionDeserializer, deserializeFieldsByMetaField));
	orc_metaField_method(&pNext, "deserializeField", offsetof(SuiDesigner$ReflectionDeserializer, deserializeField));
	orc_metaField_method(&pNext, "deserializePrimitiveField", offsetof(SuiDesigner$ReflectionDeserializer, deserializePrimitiveField));
	orc_metaField_method(&pNext, "deserializeClassField", offsetof(SuiDesigner$ReflectionDeserializer, deserializeClassField));
	orc_metaField_method(&pNext, "deserializeStructField", offsetof(SuiDesigner$ReflectionDeserializer, deserializeStructField));
	orc_metaField_method(&pNext, "deserializeSceneWithChildren", offsetof(SuiDesigner$ReflectionDeserializer, deserializeSceneWithChildren));
	orc_metaField_method(&pNext, "deserializeNodeChildren", offsetof(SuiDesigner$ReflectionDeserializer, deserializeNodeChildren));
	orc_metaField_method(&pNext, "loadSceneFromFile", offsetof(SuiDesigner$ReflectionDeserializer, loadSceneFromFile));
	orc_metaField_method(&pNext, "deserializeScene", offsetof(SuiDesigner$ReflectionDeserializer, deserializeScene));
}


// vtable init


Vtable_SuiDesigner$ReflectionDeserializer* Vtable_SuiDesigner$ReflectionDeserializer_init(Vtable_SuiDesigner$ReflectionDeserializer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ReflectionDeserializer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ReflectionDeserializer_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ReflectionDeserializer";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ReflectionDeserializer_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$ReflectionDeserializer_fini(SuiDesigner$ReflectionDeserializer *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$ReflectionDeserializer_init_fields(SuiDesigner$ReflectionDeserializer *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ReflectionDeserializer_fini;
	//fields
    {
	
    }
	((SuiDesigner$ReflectionDeserializer*)self)->deserializeObject = (void*)SuiDesigner$ReflectionDeserializer$deserializeObject;
	((SuiDesigner$ReflectionDeserializer*)self)->deserializeFields = (void*)SuiDesigner$ReflectionDeserializer$deserializeFields;
	((SuiDesigner$ReflectionDeserializer*)self)->deserializeFieldsByMetaField = (void*)SuiDesigner$ReflectionDeserializer$deserializeFieldsByMetaField;
	((SuiDesigner$ReflectionDeserializer*)self)->deserializeField = (void*)SuiDesigner$ReflectionDeserializer$deserializeField;
	((SuiDesigner$ReflectionDeserializer*)self)->deserializePrimitiveField = (void*)SuiDesigner$ReflectionDeserializer$deserializePrimitiveField;
	((SuiDesigner$ReflectionDeserializer*)self)->deserializeClassField = (void*)SuiDesigner$ReflectionDeserializer$deserializeClassField;
	((SuiDesigner$ReflectionDeserializer*)self)->deserializeStructField = (void*)SuiDesigner$ReflectionDeserializer$deserializeStructField;
	((SuiDesigner$ReflectionDeserializer*)self)->deserializeSceneWithChildren = (void*)SuiDesigner$ReflectionDeserializer$deserializeSceneWithChildren;
	((SuiDesigner$ReflectionDeserializer*)self)->deserializeNodeChildren = (void*)SuiDesigner$ReflectionDeserializer$deserializeNodeChildren;
	((SuiDesigner$ReflectionDeserializer*)self)->loadSceneFromFile = (void*)SuiDesigner$ReflectionDeserializer$loadSceneFromFile;
	((SuiDesigner$ReflectionDeserializer*)self)->deserializeScene = (void*)SuiDesigner$ReflectionDeserializer$deserializeScene;
}

// init function

void SuiDesigner$ReflectionDeserializer_init(SuiDesigner$ReflectionDeserializer *self, void *pOwner){
    Vtable_SuiDesigner$ReflectionDeserializer_init(&_vtable_SuiDesigner$ReflectionDeserializer);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ReflectionDeserializer;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ReflectionDeserializer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ReflectionDeserializer * SuiDesigner$ReflectionDeserializer_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ReflectionDeserializer *self = calloc(1, sizeof(SuiDesigner$ReflectionDeserializer));
	
    SuiDesigner$ReflectionDeserializer_init(self, pOwner);
    return self;
}


// class members
Object*  SuiDesigner$ReflectionDeserializer$deserializeObject(Object **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);

	if (!json) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	if (json->isArray(json) ) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  list = (list=NULL,urgc_init_var_class((void**)&list, Orc$List_new(&list) ));
		int  arraySize = json->arraySize(json) ;
		for (int  i = 0; i < arraySize; i++) {
			URGC_VAR_CLEANUP_CLASS Json$Json*  itemJson = json->at((itemJson = NULL,&itemJson), json, i) ;
			if (itemJson && !itemJson->isNull(itemJson) ) {
				URGC_VAR_CLEANUP_CLASS Object*  item = self->deserializeObject((item = NULL,&item), self, itemJson) ;
				if (item) {
					list->add(list, item) ;
				}
			}
		}
		return urgc_set_var_for_return_class((void ** )__outRef__, (Object* )list) ; 
	}
	if (!json->isObject(json) ) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  className = json->getString((className = NULL,&className), json, "__class") ;
	if (!className) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	Vtable_Object *  vt = SuiDesigner$BiJson_findClass(className->str) ;
	if (!vt) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	URGC_VAR_CLEANUP_CLASS Object*  obj = NULL;
	vt->make(&obj) ;
	if (!obj) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	self->deserializeFields(self, json, obj, vt) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
}


void  SuiDesigner$ReflectionDeserializer$deserializeFields(SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json, Object*  obj, Vtable_Object *  vt){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(obj);

	if (!json || !obj || !vt) {
		return ; 
	}
	OrcMetaField *  mf = orc_getOrInitMeta(vt) ;
	self->deserializeFieldsByMetaField(self, json, obj, mf) ;
	Vtable_Object *  superVt = Vtable_getSuper(vt) ;
	while (superVt) {
		OrcMetaField *  superMf = orc_getOrInitMeta(superVt) ;
		self->deserializeFieldsByMetaField(self, json, obj, superMf) ;
		superVt = Vtable_getSuper(superVt) ;
	}
}


void  SuiDesigner$ReflectionDeserializer$deserializeFieldsByMetaField(SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json, Object*  obj, OrcMetaField *  mf){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(obj);

	if (!json || !obj || !mf) {
		return ; 
	}
	OrcMetaField *  cur = mf;
	while (cur) {
		const char *  fieldName = OrcMetaField_getName(cur) ;
		if (fieldName && strcmp(fieldName, "ctor")  != 0 && strcmp(fieldName, "dtor")  != 0) {
			if (json->hasKey(json, fieldName) ) {
				URGC_VAR_CLEANUP_CLASS Json$Json*  fieldJson = json->get((fieldJson = NULL,&fieldJson), json, fieldName) ;
				if (fieldJson) {
					self->deserializeField(self, obj, cur, fieldName, fieldJson) ;
				}
			}
		}
		cur = OrcMetaField_getNext(cur) ;
	}
}


void  SuiDesigner$ReflectionDeserializer$deserializeField(SuiDesigner$ReflectionDeserializer *  self, Object*  obj, OrcMetaField *  mf, const char *  fieldName, Json$Json*  fieldJson){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(obj);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fieldJson);

	if (!obj || !mf || !fieldName || !fieldJson) {
		return ; 
	}
	OrcMetaType type = (OrcMetaType)OrcMetaField_getType(mf) ;
	void *  fieldPtr = OrcMetaField_getPtr(mf, obj) ;
	if (OrcMetaField_isPrimitive(mf) ) {
		self->deserializePrimitiveField(self, fieldPtr, mf, type, fieldJson) ;
	}
	else if (type == OrcMetaType_class) {
		if (mf->classVtable && strcmp(mf->classVtable->className, "List")  == 0) {
			
		}
		else {
			
		}
	}
	else if (type == OrcMetaType_struct) {
		self->deserializeStructField(self, fieldPtr, mf, fieldJson) ;
	}
}


void  SuiDesigner$ReflectionDeserializer$deserializePrimitiveField(SuiDesigner$ReflectionDeserializer *  self, void *  fieldPtr, OrcMetaField *  mf, OrcMetaType type, Json$Json*  fieldJson){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fieldJson);

	if (!fieldPtr || !fieldJson) {
		return ; 
	}
	if (type == OrcMetaType_bool) {
		bool *  pv = (bool * )fieldPtr * pv = fieldJson->asBool(fieldJson) ;
	}
	else if (type == OrcMetaType_char) {
		char *  pv = (char * )fieldPtr * pv = (char )fieldJson->asInt(fieldJson) ;
	}
	else if (type == OrcMetaType_short) {
		short *  pv = (short * )fieldPtr * pv = (short )fieldJson->asInt(fieldJson) ;
	}
	else if (type == OrcMetaType_int) {
		int *  pv = (int * )fieldPtr * pv = fieldJson->asInt(fieldJson) ;
	}
	else if (type == OrcMetaType_long) {
		long *  pv = (long * )fieldPtr * pv = (long )fieldJson->asNumber(fieldJson) ;
	}
	else if (type == OrcMetaType_long_long) {
		long long *  pv = (long long * )fieldPtr * pv = (long long )fieldJson->asNumber(fieldJson) ;
	}
	else if (type == OrcMetaType_float) {
		float *  pv = (float * )fieldPtr * pv = (float )fieldJson->asNumber(fieldJson) ;
	}
	else if (type == OrcMetaType_double) {
		double *  pv = (double * )fieldPtr * pv = fieldJson->asNumber(fieldJson) ;
	}
}


void  SuiDesigner$ReflectionDeserializer$deserializeClassField(SuiDesigner$ReflectionDeserializer *  self, void *  fieldPtr, OrcMetaField *  mf, Json$Json*  fieldJson){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fieldJson);

	if (!fieldPtr || !mf || !fieldJson) {
		return ; 
	}
	if (mf->isRef || mf->isPointer) {
		if (fieldJson->isNull(fieldJson) ) {
			return ; 
		}
		Object **  objPtr = (Object ** )fieldPtr;
		URGC_VAR_CLEANUP_CLASS Object*  childObj = self->deserializeObject((childObj = NULL,&childObj), self, fieldJson) ;
		if (childObj) {
			*objPtr = childObj;
		}
	}
}


void  SuiDesigner$ReflectionDeserializer$deserializeStructField(SuiDesigner$ReflectionDeserializer *  self, void *  fieldPtr, OrcMetaField *  mf, Json$Json*  fieldJson){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fieldJson);

	if (!fieldPtr || !mf || !fieldJson || !fieldJson->isObject(fieldJson)  || !mf->metaStruct) {
		return ; 
	}
	OrcMetaField *  structMf = mf->metaStruct->headMetaField;
	while (structMf) {
		const char *  structFieldName = OrcMetaField_getName(structMf) ;
		if (structFieldName && fieldJson->hasKey(fieldJson, structFieldName) ) {
			URGC_VAR_CLEANUP_CLASS Json$Json*  structFieldJson = fieldJson->get((structFieldJson = NULL,&structFieldJson), fieldJson, structFieldName) ;
			if (structFieldJson) {
				void *  structFieldPtr = (void * )((char * )fieldPtr + OrcMetaField_getAddress(structMf) );
				OrcMetaType structFieldType = (OrcMetaType)OrcMetaField_getType(structMf) ;
				if (OrcMetaField_isPrimitive(structMf) ) {
					self->deserializePrimitiveField(self, structFieldPtr, structMf, structFieldType, structFieldJson) ;
				}
			}
		}
		structMf = OrcMetaField_getNext(structMf) ;
	}
}


Sgl$Scene*  SuiDesigner$ReflectionDeserializer$deserializeSceneWithChildren(Sgl$Scene **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, Json$Json*  json){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(json);

	if (!json) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	URGC_VAR_CLEANUP_CLASS Object*  obj = self->deserializeObject((obj = NULL,&obj), self, json) ;
	if (!obj || !(Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Sgl$Scene_init(NULL)))) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	Sgl$Scene *  scene = (Sgl$Scene * )obj;
	URGC_VAR_CLEANUP_CLASS Json$Json*  childrenJson = json->get((childrenJson = NULL,&childrenJson), json, "children") ;
	if (childrenJson && childrenJson->isArray(childrenJson) ) {
		self->deserializeNodeChildren(self, (SuiCore$Node* )scene, childrenJson) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, scene) ; 
}


void  SuiDesigner$ReflectionDeserializer$deserializeNodeChildren(SuiDesigner$ReflectionDeserializer *  self, SuiCore$Node*  parent, Json$Json*  childrenArray){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(parent);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(childrenArray);

	if (!parent || !childrenArray || !childrenArray->isArray(childrenArray) ) {
		return ; 
	}
	int  arraySize = childrenArray->arraySize(childrenArray) ;
	for (int  i = 0; i < arraySize; i++) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  childJson = childrenArray->at((childJson = NULL,&childJson), childrenArray, i) ;
		if (childJson) {
			URGC_VAR_CLEANUP_CLASS Object*  childObj = self->deserializeObject((childObj = NULL,&childObj), self, childJson) ;
			if (childObj && Orc_instanceof((Object*)childObj, (Vtable_Object*)Vtable_SuiCore$Node_init(NULL))) {
				SuiCore$Node *  childNode = (SuiCore$Node * )childObj;
				parent->appendChild(parent, childNode) ;
				URGC_VAR_CLEANUP_CLASS Json$Json*  grandChildrenJson = childJson->get((grandChildrenJson = NULL,&grandChildrenJson), childJson, "children") ;
				if (grandChildrenJson && grandChildrenJson->isArray(grandChildrenJson) ) {
					self->deserializeNodeChildren(self, childNode, grandChildrenJson) ;
				}
			}
		}
	}
}


Sgl$Scene*  SuiDesigner$ReflectionDeserializer$loadSceneFromFile(Sgl$Scene **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, const char *  filepath){
	URGC_VAR_CLEANUP_CLASS Json$Json*  json = Json$Json_parseByPathCstr((json = NULL,&json), filepath) ;
	if (!json) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, self->deserializeSceneWithChildren(&tmpReturn_1, self, json) ) ; 
}


Sgl$Scene*  SuiDesigner$ReflectionDeserializer$deserializeScene(Sgl$Scene **  __outRef__, SuiDesigner$ReflectionDeserializer *  self, const char *  jsonString){
	if (!jsonString) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  json = Json$Json_parse((json = NULL,&json), jsonString) ;
	if (!json) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, self->deserializeSceneWithChildren(&tmpReturn_1, self, json) ) ; 
}



SuiDesigner$ReflectionSerializer SuiDesigner$reflectionSerializer;
SuiDesigner$ReflectionDeserializer SuiDesigner$reflectionDeserializer;
void  SuiDesigner$registerSglClasses(){
	SuiDesigner$BiJson_registerClass(Vtable_Sgl$Scene_init(NULL)) ;
	SuiDesigner$BiJson_registerClass(Vtable_Sgl$Obj3d_init(NULL)) ;
	SuiDesigner$BiJson_registerClass(Vtable_Sgl$Mesh_init(NULL)) ;
	SuiDesigner$BiJson_registerClass(Vtable_Sgl$Camera_init(NULL)) ;
	SuiDesigner$BiJson_registerClass(Vtable_Sgl$PerspectiveCamera_init(NULL)) ;
	SuiDesigner$BiJson_registerClass(Vtable_Sgl$Light_init(NULL)) ;
	SuiDesigner$BiJson_registerClass(Vtable_Sgl$PointLight_init(NULL)) ;
	SuiDesigner$BiJson_registerClass(Vtable_Sgl$DirLight_init(NULL)) ;
	SuiDesigner$BiJson_registerClass(Vtable_Sgl$SpotLight_init(NULL)) ;
}

Orc$String*  SuiDesigner$serializeSceneToString(Orc$String **  __outRef__, Sgl$Scene*  scene){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(scene);

	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, SuiDesigner$reflectionSerializer.serializeSceneToString(&tmpReturn_1, SuiDesigner$reflectionSerializer, scene) ) ; 
}

bool  SuiDesigner$saveSceneToFile(Sgl$Scene*  scene, const char *  filepath){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(scene);

	return SuiDesigner$reflectionSerializer.saveSceneToFile(SuiDesigner$reflectionSerializer, scene, filepath) ; 
}

Sgl$Scene*  SuiDesigner$loadSceneFromFile(Sgl$Scene **  __outRef__, const char *  filepath){
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, SuiDesigner$reflectionDeserializer.loadSceneFromFile(&tmpReturn_1, SuiDesigner$reflectionDeserializer, filepath) ) ; 
}

Sgl$Scene*  SuiDesigner$deserializeSceneFromString(Sgl$Scene **  __outRef__, const char *  jsonString){
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, SuiDesigner$reflectionDeserializer.deserializeScene(&tmpReturn_1, SuiDesigner$reflectionDeserializer, jsonString) ) ; 
}



