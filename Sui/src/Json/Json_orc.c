
#include "Json_orc.h" 

#include "./cJSON.h"
#include "../Orc/Orc.h"
#include <stdio.h>
#include <string.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Json$Json _vtable_Json$Json;

// init meta

void Json$Json_initMeta(Vtable_Json$Json *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "kind", OrcMetaType_int, offsetof(Json$Json, kind), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "boolValue", OrcMetaType_bool, offsetof(Json$Json, boolValue), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "numberValue", OrcMetaType_double, offsetof(Json$Json, numberValue), 0, 0, 0, 0);//double
	orc_metaField_class(&pNext, "stringValue", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Json$Json, stringValue), true, false, 1);
	orc_metaField_class(&pNext, "list", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Json$Json, list), true, false, 1);
	orc_metaField_class(&pNext, "map", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(Json$Json, map), true, false, 1);

	orc_metaField_method(&pNext, "dump", offsetof(Json$Json, dump));
	orc_metaField_method(&pNext, "dumpToFileByPathCstr", offsetof(Json$Json, dumpToFileByPathCstr));
	orc_metaField_method(&pNext, "toString", offsetof(Json$Json, toString));
	orc_metaField_method(&pNext, "setNull", offsetof(Json$Json, setNull));
	orc_metaField_method(&pNext, "isBool", offsetof(Json$Json, isBool));
	orc_metaField_method(&pNext, "isNumber", offsetof(Json$Json, isNumber));
	orc_metaField_method(&pNext, "isString", offsetof(Json$Json, isString));
	orc_metaField_method(&pNext, "isObject", offsetof(Json$Json, isObject));
	orc_metaField_method(&pNext, "isArray", offsetof(Json$Json, isArray));
	orc_metaField_method(&pNext, "isNull", offsetof(Json$Json, isNull));
	orc_metaField_method(&pNext, "asString", offsetof(Json$Json, asString));
	orc_metaField_method(&pNext, "asBool", offsetof(Json$Json, asBool));
	orc_metaField_method(&pNext, "asInt", offsetof(Json$Json, asInt));
	orc_metaField_method(&pNext, "asNumber", offsetof(Json$Json, asNumber));
	orc_metaField_method(&pNext, "size", offsetof(Json$Json, size));
	orc_metaField_method(&pNext, "arraySize", offsetof(Json$Json, arraySize));
	orc_metaField_method(&pNext, "keySize", offsetof(Json$Json, keySize));
	orc_metaField_method(&pNext, "keys", offsetof(Json$Json, keys));
	orc_metaField_method(&pNext, "atAsInt", offsetof(Json$Json, atAsInt));
	orc_metaField_method(&pNext, "atAsNumber", offsetof(Json$Json, atAsNumber));
	orc_metaField_method(&pNext, "atAsBool", offsetof(Json$Json, atAsBool));
	orc_metaField_method(&pNext, "atAsString", offsetof(Json$Json, atAsString));
	orc_metaField_method(&pNext, "at", offsetof(Json$Json, at));
	orc_metaField_method(&pNext, "hasKey", offsetof(Json$Json, hasKey));
	orc_metaField_method(&pNext, "get", offsetof(Json$Json, get));
	orc_metaField_method(&pNext, "getInt", offsetof(Json$Json, getInt));
	orc_metaField_method(&pNext, "getNumber", offsetof(Json$Json, getNumber));
	orc_metaField_method(&pNext, "getToBool", offsetof(Json$Json, getToBool));
	orc_metaField_method(&pNext, "getToInt", offsetof(Json$Json, getToInt));
	orc_metaField_method(&pNext, "getToFloat", offsetof(Json$Json, getToFloat));
	orc_metaField_method(&pNext, "getBool", offsetof(Json$Json, getBool));
	orc_metaField_method(&pNext, "getString", offsetof(Json$Json, getString));
	orc_metaField_method(&pNext, "getToInts", offsetof(Json$Json, getToInts));
	orc_metaField_method(&pNext, "getToFloats", offsetof(Json$Json, getToFloats));
	orc_metaField_method(&pNext, "getToStruct", offsetof(Json$Json, getToStruct));
	orc_metaField_method(&pNext, "setNumber", offsetof(Json$Json, setNumber));
	orc_metaField_method(&pNext, "setBool", offsetof(Json$Json, setBool));
	orc_metaField_method(&pNext, "setString", offsetof(Json$Json, setString));
	orc_metaField_method(&pNext, "setCstr", offsetof(Json$Json, setCstr));
	orc_metaField_method(&pNext, "initList", offsetof(Json$Json, initList));
	orc_metaField_method(&pNext, "initMap", offsetof(Json$Json, initMap));
	orc_metaField_method(&pNext, "add", offsetof(Json$Json, add));
	orc_metaField_method(&pNext, "addNumber", offsetof(Json$Json, addNumber));
	orc_metaField_method(&pNext, "addBool", offsetof(Json$Json, addBool));
	orc_metaField_method(&pNext, "addString", offsetof(Json$Json, addString));
	orc_metaField_method(&pNext, "putNumber", offsetof(Json$Json, putNumber));
	orc_metaField_method(&pNext, "putBool", offsetof(Json$Json, putBool));
	orc_metaField_method(&pNext, "putString", offsetof(Json$Json, putString));
	orc_metaField_method(&pNext, "putCstr", offsetof(Json$Json, putCstr));
	orc_metaField_method(&pNext, "put", offsetof(Json$Json, put));
	orc_metaField_method(&pNext, "putObject", offsetof(Json$Json, putObject));
	orc_metaField_method(&pNext, "mergeToSelf", offsetof(Json$Json, mergeToSelf));
	orc_metaField_method(&pNext, "toObject", offsetof(Json$Json, toObject));
	orc_metaField_method(&pNext, "toObjectByVtables", offsetof(Json$Json, toObjectByVtables));
	orc_metaField_method(&pNext, "toObjectByVtable", offsetof(Json$Json, toObjectByVtable));
	orc_metaField_method(&pNext, "getObjectsByVtable", offsetof(Json$Json, getObjectsByVtable));
	orc_metaField_method(&pNext, "toObjectsByVtable", offsetof(Json$Json, toObjectsByVtable));
	orc_metaField_method(&pNext, "toInts", offsetof(Json$Json, toInts));
	orc_metaField_method(&pNext, "toFloats", offsetof(Json$Json, toFloats));
}


// vtable init


Vtable_Json$Json* Vtable_Json$Json_init(Vtable_Json$Json* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Json$Json;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Json$Json_new;
    ((Vtable_Object*)pvt)->className = "Json$Json";

    ((Vtable_Object*)pvt)->initMeta = (void*)Json$Json_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Json$Json_fini(Json$Json *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Json$Json*)self)->stringValue);
	urgc_fini_field_class(self, (void**)&((Json$Json*)self)->list);
	urgc_fini_field_class(self, (void**)&((Json$Json*)self)->map);

}

// init fields function


void Json$Json_init_fields(Json$Json *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Json$Json_fini;
	//fields
    {
	((Json$Json*)self)->kind = 0;
	urgc_set_field_class(self, (void**)&((Json$Json*)self)->stringValue, NULL);
	urgc_set_field_class(self, (void**)&((Json$Json*)self)->list, NULL);
	urgc_set_field_class(self, (void**)&((Json$Json*)self)->map, NULL);
    }
	((Object*)self)->dtor = (void*)Json$Json$dtor;
	((Json$Json*)self)->dump = (void*)Json$Json$dump;
	((Json$Json*)self)->dumpToFileByPathCstr = (void*)Json$Json$dumpToFileByPathCstr;
	((Json$Json*)self)->toString = (void*)Json$Json$toString;
	((Json$Json*)self)->setNull = (void*)Json$Json$setNull;
	((Json$Json*)self)->isBool = (void*)Json$Json$isBool;
	((Json$Json*)self)->isNumber = (void*)Json$Json$isNumber;
	((Json$Json*)self)->isString = (void*)Json$Json$isString;
	((Json$Json*)self)->isObject = (void*)Json$Json$isObject;
	((Json$Json*)self)->isArray = (void*)Json$Json$isArray;
	((Json$Json*)self)->isNull = (void*)Json$Json$isNull;
	((Json$Json*)self)->asString = (void*)Json$Json$asString;
	((Json$Json*)self)->asBool = (void*)Json$Json$asBool;
	((Json$Json*)self)->asInt = (void*)Json$Json$asInt;
	((Json$Json*)self)->asNumber = (void*)Json$Json$asNumber;
	((Json$Json*)self)->size = (void*)Json$Json$size;
	((Json$Json*)self)->arraySize = (void*)Json$Json$arraySize;
	((Json$Json*)self)->keySize = (void*)Json$Json$keySize;
	((Json$Json*)self)->keys = (void*)Json$Json$keys;
	((Json$Json*)self)->atAsInt = (void*)Json$Json$atAsInt;
	((Json$Json*)self)->atAsNumber = (void*)Json$Json$atAsNumber;
	((Json$Json*)self)->atAsBool = (void*)Json$Json$atAsBool;
	((Json$Json*)self)->atAsString = (void*)Json$Json$atAsString;
	((Json$Json*)self)->at = (void*)Json$Json$at;
	((Json$Json*)self)->hasKey = (void*)Json$Json$hasKey;
	((Json$Json*)self)->get = (void*)Json$Json$get;
	((Json$Json*)self)->getInt = (void*)Json$Json$getInt;
	((Json$Json*)self)->getNumber = (void*)Json$Json$getNumber;
	((Json$Json*)self)->getToBool = (void*)Json$Json$getToBool;
	((Json$Json*)self)->getToInt = (void*)Json$Json$getToInt;
	((Json$Json*)self)->getToFloat = (void*)Json$Json$getToFloat;
	((Json$Json*)self)->getBool = (void*)Json$Json$getBool;
	((Json$Json*)self)->getString = (void*)Json$Json$getString;
	((Json$Json*)self)->getToInts = (void*)Json$Json$getToInts;
	((Json$Json*)self)->getToFloats = (void*)Json$Json$getToFloats;
	((Json$Json*)self)->getToStruct = (void*)Json$Json$getToStruct;
	((Json$Json*)self)->setNumber = (void*)Json$Json$setNumber;
	((Json$Json*)self)->setBool = (void*)Json$Json$setBool;
	((Json$Json*)self)->setString = (void*)Json$Json$setString;
	((Json$Json*)self)->setCstr = (void*)Json$Json$setCstr;
	((Json$Json*)self)->initList = (void*)Json$Json$initList;
	((Json$Json*)self)->initMap = (void*)Json$Json$initMap;
	((Json$Json*)self)->add = (void*)Json$Json$add;
	((Json$Json*)self)->addNumber = (void*)Json$Json$addNumber;
	((Json$Json*)self)->addBool = (void*)Json$Json$addBool;
	((Json$Json*)self)->addString = (void*)Json$Json$addString;
	((Json$Json*)self)->putNumber = (void*)Json$Json$putNumber;
	((Json$Json*)self)->putBool = (void*)Json$Json$putBool;
	((Json$Json*)self)->putString = (void*)Json$Json$putString;
	((Json$Json*)self)->putCstr = (void*)Json$Json$putCstr;
	((Json$Json*)self)->put = (void*)Json$Json$put;
	((Json$Json*)self)->putObject = (void*)Json$Json$putObject;
	((Json$Json*)self)->mergeToSelf = (void*)Json$Json$mergeToSelf;
	((Json$Json*)self)->toObject = (void*)Json$Json$toObject;
	((Json$Json*)self)->toObjectByVtables = (void*)Json$Json$toObjectByVtables;
	((Json$Json*)self)->toObjectByVtable = (void*)Json$Json$toObjectByVtable;
	((Json$Json*)self)->getObjectsByVtable = (void*)Json$Json$getObjectsByVtable;
	((Json$Json*)self)->toObjectsByVtable = (void*)Json$Json$toObjectsByVtable;
	((Json$Json*)self)->toInts = (void*)Json$Json$toInts;
	((Json$Json*)self)->toFloats = (void*)Json$Json$toFloats;
}

// init function

void Json$Json_init(Json$Json *self, void *pOwner){
    Vtable_Json$Json_init(&_vtable_Json$Json);

    ((Object*)self)->vtable = (void*)&_vtable_Json$Json;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Json$Json_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Json$Json * Json$Json_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Json$Json *self = calloc(1, sizeof(Json$Json));
	
    Json$Json_init(self, pOwner);
    return self;
}


// class members
void  Json$Json$dtor(Json$Json *  self){
	
}


void  Json$Json$dumpToFileByPathCstr(Json$Json *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Orc$String*  text = self->dump((text = NULL,&text), self) ;
	Orc$Path_writeText(path, text->str) ;
}


Orc$String*  Json$Json$toString(Orc$String **  __outRef__, Json$Json *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, self->dump(&tmpReturn_1, self) ) ; 
}


void  Json$Json$setNull(Json$Json *  self){
	self->kind = 0;
}


bool  Json$Json$isBool(Json$Json *  self){
	return self->kind == 1; 
}


bool  Json$Json$isNumber(Json$Json *  self){
	return self->kind == 2; 
}


bool  Json$Json$isString(Json$Json *  self){
	return self->kind == 3; 
}


bool  Json$Json$isObject(Json$Json *  self){
	return self->kind == 4; 
}


bool  Json$Json$isArray(Json$Json *  self){
	return self->kind == 5; 
}


bool  Json$Json$isNull(Json$Json *  self){
	if (self->kind == 0) {
		return true; 
	}
	if (self->kind == 4 && !self->map) {
		return true; 
	}
	if (self->kind == 5 && !self->list) {
		return true; 
	}
	return false; 
}


Orc$String*  Json$Json$asString(Orc$String **  __outRef__, Json$Json *  self){
	if (self->kind == 1) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, self->boolValue ? "true" : "false") ) ; 
	}
	if (self->kind == 2) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$addDouble(Orc$str(&tmpReturn_2, "") , self->numberValue) ) ; 
	}
	if (self->kind == 3) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, self->stringValue ? self->stringValue : Orc$str(&tmpReturn_3, "") ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_4, "") ) ; 
}


bool  Json$Json$asBool(Json$Json *  self){
	if (self->kind == 0) {
		return false; 
	}
	if (self->kind == 1) {
		return self->boolValue; 
	}
	if (self->kind == 2) {
		return self->numberValue ? true : false; 
	}
	return false; 
}


int  Json$Json$asInt(Json$Json *  self){
	if (self->kind == 0) {
		return 0; 
	}
	if (self->kind == 1) {
		return self->boolValue ? 1 : 0; 
	}
	if (self->kind == 2) {
		return (int )self->numberValue; 
	}
	return 0; 
}


double  Json$Json$asNumber(Json$Json *  self){
	if (self->kind == 0) {
		return 0; 
	}
	if (self->kind == 1) {
		return self->boolValue ? 1 : 0; 
	}
	if (self->kind == 2) {
		return self->numberValue; 
	}
	return 0; 
}


int  Json$Json$size(Json$Json *  self){
	if (self->kind == 5) {
		return self->arraySize(self) ; 
	}
	if (self->kind == 4) {
		return self->keySize(self) ; 
	}
	return 0; 
}


int  Json$Json$arraySize(Json$Json *  self){
	if (self->kind == 5) {
		if (self->list == NULL) {
			return 0; 
		}
		return self->list->size(self->list) ; 
	}
	return 0; 
}


int  Json$Json$keySize(Json$Json *  self){
	if (self->kind == 4) {
		if (self->map == NULL) {
			return 0; 
		}
		return self->map->size(self->map) ; 
	}
	return 0; 
}


Orc$List*  Json$Json$keys(Orc$List **  __outRef__, Json$Json *  self){
	if (self->kind == 4) {
		if (self->map != NULL) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_1 = NULL;
			return urgc_set_var_for_return_class((void ** )__outRef__, self->map->keys(&tmpReturn_1, self->map) ) ; 
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$List_new(&tmpNewOwner_2) ) ; 
}


int  Json$Json$atAsInt(Json$Json *  self, int  i){
	URGC_VAR_CLEANUP_CLASS Json$Json*  ret = self->at((ret = NULL,&ret), self, i) ;
	return ret->asInt(ret) ; 
}


double  Json$Json$atAsNumber(Json$Json *  self, int  i){
	URGC_VAR_CLEANUP_CLASS Json$Json*  ret = self->at((ret = NULL,&ret), self, i) ;
	return ret->asNumber(ret) ; 
}


bool  Json$Json$atAsBool(Json$Json *  self, int  i){
	URGC_VAR_CLEANUP_CLASS Json$Json*  ret = self->at((ret = NULL,&ret), self, i) ;
	return ret->asBool(ret) ; 
}


Orc$String*  Json$Json$atAsString(Orc$String **  __outRef__, Json$Json *  self, int  i){
	URGC_VAR_CLEANUP_CLASS Json$Json*  ret = self->at((ret = NULL,&ret), self, i) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret->asString(&tmpReturn_1, ret) ) ; 
}


Json$Json*  Json$Json$at(Json$Json **  __outRef__, Json$Json *  self, int  i){
	if (self->kind == 5) {
		if (self->list != NULL) {
			return urgc_set_var_for_return_class((void ** )__outRef__, (Json$Json* )self->list->get(self->list, i) ) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


bool  Json$Json$hasKey(Json$Json *  self, const char *  key){
	if (self->kind == 4) {
		if (self->map != NULL) {
			bool  b = self->map->has(self->map, key) ;
			return b; 
		}
	}
	return false; 
}


Json$Json*  Json$Json$get(Json$Json **  __outRef__, Json$Json *  self, const char *  key){
	if (self->kind == 4) {
		if (self->map != NULL) {
			return urgc_set_var_for_return_class((void ** )__outRef__, (Json$Json* )self->map->get(self->map, key) ) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


int  Json$Json$getInt(Json$Json *  self, const char *  key){
	URGC_VAR_CLEANUP_CLASS Json$Json*  ret = self->get((ret = NULL,&ret), self, key) ;
	if (!ret) {
		return 0; 
	}
	return ret->asInt(ret) ; 
}


double  Json$Json$getNumber(Json$Json *  self, const char *  key){
	URGC_VAR_CLEANUP_CLASS Json$Json*  ret = self->get((ret = NULL,&ret), self, key) ;
	if (!ret) {
		return 0.0; 
	}
	return ret->asNumber(ret) ; 
}


void  Json$Json$getToBool(Json$Json *  self, const char *  key, bool *  p){
	if (self->hasKey(self, key) ) {
		*p = self->getBool(self, key) ;
	}
}


void  Json$Json$getToInt(Json$Json *  self, const char *  key, int *  p){
	if (self->hasKey(self, key) ) {
		*p = (int )self->getNumber(self, key) ;
	}
}


void  Json$Json$getToFloat(Json$Json *  self, const char *  key, float *  p){
	if (self->hasKey(self, key) ) {
		*p = (float )self->getNumber(self, key) ;
	}
}


bool  Json$Json$getBool(Json$Json *  self, const char *  key){
	URGC_VAR_CLEANUP_CLASS Json$Json*  ret = self->get((ret = NULL,&ret), self, key) ;
	if (!ret) {
		return false; 
	}
	return ret->asBool(ret) ; 
}


Orc$String*  Json$Json$getString(Orc$String **  __outRef__, Json$Json *  self, const char *  key){
	URGC_VAR_CLEANUP_CLASS Json$Json*  ret = self->get((ret = NULL,&ret), self, key) ;
	if (ret) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, ret->asString(&tmpReturn_1, ret) ) ; 
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


void  Json$Json$getToInts(Json$Json *  self, const char *  key, int *  pInts, int  maxCount){
	if (self->hasKey(self, key) ) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		Json$Json *  kid = self->get(&tmpReturn_1, self, key) ;
		kid->toInts(kid, pInts, maxCount) ;
	}
}


void  Json$Json$getToFloats(Json$Json *  self, const char *  key, float *  pInts, int  maxCount){
	if (self->hasKey(self, key) ) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		Json$Json *  kid = self->get(&tmpReturn_1, self, key) ;
		kid->toFloats(kid, pInts, maxCount) ;
	}
}


void  Json$Json$getToStruct(Json$Json *  self, const char *  key, void *  pStruct, MetaStruct *  metaStruct){
	if (self->hasKey(self, key) ) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		Json$Json *  kid = self->get(&tmpReturn_1, self, key) ;
		Json$Json_setStructByJsonObject(pStruct, metaStruct, kid) ;
	}
}


void  Json$Json$setNumber(Json$Json *  self, double  v){
	self->kind = 2;
	self->numberValue = v;
}


void  Json$Json$setBool(Json$Json *  self, bool  v){
	self->kind = 1;
	self->boolValue = v;
}


void  Json$Json$setString(Json$Json *  self, Orc$String*  v){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(v);

	self->kind = 3;
	urgc_set_field_class(self, (void * )offsetof(Json$Json, stringValue) , v) ;
}


void  Json$Json$setCstr(Json$Json *  self, const char *  v){
	self->kind = 3;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Json$Json, stringValue) , Orc$str(&tmpReturn_1, v) ) ;
}


void  Json$Json$initList(Json$Json *  self){
	if (!self->list) {
		self->kind = 5;
		URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Json$Json, list) , Orc$List_new(&tmpNewOwner_1) ) ;
	}
}


void  Json$Json$initMap(Json$Json *  self){
	if (!self->map) {
		self->kind = 4;
		URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Json$Json, map) , Orc$Map_new(&tmpNewOwner_1) ) ;
	}
}


void  Json$Json$add(Json$Json *  self, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	self->initList(self) ;
	self->list->add(self->list, jo) ;
}


void  Json$Json$addNumber(Json$Json *  self, double  v){
	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->setNumber(obj, v) ;
	self->add(self, obj) ;
}


void  Json$Json$addBool(Json$Json *  self, bool  v){
	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->setBool(obj, v) ;
	self->add(self, obj) ;
}


void  Json$Json$addString(Json$Json *  self, Orc$String*  v){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(v);

	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->setString(obj, v) ;
	self->add(self, obj) ;
}


void  Json$Json$putNumber(Json$Json *  self, const char *  key, double  v){
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	self->put(self, key, Json$Json_mkNumber(&tmpReturn_1, v) ) ;
}


void  Json$Json$putBool(Json$Json *  self, const char *  key, double  v){
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	self->put(self, key, Json$Json_mkBool(&tmpReturn_1, v) ) ;
}


void  Json$Json$putString(Json$Json *  self, const char *  key, Orc$String*  v){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(v);

	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	self->put(self, key, Json$Json_mkString(&tmpReturn_1, v) ) ;
}


void  Json$Json$putCstr(Json$Json *  self, const char *  key, const char *  v){
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	self->put(self, key, Json$Json_mkStringByCstr(&tmpReturn_1, v) ) ;
}


void  Json$Json$put(Json$Json *  self, const char *  key, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	self->initMap(self) ;
	self->map->put(self->map, key, jo) ;
}


void  Json$Json$putObject(Json$Json *  self, const char *  key, Object *  jo){
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	self->put(self, key, Json$Json_toJson(&tmpReturn_1, jo) ) ;
}


void  Json$Json$mergeToSelf(Json$Json *  self, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	if (jo->isNull(jo) ) {
		return ; 
	}
	if (jo->isArray(jo) ) {
		int  l = jo->arraySize(jo) ;
		for (int  i = 0; i < l; i++) {
			URGC_VAR_CLEANUP_CLASS Json$Json*  item = jo->at((item = NULL,&item), jo, i) ;
			self->add(self, item) ;
		}
		return ; 
	}
	if (jo->isObject(jo) ) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  keys = jo->keys((keys = NULL,&keys), jo) ;
		int  l = keys->size(keys) ;
		for (int  i = 0; i < l; i++) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  key = (key=NULL,urgc_init_var_class((void**)&key, (Orc$String* )keys->get(keys, i) ));
			URGC_VAR_CLEANUP_CLASS Json$Json*  item = jo->get((item = NULL,&item), jo, key->str) ;
			self->put(self, key->str, item) ;
		}
		return ; 
	}
}


void  Json$Json$toObject(Json$Json *  self, Object *  obj){
	OrcMetaField *  mf = orc_getMetaFieldByObject(obj, "fromJson") ;
	if (mf) {
		void **  ptr = (void ** )OrcMetaField_getPtr(mf, obj) ;
		void  (*p_fromJson)(Object *  _self, Json$Json *  jo);
		p_fromJson = *ptr;
		if (p_fromJson) {
			p_fromJson(obj, self) ;
		}
	}
}


Object*  Json$Json$toObjectByVtables(Object **  __outRef__, Json$Json *  self, Orc$PointerArray*  vts){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(vts);

	URGC_VAR_CLEANUP_CLASS Orc$String*  className = self->getString((className = NULL,&className), self, "__class") ;
	for (int  i = 0; i < vts->size(vts) ; i++) {
		Vtable_Object *  vt = (Vtable_Object * )vts->get(vts, i) ;
		if (vt && strcmp(vt->className, className->str)  == 0) {
			URGC_VAR_CLEANUP_CLASS Object*  tmpReturn_1 = NULL;
			return urgc_set_var_for_return_class((void ** )__outRef__, self->toObjectByVtable(&tmpReturn_1, self, vt) ) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


Object*  Json$Json$toObjectByVtable(Object **  __outRef__, Json$Json *  self, Vtable_Object *  vt){
	if (self->kind == 5) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, self->toObjectsByVtable(&tmpReturn_1, self, vt) ) ; 
	}
	if (self->kind == 4 && self->map != NULL) {
		URGC_VAR_CLEANUP_CLASS Object*  obj = NULL;
		vt->make(&obj) ;
		self->toObject(self, obj) ;
		return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


Orc$List*  Json$Json$getObjectsByVtable(Orc$List **  __outRef__, Json$Json *  self, const char *  key, Vtable_Object *  vt){
	URGC_VAR_CLEANUP_CLASS Json$Json*  sub = self->get((sub = NULL,&sub), self, key) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  list = sub->toObjectsByVtable((list = NULL,&list), sub, vt) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, list) ; 
}


Orc$List*  Json$Json$toObjectsByVtable(Orc$List **  __outRef__, Json$Json *  self, Vtable_Object *  vt){
	if (self->kind != 5 || self->list == NULL) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$List*  list = (list=NULL,urgc_init_var_class((void**)&list, Orc$List_new(&list) ));
	int  l = self->size(self) ;
	for (int  i = 0; i < l; i++) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		Json$Json *  jo = self->at(&tmpReturn_1, self, i) ;
		URGC_VAR_CLEANUP_CLASS Object*  obj = jo->toObjectByVtable((obj = NULL,&obj), jo, vt) ;
		list->add(list, obj) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, list) ; 
}


void  Json$Json$toInts(Json$Json *  self, int *  pInts, int  maxCount){
	if (self->kind != 5 || self->list == NULL) {
		return ; 
	}
	int  l = self->size(self) ;
	for (int  i = 0; i < l && i < maxCount; i++) {
		int  v = self->atAsInt(self, i) ;
		pInts[i] = v;
	}
}


void  Json$Json$toFloats(Json$Json *  self, float *  pInts, int  maxCount){
	if (self->kind != 5 || self->list == NULL) {
		return ; 
	}
	int  l = self->size(self) ;
	for (int  i = 0; i < l && i < maxCount; i++) {
		float  v = self->atAsNumber(self, i) ;
		pInts[i] = v;
	}
}



Json$Json*  Json$Json_mkNull(Json$Json **  __outRef__){
	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->setNull(obj) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
}

Json$Json*  Json$Json_mkNumber(Json$Json **  __outRef__, double  v){
	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->setNumber(obj, v) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
}

Json$Json*  Json$Json_mkBool(Json$Json **  __outRef__, bool  v){
	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->setBool(obj, v) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
}

Json$Json*  Json$Json_mkStringByCstr(Json$Json **  __outRef__, const char *  v){
	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->setCstr(obj, v) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
}

Json$Json*  Json$Json_mkString(Json$Json **  __outRef__, Orc$String*  v){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(v);

	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->setString(obj, v) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
}

Json$Json*  Json$Json_mkArray(Json$Json **  __outRef__){
	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->initList(obj) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
}

Json$Json*  Json$Json_mkObject(Json$Json **  __outRef__){
	URGC_VAR_CLEANUP_CLASS Json$Json*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, Json$Json_new(&obj) ));
	obj->initMap(obj) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
}

Json$Json*  Json$Json_toJsonNumberArrayByInts(Json$Json **  __outRef__, int *  ints, int  count){
	if (!ints) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNull(&tmpReturn_1) ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  ja = Json$Json_mkArray((ja = NULL,&ja)) ;
	for (int  i = 0; i < count; i++) {
		ja->addNumber(ja, ints[i]) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ja) ; 
}

Json$Json*  Json$Json_toJsonNumberArrayByFloats(Json$Json **  __outRef__, float *  ints, int  count){
	if (!ints) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNull(&tmpReturn_1) ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  ja = Json$Json_mkArray((ja = NULL,&ja)) ;
	for (int  i = 0; i < count; i++) {
		ja->addNumber(ja, ints[i]) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ja) ; 
}

Json$Json*  Json$Json_toJsonByMetaStruct(Json$Json **  __outRef__, void *  pStruct, MetaStruct *  metaStruct){
	if (metaStruct == NULL || pStruct == NULL) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	OrcMetaField *  mf = metaStruct->headMetaField;
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	while (mf) {
		jo->putCstr(jo, "__struct", metaStruct->structName) ;
		if (!(mf->isPointer || mf->isRef || mf->isArray)) {
			if (mf->type == OrcMetaType_float) {
				float *  pv = (float * )OrcMetaField_getPtr(mf, pStruct) ;
				jo->putNumber(jo, mf->name, *pv) ;
			}
			else if (mf->type == OrcMetaType_double) {
				double *  pv = (double * )OrcMetaField_getPtr(mf, pStruct) ;
				jo->putNumber(jo, mf->name, *pv) ;
			}
			else if (mf->type == OrcMetaType_int) {
				int *  pv = (int * )OrcMetaField_getPtr(mf, pStruct) ;
				jo->putNumber(jo, mf->name, *pv) ;
			}
			else if (mf->type == OrcMetaType_bool) {
				bool *  pv = (bool * )OrcMetaField_getPtr(mf, pStruct) ;
				jo->putBool(jo, mf->name, *pv) ;
			}
			else if (mf->type == OrcMetaType_struct) {
				if (mf->metaStruct) {
					void *  pFieldStruct = OrcMetaField_getPtr(mf, pStruct) ;
					URGC_VAR_CLEANUP_CLASS Json$Json*  nest = Json$Json_toJsonByMetaStruct((nest = NULL,&nest), pFieldStruct, mf->metaStruct) ;
					jo->put(jo, mf->name, nest) ;
				}
			}
		}
		mf = mf->next;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, jo) ; 
}

Json$Json*  Json$Json_toJson(Json$Json **  __outRef__, Object *  obj){
	if (obj == NULL) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNull(&tmpReturn_1) ) ; 
	}
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Orc$String_init(NULL))) {
		Orc$String *  sobj = (Orc$String * )obj;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkString(&tmpReturn_2, sobj) ) ; 
	}
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Orc$Boolean_init(NULL))) {
		Orc$Boolean *  bobj = (Orc$Boolean * )obj;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_3 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkBool(&tmpReturn_3, bobj->value) ) ; 
	}
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Orc$Number_init(NULL))) {
		Orc$Number *  nobj = (Orc$Number * )obj;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_4 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNumber(&tmpReturn_4, nobj->toDouble(nobj) ) ) ; 
	}
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Orc$StructObj_init(NULL))) {
		Orc$StructObj *  so = (Orc$StructObj * )obj;
		URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_toJsonByMetaStruct((jo = NULL,&jo), so->pStruct, so->metaStruct) ;
		return urgc_set_var_for_return_class((void ** )__outRef__, jo) ; 
	}
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Orc$List_init(NULL))) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_5 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_toJsonArray(&tmpReturn_5, (Orc$List * )obj) ) ; 
	}
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Orc$Map_init(NULL))) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
		Orc$Map *  m = (Orc$Map * )obj;
		URGC_VAR_CLEANUP_CLASS Orc$List*  keys = m->keys((keys = NULL,&keys), m) ;
		int  l = keys->size(keys) ;
		for (int  i = 0; i < l; i++) {
			Orc$String *  key = (Orc$String * )keys->get(keys, i) ;
			Object *  kidObj = m->get(m, key) ;
			URGC_VAR_CLEANUP_CLASS Json$Json*  kidJo = Json$Json_toJson((kidJo = NULL,&kidJo), kidObj) ;
			jo->put(jo, key->str, kidJo) ;
		}
		return urgc_set_var_for_return_class((void ** )__outRef__, jo) ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	const char *  className = Object_getClassName(obj) ;
	jo->putCstr(jo, "__class", className) ;
	OrcMetaField *  mf = orc_getMetaFieldByObject(obj, "toJson") ;
	if (mf) {
		void **  ptr = (void ** )OrcMetaField_getPtr(mf, obj) ;
		void  (*p_toJson)(Object *  _self, Json$Json *  jo);
		p_toJson = *ptr;
		if (p_toJson) {
			p_toJson(obj, jo) ;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, jo) ; 
}

Json$Json*  Json$Json_toJsonArray(Json$Json **  __outRef__, Orc$List *  list){
	if (!list) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Json$Json_mkNull(&tmpReturn_1) ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  ja = Json$Json_mkArray((ja = NULL,&ja)) ;
	int  l = list->size(list) ;
	for (int  i = 0; i < l; i++) {
		Object *  obj = list->get(list, i) ;
		URGC_VAR_CLEANUP_CLASS Json$Json*  kidJo = Json$Json_toJson((kidJo = NULL,&kidJo), obj) ;
		ja->add(ja, kidJo) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ja) ; 
}

void  Json$Json_setPrimitive(OrcMetaField *  mf, void *  obj, Json$Json *  value){
	if (mf->metaStruct != NULL && !mf->isPointer && !mf->isRef && !mf->isArray) {
		void *  p = OrcMetaField_getPtr(mf, obj) ;
		Json$Json_setStructByJsonObject(p, mf->metaStruct, value) ;
		return ; 
	}
	if (!OrcMetaField_isPrimitive(mf) ) {
		return ; 
	}
	int  type = OrcMetaField_getType(mf) ;
	void *  p = OrcMetaField_getPtr(mf, obj) ;
	if (type == OrcMetaType_bool) {
		bool *  pv = (bool * )p;
		*pv = value->asBool(value) ;
	}
	else if (type == OrcMetaType_char) {
		char *  pv = (char * )p;
		*pv = (char )value->asInt(value) ;
	}
	else if (type == OrcMetaType_short) {
		short *  pv = (short * )p;
		*pv = (short )value->asInt(value) ;
	}
	else if (type == OrcMetaType_int) {
		int *  pv = (int * )p;
		*pv = value->asInt(value) ;
	}
	else if (type == OrcMetaType_long) {
		long *  pv = (long * )p;
		*pv = (long )value->asInt(value) ;
	}
	else if (type == OrcMetaType_long_long) {
		long long *  pv = (long long * )p;
		*pv = (long long )value->asInt(value) ;
	}
	else if (type == OrcMetaType_float) {
		float *  pv = (float * )p;
		*pv = (float )value->asNumber(value) ;
	}
	else if (type == OrcMetaType_double) {
		double *  pv = (double * )p;
		*pv = value->asNumber(value) ;
	}
}

void  Json$Json_setStructField(void *  pStruct, MetaStruct *  metaStruct, const char *  key, Json$Json*  value){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(value);

	OrcMetaField *  mf = MetaStruct_getMetaFieldByFieldName(metaStruct, key) ;
	if (mf != NULL) {
		Json$Json_setPrimitive(mf, pStruct, value) ;
	}
}

void  Json$Json_setStructByJsonObject(void *  pStruct, MetaStruct *  metaStruct, Json$Json*  value){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(value);

	if (!value->isObject(value) ) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$List*  keys = value->keys((keys = NULL,&keys), value) ;
	for (int  i = 0; i < keys->size(keys) ; i++) {
		Orc$String *  key = (Orc$String * )keys->get(keys, i) ;
		URGC_VAR_CLEANUP_CLASS Json$Json*  fieldValue = value->get((fieldValue = NULL,&fieldValue), value, key->str) ;
		Json$Json_setStructField(pStruct, metaStruct, key->str, fieldValue) ;
	}
}

Json$Json*  Json$Json_parseByPathCstr(Json$Json **  __outRef__, const char *  path){
	URGC_VAR_CLEANUP_CLASS Orc$String*  text = Orc$Path_readText((text = NULL,&text), path) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  ret = Json$Json_parse((ret = NULL,&ret), text->str) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

void  Json$testJson(){
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = Orc$str((s = NULL,&s), "{\"id\":1, \"name\":\"zgww\"}") ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), s->str) ;
	jo->dumpToFileByPathCstr(jo, "./testJson.json") ;
	{
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmp = Json$Json_parseByPathCstr((tmp = NULL,&tmp), "./testJson.json") ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  d = tmp->dump((d = NULL,&d), tmp) ;
		printf("from json. d:%s\n", d->str) ;
		Orc$Path_remove("./testJson.json") ;
	}
}



