
#include "String_orc.h" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./List_orc.h"
#include "./Map_orc.h"
#include "./Math_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_OrcLang$String _vtable_OrcLang$String;

// init meta

void OrcLang$String_initMeta(Vtable_OrcLang$String *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "str", OrcMetaType_char, offsetof(OrcLang$String, str), 0, 0, 1, 1);//char
	orc_metaField_primitive(&pNext, "_charSize", OrcMetaType_int, offsetof(OrcLang$String, _charSize), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "_runeSize", OrcMetaType_int, offsetof(OrcLang$String, _runeSize), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "addll", offsetof(OrcLang$String, addll));
	orc_metaField_method(&pNext, "addi", offsetof(OrcLang$String, addi));
	orc_metaField_method(&pNext, "addf", offsetof(OrcLang$String, addf));
	orc_metaField_method(&pNext, "addString", offsetof(OrcLang$String, addString));
	orc_metaField_method(&pNext, "addBytesWithCount", offsetof(OrcLang$String, addBytesWithCount));
	orc_metaField_method(&pNext, "add", offsetof(OrcLang$String, add));
	orc_metaField_method(&pNext, "fillCount", offsetof(OrcLang$String, fillCount));
	orc_metaField_method(&pNext, "set_as_own", offsetof(OrcLang$String, set_as_own));
	orc_metaField_method(&pNext, "set", offsetof(OrcLang$String, set));
	orc_metaField_method(&pNext, "charSize", offsetof(OrcLang$String, charSize));
	orc_metaField_method(&pNext, "expand", offsetof(OrcLang$String, expand));
	orc_metaField_method(&pNext, "notEquals", offsetof(OrcLang$String, notEquals));
	orc_metaField_method(&pNext, "empty", offsetof(OrcLang$String, empty));
	orc_metaField_method(&pNext, "notEmpty", offsetof(OrcLang$String, notEmpty));
	orc_metaField_method(&pNext, "equalsIgnoreCase", offsetof(OrcLang$String, equalsIgnoreCase));
	orc_metaField_method(&pNext, "equals", offsetof(OrcLang$String, equals));
	orc_metaField_method(&pNext, "equalsString", offsetof(OrcLang$String, equalsString));
	orc_metaField_method(&pNext, "runeSize", offsetof(OrcLang$String, runeSize));
	orc_metaField_method(&pNext, "calcRuneSize", offsetof(OrcLang$String, calcRuneSize));
	orc_metaField_method(&pNext, "size", offsetof(OrcLang$String, size));
	orc_metaField_method(&pNext, "length", offsetof(OrcLang$String, length));
	orc_metaField_method(&pNext, "substring", offsetof(OrcLang$String, substring));
	orc_metaField_method(&pNext, "substringToEnd", offsetof(OrcLang$String, substringToEnd));
	orc_metaField_method(&pNext, "_substringByCount", offsetof(OrcLang$String, _substringByCount));
	orc_metaField_method(&pNext, "substringByCount", offsetof(OrcLang$String, substringByCount));
	orc_metaField_method(&pNext, "substringByByteRange", offsetof(OrcLang$String, substringByByteRange));
	orc_metaField_method(&pNext, "substringByByteStart", offsetof(OrcLang$String, substringByByteStart));
	orc_metaField_method(&pNext, "substringByByteCount", offsetof(OrcLang$String, substringByByteCount));
	orc_metaField_method(&pNext, "indexByteOf", offsetof(OrcLang$String, indexByteOf));
	orc_metaField_method(&pNext, "lastIndexByteOf", offsetof(OrcLang$String, lastIndexByteOf));
	orc_metaField_method(&pNext, "replaceAll", offsetof(OrcLang$String, replaceAll));
	orc_metaField_method(&pNext, "replaceAllByRe", offsetof(OrcLang$String, replaceAllByRe));
	orc_metaField_method(&pNext, "clear", offsetof(OrcLang$String, clear));
	orc_metaField_method(&pNext, "splitByRe", offsetof(OrcLang$String, splitByRe));
}


// vtable init


Vtable_OrcLang$String* Vtable_OrcLang$String_init(Vtable_OrcLang$String* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$String;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$String_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$String";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$String_initMeta;

    return pvt;
}


// fini function

void OrcLang$String_fini(OrcLang$String *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void OrcLang$String_init_fields(OrcLang$String *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)OrcLang$String_fini;
	//fields
    {
	((OrcLang$String*)self)->str = NULL;
	((OrcLang$String*)self)->_charSize = -1;
	((OrcLang$String*)self)->_runeSize = -1;
    }
	((Object*)self)->dtor = (void*)OrcLang$String$dtor;
	((OrcLang$String*)self)->addll = (void*)OrcLang$String$addll;
	((OrcLang$String*)self)->addi = (void*)OrcLang$String$addi;
	((OrcLang$String*)self)->addf = (void*)OrcLang$String$addf;
	((OrcLang$String*)self)->addString = (void*)OrcLang$String$addString;
	((OrcLang$String*)self)->addBytesWithCount = (void*)OrcLang$String$addBytesWithCount;
	((OrcLang$String*)self)->add = (void*)OrcLang$String$add;
	((OrcLang$String*)self)->fillCount = (void*)OrcLang$String$fillCount;
	((OrcLang$String*)self)->set_as_own = (void*)OrcLang$String$set_as_own;
	((OrcLang$String*)self)->set = (void*)OrcLang$String$set;
	((OrcLang$String*)self)->charSize = (void*)OrcLang$String$charSize;
	((OrcLang$String*)self)->expand = (void*)OrcLang$String$expand;
	((OrcLang$String*)self)->notEquals = (void*)OrcLang$String$notEquals;
	((OrcLang$String*)self)->empty = (void*)OrcLang$String$empty;
	((OrcLang$String*)self)->notEmpty = (void*)OrcLang$String$notEmpty;
	((OrcLang$String*)self)->equalsIgnoreCase = (void*)OrcLang$String$equalsIgnoreCase;
	((OrcLang$String*)self)->equals = (void*)OrcLang$String$equals;
	((OrcLang$String*)self)->equalsString = (void*)OrcLang$String$equalsString;
	((OrcLang$String*)self)->runeSize = (void*)OrcLang$String$runeSize;
	((OrcLang$String*)self)->calcRuneSize = (void*)OrcLang$String$calcRuneSize;
	((OrcLang$String*)self)->size = (void*)OrcLang$String$size;
	((OrcLang$String*)self)->length = (void*)OrcLang$String$length;
	((OrcLang$String*)self)->substring = (void*)OrcLang$String$substring;
	((OrcLang$String*)self)->substringToEnd = (void*)OrcLang$String$substringToEnd;
	((OrcLang$String*)self)->_substringByCount = (void*)OrcLang$String$_substringByCount;
	((OrcLang$String*)self)->substringByCount = (void*)OrcLang$String$substringByCount;
	((OrcLang$String*)self)->substringByByteRange = (void*)OrcLang$String$substringByByteRange;
	((OrcLang$String*)self)->substringByByteStart = (void*)OrcLang$String$substringByByteStart;
	((OrcLang$String*)self)->substringByByteCount = (void*)OrcLang$String$substringByByteCount;
	((OrcLang$String*)self)->indexByteOf = (void*)OrcLang$String$indexByteOf;
	((OrcLang$String*)self)->lastIndexByteOf = (void*)OrcLang$String$lastIndexByteOf;
	((OrcLang$String*)self)->replaceAll = (void*)OrcLang$String$replaceAll;
	((OrcLang$String*)self)->replaceAllByRe = (void*)OrcLang$String$replaceAllByRe;
	((OrcLang$String*)self)->clear = (void*)OrcLang$String$clear;
	((OrcLang$String*)self)->splitByRe = (void*)OrcLang$String$splitByRe;
}

// init function

void OrcLang$String_init(OrcLang$String *self){
    Vtable_OrcLang$String_init(&_vtable_OrcLang$String);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$String;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$String_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$String * OrcLang$String_new(){
    OrcLang$String *self = calloc(1, sizeof(OrcLang$String));
    OrcLang$String_init(self);
    return self;
}


// class members
void  OrcLang$String$dtor(OrcLang$String *  self){
	if (self->str) {
		free(self->str) ;
	}
}


OrcLang$String *  OrcLang$String$addll(OrcLang$String *  self, long long  i){
	char  data[200];
	snprintf(data, 199, "%lld", i) ;
	self->add(self, data) ;
	return self; 
}


OrcLang$String *  OrcLang$String$addi(OrcLang$String *  self, int  i){
	char  data[200];
	snprintf(data, 199, "%d", i) ;
	self->add(self, data) ;
	return self; 
}


OrcLang$String *  OrcLang$String$addf(OrcLang$String *  self, float  i){
	char  data[200];
	snprintf(data, 199, "%f", i) ;
	self->add(self, data) ;
	return self; 
}


OrcLang$String *  OrcLang$String$addString(OrcLang$String *  self, OrcLang$String *  s){
	if (s) {
		self->add(self, s->str) ;
	}
	return self; 
}


OrcLang$String *  OrcLang$String$addBytesWithCount(OrcLang$String *  self, const char *  str, int  count){
	int  addSize = OrcLang$minInt(count, strlen(str) ) ;
	int  newSize = self->charSize(self)  + addSize;
	self->expand(self, newSize + 1) ;
	memcpy(self->str + self->charSize(self) , str, addSize) ;
	self->_charSize = newSize;
	self->str[newSize] = 0;
	self->_runeSize = -1;
	return self; 
}


OrcLang$String *  OrcLang$String$add(OrcLang$String *  self, const char *  str){
	if (self->str == NULL) {
		self->str = _strdup(str) ;
		return self; 
	}
	if (str) {
		int  addSize = strlen(str) ;
		int  newSize = self->charSize(self)  + addSize;
		self->expand(self, newSize + 1) ;
		memcpy(self->str + self->charSize(self) , str, addSize + 1) ;
		self->_charSize = newSize;
		self->_runeSize = -1;
	}
	return self; 
}


void  OrcLang$String$fillCount(OrcLang$String *  self, const char *  s, int  count){
	for (int  i = 0; i < count; i++) {
		self->add(self, s) ;
	}
}


OrcLang$String *  OrcLang$String$set_as_own(OrcLang$String *  self, char *  str){
	if (self->str) {
		free(self->str) ;
	}
	self->str = str;
	return self; 
}


OrcLang$String *  OrcLang$String$set(OrcLang$String *  self, const char *  str){
	if (self->equals(self, str) ) {
		return self; 
	}
	self->clear(self) ;
	self->add(self, str) ;
	return self; 
}


int  OrcLang$String$charSize(OrcLang$String *  self){
	if (self->str == NULL) {
		return 0; 
	}
	if (self->_charSize == -1) {
		self->_charSize = strlen(self->str) ;
	}
	return self->_charSize; 
}


void  OrcLang$String$expand(OrcLang$String *  self, int  needSize){
	if (self->str == NULL) {
		self->str = calloc(1, needSize) ;
	}
	self->str = realloc(self->str, needSize) ;
}


bool  OrcLang$String$notEquals(OrcLang$String *  self, const char *  str){
	return !self->equals(self, str) ; 
}


bool  OrcLang$String$empty(OrcLang$String *  self){
	return self->str == NULL || self->str[0] == 0; 
}


bool  OrcLang$String$notEmpty(OrcLang$String *  self){
	return !self->empty(self) ; 
}


bool  OrcLang$String$equalsIgnoreCase(OrcLang$String *  self, const char *  str){
	if (self->str == str) {
		return true; 
	}
	if (str == NULL || self->str == NULL) {
		return false; 
	}
	int  ret = stricmp(self->str, str) ;
	return ret == 0; 
}


bool  OrcLang$String$equals(OrcLang$String *  self, const char *  str){
	if (self->str == str) {
		return true; 
	}
	if (str == NULL || self->str == NULL) {
		return false; 
	}
	int  ret = strcmp(self->str, str) ;
	return ret == 0; 
}


bool  OrcLang$String$equalsString(OrcLang$String *  self, OrcLang$String *  str){
	return self->equals(self, str->str) ; 
}


int  OrcLang$String$runeSize(OrcLang$String *  self){
	if (self->_runeSize == -1) {
		self->_runeSize = self->calcRuneSize(self) ;
	}
	return self->_runeSize; 
}


int  OrcLang$String$size(OrcLang$String *  self){
	return self->runeSize(self) ; 
}


int  OrcLang$String$length(OrcLang$String *  self){
	return self->runeSize(self) ; 
}


OrcLang$String*  OrcLang$String$substring(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  end){
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return((void ** )__outRef__, self->substringByCount(&tmpReturn_1, self, start, end - start) ) ; 
}


OrcLang$String*  OrcLang$String$substringToEnd(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start){
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return((void ** )__outRef__, self->substringByCount(&tmpReturn_1, self, start, self->length(self)  - start) ) ; 
}


OrcLang$String*  OrcLang$String$substringByCount(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  n){
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return((void ** )__outRef__, self->_substringByCount(&tmpReturn_1, self, start, n) ) ; 
}


OrcLang$String*  OrcLang$String$substringByByteRange(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  end){
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return((void ** )__outRef__, self->substringByByteCount(&tmpReturn_1, self, start, end - start) ) ; 
}


OrcLang$String*  OrcLang$String$substringByByteStart(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start){
	URGC_VAR_CLEANUP OrcLang$String*  ret = urgc_init_var((void**)&ret, OrcLang$String_new() );
	return urgc_set_var_for_return((void ** )__outRef__, ret->addBytesWithCount(ret, self->str + start, self->charSize(self)  - start) ) ; 
}


OrcLang$String*  OrcLang$String$substringByByteCount(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  end){
	URGC_VAR_CLEANUP OrcLang$String*  ret = urgc_init_var((void**)&ret, OrcLang$String_new() );
	return urgc_set_var_for_return((void ** )__outRef__, ret->addBytesWithCount(ret, self->str + start, end - start) ) ; 
}


int  OrcLang$String$indexByteOf(OrcLang$String *  self, const char *  cstr){
	if (self->str == NULL) {
		return -1; 
	}
	const char *  tmp = strstr(self->str, cstr) ;
	if (tmp == NULL) {
		return -1; 
	}
	return ((int )tmp) - ((int )self->str); 
}


int  OrcLang$String$lastIndexByteOf(OrcLang$String *  self, const char *  cstr){
	if (self->str == NULL || cstr == NULL || strlen(cstr)  == 0) {
		return -1; 
	}
	for (int  i = self->charSize(self)  - 1; i >= 0; i--) {
		bool  ok = OrcLang$String_startsWith(self->str + i, cstr) ;
		if (ok) {
			return i; 
		}
	}
	return -1; 
}


void  OrcLang$String$clear(OrcLang$String *  self){
	if (self->str) {
		self->str[0] = 0;
		self->_charSize = -1;
		self->_runeSize = -1;
	}
}



bool  OrcLang$String_startsWith(const char *  s, const char *  find){
	if (s == NULL || find == NULL) {
		return false; 
	}
	int  slen = strlen(s) ;
	int  findLen = strlen(find) ;
	if (slen < findLen) {
		return false; 
	}
	for (int  i = 0; i < findLen; i++) {
		if (s[i] != find[i]) {
			return false; 
		}
	}
	return true; 
}

bool  OrcLang$strEq(const char *  a, const char *  b){
	return strcmp(a, b)  == 0; 
}

OrcLang$String*  OrcLang$str(OrcLang$String **  __outRef__, const char *  data){
	URGC_VAR_CLEANUP OrcLang$String*  ret = urgc_init_var((void**)&ret, OrcLang$String_new() );
	ret->add(ret, data) ;
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}

void  OrcLang$testStr(){
	URGC_VAR_CLEANUP OrcLang$String*  s = OrcLang$str((s = NULL,&s), "你好吗") ;
	s->add(s, "添加的字符串") ;
	OrcLang$String *  tmpThis_1 = NULL;
	OrcLang$String *  tmpThis_2 = NULL;
	OrcLang$String *  tmpThis_3 = NULL;
	OrcLang$String *  tmpThis_4 = NULL;
	(tmpThis_1 = (tmpThis_2 = (tmpThis_3 = (tmpThis_4 = s->add(s, "-第二段-") )->add(tmpThis_4, "??链式调用??") )->addf(tmpThis_3, 123.f) )->add(tmpThis_2, " int:") )->addi(tmpThis_1, 12389273) ;
	printf("testStr:%s\n", s->str) ;
	URGC_VAR_CLEANUP OrcLang$List*  list = urgc_init_var((void**)&list, OrcLang$List_new() );
	list->add(list, s) ;
	URGC_VAR_CLEANUP OrcLang$Map*  map = urgc_init_var((void**)&map, OrcLang$Map_new() );
	map->put(map, "key", s) ;
	URGC_VAR_CLEANUP OrcLang$String*  str2 = urgc_init_var((void**)&str2, s);
	str2->add(str2, "-str2-") ;
	printf(" str2:%s\n", str2->str) ;
	printf("list size:%d\n", list->size(list) ) ;
	printf("map size:%d\n", map->size(map) ) ;
	URGC_VAR_CLEANUP OrcLang$String*  tmp = urgc_init_var((void**)&tmp, map->get(map, "key") );
	URGC_VAR_CLEANUP OrcLang$String*  tmp2 = urgc_init_var((void**)&tmp2, list->get(list, 0) );
	printf("map value:%s\n", tmp->str) ;
	printf("list value:%s\n", tmp2->str) ;
	list->remove(list, s) ;
	map->del(map, "key") ;
	printf("list size:%d\n", list->size(list) ) ;
	printf("map size:%d\n", map->size(map) ) ;
	{
		URGC_VAR_CLEANUP OrcLang$String*  tmp = OrcLang$str((tmp = NULL,&tmp), "123$45^67^8") ;
		URGC_VAR_CLEANUP OrcLang$String*  out = tmp->replaceAll((out = NULL,&out), tmp, "^", "+^^+") ;
		printf("replaceAll :%s\n", out->str) ;
	}
	{
		URGC_VAR_CLEANUP OrcLang$String*  tmp = OrcLang$str((tmp = NULL,&tmp), "123$45^67^8") ;
		URGC_VAR_CLEANUP OrcLang$String*  out = tmp->replaceAllByRe((out = NULL,&out), tmp, "\\d+", "d") ;
		printf("replaceAllByRe :%s\n", out->str) ;
	}
	{
		URGC_VAR_CLEANUP OrcLang$String*  tmp = OrcLang$str((tmp = NULL,&tmp), "1\\23\\45^67^8") ;
		URGC_VAR_CLEANUP OrcLang$String*  out = tmp->replaceAllByRe((out = NULL,&out), tmp, "\\\\+", "/") ;
		printf("replaceAllByRe :%s\n", out->str) ;
	}
}



