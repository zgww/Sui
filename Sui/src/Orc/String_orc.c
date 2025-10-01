
#include "String_orc.h" 

#include "./Orc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./List_orc.h"
#include "./Map_orc.h"
#include "./Math_orc.h"
#include "./ScopeData_orc.h"
#include "./Number_orc.h"


// static struct 


// static function declaration
static Orc$ScopeData PrintStyle__exit__(Orc$PrintStyle *  _self);



//vtable instance
Vtable_Orc$String _vtable_Orc$String;

// init meta

void Orc$String_initMeta(Vtable_Orc$String *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "str", OrcMetaType_char, offsetof(Orc$String, str), 0, 0, 1, 1);//char
	orc_metaField_primitive(&pNext, "_charSize", OrcMetaType_int, offsetof(Orc$String, _charSize), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "_runeSize", OrcMetaType_int, offsetof(Orc$String, _runeSize), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "capacity", OrcMetaType_int, offsetof(Orc$String, capacity), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_Orc$String* Vtable_Orc$String_init(Vtable_Orc$String* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$String;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$String_new;
    ((Vtable_Object*)pvt)->className = "Orc$String";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$String_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Orc$String_fini(Orc$String *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Orc$String_init_fields(Orc$String *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Orc$String_fini;
	//fields
    {
	((Orc$String*)self)->str = NULL;
	((Orc$String*)self)->_charSize = -1;
	((Orc$String*)self)->_runeSize = -1;
	((Orc$String*)self)->capacity = 0;
    }
	((Object*)self)->dtor = (void*)Orc$String$dtor;
}

// init function

void Orc$String_init(Orc$String *self, void *pOwner){
    Vtable_Orc$String_init(&_vtable_Orc$String);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$String;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$String_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$String * Orc$String_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$String *self = calloc(1, sizeof(Orc$String));
	
    Orc$String_init(self, pOwner);
    return self;
}


// class members
void  Orc$String$dtor(Orc$String *  self){
	if (self->str) {
		free(self->str) ;
	}
}



Orc$String*  Orc$String_join(Orc$String **  __outRef__, Orc$List *  list, const char *  dep){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$str((ret = NULL,&ret), "") ;
	if (list) {
		int  l = list->size(list) ;
		for (int  i = 0; i < l; i++) {
			Orc$String *  part = (Orc$String * )list->get(list, i) ;
			Orc$String$addString(ret, part) ;
			if (i < l - 1) {
				Orc$String$add(ret, dep) ;
			}
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

bool  Orc$String_startsWith(const char *  s, const char *  find){
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

bool  Orc$String_endsWithIgnoreCase(const char *  s, const char *  find){
	if (!s) {
		return false; 
	}
	int  findlen = strlen(find) ;
	int  slen = strlen(s) ;
	if (slen < findlen) {
		return false; 
	}
	const char *  tmp = s + slen - findlen;
	bool  ok = stricmp(tmp, find)  == 0;
	return ok; 
}

bool  Orc$String_endsWith(const char *  s, const char *  find){
	if (!s) {
		return false; 
	}
	int  findlen = strlen(find) ;
	int  slen = strlen(s) ;
	if (slen < findlen) {
		return false; 
	}
	const char *  tmp = s + slen - findlen;
	bool  ok = strcmp(tmp, find)  == 0;
	return ok; 
}

bool  Orc$strEq(const char *  a, const char *  b){
	return strcmp(a, b)  == 0; 
}

Orc$String*  Orc$str(Orc$String **  __outRef__, const char *  data){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$String_new(&ret) ));
	Orc$String$add(ret, data) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

int  Orc$String$toInt(Orc$String *  self){
	if (!self->str) {
		return 0; 
	}
	return atoi(self->str) ; 
}

float  Orc$String$toFloat(Orc$String *  self){
	if (!self->str) {
		return 0; 
	}
	return atof(self->str) ; 
}

Orc$String *  Orc$String$addPtr(Orc$String *  self, void *  p){
	char  data[100];
	snprintf(data, 99, "%p", p) ;
	Orc$String$add(self, data) ;
	return self; 
}

Orc$String *  Orc$String$addll(Orc$String *  self, long long  i){
	char  data[200];
	snprintf(data, 199, "%lld", i) ;
	Orc$String$add(self, data) ;
	return self; 
}

Orc$String *  Orc$String$addc(Orc$String *  self, char  c){
	char  data[20];
	snprintf(data, 19, "%c", c) ;
	Orc$String$add(self, data) ;
	return self; 
}

Orc$String *  Orc$String$addi(Orc$String *  self, int  i){
	char  data[200];
	snprintf(data, 199, "%d", i) ;
	Orc$String$add(self, data) ;
	return self; 
}

Orc$String *  Orc$String$addf(Orc$String *  self, float  i){
	char  data[200];
	snprintf(data, 199, "%f", i) ;
	Orc$String$add(self, data) ;
	return self; 
}

Orc$String *  Orc$String$addDouble(Orc$String *  self, double  i){
	char  data[200];
	snprintf(data, 199, "%f", i) ;
	Orc$String$add(self, data) ;
	return self; 
}

Orc$String *  Orc$String$addString(Orc$String *  self, Orc$String *  s){
	if (s) {
		Orc$String$add(self, s->str) ;
	}
	return self; 
}

Orc$String *  Orc$String$addBytesWithCount(Orc$String *  self, const char *  str, int  count){
	int  addSize = Orc$minInt(count, strlen(str) ) ;
	int  newSize = Orc$String$charSize(self)  + addSize;
	Orc$String$expand(self, newSize + 1) ;
	if (str) {
		memcpy(self->str + Orc$String$charSize(self) , str, addSize) ;
	}
	self->_charSize = newSize;
	self->str[newSize] = 0;
	self->_runeSize = -1;
	return self; 
}

Orc$String *  Orc$String$add(Orc$String *  self, const char *  str){
	if (self->str == NULL) {
		self->str = _strdup(str) ;
		self->capacity = strlen(self->str)  + 1;
		return self; 
	}
	if (str) {
		int  addSize = strlen(str) ;
		int  newSize = Orc$String$charSize(self)  + addSize;
		Orc$String$expand(self, newSize + 1) ;
		memcpy(self->str + Orc$String$charSize(self) , str, addSize + 1) ;
		self->_charSize = newSize;
		self->_runeSize = -1;
	}
	return self; 
}

void  Orc$String$fillCount(Orc$String *  self, const char *  s, int  count){
	for (int  i = 0; i < count; i++) {
		Orc$String$add(self, s) ;
	}
}

Orc$String *  Orc$String$set_as_own(Orc$String *  self, char *  str){
	if (self->str) {
		free(self->str) ;
	}
	self->str = str;
	self->capacity = strlen(str)  + 1;
	return self; 
}

Orc$String *  Orc$String$set(Orc$String *  self, const char *  str){
	if (Orc$String$equals(self, str) ) {
		return self; 
	}
	Orc$String$clear(self) ;
	Orc$String$add(self, str) ;
	return self; 
}

int  Orc$String$charSize(Orc$String *  self){
	if (self == NULL) {
		return 0; 
	}
	if (self->str == NULL) {
		return 0; 
	}
	if (self->_charSize == -1) {
		self->_charSize = strlen(self->str) ;
	}
	return self->_charSize; 
}

void  Orc$String$expand(Orc$String *  self, int  needSize){
	if (self->str == NULL) {
		self->str = calloc(1, needSize) ;
		self->capacity = needSize;
		return ; 
	}
	int  x2 = self->capacity * 2;
	if (x2 < 10000 && x2 > needSize) {
		needSize = x2;
	}
	self->str = realloc(self->str, needSize) ;
	self->capacity = needSize;
}

Orc$String*  Orc$String$trimLeft(Orc$String **  __outRef__, Orc$String *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$trimChars(&tmpReturn_1, self, " \t\n\r", true, false) ) ; 
}

Orc$String*  Orc$String$trimRight(Orc$String **  __outRef__, Orc$String *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$trimChars(&tmpReturn_1, self, " \t\n\r", false, true) ) ; 
}

Orc$String*  Orc$String$trim(Orc$String **  __outRef__, Orc$String *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$trimChars(&tmpReturn_1, self, " \t\n\r", true, true) ) ; 
}

Orc$String*  Orc$String$trimChars(Orc$String **  __outRef__, Orc$String *  self, const char *  chars, bool  trimLeft, bool  trimRight){
	int  start = 0;
	int  l = Orc$String$charSize(self) ;
	int  cl = strlen(chars) ;
	if (trimLeft) {
		for (int  i = 0; i < l; i++) {
			bool  found = false;
			for (int  j = 0; j < cl; j++) {
				if (self->str[i] == chars[j]) {
					found = true;
					break;
				}
			}
			if (!found) {
				start = i;
				break;
			}
		}
	}
	int  end = l;
	if (trimRight) {
		for (int  i = l - 1; i >= 0; i--) {
			bool  found = false;
			for (int  j = 0; j < cl; j++) {
				if (self->str[i] == chars[j]) {
					found = true;
					break;
				}
			}
			if (!found) {
				end = i + 1;
				break;
			}
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$substringByByteRange(&tmpReturn_1, self, start, end) ) ; 
}

Orc$String*  Orc$String$substring(Orc$String **  __outRef__, Orc$String *  self, int  start, int  end){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$substringByCount(&tmpReturn_1, self, start, end - start) ) ; 
}

Orc$String*  Orc$String$substringToEnd(Orc$String **  __outRef__, Orc$String *  self, int  start){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$substringByCount(&tmpReturn_1, self, start, Orc$String$length(self)  - start) ) ; 
}

Orc$String*  Orc$String$substringByCount(Orc$String **  __outRef__, Orc$String *  self, int  start, int  n){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$_substringByCount(&tmpReturn_1, self, start, n) ) ; 
}

Orc$String*  Orc$String$substringByByteRange(Orc$String **  __outRef__, Orc$String *  self, int  start, int  end){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$substringByByteCount(&tmpReturn_1, self, start, end - start) ) ; 
}

Orc$String*  Orc$String$substringByByteStart(Orc$String **  __outRef__, Orc$String *  self, int  start){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$String_new(&ret) ));
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$addBytesWithCount(ret, self->str + start, Orc$String$charSize(self)  - start) ) ; 
}

Orc$String*  Orc$String$substringByByteCount(Orc$String **  __outRef__, Orc$String *  self, int  start, int  count){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$String_new(&ret) ));
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$addBytesWithCount(ret, self->str + start, count) ) ; 
}

int  Orc$String$indexByteOf(Orc$String *  self, const char *  cstr){
	if (self->str == NULL) {
		return -1; 
	}
	const char *  tmp = strstr(self->str, cstr) ;
	if (tmp == NULL) {
		return -1; 
	}
	return ((long long )tmp) - ((long long )self->str); 
}

int  Orc$String$lastIndexByteOf(Orc$String *  self, const char *  cstr){
	if (self->str == NULL || cstr == NULL || strlen(cstr)  == 0) {
		return -1; 
	}
	for (int  i = Orc$String$charSize(self)  - 1; i >= 0; i--) {
		bool  ok = Orc$String_startsWith(self->str + i, cstr) ;
		if (ok) {
			return i; 
		}
	}
	return -1; 
}

void  Orc$String$clear(Orc$String *  self){
	if (self->str) {
		self->str[0] = 0;
		self->_charSize = -1;
		self->_runeSize = -1;
	}
}

Orc$List*  Orc$String$splitToLines(Orc$List **  __outRef__, Orc$String *  self){
	URGC_VAR_CLEANUP_CLASS Orc$List*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$List_new(&ret) ));
	int  start = 0;
	int  len = Orc$String$charSize(self) ;
	for (int  i = 0; i < len; i++) {
		if (self->str[i] == '\n' || self->str[i] == '\r') {
			URGC_VAR_CLEANUP_CLASS Orc$String*  line = Orc$String$substringByByteRange((line = NULL,&line), self, start, i) ;
			ret->add(ret, line) ;
			if (self->str[i] == '\r' && i + 1 < len && self->str[i + 1] == '\n') {
				i++;
			}
			start = i + 1;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  Orc$String$clone(Orc$String **  __outRef__, Orc$String *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, self->str ? self->str : "") ) ; 
}

int  Orc$String$runeSize(Orc$String *  self){
	if (self->_runeSize == -1) {
		self->_runeSize = Orc$String$calcRuneSize(self) ;
	}
	return self->_runeSize; 
}

int  Orc$String$size(Orc$String *  self){
	return Orc$String$runeSize(self) ; 
}

int  Orc$String$length(Orc$String *  self){
	return Orc$String$runeSize(self) ; 
}

bool  Orc$String$equalsIgnoreCase(Orc$String *  self, const char *  str){
	if (self->str == str) {
		return true; 
	}
	if (str == NULL || self->str == NULL) {
		return false; 
	}
	int  ret = _stricmp(self->str, str) ;
	return ret == 0; 
}

bool  Orc$String$equals(Orc$String *  self, const char *  str){
	if (self == NULL) {
		return str == NULL; 
	}
	if (self->str == str) {
		return true; 
	}
	if (str == NULL || self->str == NULL) {
		return false; 
	}
	int  ret = strcmp(self->str, str) ;
	return ret == 0; 
}

bool  Orc$String$equalsString(Orc$String *  self, Orc$String *  str){
	if (str == NULL) {
		return NULL == self; 
	}
	return Orc$String$equals(self, str->str) ; 
}

bool  Orc$String$notEquals(Orc$String *  self, const char *  str){
	return !Orc$String$equals(self, str) ; 
}

bool  Orc$String$empty(Orc$String *  self){
	return self->str == NULL || self->str[0] == 0; 
}

bool  Orc$String$notEmpty(Orc$String *  self){
	return !Orc$String$empty(self) ; 
}

bool  Orc$String$startsWith(Orc$String *  self, const char *  find){
	return Orc$String_startsWith(self->str, find) ; 
}

bool  Orc$String$endsWith(Orc$String *  self, const char *  find){
	return Orc$String_endsWith(self->str, find) ; 
}


// get or init meta 
MetaStruct* Orc$PrintStyle_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Orc$PrintStyle", sizeof( Orc$PrintStyle ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(Orc$PrintStyle, color), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "bg", OrcMetaType_int, offsetof(Orc$PrintStyle, bg), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "code", OrcMetaType_int, offsetof(Orc$PrintStyle, code), 0, 0, 0, 0);//int
    }
	return meta;
}
static Orc$ScopeData PrintStyle__exit__(Orc$PrintStyle *  _self){
	if (_self->color) {
		printf("\033[0;0;0m\033[%d;%dm", _self->code, _self->color) ;
	}
	return Orc$mkScopeData(_self, (void * )Orc$PrintStyle_exit) ; 
}

Orc$PrintStyle *  Orc$PrintStyle$black(Orc$PrintStyle *  self){
	self->color = 30;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$red(Orc$PrintStyle *  self){
	self->color = 31;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$green(Orc$PrintStyle *  self){
	self->color = 32;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$yellow(Orc$PrintStyle *  self){
	self->color = 33;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$blue(Orc$PrintStyle *  self){
	self->color = 34;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$purple(Orc$PrintStyle *  self){
	self->color = 35;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$cyan(Orc$PrintStyle *  self){
	self->color = 36;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$white(Orc$PrintStyle *  self){
	self->color = 37;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$bgblack(Orc$PrintStyle *  self){
	self->color = 40;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$bgred(Orc$PrintStyle *  self){
	self->color = 41;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$bggreen(Orc$PrintStyle *  self){
	self->color = 42;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$bgyellow(Orc$PrintStyle *  self){
	self->color = 43;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$bgblue(Orc$PrintStyle *  self){
	self->color = 44;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$bgpurple(Orc$PrintStyle *  self){
	self->color = 45;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$bgcyan(Orc$PrintStyle *  self){
	self->color = 46;
	return self; 
}

Orc$PrintStyle *  Orc$PrintStyle$bgwhite(Orc$PrintStyle *  self){
	self->color = 47;
	return self; 
}

Orc$PrintStyle Orc$mkPrintStyle(){
	Orc$PrintStyle r;
	r.bg = 0;
	r.color = 31;
	r.code = 1;
	r.__exit__ = PrintStyle__exit__;
	return r; 
}

void  Orc$PrintStyle_exit(Orc$ScopeData *  scopeData){
	printf("\033[0m\n") ;
}

Orc$String*  Orc$Object$toString(Orc$String **  __outRef__, Object *  self){
	if (Orc_instanceof((Object*)self, (Vtable_Object*)Vtable_Orc$Number_init(NULL))) {
		Orc$Number *  n = (Orc$Number * )self;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, n->toString(&tmpReturn_1, n) ) ; 
	}
	if (Orc_instanceof((Object*)self, (Vtable_Object*)Vtable_Orc$String_init(NULL))) {
		return urgc_set_var_for_return_class((void ** )__outRef__, (Orc$String* )self) ; 
	}
	Vtable_Object *  vt = orc_getVtableByObject(self) ;
	char  tmp[100];
	sprintf(tmp, "%s(%p)", vt->className, self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_2, tmp) ) ; 
}

void  Orc$testOk(bool  ok, const char *  msg){
	if (!ok) {
		printf("\033[1;31mtest fail: %s\033[0m\n", msg) ;
	}
}

void  Orc$testStr(){
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = Orc$str((s = NULL,&s), "你好吗") ;
	Orc$String$add(s, "添加的字符串") ;
	Orc$String$addi(Orc$String$add(Orc$String$addf(Orc$String$add(Orc$String$add(s, "-第二段-") , "??链式调用??") , 123.f) , " int:") , 12389273) ;
	printf("testStr:%s\n", s->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  list = (list=NULL,urgc_init_var_class((void**)&list, Orc$List_new(&list) ));
	list->add(list, s) ;
	URGC_VAR_CLEANUP_CLASS Orc$Map*  map = (map=NULL,urgc_init_var_class((void**)&map, Orc$Map_new(&map) ));
	map->put(map, "key", s) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  str2 = (str2=NULL,urgc_init_var_class((void**)&str2, s));
	Orc$String$add(str2, "-str2-") ;
	printf(" str2:%s\n", str2->str) ;
	printf("list size:%d\n", list->size(list) ) ;
	printf("map size:%d\n", map->size(map) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = (tmp=NULL,urgc_init_var_class((void**)&tmp, (Orc$String* )map->get(map, "key") ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp2 = (tmp2=NULL,urgc_init_var_class((void**)&tmp2, (Orc$String* )list->get(list, 0) ));
	printf("map value:%s\n", tmp->str) ;
	printf("list value:%s\n", tmp2->str) ;
	list->remove(list, s) ;
	map->del(map, "key") ;
	printf("list size:%d\n", list->size(list) ) ;
	printf("map size:%d\n", map->size(map) ) ;
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$str((tmp = NULL,&tmp), "123$45^67^8") ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  out = Orc$String$replaceAll((out = NULL,&out), tmp, "^", "+^^+") ;
		printf("replaceAll :%s\n", out->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$str((tmp = NULL,&tmp), "123$45^67^8") ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  out = Orc$String$replaceAllByRe((out = NULL,&out), tmp, "\\d+", "d") ;
		printf("replaceAllByRe :%s\n", out->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$str((tmp = NULL,&tmp), "1\\23\\45^67^8") ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  out = Orc$String$replaceAllByRe((out = NULL,&out), tmp, "\\\\+", "/") ;
		printf("replaceAllByRe :%s\n", out->str) ;
	}
	{
		Orc$PrintStyle tmpStructThis1;
		{
			Orc$PrintStyle *  o = Orc$PrintStyle$red((tmpStructThis1 = Orc$mkPrintStyle() ,&tmpStructThis1)) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_735_8 = o->__exit__(o);
		
			printf("hi") ;
		}
	}
}



