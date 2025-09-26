
typedef struct tagOrcLang$String OrcLang$String;
typedef struct tagVtable_OrcLang$String Vtable_OrcLang$String;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef __String_orc_h__
#define __String_orc_h__

//include  importHeadCode
#include "Orc/Orc.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./List_orc.h"
#include "./Map_orc.h"
#include "./Math_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_OrcLang$String {
	Vtable_Object super;
};
//虚表实例
extern Vtable_OrcLang$String _vtable_OrcLang$String;

// class
struct tagOrcLang$String {
	Object super; 
	char *  str ;
	int  _charSize ;
	int  _runeSize ;
	OrcLang$String *  (*addll) (OrcLang$String *  self, long long  i);
	OrcLang$String *  (*addi) (OrcLang$String *  self, int  i);
	OrcLang$String *  (*addf) (OrcLang$String *  self, float  i);
	OrcLang$String *  (*addString) (OrcLang$String *  self, OrcLang$String *  s);
	OrcLang$String *  (*addBytesWithCount) (OrcLang$String *  self, const char *  str, int  count);
	OrcLang$String *  (*add) (OrcLang$String *  self, const char *  str);
	void  (*fillCount) (OrcLang$String *  self, const char *  s, int  count);
	OrcLang$String *  (*set_as_own) (OrcLang$String *  self, char *  str);
	OrcLang$String *  (*set) (OrcLang$String *  self, const char *  str);
	int  (*charSize) (OrcLang$String *  self);
	void  (*expand) (OrcLang$String *  self, int  needSize);
	bool  (*notEquals) (OrcLang$String *  self, const char *  str);
	bool  (*empty) (OrcLang$String *  self);
	bool  (*notEmpty) (OrcLang$String *  self);
	bool  (*equalsIgnoreCase) (OrcLang$String *  self, const char *  str);
	bool  (*equals) (OrcLang$String *  self, const char *  str);
	bool  (*equalsString) (OrcLang$String *  self, OrcLang$String *  str);
	int  (*runeSize) (OrcLang$String *  self);
	int  (*calcRuneSize) (OrcLang$String *  self);
	int  (*size) (OrcLang$String *  self);
	int  (*length) (OrcLang$String *  self);
	OrcLang$String*  (*substring) (OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  end);
	OrcLang$String*  (*substringToEnd) (OrcLang$String **  __outRef__, OrcLang$String *  self, int  start);
	OrcLang$String*  (*_substringByCount) (OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  n);
	OrcLang$String*  (*substringByCount) (OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  n);
	OrcLang$String*  (*substringByByteRange) (OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  end);
	OrcLang$String*  (*substringByByteStart) (OrcLang$String **  __outRef__, OrcLang$String *  self, int  start);
	OrcLang$String*  (*substringByByteCount) (OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  end);
	int  (*indexByteOf) (OrcLang$String *  self, const char *  cstr);
	int  (*lastIndexByteOf) (OrcLang$String *  self, const char *  cstr);
	OrcLang$String*  (*replaceAll) (OrcLang$String **  __outRef__, OrcLang$String *  self, const char *  find, const char *  newStr);
	OrcLang$String*  (*replaceAllByRe) (OrcLang$String **  __outRef__, OrcLang$String *  self, const char *  pattern, const char *  newStr);
	void  (*clear) (OrcLang$String *  self);
	OrcLang$List*  (*splitByRe) (OrcLang$List **  __outRef__, OrcLang$String *  self, const char *  pattern);
};
Vtable_OrcLang$String* Vtable_OrcLang$String_init(Vtable_OrcLang$String* pvt);
void OrcLang$String_init_fields(OrcLang$String *self);
void OrcLang$String_init(OrcLang$String *self);
OrcLang$String * OrcLang$String_new();
void OrcLang$String_fini(OrcLang$String *self);

void  OrcLang$String$dtor(OrcLang$String *  self);
OrcLang$String *  OrcLang$String$addll(OrcLang$String *  self, long long  i);
OrcLang$String *  OrcLang$String$addi(OrcLang$String *  self, int  i);
OrcLang$String *  OrcLang$String$addf(OrcLang$String *  self, float  i);
OrcLang$String *  OrcLang$String$addString(OrcLang$String *  self, OrcLang$String *  s);
OrcLang$String *  OrcLang$String$addBytesWithCount(OrcLang$String *  self, const char *  str, int  count);
OrcLang$String *  OrcLang$String$add(OrcLang$String *  self, const char *  str);
void  OrcLang$String$fillCount(OrcLang$String *  self, const char *  s, int  count);
OrcLang$String *  OrcLang$String$set_as_own(OrcLang$String *  self, char *  str);
OrcLang$String *  OrcLang$String$set(OrcLang$String *  self, const char *  str);
int  OrcLang$String$charSize(OrcLang$String *  self);
void  OrcLang$String$expand(OrcLang$String *  self, int  needSize);
bool  OrcLang$String$notEquals(OrcLang$String *  self, const char *  str);
bool  OrcLang$String$empty(OrcLang$String *  self);
bool  OrcLang$String$notEmpty(OrcLang$String *  self);
bool  OrcLang$String$equalsIgnoreCase(OrcLang$String *  self, const char *  str);
bool  OrcLang$String$equals(OrcLang$String *  self, const char *  str);
bool  OrcLang$String$equalsString(OrcLang$String *  self, OrcLang$String *  str);
int  OrcLang$String$runeSize(OrcLang$String *  self);
int  OrcLang$String$calcRuneSize(OrcLang$String *  self);
int  OrcLang$String$size(OrcLang$String *  self);
int  OrcLang$String$length(OrcLang$String *  self);
OrcLang$String*  OrcLang$String$substring(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  end);
OrcLang$String*  OrcLang$String$substringToEnd(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start);
OrcLang$String*  OrcLang$String$_substringByCount(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  n);
OrcLang$String*  OrcLang$String$substringByCount(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  n);
OrcLang$String*  OrcLang$String$substringByByteRange(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  end);
OrcLang$String*  OrcLang$String$substringByByteStart(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start);
OrcLang$String*  OrcLang$String$substringByByteCount(OrcLang$String **  __outRef__, OrcLang$String *  self, int  start, int  end);
int  OrcLang$String$indexByteOf(OrcLang$String *  self, const char *  cstr);
int  OrcLang$String$lastIndexByteOf(OrcLang$String *  self, const char *  cstr);
OrcLang$String*  OrcLang$String$replaceAll(OrcLang$String **  __outRef__, OrcLang$String *  self, const char *  find, const char *  newStr);
OrcLang$String*  OrcLang$String$replaceAllByRe(OrcLang$String **  __outRef__, OrcLang$String *  self, const char *  pattern, const char *  newStr);
void  OrcLang$String$clear(OrcLang$String *  self);
OrcLang$List*  OrcLang$String$splitByRe(OrcLang$List **  __outRef__, OrcLang$String *  self, const char *  pattern);

OrcLang$String*  OrcLang$strByWcs(OrcLang$String **  __outRef__, const wchar_t *  data);
int  OrcLang$utf8RuneLength(const char *  data);
int  OrcLang$utf8CharLen(const char *  data);
int  OrcLang$utf8NumberCharLen(const char *  data, int  runeCnt);
OrcLang$String*  OrcLang$String_toActiveCodePage(OrcLang$String **  __outRef__, const char *  utf8);
bool  OrcLang$String_startsWith(const char *  s, const char *  find);
bool  OrcLang$strEq(const char *  a, const char *  b);
OrcLang$String*  OrcLang$str(OrcLang$String **  __outRef__, const char *  data);
void  OrcLang$testStr();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
