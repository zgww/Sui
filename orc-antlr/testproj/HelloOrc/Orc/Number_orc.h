
typedef struct tagOrcLang$Number OrcLang$Number;
typedef struct tagVtable_OrcLang$Number Vtable_OrcLang$Number;
typedef struct tagOrcLang$Integer OrcLang$Integer;
typedef struct tagVtable_OrcLang$Integer Vtable_OrcLang$Integer;
typedef struct tagOrcLang$Boolean OrcLang$Boolean;
typedef struct tagVtable_OrcLang$Boolean Vtable_OrcLang$Boolean;
typedef struct tagOrcLang$Float OrcLang$Float;
typedef struct tagVtable_OrcLang$Float Vtable_OrcLang$Float;
typedef struct tagOrcLang$Double OrcLang$Double;
typedef struct tagVtable_OrcLang$Double Vtable_OrcLang$Double;


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef __Number_orc_h__
#define __Number_orc_h__

//include  importHeadCode
#include "Orc/Orc.h"
#include <stdlib.h>
#include "./String_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_OrcLang$Number {
	Vtable_Object super;
};
//虚表实例
extern Vtable_OrcLang$Number _vtable_OrcLang$Number;

// class
struct tagOrcLang$Number {
	Object super; 
	OrcLang$String*  (*toString) (OrcLang$String **  __outRef__, OrcLang$Number *  self);
	long long  (*toLongLong) (OrcLang$Number *  self);
	int  (*toInt) (OrcLang$Number *  self);
	double  (*toDouble) (OrcLang$Number *  self);
};
Vtable_OrcLang$Number* Vtable_OrcLang$Number_init(Vtable_OrcLang$Number* pvt);
void OrcLang$Number_init_fields(OrcLang$Number *self);
void OrcLang$Number_init(OrcLang$Number *self);
OrcLang$Number * OrcLang$Number_new();
void OrcLang$Number_fini(OrcLang$Number *self);

OrcLang$String*  OrcLang$Number$toString(OrcLang$String **  __outRef__, OrcLang$Number *  self);
long long  OrcLang$Number$toLongLong(OrcLang$Number *  self);
int  OrcLang$Number$toInt(OrcLang$Number *  self);
double  OrcLang$Number$toDouble(OrcLang$Number *  self);


// 虚表
struct tagVtable_OrcLang$Integer {
	Vtable_OrcLang$Number super;
};
//虚表实例
extern Vtable_OrcLang$Integer _vtable_OrcLang$Integer;

// class
struct tagOrcLang$Integer {
	OrcLang$Number super; 
	int  value ;
	OrcLang$String*  (*toString) (OrcLang$String **  __outRef__, OrcLang$Integer *  self);
	int  (*toLongLong) (OrcLang$Integer *  self);
	int  (*toInt) (OrcLang$Integer *  self);
	double  (*toDouble) (OrcLang$Integer *  self);
};
Vtable_OrcLang$Integer* Vtable_OrcLang$Integer_init(Vtable_OrcLang$Integer* pvt);
void OrcLang$Integer_init_fields(OrcLang$Integer *self);
void OrcLang$Integer_init(OrcLang$Integer *self);
OrcLang$Integer * OrcLang$Integer_new();
void OrcLang$Integer_fini(OrcLang$Integer *self);

OrcLang$String*  OrcLang$Integer$toString(OrcLang$String **  __outRef__, OrcLang$Integer *  self);
int  OrcLang$Integer$toLongLong(OrcLang$Integer *  self);
int  OrcLang$Integer$toInt(OrcLang$Integer *  self);
double  OrcLang$Integer$toDouble(OrcLang$Integer *  self);


// 虚表
struct tagVtable_OrcLang$Boolean {
	Vtable_OrcLang$Number super;
};
//虚表实例
extern Vtable_OrcLang$Boolean _vtable_OrcLang$Boolean;

// class
struct tagOrcLang$Boolean {
	OrcLang$Number super; 
	bool  value ;
	OrcLang$String*  (*toString) (OrcLang$String **  __outRef__, OrcLang$Boolean *  self);
	long long  (*toLongLong) (OrcLang$Boolean *  self);
	int  (*toInt) (OrcLang$Boolean *  self);
	double  (*toDouble) (OrcLang$Boolean *  self);
};
Vtable_OrcLang$Boolean* Vtable_OrcLang$Boolean_init(Vtable_OrcLang$Boolean* pvt);
void OrcLang$Boolean_init_fields(OrcLang$Boolean *self);
void OrcLang$Boolean_init(OrcLang$Boolean *self);
OrcLang$Boolean * OrcLang$Boolean_new();
void OrcLang$Boolean_fini(OrcLang$Boolean *self);

OrcLang$String*  OrcLang$Boolean$toString(OrcLang$String **  __outRef__, OrcLang$Boolean *  self);
long long  OrcLang$Boolean$toLongLong(OrcLang$Boolean *  self);
int  OrcLang$Boolean$toInt(OrcLang$Boolean *  self);
double  OrcLang$Boolean$toDouble(OrcLang$Boolean *  self);


// 虚表
struct tagVtable_OrcLang$Float {
	Vtable_OrcLang$Number super;
};
//虚表实例
extern Vtable_OrcLang$Float _vtable_OrcLang$Float;

// class
struct tagOrcLang$Float {
	OrcLang$Number super; 
	float  value ;
	OrcLang$String*  (*toString) (OrcLang$String **  __outRef__, OrcLang$Float *  self);
	long long  (*toLongLong) (OrcLang$Float *  self);
	int  (*toInt) (OrcLang$Float *  self);
	double  (*toDouble) (OrcLang$Float *  self);
};
Vtable_OrcLang$Float* Vtable_OrcLang$Float_init(Vtable_OrcLang$Float* pvt);
void OrcLang$Float_init_fields(OrcLang$Float *self);
void OrcLang$Float_init(OrcLang$Float *self);
OrcLang$Float * OrcLang$Float_new();
void OrcLang$Float_fini(OrcLang$Float *self);

OrcLang$String*  OrcLang$Float$toString(OrcLang$String **  __outRef__, OrcLang$Float *  self);
long long  OrcLang$Float$toLongLong(OrcLang$Float *  self);
int  OrcLang$Float$toInt(OrcLang$Float *  self);
double  OrcLang$Float$toDouble(OrcLang$Float *  self);


// 虚表
struct tagVtable_OrcLang$Double {
	Vtable_OrcLang$Number super;
};
//虚表实例
extern Vtable_OrcLang$Double _vtable_OrcLang$Double;

// class
struct tagOrcLang$Double {
	OrcLang$Number super; 
	double  value ;
	OrcLang$String*  (*toString) (OrcLang$String **  __outRef__, OrcLang$Double *  self);
	long long  (*toLongLong) (OrcLang$Double *  self);
	int  (*toInt) (OrcLang$Double *  self);
	double  (*toDouble) (OrcLang$Double *  self);
};
Vtable_OrcLang$Double* Vtable_OrcLang$Double_init(Vtable_OrcLang$Double* pvt);
void OrcLang$Double_init_fields(OrcLang$Double *self);
void OrcLang$Double_init(OrcLang$Double *self);
OrcLang$Double * OrcLang$Double_new();
void OrcLang$Double_fini(OrcLang$Double *self);

OrcLang$String*  OrcLang$Double$toString(OrcLang$String **  __outRef__, OrcLang$Double *  self);
long long  OrcLang$Double$toLongLong(OrcLang$Double *  self);
int  OrcLang$Double$toInt(OrcLang$Double *  self);
double  OrcLang$Double$toDouble(OrcLang$Double *  self);

OrcLang$Integer*  OrcLang$mkInteger(OrcLang$Integer **  __outRef__, int  v);
OrcLang$Boolean*  OrcLang$mkBoolean(OrcLang$Boolean **  __outRef__, bool  v);
OrcLang$Double*  OrcLang$mkDouble(OrcLang$Double **  __outRef__, double  v);
OrcLang$Float*  OrcLang$mkFloat(OrcLang$Float **  __outRef__, float  val);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
