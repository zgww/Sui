
typedef struct tagSgl$StructArrayBase Sgl$StructArrayBase;
typedef struct tagVtable_Sgl$StructArrayBase Vtable_Sgl$StructArrayBase;
typedef struct tagSgl$CharArray Sgl$CharArray;
typedef struct tagVtable_Sgl$CharArray Vtable_Sgl$CharArray;
typedef struct tagSgl$ShortArray Sgl$ShortArray;
typedef struct tagVtable_Sgl$ShortArray Vtable_Sgl$ShortArray;
typedef struct tagSgl$FloatArray Sgl$FloatArray;
typedef struct tagVtable_Sgl$FloatArray Vtable_Sgl$FloatArray;
typedef struct tagSgl$MatArray Sgl$MatArray;
typedef struct tagVtable_Sgl$MatArray Vtable_Sgl$MatArray;
typedef struct tagSgl$Vec4Array Sgl$Vec4Array;
typedef struct tagVtable_Sgl$Vec4Array Vtable_Sgl$Vec4Array;
typedef struct tagSgl$Vec3Array Sgl$Vec3Array;
typedef struct tagVtable_Sgl$Vec3Array Vtable_Sgl$Vec3Array;
typedef struct tagSgl$Vec2Array Sgl$Vec2Array;
typedef struct tagVtable_Sgl$Vec2Array Vtable_Sgl$Vec2Array;
typedef struct tagSgl$IntArray Sgl$IntArray;
typedef struct tagVtable_Sgl$IntArray Vtable_Sgl$IntArray;
typedef struct tagSgl$Buffer Sgl$Buffer;
typedef struct tagVtable_Sgl$Buffer Vtable_Sgl$Buffer;
typedef struct tagSgl$BufferReader Sgl$BufferReader;
typedef struct tagVtable_Sgl$BufferReader Vtable_Sgl$BufferReader;
typedef struct tagSgl$FloatsProxy Sgl$FloatsProxy;


#ifndef define_struct___Sgl__Buffer_orc_h__
#define define_struct___Sgl__Buffer_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Buffer_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___Sgl__Buffer_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSgl$FloatsProxy {
	float *  data ;
	int  capacity ;
	int  size ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Buffer_orc_h__
#define __Sgl__Buffer_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Quat_orc.h"
#include "../Json/Json_orc.h"
#include "./Mat_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$StructArrayBase {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$StructArrayBase _vtable_Sgl$StructArrayBase;

// class refc:1
struct tagSgl$StructArrayBase {
	Object super; 
	int  size ;
	int  capacity ;
	int  elementSize ;
	void **  (*getPtrData) (Sgl$StructArrayBase *  self);
	char *  (*getRaw) (Sgl$StructArrayBase *  self);
	bool  (*equalsRaw) (Sgl$StructArrayBase *  self, char *  a, char *  b);
	void  (*distinct) (Sgl$StructArrayBase *  self);
	bool  (*hasByRaw) (Sgl$StructArrayBase *  self, char *  data);
	char *  (*getPtrRawAtElement) (Sgl$StructArrayBase *  self, int  index);
	void  (*setRawAtElement) (Sgl$StructArrayBase *  self, int  index, char *  data);
	void  (*setByPtr) (Sgl$StructArrayBase *  self, int  index, void *  data);
	void  (*appendByCount) (Sgl$StructArrayBase *  self, void *  data, int  count);
	void  (*clear) (Sgl$StructArrayBase *  self);
	void  (*expandToSize) (Sgl$StructArrayBase *  self, int  toSize);
	void  (*expandIfNeed) (Sgl$StructArrayBase *  self, int  addEleSize);
	void  (*expandCapacity) (Sgl$StructArrayBase *  self, int  needSize);
};
Vtable_Sgl$StructArrayBase* Vtable_Sgl$StructArrayBase_init(Vtable_Sgl$StructArrayBase* pvt);
void Sgl$StructArrayBase_init_fields(Sgl$StructArrayBase *self);
void Sgl$StructArrayBase_init(Sgl$StructArrayBase *self, void *pOwner);
Sgl$StructArrayBase * Sgl$StructArrayBase_new(void *pOwner);
void Sgl$StructArrayBase_fini(Sgl$StructArrayBase *self);

void **  Sgl$StructArrayBase$getPtrData(Sgl$StructArrayBase *  self);
char *  Sgl$StructArrayBase$getRaw(Sgl$StructArrayBase *  self);
bool  Sgl$StructArrayBase$equalsRaw(Sgl$StructArrayBase *  self, char *  a, char *  b);
void  Sgl$StructArrayBase$distinct(Sgl$StructArrayBase *  self);
bool  Sgl$StructArrayBase$hasByRaw(Sgl$StructArrayBase *  self, char *  data);
char *  Sgl$StructArrayBase$getPtrRawAtElement(Sgl$StructArrayBase *  self, int  index);
void  Sgl$StructArrayBase$setRawAtElement(Sgl$StructArrayBase *  self, int  index, char *  data);
void  Sgl$StructArrayBase$setByPtr(Sgl$StructArrayBase *  self, int  index, void *  data);
void  Sgl$StructArrayBase$appendByCount(Sgl$StructArrayBase *  self, void *  data, int  count);
void  Sgl$StructArrayBase$clear(Sgl$StructArrayBase *  self);
void  Sgl$StructArrayBase$expandToSize(Sgl$StructArrayBase *  self, int  toSize);
void  Sgl$StructArrayBase$expandIfNeed(Sgl$StructArrayBase *  self, int  addEleSize);
void  Sgl$StructArrayBase$expandCapacity(Sgl$StructArrayBase *  self, int  needSize);


// 虚表
struct tagVtable_Sgl$CharArray {
	Vtable_Sgl$StructArrayBase super;
};
//虚表实例
extern Vtable_Sgl$CharArray _vtable_Sgl$CharArray;

// class refc:0
struct tagSgl$CharArray {
	Sgl$StructArrayBase super; 
	char *  data ;
	Orc$String*  (*toString) (Orc$String **  __outRef__, Sgl$CharArray *  self);
	char  (*get) (Sgl$CharArray *  self, int  i);
	bool  (*set) (Sgl$CharArray *  self, int  i, char  v);
	void  (*add) (Sgl$CharArray *  self, char  v);
	bool  (*has) (Sgl$CharArray *  self, char  v);
};
Vtable_Sgl$CharArray* Vtable_Sgl$CharArray_init(Vtable_Sgl$CharArray* pvt);
void Sgl$CharArray_init_fields(Sgl$CharArray *self);
void Sgl$CharArray_init(Sgl$CharArray *self, void *pOwner);
Sgl$CharArray * Sgl$CharArray_new(void *pOwner);
void Sgl$CharArray_fini(Sgl$CharArray *self);

void  Sgl$CharArray$ctor(Sgl$CharArray *  self);
Orc$String*  Sgl$CharArray$toString(Orc$String **  __outRef__, Sgl$CharArray *  self);
void **  Sgl$CharArray$getPtrData(Sgl$CharArray *  self);
char *  Sgl$CharArray$getRaw(Sgl$CharArray *  self);
char  Sgl$CharArray$get(Sgl$CharArray *  self, int  i);
bool  Sgl$CharArray$set(Sgl$CharArray *  self, int  i, char  v);
void  Sgl$CharArray$add(Sgl$CharArray *  self, char  v);
bool  Sgl$CharArray$has(Sgl$CharArray *  self, char  v);


// 虚表
struct tagVtable_Sgl$ShortArray {
	Vtable_Sgl$StructArrayBase super;
};
//虚表实例
extern Vtable_Sgl$ShortArray _vtable_Sgl$ShortArray;

// class refc:0
struct tagSgl$ShortArray {
	Sgl$StructArrayBase super; 
	short *  data ;
	short  (*get) (Sgl$ShortArray *  self, int  i);
	bool  (*set) (Sgl$ShortArray *  self, int  i, short  v);
	void  (*add) (Sgl$ShortArray *  self, short  v);
	bool  (*has) (Sgl$ShortArray *  self, short  v);
};
Vtable_Sgl$ShortArray* Vtable_Sgl$ShortArray_init(Vtable_Sgl$ShortArray* pvt);
void Sgl$ShortArray_init_fields(Sgl$ShortArray *self);
void Sgl$ShortArray_init(Sgl$ShortArray *self, void *pOwner);
Sgl$ShortArray * Sgl$ShortArray_new(void *pOwner);
void Sgl$ShortArray_fini(Sgl$ShortArray *self);

void  Sgl$ShortArray$ctor(Sgl$ShortArray *  self);
void **  Sgl$ShortArray$getPtrData(Sgl$ShortArray *  self);
char *  Sgl$ShortArray$getRaw(Sgl$ShortArray *  self);
short  Sgl$ShortArray$get(Sgl$ShortArray *  self, int  i);
bool  Sgl$ShortArray$set(Sgl$ShortArray *  self, int  i, short  v);
void  Sgl$ShortArray$add(Sgl$ShortArray *  self, short  v);
bool  Sgl$ShortArray$has(Sgl$ShortArray *  self, short  v);


// 虚表
struct tagVtable_Sgl$FloatArray {
	Vtable_Sgl$StructArrayBase super;
};
//虚表实例
extern Vtable_Sgl$FloatArray _vtable_Sgl$FloatArray;

// class refc:0
struct tagSgl$FloatArray {
	Sgl$StructArrayBase super; 
	float *  data ;
	float  (*get) (Sgl$FloatArray *  self, int  i);
	bool  (*set) (Sgl$FloatArray *  self, int  i, float  v);
	void  (*appendFloat3) (Sgl$FloatArray *  self, float  a, float  b, float  c);
	void  (*add) (Sgl$FloatArray *  self, float  v);
	bool  (*has) (Sgl$FloatArray *  self, float  v);
};
Vtable_Sgl$FloatArray* Vtable_Sgl$FloatArray_init(Vtable_Sgl$FloatArray* pvt);
void Sgl$FloatArray_init_fields(Sgl$FloatArray *self);
void Sgl$FloatArray_init(Sgl$FloatArray *self, void *pOwner);
Sgl$FloatArray * Sgl$FloatArray_new(void *pOwner);
void Sgl$FloatArray_fini(Sgl$FloatArray *self);

void  Sgl$FloatArray$ctor(Sgl$FloatArray *  self);
void **  Sgl$FloatArray$getPtrData(Sgl$FloatArray *  self);
char *  Sgl$FloatArray$getRaw(Sgl$FloatArray *  self);
float  Sgl$FloatArray$get(Sgl$FloatArray *  self, int  i);
bool  Sgl$FloatArray$set(Sgl$FloatArray *  self, int  i, float  v);
void  Sgl$FloatArray$appendFloat3(Sgl$FloatArray *  self, float  a, float  b, float  c);
void  Sgl$FloatArray$add(Sgl$FloatArray *  self, float  v);
bool  Sgl$FloatArray$has(Sgl$FloatArray *  self, float  v);


// 虚表
struct tagVtable_Sgl$MatArray {
	Vtable_Sgl$StructArrayBase super;
};
//虚表实例
extern Vtable_Sgl$MatArray _vtable_Sgl$MatArray;

// class refc:0
struct tagSgl$MatArray {
	Sgl$StructArrayBase super; 
	Sgl$Mat *  data ;
	Sgl$Mat (*get) (Sgl$MatArray *  self, int  i);
	bool  (*set) (Sgl$MatArray *  self, int  i, Sgl$Mat v);
	void  (*add) (Sgl$MatArray *  self, Sgl$Mat v);
	bool  (*has) (Sgl$MatArray *  self, Sgl$Mat v);
};
Vtable_Sgl$MatArray* Vtable_Sgl$MatArray_init(Vtable_Sgl$MatArray* pvt);
void Sgl$MatArray_init_fields(Sgl$MatArray *self);
void Sgl$MatArray_init(Sgl$MatArray *self, void *pOwner);
Sgl$MatArray * Sgl$MatArray_new(void *pOwner);
void Sgl$MatArray_fini(Sgl$MatArray *self);

void  Sgl$MatArray$ctor(Sgl$MatArray *  self);
void **  Sgl$MatArray$getPtrData(Sgl$MatArray *  self);
char *  Sgl$MatArray$getRaw(Sgl$MatArray *  self);
Sgl$Mat Sgl$MatArray$get(Sgl$MatArray *  self, int  i);
bool  Sgl$MatArray$set(Sgl$MatArray *  self, int  i, Sgl$Mat v);
void  Sgl$MatArray$add(Sgl$MatArray *  self, Sgl$Mat v);
bool  Sgl$MatArray$has(Sgl$MatArray *  self, Sgl$Mat v);


// 虚表
struct tagVtable_Sgl$Vec4Array {
	Vtable_Sgl$StructArrayBase super;
};
//虚表实例
extern Vtable_Sgl$Vec4Array _vtable_Sgl$Vec4Array;

// class refc:0
struct tagSgl$Vec4Array {
	Sgl$StructArrayBase super; 
	SuiCore$Vec4 *  data ;
	SuiCore$Vec4 (*get) (Sgl$Vec4Array *  self, int  i);
	bool  (*set) (Sgl$Vec4Array *  self, int  i, SuiCore$Vec4 v);
	void  (*add) (Sgl$Vec4Array *  self, SuiCore$Vec4 v);
	bool  (*has) (Sgl$Vec4Array *  self, SuiCore$Vec4 v);
};
Vtable_Sgl$Vec4Array* Vtable_Sgl$Vec4Array_init(Vtable_Sgl$Vec4Array* pvt);
void Sgl$Vec4Array_init_fields(Sgl$Vec4Array *self);
void Sgl$Vec4Array_init(Sgl$Vec4Array *self, void *pOwner);
Sgl$Vec4Array * Sgl$Vec4Array_new(void *pOwner);
void Sgl$Vec4Array_fini(Sgl$Vec4Array *self);

void  Sgl$Vec4Array$ctor(Sgl$Vec4Array *  self);
void **  Sgl$Vec4Array$getPtrData(Sgl$Vec4Array *  self);
char *  Sgl$Vec4Array$getRaw(Sgl$Vec4Array *  self);
SuiCore$Vec4 Sgl$Vec4Array$get(Sgl$Vec4Array *  self, int  i);
bool  Sgl$Vec4Array$set(Sgl$Vec4Array *  self, int  i, SuiCore$Vec4 v);
void  Sgl$Vec4Array$add(Sgl$Vec4Array *  self, SuiCore$Vec4 v);
bool  Sgl$Vec4Array$has(Sgl$Vec4Array *  self, SuiCore$Vec4 v);


// 虚表
struct tagVtable_Sgl$Vec3Array {
	Vtable_Sgl$StructArrayBase super;
};
//虚表实例
extern Vtable_Sgl$Vec3Array _vtable_Sgl$Vec3Array;

// class refc:0
struct tagSgl$Vec3Array {
	Sgl$StructArrayBase super; 
	SuiCore$Vec3 *  data ;
	Orc$String*  (*toString) (Orc$String **  __outRef__, Sgl$Vec3Array *  self);
	SuiCore$Vec3 (*get) (Sgl$Vec3Array *  self, int  i);
	bool  (*set) (Sgl$Vec3Array *  self, int  i, SuiCore$Vec3 v);
	void  (*add) (Sgl$Vec3Array *  self, SuiCore$Vec3 v);
	bool  (*has) (Sgl$Vec3Array *  self, SuiCore$Vec3 v);
};
Vtable_Sgl$Vec3Array* Vtable_Sgl$Vec3Array_init(Vtable_Sgl$Vec3Array* pvt);
void Sgl$Vec3Array_init_fields(Sgl$Vec3Array *self);
void Sgl$Vec3Array_init(Sgl$Vec3Array *self, void *pOwner);
Sgl$Vec3Array * Sgl$Vec3Array_new(void *pOwner);
void Sgl$Vec3Array_fini(Sgl$Vec3Array *self);

Orc$String*  Sgl$Vec3Array$toString(Orc$String **  __outRef__, Sgl$Vec3Array *  self);
void  Sgl$Vec3Array$ctor(Sgl$Vec3Array *  self);
void **  Sgl$Vec3Array$getPtrData(Sgl$Vec3Array *  self);
char *  Sgl$Vec3Array$getRaw(Sgl$Vec3Array *  self);
SuiCore$Vec3 Sgl$Vec3Array$get(Sgl$Vec3Array *  self, int  i);
bool  Sgl$Vec3Array$set(Sgl$Vec3Array *  self, int  i, SuiCore$Vec3 v);
void  Sgl$Vec3Array$add(Sgl$Vec3Array *  self, SuiCore$Vec3 v);
bool  Sgl$Vec3Array$has(Sgl$Vec3Array *  self, SuiCore$Vec3 v);


// 虚表
struct tagVtable_Sgl$Vec2Array {
	Vtable_Sgl$StructArrayBase super;
};
//虚表实例
extern Vtable_Sgl$Vec2Array _vtable_Sgl$Vec2Array;

// class refc:0
struct tagSgl$Vec2Array {
	Sgl$StructArrayBase super; 
	SuiCore$Vec2 *  data ;
	SuiCore$Vec2 (*get) (Sgl$Vec2Array *  self, int  i);
	bool  (*set) (Sgl$Vec2Array *  self, int  i, SuiCore$Vec2 v);
	void  (*add) (Sgl$Vec2Array *  self, SuiCore$Vec2 v);
	bool  (*has) (Sgl$Vec2Array *  self, SuiCore$Vec2 v);
};
Vtable_Sgl$Vec2Array* Vtable_Sgl$Vec2Array_init(Vtable_Sgl$Vec2Array* pvt);
void Sgl$Vec2Array_init_fields(Sgl$Vec2Array *self);
void Sgl$Vec2Array_init(Sgl$Vec2Array *self, void *pOwner);
Sgl$Vec2Array * Sgl$Vec2Array_new(void *pOwner);
void Sgl$Vec2Array_fini(Sgl$Vec2Array *self);

void  Sgl$Vec2Array$ctor(Sgl$Vec2Array *  self);
void **  Sgl$Vec2Array$getPtrData(Sgl$Vec2Array *  self);
char *  Sgl$Vec2Array$getRaw(Sgl$Vec2Array *  self);
SuiCore$Vec2 Sgl$Vec2Array$get(Sgl$Vec2Array *  self, int  i);
bool  Sgl$Vec2Array$set(Sgl$Vec2Array *  self, int  i, SuiCore$Vec2 v);
void  Sgl$Vec2Array$add(Sgl$Vec2Array *  self, SuiCore$Vec2 v);
bool  Sgl$Vec2Array$has(Sgl$Vec2Array *  self, SuiCore$Vec2 v);


// 虚表
struct tagVtable_Sgl$IntArray {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$IntArray _vtable_Sgl$IntArray;

// class refc:0
struct tagSgl$IntArray {
	Object super; 
	int *  data ;
	int  size ;
	int  capacity ;
};
Vtable_Sgl$IntArray* Vtable_Sgl$IntArray_init(Vtable_Sgl$IntArray* pvt);
void Sgl$IntArray_init_fields(Sgl$IntArray *self);
void Sgl$IntArray_init(Sgl$IntArray *self, void *pOwner);
Sgl$IntArray * Sgl$IntArray_new(void *pOwner);
void Sgl$IntArray_fini(Sgl$IntArray *self);

void  Sgl$IntArray$dtor(Sgl$IntArray *  self);

Orc$String*  Sgl$IntArray$toString(Orc$String **  __outRef__, Sgl$IntArray *  self);
bool  Sgl$IntArray$removeFirst(Sgl$IntArray *  self, int  v);
bool  Sgl$IntArray$has(Sgl$IntArray *  self, int  v);
int  Sgl$IntArray$get(Sgl$IntArray *  self, int  idx);
int  Sgl$IntArray$at(Sgl$IntArray *  self, int  idx);
void  Sgl$IntArray$set(Sgl$IntArray *  self, int  idx, int  v);
void  Sgl$IntArray$clear(Sgl$IntArray *  self);
void  Sgl$IntArray$pop(Sgl$IntArray *  self, int  count);
void  Sgl$IntArray$initSize(Sgl$IntArray *  self, int  size);
Sgl$IntArray *  Sgl$IntArray$appendByCount(Sgl$IntArray *  self, void *  data, int  cnt);
Sgl$IntArray *  Sgl$IntArray$appendValueByCount(Sgl$IntArray *  self, int  v, int  cnt);
Sgl$IntArray *  Sgl$IntArray$append(Sgl$IntArray *  self, int  v);
bool  Sgl$IntArray$removeRange(Sgl$IntArray *  self, int  fromIndex, int  to);
void  Sgl$IntArray$expandIfNeed(Sgl$IntArray *  self, int  addIntSize);
void  Sgl$IntArray$expandCapacity(Sgl$IntArray *  self, int  needSize);
void  Sgl$IntArray$fromJson(Sgl$IntArray *  self, Json$Json *  ja);
Json$Json*  Sgl$IntArray$mkJson(Json$Json **  __outRef__, Sgl$IntArray *  self);

// 虚表
struct tagVtable_Sgl$Buffer {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Buffer _vtable_Sgl$Buffer;

// class refc:0
struct tagSgl$Buffer {
	Object super; 
	unsigned char *  data ;
	int  size ;
	int  capacity ;
};
Vtable_Sgl$Buffer* Vtable_Sgl$Buffer_init(Vtable_Sgl$Buffer* pvt);
void Sgl$Buffer_init_fields(Sgl$Buffer *self);
void Sgl$Buffer_init(Sgl$Buffer *self, void *pOwner);
Sgl$Buffer * Sgl$Buffer_new(void *pOwner);
void Sgl$Buffer_fini(Sgl$Buffer *self);

void  Sgl$Buffer$dtor(Sgl$Buffer *  self);

void  Sgl$Buffer$initSize(Sgl$Buffer *  self, int  size);
Orc$String*  Sgl$Buffer$toFloatString(Orc$String **  __outRef__, Sgl$Buffer *  self);
Orc$String*  Sgl$Buffer$toIntString(Orc$String **  __outRef__, Sgl$Buffer *  self);
int  Sgl$Buffer$doubleSize(Sgl$Buffer *  self);
int  Sgl$Buffer$floatSize(Sgl$Buffer *  self);
int  Sgl$Buffer$intSize(Sgl$Buffer *  self);
Sgl$Buffer *  Sgl$Buffer$appendBuffer(Sgl$Buffer *  self, Sgl$Buffer *  buf);
Sgl$Buffer *  Sgl$Buffer$appendChars(Sgl$Buffer *  self, char *  data, int  size);
Sgl$Buffer *  Sgl$Buffer$append(Sgl$Buffer *  self, unsigned char *  data, int  size);
Sgl$Buffer *  Sgl$Buffer$appendFloat(Sgl$Buffer *  self, float  v);
Sgl$Buffer *  Sgl$Buffer$appendFloat4(Sgl$Buffer *  self, float  a, float  b, float  c, float  d);
Sgl$Buffer *  Sgl$Buffer$appendVec3(Sgl$Buffer *  self, SuiCore$Vec3 v3);
Sgl$Buffer *  Sgl$Buffer$appendFloat3(Sgl$Buffer *  self, float  a, float  b, float  c);
Sgl$Buffer *  Sgl$Buffer$appendFloat2(Sgl$Buffer *  self, float  v, float  b);
Sgl$Buffer *  Sgl$Buffer$appendFloats(Sgl$Buffer *  self, float *  data, int  floatCount);
Sgl$Buffer *  Sgl$Buffer$appendCstr(Sgl$Buffer *  self, char *  str);
Sgl$Buffer *  Sgl$Buffer$appendInt(Sgl$Buffer *  self, int  v);
Sgl$Buffer *  Sgl$Buffer$appendInt3(Sgl$Buffer *  self, int  a, int  b, int  c);
Sgl$Buffer *  Sgl$Buffer$appendInts(Sgl$Buffer *  self, int *  data, int  intCount);
void  Sgl$Buffer$clear(Sgl$Buffer *  self);
void  Sgl$Buffer$pop(Sgl$Buffer *  self, int  count);
bool  Sgl$Buffer$removeRange(Sgl$Buffer *  self, int  fromIndex, int  to);
void  Sgl$Buffer$expandIfNeed(Sgl$Buffer *  self, int  addByteSize);
void  Sgl$Buffer$expandCapacity(Sgl$Buffer *  self, int  needSize);
extern Sgl$Buffer*  Sgl$Buffer_readFile(Sgl$Buffer **  __outRef__, const char *  path);

// 虚表
struct tagVtable_Sgl$BufferReader {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$BufferReader _vtable_Sgl$BufferReader;

// class refc:0
struct tagSgl$BufferReader {
	Object super; 
	Sgl$Buffer*  buffer ;
	int  index ;
	Sgl$BufferReader *  (*init) (Sgl$BufferReader *  self, Sgl$Buffer *  buffer);
	int  (*remaining) (Sgl$BufferReader *  self);
	void  (*advance) (Sgl$BufferReader *  self, int  byteLen);
	void  (*readBinary) (Sgl$BufferReader *  self, void *  p, int  byteLen);
	Orc$String*  (*readString) (Orc$String **  __outRef__, Sgl$BufferReader *  self, int  byteLen);
	unsigned char  (*readUint8) (Sgl$BufferReader *  self);
	void  (*readChars) (Sgl$BufferReader *  self, char *  dst, int  cnt, bool  setNullTail);
	unsigned char  (*readByte) (Sgl$BufferReader *  self);
	short  (*readInt16) (Sgl$BufferReader *  self);
	short  (*readShort) (Sgl$BufferReader *  self);
	int  (*readInt) (Sgl$BufferReader *  self);
	long long  (*readLongLong) (Sgl$BufferReader *  self);
	Sgl$CharArray*  (*readCharArray) (Sgl$CharArray **  __outRef__, Sgl$BufferReader *  self, int  cnt);
	Sgl$ShortArray*  (*readShortArray) (Sgl$ShortArray **  __outRef__, Sgl$BufferReader *  self, int  cnt);
	Sgl$IntArray*  (*readIntArray) (Sgl$IntArray **  __outRef__, Sgl$BufferReader *  self, int  cnt);
	Sgl$Vec2Array*  (*readVec2Array) (Sgl$Vec2Array **  __outRef__, Sgl$BufferReader *  self, int  cnt);
	Sgl$Vec4Array*  (*readVec4Array) (Sgl$Vec4Array **  __outRef__, Sgl$BufferReader *  self, int  cnt);
	Sgl$Vec3Array*  (*readVec3Array) (Sgl$Vec3Array **  __outRef__, Sgl$BufferReader *  self, int  cnt);
	SuiCore$Vec3 (*readVec3) (Sgl$BufferReader *  self);
	SuiCore$Vec4 (*readVec4) (Sgl$BufferReader *  self);
	SuiCore$Quat (*readQuat) (Sgl$BufferReader *  self);
	float  (*readFloat) (Sgl$BufferReader *  self);
	double  (*readDouble) (Sgl$BufferReader *  self);
};
Vtable_Sgl$BufferReader* Vtable_Sgl$BufferReader_init(Vtable_Sgl$BufferReader* pvt);
void Sgl$BufferReader_init_fields(Sgl$BufferReader *self);
void Sgl$BufferReader_init(Sgl$BufferReader *self, void *pOwner);
Sgl$BufferReader * Sgl$BufferReader_new(void *pOwner);
void Sgl$BufferReader_fini(Sgl$BufferReader *self);

Sgl$BufferReader *  Sgl$BufferReader$init(Sgl$BufferReader *  self, Sgl$Buffer *  buffer);
int  Sgl$BufferReader$remaining(Sgl$BufferReader *  self);
void  Sgl$BufferReader$advance(Sgl$BufferReader *  self, int  byteLen);
void  Sgl$BufferReader$readBinary(Sgl$BufferReader *  self, void *  p, int  byteLen);
Orc$String*  Sgl$BufferReader$readString(Orc$String **  __outRef__, Sgl$BufferReader *  self, int  byteLen);
unsigned char  Sgl$BufferReader$readUint8(Sgl$BufferReader *  self);
void  Sgl$BufferReader$readChars(Sgl$BufferReader *  self, char *  dst, int  cnt, bool  setNullTail);
unsigned char  Sgl$BufferReader$readByte(Sgl$BufferReader *  self);
short  Sgl$BufferReader$readInt16(Sgl$BufferReader *  self);
short  Sgl$BufferReader$readShort(Sgl$BufferReader *  self);
int  Sgl$BufferReader$readInt(Sgl$BufferReader *  self);
long long  Sgl$BufferReader$readLongLong(Sgl$BufferReader *  self);
Sgl$CharArray*  Sgl$BufferReader$readCharArray(Sgl$CharArray **  __outRef__, Sgl$BufferReader *  self, int  cnt);
Sgl$ShortArray*  Sgl$BufferReader$readShortArray(Sgl$ShortArray **  __outRef__, Sgl$BufferReader *  self, int  cnt);
Sgl$IntArray*  Sgl$BufferReader$readIntArray(Sgl$IntArray **  __outRef__, Sgl$BufferReader *  self, int  cnt);
Sgl$Vec2Array*  Sgl$BufferReader$readVec2Array(Sgl$Vec2Array **  __outRef__, Sgl$BufferReader *  self, int  cnt);
Sgl$Vec4Array*  Sgl$BufferReader$readVec4Array(Sgl$Vec4Array **  __outRef__, Sgl$BufferReader *  self, int  cnt);
Sgl$Vec3Array*  Sgl$BufferReader$readVec3Array(Sgl$Vec3Array **  __outRef__, Sgl$BufferReader *  self, int  cnt);
SuiCore$Vec3 Sgl$BufferReader$readVec3(Sgl$BufferReader *  self);
SuiCore$Vec4 Sgl$BufferReader$readVec4(Sgl$BufferReader *  self);
SuiCore$Quat Sgl$BufferReader$readQuat(Sgl$BufferReader *  self);
float  Sgl$BufferReader$readFloat(Sgl$BufferReader *  self);
double  Sgl$BufferReader$readDouble(Sgl$BufferReader *  self);

Sgl$BufferReader*  Sgl$mkBufferReader(Sgl$BufferReader **  __outRef__, Sgl$Buffer *  buffer);
Sgl$Buffer*  Sgl$mkBufferFloatByJsonArray(Sgl$Buffer **  __outRef__, Json$Json*  jo);
Sgl$Buffer*  Sgl$mkBufferIntByJsonArray(Sgl$Buffer **  __outRef__, Json$Json*  jo);


//结构体元数据获取即初始化
MetaStruct* Sgl$FloatsProxy_getOrInitMetaStruct();

Sgl$FloatsProxy Sgl$mkFloatsProxy(float *  floats, int  capacity);
void  Sgl$FloatsProxy$fillRemainsByValue(Sgl$FloatsProxy *  self, float  v);
void  Sgl$FloatsProxy$appendFloats(Sgl$FloatsProxy *  self, float *  a, int  cnt);
void  Sgl$FloatsProxy$appendFloat(Sgl$FloatsProxy *  self, float  v);
void  Sgl$FloatsProxy$appendFloat2(Sgl$FloatsProxy *  self, float  a, float  b);
void  Sgl$FloatsProxy$appendFloat3(Sgl$FloatsProxy *  self, float  a, float  b, float  c);
void  Sgl$FloatsProxy$appendFloat4(Sgl$FloatsProxy *  self, float  a, float  b, float  c, float  d);
void  Sgl$FloatsProxy$distinctSelf(Sgl$FloatsProxy *  self);
bool  Sgl$FloatsProxy$distinctTo(Sgl$FloatsProxy *  self, Sgl$FloatsProxy *  fp);
bool  Sgl$FloatsProxy$has(Sgl$FloatsProxy *  self, float  v);
void  Sgl$FloatsProxy$setAllCapacity(Sgl$FloatsProxy *  self, float  v);
void  Sgl$FloatsProxy$set(Sgl$FloatsProxy *  self, int  i, float  v);
void  Sgl$FloatsProxy$append(Sgl$FloatsProxy *  self, float  v);
void  Sgl$FloatsProxy$clear(Sgl$FloatsProxy *  self);
bool  Sgl$FloatsProxy$removeRange(Sgl$FloatsProxy *  self, int  fromIndex, int  toExcludeIndex);
void  Sgl$Floats_bubbleSort(float *  arr, int  len, bool  asc);
int  Sgl$Floats_distinct(float *  floats, int  cnt);
int  Sgl$Floats_distinctTo(float *  floats, float *  target, int  cnt);
bool  Sgl$Floats_has(float *  floats, int  cnt, float  value);
void  Sgl$Floats_set(float *  floats, int  cnt, float  value);
void  Sgl$testIntArray();
void  Sgl$testBuffer();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
