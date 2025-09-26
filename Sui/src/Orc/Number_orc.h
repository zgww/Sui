
typedef struct tagOrc$Number Orc$Number;
typedef struct tagVtable_Orc$Number Vtable_Orc$Number;
typedef struct tagOrc$Integer Orc$Integer;
typedef struct tagVtable_Orc$Integer Vtable_Orc$Integer;
typedef struct tagOrc$Boolean Orc$Boolean;
typedef struct tagVtable_Orc$Boolean Vtable_Orc$Boolean;
typedef struct tagOrc$Float Orc$Float;
typedef struct tagVtable_Orc$Float Vtable_Orc$Float;
typedef struct tagOrc$Double Orc$Double;
typedef struct tagVtable_Orc$Double Vtable_Orc$Double;
typedef struct tagOrc$StructObj Orc$StructObj;
typedef struct tagVtable_Orc$StructObj Vtable_Orc$StructObj;


#ifndef define_struct___Orc__Number_orc_h__
#define define_struct___Orc__Number_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__Number_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "./Orc.h"
#include <string.h>




#ifdef INCLUDE_ONLY_TYPE___Orc__Number_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__Number_orc_h__
#define __Orc__Number_orc_h__

//include  importHeadCode
#include "./String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Orc$Number {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Orc$Number _vtable_Orc$Number;

// class refc:1
struct tagOrc$Number {
	Object super; 
	Orc$String*  (*toString) (Orc$String **  __outRef__, Orc$Number *  self);
	long long  (*toLongLong) (Orc$Number *  self);
	int  (*toInt) (Orc$Number *  self);
	double  (*toDouble) (Orc$Number *  self);
	float  (*toFloat) (Orc$Number *  self);
};
Vtable_Orc$Number* Vtable_Orc$Number_init(Vtable_Orc$Number* pvt);
void Orc$Number_init_fields(Orc$Number *self);
void Orc$Number_init(Orc$Number *self, void *pOwner);
Orc$Number * Orc$Number_new(void *pOwner);
void Orc$Number_fini(Orc$Number *self);

Orc$String*  Orc$Number$toString(Orc$String **  __outRef__, Orc$Number *  self);
long long  Orc$Number$toLongLong(Orc$Number *  self);
int  Orc$Number$toInt(Orc$Number *  self);
double  Orc$Number$toDouble(Orc$Number *  self);
float  Orc$Number$toFloat(Orc$Number *  self);


// 虚表
struct tagVtable_Orc$Integer {
	Vtable_Orc$Number super;
};
//虚表实例
extern Vtable_Orc$Integer _vtable_Orc$Integer;

// class refc:1
struct tagOrc$Integer {
	Orc$Number super; 
	int  value ;
};
Vtable_Orc$Integer* Vtable_Orc$Integer_init(Vtable_Orc$Integer* pvt);
void Orc$Integer_init_fields(Orc$Integer *self);
void Orc$Integer_init(Orc$Integer *self, void *pOwner);
Orc$Integer * Orc$Integer_new(void *pOwner);
void Orc$Integer_fini(Orc$Integer *self);

Orc$String*  Orc$Integer$toString(Orc$String **  __outRef__, Orc$Integer *  self);
int  Orc$Integer$toLongLong(Orc$Integer *  self);
int  Orc$Integer$toInt(Orc$Integer *  self);
double  Orc$Integer$toDouble(Orc$Integer *  self);
float  Orc$Integer$toFloat(Orc$Integer *  self);


// 虚表
struct tagVtable_Orc$Boolean {
	Vtable_Orc$Number super;
};
//虚表实例
extern Vtable_Orc$Boolean _vtable_Orc$Boolean;

// class refc:1
struct tagOrc$Boolean {
	Orc$Number super; 
	bool  value ;
};
Vtable_Orc$Boolean* Vtable_Orc$Boolean_init(Vtable_Orc$Boolean* pvt);
void Orc$Boolean_init_fields(Orc$Boolean *self);
void Orc$Boolean_init(Orc$Boolean *self, void *pOwner);
Orc$Boolean * Orc$Boolean_new(void *pOwner);
void Orc$Boolean_fini(Orc$Boolean *self);

Orc$String*  Orc$Boolean$toString(Orc$String **  __outRef__, Orc$Boolean *  self);
long long  Orc$Boolean$toLongLong(Orc$Boolean *  self);
int  Orc$Boolean$toInt(Orc$Boolean *  self);
double  Orc$Boolean$toDouble(Orc$Boolean *  self);
float  Orc$Boolean$toFloat(Orc$Boolean *  self);


// 虚表
struct tagVtable_Orc$Float {
	Vtable_Orc$Number super;
};
//虚表实例
extern Vtable_Orc$Float _vtable_Orc$Float;

// class refc:1
struct tagOrc$Float {
	Orc$Number super; 
	float  value ;
};
Vtable_Orc$Float* Vtable_Orc$Float_init(Vtable_Orc$Float* pvt);
void Orc$Float_init_fields(Orc$Float *self);
void Orc$Float_init(Orc$Float *self, void *pOwner);
Orc$Float * Orc$Float_new(void *pOwner);
void Orc$Float_fini(Orc$Float *self);

Orc$String*  Orc$Float$toString(Orc$String **  __outRef__, Orc$Float *  self);
long long  Orc$Float$toLongLong(Orc$Float *  self);
int  Orc$Float$toInt(Orc$Float *  self);
double  Orc$Float$toDouble(Orc$Float *  self);
float  Orc$Float$toFloat(Orc$Float *  self);


// 虚表
struct tagVtable_Orc$Double {
	Vtable_Orc$Number super;
};
//虚表实例
extern Vtable_Orc$Double _vtable_Orc$Double;

// class refc:1
struct tagOrc$Double {
	Orc$Number super; 
	double  value ;
};
Vtable_Orc$Double* Vtable_Orc$Double_init(Vtable_Orc$Double* pvt);
void Orc$Double_init_fields(Orc$Double *self);
void Orc$Double_init(Orc$Double *self, void *pOwner);
Orc$Double * Orc$Double_new(void *pOwner);
void Orc$Double_fini(Orc$Double *self);

Orc$String*  Orc$Double$toString(Orc$String **  __outRef__, Orc$Double *  self);
long long  Orc$Double$toLongLong(Orc$Double *  self);
int  Orc$Double$toInt(Orc$Double *  self);
double  Orc$Double$toDouble(Orc$Double *  self);
float  Orc$Double$toFloat(Orc$Double *  self);


// 虚表
struct tagVtable_Orc$StructObj {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Orc$StructObj _vtable_Orc$StructObj;

// class refc:0
struct tagOrc$StructObj {
	Object super; 
	void *  pStruct ;
	MetaStruct *  metaStruct ;
	void  (*copyTo) (Orc$StructObj *  self, void *  dst);
};
Vtable_Orc$StructObj* Vtable_Orc$StructObj_init(Vtable_Orc$StructObj* pvt);
void Orc$StructObj_init_fields(Orc$StructObj *self);
void Orc$StructObj_init(Orc$StructObj *self, void *pOwner);
Orc$StructObj * Orc$StructObj_new(void *pOwner);
void Orc$StructObj_fini(Orc$StructObj *self);

void  Orc$StructObj$dtor(Orc$StructObj *  self);
void  Orc$StructObj$copyTo(Orc$StructObj *  self, void *  dst);

Orc$StructObj*  Orc$mkStructObj(Orc$StructObj **  __outRef__, MetaStruct *  metaStruct, void *  pStruct);
Orc$Integer*  Orc$mkInteger(Orc$Integer **  __outRef__, int  v);
Orc$Boolean*  Orc$mkBoolean(Orc$Boolean **  __outRef__, bool  v);
Orc$Double*  Orc$mkDouble(Orc$Double **  __outRef__, double  v);
Orc$Float*  Orc$mkFloat(Orc$Float **  __outRef__, float  val);
void  Orc$Orc_setField(Object *  obj, OrcMetaField *  mf, Object *  value);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
