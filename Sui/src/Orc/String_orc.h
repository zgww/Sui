
typedef struct tagOrc$String Orc$String;
typedef struct tagVtable_Orc$String Vtable_Orc$String;
typedef struct tagOrc$PrintStyle Orc$PrintStyle;


#ifndef define_struct___Orc__String_orc_h__
#define define_struct___Orc__String_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__String_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCLUDE_ONLY_TYPE
#include "./ScopeData_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___Orc__String_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagOrc$PrintStyle {
	int  color ;
	int  bg ;
	int  code ;
	Orc$ScopeData (*__exit__)(void *  _self);
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__String_orc_h__
#define __Orc__String_orc_h__

//include  importHeadCode
#include "./List_orc.h"
#include "./Map_orc.h"
#include "./Math_orc.h"
#include "./ScopeData_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Orc$String {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Orc$String _vtable_Orc$String;

// class refc:0
struct tagOrc$String {
	Object super; 
	char *  str ;
	int  _charSize ;
	int  _runeSize ;
	int  capacity ;
};
Vtable_Orc$String* Vtable_Orc$String_init(Vtable_Orc$String* pvt);
void Orc$String_init_fields(Orc$String *self);
void Orc$String_init(Orc$String *self, void *pOwner);
Orc$String * Orc$String_new(void *pOwner);
void Orc$String_fini(Orc$String *self);

void  Orc$String$dtor(Orc$String *  self);

extern Orc$String*  Orc$strByWcs(Orc$String **  __outRef__, const wchar_t *  data);
extern int  Orc$utf8RuneLength(const char *  data);
extern int  Orc$utf8CharLen(const char *  data);
extern int  Orc$utf8NumberCharLen(const char *  data, int  runeCnt);
extern Orc$String*  Orc$String_toActiveCodePage(Orc$String **  __outRef__, const char *  utf8);
Orc$String*  Orc$String_join(Orc$String **  __outRef__, Orc$List *  list, const char *  dep);
bool  Orc$String_startsWith(const char *  s, const char *  find);
bool  Orc$String_endsWithIgnoreCase(const char *  s, const char *  find);
bool  Orc$String_endsWith(const char *  s, const char *  find);
bool  Orc$strEq(const char *  a, const char *  b);
Orc$String*  Orc$str(Orc$String **  __outRef__, const char *  data);
int  Orc$String$toInt(Orc$String *  self);
float  Orc$String$toFloat(Orc$String *  self);
Orc$String *  Orc$String$addPtr(Orc$String *  self, void *  p);
Orc$String *  Orc$String$addll(Orc$String *  self, long long  i);
Orc$String *  Orc$String$addc(Orc$String *  self, char  c);
Orc$String *  Orc$String$addi(Orc$String *  self, int  i);
Orc$String *  Orc$String$addf(Orc$String *  self, float  i);
Orc$String *  Orc$String$addDouble(Orc$String *  self, double  i);
Orc$String *  Orc$String$addString(Orc$String *  self, Orc$String *  s);
Orc$String *  Orc$String$addBytesWithCount(Orc$String *  self, const char *  str, int  count);
Orc$String *  Orc$String$add(Orc$String *  self, const char *  str);
void  Orc$String$fillCount(Orc$String *  self, const char *  s, int  count);
Orc$String *  Orc$String$set_as_own(Orc$String *  self, char *  str);
Orc$String *  Orc$String$set(Orc$String *  self, const char *  str);
int  Orc$String$charSize(Orc$String *  self);
void  Orc$String$expand(Orc$String *  self, int  needSize);
Orc$String*  Orc$String$trimLeft(Orc$String **  __outRef__, Orc$String *  self);
Orc$String*  Orc$String$trimRight(Orc$String **  __outRef__, Orc$String *  self);
Orc$String*  Orc$String$trim(Orc$String **  __outRef__, Orc$String *  self);
Orc$String*  Orc$String$trimChars(Orc$String **  __outRef__, Orc$String *  self, const char *  chars, bool  trimLeft, bool  trimRight);
Orc$String*  Orc$String$substring(Orc$String **  __outRef__, Orc$String *  self, int  start, int  end);
Orc$String*  Orc$String$substringToEnd(Orc$String **  __outRef__, Orc$String *  self, int  start);
extern Orc$String*  Orc$String$_substringByCount(Orc$String **  __outRef__, Orc$String *  self, int  start, int  n);
Orc$String*  Orc$String$substringByCount(Orc$String **  __outRef__, Orc$String *  self, int  start, int  n);
Orc$String*  Orc$String$substringByByteRange(Orc$String **  __outRef__, Orc$String *  self, int  start, int  end);
Orc$String*  Orc$String$substringByByteStart(Orc$String **  __outRef__, Orc$String *  self, int  start);
Orc$String*  Orc$String$substringByByteCount(Orc$String **  __outRef__, Orc$String *  self, int  start, int  count);
int  Orc$String$indexByteOf(Orc$String *  self, const char *  cstr);
int  Orc$String$lastIndexByteOf(Orc$String *  self, const char *  cstr);
extern Orc$String*  Orc$String$replaceAll(Orc$String **  __outRef__, Orc$String *  self, const char *  find, const char *  newStr);
extern Orc$String*  Orc$String$replaceAllByRe(Orc$String **  __outRef__, Orc$String *  self, const char *  pattern, const char *  newStr);
void  Orc$String$clear(Orc$String *  self);
extern Orc$List*  Orc$String$splitByRe(Orc$List **  __outRef__, Orc$String *  self, const char *  pattern);
Orc$List*  Orc$String$splitToLines(Orc$List **  __outRef__, Orc$String *  self);
Orc$String*  Orc$String$clone(Orc$String **  __outRef__, Orc$String *  self);
int  Orc$String$runeSize(Orc$String *  self);
extern int  Orc$String$calcRuneSize(Orc$String *  self);
int  Orc$String$size(Orc$String *  self);
int  Orc$String$length(Orc$String *  self);
bool  Orc$String$equalsIgnoreCase(Orc$String *  self, const char *  str);
bool  Orc$String$equals(Orc$String *  self, const char *  str);
bool  Orc$String$equalsString(Orc$String *  self, Orc$String *  str);
bool  Orc$String$notEquals(Orc$String *  self, const char *  str);
bool  Orc$String$empty(Orc$String *  self);
bool  Orc$String$notEmpty(Orc$String *  self);
bool  Orc$String$startsWith(Orc$String *  self, const char *  find);
bool  Orc$String$endsWith(Orc$String *  self, const char *  find);


//结构体元数据获取即初始化
MetaStruct* Orc$PrintStyle_getOrInitMetaStruct();

Orc$PrintStyle *  Orc$PrintStyle$black(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$red(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$green(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$yellow(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$blue(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$purple(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$cyan(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$white(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$bgblack(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$bgred(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$bggreen(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$bgyellow(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$bgblue(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$bgpurple(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$bgcyan(Orc$PrintStyle *  self);
Orc$PrintStyle *  Orc$PrintStyle$bgwhite(Orc$PrintStyle *  self);
Orc$PrintStyle Orc$mkPrintStyle();
void  Orc$PrintStyle_exit(Orc$ScopeData *  scopeData);
void  Orc$testOk(bool  ok, const char *  msg);
void  Orc$testStr();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
